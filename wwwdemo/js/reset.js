/**
 * ����ҳ���õ��Ľű�
 */
var stime = document.getElementById("stime_stamp");
var etime = document.getElementById("etime_stamp");
var mtr_no = document.getElementById("mtr_no");
$(document).ready(function() {
	$("#btn").click(function() {
		$.get("/um/compara1.asp", function(result) {
			$("#log").html(result);
		});
	});
	$("#btnPost").click(function() {
		// ��ʾ
		$("#msgbox_wait").show("fade", {}, 1);
		$.post('/goform/get_tou',
			$("#history_tou").serialize(),
			function(result) {
				$("#tr_dat").html(result);
				// ��̬�������ҳ��ſ��Խ��������ͣ���¼�
				$("#history_tou tr").mouseover(function() {
					$(this).addClass("over");
					//var rows = $(this).attr('relrow');
				});
				$("#history_tou tr").mouseout(function() {
					$(this).removeClass("over");
				});
				// ���֮������
				$("#msgbox_wait").hide("fade", {}, 1000);
			});
	});
	//�ӷ��������ش�����־�ļ�
	$("#load_log").click(function() {
		// ��ʾ
		$("#log_wait").show("fade", {}, 1);
		$.post("/goform/load_log",
			"load",
			function(result) {
				$("#log_wait").hide("fade", {}, 1000);
				var b=document.getElementById("log_text");
				b.value=result;
				//$("#log_text").html("1231");
				//$("#log_text").html(result);
				// ���֮������
				
			});
	});
	//���ı����浽�������Ĵ�����־�ļ�
	$("#save_log").click(function () {
		var b=document.getElementById("log_text");
		if (b.value==""){
			//
			alert("�ı�����Ϊ��");
		}else{
			$("#log_wait").show("fade", {}, 1);
			$.post("/goform/save_log",
				$("#log_text").val(),
				function(result) {
					// ���֮������
					$("#log_wait").hide("fade", {}, 1000);
				});
		}

	});

});
