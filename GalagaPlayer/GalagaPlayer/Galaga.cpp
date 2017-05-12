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
	shipSize[0] = 16;//centering
	shipSize[1] = 16;
	bulletSize[0] = 3;//centering
	bulletSize[1] = 8;

	radius[0][0] = 6;//collission radius, ship
	radius[0][1] = 5;
	radius[1][0] = 1;//collission radius, bullet
	radius[1][1] = 3;

	lives = 2;//extra lives
	level = 0;
	numBullets = 0;//live player bullet count

	//initialize background
	for (int i = 0; i < 20; i++)
	{
		backgroundScrollX[i] = rand() % 250;
		backgroundScrollY[i] = rand() % 322;
	}

	score = 0;
	separating = false;//enemy formation (separating vs sliding)
}


Galaga::~Galaga()
{
}


void Galaga::play(sf::RenderWindow *window)
{
  int originKeyState = GetKeyState(27);//whether exc key was originally toggled on\

  makePath("Intro Path 1.txt", paths);//load path
  makePath("Intro Path 2.txt", &paths[1]);
  makePath("Intro Path 3.txt", &paths[2]);
  makePath("Intro Path 4.txt", &paths[3]);
  makePath("Swoop Path 1.txt", &paths[4]);
  makePath("Swoop Path 2.txt", &paths[5]);
  makePath("Dive Path 1.txt", &paths[6]);
  makePath("Dive Path 2.txt", &paths[7]);

  srand(time(NULL));//rand seed

  while (window->isOpen())//game loop
  {
	  initTime = clock();
	  ticks = 0;
	while (window->isOpen()&&lives>=0)//level loop
    {
		for (int i = 68; i < 124; i += 16)//first set entering
		{
			create(3, 105, i);//makes an enemy with path 3 and home (105, i)
			tick(window, originKeyState, 8,false);
			create(2, 125, i);//type of enemy is automatically generated based on height
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);//wait to get in position

		for (int i = 0; i < 4; i ++)//second set entering
		{
			create(0, 85+20*i,45);
			tick(window, originKeyState, 8, false);
			create(0, 85+60*(i%2), 68+16*(i/2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);//wait to get in position

		for (int i = 0; i < 4; i++)//third set entering
		{
			create(1, 165 + 20 * (i%2), 68+16*(i/2));
			tick(window, originKeyState, 8, false);
			create(1, 45 + 20 * (i % 2), 68 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);//wait to get in position

		for (int i = 0; i < 4; i++)//fourth set entering
		{
			create(2, 145 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
			create(2, 65 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);//wait to get in position

		for (int i = 0; i < 4; i++)
		{
			create(3, 185 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
			create(3, 25 + 20 * (i % 2), 100 + 16 * (i / 2));
			tick(window, originKeyState, 8, false);
		}

		tick(window, originKeyState, 175, false);

		separating = true;//bugs switch from side to side to expand/contract


	  while (window->isOpen()&&enemies.size()>0)//repeat for the rest of the level
	  {
		  dive();//have three bugs dive
		  tick(window, originKeyState, 200, true);
	  } 

	  level++;
	  separating = false;//end of level reset
    }
	lives = 2;
	player.reset();//death reset
	score = 0;
  }

  return;//when window closes
}


//chooses up to three enemies (if there are three) and has them drop
void Galaga::dive()
{
	Enemy* draftees[3];
	bool beeSwap = false;
	if (draft() != -1)//if you can draft something
	{
		draftees[0] = enemies.at(draft());//draft something
		draftees[0]->drop();//mark it as drafted

		if (draft() != -1)//if you can draft something
		{
			draftees[1] = enemies.at(draft());//draft something
			draftees[1]->drop();//mark it as drafted

			if (draft() != -1)//if you can draft something
			{
				draftees[2] = enemies.at(draft());//draft something
				draftees[2]->drop();//mark it as drafted

				if (draftees[2]->identity() == 4)//if a bee
				{
					draftees[2]->setPath(paths[4]);//swoop
					beeSwap = !beeSwap;//remember there was a bee
				}
				else
				{
					draftees[2]->setPath(paths[6]);//dive
				}
			}

			if (draftees[1]->identity() == 4)//make sure to avoid using the same path if you can
			{
				draftees[1]->setPath(paths[beeSwap ? 5 : 4]);//avoid the previous path
				beeSwap = !beeSwap;
			}
			else
			{
				draftees[1]->setPath(paths[beeSwap ? 6 : 7]);//avoid the previous path
			}
		}

		if (draftees[0]->identity() == 4)
		{
			draftees[0]->setPath(paths[beeSwap ? 5 : 4]);//avoid the previous path
		}
		else
		{
			draftees[0]->setPath(paths[beeSwap ? 7 : 6]);//avoid the previous path
		}
	}
}


int Galaga::draft()
{
	//make sure theres something to draft
	int numWaiting = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!(enemies.at(i)->isDropping()))
			numWaiting++;
	}
	if (numWaiting == 0)
	{
		return -1;//error code
	}

	//draft it
	else
	{
		int draftPic = rand() % numWaiting;//choose a number

		//find the corresponding enemy
		for (int i = 0; i < enemies.size(); i++)
		{
			if (!(enemies.at(i)->isDropping()))
			{
				if (draftPic-- == 0)
					return i;
			}
		}
	}
}


void Galaga::create(int path, int x, int y)
{
	Enemy* newptr;

	//determing enemy type based on home elevation
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
	//do numTicks ticks
	for (int i = 0; i < numTicks; i++)
	{
		try
		{
			tick(window, originKeyState, shoot);
		}
		catch (int e) //if you die
		{
			tick(window, originKeyState, 40, false);//let the explosion happen
			lives--;//decrement lives
			if (lives >= 0)//if you have another life
			{
				//move the next guy over
				for (int j = lives * 16; j < 135; j++)
				{
					player.rebirth(j);
					tick(window, originKeyState, false);
				}
			}
			else//if you dont have another life
			{
				i = numTicks;//end the loop
				enemies.clear();//clear the enemies
			}//This will leave all the loops and restart
		}
	}
}


void Galaga::tick(sf::RenderWindow *window, int originKeyState, bool shoot)
{
	static int loopPos = 0;//used to determine flap position

	static clock_t cooldown = clock();//bullet shoot
	static clock_t cheatCooldown = clock();//developer cheats
	static int lastCheat = 0;//last up arrow keystate
	static int lastFire = 0;//last spacebar keystate

	clock_t time = clock();//tick speed reglation
	int temp[2][2];//player middle
	loopPos++;//increment flap position

	if (GetKeyState(37) < -5)//move left
		player.move(false);

	if (GetKeyState(39) < -5)//move right
		player.move(true);

	if (GetKeyState(32) < -5)//shoot
	{
		if ((clock() - 350 > cooldown || GetKeyState(32) != lastFire)&&numBullets<2&&!player.dying()){//hold cooldown
			cooldown = clock();//reset cooldown (for holding)
			lastFire = GetKeyState(32);//check current keystate

			bullets.push_back(player.shoot());//shoot a bullet

			numBullets++;//a new live player bullet
		}

	}


	if (GetKeyState(38) < -5)//cheaty whatever
	{
		if ((clock() - 1000 > cheatCooldown || GetKeyState(38) != lastCheat)&&!player.dying()){//hold cooldown
			cheatCooldown = clock();//reset cooldown
			lastCheat = GetKeyState(38);//check current keystate
			lives++;
		}
	}

	player.incrementDieState();//for death animation

	for (int i = 0; i < bullets.size(); i++)//move all the bullets
	{
		if ((bullets.at(i))->move())//returns true if bullet is out of the window
		{
			if (!(bullets.at(i)->getEnemy()))//if its not an enemy bullet
				numBullets--;//one less live bullet

			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);//get rid of bullet
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (shoot&&rand() % 3000 == 199)//if they can shoot, sometimes shoot
			bullets.push_back(enemies.at(i)->shoot(&player));

		enemies.at(i)->goAlongPath(loopPos, separating);//path following
	}

	//Making collision check from center instead of corner
	temp[0][0] = convertRadius(player.getPos()[0], shipSize[0]);
	temp[0][1] = convertRadius(player.getPos()[1], shipSize[1]);

	for (int i = 0; i < bullets.size(); i++) {

		temp[1][0] = convertRadius(bullets.at(i)->getPos(true), bulletSize[0]);//get center of bullet
		temp[1][1] = convertRadius(bullets.at(i)->getPos(false), bulletSize[1]);

		if (bullets.at(i)->getEnemy()){//if its an enemy bullet
			//if its touching the player
			if (collide(temp[0][0], temp[0][1], temp[1][0], temp[1][1], true)&&!player.dying())
			{
				delete bullets.at(i);
				bullets.erase(bullets.begin() + i);

				player.die();
				throw 42;//lets the loop know the player died
			}
		}
		
		else {//player bullet
			int i2 = i;//to make sure you quit after you hit one enemy
			for (int j = 0; j < enemies.size()&&i2==i; j++)
			{
				double temp1 = convertRadius(enemies.at(j)->getPos()[0], shipSize[0]);
				double temp2 = convertRadius(enemies.at(j)->getPos()[1], shipSize[1]);

				//if it hit an enemy
				if (collide(temp1, temp2, temp[1][0], temp[1][1], true)) {
					if (enemies.at(j)->identity() == 1)//if its a boss with both lives
						enemies.at(j)->loseLife();
					else
					{
						//scoring
						int beeScore = 50;
						int butterflyScore = 80;
						int bossScore = 150;

						if (enemies.at(j)->identity() == 4)//bees
						{
							if (enemies.at(j)->isDropping())//double score for hitting while dropping
								score += beeScore * 2;
							else
								score += beeScore;
						}

						else if (enemies.at(j)->identity() == 3)//butterflies
						{
							if (enemies.at(j)->isDropping())//double score for hitting while dropping
								score += butterflyScore * 2;
							else
								score += butterflyScore;
						}

						else//boss
						{
							if (enemies.at(j)->isDropping())//double score for hitting while dropping
								score += (bossScore * 2) + 100;
							else
								score += bossScore;
						}


						delete enemies.at(j);
						enemies.erase(enemies.begin() + j);
					}
  					delete bullets.at(i);
					bullets.erase(bullets.begin() + i);
					i--;
					numBullets--;
				}
			}
		}

	}

	for (int i = 0; i < enemies.size(); i++)//check if each enemy his the player
	{
		double temp1 = convertRadius(enemies.at(i)->getPos()[0], shipSize[0]);
		double temp2 = convertRadius(enemies.at(i)->getPos()[1], shipSize[1]);

		//if they collide
		if (collide(temp1, temp2, temp[0][0], temp[0][1], false)&&!player.dying()) {
			delete enemies.at(i);
			enemies.erase(enemies.begin() + i);
			i--;

			player.die();
			throw 42;//break the loop
		}

	}

	render(window, originKeyState);
	while (clock() - initTime < 15*ticks){}
	ticks++;
}

//framework to draw level with symbols. not currently implemented.
string Galaga::drawLevel(int curLevel)
{
	string outputNumerals = "";//writes in pseudo roman numerals
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

//draws everything
void Galaga::render(sf::RenderWindow *window, int originKeyState)
{


	bool display = (clock() - initTime) < 15 * ticks;

	sf::Event event;//standard sfml
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || GetKeyState(27) == 1 - originKeyState)//x button or escape key
			window->close();
	}
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("star.png");

	sf::Sprite background[20];
	for (int i = 0; i < 20; i++)//update background
	{
		background[i].setTexture(backgroundTexture);
		if (backgroundScrollY[i] >= 322)
			backgroundScrollY[i] = 0;
		background[i].setTextureRect(sf::IntRect(0, 0, 3, 4));
		background[i].setPosition(backgroundScrollX[i], backgroundScrollY[i]);
		backgroundScrollY[i] += 2;
	}

	if (display)
	{

		sf::Texture texture;//open up main sprite file
		texture.loadFromFile("GalagaSprites.png");

		sf::Sprite playerSprite;
		playerSprite.setTexture(texture);
		if (player.getDieState() == 0)//if you're not dying
		{
			playerSprite.setTextureRect(sf::IntRect(184, 55, 16, 16));//normal sprite
			playerSprite.setPosition(*player.getPos(), *(player.getPos() + 1));
		}
		else
		{
			playerSprite.setTextureRect(sf::IntRect(168 + 40 * player.getDieState(), 47, 32, 32));//explode sprite
			playerSprite.setPosition(*player.getPos() - 8, *(player.getPos() + 1) - 8);//explode sprite is 8 larger on each side
		}


		sf::Sprite myShotSprite;//player buller
		myShotSprite.setTexture(texture);
		myShotSprite.setTextureRect(sf::IntRect(366, 195, 3, 7));

		sf::Sprite hisShotSprite;//enemy bullet
		hisShotSprite.setTexture(texture);
		hisShotSprite.setTextureRect(sf::IntRect(374, 51, 3, 7));

		sf::Sprite beeSprite;//all enemies
		beeSprite.setTexture(texture);
		beeSprite.setTextureRect(sf::IntRect(162, 178, 13, 10));


		sf::Texture scoreTexture;//alternate texture file that has numbers
		scoreTexture.loadFromFile("number_sprites.png");

		sf::Sprite scoreSprite;
		scoreSprite.setTexture(scoreTexture);


		window->clear();

		for (int i = 0; i < 20; i++)//draw all the stars
			window->draw(background[i]);

		window->draw(playerSprite);

		for (int i = 0; i < lives; i++)//draw extra lives
		{
			playerSprite.setTextureRect(sf::IntRect(184, 55, 16, 16));
			playerSprite.setPosition(sf::Vector2f(16 * i, 302));
			window->draw(playerSprite);
		}


		for (int i = 0; i < bullets.size(); i++)//draw bullets
		{
			//sprite for enemy bullets
			if (bullets.at(i)->getEnemy())
			{
				hisShotSprite.setPosition((bullets.at(i)->getPos(true)), (bullets.at(i)->getPos(false)));
				window->draw(hisShotSprite);
			}
			//sprite for player bullets
			else
			{
				myShotSprite.setPosition((bullets.at(i)->getPos(true)), (bullets.at(i)->getPos(false)));
				window->draw(myShotSprite);
			}
		}

		for (int i = 0; i < enemies.size(); i++)//draw enemies
		{
			beeSprite.setTextureRect(enemies.at(i)->textureLocation());
			beeSprite.setPosition((enemies.at(i)->getPos())[0], (enemies.at(i)->getPos())[1]);
			window->draw(beeSprite);
		}

		sf::Sprite scoreTextSprite;
		scoreTextSprite.setTexture(scoreTexture);
		scoreTextSprite.setTextureRect(sf::IntRect(225,8,28,5));

		scoreTextSprite.setPosition(sf::Vector2f(1, 1));
		window->draw(scoreTextSprite);

		string scoreString = std::to_string(score);
		for (int i = 0; i < scoreString.size(); i++)//draw score
		{
			scoreSprite.setTextureRect(sf::IntRect((scoreString.at(i) - '0') * 8, 0, 4, 5));
			scoreSprite.setPosition(sf::Vector2f(6 * i+1, 8));
			window->draw(scoreSprite);
		}
		window->display();
	}
}

//import path
void Galaga::makePath(string pathPos, vector<pair<int,int>>* path) {
	int temp = 0;//comma location
	int pathPoints[2] = { 0, 0 };//temp path point
	string lineWords;//a line
	string strngNumbers;//a coordinates
	ifstream pathAccess;//the file
	pathAccess.open(pathPos);

	//strngNumbers.resize(10);
	while (getline(pathAccess,lineWords) && lineWords!="end"){
		if (lineWords != "start")
		{
			temp = lineWords.find(',');

			strngNumbers = lineWords.substr(0, temp);
			pathPoints[0] = stringToInt(strngNumbers);//import x

			strngNumbers = lineWords.substr(temp + 1, lineWords.size());
			pathPoints[1] = stringToInt(strngNumbers);//import y

			path->push_back({ pathPoints[0], pathPoints[1] });//add to path
		}
	}
}



int Galaga::stringToInt(std::string strngONumbers) {
	int number = 0;
	int place = 1;

	for (int i = strngONumbers.size() - 1; i >= 0; --i){//reads right to left
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

//change radii
void Galaga::setRadius(int x, int y, bool isBullet){
	radius[isBullet?1:0][0] = x;
	radius[isBullet?1:0][1] = y;
	return;
}


bool Galaga::collide(int ship1X, int ship1Y, int ship2X, int ship2Y, bool vsBullet){
	float theDistance[2];

	//Calculates the exact distance
	//Between Ship 1 and Ship for collision
	theDistance[0] = hypot(ship1X - ship2X, ship1Y - ship2Y);//distance between ships
	if (vsBullet) {
		theDistance[1] = hypot(radius[0][0], radius[0][1]);
		theDistance[1] += hypot(radius[1][0], radius[1][1]);//clearing distance with bullet
	}
	else
		theDistance[1] = hypot(radius[0][0], radius[0][1]) * 2;//clearing distance with other ship
	//Tests whether the ships are to close to eachother.
	return theDistance[0] <= theDistance[1];
}

//move to middle instead of cornet
int Galaga::convertRadius(int x, int sideSize){
	int result;
	result = x + sideSize / 2;

	return result;
}