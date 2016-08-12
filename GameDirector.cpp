#include "stdafx.h"
#include "GameDirector.h"
#include "InputManager.h"
#include "LoadGame.h"

GameDirector::GameDirector() {}

int GameDirector::SetGame() {

	std::cout << "New game or load game? (N/L)" << std::endl;
	
	char charCollection[] = { 'n', 'l' };
	char key = InputManager::GetChar(charCollection);

	if (key == 'n' || key == 'N') {
		gameBuilder = boost::shared_ptr<GameBuilder>(new NewGame());
		return 0;
	}
	if (key == 'l' || key == 'L') {
		if (LoadGame::existFile(LoadGame::saveFile)) {
			gameBuilder = boost::shared_ptr<GameBuilder>(new LoadGame());
			return 0;
		}
		else {
			std::cout << "Saved game doesnt exist! Please start new game." << std::endl;
			return -1;
		}
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
	gameBuilder->BuildBoardState();
	gameBuilder->BuildOrderOfPlay();
	return 0;
}

boost::shared_ptr<IGame> GameDirector::GetGame()
{
	return (gameBuilder->getGame());
}

