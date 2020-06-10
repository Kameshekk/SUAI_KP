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
	// ������ ������ � ��������
	int size_cell;
	// ������� ��������
	Model* _Model;
public:
	// ������ � ������������� ����� ����������� ����������
	View(Model* _Model_of_game);
	~View();
	// ���������� ������� ���� � ��������� ����������� ���������
	void Draw_Start(HDC hdc);
	void Draw_Wait_Connection(HDC hdc, RECT& rect);
	void Draw_Connection(HDC hdc, RECT& rect);
	void Draw_Allocation(HDC hdc);
	void Draw(HDC hdc, RECT& rect, char select);
	void Draw_Wait(HDC hdc);
	void Draw_Win(HDC hdc);
	void Draw_Lose(HDC hdc);
	// ������������ ������� �� ����� ������ ����
	void ClickLeft(int x, int y);
	// ������������ ������� �� ������ ������ ����
	void ClickRight(int x, int y);

	// ���������� ����������� ������ ������������ ���������
	int GetWidth();
	// ���������� ����������� ������ ������������ ���������
	int GetHeight();
};


#endif