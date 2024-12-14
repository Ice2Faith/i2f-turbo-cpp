
// 简易计算器Dlg.h : 头文件
//

#pragma once
#define MAXSIZE 1000
typedef int elemtype;
typedef struct
{
	elemtype data[MAXSIZE];
	int top;
} StackList;


// C简易计算器Dlg 对话框
class C简易计算器Dlg : public CDialog
{
// 构造
public:
	C简易计算器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void OnOK();

// 实现
protected:
	HICON m_hIcon;
	CString cnum1, cnum2, cresult, onlycal = L"1", tempstring;
	double num1, num2, result, tempnum;
	int exc = 0;
	const double PI = 3.14159265358979323846;
	const double MATHE = 2.718281828459;
	const double MATHGOLD = 0.6180339887498948;
	const double MATHKHINCHINK = 2.685452001065306;
	const double MATHCONWAY = 1.3035772690342963913;
	const double MATHLIGHTC = 299792458;
	int ControlBase = 0;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void UpdataResultToEditBox();
	void UpdataResultToEditBoxSingle();
	StackList * DefultStack();
	int IsEmpty(StackList * S);
	int IsFull(StackList * S);
	int Push(StackList * S, elemtype x);
	int Pop(StackList * S, elemtype * x);
	void OTC2Other(double num, int oth, CString & result);
	double Oth2OTC(CString & txt, int oth);


	void SetMoney();
	void SetBoom();
	void CoreUpdataMore(int nID);

	double SumTimeSec(int iyear, int imon, int iday, int ihour, int imin, int isec);
	int IsRunYear(int year);
	afx_msg void OnBnClickedButtonRem();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonMi();
	afx_msg void OnBnClickedButtonMls();
	afx_msg void OnBnClickedButtonPow();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonLog();
	afx_msg void OnBnClickedButtonPi();
	afx_msg void OnBnClickedButtonE();
	afx_msg void OnBnClickedButtonNumone();
	afx_msg void OnBnClickedButtonNumtwe();
	afx_msg void OnBnClickedButtonSin();
	afx_msg void OnBnClickedButtonExc();
	afx_msg void OnBnClickedButtonCos();
	afx_msg void OnBnClickedButtonTan();
	afx_msg void OnEnChangeEditSingelin();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonArcsin();
	afx_msg void OnBnClickedButtonArccos();
	afx_msg void OnBnClickedButtonArctan();
	afx_msg void OnBnClickedButtonPresent();
	afx_msg void OnBnClickedButtonMiadd();
	afx_msg void OnBnClickedButtonRandbewteen();
	afx_msg void OnBnClickedButtonMimul();
	afx_msg void OnBnClickedButtonVert();
	afx_msg void OnBnClickedButtonUptime();
	afx_msg void OnStnClickedStaticDef();
	afx_msg void OnBnClickedButtonSurvive();
	afx_msg void OnEnChangeEditInyear();
	afx_msg void OnEnChangeEditOutyear();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonEqunext();
	afx_msg void OnBnClickedButtonGoldmath();
	afx_msg void OnBnClickedButtonMathfg();
	afx_msg void OnBnClickedButtonMathafojadeluo();
	afx_msg void OnBnClickedButtonMathlight();
	afx_msg void OnBnClickedButtonMathkhinchink();
	afx_msg void OnBnClickedButtonMathconway();
	afx_msg void OnBnClickedButtonHexexchange();
	afx_msg void OnBnClickedButtonFilling();
	afx_msg void OnBnClickedButtonLockcommputer();
	afx_msg void OnBnClickedButtonShutdownnow();
	afx_msg void OnBnClickedButtonRebootnow();
	afx_msg void OnBnClickedButtonOpencmd();
	afx_msg void OnBnClickedButtonOpenpoewrshell();
	afx_msg void OnBnClickedButtonSwitchcontrol();
	afx_msg void OnBnClickedButtonShutdownlater();
	afx_msg void OnBnClickedButtonRebootlater();
	afx_msg void OnBnClickedButtonCancelplan();
	afx_msg void OnBnClickedButtonAddfile();
	afx_msg void OnLbnSelchangeListDisplay();
	afx_msg void OnBnClickedButtonStartlock();
	afx_msg void OnEnChangeMfceditbrowseGetfilepath();
	afx_msg void OnBnClickedButtonGstart();
	afx_msg void OnBnClickedButtonG1();
	afx_msg void OnBnClickedButtonG2();
	afx_msg void OnBnClickedButtonG3();
	afx_msg void OnBnClickedButtonG4();
	afx_msg void OnBnClickedButtonG5();
	afx_msg void OnBnClickedButtonG6();
	afx_msg void OnBnClickedButtonG7();
	afx_msg void OnBnClickedButtonG8();
	afx_msg void OnBnClickedButtonG9();
	afx_msg void OnBnClickedButtonGover();
	afx_msg void OnBnClickedButtonYaosaizi();
	afx_msg void OnBnClickedButtonRegedit();
	afx_msg void OnBnClickedButtonOpenhost();
	afx_msg void OnBnClickedButtonTobase();
	afx_msg void OnBnClickedButtonTostring();
	afx_msg void OnBnClickedButtonEqu();
	afx_msg void OnBnClickedButtonExpcalcul();
};
