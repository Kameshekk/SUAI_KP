#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

enum State_of_game {
	// ������ ����
	allocation,
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
protected:
	// ��������� ����
	State_of_game state;

	SOCKET Connect;

	SOCKADDR_IN address;
	SOCKET Connection;

	static Controller* instance;

	//Model* Model_of_game;

public:
	// ������ � �������������� ����� ������� ��������
	Controller();
	// ����������� ������� �������
	~Controller();
	// ������������ ��������� ������

	virtual bool sended() = 0;
	virtual bool recved() = 0;
};


#endif