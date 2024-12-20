#ifndef _HIPSGUARD_H_
#define _HIPSGUARD_H_
#include<Windows.h>
//DLL 和主控程序的共同头文件
//请求的操作类型枚举
#define HIPS_CLASS_CREATE_PROCESSW		0x00000001L
#define HIPS_CLASS_CREATE_PROCESSA		0x00000002L
#define HIPS_CLASS_REG_SET_VALUE_EXW	0x00000003L
#define HIPS_CLASS_REG_SET_VALUE_EXA	0x00000004L
#define HIPS_CLASS_REG_DELETE_VALUEW	0x00000005L
#define HIPS_CLASS_REG_DELETE_VALUEA	0x00000006L
#define HIPS_CLASS_CREATE_SERVICEA		0x00000007L
#define HIPS_CLASS_CREATE_SERVICEW		0x00000008L
#define HIPS_CLASS_WIN_EXEC				0x00000009L
#define HIPS_CLASS_SHELL_EXECUTEA		0x0000000AL
#define HIPS_CLASS_SHELL_EXECUTEW		0x0000000BL
#define HIPS_CLASS_ADJUST_TOKEN_PRIVILEGES	0x0000000CL
#define HIPS_CLASS_REG_CREATE_KEYEXA	0x0000000DL
#define HIPS_CLASS_REG_CREATE_KEYEXW	0x0000000EL
#define HIPS_CLASS_CREATE_FILEA			0x0000000FL
#define HIPS_CLASS_CREATE_FILEW			0x00000010L
#define HIPS_CLASS_DELET_FILEA			0x00000011L
#define HIPS_CLASS_DELET_FILEW			0x00000012L
#define HIPS_CLASS_MOVE_FILEEXA			0x00000013L
#define HIPS_CLASS_MOVE_FILEEXW			0x00000014L
#define HIPS_CLASS_COPY_FILEEXA			0x00000015L
#define HIPS_CLASS_COPY_FILEEXW			0x00000016L

//授权结果的枚举
#define HIPS_AUTH_AGREEN 0
#define HIPS_AUTH_REDUCE -1
//请求信息发送给主控程序的封包
#define HIPS_INFO_MAXLENTH 2048
typedef struct _HIPS_INFO
{
	DWORD dwHipsClass;//请求类型
	BOOL bisAsciiInfo;//是否是ASCII描述字符串
	WCHAR wszHipsInfo[HIPS_INFO_MAXLENTH];//存放描述字符串的内存，存放的编码类型根据bisAsciiInfo而定，需要进行强转
}HIPS_INFO, *PHIPS_INFO;
#endif //_HIPSGUARD_H_