#pragma once
#include "Enemy.h"
#include "Boss.h"
class EvilGyaraga : public Enemy
{
public:
    EvilGyaraga();
    ~EvilGyaraga();
    void becomeGood();
    Boss* getBoss();
    void setBoss(Boss*);
    int getTicks();
    void setTicks(int);
    void tick();
    void update();
private:
    Boss* myBoss;
    int ticksToSwitch;
};