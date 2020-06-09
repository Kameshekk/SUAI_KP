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
	void Draw_Allocation(HDC hdc);
	void Draw_Move(HDC hdc);
	void Draw_Wait(HDC hdc);
	void Draw_Win(HDC hdc);
	void Draw_Lose(HDC hdc);
};


#endif