#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "Model.h"


#define WIDTH 900
#define HEIGHT 450

using namespace std;

enum State_of_game {
	// Начало игры
	ready,
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

	// состояние игры
	State_of_game state;
	
	SOCKET Connect;

	SOCKADDR_IN address;
	SOCKET sListen;
	SOCKET newConnection;

	Model* Model_of_game;

public:
	// создаёт и инициализирует новый игровой контекст
	Controller();
	// освобождает занятые ресурсы
	~Controller();
	// единственный экземпляр класса
	static Controller* instance;

	void sended();
};


#endif