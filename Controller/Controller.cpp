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

