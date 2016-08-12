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

protected:
	typedef std::vector<boost::shared_ptr<Memento>> ptrMementoVec;
	typedef std::vector<std::tuple<int, int>> positionVec;

	// Atributes 
	int depth;
	int round = 0;
	boost::shared_ptr<Pawn> pawn;
	boost::shared_ptr<Validation> valid;

	// Find positions functions
	ptrMementoVec SelectPositions(Board &board, const Pawn& pawn);
	positionVec ExtractOptionalMoves(Board &board, const Memento& mem);
	void UniquePositions(HeuristicAlgorithm::positionVec& positions);
	positionVec PrepareOptionalMoves(Board &board, const Pawn& pawn);
	void GenerateOptionalPositions(Board& board, const Memento& mem, positionVec& positions);

private:
	// Functions
	std::tuple<int, int> TryMoves(Board& board, const boost::shared_ptr<Pawn>& pawn);
	std::tuple<int, int> TryMovesMultithread(Board& board, const boost::shared_ptr<Pawn>& pawn);
	int RecursiveFinding(Board& board, int counter, const boost::shared_ptr<Pawn>& pawn, Validation& valid);
	void RecursiveFindingMultithread(Board board, int counter, const boost::shared_ptr<Pawn>& pawn, int index);

	boost::shared_ptr<Pawn> ChooseBestStrategy();
	std::tuple<int, int> FirstRound();

};

