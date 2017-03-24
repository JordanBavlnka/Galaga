#pragma once
#include "stdafx.h"
#include <vector>
#include "Galaga.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <time.h>

using namespace std;

Galaga::Galaga()
{
	bullets.resize(0);
}


Galaga::~Galaga()
{
}


void Galaga::play(sf::RenderWindow *window)
{
  clock_t cooldown = clock();
  int lastFire = 0;
  bool quit=false;
  int something=0;
  bool clickedOnAnything=true;
  int lives=0;
  int originKeyState = GetKeyState(27);//whether exc key was originally toggled on
  while (window->isOpen())
  {

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
	  while (window->isOpen())
	  {
		  if (GetKeyState(37) < -5)//move left
			  player.move(false);

		  if (GetKeyState(39) < -5)//move right
			  player.move(true);

		  if (GetKeyState(32) < -5)//shoot
		  {
			  if (clock() - 350 > cooldown||GetKeyState(32)!=lastFire){//hold cooldown
				  cooldown = clock();
				  lastFire = GetKeyState(32);
				  bullets.push_back(player.shoot());
			  }
		  }

		  for (int i = 0; i < bullets.size(); i++)
		  {
			  if ((bullets.at(i))->move())
				  bullets.erase(bullets.begin()+i);
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


void Galaga::drawScore()
{
}


void Galaga::drawLevel()
{
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


	window->clear();
	window->draw(playerSprite);
	for (int i = 0; i < bullets.size(); i++)
	{
		if (/*(bullets.at(i))->getEnemy()*/ false)
		{

		}
		else
		{
			myShotSprite.setPosition((bullets.at(i)->getPos(true)), (bullets.at(i)->getPos(false)));
			window->draw(myShotSprite);
		}
	}
	window->display();
}