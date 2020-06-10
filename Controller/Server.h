#ifndef SERVER_H
#define SERVER_H
#include "Controller.h"

using namespace std;

class Server : public Controller
{
	SOCKET sListen;
	SOCKET Connection;
public:
	Server(Model* _Model_of_game);
	~Server();
	void conect();
	bool sended(char* msg);
	bool recved();
	int ClickLeft(int x, int y);
	int Located(int** field, int x, int y);
	void Send_Model(Model* Model);
	void Recv_Model(Model* Model);
	void ready();
	int Hit(int** field, int x, int y, char who);
	void moving(int x, int y);
	void waiting();
	int check_on_kill(int field[10][10], int x, int y);
};

#endif
