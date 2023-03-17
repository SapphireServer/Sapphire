
#ifndef _CELL_H
#define _CELL_H

#include <stdint.h>

#include "ForwardsZone.h"
#include <set>

namespace Sapphire {

typedef std::set< Entity::ActorPtr > ActorSet;

class Cell
{
  friend class Territory;

private:
  bool m_bForcedActive;
  uint16_t m_posX;
  uint16_t m_posY;
  ActorSet m_actors;
  bool m_bActive;

  uint16_t m_playerCount;
  uint32_t m_lastActiveTime;

public:
  Cell();

  ~Cell();

  void init( uint32_t x, uint32_t y );

  void addActor( Entity::ActorPtr pAct );

  void removeActorFromCell( Entity::ActorPtr pAct );

  bool hasActor( Entity::ActorPtr pAct )
  {
    return ( m_actors.find( pAct ) != m_actors.end() );
  }

  bool hasPlayers() const
  {
    return m_playerCount > 0;
  }

  size_t getActorCount() const
  {
    return m_actors.size();
  }

  void removeActors();

  ActorSet::iterator begin()
  {
    return m_actors.begin();
  }

  ActorSet::iterator end()
  {
    return m_actors.end();
  }

  void setActivity( bool state );

  bool isActive() const
  {
    return m_bActive;
  }

  void unload();

  bool isForcedActive() const
  {
    return m_bForcedActive;
  }

  uint16_t getPosX() const
  {
    return m_posX;
  }

  uint16_t getPosY() const
  {
    return m_posY;
  }

  uint32_t getLastActiveTime() const;
  void setLastActiveTime( uint32_t lastActiveTime );
};

}
#endif
