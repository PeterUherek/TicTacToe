#pragma once
#include <boost/make_shared.hpp>

#include "board.h"
#include "Memento.h"

class Validation
{

public:
	Validation(const boost::shared_ptr<Board>& board, int win);
	bool IsWinner(const int& x, const int& y, const char& label);
	int GetNumberLabelsForWin() const;
	int GetScore() const;
	
private:
	typedef enum { UP, DOWN, RIGHT, LEFT, NO } direction;
	boost::shared_ptr<Board> board;
	int score; // Score for AI algorithm
	int win; //Num of labels in line for win; 

	void ChangeIndex(int& index, direction direct);
	void RecursiveControl(int x, int y, const char& label, int& counter, direction direct1, direction direct2);
};

