#include <Windows.h>  
#include <stdio.h>
#include<conio.h>
#include <tchar.h>  
#include <iostream>  
#include<sstream>
#include<ctime>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////
//����ת��
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
//ʮ����ת��������
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

//��������תʮ���ƣ�����double���ͣ��������������ַ���txt,�ͽ��Ʊ�ʶoth
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
//���ֽڶ��ֽ�ת��
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
//����͸��
void WindowAlpha(HWND hwnd, float alpha)
{
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255 * ((100 - alpha) / 100.0), LWA_ALPHA);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//base64ת��
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
//�������д��ھ����ȡ��Ϣ
void DisplayAllHWND(bool allset, float alpha)
{
	//�õ����洰��  
	HWND hd = GetDesktopWindow();

	//�õ���Ļ�ϵ�һ���Ӵ���  
	hd = GetWindow(hd, GW_CHILD);
	WCHAR windowname[200] = { 0 };
	char disname[400] = { 0 };
	WCHAR classname[200] = { 0 };
	char discname[400] = { 0 };

	//ѭ���õ����е��Ӵ���  
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
//�ַ�ת��д
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
//���ַ�����ȡ��ȡָ����������
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
//����̨��������
//��1�в��ᱻ������Ϊ�˷���������
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
		cout << ">>>�����в���<<<" << endl;
		cout << "MODE �������ִ�Сд�� ����VALUE�������ִ�Сд" << endl;
		cout << "	MODE VALUE_1 VALUE_2 VALUE_3" << endl;
		cout << "MODE:" << endl;
		cout << "	HWND:		һ�����ڵľ����һ������»�ı䣩" << endl;
		cout << "	CLASSNAME:	�������������ǹ̶��ģ�����ı䣩" << endl;
		cout << "	NAME:		���ڱ��⣨���ǹ̶��ģ�����һ��������˵��" << endl;
		cout << "	POINT:		����������µĴ��ڣ�ֻ��������˿���˵��" << endl;
		cout << "	ALL:		ָ����ǰ���д���(��������)" << endl;
		cout << "	LIST:		��ʾ��ǰ���д�����Ϣ�������������κβ���" << endl;
		cout << "	HELP:		�鿴���˰�����Ϣ" << endl;
		cout << "�÷�ʾ����" << endl;
		cout << "	HWND ��� ͸����" << endl;
		cout << "		�����һ��16���Ʊ�ʶ���޷���32λ������16���Ʊ�ʶ��8λ����͸������С���ٷֱȼ��㣨0.0-100.0��" << endl;
		cout << "		���磺 HWND 0001023C 40" << endl;
		cout << "		���ҵĻ����ϴ˿����������ھ����������������͸����Ϊ40%" << endl;
		cout << "	CLASSNAME ���� ͸����" << endl;
		cout << "		���磺CLASSNAME CabinetWClass 30" << endl;
		cout << "		��ʶ������Դ������͸����Ϊ30%" << endl;
		cout << "	NAME ������ ͸����" << endl;
		cout << "		������������пո񣬲�����дΪ�� \"�� ��\" ��ʽ" << endl;
		cout << "		���磺NAME ���� 25.3" << endl;
		cout << "		��ʶ���������˵�͸����Ϊ25.3%" << endl;
		cout << "	POINT ������ ������ ͸����" << endl;
		cout << "		���磺POINT 508 846 50" << endl;
		cout << "		��ʶ����508,846��λ�õĴ���͸��������Ϊ50%���һ�������������λ��" << endl;
		cout << "	ALL ͸����" << endl;
		cout << "		���磺ALL 25" << endl;
		cout << "		��ʶ���õ�ǰ���д��ڵ�͸����Ϊ%25" << endl;
		cout << "ע�����" << endl;
		cout << "	��ȷ������Ĳ������������򲻻���" << endl;
		cout << "	��Ȼ���棬����Ҫ��ס����" << endl;
		cout << "	���ֽ������û���Ч�����ֽ������û���" << endl;
		cout << "	�������û������´򿪶�Ӧ���ں�ʧЧ���������Ժ����ж�������" << endl;
		cout << ">>>�������沿��<<<" << endl;
		cout << "�鿴��ǰ���д�����Ϣ" << endl;
		cout << "	�������е�LIST����һ��Ч����������ʾ��ǰ���д�����Ϣ" << endl;
		cout << "���ô���͸����" << endl;
		cout << "	��ѡģʽ��" << endl;
		cout << "		0=HWND 1 ClassName 2 NAME    3 CursorPoint" << endl;
		cout << "		0 ��� 1 ����      2 ������	 3 ���λ��" << endl;
		cout << "	0 1 2 ��������������ģʽ����������/����/��������������͸����" << endl;
		cout << "	3 ��������⣺" << endl;
		cout << "		�ƶ���굽��Ҫ͸���Ĵ���֮�ϣ���Ҫ�κε��" << endl;
		cout << "		����     1      ѡ�д���" << endl;
		cout << "		���� Space/�ո� ��ͣ" << endl;
		cout << "		������ò�Ҫ����������棬���򱾳����ȡ�����������" << endl;
		cout << "		��������ط�֮����Alt+Table�л��ر���������������Ч" << endl;
		cout << "		����ֱ������������ڲ��ܷ�������" << endl;
		cout << "		����ʹ�ÿո����ͣ�������λ�ã���������Ҫ�ľ������Ϣ" << endl;
		cout << "����ȫ��͸����" << endl;
		cout << "	��������ALL�������ƣ���ѡ���ģʽ��������͸����" << endl;
		cout << "��Դ������͸��������" << endl;
		cout << "	ϵͳ�汾��ͬ�������ò�����Ч������WIN10��Ч" << endl; 
		cout << "�����и߼�ģʽ" << endl;
		cout << "	�������ʹ���������в���һ��" << endl;
		cout << "	����������" << endl;
		cout << "		EXIT:�˳������в���ģʽ" << endl;
		cout << "		CLS:�����Ļ" << endl;
		cout << "		SYS:ʹ��ϵͳ����������" << endl;
		cout << "			���磺sys color 0a" << endl;
		cout << "			���磺sys ping baidu.com" << endl;
		cout << "			��ʶִ��ϵͳ����color 0a��" << endl;
		cout << "		RAND:��ȡһ����Χ�ڵ������" << endl;
		cout << "			���磺rand 5 \"-1\"" << endl;
		cout << "			��ʶ����һ��-1��5֮��������������-1��5,ע�⣬��������������ţ���ô�ᱻ����������" << endl;
		cout << "		HEX:����ת����2-64����֮�䣩" << endl;
		cout << "			���磺 hex 16 2 a2.2" << endl;
		cout << "			��ʶ��16������a2.2ת����2������" << endl;
		cout << "		BASE64��base64ת����˫��" << endl;
		cout << "			������TOSTRING TOBASE �ֱ��ʶbase64ת�ַ����ַ�תbase64�������ִ�Сд��" << endl;
		cout << "			���磺BASE64 tobase \"this is a ����\"" << endl;
		cout << "			��ʶ��\"this is a ����\"ת��Ϊbase64" << endl;
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
//�����й���ģʽ
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
	cout << "System:���� EXIT �˳�������" << endl;
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
				cout << "��Ч������" << endl;
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
	system("title ͸�����߼��ۺϹ��� designer Ice2Faith");
	HWND self = FindWindow(NULL, L"͸�����߼��ۺϹ��� designer Ice2Faith");
	WindowAlpha(self, 20);
	char sel = '\0';
	while (1)
	{
		fflush(stdin);
		sel = '\0';
		cout << "\t͸�����߼��ۺϹ���" << endl;
		cout << "1.�鿴��ǰ���д�����Ϣ\t��ɨ�贰��������" << endl;
		cout << "2.���ô���͸����\t������ȡ��Ϣ������" << endl;
		cout << "3.����ȫ��͸����\t������������" << endl;
		cout << "4.��Դ������͸��������\t��ϵͳ�汾��һ����һ����Ч��" << endl;
		cout << "5.��յ�ǰ��Ļ\t\t����յ�ǰ������Ϣ��" << endl;
		cout << "6.�����и߼�ģʽ\t��ʹ�������в������ݣ�" << endl;
		cout << "0.�˳�����" << endl;
		while (sel<'0' || sel>'6')
			sel = getch();
		cout << sel << endl;
		fflush(stdin);
		switch ((int)(sel - '0'))
		{
		case 1:
		{
				  DisplayAllHWND(false, 0);
				  cout << "�����������" << endl;
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
					  cout << "��ѡ�����ģʽ��0=HWND 1 ClassName 2 NAME 3 CursorPoint" << endl;
					  char mode = '\0';
					  while (mode<'0' || mode>'3')
						  mode = getch();
					  cout << mode << endl;
					  fflush(stdin);
					  if (mode == '0')
					  {
						  cout << "������һ�� HWND" << endl;
						  cin >> hex >> sel;
					  }
					  else if (mode == '1')
					  {
						  cout << "������һ�� ClassName" << endl;
						  fflush(stdin);
						  char classname[256] = { 0 };
						  WCHAR Claname[256] = { 0 };
						  gets(classname);
						  Char2Wchar_t(classname, Claname);
						  sel = (int)FindWindow(Claname, NULL);
					  }
					  else if (mode == '2')
					  {
						  cout << "������һ�� NAME" << endl;
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
							  cout << "���� 1 ѡ�д��� Space ��ͣ(��������ط�֮����Alt+Table�л��ر���������� 1)" << endl;
							  GetCursorPos(&cursor);
							  cout << "���꣺" << cursor.x << "  " << cursor.y << endl;
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
					  cout << "������͸����(0-100.0)" << endl;
					  cin >> dec >> alpha;
					  fflush(stdin);
					  cout << "���ã�" << sel << "͸���ȣ�" << alpha << endl;
					  WindowAlpha((HWND)sel, alpha);
					  cout << "���������������0�˳�����" << endl;
					  if (getch() == '0') break;
					  fflush(stdin);
				  }
				  cout << "�����������" << endl;
				  getch();
				  cout << "--------------------------------------------------" << endl;
				  fflush(stdin);
		}
			break;
		case 3:
		{
				  float alpha = 15;
				  cout << "������ȫ��͸����(0-100.0)" << endl;
				  cin >> dec >> alpha;
				  DisplayAllHWND(true, alpha);
				  fflush(stdin);
				  cout << "�����������" << endl;
				  getch();
				  cout << "--------------------------------------------------" << endl;
				  fflush(stdin);
		}
			break;
		case 4:
		{
				  float alpha = 15;
				  cout << "��������Դ������͸����(0-100.0)" << endl;
				  cin >> dec >> alpha;
				  HWND sel = FindWindow(L"CabinetWClass", NULL);
				  WindowAlpha((HWND)sel, alpha);
				  fflush(stdin);
				  cout << "�����������" << endl;
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
