#pragma once

#include "Common.h"
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace Sapphire::World::Action
{
  struct ConeEntry {
    float startAngle;
    float endAngle;
  };

  class ActionShapeLut
  {
  public:
    using ConeLut = std::unordered_map< uint16_t, ConeEntry >;

    static bool validConeEntryExists( uint16_t actionId );
    static const ConeEntry& getConeEntry( uint16_t actionId );

    static ConeLut m_coneLut;
  };
}
