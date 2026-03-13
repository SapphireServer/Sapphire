#define GLM_ENABLE_EXPERIMENTAL
#include <datReaderPs3/GameData.h>
#include <datReaderPs3/File.h>
#include <datReaderPs3/DatCat.h>
#include <datReaderPs3/ExdData.h>
#include <datReaderPs3/ExdCat.h>
#include <datReaderPs3/Exd.h>
#include <datReaderPs3/Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include "ExdData.h"
#include <datReaderPs3/Exd/Structs.h>
#include <Logging/Logger.h>
#include <Common.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <streambuf>
#include <regex>

#include <filesystem>

#include "Application.h"

namespace fs = std::filesystem;

using namespace Sapphire;
Data::ExdData g_exdDataGen;


int main( int argc, char* argv[] )
{
  auto app = std::make_shared< Engine::Application >( "Sapphire-Toolkit" );

  app->init();
  app->mainLoop();




  return 0;
}
