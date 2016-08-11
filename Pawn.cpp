#include "stdafx.h"
#include "Pawn.h"


Pawn::Pawn(char symbol, std::string color): label(symbol), color(color) {};
Pawn::Pawn() {}
Pawn::~Pawn() {}

const char vinit[] = { 'x' ,'o' };
const std::vector<char> Pawn::symbols(vinit, std::end(vinit));
const std::vector<char> Pawn::GetSymbols() { return symbols; }

char Pawn::GetLabel() const { return label; }
