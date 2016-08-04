#include "stdafx.h"
#include "Memento.h"

Memento::Memento(const boost::shared_ptr<Pawn>& label, const int& x, const int& y) : label(label), x(x), y(y) {};

Memento::~Memento() {};

int Memento::GetXos() const { return this->x; }
int Memento::GetYos() const { return this->y; }
boost::shared_ptr<Pawn> Memento::GetLabel() const { return this->label; }




