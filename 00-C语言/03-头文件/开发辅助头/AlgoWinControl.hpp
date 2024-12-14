#ifndef _ALGO_WIN_CONTROL_HPP_
#define _ALGO_WIN_CONTROL_HPP_
#include<Windows.h>
#include<stdio.h>

#include<mmsystem.h>
#include<mmreg.h>

class AlgoWinControl
{
public:
	
	static void KeyDown(BYTE vkCode)
	{
		keybd_event(vkCode, 0, 0, 0);
	}
	static void KeyUp(BYTE vkCode)
	{
		keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
	}
	static void KeyClick(BYTE vkCode)
	{
		keybd_event(vkCode, 0, 0, 0);
		keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);
	}
	static void KeyClickVkInput(BYTE * ckCodes, int length, int sleepMs=30)
	{
		for (int i = 0; i < length; i++)
		{
			KeyClick(ckCodes[i]);
			Sleep(sleepMs);
		}
	}
	static void KeyClickCharInput(char * str, int sleepMs=30)
	{
		static char chs[] = { " \n\t;:+,<-.>/?`~[{\\|]}'\"()*&^%$#@!" };
		static BYTE cds[][2] = { 
			{VK_SPACE},
			{VK_RETURN},
			{ VK_TAB },
			{VK_OEM_1},
			{VK_SHIFT,VK_OEM_1},
			{ VK_OEM_PLUS },
			{ VK_OEM_COMMA },
			{ VK_SHIFT,VK_OEM_COMMA },
			{ VK_OEM_MINUS },
			{ VK_OEM_PERIOD },
			{ VK_SHIFT,VK_OEM_PERIOD },
			{ VK_OEM_2 },
			{ VK_SHIFT,VK_OEM_2 },
			{ VK_OEM_3 },
			{ VK_SHIFT,VK_OEM_3 },
			{VK_OEM_4},
			{ VK_SHIFT, VK_OEM_4 },
			{ VK_OEM_5 },
			{ VK_SHIFT, VK_OEM_5 },
			{ VK_OEM_6 },
			{ VK_SHIFT, VK_OEM_6 },
			{ VK_OEM_7 },
			{ VK_SHIFT, VK_OEM_7 },
			{ VK_SHIFT, '9' },
			{ VK_SHIFT, '0' },
			{ VK_SHIFT, '8' },
			{ VK_SHIFT, '7' },
			{ VK_SHIFT, '6' },
			{ VK_SHIFT, '5' },
			{ VK_SHIFT, '4' },
			{ VK_SHIFT, '3' },
			{ VK_SHIFT, '2' },
			{ VK_SHIFT, '1' },

		};
		for (int i = 0; str[i]!=0; i++)
		{
			BYTE code=str[i];
			if (code >= 'a' && code <= 'z')
			{
				code &= ~32;
				KeyClick(code);
			}
			else if (code >= '0' && code <= '9' || code>='A' && code<='Z')
			{
				KeyClick(code);
			}
			else
			{
				bool isfind = false;
				for (int j = 0; chs[j] != 0; j++)
				{
					if (code == chs[j])
					{
						if (cds[j][1] != 0)
							KeyClickComposite(cds[j], 2);
						else
							KeyClick(cds[j][0]);
						isfind = true;
						break;
					}
				}
				if (isfind == false)
					continue;
			}
			Sleep(sleepMs);
		}
	}
	static void KeyClickRepeat(BYTE vkCode, int count = 2, int sleepMs = 30)
	{
		for (int i = 0; i < count; i++)
		{
			KeyClick(vkCode);
			Sleep(sleepMs);
		}
	}
	static void KeyClickComposite(BYTE * vkCode, int count)
	{
		for (int i = 0; i < count; i++)
		{
			KeyDown(vkCode[i]);
		}
		for (int i = count - 1; i >= 0; i--)
		{
			KeyUp(vkCode[i]);
		}
	}
	static void KeyClick_CtrlC()
	{
		BYTE keys[] = { VK_CONTROL, 'C' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_CtrlV()
	{
		BYTE keys[] = { VK_CONTROL, 'V' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_WinR()
	{
		BYTE keys[] = { VK_LWIN, 'R' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_CtrlX()
	{
		BYTE keys[] = { VK_CONTROL, 'X' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_CtrlA()
	{
		BYTE keys[] = { VK_CONTROL, 'A' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_CtrlS()
	{
		BYTE keys[] = { VK_CONTROL, 'S' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_CtrlZ()
	{
		BYTE keys[] = { VK_CONTROL, 'Z' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_WinL()
	{
		BYTE keys[] = { VK_LWIN, 'L' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_WinS()
	{
		BYTE keys[] = { VK_LWIN, 'S' };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_AltTab()
	{
		BYTE keys[] = { VK_MENU, VK_TAB };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_AltF4()
	{
		BYTE keys[] = { VK_MENU, VK_F4 };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_AltEnter()
	{
		BYTE keys[] = { VK_MENU, VK_RETURN };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_ShiftDelete()
	{
		BYTE keys[] = { VK_SHIFT, VK_DELETE };
		KeyClickComposite(keys, 2);
	}
	static void KeyClick_CtrlShiftEsc()
	{
		BYTE keys[] = { VK_CONTROL, VK_SHIFT,VK_ESCAPE };
		KeyClickComposite(keys, 3);
	}
	static void KeyClick_CtrlAltDelete()
	{
		BYTE keys[] = { VK_CONTROL, VK_MENU,VK_DELETE };
		KeyClickComposite(keys, 3);
	}

	static void KeyVolumeMute()
	{
		KeyClick(VK_VOLUME_MUTE);
	}
	static void KeyVolumeUp()
	{
		KeyClick(VK_VOLUME_UP);
	}
	static void KeyVolumeDown()
	{
		KeyClick(VK_VOLUME_DOWN);
	}
	static void KeyVolumeToZero()
	{
		for (int i = 0; i < 100; i++)
		{
			KeyVolumeDown();
		}
	}
	static void KeyVolumeToMax()
	{
		for (int i = 0; i < 100; i++)
		{
			KeyVolumeUp();
		}
	}
	static void KeyVolumeToValue(int vol)
	{
		KeyVolumeToZero();
		for (int i = 0; i < vol / 2; i++)//key once add 2% volume value on my pc
		{
			KeyVolumeUp();
		}
	}
	static void KeyMediaNext()
	{
		KeyClick(VK_MEDIA_NEXT_TRACK);
	}
	static void KeyMediaPrevious()
	{
		KeyClick(VK_MEDIA_PREV_TRACK);
	}
	static void KeyMediaPlayPause()
	{
		KeyClick(VK_MEDIA_PLAY_PAUSE);
	}
	static void KeyMediaStop()
	{
		KeyClick(VK_MEDIA_STOP);
	}
	
	static void LButtonDown()
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	}
	static void LButtonUp()
	{
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	static void LButtonClick()
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	static void LButtonClickRepeat(int count = 2, int sleepMs = 30)
	{
		for (int i = 0; i < count; i++)
		{
			LButtonClick();
			Sleep(sleepMs);
		}
	}
	static void RButtonDown()
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	}
	static void RButtonUp()
	{
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	static void RButtonClick()
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	static void RButtonClickRepeat(int count = 2, int sleepMs = 30)
	{
		for (int i = 0; i < count; i++)
		{
			RButtonClick();
			Sleep(sleepMs);
		}
	}
	static void MidButtonDown()
	{
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
	}
	static void MidButtonUp()
	{
		mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
	}
	static void MidButtonClick()
	{
		mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
	}
	static void MidButtonClickRepeat(int count = 2, int sleepMs = 30)
	{
		for (int i = 0; i < count; i++)
		{
			MidButtonClick();
			Sleep(sleepMs);
		}
	}
	static void XButtonDown()
	{
		mouse_event(MOUSEEVENTF_XDOWN, 0, 0, 0, 0);
	}
	static void XButtonUp()
	{
		mouse_event(MOUSEEVENTF_XUP, 0, 0, 0, 0);
	}
	static void XButtonClick()
	{
		mouse_event(MOUSEEVENTF_XDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_XUP, 0, 0, 0, 0);
	}
	static void XButtonClickRepeat(int count = 2, int sleepMs = 30)
	{
		for (int i = 0; i < count; i++)
		{
			XButtonClick();
			Sleep(sleepMs);
		}
	}
	static void MouseWheelUp()
	{
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 120, 0);
	}
	static void MouseWheelDown()
	{
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -120, 0);
	}
	static void MouseSetPos(int x, int y)
	{
		SetCursorPos(x, y);
	}
	static void MouseMoveAbs(int x, int y)
	{

		HDC hdeskDc = GetDC(NULL);
		int sxDpi = ::GetDeviceCaps(hdeskDc, LOGPIXELSX);
		double rate = sxDpi*1.0 / 96;

		int sx = GetSystemMetrics(SM_CXFULLSCREEN)*rate;
		int sy = GetSystemMetrics(SM_CYFULLSCREEN)*rate;
		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x * 65535 / sx, y * 65535 / sy, 0, 0);
	}
	static void MouseMoveRel(int dx, int dy)
	{
		mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
	}
	static void MouseDropAbs(int sx, int sy, int ex, int ey)
	{
		MouseMoveAbs(sx, sy);
		LButtonDown();
		MouseMoveAbs(ex, ey);
		LButtonUp();
	}
	static void MouseDropAbs(int ex, int ey)
	{
		LButtonDown();
		MouseMoveAbs(ex, ey);
		LButtonUp();
	}
	static void MouseDropRel(int dx, int dy)
	{
		LButtonDown();
		MouseMoveRel(dx, dy);
		LButtonUp();
	}
	static void MouseLRSwap(bool swap = true)
	{
		if (swap)
			SwapMouseButton(TRUE);
		else
			SwapMouseButton(FALSE);
	}
	static void getMousePosAbs(int * x, int * y)
	{
		POINT p;
		GetCursorPos(&p);
		*x = p.x;
		*y = p.y;
	}
	static void getMousePosClient(HWND clientWnd, int * x, int * y)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(clientWnd, &p);
		*x = p.x;
		*y = p.y;
	}

	static bool IsAsynKeyDown(BYTE vkCode)
	{
		return 0 != (GetAsyncKeyState(vkCode) & 0x8000);
	}
	static bool IsAsynKeysDown(BYTE * vkCodes, int count)
	{
		for (int i = 0; i < count; i++)
		{
			if (GetAsyncKeyState(vkCodes[i]) & 0x8000 == 0)
				return false;
		}
		return true;
	}
	static bool IsAsynLButtonDown()
	{
		return 0 != (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
	}
	static bool IsAsynRButtonDown()
	{
		return 0 != (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
	}
	static bool IsAsynMidButtonDown()
	{
		return 0 != (GetAsyncKeyState(VK_MBUTTON) & 0x8000);
	}

	static void CdAudioDoorOpen()
	{
		mciSendString(TEXT("set cdaudio door open"), NULL, NULL, NULL);
	}
	static void CdAudioDoorClose()
	{
		mciSendString(TEXT("set cdaudio door closed"), NULL, NULL, NULL);
	}

	static void PowerOffDelaySecond(int sec)
	{
		char cmd[50] = { 0 };
		sprintf(cmd, "shutdown -s -f -t %d\0", sec);
		WinExec(cmd, SW_HIDE);
	}
	static void PowerRebootDelaySecond(int sec)
	{
		char cmd[50] = { 0 };
		sprintf(cmd, "shutdown -r -f -t %d\0", sec);
		WinExec(cmd, SW_HIDE);
	}
	static void PowerTaskCancel()
	{
		WinExec("shutdown -a", SW_HIDE);
	}

	static void LockScreen()
	{
		WinExec("rundll32 user32.dll,LockWorkStation", SW_HIDE);
	}

	static void NetPhoneLink(char * netName, char * netAccout, char * netPass)
	{
		char cmd[256] = { 0 };
		sprintf(cmd, "start rasdial %s %s %s", netName, netAccout, netPass);
		WinExec(cmd, SW_HIDE);
	}
	static void NetWirelessDisconnect()
	{
		WinExec("netsh wlan disconnect", SW_HIDE);
	}
	/*
	网卡名称，可以在这里查看：
	控制面板\网络和 Internet\网络连接
	*/
	static void NetDisableNetCard(char * cardName = "本地连接")
	{
		char cmd[256] = { 0 };
		sprintf(cmd, "netsh interface set interface \"%s\" disabled\0", cardName);
		WinExec(cmd, SW_HIDE);
	}
	static void NetEnableNetCard(char * cardName = "本地连接")
	{
		char cmd[256] = { 0 };
		sprintf(cmd, "netsh interface set interface \"%s\" enabled\0", cardName);
		WinExec(cmd, SW_HIDE);
	}
	static void NetEnableWirelessCard()
	{
		char * netName = "WLAN";
		AlgoWinControl::NetEnableNetCard(netName);
	}
	static void NetDisableWirelessCard()
	{
		char * netName = "WLAN";
		AlgoWinControl::NetDisableNetCard(netName);
	}

	static void ScreenOff()
	{
		SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, 2);
	}
	static void ScreenOn()
	{
		SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, -1);
	}
	static void ScreenLowPower()
	{
		SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, 1);
	}

};

#endif // _ALGO_WIN_CONTROL_HPP_