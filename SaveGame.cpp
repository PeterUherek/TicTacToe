#include "stdafx.h"
#include "SaveGame.h"

#include "game.pb.h"
#include "ContextGame.h"
#include "AIUser.h"

#include <iostream>
#include <fstream>
#include <sstream>


SaveGame::SaveGame()
{
}


SaveGame::~SaveGame()
{

}

int SaveGame::SaveToFile(const game::Game& game)
{
	std::fstream output(saveFile, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!game.SerializeToOstream(&output) && nGame->IsInitialized())
	{
		std::cerr << "Failed to write address book." << std::endl;
		return -1;
	}
	return 0;
}

void SaveGame::SerializePlayers(const ContextGame& context)
{
	auto players = context.GetUsers();

	for (auto& player : players) {
		game::User* user(nGame->add_user());
		user->set_name(player->getName());
		user->set_score(player->GetBestScore());
		user->set_symbol(std::string(1,player->GetPawn()->GetLabel()));

		if (AIUser * p = dynamic_cast<AIUser *>(&(*player))) {
			user->set_human(false);
		}else{
			user->set_human(true);
		}
	}
}

void SaveGame::SerializeMovments(const ContextGame& context) 
{
	auto moves = context.GetSavedStates();

	for (auto& move : moves){
		game::Move* mem(nGame->add_mem());
		mem->set_x(move->GetXos());
		mem->set_y(move->GetYos());
		char c = move->GetLabel()->GetLabel();
		mem->set_symbol(std::to_string(c));
	}

}

void SaveGame::SerializeBoard(const ContextGame& context)
{
	game::Board* board(new game::Board());

	board->set_x(context.GetBoard()->GetX());
	board->set_y(context.GetBoard()->GetY());

	nGame->set_allocated_board(board);
}

void SaveGame::SerializeOptions(const ContextGame & context)
{
	nGame->set_options(context.GetOption());
}

void SaveGame::SerializeLastPlayer(const User & player)
{
	nGame->set_turnfor(player.getName());
}

int SaveGame::Save(const ContextGame& context,const User& player)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	SerializeOptions(context);
	SerializePlayers(context);
	SerializeBoard(context);
	SerializeMovments(context);
	SerializeLastPlayer(player);

	return SaveToFile(*nGame);
}





