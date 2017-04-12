#pragma once
#include "Ship.h"
#include <vector>
#include "Bullet.h"
#include "Gyaraga.h"
#include <SFML/Graphics.hpp>

class Enemy : public Ship
{
public:
        Enemy();
		~Enemy();
        void dive();
        void idle();
        void goAlongPath();
        virtual void update();
		virtual int identity() = 0;
		Bullet * shoot(Ship*);
		void setPath(std::vector<std::pair<int, int>>);
		void setHome(int, int);
		sf::Rect<int> textureLocation();
private:
        bool canIdle;
        std::vector<std::pair<int,int>> curPath;
		int nextLoc;
        int home[2];
};
