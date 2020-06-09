#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model.h"
#include <iostream>

using namespace std;

enum State_of_game 
{
	start,
	connection,	// Подключение
	allocation,	// Расстановка
	mov,		// Ход
	wait,		// Ожидание
	win,		// Победа
	lose		// Поражение
};

class Controller
{
protected:
	State_of_game state;
	SOCKET Connect;
	int stay;
	int ships;
	int installed;
	int prevx1;
	int prevy1;
	int prevx2;
	int prevy2;
	int prevx3;
	int prevy3;
	SOCKADDR_IN address;
	SOCKET Connection;
	Model* _Model;
	
	static Controller* instance;

public:
	Controller();
	~Controller();
	State_of_game get_state();
	void set_state(State_of_game _state);
	virtual bool sended() = 0;
	virtual bool recved() = 0;
	virtual void Located(int** field, int x, int y) = 0;
	virtual int Hit(int** field, int x, int y) = 0;
	void Reset();
	virtual void ClickLeft(int x, int y) = 0;

	//virtual void ClickRight(int x, int y);
};


#endif