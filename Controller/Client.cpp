#include "Client.h"


Client::Client(Model* _Model_of_game)
{
	_Model = _Model_of_game;
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);

	if ((WSAStartup(DLLVersion, &wsaData)) != 0)
	{
		cout << "err" << endl;
		exit(1);
	}

}

Client::~Client()
{
	_Model = nullptr;
	closesocket(Connection);
}

void Client::conect()
{
	address.sin_addr.S_un.S_addr = inet_addr(_Model->IPaddress);
	address.sin_port = htons(9999);
	address.sin_family = AF_INET;
	int size_of_address = sizeof(address);
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	connect(Connection, (SOCKADDR*)&address, size_of_address);
	if (WSAGetLastError())
	{
		MessageBox(_Model->hWnd, "Ñommunication is not established", NULL, NULL);
		exit(1);
	}
	else
		state = allocation;
}

bool Client::sended(char* msg)
{
	send(Connection, msg, MESSAGE_BLOCK, NULL);
	if (strcmp(msg, "STOP"))
		return 1;
	else return 0;
}


int Client::Located(int** field, int x, int y)
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
			_Model->set_heals('m', 20);
			state = mov;
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

void Client::Send_Model(Model* Model)
{
	char msg[256];
	int z = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			msg[z++] = '0' + _Model->get_from_field('m', i, j);
		}
	}
	sended(msg);
}

void Client::Recv_Model(Model* Model)
{
	char msg[MESSAGE_BLOCK];
	int z = 0;
	recv(Connection, msg, MESSAGE_BLOCK, NULL); 
	if (WSAGetLastError())
	{
		MessageBox(_Model->get_HWND(), "Disconnect", NULL, NULL);
		exit(1);
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			_Model->set_on_field('h', i, j, msg[z++] - '0');
	state = wait;
}


void Client::moving(int x, int y)
{
	if ((_Model->field_his[x][y] == kill) || (_Model->field_his[x][y] == damaged) || (_Model->field_his[x][y] == miss))
		return;
	char msg_out[MESSAGE_BLOCK];
	msg_out[0] = x + '0';
	msg_out[1] = y + '0';
	sended(msg_out);
	//recv(Connection, msg_in, MESSAGE_BLOCK, NULL);
	In_Recv* st_msg = new In_Recv(Connection, msg_in, MESSAGE_BLOCK, NULL);
	hThread = CreateThread(NULL, NULL, ((LPTHREAD_START_ROUTINE)recved), (st_msg), NULL, NULL);
	int i = 0;
	while ((msg_in[0] < '0') || (msg_in[0] > '9'))
	{
		Sleep(100);
		if (i == 5000)
			break;
		i++;
	}
	CloseHandle(hThread);
	delete st_msg;
	if (WSAGetLastError())
	{
		MessageBox(_Model->get_HWND(), "Disconnect", NULL, NULL);
		exit(1);
	}
	msg_in[0] = msg_in[0] - '0';
	switch (msg_in[0])
	{
	case 0:
		_Model->set_on_field('h', x, y, miss);
		state = wait;
		break;
	case 1:
		_Model->set_on_field('h', x, y, damaged);
		_Model->heals_his--;
		break;
	case 2:
		_Model->set_on_field('h', x, y, damaged);
		_Model->heals_his--;
		kills('h', x, y);
		break;
	}
	msg_in[0] = -1;
	if (_Model->heals_his == 0)
		state = win;
}

void Client::waiting()
{
	int x = -1, y = -1;
	In_Recv* st_msg = new In_Recv(Connection, msg_in, MESSAGE_BLOCK, NULL);
	if(flag_waitrecv == 0)
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
	delete st_msg;
	if (WSAGetLastError())
	{
		MessageBox(_Model->get_HWND(), "Disconnect", NULL, NULL);
		exit(1);
	}
	x = msg_in[1] - '0';
	y = msg_in[2] - '0';
	switch (msg_in[0] - '0')
	{
	case 0:
		state = mov;
		_Model->set_on_field('m', x, y, miss);
		break;
	case 1:
		_Model->heals_my--;
		_Model->set_on_field('m', x, y, damaged);
		break;
	case 2:
		_Model->heals_my--;
		_Model->set_on_field('m', x, y, damaged);
		kills('m', x, y);
		break;
	}
	msg_in[0] = -1;
	if (_Model->heals_my == 0)
		state = lose;
}

void Client::ready()
{
	_Model->set_heals('m', 20);
	char msg[MESSAGE_BLOCK];
	recv(Connection, msg, MESSAGE_BLOCK, NULL);
	send(Connection, msg, MESSAGE_BLOCK, NULL);
	if (WSAGetLastError())
	{
		MessageBox(_Model->hWnd, "Disconnect", NULL, NULL);
		exit(1);
	}
	Send_Model(_Model);
	state = wait;
}

int Client::ClickLeft(int x, int y)
{
	int vertical;
	int horisontal;
	switch (state)
	{
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


