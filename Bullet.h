#pragma once
class Bullet
{
public:
	Bullet();
	bool isEnemy();
	~Bullet();
	void update();
private:
	bool enemy;
	int direction;
};

