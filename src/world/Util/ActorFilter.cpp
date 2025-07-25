#include "ActorFilter.h"
#include "Actor/GameObject.h"
#include "Util/Util.h"
#include "Util/UtilMath.h"
#include <math.h>


Sapphire::World::Util::ActorFilterInRange::ActorFilterInRange( Common::FFXIVARR_POSITION3 startPos,
                                                               float range ) :
  m_startPos( startPos ),
  m_range( range )
{
}

bool Sapphire::World::Util::ActorFilterInRange::conditionApplies( const Entity::GameObject& actor )
{
  return Sapphire::Common::Util::distance( m_startPos, actor.getPos() ) <= m_range;
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

Sapphire::World::Util::ActorFilterInCone::ActorFilterInCone( Common::FFXIVARR_POSITION3 startPos, Common::FFXIVARR_POSITION3 skillTargetPos, float startAngle, float endAngle ) :
  m_startPos( startPos ), m_skillTargetPos( skillTargetPos ), m_startAngle( startAngle ), m_endAngle( endAngle )
{
}

bool Sapphire::World::Util::ActorFilterInCone::conditionApplies( const Entity::GameObject& actor )
{
  Common::FFXIVARR_POSITION3 targetPos = actor.getPos();
  
  float angleToCurrentTarget = Sapphire::Common::Util::radianToDegrees( Sapphire::Common::Util::calcAngTo( m_startPos.x, m_startPos.z, targetPos.x, targetPos.z ) );
  float angleToSkillTarget = Sapphire::Common::Util::radianToDegrees( Sapphire::Common::Util::calcAngTo( m_startPos.x, m_startPos.z, m_skillTargetPos.x, m_skillTargetPos.z ) );
  angleToCurrentTarget = angleToCurrentTarget - angleToSkillTarget; // Checking angle in world rotation

  if( angleToCurrentTarget < 0.0f )
    angleToCurrentTarget += 360.0f;

  if( m_startAngle > m_endAngle ) // start -> end wraps around
  {
    return angleToCurrentTarget >= m_startAngle || angleToCurrentTarget <= m_endAngle;
  }

  // Simple case where values don't warp around
  return angleToCurrentTarget >= m_startAngle && angleToCurrentTarget <= m_endAngle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
