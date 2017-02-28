#pragma once
#include <vector>
#include "Gyaraga.h"
#include "BonusBug.h"
#include "EvilGyaraga.h"
#include "Boss.h"
#include "Bee.h"
#include "Butterfly.h"
#include "Bullet.h"


class Galaga
{
public:
  Galaga();
  ~Galaga();
  void play();
  void checkCollision();
  void drawScore();
  void drawLevel();
  void render();
private:
  vector<Enemy> enemies;
  vector<Bullet> bullets;
  Gyaraga player;
  int score;
  int highscore;
  const vector<int[2]>[] paths;
  int level;
}
