#pragma once
class Ship
{
public:
	Ship();
	int* getPos();
	void move(bool);
	void shoot();
	void die();
	~Ship();
	virtual void update() = 0;
private:
	int pos[2];
	int mSpeed;
	bool canShoot;
};

