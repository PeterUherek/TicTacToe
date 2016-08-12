#include "stdafx.h"
#include "MultithreadWorker.h"


MultithreadWorker::MultithreadWorker(const ContextGame& con, const int& depth) : HeuristicAlgorithm(depth)
{
	 this->context = boost::make_shared<ContextGame>(con);
	 boost::shared_ptr<Board> boardPtr = context->GetBoard();
	 this->valid = boost::shared_ptr<Validation>(new Validation(boardPtr,depth));
}

MultithreadWorker::~MultithreadWorker(){}

std::vector<int> MultithreadWorker::scores;
boost::mutex MultithreadWorker::guard;

void MultithreadWorker::RecursiveFindingMultithread(int counter, int i)
{
	counter++;
	boost::shared_ptr<Board> board = context->GetBoard();
	positionVec positions = PrepareOptionalMoves(*board, *pawn);
	std::vector<int> positionsScore;

	if (counter > depth) {
		boost::mutex::scoped_lock lock(guard);
		scores.at(i) = counter;
		return;
	}

	for (auto &pos : positions) {

		int x = std::get<0>(pos);
		int y = std::get<1>(pos);

		Memento mem(pawn, x, y);
		board->Add(mem);

		bool result = valid->IsWinner(x, y, pawn->GetLabel());
		positionsScore.push_back(valid->GetScore());

		board->Undo(mem);

		if (result) {
			boost::mutex::scoped_lock lock(guard);
			scores.at(i) = counter;
			return;
		}
	}

	// Find maxium from vector
	int index = std::distance(std::begin(positionsScore), std::max_element(positionsScore.begin(), positionsScore.end()));

	auto pos = positions[index];

	int x = std::get<0>(pos);
	int y = std::get<1>(pos);

	boost::shared_ptr<Memento> mem(new Memento(pawn, x, y));
	int m_score = 0;
	if (context->TryMove(mem)) {
		m_score = RecursiveFinding(counter);
		context->Undo();
	}

	boost::mutex::scoped_lock lock(guard);
	scores.at(i) = m_score;
}

void MultithreadWorker::CleanScore()
{
	scores.clear();
}

void MultithreadWorker::InitScore()
{
	scores.push_back(0);
}

int MultithreadWorker::GetBestScoreIndex()
{
	auto it = std::min_element(scores.begin(), scores.end());
	return std::distance(scores.begin(), it);
}

int MultithreadWorker::RecursiveFinding(int counter)
{
	counter++;
	auto board = context->GetBoard();
	positionVec positions = PrepareOptionalMoves(*board, *pawn);
	std::vector<int> positionsScore;

	if (counter > depth)
		return counter;

	for (auto &pos : positions) {

		int x = std::get<0>(pos);
		int y = std::get<1>(pos);

		Memento mem(pawn, x, y);
		board->Add(mem);

		bool result = valid->IsWinner(x, y, pawn->GetLabel());
		positionsScore.push_back(valid->GetScore());

		board->Undo(mem);

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
	if (context->TryMove(mem))
	{
		m_score = RecursiveFinding(counter);
		context->Undo();
	}

	return m_score;
}

