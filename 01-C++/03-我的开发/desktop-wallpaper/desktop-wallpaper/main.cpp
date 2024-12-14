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
	printf("桌面壁纸设置辅助程序\n");
	printf("************************************\n");
	printf("参数列表：\n");
	printf("\t[option] [hwnd]\n");
	printf("参数解释：\n");
	printf("\t[option] 表示要执行的选项\n");
	printf("\t\t-w|/w 表示获取桌面壁纸窗口的句柄\n");
	printf("\t\t-s|/s 表示要将下一个参数HWND设置为桌面壁纸\n");
	printf("\t\t-p|/p 根据输入的下一个参数PID查找对应的主窗口HWND\n");
	printf("\t\t-h|/h 根据输入的下一个参数HWND查找对应的进程PID\n");
	printf("用法(以下的*.exe代表本程序名称)：\n");
	printf("\t只获取句柄：\n");
	printf("\t\t*.exe -w\n");
	printf("\t\t*.exe /w\n");
	printf("\t将窗口HWND=63544设置为壁纸：\n");
	printf("\t\t*.exe -s 63544\n");
	printf("\t\t*.exe /s 63544\n");
	printf("\t获取进程PID=26633的主窗口HWND：\n");
	printf("\t\t*.exe -p 26633\n");
	printf("\t\t*.exe /p 26633\n");
	printf("\t获取窗口HWND=6655的进程PID：\n");
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

	// w选项 直接输出桌面壁纸窗口的句柄
	if (cmd_option_exists("w")){
		HWND deskHwnd = GetDesktopWallpaperWorkerHwnd();
		printf("%d", deskHwnd);
		return 0;
	}

	// s选项 直接设置为桌面壁纸窗口
	if (cmd_option_exists("s")){
		vector<string> args = cmd_option_args("s");
		if (args.size() > 0){
			const char * childHwndStr = args[0].data();
			HWND childHwnd = (HWND)atol(childHwndStr);

			HWND deskHwnd = GetDesktopWallpaperWorkerHwnd();
			// 设置为桌面壁纸窗口的子窗口
			SetParent(childHwnd, deskHwnd);
			// 去除边框
			//SetWindowLong(childHwnd, GWL_STYLE, GetWindowLong(childHwnd, GWL_STYLE) - WS_CAPTION);
			HDC hdc = GetDC(NULL);
			int dwid = GetDeviceCaps(hdc, HORZRES);
			int dhei = GetDeviceCaps(hdc, VERTRES);
			int swid = GetSystemMetrics(SM_CXFULLSCREEN);
			int shei = GetSystemMetrics(SM_CYFULLSCREEN);
			// 设置到桌面0，0坐标,大小设置为桌面大小
			SetWindowPos(childHwnd, 0, 0, 0, max(dwid, swid), max(dhei, shei), SWP_NOZORDER);
			// 设置最大化
			ShowWindow(childHwnd, SW_MAXIMIZE);

			return 0;
		}
		else{
			printf("s选项 缺少参数\n");
			help();
			return 0;
		}
	}

	// p选项 直接输出找到的窗口句柄
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
			printf("p选项 缺少参数\n");
			help();
			return 0;
		}
	}


	// h选项 直接输出找到的窗口句柄
	if (cmd_option_exists("h")){
		vector<string> args = cmd_option_args("h");
		if (args.size() > 0){
			const char * pidStr = args[0].data();
			HWND hwnd = (HWND)atol(pidStr);

			DWORD findPid = getPidByHwnd(hwnd);
			// 直接输出找到的进程ID
			printf("%d", findPid);
			return 0;
		}
		else{
			printf("h选项 缺少参数\n");
			help();
			return 0;
		}
	}

	help();
	
	return 0;
}