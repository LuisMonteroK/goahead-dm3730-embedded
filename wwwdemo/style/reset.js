/**
 * ����ҳ���õ��Ľű�
 */
var stime = document.getElementById("stime_stamp");
var etime = document.getElementById("etime_stamp");
var mtr_no = document.getElementById("mtr_no");
$(document).ready(
		function() {
			$("#btn").click(function() {
				$.get("/um/compara1.asp", function(result) {
					$("#log").html(result);
				});
			});
			$("#btnPost").click(
					function() {
						// ��ʾ
						$("#msgbox_wait").show("fade", {}, 1);
						$.post('/goform/get_tou',
								$("#history_tou").serialize(),
								function(result) {
									$("#tr_dat").html(result);
									// ��̬�������ҳ��ſ��Խ��������ͣ���¼�
									$("#history_tou tr").mouseover(function() {
										$(this).addClass("over");
										var rows = $(this).attr('relrow');
									});
									$("#history_tou tr").mouseout(function() {
										$(this).removeClass("over");
									});
									// ���֮������
									$("#msgbox_wait").hide("fade", {}, 1);
									$("#msgbox_ok").show("fade", {}, 1);
									$("#msgbox_ok").hide("fade", {}, 1000);
								});
					});
			$("#showLog").click(
					function() {
						// ��ʾ
						$("#msgbox_wait").show("fade", {}, 1);
						$.post('/goform/get_tou',
								$("#history_tou").serialize(),
								function(result) {
									$("#tr_dat").html(result);
									// ��̬�������ҳ��ſ��Խ��������ͣ���¼�
									$("#history_tou tr").mouseover(function() {
										$(this).addClass("over");
										var rows = $(this).attr('relrow');
									});
									$("#history_tou tr").mouseout(function() {
										$(this).removeClass("over");
									});
									// ���֮������
									$("#msgbox_wait").hide("fade", {}, 1);
									$("#msgbox_ok").show("fade", {}, 1);
									$("#msgbox_ok").hide("fade", {}, 1000);
								});
					});
		});