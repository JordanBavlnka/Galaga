#pragma once
class Bullet
{
public:
	Bullet();
	bool isEnemy();
	~Bullet();
private:
	bool enemy;
	int direction;
};

