/** Name: URL Downloader*/
#include<stdio.h>
#include<conio.h>

#include<Windows.h>
#include<urlmon.h>
#pragma comment(lib,"urlmon")

/*
创建一个进程函数：
	UINT WinExec(LPCSTR lpCmdLine,//命令行参数，直接给可执行程序路径也行
		UINT uCmdShow);//程序运行后的状态，常用的SW_SHOW显示运行，SW_HIDE隐藏运行

URL文件下载函数：
	HRESULT URLDownloadToFile(LPUNKOWN pCaller,
		LPCSTR szURL,//指定下载源URL
		LPCSTR szFileName,//指定下载到本地的文件位置
		DWORD dwReserved,
		LPBINDSTATUSCALLBACK lpfnCB);
	//其他参数给0、NULL即可
*/
int main(int argc, char * argv[])
{
	if (argc >= 3)
	{
		printf("文件正在下载中...\n");
		URLDownloadToFile(NULL, argv[1], argv[2], 0, NULL);
		printf("文件下载完毕！！\n");
		printf("是否打开下载的文件？1：是 else：否\n>/ ");
		if (getch() == '1')
			WinExec(argv[2], SW_SHOW);
	}
	else
	{
		printf("参数不正确！！\n");
		printf("参数：\n");
		printf("\t远程文件URL地址 本地保存文件名称");
		printf("例如：\n");
		printf("\thttps://www.baidu.com/ baidu.html");
	}
	return 0;
}