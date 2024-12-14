#ifndef _PLUGOUT_U_DISK_HPP_
#define _PLUGOUT_U_DISK_HPP_
#include <windows.h>
#include <Setupapi.h>
#include <winioctl.h>
#include <cfgmgr32.h>
#include <regstr.h>  
#include <initguid.h>  
#include<stdio.h>
#include<tchar.h>

void directChoicePlugoutDialog(){
	ShellExecute(NULL, 
		TEXT("open"), 
		TEXT("RUNDLL32.EXE"), 
		TEXT("shell32.dll,Control_RunDLL hotplug.dll"), 
		NULL, 
		SW_SHOW);
}

bool plugoutTargetUDisk(char disk)
{
	TCHAR phisycalPath[1024] = { 0 };
	_stprintf(phisycalPath, TEXT("\\\\.\\%c:"), disk);
	//�����������������·��������·�����������߼�����·����\\.\H:
	HANDLE hDevice = CreateFile(phisycalPath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hDevice == INVALID_HANDLE_VALUE){
		MessageBox(NULL, TEXT("can't open driver."), TEXT("driver manager"), MB_OK);
		return false;
	}

	//ж������������
	DWORD dwReturnBytes;
	BOOL bResult = DeviceIoControl(hDevice,
		FSCTL_DISMOUNT_VOLUME,
		NULL, 0, NULL, 0,
		&dwReturnBytes,
		(LPOVERLAPPED)NULL);
	if (bResult == FALSE){
		MessageBox(NULL, TEXT("disamount driver failure."), TEXT("driver manager"), MB_OK);
		bResult = CloseHandle(hDevice);
		return false;
	}

	//����������������������������ʹ��
	for (int i = 0; i < 10; i++){
		bResult = DeviceIoControl(hDevice,
			FSCTL_LOCK_VOLUME,
			NULL, 0, NULL, 0,
			&dwReturnBytes,
			(LPOVERLAPPED)NULL);
		if (bResult){
			break;
		}
		Sleep(30);
	}
	if (bResult == FALSE){
		MessageBox(NULL, TEXT("lock driver failure."), TEXT("driver manager"), MB_OK);
		bResult = CloseHandle(hDevice);
		return false;
	}

	//ж������ý��
	PREVENT_MEDIA_REMOVAL PMRBuffer;
	PMRBuffer.PreventMediaRemoval = FALSE;
	bResult = DeviceIoControl(hDevice,
		IOCTL_STORAGE_MEDIA_REMOVAL,
		&PMRBuffer, sizeof(PREVENT_MEDIA_REMOVAL),
		NULL, 0,
		&dwReturnBytes,
		(LPOVERLAPPED)NULL);
	if (bResult == FALSE){
		MessageBox(NULL, TEXT("remove driver failure."), TEXT("driver manager"), MB_OK);
		bResult = CloseHandle(hDevice);
		return false;
	}

	//�Ƴ������豸�����̱�Ϊ�����ò��ɷ���״̬
	bResult = DeviceIoControl(hDevice,
		IOCTL_STORAGE_EJECT_MEDIA,
		NULL, 0, NULL, 0,
		&dwReturnBytes,
		(LPOVERLAPPED)NULL);
	if (bResult == FALSE){
		MessageBox(NULL, TEXT("plugout driver failure."), TEXT("driver manager"), MB_OK);
		bResult = CloseHandle(hDevice);
		return false;
	}

	//�ر�֮ǰ���豸���
	bResult = CloseHandle(hDevice);
	if (bResult == FALSE){
		MessageBox(NULL, TEXT("close driver handle failure."), TEXT("driver manager"), MB_OK);
		return false;
	}

	return true;
}

#endif // _PLUGOUT_U_DISK_HPP_