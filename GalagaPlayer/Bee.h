#pragma once
#include "Enemy.h"

class Bee : public Enemy
{
public:
	Bee();
	Bee(int, int);
	~Bee();
	Bee(std::vector<std::pair<int, int>>);
	void swoop();
	void transform(int);
	virtual int identity();
};
