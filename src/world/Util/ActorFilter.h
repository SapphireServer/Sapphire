#ifndef _WORLD_UTIL_H
#define _WORLD_UTIL_H

#include <stdint.h>
#include <string>
#include <functional>
#include <ForwardsZone.h>
#include <Util/Util.h>

namespace Sapphire::World::Util
{
  class ActorFilter
  {
  public:
    ActorFilter() = default;
    virtual ~ActorFilter() = default;
    virtual bool conditionApplies( const Entity::Actor& actor ) = 0;
  };

  using ActorFilterPtr = std::shared_ptr< ActorFilter >;

  /////////////////////////////////////////////////////////////////////////////
 
  class ActorFilterInRange : public ActorFilter
  {
    Common::FFXIVARR_POSITION3 m_startPos;
    float m_range;
  public:
    ActorFilterInRange( Common::FFXIVARR_POSITION3 startPos, float range );
    bool conditionApplies( const Entity::Actor& actor ) override;
  };

  /////////////////////////////////////////////////////////////////////////////

  class ActorFilterSingleTarget : public ActorFilter
  {
    uint32_t m_actorId;
  public:
    explicit ActorFilterSingleTarget( uint32_t actorId );
    bool conditionApplies( const Entity::Actor& actor ) override;
  };
}

#endif
