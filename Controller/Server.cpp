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


	const char* google_dns_server = "8.8.8.8";
	int dns_port = 53;

	struct sockaddr_in serv;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("Socket error");
	}

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(google_dns_server);
	serv.sin_port = htons(dns_port);

	int err = connect(sock, (const struct sockaddr*) & serv, sizeof(serv));

	struct sockaddr_in name;
	socklen_t namelen = sizeof(name);
	err = getsockname(sock, (struct sockaddr*) & name, &namelen);
	const char* p = inet_ntop(AF_INET, &name.sin_addr, IPadress, 100);

	if (p != NULL)
	{
		printf("Local ip is : %s \n", IPadress);
	}
	else
	{
		//Some error
		printf("Error number : %d . Error message : %s \n", errno, strerror(errno));
	}

	//close(sock);






	cout << "Server's adress: " << IPadress; 
	//cin.clear(); 
	//cin.ignore(INT_MAX, '\n');
	//cin.getline(IPadress, sizeof(IPadress));
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
	cin.ignore(0, '\n');
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
