#include "stdafx.h"
#include "Gyaraga.h"
#include "Bullet.h"


Gyaraga::Gyaraga()
{
	pos[0] = 117;
	pos[1] = 285;
}


Gyaraga::~Gyaraga()
{
}


void Gyaraga::move(bool right)
{
	if (right)
	{
		if (pos[0] < 234)
			pos[0] += 2;
		else
			pos[0] = 233;
	}
	else if (pos[0]>1)
		pos[0] -= 3;
	else
		pos[0] = 3;
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