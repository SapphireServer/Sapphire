#pragma once

#include "Common.h"
#include <cstdint>
#include <unordered_map>
#include <vector>
#include "Service.h"

namespace Sapphire::World::Action
{
  struct ConeEntry
  {
    float startAngle;
    float endAngle;
  };

  class ActionShapeLut
  {
  public:
    using ConeLut = std::unordered_map< uint16_t, ConeEntry >;

    static bool validConeEntryExists( uint16_t actionId );

    static const ConeEntry& getConeEntry( uint16_t actionId );

    // Process-wide accessor through the Service locator
    static ConeLut& lut()
    {
      if( Sapphire::Common::Service< ConeLut >::empty() )
        Sapphire::Common::Service< ConeLut >::set< ConeLut >();
      return Sapphire::Common::Service< ConeLut >::ref();
    }
  };
}
