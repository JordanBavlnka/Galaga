#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
	dieState = 0;
}


Ship::~Ship()
{
}


double* Ship::getPos()
{
	return pos;
}


Bullet* Ship::shoot()
{
	return nullptr;
}


void Ship::die()
{
	dieState=1;
}


void Ship::incrementDieState()
{
	if (dieState > 0)
		dieState+=0.1;
	if (dieState >=5)
		dieState = 0;
}


int Ship::getDieState()
{
	return dieState;
}
