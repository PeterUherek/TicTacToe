#include "stdafx.h"
#include "SaverLoader.h"
#include <sys/stat.h>



SaverLoader::SaverLoader()
{
	nGame = boost::shared_ptr<game::Game>(new game::Game());
}


SaverLoader::~SaverLoader()
{
	google::protobuf::ShutdownProtobufLibrary();
}

 bool SaverLoader::existFile(const std::string& name) 
{
	 struct stat buffer;
	 return (stat(name.c_str(), &buffer) == 0);
}

 const std::string SaverLoader::saveFile  = "SaveFile.pb";