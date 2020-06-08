#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model.h"
#include <iostream>

using namespace std;

enum State_of_game 
{
	connection,	// �����������
	allocation,	// �����������
	move,		// ���
	wait,		// ��������
	win,		// ������
	lose		// ���������
};


class Controller
{
protected:
	// ��������� ����
	State_of_game state;

	SOCKET Connect;

	SOCKADDR_IN address;
	SOCKET Connection;

	static Controller* instance;

public:
	Controller();
	~Controller();

	virtual bool sended() = 0;
	virtual bool recved() = 0;

	virtual void ClickLeft(int x, int y) = 0;

	//virtual void ClickRight(int x, int y);
};


#endif