#pragma once
#include "Ship.h"
#include <vector>

class Enemy : public Ship
{
public:
        Enemy();
		~Enemy();
        void dive();
        void idle();
        void goAlongPath();
        virtual void update();
private:
        bool canIdle;
        std::vector<int[2]>* curPath;
        int home[2];
};
