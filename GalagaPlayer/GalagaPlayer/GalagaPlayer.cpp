// GalagaPlayer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Galaga.h"
#include <SFML/Graphics.hpp>


int _tmain(int argc, _TCHAR* argv[])
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Galaga");
	Galaga game;
	game.play(&window);
	return 0;
}

