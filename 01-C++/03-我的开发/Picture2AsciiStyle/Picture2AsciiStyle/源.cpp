
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
void showCommandHelp();
void picture2AsciiStyle(char * srcFile, char * dstFile, int dstWidth, int dstHeight, int charSize, bool keepRgb);

int main(int argc, char * argv[]){
	char  srcFile[2048] = { 0 };
	char  dstFile[2048] = { 0 };
	int dstWidth = 480;
	int dstHeight = 0;
	int charSize = 3;
	bool keepRgb = true;
	if (argc < 2){
		showCommandHelp();
		system("pause");
		return 0;
	}
	if (argc >= 2){
		strcpy(srcFile, argv[1]);
		sprintf(dstFile, "%s.asc.png\0", srcFile);
	}
	if (argc >= 3){
		strcpy(dstFile, argv[2]);
	}
	if (argc >= 4){
		dstWidth=atoi(argv[3]);
	}
	if (argc >= 5){
		dstHeight = atoi(argv[4]);
	}
	if (argc >= 6){
		charSize = atoi(argv[5]);
	}
	if (argc >= 7){
		if (strcmp(argv[6], "true") == 0){
			keepRgb = true;
		}
		else if (strcmp(argv[6], "false") == 0){
			keepRgb = false;
		}
	}
	picture2AsciiStyle(srcFile, dstFile, dstWidth, dstHeight, charSize, keepRgb);
	// 5875ms 3922ms
	return 0;
}

void showCommandHelp(){
	printf("image 2 ascii style command:\n");
	printf("\tsrcImageFile [dstImageFile [dstWidth [dstHeight [asciiCharSize [keepRgb]]]]]\n");
	printf("\tdescription:\n");
	printf("\t\tsrcImageFile:[must] source image file.\n");
	printf("\t\tdstImageFile:[option] save image file.\n");
	printf("\t\tdstWidth:[option] save image character width count.\n");
	printf("\t\tdstHeight:[option] save image charactor height count.\n");
	printf("\t\tasciiCharSize:[option] ascii charactor size.\n");
	printf("\t\tkeepRgb:[option] save image which keep rgb color.\n");
	printf("\tdeclare:\n");
	printf("\t\twhen dstWidth/dstHeight exist one <=0,the other on value will be base of source image size keep rate scale.\n");
	printf("\t\tdefault asciiCharSize is 8.\n");
	printf("\t\tdefault keepRgb is true.\n");
	printf("\t\tdefault dstWidth is 480,default height is keep rate scale to adapt 480 width.\n");
	printf("\t\tdefault dstImage is srcImageFile+'.asc.png'.\n");
	printf("\tusage case:\n");
	printf("\t\tC:\\1.png\n");
	printf("\t\tC:\\1.png C:\\2.png\n");
	printf("\t\tC:\\1.png C:\\2.jpg 480\n");
	printf("\t\tC:\\1.png C:\\2.png 480 0\n");
	printf("\t\tC:\\1.png C:\\2.png 0 320\n");
	printf("\t\tC:\\1.png C:\\2.png 480 320\n");
	printf("\t\tC:\\1.png C:\\2.png 480 0 8\n");
	printf("\t\tC:\\1.png C:\\2.png 480 0 8 true\n");
}


void picture2AsciiStyle(char * srcFile, char * dstFile, int dstWidth, int dstHeight, int charSize, bool keepRgb)
{
	printf("image 2 ascii charator style process...\n");
	printf("\tfile:\n\t\t%s\n\t\t-> %s\n", srcFile, dstFile);
	char chArr[] = { ' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 'c', 't', '+',
		'{', 'i', '7', '?', 'u', '3', '0', 'p', 'w', '4', 'A', '8', 'D', 'X', '%', '#', 'H', 'W', 'M' };
	int mappingLen = sizeof(chArr) / sizeof(chArr[0]);
	IMAGE srcImg;
	loadimage(&srcImg, srcFile);
	printf("\tsrc image size:%d,%d\n", srcImg.getwidth(), srcImg.getheight());
	if (dstWidth <= 0 && dstHeight > 0){
		double rate = dstHeight*1.0 / srcImg.getheight();
		dstWidth = rate*srcImg.getwidth();
	}
	else if (dstHeight <= 0 && dstWidth > 0){
		double rate = dstWidth*1.0 / srcImg.getwidth();
		dstHeight = rate*srcImg.getheight();
	}
	else if(dstWidth<=0 && dstHeight<=0){
		dstWidth = srcImg.getwidth();
		dstHeight = srcImg.getheight();
	}
	if (charSize <= 0){
		charSize = 8;
	}
	printf("\tkeep RGB color mode:%s\n", (keepRgb ? "true" : "false"));
	printf("\tcharactor size:%d\n", charSize);
	printf("\tdst image character sie:%d,%d\n", dstWidth, dstHeight);
	loadimage(&srcImg, srcFile, dstWidth, dstHeight, true);
	int dstPixelWidth = dstWidth*charSize;
	int dstPixelHeight = dstHeight*charSize;
	printf("\tdst image pixel size:%d,%d\n", dstPixelWidth, dstPixelHeight);
	IMAGE dstImg(dstPixelWidth, dstPixelHeight);
	if (keepRgb){
		SetWorkingImage(&dstImg);
		setfillcolor(RGB(255, 255, 255));
		solidrectangle(-1, -1, dstImg.getwidth() + 1, dstImg.getheight() + 1);
	}
	printf("\tbegin process pixels...\n");
	HDC srcHdc = GetImageHDC(&srcImg);

	HDC dstHdc = GetImageHDC(&dstImg);
	SetBkMode(dstHdc, TRANSPARENT);
	LOGFONT lfont = { 0 };
	lstrcpy(lfont.lfFaceName, "ºÚÌå");
	lfont.lfWidth = charSize;
	lfont.lfHeight = charSize;
	HFONT font = CreateFontIndirect(&lfont);
	HGDIOBJ old=SelectObject(dstHdc, font);

	long startTime = GetTickCount();
	char ch[2] = { 0 };
	for (int i = 0; i < dstWidth; i++){
		int dstPosX = i*charSize;
		for (int j = 0; j < dstHeight; j++){

			COLORREF color = GetPixel(srcHdc, i, j);

			COLORREF dstColor = color;
			COLORREF gray = RGBtoGRAY(color);
			if (keepRgb){
				dstColor = color;
			}
			else{
				dstColor = 0xffffff;// RGB(255, 255, 255);
			}
			SetTextColor(dstHdc, dstColor);
			double rate = ((gray & 0xff)*1.0 / 255);
			int idx = (1.0 - rate)*mappingLen;
			if (!keepRgb){
				idx = rate*mappingLen;
			}
			
			ch[0] = chArr[idx];
			TextOut(dstHdc, dstPosX, j*charSize, ch, 1);
		}
	}
	DeleteObject(font);
	SelectObject(dstHdc, old);
	long endTime = GetTickCount();
	printf("\tpixels process done.time used:%dms\n",(endTime-startTime));
	saveimage(dstFile, &dstImg);
	printf("\timage has saved into:%s\n", dstFile);
}
