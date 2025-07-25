#include "ActionShapeLut.h"
#include "ActionShapeLutData.h"
#include <Logging/Logger.h>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace Sapphire;
using namespace Sapphire::World::Action;

ActionShapeLut::ConeLut ActionShapeLut::m_coneLut;

bool ActionShapeLutData::cacheShapes()
{
  std::fstream f;
  f.open( "data/actionShapes/cone.json" );

  if( !f.is_open() )
    return false;

  auto coneJSON = nlohmann::json::parse( f );

  for( auto& i : coneJSON.items() )
  {
    auto id = std::stoi( i.key() );
    auto cone = i.value().get< ConeEntry >();

    if( ActionShapeLut::m_coneLut.count( id ) > 0 )
      throw std::runtime_error( fmt::format( "Cone for action with ID {} cannot be defined more than once", i.key() ) );

    if( cone.startAngle < 0 )
      cone.startAngle += 360;
    if( cone.endAngle < 0 )
      cone.endAngle += 360;

    ActionShapeLut::m_coneLut.try_emplace( id, cone );
  }

  f.close();
  f.clear();

  // Repeat for new shapes here

  if( ActionShapeLut::m_coneLut.empty() )
    return false;

  return true;
}

bool ActionShapeLutData::reloadShapes()
{
  if( !ActionShapeLut::m_coneLut.empty() )
    ActionShapeLut::m_coneLut.clear();

  return cacheShapes();
}