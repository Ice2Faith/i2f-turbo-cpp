#include <Windows.h>  
#include <stdio.h>
#include<conio.h>
#include <tchar.h>  
#include <iostream>  
#include<sstream>
#include<ctime>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////
//进制转换
#define MAXSIZE 1000
typedef int elemtype;
typedef struct
{
	elemtype data[MAXSIZE];
	int top;
} StackList;
StackList * DefultStack()
{
	StackList * p = (StackList *)malloc(sizeof(StackList));
	p->top = -1;
	return p;
}
int IsEmpty(StackList * S)
{
	return S->top == -1;
}
int IsFull(StackList * S)
{
	return S->top == MAXSIZE - 1;
}
int Push(StackList * S, elemtype x)
{
	if (IsFull(S))
		return 0;
	S->data[++S->top] = x;
	return 1;
}
int Pop(StackList * S, elemtype * x)
{
	if (IsEmpty(S))
		return 0;
	*x = S->data[S->top--];
	return 1;
}
char Change[MAXSIZE] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwsyz@#\0" };
//十进制转其他进制
void OTC2Other(double num, int oth, int bef)
{
	int otc = (int)num;
	double flo = num - otc;
	int FloNum[MAXSIZE];
	StackList * p;
	p = DefultStack();
	while (otc != 0)
	{
		Push(p, otc%oth);
		otc = (int)otc / oth;
	}
	int i = 0;
	while (flo != 0.0&&i<100)
	{
		FloNum[i] = (int)(flo*oth);
		flo = flo*oth - FloNum[i];
		i++;
	}
	FloNum[i] = 0;
	FloNum[++i] = -9999;
	printf(">>\t%d->%d\t>/ ", bef, oth);
	i = 0;
	while (!IsEmpty(p))
	{
		Pop(p, &otc);
		printf("%c", Change[otc]);
		if (i % 4 == 3)
			printf(" ");
		i++;
	}
	printf(".");
	i = 0;
	while (FloNum[i] != -9999)
	{
		printf("%c", Change[FloNum[i]]);
		if (i % 4 == 3)
			printf(" ");
		i++;
	}
	printf("\n\n");
	free(p);
}

//其他进制转十进制，返回double类型，传入其他进制字符串txt,和进制标识oth
double Oth2OTC(char * txt, int oth)
{
	double result = 0;
	while (*txt != '.'&&*txt != '\0')
	{
		result *= oth;
		if (*txt >= '0'&&*txt <= '9')
			result += (*txt - '0');
		else if (*txt >= 'A'&&*txt <= 'Z')
			result += (*txt - 'A' + 10);
		else if (*txt >= 'a'&&*txt <= 'z')
			result += (*txt - 'a' + 10);
		txt++;
	}
	txt++;
	int i = 1;
	while (*txt >= '0'&&*txt <= '9')
	{

		if (*txt >= '0'&&*txt <= '9')
			result += (*txt - '0')*pow(1.0 / oth, (double)i++);
		else if (*txt >= 'A'&&*txt <= 'Z')
			result += (*txt - 'A' + 10)*pow(1.0 / oth, (double)i++);
		else if (*txt >= 'a'&&*txt <= 'z')
			result += (*txt - 'a' + 10)*pow(1.0 / oth, (double)i++);
		txt++;
	}
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//宽字节多字节转换
void Wchar_t2Char(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void Char2Wchar_t(char Char[], wchar_t Wchar[])
{
	int size = MultiByteToWideChar(CP_ACP, 0, Char, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Char, -1, Wchar, size);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//窗口透明
void WindowAlpha(HWND hwnd, float alpha)
{
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255 * ((100 - alpha) / 100.0), LWA_ALPHA);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//base64转换
#define BASE_MODE int
#define BASE_NORMAL_STR 0
#define BASE_URL 1
#define BASE_EXP 2
#define BASE_XML_NMTOKEN 3
#define BASE_XML_NAME 4
#define BASE_CHINA 5

int Base64(char * str, char * base64, int base64_size, BASE_MODE mode)
{
	if (strlen(str) * 4 / 3 >= base64_size)
	{
		return 0;
	}
	char table[65] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
	char EndFill = '=';
	if (mode == BASE_NORMAL_STR)
	{
		EndFill = '=';
	}
	else if (mode == BASE_URL)
	{
		table[62] = '-';
		table[63] = '_';
		EndFill = '=';
	}
	else if (mode == BASE_EXP)
	{
		table[62] = '!';
		table[63] = '-';
		EndFill = '=';
	}
	else if (mode == BASE_XML_NMTOKEN)
	{
		table[62] = '.';
		table[63] = '-';
		EndFill = '=';
	}
	else if (mode == BASE_XML_NAME)
	{
		table[62] = '_';
		table[63] = ':';
		EndFill = '=';
	}
	else if (mode == BASE_CHINA)
	{
		table[62] = '.';
		table[63] = '_';
		EndFill = '=';
	}

	unsigned char in[3] = { 0 };
	unsigned char out[4] = { 0 };
	int i = 0, k = 0;
	int end = 0;
	int endspace = 8;
	while (end == 0)
	{
		for (int j = 0; j<4; j++)
		{
			if (j<3)
				in[j] = 0;
			out[j] = 0;
		}
		for (int j = 0; j<3; j++)
		{
			in[j] = str[i];
			i++;
			if (str[i] == '\0')
			{
				end = 1;
				endspace = j + 2;
				break;
			}
		}
		int temp = 0;
		temp = (((int)in[0]) << (2 * 8)) | (((int)in[1]) << (1 * 8)) | ((int)in[2]);
		out[0] = table[((temp&(63 << (6 * 3))) >> (6 * 3))];
		out[1] = table[((temp&(63 << (6 * 2))) >> (6 * 2))];
		out[2] = table[((temp&(63 << (6 * 1))) >> (6 * 1))];
		out[3] = table[(temp & 63)];
		if (endspace <= 0)
			out[0] = EndFill;
		if (endspace <= 1)
			out[1] = EndFill;
		if (endspace <= 2)
			out[2] = EndFill;
		if (endspace <= 3)
			out[3] = EndFill;
		for (int j = 0; j<4; j++)
		{
			base64[k] = out[j];
			k++;
		}

	}
	base64[k] = '\0';
	return 1;
}
int Anti_Base64(char * base64, char * str, int str_size, BASE_MODE mode)
{
	if (strlen(base64) * 3 / 4 >= str_size)
	{
		return 0;
	}
	char table[65] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
	char EndFill = '=';
	if (mode == BASE_NORMAL_STR)
	{
		EndFill = '=';
	}
	else if (mode == BASE_URL)
	{
		table[62] = '-';
		table[63] = '_';
		EndFill = '=';
	}
	else if (mode == BASE_EXP)
	{
		table[62] = '!';
		table[63] = '-';
		EndFill = '=';
	}
	else if (mode == BASE_XML_NMTOKEN)
	{
		table[62] = '.';
		table[63] = '-';
		EndFill = '=';
	}
	else if (mode == BASE_XML_NAME)
	{
		table[62] = '_';
		table[63] = ':';
		EndFill = '=';
	}
	else if (mode == BASE_CHINA)
	{
		table[62] = '.';
		table[63] = '_';
		EndFill = '=';
	}
	unsigned char in[4] = { 0 };
	int iin[4] = { 0 };
	unsigned char out[3] = { 0 };
	int i = 0, k = 0;
	int end = 0;
	while (end == 0)
	{
		for (int j = 0; j<4; j++)
		{
			if (j<3)
				out[j] = 0;
			in[j] = 0;
			iin[j] = 0;
		}
		for (int j = 0; j<4; j++)
		{
			in[j] = base64[i];
			i++;
			if (base64[i] == '\0' || base64[i] == EndFill)
			{
				end = 1;
				break;
			}
		}
		for (int j = 0; table[j] != '\0'; j++)
		{
			if (in[0] == table[j])
				iin[0] = j;
			if (in[1] == table[j])
				iin[1] = j;
			if (in[2] == table[j])
				iin[2] = j;
			if (in[3] == table[j])
				iin[3] = j;
		}
		int temp = 0;
		temp = ((iin[0]) << (3 * 6)) | ((iin[1]) << (2 * 6)) | ((iin[2]) << (1 * 6)) | (iin[3]);
		out[0] = ((temp&(255 << (8 * 2))) >> (8 * 2));
		out[1] = ((temp&(255 << (8 * 1))) >> (8 * 1));
		out[2] = (temp & 255);
		for (int j = 0; j<3; j++)
		{
			str[k] = out[j];
			k++;
		}

	}
	str[k] = '\0';
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//遍历所有窗口句柄获取信息
void DisplayAllHWND(bool allset, float alpha)
{
	//得到桌面窗口  
	HWND hd = GetDesktopWindow();

	//得到屏幕上第一个子窗口  
	hd = GetWindow(hd, GW_CHILD);
	WCHAR windowname[200] = { 0 };
	char disname[400] = { 0 };
	WCHAR classname[200] = { 0 };
	char discname[400] = { 0 };

	//循环得到所有的子窗口  
	while (hd != NULL)
	{
		memset(windowname, 0, 200);
		GetWindowText(hd, windowname, 200);
		GetClassName(hd, classname, 200);
		Wchar_t2Char(classname, discname);
		Wchar_t2Char(windowname, disname);
		if (allset)
			WindowAlpha(hd, alpha);
		cout << "HWND: " << hd << "\tClassName: " << discname << "\t\tNAME: " << disname << endl;
		hd = GetNextWindow(hd, GW_HWNDNEXT);
	}
	cout << "-------------------------------------------------" << endl;
}
//字符转大写
void BigStr(char * str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i]>='a'&&str[i]<='z')
		str[i] &= ~32;
		i++;
	}
}
//从字符串获取抽取指定类型数据
template<class T>
T stringToIStream(T flag, const string & str, int mode)
{
	istringstream stream(str);
	T result;
	if (mode == 0)
		stream >> result;
	else if (mode == 1)
		stream >> oct >> result;
	else if (mode == 2)
		stream >> hex >> result;
	return result;
}
//控制台参数处理
//第1行不会被处理到，为了符合主函数
void CommandSet(int count, char * mind[])
{
	char mindstr[10][512] = { 0 };
	int mindcou = 0;
	bool needset = false;
	float alpha = 0;
	HWND hwnd = 0;
	for (int i = 1; i < count; i++)
	{
		strcpy(mindstr[i - 1], mind[i]);
		mindcou++;
	}
	BigStr(mindstr[0]);
	if (strcmp(mindstr[0], "HWND") == 0)
	{
		string sh(mindstr[1]);
		int ih = 0;
		ih = stringToIStream(ih, sh, 2);
		hwnd = (HWND)ih;
		sh = mindstr[2];
		alpha = stringToIStream(alpha, sh, 0);
		needset = true;
	}
	else if (strcmp(mindstr[0], "CLASSNAME") == 0)
	{
		WCHAR Claname[256] = { 0 };
		Char2Wchar_t(mindstr[1], Claname);
		hwnd = FindWindow(Claname, NULL);
		string sh(mindstr[2]);
		alpha = 0;
		alpha = stringToIStream(alpha, sh, 0);
		needset = true;
	}
	else if (strcmp(mindstr[0], "NAME") == 0)
	{
		WCHAR hname[512 * 2] = { 0 };
		Char2Wchar_t(mindstr[1], hname);
		hwnd = FindWindow(NULL, hname);
		string sh(mindstr[2]);
		alpha = 0;
		alpha = stringToIStream(alpha, sh, 0);
		needset = true;
	}
	else if (strcmp(mindstr[0], "POINT") == 0)
	{
		POINT cursor;
		string sh(mindstr[1]);
		int x = 0, y = 0;
		x = stringToIStream(x, sh, 0);
		sh = mindstr[2];
		y = stringToIStream(y, sh, 0);
		cursor.x = x;
		cursor.y = y;
		hwnd = WindowFromPoint(cursor);
		sh = mindstr[3];
		alpha = stringToIStream(alpha, sh, 0);
		needset = true;
	}
	else if (strcmp(mindstr[0], "ALL") == 0)
	{
		string sh(mindstr[1]);
		alpha = stringToIStream(alpha, sh, 0);
		DisplayAllHWND(true, alpha);
	}
	else if (strcmp(mindstr[0], "LIST") == 0)
	{
		DisplayAllHWND(false, 0);
	}
	else if (strcmp(mindstr[0], "HELP") == 0)
	{
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
		cout << "Help Info" << endl;
		cout << ">>>命令行部分<<<" << endl;
		cout << "MODE （不区分大小写） 其他VALUE参数区分大小写" << endl;
		cout << "	MODE VALUE_1 VALUE_2 VALUE_3" << endl;
		cout << "MODE:" << endl;
		cout << "	HWND:		一个窗口的句柄（一般情况下会改变）" << endl;
		cout << "	CLASSNAME:	窗口类名（这是固定的，不会改变）" << endl;
		cout << "	NAME:		窗口标题（这是固定的，对于一个程序来说）" << endl;
		cout << "	POINT:		该鼠标坐标下的窗口（只对于输入此刻来说）" << endl;
		cout << "	ALL:		指定当前所有窗口(谨慎操作)" << endl;
		cout << "	LIST:		显示当前所有窗口信息，不进行其他任何操作" << endl;
		cout << "	HELP:		查看到此帮助信息" << endl;
		cout << "用法示例：" << endl;
		cout << "	HWND 句柄 透明度" << endl;
		cout << "		句柄是一个16进制标识的无符号32位整数（16进制标识有8位），透明度是小数百分比计算（0.0-100.0）" << endl;
		cout << "		例如： HWND 0001023C 40" << endl;
		cout << "		在我的机器上此刻是启动窗口句柄，设置启动窗口透明度为40%" << endl;
		cout << "	CLASSNAME 类名 透明度" << endl;
		cout << "		例如：CLASSNAME CabinetWClass 30" << endl;
		cout << "		标识设置资源管理器透明度为30%" << endl;
		cout << "	NAME 窗口名 透明度" << endl;
		cout << "		窗口名如果含有空格，参数请写为： \"名 字\" 形式" << endl;
		cout << "		例如：NAME 启动 25.3" << endl;
		cout << "		标识设置启动菜单透明度为25.3%" << endl;
		cout << "	POINT 横坐标 纵坐标 透明度" << endl;
		cout << "		例如：POINT 508 846 50" << endl;
		cout << "		标识坐标508,846的位置的窗口透明度设置为50%，我机器上是任务栏位置" << endl;
		cout << "	ALL 透明度" << endl;
		cout << "		例如：ALL 25" << endl;
		cout << "		标识设置当前所有窗口的透明度为%25" << endl;
		cout << "注意事项：" << endl;
		cout << "	请确保输入的参数合理，本程序不会检测" << endl;
		cout << "	虽然好玩，可是要稳住车速" << endl;
		cout << "	部分界面设置会无效，部分界面设置会变黑" << endl;
		cout << "	所有设置会在重新打开对应窗口后失效，重启电脑后所有都会重置" << endl;
		cout << ">>>操作界面部分<<<" << endl;
		cout << "查看当前所有窗口信息" << endl;
		cout << "	和命令行的LIST命令一个效果，都是显示当前所有窗口信息" << endl;
		cout << "设置窗口透明度" << endl;
		cout << "	可选模式：" << endl;
		cout << "		0=HWND 1 ClassName 2 NAME    3 CursorPoint" << endl;
		cout << "		0 句柄 1 类名      2 窗口名	 3 鼠标位置" << endl;
		cout << "	0 1 2 操作类似命令行模式，先输入句柄/类名/窗口名，再输入透明度" << endl;
		cout << "	3 鼠标操作详解：" << endl;
		cout << "		移动鼠标到你要透明的窗口之上，不要任何点击" << endl;
		cout << "		输入     1      选中窗口" << endl;
		cout << "		输入 Space/空格 暂停" << endl;
		cout << "		过程最好不要点击其他界面，否则本程序获取不到你的输入" << endl;
		cout << "		点击其他地方之后请Alt+Table切换回本程序后输入才能生效" << endl;
		cout << "		或者直接鼠标点击本窗口才能返回输入" << endl;
		cout << "		合理使用空格键暂停捕获鼠标位置，复制你需要的句柄等信息" << endl;
		cout << "设置全局透明度" << endl;
		cout << "	和命令行ALL操作类似，先选择该模式，在输入透明度" << endl;
		cout << "资源管理器透明度设置" << endl;
		cout << "	系统版本不同可能设置不会生效，至少WIN10有效" << endl; 
		cout << "命令行高级模式" << endl;
		cout << "	命令参数使用与命令行参数一致" << endl;
		cout << "	其他参数：" << endl;
		cout << "		EXIT:退出命令行参数模式" << endl;
		cout << "		CLS:清空屏幕" << endl;
		cout << "		SYS:使用系统命令行命令" << endl;
		cout << "			例如：sys color 0a" << endl;
		cout << "			例如：sys ping baidu.com" << endl;
		cout << "			标识执行系统命令color 0a等" << endl;
		cout << "		RAND:获取一个范围内的随机数" << endl;
		cout << "			例如：rand 5 \"-1\"" << endl;
		cout << "			标识生成一个-1到5之间的随机数，包含-1和5,注意，如果负数不加引号，那么会被解析掉负号" << endl;
		cout << "		HEX:进制转换（2-64进制之间）" << endl;
		cout << "			例如： hex 16 2 a2.2" << endl;
		cout << "			标识把16进制数a2.2转换成2进制数" << endl;
		cout << "		BASE64：base64转换（双向）" << endl;
		cout << "			参数：TOSTRING TOBASE 分别标识base64转字符和字符转base64（不区分大小写）" << endl;
		cout << "			例如：BASE64 tobase \"this is a 测试\"" << endl;
		cout << "			标识把\"this is a 测试\"转换为base64" << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	}
	if (needset)
	{
		WindowAlpha(hwnd, alpha);
		WCHAR windowname[200] = { 0 };
		char disname[400] = { 0 };
		WCHAR classname[200] = { 0 };
		char discname[400] = { 0 };
		GetWindowText((HWND)hwnd, windowname, 200);
		GetClassName((HWND)hwnd, classname, 200);
		Wchar_t2Char(classname, discname);
		Wchar_t2Char(windowname, disname);
		cout << "HWND: " << (HWND)hwnd << endl;
		cout << "ClassName: " << discname << endl;
		cout << "NAME: " << disname << endl;
	}

}
//命令行工作模式
void CommandMode()
{
	system("cls");
	char line[2048] = { "\0" };
	char mind[20][512] = { 0 };
	char * mindp[20] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		mindp[i] = mind[i];
	}
	cout << "System:输入 EXIT 退出命令行" << endl;
	while (true)
	{
		cout << ">/ ";
		gets(line);
		int counter = 1;
		int i = 0;
		int j = 0;
		bool endstr = false;
		while (true)
		{

			while (line[i] == ' ' || line[i] == '\t')
			{
				i++;
			}
			if (line[i] == '-')
				i++;
			j = 0;
			if (line[i] != '\"')
			{
				while (line[i] != ' '&&line[i] != '\t'&&line[i] != '\"')
				{
					mind[counter][j] = line[i];
					i++;
					j++;
					if (line[i] == '\0')
					{
						endstr = true;
						break;
					}
				}
				mind[counter][j] = '\0';
				counter++;
			}
			j = 0;
			if (line[i] == '\"')
			{
				i++;
				while (line[i] != '\"')
				{
					mind[counter][j] = line[i];
					i++;
					j++;
					if (line[i] == '\"')
					{
						i++;
						break;
					}
					if (line[i] == '\0')
					{
						endstr = true;
						break;
					}
				}
				mind[counter][j] = '\0';
				counter++;
			}
			if (endstr)
			{
				break;
			}
		}
		BigStr(mind[1]);
		string tempstr(mind[0]);
		if (strcmp(mind[1], "EXIT") == 0)
			break;
		else
		if (strcmp(mind[1], "CLS") == 0)
			system("cls");
		else if (strcmp(mind[1], "RAND") == 0)
		{
			tempstr = mind[2];
			int low=0, heigh = 100;
			low = stringToIStream(low,tempstr,0);
			tempstr = mind[3];
			heigh = stringToIStream(heigh,tempstr,0);
			if (low > heigh)
			{
				int tp = low;
				low = heigh;
				heigh = tp;
			}
			cout << rand() % (heigh - low + 1) + low <<endl;
		}
		else if (strcmp(mind[1], "HEX") == 0)
		{
			int bef=10, oth=16;
			double num=0;
			tempstr = mind[2];
			bef = stringToIStream(bef,tempstr,0);
			tempstr = mind[3];
			oth = stringToIStream(oth,tempstr,0);
			num = Oth2OTC(mind[4], bef);
			OTC2Other(num, oth, bef);

		}
		else if (strcmp(mind[1], "BASE64") == 0)
		{
			char outresult[1024] = { 0 };
			BigStr(mind[2]);
			if (strcmp(mind[2], "TOSTRING") == 0)
			{
				Anti_Base64(mind[3],outresult,sizeof(outresult),BASE_NORMAL_STR);
				cout << outresult << endl;
			}
			else if (strcmp(mind[2], "TOBASE") == 0)
			{
				Base64(mind[3], outresult,sizeof(outresult),BASE_NORMAL_STR);
				cout << outresult << endl;
			}
			else
			{
				cout << "无效参数！" << endl;
			}
		}
		else if (strcmp(mind[1],"SYS")==0)
		{
			char sysmind[1024] = { 0 };
			for (int k = 2; k < counter; k++)
			{
				strcat(sysmind,mind[k]);
				strcat(sysmind," ");
			}
			system(sysmind);
		}
		else
		CommandSet(counter,mindp);
	}
	system("cls");
}
int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	if (argc > 1)
	{
		CommandSet(argc, argv);
		return 0;
	}
	system("title 透明化高级综合工具 designer Ice2Faith");
	HWND self = FindWindow(NULL, L"透明化高级综合工具 designer Ice2Faith");
	WindowAlpha(self, 20);
	char sel = '\0';
	while (1)
	{
		fflush(stdin);
		sel = '\0';
		cout << "\t透明化高级综合工具" << endl;
		cout << "1.查看当前所有窗口信息\t（扫描窗口利器）" << endl;
		cout << "2.设置窗口透明度\t（鼠标获取信息利器）" << endl;
		cout << "3.设置全局透明度\t（谨慎操作）" << endl;
		cout << "4.资源管理器透明度设置\t（系统版本不一样不一定生效）" << endl;
		cout << "5.清空当前屏幕\t\t（清空当前界面信息）" << endl;
		cout << "6.命令行高级模式\t（使用命令行参数传递）" << endl;
		cout << "0.退出程序" << endl;
		while (sel<'0' || sel>'6')
			sel = getch();
		cout << sel << endl;
		fflush(stdin);
		switch ((int)(sel - '0'))
		{
		case 1:
		{
				  DisplayAllHWND(false, 0);
				  cout << "按任意键继续" << endl;
				  getch();
				  cout << "--------------------------------------------------" << endl;
				  fflush(stdin);
		}
			break;
		case 2:
		{
				  while (1)
				  {
					  int sel;
					  float alpha = 15;
					  char name[512] = { 0 };
					  cout << "请选择操作模式：0=HWND 1 ClassName 2 NAME 3 CursorPoint" << endl;
					  char mode = '\0';
					  while (mode<'0' || mode>'3')
						  mode = getch();
					  cout << mode << endl;
					  fflush(stdin);
					  if (mode == '0')
					  {
						  cout << "请输入一个 HWND" << endl;
						  cin >> hex >> sel;
					  }
					  else if (mode == '1')
					  {
						  cout << "请输入一个 ClassName" << endl;
						  fflush(stdin);
						  char classname[256] = { 0 };
						  WCHAR Claname[256] = { 0 };
						  gets(classname);
						  Char2Wchar_t(classname, Claname);
						  sel = (int)FindWindow(Claname, NULL);
					  }
					  else if (mode == '2')
					  {
						  cout << "请输入一个 NAME" << endl;
						  gets(name);
						  WCHAR hname[512 * 2] = { 0 };
						  Char2Wchar_t(name, hname);
						  sel = (int)FindWindow(NULL, hname);
					  }
					  else if (mode == '3')
					  {
						  WindowAlpha(self, 40);
						  SetWindowPos(self, HWND_TOPMOST, 0, 0, 480, 320, SWP_SHOWWINDOW);
						  POINT cursor;
						  while (1)
						  {
							  system("cls");
							  cout << "输入 1 选中窗口 Space 暂停(点击其他地方之后请Alt+Table切换回本程序后输入 1)" << endl;
							  GetCursorPos(&cursor);
							  cout << "坐标：" << cursor.x << "  " << cursor.y << endl;
							  WCHAR windowname[200] = { 0 };
							  char disname[400] = { 0 };
							  WCHAR classname[200] = { 0 };
							  char discname[400] = { 0 };
							  sel = (int)WindowFromPoint(cursor);
							  GetWindowText((HWND)sel, windowname, 200);
							  GetClassName((HWND)sel, classname, 200);
							  Wchar_t2Char(classname, discname);
							  Wchar_t2Char(windowname, disname);
							  cout << "HWND: " << (HWND)sel << endl;
							  cout << "ClassName: " << discname << endl;
							  cout << "NAME: " << disname << endl;

							  HWND phwnd = (HWND)sel;
							  phwnd = GetParent(phwnd);
							  if (phwnd)
								  cout << "--------------------------------------" << endl << "Parent HWND:" << endl;
							  while (phwnd)
							  {
								  WCHAR windowname[200] = { 0 };
								  char disname[400] = { 0 };
								  WCHAR classname[200] = { 0 };
								  char discname[400] = { 0 };
								  GetWindowText((HWND)phwnd, windowname, 200);
								  GetClassName((HWND)phwnd, classname, 200);
								  Wchar_t2Char(classname, discname);
								  Wchar_t2Char(windowname, disname);
								  cout << "HWND: " << (HWND)phwnd << endl;
								  cout << "ClassName: " << discname << endl;
								  cout << "NAME: " << disname << endl;
								  phwnd = GetParent(phwnd);
							  }
							  char key = '\0';
							  if (kbhit())
								  key = getch();
							  if (key == '1')
								  break;
							  if (key == ' ')
								  system("pause");
							  Sleep(200);
						  }

						  sel = (int)WindowFromPoint(cursor);
						  SetWindowPos(self, HWND_NOTOPMOST, 0, 0, 480, 320, SWP_SHOWWINDOW);
						  WindowAlpha(self, 20);
					  }
					  fflush(stdin);
					  cout << "请输入透明度(0-100.0)" << endl;
					  cin >> dec >> alpha;
					  fflush(stdin);
					  cout << "设置：" << sel << "透明度：" << alpha << endl;
					  WindowAlpha((HWND)sel, alpha);
					  cout << "按任意键继续，按0退出这里" << endl;
					  if (getch() == '0') break;
					  fflush(stdin);
				  }
				  cout << "按任意键继续" << endl;
				  getch();
				  cout << "--------------------------------------------------" << endl;
				  fflush(stdin);
		}
			break;
		case 3:
		{
				  float alpha = 15;
				  cout << "请输入全局透明度(0-100.0)" << endl;
				  cin >> dec >> alpha;
				  DisplayAllHWND(true, alpha);
				  fflush(stdin);
				  cout << "按任意键继续" << endl;
				  getch();
				  cout << "--------------------------------------------------" << endl;
				  fflush(stdin);
		}
			break;
		case 4:
		{
				  float alpha = 15;
				  cout << "请输入资源管理器透明度(0-100.0)" << endl;
				  cin >> dec >> alpha;
				  HWND sel = FindWindow(L"CabinetWClass", NULL);
				  WindowAlpha((HWND)sel, alpha);
				  fflush(stdin);
				  cout << "按任意键继续" << endl;
				  getch();
				  cout << "--------------------------------------------------" << endl;
				  fflush(stdin);

		}
			break;
		case 5:
		{
				  system("cls");
		}
			break;
		case 6:
		{
				  CommandMode();
		}
			break;
		case 0:
		{
				  exit(0);
		}
			break;
		}
	}

	return 0;
}
