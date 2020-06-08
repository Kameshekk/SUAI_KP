#include "Model.h"

Model::Model(HWND _hWnd)
{
	hWnd = _hWnd;
	heals_server = 20;
	heals_client = 20;
	field_server = new int*[10];
	for (int i = 0; i < 10; i++)
	{
		field_server[i] = new int[10];
		for (int j = 0; j < 10; j++)
			field_server[i][j] = empt;
	}

	field_client = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		field_client[i] = new int[10];
		for (int j = 0; j < 10; j++)
			field_client[i][j] = empt;
	}
}


Model::~Model()
{
	for (int i = 0; i < 10; i++)
		delete[] field_server[i];
	delete[] field_server;

	for (int i = 0; i < 10; i++)
		delete[] field_client[i];
	delete[] field_client;
}

bool Model::check()
{
	int ship_4x = 1;
	int ship_3x = 2;
	int ship_2x = 3;
	int ship_1x = 4;
	return false;
}

int Model::set_on_field(char who, int horizontal, int vertical, int set_cell)
{
	int tmp = 0;
	switch (who)
	{
	case 's': 
		tmp = field_server[horizontal][vertical];
		field_server[horizontal][vertical] = set_cell;
		break;
	case 'c':
		tmp = field_server[horizontal][vertical];
		field_server[horizontal][vertical] = set_cell;
		break;
	default:
		return -1;
		break;
	}
	UpdateWindow(hWnd);
	return tmp;
}
