#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
}


Boss::~Boss()
{
}




Boss::Boss(std::vector<std::pair<int, int>> newPath)
{
	setPath(newPath);
	pos[0] = std::get<0>(newPath.at(0));
	pos[1] = std::get<1>(newPath.at(0));
}


Boss::Boss(int x, int y)
{
	pos[0] = x;
	pos[1] = y;
}


void Boss::vortex()
{

}


int Boss::identity()
{
	if (extraLife)
		return 1;
	return 2;
}