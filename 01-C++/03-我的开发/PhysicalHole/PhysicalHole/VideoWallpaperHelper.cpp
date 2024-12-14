#include"VideoWallpaperHelper.h"
BOOL CALLBACK __EnumWindowProcFindDesktopWindow(HWND hTop, LPARAM lparam)
{
	HWND * hWorkerW = (HWND *)lparam;
	// ���� SHELLDLL_DefView ������
	// ���ڶ��WorkerW���壬ֻ�е��´���SHELLDLL_DefView�Ĳ���
	HWND hTemp = ::FindWindowEx(
		hTop, NULL, TEXT("SHELLDLL_DefView"), NULL);
	if (hTemp == NULL) {
		return TRUE;
	}

	// XP ֱ�Ӳ���SysListView32����
	// g_hWorker = ::FindWindowEx(hWndShl, NULL, _T("SysListView32"),_T("FolderView"));

	// win7����߰汾
	// ���� WorkerW ���ھ��(�����洰��Ϊ������)
	*hWorkerW = ::FindWindowEx(NULL, hTop, TEXT("WorkerW"), NULL);
	return (*hWorkerW) == NULL;
}
HWND GetDesktopWallpaperWorkerHwnd(){
	// ����������
	HWND hProgman = NULL;
	HWND hWorkerW = NULL;
	// �����������ж��㴰��ȥ�������汳�����ھ��
	if (hProgman == NULL) {
		// ���ҵ�Progman ����
		hProgman = ::FindWindowEx(NULL, NULL, TEXT("Progman"), NULL);
		if (hProgman == NULL) {
			//�Ҳ���Progman����
			return NULL;
		}
		// ������Ϣ 0x052C ��Program Manager���ڣ�����һ������Ҫ��Ŀ�괰��
		// win10 1903 ��δ�ܳɹ����޷����룩
		DWORD_PTR lpdwResult = 0;
		SendMessageTimeout(hProgman, 0x052C, NULL, NULL, SMTO_NORMAL, 1000, &lpdwResult);

		// ���ҵ� WorkerW ���ڣ�������ʾ
		EnumWindows(__EnumWindowProcFindDesktopWindow, (LPARAM)&hWorkerW);
		//::ShowWindowAsync(hWorkerW, 0);
	}
	if (hProgman == NULL) {
		//�Ҳ��������ֽ�㴰��
		return NULL;
	}
	return hWorkerW;
}
