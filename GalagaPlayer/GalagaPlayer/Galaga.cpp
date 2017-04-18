#pragma once
#include "stdafx.h"
#include <vector>
#include "Galaga.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <time.h>
#include "Bee.h"
#include <fstream>
#include <string>

using namespace std;

Galaga::Galaga()
{
	shipSize[0] = 16;
	shipSize[1] = 16;
	bulletSize[0] = 3;
	bulletSize[1] = 8;
	radius[0][0] = 6;
	radius[0][1] = 5;
	radius[1][0] = 1;
	radius[1][1] = 3;
	lives = 2;
	level = 0;
}


Galaga::~Galaga()
{
}


void Galaga::play(sf::RenderWindow *window)
{
  
  int something=0;//menu load time
  bool clickedOnAnything=true;//leave menu?
  int originKeyState = GetKeyState(27);//whether exc key was originally toggled on

  srand(time(NULL));//rand seed
  while (window->isOpen())
  {
	  vector<pair<int, int>> firstPath;//triangle path for ship

	  makePath("Intro Path 1.txt", paths);
	  makePath("Intro Path 2.txt", &paths[1]);
	  makePath("Intro Path 3.txt", &paths[2]);
	  makePath("Intro Path 4.txt", &paths[3]);
	  makePath("Swoop Path 1.txt", &paths[4]);
	  makePath("Swoop Path 2.txt", &paths[5]);
	  makePath("Dive Path 1.txt", &paths[6]);
	  makePath("Dive Path 2.txt", &paths[7]);

	for (int i = 0; i < something; i++)
    {
      //carry menu up
    }
    
	do 
    {
    //display menu
    }while(!clickedOnAnything);
    
	while (window->isOpen())
    {
		for (int i = 68; i < 124; i += 16)
		{
			create(3, 105, i);//makes an enemy with path 3 and home (105, i)
			tick(window, originKeyState, 8,false);
			create(2, 125, i);//type of enemy is automatically generated based on height
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 150, false);

		for (int i = 0; i < 4; i ++)
		{
			create(0, 85+20*i,45);
			tick(window, originKeyState, 8, false);
			create(0, 85+60*(i%2), 68+16*(i/2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);

		for (int i = 0; i < 4; i++)
		{
			create(1, 165 + 20 * (i%2), 68+16*(i/2));
			tick(window, originKeyState, 8, false);
			create(1, 45 + 20 * (i % 2), 68 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);

		for (int i = 0; i < 4; i++)
		{
			create(2, 145 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
			create(2, 65 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);

		for (int i = 0; i < 4; i++)
		{
			create(3, 185 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
			create(3, 25 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
		}


		tick(window, originKeyState, 175, false);


	  while (window->isOpen()&&enemies.size()>0)
	  {
		  dive();
		  tick(window, originKeyState, 200, true);
	  } 
	  level++;
    }
  }

  return;
}


void Galaga::dive()
{
	Enemy* draftees[3];
	bool beeSwap = false;
	if (draft() != -1)
	{
		draftees[0] = enemies.at(draft());
		draftees[0]->drop();

		if (draft() != -1)
		{
			draftees[1] = enemies.at(draft());
			draftees[1]->drop();

			if (draft() != -1)
			{
				draftees[2] = enemies.at(draft());
				draftees[2]->drop();

				if (draftees[2]->identity() == 4)
				{
					draftees[2]->setPath(paths[4]);
					beeSwap = !beeSwap;
				}
				else
				{
					draftees[2]->setPath(paths[6]);
				}
			}

			if (draftees[1]->identity() == 4)
			{
				draftees[1]->setPath(paths[beeSwap ? 5 : 4]);
				beeSwap = !beeSwap;
			}
			else
			{
				draftees[1]->setPath(paths[beeSwap ? 6 : 7]);
			}
		}

		if (draftees[0]->identity() == 4)
		{
			draftees[0]->setPath(paths[beeSwap ? 5 : 4]);
			beeSwap = !beeSwap;
		}
		else
		{
			draftees[0]->setPath(paths[beeSwap ? 7 : 6]);
		}
	}
}


int Galaga::draft()
{
	int numWaiting = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!(enemies.at(i)->isDropping()))
			numWaiting++;
	}
	if (numWaiting == 0)
	{
		return -1;
	}
	else
	{
		int draftPic = rand() % numWaiting;
		cout << draftPic << endl;
		for (int i = 0; i < enemies.size(); i++)
		{
			if (!(enemies.at(i)->isDropping()))
			{
				if (draftPic == 0)
					return i;
				else
					draftPic--;
			}
		}
	}
}


void Galaga::create(int path, int x, int y)
{
	Enemy* newptr;
	if (y < 55)
		newptr = new Boss(paths[path]);
	else if (y < 92)
		newptr = new Butterfly(paths[path]);
	else
		newptr = new Bee(paths[path]);

	newptr->setHome(x, y);

	enemies.push_back(newptr);

}


void Galaga::tick(sf::RenderWindow *window, int originKeyState, int numTicks, bool shoot)
{
	for (int i = 0; i < numTicks; i++)
		tick(window, originKeyState, shoot);
}


void Galaga::tick(sf::RenderWindow *window, int originKeyState, bool shoot)
{
  static clock_t cooldown = clock();//bullet shoot
  static clock_t cheatCooldown = clock();//developer cheats
  static int lastCheat = 0;//last l keystate
  static int lastFire = 0;//last spacebar keystate
  clock_t time = clock();
  int temp[2][2];
	if (GetKeyState(37) < -5)//move left
		player.move(false);

	if (GetKeyState(39) < -5)//move right
		player.move(true);

	if (GetKeyState(32) < -5)//shoot
	{
		if ((clock() - 350 > cooldown || GetKeyState(32) != lastFire)&&numBullets<2){//hold cooldown
			cooldown = clock();//reset cooldown (for holding)
			lastFire = GetKeyState(32);//check current keystate
			bullets.push_back(player.shoot());//shoot a bullet
			numBullets++;
			cout << numBullets << endl;
		}

	}

	player.incrementDieState();

	if (GetKeyState(38) < -5)//cheaty whatever
	{
		if (clock() - 1000 > cheatCooldown || GetKeyState(38) != lastCheat){//hold cooldown
			cheatCooldown = clock();//reset cooldown
			lastCheat = GetKeyState(38);//check current keystate
			player.die();
			lives--;
		}
		cout << player.getDieState() << endl;
	}

	for (int i = 0; i < bullets.size(); i++)//move all the bullets
	{
		if ((bullets.at(i))->move())//returns true if bullet is out
		{
			if (!(bullets.at(i)->getEnemy()))
				numBullets--;
			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);//get rid of bullet
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (shoot&&rand() % 3000 == 199)
			bullets.push_back(enemies.at(i)->shoot(&player));
		enemies.at(i)->goAlongPath();
	}

	//Making collision check from center
	temp[0][0] = convertRadius(player.getPos()[0], shipSize[0]);
	temp[0][1] = convertRadius(player.getPos()[1], shipSize[1]);

	for (int i = 0; i < bullets.size(); i++) {
		temp[1][0] = convertRadius(bullets.at(i)->getPos(true), bulletSize[0]);
		temp[1][1] = convertRadius(bullets.at(i)->getPos(false), bulletSize[1]);
		if (bullets.at(i)->getEnemy()){
			if (collide(temp[0][0], temp[0][1], temp[1][0], temp[1][1], true)) {
				player.die();
				delete bullets.at(i);
				bullets.erase(bullets.begin() + i);
				i--;
				lives--;
			}
		}
		
		else {
			for (int j = 0; j < enemies.size(); j++)
			{
				double temp1 = convertRadius(enemies.at(j)->getPos()[0], shipSize[0]);
				double temp2 = convertRadius(enemies.at(j)->getPos()[1], shipSize[1]);

				if (collide(temp1, temp2, temp[1][0], temp[1][1], true)) {
					delete enemies.at(j);
					enemies.erase(enemies.begin() + j);
					delete bullets.at(i);
					bullets.erase(bullets.begin() + i);
					i--;
					numBullets--;
				}
			}
		}

	}

	for (int i = 0; i < enemies.size(); i++)
	{
		double temp1 = convertRadius(enemies.at(i)->getPos()[0], shipSize[0]);
		double temp2 = convertRadius(enemies.at(i)->getPos()[1], shipSize[1]);
		if (collide(temp1, temp2, temp[0][0], temp[0][1], false)) {
			delete enemies.at(i);
			enemies.erase(enemies.begin() + i);
			player.die();
			i--;
			lives--;
		}

	}

	render(window, originKeyState);

	while (clock() - time < 15){}
}


void Galaga::checkCollision()
{
}


string Galaga::drawLevel(int curLevel)
{
	string outputNumerals = "";
	while (curLevel >= 50)
	{
		outputNumerals = outputNumerals + 'L';
		curLevel -= 50;
	}

	while (curLevel >= 30)
	{
		outputNumerals = outputNumerals + 'T';
		curLevel -= 30;
	}

	while (curLevel >= 20)
	{
		outputNumerals = outputNumerals + 'W';
		curLevel -= 20;
	}

	while (curLevel >= 10)
	{
		outputNumerals = outputNumerals + 'X';
		curLevel -= 10;
	}

	while (curLevel >= 5)
	{
		outputNumerals = outputNumerals + 'V';
		curLevel -= 5;
	}

	while (curLevel >= 1)
	{
		outputNumerals = outputNumerals + 'I';
		curLevel -= 1;
	}
	return outputNumerals;
}


void Galaga::render(sf::RenderWindow *window, int originKeyState)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || GetKeyState(27) == 1 - originKeyState||lives<0)//x button or escape key
			window->close();
	}

	sf::Texture texture;
	texture.loadFromFile("GalagaSprites.png");

	sf::Sprite playerSprite;
	playerSprite.setTexture(texture);
	if (player.getDieState() == 0)
	{
		playerSprite.setTextureRect(sf::IntRect(184, 55, 16, 16));
		playerSprite.setPosition(*player.getPos(), *(player.getPos() + 1));
	}
	else
	{
		playerSprite.setTextureRect(sf::IntRect(168 + 40 * player.getDieState(), 47, 32, 32));
		playerSprite.setPosition(*player.getPos()-8, *(player.getPos() + 1)-8);
	}


	sf::Sprite myShotSprite;
	myShotSprite.setTexture(texture);
	myShotSprite.setTextureRect(sf::IntRect(373, 75, 3, 7));

	sf::Sprite beeSprite;
	beeSprite.setTexture(texture);
	beeSprite.setTextureRect(sf::IntRect(162,178,13,10));


	window->clear();
	window->draw(playerSprite);
	for (int i = 0; i < lives; i++)
	{
		playerSprite.setTextureRect(sf::IntRect(184, 55, 16, 16));
		playerSprite.setPosition(sf::Vector2f(16*i,300));
		window->draw(playerSprite);		
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (/*(bullets.at(i))->getEnemy()*/false)
		{

		}
		else
		{
			myShotSprite.setPosition((bullets.at(i)->getPos(true)), (bullets.at(i)->getPos(false)));
			window->draw(myShotSprite);
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
			beeSprite.setTextureRect(enemies.at(i)->textureLocation());
			beeSprite.setPosition((enemies.at(i)->getPos())[0], (enemies.at(i)->getPos())[1]);
			window->draw(beeSprite);
	}
	window->display();
}


void Galaga::makePath(string pathPos, vector<pair<int,int>>* path) {
	int temp = 0;
	int pathPoints[2] = { 0, 0 };
	string lineWords;
	string strngNumbers;
	ifstream pathAccess;
	pathAccess.open(pathPos);

	//strngNumbers.resize(10);
	while (getline(pathAccess,lineWords) && lineWords!="end"){
		if (lineWords != "start")
		{
			temp = lineWords.find(',');
			strngNumbers = lineWords.substr(0, temp);
			pathPoints[0] = stringToInt(strngNumbers);
			strngNumbers = lineWords.substr(temp + 1, lineWords.size());
			pathPoints[1] = stringToInt(strngNumbers);
			path->push_back({ pathPoints[0], pathPoints[1] });
		}
	}
	if (path->size() == 0)
	{
		cout << lineWords << endl;
	}
}


int Galaga::stringToInt(std::string strngONumbers) {
	int number = 0;
	int place = 1;

	for (int i = strngONumbers.size() - 1; i >= 0; --i){
		switch (strngONumbers.at(i)){
		case '0':
			break;
		case '1':
			number += 1* place;
			break;
		case '2':
			number += 2* place;
			break;
		case '3':
			number += 3* place;
			break;
		case '4':
			number += 4* place;
			break;
		case '5':
			number += 5* place;
			break;
		case '6':
			number += 6* place;
			break;
		case '7':
			number += 7* place;
			break;
		case '8':
			number += 8* place;
			break;
		case '9':
			number += 9* place;
			break;
		case '-':
			number *= -1;
			break;

		default:
			place /= 10;
			break;
		}
		
		if (place > 0)
			place *= 10;
		else
			place = 1;
	}

	return number;
}

void Galaga::setRadius(int x, int y, bool isBullet){
	radius[isBullet?1:0][0] = x;
	radius[isBullet?1:0][1] = y;
	return;
}

bool Galaga::collide(int ship1X, int ship1Y, int ship2X, int ship2Y, bool vsBullet){
	float theDistance[2];

	//Calculates the exact distance
	//Between Ship 1 and Ship for collision
	theDistance[0] = hypot(ship1X - ship2X, ship1Y - ship2Y);
	if (vsBullet) {
		theDistance[1] = hypot(radius[0][0], radius[0][1]);
		theDistance[1] += hypot(radius[1][0], radius[1][1]);
	}
	else
		theDistance[1] = hypot(radius[0][0], radius[0][1]) * 2;
	//Tests whether the ships are to close to eachother.
	if (theDistance[0] <= theDistance[1])
		return true;
	else
		return false;
}

int Galaga::convertRadius(int x, int sideSize){
	int result;
	result = x + sideSize / 2;

	return result;
}