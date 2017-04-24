#include "stdafx.h"
#include "Gyaraga.h"
#include "Bullet.h"
#include <iostream>


Gyaraga::Gyaraga()
{
	pos[0] = 117;
	pos[1] = 285;
}


void Gyaraga::reset()
{
	pos[0] = 117;
	pos[1] = 285;
}


Gyaraga::~Gyaraga()
{
}


void Gyaraga::move(bool right)
{
	if (!this->dying())
	{
		if (right)
		{
			if (pos[0] < 230)
				pos[0] += 3;
			else
				pos[0] = 233;
		}
		else if (pos[0]>2)
			pos[0] -= 3;
		else
			pos[0] = 0;
	}
}


void Gyaraga::rebirth(int t)
{
	if (t < 117)
	{
		pos[0] = t;
		pos[1] = 300;
	}
	else
	{
		pos[0] = 117;
		pos[1] = 417 - t;
	}
}


void Gyaraga::addShip()
{

}


void Gyaraga::caught()
{

}


Bullet* Gyaraga::shoot()
{
	Bullet *myShot = new Bullet(false,pos[0]+6,pos[1]-5,0);
	return myShot;
}


bool Gyaraga::dying()
{
	return this->getDieState() != 0||pos[1]!=285;
}