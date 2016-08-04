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
	virtual void setDesk(const int& x,const int& y) = 0;
	virtual void setOptions(const int& opt) = 0;
	virtual void addUser(const boost::shared_ptr<User>& usr) = 0;
	virtual void setValidator(const int& win) = 0;
	virtual void setGameContext() = 0;
	virtual void assignPawns() = 0;

	virtual boost::shared_ptr<ContextGame> getGameContext() = 0;
	virtual int getOptions() = 0;
	virtual int getNumberLabelsForWin() = 0;

private:
	virtual bool IsWin(const boost::shared_ptr<User>& player) = 0;
	virtual bool Save() = 0;
};

#endif

