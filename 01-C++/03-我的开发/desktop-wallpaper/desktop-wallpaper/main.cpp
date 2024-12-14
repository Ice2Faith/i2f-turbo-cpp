#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include"VideoWallpaperHelper.h"
#include"CommandParser.h"

using namespace std;

void help(){
	printf("************************************\n");
	printf("�����ֽ���ø�������\n");
	printf("************************************\n");
	printf("�����б�\n");
	printf("\t[option] [hwnd]\n");
	printf("�������ͣ�\n");
	printf("\t[option] ��ʾҪִ�е�ѡ��\n");
	printf("\t\t-w|/w ��ʾ��ȡ�����ֽ���ڵľ��\n");
	printf("\t\t-s|/s ��ʾҪ����һ������HWND����Ϊ�����ֽ\n");
	printf("\t\t-p|/p �����������һ������PID���Ҷ�Ӧ��������HWND\n");
	printf("\t\t-h|/h �����������һ������HWND���Ҷ�Ӧ�Ľ���PID\n");
	printf("�÷�(���µ�*.exe������������)��\n");
	printf("\tֻ��ȡ�����\n");
	printf("\t\t*.exe -w\n");
	printf("\t\t*.exe /w\n");
	printf("\t������HWND=63544����Ϊ��ֽ��\n");
	printf("\t\t*.exe -s 63544\n");
	printf("\t\t*.exe /s 63544\n");
	printf("\t��ȡ����PID=26633��������HWND��\n");
	printf("\t\t*.exe -p 26633\n");
	printf("\t\t*.exe /p 26633\n");
	printf("\t��ȡ����HWND=6655�Ľ���PID��\n");
	printf("\t\t*.exe -h 6655\n");
	printf("\t\t*.exe /h 6655\n");
	system("pause");
}

HWND getHwndByPid(DWORD pid){
	HWND h = GetTopWindow(NULL);
	HWND ret = NULL;
	while (h){
		DWORD processId = NULL;
		DWORD threadId = GetWindowThreadProcessId(h, &processId);
		if (threadId != NULL){
			if (pid == processId && GetParent(h) == NULL && IsWindowVisible(h) == TRUE){
				ret = h;
				break;
			}
		}
		h = GetNextWindow(h, GW_HWNDNEXT);
	}
	return ret;
}

DWORD getPidByHwnd(HWND hwnd){
	DWORD processId = NULL;
	DWORD threadId = GetWindowThreadProcessId(hwnd, &processId);
	return processId;
}

int main(int argc, char * argv[]){
	cmd_init(argc, argv);

	if (cmd_get_count() == 0){
		help();
		return 0;
	}

	// wѡ�� ֱ����������ֽ���ڵľ��
	if (cmd_option_exists("w")){
		HWND deskHwnd = GetDesktopWallpaperWorkerHwnd();
		printf("%d", deskHwnd);
		return 0;
	}

	// sѡ�� ֱ������Ϊ�����ֽ����
	if (cmd_option_exists("s")){
		vector<string> args = cmd_option_args("s");
		if (args.size() > 0){
			const char * childHwndStr = args[0].data();
			HWND childHwnd = (HWND)atol(childHwndStr);

			HWND deskHwnd = GetDesktopWallpaperWorkerHwnd();
			// ����Ϊ�����ֽ���ڵ��Ӵ���
			SetParent(childHwnd, deskHwnd);
			// ȥ���߿�
			//SetWindowLong(childHwnd, GWL_STYLE, GetWindowLong(childHwnd, GWL_STYLE) - WS_CAPTION);
			HDC hdc = GetDC(NULL);
			int dwid = GetDeviceCaps(hdc, HORZRES);
			int dhei = GetDeviceCaps(hdc, VERTRES);
			int swid = GetSystemMetrics(SM_CXFULLSCREEN);
			int shei = GetSystemMetrics(SM_CYFULLSCREEN);
			// ���õ�����0��0����,��С����Ϊ�����С
			SetWindowPos(childHwnd, 0, 0, 0, max(dwid, swid), max(dhei, shei), SWP_NOZORDER);
			// �������
			ShowWindow(childHwnd, SW_MAXIMIZE);

			return 0;
		}
		else{
			printf("sѡ�� ȱ�ٲ���\n");
			help();
			return 0;
		}
	}

	// pѡ�� ֱ������ҵ��Ĵ��ھ��
	if (cmd_option_exists("p")){
		vector<string> args = cmd_option_args("p");
		if (args.size() > 0){
			const char * pidStr = args[0].data();
			DWORD pid = (DWORD)atol(pidStr);

			HWND findHwnd = getHwndByPid(pid);
			printf("%d", findHwnd);
			return 0;
		}
		else{
			printf("pѡ�� ȱ�ٲ���\n");
			help();
			return 0;
		}
	}


	// hѡ�� ֱ������ҵ��Ĵ��ھ��
	if (cmd_option_exists("h")){
		vector<string> args = cmd_option_args("h");
		if (args.size() > 0){
			const char * pidStr = args[0].data();
			HWND hwnd = (HWND)atol(pidStr);

			DWORD findPid = getPidByHwnd(hwnd);
			// ֱ������ҵ��Ľ���ID
			printf("%d", findPid);
			return 0;
		}
		else{
			printf("hѡ�� ȱ�ٲ���\n");
			help();
			return 0;
		}
	}

	help();
	
	return 0;
}