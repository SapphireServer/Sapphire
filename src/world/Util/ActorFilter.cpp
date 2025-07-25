#include "ActorFilter.h"
#include "Actor/GameObject.h"
#include "Util/Util.h"
#include "Util/UtilMath.h"
#include <math.h>

#include "Manager/PlayerMgr.h"


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

Sapphire::World::Util::ActorFilterInCone::ActorFilterInCone( Common::FFXIVARR_POSITION3 startPos, Common::FFXIVARR_POSITION3 skillTargetPos, int8_t startAngle, int8_t endAngle, Sapphire::Entity::Player& player ) : m_startPos( startPos ), m_skillTargetPos( skillTargetPos ), m_startAngle( startAngle ), m_endAngle( endAngle ), m_player( player )
{
}

bool Sapphire::World::Util::ActorFilterInCone::conditionApplies( const Entity::GameObject& actor )
{
  Common::FFXIVARR_POSITION3 targetPos = actor.getPos();
  
  float angleToCurrentTarget = Sapphire::Common::Util::radianToDegrees( Sapphire::Common::Util::calcAngTo( m_startPos.x, m_startPos.z, targetPos.x, targetPos.z ) );
  float angleToSkillTarget = Sapphire::Common::Util::radianToDegrees( Sapphire::Common::Util::calcAngTo( m_startPos.x, m_startPos.z, m_skillTargetPos.x, m_skillTargetPos.z ) );
  angleToCurrentTarget = angleToCurrentTarget - angleToSkillTarget;// Checking angle in world rotation
  Manager::PlayerMgr::sendDebug( m_player, "angleToTargetFinal: {}", angleToCurrentTarget );

  float leftAngle = m_startAngle - angleToCurrentTarget;
  float rightAngle = m_endAngle - angleToCurrentTarget;

  while( leftAngle < -180 )
    leftAngle += 360;
  while( leftAngle > 180 )
    leftAngle -= 360;

  while( rightAngle < -180 )
    rightAngle += 360;
  while( rightAngle > 180 )
    rightAngle -= 360;

  if( leftAngle * rightAngle >= 0 )
    return false;
  return abs( leftAngle - rightAngle ) < 180;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
