#pragma once
#include "Enemy.h"
#include "Boss.h"
class EvilGyaraga : public Enemy
{
public:
    EvilGyaraga();
    ~EvilGyaraga();
    void return();
    Boss* getBoss();
private:
    Boss* myBoss;
    int ticksToSwitch;
}
