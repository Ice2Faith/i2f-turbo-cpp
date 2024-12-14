#include<Windows.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName)
{
	//计算位图文件每个像素所占字节数   
	HDC   hDC = CreateDC("DISPLAY", NULL, NULL, NULL);//设备描述表
	int iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);//当前显示分辨率下每个像素所占字节数
	DeleteDC(hDC);

	WORD     wBitCount=24;//位图中每个像素所占字节数  
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else if (iBits <= 32)
		wBitCount = 24;
	else 
		wBitCount = 32;

	DWORD   dwPaletteSize = 0;//定义调色板大小
	//计算调色板大小   
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) *sizeof(RGBQUAD);


	//设置位图信息头结构   
	BITMAP         Bitmap = {0};//位图结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);

	BITMAPINFOHEADER   bi = {0};       //位图文件头结构
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;// 指定位图是否压缩，有效的值为BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS(都是一些Windows定义好的常量)。要说明的是，Windows位图可以采用RLE4，和RLE8的压缩格式，但用的不多。我们今后所讨论的只有第一种不压缩的情况，即biCompression为BI_RGB的情况
	bi.biSizeImage = 0;//指定实际的位图数据占用的字节数，其实也可以从以下的公式中计算出来： biSizeImage=biWidth’ × biHeight 要注意的是：上述公式中的biWidth’必须是4的整倍数(所以不是biWidth，而是biWidth’，表示大于或等于biWidth的，最接近4的整倍数。
	bi.biXPelsPerMeter = 0;//指定目标设备的水平分辨率，单位是每米的象素个数
	bi.biYPelsPerMeter = 0; //指定目标设备的垂直分辨率
	bi.biClrUsed = 0;//指定本图象实际用到的颜色数，如果该值为零，则用到的颜色数为2biBitCount
	bi.biClrImportant = 0;//指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的。

	
	DWORD dwBmBitsSize = ((Bitmap.bmWidth *wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;//位图中像素字节大小

	//为位图内容分配内存   
	HANDLE hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));//分配内存句柄
	 LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);//位图信息头结构     指向位图信息头结构
	if (lpbi == NULL)
	{
		return 0;
	}
	*lpbi = bi;

	// 处理调色板
	HANDLE hPal = GetStockObject(DEFAULT_PALETTE);//分配内存句柄
	HANDLE hOldPal = NULL;//调色板句柄  
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	// 获取该调色板下新的像素值   
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
	//恢复调色板      
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	//创建位图文件   
	HANDLE fh = CreateFile(lpFileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//定义文件句柄
	//检查文件是否创建成功
	if (fh == INVALID_HANDLE_VALUE)
		return 0;
	// 设置位图文件头   
	BITMAPFILEHEADER   bmfHdr = {0};   //位图属性结构   
	bmfHdr.bfType = 0x4D42;  // "BM"   
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;// 位图文件大小
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize ;
	// 写入位图文件头   
	DWORD dwWritten=0;//写入文件字节数
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// 写入位图文件其余内容   
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//清除      
	CloseHandle(fh);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	return 1;
}

HBITMAP  GetCaptureBmp(RECT rect)
{
	BITMAPINFO   bi = {0};
	bi.bmiHeader.biSize = sizeof(BITMAPINFO); //指定这个结构的长度
	bi.bmiHeader.biWidth = rect.right-rect.left;
	bi.bmiHeader.biHeight = rect.bottom-rect.top; //指定图象的高度，单位是像素。
	bi.bmiHeader.biPlanes = 1;//必须是1，不用考虑。
	bi.bmiHeader.biBitCount = 24; //指定表示颜色时要用到的位数，常用的值为1(黑白二色图), 4(16色图), 8(256色), 24(真彩色图)(新的.bmp格式支持32位色)。

	HDC     hDC = GetDC(NULL);//获取桌面DC的方法:GetDc(NULL)  或者 GetWindowDC(NULL) 或者 GetWindowDC(GetDesktopWindow());
	HDC     MemDC = CreateCompatibleDC(hDC);//创建一个与指定设备兼容的内存设备上下文环境（DC）。
	BYTE*   Data = NULL;
	HBITMAP   hBmp = CreateDIBSection(MemDC, &bi, DIB_RGB_COLORS, (void**)&Data, NULL, 0);//创建的是设备无关位图句柄 - HBITMAP,最后一个参数取消，倒数第二个参数NULL

	SelectObject(MemDC, hBmp);//选择一对象到指定的设备上下文环境中，该新对象替换先前的同样类型的对象。
	BitBlt(MemDC, rect.left, rect.top, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight, hDC, 0, 0, SRCCOPY);//对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境。

	ReleaseDC(NULL, hDC);
	DeleteDC(MemDC);
	return   hBmp;
}

int main(int argc, char * argv[])
{
	RECT rect = {0};
	rect.left = 0;
	rect.top = 0;
	rect.right = GetSystemMetrics(SM_CXSCREEN)*5/4;
	rect.bottom = GetSystemMetrics(SM_CYSCREEN)*5/4;
	HBITMAP   hBmp = GetCaptureBmp(rect);
	if (1 == SaveBitmapToFile(hBmp, "C:\\Capture.bmp"))
	{
		system("explorer C:\\");
		system("explorer C:\\Capture.bmp");
	}
	else
	{
		SaveBitmapToFile(hBmp, "D:\\Capture.bmp");
		system("explorer D:\\");
		system("explorer D:\\Capture.bmp");
	}
	return 0;
}