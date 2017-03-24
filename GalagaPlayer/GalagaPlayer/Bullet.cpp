#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	enemy = true;
	direction = 0;
	pos[0] = 10;
	pos[1] = 10;
}

Bullet::Bullet(bool theEnemy, int posx, int posy, int sideVelocity)
{
	enemy = theEnemy;
	pos[0] = posx;
	pos[1] = posy;
	direction = sideVelocity;
}

Bullet::~Bullet()
{
}


bool Bullet::getEnemy()
{
	return enemy;
}


int Bullet::getPos(bool isX)
{
	if (isX)
		return pos[0];
	else
		return pos[1];
}


bool Bullet::move()
{
	if (enemy)
		pos[1]++;
	else
		pos[1]--;
	pos[0] += direction;
	return pos[1] < -5;
}