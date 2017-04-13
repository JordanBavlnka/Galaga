#pragma once
#include "Enemy.h"

class Boss :
	public Enemy
{
public:
	Boss();
	Boss(int, int);

	Boss(std::vector<std::pair<int, int>>);
	~Boss();
	void vortex();
	virtual int identity();
};

