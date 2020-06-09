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

