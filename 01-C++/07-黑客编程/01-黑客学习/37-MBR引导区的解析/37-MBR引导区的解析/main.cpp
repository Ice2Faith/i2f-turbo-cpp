#include<stdio.h>
#include<Windows.h>
/*MBRλ���豸�ĵ�һ��������Ҳ���ǿ�ʼ��512�ֽڣ�һ������512�ֽڣ�

�����GPTӲ�̣���ô��Ȼ����MBR����Ϊ����
GPTͷλ�ڵڶ���������
�����ź����32���������ܹ�����128���������ÿ��������128�ֽ�
*/
//�����ⲿ����MBR�Ľṹ����
#define BOOTRECORDSIZE 440
typedef struct _BootRecord//��������ṹ��
{
	unsigned char bootRecord[BOOTRECORDSIZE];//��������440�ֽ�
}BootRecord, *PBootRecord;

#define DPTSIZE 64
typedef struct _DevicePartitionTable//������ṹ��
{
	unsigned char dpt[DPTSIZE];//64�ֽڣ�һ������4����¼��ÿ����¼����ΪDevicePartition�������Ҫ��ǿת
}DevicePartitionTable, *PDevicePartitionTable;

#define DPTNUMBER 4
typedef struct _DevicePartition//�������һ����¼�ṹ��
{
	unsigned char bootFlag;//������־
	unsigned char startHsc[3];//head sector cylinder
	unsigned char partitionType;//��������,���������
	unsigned char endHsc[3];
	unsigned int sectorsPreceding;//������֮ǰʹ�õ�������
	unsigned int sectorsInpartition;//����������������
}DevicePartition, *PDevicePartition;
typedef struct _MasterBootRecord//MBR��Ϣ�ṹ�壬��512�ֽڣ�ռ��һ��������С��һ��������С����512�ֽ�
{
	BootRecord bootRecord;//��������440�ֽ�
	unsigned char ulSigned[4];//windows����ǩ��4�ֽ�
	unsigned char sReserve[2];//����λ2�ֽ�
	DevicePartitionTable dpt;//������64�ֽ�
	unsigned char endFlag[2];//������־2�ֽ�
}MasterBootRecord, *PMasterBootRecord;
/*
�������ͣ�
	0x07 ��ͨ���� NTFS 
	0xee ��ʶ��������PMBR���������ľ���GPT������ͷ��GPT�������ʶ��һ��GPTӲ��
	0xef ��ʶEFIϵͳ����
	0x27 ��ʶ�ָ�����
	0x42 ��ʶLDM���ݷ���
	0x12 0x84 0xde 0xfe 0xa0 ���ǲ�ͬ���̵�OEM����
*/
//�����ⲿ����GPT�Ľṹ����
typedef struct _GUIDPartitionTableHeader//GPT����ͷ��λ�ڵڶ�������512�ֽ�
{
	unsigned char sign[8];//ǩ��8�ֽڣ��̶�ֵΪ��EFI PART
	unsigned int version;//�汾��4�ֽ�
	unsigned int totalHeadLength;//GPTͷ�ֽ�����4�ֽ�
	unsigned int headCrcChechsum;//GPTͷ��CRC�����4�ֽ�
	unsigned char sReserve[4];//����
	unsigned char headSectorIndex[8];//GPTͷ���ڵ�������
	unsigned char headSectorBackupIndex[8];//GPTͷ�������ڵ�������
	unsigned char startUseSectorIndex[8];//GPT��ʼ��������������
	unsigned char endUseSectorIndex[8];//GPT������������������
	unsigned char guid[16];//����GUID
	unsigned char tableStartSectorIndex[8];//GPT������ʼ������
	unsigned int tableItemCount;//����������4�ֽ�
	unsigned int tableItemLength;//ÿ������������ֽ���4�ֽ�
	unsigned int tableCrcChecksum;//�������CRCУ���4�ֽ�
	unsigned char reservePadding[420];//����
}GUIDPartitionTableHeader,*PGUIDPartitionTableHeader;
#define GPT_TABLEITEM_COUNT 128
typedef struct _GUIDPatartitionTableItem//GPT�������128�ֽ�
{
	unsigned char typeGUID[16];//��������GUID
	unsigned char partitionGUID[16]; //����GUID
	unsigned char startPartitionAddress[8];//������ʼ��ַ
	unsigned char entPartitionAddress[8];//����������ַ
	unsigned char partitionAttributes[8];//��������
	unsigned char partitionNameUnicode[72];//��������UNICODE���룩
}GUIDPatartitionTableItem,*PGUIDPatartitionTableItem;

//�����豸�������ӣ����ｫ��һ�������豸��Ϊ���ӣ�ע����д��ʽ��\\.\PhysicalDrive0�������Ǵ���ת��
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
	if (hDevice == INVALID_HANDLE_VALUE)//ע�⣬��ʹ�ù���Ա���У������޷����豸
	{
		printf("Sys:Error %d,Create File Failure!",GetLastError());
		return -1;
	}
	//��ȡMBR��Ϣ
	MasterBootRecord mbr = { 0 };
	GetMBRInfomation(hDevice,&mbr);
	CloseHandle(hDevice);
	//��ʾMBR���ݵ�ʮ������
	ShowMBRBinaryData(&mbr);
	//�ж��Ƿ���GPTӲ�̻���MBRԭ��
	if (MBRTypeIsGPT(&mbr))
	{
		//�����GPTӲ�̣����¶�ȡGPTͷ�ͷ�����
		hDevice = OpenDevice(DEVICE_FLAG_LINK);
		//��ȡGPTͷ����ʾ����
		GUIDPartitionTableHeader gptHeader = { 0 };
		GetGPTHeaderInfomation(hDevice,&gptHeader);
		ShowGPTHeaderBinaryData(&gptHeader);
		//����GPTͷ
		ParseGUIDPartitionTableHeader(&gptHeader);
		//��ȡGPT����������
		GUIDPatartitionTableItem gptItems[GPT_TABLEITEM_COUNT] = { 0 };
		GetAllGPTItems(hDevice,gptItems);
		ParseGUIDPatartitionTableItems(gptItems);
		//�ر��豸���
		CloseHandle(hDevice);
	}
	else
	{
		//����һ��MBR
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
	DWORD dwReaded = 0;//ע�������ȡ��ʽ������Ϊ512���������������ȡ������Ϊ0��Ҳ����û��ȡ������87����˲���һ���Զ�ȡ���������£�������
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
	printf("��������¼��\r\n");
	for (int i = 0; i < BOOTRECORDSIZE; i++)
	{
		printf("%02x ",pMbr->bootRecord.bootRecord[i]);
		if (i % 16 == 15)
			printf("\r\n");
	}
	printf("\r\n");

	printf("����ǩ����\r\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%02x ", pMbr->ulSigned[i]);
	}
	printf("\r\n");

	printf("������\r\n");
	for (int i = 0; i < DPTSIZE; i++)
	{
		printf("%02x ", pMbr->dpt.dpt[i]);
		if (i % 16 == 15)
			printf("\r\n");
	}
	printf("\r\n");

	printf("������¼���飺\r\n");
	PDevicePartition pDp = (PDevicePartition)&(pMbr->dpt.dpt);
	for (int i = 0; i < DPTNUMBER; i++)
	{
		printf("������־��%2x �������ͣ�%2x\r\n",pDp[i].bootFlag,pDp[i].partitionType);
		printf("������֮����������%u ������������������%u\r\n",pDp[i].sectorsPreceding,pDp[i].sectorsInpartition);
		printf("�������Ĵ�С��%.4lfGB\r\n",(double)pDp[i].sectorsInpartition/1024*512/1024/1024);
		printf("\r\n");
	}
	printf("\r\n");

	printf("������ǣ�\r\n");
	for (int i = 0; i < 2; i++)
	{
		printf("%2x ",pMbr->endFlag[i]);
	}
	printf("\r\n");
}
void ParseGUIDPartitionTableHeader(PGUIDPartitionTableHeader pgptHeader)
{
	printf("GPT����GUID��");
	for (int i = 0; i < 16; i++)
	{
		printf("%02x ", pgptHeader->guid[i]);
	}
	printf("\n");

	printf("ǩ����%s\n", pgptHeader->sign);
	printf("�汾��%u\n", pgptHeader ->version );

	printf("GPT������ʼ�����ţ�");
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ", pgptHeader->tableStartSectorIndex[i]);
	}
	printf("\n");

	printf("������������%u\n", pgptHeader->tableItemCount);

	printf("GPTͷ���������ţ�" );
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ",pgptHeader->headSectorBackupIndex[i]);
	}
	printf("\n");

	printf("GPTʹ������ʼ�����ţ�");
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ", pgptHeader->startUseSectorIndex[i]);
	}
	printf("\n");

	printf("GPTʹ��������������ţ�");
	for (int i = 0; i < 8; i++)
	{
		printf("%02x ", pgptHeader->endUseSectorIndex[i]);
	}
	printf("\n");

}
void ParseGUIDPatartitionTableItems(PGUIDPatartitionTableItem items)
{
	GUIDPatartitionTableItem zeroInfo = { 0 };

	printf("�������飺\n");
	for (int i = 0; i < GPT_TABLEITEM_COUNT; i++)
	{
		if (memcmp(&items[i], &zeroInfo, sizeof(GUIDPatartitionTableItem)) == 0)
			continue;
		wprintf(L"��������%s\n", (WCHAR *)items[i].partitionNameUnicode);

		printf("����GUID��");
		for (int i = 0; i < 16; i++)
		{
			printf("%02x ", items[i].partitionGUID[i]);
		}
		printf("\n");

		printf("��������GUID��");
		for (int i = 0; i < 16; i++)
		{
			printf("%02x ", items[i].typeGUID[i]);
		}
		printf("\n");

		printf("������ʼ��ַ��");
		for (int i = 0; i < 8; i++)
		{
			printf("%02x ", items[i].startPartitionAddress[i]);
		}
		printf("\n");

		printf("����������ַ��");
		for (int i = 0; i < 8; i++)
		{
			printf("%02x ", items[i].entPartitionAddress[i]);
		}
		printf("\n");
		printf("\n");
	}

}