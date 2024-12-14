#include "stdafx.h"
#include "D3EmitBall.h"

D3EmitBall::D3EmitBall()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(2000);
}

D3EmitBall::D3EmitBall(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width, height);
	SetMaxCount(count);
}
void D3EmitBall::makeUniqueStereo(){
	if (m_storeo != NULL){
		delete m_storeo;
	}

	int type = rand() % 12;
	switch (type)
	{
	case 0:
		m_storeo = GStereo::CreateBallEx(mWinHeight / 3, 3);
		break;
	case 1:
		m_storeo = GStereo::CreateBall(mWinHeight / 3, 60, 30);
		m_storeo = GTeanglelized::PointsTranglelized(m_storeo);
		break;
	case 2:
		m_storeo = GStereo::CreateCone(mWinHeight / 2, mWinHeight / 4, 30, 30, 50);
		m_storeo = GTeanglelized::PointsTranglelized(m_storeo);
		break;
	case 3:
		m_storeo = GStereo::CreateCylinder(mWinHeight / 6, mWinHeight / 3, 20, 40, 40);
		m_storeo = GTeanglelized::PointsTranglelized(m_storeo);
		break;
	case 4:
		m_storeo = GStereo::CreateDodecahedron(mWinHeight / 4);
		break;
	case 5:
		m_storeo = GStereo::CreateHexahedron(mWinHeight / 4);
		break;
	case 6:
		m_storeo = GStereo::CreateIcosahedron(mWinHeight / 3);
		break;
	case 7:
		m_storeo = GStereo::CreateOctahedron(mWinHeight / 3);
		break;
	case 8:
		m_storeo = GStereo::CreateTetrahedron(mWinHeight / 4);
		break;
	case 9:
		m_storeo = GStereo::CreateTorus(mWinHeight / 3, mWinHeight / 10, 50, 22);
		m_storeo = GTeanglelized::PointsTranglelized(m_storeo);
		break;
	case 10:
		m_storeo = GStereo::CreateSixCrystal(mWinHeight / 3, mWinHeight / 3/2);
		break;
	case 11:
		m_storeo = GStereo::CreateEightCrystal(mWinHeight / 4, (mWinHeight / 4) *(2.0/5));
		break;
	default:
		break;
	}
	xAngleDirect = (rand() % 360) / 180.0*3.1415926535;
	yAngleDirect = (rand() % 360) / 180.0*3.1415926535;
	zAngleDirect = (rand() % 360) / 180.0*3.1415926535;

	xAngleStep = ((rand() % 10) / 10.0) / 180.0*3.1415926535;
	yAngleStep = ((rand() % 10) / 10.0) / 180.0*3.1415926535;
	zAngleStep = ((rand() % 10) / 10.0) / 180.0*3.1415926535;
}
void D3EmitBall::SetDefaultArgument()
{
	mMaxCount = 2000;
	mLight = NULL;
	mWinWidth = 720;
	mWinHeight = 480;

	roundR = 300;
	roundAAngle = 0;
	roundBAngle = 0;
}


D3EmitBall::~D3EmitBall()
{
	if (m_storeo != NULL){
		delete m_storeo;
	}
	for (int i = 0; i < mMaxCount; i++){
		if (mLight[i].head4!=NULL)
			delete mLight[i].head4;
	}
	if (mLight != NULL)
	{
		free(mLight);
	}
}

void D3EmitBall::SetMaxCount(int count)
{
	if (mLight != NULL)
	{
		free(mLight);
		mLight = NULL;
	}
	mMaxCount = count;
	mLight = (Light*)malloc(sizeof(Light)*mMaxCount);
	for (int i = 0; i < mMaxCount; i++){
		mLight[i].head4 = NULL;
	}
}

void D3EmitBall::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}
void D3EmitBall::SetLightToDefault(int index)
{
	//POINT cursor = { 0 };
	//GetCursorPos(&cursor);
	mLight[index].live = true;

	mLight[index].len = 0;
	mLight[index].maxLen = rand() % (mWinWidth * 2 / 3) + (mWinWidth * 1 / 3);
	mLight[index].lenStep = rand() % (int)(mLight[index].maxLen/20)+1;

	mLight[index].aAngleDirect = (rand() % 360) / 180.0*3.1415926535;
	mLight[index].bAngleDirect = (rand() % 180) / 180.0*3.1415926535;

	mLight[index].aAngleStep = ((rand() % 10)/10.0) / 180.0*3.1415926535;
	mLight[index].bAngleStep = ((rand() % 10)/10.0) / 180.0*3.1415926535;

	mLight[index].r = rand() % 200 + 54;
	mLight[index].b = rand() % 200 + 54;
	mLight[index].g = rand() % 200 + 54;
	
	mLight[index].clipLen = 0;

	if (mLight[index].head4 != NULL){
		delete mLight[index].head4;
	}
	mLight[index].head4 = GStereo::CreateOctahedron(rand()%(mWinHeight/100)+1);
}

void D3EmitBall::InitLight()
{
	makeUniqueStereo();
	for (int i = 0; i < mMaxCount; i++)
	{
		SetLightToDefault(i);
		if (3 > rand() % 100)
			mLight[i].live = true;
		else
			mLight[i].live = false;
	}
}
void D3EmitBall::CreateLight()
{
	int maxCount = rand() % mMaxCount + 1;
	int curCount = 0;
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live == false)
		{
			if (rand() % 100 < 21)
			{
				SetLightToDefault(i);
				mLight[i].live = true;
				curCount++;
			}
		}
		if (curCount >= maxCount)
			break;
	}
}

void D3EmitBall::drawD3Data(HDC hdc, GD3DataGroup * gddata, double viewR, double viewD)
{
	static double PI2 = 3.141592653549 * 2;
	static int lr = 128, lg = 128, lb = 128;
	static int cr = 255, cg = 0, cb = 255;
	static int curTimes = 0, maxTimes = 100;
	static double rate = 0, drate = 1.0;
	if (curTimes == 0){
		lr = cr;
		lg = cg;
		lb = cb;
		cr = rand() % 255;
		cg = rand() % 255;
		cb = rand() % 255;
	}
	rate = curTimes*1.0 / maxTimes;
	drate = 1.0 - rate;
	curTimes = (curTimes + 1) % maxTimes;

	POINT arr[4];
	
	HPEN pen = CreatePen(0, 1, RGB(drate*lr + rate*cr, drate*lg+rate*cg,drate*lb+rate*cb));
	HGDIOBJ op = SelectObject(hdc, pen);

	static double scaleRate = 1;
	static int directScale = 1;
	static int directFactor = 1;
	GD3Point round = GD3Point();
	round.ParseSpherical(roundR, roundAAngle, roundBAngle);
	roundR += (rand()%5)*directFactor;
	if (roundR < -1200){
		directFactor =1;
	}
	if (roundR>1200){
		directFactor = -1;
	}
	if (directScale > 0){
		scaleRate *= 1.01;
	}
	if (directScale < 0){
		scaleRate *= 0.99;
	}
	if (directScale < 0.5){
		if (rand() % 100 < 5 && rand() % 100 < 5){
			directScale = 1;
		}
	}
	if (scaleRate>2.00){
		if (rand() % 100 < 5 && rand() % 100 < 5){
			directScale = -1;
		}
	}
	if (scaleRate < 0.1){
		directScale = 1;
	}
	if (scaleRate>3.00){
		directScale = -1;
	}
	
	roundAAngle += 1/180.0*3.1415926535;
	roundBAngle += 1 / 180.0*3.1415926535;

	if (roundAAngle > PI2){
		roundAAngle -= PI2;
	}
	if (roundBAngle > PI2){
		roundBAngle -= PI2;
	}

	for (int i = 0; i<gddata->getTrangleCount(); i++)
	{

		GD3Point tp = gddata->pointAt(gddata->trangleAt(i).p1);
		GD3Vary::Scale(&tp, scaleRate, scaleRate, scaleRate);
		GD3Vary::Spin(&tp, xAngleDirect, yAngleDirect, zAngleDirect);
		GD3Vary::Move(&tp, round.x, round.y, round.z);

		GProj::TwoPoint(&tp, viewR, viewD);
		arr[0].x = tp.x;
		arr[0].y = tp.y;

		tp = gddata->pointAt(gddata->trangleAt(i).p2);
		GD3Vary::Scale(&tp, scaleRate, scaleRate, scaleRate);
		GD3Vary::Spin(&tp, xAngleDirect, yAngleDirect, zAngleDirect);
		GD3Vary::Move(&tp, round.x, round.y, round.z);

		GProj::TwoPoint(&tp, viewR, viewD);
		arr[1].x = tp.x;
		arr[1].y = tp.y;

		tp = gddata->pointAt(gddata->trangleAt(i).p3);
		GD3Vary::Scale(&tp, scaleRate, scaleRate, scaleRate);
		GD3Vary::Spin(&tp, xAngleDirect, yAngleDirect, zAngleDirect);
		GD3Vary::Move(&tp, round.x, round.y, round.z);

		GProj::TwoPoint(&tp, viewR, viewD);
		arr[2].x = tp.x;
		arr[2].y = tp.y;

		arr[3] = arr[0];
		
		

		Polyline(hdc, arr, 4);


	}
	SelectObject(hdc, op);
	DeleteObject(pen);
	DeleteObject(op);


	xAngleDirect += xAngleStep;
	yAngleDirect += yAngleStep;
	zAngleDirect += zAngleStep;
	if (xAngleDirect >= 2 * 3.1415926535){
		xAngleDirect -= 2 * 3.1415926535;
	}
	if (yAngleDirect >= 2 * 3.1415926535){
		yAngleDirect -= 2 * 3.1415926535;
	}
	if (zAngleDirect >= 2 * 3.1415926535){
		zAngleDirect -= 2 * 3.1415926535;
	}
}
void D3EmitBall::drawHead4(HDC hdc, int index,GD3Point & relpoint, double viewR, double viewD)
{
	GD3DataGroup * gddata = mLight[index].head4;

	POINT arr[4];

	for (int i = 0; i<gddata->getTrangleCount(); i++)
	{

		GD3Point tp = gddata->pointAt(gddata->trangleAt(i).p1);
		GD3Vary::Move(&tp, relpoint.x, relpoint.y, relpoint.z);
		GProj::TwoPoint(&tp, viewR, viewD);
		
		arr[0].x = tp.x;
		arr[0].y = tp.y;

		tp = gddata->pointAt(gddata->trangleAt(i).p2);
		GD3Vary::Move(&tp, relpoint.x, relpoint.y, relpoint.z);
		GProj::TwoPoint(&tp, viewR, viewD);
		
		arr[1].x = tp.x;
		arr[1].y = tp.y;

		tp = gddata->pointAt(gddata->trangleAt(i).p3);
		GD3Vary::Move(&tp, relpoint.x, relpoint.y, relpoint.z);
		GProj::TwoPoint(&tp, viewR, viewD);
		
		arr[2].x = tp.x;
		arr[2].y = tp.y;

		arr[3] = arr[0];


		Polyline(hdc, arr, 4);


	}
}
void D3EmitBall::DrawBackground(HDC hdc)
{
	//中央坐标系
	int width = mWinWidth;
	int height = mWinHeight;

	POINT oldPoint;
	SIZE oldSize, oldWinSize;
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportOrgEx(hdc, width / 2, height / 2, &oldPoint);
	SetViewportExtEx(hdc, width, height, &oldSize);
	SetWindowExtEx(hdc, width, -height, &oldWinSize);

	double viewR = mWinWidth *2;
	double viewD = mWinWidth*2;

	static int PER_SIFT = 3;

	POINT temptp;
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mLight[i].live)
		{
			HPEN pen = CreatePen(0, 1, RGB(mLight[i].r, mLight[i].g, mLight[i].b));
			HGDIOBJ op = SelectObject(hdc, pen);

			GD3Point point;
			point.ParseSpherical(mLight[i].len, mLight[i].aAngleDirect, mLight[i].bAngleDirect);
			drawHead4(hdc, i, point, viewR, viewD);
			GProj::TwoPoint(&point, viewR,viewD);

			GD3Point cpoint;
			cpoint.ParseSpherical(mLight[i].clipLen, mLight[i].aAngleDirect, mLight[i].bAngleDirect);
			GProj::TwoPoint(&cpoint, viewR, viewD);
			mLight[i].clipLen += rand()%(int)(mLight[i].lenStep+1);

			

			MoveToEx(hdc, cpoint.x, cpoint.y, &temptp);
			LineTo(hdc, point.x, point.y);

			SelectObject(hdc, op);
			DeleteObject(pen);
			DeleteObject(op);


			/*mLight[i].aAngleDirect += mLight[i].aAngleStep;
			mLight[i].bAngleDirect += mLight[i].bAngleStep;
			if (mLight[i].aAngleDirect >= 2 * 3.1415926535){
				mLight[i].aAngleDirect -= 2 * 3.1415926535;
			}
			if (mLight[i].bAngleDirect >=  3.1415926535){
				mLight[i].bAngleDirect -=  3.1415926535;
			}*/

			mLight[i].len += mLight[i].lenStep;
			if (mLight[i].len >= mLight[i].maxLen){
				mLight[i].live = false;
			}
		}

	}
	drawD3Data(hdc, m_storeo,viewR,viewD);

	POINT voldPoint;
	SIZE voldSize, voldWinSize;
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportOrgEx(hdc, oldPoint.x,oldPoint.y, &voldPoint);
	SetViewportExtEx(hdc, oldSize.cx, oldSize.cy, &voldSize);
	SetWindowExtEx(hdc, oldWinSize.cx,oldWinSize.cy, &voldWinSize);


	//记录上一次创建新的粒子的时间
	static DWORD last_create_time = GetTickCount();

	//判断是否有任何按键按下，如果有任何按键按下，就创建粒子
	bool isDown = false;
	//最小的虚拟键码就是VK_LBUTTON，值为0x01
	for (int i = 1; i < 256; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			CreateLight();
			isDown = true;
			last_create_time = GetTickCount();
			break;
		}
	}

	//如果没有任何按键按下，如果距离上一次创建粒子时间超过了一个时间，那就创建一次
	if (isDown == false)
	{
		DWORD now_time = GetTickCount();
		int diff = rand() % 3000 + 2000;//时间随机到此区间
		if (now_time - last_create_time > diff)
		{
			CreateLight();
			last_create_time = now_time;
		}
	}

}