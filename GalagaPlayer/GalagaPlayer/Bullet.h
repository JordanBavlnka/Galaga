#pragma once
class Bullet
{
public:
	Bullet();
	Bullet(bool, int, int, double);
	~Bullet();
	bool getEnemy();
	int getPos(bool);
	bool move();
private:
	bool enemy;
	double direction;
	int pos[2];
	double partialMove;
};

