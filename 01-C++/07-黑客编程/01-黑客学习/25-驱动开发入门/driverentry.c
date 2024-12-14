#include<ntddk.h>
/*
驱动开发也是一样的，它有不同的入口：DriverEntry

驱动对象结构体定义：
	typedef struct _DRIVER_OBJECT
{
	CSHORT Type;
	CSHORT Size;
	
	PDEVICE_OBJECT DeviceObject;//连驱动程序创建的设备
	ULONG Flag;//给驱动程序提供的可扩展标注位置
	
	
	//用于描述驱动程序的位置，Count字段用于统计调用其注册的重新初始化次数
	
	PVOID DriverStart;
	ULONG DriverSize;
	PVOID DriverSection;
	PDERVEREXTENSION DriverExtension;
	
	//错误日志线程使用驱动程序名称字段，确认绑定IO请求的驱动程序名称
	UNICODE_STRING DriveName;
	
	//注册支持，指向注册表中硬件信息路径的指针
	PUNICODE_STRING HardwareDatabase;
	
	
	//包含一个可造指针，指向快速IO支持的驱动程序的另一个入口点数组，快速IO由驱动程序
	//例直接调用，不使用标准的IRP调用机制，这些函数只能用于同步IO和缓存文件的情况
	
	PFAST_IO_DISPATCH FastIODispatch;
	
	
	//特定驱动程序的另一个入口点，主函数调用表必须是对象中的最后一个字段，
	//以遍它任然可扩
	
	PDRIVE_INITIALIZE DriverInit;
	PDRIVER_STARTIO DriverStartIO;
	PDRIVER_UNLOAD DriverUnload;//用来指定卸载驱动时调用的函数，函数原型如下
	PDRIVER_DISPATCH MajorFunction[IRP_MJ_MAXIMUM_FUNCTION+1];
	
}DRIVER_OBJECT,* PDRIVER_OBJECT;

卸载驱动函数原型：
	VOID Unload(struct _DRIVER_OBJECT * DriveObject);
	几乎所有的驱动都需要卸载，除了写Rootkits，需要常驻内存而不希望被卸载

Unicode字符串结构体：
typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;//分别保存了驱动程序名称的长度和最大长度
	PWSTR Buffer;//保存了驱动程序的名称
}UNICODE_STRING,* PUNICODE_STRING;
*/

VOID DriverUnload( PDRIVER_OBJECT pDriverObj )
{
	//用法类似c语言的printf函数
	KdPrint(("DriverUnload Routine!!\r\n"));
	
}

NTSTATUS DriverEntry(
			PDRIVER_OBJECT pDriverObj,//由操作系统传入的驱动对象结构体
			PUNICODE_STRING pRegistryPath)//一个指向负责此驱动的注册表子键，该子键保存了驱动的配置信息等
{
	//指定卸载驱动时触发的回调函数
	pDriverObj->DriverUnload=DriverUnload;
	
	KdPrint(("Load :%s\r\n",pDriverObj->DriverName.Buffer));
	
	//返回驱动成功状态
	return STATUS_SUCCESS;
}