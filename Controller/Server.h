#ifndef SERVER_H
#define SERVER_H
#include "Controller.h"

using namespace std;

class Server : public Controller
{
	SOCKET sListen;
	SOCKET Connection;
	Model* _Model;
public:
	Server(Model* _Model_of_game);
	~Server();
	bool sended();
	bool recved();
	void ClickLeft(int x, int y);
	void Located(int** field, int x, int y);
	int Hit(int** field, int x, int y);
	int check_on_kill(int field[10][10], int x, int y);
	void kills(char who, int x, int y);
};

#endif
