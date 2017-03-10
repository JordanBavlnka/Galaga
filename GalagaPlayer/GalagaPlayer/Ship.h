#pragma once
class Ship
{
public:
	Ship();
	int* getPos();
	virtual void move(bool);
	virtual void shoot();
	virtual void die();
	~Ship();
private:
	int pos[2];
	int mSpeed;
	bool canShoot;
};

