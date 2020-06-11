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
	Model* _Model;
public:
	// Создаёт и иницализирует новый экзамемпляр интерфейса
	View(Model* _Model_of_game);
	~View();
	// Отображает игровое поле в указанном графическом контексте
	void Draw_Start(HDC hdc);
	void Draw_Wait_Connection(HDC hdc, RECT& rect);
	void Draw_Connection(HDC hdc, RECT& rect);
	void Draw_Allocation(HDC hdc);
	void Draw(HDC hdc, RECT& rect, char select);
	void Draw_Win(HDC hdc, RECT& rect);
	void Draw_Lose(HDC hdc, RECT& rect);
};


#endif