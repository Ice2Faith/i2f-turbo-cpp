#include<stdio.h>
#include<iostream>//__int64 type support
using namespace std;
#include<stdlib.h>
#include<string.h>
#include<conio.h>
//----------------__int64--------------------
//-------------2019 06 17 23 18 -------------------
int Meau();
void help();
void GetPathPart(char * path, char * fpath, char * name, char * tail);
void FileSplitGroup(char * file, __int64 bytesize, int delsource);
void FileGroupCombine(char * mainfile, int delsource);
int main(int argc, char * argv[])
{
	system("title �ļ�ǿ�Ʋ�ֹ��� by Ice2Faith");
	system("color f1");
	__int64  maxsizefile = 1024 * 1024;
	int delsource = 1;
	char file[2048] = { 0 };
	while (1)
	{
		int sel = Meau();
		if (argc > 1)
			cout << "�ѹ����ļ���" << argv[1] << endl;
		switch (sel)
		{
		case 1:
		{
				  char def = 0;
				  if (argc > 1)
				  {
					  cout << "ѡ�0=���� 1=�Ѽ���\n>/ ";
					  while (def<'0' || def>'1')
						  def = getch();
				  }
				  else
					  def = '0';

				  if (def == '0')
				  {
					  cout << "������Ҫ��ֵ��ļ���\n>/ ";
					  gets(file);
					  while (!strlen(file))
						  gets(file);
				  }
				  else
				  {
					  strcpy(file, argv[1]);
				  }
				  char basesize = 0;
				  cout << "��ֵ�λ��0=KB 1=MB 2=GB\n>/ ";
				  while (basesize<'0' || basesize>'2')
				  {
					  basesize = getch();
				  }
				  char ssize[3][5] = { "KB", "MB", "GB" };
				  cout << "�����뵥���ļ��Ĳ�ֿռ�(��λ" << ssize[basesize - '0'] << ")\n>/ ";
				  cin >> maxsizefile;
				  if (basesize == '0')
					  maxsizefile *= 1024;
				  else
				  if (basesize == '1')
					  maxsizefile *= 1024 * 1024;
				  else
				  if (basesize == '2')
					  maxsizefile *= 1024 * 1024 * 1024;
				  while (maxsizefile < 1024 || maxsizefile >= 9223372036854775806)
				  {
					  cout << "������һ���������룬��Χ����1KB-8589934591GB֮��\n>/ ";
					  cin >> maxsizefile;
				  }
				  cout << "ɾ��Դ�ļ���0=���� 1=ɾ��\n>/ ";
				  char del = 0;
				  while (del<'0' || del>'1')
					  del = getch();
				  cout << del << endl;
				  delsource = (int)(del - '0');
				  FileSplitGroup(file, maxsizefile, delsource);
		}

			break;
		case 2:
		{
				  char def = 0;
				  if (argc > 1)
				  {
					  cout << "ѡ�0=���� 1=�Ѽ���\n>/ ";
					  while (def<'0' || def>'1')
						  def = getch();
				  }
				  else
					  def = '0';

				  if (def == '0')
				  {
					  cout << "������Ҫ��ԭ�ĵ��ļ���(.mfsg)\n>/ ";
					  gets(file);
					  while (!strlen(file))
						  gets(file);
				  }
				  else
				  {
					  strcpy(file, argv[1]);
				  }

				  cout << "ɾ��Դ�ļ���0=���� 1=ɾ��\n>/ ";
				  char del = 0;
				  while (del<'0' || del>'1')
					  del = getch();
				  cout << del << endl;
				  delsource = (int)(del - '0');
				  FileGroupCombine(file, delsource);
		}

			break;
		case 3:
			help();
			break;
		case 0:
			exit(0);
			break;
		}
		system("pause");
	}

	return 0;
}
int Meau()
{
	system("cls");
	cout << "\t�ļ�ǿ�Ʋ�ֹ���\n\n";
	cout << "\t1.����ļ�\n";
	cout << "\t2.��ԭ�ļ�\n";
	cout << "\t3.�鿴����\n";
	cout << "\t0.�˳�����\n";
	cout << "\t>/ ";
	char sel = 0;
	while (sel<'0' || sel>'3')
	{
		sel = getch();
	}
	cout << sel << endl;
	return (int)(sel - '0');
}
void help()
{
	system("cls");
	cout << "\t   �ļ�ǿ�Ʋ�ֹ���\n\n";
	cout << "\t��С֧�ֵĲ�ֵ�Ԫ��С��\n";
	cout << "\t=1KB\n";
	cout << "\t���֧�ֵ�(��)��ֵ�Ԫ��С��\n";
	cout << "\t=9007199254740991KB\n";
	cout << "\t=8796093022207MB\n";
	cout << "\t=8589934591GB\n";
	cout << "\t=8388607TB\n";
	cout << "\t������ļ���������\n";
	cout << "\t=2048��\n";
	cout << "\t����ļ���ѡ��λ��\n";
	cout << "\t=KB\n";
	cout << "\t=MB\n";
	cout << "\t=GB\n";
	cout << "\t�����ٶȽ��ܣ�\n";
	cout << "\t�ܲ���ϵͳ��Դ����Ӱ��\n";
	cout << "\t��ϵͳ������ƵӲ������Ӱ��\n";
}
void FileSplitGroup(char * file, __int64  bytesize, int delsource)
{
	FILE * sfile = fopen(file, "rb");
	if (!sfile)
		return;
	cout << "�ļ��򿪳ɹ�����\n";
	FILE * gfile = NULL;
	char fpath[2048] = { 0 };
	char name[300] = { 0 };
	char tail[20] = { 0 };
	GetPathPart(file, fpath, name, tail);
	char sourcefilename[400] = { 0 };
	strcpy(sourcefilename, name);
	if (tail[0])
	{
		strcat(sourcefilename, ".");
		strcat(sourcefilename, tail);
	}
	char newfile[2048][400] = { 0 };
	__int64 newcount = 0;
	_fseeki64(sfile, 0, SEEK_END);
	__int64 sumcount = _ftelli64(sfile);
	sumcount = sumcount / bytesize + 1;
	if (sumcount > 2048)
	{
		cout << "��ֺ��ļ����࣬����ȡ������\n";
		return;
	}
	rewind(sfile);
	strcpy(newfile[0], sourcefilename);
	strcat(newfile[0], ".mfsg");
	char node[20] = { 0 };
	for (__int64 i = 1; i < sumcount; i++)
	{
		sprintf(node, "0%d\0", i);
		strcpy(newfile[i], name);
		strcat(newfile[i], node);
		strcat(newfile[i], ".fsg");
	}
	cout << "���ڴ����ļ���...\n";
	cout << "�������ļ���" << newfile[newcount] << endl;
	gfile = fopen(newfile[newcount], "wb");
	newcount++;
	int flag = -17;
	fwrite(&flag, sizeof(int), 1, gfile);
	int lensourcename = strlen(sourcefilename);
	fwrite(&lensourcename, sizeof(int), 1, gfile);
	fwrite(&sourcefilename, sizeof(char), lensourcename, gfile);
	fwrite(&sumcount, sizeof(__int64), 1, gfile);
	for (int i = 0; i < sumcount; i++)
	{
		int lenname = strlen(newfile[i]);
		fwrite(&lenname, sizeof(int), 1, gfile);
		fwrite(&newfile[i], sizeof(char), lenname, gfile);
	}
	__int64 size = 0;
	unsigned char temp = 0;
	while (1)
	{
		if (1 != fread(&temp, sizeof(unsigned char), 1, sfile))
			break;
		if (feof(sfile))
			break;
		fwrite(&temp, sizeof(unsigned char), 1, gfile);
		size++;
		if (size == bytesize)
		{
			size = 0;
			fclose(gfile);
			cout << "���������ļ���" << newfile[newcount] << endl;
			gfile = fopen(newfile[newcount], "wb");
			newcount++;
		}
	}
	fclose(gfile);
	fclose(sfile);
	cout << "�ļ��鴴����ϣ���\n";
	if (delsource)
	{
		remove(file);
		cout << "�Ƴ�Դ�ļ���ϣ���\n";
	}
	cout << "���в����ѽ�������\n";
}
void FileGroupCombine(char * mainfile, int delsource)
{
	FILE * gfile = fopen(mainfile, "rb");
	if (!gfile)
		return;
	cout << "���ļ��ɹ�����\n";
	char sourcefilename[400] = { 0 };
	char newfile[100][400] = { 0 };
	__int64 sumcount = 0;
	int lenname = 0;
	int flag = 0;
	fread(&flag, sizeof(int), 1, gfile);
	if (flag != -17)
	{
		fclose(gfile);
		cout << "���ļ�У��ʧ�ܣ�������������\n";
		return;
	}
	cout << "���ļ�У��ɹ�����\n";
	fread(&lenname, sizeof(int), 1, gfile);
	fread(&sourcefilename, sizeof(char), lenname, gfile);
	FILE * cfile = fopen(sourcefilename, "wb");
	fread(&sumcount, sizeof(__int64), 1, gfile);
	for (int i = 0; i < sumcount; i++)
	{
		int lenname = strlen(newfile[i]);
		fread(&lenname, sizeof(int), 1, gfile);
		fread(&newfile[i], sizeof(char), lenname, gfile);
	}
	cout << "���ںϲ��ļ���...\n";
	cout << "���ļ��ϲ��У�" << mainfile << "...\n";
	unsigned char temp = 0;
	while (1)
	{
		if (1 != fread(&temp, sizeof(unsigned char), 1, gfile))
			break;
		if (feof(gfile))
			break;
		fwrite(&temp, sizeof(unsigned char), 1, cfile);
	}
	fclose(gfile);
	for (int i = 1; i < sumcount; i++)
	{
		cout << "�����ļ��ϲ��У�" << newfile[i] << "...\n";
		gfile = fopen(newfile[i], "rb");
		if (!gfile)
		{
			cout << "�ļ���ʧ��" << newfile[i] << endl;
			cout << "�ϲ�ʧ�ܣ�������ֹ��������\n";
			fclose(cfile);
			remove(sourcefilename);
			return;
		}
		while (1)
		{
			if (1 != fread(&temp, sizeof(unsigned char), 1, gfile))
				break;
			if (feof(gfile))
				break;
			fwrite(&temp, sizeof(unsigned char), 1, cfile);
		}
		fclose(gfile);
	}
	cout << "�ļ��ϲ���ϣ���\n";
	fclose(cfile);
	if (delsource)
	{
		for (int i = 0; i < sumcount; i++)
			remove(newfile[i]);
		cout << "�Ƴ�Դ�ļ���ϣ���\n";
	}
	cout << "���в����ѽ�������\n";
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
		while (j < stail)
		{
			name[k] = tpath[j];
			k++;
			j++;
		}
	}
	else
	{
		j = 0;
		while (j < stail)
		{
			name[k] = tpath[j];
			k++;
			j++;
		}
		sname = 0;
	}

	name[k] = 0;

	k = 0;
	while (k < sname)
	{
		fpath[k] = tpath[k];
		k++;
	}
	fpath[k] = 0;
}
