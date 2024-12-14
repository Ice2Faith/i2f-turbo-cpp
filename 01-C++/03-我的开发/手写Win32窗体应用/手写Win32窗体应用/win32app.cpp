#include<Windows.h>
#include<windowsx.h>
#include<map>

enum RESIZE_MODE{
	RESIZE_MODE_ADAPT=0,
	RESIZE_MODE_CUT = 1,
	RESIZE_MODE_FIXED = 2
};

typedef struct _BITMAP_DC{
	HDC hdc;
	HBITMAP hBitMap;
	int width;
	int height;
} BITMAP_DC,* P_BITMAP_DC;


struct _WIN32_APP_CONFIG;
typedef _WIN32_APP_CONFIG WIN32_APP_CONFIG;
typedef _WIN32_APP_CONFIG* P_WIN32_APP_CONFIG;

struct _WIN32_APP_INSTANCE;
typedef _WIN32_APP_INSTANCE WIN32_APP_INSTANCE;
typedef _WIN32_APP_INSTANCE* P_WIN32_APP_INSTANCE;


struct _WIN32_APP_CONFIG{
	wchar_t className[1024];
	wchar_t windowTitle[1024];
	wchar_t iconFileName[2048];
	DWORD nCmdShow;
	BOOL showConsole;
	RESIZE_MODE mdcResizeMode;
	void * callbackEnv;
	LRESULT(*callbackFunc)(P_WIN32_APP_INSTANCE pInstance, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

struct _WIN32_APP_INSTANCE{
	HINSTANCE hInstance;
	HWND hWnd;
	BITMAP_DC mdc;
	RESIZE_MODE mdcResizeMode;
	HICON icon;
	BOOL showConsole;
	void * callbackEnv;
	LRESULT(*callbackFunc)(P_WIN32_APP_INSTANCE pInstance, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


// 管理多个窗体的容器
static std::map<HWND, P_WIN32_APP_INSTANCE> g_apps_map;


HBITMAP createBitmap(int wWid, int wHei){
	BITMAPINFOHEADER stBmpInfoHeader = { 0 };
	int nBytesPerLine = ((wWid * 32 + 31) & (~31)) >> 3;
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	stBmpInfoHeader.biWidth = wWid;
	stBmpInfoHeader.biHeight = wHei;
	stBmpInfoHeader.biPlanes = 1;
	stBmpInfoHeader.biBitCount = 32;
	stBmpInfoHeader.biCompression = BI_RGB;
	stBmpInfoHeader.biClrUsed = 0;
	stBmpInfoHeader.biSizeImage = nBytesPerLine * wHei;
	PVOID pvBits = NULL;
	HBITMAP bitMap = CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
	return bitMap;
}

void resizeCompatibleDC(HDC hdc,P_BITMAP_DC pBDC,int newWidth,int newHeight,RESIZE_MODE resizeMode){

	bool resize = true;
	bool init = (pBDC->hdc == NULL);
	if (!init){
		if (resizeMode == RESIZE_MODE_ADAPT){
			newWidth = max(newWidth, pBDC->width);
			newHeight = max(newHeight, pBDC->height);
			resize = true;
		}
		else if (resizeMode == RESIZE_MODE_CUT){
			resize = true;
		}
		else if (resizeMode == RESIZE_MODE_FIXED){
			newWidth = pBDC->width;
			newHeight = pBDC->height;
			resize = false;
		}
		if (newWidth == pBDC->width && newHeight == pBDC->height){
			resize = false;
		}
	}

	if (resize){

		HDC mdc = CreateCompatibleDC(hdc);

		HBITMAP bitMap = createBitmap(newWidth, newHeight);
		HGDIOBJ oldBitmap = SelectObject(mdc, bitMap);
		Rectangle(mdc, -1, -1, newWidth + 1, newHeight + 1);

		if (!init){
			BitBlt(mdc, 0, 0, pBDC->width, pBDC->height, pBDC->hdc, 0, 0, SRCCOPY);
			DeleteObject(pBDC->hBitMap);
			DeleteDC(pBDC->hdc);
		}

		pBDC->hBitMap = bitMap;
		pBDC->hdc = mdc;
		pBDC->width = newWidth;
		pBDC->height = newHeight;
	}

}


// 事件分发器
LRESULT CALLBACK dispatcherWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	
	P_WIN32_APP_INSTANCE p_instance = g_apps_map[hWnd];
	std::map<HWND, P_WIN32_APP_INSTANCE>* p_g_apps = &g_apps_map;

	if (p_instance == NULL){
		return  DefWindowProcW(hWnd, message, wParam, lParam);
	}

	p_instance->callbackFunc(p_instance, hWnd, message, wParam, lParam);

}


int createWin32App(WIN32_APP_CONFIG* config){

	P_WIN32_APP_INSTANCE p_instance = (P_WIN32_APP_INSTANCE)malloc(sizeof(WIN32_APP_INSTANCE));
	memset(p_instance, 0, sizeof(WIN32_APP_INSTANCE));
	// 参数拷贝
	p_instance->showConsole = config->showConsole;
	// 设置MDC大小处理
	p_instance->mdcResizeMode = config->mdcResizeMode;

	// 获取实例句柄
	p_instance->hInstance = GetModuleHandleW(NULL);
	// 初始化回调
	p_instance->callbackEnv = config->callbackEnv;
	p_instance->callbackFunc = config->callbackFunc;

	// 加载图标
	if (lstrlenW(config->iconFileName) > 0){
		p_instance->icon = ExtractIconW(p_instance->hInstance, config->iconFileName, 0);
	}
	if ((int)p_instance->icon == 1){
		p_instance = NULL;
	}

	
	// 控制台
	if (p_instance->showConsole==FALSE) {
		FreeConsole();
	}
	
	
	
	// 注册类样式
	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXW);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)dispatcherWndProc;
	wc.cbClsExtra = 0;
	wc.hInstance = p_instance->hInstance;
	wc.hIcon = p_instance->icon;
	wc.hCursor = LoadCursorW(p_instance->hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = config->className;
	wc.hIconSm = p_instance->icon;

	ATOM retRc=RegisterClassExW(&wc);

	// 创建窗口
	p_instance->hWnd = CreateWindowW(config->className,
		config->windowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0,
		NULL,
		NULL,
		p_instance->hInstance,
		NULL);

	// 绑定全局
	g_apps_map[p_instance->hWnd] = p_instance;


	// 初始化MDC
	RECT rect = { 0 };
	GetClientRect(p_instance->hWnd, &rect);

	int newWidth = rect.right - rect.left;
	int newHeight = rect.bottom - rect.top;

	HDC hdc = GetDC(p_instance->hWnd);
	resizeCompatibleDC(hdc, &p_instance->mdc, newWidth, newHeight, p_instance->mdcResizeMode);
	ReleaseDC(p_instance->hWnd, hdc);

	// 显示窗口
	BOOL retSw = ShowWindow(p_instance->hWnd, config->nCmdShow);
	BOOL retUw= UpdateWindow(p_instance->hWnd);

	// 开始消息循环
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return (int)msg.wParam;
}

DWORD WINAPI createWin32AppThreadFunction(LPVOID lpParam){
	P_WIN32_APP_CONFIG config = (P_WIN32_APP_CONFIG)lpParam;
	return createWin32App(config);
}

LRESULT simpleCallbackFunc(P_WIN32_APP_INSTANCE p_instance, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;

	static bool isLeftDown = false;
	static POINT lastPoint = { 0, 0 };
	static bool hasConsole = false;

	RECT rect = { 0 };
	GetClientRect(hWnd, &rect);


	switch (message){
	case WM_CREATE:

		break;
	case WM_COMMAND:

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, p_instance->mdc.hdc, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		g_apps_map.erase(hWnd);
		DeleteDC(p_instance->mdc.hdc);
		if (p_instance->icon != NULL){
			DestroyIcon(p_instance->icon);
		}
		free(p_instance);
		break;
	case WM_KEYUP:
	{
					 if (wParam == VK_F12){
						 p_instance->showConsole = !p_instance->showConsole;
						 if (p_instance->showConsole){
							 AllocConsole();
							 freopen("CONIN$", "r", stdin); // 重定向标准输入
							 freopen("CONOUT$", "w", stdout); // 重定向标准输出
							 freopen("CONOUT$", "w", stderr); // 重定向标准错误输出
						 }
						 else{
							 HWND h = GetConsoleWindow();
							 FreeConsole();
							 PostMessageW(h, WM_DESTROY, 0, 0);
							 PostMessageW(h, WM_QUIT, 0, 0);
						 }
					 }
	}
		break;
	case WM_LBUTTONDOWN:
	{
						   isLeftDown = true;
						   lastPoint.x = GET_X_LPARAM(lParam);
						   lastPoint.y = GET_Y_LPARAM(lParam);

	}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
	{
						 isLeftDown = false;
						 lastPoint.x = GET_X_LPARAM(lParam);
						 lastPoint.y = GET_Y_LPARAM(lParam);
	}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_RBUTTONUP:
	{
						 HBRUSH brush = CreateSolidBrush(0xffffff);
						 HGDIOBJ oldBrush = SelectObject(p_instance->mdc.hdc, brush);
						 Rectangle(p_instance->mdc.hdc, -1, -1, p_instance->mdc.width + 1, p_instance->mdc.height + 1);
						 SelectObject(p_instance->mdc.hdc, brush);
						 DeleteObject(brush);
						 InvalidateRect(hWnd, NULL, TRUE);
	}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
	{
						 int x = GET_X_LPARAM(lParam);
						 int y = GET_Y_LPARAM(lParam);

						 if (isLeftDown){
							 MoveToEx(p_instance->mdc.hdc, lastPoint.x, lastPoint.y, NULL);
							 LineTo(p_instance->mdc.hdc, x, y);
						 }

						 lastPoint.x = x;
						 lastPoint.y = y;
						 printf("%d,%d\n", x, y);
	}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SIZE:
	{

					int newWidth = rect.right - rect.left;
					int newHeight = rect.bottom - rect.top;
					HDC dc = GetDC(hWnd);
					resizeCompatibleDC(dc, &p_instance->mdc, newWidth, newHeight, p_instance->mdcResizeMode);
					ReleaseDC(hWnd, dc);

	}
		break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}

int main(int argc, char* argv[]){
	WIN32_APP_CONFIG config = { 0 };
	lstrcpyW(config.className, L"Win32Application");
	lstrcpyW(config.windowTitle, L"Win32应用程序");
	lstrcpyW(config.iconFileName, L"win32.ico");
	config.callbackFunc = simpleCallbackFunc;
	config.showConsole = FALSE;
	config.mdcResizeMode = RESIZE_MODE_ADAPT;
	config.nCmdShow = SW_SHOW;

	// 使用两个线程创建两个窗体
	WIN32_APP_CONFIG config1 = { 0 };
	memcpy(&config1, &config, sizeof(WIN32_APP_CONFIG));
	lstrcatW(config1.windowTitle, L"-1");
	HANDLE th1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)createWin32AppThreadFunction, &config1, 0, NULL);

	WIN32_APP_CONFIG config2 = { 0 };
	memcpy(&config2, &config, sizeof(WIN32_APP_CONFIG));
	lstrcatW(config2.windowTitle, L"-2");
	HANDLE th2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)createWin32AppThreadFunction, &config2, 0, NULL);
	// 并等待两个窗体结束
	HANDLE arr[] = { th1, th2 };
	WaitForMultipleObjects(2, arr, TRUE, -1);
	return 0;
}
