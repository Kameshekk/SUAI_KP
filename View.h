#pragma once
#ifndef VIEW_H
#define VIEW_H
#include "Model.h"
#include <iostream>
#include <Windows.h>
#include <windowsx.h>

using namespace std;


class View
{
	int width = WIDTH;
	// размер клетки в пикселях
	int size_cell;
	// Игровой контекст
	Model* _Model;
public:
	// Создаёт и иницализирует новый экзамемпляр интерфейса
	View(Model* _Model_of_game);
	~View();
	// Отображает игровое поле в указанном графическом контексте
	void Draw_Start(HDC hdc, RECT& rect);
	void Draw_Connection(HDC hdc);
	void Draw_Allocation(HDC hdc, RECT& rect);
	void Draw_Move(HDC hdc);
	void Draw_Wait(HDC hdc);
	void Draw_Win(HDC hdc);
	void Draw_Lose(HDC hdc);
	// Обрабатывает нажатие на левую кнопку мыши
	void ClickLeft(int x, int y);
	// Обрабатывает нажатие на правую кнопку мыши
	void ClickRight(int x, int y);

	// Возвращает необходимую ширину графического контекста
	int GetWidth();
	// Возвращает необходимую высоту графического контекста
	int GetHeight();
};


#endif