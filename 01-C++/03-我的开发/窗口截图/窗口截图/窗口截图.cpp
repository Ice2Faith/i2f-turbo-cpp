#include<Windows.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // ������ڵ�ַ
int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName)
{
	//����λͼ�ļ�ÿ��������ռ�ֽ���   
	HDC   hDC = CreateDC("DISPLAY", NULL, NULL, NULL);//�豸������
	int iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
	DeleteDC(hDC);

	WORD     wBitCount=24;//λͼ��ÿ��������ռ�ֽ���  
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

	DWORD   dwPaletteSize = 0;//�����ɫ���С
	//�����ɫ���С   
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) *sizeof(RGBQUAD);


	//����λͼ��Ϣͷ�ṹ   
	BITMAP         Bitmap = {0};//λͼ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);

	BITMAPINFOHEADER   bi = {0};       //λͼ�ļ�ͷ�ṹ
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;// ָ��λͼ�Ƿ�ѹ������Ч��ֵΪBI_RGB��BI_RLE8��BI_RLE4��BI_BITFIELDS(����һЩWindows����õĳ���)��Ҫ˵�����ǣ�Windowsλͼ���Բ���RLE4����RLE8��ѹ����ʽ�����õĲ��ࡣ���ǽ�������۵�ֻ�е�һ�ֲ�ѹ�����������biCompressionΪBI_RGB�����
	bi.biSizeImage = 0;//ָ��ʵ�ʵ�λͼ����ռ�õ��ֽ�������ʵҲ���Դ����µĹ�ʽ�м�������� biSizeImage=biWidth�� �� biHeight Ҫע����ǣ�������ʽ�е�biWidth��������4��������(���Բ���biWidth������biWidth������ʾ���ڻ����biWidth�ģ���ӽ�4����������
	bi.biXPelsPerMeter = 0;//ָ��Ŀ���豸��ˮƽ�ֱ��ʣ���λ��ÿ�׵����ظ���
	bi.biYPelsPerMeter = 0; //ָ��Ŀ���豸�Ĵ�ֱ�ֱ���
	bi.biClrUsed = 0;//ָ����ͼ��ʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2biBitCount
	bi.biClrImportant = 0;//ָ����ͼ������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�

	
	DWORD dwBmBitsSize = ((Bitmap.bmWidth *wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;//λͼ�������ֽڴ�С

	//Ϊλͼ���ݷ����ڴ�   
	HANDLE hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));//�����ڴ���
	 LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);//λͼ��Ϣͷ�ṹ     ָ��λͼ��Ϣͷ�ṹ
	if (lpbi == NULL)
	{
		return 0;
	}
	*lpbi = bi;

	// �����ɫ��
	HANDLE hPal = GetStockObject(DEFAULT_PALETTE);//�����ڴ���
	HANDLE hOldPal = NULL;//��ɫ����  
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	// ��ȡ�õ�ɫ�����µ�����ֵ   
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
	//�ָ���ɫ��      
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	//����λͼ�ļ�   
	HANDLE fh = CreateFile(lpFileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//�����ļ����
	//����ļ��Ƿ񴴽��ɹ�
	if (fh == INVALID_HANDLE_VALUE)
		return 0;
	// ����λͼ�ļ�ͷ   
	BITMAPFILEHEADER   bmfHdr = {0};   //λͼ���Խṹ   
	bmfHdr.bfType = 0x4D42;  // "BM"   
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;// λͼ�ļ���С
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize ;
	// д��λͼ�ļ�ͷ   
	DWORD dwWritten=0;//д���ļ��ֽ���
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// д��λͼ�ļ���������   
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//���      
	CloseHandle(fh);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	return 1;
}

HBITMAP  GetCaptureBmp(RECT rect)
{
	BITMAPINFO   bi = {0};
	bi.bmiHeader.biSize = sizeof(BITMAPINFO); //ָ������ṹ�ĳ���
	bi.bmiHeader.biWidth = rect.right-rect.left;
	bi.bmiHeader.biHeight = rect.bottom-rect.top; //ָ��ͼ��ĸ߶ȣ���λ�����ء�
	bi.bmiHeader.biPlanes = 1;//������1�����ÿ��ǡ�
	bi.bmiHeader.biBitCount = 24; //ָ����ʾ��ɫʱҪ�õ���λ�������õ�ֵΪ1(�ڰ׶�ɫͼ), 4(16ɫͼ), 8(256ɫ), 24(���ɫͼ)(�µ�.bmp��ʽ֧��32λɫ)��

	HDC     hDC = GetDC(NULL);//��ȡ����DC�ķ���:GetDc(NULL)  ���� GetWindowDC(NULL) ���� GetWindowDC(GetDesktopWindow());
	HDC     MemDC = CreateCompatibleDC(hDC);//����һ����ָ���豸���ݵ��ڴ��豸�����Ļ�����DC����
	BYTE*   Data = NULL;
	HBITMAP   hBmp = CreateDIBSection(MemDC, &bi, DIB_RGB_COLORS, (void**)&Data, NULL, 0);//���������豸�޹�λͼ��� - HBITMAP,���һ������ȡ���������ڶ�������NULL

	SelectObject(MemDC, hBmp);//ѡ��һ����ָ�����豸�����Ļ����У����¶����滻��ǰ��ͬ�����͵Ķ���
	BitBlt(MemDC, rect.left, rect.top, bi.bmiHeader.biWidth, bi.bmiHeader.biHeight, hDC, 0, 0, SRCCOPY);//��ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת�����Դ��͵�Ŀ���豸������

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