#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "Model.h"


#define WIDTH 900
#define HEIGHT 450

using namespace std;

enum State_of_game {
	// ������ ����
	ready,
	// ���� ���
	move,
	wait,
	// ���� ��������� �������
	win,
	// ���� ��������� ��������
	lose
};


class Controller
{

	// ��������� ����
	State_of_game state;
	
	SOCKET Connect;

	SOCKADDR_IN address;
	SOCKET sListen;
	SOCKET newConnection;

	Model* Model_of_game;

public:
	// ������ � �������������� ����� ������� ��������
	Controller();
	// ����������� ������� �������
	~Controller();
	// ������������ ��������� ������
	static Controller* instance;

	void sended();
};


#endif