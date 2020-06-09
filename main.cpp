#include "Model.h"
#include "View.h"
#include "Controller/Server.h"
#include "Controller/Client.h"


// main.cpp : Defines the entry point for the application.
//

// main.cpp : Defines the entry point for the application.
//

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
	LoadStringW(hInstance, IDS_TITLE, szTitle, MAX_LOADSTRING);	// Вставить название окна	// ПОМЕНЯТЬ!!!!!!!!!!!!!!!!!!!!!!!!!
	LoadStringW(hInstance, IDS_SHIPS, szWindowClass, MAX_LOADSTRING);	// ПОМЕНЯТЬ!!!!!!!!!!!!!!!!!!!!!!!!!
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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
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
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDS_SHIPS);	// ПОМЕНЯТЬ!!!!!!!!!!!!!!!!!!!!!!!!!
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
		CW_USEDEFAULT, 0, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//
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
		_Controller->set_state(start);

		static HWND OK = CreateWindow("BUTTON", "Game", WS_CHILD | WS_VISIBLE, 550, 500, 100, 30, hWnd, (HMENU)1001, hInst, NULL);
		//GameContext::GetInstance()->Reset();
		//GameContext::GetInstance()->SeedRandom(time(0));
		//SetTimer(hWnd, IDT_STEP_TIMER, 200, NULL);
		
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		if (wParam == 1001)
		{
			switch (_Controller->get_state())
			{
			case start: _Controller->set_state(allocation); break;
			case allocation: _Controller->set_state(mov); break;
			case mov: _Controller->set_state(wait); break;
			case wait: _Controller->set_state(start); break;

			default:
				break;
			}
			//DestroyWindow(OK);
		}
		UpdateWindow(hWnd);
	}
	break;
	/*case WM_LBUTTONDOWN:
		HDC hdc = GetDC(hWnd);
		POINT pt;
		RECT rect;
		static POINT dif;
		static POINT str_pt{ 0,0 };
		RECT str_rect;
		SIZE str_sz;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		SetRect(&str_rect, str_pt.x, str_pt.y, 4*CELL_SIZE, CELL_SIZE);

		if (PtInRect(&str_rect, pt))
			SetTimer(hWnd, 2, 16, 0);
		ReleaseDC(hWnd, hdc);
		dif.x = pt.x - str_pt.x;
		dif.y = pt.y - str_pt.y;
		break;
	case WM_TIMER:
		GetClientRect(hWnd, &rect);
		GetCursorPos(&str_pt);
		str_pt.x -= dif.x;
		str_pt.y -= dif.y;
		ScreenToClient(hWnd, &str_pt);
		InvalidateRect(hWnd, 0, 1);
		break;
	case WM_LBUTTONUP:
		KillTimer(hWnd, 2);
		break;
	case WM_MOVE:
		
		
		break;*/
	case WM_PAINT:
	{
		//SetClientSize(hWnd, gameUI->GetWidth(), gameUI->GetHeight());

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

		switch (_Controller->get_state())
		{
		case start: _View->Draw_Start(memDC, rcClientRect); break;
		case connection: _View->Draw_Start(memDC, rcClientRect); break;
		case allocation:  _View->Draw_Allocation(memDC); break;
		case mov: _View->Draw_Move(memDC); break;
		case wait: _View->Draw_Move(memDC); break;
		case win: _View->Draw_Move(memDC); break;
		case lose: _View->Draw_Move(memDC); break;
		default:
			break;
		}
		//_View->Draw_Move(memDC);

		
		// OK, everything is drawn into memory DC, 
		// now is the time to draw that final result into our target DC

		BitBlt(hdc, 0, 0, rcClientRect.right - rcClientRect.left,
			rcClientRect.bottom - rcClientRect.top, memDC, 0, 0, SRCCOPY);

		// all done, now we need to cleanup
		SelectObject(memDC, oldBmp); // select back original bitmap
		DeleteObject(bmp); // delete bitmap since it is no longer required
		DeleteDC(memDC);   // delete memory DC since it is no longer required
		EndPaint(hWnd, &ps); //завершение рисования
		//HWND OK = CreateWindow("BUTTON","Game",WS_CHILD | WS_VISIBLE, 550, 500, 100, 30, hWnd, (HMENU)1001, hInst, NULL);
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
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		system("pause");
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
