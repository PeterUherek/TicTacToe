#include "stdafx.h"
#include "TicTacToe.h"
#include "HumanUser.h"
#include "ConsoleManager.h"
#include "SaveGame.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>


TicTacToe::TicTacToe() {}

void TicTacToe::setValidator(const int& win) 
{
	validator = boost::shared_ptr<Validation>(new Validation(context->GetBoard(), win));
}

void TicTacToe::setGameContext(const boost::shared_ptr<ContextGame>& context)
{
	this->context = context;
}

boost::shared_ptr<ContextGame> TicTacToe::getGameContext()
{
	return context;
}

int TicTacToe::getNumberLabelsForWin()
{
	return validator->GetNumberLabelsForWin();
}

void TicTacToe::Play()
{	
	system("color 3A");
	bool gameEnd = false;

	std::cout << "Game start" << std::endl;
	context->DrawBoard();
	
	do {
		gameEnd = GameLoop();
	}while (!gameEnd);

}

bool TicTacToe::IsWin(const boost::shared_ptr<User>& player)
{
	boost::shared_ptr<Memento> mem = context->GetLastState();
	int x = mem->GetXos();
	int y = mem->GetYos();

	boost::shared_ptr<Pawn> pawn = mem->GetLabel();
	char label = pawn->GetLabel();

	if (validator->IsWinner(x, y, label)) 
	{
		std::cout << "Winner is " << player->getName() << std::endl;
		return true;
	}

	player->setScore(validator->GetScore());
	return false;
}


bool TicTacToe::GameLoop() 
{
	auto players = context->GetUsers();
	for (auto& player : players) {

		bool playerTurn = false;
		do {
			int key = player->Action();

			switch (key) {
			case 1:
				Move(player);
				context->DrawBoard();

				if (IsWin(player)) 
				{
					return true;
				}

				WriteScore();
				context->ClearOldStates();
				playerTurn = false;
				break;
			case 2:
				Undo();
				playerTurn = true;
				break;
			case 3:
				Redo();
				playerTurn = true;
				break;
			case 4:
				Save(player);
				playerTurn = true;
				break;
			}
		} while (playerTurn);

	}
	return false;
}


void TicTacToe::Undo()
{
	Unoredo(context->GetSavedStates(), &ContextGame::Undo);
}

void TicTacToe::Redo()
{
	Unoredo(context->GetOldStates(), &ContextGame::Redo);
}

void TicTacToe::Unoredo(const ptrMementoVec& vec, void (ContextGame::*unoredoFunction)())
{
	if (vec.size() < 2)
	{
		std::cout << "Nothing to do!";
		return;
	}

	for (int n = 1; n <= 2; ++n) 
	{
		(*context.*unoredoFunction)();
	}

	context->DrawBoard();
}


void TicTacToe::Move(const boost::shared_ptr<User>& player) 
{	
	boost::shared_ptr<Memento> mem;

	do {
		std::tuple<int, int> move = player->Move();
		boost::shared_ptr<Pawn> pawn = context->GetPawnFromUser(player);
		mem = boost::shared_ptr<Memento>(new Memento(pawn, std::get<0>(move), std::get<1>(move)));
	} while (!context->TryMove(mem));

}

void TicTacToe::WriteScore()
{	
	auto players = context->GetUsers();
	for (auto &player : players)
	{
		std::cout << player->getName() << ": " << player->GetBestScore() << "  ";
	}

	std::cout << std::endl;
}

void TicTacToe::Save(const boost::shared_ptr<User>& player)
{
	boost::shared_ptr<SaveGame> saver(new SaveGame());
	if (saver->Save(*context, *player) >= 0) {
		std::cout << "You save the game!" << std::endl;
	}

}

TicTacToe::~TicTacToe() {}

