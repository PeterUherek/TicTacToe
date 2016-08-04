#include "stdafx.h"
#include "board.h"
#include "boost/multi_array.hpp"
	
#include <iostream>
#include <iomanip>
#include <stdexcept>  
#include <stdlib.h>

void Board::SetDesk()
{
	desk.resize(x, std::vector<char>(y,emptySquare));
}

Board::Board(const int& x, const int& y)
{
	this->x = x;
	this->y = y;
	
	SetDesk();
};		

const Board::board_array Board::GetDesk() {
	return this->desk;
};

Board::~Board() {};

void Board::Add(const Memento& mem) {
	int x = mem.GetXos();
	int y = mem.GetYos();
	boost::shared_ptr<Pawn> label = mem.GetLabel();

	desk[x][y] = label->GetLabel();
}

bool Board::CanAdd(const int& x, const int& y) {

	if (IsOutRange(x, y))
		return false;

	char label = desk[x][y];
	if (label != emptySquare)
		return false;

	return true;
}

void Board::CheckAdd(const Memento& mem){
	int x = mem.GetXos();
	int y = mem.GetYos();

	if(IsOutRange(x, y))
		throw std::out_of_range("Out of the range");

	char label = desk[x][y];
	if (label != emptySquare)
		throw std::exception("Square is taken");
};

bool Board::IsOutRange(const int& x, const int& y)
{
	return (x >= this->x || x < 0 || y >= this->y || y < 0) ? true : false;
}

void Board::Undo(const Memento& mem)
{
	int x = mem.GetXos();
	int y = mem.GetYos();

	desk[x][y] = emptySquare;
};

void Board::Redo(const Memento& mem) 
{
	Add(mem);
};

void Board::DrawBoard()
{
	system("cls");

	for (int col = 0; col < y; col++) {
		if (col == 0)
			std::cout << std::setw(3) << col;
		else
			std::cout << std::setw(2) << col;
	}

	for (int row = 0; row < x; row++) {
		std::cout << std::endl;
		std::cout << row << std::setw(2) << std::endl;

		for (int col = 0; col < y; col++)
			std::cout << " " << desk[row][col];
	}
	std::cout << std::endl;
};

void Board::Clear() {
	SetDesk();
};

char Board::GetEmptySquare()
{
	return emptySquare;
}

int Board::GetX(){
	return x;
};

int Board::GetY(){
	return y;
};



