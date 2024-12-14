#include <string.h>
#include <stdio.h>
#include<conio.h>
#include<graphics.h>
#include"GameKeyTool.h"
typedef int FILE_ERROR;                                             //文件处理状态信号
#define FILE_SUCCESS 0                                              //正常处理
#define FILE_INVALID 1                                              //出现文件无效
#define FILE_NOT_FILE 2                                             //无文件传入
#define FILE_NOT_COMBINE 3                                          //文件没有被组合
#define FILE_OVERSTEP_MAXSIZE 4                                     //组合后文件会超过4G
char ComFlag[5] = { "FCOM" };                                           //组合文件标志
typedef int PATH_INFO;                                              //定义文件路径信息获取类型
#define PATH_FATHER 0                                               //获取文件父目录
#define PATH_NAME 1                                                 //获取文件名称（不包含后缀和父路径）
#define PATH_TAIL 2                                                 //获取文件后缀，包含.
void GetPathInfo(char * path, char * save, PATH_INFO infotype);       //获取文件信息，传入文件路径，保存位置，需要的信息类型
/*返回处理转态，传入文件个数，文件名，新文件名，是否需要移除源文件*/
FILE_ERROR FilesCombine(int counter, char * files[], char * newFileName, int needRemoveSource);
/*返回处理转态，传入文件名，是否需要移除源文件*/
FILE_ERROR FileSplit(char * fileName, int needRemoveSource, int * retcounter, char * retfiles[]);

int LoadImageFileCombine(char * path);
void ImageKeepZoom();
void ImageFullZoom();
void InitApp();
void FullScreen();
void ZoomScreen();
void LoadFileRound(char * file);
void DrawPicture();
void KeyStateDeal();
void SpeedCheck();
int Meau();
void Help();
void BuildCombine(int counter, char * files[]);

#define MAXLEN 512
#define MAXNAMELEN 1024
int SX = GetSystemMetrics(SM_CXSCREEN);
int SY = GetSystemMetrics(SM_CYSCREEN);

char filebody[MAXLEN][MAXNAMELEN] = { 0 };
int filecounter = 0;
char * files[MAXLEN] = { 0 };
IMAGE * img;
HWND hwnd;

int round = 0;
int Stime = 800;
bool FullDisplay = false;
bool FullScreenDis = false;
int main(int argc, char * argv[])
{
	InitApp();
	while (true)
	{
		solidrectangle(0, 0, SX, SY);
		int sel = Meau();
		solidrectangle(0, 0, SX, SY);
		switch (sel)
		{
		case 0:
			exit(0);
			break;
		case 1:
		{
				  outtextxy(SX * 40 / 100, SY / 2, "资源加载中...");
				  if (argc > 1)
					  LoadFileRound(argv[1]);
				  else
					  LoadFileRound(NULL);
		}
			break;
		case 2:
		{
				  if (argc > 1)
				  {
					  outtextxy(SX * 30 / 100, SY * 30 / 100, "请稍后...");
						BuildCombine(argc-1, &argv[1]);
						outtextxy(SX * 30 / 100, SY * 40 / 100, "文件合并结束");
				  }
				  else
				  {
					  outtextxy(SX * 20 / 100, SY *10/100, "没有任何文件可以合并哦！");
					  outtextxy(SX * 20 / 100, SY * 20 / 100, "合并文件步骤：");
					  outtextxy(SX * 20 / 100, SY * 30 / 100, "1.选择多个文件");
					  outtextxy(SX * 20 / 100, SY * 40 / 100, "2.将选中文件拖动到本程序图标上进行启动");
					  outtextxy(SX * 20 / 100, SY * 50 / 100, "3.进行合并操作");
					  outtextxy(SX * 20 / 100, SY * 60 / 100, "支持的格式：");
					  outtextxy(SX * 20 / 100, SY * 70/ 100, "jpg / png / bmp / gif / tif / emf / wmf / ico");
					  outtextxy(SX * 20 / 100, SY * 80 / 100, " gif 格式的图片仅加载第一帧");
				  }
				  outtextxy(SX * 40 / 100, SY * 90 / 100, "按任意键继续");
				  getch();
		}
			break;
		case 3:
			Help();
			break;
		}
		if (sel == 1)
			break;
	}
	
	ImageKeepZoom();
	long nowtime = GetTickCount();
	long beforetime = nowtime;
	long keychecktime = nowtime;
	long speedtime = nowtime;
	while (true)
	{
		nowtime = GetTickCount();
		if (nowtime - beforetime > Stime)
		{
			beforetime = nowtime;
			DrawPicture();
		}
		if (IsKeyDown(VK_ESCAPE))
			break;
		if (nowtime - keychecktime > 20)
		{
			keychecktime = nowtime;
			KeyStateDeal();
		}
		if (nowtime - speedtime > 150)
		{
			speedtime = nowtime;
			SpeedCheck();
		}


		Sleep(3);
	}
	for (int i = 0; i < filecounter; i++)
	{
		remove(filebody[i]);
	}
	closegraph();
	return 0;
}
int Meau()
{
	outtextxy(SX * 45 / 100, SY * 10 / 100, "文件轮播器");
	outtextxy(SX * 40 / 100, SY * 20 / 100, "1.开始轮播图片");
	outtextxy(SX * 40 / 100, SY * 30 / 100, "2.创建轮播文件");
	outtextxy(SX * 40 / 100, SY * 40 / 100, "3.获取使用帮助");
	outtextxy(SX * 40 / 100, SY * 50 / 100, "0.退出当前程序");
	char sel = '\0';
	while (sel<'0' || sel>'3')
		sel = getch();
	return (int)(sel - '0');
}
void Help()
{
	outtextxy(SX * 35 / 100, 0 , "     Help & Question");
	outtextxy(SX * 30 / 100, SY * 10 / 100, "Ctrl+Space: 自适应/拉伸显示");
	outtextxy(SX * 30 / 100, SY * 20 / 100, "Ctrl+M    : 全屏/自适应大小");
	outtextxy(SX * 30 / 100, SY * 30 / 100, "Ctrl+UP   : 加快轮播速度");
	outtextxy(SX * 30 / 100, SY * 40 / 100, "Ctrl+DOWN : 减慢轮播速度");
	outtextxy(SX * 30 / 100, SY * 50 / 100, "ESC       : 退出程序");
	outtextxy(SX * 5 / 100, SY * 60 / 100, "轮播你可以直接拖动轮播文件到本程序图标上启动快捷打开");
	outtextxy(SX * 5 / 100, SY * 70 / 100, "也可以先打开程序后输入轮播文件名称，需要带后缀");
	outtextxy(SX * 5 / 100, SY * 80 / 100, "创建轮播文件必须把图片文件多选后拖到图标上启动才能创建");
	outtextxy(SX * 30 / 100, SY * 90 / 100, "按任意键继续");
	getch();
}
void BuildCombine(int counter, char * files[])
{
	char newfile[1024] = { 0 };
	while (strlen(newfile) < 1)
	{
		InputBox(newfile, 1024 - 1, "请输入组合后的文件名，#号退出，支持回车键确定");
		if (newfile[0] == '#')
			exit(0);
	}
	strcat(newfile,".prc");
	FilesCombine(counter, files, newfile, 1);
	outtextxy(SX * 30 / 100, SY * 50 / 100, "组合文件名：");
	outtextxy(SX * 30 / 100, SY * 60 / 100, newfile);
}
void SpeedCheck()
{
	if (IsKeyDown(VK_CONTROL) && IsKeyDown(VK_UP))
		Stime -= Stime * 1 / 10;
	if (IsKeyDown(VK_CONTROL) && IsKeyDown(VK_DOWN))
	{
		if (Stime < 10)
			Stime += 2;
		else
			Stime += Stime * 1 / 10;
	}
	if (Stime < 2)
		Stime = 3;
	if (Stime>15 * 1000)
		Stime = 15 * 1000;
}
void KeyStateDeal()
{
	if (IsKeyDown(VK_CONTROL) && IsKeyDown(VK_SPACE))
	{
		if (FullDisplay)
			ImageFullZoom();
		else
			ImageKeepZoom();
		FullDisplay = !FullDisplay;
	}
	if (IsKeyDown(VK_CONTROL) && IsKeyDown('M'))
	{
		if (FullScreenDis)
			FullScreen();
		else
			ZoomScreen();
		FullScreenDis = !FullScreenDis;
		if (FullDisplay)
			ImageFullZoom();
		else
			ImageKeepZoom();
	}
}
void DrawPicture()
{
	BeginBatchDraw();
	solidrectangle(0, 0, SX, SY);
	int spacex = 0, spacey = 0;
	int hei = img[round].getheight();
	int wid = img[round].getwidth();
	if (hei == SY)
	{
		spacex = (SX - wid) / 2;
	}
	else
	{
		spacey = (SY - hei) / 2;
	}
	putimage(spacex, spacey, &img[round]);
	EndBatchDraw();
	round++;
	if (round >= filecounter)
		round = 0;
}
void LoadFileRound(char * file)
{
	int success = 0;
	if (file != NULL)
		success = LoadImageFileCombine(file);
	while (!success)
	{
		char filename[1024] = { 0 };
		InputBox(filename, 1024 - 1, "请输入文件名(.prc文件可以不用填入后缀)，输入#退出，支持回车确认");
		if (filename[0] == '#')
			exit(0);
		int havetail=0;
		int i = 1;
		while (filename[i])
		{
			i++;
		}
		while (filename[i] != '.'&&filename[i] != ':'&&filename[i] != '\\'&&i > 0)
		{
			i--;
		}
		if (filename[i] == '.')
			havetail = 1;
		if (havetail == 0)
			strcat(filename,".prc");
		success = LoadImageFileCombine(filename);
	}
}
void FullScreen()
{
	SX = GetSystemMetrics(SM_CXSCREEN);
	SY = GetSystemMetrics(SM_CYSCREEN);
	//窗口最前端
	SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, SX, SY, SWP_SHOWWINDOW);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
}
void ZoomScreen()
{
	SX = GetSystemMetrics(SM_CXSCREEN) * 2 / 3;
	SY = GetSystemMetrics(SM_CYSCREEN) * 2 / 3;
	//窗口最前端
	SetWindowPos(hwnd, HWND_NOTOPMOST, (GetSystemMetrics(SM_CXSCREEN) - SX) / 2, (GetSystemMetrics(SM_CYSCREEN) - SY) / 2, SX, SY, SWP_SHOWWINDOW);
	SetWindowLong(hwnd, GWL_HINSTANCE, GetWindowLong(hwnd, GWL_HINSTANCE) - WS_CAPTION);
}
void InitApp()
{
	img = new IMAGE[MAXLEN];
	filecounter = 0;
	for (int i = 0; i < MAXLEN; i++)
	{
		files[i] = filebody[i];
	}
	hwnd = initgraph(SX, SY);
	ZoomScreen();
	setfillcolor(RGB(231, 244, 244));
	solidrectangle(0, 0, SX, SY);
	setbkmode(TRANSPARENT);
	int minpix = (SX < SY ? SX : SY);
	settextstyle(minpix * 3 / 100.0, minpix * 3 / 100.0, "黑体");
	settextcolor(RGB(4, 27, 231));

}
int LoadImageFileCombine(char * path)
{
	FILE_ERROR success = FileSplit(path, 0, &filecounter, files);
	if (success != FILE_SUCCESS) return 0;
	for (int i = 0; i < filecounter; i++)
	{
		loadimage(&img[i], filebody[i]);
	}
	return 1;
}
void ImageKeepZoom()
{
	delete[] img;
	img = new IMAGE[MAXLEN];
	for (int i = 0; i < filecounter; i++)
	{
		loadimage(&img[i], filebody[i]);
		int hei = img[i].getheight();
		int wid = img[i].getwidth();
		int nhei = hei, nwid = wid;
		if (SY*(wid*1.0 / hei) <= SX)
		{
			nhei = SY;
			nwid = nhei*(wid*1.0 / hei);
		}
		else
		{
			nwid = SX;
			nhei = nwid*(hei*1.0 / wid);
		}
		loadimage(&img[i], filebody[i], nwid, nhei, true);
	}
}
void ImageFullZoom()
{
	delete[] img;
	img = new IMAGE[MAXLEN];
	for (int i = 0; i < filecounter; i++)
	{
		loadimage(&img[i], filebody[i], SX, SY, true);
	}
}

////////////////////////////////////////////////////////////////////
FILE_ERROR FilesCombine(int counter, char * files[], char * newFileName, int needRemoveSource)
{
	int haveInvalid = 0;  /*文件是否存在无效文件*/
	if (counter == 0)
		return FILE_NOT_FILE;   /*检查是否有传入文件*/
	FILE * SI = NULL;
	double sumLen = 0;    /*计算组合之后文件总长度*/
	int InvalidFile[1024] = { 0 }; /*记录有效文件的下标*/
	double InvalidFileSize[1024] = { 0 };   /*记录有效文件的大小*/
	int InvalidFileLen = 0;   /*记录有效文件的个数*/
	for (int i = 0; i < counter; i++)
	{
		fopen_s(&SI, files[i], "r");
		if (!SI) /*检查文件有效性*/
		{
			haveInvalid = 1;
			continue;
		}
		fseek(SI, 0L, SEEK_SET);
		long fbegin = ftell(SI);
		fseek(SI, 0L, SEEK_END);
		long fend = ftell(SI);
		sumLen += fend - fbegin;    /*计算文件大小（字节）*/
		InvalidFile[InvalidFileLen] = i;
		InvalidFileSize[InvalidFileLen] = fend - fbegin;
		InvalidFileLen++;
		fclose(SI);
	}
	if (sumLen > (3.99 * 1024 * 1024 * 1024))    /*判断文件是否会大于4G*/
		return FILE_OVERSTEP_MAXSIZE;
	FILE * DI = NULL;
	fopen_s(&DI, newFileName, "wb");
	fwrite(&ComFlag, sizeof(char), 5, DI);     /*建立组合文件并写入标记*/
	char SaveFileName[300] = { 0 };     /*记录文件名，不含路径*/
	char name[300] = { 0 };
	char tail[20] = { 0 };  /*临时保存文件名和后缀*/
	for (int i = 0; i < InvalidFileLen; i++)
	{
		fopen_s(&SI, files[InvalidFile[i]], "rb");
		GetPathInfo(files[InvalidFile[i]], name, PATH_NAME);
		GetPathInfo(files[InvalidFile[i]], tail, PATH_TAIL);
		strcpy_s(SaveFileName, name);
		strcat_s(SaveFileName, tail);  /*获取文件名后缀并组合成完整文件名*/
		int namelen = strlen(SaveFileName);
		fwrite(&namelen, sizeof(int), 1, DI);
		fwrite(SaveFileName, sizeof(char), namelen, DI);
		fwrite(&InvalidFileSize[i], sizeof(double), 1, DI);    /*写入文件名长度，文件名，文件长度*/
		unsigned char temp = 0;
		while (!feof(SI))
		{
			fread(&temp, sizeof(temp), 1, SI); /*读取文件写入进行组合*/
			if (feof(SI))
				break;
			fwrite(&temp, sizeof(temp), 1, DI);
		}
		fclose(SI);
		if (needRemoveSource != 0) /*检查是否需要移除源文件并执行*/
			remove(files[InvalidFile[i]]);
	}
	fclose(DI);
	if (haveInvalid == 1)  /*检查是否存在无效文件*/
		return FILE_INVALID;
	return FILE_SUCCESS;
}
FILE_ERROR FileSplit(char * fileName, int needRemoveSource, int * retcounter, char * retfiles[])
{
	FILE * SI = NULL;
	fopen_s(&SI, fileName, "rb");
	if (!SI) return FILE_NOT_FILE;   /*检查文件是否存在*/
	char check[5] = { 0 };
	fread(&check, sizeof(char), 5, SI);    /*检查是否是组合文件*/
	if (strcmp(ComFlag, check) != 0)
	{
		fclose(SI);
		return FILE_NOT_COMBINE;
	}

	int namelen = 0;  /*保存文件名长度*/
	char GetFileName[1024] = { 0 }; /*保存文件名*/
	double FileSize = 0;  /*保存文件长度*/
	unsigned char temp = 0;   /*临时复制缓存单元*/
	while (1)
	{
		fread(&namelen, sizeof(int), 1, SI);   /*获取名字长度并检查是否结束*/
		if (feof(SI)) break;
		fread(GetFileName, sizeof(char), namelen, SI); /*获取文件名*/
		GetFileName[namelen] = '\0';
		strcpy(retfiles[*retcounter], (char *)GetFileName);
		(*retcounter)++;
		fread(&FileSize, sizeof(double), 1, SI);   /*获取文件大小*/
		FILE * DI = NULL;
		fopen_s(&DI, GetFileName, "wb");  /*建立文件并进行复制*/
		for (double i = 0; i < FileSize; i++)
		{
			fread(&temp, sizeof(temp), 1, SI);
			fwrite(&temp, sizeof(temp), 1, DI);
		}
		fclose(DI);
	}
	fclose(SI);
	if (needRemoveSource != 0) /*判断是否需要移除并执行*/
		remove(fileName);
	return FILE_SUCCESS;
}
void GetPathInfo(char * path, char * save, PATH_INFO infotype)
{
	int i = 0;
	while (path[i])  /*获取路径长度*/
		i++;
	if (infotype == PATH_FATHER)       /*判断要获取的内容类型*/
	{
		int j = i;
		while (path[j] != '\\'&&path[j] != ':'&&j >= 0)    /*找到从后往前第一个文件分割位置*/
		{
			j--;
		}
		if (j <= 0)    /*检查是否是相对路径*/
		{
			save[0] = '.';
			save[1] = '\0';
			return;
		}
		int m = 0;
		while (m < j)  /*复制父目录信息*/
		{
			save[m] = path[m];
			m++;
		}
		save[m] = '\0';
	}
	else if (infotype == PATH_NAME)
	{
		int j = i, n = i;
		int frist = 1;
		while (path[j] != '\\'&&path[j] != ':'&&j >= 0)    /*检查从后往前第一个文件分割*/
		{
			if (path[j] == '.'&&frist == 1)  /*检查是否是后缀标识，最后一个.才算*/
			{
				n = j;
				frist = 0;
			}

			j--;
		}
		int m = 0;    /*复制文件名，知道后缀位置，没有后缀也能正常*/
		while (j + 1 + m < n)
		{
			save[m] = path[j + 1 + m];
			m++;
		}
		save[m] = '\0';
	}
	else if (infotype == PATH_TAIL)
	{
		int j = i;
		while (path[j] != '\\'&&path[j] != ':'&&path[j] != '.'&&j >= 0)
		{
			j--;
		}
		if (path[j] != '.')    /*判断是否有文件后缀*/
		{
			save[0] = '\0';
			return;
		}
		int m = 0;
		while (path[j + m])    /*复制文件后缀，包含.*/
		{
			save[m] = path[j + m];
			m++;
		}
		save[m] = '\0';
	}
}
