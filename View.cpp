#include "View.h"


View::View(Model* _Model_of_game)
{
	_Model = _Model_of_game;
}

void View::Draw(HDC hdc, RECT& rect, char select)
{


	HBRUSH ClozeBrush = CreateSolidBrush(RGB(135, 206, 250));	// Закрытая клетка
	HBRUSH OurShipBrush = CreateSolidBrush(RGB(0, 255, 0)); // Свой корабль
	HBRUSH HitOfOurShip = CreateSolidBrush(RGB(85, 107, 47));	// Поврежденный свой
	HBRUSH HitOfEnemyShip = CreateSolidBrush(RGB(255, 127, 80));	// Поврежденный вражеский
	HBRUSH KillOfOurShip = CreateSolidBrush(RGB(22, 44, 0));	// Потопленный свой
	HBRUSH KillOfEnemyShip = CreateSolidBrush(RGB(52, 0, 18));	// Потопленный вражеский
	HBRUSH MissBrush = CreateSolidBrush(RGB(0, 0, 255));	// Промах
	wchar_t c[1];
	wchar_t num[1];
	c[0] = 'A';
	num[0] = '0';
	for (int vertical = 0; vertical < 10; vertical++) 
	{
		TextOut(hdc, MARGIN_LEFT - CELL_SIZE / 2, MARGIN_TOP + vertical * CELL_SIZE + CELL_SIZE/4, (LPCSTR)c, 1);
		
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
			switch (_Model->get_from_field('m', horizontal, vertical))
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
			switch (_Model->get_from_field('h', horizontal, vertical))
			{
			case empt: SelectBrush(hdc, ClozeBrush); break;
			case damaged: SelectBrush(hdc, HitOfEnemyShip); break;
			case kill: SelectBrush(hdc, KillOfEnemyShip); break;
			case miss: SelectBrush(hdc, MissBrush); break;
			default:
				break;
			}

			Rectangle(hdc, left, top, right, bottom);

		}
	}
	HFONT hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	
	SelectObject(hdc, hFont);
	if(select == 'w')
		DrawText(hdc, "Wait", -1, &rect, DT_CENTER);
	else
		DrawText(hdc, "Move", -1, &rect, DT_CENTER);
	DeleteFont(hFont);

	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	
	SelectObject(hdc, hFont);
	DrawText(hdc, "\n\n\n\n\nHealth:", -1, &rect, DT_CENTER);
	DeleteFont(hFont);

	char Health_his[3];
	char Health[7];
	
	_itoa_s(_Model->get_heals('m'), Health, sizeof(Health), 10);
	_itoa_s(_Model->get_heals('h'), Health_his, sizeof(Health_his), 10);
	strcat(Health, ":");
	strcat(Health, Health_his);



	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	
	SelectObject(hdc, hFont);
	DrawText(hdc, Health, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteFont(hFont);

	DeleteBrush(ClozeBrush);
	DeleteBrush(OurShipBrush);
	DeleteBrush(HitOfOurShip);
	DeleteBrush(HitOfEnemyShip);
	DeleteBrush(KillOfOurShip);
	DeleteBrush(KillOfEnemyShip);
	DeleteBrush(MissBrush);
}


void View::Draw_Win(HDC hdc)
{
}

void View::Draw_Lose(HDC hdc)
{
}

void View::Draw_Start(HDC hdc)
{
	HBRUSH ServerBrush = CreateSolidBrush(RGB(128, 128, 240));
	HBRUSH ClientBrush = CreateSolidBrush(RGB(240, 128, 128));
	RECT Title;
	Title.left = WIDTH/2 - 200;
	Title.top = 0;
	Title.right = WIDTH/2 + 200;
	Title.bottom = Title.top + 210;
	HFONT hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	DrawText(hdc, "Let's Battle", -1, &Title, DT_CENTER);// Выводим текст управления для первой фигуры
	DeleteFont(hFont);

	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	DrawText(hdc, "\n\nChoose your role", -1, &Title, DT_CENTER);
	DeleteFont(hFont);

	RECT ButtonServer;
	ButtonServer.left = MARGIN_LEFT;
	ButtonServer.top = MARGIN_TOP;
	ButtonServer.right = ButtonServer.left + 10 * CELL_SIZE;
	ButtonServer.bottom = ButtonServer.top + 10 * CELL_SIZE;

	RECT ButtonClient;
	ButtonClient.left = ButtonServer.right + MARGIN_BETWEEN_FIELDS;
	ButtonClient.top = MARGIN_TOP;
	ButtonClient.right = ButtonClient.left + 10 * CELL_SIZE;
	ButtonClient.bottom = ButtonClient.top + 10 * CELL_SIZE;


	SelectObject(hdc, ServerBrush);
	Rectangle(hdc, MARGIN_LEFT, MARGIN_TOP, MARGIN_LEFT + 10 * CELL_SIZE, MARGIN_TOP + 10 * CELL_SIZE);
	SelectObject(hdc, ClientBrush);
	Rectangle(hdc, WIDTH - MARGIN_LEFT - 10 * CELL_SIZE, MARGIN_TOP, WIDTH - MARGIN_LEFT, MARGIN_TOP + 10 * CELL_SIZE);

	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	SetBkMode(hdc, 3);
	DrawText(hdc, "Server", -1, &ButtonServer, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteFont(hFont);
	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	SetBkMode(hdc, 3);
	DrawText(hdc, "Client", -1, &ButtonClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteFont(hFont);
	DeleteBrush(ServerBrush);
	DeleteBrush(ClientBrush);
}

void View::Draw_Wait_Connection(HDC hdc, RECT &rect)
{
	HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);
	DrawText(hdc, "Your IP-address: ", -1, &rect, DT_LEFT);
	DeleteFont(hFont);
	
	
	hFont = CreateFont(60, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);
	DrawText(hdc, _Model->get_IP(), -1, &rect, DT_CENTER);
	DeleteFont(hFont);

	hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);
	DrawText(hdc,"Waiting for the player to connect", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteFont(hFont);
}

void View::Draw_Connection(HDC hdc, RECT& rect)
{
	HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);
	DrawText(hdc, "Enter the server IP address", -1, &rect, DT_LEFT);
	DeleteFont(hFont);

	hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);
	DrawText(hdc, _Model->get_IP(), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteFont(hFont);
}

void View::Draw_Allocation(HDC hdc)
{
	HBRUSH ClozeBrush = CreateSolidBrush(RGB(135, 206, 250));	// Закрытая клетка
	HBRUSH OurShipBrush = CreateSolidBrush(RGB(0, 255, 0)); // Свой корабль
	wchar_t c[1];
	wchar_t num[1];
	c[0] = 'A';
	num[0] = '0';
	for (int vertical = 0; vertical < 10; vertical++)
	{
		TextOut(hdc, MARGIN_LEFT - CELL_SIZE / 2, MARGIN_TOP + vertical * CELL_SIZE + CELL_SIZE / 4, (LPCSTR)c, 1);
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
			switch (_Model->get_from_field('m', horizontal, vertical))
			{
			case empt: SelectBrush(hdc, ClozeBrush); break;
			case located: SelectBrush(hdc, OurShipBrush); break;
			default:
				break;
			}

			Rectangle(hdc, left, top, right, bottom);

		}
	}

	RECT Text;
	Text.left = MARGIN_LEFT + 10 * CELL_SIZE + 100;
	Text.top = MARGIN_TOP;
	Text.right = Text.left + 500;
	Text.bottom = Text.top + 210;

	HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold");	// Параметры текста (размер, шрифт и т.д.)
	SelectObject(hdc, hFont);//Выбираем обект
	DrawText(hdc, "1. Place a four-deck ship", -1, &Text, DT_LEFT);
	DrawText(hdc, "\n2. Place three-decked ships", -1, &Text, DT_LEFT);
	DrawText(hdc, "\n\n3. Place two-decked ships", -1, &Text, DT_LEFT);
	DrawText(hdc, "\n\n\n4. Place single-deck ships", -1, &Text, DT_LEFT);


	//HBRUSH ResetBrush = CreateSolidBrush(RGB(240, 128, 128));
	HBRUSH ResetBrush = CreateSolidBrush(RGB(240, 0, 50));
	SelectObject(hdc, ResetBrush);
	RECT ResetRect;
	ResetRect.left = Text.left;
	ResetRect.top = Text.bottom + 30;
	ResetRect.right = ResetRect.left + 100;
	ResetRect.bottom = ResetRect.top + 60;
	Rectangle(hdc, ResetRect.left, ResetRect.top, ResetRect.right, ResetRect.bottom);
	hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, VARIABLE_PITCH, "Arial Bold"); 
	SelectObject(hdc, hFont);
	SetBkMode(hdc, 3);
	DrawText(hdc, "RESET", -1, &ResetRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DeleteFont(hFont);
	DeleteBrush(ResetBrush);
	DeleteBrush(ClozeBrush);
	DeleteBrush(OurShipBrush);
}


