#pragma once
#include <vector>
#include "Gyaraga.h"
#include "BonusBug.h"
#include "EvilGyaraga.h"
#include "Boss.h"
#include "Bee.h"
#include "Butterfly.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <time.h>



class Galaga
{
public:
  Galaga();//constructor
  ~Galaga();//deconstructor

  void play(sf::RenderWindow*);//main loop

  std::string drawLevel(int);//unimplemented
  void render(sf::RenderWindow*, int);//draw everything

  void makePath(std::string, std::vector<std::pair<int, int>>*);//import path
  int stringToInt(std::string);

  void tick(sf::RenderWindow*, int, int, bool);//many ticks
  void tick(sf::RenderWindow*, int, bool);//one tick

  void create(int, int, int);//new enemy
  void dive();//have some enemies dive
  int draft();//choose which enemy dives

  void setRadius(int, int, bool);//change a preset radius
  int convertRadius(int, int);//pythagoras
  bool collide(int, int, int, int, bool);//check whether two things are close enough to collide
protected:
  //should be vector<int[2]>, but c++ doesnt like that
  std::vector<std::pair<int, int>> paths[8];//all the paths enemies can follow
private:
  std::vector<Enemy*> enemies;
  std::vector<Bullet*> bullets;
  Gyaraga player;
  int score;
  int highscore;
  int level;
  int lives;

  int radius[2][2];//used for collission

  int shipSize[2];
  int bulletSize[2];//used to find center

  int numBullets;//live player bullets
  int backgroundScrollY[20];//background star locations
  int backgroundScrollX[20];
  bool separating;//enemy drift

  int ticks;
  clock_t initTime;
  
};
