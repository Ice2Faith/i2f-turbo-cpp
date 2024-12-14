/** Name: Item Name*/
#include<stdio.h>
#include<stdlib.h>
#include"EverythingLocker.hpp"
#include"EveryFileLocker.hpp"

int main(int argc, char * argv[])
{
	if (argc >= 5)
	{
		EveryFileLocker flocker;
		bool modeIsLock = false;
		if (strcmp(argv[1], "lock") == 0)
			modeIsLock = true;
		else if (strcmp(argv[1], "unlock") == 0)
			modeIsLock = false;
		else
		{
			printf("�ļ��ӽ��ܲ�����\n\tģʽ��lock|unlock�� Դ�ļ��� ���ļ��� ����\n");
			system("pause");
			return 0;
		}
		char * srcF = argv[2];
		char * drtF = argv[3];
		char * opeP = argv[4];
		if (modeIsLock)
			flocker.lock(srcF,drtF,opeP);
		else
			flocker.unlock(srcF, drtF, opeP);
	}
	else
	{
		printf("�ļ��ӽ��ܲ�����\n\tģʽ��lock|unlock�� Դ�ļ��� ���ļ��� ����\n");
		system("pause");
		return 0;
	}

#if 0
	EverythingLocker locker;
	char arr[] = {"������飺\n\
		��sizeData�ֽڴ�С��data������sizePass�ֽڴ�С��pass�������\n\
		���У�֧����ʷ��������в�����ܣ��⽫�����ӱ�������ܵ����Ѷȣ�Ҳ���Ǹ��Ӱ�ȫ\n\
	����˵����\n\
		data : ���ݵ�ַ\n\
		sizeData : ���ݴ�С���ֽڣ�\n\
		pass : �����ַ\n\
		sizePass : �����С(�ֽ�)\n\
		continueLast : �Ƿ������һ��ִ�к�������룬��Ϊ������ʷ������������\n\
		cleanLast : �Ƿ������һ��ִ�е�������\n\
	����ֵ��\n\
		�����Ƿ�ɹ�����cleanLast��־λΪtrue����ֱ�������һ��ִ�в�����false"};
	char pass[] = {"1111111"};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//ֱ��ȫ��һ�����ʾ����
	//continueLastֵΪfalse����ʹ����ʷ��ʷ�����룬Ĭ��ֵҲ��false,������ܻ���Ϊ��ʷ�����뵼�������ʧ��
	//���ߣ��������ǰ��cleanLastλΪtrue���Ҳ��
	locker.lock((unsigned char *)arr, sizeof(arr), (unsigned char *)pass, sizeof(pass), false);

	locker.unlock((unsigned char *)arr, sizeof(arr), (unsigned char *)pass, sizeof(pass), false);
	printf("���δ����\n%s\n",arr);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��ռ��ܽ��ܵ���ʷ������
	//Ϊ����ķֶδ�����׼��
	locker.lock(NULL, 0, NULL, 0, false, true);
	locker.unlock(NULL, 0, NULL, 0, false, true);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����������ʷ�����룬��ԭʼ���ݽ��зֶδ���
	//ʹ�ñ�־λ��continueLast=true
	//����Ϊ��������ʷ����������ã����������˼��ܺͽ���ʱ�Ķγ��Ȳ�һ����������
	long sizeArr = sizeof(arr);
	//����ʱ����stepLock�������м���
	long stepLock = 5;
	long i=0;
	for ( i = 0; i + stepLock < sizeArr; i += stepLock)
	{
		locker.lock((unsigned char *)&arr[i], stepLock, (unsigned char *)pass, sizeof(pass), true);
	}
	//ע�⣬�����������ݴ������֮�󣬿��ܻ��в�����һ�ε����ݣ�����С�ڶγ��ȣ�
	if (i<sizeArr)
		locker.lock((unsigned char *)&arr[i], sizeArr-i, (unsigned char *)pass, sizeof(pass), true);

	//����ʱ����stepUnlock�������н���
	//pass[0] = 'A';//������һ�������ͬ�����ܻ���������ȫ����Ľ����������Ѵ���ȡ��ע��
	long stepUnlock = 3;
	for (i = 0; i + stepUnlock < sizeArr; i += stepUnlock)
	{
		locker.unlock((unsigned char *)&arr[i], stepUnlock, (unsigned char *)pass, sizeof(pass), true);
	}
	if (i<sizeArr)
		locker.unlock((unsigned char *)&arr[i], sizeArr - i, (unsigned char *)pass, sizeof(pass), true);
	printf("\n\n�ֶ������봦���\n%s\n", arr);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	system("pause");
#endif
	return 0;
}