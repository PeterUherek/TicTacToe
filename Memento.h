#pragma once
#include <string>
#include "boost/shared_ptr.hpp"
#include "Pawn.h"

class Memento
{
public:
	Memento(const boost::shared_ptr<Pawn>& label, const int& x, const int& y);
	
	int GetXos() const;
	int GetYos() const;
	boost::shared_ptr<Pawn> GetLabel() const;

	~Memento();

private:
	int x;
	int y;
	boost::shared_ptr<Pawn> label;

};

