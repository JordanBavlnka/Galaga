#pragma once
#include "Bullet.h"
class Ship
{
public:
	Ship();
	int* getPos();
	void move(bool);
	virtual Bullet * shoot();
	void die();
	~Ship();
protected:
	int pos[2];
	int mSpeed;
private:
	bool canShoot;
};

