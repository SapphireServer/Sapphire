#include <ScriptObject.h>

#include <Actor/EventObject.h>
#include <Actor/BNpc.h>
#include <Encounter/Encounter.h>
#include <Encounter/TimelinePack.h>
#include <Logging/Logger.h>

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
    if( pDenn && pDenn->getState() == Entity::BNpcState::Combat )
    {
      auto dennHpp = pDenn->getHpPercent();
      bool sendLogMessage = false;

      if( m_lastUnnaturalRipplesStart == 0 )
      {
        Logger::info( "Unnatural ripples last start time 0" );
        m_lastUnnaturalRipplesStart = tick;
      }

      auto elapsed = tick - m_lastUnnaturalRipplesStart;
      if( elapsed > 12000 )
      {
        Logger::info( "Unnatural ripples elapsed" );
        Logger::info( "Denn HP {} MaxHP {} HPP {}", pDenn->getHp(), pDenn->getMaxHp(), dennHpp );

        if( dennHpp < 20 )
        {
          Logger::info( "HP Breakpoint 20" );
          if( pack.isPhaseActive( "Unnaturalripples", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples", "Bubbles" );
            sendLogMessage = true;
          }
        }

        if( dennHpp < 40 )
        {
          Logger::info( "HP Breakpoint 40" );
          if( pack.isPhaseActive( "Unnaturalripples_1", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples_1", "Bubbles" );
            sendLogMessage = true;
          }
        }

        if( dennHpp < 60 )
        {
          Logger::info( "HP Breakpoint 60" );
          if( pack.isPhaseActive( "Unnaturalripples_2", "Setup Phase" ) )
          {
            pack.requestPhaseTransition( "Unnaturalripples_2", "Bubbles" );
            sendLogMessage = true;
          }
        }

        if( dennHpp < 80 )
        {
          Logger::info( "HP Breakpoint 80" );

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
          Logger::info( "Unnatural ripples started bubbling" );
          m_lastUnnaturalRipplesStart = tick;
        }
      }

    }

    m_lastTick = tick;
    ++m_updateCount;

    if( m_maxUpdates != 0 && m_updateCount >= m_maxUpdates )
      m_armed = false;
  }

private:
  bool m_armed{ false };

  uint64_t m_intervalMs{ 1000 };
  uint64_t m_lastTick{ 0 };
  uint64_t m_lastUnnaturalRipplesStart{ 0 };
  uint32_t m_maxUpdates{ 0 };
  uint32_t m_updateCount{ 0 };
};

EXPOSE_MECHANIC_SCRIPT(
  SastashaUnnaturalRipples,
  MECHANIC_FUNCTION( arm ),
  MECHANIC_FUNCTION( disarm )
);
