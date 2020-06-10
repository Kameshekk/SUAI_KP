#include "Controller.h"

Controller::Controller() 
{ 
	state = start; 
	stay = 0; 
	ships = 0;
	prevx1 = 0;
	prevy1 = 0;
	prevx2 = 0;
	prevy2 = 0;
	prevx3 = 0;
	prevy3 = 0;
}

Controller::~Controller() { }

State_of_game Controller::get_state()
{
	return state;
}

void Controller::set_state(State_of_game _state)
{
	state = _state;
}

void Controller::Reset()
{
	state = allocation;
	stay = 0;
	ships = 0;
	prevx1 = 0;
	prevy1 = 0;
	prevx2 = 0;
	prevy2 = 0;
	prevx3 = 0;
	prevy3 = 0;
	_Model->set_heals('m', 0);
	_Model->set_heals('h', 20);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_Model->set_on_field('m', i, j, 0);
			_Model->set_on_field('h', i, j, 0);
		}
	}
}


void Controller::kills(char who, int x, int y)
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

