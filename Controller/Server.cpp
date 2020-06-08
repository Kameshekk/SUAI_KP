#include "Server.h"

Server::Server(Model* _Model_of_game)
{
	_Model = _Model_of_game;
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

//	Connection = accept(sListen, (SOCKADDR*)&address, &size_of_address);
	if (Connection)
		cout << "++" << endl;
	else
		cout << "error" << endl;
}

Server::~Server()
{
	_Model = nullptr;
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

void Server::ClickLeft(int x, int y)
{
	/*if (state == allocation)
	{
		int vertical = ((y - MARGIN_TOP) / CELL_SIZE);
		int horisontal = ((x - MARGIN_LEFT) / CELL_SIZE);
		if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10)
			return;
	}
	else
	{
		int vertical = ((y - MARGIN_TOP) / CELL_SIZE);
		int horisontal = ((x - 2 * MARGIN_LEFT - 10 * CELL_SIZE) / CELL_SIZE);
		if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10)
			return;

		if (state == 1)
		{
			if (Hit(_Model->field_client, horisontal, vertical))
				state = wait;
		}
	}*/
	int vertical = ((y - MARGIN_TOP) / CELL_SIZE);
	int horisontal = ((x - MARGIN_LEFT) / CELL_SIZE);
	if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10 || x < MARGIN_LEFT || y < MARGIN_TOP)
		return;
	Hit(_Model->field_server, horisontal, vertical);

}

void Server::OnServerField(int vertical, int horisontal)
{
}

int Server::Hit(int** field, int x, int y)
{
	/*if (field[x][y] == located)
	{
		field[x][y] = damaged;
		return 1;
	}
	if (field[x][y] == 0)
	{
		field[x][y] = miss;
		return 0;
	}*/
	switch (field[x][y])
	{
	case empt: _Model->set_on_field('s', x, y, 1); break;
	case located: _Model->set_on_field('s', x, y, 2); break;
	case damaged: _Model->set_on_field('s', x, y, 3); break;
	case miss: _Model->set_on_field('s', x, y, 4); break;
	case kill: _Model->set_on_field('s', x, y, 0); break;
	default:
		break;
	}
	return 1;
}
