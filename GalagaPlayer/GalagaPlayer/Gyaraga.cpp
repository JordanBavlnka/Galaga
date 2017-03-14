#include "stdafx.h"
#include "Gyaraga.h"


Gyaraga::Gyaraga()
{
	pos[0] = 250;
	pos[1] = 750;
}


Gyaraga::~Gyaraga()
{
}


void Gyaraga::move(bool right)
{
	if (right)
	{
		if (pos[0] < 484)
			pos[0]++;
	}
	else if (pos[0]>1)
		pos[0]--;
}


void Gyaraga::addShip()
{

}


void Gyaraga::caught()
{

}