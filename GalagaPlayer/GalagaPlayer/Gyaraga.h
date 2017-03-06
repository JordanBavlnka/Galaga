#ifndef GYARAGA_H
#define GYARAGA_H

#include "Ship.h"


class Gyaraga : public Ship
{
public:
	Gyaraga();
	~Gyaraga();
	void move(bool);
	void addShip();
	void caught();
private:
	bool together;
};

#endif // GYARAGA_H