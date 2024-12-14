#include<ntddk.h>
#define REG_PATH (L"\\Registry\\Machine\\Software\\Microsoft\\Windows\\CurrentVersion\\run\\")
//注册表创建或者打开键
HANDLE DriverRegCreateKey(WCHAR * regPath);
//注册表打开键
HANDLE DriverRegOpenKey(WCHAR * regPath);
//关闭注册表键
BOOLEAN DriverRegClose(HANDLE hreg);
//在已经打开的键下添加（值名称-值数据）
BOOLEAN DriverRegSetValueKey(HANDLE hreg, WCHAR * valueName, WCHAR * value);
//查询值数据保存到结构体指针中
BOOLEAN DriverRegQueryValueKey(HANDLE hreg, WCHAR * valueName, PKEY_VALUE_PARTIAL_INFORMATION pKeyValueParticialClass);
//释放查询值数据的结构体数据
VOID DriverRegFreeQueryValueKeyData(PKEY_VALUE_PARTIAL_INFORMATION pKeyValueParticialClass);

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{

}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING szRegistryPath)
{
	HANDLE hreg;
	BOOLEAN ret;
	PKEY_VALUE_PARTIAL_INFORMATION pkeydata=NULL;

	pDriverObject->DriverUnload = DriverUnload;

	hreg=DriverRegCreateKey(REG_PATH);
	KdPrint(("Create key:%d\r\n",hreg));

	ret=DriverRegSetValueKey(hreg, L"test", L"test");
	KdPrint(("set value key:%d\r\n", ret));

	ret=DriverRegQueryValueKey(hreg, L"test", pkeydata);
	KdPrint(("query value=%s key:%d\r\n",pkeydata->Data, ret));

	ret=DriverRegClose(hreg);
	KdPrint(("close key:%d\r\n", ret));

	DriverRegFreeQueryValueKeyData(pkeydata);

	return STATUS_SUCCESS;
}
/*
内核层注册表操作使用与应用层不一样，不能使用应用层的函数API

注册表的创建（打开）函数：
	参数标注说明：
	__out：输出参数
	__in：输入参数
	__reserved：保留参数
	_opt：可选参数

	NTSTATUS ZwCreateKey(
		__out PHANDLE KeyHandle,//获得的注册表句柄
		__in ACCESS_MASK DesiredAccess,//访问权限，一般设置为KEY_ALL_ACCESS
		__in POBJECT_ATTRIBUTES ObjectAttributes,//指向保存要创建的子键的结构体
		__reserved ULONG TitleIndex,//保留参数。设置为0
		__in_opt PUNICODE_STRING Class,//一般设置为NULL
		__in ULONG CreateOptions,//创建时选项，一般设置为REG_OPTION_NON_VOLATILE
		__out_opt PULONG Disposition//返回创建成功还是打开成功
		);

注册表打开函数（和文件的创建与打开一样）：
	NTSTATUS ZwOpenKey(
		__out PHANDLE KeyHandle,//返回被打开的的句柄
		__in ACCESS_MASK DesiredAccess,//打开的权限，一般为KEY_ALL_ACCESS
		__in POBJECT_ATTRIBUTES ObjectAttributes//指向的结构体，和应用层的标识有不同，
		);//HKEY_LOCAL_MACHINE==\Registry\Machine，HKEY_USER==\Registry\User，但是HKEY_CLASSES_ROOT和HKEY_CURRENT_USER在内核中没有对应的标识

注册表设置键值：
	NTSTATUS ZwSetValueKey(
		__in HANDLE KeyHandle,//注册表句柄
		__in PUNICODE_STRING ValueName,//要新建或修改的键名
		__in_opt ULONG TitleIndex,//一般设置为0
		__in ULONG Type,//键值的类型，比如：REG_SZ、REG_DWORD、REG_MULTI_SZ等
		__in_bcount_opt(DataSize) PVOID Data,//写入的键值的值
		__in ULONG DataSize//写入的键值的大小
		);

注册表查询键值：
	NTSTATUS ZwQueryValueKey(
		__in HANDLE KeyHandle,//已经打开的注册表句柄
		__in PUNICODE_STRING ValueName,//要查询的键名
		__in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,//选择一种查询类别，可以是KeyValueBasicInformation、KeyValueFullInformation、KeyValueParticialInformation
		__out_bcount_opt(Length) PVOID KeyValueInformation,//根据KeyValueInformationClass的不同，传递响应的结构体
		__in ULONG Length,//要查询的数据长度
		__out PULONG ResultLength//实际查询数据的长度
		);
		第三个参数为 KeyValueParticialInformation 时对应的结构体：
		typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
		ULONG   TitleIndex;//保留不使用
		ULONG   Type;//数据的类型
		ULONG   DataLength;//数据的大小
		UCHAR   Data[1];            // 利用结构体最后一个位置，存放一个一字节大小的数组，使用数据越界的技巧，实际长度将会越界存放，这种方式很常见
		} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;
*/
HANDLE DriverRegCreateKey(WCHAR * regPath)
{
	UNICODE_STRING uniStr;
	OBJECT_ATTRIBUTES objAttri;
	NTSTATUS status = STATUS_SUCCESS;
	HANDLE hreg;
	ULONG ulResult;

	RtlInitUnicodeString(&uniStr, regPath);

	InitializeObjectAttributes(&objAttri,
		&uniStr,
		OBJ_CASE_INSENSITIVE,
		NULL, NULL);

	status = ZwCreateKey(&hreg,
		KEY_ALL_ACCESS,
		&objAttri,
		0, NULL,
		REG_OPTION_NON_VOLATILE,
		&ulResult);
	if (NT_SUCCESS(status))
		return hreg;
	else
		return NULL;
}
HANDLE DriverRegOpenKey(WCHAR * regPath)
{
	UNICODE_STRING uniRegPath;
	NTSTATUS status = STATUS_SUCCESS;
	OBJECT_ATTRIBUTES objAttri;
	HANDLE hreg;

	RtlInitUnicodeString(&uniRegPath, regPath);

	InitializeObjectAttributes(&objAttri,
		&uniRegPath,
		OBJ_CASE_INSENSITIVE,
		NULL, NULL);

	status = ZwOpenKey(&hreg,
		KEY_ALL_ACCESS,
		&objAttri);

	if (NT_SUCCESS(status))
		return hreg;
	else
		return NULL;

}
BOOLEAN DriverRegClose(HANDLE hreg)
{
	if (NT_SUCCESS(ZwClose(hreg)))
	{
		return TRUE;
	}
	else
		return FALSE;
}
BOOLEAN DriverRegSetValueKey(HANDLE hreg,WCHAR * valueName,WCHAR * value)
{
	UNICODE_STRING uniValueName;
	NTSTATUS status = STATUS_SUCCESS;

	RtlInitUnicodeString(&uniValueName, valueName);

	status = ZwSetValueKey(hreg,
		&uniValueName,
		0, REG_SZ,
		value,
		wcslen(value) * 2 + sizeof(WCHAR));
	if (NT_SUCCESS(status))
		return TRUE;
	else
		return FALSE;
}
BOOLEAN DriverRegQueryValueKey(HANDLE hreg, WCHAR * valueName,PKEY_VALUE_PARTIAL_INFORMATION pKeyValueParticialClass)
{
	UNICODE_STRING uniValueName;
	NTSTATUS status = STATUS_SUCCESS;
	ULONG ulResult;

	RtlInitUnicodeString(&uniValueName, valueName);

	status = ZwQueryValueKey(hreg,
		&uniValueName,
		KeyValuePartialInformation,
		NULL, NULL,
		&ulResult);

	if (status == STATUS_BUFFER_TOO_SMALL || ulResult != 0)
	{
		pKeyValueParticialClass = ExAllocatePool(PagedPool, ulResult);
		status = ZwQueryValueKey(hreg,
			&uniValueName,
			KeyValuePartialInformation,
			pKeyValueParticialClass,
			ulResult,
			&ulResult);
		if (NT_SUCCESS(status))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}
VOID DriverRegFreeQueryValueKeyData(PKEY_VALUE_PARTIAL_INFORMATION pKeyValueParticialClass)
{
	ExFreePool(pKeyValueParticialClass);
}
