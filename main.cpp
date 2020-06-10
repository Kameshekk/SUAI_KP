#include "Model.h"
#include "View.h"
#include "Controller/Server.h"
#include "Controller/Client.h"
#define FIRST_TIMER 1 
int nTimerID = 0; 
// main.cpp : Defines the entry point for the application.
//

// main.cpp : Defines the entry point for the application.
//

//#include "framework.h"


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
bool                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
bool InitInstance(HINSTANCE hInstance, int nCmdShow)
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

bool InitController(int mouseX, int mouseY)
{
		if ((mouseX > MARGIN_LEFT) && (mouseX < MARGIN_LEFT + 10 * CELL_SIZE) &&
			(mouseY > MARGIN_TOP) && (mouseY < MARGIN_TOP + 10 * CELL_SIZE))
		{
			_Controller = new Server(_Model);
			_Controller->set_state(wait_connection);
			return true;
		}
		if ((mouseX > WIDTH - MARGIN_LEFT - 10 * CELL_SIZE) && (mouseX < WIDTH - MARGIN_LEFT) &&
			(mouseY > MARGIN_TOP) && (mouseY < MARGIN_TOP + 10 * CELL_SIZE))
		{
			_Controller = new Client(_Model);
			_Controller->set_state(connection);
			return true;
		}
		return false;
}

void enter(char var)
{
	char IPaddress[16];
	strcpy(IPaddress, _Model->get_IP());
	int len = strlen(IPaddress);
	if((len > 13) && (var != 'b'))
		return;
	if (var == 'b')
	{
		if (len < 1)
			return;
		len--;
		IPaddress[len] = '\0';
	}
	else
	{
		IPaddress[len] = var;
		IPaddress[len + 1] = '\0';
	}
	_Model->set_IP(IPaddress);
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

		static HWND OK = CreateWindow("BUTTON", "Game", WS_CHILD | WS_VISIBLE, 550, 500, 100, 30, hWnd, (HMENU)1001, hInst, NULL);
		_Model = new Model(hWnd);
		_View = new View(_Model);
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
		}
		UpdateWindow(hWnd);
	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x30: enter('0'); break;
		case 0x31: enter('1'); break;
		case 0x32: enter('2'); break;
		case 0x33: enter('3'); break;
		case 0x34: enter('4'); break;
		case 0x35: enter('5'); break;
		case 0x36: enter('6'); break;
		case 0x37: enter('7'); break;
		case 0x38: enter('8'); break;
		case 0x39: enter('9'); break;
		case VK_NUMPAD0: enter('0'); break;
		case VK_NUMPAD1: enter('1'); break;
		case VK_NUMPAD2: enter('2'); break;
		case VK_NUMPAD3: enter('3'); break;
		case VK_NUMPAD4: enter('4'); break;
		case VK_NUMPAD5: enter('5'); break;
		case VK_NUMPAD6: enter('6'); break;
		case VK_NUMPAD7: enter('7'); break;
		case VK_NUMPAD8: enter('8'); break;
		case VK_NUMPAD9: enter('9'); break;
		case VK_BACK: enter('b'); break;
		case VK_OEM_PERIOD: enter('.'); break;
		case VK_RETURN:
			_Controller->conect();
			break;
		}
		UpdateWindow(hWnd);
		InvalidateRect(hWnd, NULL, false);
		break;
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
		int flag = 0;
		// we need to save original bitmap, and select it back when we are done,
		// in order to avoid GDI leaks!
		HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);
		PatBlt(memDC, 0, 0, 1550, 800, WHITENESS);
		if (_Controller == nullptr)
		{
			_View->Draw_Start(memDC);
		}
		else
		{
			switch (_Controller->get_state())
			{
			case wait_connection: _View->Draw_Wait_Connection(memDC, rcClientRect); flag = 1; break;
			case connection: _View->Draw_Connection(memDC, rcClientRect); break;
			case allocation:  _View->Draw_Allocation(memDC); break;
			case mov: _View->Draw(memDC, rcClientRect, 'm'); break;
			case wait: _View->Draw(memDC, rcClientRect, 'w'); break;
			case win:  break;
			case lose:  break;
			default:
				break;
			}
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
		if (flag == 1)
		{
			_Controller->conect();
			UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, false);
		}
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
		if (_Controller == nullptr)
		{
			if(InitController(mouseX, mouseY))
			{
				UpdateWindow(hWnd);
				InvalidateRect(hWnd, NULL, false);
			}
			break;
		}
		if (_Controller->ClickLeft(mouseX, mouseY) == allocation)
		{
			UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, false);
			_Controller->ready();
		}
		if((_Controller->get_state() == wait) && nTimerID == 0)
			nTimerID = SetTimer(hWnd, FIRST_TIMER, 1000, NULL);
		UpdateWindow(hWnd);
		InvalidateRect(hWnd, NULL, false);
		break;
	}
	case WM_TIMER:
	{
		if (_Controller->get_state() == wait)
		{
			_Controller->waiting();
			if (_Controller->get_state() != wait)
			{
				KillTimer(hWnd, FIRST_TIMER);
				nTimerID = 0;
			}
		}
		UpdateWindow(hWnd);
		InvalidateRect(hWnd, NULL, false);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
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