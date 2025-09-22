#include "ActionShapeLut.h"
#include "ActionShapeLutData.h"
#include "Util/UtilMath.h"
#include <Logging/Logger.h>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace Sapphire;
using namespace Sapphire::World::Action;


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

    if( ActionShapeLut::lut().count( static_cast< uint16_t >( id ) ) > 0 )
      throw std::runtime_error( fmt::format( "Cone for action with ID {} cannot be defined more than once", i.key() ) );

    if( cone.startAngle < -180 )
      cone.startAngle += 360;
    if( cone.startAngle >= 180 )
      cone.startAngle -= 360;
    if( cone.endAngle < -180 )
      cone.endAngle += 360;
    if( cone.endAngle >= 180 )
      cone.endAngle -= 360;

    cone.startAngle = Sapphire::Common::Util::degreesToRadians( cone.startAngle );
    cone.endAngle = Sapphire::Common::Util::degreesToRadians( cone.endAngle );

    ActionShapeLut::lut().try_emplace( static_cast< uint16_t >( id ), cone );
  }

  f.close();
  f.clear();

  // Repeat for new shapes here

  if( ActionShapeLut::lut().empty() )
    return false;

  return true;
}

bool ActionShapeLutData::reloadShapes()
{
  if( !ActionShapeLut::lut().empty() )
    ActionShapeLut::lut().clear();

  return cacheShapes();
}
