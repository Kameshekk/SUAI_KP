#include "View.h"


View::View(Model* _Model_of_game)
{
	_Model = _Model_of_game;
}

void View::Draw_Move(HDC hdc)
{


	HBRUSH ClozeBrush = CreateSolidBrush(RGB(128, 128, 255));	// Закрытая клетка
	HBRUSH OurShipBrush = CreateSolidBrush(RGB(255, 0, 255)); // Свой корабль
	HBRUSH EnemyShipBrush = CreateSolidBrush(RGB(255, 0, 0));	// Вражеский корабль
	HBRUSH HitOfOurShip = CreateSolidBrush(RGB(255, 128, 0));	// Поврежденный свой
	HBRUSH HitOfEnemyShip = CreateSolidBrush(RGB(64, 64, 0));	// Поврежденный вражеский
	HBRUSH KillOfOurShip = CreateSolidBrush(RGB(20, 120, 20));	// Потопленный свой
	HBRUSH KillOfEnemyShip = CreateSolidBrush(RGB(120, 20, 20));	// Потопленный вражеский
	HBRUSH MissBrush = CreateSolidBrush(RGB(0, 192, 64));	// Промах
	wchar_t c[1];
	wchar_t num[1];
	c[0] = 'A';
	num[0] = '0';
	for (int vertical = 0; vertical < 10; vertical++) 
	{
		TextOut(hdc, MARGIN_LEFT - CELL_SIZE / 2, MARGIN_TOP + vertical * CELL_SIZE + CELL_SIZE/4, (LPCSTR)c, 1);
		//DrawText(hdc, (LPCSTR)c, cchText, lprc, format);
		
		c[0]++;
		for (int horizontal = 0; horizontal < 10; horizontal++)
		{
			if (vertical == 0)
			{
				TextOut(hdc, MARGIN_LEFT + horizontal * CELL_SIZE + CELL_SIZE / 3, MARGIN_TOP - CELL_SIZE / 2, (LPCSTR)num, 1);
				num[0]++;
			}
			int left = horizontal * CELL_SIZE + MARGIN_LEFT;
			int top = vertical * CELL_SIZE + MARGIN_TOP;
			int right = left + CELL_SIZE;
			int bottom = vertical * CELL_SIZE + CELL_SIZE + MARGIN_TOP;

			SelectBrush(hdc, ClozeBrush);
			switch (_Model->field_my[horizontal][vertical])
			{
			case empt: SelectBrush(hdc, ClozeBrush); break;
			case located: SelectBrush(hdc, OurShipBrush); break;
			case damaged: SelectBrush(hdc, HitOfOurShip); break;
			case kill: SelectBrush(hdc, KillOfOurShip); break;
			case miss: SelectBrush(hdc, MissBrush); break;
			default:
				break;
			}

			Rectangle(hdc, left, top, right, bottom);

		}
	}

	c[0] = 'A';
	num[0] = '0';
	for (int vertical = 0; vertical < 10; vertical++)
	{
		TextOut(hdc, 10 * CELL_SIZE + MARGIN_BETWEEN_FIELDS + MARGIN_LEFT - CELL_SIZE / 2, MARGIN_TOP + vertical * CELL_SIZE + CELL_SIZE / 4, (LPCSTR)c, 1);
		c[0]++;
		for (int horizontal = 0; horizontal < 10; horizontal++) 
		{
			if (vertical == 0)
			{
				TextOut(hdc, MARGIN_LEFT + 10 * CELL_SIZE + MARGIN_BETWEEN_FIELDS + + horizontal * CELL_SIZE + CELL_SIZE / 3, MARGIN_TOP - CELL_SIZE / 2, (LPCSTR)num, 1);
				num[0]++;
			}
			int left = (10 + horizontal) * CELL_SIZE + MARGIN_LEFT + MARGIN_BETWEEN_FIELDS;
			int top = vertical * CELL_SIZE + MARGIN_TOP;
			int right = left + CELL_SIZE;
			int bottom = vertical * CELL_SIZE + CELL_SIZE + MARGIN_TOP;

			SelectBrush(hdc, ClozeBrush);
			switch (_Model->field_his[horizontal][vertical])
			{
			case empt: SelectBrush(hdc, ClozeBrush); break;
			case located: SelectBrush(hdc, EnemyShipBrush); break;
			case damaged: SelectBrush(hdc, HitOfEnemyShip); break;
			case kill: SelectBrush(hdc, KillOfEnemyShip); break;
			case miss: SelectBrush(hdc, MissBrush); break;
			default:
				break;
			}

			Rectangle(hdc, left, top, right, bottom);

		}
	}
	DeleteBrush(ClozeBrush);
	DeleteBrush(OurShipBrush);
	DeleteBrush(EnemyShipBrush);
	DeleteBrush(HitOfOurShip);
	DeleteBrush(HitOfEnemyShip);
	DeleteBrush(KillOfOurShip);
	DeleteBrush(KillOfEnemyShip);
	DeleteBrush(MissBrush);
}

void View::Draw_Wait(HDC hdc)
{
}

void View::Draw_Win(HDC hdc)
{
}

void View::Draw_Lose(HDC hdc)
{
}

void View::Draw_Start(HDC hdc, RECT &rect)
{
	HBRUSH ServerBrush = CreateSolidBrush(RGB(128, 128, 240));
	HBRUSH ClientBrush = CreateSolidBrush(RGB(240, 128, 128));
	SelectObject(hdc, ServerBrush);
	Rectangle(hdc, MARGIN_LEFT, MARGIN_TOP, MARGIN_LEFT + 10 * CELL_SIZE, MARGIN_TOP + 10 * CELL_SIZE);
	SelectObject(hdc, ClientBrush);
	Rectangle(hdc, WIDTH - MARGIN_LEFT - 10*CELL_SIZE, MARGIN_TOP, WIDTH - MARGIN_LEFT, MARGIN_TOP + 10 * CELL_SIZE);

	HFONT hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	DrawText(hdc, "Let's Battle", -1, &rect, DT_CENTER);// Выводим текст управления для первой фигуры
	DeleteFont(hFont);

	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	DrawText(hdc, "\n\n\nChoose your role", -1, &rect, DT_CENTER);
	DeleteFont(hFont);

	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	SetBkMode(hdc, 3);
	DrawText(hdc, "\n\n\n\n\n                         Server", -1, &rect, DT_LEFT);
	DeleteFont(hFont);
	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	SetBkMode(hdc, 3);
	DrawText(hdc, "\n\n\n\n\nClient                         ", -1, &rect, DT_RIGHT);
	DeleteFont(hFont);
	DeleteBrush(ServerBrush);
	DeleteBrush(ClientBrush);
}

void View::Draw_Connection(HDC hdc)
{
}

void View::Draw_Allocation(HDC hdc)
{



	HBRUSH ClozeBrush = CreateSolidBrush(RGB(128, 128, 255));	// Закрытая клетка
	HBRUSH OurShipBrush = CreateSolidBrush(RGB(255, 0, 255)); // Свой корабль
	wchar_t c[1];
	wchar_t num[1];
	c[0] = 'A';
	num[0] = '0';
	for (int vertical = 0; vertical < 10; vertical++)
	{
		TextOut(hdc, MARGIN_LEFT - CELL_SIZE / 2, MARGIN_TOP + vertical * CELL_SIZE + CELL_SIZE / 4, (LPCSTR)c, 1);
		//DrawText(hdc, (LPCSTR)c, cchText, lprc, format);

		c[0]++;
		for (int horizontal = 0; horizontal < 10; horizontal++)
		{
			if (vertical == 0)
			{
				TextOut(hdc, MARGIN_LEFT + horizontal * CELL_SIZE + CELL_SIZE / 3, MARGIN_TOP - CELL_SIZE / 2, (LPCSTR)num, 1);
				num[0]++;
			}
			int left = horizontal * CELL_SIZE + MARGIN_LEFT;
			int top = vertical * CELL_SIZE + MARGIN_TOP;
			int right = left + CELL_SIZE;
			int bottom = vertical * CELL_SIZE + CELL_SIZE + MARGIN_TOP;

			SelectBrush(hdc, ClozeBrush);
			switch (_Model->field_my[horizontal][vertical])
			{
			case empt: SelectBrush(hdc, ClozeBrush); break;
			case located: SelectBrush(hdc, OurShipBrush); break;
			default:
				break;
			}

			Rectangle(hdc, left, top, right, bottom);

		}
	}
	DeleteBrush(ClozeBrush);
	DeleteBrush(OurShipBrush);
}


