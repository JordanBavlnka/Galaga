#pragma once
#include "Enemy.h"

class Bee : public Enemy
{
public:
	Bee();
	Bee(int, int);
	~Bee();
	void swoop();
	void transform(int);
	virtual int identity();
};
