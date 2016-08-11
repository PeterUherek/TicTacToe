#include "stdafx.h"
#include "SaverLoader.h"


SaverLoader::SaverLoader()
{
	nGame = boost::shared_ptr<game::Game>(new game::Game());
}


SaverLoader::~SaverLoader()
{
	google::protobuf::ShutdownProtobufLibrary();
}
