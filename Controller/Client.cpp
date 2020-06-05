#include "Client.h"

Client::Client()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);

	if ((WSAStartup(DLLVersion, &wsaData)) != 0)
	{
		cout << "err" << endl;
		exit(1);
	}

	SOCKADDR_IN address;
	char IPadress[16];
	cout << "Server's adress: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cin.getline(IPadress, sizeof(IPadress));
	address.sin_addr.S_un.S_addr = inet_addr(IPadress);
	address.sin_port = htons(9999);
	address.sin_family = AF_INET;

	int size_of_address = sizeof(address);

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&address, size_of_address))
		cout << "Error" << endl;
	else
		cout << "Connect" << endl;
}

Client::~Client()
{
}

bool Client::sended()
{
	char msg[256];
	cin.clear();
	cin.getline(msg, sizeof(msg));
	send(Connection, msg, sizeof(msg), NULL);
	if (strcmp(msg, "STOP"))
		return 1;
	else return 0;
}

bool Client::recved()
{
	char msg[256];
	int x = recv(Connection, msg, sizeof(msg), NULL);
	cout << msg << endl;
	if (strcmp(msg, "STOP"))
		return 1;
	else return 0;
}


