#include "stdafx.h"
#include "RandomStrategy.h"
#include <ctime>


RandomStrategy::RandomStrategy()
{
	srand(time(NULL));
}


RandomStrategy::~RandomStrategy()
{
}

std::tuple<int, int> RandomStrategy::ChooseNextSetp()
{
	int x, y;

	boost::shared_ptr<Board> board = context->GetBoard();
	Board::board_array desk = board->GetDesk();

	do{
		x = GetRandomNum(0, board->GetX()-1);
		y = GetRandomNum(0, board->GetY()-1);
	} while (desk[x][y] != board->GetEmptySquare());

	return std::tuple<int, int>(x,y);
}

int RandomStrategy::GetRandomNum(const int& min, const int& max)
{
	return min + (rand() % (int)(max - min + 1));
}

void RandomStrategy::setPawn(const boost::shared_ptr<Pawn>& pawn) {}
