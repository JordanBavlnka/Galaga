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
        void dive();//unused
        void idle();//unused
        void goAlongPath(int, bool);//follow your path, passed idling info
        virtual void update();//unused
		virtual int identity() = 0;//pure virtual for identifying what kind of ship
		Bullet * shoot(Ship*);//passes a newly made bullet
		void setPath(std::vector<std::pair<int, int>>);//changes course
		void drop();//records that it is dropping
		bool isDropping();//asks whether dropping
		void setHome(int, int);//sets default location (before movement)
		sf::Rect<int> textureLocation();//returns where on spritesheet
		void loseLife();//only for bosses
protected:
		bool extraLife;//whether bosses have extra lives
private:
        bool canIdle;//unused
		bool dropping;
		bool isHome;
        std::vector<std::pair<int,int>> curPath;
		int nextLoc;
		int home[2];
		bool openWings;//used when idling
};
