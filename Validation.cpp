#include "stdafx.h"
#include "Validation.h"


Validation::Validation(const boost::shared_ptr<Board>& board, int win) 
{	
	this->board = board;
	this->win = win;
}

int Validation::GetScore() const
{
	return score;
}

int Validation::GetNumberLabelsForWin() const
{
	return win;
}

bool Validation::IsWinner(const int& x, const int& y, const char& label)
{
	this->score = 0;

	boost::shared_ptr<std::vector<int>> vec (new std::vector<int>(4));

	int winCounter = -1;
	RecursiveControl(x, y, label, winCounter, UP, NO);
	RecursiveControl(x, y, label, winCounter, DOWN, NO);
	vec->push_back(winCounter);
	if (winCounter == win)
		return true;

	winCounter = -1;
	RecursiveControl(x, y, label, winCounter, NO, LEFT);
	RecursiveControl(x, y, label, winCounter, NO, RIGHT);
	vec->push_back(winCounter);
	if (winCounter == win)
		return true;

	winCounter = -1;
	RecursiveControl(x, y, label, winCounter, UP, LEFT);
	RecursiveControl(x, y, label, winCounter, DOWN, RIGHT);
	vec->push_back(winCounter);
	if (winCounter == win)
		return true;

	winCounter = -1;
	RecursiveControl(x, y, label, winCounter, UP, RIGHT);
	RecursiveControl(x, y, label, winCounter, DOWN, LEFT);
	vec->push_back(winCounter);
	if (winCounter == win)
		return true;

	int max_score = *std::max_element(vec->begin(), vec->end());
	score = max_score-1;

	return false;
}

void Validation::ChangeIndex(int& index, direction direct)
{
	switch (direct)
	{
	case Validation::LEFT:
	case Validation::DOWN:
		index--;
		break;
	case Validation::RIGHT:
	case Validation::UP:
		index++;
		break;
	}
}

void Validation::RecursiveControl(int x, int y, const char& label, int& counter, direction direct1, direction direct2) {
	Board::board_array desk = board->GetDesk();
	
	if (board->IsOutRange(x, y))
		return;

	if (desk[x][y] == label) {
		counter++;
		ChangeIndex(x, direct1);
		ChangeIndex(y, direct2);

		RecursiveControl(x, y, label, counter, direct1, direct2);
	}

	return;
}

