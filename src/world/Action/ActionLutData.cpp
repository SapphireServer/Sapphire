#include "ActionLut.h"
#include "ActionLutData.h"
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace Sapphire::World::Action;
namespace fs = std::filesystem;

ActionLut::Lut ActionLut::m_actionLut;

bool ActionLutData::cacheActions()
{
  std::fstream f;

  for( auto& p : fs::recursive_directory_iterator( "data/actions/" ) )
  {
    if( p.path().extension() == ".json" )
    {
      f.open( p.path() );

      if( !f.is_open() )
        return false;

      auto actionJSON = nlohmann::json::parse( f );

      for( auto& i : actionJSON.items() )
      {
        auto id = std::stoi( i.key() );
        auto action = i.value().get< ActionEntry >();
        ActionLut::m_actionLut.try_emplace( id, action );
      }

      f.close();
      f.clear();
    }
  }

  if( ActionLut::m_actionLut.empty() )
    return false;

  return true;
}

bool ActionLutData::reloadActions()
{
  if( !ActionLut::m_actionLut.empty() )
    ActionLut::m_actionLut.clear();

  return cacheActions();
}