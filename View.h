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
	void Draw(HDC hdc);

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