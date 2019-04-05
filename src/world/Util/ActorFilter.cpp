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
  return Sapphire::Util::distance( m_startPos.x, m_startPos.y, m_startPos.z,
                               actor.getPos().x, actor.getPos().y, actor.getPos().z ) <= m_range;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
