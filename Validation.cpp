#include "stdafx.h"
#include "Validation.h"
#include <boost/thread/thread.hpp>


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
	vec.clear();
	clock_t begin = clock();
	//IsWinnerMultiThread(x, y, label);
	clock_t end = clock();
	
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//std::cout << "Multithread function: " << elapsed_secs << std::endl;

	begin = clock();
	IsWinnerNoMultiThread(x, y, label);
	end = clock();

	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//std::cout << "NoMultithread function: " << elapsed_secs << std::endl;

	return winner;
}

bool Validation::IsWinnerNoMultiThread(const int& x, const int& y, const char& label) 
{
	int m_score = score;
	this->score = 0;

	int winCounter = -1;
	RecursiveControl(x, y, label, winCounter, UP, NO);
	RecursiveControl(x, y, label, winCounter, DOWN, NO);
	vec.push_back(winCounter);
	if (winCounter == win)
		return true;

	winCounter = -1;
	RecursiveControl(x, y, label, winCounter, NO, LEFT);
	RecursiveControl(x, y, label, winCounter, NO, RIGHT);
	vec.push_back(winCounter);
	if (winCounter == win)
		return true;

	winCounter = -1;
	RecursiveControl(x, y, label, winCounter, UP, LEFT);
	RecursiveControl(x, y, label, winCounter, DOWN, RIGHT);
	vec.push_back(winCounter);
	if (winCounter == win)
		return true;

	winCounter = -1;
	RecursiveControl(x, y, label, winCounter, UP, RIGHT);
	RecursiveControl(x, y, label, winCounter, DOWN, LEFT);
	vec.push_back(winCounter);
	if (winCounter == win)
		return true;

	score = *std::max_element(vec.begin(), vec.end());
	vec.clear();
}

void Validation::IsWinnerMultiThread(const int& x, const int& y, const char& label)
{	
	this->score = 0;
	this->winner = false;
	boost::thread_group tgroup;
	std::vector<direction> dir;

	// Up and Down way
	dir = { UP, NO, DOWN, NO };
	tgroup.create_thread(boost::bind(&Validation::Worker, this, x, y, label, dir));

	// Left and Right way
	dir = { NO, LEFT, NO, RIGHT };
	tgroup.create_thread(boost::bind(&Validation::Worker, this, x, y, label, dir));
	
	// Diagnol way 
	dir = { UP, LEFT, DOWN, RIGHT };
	tgroup.create_thread(boost::bind(&Validation::Worker, this, x, y, label, dir));
	
	// Diagonal way 
	dir = { UP, RIGHT, DOWN, LEFT };
	tgroup.create_thread(boost::bind(&Validation::Worker, this, x, y, label, dir));
	
	tgroup.join_all();
	
	score = *std::max_element(vec.begin(), vec.end());
	vec.clear();
}

void Validation::Worker(const int& x, const int& y, const char& label, const std::vector<direction>& dir)
{
	int winCounter = -1;
	RecursiveControl(x, y, label, winCounter, dir[0], dir[1]);
	RecursiveControl(x, y, label, winCounter, dir[2], dir[3]);
	
	boost::mutex::scoped_lock lock(guard);
	vec.push_back(winCounter);
	
	if (winCounter == win) {
		winner = true;
	}

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

	/**
	for (int i = 0; i < 10000000; i++) {
		int p = 3;
	}
	*/

	if (desk[x][y] == label) 
	{
		counter++;
		ChangeIndex(x, direct1);
		ChangeIndex(y, direct2);

		RecursiveControl(x, y, label, counter, direct1, direct2);
	}

	return;
}


