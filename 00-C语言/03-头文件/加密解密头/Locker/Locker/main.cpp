#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"EveryFileLocker.hpp"

int main(int argc, char * argv[])
{
	char helpInfo[] = {"命令参数：模式 源文件名 新文件名 密码 [-d]\n\
\t-d:指定操作成功删除源文件，可选参数\n\
\t模式选项：lock/unlock\n\
\t例如：lock D:\\aaa.zip D:\\aaa.zip.flcl hello -d\n\
\t对于加密后的文件，建议添加后缀：.flcl,这样方便你识别\n\
"};
	if (argc < 5)
	{
		printf(helpInfo);
		system("pause");
		return 0;
	}
	bool modeLock = true;
	if (strcmp(argv[1], "lock") == 0)
		modeLock = true;
	else if (strcmp(argv[1], "unlock") == 0)
		modeLock = false;
	else
	{
		printf("关键模式参数不正确，请查看帮助\n");
		printf(helpInfo);
		system("pause");
		return 0;
	}
	char * srcFile = argv[2];
	char * drtFile = argv[3];
	char * password = argv[4];
	bool needDelSrc = false;
	if (argc >= 6)
	{
		if (strcmp(argv[5], "-d") == 0)
			needDelSrc = true;
		else
		{
			printf("检测到无效参数，已被忽略：%s\n",argv[5]);
		}
	}

	EveryFileLocker locker;
	BOOL_T isSuccess = BOOL_FALSE;
	if (modeLock)
		isSuccess = locker.lock(srcFile, drtFile, password);
	else
		isSuccess = locker.unlock(srcFile, drtFile, password);

	if (isSuccess)
	{
		if (needDelSrc)
		{
			remove(srcFile);
		}
		printf("文件 %s 成功：%s --> %s by password:%s\n",(modeLock==true?"加密":"解密"),srcFile,drtFile,password);
	}
	else
	{
		printf("文件 %s 失败：%s 请检查文件是否存在或其他原因！\n", (modeLock == true ? "加密" : "解密"), srcFile);
	}

	return 0;
}