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
  Galaga();
  ~Galaga();
  void play(sf::RenderWindow*);
  void drawScore();
  std::string drawLevel(int);
  void render(sf::RenderWindow*, int);
  void makePath(std::string, std::vector<std::pair<int, int>>*);
  int stringToInt(std::string);
  void tick(sf::RenderWindow*, int, int, bool);
  void tick(sf::RenderWindow*, int, bool);
  void create(int, int, int);
  void dive();
  int draft();

  void setRadius(int, int, bool);
  int convertRadius(int, int);
  bool collide(int, int, int, int, bool);
protected:
  //should be vector<int[2]>, but c++ doesnt like that
  std::vector<std::pair<int, int>> paths[8];
private:
  std::vector<Enemy*> enemies;
  std::vector<Bullet*> bullets;
  Gyaraga player;
  unsigned long long int score;
  int highscore;
  int level;
  int lives;

  int radius[2][2];

  int shipSize[2];
  int bulletSize[2];
  int numBullets;
  int backgroundScrollY[20];
  int backgroundScrollX[20];
  bool separating;
  
};
