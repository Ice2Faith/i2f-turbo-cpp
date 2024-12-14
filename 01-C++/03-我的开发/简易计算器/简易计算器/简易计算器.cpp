
// 简易计算器.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "简易计算器.h"
#include "简易计算器Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C简易计算器App

BEGIN_MESSAGE_MAP(C简易计算器App, CWinApp)
END_MESSAGE_MAP()


// C简易计算器App 构造

C简易计算器App::C简易计算器App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 C简易计算器App 对象

C简易计算器App theApp;


// C简易计算器App 初始化

BOOL C简易计算器App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	C简易计算器Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
	}


	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//其他进制转十进制，返回double类型，传入其他进制字符串txt,和进制标识oth
double C简易计算器Dlg::Oth2OTC(CString & txt, int oth)
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

//十进制转其他进制
void C简易计算器Dlg::OTC2Other(double num, int oth, CString & result)
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

StackList * C简易计算器Dlg::DefultStack()
{
	StackList * p = (StackList *)malloc(sizeof(StackList));
	p->top = -1;
	return p;
}
int C简易计算器Dlg::IsEmpty(StackList * S)
{
	return S->top == -1;
}
int C简易计算器Dlg::IsFull(StackList * S)
{
	return S->top == MAXSIZE - 1;
}
int C简易计算器Dlg::Push(StackList * S, elemtype x)
{
	if (IsFull(S))
		return 0;
	S->data[++S->top] = x;
	return 1;
}
int C简易计算器Dlg::Pop(StackList * S, elemtype * x)
{
	if (IsEmpty(S))
		return 0;
	*x = S->data[S->top--];
	return 1;
}
double C简易计算器Dlg::SumTimeSec(int iyear, int imon, int iday, int ihour, int imin, int isec)
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
int C简易计算器Dlg::IsRunYear(int year)
{
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return 1;
	else return 0;
}

