#include<ntddk.h>
#define REG_PATH (L"\\Registry\\Machine\\Software\\Microsoft\\Windows\\CurrentVersion\\run\\")
//ע��������ߴ򿪼�
HANDLE DriverRegCreateKey(WCHAR * regPath);
//ע���򿪼�
HANDLE DriverRegOpenKey(WCHAR * regPath);
//�ر�ע����
BOOLEAN DriverRegClose(HANDLE hreg);
//���Ѿ��򿪵ļ�����ӣ�ֵ����-ֵ���ݣ�
BOOLEAN DriverRegSetValueKey(HANDLE hreg, WCHAR * valueName, WCHAR * value);
//��ѯֵ���ݱ��浽�ṹ��ָ����
BOOLEAN DriverRegQueryValueKey(HANDLE hreg, WCHAR * valueName, PKEY_VALUE_PARTIAL_INFORMATION pKeyValueParticialClass);
//�ͷŲ�ѯֵ���ݵĽṹ������
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
�ں˲�ע������ʹ����Ӧ�ò㲻һ��������ʹ��Ӧ�ò�ĺ���API

ע���Ĵ������򿪣�������
	������ע˵����
	__out���������
	__in���������
	__reserved����������
	_opt����ѡ����

	NTSTATUS ZwCreateKey(
		__out PHANDLE KeyHandle,//��õ�ע�����
		__in ACCESS_MASK DesiredAccess,//����Ȩ�ޣ�һ������ΪKEY_ALL_ACCESS
		__in POBJECT_ATTRIBUTES ObjectAttributes,//ָ�򱣴�Ҫ�������Ӽ��Ľṹ��
		__reserved ULONG TitleIndex,//��������������Ϊ0
		__in_opt PUNICODE_STRING Class,//һ������ΪNULL
		__in ULONG CreateOptions,//����ʱѡ�һ������ΪREG_OPTION_NON_VOLATILE
		__out_opt PULONG Disposition//���ش����ɹ����Ǵ򿪳ɹ�
		);

ע���򿪺��������ļ��Ĵ������һ������
	NTSTATUS ZwOpenKey(
		__out PHANDLE KeyHandle,//���ر��򿪵ĵľ��
		__in ACCESS_MASK DesiredAccess,//�򿪵�Ȩ�ޣ�һ��ΪKEY_ALL_ACCESS
		__in POBJECT_ATTRIBUTES ObjectAttributes//ָ��Ľṹ�壬��Ӧ�ò�ı�ʶ�в�ͬ��
		);//HKEY_LOCAL_MACHINE==\Registry\Machine��HKEY_USER==\Registry\User������HKEY_CLASSES_ROOT��HKEY_CURRENT_USER���ں���û�ж�Ӧ�ı�ʶ

ע������ü�ֵ��
	NTSTATUS ZwSetValueKey(
		__in HANDLE KeyHandle,//ע�����
		__in PUNICODE_STRING ValueName,//Ҫ�½����޸ĵļ���
		__in_opt ULONG TitleIndex,//һ������Ϊ0
		__in ULONG Type,//��ֵ�����ͣ����磺REG_SZ��REG_DWORD��REG_MULTI_SZ��
		__in_bcount_opt(DataSize) PVOID Data,//д��ļ�ֵ��ֵ
		__in ULONG DataSize//д��ļ�ֵ�Ĵ�С
		);

ע����ѯ��ֵ��
	NTSTATUS ZwQueryValueKey(
		__in HANDLE KeyHandle,//�Ѿ��򿪵�ע�����
		__in PUNICODE_STRING ValueName,//Ҫ��ѯ�ļ���
		__in KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,//ѡ��һ�ֲ�ѯ��𣬿�����KeyValueBasicInformation��KeyValueFullInformation��KeyValueParticialInformation
		__out_bcount_opt(Length) PVOID KeyValueInformation,//����KeyValueInformationClass�Ĳ�ͬ��������Ӧ�Ľṹ��
		__in ULONG Length,//Ҫ��ѯ�����ݳ���
		__out PULONG ResultLength//ʵ�ʲ�ѯ���ݵĳ���
		);
		����������Ϊ KeyValueParticialInformation ʱ��Ӧ�Ľṹ�壺
		typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
		ULONG   TitleIndex;//������ʹ��
		ULONG   Type;//���ݵ�����
		ULONG   DataLength;//���ݵĴ�С
		UCHAR   Data[1];            // ���ýṹ�����һ��λ�ã����һ��һ�ֽڴ�С�����飬ʹ������Խ��ļ��ɣ�ʵ�ʳ��Ƚ���Խ���ţ����ַ�ʽ�ܳ���
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
