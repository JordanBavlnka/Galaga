#include "stdafx.h"
#include "Enemy.h"
#include <iostream>

using namespace std;


Enemy::Enemy()
{
	nextLoc = 1;
	mSpeed = 2000;
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
	if (totalDistance*1000 <= mSpeed)//if you're there
	{
		pos[0] = targetX;
		pos[1] = targetY;//get the rest of the way
		nextLoc++;
		if (nextLoc == curPath->size())
			nextLoc = 0;//return completed bool

		targetX = get<0>(curPath->at(nextLoc));
		targetY = get<1>(curPath->at(nextLoc));

		curX = pos[0];
		curY = pos[1];

		pos[0] += ((mSpeed-totalDistance*1000)*(targetX - curX)) / totalDistance / 1000;
		pos[1] += ((mSpeed - totalDistance * 1000)*(targetY - curY)) / totalDistance / 1000;
		cout << pos[0] << " " << pos[1] << endl;
	}

	else//normal moving
	{

		pos[0] += (mSpeed*(targetX - curX)) / totalDistance / 1000;
		pos[1] += (mSpeed*(targetY - curY)) / totalDistance/1000;
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
	Bullet * myShot = new Bullet(true, pos[0]+8, pos[1]+8, run / rise);
	return myShot;
}


sf::Rect<int> Enemy::textureLocation()
{
	int identity = this->identity();
	int topBoundary = 80 + 24 * identity;
	int leftBoundary = 160;//default value

	int targetX = get<0>(curPath->at(nextLoc));
	int targetY = get<1>(curPath->at(nextLoc));

	double lastX = get<0>(curPath->at(nextLoc == 0?0:nextLoc-1));
	double lastY = get<1>(curPath->at(nextLoc == 0 ? 0 : nextLoc - 1));

	if (lastX!=targetX)
	{
		static double prevslope;

		double slope = abs((targetY - lastY) / (targetX - lastX));


		cout << targetY << "  " <<lastY <<  endl;
		for (int i = 1; i < 12; i+=2)
		{
			if (leftBoundary == 160 && slope < tan(0.131*i))
			{
				leftBoundary = i * 12 + 4;
			}
		}
	}
	if (lastX > targetX)
	{
		if (lastY > targetY)
		{
			return sf::IntRect(leftBoundary, topBoundary, 16, 16);
		}
		else
		{
			return sf::IntRect(leftBoundary, topBoundary+15, 16, -16);
		}
	}
	else
	{
		if (lastY > targetY)
		{
			return sf::IntRect(leftBoundary+15, topBoundary, -16, 16);
		}
		else
		{
			return sf::IntRect(leftBoundary+15, topBoundary + 15, -16, -16);
		}
	}

}