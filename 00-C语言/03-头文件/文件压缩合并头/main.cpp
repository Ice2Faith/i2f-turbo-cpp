#include<stdio.h>
#include"FileJoin.hpp"
#include"HuffmanZip.hpp"
#include"MultiFileZip.hpp"
#include<stdlib.h>
#include<string.h>
int main(int argc, char * argv[])
{
	char helpInfo[] = {"�����в�����\n\
\tģʽ Ŀ��·�� Դ·��1 Դ·��2 ...\n\
\tģʽ��\n\
\t\thzp:\t���ļ�ѹ��\n\
\t\t\thzp test_save.hzp test.mp3\n\
\t\tdhzp:\t���ļ���ѹ\n\
\t\t\tdhzp test.mp3 test_save.hzp\n\
\t\tfjs:\t���ļ�ƴ��\n\
\t\t\tfjs test_save.fjs test1.mp3 test2.mp4\n\
\t\tdfjs:\t���ļ����\n\
\t\t\tdfjs .\savepath\ test_save.fjs\n\
\t\tmzp:\t���ļ�ѹ��\n\
\t\t\tmzp test_save.mzp test.png test.mp3 test.txt\n\
\t\tdmzp:\t���ļ���ѹ\n\
\t\t\tdmzp .\savepath\ test_save.mzp\n\
\tע�⣺\n\
\t\tͨ���������ӣ���Ӧ��֪���ˣ����ļ���ֺͶ��ļ���ѹʱ\n\
\t\tĿ��·����Ҫ��һ���ļ��У�Ҳ���Ƿ��š�\\����β\n\
\t\t���ļ�ѹ���ı��ʣ��Ⱥϲ����ļ� ��ѹ��\n\
" };
	if (argc < 4)
	{
		printf(helpInfo);
		system("pause");
		return 0;
	}
	HuffmanZip ziper;

	FileJoin joiner;

	MultiFileZip mulziper;

	char * mode = argv[1];
	char * drtFile = argv[2];
	int beginInputIndex = 3;

	BOOL_T rst = BOOL_FALSE;
	if (strcmp("hzp", mode) == 0)
	{
		rst=ziper.ZipFile(argv[beginInputIndex], drtFile);
	}
	else if (strcmp("dhzp", mode) == 0)
	{
		rst = ziper.UnzipFile(argv[beginInputIndex], drtFile);
	}
	else if (strcmp("fjs", mode) == 0)
	{
		rst = joiner.join(argc - beginInputIndex, &argv[beginInputIndex], drtFile);
	}
	else if (strcmp("dfjs", mode) == 0)
	{
		rst = joiner.split(argv[beginInputIndex], drtFile);
	}
	else if (strcmp("mzp", mode) == 0)
	{
		rst = mulziper.ZipFiles(argc - beginInputIndex, &argv[beginInputIndex], drtFile);
	}
	else if (strcmp("dmzp", mode) == 0)
	{
		rst = mulziper.UnzipFiles(argv[beginInputIndex], drtFile);
	}
	else
	{
		printf("δʶ���ģʽ����ע���Сд��������ʹ�ð�����");
		printf(helpInfo);
		system("pause");
		return 0;
	}
	if (rst == BOOL_TRUE)
	{
		printf("�����ɹ�,ģʽ��%s\n",mode);
	}
	else
	{
		printf("����ʧ�ܣ������ļ�������Ƿ����Ҫ��\n");
	}

	return 0;
}