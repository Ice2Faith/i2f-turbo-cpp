
// ���׼�����.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "���׼�����.h"
#include "���׼�����Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���׼�����App

BEGIN_MESSAGE_MAP(C���׼�����App, CWinApp)
END_MESSAGE_MAP()


// C���׼�����App ����

C���׼�����App::C���׼�����App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� C���׼�����App ����

C���׼�����App theApp;


// C���׼�����App ��ʼ��

BOOL C���׼�����App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	C���׼�����Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
	}


	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

//��������תʮ���ƣ�����double���ͣ��������������ַ���txt,�ͽ��Ʊ�ʶoth
double C���׼�����Dlg::Oth2OTC(CString & txt, int oth)
{
	double result = 0;
	int visit = 0, size = 0;
	size = (int)txt.GetAt(visit++);
	while (size != '.'&&size != '\0')
	{
		result *= oth;
		if (size >= '0'&&size <= '9')
			result += (size - '0');
		else if (size >= 'A'&&size <= 'Z')
			result += (size - 'A' + 10);
		else if (size >= 'a'&&size <= 'z')
			result += (size - 'a' + 10);
		size = (int)txt.GetAt(visit++);
	}
	if (size == '\0')
		return result;
	size = (int)txt.GetAt(visit++);
	int i = 1;
	while (size >= '0'&&size <= '9')
	{

		if (size >= '0'&&size <= '9')
			result += (size - '0')*pow(1.0 / oth, (double)i++);
		else if (size >= 'A'&&size <= 'Z')
			result += (size - 'A' + 10)*pow(1.0 / oth, (double)i++);
		else if (size >= 'a'&&size <= 'z')
			result += (size - 'a' + 10)*pow(1.0 / oth, (double)i++);
		size = (int)txt.GetAt(visit++);
	}
	return result;
}

//ʮ����ת��������
void C���׼�����Dlg::OTC2Other(double num, int oth, CString & result)
{
	CString Change[MAXSIZE] = { L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"A", L"B", L"C", L"D", L"E", L"F", \
		L"G", L"H", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z" };
	int otc = (int)num;
	double flo = num - otc;
	BOOLEAN HDouble = TRUE;
	if (flo == 0)
		HDouble = FALSE;
	int FloNum[MAXSIZE];
	StackList * p;
	p = DefultStack();
	while (otc != 0)
	{
		Push(p, otc%oth);
		otc = (int)otc / oth;
	}
	int i = 0;
	while (flo != 0.0&&i<100)
	{
		FloNum[i] = (int)(flo*oth);
		flo = flo*oth - FloNum[i];
		i++;
	}
	FloNum[i] = 0;
	FloNum[++i] = -9999;
	i = 0;
	while (!IsEmpty(p))
	{
		Pop(p, &otc);
		result += Change[otc];
		i++;
	}
	if (HDouble)
	{
		result += ".";
		i = 0;
		while (FloNum[i + 1] != -9999)
		{
			result += Change[FloNum[i]];
			i++;
		}
	}
	free(p);
}

StackList * C���׼�����Dlg::DefultStack()
{
	StackList * p = (StackList *)malloc(sizeof(StackList));
	p->top = -1;
	return p;
}
int C���׼�����Dlg::IsEmpty(StackList * S)
{
	return S->top == -1;
}
int C���׼�����Dlg::IsFull(StackList * S)
{
	return S->top == MAXSIZE - 1;
}
int C���׼�����Dlg::Push(StackList * S, elemtype x)
{
	if (IsFull(S))
		return 0;
	S->data[++S->top] = x;
	return 1;
}
int C���׼�����Dlg::Pop(StackList * S, elemtype * x)
{
	if (IsEmpty(S))
		return 0;
	*x = S->data[S->top--];
	return 1;
}
double C���׼�����Dlg::SumTimeSec(int iyear, int imon, int iday, int ihour, int imin, int isec)
{
	double sumtime = 0;
	sumtime += isec;
	sumtime += imin * 60;
	sumtime += ihour*60*60;
	sumtime += iday* 24*60*60;
	int sumday = 0;
	switch (imon-1)
	{
	case 12: sumday += 31;
	case 11: sumday += 30;
	case 10: sumday += 31;
	case 9:sumday += 30;
	case 8:sumday += 31;
	case 7:sumday += 31;
	case 6:sumday += 30;
	case 5:sumday += 31;
	case 4:sumday += 30;
	case 3:sumday += 31;
	case 2:sumday += 28;
	case 1:sumday += 31;
	default: sumday += 0;
	}
	if (IsRunYear(iyear))
		sumday += 1;
	sumtime += sumday* 24*60*60;
	return sumtime;
}
int C���׼�����Dlg::IsRunYear(int year)
{
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return 1;
	else return 0;
}

