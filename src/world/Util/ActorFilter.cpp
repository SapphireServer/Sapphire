#include "ActorFilter.h"
#include "Actor/GameObject.h"
#include "Util/Util.h"
#include "Util/UtilMath.h"
#include <math.h>


Sapphire::World::Util::ActorFilterInRange::ActorFilterInRange( Common::FFXIVARR_POSITION3 aoePos,
                                                               float radius ) :
  m_aoePos( aoePos ),
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
///////////////////////////////////////////////////////////////////////////////////////////////////////

Sapphire::World::Util::ActorFilterCone::ActorFilterCone( Common::FFXIVARR_POSITION3 startPos, Common::FFXIVARR_POSITION3 skillTargetPos, float startAngle, float endAngle ) :
                                                         m_startPos( startPos ), m_skillTargetPos( skillTargetPos ), m_startAngle( startAngle ), m_endAngle( endAngle )
{
}

bool Sapphire::World::Util::ActorFilterCone::conditionApplies( const Entity::GameObject& actor )
{
  Common::FFXIVARR_POSITION3 targetPos = actor.getPos();
  
  float angleToCurrentTarget = Sapphire::Common::Util::calcAngTo( m_startPos.x, m_startPos.z, targetPos.x, targetPos.z );
  float angleToSkillTarget = Sapphire::Common::Util::calcAngTo( m_startPos.x, m_startPos.z, m_skillTargetPos.x, m_skillTargetPos.z );
  angleToCurrentTarget = angleToCurrentTarget - angleToSkillTarget; // Checking angle in world rotation

  if( angleToCurrentTarget < -PI )
    angleToCurrentTarget += 2 * PI;

  if( m_startAngle > m_endAngle ) // start -> end wraps around
  {
    return angleToCurrentTarget >= m_startAngle || angleToCurrentTarget <= m_endAngle;
  }

  // Simple case where values don't warp around
  return angleToCurrentTarget >= m_startAngle && angleToCurrentTarget <= m_endAngle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
