#include<iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
void OperateLoop(FILE * fp);
void CreateBash();
void ReadClickEvent(char * name);
void help();
char Menu();
void OperateMedel(char * FileName);
void ModelCursor(int x, int y, int cltype, int stime);
void ModelCursorRoll(int mx, int my, int rdata, int wait);
void MedelKebord(int key, int set, int wt);
void ModelCursorMove(int mx, int my, int mx1, int my2, int wite);
void GetFilesList(int * len, char *list[]);
int main(int argc, char *argv[])
{
	rename(argv[0], "ģ���û��ű���.exe");
	system("title ģ���û��ű��� V1.0 designer Ice2Faith");
	system("color 0A");
	srand((unsigned)time(NULL));
	if (argc > 1)
	{
		if (strcmp(argv[1], "help") == 0)
			help();
		else
			OperateMedel(argv[1]);
	}
	else
	{
		char choice = Menu();
		switch (choice)
		{
		case '1':
		{
					char listbody[256][1024] = { 0 };
					char * list[100] = { 0 };
					for (int i = 0; i < 100; i++)
						list[i] = listbody[i];
					int len = 0;
					GetFilesList(&len, list);
					char filename[1024] = { 0 };
					cout << "\n\t�ļ���ģʽ" << endl;
					cout << "---------------------------" << endl;
					cout << "\t1.Ĭ�Ϻ�׺(_MU.txt)" << endl;
					cout << "\t2.��ȫ�ļ���(*.*)" << endl;
					cout << "\t0.�˳�����" << endl;
					cout << "---------------------------" << endl;
					cout << "\n>/ ";
					char model = '7';
					while (model<'0' || model>'2')
						model = _getch();
					printf("%c\n", model);
					if (model == '0')
						exit(0);
					if (model == '2')
					{
						cout << "����1����Ŀ¼�ļ�����ѡ�񣬷����ֶ�����\n>/";
						char open = _getch();
						printf("%c\n", open);
						if (open == '1')
						{
							cout << "Found those files:\n-----------------------------" << endl;
							for (int i = 0; i < len; i++)
							{
								cout << i << ". " << list[i] << endl;
							}
							cout << "-----------------------------\nView end,Please select\n>/ ";
							int sel = -1;
							while (sel<0 || sel>len)
								cin >> sel;
							strcpy_s(filename, list[sel]);
						}
						else
						{
							cout << "�������ļ�������ȫ����(������׺)\n>/ ";
							cin >> filename;
						}

					}
					if (model == '1')   //ʹ��Ĭ����չ��ʱ�Զ��Ӻ�׺
					{
						cout << "�������ļ���(��Ҫ��Ĭ�Ϻ�׺)\n>/ ";
						cin >> filename;
						strcat_s(filename, "_MU.txt");
					}
					cout << "Run >> " << filename << endl;
					Sleep(800);
					system("TASKKILL /F /IM cmd.exe /T");
					OperateMedel(filename);
					break;
		}
		case '2':
		{
					CreateBash();
					break;
		}
		case '3':
		{
					help();
					break;
		}
		default:
			break;
		}

	}

	return 0;
}
void GetFilesList(int * len, char *list[])
{
	remove("temp.tp");
	system("dir *.* /b >> temp.tp");
	FILE * FileList = NULL;
	fopen_s(&FileList, "temp.tp", "r");
	int llen = 0;
	while (!feof(FileList))
	{
		fgets(list[llen], 1024, FileList);
		int slen = strlen(list[llen]);
		list[llen][slen - 1] = '\0';
		if ((strcmp(list[llen], "temp.tp") != 0) && slen != 0)
			llen++;
		if (llen > 255)
		{
			llen = 255;
			break;
		}
	}
	*len = llen;
	fclose(FileList);
	remove("temp.tp");
}
char Menu()
{
	char choice = '7';
	cout << "\n\tģ���û��ű���" << endl;
	cout << "---------------------------" << endl;
	cout << "\t1.���нű�" << endl;
	cout << "\t2.¼��ű�" << endl;
	cout << "\t3.��ȡ����" << endl;
	cout << "\t9.��������" << endl;
	cout << "\t0.�˳�����" << endl;
	cout << "---------------------------" << endl;
	cout << "\n>/ ";
	while (choice<'0' || choice>'3')
	if ((choice = _getch()) == '9')
	{
		cout << "9\nTips>> ���Ѿ��������У��������� exit �˳������У��ص����򣬼�������\n" << endl;
		system("cmd /k dir");
		cout << "\nTips>> �����ڿ�������ѡ�������ʽ\n>/ ";
	}
	printf("%c\n", choice);
	Sleep(80);
	system("cls");
	return choice;
}
void CreateBash()
{
	char filename[1024] = { 0 };
	cout << "��������Դ���һ���ű�" << endl;
	cout << "������ű�����\n>/ ";
	cin >> filename;
	fflush(stdin);
	cout << "���� 1 ʹ��Ĭ�Ϻ�׺������ʹ��" << endl;
	if (_getch() == '1')
		strcat_s(filename, "_MU.txt");
	cout << "����Ϊ�㴴���ű���" << filename << endl;
	Sleep(1200);
	char Spechar[50][16] = { "SHIFT", "CONTROL", "ALT", "WIN", "CAPSLOCK", "ESC", "ENTER", "TAB", "BACKSPACE", "DELETE", "PRTSC", "SCROLL", "PAUSE", "NUMLOCK", "SPACE", "UP", "DOWN", "LEFT", "RIGHT",
		"PGUP", "PGDOWN", "HOME", "END", "INSERT", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "WAITRUN", "RANDIN", "CMD", "POWERSHELL", };
	int Spekey[50] = { 16, 17, 18, 91, 20, 27, 13, 9, 8, 46, 42, 145, 19, 144, 32, 38, 40, 37, 39, 33, 34, 36, 35, 45, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 281, 282, 283, 284 };
	char Norchar[64] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ+*`-=[]\\;',./\0" };
	int Norkey[64] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 107, 106, 192, 189, 187, 219, 221,
		220, 186, 222, 188, 190, 191, 0 };
	int Spelen = 0, Norlen = 0;
	while (Spechar[Spelen][0])
		Spelen++;
	Norlen = strlen(Norchar);
	int loop = 0;
	int inloop = 0;
	int waitloop = 0;
	while (1)
	{

		system("cls");
		if (inloop == 1) cout << "Roll..." << endl;
		cout << "��ѡ��¼�Ʋ���" << endl;
		cout << "1.�����" << endl;
		cout << "2.��ͨ��������(0-9 & A-Z)" << endl;
		cout << "3.���������̵��(WIN ALT D 9 ...)" << endl;
		cout << "4.��ϼ�����" << endl;
		cout << "5.���ע��" << endl;
		cout << "6.��ʼѭ��" << endl;
		cout << "7.����ѭ��" << endl;
		cout << "0.�˳�¼��" << endl;
		cout << ">/ ";
		char sel = '9';
		while (sel < '0' || sel>'7')
			sel = _getch();
		cout << sel << endl;
		Sleep(500);
		system("cls");

		if (sel == '2'||sel=='3'||sel=='4')
		{
			cout << "�������ַ���,ע���д" << endl;
			if (sel != '2')
			{
				for (int i = 0; i < Spelen; i++)
					cout << Spechar[i] << " ";
				cout << endl;
			}

			for (int i = 0; i < Norlen; i++)
				cout << Norchar[i] << " ";
			cout << endl;
			if (sel == '2' || sel == '3' || sel == '4')
			{
				MedelKebord(20, 1, 30);
				MedelKebord(20, 0, 30);
			}
		}
		else if (sel == '1')
		{
			cout << "����������겶����棬�벻Ҫ�ڵ�������Ŷ����" << endl;
			cout << "������ʾ���ƶ���굽���λ��" << endl;
			cout << "����1��ʶ��������2��ʾ�Ҽ������5��ʾ��������" << endl;
			cout << "����3��ʶ��ʼ��ק��4��ʾ������ק��6��ʾ�Ϲ���7��ʾ�¹�" << endl;
			Sleep(2000);
		}
		if (sel == '0')
		{
			if (inloop==1)
			{
				FILE * bashfile = NULL;
				fopen_s(&bashfile, filename, "a");
				fprintf_s(bashfile, "l 0 %d %d LOOP\n", loop, waitloop);
				inloop = 0;
				fclose(bashfile);
			}
			break;
		}
		switch (sel)
		{
		case '1':
		{
					ReadClickEvent(filename);
					break;
		}
		case '2':
		{
					FILE * bashfile = NULL;
					fopen_s(&bashfile, filename, "a");
					char temp = '\0';
					fflush(stdin);
					cout << "�����������У����н�����֧��ת���ַ�\"\\N\\T\"�Ϳո�\n>/ ";
					while (temp != '\n')
					{
						temp = getchar();
						if (temp == ' ')
						{
							fprintf_s(bashfile, "k 32 1 30 SPACE\n");
							fprintf_s(bashfile, "k 32 0 30 SPACE\n");
							continue;
						}
						if (temp == '\\')
						{
							temp = getchar();
							if (temp == 'N')
							{
								fprintf_s(bashfile, "k 13 1 30 ENTER\n");
								fprintf_s(bashfile, "k 13 0 30 ENTER\n");
								continue;
							}
							else
							if (temp == 'T')
							{
								fprintf_s(bashfile, "k 9 1 30 TAB\n");
								fprintf_s(bashfile, "k 9 0 30 TAB\n");
								continue;
							}
							else
							{
								fprintf_s(bashfile, "k 220 1 30 \\\n");
								fprintf_s(bashfile, "k 220 0 30 \\\n");
							}
						}
						int i = 0;
						while (Norchar[i] != temp)
						{
							i++;
							if (i > Norlen)
								break;
						}
						if (i > Norlen)
							continue;
						fprintf_s(bashfile, "k %d 1 30 %c\n", Norkey[i], Norchar[i]);
						fprintf_s(bashfile, "k %d 0 30 %c\n", Norkey[i], Norchar[i]);
					}
					fclose(bashfile);
					break;
		}
		case '3':
		{
					char temp[16] = { "0110" };
					int getlen = 0;
					FILE * bashfile = NULL;
					fopen_s(&bashfile, filename, "a");
					cout << "���������ַ���ÿ���ַ�֮��ո������00����" << endl;
					while (strcmp(temp, "00") != 0)
					{
						cin >> temp;
						getlen = strlen(temp);
						if (strcmp(temp, "00") == 0) break;
						if (getlen == 1)
						{
							int i = 0;
							while (Norchar[i] != temp[0])
							{
								i++;
								if (i > Norlen)
									break;
							}
							if (i > Norlen)
								continue;
							fprintf_s(bashfile, "k %d 1 30 %c\n", Norkey[i], Norchar[i]);
							fprintf_s(bashfile, "k %d 0 30 %c\n", Norkey[i], Norchar[i]);
						}
						else
						{
							int i = 0;
							while (strcmp(Spechar[i], temp) != 0)
							{
								i++;
								if (i > Spelen)
									break;
							}
							if (i > Spelen)
								continue;
							int wtime = 30;
							switch (Spekey[i])
							{
							case 281:
								wtime = 1000;
								break;
							case 283:
							case 284:
								wtime = 300;
								break;
							default:
								break;
							}

							fprintf_s(bashfile, "k %d 1 %d %s\n", Spekey[i], wtime, Spechar[i]);
							if (Spekey[i] < 281)
								fprintf_s(bashfile, "k %d 0 %d %s\n", Spekey[i], wtime, Spechar[i]);
						}
					}
					fclose(bashfile);
					break;
		}
		case '4':
		{
					char temp[10][20] = { 0 };
					char outfile[22][40] = { 0 };
					FILE * bashfile = NULL;
					fopen_s(&bashfile, filename, "a");
					cout << "���������ַ���ÿ���ַ�֮��ո������00����" << endl;
					int i = 0;
					while (strcmp(temp[i], "00") != 0)
					{
						cin >> temp[i];
						if (strcmp(temp[i], "00") == 0)
						{
							break;
						}
						i++;
					}
					int conbilen = 0;
					while (temp[conbilen][0])
						conbilen++;
					conbilen--;
					for (int i = 0; i < conbilen; i++)
					{
						int comlen = strlen(temp[i]);
						int j = 0;
						if (comlen == 1)
						{
							while (Norchar[j] != temp[i][0])
							{
								j++;
								if (j > Norlen)
									break;
							}
							if (j > Norlen)
								continue;
							sprintf_s(outfile[i], "k %d 1 30 %c\n", Norkey[j], Norchar[j]);
							sprintf_s(outfile[conbilen * 2 - i], "k %d 0 30 %c\n", Norkey[j], Norchar[j]);
						}
						else
						{
							while (strcmp(Spechar[j], temp[i]) != 0)
							{
								j++;
								if (j > Spelen)
									break;
							}
							if (j > Spelen)
								continue;
							sprintf_s(outfile[i], sizeof(outfile[i]), "k %d 1 30 %s\n", Spekey[j], Spechar[j]);
							sprintf_s(outfile[conbilen * 2 - i], sizeof(outfile[i]), "k %d 0 30 %s\n", Spekey[j], Spechar[j]);
						}

					}
					for (int i = 0; i <= conbilen * 2; i++)
						fprintf_s(bashfile, outfile[i]);
					fclose(bashfile);
					break;
		}
		case '5':
		{
					cout << "������һ��ע��" << endl<<">/ ";
					char declare[1024] = { 0 };
					fflush(stdin);
					gets_s(declare);
					FILE * bashfile = NULL;
					fopen_s(&bashfile, filename, "a");
					fprintf_s(bashfile, "# %s\n", declare);
					fclose(bashfile);
					break;
		}
		case '6':
		{
					FILE * bashfile = NULL;
					fopen_s(&bashfile, filename, "a");
					cout << "������ѭ����������һ��ѭ���ȴ�ʱ��\n>/ ";
					cin >> loop>>waitloop;
					if (loop < 1)
						loop = 1;
					if (waitloop < 0)
						waitloop = 30;
					fprintf_s(bashfile, "l 1 %d %d LOOP\n",loop,waitloop);
					inloop = 1;
					fclose(bashfile);
					break;
		}
		case '7':
		{
					FILE * bashfile = NULL;
					fopen_s(&bashfile, filename, "a");
					fprintf_s(bashfile, "l 0 %d %d LOOP\n", loop, waitloop);
					inloop = 0;
					fclose(bashfile);
					break;
		}
		}
		if (sel == '2' || sel == '3' || sel == '4')
		{
			MedelKebord(20, 1, 30);
			MedelKebord(20, 0, 30);
		}
	}
}
void ReadClickEvent(char * name)
{
	system("mode con lines=3 cols=20");
	FILE * click = NULL;
	char path[1024] = { "\0" };
	strcat_s(path, name);
	fopen_s(&click, path, "a");
	POINT point;
	char get = '\0';
	long beft = time(NULL), pret = time(NULL), subt = 0;
	int mx = 0, my = 0, mx1 = 0, my1 = 0, c3 = 0, c4 = 0;
	while (1)
	{
		GetCursorPos(&point);
		system("cls");
		cout << "Point:" << point.x << "," << point.y << endl;
		int lock = 0;
		if (_kbhit())
			get = _getch();
		if (get == '5')
			break;

		if (get == '1')
		{
			pret = time(NULL);
			subt = pret - beft;
			beft = pret;
			subt *= 300;
			if (subt == 0)
				subt = 300;
			fprintf(click, "c %d %d %d %d CLEFT\n", point.x, point.y, 1, subt);
			cout << "���";
		}
		if (get == '2')
		{
			pret = time(NULL);
			subt = pret - beft;
			beft = pret; \
				subt *= 300;
			if (subt == 0)
				subt = 300;
			fprintf(click, "c %d %d %d %d CRIGHT\n", point.x, point.y, 0, subt);
			cout << "�Ҽ�";
		}
		if (get == '6')
		{
			fprintf(click, "r %d %d 1 80 ROOLUP\n", point.x, point.y);
			cout << "�Ϲ�";
		}
		if (get == '7')
		{
			fprintf(click, "r %d %d 0 80 ROOLDOWN\n", point.x, point.y);
			cout << "�¹�";
		}
		if (c3 == 1 && c4 == 1)
		{
			fprintf(click, "m %d %d %d %d 60 CMOVE\n", mx, my, mx1, my1);
			cout << "��ק���";
			c3 = 0;
			c4 = 0;
		}
		if (get == '4'&&c4 == 0)
		{
			mx1 = point.x;
			my1 = point.y;
			c4 = 1;
			cout << "��ק�ͷ�";
		}
		if (get == '3'&&c3 == 0)
		{
			mx = point.x;
			my = point.y;
			c3 = 1;
			cout << "��ק��ʼ";
			lock = 1;
		}
		get = '\0';
		Sleep(10);
	}
	fclose(click);
	system("mode con lines=35 cols=120");
}
void ExtenBordyKey(int key, int set, int wt)
{
	if (set == 0)
		return;
	switch (key)
	{
	case 281:
	{
				Sleep(wt);
				break;
	}
	case 282:
	{
				char Norchar[64] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
				int Norkey[64] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90 };
				int Norlen = strlen(Norchar);
				int randkey = rand() % Norlen;
				int key = Norkey[randkey];
				MedelKebord(key, set, wt);
				MedelKebord(key, 0, wt);
				break;
	}
	case 283:
	{
				system("start cmd");
				break;
	}
	case 284:
	{
				system("start powershell");
				break;
	}

	default:
		break;
	}
}
void OperateLoop(FILE * fp)
{
	int count = 0;
	int loop = 0, looptime = 0,waitloop=0;
	char mode = '\0';
	typedef struct
	{
		char type;
		int num1, num2, num3, num4, num5;
	}mind;
	mind mindlist[1024];
	int mindcount = 0;
	int num1, num2, num3, num4, num5;
	count = fscanf_s(fp, "%d%d%d", &loop, &looptime,&waitloop);
	if (count != 3)
		return;
	if (loop == 1)
	{
		
		while (!feof(fp))
		{
			fscanf_s(fp, "%c", &mode);
			if (mode == 'k')
			{
				count = fscanf_s(fp, "%d%d%d", &num1, &num2, &num3);
				if (count != 3)
					continue;
				mindlist[mindcount].type = 'k';
				mindlist[mindcount].num1 = num1;
				mindlist[mindcount].num2 = num2;
				mindlist[mindcount].num3 = num3;
				mindlist[mindcount].num4 = 0;
				mindlist[mindcount].num5 = 0;
				mindcount++;
			}
			else if (mode == 'c')
			{
				count = fscanf_s(fp, "%d%d%d%d", &num1, &num2, &num3, &num4);
				if (count != 4)
					continue;
				mindlist[mindcount].type = 'c';
				mindlist[mindcount].num1 = num1;
				mindlist[mindcount].num2 = num2;
				mindlist[mindcount].num3 = num3;
				mindlist[mindcount].num4 = num4;
				mindlist[mindcount].num5 = 0;
				mindcount++;
			}
			else if (mode == 'm')
			{
				count = fscanf_s(fp, "%d%d%d%d%d", &num1, &num2, &num3, &num4, &num5);
				if (count != 5)
					continue;
				mindlist[mindcount].type = 'm';
				mindlist[mindcount].num1 = num1;
				mindlist[mindcount].num2 = num2;
				mindlist[mindcount].num3 = num3;
				mindlist[mindcount].num4 = num4;
				mindlist[mindcount].num5 = num5;
				mindcount++;
			}
			else if (mode == 'r')
			{
				count = fscanf_s(fp, "%d%d%d%d", &num1, &num2, &num3, &num4);
				if (count != 4)
					continue;
				mindlist[mindcount].type = 'r';
				mindlist[mindcount].num1 = num1;
				mindlist[mindcount].num2 = num2;
				mindlist[mindcount].num3 = num3;
				mindlist[mindcount].num4 = num4;
				mindlist[mindcount].num5 = 0;
				mindcount++;
			}
			else if (mode == 'l')
			{
				count = fscanf_s(fp, "%d%d%d", &loop, &looptime,&waitloop);
				if (count != 3)
					continue;
				if (loop == 0)
					break;
			}
			else continue;
		}
		////////////////////////////////////////////
		for (int i = 0; i < looptime; i++)
		{
			for (int j = 0; j < mindcount; j++)
			{
				if (mindlist[j].type == 'k')
				{
					if (mindlist[j].num1 >= 281)
						ExtenBordyKey(mindlist[j].num1, mindlist[j].num2, mindlist[j].num3);
					else
						MedelKebord(mindlist[j].num1, mindlist[j].num2, mindlist[j].num3);
				}
				else if (mindlist[j].type == 'c')
				{
					ModelCursor(mindlist[j].num1, mindlist[j].num2, mindlist[j].num3, mindlist[j].num4);
				}
				else if (mindlist[j].type == 'm')
				{
					ModelCursorMove(mindlist[j].num1, mindlist[j].num2, mindlist[j].num3, mindlist[j].num4, mindlist[j].num5);
				}
				else if (mindlist[j].type == 'r')
				{
					ModelCursorRoll(mindlist[j].num1, mindlist[j].num2, mindlist[j].num3, mindlist[j].num4);
				}
			}
			Sleep(waitloop);
		}
	}
	else
		return;
}
void OperateMedel(char * FileName)
{
	HWND consle = GetForegroundWindow();
	ShowWindow(consle, SW_MINIMIZE);
	FILE * fp = NULL;
	fopen_s(&fp, FileName, "r");
	if (!fp) return;
	char mode = '\0';
	int key = -1, set = -1, wt = 0;
	int x = 0, y = 0, cltype = 3, stime = 0;
	int count = 0;
	while (!feof(fp))
	{
		fscanf_s(fp, "%c", &mode);
		char temp[20] = { 0 };
		if (mode == 'l')
		{
			 OperateLoop(fp);
		}
		else
		if (mode == 'k')
		{
			count = fscanf_s(fp, "%d%d%d", &key, &set, &wt);
			if (count != 3)
				continue;
			if (key >= 281)
				ExtenBordyKey(key, set, wt);
			else
				MedelKebord(key, set, wt);
		}
		else if (mode == 'c')
		{
			count = fscanf_s(fp, "%d%d%d%d", &x, &y, &cltype, &stime);
			if (count != 4)
				continue;
			ModelCursor(x, y, cltype, stime);

		}
		else if (mode == 'm')
		{
			int mx, my, mx1, my1, wite;
			count = fscanf_s(fp, "%d%d%d%d%d", &mx, &my, &mx1, &my1, &wite);
			if (count != 5)
				continue;
			ModelCursorMove(mx, my, mx1, my1, wite);
		}
		else if (mode == 'r')
		{
			int mx, my, roll, wait;
			count = fscanf_s(fp, "%d%d%d%d", &mx, &my, &roll, &wait);
			if (count != 4)
				continue;
			ModelCursorRoll(mx, my, roll, wait);
		}
		else continue;
	}
	fclose(fp);
}
void ModelCursorRoll(int mx, int my, int rdata, int wait)
{
	SetCursorPos(mx, my);
	if (rdata == 1)
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
	else if (rdata == 0)
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
	Sleep(wait);

}
void ModelCursorMove(int mx, int my, int mx1, int my1, int wite)
{
	int addx = mx1 - mx >= 0 ? 1 : -1;
	int addy = my1 - my >= 0 ? 1 : -1;
	SetCursorPos(mx, my);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //�������
	for (int i = mx; i < mx1; i++)
	{
		SetCursorPos(i, my);
		mx = i;
		if (i % 3 == 0)
			Sleep(1);
	}
	for (int j = my; j < my1; j++)
	{
		SetCursorPos(mx, j);
		my = j;
		if (j % 3 == 0)
			Sleep(1);
	}
	SetCursorPos(mx1, my1);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //����ɿ�
	Sleep(wite);
}
void MedelKebord(int key, int set, int wt)
{
	if (set == 1)
		keybd_event(key, 0, 0, 0);
	if (set == 0)
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	Sleep(wt);
}
void ModelCursor(int x, int y, int cltype, int stime)
{
	SetCursorPos(x, y);
	if (cltype == 1)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); //�������
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);  //����ɿ�
	}
	if (cltype == 0)
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); //�Ҽ�����
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);  //�Ҽ��ɿ�
	}
	Sleep(stime);
}

void help()
{
	char deca[400][80]{
		"�������\t\t��Ӧֵ\t\t��Ӧ��",
			"Designer: Ice2Faith",
			"-------------------------------",
			"VK_F1\t\t\t112\t\tF1",
			"VK_F2\t\t\t113\t\tF2",
			"VK_F3\t\t\t114\t\tF3",
			"VK_F4\t\t\t115\t\tF4",
			"VK_F5\t\t\t116\t\tF5",
			"VK_F6\t\t\t117\t\tF6",
			"VK_F7\t\t\t118\t\tF7",
			"VK_F8\t\t\t119\t\tF8",
			"VK_F9\t\t\t120\t\tF9",
			"VK_F10\t\t\t121\t\tF10",
			"VK_F11\t\t\t122\t\tF11",
			"VK_F12\t\t\t123\t\tF12",
			"0\t\t\t48",
			"1\t\t\t49",
			"2\t\t\t50",
			"3\t\t\t51",
			"4\t\t\t52",
			"5\t\t\t53",
			"6\t\t\t54",
			"7\t\t\t55",
			"8\t\t\t56",
			"9\t\t\t57",
			"A\t\t\t65",
			"B\t\t\t66",
			"C\t\t\t67",
			"D\t\t\t68",
			"E\t\t\t69",
			"F\t\t\t70",
			"G\t\t\t71",
			"H\t\t\t72",
			"I\t\t\t73",
			"J\t\t\t74",
			"K\t\t\t75",
			"L\t\t\t76",
			"M\t\t\t77",
			"N\t\t\t78",
			"O\t\t\t79",
			"P\t\t\t80",
			"Q\t\t\t81",
			"R\t\t\t82",
			"S\t\t\t83",
			"T\t\t\t84",
			"U\t\t\t85",
			"V\t\t\t86",
			"W\t\t\t87",
			"X\t\t\t88",
			"Y\t\t\t89",
			"Z\t\t\t90",
			"VK_ESCAPE\t\t27\t\tEsc",
			"VK_TAB\t\t\t9\t\tTab",
			"VK_CAPITAL\t\t20\t\tCaps Lock",
			"VK_SHIFT\t\t16\t\tShift",
			"VK_CONTROL\t\t17\t\tCtrl",
			"VK_MENU\t\t\t18\t\tAlt",
			"VK_LSHIFT\t\t160\t\t��shift",
			"VK_RSHIFT\t\t161\t\t��shift",
			"VK_LCONTROL\t\t162\t\t��control",
			"VK_RCONTROL\t\t163\t\t��control",
			"VK_LMENU\t\t164\t\t��Alt",
			"VK_RMENU\t\t165\t\t��Alt",
			"VK_LWIN\t\t\t91\t\t��WIN",
			"VK_RWIN\t\t\t92\t\t��WIN",
			"VK_SPACE\t\t32\t\tSpace",
			"VK_BACK\t\t\t8\t\tBackspace",
			"VK_RETURN\t\t13\t\tEnter",
			"VK_KANJI\t\t25\t\t*",
			"VK_OEM_3\t\t192\t\t` ~",
			"VK_OEM_PLUS\t\t187\t\t= +",
			"VK_OEM_MINUS\t\t189\t\t- _",
			"VK_OEM_4\t\t219\t\t[ {",
			"VK_OEM_6\t\t221\t\t] }",
			"VK_OEM_5\t\t220\t\t\\ |",
			"VK_OEM_1\t\t186\t\t; :",
			"VK_OEM_7\t\t222\t\t' \"",
			"VK_OEM_COMMA\t\t188\t\t, <",
			"VK_OEM_PERIOD\t\t190\t\t. >",
			"VK_OEM_2\t\t191\t\t/ ?",
			"VK_LBUTTON\t\t1\t\t������",
			"VK_RBUTTON\t\t2\t\t����Ҽ�",
			"VK_MBUTTON\t\t4\t\t����м�",
			"VK_INSERT\t\t45\t\tInsert",
			"VK_DELETE\t\t46\t\tDelete",
			"VK_PRIOR\t\t33\t\tPage Up",
			"VK_NEXT\t\t\t34\t\tPage Down",
			"VK_END\t\t\t35\t\tEnd",
			"VK_HOME\t\t\t36\t\tHome",
			"VK_LEFT\t\t\t37\t\tLeft Arrow",
			"VK_UP\t\t\t38\t\tUp Arrow",
			"VK_RIGHT\t\t39\t\tRight Arrow",
			"VK_DOWN\t\t\t40\t\tDown Arrow",
			"VK_PRINT\t\t42\t\tPrint Sc Sys",
			"VK_SCROLL\t\t145\t\tScroll Lock",
			"VK_PAUSE\t\t19\t\tPause Break",
			"VK_NUMLOCK\t\t144\t\tNum Lock",
			"VK_NUMPAD0\t\t96\t\tС���� 0",
			"VK_NUMPAD1\t\t97\t\tС���� 1",
			"VK_NUMPAD2\t\t98\t\tС���� 2",
			"VK_NUMPAD3\t\t99\t\tС���� 3",
			"VK_NUMPAD4\t\t100\t\tС���� 4",
			"VK_NUMPAD5\t\t101\t\tС���� 5",
			"VK_NUMPAD6\t\t102\t\tС���� 6",
			"VK_NUMPAD7\t\t103\t\tС���� 7",
			"VK_NUMPAD8\t\t104\t\tС���� 8",
			"VK_NUMPAD9\t\t105\t\tС���� 9",
			"VK_MULTIPLY\t\t106\t\tС���� *",
			"VK_ADD\t\t\t107\t\tС���� +",
			"VK_SEPARATOR\t\t108\t\tС���� Enter",
			"VK_SUBTRACT\t\t109\t\tС���� -",
			"VK_DECIMAL\t\t110\t\tС���� .",
			"VK_DIVIDE\t\t111\t\tС���� /",
			"VK_SELECT\t\t41\t\tSelect",
			"VK_EXECUTE\t\t43\t\tExecute",
			"VK_SNAPSHOT\t\t44\t\tSnapshot",
			"VK_HELP\t\t\t47\t\tHelp",
			"VK_CANCEL\t\t3\t\tCancel",
			"VK_CLEAR\t\t12\t\tClear",
			"VK_VOLUME_MUTE\t\t173\t\tVolumeMute",
			"VK_VOLUME_DOWN\t\t174\t\tVolumeDown",
			"VK_VOLUME_UP\t\t175\t\tVolumeUp",
			"VK_BROWSER_BACK\t\t166\t\t�����back",
			"VK_BROWSER_FORWARD\t167\t\t�����forward",
			"VK_BROWSER_REFRESH\t168\t\t�����refresh",
			"VK_BROWSER_STOP\t\t169\t\t�����\t\t",
			"VK_BROWSER_SEARCH\t170\t\t�����search",
			"VK_BROWSER_FAVORITES\t171\t\t�����favorites",
			"VK_BROWSER_HOME\t\t172\t\t�����home",
			"VK_F13\t\t\t124",
			"VK_F14\t\t\t125",
			"VK_F15\t\t\t126",
			"VK_F16\t\t\t127",
			"VK_F17\t\t\t128",
			"VK_F18\t\t\t129",
			"VK_F19\t\t\t130",
			"VK_F20\t\t\t131",
			"VK_F21\t\t\t132",
			"VK_F22\t\t\t133",
			"VK_F23\t\t\t134",
			"VK_F24\t\t\t135",
			"VK_XBUTTON1\t\t5",
			"VK_XBUTTON2\t\t6",
			"VK_KANA\t\t\t21",
			"VK_HANGUL\t\t21",
			"VK_JUNJA\t\t23",
			"VK_FINAL\t\t24",
			"VK_HANJA\t\t25",
			"VK_CONVERT\t\t28",
			"VK_NONCONVERT\t\t29",
			"VK_ACCEPT\t\t30",
			"VK_MODECHANGE\t\t31",
			"VK_APPS\t\t\t93",
			"VK_SLEEP\t\t95",
			"VK_MEDIA_NEXT_TRACK\t176",
			"VK_MEDIA_PREV_TRACK\t177",
			"VK_MEDIA_STOP\t\t178",
			"VK_MEDIA_PLAY_PAUSE\t179",
			"VK_LAUNCH_MAIL\t\t180",
			"VK_LAUNCH_MEDIA_SELECT\t181",
			"VK_LAUNCH_APP1\t\t182",
			"VK_LAUNCH_APP2\t\t183",
			"VK_OEM_8\t\t223",
			"VK_OEM_102\t\t226",
			"VK_PACKET\t\t231",
			"VK_PROCESSKEY\t\t229",
			"VK_ATTN\t\t\t246",
			"VK_CRSEL\t\t247",
			"VK_EXSEL\t\t248",
			"VK_EREOF\t\t249",
			"VK_PLAY\t\t\t250",
			"VK_ZOOM\t\t\t251",
			"VK_NONAME\t\t252",
			"VK_PA1\t\t\t253",
			"VK_OEM_CLEAR\t\t254",
			"-------------------------------",
			"ר�����ӹ��ܰ���:",
			"���Ӱ����ű�û��״̬0��־�����ֻ��һ��",
			"��Ȼ�����Ľű���״̬0��־�У�Ҳ�ᱻ����",
			"WAITRUN\t\t\t281\t\t��ͣ�ű�����һ��",
			"RANDIN\t\t\t282\t\t��������ַ�1��15��",
			"CMD\t\t\t283\t\t��CMD����̨",
			"POWERSHELL\t\t284\t\t��Powershell",
			"-------------------------------",
			"ִ���ļ�˵����",
			"����ִ�б�ʶ��ֻ��c��k��������ʶ�ᱻ����",
			"����˵����k ���� ״̬ ʱ�� (����������ʾ)",
			"���磺k 91 1 30 ��WIN��",
			"��ʶ�Ǽ��̲�������Win�����ӳ�30�����ִ����һ��",
			"״̬��1���£�0̧��",
			"��˳���������",
			"k 91 1 30",
			"k 91 0 30",
			"��ϼ���ʶ��WIN+SΪ��",
			"k 91 1 30",
			"k 83 1 30",
			"k 83 0 30",
			"k 91 0 30",
			"����˵����k ������ ������ ״̬ ʱ�� (����������ʾ)",
			"���磺c 18 854 1 1200 CLEFT",
			"��ʶ��������������λ��18-854��λ�ã��ӳ�1200�����ִ����һ��",
			"18�������ҵ�18����",
			"854�����ϵ��µ�854����",
			"״̬��1���������0�Ҽ�����",
			"���ҵĵ��������λ���ǿ�ʼ�˵�",
			"��ק�ļ�����˵����",
			"m Դ������ Դ������ Ŀ�ĺ����� Ŀ�������� ʱ�� (����������ʾ)",
			"���磺m 290 296 1012 308 60 CMOVE",
			"��ʾ��290,296λ����ק��1012,308λ�ã�60�����ִ����һ��ָ��",
			"�ر�ע�⣺ֻ�а�4֮��Ż��¼���˴β�����Ҳ���ǲ�����˳��",
			"�����ֲ���˵����",
			"m Դ������ Դ������ Ŀ�ĺ����� Ŀ�������� ʱ�� (����������ʾ)",
			"���磺r 306 486 1 80 ROOLUP",
			"��ʾ��306,486λ���Ϲ�һ��80�����ִ����һ��ָ��",
			"-------------------------------",
			"�ļ��ű�¼��˵��",
			"1.��������֣�",
			"�ƶ���굽Ҫ����ĵط���ע������в�Ҫ������������Ҽ�����Ҫ",
			"Ȼ��1��ʶ���������2��ʶ�Ҽ�������5��ʶ�������¼��",
			"�ر�ģ�����3��ʶ��ʼ��ק��4��ʾ������ק��6��ʾ���Ĺ����Ϲ���7��ʾ�¹�",
			"����3�ڼ��Ժ���������������Ч������5�����Լǵð�4������ק",
			"���¼�Ƽ���",
			"������ָ��λ�ã��������м�¼�����������Ҫ�ƶ����",
			"������ղŵ�λ�ý�����һ��",
			"����Alt+Tab����¼�����Ƶ�ǰ̨������¼�����η�������",
			"���¼��ʱʱ����������ʱ�Ӿ���",
			"2.��ͨ��������(0-9 & A-Z)",
			"������������룬ֱ��������س�Ϊֹ�������п����пո��\\N\\Tת���ַ�����",
			"ע�⣬����ת���ַ���ʶ��",
			"3/4.���������̵��(WIN ALT D 9 ...) & ��ϼ����룺",
			"��ע��������д�������룬��ȷ���������ȷ��",
			"�����ǵ����ַ�����ҲҪ�ո����",
			"¼�벻��ȷ�İ������ᱻ������������ɴﲻ��Ԥ�ڵ�Ч��",
			"������нű��������������²���",
			"�Ҽ�����ѡ�����ԣ�ѡ������ԣ�ѡ���ù���ԱȨ�����У�ѡ��ȷ�ϼ��ɡ�",
			"ִ�нű�ʱ���Զ���С����������Ŷ�����Ҳ�����",
			"-------------------------------",
			"�����ļ���ִ��˵����",
			"Ĭ�Ϻ�׺ģʽ��001_MU.txtֻ������001",
			"��ȫ����ģʽ����Ҫ��׺�����Զ��г�Ŀ¼���ļ����ṩ��ݸ���",
			"�����й��ߣ�",
			"�ṩ������ɾ���ű������del �ļ�������ȫ���ƣ�",
			"��Ҫɾ��ȷ��������dir�鿴�ļ��Ƿ񻹴���",
			"-------------------------------",
	};
	int i = 0;
	while (deca[i][0] != 0)
	{
		cout << deca[i++] << endl;
	}
	cout << "Click any key end view" << endl;
	_getch();
}
