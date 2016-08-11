#pragma once
#include "board.h"
#include "Memento.h"
#include "User.h"

#include <map>
#include <algorithm>

class ContextGame
{
public:
	typedef std::vector<boost::shared_ptr<Memento>> ptrMementoVec;
	typedef boost::shared_ptr<Memento> ptrMemento;
	typedef std::vector<boost::shared_ptr<User>> ptrUserVec;
	typedef std::map<boost::shared_ptr<User>, boost::shared_ptr<Pawn>, User::UserComparator> LabelMap;
	ContextGame();
	~ContextGame();

	void setDesk(const int& x, const int& y);
	void addUser(const boost::shared_ptr<User>& usr);
	void setOption(const int& opt);
	void addUserToPawn(const boost::shared_ptr<User>& player, const boost::shared_ptr<Pawn>& pawn);
	
	boost::shared_ptr<Pawn> GetPawnFromUser(const boost::shared_ptr<User>& player);
	boost::shared_ptr<Board> GetBoard() const;
	ptrMementoVec GetSavedStates() const;
	ptrMementoVec GetOldStates() const;
	ptrMemento GetLastState() const;
	ptrUserVec GetUsers() const;
	int GetOption() const;

	void Undo();
	void Redo();
	void DrawBoard();
	void ClearOldStates();
	bool TryMove(const ptrMemento& mem);

private:
	// Atributes
	LabelMap labMap;
	boost::shared_ptr<Board> board;
	ptrMementoVec savedStates;
	ptrMementoVec oldStates;
	ptrUserVec players;
	int option;

	// Functions
	void Unoredo(ptrMementoVec& vec1, ptrMementoVec& vec2, void (Board::*unoredoFunction)(const Memento& mem));

};

