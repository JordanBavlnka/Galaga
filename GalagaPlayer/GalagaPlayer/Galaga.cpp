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

	  /*for (int i = 0; i < 15; i++)
	  {
		  firstPath.push_back({ rand() % 234, rand() % 200 });
	  }*/
	  makePath("Intro Path 1.txt", &firstPath);

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
	  Bee* beeptr = new Bee(40,80);//test enemy
	  enemies.push_back(beeptr);


	  beeptr->setPath(&firstPath);//acrobatics to set the bee path



	  while (window->isOpen())
	  {
		  tick(window, originKeyState);
	  } 
    }
  }

  return;
}


void Galaga::tick(sf::RenderWindow *window, int originKeyState)
{
  static clock_t cooldown = clock();//bullet shoot
  static clock_t cheatCooldown = clock();//developer cheats
  static int lastCheat = 0;//last l keystate
  static int lastFire = 0;//last spacebar keystate
	if (GetKeyState(37) < -5)//move left
		player.move(false);

	if (GetKeyState(39) < -5)//move right
		player.move(true);

	if (GetKeyState(32) < -5)//shoot
	{
		if (clock() - 350 > cooldown || GetKeyState(32) != lastFire){//hold cooldown
			cooldown = clock();//reset cooldown (for holding)
			lastFire = GetKeyState(32);//check current keystate
			bullets.push_back(player.shoot());//shoot a bullet
		}

	}

	player.incrementDieState();

	if (GetKeyState(38) < -5)//cheaty whatever
	{
		if (clock() - 1000 > cheatCooldown || GetKeyState(38) != lastCheat){//hold cooldown
			cheatCooldown = clock();//reset cooldown
			lastCheat = GetKeyState(38);//check current keystate
			player.die();
		}
		cout << player.getDieState() << endl;
	}

	for (int i = 0; i < bullets.size(); i++)//move all the bullets
	{
		if ((bullets.at(i))->move())//returns true if bullet is out
			bullets.erase(bullets.begin() + i);//get rid of bullet
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (rand() % 20 == 0)
			bullets.push_back(enemies.at(i)->shoot(&player));
		enemies.at(i)->goAlongPath();
	}

	render(window, originKeyState);
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
		if (event.type == sf::Event::Closed || GetKeyState(27) == 1 - originKeyState)//x button or escape key
			window->close();
	}


	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");

	sf::Sprite background;
	background.setTexture(backgroundTexture);
	if (backgroundScroll <= 0)
		backgroundScroll = 322;
	background.setTextureRect(sf::IntRect(0, backgroundScroll, 250, 322));
	background.setPosition(0, 0);

	backgroundScroll -= 2;


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
	window->draw(background);
	window->draw(playerSprite);
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
		switch (enemies.at(i)->identity())
		{
		case 4:
			beeSprite.setTextureRect(enemies.at(i)->textureLocation());
			beeSprite.setPosition((enemies.at(i)->getPos())[0], (enemies.at(i)->getPos())[1]);
			window->draw(beeSprite);
			break;
		}
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
		temp = lineWords.find(',');
		strngNumbers = lineWords.substr(0, temp);
		pathPoints[0] = stringToInt(strngNumbers);
		cout << strngNumbers << ", ";
		strngNumbers = lineWords.substr(temp+1, lineWords.size());
		pathPoints[1] = stringToInt(strngNumbers);
		cout << strngNumbers << endl;
		path->push_back({pathPoints[0],pathPoints[1]});
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
