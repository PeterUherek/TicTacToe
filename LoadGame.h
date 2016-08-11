#pragma once
#include "SaverLoader.h"
#include "GameBuilder.h"

class LoadGame : public GameBuilder, public SaverLoader
{
public:
	LoadGame();
	~LoadGame();

	// Inherited via GameBuilder
	virtual void buildBoard() override;
	virtual void buildUser() override;
	virtual void buildOptions() override;
	virtual void buildValidator() override;
	virtual void BuildBoardState() override;
	virtual void BuildOrderOfPlay() override;

private:
	int LoadFile();
	void createHumanPlayer(const game::User& player);
	void createAIPlayer(const game::User& player);
	void AddLabeltoUser(User& usr, const game::User& player);
	void setGameStates(const int& x, const int& y, const char& symbol);
	void addAtributestoUser(const game::User& player, const boost::shared_ptr<User>& usr);
	void buildLabels();

};

