#include "ActionShapeLut.h"
#include "Common.h"
#include <nlohmann/json.hpp>

namespace Sapphire::World::Action
{
  class ActionShapeLutData
  {
  public:
    static bool cacheShapes();

    static bool reloadShapes();
  };

  inline void from_json( const nlohmann::json& j, ConeEntry& coneEntry )
  {
    j.at( "start" ).get_to( coneEntry.startAngle );
    j.at( "end" ).get_to( coneEntry.endAngle );
  }
}
