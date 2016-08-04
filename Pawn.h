#pragma once
#include <vector>
#include <string>
#include <boost/assign/list_of.hpp>

class Pawn
{
public:
	Pawn(char label, std::string color);
	Pawn();
	~Pawn();

	char GetLabel();
	static const std::vector<char> GetSymbols();

private:
	char label;
	std::string color;
	static const std::vector<char> symbols;
};

