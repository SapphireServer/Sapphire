#include "ActorFilter.h"
#include "Actor/GameObject.h"
#include "Util/Util.h"
#include "Util/UtilMath.h"


Sapphire::World::Util::ActorFilterInRange::ActorFilterInRange( Common::FFXIVARR_POSITION3 startPos,
                                                               float radius ) :
  m_aoePos( startPos ),
  m_radius( radius )
{
}

bool Sapphire::World::Util::ActorFilterInRange::conditionApplies( const Entity::GameObject& actor )
{
  return Sapphire::Common::Util::distance( m_aoePos, actor.getPos() ) <= m_radius;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

Sapphire::World::Util::ActorFilterSingleTarget::ActorFilterSingleTarget( uint32_t actorId ) :
  m_actorId( actorId )
{
}

bool Sapphire::World::Util::ActorFilterSingleTarget::conditionApplies( const Sapphire::Entity::GameObject& actor )
{
  return actor.getId() == m_actorId;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

Sapphire::World::Util::ActorFilterBox::ActorFilterBox( Common::FFXIVARR_POSITION3 aoePos, uint16_t width, uint16_t height ) :
  m_aoePos( aoePos ),
  m_width( width ),
  m_height( height )
{
}

bool Sapphire::World::Util::ActorFilterBox::conditionApplies( const Sapphire::Entity::GameObject& actor )
{
  return actor.getPos().x < m_aoePos.x + m_width &&
      actor.getPos().x > m_aoePos.x &&
      actor.getPos().y < m_aoePos.y + m_height &&
      actor.getPos().y > m_aoePos.y;
}
