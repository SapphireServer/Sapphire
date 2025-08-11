#define GLM_ENABLE_EXPERIMENTAL
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <Exd/ExdData.h>
#include <Exd/Structs.h>
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
Sapphire::Data::ExdData g_exdDataGen;


int main( int argc, char* argv[] )
{
  auto app = std::make_shared< Engine::Application >( "Sapphire-Toolkit" );

  app->init();
  app->mainLoop();




  return 0;
}
