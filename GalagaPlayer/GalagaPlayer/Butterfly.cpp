#include "stdafx.h"
#include "Butterfly.h"


Butterfly::Butterfly()
{
}

Butterfly::Butterfly(int x, int y)
{
	pos[0] = x;
	pos[1] = y;
}




Butterfly::Butterfly(std::vector<std::pair<int, int>> newPath)
{
	setPath(newPath);
	pos[0] = std::get<0>(newPath.at(0));
	pos[1] = std::get<1>(newPath.at(0));
}

Butterfly::~Butterfly()
{
}

int Butterfly::identity()
{
	return 3;
}