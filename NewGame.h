#pragma once
#include "GameBuilder.h"
#include "AlgorithmStrategy.h"
#include "HeuristicAlgorithm.h"
#include "ContextGame.h"
#include "RandomStrategy.h"
#include "HumanUser.h"
#include "AIUser.h"


class NewGame : public GameBuilder
{

public:
	NewGame();
	~NewGame();

	// Inherited via GameBuilder
	void buildBoard() override;
	void buildUser() override;
	void buildOptions() override;
	void buildLabels() override;
	void buildValidator() override;

private:
	void createAIPlayer();
	void createHumanPlayer();

};

