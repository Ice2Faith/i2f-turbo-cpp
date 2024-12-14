#include"D3Graph.h"
#include<Windows.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
	double Deep;
	COLORREF color;
}ZBufferItem;
typedef struct
{
	ZBufferItem ** info;
	int height;
	int width;
}ZBufferData, *LPZBufferData;
LPZBufferData MakeZBufferData(int width, int height);
void FreeZbufferData(LPZBufferData * data);
void ZBufferAlgorithm(D3Flat * flat, COLORREF * color, int flatCount, int width, int height, HDC hdc, COLORREF bgcolor);