#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model.h"
#include <iostream>

#define MESSAGE_BLOCK 256

using namespace std;

enum State_of_game
{
	start,
	connection,	// Подключение
	wait_connection,
	wait_game,
	allocation,	// Расстановка
	mov,		// Ход
	wait,		// Ожидание
	win,		// Победа
	lose		// Поражение
};

struct In_Recv
{
	SOCKET sock;
	char* msg;
	int lenght;
	int flags;
	In_Recv(SOCKET _sock, char* _msg, int _lenght, int _flags);
	~In_Recv();
};


void recved(In_Recv* st_msg);

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
	int flag_waitrecv;
	static Controller* instance;
	HANDLE hThread;
	char msg_in[MESSAGE_BLOCK];

public:
	Controller();
	~Controller();
	State_of_game get_state();
	void set_state(State_of_game _state);
	virtual void conect() = 0;
	virtual bool sended(char* msg) = 0;
	virtual int Located(int** field, int x, int y) = 0;
	virtual void Send_Model(Model* Model) = 0;
	virtual void Recv_Model(Model* Model) = 0;
	virtual void ready() = 0;
	virtual void moving(int x, int y) = 0;
	virtual void waiting() = 0;
	void Reset();
	virtual int ClickLeft(int x, int y) = 0;
	void kills(char who, int x, int y);
};


#endif