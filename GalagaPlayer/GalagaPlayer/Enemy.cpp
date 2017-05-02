#include "stdafx.h"
#include "Enemy.h"
#include <iostream>

using namespace std;


Enemy::Enemy()
{
	nextLoc = 1;
	mSpeed = 3000;
	dropping = false;
	isHome = false;
}


Enemy::~Enemy()
{
}


void Enemy::loseLife()
{
	extraLife = false;
}


void Enemy::dive()
{
}


void Enemy::idle()
{
}


void Enemy::goAlongPath(int staticPos, bool separating)
{
	if (nextLoc >= curPath.size())
	{
		cout << nextLoc <<"  " << curPath.size() << endl;
		system("pause");
	}
	double targetX;
	double targetY;
	targetX = get<0>(curPath.at(nextLoc));
	targetY = get<1>(curPath.at(nextLoc));
	if (targetX == home[0] && targetY == home[1])
	{
		if (separating)
		{
			staticPos /= 30;
			openWings = (staticPos) % 2 == 0;
			staticPos *= 10;

			staticPos = staticPos % 120;

			if (staticPos > 60)
				staticPos = 120 - staticPos;

			if (this->identity() < 3)
				staticPos = 0;

			staticPos /= 5;
			staticPos *= 2;

			pos[0] = targetX = static_cast<double>((home[0] - 115)*(90+staticPos))/90+115;
			pos[1] = targetY = home[1];
		}
		else
		{
			staticPos /= 30;
			openWings = (staticPos) % 2 == 0;
			staticPos *= 10;
			staticPos = staticPos % 80;
			if (staticPos > 20)
				staticPos = 40 - staticPos;
			if (staticPos < -20)
				staticPos = -40 - staticPos;

			staticPos /= 10;
			staticPos *= 6;

			pos[0] = targetX = home[0] + staticPos;
			pos[1] = targetY = home[1];

		}
	}
	int curX = pos[0];
	int curY = pos[1];

	double totalDistance = pow(pow(curX - targetX, 2) + pow(curY - targetY, 2), 0.5);
	if (totalDistance*1000 <= mSpeed)//if you're there
	{
		pos[0] = targetX;
		pos[1] = targetY;//get the rest of the way
		nextLoc++;
		if (nextLoc == curPath.size())
		{
			if (dropping)
			{
				dropping = false;
				if (identity() != 4)
				{
					pos[0] = 125;
					pos[1] = -20;
					curPath.push_back({ 125, -20 });
					nextLoc++;
				}
				curPath.push_back({ home[0], home[1] + 1 });
				curPath.push_back({ home[0], home[1] });
			}
			else
			{
				isHome = true;
				nextLoc--;
			}
		}
		/*
		targetX = get<0>(curPath.at(nextLoc));
		targetY = get<1>(curPath.at(nextLoc));

		curX = pos[0];
		curY = pos[1];

		double newDistance = pow(pow(curX - targetX, 2) + pow(curY - targetY, 2), 0.5);

		pos[0] += ((mSpeed-totalDistance*1000)*(targetX - curX)) / newDistance / 1000;
		pos[1] += ((mSpeed - totalDistance * 1000)*(targetY - curY)) / newDistance / 1000;
		cout << pos[0] << " " << pos[1] << endl;*/
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


void Enemy::drop()
{
	dropping = true;
	isHome = false;
}


bool Enemy::isDropping()
{
	return dropping;
}


void Enemy::setPath(std::vector<std::pair<int, int>> newPath)
{
	curPath = newPath;
	nextLoc = 0;
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
	int leftBoundary = 161;//default value

	int targetX = get<0>(curPath.at(nextLoc));
	int targetY = get<1>(curPath.at(nextLoc));

	double lastX;
	double lastY;

	if (isHome)
	{
		if (openWings)
		{

		}
	}

	if (nextLoc == 0)
	{
		lastX = home[0];
		lastY = home[1];
	}
	else
	{
		lastX = get<0>(curPath.at(nextLoc - 1));
		lastY = get<1>(curPath.at(nextLoc - 1));
	}

	if (lastX!=targetX)
	{
		static double prevslope;

		double slope = abs((targetY - lastY) / (targetX - lastX));
		for (int i = 1; i < 12; i+=2)
		{
			if (leftBoundary == 161 && slope < tan(0.131*i))
			{
				leftBoundary = i * 12 + 5;
			}
		}
	}
	else
	{
		if (isHome&&!openWings)
		{
			leftBoundary += 24;
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


void Enemy::setHome(int x, int y)
{
	curPath.push_back({ x, y+1 });
	curPath.push_back({ x, y });
	home[0] = x;
	home[1] = y;
}