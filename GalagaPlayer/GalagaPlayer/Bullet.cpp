#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	enemy = true;
	direction = 0;
	pos[0] = 10;
	pos[1] = 10;
	partialMove = 0;
}

Bullet::Bullet(bool theEnemy, int posx, int posy, double sideVelocity)
{
	enemy = theEnemy;
	pos[0] = posx;
	pos[1] = posy;
	direction = sideVelocity;
	partialMove = 0;
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
	++partialMove += direction;
	while (partialMove-- > 1)
	{
		pos[0]++;
	}
	return pos[1] < -5||pos[1]>810;
}