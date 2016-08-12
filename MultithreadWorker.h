#pragma once
#include "Pawn.h"
#include "Validation.h"
#include "ContextGame.h"
#include "board.h"
#include "HeuristicAlgorithm.h"
#include <boost/shared_ptr.hpp>

class MultithreadWorker : public HeuristicAlgorithm
{
public:
	MultithreadWorker::MultithreadWorker(const ContextGame& context, const int& depth);
	~MultithreadWorker();

	void RecursiveFindingMultithread(int counter, int i);
	static void CleanScore();
	static void InitScore();
	static int GetBestScoreIndex();

private:
	int RecursiveFinding(int counter);

	// Multithread atributes
	static std::vector<int> scores;
	static boost::mutex guard;

};

