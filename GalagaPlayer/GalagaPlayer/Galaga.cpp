#pragma once
#include "stdafx.h"
#include <vector>
#include "Galaga.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

using namespace std;

Galaga::Galaga()
{
}


Galaga::~Galaga()
{
}


void Galaga::play(sf::RenderWindow *window)
{
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
      bool enemiesAlive;
	  while (window->isOpen())
	  {
		  if (GetKeyState(37) < -5)
			  player.move(false);
		  if (GetKeyState(39) < -5)
			  player.move(true);
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
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(184, 55, 16, 16));
	sprite.setPosition(*player.getPos(),*(player.getPos()+1));


	window->clear();
	window->draw(sprite);
	window->display();
}
