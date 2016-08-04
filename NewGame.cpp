#include "stdafx.h"
#include "NewGame.h"
#include "InputManager.h"


NewGame::NewGame() {}
NewGame::~NewGame() {}

void NewGame::buildBoard()
{	
	int opt = game->getOptions();
	game->setDesk(opt * 4, opt * 4);
}

void NewGame::createHumanPlayer()
{
	string name;
	std::cout << "Enter name:" << std::endl;
	name = InputManager::GetString(10);

	boost::shared_ptr<HumanUser> usr(new HumanUser(name));
	game->addUser(usr);
}

void NewGame::buildValidator()
{
	int opt = game->getOptions();
	game->setValidator(opt * 3);
}

void NewGame::createAIPlayer() 
{
	boost::shared_ptr<AIUser> usr; 
	boost::shared_ptr<AlgorithmStrategy> strategy;

	if (game->getOptions() == 1) 
		strategy = boost::shared_ptr<AlgorithmStrategy>(new RandomStrategy());
	else 
		strategy = boost::shared_ptr<AlgorithmStrategy>(new HeuristicAlgorithm(game->getNumberLabelsForWin()));
	
	boost::shared_ptr<ContextGame> context = game->getGameContext();
	strategy->setGameContext(context);

	usr = boost::shared_ptr<AIUser>(new AIUser(strategy));
	game->addUser(usr);
}

void NewGame::buildUser()
{
	std::cout << "Please enter number of players:" << std::endl;
	int num_players = InputManager::GetNumber(1, 2);

	if (num_players == 1)
		createAIPlayer();

	while (num_players != 0) {
		createHumanPlayer();
		num_players--;
	}

}

void NewGame::buildOptions()
{
	std::cout << "Options: easy(1) medium(2) hard(3)" << std::endl;
	int options = InputManager::GetNumber(1, 3);

	game->setOptions(options);
}

void NewGame::buildLabels()
{
	game->assignPawns();
}



