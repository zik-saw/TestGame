#include <windows.h>

//формуруем функции по созданию окна
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowTitle, int width, int height);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className, LPCTSTR windowTitle, int x, int y ,int width, int height);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wPARAM, LPARAM lParam);

//основная функция
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(GenerateWindow(hInstance, nCmdShow, "Win32Window", "Your first Win32 Window", 1280, 720))
	{
		MSG msg;

		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //проверяет есть ли в очереди сообщения и программа работает дальше(в отличиии от getMessage, которая ожидает пока не выолнися текущее событие(в духе синхронных и асинхронных процессов))
			{//PM_REMOVE - Удалять сообщения из очереди
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
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, (GetSystemMetrics(SM_CXSCREEN) - width) / 2, 
		(GetSystemMetrics(SM_CXSCREEN) - height)/2 , width, height);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCTSTR className , LPCTSTR windowTitle ,int x, int y, int width, int height)
{
	HWND hWnd;

	WNDCLASS wc;
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszClassName = className;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}


	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_VISIBLE, 0,0, width, height, NULL,NULL,hInstance, NULL);

	//мутит полноэкранное окно
	//hWnd = CreateWindowEx(WS_EX_WINDOWEDGE , className, windowTitle, WS_VISIBLE, 0,0, GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CXSCREEN), NULL,NULL,hInstance, NULL);
	//SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & (~WS_CAPTION));
	
	ShowWindow(hWnd, nCmdShow);

	return true;
}


//обработчик события окна
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0); //ставит в очередь сообщение WM_destroy

			return 0;
		}break;

	case WM_PAINT:
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam); //обрабатывает те сообщения,которые вы не используете

}
