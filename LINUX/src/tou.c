/**
 * @file tou.c 电量历史数据文件,=>所有历史数据,电量,瞬时量,需量
 * @param mtr_no
 * @param range
 * @param tou
 * @return
 */
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include "../uemf.h"
#include "../wsIntrn.h"
#include "tou.h"
#include "web_err.h"
#include "conf.h"
#include "define.h"
///仅在本文件中使用的静态函数定义.
static int webRece_history_data(webs_t wp);
static int check_mtrnum(int mtrnum);
static int
add_mtr_tou(jsObj *oMtr, int mtrNo, char const *abTou,
	TimeRange const range,const char *enable);
static void timeToNextDayMorning(struct tm *stTime, time_t *time_t);
static int
webWrite_toudata_json(jsObj *OneTimeTou, time_t t2, const stTou tou,
	int i, int mtr_no,const char *enable);
static int webWriteOneTI_json(jsObj *o, Ti_Category ti,const char *enable);
static int webWrite1Tou_json(jsObj *o, const stTou tou,const char *enable);
//
static char * float2string(uint8_t const float_array[4], char * strval);
static int isRightDate(const stTouFilehead filehead, struct tm t);
static int
load_tou_dat(jsObj *oMtr, uint32_t mtr_no,
	TimeRange const range,const char* enable);
#if 0
/**
 * 提交表单,历史电量数据.操作:获取.参数:时间范围,表号.
 * @param wp
 * @param path
 * @param query
 */
void form_history_tou(webs_t wp, char_t *path, char_t *query)
{
	PRINT_FORM_INFO;
	char * strmtr_no = websGetVar(wp, T("mtr_no"), T("0"));
	char * stime_t = websGetVar(wp, T("stime_stamp"), T("0"));
	char * etime_t = websGetVar(wp, T("etime_stamp"), T("0"));
	char * strtz = websGetVar(wp, T("timezone"), T("0"));
	int tz = 0;
	//printf("时间戳范围:%s~%s\n", stime_t, etime_t);
	TimeRange tr;
	int ret;
	int mtr_no = 0;
	stTou tou;
	memset(&tou, 0x00, sizeof(stTou));
	ret = sscanf(strmtr_no, "%d", &mtr_no);
	if (ret!=1) {
		web_err_proc(EL);
	}
	ret = sscanf(stime_t, "%ld", &tr.s);
	if (ret!=1) {
		web_err_proc(EL);
	}
	ret = sscanf(etime_t, "%ld", &tr.e);
	if (ret!=1) {
		web_err_proc(EL);
	}
	ret = sscanf(strtz, "%d", &tz);
	if (ret!=1) {
		web_err_proc(EL);
	}
	tr.s += (tz*60);
	tr.e += (tz*60);
	//printf("时间戳 (数值) 范围:%ld~%ld 表号:%d\n", tr.s, tr.e, mtr_no);
	websHeader_pure(wp);
	ret = load_tou_dat(mtr_no, tr, &tou, wp);
	if (ret==ERR) {
		web_err_proc(EL);
	}
	websDone(wp, 200);
	return;
}
#else
void form_history_tou(webs_t wp, char_t *path, char_t *query)
{
	PRINT_FORM_INFO;
	websHeader_pure(wp);
	char * action = websGetVar(wp, T("action"), T("null"));
	if (strcmp(action, "get")==0) {
		webRece_history_data(wp);
	} else {
		web_err_proc(EL);
	}
	websDone(wp, 200);
	return;
}
#endif
static int webRece_history_data(webs_t wp)
{
	int i;int ret;
	char * stime_t = websGetVar(wp, T("stime_stamp"), T("0"));
	char * etime_t = websGetVar(wp, T("etime_stamp"), T("0"));
	char * strtz = websGetVar(wp, T("timezone"), T("0"));
	char * abMtr = websGetVar(wp, T("mtr"), T(""));
	char * datatType =websGetVar(wp, T("type"), T(""));
	char * abTou = websGetVar(wp, T("tou"), T(""));
	char * abQr = websGetVar(wp, T("qr"), T(""));
	char * abV = websGetVar(wp, T("v"), T(""));
	char * abI = websGetVar(wp, T("i"), T(""));
	char * abP = websGetVar(wp, T("p"), T(""));
	char * abQ = websGetVar(wp, T("q"), T(""));
	char * abPf = websGetVar(wp, T("pf"), T(""));
	char * abF = websGetVar(wp, T("f"), T(""));     //频率貌似暂时没用
	char * abMaxn = websGetVar(wp, T("maxn"), T(""));
	int mtrnum = strlen(abMtr);
	int tz = 0;
	if (check_mtrnum(mtrnum)<0) {
		web_err_proc(EL);
	}
	TimeRange tr;
	ret = sscanf(stime_t, "%ld", &tr.s);
	if (ret!=1) {
		web_err_proc(EL);
	}
	ret = sscanf(etime_t, "%ld", &tr.e);
	if (ret!=1) {
		web_err_proc(EL);
	}
	ret = sscanf(strtz, "%d", &tz);
	if (ret!=1) {
		web_err_proc(EL);
	}
	tr.s += (tz);
	tr.e += (tz);
	jsObj oHistoryData = jsonNew();     //{[{表1},{表2}],终端属性=xx,终端属性2=yy}
	jsObj aMtr = jsonNewArray();     //{[表0,表1...]}
	jsObj oMtr = jsonNew();     //{[it],表属性}
	//回显查询信息,增强可靠性
	jsonAdd(&oHistoryData, "rtu_info",
	                "this is rtu info,like version etc..");
	jsonAdd(&oHistoryData, "abMtr", abMtr);     //将参数回传,保证不出错
	jsonAdd(&oHistoryData, "abTou", abTou);
	jsonAdd(&oHistoryData, "abQr", abQr);
	jsonAdd(&oHistoryData, "abV", abV);
	jsonAdd(&oHistoryData, "abI", abI);
	jsonAdd(&oHistoryData, "abP", abP);
	jsonAdd(&oHistoryData, "abQ", abQ);
	jsonAdd(&oHistoryData, "abPf", abPf);
	jsonAdd(&oHistoryData, "abF", abF);
	jsonAdd(&oHistoryData, "abMaxn", abMaxn);
	for (i = 0; i<mtrnum; i++) {     //遍历所有表
		if (abMtr[i]!='1') {
			continue;
		}
		add_mtr_tou(&oMtr, i, abTou, tr,abTou);
		//
		jsonAdd(&aMtr, NULL, oMtr);
		jsonClear(&oMtr);
	}
	jsonAdd(&oHistoryData, "mtr", aMtr);     //添加整个表对象
	printf(WEBS_DBG"历史数据:%s\n",oHistoryData);
	wpsend(wp, oHistoryData);
	jsonFree(&oMtr);
	jsonFree(&aMtr);
	jsonFree(&oHistoryData);
	return 0;
}
//一个表(mtrNo)在一段时间范围(range)内特定电量项目(abTou)保存到oMtr json数组中.
static int
add_mtr_tou(jsObj *oMtr, int mtrNo, char const *abTou,
	TimeRange const range,const char *enable)
{
	if (strlen(abTou)!=TOUNUM) {
		web_err_proc(EL);
		return -100;
	}
	jsObj aOneDate = jsonNewArray();     //一个电量数据=[电量,有效位...]
	jsObj aTou = jsonNewArray();     //[正有,反有,正无,反无]
	load_tou_dat(&aTou, mtrNo, range,enable);
	jsonAdd(oMtr, "tou", aTou);
#if DEBUG_PRINT_REALTIME_TOU_DAT
	printf(WEBS_DBG"tou:%s\n",*oMtr);
#endif
	jsonFree(&aOneDate);
	jsonFree(&aTou);
	return 0;
}
/**
 * 将时间推至次日凌晨0点,用于检索到下一个文件
 * @param stTime 时间结构体
 * @param time_t 时间戳(32位!bug Y2038)
 */
static void timeToNextDayMorning(struct tm *stTime, time_t *time_t)
{
	stTime->tm_hour = 0;
	stTime->tm_min = 0;
	stTime->tm_sec = 0;
	*time_t = mktime(stTime);
	*time_t += (60*60*24);
}
///简单检查表数量合法性
static int check_mtrnum(int mtrnum)
{
	if (mtrnum<=0) {
		web_errno = eno_realtime_tou_mtrnum_too_small;
		return -1000;
	}
	if (mtrnum>MAXMETER) {
		web_errno = eno_realtime_tou_mtrnum_too_big;
		return -1002;
	}
	return 0;
}
/**
 * 读取一个电表的一段时间段的电量数据.
 * 这个函数思路十分难以理解.
 * 主要是按照时间戳,以一分钟为最小刻度依次从开始时刻到结束时刻遍历一遍.
 * 获取采样周期,如5分钟,则可以以5分钟为最小刻度遍历,速度更快.
 * 遍历过程中有一种比较特殊的情况:
 * 1. 开始时刻不是周期的整数倍.
 * 	如01月01日00时01分开始,读取文件mtr0010101之后发现周期是5分钟.
 * 	那个需要将起始时刻向上园整到5分钟的整数倍,即从01月01日00时05分这个时刻开始.
 * 	之后就可以按照5分钟递增了.
 * 2. 开始时刻为一日较晚时刻,采样跨天.
 * 	如01月01日23时59分开始,读取文件mtr0010101之后得到采样周期5分钟.
 * 	那么23:59加5分钟就到了次日.所以应该返回打开下一个文件mtr0010102.
 * 	然后从01月02日00时00分开始,以5分钟为一个周期开始读取.
 * 3. 在不同的天中采样周期有所变更.
 * 	程序始终以min{当前周期,文件中读取的周期}为步距递增.所以不同天不同周期没问题.
 * 4. 在同一天中变更采样周期. @bug
 * 	无法判断,因为一天就保存一个周期到文件头中.而且文件的程度计算必然出错.
 * @param[in] range
 * @param[in] mtr_no
 * @param[in] ptou
 * @param[out] wp 写入到这个页面
 * @return
 * @todo 分解,流程较为复杂
 */
static int
load_tou_dat(jsObj *oMtr, uint32_t mtr_no,
	TimeRange const range,const char *enable)
{
	stTouFilehead filehead;
	if (range.e<range.s) {
		web_errno = tou_timerange_err;
		return ERR;
	}
	if (range.e==0) {
		web_errno = tou_stime_err;
		return ERR;
	}
	if (range.e==0) {
		web_errno = tou_etime_err;
		return ERR;
	}
	char file[256] = { 0 };
	struct tm stTime;
	struct tm stToday_0;     //今日凌晨00点00分
	time_t today_0_t;
	time_t start_t = range.s;     //开始时刻
	time_t end_t = range.e;     //结束时刻
	time_t t2;     //时刻
	time_t minCycle_t = 0;
	stTou tou;
	memset(&tou, 0x0, sizeof(stTou));
	FILE*fp;
	int flen;
	int i = 0;
	//从开始时刻到结束时刻,按分钟遍历,步距为周期,可变.[start,end]两边闭区间
	for (t2 = start_t; t2<=end_t; /*t2 += (mincycle * 60)*/) {
		Start:
		#if __arm__ ==2
		gmtime_r(&t2,&stTime);
		gmtime_r(&t2,&stToday_0);
//		printf("gmtime_r %02d-%02d %02d:%02d %s stTime.tm_gmtoff=%d \n",
//				t.tm_mon+1,stTime.tm_mday,stTime.tm_hour,stTime.tm_min,
//				stTime.tm_zone,stTime.tm_gmtoff);
#else
		localtime_r(&t2, &stTime);
		localtime_r(&t2, &stToday_0);
#endif
		sprintf(file, "%s/mtr%03d%02d%02d.%s", TOU_DAT_DIR, mtr_no, 0,
		                stTime.tm_mday, TOU_DAT_SUFFIX);
		fp = fopen(file, "r");
		if (fp==NULL ) {     //这一天没有数据,直接跳到次日零点,这不是错误
			printf(WEBS_INF"%d:%04d-%02d-%02d没有数据文件\n",
			                mtr_no, stTime.tm_year+1900, stTime.tm_mon+1
			                                , stTime.tm_mday);
			web_errno = open_tou_file;
			//到下一天的凌晨,即下一个文件.
			timeToNextDayMorning(&stTime, &t2);
			continue;
		}
		fseek(fp, 0, SEEK_END);
		flen = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		int n = fread(&filehead, sizeof(stTouFilehead), 1, fp);
		if (n!=1) {
			web_errno = read_tou_file_filehead;
			fclose(fp);
			timeToNextDayMorning(&stTime, &t2);
			continue;
		}
		///@note 检查文件头中是否和请求的日期相一致.
		if (isRightDate(filehead, stTime)==0) {     //这也不算错误,最多算信息.
			fclose(fp);
			timeToNextDayMorning(&stTime, &t2);
			continue;
		}
		int cycle = (filehead.save_cycle_hi*256)
		                +filehead.save_cycle_lo;
		minCycle_t = cycle;
		//stTou at[24 * 60 / cycle];
		int t_mod = t2%(minCycle_t*60);     //向上园整至采样周期.
		if (t_mod!=0) {     //需要园整
			t2 += (minCycle_t*60-t_mod);
		}
		//}
		/**@note 判断开始时间+周期是否跨度到了第二天,如果跨度到第二天则需要
		 打开另一个(下一天)数据文件.
		 */
		stToday_0.tm_hour = 0;
		stToday_0.tm_min = 0;
		stToday_0.tm_sec = 0;
		today_0_t = mktime(&stToday_0);
		if (t2-today_0_t>=(60*60*24)) {     //t2已经时间跨过本日了.次日则文件等等需要重新打开.
			fclose(fp);
			goto Start;
		}
		///移动文件指针,指向开始的数据结构.
		int DeltaSec = t2-today_0_t;     //本采样时刻举今日凌晨几秒
		int NumCycle = DeltaSec/(minCycle_t*60);     //从凌晨开始向后偏移几个采样周期
		int offset = sizeof(stTou)*NumCycle;     //每个样本长度*采样个数
		fseek(fp, offset, SEEK_CUR);     ///当前位置为除去文件头的第一个数据体.

		if (ftell(fp)>=flen) {
			printf(WEBS_WAR"本日的数据不够.filesize=%d,fseek=%ld:%s\n", flen,
			                ftell(fp), file);
			t2 += (minCycle_t*60);
			fclose(fp);
			continue;
		}
		while (ftell(fp)<flen&&t2<=end_t) {
			memset(&tou, 0x0, sizeof(stTou));
			//t_cur += cycle * 60;
			int n = fread(&tou, sizeof(stTou), 1, fp);
			if (n!=1) {
				web_errno = read_tou_file_dat;
				return ERR;
			}
			//成功
			webWrite_toudata_json(oMtr,t2, tou, i, mtr_no,enable);
			i++;
			t2 += (minCycle_t*60);
		}     // end while 在一个文件中
		fclose(fp);
	}     // end for
	return 0;
}

/**
 *
 * @param OneTimeTou
 * @param t2
 * @param tou
 * @param i
 * @param mtr_no
 * @param enable
 * @return
 */
static int
webWrite_toudata_json(jsObj *OneTimeTou, time_t t2, const stTou tou,
	int i, int mtr_no,const char *enable)
{
	struct tm t;
#if __arm__ ==2
	gmtime_r(&t2,&t);
#else
	localtime_r(&t2, &t);
#endif
	jsObj oneRecord=jsonNewArray();//一条记录(某个表一个时刻所有电量)
	char tmp[128];
	jsonAdd(&oneRecord, NULL, toStr(tmp, "%d", mtr_no)); //表号
	jsonAdd(&oneRecord, NULL,
	                toStr(tmp, "%04d-%02d-%02d %02d:%02d:%02d",
	                                t.tm_year+1900,
	                                t.tm_mon+1, t.tm_mday, t.tm_hour,
	                                t.tm_min, t.tm_sec, t.tm_zone));
	webWrite1Tou_json(&oneRecord, tou,enable);
	jsonAdd(OneTimeTou,NULL,oneRecord);
	jsonClear(&oneRecord);
	return 0;
}

/**
 * 将由4个字节型数组组成的浮点型转化为最短的字符输出.
 * 应为websWrite仅实现了%d和%s,所以必须转化成字符串.
 * @param float_array
 * @param strval
 * @return
 */
static char * float2string(uint8_t const float_array[4], char * strval)
{
#if __arm__ ==1
	/*arm-linux-gcc会优化掉下面的 #else 的方式. - -
	 * 而且是优化掉第二次调用,第一次调用得出的数值还是对的
	 * 所以只能使用这种不优雅的方式防止优化掉强制类型转换
	 */
	typedef union kf {
		char tmp[4];
		float fot;
	}stFloat;
	stFloat f;
	f.tmp[0]=float_array[0];
	f.tmp[1]=float_array[1];
	f.tmp[2]=float_array[2];
	f.tmp[3]=float_array[3];
	sprintf(strval, "%g", f.fot);
	//float f2=*(float*) (&float_array[0]);
	//sprintf(strval, "%g", f2);
#else
	sprintf(strval, "%g", *(float*) (&float_array[0]));
#endif
	return strval;
}
/**
 *
 * @param o
 * @param ti
 * @param enable
 * @return
 */
static int webWriteOneTI_json(jsObj *o, Ti_Category ti,const char *enable)
{
	char strval[32];
	char tmp[32];
	jsObj aTi=jsonNewArray();
	printf(WEBS_DBG"使能:%s\n",enable);
	if(enable[0]=='1'){
		printf(WEBS_DBG"总采集\n");
		jsonAdd(&aTi,NULL,float2string(ti.total.fake_float_val, strval));
		jsonAdd(&aTi,NULL,toStr(tmp,"%d",ti.total.iv));
		jsonAdd(o,NULL,aTi);
		jsonClear(&aTi);
	}
	if(enable[1]=='1'){
		printf(WEBS_DBG"尖采集\n");
		jsonAdd(&aTi,NULL,float2string(ti.tip.fake_float_val, strval));
		jsonAdd(&aTi,NULL,toStr(tmp,"%d",ti.tip.iv));
		jsonAdd(o,NULL,aTi);
		jsonClear(&aTi);
	}
	if(enable[2]=='1'){
		printf(WEBS_DBG"峰采集\n");
		jsonAdd(&aTi,NULL,float2string(ti.peak.fake_float_val, strval));
		jsonAdd(&aTi,NULL,toStr(tmp,"%d",ti.peak.iv));
		jsonAdd(o,NULL,aTi);
		jsonClear(&aTi);
	}
	if(enable[3]=='1'){
		printf(WEBS_DBG"平采集\n");
		jsonAdd(&aTi,NULL,float2string(ti.flat.fake_float_val, strval));
		jsonAdd(&aTi,NULL,toStr(tmp,"%d",ti.flat.iv));
		jsonAdd(o,NULL,aTi);
		jsonClear(&aTi);
	}
	if(enable[4]=='1'){
		printf(WEBS_DBG"谷采集\n");
		jsonAdd(&aTi,NULL,float2string(ti.valley.fake_float_val, strval));
		jsonAdd(&aTi,NULL,toStr(tmp,"%d",ti.valley.iv));
		jsonAdd(o,NULL,aTi);
		jsonClear(&aTi);
	}
	jsonFree(&aTi);
	return 0;
}

//写一条电量Tou数据
static int webWrite1Tou_json(jsObj *o, const stTou tou,const char *enable)
{
	webWriteOneTI_json(o, tou.FA,&enable[0]);     ///正向有功
	webWriteOneTI_json(o, tou.RA,&enable[5]);     ///正向无功
	webWriteOneTI_json(o, tou.FR,&enable[10]);     ///反向有功
	webWriteOneTI_json(o, tou.RR,&enable[15]);     ///反向无功
	return 0;
}
/**
 * 通过比较文件头中的日期字节和请求的日期,判断是否是正确的日期,没有差几个月
 * @param filehead
 * @param t
 * @return
 */
static int isRightDate(const stTouFilehead filehead, struct tm t)
{
	if (filehead.month!=t.tm_mon+1) {
		return 0;
	}
	if (filehead.year+2000!=t.tm_year+1900) {
		return 0;
	}
	return 1;
}
