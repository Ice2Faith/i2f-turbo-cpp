#include<ntddk.h>

#define TARGETFILENAME (L"\\??\\C:\\driver_file.txt")

//�ں������µ��ļ�������ģ��C����APIʵ��
//�����ļ�
BOOLEAN DriverCreateFile(WCHAR * fileName);
//���ļ�
HANDLE DriverOpenFile(WCHAR * fileName);
//�ر��ļ�
BOOLEAN DriverCloseFile(HANDLE hFile);
//д���ļ�
BOOLEAN DriverWriteFile(HANDLE hFile, PVOID buffer, LONGLONG bufferSize);
//�ж��ļ��Ƿ����ļ���
BOOLEAN DriverIsDirectory(HANDLE hFile);
//��ȡ�ļ���С
LONGLONG DriverFileSize(HANDLE hFile);
//��ȡ�ļ�
BOOLEAN DriverReadFile(HANDLE hFile, PVOID data, LONGLONG maxReadSize);
//��ȡ��ǰ�ļ�ָ��
LONGLONG DriverGetFilePosition(HANDLE hFile);
//���������ļ�ָ�룬�����relativeλ�õ�ƫ����position,relative=0��ʶ��ǰλ�ã�relative<0��ʶ�ļ�ͷ��relative>0��ʶ�ļ�β
BOOLEAN DriverSetFilePositon(HANDLE hFile, LONGLONG position, SHORT relative);
//�����ڴ�ռ�
PVOID DriverAllocMemory(LONGLONG size);
//��fillChar���buffer��ʼ��СΪsize���ڴ�
VOID DriverFillMemory(PVOID buffer, LONGLONG size, CHAR fillCHAR);
//�ͷ�������ڴ�
VOID DriverFreeMemory(PVOID buffer);
VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{

}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING szRegistryPath)
{
	HANDLE hFile;
	LONGLONG bufferSize = 60;
	PVOID buffer = NULL;
	BOOLEAN ret = 0;

	pDriverObject->DriverUnload = DriverUnload;

	ret=DriverCreateFile(TARGETFILENAME);
	KdPrint(("create file %d\r\n",ret));

	hFile= DriverOpenFile(TARGETFILENAME);
	KdPrint(("open file %d\r\n", hFile));
	
	buffer = DriverAllocMemory(bufferSize);
	DriverFillMemory(buffer, bufferSize, 0);
	DriverFillMemory(buffer, bufferSize-1, 0x63);

	ret=DriverWriteFile(hFile, buffer, bufferSize-1);
	KdPrint(("write file %d\r\n", ret));
	ret=DriverCloseFile(hFile);
	KdPrint(("close file %d\r\n", ret));

	DriverFillMemory(buffer, bufferSize, 0);

	hFile = DriverOpenFile(TARGETFILENAME);
	KdPrint(("open file %d\r\n", hFile));
	ret=DriverReadFile(hFile, buffer, bufferSize-1);
	KdPrint(("read file %d\r\n", ret));

	KdPrint(("Read File Content:%s\r\n",buffer));
	return STATUS_SUCCESS;
}
/*
ע�⣬���ڰ���C���Ա��룬������еı�������������ͷ��������C98��C������֮ǰ�汾���б������
	һ������£��ں˲㲻�ܵ����û����API����

������飺
�ļ��������򿪣�������
NTSTATUS ZwCreateFile(
	PHANDLE FileHandle,//���ܴ�������ļ����
	ACCESS_MASK DesiredAccess,//���ļ���������������һ��Ϊ��дGENERIC_READ|GENERIC_WRITE����CreateFileһ��
	POBJECT_ATTRIBUTES ObjectAttributes,//ָ��ṹ�壬�ýṹ�����Ҫ������򿪵��ļ���
	PIO_STATUS_BLOCK IoStatusBlock,//���ܲ������ת̬�Ľṹ��
	PLARGE_INTEGER AllocationSize,//ָ��64λ��������ʶ�ļ��ĳ�ʼ�������С
	ULONG FileAttributes,//ͨ��ΪFILE_ATTRIBUTE_NORMAL����CreateFileһ��
	ULONG ShareAccess,//ָ���ļ��Ĺ���ʽ������ΪFILE_SHARE_READ��FILE_SHARE_WRITE��FILE_SHARE_DELETE����CreateFileһ��
	ULONG CreateDisposition,//�����������ε��ñ���������ͼ������ΪFILE_CREATE��FILE_OPEN��FILE_OPEN_IF��
	ULONG CreateOptions,//ͨ��ΪFILE_SYNCHRONOUS_IO_NONALERT����ʶ�ļ�ͬ�������������ú�������ʱ�����Ѿ�д�����
	PVOID EaBuffer,//ָ���ѡ��չ��������һ��ΪNULL
	ULONG EaLength//ָʾ��չ�������Ĵ�С��һ��Ϊ0
	);
	����ֵ��NTSTATUS���ͣ�������NT_SUCCESS()�����Ƿ�ɹ�

	�ṹ�壨һ�㲻ֱ�ӽ����ֶ����ƣ�ʹ�ú�������
	typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
	} OBJECT_ATTRIBUTES;
	��ֵ��ʼ��������ʵ������һ���꣩��
		InitializeObjectAttributes( 
			POBJECT_ATTRIBUTES initedObjAttri, //ָ��ṹ���ָ��
			PUNICODE_STRING objectName,//�������ƣ�����ZwCreateFile��˵����������ļ�����ע���������ں�ģʽ�µ�·������������Ӧ�ò�"C:\\a.txt"(����"\\\\.\\"��ͷ)���ں˲�Ϊ"\\??\\C:\\a.txt"(������"\\DosDevice\\"��ͷ)
			ULONG attris,//һ��ΪOBJ_CASE_INSENSITIVE����ʶ�����ַ��������ִ�Сд
			HANDLE RootDirectory,//һ��ΪNULL
			PSECURITY_DESCRIPTOR securityDescripor);//���ð�ȫ��������һ��ΪNULL
	UNICEDE_STRING�ṹ��֮ǰ�Ѿ����ܹ���
	typedef struct _UNICODE_STRING {
		USHORT Length;
		USHORT MaximumLength;
		PWCH   Buffer;
		} UNICODE_STRING;
		����UNICEDE_STRING���ͣ�����ֱ����KdPrint�������ʽΪ��KdPrint(("%wZ",&str));
		����ע��ûʹ��֮ǰ��Ҫ���г�ʼ����һ��ʹ�ú������г�ʼ������ȻҲ������������ռ䡣
		��ʼ��������
			VOID RtlInitUnicodeString(
			   PUNICODE_STRING DestinationString,//�ṹָ��
			   PCWSTR SourceString//������ַ���
				);

���ļ�������
��ȻZwCreateFileҲ���Դ��ļ������ǲ���̫�࣬������
������Ǿ����ĺ������������ڽ��н���
	NTSTATUS ZwOpenFile(
		PHANDLE FileHandle,
		ACCESS_MASK DesiredAccess,
		POBJECT_ATTRIBUTES ObjectAttributes,
		PIO_STATUS_BLOCK IoStatusBlock,
		ULONG ShareAccess,
		ULONG OpenOptions
		);

�ر��ļ�������
	NTSTATUS ZwClose(
		 HANDLE Handle//Ҫ�رյ��ļ����
		);

�ļ���Ϣ��ѯ��������С���Ƿ��ļ��еȣ���
	NTSTATUS ZwQueryInformationFile(
		HANDLE FileHandle,//���򿪵��ļ����
		PIO_STATUS_BLOCK IoStatusBlock,//�������õ�״̬
		PVOID FileInformation,//����FileInfomationClass��ͬ����ͬ
		ULONG Length,//FileInfomation���ݵĳ���
		FILE_INFORMATION_CLASS FileInformationClass//������Ҫ��ȡ����������
		);
�ļ���Ϣ���ú������ļ�ָ�룬�޸�ʱ��ȣ���
	NTSTATUS ZwSetInformationFile(//�������ѯ�����������ƣ�ֻ��ע�����������ϵ��ͬ
		HANDLE FileHandle,
		PIO_STATUS_BLOCK IoStatusBlock,
		PVOID FileInformation,
		ULONG Length,
		FILE_INFORMATION_CLASS FileInformationClass
		);
���������ĵ�����������FileInformation���Ǹ��ݵ����������FileInformationClass�������ݾ����ģ�
������������õ�ֵ�У�
	FileStandardInfomation
	FileBasicInfomation
	FilePositionInfomation
	���������Ҳ�Ͷ�Ӧ�˵���������Ҫ����ʲô���Ľṹ��
	���Ƕ�Ӧ�Ľṹ�����£�
	typedef struct _FILE_BASIC_INFORMATION {
	LARGE_INTEGER CreationTime;//�ļ�����ʱ��
	LARGE_INTEGER LastAccessTime;//������ʱ��
	LARGE_INTEGER LastWriteTime;//���д��ʱ��
	LARGE_INTEGER ChangeTime;//�޸�ʱ��
	ULONG FileAttributes;//�ļ�����
	} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

	typedef struct _FILE_STANDARD_INFORMATION {
	LARGE_INTEGER AllocationSize;//Ϊ�ļ�����Ĵ�С��ռ�ô������С��
	LARGE_INTEGER EndOfFile;//�����ļ���β���ֽ���
	ULONG NumberOfLinks;//ӵ�е������ļ�����
	BOOLEAN DeletePending;//�Ƿ�׼��ɾ��
	BOOLEAN Directory;//�Ƿ�ΪĿ¼
	} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

	typedef struct _FILE_POSITION_INFORMATION {
	LARGE_INTEGER CurrentByteOffset;//��ǰ�ļ�ָ��λ��
	} FILE_POSITION_INFORMATION, *PFILE_POSITION_INFORMATION;

	��Щ�ṹ���еĳ�Ա�ṹ�壺
	typedef union _LARGE_INTEGER {
	struct {
		ULONG LowPart;
		LONG HighPart;
	} DUMMYSTRUCTNAME;
	struct {
		ULONG LowPart;
		LONG HighPart;
	} u;
	LONGLONG QuadPart;
	} LARGE_INTEGER;
	�ýṹ����Ҫ������ʶ64λ��������һ��ʹ��QuadPart��Ա

�ļ���ȡ������
	NTSTATUS ZwReadFile(
		HANDLE FileHandle,//�Ѿ��򿪵��ļ����
		 HANDLE Event,//�����첽��ɶ�ȡʱʹ�ã�һ��ΪNULL
		 PIO_APC_ROUTINE ApcRoutine,//�ص����̣������첽��ȡʱ��һ��ΪNULL
		PVOID ApcContext,//һ��ΪNULL
		PIO_STATUS_BLOCK IoStatusBlock,//��¼��ȡ����״̬�Ľṹָ�룬���ԱInformation���ڼ�¼��ȡ���ֽ���
		PVOID Buffer,//�������ݵĻ�����
		ULONG Length,//׼����ȡ�����ݴ�С
		 PLARGE_INTEGER ByteOffset,//ָ����ȡ���ݵ�ƫ�Ƶ�ַ
		PULONG Key//��ȡ�ļ�ʱ�ĸ�����Ϣ��һ��ΪNULL
		);

д���ļ�������
	NTSTATUS ZwWriteFile(//���������Ͷ�ȡ���ƣ�ע�ⷽ�򣬲��ڽ���
		HANDLE FileHandle,
		HANDLE Event,
		PIO_APC_ROUTINE ApcRoutine,
		PVOID ApcContext,
		PIO_STATUS_BLOCK IoStatusBlock,
		bcount(Length) PVOID Buffer,
		ULONG Length,
		PLARGE_INTEGER ByteOffset,
		PULONG Key
		);

�ڴ����뺯����
	PVOID ExAllocatePool(
		POOL_TYPE PoolType,//ö��ֵ������NonPagedPool��PagedPool���ֱ��ʶ�Ƿ�ҳ�ڴ�ͷ�ҳ�ڴ棬�������ܱ��������ļ����ڴ��Ϊ��ҳ�ڴ�
		SIZE_T NumberOfBytes//��Ҫ������ڴ��С
		);
	����ֵ������������ڴ�ĵ�ַ

�ڴ���亯��(����һ����)��
	������Ŀ���ڴ��ַ���ڴ�����С������ַ�
	#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))

�ڴ���պ���(��Ҳ��һ����)��
	��������Ҫ�ͷŵ��ڴ��ַ
	#define ExFreePool(a) ExFreePoolWithTag(a,0)
*/
BOOLEAN DriverCreateFile(WCHAR * fileName)
{
	UNICODE_STRING uniFileName;
	OBJECT_ATTRIBUTES objAttri;
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	HANDLE hFile = NULL;

	RtlInitUnicodeString(&uniFileName, fileName);

	InitializeObjectAttributes(&objAttri, &uniFileName,
		OBJ_CASE_INSENSITIVE,
		NULL, NULL);

	status = ZwCreateFile(&hFile,
		GENERIC_READ | GENERIC_WRITE,
		&objAttri,
		&ioStatusBlock,
		0, FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ,
		FILE_OPEN_IF,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL, 0);
	ZwClose(hFile);
	if (NT_SUCCESS(status))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

HANDLE DriverOpenFile(WCHAR * fileName)
{
	UNICODE_STRING uniFileName;
	OBJECT_ATTRIBUTES objAttri;
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	HANDLE hFile = NULL;

	RtlInitUnicodeString(&uniFileName, fileName);

	InitializeObjectAttributes(&objAttri, &uniFileName,
		OBJ_CASE_INSENSITIVE,
		NULL, NULL);

	status = ZwOpenFile(&hFile,
		GENERIC_READ | GENERIC_WRITE,
		&objAttri,
		&ioStatusBlock,
		FILE_SHARE_READ,
		FILE_SYNCHRONOUS_IO_NONALERT);
	if (NT_SUCCESS(status))
	{
		return hFile;
	}
	else
	{
		return NULL;
	}
}

BOOLEAN DriverCloseFile(HANDLE hFile)
{
	if (NT_SUCCESS(ZwClose(hFile)))
		return TRUE;
	else
		return FALSE;
}

BOOLEAN DriverWriteFile(HANDLE hFile, PVOID buffer, LONGLONG bufferSize)
{
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;

	status = ZwWriteFile(hFile,
		NULL,
		NULL,
		NULL,
		&ioStatusBlock,
		buffer,
		bufferSize,
		0, NULL);
	if (NT_SUCCESS(status))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOLEAN DriverIsDirectory(HANDLE hFile)
{
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	FILE_STANDARD_INFORMATION fsi;

	status = ZwQueryInformationFile(hFile,
		&ioStatusBlock,
		&fsi,
		sizeof(FILE_STANDARD_INFORMATION),
		FileStandardInformation);

	return fsi.Directory;
}

LONGLONG DriverFileSize(HANDLE hFile)
{
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	FILE_STANDARD_INFORMATION fsi;

	status = ZwQueryInformationFile(hFile,
		&ioStatusBlock,
		&fsi,
		sizeof(FILE_STANDARD_INFORMATION),
		FileStandardInformation);

	return (LONGLONG)(fsi.EndOfFile.QuadPart);
}

BOOLEAN DriverReadFile(HANDLE hFile, PVOID data, LONGLONG maxReadSize)
{
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	FILE_POSITION_INFORMATION fpi;

	status = ZwReadFile(hFile,
		NULL,
		NULL,
		NULL,
		&ioStatusBlock,
		data,
		maxReadSize,
		NULL,
		NULL);
	if (NT_SUCCESS(status))
		return TRUE;
	else
		return FALSE;

}

LONGLONG DriverGetFilePosition(HANDLE hFile)
{
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	FILE_POSITION_INFORMATION fpi;

	status = ZwQueryInformationFile(hFile,
		&ioStatusBlock,
		&fpi,
		sizeof(FILE_POSITION_INFORMATION),
		FilePositionInformation);
	if (NT_SUCCESS(status))
		return fpi.CurrentByteOffset.QuadPart;
	else
		return -1;
}
BOOLEAN DriverSetFilePositon(HANDLE hFile, LONGLONG position,SHORT relative)
{
	NTSTATUS status = STATUS_SUCCESS;
	IO_STATUS_BLOCK ioStatusBlock;
	FILE_POSITION_INFORMATION fpi;

	status = ZwQueryInformationFile(hFile,
		&ioStatusBlock,
		&fpi,
		sizeof(FILE_POSITION_INFORMATION),
		FilePositionInformation);
	if (!NT_SUCCESS(status))
		return FALSE;
	if (relative < 0)
		fpi.CurrentByteOffset.QuadPart =  0+position;
	else if (relative == 0)
		fpi.CurrentByteOffset.QuadPart = fpi.CurrentByteOffset.QuadPart + position;
	else if (relative>0)
		fpi.CurrentByteOffset.QuadPart = DriverFileSize(hFile)- position;
	
	status = ZwSetInformationFile(hFile,
		&ioStatusBlock,
		&fpi,
		sizeof(FILE_POSITION_INFORMATION),
		FilePositionInformation);
	if (NT_SUCCESS(status))
		return TRUE;
	else
		return FALSE;
}
PVOID DriverAllocMemory(LONGLONG size)
{
	return ExAllocatePool(PagedPool, size);
}

VOID DriverFillMemory(PVOID buffer, LONGLONG size, CHAR fillCHAR)
{
	RtlFillMemory(buffer, size, fillCHAR);
}

VOID DriverFreeMemory(PVOID buffer)
{
	ExFreePool(buffer);
}