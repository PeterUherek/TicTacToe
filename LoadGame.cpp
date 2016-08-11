#include "stdafx.h"
#include "LoadGame.h"
#include "HumanUser.h"
#include "AIUser.h"

#include <iostream>
#include <fstream>
#include <sstream>

LoadGame::LoadGame()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	LoadFile();
}

LoadGame::~LoadGame()
{

}

int LoadGame::LoadFile() 
{
	std::fstream input(saveFile, std::ios::in | std::ios::binary);
	if (!nGame->ParseFromIstream(&input)) 
	{
		std::cerr << "Failed to parse address book." << std::endl;
		return -1;
	}
}

void LoadGame::AddLabeltoUser(User& usr, const game::User& player)
{
	boost::shared_ptr<Pawn> pawn(new Pawn(player.symbol().c_str()[0], "red"));
	usr.setLabel(pawn);
}

void LoadGame::addAtributestoUser(const game::User& player, const boost::shared_ptr<User>& usr) 
{
	usr->setScore(player.score());
	AddLabeltoUser(*usr, player);

	context->addUser(usr);
}

void LoadGame::createHumanPlayer(const game::User& player)
{
	boost::shared_ptr<HumanUser> usr(new HumanUser(player.name()));
	addAtributestoUser(player, usr);
}

void LoadGame::createAIPlayer(const game::User& player)
{
	boost::shared_ptr<AIUser> usr = GameBuilder::createAIPlayer();
	addAtributestoUser(player, usr);
}

void LoadGame::buildBoard()
{	
	const game::Board board = nGame->board();
	context->setDesk(board.x(), board.y());
}

void LoadGame::setGameStates(const int& x, const int& y, const char& symbol)
{
	auto players = context->GetUsers();

	auto player = *std::find_if(players.begin(), players.end(),
		[&symbol](const boost::shared_ptr<User>& player) {
		return (player->GetPawn()->GetLabel() == symbol);
	});

	boost::shared_ptr<Memento> mem(new Memento(player->GetPawn(), x, y));
	context->TryMove(mem);
}

void LoadGame::BuildBoardState() 
{
	for (int j = 0; j < nGame->mem_size(); j++)
	{
		const game::Move& mem = nGame->mem(j);
		char label = std::stoi(mem.symbol());
		setGameStates(mem.x(), mem.y(), label);
	}
}

void LoadGame::BuildOrderOfPlay()
{
	auto players = context->GetUsers();
	std::string name = nGame->turnfor();

	auto it = std::find_if(players.begin(), players.end(),
		[&name](const boost::shared_ptr<User>& player) {
		return (player->getName() == name);
	});

	auto pos = std::distance(players.begin(), it);
	std::rotate(players.begin(), players.begin() + pos, players.end());

}

void LoadGame::buildUser()
{
	for (int j = 0; j < nGame->user_size(); j++)
	{
		const game::User& usr = nGame->user(j);
		if (usr.human() == true)
		{
			createHumanPlayer(usr);
		}
		else 
		{
			createAIPlayer(usr);
		}
	}

	buildLabels();
}

void LoadGame::buildOptions()
{
	context->setOption(nGame->options());
}

void LoadGame::buildLabels()
{
	auto players = context->GetUsers();
	for (auto &player : players)
	{
		context->addUserToPawn(player, player->GetPawn());
	}
}

void LoadGame::buildValidator()
{
	int opt = context->GetOption();
	game->setValidator(opt * 3);
}





