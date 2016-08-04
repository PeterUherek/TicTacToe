#include "stdafx.h"
#include "HeuristicAlgorithm.h"
#include "RandomStrategy.h"


HeuristicAlgorithm::HeuristicAlgorithm(const int& depth) : depth(depth) {};
HeuristicAlgorithm::~HeuristicAlgorithm() {}

void HeuristicAlgorithm::setPawn(const boost::shared_ptr<Pawn>& pawn)
{
	this->pawn = pawn;
}

void HeuristicAlgorithm::UniquePositions(positionVec& positions) 
{
	std::sort(positions.begin(), positions.end());
	auto it = std::unique(positions.begin(), positions.end());
	positions.resize(std::distance(positions.begin(), it));
}

HeuristicAlgorithm::ptrMementoVec HeuristicAlgorithm::SelectPositions(Board &board)
{
	char label = pawn->GetLabel();
	ptrMementoVec savedStates = context->GetSavedStates();
	ptrMementoVec myStates(savedStates.size());

	auto it = copy_if(savedStates.begin(), savedStates.end(), myStates.begin(),
		[&label](const boost::shared_ptr<Memento>& mem) {
		return (mem->GetLabel()->GetLabel() == label);
	});

	myStates.resize(std::distance(myStates.begin(), it));
	return myStates;
}

void HeuristicAlgorithm::GenerateOptionalPositions(Board& board, const Memento& mem, positionVec& positions)
{
	int x = mem.GetXos();
	int y = mem.GetYos();

	for (int row = -1; row < 2; row++) {
		for (int col = -1; col < 2; col++) {
			if (board.CanAdd(x+row,y+col)) {
				std::tuple<int, int> pos(x+row, y+col);
				positions.push_back(pos);
			}
		}
	}
}

HeuristicAlgorithm::positionVec HeuristicAlgorithm::PrepareOptionalMoves(Board &board) 
{
	ptrMementoVec myStates = SelectPositions(board);
	positionVec positions;

	for (auto& mem : myStates) {
		GenerateOptionalPositions(board, *mem, positions);
	}

	UniquePositions(positions);
	return positions;
}

std::tuple<int, int> HeuristicAlgorithm::TryMoves(Board& board)
{	
	positionVec positions = PrepareOptionalMoves(board);
	std::vector<int> positionsScore;
	std::tuple<int, int> best;
	int score = 99;
	int counter = 1;

	for (auto &pos : positions) {

		int x = std::get<0>(pos);
		int y = std::get<1>(pos);

		boost::shared_ptr<Memento> mem(new Memento(pawn, x, y));
	    context->TryMove(mem);

		bool result = valid->IsWinner(x,y,pawn->GetLabel());
		positionsScore.push_back(valid->GetScore());

		if (result) {
			context->Undo();
			return std::tuple<int, int>(x, y);
		}

		int m_score = RecursiveFinding(board, counter);

		if (m_score < score) {
			score = m_score;
			best = std::tuple<int, int>(x, y);
		}
		context->Undo();
	}

	return best;
}

int HeuristicAlgorithm::RecursiveFinding(Board& board, int counter) 
{

	counter++;
	positionVec positions = PrepareOptionalMoves(board);
	std::vector<int> positionsScore;

	if (counter > depth)
		return counter;

	for (auto &pos : positions) {

		int x = std::get<0>(pos);
		int y = std::get<1>(pos);

		Memento mem(pawn, x, y);
		board.Add(mem);

		bool result = valid->IsWinner(x, y, pawn->GetLabel());
		positionsScore.push_back(valid->GetScore());
		
		board.Undo(mem);

		if (result)
			return counter;
	}

	auto it = std::max_element(positionsScore.begin(), positionsScore.end());
	int index = std::distance(std::begin(positionsScore), it);
	
	auto pos = positions[index];

	int x = std::get<0>(pos);
	int y = std::get<1>(pos);

	boost::shared_ptr<Memento> mem(new Memento(pawn, x, y));
	int m_score = 0;
	if (context->TryMove(mem)) {
		m_score = RecursiveFinding(board, counter);
		context->Undo();
	}

	return m_score;
}

HeuristicAlgorithm::positionVec HeuristicAlgorithm::ExtractOptionalMoves(Board &board, const Memento& mem)
{
	int x = mem.GetXos();
	int y = mem.GetYos();
	std::vector<std::tuple<int, int>> positions;

	for (int row = -1; row < x; row++) {
		for (int col = -1; col < y; col++) {
			if (board.IsOutRange(x + row, y + col)) {
				std::tuple<int, int> pos(row, col);
				positions.push_back(pos);
			}
		}
	}

	return positions;
}


std::tuple<int, int> HeuristicAlgorithm::FirstRound()
{
	RandomStrategy rand;
	rand.setGameContext(context);
	return rand.ChooseNextSetp();	
}

std::tuple<int, int> HeuristicAlgorithm::ChooseNextSetp()
{
	round++;
	if (round == 1)
	{
		return FirstRound();
	}
	else 
	{
		boost::shared_ptr<Board> boardPtr = context->GetBoard();
		valid = boost::shared_ptr<Validation>(new Validation(boardPtr, depth));

		std::tuple<int, int> best = TryMoves(*boardPtr);
		return best;
	}
}
