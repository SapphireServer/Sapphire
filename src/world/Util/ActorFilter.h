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
    virtual bool conditionApplies( const Entity::GameObject& actor ) = 0;
  };

  using ActorFilterPtr = std::shared_ptr< ActorFilter >;

  /////////////////////////////////////////////////////////////////////////////
 
  class ActorFilterInRange : public ActorFilter
  {
    Common::FFXIVARR_POSITION3 m_aoePos;
    float m_radius;
  public:
    ActorFilterInRange( Common::FFXIVARR_POSITION3 aoePos, float range );
    bool conditionApplies( const Entity::GameObject& actor ) override;
  };

  /////////////////////////////////////////////////////////////////////////////

  class ActorFilterSingleTarget : public ActorFilter
  {
    uint32_t m_actorId;
  public:
    explicit ActorFilterSingleTarget( uint32_t actorId );
    bool conditionApplies( const Entity::GameObject& actor ) override;
  };
  
  /////////////////////////////////////////////////////////////////////////////

  class ActorFilterBox : public ActorFilter
  {
    Common::FFXIVARR_POSITION3 m_aoePos;
    uint16_t m_width;
    uint16_t m_height;
  public:
    explicit ActorFilterBox( Common::FFXIVARR_POSITION3 aoePos, uint16_t width, uint16_t height );
    bool conditionApplies( const Entity::GameObject& actor ) override;
  };
}

#endif
