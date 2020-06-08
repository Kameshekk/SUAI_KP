#include "Model.h"
#include "View.h"
#include "Controller/Server.h"
#include "Controller/Client.h"


// main.cpp : Defines the entry point for the application.
//

// main.cpp : Defines the entry point for the application.
//

//#include "framework.h"
#include "resource.h"


#define IDT_STEP_TIMER 1

#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // Глобальная переменная для дескриптора приложения
WCHAR szTitle[MAX_LOADSTRING];                  // Название, которое написано сверху
WCHAR szWindowClass[MAX_LOADSTRING];            // Имя класса окна

View* _View;										// Указатель на объект графической оболочки приложения
Model* _Model;
Controller* _Controller;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Settings(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);		// Неиспользуемые переменные
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Инициализируем глобальные переменные
	LoadStringW(hInstance, IDS_TITLE, szTitle, MAX_LOADSTRING);	// Вставить название окна
	LoadStringW(hInstance, IDS_SHIPS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, NULL);		// ВСТАВИТЬ АКСЕЛЕРАТОРЫ		
	//_Controller.InitController(ptr_Model);		// ПОМЕНЯТЬ И СДЕЛАТЬ ЧЕРЕЗ УКАЗАТЕЛИ!!!!!!!!!
	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
			//_Controller->sended();
		}
	}

	return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDS_SHIPS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL; // LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void SetClientSize(HWND hwnd, int clientWidth, int clientHeight)
{
	if (IsWindow(hwnd))
	{
		RECT newClientRC;
		GetClientRect(hwnd, &newClientRC);
		if ((newClientRC.right - newClientRC.left) == clientWidth &&
			(newClientRC.bottom - newClientRC.top) == clientHeight)
			return;

		DWORD dwStyle = GetWindowLongPtr(hwnd, GWL_STYLE);
		DWORD dwExStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
		HMENU menu = GetMenu(hwnd);

		RECT rc = { 0, 0, clientWidth, clientHeight };

		AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle);

		SetWindowPos(hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
			SWP_NOZORDER | SWP_NOMOVE);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC, hdcMem;
	BITMAP bm;
	HGDIOBJ hbmOld;
	PAINTSTRUCT ps; 
	HBITMAP hBitMap;
	switch (message)
	{
	case WM_CREATE:
		_Model = new Model(hWnd);
		_Controller = new Server(_Model);
		_View = new View(_Model);
		
		break;

	break;
	case WM_PAINT:
	{
		
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// double-buffered
		HDC memDC = CreateCompatibleDC(hdc);

		// get window's client rectangle. We need this for bitmap creation.
		RECT rcClientRect;
		GetClientRect(hWnd, &rcClientRect);

		// now we can create bitmap where we shall do our drawing
		HBITMAP bmp = CreateCompatibleBitmap(hdc,
			rcClientRect.right - rcClientRect.left,
			rcClientRect.bottom - rcClientRect.top);

		// we need to save original bitmap, and select it back when we are done,
		// in order to avoid GDI leaks!
		HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
		PatBlt(memDC, 0, 0, 1550, 800, WHITENESS);
		_View->Draw(memDC);

		// OK, everything is drawn into memory DC, 
		// now is the time to draw that final result into our target DC

		BitBlt(hdc, 0, 0, rcClientRect.right - rcClientRect.left,
			rcClientRect.bottom - rcClientRect.top, memDC, 0, 0, SRCCOPY);

		// all done, now we need to cleanup
		SelectObject(memDC, oldBmp); // select back original bitmap
		DeleteObject(bmp); // delete bitmap since it is no longer required
		DeleteDC(memDC);   // delete memory DC since it is no longer required
		EndPaint(hWnd, &ps); //завершение рисования
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		int mouseX = GET_X_LPARAM(lParam);
		int mouseY = GET_Y_LPARAM(lParam);
		_Controller->ClickLeft(mouseX, mouseY);
		InvalidateRect(hWnd, NULL, false);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		system("pause");
	}
	return 0;
}
