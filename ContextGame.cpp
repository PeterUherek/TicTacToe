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

ContextGame::ptrMementoVec ContextGame::GetSavedStates()
{
	return savedStates;
}

ContextGame::ptrMementoVec ContextGame::GetOldStates()
{
	return oldStates;
}

boost::shared_ptr<Board> ContextGame::GetBoard()
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

ContextGame::ptrMemento ContextGame::GetLastState()
{
	return savedStates.back();
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