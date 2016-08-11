#pragma once
#include <boost/shared_ptr.hpp>
#include "game.pb.h"

class SaverLoader
{

public:
	SaverLoader();
	~SaverLoader();

	static bool existFile(const std::string& name);
	static const std::string saveFile;
protected:
	boost::shared_ptr<game::Game> nGame;

};

