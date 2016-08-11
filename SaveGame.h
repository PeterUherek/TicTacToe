#pragma once
#include <string>
#include "game.pb.h"
#include "ContextGame.h"
#include "SaverLoader.h"

class SaveGame : public SaverLoader
{
public:
	SaveGame();
	~SaveGame();

	int Save(const ContextGame& context, const User& player);

private:

	// Save Game
	void SerializePlayers(const ContextGame& context);
	void SerializeMovments(const ContextGame& context);
	void SerializeBoard(const ContextGame& context);
	void SerializeOptions(const ContextGame& context);
	void SerializeLastPlayer(const User& player);
	int SaveToFile(const game::Game& game);


};

