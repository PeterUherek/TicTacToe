#pragma once
#include "Memento.h";

class Board
{
public:
	//typedef boost::multi_array<char, 2> board_array;
	typedef std::vector<std::vector<char>> board_array;

	Board(const int& x, const int& y);
	~Board();

	void CheckAdd(const Memento& mem);
	bool CanAdd(const int& x, const int& y);
	bool IsOutRange(const int& x, const int& y);

	void Add(const Memento& mem);
	void Undo(const Memento& mem);
	void Redo(const Memento& mem);
	void DrawBoard();
	void Clear();

	char GetEmptySquare();
	int GetX();
	int GetY();

	const board_array GetDesk();

private:
	const char emptySquare = '-';
	void SetDesk();

	int x;
	int y;
	board_array desk;

};

