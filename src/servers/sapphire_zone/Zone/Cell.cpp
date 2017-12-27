#include "Cell.h"

#include "Actor/Actor.h"
#include "Actor/BattleNpc.h"
#include "Forwards.h"
#include "Zone.h"


// TODO: the entire zone / areahandling is a bit outdated ( in parts i used this for the 1.0 iteration )
// likely this could be greatly improved or redone
namespace Core 
{


   Cell::Cell() 
      : m_bActive(false)
      , m_bLoaded(false)
      , m_playerCount(0)
      , m_bUnloadPending(false)
   {
      m_bForcedActive = false;
   }

   Cell::~Cell() 
   {
      removeActors();
   }

   void Cell::init(uint32_t x, uint32_t y, ZonePtr pZone)
   {
      //Console->outDebOnly("[Region:%X] Initializing a new cell[%i/%i]", pRegion->getId(), x, y );
      m_pZone				= pZone;
      m_posX				= x;
      m_posY				= y;

      m_actors.clear();
   }

   void Cell::loadActors(CellCache* pCC) 
   {

      m_bLoaded = true;
      assert(pCC);

      for( auto entry : pCC->battleNpcCache ) 
      {

         entry->setCurrentZone( m_pZone );
         m_pZone->pushActor( entry );

      }
   }

   void Cell::addActor(Entity::ActorPtr pAct) 
   {
      if(pAct->isPlayer()) 
      {
         //Console->outDebOnly("[Region:%X] Adding player %i to cell[%i/%i]", m_pZone->getId(), pAct->getId(), m_posX, m_posY);
         ++m_playerCount;
      }

      m_actors.insert(pAct);
   }

   void Cell::removeActor(Entity::ActorPtr pAct)
   {
      if(pAct->isPlayer()) 
      {
         //->outDebOnly("[Region:%X] Removing player %i from cell[%i/%i]", m_pZone->getId(), pAct->getId(), m_posX, m_posY);
         --m_playerCount;
      }

      m_actors.erase(pAct);
   }

   void Cell::setActivity(bool state) 
   {	
      if(!m_bActive && state)
      {
         // Move all objects to active set.
         for(auto itr = m_actors.begin(); itr != m_actors.end(); ++itr) 
         {

         }

         if(m_bUnloadPending) 
         {
            cancelPendingUnload();
         }

      } 
      else if(m_bActive && !state) 
      {
         // Move all objects from active set.
         for(auto itr = m_actors.begin(); itr != m_actors.end(); ++itr) 
         {

         }


      }

      m_bActive = state; 

   }
   void Cell::removeActors() 
   {
      //uint32_t ltime = getMSTime();

      m_actors.clear();

      //This time it's simpler! We just remove everything 
      Entity::ActorPtr pAct; //do this outside the loop!
      for(auto itr = m_actors.begin(); itr != m_actors.end();) 
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



   void Cell::queueUnloadPending() 
   {
      if(m_bUnloadPending) 
      {
         return;
      }

      m_bUnloadPending = true;

   }

   void Cell::cancelPendingUnload() 
   {

      if(!m_bUnloadPending)
      {
         return;
      }

   }

   void Cell::unload()
   {

      assert(m_bUnloadPending);
      if(m_bActive) 
      {
         return;
      }

      removeActors();
      m_bUnloadPending = false;
   }

}
