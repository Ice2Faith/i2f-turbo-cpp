/** Name: 文件模板生成器*/
#include<stdio.h>
#include<string.h>
void CreateFileC(char *path, char * fileName);
void CreateFileH(char *path, char * fileName);
void CreateFileCPP(char *path, char * fileName);
void CreateFileJava(char *path, char * fileName);
void CreateFilePython(char *path, char * fileName);
void CreateFileHtml(char *path, char * fileName);
void CreateFileGo(char *path, char * fileName);
void CreateFileBat(char *path, char * fileName);
void CreateFileBash(char *path, char * fileName);
void BuildFileAndWriteContent(char * fileName, const char * content);
void stringToLower(char * str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str |= 32;
		str++;
	}
}
void stringToUpper(char * str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str &= ~32;
		str++;
	}
}
int main(int argc, char * argv[])
{
	
	char type[20] = { 0 };
	char path[300] = { 0 };
	if (argc < 3)
	{
		printf("参数说明：类型 保存路径 文件名\n");
		printf("类型：c/h/java/py/html/go/bat/bash\n");
		printf("请输入类型：\n>/ ");
		gets(type);
		printf("请输入保存路径：\n>/ ");
		gets(path);
	}
	else
	{
		strcpy(type, argv[1]);
		strcpy(path, argv[2]);
	}
	
	stringToLower(type);
	printf("请输入文件名:\n>/ ");
	char filename[256] = { 0 };
	gets(filename);
	if (strcmp(type, "c") == 0)
	{
		CreateFileC(path, filename);
	}
	else if (strcmp(type, "h") == 0)
	{
		CreateFileH(path, filename);
	}
	else if (strcmp(type, "cpp") == 0)
	{
		CreateFileCPP(path, filename);
	}
	else if (strcmp(type, "java") == 0)
	{
		CreateFileJava(path, filename);
	}
	else if (strcmp(type, "py") == 0)
	{
		CreateFilePython(path, filename);
	}
	else if (strcmp(type, "html") == 0)
	{
		CreateFileHtml(path, filename);
	}
	else if (strcmp(type, "go") == 0)
	{
		CreateFileGo(path, filename);
	}
	else if (strcmp(type, "bat") == 0)
	{
		CreateFileBat(path, filename);
	}
	else if (strcmp(type, "bash") == 0)
	{
		CreateFileBash(path, filename);
	}
	return 0;
}
void BuildFileAndWriteContent(char * fileName, const char * content)
{
	FILE * fp = fopen(fileName,"w");
	if (fp == NULL)
		return;
	fprintf(fp, "%s", content);
	fclose(fp);
}
void CreateFileC(char *path, char * fileName)
{
	const char content[] = {
"#include<stdio.h>\n\
#include<string.h>\n\
//#include<stdlib.h>\n\
//#include<time.h>\n\
//#include<math.h>\n\
/*\n\
\tAbout:\n\
*/\n\
int main(int argc,char * argv[])\n\
{\n\
\tprintf(\"%%s\",\"%s\");\n\
\treturn 0;\n\
}\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.c", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileH(char *path, char * fileName)
{
	const char content[] = {
"//#pragma once\n\
#ifndef _%s_H_\n\
#define _%s_H_\n\
\n\
#endif // _%s_H_\n\
\0"
	};
	char rcontent[2048];
	char rfilename[300] = { 0 };
	strcpy(rfilename, fileName);
	stringToUpper(rfilename);
	sprintf(rcontent, content, rfilename,rfilename,rfilename);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.h", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileCPP(char *path, char * fileName)
{
	const char content[] = {
"#include<iostream>\n\
#include<string>\n\
//#include<cstdlib>\n\
//#include<ctime>\n\
//#include<cmath>\n\
/*\n\
\tAbout:\n\
*/\n\
using namespace::std;\n\
int main(int argc,char * argv[])\n\
{\n\
\tcout << \"%s\" <<endl;\n\
\treturn 0;\n\
}\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.cpp", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileJava(char *path, char * fileName)
{
	const char content[] = {
"//package %s\n\
public class %s{\n\
\tpublic static void main(String[] args){\n\
\t\tSystem.out.println(\"%s\");\n\
\t\t\n\
\t}\n\
}\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName,fileName,fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.java", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFilePython(char *path, char * fileName)
{
	const char content[] = {
"#-*-coding:utf-8-*-\n\
import sys\n\
import os\n\
\n\
def main():\n\
\tprint(\'%s\')\n\
\n\
if __name__==\'__main__\':\n\
\tmain()\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.py", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileHtml(char *path, char * fileName)
{
	const char content[] = {
"<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>%s</title>\n\
</head>\n\
<body>\n\
%s\n\
\n\
</body>\n\
</html>\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName,fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.html", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileGo(char *path, char * fileName)
{
	const char content[] = {
"package main\n\
\n\
import(\n\
\"fmt\"\n\
)\n\
func main() {\n\
\tfmt.Println(\"%s\")\n\
\n\
}\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.go", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileBat(char *path, char * fileName)
{
	const char content[] = {
"@echo off\n\
echo %s\n\
\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.bat", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}
void CreateFileBash(char *path,char * fileName)
{
	const char content[] = {
"#!/bin/bash\n\
echo \"%s\"\n\
\n\
\0"
	};
	char rcontent[2048];
	sprintf(rcontent, content, fileName);
	char tarFileName[256] = { 0 };
	sprintf(tarFileName, "%s\\%s.sh", path, fileName);
	BuildFileAndWriteContent(tarFileName, rcontent);
}