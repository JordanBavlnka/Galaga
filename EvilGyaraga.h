#pragma once
#include "Enemy.h"
#include "Boss.h"
class EvilGyaraga : public Enemy
{
public:
    EvilGyaraga();
    ~EvilGyaraga();
    void return();
private:
    Boss* myBoss;
    int ticksToSwitch;
}
