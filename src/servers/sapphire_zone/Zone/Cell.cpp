#include "Cell.h"

#include "Actor/Chara.h"
#include "Actor/BattleNpc.h"
#include "Forwards.h"
#include "Zone.h"

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
   removeCharas();
}

void Core::Cell::init( uint32_t x, uint32_t y, ZonePtr pZone )
{
   //Console->outDebOnly("[Region:%X] Initializing a new cell[%i/%i]", pRegion->getId(), x, y );
   m_pZone = pZone;
   m_posX = x;
   m_posY = y;

   m_charas.clear();
}

void Core::Cell::loadCharas( CellCache* pCC )
{
   m_bLoaded = true;
   assert( pCC );

   for( auto entry : pCC->battleNpcCache )
   {
      entry->setCurrentZone( m_pZone );
      m_pZone->pushActor( entry );
   }
}

void Core::Cell::addChara( Entity::CharaPtr pAct )
{
   if( pAct->isPlayer() )
      ++m_playerCount;

   m_charas.insert(pAct);
}

void Core::Cell::removeChara( Entity::CharaPtr pAct )
{
   if( pAct->isPlayer() )
      --m_playerCount;

   m_charas.erase(pAct);
}

void Core::Cell::setActivity( bool state )
{
   if( !m_bActive && state )
   {
      // Move all objects to active set.
      //for( auto itr = m_charas.begin(); itr != m_charas.end(); ++itr )
      //{

      //}

      if( m_bUnloadPending )
         cancelPendingUnload();

   }
   else if( m_bActive && !state )
   {
      // Move all objects from active set.
      //for(auto itr = m_charas.begin(); itr != m_charas.end(); ++itr)
      //{

      //}


   }

   m_bActive = state;

}

void Core::Cell::removeCharas()
{
   //uint32_t ltime = getMSTime();

   m_charas.clear();

   //This time it's simpler! We just remove everything
   Entity::ActorPtr pAct; //do this outside the loop!
   for( auto itr = m_charas.begin(); itr != m_charas.end(); )
   {
      pAct = (*itr);
      itr++;

      if(!pAct)
      {
         continue;
      }

      if(m_bUnloadPending)
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

   removeCharas();
   m_bUnloadPending = false;
}

