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


class Galaga
{
public:
  Galaga();
  ~Galaga();
  void play(sf::RenderWindow*);
  void checkCollision();
  void drawScore();
  void drawLevel();
  void render();
private:
  std::vector<Enemy> enemies;
  std::vector<Bullet> bullets;
  Gyaraga player;
  int score;
  int highscore;
  std::vector<int[2]> paths[37];
  int level;
};
