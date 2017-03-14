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
protected:
	int pos[2];
	int mSpeed;
private:
	bool canShoot;
};

