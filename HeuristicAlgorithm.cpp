#include "stdafx.h"
#include "HeuristicAlgorithm.h"
#include "RandomStrategy.h"
#include "HeuristicTask.h"
#include "ThreadPool.h"
#include <boost/thread/thread.hpp>
#include <type_traits>


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

HeuristicAlgorithm::ptrMementoVec HeuristicAlgorithm::SelectPositions(Board &board, const Pawn& pawn)
{
	char label = pawn.GetLabel();
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

HeuristicAlgorithm::positionVec HeuristicAlgorithm::PrepareOptionalMoves(Board &board, const Pawn& pawn)
{
	ptrMementoVec myStates = SelectPositions(board, pawn);
	positionVec positions;

	for (auto& mem : myStates) {
		GenerateOptionalPositions(board, *mem, positions);
	}

	UniquePositions(positions);
	return positions;
}

std::tuple<int, int> HeuristicAlgorithm::TryMoves(Board& board, const boost::shared_ptr<Pawn>& pawn)
{	
	positionVec positions = PrepareOptionalMoves(board, *pawn);
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
		
		int m_score = RecursiveFinding(board, counter, pawn, *valid);

		if (m_score < score) {
			score = m_score;
			best = std::tuple<int, int>(x, y);
		}
		context->Undo();
	}

	return best;
}


std::tuple<int, int> HeuristicAlgorithm::TryMovesMultithread(Board& board, const boost::shared_ptr<Pawn>& pawn)
{
	positionVec positions = PrepareOptionalMoves(board, *pawn);
	
	std::vector<std::tuple<int,int>> vec;
	HeuristicTask::CleanScore();

	boost::shared_ptr<ThreadPool> tPool(new ThreadPool(20));

	std::vector<int> positionsScore;
	std::tuple<int, int> best;
	int counter = 1;
	int index = 0;

	for (auto &pos : positions) {

		int x = std::get<0>(pos);
		int y = std::get<1>(pos);

		boost::shared_ptr<Memento> mem(new Memento(pawn, x, y));
		context->TryMove(mem);

		bool result = valid->IsWinner(x, y, pawn->GetLabel());
		positionsScore.push_back(valid->GetScore());

		if (result) {
			context->Undo();
			return std::tuple<int, int>(x, y);
		}
		
		HeuristicTask::InitScore();

		boost::shared_ptr<HeuristicTask> task(new HeuristicTask(*context, depth,counter,index));
		task->setPawn(pawn);

		tPool->AddTask(task);
		//tgroup.create_thread(boost::bind(&HeuristicTask::Run, worker, counter, i));

		vec.push_back(std::tuple<int, int>(x, y));
		context->Undo();
		index++;
	}
	
	tPool->Finish();
	tPool->WaitForCompletion();

	int pos = HeuristicTask::GetBestScoreIndex();
	best = vec[pos];
	return best;
}


int HeuristicAlgorithm::RecursiveFinding(Board& board, int counter, const boost::shared_ptr<Pawn>& pawn, Validation& valid)
{
	counter++;
	positionVec positions = PrepareOptionalMoves(board, *pawn);
	std::vector<int> positionsScore;

	if (counter > depth)
		return counter;

	for (auto &pos : positions) {

		int x = std::get<0>(pos);
		int y = std::get<1>(pos);

		Memento mem(pawn, x, y);
		board.Add(mem);

		bool result = valid.IsWinner(x, y, pawn->GetLabel());
		positionsScore.push_back(valid.GetScore());
		
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
		m_score = RecursiveFinding(board, counter, pawn, valid);
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


boost::shared_ptr<Pawn> HeuristicAlgorithm::ChooseBestStrategy()
{
	int myScore, opponentScore;
	auto players = context->GetUsers();
	boost::shared_ptr<Pawn> _pawn;

	for (auto &player : players){
		if (player->GetPawn()->GetLabel() == pawn->GetLabel()) {
			myScore = player->GetLastSocre();
		}else {
			opponentScore = player->GetLastSocre();
			_pawn = player->GetPawn();
		}	
	}

	if(opponentScore <= myScore && opponentScore < 4)
	{
		_pawn = this->pawn;
	}
	
	return _pawn;
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
		boost::shared_ptr<Pawn> pawn = ChooseBestStrategy();
		
		//clock_t begin = clock();
		std::tuple<int, int> best = TryMovesMultithread(*boardPtr, pawn);
		//clock_t end = clock();

		//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		/**
		//std::cout << "Multithread function: " << elapsed_secs << std::endl;

		begin = clock();
		///best = TryMoves(*boardPtr, pawn);
		end = clock();

		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		//std::cout << "NoMultithread function: " << elapsed_secs << std::endl;
		*/

		return best;
	}
}
