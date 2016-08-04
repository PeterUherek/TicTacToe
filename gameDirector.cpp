#include "stdafx.h"
#include "GameDirector.h"
#include "InputManager.h"

GameDirector::GameDirector() {}

int GameDirector::SetGame() {

	std::cout << "New game or Load Game? (N/L)" << std::endl;
	
	char charCollection[] = { 'n', 'l' };
	char key = InputManager::GetChar(charCollection);

	if (key == 'n' || key == 'N') {
		gameBuilder = boost::shared_ptr<GameBuilder>(new NewGame());
		return 0;
	}
	if (key == 'l' || key == 'L') {
		//gameBuilder = boost::shared_ptr<GameBuilder>(new NewGame());
		return 0;
	}
	return 0;
}

int GameDirector::ConstructGame()
{
	gameBuilder->createNewGame();
	gameBuilder->buildOptions();
	gameBuilder->buildBoard();
	gameBuilder->buildValidator();
	gameBuilder->buildUser();
	gameBuilder->buildLabels();
	return 0;
}

boost::shared_ptr<IGame> GameDirector::GetGame()
{
	return (gameBuilder->getGame());
}

