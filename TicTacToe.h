#pragma once
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <ctime>

#include "game.h"
#include "board.h"
#include "User.h"
#include "Pawn.h"
#include "Memento.h"
#include "Validation.h"
#include "ContextGame.h"

class TicTacToe : public IGame
{

public:
	TicTacToe();
	~TicTacToe();

	// Inherited via IGame
	void Play() override;

	void setValidator(const int& win) override;
	void setGameContext(const boost::shared_ptr<ContextGame>& context) override;

	int getNumberLabelsForWin() override;	
	boost::shared_ptr<ContextGame> getGameContext() override;

private:
	typedef std::vector<boost::shared_ptr<Memento>> ptrMementoVec;
	
	// Atributes 
	boost::shared_ptr<Validation> validator;
	boost::shared_ptr<ContextGame> context;	

	// Inherited via IGame
	bool IsWin(const boost::shared_ptr<User>& player) override;
	void Save(const boost::shared_ptr<User>& player) override;
	
	// Own Functions 
	bool GameLoop();
	void WriteScore();
	void Move(const boost::shared_ptr<User>& player);
	void Unoredo(const ptrMementoVec& vec1, void (ContextGame::*unoredoFunction)());
	void Undo();
	void Redo();

};

