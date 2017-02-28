#include "stdafx.h"
#include "EvilGyaraga.h"


EvilGyaraga::EvilGyaraga()
{
}


EvilGyaraga::~EvilGyaraga()
{
}


void EvilGyaraga::return()
{
}


Boss* EvilGyaraga::getBoss()
{
  return myBoss;
}


void EvilGyaraga::setBoss(Boss* newBoss)
{
  myBoss = newBoss;
}


int EvilGyaraga::getTicks()
{
  return ticksToSwitch;
}


void EvilGyaraga::setTicks(int newTicks)
{
  ticksToSwitch = newTicks;
}


void EvilGyaraga::tick()
{
  ticksToSwitch--;
}
