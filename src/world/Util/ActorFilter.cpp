#include "ActorFilter.h"
#include "Actor/Actor.h"
#include "Util/Util.h"
#include "Util/UtilMath.h"


Sapphire::World::Util::ActorFilterInRange::ActorFilterInRange( Common::FFXIVARR_POSITION3 startPos,
                                                               float range ) :
  m_startPos( startPos ),
  m_range( range )
{
}

bool Sapphire::World::Util::ActorFilterInRange::conditionApplies( const Entity::Actor& actor )
{
  return Sapphire::Util::distance( m_startPos, actor.getPos() ) <= m_range;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

Sapphire::World::Util::ActorFilterSingleTarget::ActorFilterSingleTarget( uint32_t actorId ) :
  m_actorId( actorId )
{
}

bool Sapphire::World::Util::ActorFilterSingleTarget::conditionApplies( const Sapphire::Entity::Actor& actor )
{
  return actor.getId() == m_actorId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////