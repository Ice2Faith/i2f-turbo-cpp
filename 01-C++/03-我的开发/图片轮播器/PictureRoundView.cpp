#include <string.h>
#include <stdio.h>
#include<conio.h>
#include<graphics.h>
#include"GameKeyTool.h"
typedef int FILE_ERROR;                                             //�ļ�����״̬�ź�
#define FILE_SUCCESS 0                                              //��������
#define FILE_INVALID 1                                              //�����ļ���Ч
#define FILE_NOT_FILE 2                                             //���ļ�����
#define FILE_NOT_COMBINE 3                                          //�ļ�û�б����
#define FILE_OVERSTEP_MAXSIZE 4                                     //��Ϻ��ļ��ᳬ��4G
char ComFlag[5] = { "FCOM" };                                           //����ļ���־
typedef int PATH_INFO;                                              //�����ļ�·����Ϣ��ȡ����
#define PATH_FATHER 0                                               //��ȡ�ļ���Ŀ¼
#define PATH_NAME 1                                                 //��ȡ�ļ����ƣ���������׺�͸�·����
#define PATH_TAIL 2                                                 //��ȡ�ļ���׺������.
void GetPathInfo(char * path, char * save, PATH_INFO infotype);       //��ȡ�ļ���Ϣ�������ļ�·��������λ�ã���Ҫ����Ϣ����
/*���ش���ת̬�������ļ��������ļ��������ļ������Ƿ���Ҫ�Ƴ�Դ�ļ�*/
FILE_ERROR FilesCombine(int counter, char * files[], char * newFileName, int needRemoveSource);
/*���ش���ת̬�������ļ������Ƿ���Ҫ�Ƴ�Դ�ļ�*/
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
				  outtextxy(SX * 40 / 100, SY / 2, "��Դ������...");
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
					  outtextxy(SX * 30 / 100, SY * 30 / 100, "���Ժ�...");
						BuildCombine(argc-1, &argv[1]);
						outtextxy(SX * 30 / 100, SY * 40 / 100, "�ļ��ϲ�����");
				  }
				  else
				  {
					  outtextxy(SX * 20 / 100, SY *10/100, "û���κ��ļ����Ժϲ�Ŷ��");
					  outtextxy(SX * 20 / 100, SY * 20 / 100, "�ϲ��ļ����裺");
					  outtextxy(SX * 20 / 100, SY * 30 / 100, "1.ѡ�����ļ�");
					  outtextxy(SX * 20 / 100, SY * 40 / 100, "2.��ѡ���ļ��϶���������ͼ���Ͻ�������");
					  outtextxy(SX * 20 / 100, SY * 50 / 100, "3.���кϲ�����");
					  outtextxy(SX * 20 / 100, SY * 60 / 100, "֧�ֵĸ�ʽ��");
					  outtextxy(SX * 20 / 100, SY * 70/ 100, "jpg / png / bmp / gif / tif / emf / wmf / ico");
					  outtextxy(SX * 20 / 100, SY * 80 / 100, " gif ��ʽ��ͼƬ�����ص�һ֡");
				  }
				  outtextxy(SX * 40 / 100, SY * 90 / 100, "�����������");
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
	outtextxy(SX * 45 / 100, SY * 10 / 100, "�ļ��ֲ���");
	outtextxy(SX * 40 / 100, SY * 20 / 100, "1.��ʼ�ֲ�ͼƬ");
	outtextxy(SX * 40 / 100, SY * 30 / 100, "2.�����ֲ��ļ�");
	outtextxy(SX * 40 / 100, SY * 40 / 100, "3.��ȡʹ�ð���");
	outtextxy(SX * 40 / 100, SY * 50 / 100, "0.�˳���ǰ����");
	char sel = '\0';
	while (sel<'0' || sel>'3')
		sel = getch();
	return (int)(sel - '0');
}
void Help()
{
	outtextxy(SX * 35 / 100, 0 , "     Help & Question");
	outtextxy(SX * 30 / 100, SY * 10 / 100, "Ctrl+Space: ����Ӧ/������ʾ");
	outtextxy(SX * 30 / 100, SY * 20 / 100, "Ctrl+M    : ȫ��/����Ӧ��С");
	outtextxy(SX * 30 / 100, SY * 30 / 100, "Ctrl+UP   : �ӿ��ֲ��ٶ�");
	outtextxy(SX * 30 / 100, SY * 40 / 100, "Ctrl+DOWN : �����ֲ��ٶ�");
	outtextxy(SX * 30 / 100, SY * 50 / 100, "ESC       : �˳�����");
	outtextxy(SX * 5 / 100, SY * 60 / 100, "�ֲ������ֱ���϶��ֲ��ļ���������ͼ����������ݴ�");
	outtextxy(SX * 5 / 100, SY * 70 / 100, "Ҳ�����ȴ򿪳���������ֲ��ļ����ƣ���Ҫ����׺");
	outtextxy(SX * 5 / 100, SY * 80 / 100, "�����ֲ��ļ������ͼƬ�ļ���ѡ���ϵ�ͼ�����������ܴ���");
	outtextxy(SX * 30 / 100, SY * 90 / 100, "�����������");
	getch();
}
void BuildCombine(int counter, char * files[])
{
	char newfile[1024] = { 0 };
	while (strlen(newfile) < 1)
	{
		InputBox(newfile, 1024 - 1, "��������Ϻ���ļ�����#���˳���֧�ֻس���ȷ��");
		if (newfile[0] == '#')
			exit(0);
	}
	strcat(newfile,".prc");
	FilesCombine(counter, files, newfile, 1);
	outtextxy(SX * 30 / 100, SY * 50 / 100, "����ļ�����");
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
		InputBox(filename, 1024 - 1, "�������ļ���(.prc�ļ����Բ��������׺)������#�˳���֧�ֻس�ȷ��");
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
	//������ǰ��
	SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, SX, SY, SWP_SHOWWINDOW);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
}
void ZoomScreen()
{
	SX = GetSystemMetrics(SM_CXSCREEN) * 2 / 3;
	SY = GetSystemMetrics(SM_CYSCREEN) * 2 / 3;
	//������ǰ��
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
	settextstyle(minpix * 3 / 100.0, minpix * 3 / 100.0, "����");
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
	int haveInvalid = 0;  /*�ļ��Ƿ������Ч�ļ�*/
	if (counter == 0)
		return FILE_NOT_FILE;   /*����Ƿ��д����ļ�*/
	FILE * SI = NULL;
	double sumLen = 0;    /*�������֮���ļ��ܳ���*/
	int InvalidFile[1024] = { 0 }; /*��¼��Ч�ļ����±�*/
	double InvalidFileSize[1024] = { 0 };   /*��¼��Ч�ļ��Ĵ�С*/
	int InvalidFileLen = 0;   /*��¼��Ч�ļ��ĸ���*/
	for (int i = 0; i < counter; i++)
	{
		fopen_s(&SI, files[i], "r");
		if (!SI) /*����ļ���Ч��*/
		{
			haveInvalid = 1;
			continue;
		}
		fseek(SI, 0L, SEEK_SET);
		long fbegin = ftell(SI);
		fseek(SI, 0L, SEEK_END);
		long fend = ftell(SI);
		sumLen += fend - fbegin;    /*�����ļ���С���ֽڣ�*/
		InvalidFile[InvalidFileLen] = i;
		InvalidFileSize[InvalidFileLen] = fend - fbegin;
		InvalidFileLen++;
		fclose(SI);
	}
	if (sumLen > (3.99 * 1024 * 1024 * 1024))    /*�ж��ļ��Ƿ�����4G*/
		return FILE_OVERSTEP_MAXSIZE;
	FILE * DI = NULL;
	fopen_s(&DI, newFileName, "wb");
	fwrite(&ComFlag, sizeof(char), 5, DI);     /*��������ļ���д����*/
	char SaveFileName[300] = { 0 };     /*��¼�ļ���������·��*/
	char name[300] = { 0 };
	char tail[20] = { 0 };  /*��ʱ�����ļ����ͺ�׺*/
	for (int i = 0; i < InvalidFileLen; i++)
	{
		fopen_s(&SI, files[InvalidFile[i]], "rb");
		GetPathInfo(files[InvalidFile[i]], name, PATH_NAME);
		GetPathInfo(files[InvalidFile[i]], tail, PATH_TAIL);
		strcpy_s(SaveFileName, name);
		strcat_s(SaveFileName, tail);  /*��ȡ�ļ�����׺����ϳ������ļ���*/
		int namelen = strlen(SaveFileName);
		fwrite(&namelen, sizeof(int), 1, DI);
		fwrite(SaveFileName, sizeof(char), namelen, DI);
		fwrite(&InvalidFileSize[i], sizeof(double), 1, DI);    /*д���ļ������ȣ��ļ������ļ�����*/
		unsigned char temp = 0;
		while (!feof(SI))
		{
			fread(&temp, sizeof(temp), 1, SI); /*��ȡ�ļ�д��������*/
			if (feof(SI))
				break;
			fwrite(&temp, sizeof(temp), 1, DI);
		}
		fclose(SI);
		if (needRemoveSource != 0) /*����Ƿ���Ҫ�Ƴ�Դ�ļ���ִ��*/
			remove(files[InvalidFile[i]]);
	}
	fclose(DI);
	if (haveInvalid == 1)  /*����Ƿ������Ч�ļ�*/
		return FILE_INVALID;
	return FILE_SUCCESS;
}
FILE_ERROR FileSplit(char * fileName, int needRemoveSource, int * retcounter, char * retfiles[])
{
	FILE * SI = NULL;
	fopen_s(&SI, fileName, "rb");
	if (!SI) return FILE_NOT_FILE;   /*����ļ��Ƿ����*/
	char check[5] = { 0 };
	fread(&check, sizeof(char), 5, SI);    /*����Ƿ�������ļ�*/
	if (strcmp(ComFlag, check) != 0)
	{
		fclose(SI);
		return FILE_NOT_COMBINE;
	}

	int namelen = 0;  /*�����ļ�������*/
	char GetFileName[1024] = { 0 }; /*�����ļ���*/
	double FileSize = 0;  /*�����ļ�����*/
	unsigned char temp = 0;   /*��ʱ���ƻ��浥Ԫ*/
	while (1)
	{
		fread(&namelen, sizeof(int), 1, SI);   /*��ȡ���ֳ��Ȳ�����Ƿ����*/
		if (feof(SI)) break;
		fread(GetFileName, sizeof(char), namelen, SI); /*��ȡ�ļ���*/
		GetFileName[namelen] = '\0';
		strcpy(retfiles[*retcounter], (char *)GetFileName);
		(*retcounter)++;
		fread(&FileSize, sizeof(double), 1, SI);   /*��ȡ�ļ���С*/
		FILE * DI = NULL;
		fopen_s(&DI, GetFileName, "wb");  /*�����ļ������и���*/
		for (double i = 0; i < FileSize; i++)
		{
			fread(&temp, sizeof(temp), 1, SI);
			fwrite(&temp, sizeof(temp), 1, DI);
		}
		fclose(DI);
	}
	fclose(SI);
	if (needRemoveSource != 0) /*�ж��Ƿ���Ҫ�Ƴ���ִ��*/
		remove(fileName);
	return FILE_SUCCESS;
}
void GetPathInfo(char * path, char * save, PATH_INFO infotype)
{
	int i = 0;
	while (path[i])  /*��ȡ·������*/
		i++;
	if (infotype == PATH_FATHER)       /*�ж�Ҫ��ȡ����������*/
	{
		int j = i;
		while (path[j] != '\\'&&path[j] != ':'&&j >= 0)    /*�ҵ��Ӻ���ǰ��һ���ļ��ָ�λ��*/
		{
			j--;
		}
		if (j <= 0)    /*����Ƿ������·��*/
		{
			save[0] = '.';
			save[1] = '\0';
			return;
		}
		int m = 0;
		while (m < j)  /*���Ƹ�Ŀ¼��Ϣ*/
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
		while (path[j] != '\\'&&path[j] != ':'&&j >= 0)    /*���Ӻ���ǰ��һ���ļ��ָ�*/
		{
			if (path[j] == '.'&&frist == 1)  /*����Ƿ��Ǻ�׺��ʶ�����һ��.����*/
			{
				n = j;
				frist = 0;
			}

			j--;
		}
		int m = 0;    /*�����ļ�����֪����׺λ�ã�û�к�׺Ҳ������*/
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
		if (path[j] != '.')    /*�ж��Ƿ����ļ���׺*/
		{
			save[0] = '\0';
			return;
		}
		int m = 0;
		while (path[j + m])    /*�����ļ���׺������.*/
		{
			save[m] = path[j + m];
			m++;
		}
		save[m] = '\0';
	}
}
