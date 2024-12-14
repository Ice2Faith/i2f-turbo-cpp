#include<ntddk.h>
/*
��������Ҳ��һ���ģ����в�ͬ����ڣ�DriverEntry

��������ṹ�嶨�壺
	typedef struct _DRIVER_OBJECT
{
	CSHORT Type;
	CSHORT Size;
	
	PDEVICE_OBJECT DeviceObject;//���������򴴽����豸
	ULONG Flag;//�����������ṩ�Ŀ���չ��עλ��
	
	
	//�����������������λ�ã�Count�ֶ�����ͳ�Ƶ�����ע������³�ʼ������
	
	PVOID DriverStart;
	ULONG DriverSize;
	PVOID DriverSection;
	PDERVEREXTENSION DriverExtension;
	
	//������־�߳�ʹ���������������ֶΣ�ȷ�ϰ�IO�����������������
	UNICODE_STRING DriveName;
	
	//ע��֧�֣�ָ��ע�����Ӳ����Ϣ·����ָ��
	PUNICODE_STRING HardwareDatabase;
	
	
	//����һ������ָ�룬ָ�����IO֧�ֵ������������һ����ڵ����飬����IO����������
	//��ֱ�ӵ��ã���ʹ�ñ�׼��IRP���û��ƣ���Щ����ֻ������ͬ��IO�ͻ����ļ������
	
	PFAST_IO_DISPATCH FastIODispatch;
	
	
	//�ض������������һ����ڵ㣬���������ñ�����Ƕ����е����һ���ֶΣ�
	//�Ա�����Ȼ����
	
	PDRIVE_INITIALIZE DriverInit;
	PDRIVER_STARTIO DriverStartIO;
	PDRIVER_UNLOAD DriverUnload;//����ָ��ж������ʱ���õĺ���������ԭ������
	PDRIVER_DISPATCH MajorFunction[IRP_MJ_MAXIMUM_FUNCTION+1];
	
}DRIVER_OBJECT,* PDRIVER_OBJECT;

ж����������ԭ�ͣ�
	VOID Unload(struct _DRIVER_OBJECT * DriveObject);
	�������е���������Ҫж�أ�����дRootkits����Ҫ��פ�ڴ����ϣ����ж��

Unicode�ַ����ṹ�壺
typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;//�ֱ𱣴��������������Ƶĳ��Ⱥ���󳤶�
	PWSTR Buffer;//�������������������
}UNICODE_STRING,* PUNICODE_STRING;
*/

VOID DriverUnload( PDRIVER_OBJECT pDriverObj )
{
	//�÷�����c���Ե�printf����
	KdPrint(("DriverUnload Routine!!\r\n"));
	
}

NTSTATUS DriverEntry(
			PDRIVER_OBJECT pDriverObj,//�ɲ���ϵͳ�������������ṹ��
			PUNICODE_STRING pRegistryPath)//һ��ָ�����������ע����Ӽ������Ӽ�������������������Ϣ��
{
	//ָ��ж������ʱ�����Ļص�����
	pDriverObj->DriverUnload=DriverUnload;
	
	KdPrint(("Load :%s\r\n",pDriverObj->DriverName.Buffer));
	
	//���������ɹ�״̬
	return STATUS_SUCCESS;
}