#include "stdafx.h"
#include "NewGame.h"
#include "InputManager.h"


NewGame::NewGame() {}
NewGame::~NewGame() {}

void NewGame::buildBoard()
{	
	int opt = context->GetOption();
	context->setDesk(opt * 4, opt * 4);
}

void NewGame::createAIPlayer()
{
	boost::shared_ptr<AIUser> usr = GameBuilder::createAIPlayer();
	context->addUser(usr);
}

void NewGame::createHumanPlayer()
{
	std::string name;
	std::cout << "Enter name:" << std::endl;
	name = InputManager::GetString(10);

	boost::shared_ptr<HumanUser> usr(new HumanUser(name));
	context->addUser(usr);
}

void NewGame::buildValidator()
{
	int opt = context->GetOption();
	game->setValidator(opt * 3);
}


void NewGame::BuildBoardState() {}

void NewGame::BuildOrderOfPlay()
{
	auto players = context->GetUsers();
	VectorShuffle(players);
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

	buildLabels();
}

void NewGame::buildOptions()
{
	std::cout << "Options: easy(1) medium(2) hard(3)" << std::endl;
	int opt = InputManager::GetNumber(1, 3);

	context->setOption(opt);
}

void NewGame::buildLabels()
{
	std::vector<char> symbols = Pawn::GetSymbols();
	VectorShuffle(symbols);
	auto players = context->GetUsers();

	int n = 0;
	for (auto &player : players)
	{
		char label = symbols[n];
		boost::shared_ptr<Pawn> pawn(new Pawn(label, "red"));
		context->addUserToPawn(player, pawn);
		player->setLabel(pawn);
		n++;
	}
	
}



