#ifndef _WIN32APP_H_
#define _WIN32APP_H_
#include<Windows.h>
/*
Win32������ڣ�Main��������
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nCmdShow)
����˵������ǰʵ�������֮ǰ��ʵ��������Ѿ��������ã��������в�����������ʾģʽ
ʹ������˵����
#include"Win32App.h"
int WAWin32Main()
{
	//����ע�ᴰ���࣬����ϵͳ������һ�������࣬���лص��������
	if (0 == WARegisterWindowClass(hInstance, className))
		return FALSE;
	//�������ڣ���ʾ���ڣ����´���
	if (WACreateWindowAndShow(hInstance, nCmdShow, className, wndName) == FALSE)
		return FALSE;
	//������Ϣѭ����ֱ�������رմ�����Ϣ�˳�ѭ������������
	return WAMessageLoop();
}
����Ҫ��ע����ʲô��
	�����Լ�����Ϣȥ��д�ص�������WAWindowProc
	�����Լ��Ļ�ͼȥ��д������WADrawApplication
������һЩ���⣺
	������Ϣѭ��֮�󣬲��ϻ�ȡ�Լ����ڵ���Ϣ��������Ϣ���ַ���Ϣ����Ϣ��ַ���ȥ�����Ե���Ӧ������̴���
	����ַ����̣�ʵ�����Ƿַ�������ϵͳ���ò���ϵͳȥ���ù��̻ص�������Ҳ����ע�ᴰ����ʱָ���Ļص�����
	Ҳ����˵�������з�����һ�У�������Ϊ��Ϣ�����仯���仯�ģ���˳�Ϊ��Ϣ��������

	�����ʱ�򣬽�������������Ϣ�����У������Ϣ������̺������ص�����WAWindowProc���ǳ���Ҫ��
	������������Ϣ�Ĵ��ھ����һ�����Լ��Ĵ��ڣ�����Ϣ���ͣ�WM_��ͷ������Ϣ����1����Ϣ����2��������Ϣ�����������κ����͵�ָ���ֵ��

	��Win32����MFC�У�������H��ͷ����ʾ�����һ����Դ�ı�ʶ���������Ϊһ��ָ�룩��
	��LP��ͷ����ʾ����һ��ָ�룬ȥ��LP֮����Ƕ�Ӧ�����ͣ��ṹ����ֵ����
	����STR��ʾ����һ���ַ���������LPSTR
	�������һ����ĸ���߶��������LPCSTR C�ͱ�ʶconst,��˱�ʶһ���ַ�������ָ��
	LPTSTR T��ʶһ���Զ���Ӧ�ֽڵ�TCHAR�������ǰ��UNICODE����ô����WCHAR���ͣ��������char��ͬ��TEXT()Ҳ���Զ���Ӧ��
*/
#define WAWin32Main() WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nCmdShow)
LRESULT CALLBACK WAWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
ATOM WARegisterWindowClass(HINSTANCE hInstance, LPTSTR className);
BOOL WACreateWindowAndShow(HINSTANCE hInstance, int nCmdShow, LPTSTR className, LPTSTR wndName);
BOOL WADirectCreateWindow(HINSTANCE hInstance, LPTSTR wndName, LPTSTR className, int nCmdShow);
WPARAM WAMessageLoop();
void WADrawApplication(HWND hWnd,HDC hdc);
#endif //_WIN32APP_H_