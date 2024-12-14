#include<graphics.h>
#include<stdio.h>
#include<string.h>
#define STYPE "黑体"
#define MAXSIZE 2048
int WX = 720;
int WY = 480;
int FW = 5;
int FH = 5;

char path[2048] = { 0 };
char fpath[2048] = { 0 }; 
char  name[300] = { 0 };
char tail[20] = { 0 };
char ssaveimage[2048] = { 0 };
char ssavefile[2048] = { 0 };
IMAGE picture;
IMAGE save(WX*FW, WY*FH);
char asciiDisplay[MAXSIZE][MAXSIZE];
int rgbColor[MAXSIZE][MAXSIZE];
void GetPicturePixel()
{
	SetWorkingImage(&picture);
	for (int i = 0; i < WY; i++)
	{
		for (int j = 0; j < WX; j++)
		{
			rgbColor[i][j]=getpixel(j, i);
		}
	}
	SetWorkingImage(NULL);
}
void GetAsciiChar()
{
	//char map[40] = { "#%@$&8XOH?LTIi!=*+^;:,. " };
	char map[40] = { "M#@$&HN%8AX*GO?TLI+=i!;:^,. " };
	int lenmap = strlen(map);
	int lenstep = (256.0 / lenmap+0.5);
	int red=0, green=0, blue=0;
	int rgbc = 0,gray=0;
	int index=0;
	for (int i = 0; i < WY; i++)
	{
		for (int j = 0; j < WX; j++)
		{
			rgbc = rgbColor[i][j];
			red = rgbc & 0xff;
			rgbc = rgbc >> 8;
			green = rgbc & 0xff;
			rgbc = rgbc >> 8;
			blue = rgbc & 0xff;
			gray = (red * 299 + green * 587 + blue * 114 ) / 1000;
			index=gray / lenstep;
			if (index < 0)index = 0;
			if (index >= lenmap) index = lenmap - 1;
			asciiDisplay[i][j] = map[index];
		}
	}
}
void DisplayPixel()
{
	BeginBatchDraw();
	for (int i = 0; i < WY; i++)
	{
		for (int j = 0; j < WX; j++)
		{
			putpixel(j, i, rgbColor[i][j]);
		}
	}
	EndBatchDraw();
}
void DisplayAscii()
{
	SetWorkingImage(&save);
	settextcolor(RGB(0, 0, 0));
	settextstyle(FH , FW , STYPE);
	setfillcolor(RGB(255, 255, 255));
	solidrectangle(0, 0, WX * FW, WY * FH);
	setbkmode(TRANSPARENT);
	FILE* out=fopen(ssavefile,"w");
	for (int i = 0; i < WY; i++)
	{
		for (int j = 0; j < WX; j++)
		{
			fprintf(out,"%c", asciiDisplay[i][j]);
			outtextxy(j * FW, i * FH, asciiDisplay[i][j]);
		}
		fprintf(out,"\n");
	}
	fclose(out);
	SetWorkingImage(NULL);
	saveimage(ssaveimage, &save);
}
void GetPathPart(char * path, char * fpath, char * name, char * tail)
{
	char tpath[4096] = { 0 };
	strcpy(tpath, path);
	int p = 0;
	while (tpath[p])
	{
		if (tpath[p] == ':')
			break;
		p++;
	}
	if (tpath[p + 1] != '\\')
	{
		int len = strlen(tpath);
		int i = len;
		while (i != p)
		{
			tpath[i + 1] = tpath[i];
			i--;
		}
		tpath[p + 1] = '\\';
	}
	int len = strlen(tpath);
	int stail = -1;
	int sname = -1;
	int spath = -1;
	int i = 0;
	while (tpath[i])
	{
		if (tpath[i] == '\\')
			sname = i;
		if (tpath[i] == '.')
			stail = i;
		i++;
	}
	int k = 0;
	int j = 0;
	if (stail != -1)
	{
		j = stail + 1;
		while (tpath[j])
		{
			tail[k] = tpath[j];
			k++;
			j++;
		}
	}
	else
		stail = len;
	tail[k] = 0;

	k = 0;
	j = 0;
	if (sname != -1)
	{
		j = sname + 1;
		while (j<stail)
		{
			name[k] = tpath[j];
			k++;
			j++;
		}
	}
	else
	{
		j = 0;
		while (j<stail)
		{
			name[k] = tpath[j];
			k++;
			j++;
		}
		sname = 0;
	}

	name[k] = 0;

	k = 0;
	while (k<sname)
	{
		fpath[k] = tpath[k];
		k++;
	}
	fpath[k] = 0;
}

int main()
{
	HWND hwnd=initgraph(720, 480,SHOWCONSOLE);
	setfillcolor(RGB(0, 255, 255));
	solidrectangle(0, 0, 720, 480);
	settextstyle(480/10,720/25,STYPE);
	setbkmode(TRANSPARENT);
	outtextxy(720*1/3,480*1/3,"图片转字符图");
	char temp[80] = { 0 };
	InputBox(path, 300 - 1, "请输入图片名称", "获取图片");
	if (strlen(path) == 0) return 0;
	GetPathPart(path, fpath, name, tail);
	memset(ssavefile, 0, sizeof(ssavefile));
	memset(ssaveimage, 0, sizeof(ssaveimage));
	if (strlen(fpath))
	{
		strcpy(ssavefile, fpath);
		strcat(ssavefile, "\\");
	}
	strcat(ssavefile, name);
	strcat(ssavefile, "_disp.txt\0");

	if (strlen(fpath))
	{
	strcpy(ssaveimage, fpath);
	strcat(ssaveimage, "\\");
	}
	
	strcat(ssaveimage, name);
	strcat(ssaveimage, "_asci.jpg\0");
	if (IDYES == MessageBox(hwnd, "是否使用自定义参数？", "选择", MB_YESNO))
	{
		int pwx=0, pwy=0, pfh=0, pfw=0;
		InputBox(temp, 300 - 1, "请输入载入图片缩放后大小（像素）：宽*高", "获取输入图片大小");
		sscanf(temp, "%d*%d", &pwx, &pwy);
		InputBox(temp, 300 - 1, "请输入输出图片字符大小（像素）：宽*高", "获取输出字体大小");
		sscanf(temp, "%d*%d", &pfw, &pfh);
		if (pwx >= 10 && pwx <= MAXSIZE)
			WX = pwx;
		if (pwy >= 10 && pwy <= MAXSIZE)
			WY = pwy;
		if (pfh >= 10 && pfh <= 48)
			FH = pfh;
		if (pfw >= 10 && pfw <= 48)
			FW = pfw;
		save.Resize(WX*FW, WY*FH);
	}
	loadimage(&picture, path, WX, WY, true);
	GetPicturePixel();
	hwnd=initgraph(WX, WY);
	DisplayPixel();
	GetAsciiChar();
	DisplayAscii();
	char tips[4096] = { 0 };
	sprintf(tips, "图片处理完成\n字符文本保存在：%s\n图片保存在：%s", ssavefile, ssaveimage);
	MessageBox(hwnd, tips, "程序运行结束", MB_OK);
	return 0;
}