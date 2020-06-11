#ifndef CLIENT_H
#define CLIENT_H
#include "Controller.h"

using namespace std;

class Client : public Controller
{
	SOCKET sListen;
public:
	Client(Model* _Model);
	~Client();
	void conect();
	bool sended(char* msg);
	int Located(int** field, int x, int y);
	void Send_Model(Model* Model);
	void Recv_Model(Model* Model);
	void moving(int x, int y);
	void waiting();
	void ready();
	int ClickLeft(int x, int y);

};

#endif
