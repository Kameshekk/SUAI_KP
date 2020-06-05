#include "Server.h"

Server::Server()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if ((WSAStartup(DLLVersion, &wsaData)) != 0)
	{
		cout << "err" << endl;
		exit(1);
	}
	char IPadress[16];
	cout << "Server's adress: "; 
	cin.clear(); 
	cin.ignore(INT_MAX, '\n');
	cin.getline(IPadress, sizeof(IPadress));
	address.sin_addr.S_un.S_addr = inet_addr(IPadress);
	address.sin_port = htons(9999);
	address.sin_family = AF_INET;

	int size_of_address = sizeof(address);

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&address, size_of_address);
	listen(sListen, SOMAXCONN);

	Connection = accept(sListen, (SOCKADDR*)&address, &size_of_address);
	if (Connection)
		cout << "++" << endl;
	else
		cout << "error" << endl;
}

Server::~Server()
{
}

bool Server::sended()
{
	char msg[256];
	cin.clear();
	cin.getline(msg, sizeof(msg));
	send(Connection, msg, sizeof(msg), NULL);
	if (strcmp(msg,"STOP"))
		return 1;
	else return 0;
}

bool Server::recved()
{
	char msg[256];
	recv(Connection, msg, sizeof(msg), NULL);
	cout << msg << endl;
	if (strcmp(msg, "STOP"))
		return 1;
	else return 0;
}
