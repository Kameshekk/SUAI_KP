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


	const char* google_dns_server = "8.8.8.8";
	int dns_port = 53;

	struct sockaddr_in serv;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		MessageBox(_Model->hWnd, "Socket error", NULL, NULL);
		exit(1);
	}

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(google_dns_server);
	serv.sin_port = htons(dns_port);

	int err = connect(sock, (const struct sockaddr*) & serv, sizeof(serv));

	struct sockaddr_in name;
	socklen_t namelen = sizeof(name);
	err = getsockname(sock, (struct sockaddr*) & name, &namelen);
	const char* p = inet_ntop(AF_INET, &name.sin_addr, _Model->IPaddress, 100);
	
}

Server::~Server()
{
	_Model = nullptr;
	closesocket(Connection);
}

void Server::conect()
{

	address.sin_addr.S_un.S_addr = inet_addr(_Model->IPaddress);
	address.sin_port = htons(9999);
	address.sin_family = AF_INET;
	int size_of_address = sizeof(address);

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&address, size_of_address);
	listen(sListen, SOMAXCONN);

	Connection = accept(sListen, (SOCKADDR*)&address, &size_of_address);
	if (WSAGetLastError())
	{
		MessageBox(_Model->hWnd, "Ñommunication is not established", NULL, NULL);
		exit(1);
	}
	state = allocation;
}

bool Server::sended(char* msg)
{
	send(Connection, msg, MESSAGE_BLOCK, NULL);
	if (strcmp(msg,"STOP"))
		return 1;
	else return 0;
}

int Server::ClickLeft(int x, int y)
{
	int vertical;
	int horisontal;

	switch (state)
	{
	case start:
	case allocation:
		if ((x > MARGIN_LEFT + 10 * CELL_SIZE + 100) && (x < MARGIN_LEFT + 10 * CELL_SIZE + 200) &&
			(y > MARGIN_TOP + 240) && (y < MARGIN_TOP + 300))
		{
			Reset();
			break;
		}
		vertical = ((y - MARGIN_TOP) / CELL_SIZE);
		horisontal = ((x - MARGIN_LEFT) / CELL_SIZE);
		if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10 || x < MARGIN_LEFT || y < MARGIN_TOP)
			return 0;
		if (Located(_Model->field_my, horisontal, vertical))
			return allocation;
		break;
	case mov:
		vertical = ((y - MARGIN_TOP) / CELL_SIZE);
		horisontal = ((x - MARGIN_LEFT - 10 * CELL_SIZE - MARGIN_BETWEEN_FIELDS) / CELL_SIZE);
		if (vertical < 0 || vertical >= 10 || horisontal < 0 || horisontal >= 10 || x < MARGIN_LEFT || y < MARGIN_TOP)
			return 0;
		moving(horisontal, vertical);
		break;
	case wait:  
		waiting();
		break;
	case win:  break;
	case lose:  break;
	default:
		break;

	}

}

int Server::Located(int** field, int x, int y)
{
	if (_Model->get_from_field('m', x, y) == located)
		return 0;
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
			return 0;
		if ((_Model->get_from_field('m', x - 1, y) == located) || (_Model->get_from_field('m', x, y - 1) == located) ||
			(_Model->get_from_field('m', x + 1, y) == located) || (_Model->get_from_field('m', x, y + 1) == located))
		{
			return 0;
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
		UpdateWindow(_Model->hWnd);
		if (ships == 10)
		{
			state = wait_game;
			return 1;
			//UpdateWindow(_Model->hWnd);
		}
		return 0;
	}

	if (installed == 1)
	{
		if (abs(prevx1 - x) > 1 || abs(prevy1 - y) > 1)
			return 0;
		if (abs(prevx1 - x) + abs(prevy1 - y) > 1)
			return 0;
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
			return 0;
		prevx2 = x;
		prevy2 = y;
		_Model->set_on_field('m', x, y, located);
		installed = 2;
		stay--;
		return 0;
	}

	if (installed == 2)
	{
		if ((abs(prevx1 - x) > 1 || abs(prevy1 - y) > 1) && (abs(prevx2 - x) > 1 || abs(prevy2 - y) > 1))
			return 0;
		if ((abs(prevx1 - x) + abs(prevy1 - y) > 1) && (abs(prevx2 - x) + abs(prevy2 - y)) > 1)
			return 0;
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
			return 0;
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
			return 0;
		}
	}
	if (installed == 3)
	{
		if ((abs(prevx1 - x) > 1 || abs(prevy1 - y) > 1) && (abs(prevx2 - x) > 1 || abs(prevy2 - y) > 1) && (abs(prevx3 - x) > 1 || abs(prevy3 - y) > 1))
			return 0;
		if ((abs(prevx1 - x) + abs(prevy1 - y) > 1) && (abs(prevx2 - x) + abs(prevy2 - y) > 1) && (abs(prevx3 - x) + abs(prevy3 - y)) > 1)
			return 0;
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
			return 0;
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
	return 0;
}

void Server::Send_Model(Model* Model)
{
	char msg[256];
	int z = 0;
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			msg[z++] = '0' + _Model->get_from_field('m', i, j);
		}
	}
	sended(msg);
}

void Server::Recv_Model(Model* Model)
{
	char msg[MESSAGE_BLOCK];
	int z = 0;
	//recv(Connection, msg, MESSAGE_BLOCK, NULL);
	msg[0] = -1;
	In_Recv* st_msg = new In_Recv(Connection, msg, MESSAGE_BLOCK, NULL);
	hThread = CreateThread(NULL, NULL, ((LPTHREAD_START_ROUTINE)recved), (st_msg), NULL, NULL);
	int i = 0;
	Sleep(100);
	while (msg[0] == -1)
	{
		Sleep(100);
		if (i == 500)
			i = 0; // Ïðîâåðèòü ïîäêëþ÷åíèå
		i++;
	}
	delete st_msg;
	CloseHandle(hThread);
	if (WSAGetLastError())
	{
		MessageBox(_Model->get_HWND(), "Disconnect", NULL, NULL);
		exit(1);
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			_Model->set_on_field('h', i, j, msg[z++] - '0');

	msg_in[0] = -1;
	state = wait;
}

void Server::ready()
{
	_Model->set_heals('m', 20);
	char msg[MESSAGE_BLOCK] = "READY";
	send(Connection, msg, MESSAGE_BLOCK, NULL);
	recv(Connection, msg, sizeof(msg), NULL);
	if (WSAGetLastError())
	{
		MessageBox(_Model->hWnd, "Disconnect", NULL, NULL);
		exit(1);
	}
	Recv_Model(_Model);
	msg_in[0] = -1;
	state = mov;
}


int Server::Hit(int** field, int x, int y, char who)
{
	int flag = 0;
	switch (field[x][y])
	{
	case empt: _Model->set_on_field(who, x, y, miss); flag = 0; break;
	case located: _Model->set_on_field(who, x, y, damaged);
		int copy_field[10][10];
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				copy_field[i][j] = field[i][j];
		if (check_on_kill(copy_field, x, y))
		{
			kills(who, x, y);
			flag = 2;
		}
		else
			flag = 1; 
		break;
	default:
		break;
	}
	//flag = 1;
	return flag;
}

void Server::moving(int x, int y)
{
	if ((_Model->field_his[x][y] == kill) || (_Model->field_his[x][y] == damaged) || (_Model->field_his[x][y] == miss))
		return;
	char msg_out[MESSAGE_BLOCK];
	msg_out[1] = x + '0';
	msg_out[2] = y + '0';
	switch (Hit(_Model->field_his, x, y, 'h'))
	{
	case 0:
		msg_out[0] = '0';
		sended(msg_out);
		state = wait;
		break;
	case 1:
		msg_out[0] = '1';
		sended(msg_out);
		_Model->heals_his--;
		break;
	case 2:
		msg_out[0] = '2';
		sended(msg_out);
		_Model->heals_his--;
		break;
	}
	if (_Model->heals_his == 0)
		state = win;
}

void Server::waiting()
{
	int x = -1, y = -1;
	char msg_out[MESSAGE_BLOCK];
	//recv(Connection, msg_in, MESSAGE_BLOCK, NULL);
	In_Recv* st_msg = new In_Recv(Connection, msg_in, MESSAGE_BLOCK, NULL);
	if (flag_waitrecv == 0)
		hThread = CreateThread(NULL, NULL, ((LPTHREAD_START_ROUTINE)recved), (st_msg), NULL, NULL);
	int i = 0;
	Sleep(100);
	if ((msg_in[0] < '0') || (msg_in[0] > '9'))
	{
		flag_waitrecv = 1;
		return;
	}
	else
	{
		flag_waitrecv = 0;
		CloseHandle(hThread);
	}
	if (WSAGetLastError())
	{
		MessageBox(_Model->get_HWND(), "Disconnect", NULL, NULL);
		exit(1);
	}
	x = msg_in[0] - '0';
	y = msg_in[1] - '0';
	switch (Hit(_Model->field_my, x, y, 'm'))
	{
	case 0:
		msg_out[0] = '0';
		sended(msg_out);
		state = mov;
		break;
	case 1:
		msg_out[0] = '1';
		sended(msg_out);
		_Model->heals_my--;
		break;
	case 2:
		msg_out[0] = '2';
		sended(msg_out);
		_Model->heals_my--;
		break;
	}
	msg_in[0] = -1;
	if (_Model->heals_my == 0)
		state = lose;
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

