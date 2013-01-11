<html>
<head>
<title>Arm Home</title>
<!--   Copyright (c) Echon., 2006. All Rights Reserved. -->
<meta http-equiv="Pragma" content="no-cache" charset=gb2312>
<link rel="stylesheet" href="/style/normal_ws.css" type="text/css"></link>
<link rel="stylesheet" href="/style/sys.css" type="text/css"></link>
<link href="/style/menuExpandable3.css" rel="stylesheet" type="text/css"></link>
<script src="/style/wwyfunc.js" language='javascript' type='text/JavaScript'></script>
<!-- ����jquery������ʱ��ؼ�����Ҫ���ļ� -��ʼ -->
<link rel="stylesheet" media="all" type="text/css" href="/style/jquery-ui.css" />
<link rel="stylesheet" media="all" type="text/css" href="/style/jquery-ui-timepicker-addon.css" />
<script type="text/javascript" src="/js/jquery-1.8.3.js"></script>
<script type="text/javascript" src="/style/jquery-ui.min.js"></script>
<script type="text/javascript" src="/style/jquery-ui.min-zh-CN-GB2312.js"></script>
<script type="text/javascript" src="/style/jquery-ui-timepicker-addon.js"></script>
<script type="text/javascript" src="/style/jquery-ui-timepicker-zh-CN-GB2312.js"></script>
<script type="text/javascript" src="/style/jquery-ui-sliderAccess.js"></script>
<script type="text/javascript" src="/js/reset.js"></script>
<!-- ����jquery������ʱ��ؼ�����Ҫ���ļ� -���� -->
<% init_sysparam(); //����ϵͳ���� %>
</head>
<body>
  <br />
  <h1>���ܲ���</h1>
  <div id="tabs">
    <ul>
      <li><a href="#tabs_func">ϵͳ����</a></li>
      <li><a href="#tabs-log">��־</a></li>
      <li><a href="#tabs-monport-cfg">���Ӷ˿�����</a></li>
      <li><a href="#tabs-other">����</a></li>
    </ul>
    <div id="tabs_func">
      <form action="/goform/reset" method=post ID="resetform" name="resetform">
        <table class="sioplanTable" id=tbl_sysReset border="1" cellspacing="1" cellpadding="1">
          <thead>
            <tr>
              <th>���</th>
              <th>˵��</th>
              <th>����</th>
            </tr>
          </thead>
          <tbody>
            <tr class="sysTDNcLItemStyle">
              <td>1</td>
              <td>�����������¼��ع�Լ�ı�.</td>
              <td>
                <button class=reboot OnClick="reset_procotol();"></button>
              </td>
            </tr>
            <tr class="sysTDNcLItemStyle">
              <td>2</td>
              <td>����web������.</td>
              <td>
                <button class=reboot OnClick="reset_web();"></button>
              </td>
            </tr>
            <tr class="sysTDNcLItemStyle">
              <td>3</td>
              <td>�����������</td>
              <td>
                <button class=reboot OnClick="reset_sample();"></button>
              </td>
            </tr>
            <tr class="sysTDNcLItemStyle">
              <td>4</td>
              <td>�����ն˲���ϵͳ</td>
              <td>
                <button class=reboot OnClick="reset_web();"></button>
              </td>
            </tr>
          </tbody>
        </table>
        <p ALIGN="CENTER">
          <!--���ص������,�����ύform�������� -->
          <input class=hideinp type=text name=OpType value="" id="optype">
        </p>
      </form>
    </div>
    <!-- ###��ǩ2 ### -->
    <div id="tabs-log">
      <p ALIGN="CENTER">
        <button id="import_log">����</button>
        <button id="export_log">����</button>
        _______
        <button id="load_log" title="���ն˶�ȡ��־�ļ�.">��ȡ</button>
        <button id="save_log" title="���ı����浽�ն���־�ļ���.">����</button>
      </p>
      <!-- ����ȷ�϶Ի���1 -->
      <div id="dialog-confirm" class=dialog title="ȷ�Ͻ��޸ı��浽�ն���?">
        <span class="ui-icon ui-icon-alert" style="float: left; margin: 0 7px 20px 0;"></span>
        ��������Ὣ�ı����е����ݱ��浽�ն���־�ļ���,���ܳ���,����������.�Ƿ񱣴浽�ն�?
      </div>
      <img class="waiticon" id=log_wait></img>
      <textarea id=log_text class=log_txt></textarea>
    </div>
    <div id="tabs-monport-cfg">
      <p ALIGN="CENTER">
        <button id="import_monprot" title="������...">����</button>
        <button id="export_monprot" title="������...">����</button>
        _______
        <button id="load_monport" title="���ն˶�ȡ���Ӷ˿������ļ�(�ı���ʽ)">��ȡ</button>
        <button id="save_monport" title="���ı����浽�ն˼��Ӷ˿��ļ�">����</button>
      </p>
      <!-- ����ȷ�϶Ի���1 -->
      <div id="dialog-confirm-monport" class=dialog title="ȷ�Ͻ��޸ı��浽�ն���?">
        <span class="ui-icon ui-icon-alert" style="float: left; margin: 0 7px 20px 0;"></span>
        <p>
          ��������Ὣ�ı����е����ݱ��浽�ն˼��Ӷ˿��ļ���.
          <br>
          �ն���������Ч.�ò������ܳ���,����������.
          <br>
          �Ƿ񱣴浽�ն�?
        </p>
      </div>
      <img class="waiticon" id=monprot_wait></img>
      <textarea id=monport_text class=log_txt></textarea>
    </div>
    <div id="tabs-other">
    </div>
  </div>
  <form id="history_tou" name="history_tou">
    <p>
    <h1>��ȡ����������ʱ��:</h1>
    <br>
    <label>
      ���:
      <input type="text" name="mtr_no" id="mtr_no" size=3 value="0">
    </label>
    <label>
      ʱ�䷶Χ:
      <input type="text" name="stime" id="stime" readonly class=date title="ѡ��ʼʱ��">
    </label>
    <label>
      ~
      <input type="text" name="etime" id="etime" readonly class=date title="ѡ���ֹʱ��">
    </label>
    <br>
    <label>
      ʱ���(��):
      <input type="text" name="stime_stamp" id="stime_stamp" value="0" readonly>
    </label>
    <label>
      ~
      <input type="text" name="etime_stamp" id="etime_stamp" value="0" readonly>
    </label>
    <br>
    <label>
      ʱ��ƫ��(����)
      <input type="text" name="timezone" id="timezone" value="0" readonly>
      <input type="text" name="timezone2" id="timezone2" value="0" readonly>
    </label>
    <br>
  </form>
  <script language=javascript>
			var startDateTextBox = $('#stime');
			var endDateTextBox = $('#etime');
			var stime_stamp = document.getElementById("stime_stamp");
			var etime_stamp = document.getElementById("etime_stamp");
			var tz = document.getElementById("timezone");
			var tz2 = document.getElementById("timezone2");
			//��ʼʱ��ؼ�����������
			startDateTextBox.datetimepicker({
				maxDate : 0,
				controlType : 'select', //ѡ��ʽѡʱ��
				dateFormat : "yy-mm-dd", //���ڸ�ʽ
				//showSecond: true, //��ʾ��
				timeFormat : 'HH:mm z', //ʱ�̸�ʽ
				separator : ' ', //����ʱ�̷ָ��ַ�(��)
				//showTimezone: true, //��ʾʱ��
				//timezone: '+0800',    //Ĭ��ʱ��
				//����ر�(���)��ť�¼� 
				//�����ʼʱ�����ڽ���ʱ��,�򽫿�ʼʱ������Ϊ����ʱ�� 
				onClose : function(dateText, inst) {
					if (endDateTextBox.val() != '') {
						var testStartDate = startDateTextBox
								.datetimepicker('getDate');
						var testEndDate = endDateTextBox
								.datetimepicker('getDate');
						if (testStartDate > testEndDate)
							endDateTextBox.datetimepicker('setDate',
									testStartDate);
					} else {
						endDateTextBox.val(dateText);
					}
					var testStartDate = startDateTextBox
							.datetimepicker('getDate');
					stime_stamp.value = testStartDate.getTime() / 1000;
					//Date.parse(endDateTextBox.datetimepicker('getDate'))/1000;
				},
				onSelect : function(selectedDateTime) {//ѡ��ʱ�޶���ʼʱ��������ڽ���ʱ��
					endDateTextBox.datetimepicker('option', 'minDate',
							startDateTextBox.datetimepicker('getDate'));
					//tz.value=startDateTextBox.datetimepicker.timezone;
					var testStartDate = startDateTextBox
							.datetimepicker('getDate');
					tz.value = testStartDate.getTimezoneOffset();
					//����ת����λ��׼ʱ��,û��ʱ����Ϣ��.
					stime_stamp.value = testStartDate.getTime() / 1000;
					//Date.parse(startDateTextBox.datetimepicker('getDate'))/1000;
				}
			});
			//����ʱ��ؼ�����������
			endDateTextBox.datetimepicker({
				maxDate : 0,//����ѡ��δ��
				controlType : 'select', //ѡ��ʽѡʱ��
				dateFormat : "yy-mm-dd", //���ڸ�ʽ
				//showSecond: true, //��ʾ��
				timeFormat : 'HH:mm z', //ʱ�̸�ʽ
				separator : ' ', //����ʱ�̷ָ��ַ�(��)
				//showTimezone: true, //��ʾʱ��
				//timezone: '+0800',    //Ĭ��ʱ��
				onClose : function(dateText, inst) {//�ر�ʱ���ж�
					if (startDateTextBox.val() != '') {
						var testStartDate = startDateTextBox
								.datetimepicker('getDate');
						var testEndDate = endDateTextBox
								.datetimepicker('getDate');
						if (testStartDate > testEndDate)
							startDateTextBox.datetimepicker('setDate',
									testEndDate);
					} else {
						startDateTextBox.val(dateText);
					}
					var testEndDate = endDateTextBox.datetimepicker('getDate');
					etime_stamp.value = testEndDate.getTime() / 1000;
					//stime_stamp.value=
					//  Date.parse(startDateTextBox.datetimepicker('getDate'))/1000;
				},
				onSelect : function(selectedDateTime) {//ѡ��ʱ���ֹ��ѡ
					startDateTextBox.datetimepicker('option', 'maxDate',
							endDateTextBox.datetimepicker('getDate'));

					var testEndDate = endDateTextBox.datetimepicker('getDate');
					tz2.value = testEndDate.getTimezoneOffset();
					etime_stamp.value = testEndDate.getTime() / 1000;
				}
			});
		</script>
  <button class="ui-button" id="btn" title="������...">��ҳ�����</button>
  <button class="ui-button" id="btnPost" title="��ѯѡ��ʱ�κ�ָ����Ƶĵ�������">��ѯ</button>
  <button class="ui-button" id="showLog" title="�ӷ�����������־">�鿴��־</button>
  <img class="waiticon" id=msgbox_wait />
  <table class="sioplanTable" ID="history_tou" border="1" cellspacing="1" cellpadding="1">
    <thead>
      <tr>
        <th rowspan=2>���</th>
        <th rowspan=2>���</th>
        <th rowspan=2>ʱ��</th>
        <th colspan=5>�����й�</th>
        <th colspan=5>�����й�</th>
        <th colspan=5>�����޹�</th>
        <th colspan=5>�����޹�</th>
      </tr>
      <tr>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>ƽ</th>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>ƽ</th>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>ƽ</th>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>��</th>
        <th>ƽ</th>
        <th>��</th>
      </tr>
    </thead>
    <tbody id=tr_dat></tbody>
  </table>
</body>
</html>
