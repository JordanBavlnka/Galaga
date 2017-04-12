#include "stdafx.h"
#include "Bee.h"

Bee::Bee(){
	pos[0] = 42;
	pos[1] = 42;
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
