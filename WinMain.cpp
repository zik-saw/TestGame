#include <windows.h>

//формуруем функции по созданию окна
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowTitle, int width, int height);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowTitle, int x, int y ,int width, int height);


//основная функция
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsce, LPSTR lpCmdLine, int nCmdShow)

	if(GenerateWindow(hInstance, nCmdShow, L"Win32ow", L"Your first Win32 Window", 1280, 720))
	{
		MSG msg;

		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //проверяет есть ли в очереди сообщения и программа работает дальше(в отличиии от getMessage, которая ожидает пока не выолнися текущее событие(в духе синхронных и асинхронных процессов))
			{//PM_REMOVE - Удалять сообщения из оеди
				TranslateMessage(&msg); //преобразование клавиатурного ввода

				DispatchMessage(&msg);// обработка и пересылка сообщений в WindowPr
			}

			if(msg.message == WM_QUIT) break;
			else
			{
				//здесь будет прорисовка и обработка нажатий на клаву с мышью
			}
		}

		return msg.wParam;
	}

	return 0;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowTitle, int width, int height)
{
	return GenerateWindow(hInstance, nCmdShow, csName, windowTitle, (GetSystemMetrics(SM_CXSCREEN) - width) / 2, 
		(GetSystemMetrics(SM_CXSCREEN) - height)/2 , width, height);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className , LPCTSTR windowTitle ,int x, int y, int width, int height)
{
	HWND hWnd;

	WNDCLASS wc;
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CSEDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIconL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszClassName = className;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}


	hWnd = CreateWindowEx(NULL, ssName, windowTitle, WS_VISIBLE, 0,0, width, height, NULL,NULL,hInstance, NULL);

	//мутит полноэкранное окно
	//hWnd = CreateWindowEx(WS_EX_WINDOWEDGE , className, windowTitle, WS_VISIBLE, 0,0, GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CXSCREEN), NULL,NULL,hInstance, NULL);
	//SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & (~WS_CAPTION));
	
	ShowWindow(hWnd, nCmdShow);

	return true;
}


//обработчик события окна
LRESULT CALLBACK WindohWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuige(0); //ставит в очередь сообщение WM_destroy

			return 0;
		}break;

	case WM_PAINT:
	
	}


