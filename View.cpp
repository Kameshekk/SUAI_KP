#include "View.h"


View::View(Model* _Model_of_game)
{
	_Model = _Model_of_game;
}

void View::Draw(HDC hdc)
{


	HBRUSH ClozeBrush = CreateSolidBrush(RGB(128, 128, 255));	// Закрытая клетка
	HBRUSH OurShipBrush = CreateSolidBrush(RGB(255, 0, 255)); // Свой корабль
	HBRUSH EnemyShipBrush = CreateSolidBrush(RGB(255, 0, 0));	// Вражеский корабль
	HBRUSH HitOfOurShip = CreateSolidBrush(RGB(255, 128, 0));	// Поврежденный свой
	HBRUSH HitOfEnemyShip = CreateSolidBrush(RGB(64, 64, 0));	// Поврежденный вражеский
	HBRUSH KillOfOurShip = CreateSolidBrush(RGB(20, 120, 20));	// Потопленный свой
	HBRUSH KillOfEnemyShip = CreateSolidBrush(RGB(120, 20, 20));	// Потопленный вражеский
	HBRUSH MissBrush = CreateSolidBrush(RGB(0, 192, 64));	// Промах

	for (int vertical = 0; vertical < 10; vertical++) {
		for (int horizontal = 0; horizontal < 10; horizontal++) {
			int left = horizontal * CELL_SIZE + MARGIN_LEFT;
			int top = vertical * CELL_SIZE + MARGIN_TOP;
			int right = horizontal * CELL_SIZE + CELL_SIZE + MARGIN_LEFT;
			int bottom = vertical * CELL_SIZE + CELL_SIZE + MARGIN_TOP;

			SelectBrush(hdc, ClozeBrush);
			switch (_Model->field_server[horizontal][vertical])
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
}


