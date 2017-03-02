#pragma once
#include "Ship.h"

class Enemy : public Ship
{
public:
        Enemy();
        void dive();
        void idle();
        void goAlongPath();
        virtual void update();
private:
        bool canIdle;
        vector<int[2]>* curPath();
        int home[2];
};
