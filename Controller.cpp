#include "Controller.h"

Controller::Controller()
{

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if ((WSAStartup(DLLVersion, &wsaData)) != 0)
	{
		cout << "err" << endl;
		exit(1);
	}
	address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9999);
	address.sin_family = AF_INET;

	int size_of_address = sizeof(address);

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&address, size_of_address);
	listen(sListen, SOMAXCONN);

	newConnection = accept(sListen, (SOCKADDR*)&address, &size_of_address);
	if (newConnection)
		cout << "++" << endl;
	else
		cout << "error" << endl;

	
}

Controller::~Controller()
{
}

void Controller::sended()
{
	char msg[256] = "Hello world \n";
	if (newConnection)
		system("pause");
	else
		system("pause");
	send(newConnection, msg, sizeof(msg), NULL);
}
