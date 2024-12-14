#ifndef _FOOTEXTMSG_H_
#define _FOOTEXTMSG_H_
#include<Windows.h>
#define WM_TFM_ADDTEXT		(WM_USER+0x101)
#define WM_TFM_OPEN			(WM_USER+0x102)
#define WM_TFM_CLOSE		(WM_USER+0x103)
#define WM_TFM_CLEAR		(WM_USER+0x104)
#define WM_TFM_SHOW			(WM_USER+0x105)
#define WM_TFM_HIDE			(WM_USER+0x106)
#define MAXLENGTH 1024
typedef struct
{
	TCHAR text[MAXLENGTH];
	int size;
	COLORREF color;
	int speed;
}MsgBody;
#endif // _FOOTEXTMSG_H_