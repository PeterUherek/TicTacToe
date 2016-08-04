// simplemath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "main.h"
#include "GameDirector.h"

#include <iostream>
#include <string>





int main()
{
	GameDirector director;
	director.SetGame();
	director.ConstructGame();

	boost::shared_ptr<IGame> game = director.GetGame();
	game->Play();
	
    return 0;
}


