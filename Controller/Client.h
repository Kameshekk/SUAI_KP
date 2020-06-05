#ifndef CLIENT_H
#define CLIENT_H
#include "Controller.h"

using namespace std;

class Client : public Controller
{
	SOCKET sListen;
public:
	Client();
	~Client();
	bool sended();
	bool recved();

};

#endif
