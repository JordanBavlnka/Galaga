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
    void setBoss(Boss*);
    int getTicks();
    void setTicks(int);
    void tick();
private:
    Boss* myBoss;
    int ticksToSwitch;
}
