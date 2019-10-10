
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
  bool m_bLoaded;
  bool m_bUnloadPending;

  uint16_t m_playerCount;
  TerritoryPtr m_pZone;

public:
  Cell();

  ~Cell();

  void init( uint32_t x, uint32_t y, TerritoryPtr pZone );

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

  bool isLoaded() const
  {
    return m_bLoaded;
  }

  uint32_t getPlayerCount() const
  {
    return m_playerCount;
  }

  bool isUnloadPending() const
  {
    return m_bUnloadPending;
  }

  void setUnloadPending( bool up )
  {
    m_bUnloadPending = up;
  }

  void queueUnloadPending();

  void cancelPendingUnload();

  void unload();

  void setPermanentActivity( bool val )
  {
    m_bForcedActive = val;
  }

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
};

}
#endif
