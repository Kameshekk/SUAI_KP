#include "Model.h"

Model::Model(HWND _hWnd)
{
	hWnd = _hWnd;
	heals_my = 0;
	heals_his = 20;
	field_my = new int*[10];
	for (int i = 0; i < 10; i++)
	{
		field_my[i] = new int[10];
		for (int j = 0; j < 10; j++)
			field_my[i][j] = empt;
	}

	field_his = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		field_his[i] = new int[10];
		for (int j = 0; j < 10; j++)
			field_his[i][j] = empt;
	}
}


Model::~Model()
{
	for (int i = 0; i < 10; i++)
		delete[] field_my[i];
	delete[] field_my;

	for (int i = 0; i < 10; i++)
		delete[] field_his[i];
	delete[] field_his;
}

bool Model::check()
{
	int ship_4x = 1;
	int ship_3x = 2;
	int ship_2x = 3;
	int ship_1x = 4;
	return false;
}

void Model::set_heals(char who, int health)
{
	switch (who)
	{
	case 'm': heals_my = health; break;
	case 'h': heals_his = health; break;
	default:
		break;
	}
}

int Model::get_heals(char who)
{
	switch (who)
	{
	case 'm': return heals_my; break;
	case 'h': return heals_his; break;
	default:
		break;
	}
	return 0;
}

int Model::set_on_field(char who, int horizontal, int vertical, int set_cell)
{
	int tmp = 0;
	switch (who)
	{
	case 'm': 
		tmp = field_my[horizontal][vertical];
		field_my[horizontal][vertical] = set_cell;
		break;
	case 'h':
		tmp = field_his[horizontal][vertical];
		field_his[horizontal][vertical] = set_cell;
		break;
	default:
		return -1;
		break;
	}
	UpdateWindow(hWnd);
	return tmp;
}

int Model::get_from_field(char who, int horizontal, int vertical)
{
	if (horizontal < 0 || vertical < 0 || horizontal > 9 || vertical > 9)
		return empt;
	switch (who)
	{
	case 'm':
		return (field_my[horizontal][vertical]);
		break;
	case 'h':
		return (field_his[horizontal][vertical]);;
		break;
	default:
		return -1;
		break;
	}
}
