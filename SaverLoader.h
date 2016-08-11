#pragma once
#include <boost/shared_ptr.hpp>
#include "game.pb.h"

class SaverLoader
{

public:
	SaverLoader();
	~SaverLoader();

protected:
	const std::string saveFile = "SaveFile.pb";
	boost::shared_ptr<game::Game> nGame;

};

