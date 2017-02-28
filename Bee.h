#pragma once
#include "Enemy.h"
class Bee : public Enemy
{
public:
	Bee();
	~Bee();
	void swoop();
	void transform(int);
};
