#pragma once
#include "AlgorithmStrategy.h"
#include "Validation.h"

class HeuristicAlgorithm : public AlgorithmStrategy
{
public:
	HeuristicAlgorithm(const int& depth);
	~HeuristicAlgorithm();

	// Inherited via AlgorithmStrategy
	std::tuple<int, int> ChooseNextSetp() override;
	void setPawn(const boost::shared_ptr<Pawn>& pawn) override;

private:
	typedef std::vector<boost::shared_ptr<Memento>> ptrMementoVec;
	typedef std::vector<std::tuple<int, int>> positionVec;

	// Atributes 
	int depth;
	int round = 0;
	boost::shared_ptr<Pawn> pawn;
	boost::shared_ptr<Validation> valid;
	boost::shared_ptr<ContextGame> testContext;

	// Functions
	std::tuple<int, int> HeuristicAlgorithm::TryMoves(Board& board);
	int HeuristicAlgorithm::RecursiveFinding(Board& board, int counter);

	std::tuple<int, int> FirstRound();
	ptrMementoVec SelectPositions(Board &board);
	positionVec ExtractOptionalMoves(Board &board, const Memento& mem);
	void UniquePositions(HeuristicAlgorithm::positionVec& positions);
	positionVec PrepareOptionalMoves(Board &board);
	void GenerateOptionalPositions(Board& board, const Memento& mem, positionVec& positions);

};

