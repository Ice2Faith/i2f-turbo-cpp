#include<ntddk.h>

#define TARGETFILENAME (L"\\??\\C:\\driver_file.txt")

//内核驱动下的文件操作，模仿C语言API实现
//创建文件
BOOLEAN DriverCreateFile(WCHAR * fileName);
//打开文件
HANDLE DriverOpenFile(WCHAR * fileName);
//关闭文件
BOOLEAN DriverCloseFile(HANDLE hFile);
//写入文件
BOOLEAN DriverWriteFile(HANDLE hFile, PVOID buffer, LONGLONG bufferSize);
//判断文件是否是文件夹
BOOLEAN DriverIsDirectory(HANDLE hFile);
//获取文件大小
LONGLONG DriverFileSize(HANDLE hFile);
//读取文件
BOOLEAN DriverReadFile(HANDLE hFile, PVOID data, LONGLONG maxReadSize);
//获取当前文件指针
LONGLONG DriverGetFilePosition(HANDLE hFile);
//重新设置文件指针，相对于relative位置的偏移量position,relative=0标识当前位置，relative<0标识文件头，relative>0标识文件尾
BOOLEAN DriverSetFilePositon(HANDLE hFile, LONGLONG position, SHORT relative);
//申请内存空间
PVOID DriverAllocMemory(LONGLONG size);
//用fillChar填充buffer开始大小为size的内存
VOID DriverFillMemory(PVOID buffer, LONGLONG size, CHAR fillCHAR);
//释放申请的内存
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
注意，由于按照C语言编译，因此所有的变量都必须在域开头，否则在C98的C编译器之前版本会有编译错误
	一般情况下，内核层不能调用用户层的API函数

函数简介：
文件创建（打开）函数：
NTSTATUS ZwCreateFile(
	PHANDLE FileHandle,//接受创建后的文件句柄
	ACCESS_MASK DesiredAccess,//打开文件操作的描述符，一般为读写GENERIC_READ|GENERIC_WRITE，和CreateFile一样
	POBJECT_ATTRIBUTES ObjectAttributes,//指向结构体，该结构体包含要创建或打开的文件名
	PIO_STATUS_BLOCK IoStatusBlock,//接受操作结果转态的结构体
	PLARGE_INTEGER AllocationSize,//指向64位整数，标识文件的初始化分配大小
	ULONG FileAttributes,//通常为FILE_ATTRIBUTE_NORMAL，和CreateFile一样
	ULONG ShareAccess,//指定文件的共享方式，可以为FILE_SHARE_READ、FILE_SHARE_WRITE、FILE_SHARE_DELETE，和CreateFile一样
	ULONG CreateDisposition,//用于描述本次调用本函数的意图，可以为FILE_CREATE、FILE_OPEN、FILE_OPEN_IF等
	ULONG CreateOptions,//通常为FILE_SYNCHRONOUS_IO_NONALERT，标识文件同步操作，即调用函数返回时，就已经写入磁盘
	PVOID EaBuffer,//指向可选扩展属性区，一般为NULL
	ULONG EaLength//指示拓展属性区的大小，一般为0
	);
	返回值：NTSTATUS类型，可以用NT_SUCCESS()宏检测是否成功

	结构体（一般不直接进行手动复制，使用函数）：
	typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
	} OBJECT_ATTRIBUTES;
	赋值初始化函数（实际上是一个宏）：
		InitializeObjectAttributes( 
			POBJECT_ATTRIBUTES initedObjAttri, //指向结构体的指针
			PUNICODE_STRING objectName,//对象名称，对于ZwCreateFile来说，这里就是文件名，注意这里是内核模式下的路径，有区别于应用层"C:\\a.txt"(或者"\\\\.\\"开头)，内核层为"\\??\\C:\\a.txt"(或者以"\\DosDevice\\"开头)
			ULONG attris,//一般为OBJ_CASE_INSENSITIVE，标识名字字符串不区分大小写
			HANDLE RootDirectory,//一般为NULL
			PSECURITY_DESCRIPTOR securityDescripor);//设置安全描述符，一般为NULL
	UNICEDE_STRING结构，之前已经介绍过。
	typedef struct _UNICODE_STRING {
		USHORT Length;
		USHORT MaximumLength;
		PWCH   Buffer;
		} UNICODE_STRING;
		对于UNICEDE_STRING类型，可以直接用KdPrint输出，格式为：KdPrint(("%wZ",&str));
		但是注意没使用之前需要进行初始化，一般使用函数进行初始化，当然也可以自行申请空间。
		初始化函数：
			VOID RtlInitUnicodeString(
			   PUNICODE_STRING DestinationString,//结构指针
			   PCWSTR SourceString//填入的字符串
				);

打开文件函数：
虽然ZwCreateFile也可以打开文件，但是参数太多，不方便
这个就是精简版的函数，参数不在进行介绍
	NTSTATUS ZwOpenFile(
		PHANDLE FileHandle,
		ACCESS_MASK DesiredAccess,
		POBJECT_ATTRIBUTES ObjectAttributes,
		PIO_STATUS_BLOCK IoStatusBlock,
		ULONG ShareAccess,
		ULONG OpenOptions
		);

关闭文件函数：
	NTSTATUS ZwClose(
		 HANDLE Handle//要关闭的文件句柄
		);

文件信息查询函数（大小，是否文件夹等）：
	NTSTATUS ZwQueryInformationFile(
		HANDLE FileHandle,//被打开的文件句柄
		PIO_STATUS_BLOCK IoStatusBlock,//返回设置的状态
		PVOID FileInformation,//根据FileInfomationClass不同而不同
		ULONG Length,//FileInfomation数据的长度
		FILE_INFORMATION_CLASS FileInformationClass//描述需要获取的类型数据
		);
文件信息设置函数（文件指针，修改时间等）：
	NTSTATUS ZwSetInformationFile(//参数与查询函数基本类似，只是注意输入输出关系不同
		HANDLE FileHandle,
		PIO_STATUS_BLOCK IoStatusBlock,
		PVOID FileInformation,
		ULONG Length,
		FILE_INFORMATION_CLASS FileInformationClass
		);
这两函数的第三个参数（FileInformation）是根据第五个参数（FileInformationClass）来传递决定的，
第五个参数常用的值有：
	FileStandardInfomation
	FileBasicInfomation
	FilePositionInfomation
	这个参数，也就对应了第三个参数要传递什么样的结构体
	它们对应的结构体如下：
	typedef struct _FILE_BASIC_INFORMATION {
	LARGE_INTEGER CreationTime;//文件创建时间
	LARGE_INTEGER LastAccessTime;//最后访问时间
	LARGE_INTEGER LastWriteTime;//最后写入时间
	LARGE_INTEGER ChangeTime;//修改时间
	ULONG FileAttributes;//文件属性
	} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

	typedef struct _FILE_STANDARD_INFORMATION {
	LARGE_INTEGER AllocationSize;//为文件分配的大小（占用簇所需大小）
	LARGE_INTEGER EndOfFile;//距离文件结尾的字节数
	ULONG NumberOfLinks;//拥有的链接文件技术
	BOOLEAN DeletePending;//是否准备删除
	BOOLEAN Directory;//是否为目录
	} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

	typedef struct _FILE_POSITION_INFORMATION {
	LARGE_INTEGER CurrentByteOffset;//当前文件指针位置
	} FILE_POSITION_INFORMATION, *PFILE_POSITION_INFORMATION;

	这些结构体中的成员结构体：
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
	该结构体主要用来标识64位的整数，一般使用QuadPart成员

文件读取函数：
	NTSTATUS ZwReadFile(
		HANDLE FileHandle,//已经打开的文件句柄
		 HANDLE Event,//用于异步完成读取时使用，一般为NULL
		 PIO_APC_ROUTINE ApcRoutine,//回调例程，用于异步读取时，一般为NULL
		PVOID ApcContext,//一般为NULL
		PIO_STATUS_BLOCK IoStatusBlock,//记录读取操作状态的结构指针，其成员Information用于记录读取的字节数
		PVOID Buffer,//保存内容的缓冲区
		ULONG Length,//准备读取的内容大小
		 PLARGE_INTEGER ByteOffset,//指定读取内容的偏移地址
		PULONG Key//读取文件时的福建信息，一般为NULL
		);

写入文件函数：
	NTSTATUS ZwWriteFile(//函数参数和读取类似，注意方向，不在介绍
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

内存申请函数：
	PVOID ExAllocatePool(
		POOL_TYPE PoolType,//枚举值，常用NonPagedPool、PagedPool，分别标识非分页内存和分页内存，区别是能被交换到文件的内存成为分页内存
		SIZE_T NumberOfBytes//需要分配的内存大小
		);
	返回值：这是申请的内存的地址

内存填充函数(这是一个宏)：
	参数：目标内存地址，内存填充大小，填充字符
	#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))

内存回收函数(这也是一个宏)：
	参数：需要释放的内存地址
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