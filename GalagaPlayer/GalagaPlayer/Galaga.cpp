#pragma once
#include "stdafx.h"
#include <vector>
#include "Galaga.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <time.h>
#include "Bee.h"

using namespace std;

Galaga::Galaga()
{
}


Galaga::~Galaga()
{
}


void Galaga::play(sf::RenderWindow *window)
{
  clock_t cooldown = clock();//bullet shoot
  clock_t cheatCooldown = clock();//developer cheats
  int lastCheat = 0;//last l keystate
  int lastFire = 0;//last spacebar keystate
  int something=0;//menu load time
  bool clickedOnAnything=true;//leave menu?
  int originKeyState = GetKeyState(27);//whether exc key was originally toggled on

  srand(time(NULL));//rand seed
  while (window->isOpen())
  {
	  vector<pair<int,int>> firstPath;//triangle path for ship

	  firstPath.push_back({ 50, 50 });
	  firstPath.push_back({ 200, 60 });//arbitrary points
	  firstPath.push_back({ 100, 5 });

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
		  if (GetKeyState(37) < -5)//move left
			  player.move(false);

		  if (GetKeyState(39) < -5)//move right
			  player.move(true);

		  if (GetKeyState(32) < -5)//shoot
		  {
			  if (clock() - 350 > cooldown||GetKeyState(32)!=lastFire){//hold cooldown
				  cooldown = clock();//reset cooldown (for holding)
				  lastFire = GetKeyState(32);//check current keystate
				  bullets.push_back(player.shoot());//shoot a bullet
			  }
		  }

		  if (GetKeyState(38) < -5)//cheaty level up
		  {
			  if (clock() - 350 > cheatCooldown || GetKeyState(38) != lastCheat){//hold cooldown
				  cheatCooldown = clock();//reset cooldown
				  lastCheat = GetKeyState(38);//check current keystate
				  level++;
			  }
		  }

		  beeptr->goAlongPath();//move the bee

		  for (int i = 0; i < bullets.size(); i++)//move all the bullets
		  {
			  if ((bullets.at(i))->move())//returns true if bullet is out
				  bullets.erase(bullets.begin()+i);//get rid of bullet
		  }

		  for (int i = 0; i < enemies.size(); i++)
		  {
			  if (rand()%20==0)
				bullets.push_back(enemies.at(i)->shoot(&player));
		  }

		  render(window, originKeyState);
	  } 
    }
  }

  return;
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

	sf::Texture texture;
	texture.loadFromFile("GalagaSprites.png");

	sf::Sprite playerSprite;
	playerSprite.setTexture(texture);
	playerSprite.setTextureRect(sf::IntRect(184, 55, 16, 16));
	playerSprite.setPosition(*player.getPos(), *(player.getPos() + 1));

	sf::Sprite myShotSprite;
	myShotSprite.setTexture(texture);
	myShotSprite.setTextureRect(sf::IntRect(373, 75, 3, 7));

	sf::Sprite beeSprite;
	beeSprite.setTexture(texture);
	beeSprite.setTextureRect(sf::IntRect(162,178,13,10));


	window->clear();
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
		case 2:
			beeSprite.setPosition((enemies.at(i)->getPos())[0], (enemies.at(i)->getPos())[1]);
			window->draw(beeSprite);
			break;
		}
	}
	window->display();
}