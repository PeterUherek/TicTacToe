#include "stdafx.h"
#include "ContextGame.h"

#include <iostream>

ContextGame::ContextGame()
{
}


ContextGame::~ContextGame()
{
}

void ContextGame::setDesk(const int & x, const int & y)
{
	board = boost::shared_ptr<Board>(new Board(x, y));
}

void ContextGame::addUser(const boost::shared_ptr<User>& usr)
{
	players.push_back(usr);
}

void ContextGame::setOption(const int& opt)
{
	this->option = opt;
}

ContextGame::ptrMementoVec ContextGame::GetSavedStates() const 
{
	return savedStates;
}

ContextGame::ptrMementoVec ContextGame::GetOldStates() const 
{
	return oldStates;
}

boost::shared_ptr<Pawn> ContextGame::GetPawnFromUser(const boost::shared_ptr<User>& player)
{
	boost::shared_ptr<Pawn> pawn = labMap[player];
	return pawn;
}

boost::shared_ptr<Board> ContextGame::GetBoard() const
{
	return board;
}

void ContextGame::ClearOldStates()
{
	oldStates.clear();
}

void ContextGame::DrawBoard()
{
	board->DrawBoard();
}

ContextGame::ptrMemento ContextGame::GetLastState() const
{
	return savedStates.back();
}

ContextGame::ptrUserVec ContextGame::GetUsers() const
{
	return players;
}

void ContextGame::addUserToPawn(const boost::shared_ptr<User>& player, const boost::shared_ptr<Pawn>& pawn)
{
	labMap[player] = pawn;
}

int ContextGame::GetOption() const
{
	return option;
}

void ContextGame::Undo()
{
	Unoredo(savedStates, oldStates, &Board::Undo);
}

void ContextGame::Redo()
{
	Unoredo(oldStates, savedStates, &Board::Redo);
}

void ContextGame::Unoredo(ptrMementoVec& vec1, ptrMementoVec& vec2, void (Board::*unoredoFunction)(const Memento& mem))
{
	auto mem = vec1.back();

	(*board.*unoredoFunction)(*mem);

	vec1.pop_back();
	vec2.push_back(mem);
}

bool ContextGame::TryMove(const ptrMemento& mem)
{
	try {
		board->CheckAdd(*mem);
		board->Add(*mem);
		savedStates.push_back(mem);
	}
	catch (std::exception& e) {
		std::cout << " Bad move: '" << e.what() << "\n";
		return false;
	}
	return true;
}