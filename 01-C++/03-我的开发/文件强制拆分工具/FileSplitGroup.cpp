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
	system("title 文件强制拆分工具 by Ice2Faith");
	system("color f1");
	__int64  maxsizefile = 1024 * 1024;
	int delsource = 1;
	char file[2048] = { 0 };
	while (1)
	{
		int sel = Meau();
		if (argc > 1)
			cout << "已关联文件：" << argv[1] << endl;
		switch (sel)
		{
		case 1:
		{
				  char def = 0;
				  if (argc > 1)
				  {
					  cout << "选项：0=输入 1=已加载\n>/ ";
					  while (def<'0' || def>'1')
						  def = getch();
				  }
				  else
					  def = '0';

				  if (def == '0')
				  {
					  cout << "请输入要拆分的文件名\n>/ ";
					  gets(file);
					  while (!strlen(file))
						  gets(file);
				  }
				  else
				  {
					  strcpy(file, argv[1]);
				  }
				  char basesize = 0;
				  cout << "拆分单位：0=KB 1=MB 2=GB\n>/ ";
				  while (basesize<'0' || basesize>'2')
				  {
					  basesize = getch();
				  }
				  char ssize[3][5] = { "KB", "MB", "GB" };
				  cout << "请输入单个文件的拆分空间(单位" << ssize[basesize - '0'] << ")\n>/ ";
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
					  cout << "请认真一点重新输入，范围不在1KB-8589934591GB之间\n>/ ";
					  cin >> maxsizefile;
				  }
				  cout << "删除源文件：0=保留 1=删除\n>/ ";
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
					  cout << "选项：0=输入 1=已加载\n>/ ";
					  while (def<'0' || def>'1')
						  def = getch();
				  }
				  else
					  def = '0';

				  if (def == '0')
				  {
					  cout << "请输入要还原的的文件名(.mfsg)\n>/ ";
					  gets(file);
					  while (!strlen(file))
						  gets(file);
				  }
				  else
				  {
					  strcpy(file, argv[1]);
				  }

				  cout << "删除源文件：0=保留 1=删除\n>/ ";
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
	cout << "\t文件强制拆分工具\n\n";
	cout << "\t1.拆分文件\n";
	cout << "\t2.还原文件\n";
	cout << "\t3.查看帮助\n";
	cout << "\t0.退出程序\n";
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
	cout << "\t   文件强制拆分工具\n\n";
	cout << "\t最小支持的拆分单元大小：\n";
	cout << "\t=1KB\n";
	cout << "\t最大支持的(被)拆分单元大小：\n";
	cout << "\t=9007199254740991KB\n";
	cout << "\t=8796093022207MB\n";
	cout << "\t=8589934591GB\n";
	cout << "\t=8388607TB\n";
	cout << "\t最大拆分文件后数量：\n";
	cout << "\t=2048个\n";
	cout << "\t拆分文件可选单位：\n";
	cout << "\t=KB\n";
	cout << "\t=MB\n";
	cout << "\t=GB\n";
	cout << "\t运行速度介绍：\n";
	cout << "\t受操作系统资源分配影响\n";
	cout << "\t受系统磁盘主频硬件性能影响\n";
}
void FileSplitGroup(char * file, __int64  bytesize, int delsource)
{
	FILE * sfile = fopen(file, "rb");
	if (!sfile)
		return;
	cout << "文件打开成功！！\n";
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
		cout << "拆分后文件过多，操作取消！！\n";
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
	cout << "正在创建文件组...\n";
	cout << "创建主文件：" << newfile[newcount] << endl;
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
			cout << "创建附加文件：" << newfile[newcount] << endl;
			gfile = fopen(newfile[newcount], "wb");
			newcount++;
		}
	}
	fclose(gfile);
	fclose(sfile);
	cout << "文件组创建完毕！！\n";
	if (delsource)
	{
		remove(file);
		cout << "移除源文件完毕！！\n";
	}
	cout << "所有操作已结束！！\n";
}
void FileGroupCombine(char * mainfile, int delsource)
{
	FILE * gfile = fopen(mainfile, "rb");
	if (!gfile)
		return;
	cout << "打开文件成功！！\n";
	char sourcefilename[400] = { 0 };
	char newfile[100][400] = { 0 };
	__int64 sumcount = 0;
	int lenname = 0;
	int flag = 0;
	fread(&flag, sizeof(int), 1, gfile);
	if (flag != -17)
	{
		fclose(gfile);
		cout << "主文件校验失败，操作结束！！\n";
		return;
	}
	cout << "主文件校验成功！！\n";
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
	cout << "正在合并文件组...\n";
	cout << "主文件合并中：" << mainfile << "...\n";
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
		cout << "附属文件合并中：" << newfile[i] << "...\n";
		gfile = fopen(newfile[i], "rb");
		if (!gfile)
		{
			cout << "文件丢失：" << newfile[i] << endl;
			cout << "合并失败，即将终止操作！！\n";
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
	cout << "文件合并完毕！！\n";
	fclose(cfile);
	if (delsource)
	{
		for (int i = 0; i < sumcount; i++)
			remove(newfile[i]);
		cout << "移除源文件完毕！！\n";
	}
	cout << "所有操作已结束！！\n";
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
