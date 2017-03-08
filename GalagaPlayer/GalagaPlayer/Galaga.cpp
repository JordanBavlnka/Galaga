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
	  sf::Event event;
	  while (window->pollEvent(event))
	  {
		  if (event.type == sf::Event::Closed||GetKeyState(27)==1-originKeyState)//x button or escape key
			  window->close();
	  }

	/*for (int i = 0; i < something; i++)
    {
      //carry menu up
    }*/
    
	std::cout << GetKeyState(37) << std::endl;
   /* do 
    {
    //display menu
    }while(!clickedOnAnything);*/
    
	/*while (GetKeyState(37)>-5)
    {
      bool enemiesAlive;
	  while (GetKeyState(37)>-5)
	  {
        //stuff
		  cout << GetKeyState(37) << endl;
        
	  } 
    }*/

	window->clear();
	window->display();
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


void Galaga::render()
{
}
