#include <ScriptObject.h>

#include <Actor/EventObject.h>
#include <Actor/BNpc.h>
#include <Encounter/Encounter.h>
#include <Encounter/TimelinePack.h>
#include <Logging/Logger.h>

#include <array>
#include <set>
#include <string>

using namespace Sapphire;
using namespace Sapphire::World::Encounter;

class SastashaUnnaturalRipples : public ScriptAPI::MechanicScript
{
public:
  void arm( const nlohmann::json& args, TimelinePack& pack, EncounterPtr pEncounter )
  {
    m_intervalMs = args.value( "intervalMs", uint64_t{ 1000 } );
    m_maxUpdates = args.value( "maxUpdates", uint32_t{ 3 } );
    m_lastTick = 0;
    m_updateCount = 0;
    m_lastUnnaturalRipplesStart = 0;
    m_armed = true;

    m_availableGuards = { 3978770, 3978761, 4064938, 4064937 };
    m_ambuscadeQueue = {};

    Logger::info( "SastashaUnnaturalRipples armed" );
  }

  void disarm( const nlohmann::json& args, TimelinePack& pack, EncounterPtr pEncounter )
  {
    m_armed = false;
    Logger::info( "SastashaUnnaturalRipples disarmed" );
  }

  void update( uint64_t tick, TimelinePack& pack, EncounterPtr pEncounter ) override
  {
    if( !m_armed )
      return;

    if( m_lastTick == 0 )
    {
      m_lastTick = tick;
      return;
    }

    if( tick - m_lastTick < m_intervalMs )
      return;

    if( !pEncounter )
      return;

    auto pDenn = pack.getBNpcByRef( "Denn The Orcatoothed", pEncounter );
    if( pDenn && pDenn->getState() == Entity::BNpcState::Combat && !m_availableGuards.empty() )
    {
      auto dennHpp = pDenn->getHpPercent();
      bool sendLogMessage = false;

      if( m_lastUnnaturalRipplesStart == 0 )
      {
        Logger::info( "Unnatural ripples last start time 0" );
      }

      auto elapsed = tick - m_lastUnnaturalRipplesStart;
      if( elapsed > 12000 )
      {
        // Logger::info( "Unnatural ripples elapsed" );
        // Logger::info( "Denn HP {} MaxHP {} HPP {}", pDenn->getHp(), pDenn->getMaxHp(), dennHpp );

        if( dennHpp < 40 )
        {
          // Logger::info( "HP Breakpoint 40" );

          if( pack.isPhaseActive( "Unnaturalripples", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples", "Bubbles" );
            sendLogMessage = true;
          }
        }

        if( dennHpp < 60 )
        {
          // Logger::info( "HP Breakpoint 60" );
          if( pack.isPhaseActive( "Unnaturalripples_1", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples_1", "Bubbles" );
            sendLogMessage = true;
          }
        }

        if( dennHpp < 80 )
        {
          // Logger::info( "HP Breakpoint 80" );

          if( pack.isPhaseActive( "Unnaturalripples_2", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples_2", "Bubbles" );
            sendLogMessage = true;
          }

          if( pack.isPhaseActive( "Unnaturalripples_3", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples_3", "Bubbles" );
            sendLogMessage = true;
          }
        }

        if( sendLogMessage )
        {
          for( auto& pPlayer : pEncounter->getPlayersInside() )
          {
            playerMgr().sendLogMessage( *pPlayer, 2040 );
          }
          // Logger::info( "Unnatural ripples started bubbling" );
          m_lastUnnaturalRipplesStart = tick;
        }
      }

    }

    constexpr std::array< const char*, 4 > eobjNames = { "Unnaturalripples", "Unnaturalripples_1", "Unnaturalripples_2", "Unnaturalripples_3" };
    // no more guards to spawn, stop bubbling
    if( m_availableGuards.empty() )
      for( const auto& name : eobjNames )
        if( pack.isPhaseActive( name, "Bubbles" ) )
          pack.requestPhaseTransition( name, "Bubbles Interrupt" );

    if( !m_ambuscadeQueue.empty() )
    {
      for( auto guardId : m_ambuscadeQueue )
        if( auto pGuard = pEncounter->getBNpc( guardId ); pGuard->isAlive() )
          actionMgr().handleTargetedAction( *pGuard, 835, pGuard->getId(), 0 );
      m_ambuscadeQueue.clear();
    }
    m_lastTick = tick;
    ++m_updateCount;

    if( m_maxUpdates != 0 && m_updateCount >= m_maxUpdates )
      m_armed = false;
  }

  void spawnGuardForEObj( const nlohmann::json& args, TimelinePack& pack, EncounterPtr pEncounter )
  {
    if( !m_armed )
      return;

    if( !pEncounter )
      return;

    if( m_availableGuards.empty() )
      return;

    auto pDenn = pack.getBNpcByRef( "Denn The Orcatoothed", pEncounter );
    if( !pDenn || !pDenn->isAlive() )
      return;

    auto& eobjName = args.at( "eobjName" );
    auto pEObj = pEncounter->getEObjByName( eobjName );
    if( pEObj )
    {
      auto pos = pEObj->getPos();
      auto rot = -1.5f;

      if( eobjName == "Unnaturalripples" || eobjName == "Unnaturalripples_1" )
        rot = -1.5f;
      else
        rot = 1.5f;

      pos = Common::Util::getOffsettedPosition( pos, rot, 0.f, 0.f, 2.5f );
      auto pTeri = pEncounter->getTeriPtr();

      auto tmpAvailable = m_availableGuards;
      for( auto guardId : tmpAvailable )
      {
        auto pGuard = pEncounter->getBNpc( guardId );
        bool createBNpc = false;
        if( pGuard )
        {
          if( !pGuard->isAlive() )
          {
            pEncounter->removeBNpc( guardId );
            pTeri->removeActor( pGuard );
            createBNpc = true;
          }
        }
        else
        {
          createBNpc = true;
        }

        if( createBNpc )
        {
          // todo: use correct hp values
          pGuard = pTeri->createBNpcFromLayoutIdNoPush( guardId, 319, Common::BNpcType::Enemy, 0 );
          if( pGuard )
          {
            m_availableGuards.erase( guardId );

            pEncounter->addBNpc( pGuard, pEncounter->getLockoutTime() != 0 );
            pGuard->setRot( rot );
            pGuard->setPos( pos );
            pGuard->init();
            pTeri->pushActor( pGuard );

            // ::update runs on 1s (intervalMs) tick, wait til guard is spawned so client can animate the action
            m_ambuscadeQueue.insert( guardId );

            for( auto& pPlayer : pEncounter->getPlayersInside() )
            {
              playerMgr().sendLogMessage( *pPlayer, 2042, 1207 );// A Baleen Guard appears!
              pGuard->aggro( pPlayer );
            }
            break;
          }
        }
      }
    }
  }

private:
  bool m_armed{ false };

  uint64_t m_intervalMs{ 1000 };
  uint64_t m_lastTick{ 0 };
  uint64_t m_lastUnnaturalRipplesStart{ 0 };
  uint32_t m_maxUpdates{ 0 };
  uint32_t m_updateCount{ 0 };
  std::set< uint32_t > m_availableGuards;
  std::set< uint32_t > m_ambuscadeQueue;
};

EXPOSE_MECHANIC_SCRIPT(
  SastashaUnnaturalRipples,
  MECHANIC_FUNCTION( arm ),
  MECHANIC_FUNCTION( disarm ),
  MECHANIC_FUNCTION( spawnGuardForEObj ),
);
