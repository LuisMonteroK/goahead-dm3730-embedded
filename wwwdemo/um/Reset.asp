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
<script type="text/javascript" src="/style/jquery-1.8.3.min.js"></script>
<script type="text/javascript" src="/style/jquery-ui.min.js"></script>
<script type="text/javascript" src="/style/jquery-ui.min-zh-CN-GB2312.js"></script>
<script type="text/javascript" src="/style/jquery-ui-timepicker-addon.js"></script>
<script type="text/javascript" src="/style/jquery-ui-timepicker-zh-CN-GB2312.js"></script>
<script type="text/javascript" src="/style/jquery-ui-sliderAccess.js"></script>
<!-- ����jquery������ʱ��ؼ�����Ҫ���ļ� -���� -->
<script type="text/javascript">
	var stime = document.getElementById("stime_stamp");
	var etime = document.getElementById("etime_stamp");
	var mtr_no = document.getElementById("mtr_no");
	$(document).ready(
			function() {
				$("#btn").click(function() {
					$.get("/um/compara1.asp", function(result) {
						$("#myDiv").html(result);
					});
				});
				$("#btnPost").click(
						function() {
							//��ʾ
							$("#msgbox_wait").show("fade", {}, 1);
							$.post('/goform/get_tou', $("#history_tou")
									.serialize(), function(result) {// ��̬�������ҳ��ſ��Խ��������ͣ���¼�
								$("#tr_dat").html(result);
								$("#history_tou tr").mouseover(function() {
									$(this).addClass("over");
									var rows = $(this).attr('relrow');
								});
								$("#history_tou tr").mouseout(function() {
									$(this).removeClass("over");
								});
								//���֮������
								$("#msgbox_wait").hide("fade", {}, 1);
								$("#msgbox_ok").show("fade", {}, 1);
								$("#msgbox_ok").hide("fade", {}, 1000);
							});
						});
			});
</script>
<% init_sysparam(); //����ϵͳ���� %>
</head>
<body>
  <br />
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
            <input type=image src="/graphics/Reset12.png" onmouseover="this.src='/graphics/Reset121.png';" onmouseout="this.src='/graphics/Reset12.png';" alt="Submit" OnClick="reset_procotol();">
          </td>
        </tr>
        <tr class="sysTDNcLItemStyle">
          <td>2</td>
          <td>����web������.</td>
          <td>
            <input type=image src="/graphics/Reset11.png" onmouseover="this.src='/graphics/Reset111.png';" onmouseout="this.src='/graphics/Reset11.png';" alt="Submit" OnClick="reset_web();">
          </td>
        </tr>
        <tr class="sysTDNcLItemStyle">
          <td>3</td>
          <td>�����������</td>
          <td>
            <input type=image src="/graphics/Reset13.png" onmouseover="this.src='/graphics/Reset131.png';" onmouseout="this.src='/graphics/Reset13.png';" alt="Submit" OnClick="reset_sample();">
          </td>
        </tr>
        <tr class="sysTDNcLItemStyle">
          <td>4</td>
          <td>�����ն˲���ϵͳ</td>
          <td>
            <input type=image src="/graphics/Reset11.png" onmouseover="this.src='/graphics/Reset111.png';" onmouseout="this.src='/graphics/Reset11.png';" alt="Submit" OnClick="reset_web();">
          </td>
        </tr>
      </tbody>
    </table>
    <p ALIGN="CENTER">
      <!--���ص������,�����ύform�������� -->
      <input class=hideinp type=text name=OpType value="" id="optype">
    </p>
  </form>
  
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
      <input type="text" name="stime" id="stime" readonly>
    </label>
    <label>
      ~
      <input type="text" name="etime" id="etime" readonly>
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
				//showSecond: true,	//��ʾ��
				timeFormat : 'HH:mm z', //ʱ�̸�ʽ
				separator : ' ', //����ʱ�̷ָ��ַ�(��)
				//showTimezone: true,	//��ʾʱ��
				//timezone: '+0800',		//Ĭ��ʱ��
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
					etime_stamp.value = testStartDate.getTime() / 1000;
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
				//showSecond: true,	//��ʾ��
				timeFormat : 'HH:mm z', //ʱ�̸�ʽ
				separator : ' ', //����ʱ�̷ָ��ַ�(��)
				//showTimezone: true,	//��ʾʱ��
				//timezone: '+0800',		//Ĭ��ʱ��
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
					//	Date.parse(startDateTextBox.datetimepicker('getDate'))/1000;
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
  <button id="btn">��ҳ�����</button>
  <button id="btnPost">��ѯ</button>
  <button id="showLog">�鿴��־</button>
  <div id="msgbox_wait" style="display: none;" class=msgbox_wait>
    <input type=image src="/style/images/wait.gif">
  </div>
  <div id="msgbox_ok" style="display: none;" class=msgbox_ok>���</div>
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
    <tbody id=tr_dat>
  </table>
  <p><% show_log(); %></p>
</body>
</html>
