#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

enum State_of_game {
	// Начало игры
	allocation,
	// Игра идёт
	move,
	wait,
	// Игра завершена успешно
	win,
	// Игра завершена неудачно
	lose
};


class Controller
{
protected:
	// состояние игры
	State_of_game state;

	SOCKET Connect;

	SOCKADDR_IN address;
	SOCKET Connection;

	static Controller* instance;

	//Model* Model_of_game;

public:
	// создаёт и инициализирует новый игровой контекст
	Controller();
	// освобождает занятые ресурсы
	~Controller();
	// единственный экземпляр класса

	virtual bool sended() = 0;
	virtual bool recved() = 0;
};


#endif