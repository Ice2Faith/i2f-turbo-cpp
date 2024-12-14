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
			printf("文件加解密参数：\n\t模式（lock|unlock） 源文件名 新文件名 密码\n");
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
		printf("文件加解密参数：\n\t模式（lock|unlock） 源文件名 新文件名 密码\n");
		system("pause");
		return 0;
	}

#if 0
	EverythingLocker locker;
	char arr[] = {"函数简介：\n\
		对sizeData字节大小的data数据用sizePass字节大小的pass密码加密\n\
		其中，支持历史特征码进行参与加密，这将会增加被反向解密的困难度，也就是更加安全\n\
	参数说明：\n\
		data : 数据地址\n\
		sizeData : 数据大小（字节）\n\
		pass : 密码地址\n\
		sizePass : 密码大小(字节)\n\
		continueLast : 是否继续上一次执行后的特征码，因为会有历史特征码参与加密\n\
		cleanLast : 是否清楚上一次执行的特征码\n\
	返回值：\n\
		加密是否成功，当cleanLast标志位为true，则直接清除上一次执行并返回false"};
	char pass[] = {"1111111"};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//直接全部一起操作示例，
	//continueLast值为false而不使用历史历史特征码，默认值也是false,否则可能会因为历史特征码导致你解密失败
	//或者，你可以提前置cleanLast位为true清除也行
	locker.lock((unsigned char *)arr, sizeof(arr), (unsigned char *)pass, sizeof(pass), false);

	locker.unlock((unsigned char *)arr, sizeof(arr), (unsigned char *)pass, sizeof(pass), false);
	printf("整段处理后：\n%s\n",arr);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//清空加密解密的历史特征码
	//为下面的分段处理做准备
	locker.lock(NULL, 0, NULL, 0, false, true);
	locker.unlock(NULL, 0, NULL, 0, false, true);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//下面利用历史特征码，对原始数据进行分段处理
	//使用标志位：continueLast=true
	//并且为了体现历史特征码的作用，我们设置了加密和解密时的段长度不一样（步长）
	long sizeArr = sizeof(arr);
	//加密时按照stepLock步长进行加密
	long stepLock = 5;
	long i=0;
	for ( i = 0; i + stepLock < sizeArr; i += stepLock)
	{
		locker.lock((unsigned char *)&arr[i], stepLock, (unsigned char *)pass, sizeof(pass), true);
	}
	//注意，所有整段数据处理完毕之后，可能还有不满足一段的数据（长度小于段长度）
	if (i<sizeArr)
		locker.lock((unsigned char *)&arr[i], sizeArr-i, (unsigned char *)pass, sizeof(pass), true);

	//解密时按照stepUnlock步长进行解密
	//pass[0] = 'A';//密码有一丁点儿不同，解密基本都是完全错误的结果，不信你把此行取消注释
	long stepUnlock = 3;
	for (i = 0; i + stepUnlock < sizeArr; i += stepUnlock)
	{
		locker.unlock((unsigned char *)&arr[i], stepUnlock, (unsigned char *)pass, sizeof(pass), true);
	}
	if (i<sizeArr)
		locker.unlock((unsigned char *)&arr[i], sizeArr - i, (unsigned char *)pass, sizeof(pass), true);
	printf("\n\n分段特征码处理后：\n%s\n", arr);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	system("pause");
#endif
	return 0;
}