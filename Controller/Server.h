#ifndef SERVER_H
#define SERVER_H
#include "Controller.h"

using namespace std;

class Server : public Controller
{
	SOCKET sListen;
	SOCKET Connection;
public:
	Server();
	~Server();
	bool sended();
	bool recved();
};

#endif
