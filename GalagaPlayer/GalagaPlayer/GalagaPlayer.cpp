// GalagaPlayer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Galaga.h"
#include <SFML/Graphics.hpp>
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	sf::RenderWindow window(sf::VideoMode(500,644), "Galaga");
	window.setView(sf::View(sf::FloatRect(0,0,250,322)));
	Galaga game;
	game.play(&window);
	return 0;
}

