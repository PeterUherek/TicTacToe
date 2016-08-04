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
	void setDesk(const int& x,const int& y) override;
	void setOptions(const int& opt) override;
	void addUser(const boost::shared_ptr<User>& usr) override;
	void assignPawns() override;
	void setValidator(const int& win) override;
	void setGameContext() override;

	int getOptions() override;
	int getNumberLabelsForWin() override;	
	virtual boost::shared_ptr<ContextGame> getGameContext() override;

private:
	typedef std::vector<boost::shared_ptr<Memento>> ptrMementoVec;

	// Atributes 
	int options;
	boost::shared_ptr<Validation> validator;
	boost::shared_ptr<ContextGame> context;
	
	std::vector<boost::shared_ptr<User>> players;
	std::map<boost::shared_ptr<User>, boost::shared_ptr<Pawn>,User::UserComparator> labelMap;

	// Inherited via IGame
	virtual void Play() override;
	virtual bool IsWin(const boost::shared_ptr<User>& player) override;
	virtual bool Save() override;
	
	// Own Functions 
	bool GameLoop();
	void WriteScore();
	void Move(const boost::shared_ptr<User>& player);
	void Unoredo(const ptrMementoVec& vec1, void (ContextGame::*unoredoFunction)());
	void Undo();
	void Redo();
	

	// Template functions 
	template<typename A>
	void VectorShuffle(A& vec)
	{
		std::srand(std::time(0));
		if((rand() % 2) == 1)
			std::random_shuffle(std::begin(vec), std::end(vec));
	}


};

