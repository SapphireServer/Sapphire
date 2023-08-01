#include "Cell.h"

#include "Actor/Chara.h"
#include "Forwards.h"
#include "Territory.h"
#include <Logging/Logger.h>

// TODO: the entire zone / areahandling is a bit outdated ( in parts i used this for the 1.0 iteration )
// likely this could be greatly improved or redone

Sapphire::Cell::Cell() :
  m_bActive( false ),
  m_playerCount( 0 )
{
  m_bForcedActive = false;
}

Sapphire::Cell::~Cell()
{
  removeActors();
}

void Sapphire::Cell::init( uint32_t x, uint32_t y )
{
  m_posX = static_cast< uint16_t >( x );
  m_posY = static_cast< uint16_t >( y );

  m_actors.clear();
}

void Sapphire::Cell::addActor( Entity::GameObjectPtr pAct )
{
  if( pAct->isPlayer() )
    ++m_playerCount;

  m_actors.insert( pAct );
}

void Sapphire::Cell::removeActorFromCell( Entity::GameObjectPtr pAct )
{
  if( pAct->isPlayer() )
    --m_playerCount;

  m_actors.erase( pAct );
}

void Sapphire::Cell::setActivity( bool state )
{
  if( !m_bActive && state )
  {
    // Move all objects to active set.
    //for( auto itr = m_actors.begin(); itr != m_actors.end(); ++itr )
    //{

    //}

  }
  else if( m_bActive && !state )
  {
    // Move all objects from active set.
    //for(auto itr = m_actors.begin(); itr != m_actors.end(); ++itr)
    //{

    //}


  }

  m_bActive = state;

}

void Sapphire::Cell::removeActors()
{
  //uint32_t ltime = getMSTime();

  m_actors.clear();

  //This time it's simpler! We just remove everything
  Entity::GameObjectPtr pAct; //do this outside the loop!
  for( auto itr = m_actors.begin(); itr != m_actors.end(); )
  {
    pAct = ( *itr );
    itr++;

    if( !pAct )
    {
      continue;
    }

  }

  m_playerCount = 0;
}

void Sapphire::Cell::unload()
{

  if( m_bActive )
    return;

  removeActors();
}

uint32_t Sapphire::Cell::getLastActiveTime() const
{
  return m_lastActiveTime;
}

void Sapphire::Cell::setLastActiveTime( uint32_t lastActiveTime )
{
  m_lastActiveTime = lastActiveTime;
}