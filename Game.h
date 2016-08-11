#ifndef IGame_h__
#define IGame_h__

#pragma once
#include "User.h"
#include "ContextGame.h"

class IGame
{

public:
	virtual ~IGame() {};

	virtual void Play() = 0;
	virtual void setValidator(const int& win) = 0;
	virtual void setGameContext(const boost::shared_ptr<ContextGame>& context) = 0;

	virtual boost::shared_ptr<ContextGame> getGameContext() = 0;
	virtual int getNumberLabelsForWin() = 0;

private:
	virtual bool IsWin(const boost::shared_ptr<User>& player) = 0;
	virtual void Save(const boost::shared_ptr<User>& player) = 0;
};

#endif

