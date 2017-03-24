#pragma once
class Bullet
{
public:
	Bullet();
	Bullet(bool, int, int, int);
	~Bullet();
	bool getEnemy();
	int getPos(bool);
	bool move();
private:
	bool enemy;
	int direction;
	int pos[2];
};

