#include"ConsoleControl.h"
namespace ConCI2F
{
int ConsoleControl::IsKeyDown(int key)
{
	return ((GetAsyncKeyState(key) & 0x8000) ? 1 : 0);
}
void ConsoleControl::ClickKeybd(int key)
{
	keybd_event(key, 0, 0, 0);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}
void ConsoleControl::SetWindowMinMax(int mode)
{
	HWND consle = GetForegroundWindow();
	if (mode==0)
	ShowWindow(consle, SW_MINIMIZE);
	else if (mode==1)
	ShowWindow(consle, SW_MAXIMIZE);
}
void ConsoleControl::GetClientCursorPos(int * x, int * y)
{
	POINT point;
	HWND hwnd = FindWindow(L"ConsoleWindowClass", NULL); // 获取绘图窗口句柄
	GetCursorPos(&point);   // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hwnd, &point); // 将鼠标指针位置转换为窗口坐标
	*x = point.y/14;
	*y = point.x/8;
}
char ConsoleControl::Getchif(void)
{
    if(_kbhit())
        return _getch();
    return '\0';
}
void ConsoleControl::ScreenTips(int mode,int time,int BeforeTextColor,int BeforeBackGroundColor)
{
    if(mode==0||mode<-1||mode>1)
        sprintf_s(mind,"color e1\0");
    else if(mode==1)
		sprintf_s(mind, "color 1f\0");
    else if(mode==-1)
		sprintf_s(mind, "color c0\0");
    system(mind);
    if(time<=0)
        time=30;
    Sleep(time);
    SetConsoleColor(BeforeTextColor,BeforeBackGroundColor);
}
char ConsoleControl::Getchf(void)
{
    char ch;
    ch=_getch();
    printf("%c\n",ch);
    return ch;
}
void ConsoleControl::GetHelp()
{
    char help[800]= {"SetColor:\n\
0 = 黑色       8 = 灰色\n\
1 = 蓝色       9 = 淡蓝色\n\
2 = 绿色       10 = 淡绿色\n\
3 = 浅绿色     11 = 淡浅绿色\n\
4 = 红色       12 = 淡红色\n\
5 = 紫色       13 = 淡紫色\n\
6 = 黄色       14 = 淡黄色\n\
7 = 白色       15 = 亮白色\n\
SetGotoxy:\n\
Set display space to lines,cols\n\
SetConsoleSize:\n\
if lines or cols >0 will set,or not set.\n\
SleepPrint:\n\
will one by one print char\n\
ConsoleCls:\n\
will clean console screen\n\
SetWindowMinMax:\n\
mode=0 Min,mode=1 Max\n\
ClickKeybd:\n\
模仿用户点击按键\n\
IsKeyDown:\n\
检测是否点击了这个按键\n\
\0"
                    };
	printf("%s", help);
}
void ConsoleControl::SleepPrint(int time,const char * text)
{
    if(time<=0)
        printf("%s",text);
    else
        while(*text)
        {
            printf("%c",*text);
            Sleep(time);
            text++;
        }
}
void ConsoleControl::SetConsoleSize(int lines,int cols)
{
    if(lines>0 && cols>0)
		sprintf_s(mind, "mode con lines=%d cols=%d\0", lines, cols);
    else if(lines <=0 && cols>0)
		sprintf_s(mind, "mode con cols=%d\0", cols);
    else if(lines >0 && cols<=0)
		sprintf_s(mind, "mode con lines=%d\0", lines);
    else if(lines<=0 && cols<=0)
        return;
    system(mind);
}
void ConsoleControl::ConsoleCls(void)
{
    system("cls");
}
void ConsoleControl::SetConsoleTitle(char title[])
{
	sprintf_s(mind, "title %s\0", title);
    system(mind);
}
void ConsoleControl::SetConsoleColor(int TextColor,int BackGroundColor)
{
    if(TextColor<0 ||TextColor>15)
        TextColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    char Model[18]= {"0123456789ABCDEF\0"};
	sprintf_s(mind, "color %c%c\0", Model[BackGroundColor], Model[TextColor]);
    system(mind);
}

void ConsoleControl::SetTextColor(int ForeColor,int BackGroundColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
}
void ConsoleControl::SetGotoxy(int lines,int cols)
{
    COORD Go = {cols, lines};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Go);
}
void ConsoleControl::GetKeybdCodeHelp()
{
	char Keybd[400][50]{
		"虚拟键码\t\t对应值\t\t对应键",
			"-------------------------------",
			"VK_F1\t\t\t112\t\tF1",
			"VK_F2\t\t\t113\t\tF2",
			"VK_F3\t\t\t114\t\tF3",
			"VK_F4\t\t\t115\t\tF4",
			"VK_F5\t\t\t116\t\tF5",
			"VK_F6\t\t\t117\t\tF6",
			"VK_F7\t\t\t118\t\tF7",
			"VK_F8\t\t\t119\t\tF8",
			"VK_F9\t\t\t120\t\tF9",
			"VK_F10\t\t\t121\t\tF10",
			"VK_F11\t\t\t122\t\tF11",
			"VK_F12\t\t\t123\t\tF12",
			"0\t\t\t48",
			"1\t\t\t49",
			"2\t\t\t50",
			"3\t\t\t51",
			"4\t\t\t52",
			"5\t\t\t53",
			"6\t\t\t54",
			"7\t\t\t55",
			"8\t\t\t56",
			"9\t\t\t57",
			"A\t\t\t65",
			"B\t\t\t66",
			"C\t\t\t67",
			"D\t\t\t68",
			"E\t\t\t69",
			"F\t\t\t70",
			"G\t\t\t71",
			"H\t\t\t72",
			"I\t\t\t73",
			"J\t\t\t74",
			"K\t\t\t75",
			"L\t\t\t76",
			"M\t\t\t77",
			"N\t\t\t78",
			"O\t\t\t79",
			"P\t\t\t80",
			"Q\t\t\t81",
			"R\t\t\t82",
			"S\t\t\t83",
			"T\t\t\t84",
			"U\t\t\t85",
			"V\t\t\t86",
			"W\t\t\t87",
			"X\t\t\t88",
			"Y\t\t\t89",
			"Z\t\t\t90",
			"VK_ESCAPE\t\t27\t\tEsc",
			"VK_TAB\t\t\t9\t\tTab",
			"VK_CAPITAL\t\t20\t\tCaps Lock",
			"VK_SHIFT\t\t16\t\tShift",
			"VK_CONTROL\t\t17\t\tCtrl",
			"VK_MENU\t\t\t18\t\tAlt",
			"VK_LSHIFT\t\t160\t\t左shift",
			"VK_RSHIFT\t\t161\t\t右shift",
			"VK_LCONTROL\t\t162\t\t左control",
			"VK_RCONTROL\t\t163\t\t右control",
			"VK_LMENU\t\t164\t\t左Alt",
			"VK_RMENU\t\t165\t\t右Alt",
			"VK_LWIN\t\t\t91\t\t左WIN",
			"VK_RWIN\t\t\t92\t\t右WIN",
			"VK_SPACE\t\t32\t\tSpace",
			"VK_BACK\t\t\t8\t\tBackspace",
			"VK_RETURN\t\t13\t\tEnter",
			"VK_KANJI\t\t25\t\t*",
			"VK_OEM_3\t\t192\t\t` ~",
			"VK_OEM_PLUS\t\t187\t\t= +",
			"VK_OEM_MINUS\t\t189\t\t- _",
			"VK_OEM_4\t\t219\t\t[ {",
			"VK_OEM_6\t\t221\t\t] }",
			"VK_OEM_5\t\t220\t\t\\ |",
			"VK_OEM_1\t\t186\t\t; :",
			"VK_OEM_7\t\t222\t\t' \"",
			"VK_OEM_COMMA\t\t188\t\t, <",
			"VK_OEM_PERIOD\t\t190\t\t. >",
			"VK_OEM_2\t\t191\t\t/ ?",
			"VK_LBUTTON\t\t1\t\t鼠标左键",
			"VK_RBUTTON\t\t2\t\t鼠标右键",
			"VK_MBUTTON\t\t4\t\t鼠标中键",
			"VK_INSERT\t\t45\t\tInsert",
			"VK_DELETE\t\t46\t\tDelete",
			"VK_PRIOR\t\t33\t\tPage Up",
			"VK_NEXT\t\t\t34\t\tPage Down",
			"VK_END\t\t\t35\t\tEnd",
			"VK_HOME\t\t\t36\t\tHome",
			"VK_LEFT\t\t\t37\t\tLeft Arrow",
			"VK_UP\t\t\t38\t\tUp Arrow",
			"VK_RIGHT\t\t39\t\tRight Arrow",
			"VK_DOWN\t\t\t40\t\tDown Arrow",
			"VK_PRINT\t\t42\t\tPrint Sc Sys",
			"VK_SCROLL\t\t145\t\tScroll Lock",
			"VK_PAUSE\t\t19\t\tPause Break",
			"VK_NUMLOCK\t\t144\t\tNum Lock",
			"VK_NUMPAD0\t\t96\t\t小键盘 0",
			"VK_NUMPAD1\t\t97\t\t小键盘 1",
			"VK_NUMPAD2\t\t98\t\t小键盘 2",
			"VK_NUMPAD3\t\t99\t\t小键盘 3",
			"VK_NUMPAD4\t\t100\t\t小键盘 4",
			"VK_NUMPAD5\t\t101\t\t小键盘 5",
			"VK_NUMPAD6\t\t102\t\t小键盘 6",
			"VK_NUMPAD7\t\t103\t\t小键盘 7",
			"VK_NUMPAD8\t\t104\t\t小键盘 8",
			"VK_NUMPAD9\t\t105\t\t小键盘 9",
			"VK_MULTIPLY\t\t106\t\t小键盘 *",
			"VK_ADD\t\t\t107\t\t小键盘 +",
			"VK_SEPARATOR\t\t108\t\t小键盘 Enter",
			"VK_SUBTRACT\t\t109\t\t小键盘 -",
			"VK_DECIMAL\t\t110\t\t小键盘 .",
			"VK_DIVIDE\t\t111\t\t小键盘 /",
			"VK_SELECT\t\t41\t\tSelect",
			"VK_EXECUTE\t\t43\t\tExecute",
			"VK_SNAPSHOT\t\t44\t\tSnapshot",
			"VK_HELP\t\t\t47\t\tHelp",
			"VK_CANCEL\t\t3\t\tCancel",
			"VK_CLEAR\t\t12\t\tClear",
			"VK_VOLUME_MUTE\t\t173\t\tVolumeMute",
			"VK_VOLUME_DOWN\t\t174\t\tVolumeDown",
			"VK_VOLUME_UP\t\t175\t\tVolumeUp",
			"VK_BROWSER_BACK\t\t166\t\t浏览器back",
			"VK_BROWSER_FORWARD\t167\t\t浏览器forward",
			"VK_BROWSER_REFRESH\t168\t\t浏览器refresh",
			"VK_BROWSER_STOP\t\t169\t\t浏览器\t\t",
			"VK_BROWSER_SEARCH\t170\t\t浏览器search",
			"VK_BROWSER_FAVORITES\t171\t\t浏览器favorites",
			"VK_BROWSER_HOME\t\t172\t\t浏览器home",
			"VK_F13\t\t\t124",
			"VK_F14\t\t\t125",
			"VK_F15\t\t\t126",
			"VK_F16\t\t\t127",
			"VK_F17\t\t\t128",
			"VK_F18\t\t\t129",
			"VK_F19\t\t\t130",
			"VK_F20\t\t\t131",
			"VK_F21\t\t\t132",
			"VK_F22\t\t\t133",
			"VK_F23\t\t\t134",
			"VK_F24\t\t\t135",
			"VK_XBUTTON1\t\t5",
			"VK_XBUTTON2\t\t6",
			"VK_KANA\t\t\t21",
			"VK_HANGUL\t\t21",
			"VK_JUNJA\t\t23",
			"VK_FINAL\t\t24",
			"VK_HANJA\t\t25",
			"VK_CONVERT\t\t28",
			"VK_NONCONVERT\t\t29",
			"VK_ACCEPT\t\t30",
			"VK_MODECHANGE\t\t31",
			"VK_APPS\t\t\t93",
			"VK_SLEEP\t\t95",
			"VK_MEDIA_NEXT_TRACK\t176",
			"VK_MEDIA_PREV_TRACK\t177",
			"VK_MEDIA_STOP\t\t178",
			"VK_MEDIA_PLAY_PAUSE\t179",
			"VK_LAUNCH_MAIL\t\t180",
			"VK_LAUNCH_MEDIA_SELECT\t181",
			"VK_LAUNCH_APP1\t\t182",
			"VK_LAUNCH_APP2\t\t183",
			"VK_OEM_8\t\t223",
			"VK_OEM_102\t\t226",
			"VK_PACKET\t\t231",
			"VK_PROCESSKEY\t\t229",
			"VK_ATTN\t\t\t246",
			"VK_CRSEL\t\t247",
			"VK_EXSEL\t\t248",
			"VK_EREOF\t\t249",
			"VK_PLAY\t\t\t250",
			"VK_ZOOM\t\t\t251",
			"VK_NONAME\t\t252",
			"VK_PA1\t\t\t253",
			"VK_OEM_CLEAR\t\t254",
			"你可以使用虚拟键码或者键值作为参数传递",
			"-----------------------------------------------",
	};
	int i = 0;
	while (Keybd[i][0] != 0)
	{
		cout << Keybd[i++] << endl;
	}
	cout << "Click any key end view" << endl;
	_getch();
}
}