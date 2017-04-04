#include "stdafx.h"
#include "Enemy.h"
#include <iostream>

using namespace std;


Enemy::Enemy()
{
	nextLoc = 1;
}


Enemy::~Enemy()
{
}


void Enemy::dive()
{
}


void Enemy::idle()
{
}


void Enemy::goAlongPath()
{
	int targetX = get<0>(curPath->at(nextLoc));
	int targetY = get<1>(curPath->at(nextLoc));
	int curX = pos[0];
	int curY = pos[1];
	double totalDistance = pow(pow(curX - targetX, 2) + pow(curY - targetY, 2), 0.5);
	if (totalDistance <= mSpeed)
	{
		pos[0] = targetX;
		pos[1] = targetY;
		nextLoc++;
		if (nextLoc == curPath->size())
			nextLoc = 0;//return completed bool?
		cout << pos[0] << endl;
	}
	else
	{
		pos[0] += (targetX - curX) / totalDistance;
		pos[1] += (targetY - curY) / totalDistance;
	}
}


void Enemy::update()
{
}


void Enemy::setPath(std::vector<std::pair<int, int>>* newPath)
{
	curPath = newPath;
}


Bullet * Enemy::shoot(Ship * toBeShot)
{
	double rise = toBeShot->getPos()[1] - pos[1];
	double run = toBeShot->getPos()[0] - pos[0];
	Bullet * myShot = new Bullet(true, pos[0], pos[1], run / rise);
	return myShot;
}