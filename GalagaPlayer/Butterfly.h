#pragma once
#include "Enemy.h"

class Butterfly : public Enemy
{
public:
        Butterfly();
		Butterfly(int, int);

		Butterfly(std::vector<std::pair<int, int>>);
        ~Butterfly();
	virtual int identity();
};
