#include "stdafx.h"
#include "Bee.h"

Bee::Bee(){
	pos[0] = 42;
	pos[1] = 42;
}


Bee::Bee(std::vector<std::pair<int, int>> newPath)
{
	setPath(newPath);
	pos[0] = std::get<0>(newPath.at(0));
	pos[1] = std::get<1>(newPath.at(0));
}

Bee::Bee(int x, int y)
{
	pos[0] = x;
	pos[1] = y;
}

Bee::~Bee()
{
}


void Bee::swoop()
{
	//swoop
}


void Bee::transform(int numBugs)
{
	//turn into bonus stuff
}


int Bee::identity()
{
	return 4;
}
