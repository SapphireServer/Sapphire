#include "Cell.h"

#include "Actor/Chara.h"
#include "Forwards.h"
#include "Zone.h"
#include <Logging/Logger.h>

#include "Framework.h"

extern Core::Framework g_fw;

// TODO: the entire zone / areahandling is a bit outdated ( in parts i used this for the 1.0 iteration )
// likely this could be greatly improved or redone

Core::Cell::Cell() :
  m_bActive( false ),
  m_bLoaded( false ),
  m_playerCount( 0 ),
  m_bUnloadPending( false )
{
  m_bForcedActive = false;
}

Core::Cell::~Cell()
{
  removeActors();
}

void Core::Cell::init( uint32_t x, uint32_t y, ZonePtr pZone )
{
  m_pZone = pZone;
  m_posX = x;
  m_posY = y;

  m_actors.clear();
}

void Core::Cell::addActor( Entity::ActorPtr pAct )
{
  auto pLog = g_fw.get< Core::Logger >();
  if( pAct->isPlayer() )
    ++m_playerCount;

  m_actors.insert( pAct );
}

void Core::Cell::removeActor( Entity::ActorPtr pAct )
{
  auto pLog = g_fw.get< Core::Logger >();
  if( pAct->isPlayer() )
    --m_playerCount;

  m_actors.erase( pAct );
}

void Core::Cell::setActivity( bool state )
{
  if( !m_bActive && state )
  {
    // Move all objects to active set.
    //for( auto itr = m_actors.begin(); itr != m_actors.end(); ++itr )
    //{

    //}

    if( m_bUnloadPending )
      cancelPendingUnload();

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

void Core::Cell::removeActors()
{
  //uint32_t ltime = getMSTime();

  m_actors.clear();

  //This time it's simpler! We just remove everything
  Entity::ActorPtr pAct; //do this outside the loop!
  for( auto itr = m_actors.begin(); itr != m_actors.end(); )
  {
    pAct = ( *itr );
    itr++;

    if( !pAct )
    {
      continue;
    }

    if( m_bUnloadPending )
    {

    }

  }

  m_playerCount = 0;
  m_bLoaded = false;
}

void Core::Cell::queueUnloadPending()
{
  if( m_bUnloadPending )
    return;

  m_bUnloadPending = true;

}

void Core::Cell::cancelPendingUnload()
{
  if( !m_bUnloadPending )
    return;
}

void Core::Cell::unload()
{

  assert( m_bUnloadPending );
  if( m_bActive )
    return;

  removeActors();
  m_bUnloadPending = false;
}

