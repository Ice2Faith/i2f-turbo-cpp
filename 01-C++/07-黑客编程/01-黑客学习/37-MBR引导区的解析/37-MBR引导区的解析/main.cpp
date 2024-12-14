#include<stdio.h>
#include<Windows.h>
/*MBR位于设备的第一个扇区，也就是开始的512字节（一个扇区512字节）

如果是GPT硬盘，那么依然保留MBR，作为保护
GPT头位于第二个扇区，
紧接着后面的32个扇区，能够容纳128个分区表项，每个分区项128字节
*/
//下面这部分是MBR的结构定义
#define BOOTRECORDSIZE 440
typedef struct _BootRecord//引导程序结构体
{
	unsigned char bootRecord[BOOTRECORDSIZE];//引导程序440字节
}BootRecord, *PBootRecord;

#define DPTSIZE 64
typedef struct _DevicePartitionTable//分区表结构体
{
	unsigned char dpt[DPTSIZE];//64字节，一共包含4条记录，每条记录定义为DevicePartition，如果需要请强转
}DevicePartitionTable, *PDevicePartitionTable;

#define DPTNUMBER 4
typedef struct _DevicePartition//分区表的一条记录结构体
{
	unsigned char bootFlag;//引导标志
	unsigned char startHsc[3];//head sector cylinder
	unsigned char partitionType;//分区类型,见后面分析
	unsigned char endHsc[3];
	unsigned int sectorsPreceding;//本分区之前使用的扇区数
	unsigned int sectorsInpartition;//本分区的总扇区数
}DevicePartition, *PDevicePartition;
typedef struct _MasterBootRecord//MBR信息结构体，共512字节，占用一个扇区大小，一个扇区大小就是512字节
{
	BootRecord bootRecord;//引导程序440字节
	unsigned char ulSigned[4];//windows磁盘签名4字节
	unsigned char sReserve[2];//保留位2字节
	DevicePartitionTable dpt;//分区表64字节
	unsigned char endFlag[2];//结束标志2字节
}MasterBootRecord, *PMasterBootRecord;
/*
分区类型：
	0x07 普通分区 NTFS 
	0xee 标识分区表是PMBR，紧跟其后的就是GPT分区表头和GPT分区表标识是一块GPT硬盘
	0xef 标识EFI系统分区
	0x27 标识恢复分区
	0x42 标识LDM数据分区
	0x12 0x84 0xde 0xfe 0xa0 都是不同厂商的OEM分区
*/
//下面这部分是GPT的结构定义
typedef struct _GUIDPartitionTableHeader//GPT分区头，位于第二扇区的512字节
{
	unsigned char sign[8];//签名8字节，固定值为：EFI PART
	unsigned int version;//版本号4字节
	unsigned int totalHeadLength;//GPT头字节总数4字节
	unsigned int headCrcChechsum;//GPT头的CRC检验和4字节
	unsigned char sReserve[4];//保留
	unsigned char headSectorIndex[8];//GPT头所在的扇区号
	unsigned char headSectorBackupIndex[8];//GPT头备份所在的扇区号
	unsigned char startUseSectorIndex[8];//GPT开始分区区域扇区号
	unsigned char endUseSectorIndex[8];//GPT结束分区区域扇区号
	unsigned char guid[16];//磁盘GUID
	unsigned char tableStartSectorIndex[8];//GPT分区表开始扇区号
	unsigned int tableItemCount;//分区表项数4字节
	unsigned int tableItemLength;//每个分区表项的字节数4字节
	unsigned int tableCrcChecksum;//分区表的CRC校验和4字节
	unsigned char reservePadding[420];//保留
}GUIDPartitionTableHeader,*PGUIDPartitionTableHeader;
#define GPT_TABLEITEM_COUNT 128
typedef struct _GUIDPatartitionTableItem//GPT分区表项，128字节
{
	unsigned char typeGUID[16];//分区类型GUID
	unsigned char partitionGUID[16]; //分区GUID
	unsigned char startPartitionAddress[8];//分区开始地址
	unsigned char entPartitionAddress[8];//分区结束地址
	unsigned char partitionAttributes[8];//分区属性
	unsigned char partitionNameUnicode[72];//分区名（UNICODE编码）
}GUIDPatartitionTableItem,*PGUIDPatartitionTableItem;

//定义设备符号链接，这里将第一个物理设备作为链接，注意书写方式：\\.\PhysicalDrive0，下面是带有转义
#define DEVICE_FLAG_LINK (TEXT("\\\\.\\PhysicalDrive0"))
HANDLE OpenDevice(TCHAR * deviceFlagLink);
BOOL MBRTypeIsGPT(PMasterBootRecord pMbr);
void ShowMBRBinaryData(PMasterBootRecord pMbr);
BOOL GetMBRInfomation(HANDLE hDevice, PMasterBootRecord pMbr);
void ParseMasterBootRecord(PMasterBootRecord pMbr);
BOOL GetGPTHeaderInfomation(HANDLE hDevice, PGUIDPartitionTableHeader pGptHeader);
void ShowGPTHeaderBinaryData(PGUIDPartitionTableHeader pgptHeader);
void ParseGUIDPartitionTableHeader(PGUIDPartitionTableHeader pgptHeader);
BOOL GetAllGPTItems(HANDLE hDevice, PGUIDPatartitionTableItem items);
void ParseGUIDPatartitionTableItems(PGUIDPatartitionTableItem items);
int main(int argc, char * argv[])
{
	HANDLE hDevice = OpenDevice(DEVICE_FLAG_LINK);
	if (hDevice == INVALID_HANDLE_VALUE)//注意，请使用管理员运行，否则无法打开设备
	{
		printf("Sys:Error %d,Create File Failure!",GetLastError());
		return -1;
	}
	//获取MBR信息
	MasterBootRecord mbr = { 0 };
	GetMBRInfomation(hDevice,&mbr);
	CloseHandle(hDevice);
	//显示MBR数据的十六进制
	ShowMBRBinaryData(&mbr);
	//判断是否是GPT硬盘还是MBR原生
	if (MBRTypeIsGPT(&mbr))
	{
		//如果是GPT硬盘，重新读取GPT头和分区表
		hDevice = OpenDevice(DEVICE_FLAG_LINK);
		//读取GPT头并显示数据
		GUIDPartitionTableHeader gptHeader = { 0 };
		GetGPTHeaderInfomation(hDevice,&gptHeader);
		ShowGPTHeaderBinaryData(&gptHeader);
		//解析GPT头
		ParseGUIDPartitionTableHeader(&gptHeader);
		//读取GPT分区表并解析
		GUIDPatartitionTableItem gptItems[GPT_TABLEITEM_COUNT] = { 0 };
		GetAllGPTItems(hDevice,gptItems);
		ParseGUIDPatartitionTableItems(gptItems);
		//关闭设备句柄
		CloseHandle(hDevice);
	}
	else
	{
		//解析一般MBR
		ParseMasterBootRecord(&mbr);
	}
	system("pause");
	return 0;
}
HANDLE OpenDevice(TCHAR * deviceFlagLink)
{
	return CreateFile(deviceFlagLink,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0, NULL);
}
BOOL MBRTypeIsGPT(PMasterBootRecord pMbr)
{
	PDevicePartition pDp = (PDevicePartition)&(pMbr->dpt.dpt);
	if (pDp[0].partitionType == 0xee)
		return TRUE;
	return FALSE;
}
void ShowGPTHeaderBinaryData(PGUIDPartitionTableHeader pgptHeader)
{
	printf("BEGIN--------------------------GPTH--------------------------\r\n");
	for (int i = 0; i < sizeof(GUIDPartitionTableHeader); i++)
	{
		printf("%02x ", ((unsigned char*)pgptHeader)[i]);
		if (i % 16 == 15)
			printf("\r\n");
	}
	printf("END----------------------------GPTH--------------------------\r\n");
}
void ShowMBRBinaryData(PMasterBootRecord pMbr)
{
	printf("BEGIN--------------------------MBR--------------------------\r\n");
	for (int i = 0; i < sizeof(MasterBootRecord); i++)
	{
		printf("%02x ",((unsigned char*)pMbr)[i]);
		if (i % 16 == 15)
			printf("\r\n");
	}
	printf("END----------------------------MBR--------------------------\r\n");
}
BOOL GetAllGPTItems(HANDLE hDevice,PGUIDPatartitionTableItem items)
{
	DWORD dwReaded = 0;//注意这里读取方式，必须为512的整数倍，否则读取数量会为0，也就是没读取，错误87，因此采用一次性读取方案（如下），即可
	ReadFile(hDevice, (LPVOID)items, sizeof(GUIDPatartitionTableItem)*GPT_TABLEITEM_COUNT, &dwReaded, NULL);
	if (dwReaded != sizeof(GUIDPatartitionTableItem)*GPT_TABLEITEM_COUNT)
		return FALSE;
	return TRUE;
}
BOOL GetGPTHeaderInfomation(HANDLE hDevice, PGUIDPartitionTableHeader pGptHeader)
{
	DWORD dwReaded = 0;
	MasterBootRecord buffer = { 0 };
	ReadFile(hDevice, (LPVOID)&buffer, sizeof(MasterBootRecord), &dwReaded, NULL);
	ReadFile(hDevice, (LPVOID)pGptHeader, sizeof(GUIDPartitionTableHeader), &dwReaded, NULL);
	if (dwReaded != sizeof(MasterBootRecord))
		return FALSE;
	return TRUE;
}
BOOL GetMBRInfomation(HANDLE hDevice, PMasterBootRecord pMbr)
{
	DWORD dwReaded = 0;
	ReadFile(hDevice, (LPVOID)pMbr, sizeof(MasterBootRecord), &dwReaded, NULL);
	if (dwReaded != sizeof(MasterBootRecord))
		return FALSE;
	return TRUE;
}
void ParseMasterBootRecord(PMasterBootRecord pMbr)
{
	printf("引导区记录：\r\n");
	for (int i = 0; i < BOOTRECORDSIZE; i++)
	{
		printf("%02x ",pMbr->bootRecord.bootRecord[i]);
		if (i % 16 == 15)
			printf("\r\n");
	}
	printf("\r\n");

	printf("磁盘签名：\r\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%02x ", pMbr->ulSigned[i]);
	}
	printf("\r\n");

	printf("分区表：\r\n");
	for (int i = 0; i < DPTSIZE; i++)
	{
		printf("%02x ", pMbr->dpt.dpt[i]);
		if (i % 16 == 15)
			printf("\r\n");
	}
	printf("\r\n");

	printf("分区记录详情：\r\n");
	PDevicePartition pDp = (PDevicePartition)&(pMbr->dpt.dpt);
	for (int i = 0; i < DPTNUMBER; i++)
	{
		printf("引导标志：%2x 分区类型：%2x\r\n",pDp[i].bootFlag,pDp[i].partitionType);
		printf("本分区之间扇区数：%u 本分区的总扇区数：%u\r\n",pDp[i].sectorsPreceding,pDp[i].sectorsInpartition);
		printf("本分区的大小：%.4lfGB\r\n",(double)pDp[i].sectorsInpartition/1024*512/1024/1024);
		printf("\r\n");
	}
	printf("\r\n");

	printf("结束标记：\r\n");
	for (int i = 0; i < 2; i++)
	{
		printf("%2x ",pMbr->endFlag[i]);
	}
	printf("\r\n");
}
void ParseGUIDPartitionTableHeader(PGUIDPartitionTableHeader pgptHeader)
{
	printf("GPT磁盘GUID：");
	for (int i = 0; i < 16; i++)
	{
		printf("%02x ", pgptHeader->guid[i]);
	}
	printf("\n");

	printf("签名：%s\n", pgptHeader->sign);
	printf("版本：%u\n", pgptHeader ->version );

	printf("GPT分区表开始扇区号：");
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ", pgptHeader->tableStartSectorIndex[i]);
	}
	printf("\n");

	printf("分区表项数：%u\n", pgptHeader->tableItemCount);

	printf("GPT头备份扇区号：" );
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ",pgptHeader->headSectorBackupIndex[i]);
	}
	printf("\n");

	printf("GPT使用区域开始扇区号：");
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ", pgptHeader->startUseSectorIndex[i]);
	}
	printf("\n");

	printf("GPT使用区域结束扇区号：");
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ", pgptHeader->endUseSectorIndex[i]);
	}
	printf("\n");

}
void ParseGUIDPatartitionTableItems(PGUIDPatartitionTableItem items)
{
	GUIDPatartitionTableItem zeroInfo = { 0 };

	printf("分区详情：\n");
	for (int i = 0; i < GPT_TABLEITEM_COUNT; i++)
	{
		if (memcmp(&items[i], &zeroInfo, sizeof(GUIDPatartitionTableItem)) == 0)
			continue;
		wprintf(L"分区名：%s\n", (WCHAR *)items[i].partitionNameUnicode);

		printf("分区GUID：");
		for (int i = 0; i < 16; i++)
		{
			printf("%02x ", items[i].partitionGUID[i]);
		}
		printf("\n");

		printf("分区类型GUID：");
		for (int i = 0; i < 16; i++)
		{
			printf("%02x ", items[i].typeGUID[i]);
		}
		printf("\n");

		printf("分区开始地址：");
		for (int i = 0; i < 8; i++)
		{
			printf("%02x ", items[i].startPartitionAddress[i]);
		}
		printf("\n");

		printf("分区结束地址：");
		for (int i = 0; i < 8; i++)
		{
			printf("%02x ", items[i].entPartitionAddress[i]);
		}
		printf("\n");
		printf("\n");
	}

}