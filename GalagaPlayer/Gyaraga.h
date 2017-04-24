#ifndef GYARAGA_H
#define GYARAGA_H

#include "Ship.h"
#include "Bullet.h"


class Gyaraga : public Ship
{
public:
	Gyaraga();
	~Gyaraga();
	void move(bool);
	void addShip();
	void caught();
	virtual Bullet* shoot();
	void rebirth(int);
	void reset();
	bool dying();
private:
	bool together;
};

#endif // GYARAGA_H