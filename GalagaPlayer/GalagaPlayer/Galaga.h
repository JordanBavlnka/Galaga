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
  void checkCollision();
  void drawScore();
  std::string drawLevel(int);
  void render(sf::RenderWindow*, int);
  void makePath(std::string, std::vector<std::pair<int, int>>*);
  int stringToInt(std::string);
  void tick(sf::RenderWindow*, int, int);
  void tick(sf::RenderWindow*, int);
  void create(int, int, int);
  void dive();
  int draft();
protected:
  //should be vector<int[2]>, but c++ doesnt like that
  std::vector<std::pair<int, int>> paths[8];
private:
  std::vector<Enemy*> enemies;
  std::vector<Bullet*> bullets;
  Gyaraga player;
  int score;
  int highscore;
  int level;
};
