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
			if (Hit(_Model->field_his, horisontal, vertical))
				state = wait;
		}
	}*/
	int vertical;
	int horisontal;

	switch (state)
	{
	case start: 
		break;
	case connection:  break;
	case allocation:   
		vertical = ((y - MARGIN_TOP) / CELL_SIZE);
		horisontal = ((x - MARGIN_LEFT) / CELL_SIZE);
		if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10 || x < MARGIN_LEFT || y < MARGIN_TOP)
			return;
		Located(_Model->field_my, horisontal, vertical);
		break;
	case mov:
		vertical = ((y - MARGIN_TOP) / CELL_SIZE);
		horisontal = ((x - MARGIN_LEFT - 10 * CELL_SIZE - MARGIN_BETWEEN_FIELDS) / CELL_SIZE);
		if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10 || x < MARGIN_LEFT || y < MARGIN_TOP)
			return;
		Hit(_Model->field_his, horisontal, vertical);
		break;
	case wait:  break;
	case win:  break;
	case lose:  break;
	default:
		break;
	}

}

void Server::Located(int** field, int x, int y)
{
	if (stay == 0)
	{
		int cnt = 0;
		if (_Model->get_from_field('m', x - 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x, y + 1) == located) cnt++;
		if (_Model->get_from_field('m', x - 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x - 1, y + 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y + 1) == located) cnt++;
		if (cnt > 0)
			return;
		if ((_Model->get_from_field('m', x - 1, y) == located) || (_Model->get_from_field('m', x, y - 1) == located) ||
			(_Model->get_from_field('m', x + 1, y) == located) || (_Model->get_from_field('m', x, y + 1) == located))
		{
			return;
		}
		switch (ships)
		{
		case 0: stay = 4; break;
		case 1: stay = 3; break;
		case 2: stay = 3; break;
		case 3: stay = 2; break;
		case 4: stay = 2; break;
		case 5: stay = 2; break;
		case 6: stay = 1; break;
		case 7: stay = 1; break;
		case 8: stay = 1; break;
		case 9: stay = 1; break;
		case 10: 
			_Model->set_heals('m', 20);
			state = allocation;
			break;
		default:
			break;
		}
		
		_Model->set_on_field('m', x, y, located);
		prevx1 = x;
		prevy1 = y;
		installed = 1;
		stay--;
		ships++;
		return;
	}

	if (installed == 1)
	{
		if (abs(prevx1 - x) > 1 || abs(prevy1 - y) > 1)
			return;
		if (abs(prevx1 - x) + abs(prevy1 - y) > 1)
			return;
		int cnt = 0;
		if (_Model->get_from_field('m', x - 1, y) == located) cnt++; 
		if (_Model->get_from_field('m', x + 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x, y + 1) == located) cnt++;
		if (_Model->get_from_field('m', x - 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x - 1, y + 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y + 1) == located) cnt++;
		if (cnt > 1)
			return;
		prevx2 = x;
		prevy2 = y;
		_Model->set_on_field('m', x, y, located);
		installed = 2;
		stay--;
		return;
	}

	if (installed == 2)
	{
		if ((abs(prevx1 - x) > 1 || abs(prevy1 - y) > 1) && (abs(prevx2 - x) > 1 || abs(prevy2 - y) > 1))
			return;
		if ((abs(prevx1 - x) + abs(prevy1 - y) > 1) && (abs(prevx2 - x) + abs(prevy2 - y)) > 1)
			return;
		int cnt = 0;
		if (_Model->get_from_field('m', x - 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x, y + 1) == located) cnt++;

		if (_Model->get_from_field('m', x - 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x - 1, y + 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y + 1) == located) cnt++;
		if (cnt > 1)
			return;
		int flag = 0;
		if ((_Model->get_from_field('m', x - 2, y) == located) && (_Model->get_from_field('m', x - 1, y) == located) ||
			(_Model->get_from_field('m', x + 2, y) == located) && (_Model->get_from_field('m', x + 1, y) == located) ||
			(_Model->get_from_field('m', x, y - 2) == located) && (_Model->get_from_field('m', x, y - 1) == located) ||
			(_Model->get_from_field('m', x, y + 2) == located) && (_Model->get_from_field('m', x, y + 1) == located))

		{
			prevx3 = x;
			prevy3 = y;
			_Model->set_on_field('m', x, y, located);
			installed = 3;
			stay--;
			return;
		}
	}
	if (installed == 3)
	{
		if ((abs(prevx1 - x) > 1 || abs(prevy1 - y) > 1) && (abs(prevx2 - x) > 1 || abs(prevy2 - y) > 1) && (abs(prevx3 - x) > 1 || abs(prevy3 - y) > 1))
			return;
		if ((abs(prevx1 - x) + abs(prevy1 - y) > 1) && (abs(prevx2 - x) + abs(prevy2 - y) > 1) && (abs(prevx3 - x) + abs(prevy3 - y)) > 1)
			return;
		int cnt = 0;
		if (_Model->get_from_field('m', x - 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y) == located) cnt++;
		if (_Model->get_from_field('m', x, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x, y + 1) == located) cnt++;

		if (_Model->get_from_field('m', x - 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y - 1) == located) cnt++;
		if (_Model->get_from_field('m', x - 1, y + 1) == located) cnt++;
		if (_Model->get_from_field('m', x + 1, y + 1) == located) cnt++;
		if (cnt > 1)
			return;
		int flag = 0;
		if ((_Model->get_from_field('m', x - 2, y) == located) && (_Model->get_from_field('m', x - 1, y) == located) ||
			(_Model->get_from_field('m', x + 2, y) == located) && (_Model->get_from_field('m', x + 1, y) == located) ||
			(_Model->get_from_field('m', x, y - 2) == located) && (_Model->get_from_field('m', x, y - 1) == located) ||
			(_Model->get_from_field('m', x, y + 2) == located) && (_Model->get_from_field('m', x, y + 1) == located))

		{
			prevx3 = x;
			prevy3 = y;
			_Model->set_on_field('m', x, y, located);
			installed++;
			stay--;
		}
	}
}

int Server::Hit(int** field, int x, int y)
{
	switch (field[x][y])
	{
	case empt: _Model->set_on_field('h', x, y, located); return 0; break;
	case located: _Model->set_on_field('h', x, y, damaged); 
		int copy_field[10][10];
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				copy_field[i][j] = field[i][j];
		if (check_on_kill(copy_field, x, y))
			kills('h', x, y);

		return 1; break;
	case damaged: _Model->set_on_field('h', x, y, damaged); break;	// Невозможно
	case miss: _Model->set_on_field('h', x, y, miss); break;	// Невозможно
	case kill: _Model->set_on_field('h', x, y, kill); break;	// Невозможно
	default:
		break;
	}
	return 1;
}

int Server::check_on_kill(int field[10][10], int x, int y)
{
	if (field[x][y] == damaged)
		field[x][y] = kill;
	if (x > 0)
		if (field[x - 1][y] == located)
			return 0;
	if (x < 9)
		if (field[x + 1][y] == located)
			return 0;
	if (y > 0)
		if (field[x][y - 1] == located)
			return 0;
	if (y < 9)
		if (field[x][y + 1] == located)
			return 0;
	int xup = 1, xdown = 1, yup = 1, ydown = 1;

	if (field[x - 1][y] == damaged)
		xdown = check_on_kill(field, x - 1, y);
	if (field[x + 1][y] == damaged)
		xup = check_on_kill(field, x + 1, y);
	if (field[x][y - 1] == damaged)
		yup = check_on_kill(field, x, y - 1);
	if (field[x][y + 1] == damaged)
		ydown = check_on_kill(field, x, y + 1);
	if (xup == 0 || xdown == 0 || yup == 0 || ydown == 0)
		return 0;
	else return 1;
	return 1;
}

void Server::kills(char who, int x, int y)
{
	//if (_Model->get_from_field(x - 1, y, who) == located)
		
	_Model->set_on_field(who, x, y, kill);
	if (_Model->get_from_field(who, x - 1, y) == damaged)
		kills(who, x - 1, y);
	if (_Model->get_from_field(who, x + 1, y) == damaged)
		kills(who, x + 1, y);
	if (_Model->get_from_field(who, x, y - 1) == damaged)
		kills(who, x, y - 1);
	if (_Model->get_from_field(who, x, y + 1) == damaged)
		kills(who, x, y + 1);
	return;
}
