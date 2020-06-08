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
	void OnServerField(int vertical, int horisontal);
	void OnClientField(int vertical, int horisontal);
	int Hit(int** field, int x, int y);
};

#endif
