#pragma once
#include "Bullet.h"
class Ship
{
public:
	Ship();
	double* getPos();
	void move(bool);
	virtual Bullet * shoot();
	void die();
	~Ship();
	void incrementDieState();
	int getDieState();
protected:
	double pos[2];
	int mSpeed;
private:
	double dieState;
	bool canShoot;
};

