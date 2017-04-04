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
protected:
	double pos[2];
	int mSpeed;
private:
	bool canShoot;
};

