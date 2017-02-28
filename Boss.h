#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:
        Boss();
        ~Boss();
        bool getEnemy();
private:
        bool enemy;
        int direction[2];
}
