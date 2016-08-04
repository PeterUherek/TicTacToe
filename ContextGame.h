#pragma once
#include "board.h"
#include "Memento.h"

class ContextGame
{
public:
	typedef std::vector<boost::shared_ptr<Memento>> ptrMementoVec;
	typedef boost::shared_ptr<Memento> ptrMemento;

	ContextGame();
	~ContextGame();

	void setDesk(const int& x, const int& y);
	boost::shared_ptr<Board> GetBoard();
	ptrMementoVec GetSavedStates();
	ptrMementoVec GetOldStates();
	ptrMemento GetLastState();

	void Undo();
	void Redo();
	void DrawBoard();
	void ClearOldStates();
	bool TryMove(const ptrMemento& mem);

private:
	boost::shared_ptr<Board> board;
	ptrMementoVec savedStates;
	ptrMementoVec oldStates;

	void Unoredo(ptrMementoVec& vec1, ptrMementoVec& vec2, void (Board::*unoredoFunction)(const Memento& mem));

};

