#ifndef _SYSPARAM_H_
#define _SYSPARAM_H_
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define SHOW_WHERE {					\
	printf("\n\n[File:%s Line:%d] Fun:%s\n\n",	\
	__FILE__, __LINE__, __FUNCTION__);	\
	}
enum eParam {//����,ʹ����Щ����Ҫ�˽���ṹ
    //��ϸ�μ�������Բ������ݽṹ�Ķ��塣
    // *** in sysspara.cfg ***
    meter_num,//������
    sioports_num,//��������
    netports_num,//��������
    pulse_num,//������
    monitor_port_num,//���Ӷ˿�����
    control_port_num,//���ƶ˿�����
    sioplan_num,//���ڷ�������
    // *** in file sioplan.cfg ***
    sioplanConfig,//�����������÷��� ����λ У��λ ֹͣλ �����ʵ�
    // *** in file mtrspara.cfg ***
    meter_Linename,//�����·����
    meter_addr,//���ַ
    meter_pwd,//������
    meter_commPort,//��˿�
    meter_commPlan,//���ڷ���
    MeterType,
    MeterProt,
    DLDot,
    XLDot,
    UDot,
    IDot,
    PDot,
    QDot,
    P3L4,
    Ue,
    Ie,
    Validflag,
    // *** in file netpara.cfg ***
    netport,//����˿ڱ�� �������ݿ�����
    ipaddr,//
    netMask,//��������
    Gateway,//���ص�ַ
    // *** in file monpara.cfg ***
    mon_commPort,//like ����
    mon_listenPort,//�����˿ں�
    mon_commPlan,
    mom_protType,
    mon_portAddr,//���Ӷ˿ڵ�ַ
    mon_check_time_Valiflag,
    mon_retransmit_flag,
    mon_retransmit_mtrnum,
    // *** in file ctlpara.cfg ***
    ctl_commPort,
    //
    __Retention__
};

class sysparam
{
public:
	sysparam(const std::string path="./para");
	sysparam(void);
	int len(eParam p)const;
	int read(eParam p,int len,void *const retval, int number)const;
	int read(eParam p,void *const retval)const;
	int write(eParam p,int len,void *const retval,int number=0)const;
private:
	std::string path;
private:
	bool isindexparam(eParam p)const;
	FILE* openfile(eParam p, const char *mod, int number=0)const;
	int modify_file( eParam p, const void *const retval)const;
};

#endif
