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
    virtual bool conditionApplies( const Entity::Actor& actor );
  };

  class ActorFilterInRange : public ActorFilter
  {
    FFXIVARR_POSITION3 m_startPos;
    float m_range;
  public:
    ActorFilterInRange( FFXIVARR_POSITION3 startPos, float range ) : m_startPos( startPos ), m_range( range );

    bool conditionApplies( const Entity::Actor& actor ) override
    {
      return Util::distance( m_startPos.x, m_startPos.y, m_startPos.z,
                             actor.getPos().x, actor.getPos().y, actor.getPos().z ) <= m_range;
    }
  };

  // usage in psudocode
  //
  //  std::set< ActorPtr > filterActorList( inputSet, filter )
  //  {
  //    std::set< ActorPtr > resultSet;
  //    for( every actor in inputSet )
  //    {
  //       if( filter.conditionApplies( actor ) )
  //         resultSet.insert( actor.asPointer() );
  //    }
  //    return resultSet;
  //
}