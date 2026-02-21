#include "Encounter.h"

#include "TimelinePack.h"
#include "Actor/BNpc.h"
#include "Actor/EventObject.h"
#include "Actor/GameObject.h"
#include "Actor/Player.h"

#include "Util/UtilMath.h"
#include "Util/Util.h"

namespace Sapphire
{
  Encounter::Encounter( TerritoryPtr pInstance, std::shared_ptr< Event::Director > pDirector,
                        const std::string& timelineName ) :
    m_pTeri( pInstance ),
    m_pDirector( pDirector ),
    m_status( EncounterStatus::UNINITIALIZED )
  {
    m_type = EncounterType::Fate;
    m_position = { 0, 0, 0 };
    m_setup.timelineName = timelineName;
    m_id = m_pTeri->getNextEncounterId();
  }

  uint32_t Encounter::getId() const
  {
    return m_id;
  }

  void Encounter::init()
  {
    m_type = m_setup.type;
    m_pTimeline = TimelinePack::createTimelinePack( m_setup.timelineName );
    m_pTimeline->setEncounter( shared_from_this() );
    m_status = EncounterStatus::IDLE;
    m_startTime = 0;
    m_duration = m_setup.duration;
    m_position = m_setup.position;
    m_lastTick = 0;
    m_lockoutTime = 0;
    m_failTime = 0;
    m_finishTime = 0;

    // todo: probably add invisible untargetable BNpc for FATEs?
    for( const auto& actor : m_setup.bnpcSetupList )
    {
      auto pBNpc = m_pTeri->getActiveBNpcByLayoutId( actor.layoutId );
      if( !pBNpc )
        pBNpc = m_pTeri->createBNpcFromLayoutId( actor.layoutId, actor.hp, actor.type );

      pBNpc->init();
      addBNpc( pBNpc );

      if( actor.isBoss )
        m_bossBnpcs.emplace( pBNpc->getId(), pBNpc );

      if( m_type == EncounterType::Fate )
        bindActor( pBNpc );
    }

    for( const auto& eobj : m_setup.eobjSetupList )
    {
      auto pEObj = m_pTeri->getEObj( eobj.eobjId );
      if( !pEObj )
      {

      }
      // todo:
      if( pEObj )
      {
        pEObj->setPos( eobj.pos );
        pEObj->setRot( eobj.rot );
        pEObj->setScale( eobj.scale );
        pEObj->setState( eobj.state );
        pEObj->setPermissionInvisibility( eobj.permissionInvisibility );
        bindActor( pEObj );
      }
    }
  }

  void Encounter::setEncounterSetup( const EncounterSetup& setup )
  {
    m_setup = setup;
  }

  void Encounter::start()
  {
    setStatus( EncounterStatus::ACTIVE );
  }

  void Encounter::update( uint64_t currTime )
  {
    auto elapsed = currTime - m_startTime;
    auto dt = currTime - m_lastTick;
    auto dtRange = currTime - m_lastRangeTick;

    if( m_lockoutTime == 0 && elapsed >= 15000 )
    {
      // todo: send encounter sealed message
      if( m_type == EncounterType::DungeonBoss )
      {

      }
      m_lockoutTime = currTime;
    }

    if( canBindActors() )
    {
      if( m_setup.encounterShape == EncounterShape::CYLINDER && dtRange >= 1000 )
      {
        auto radius = m_setup.position2.x;
        auto height = m_setup.position2.y;

        // todo: this is hacky, ideally we'd have an actor at m_position coords 
        auto pCell = m_pTeri->getCellByCoords( m_position.x, m_position.z );
        std::set< Entity::GameObjectPtr > inRange;

        if( pCell && pCell->getActorCount() > 0 )
          inRange = ( *pCell->begin() )->getInRangeActors();

        for( auto& pActor : inRange )
        {
          auto distance = Common::Util::distance( m_position, pActor->getPos() );
          // if( pActor->isPlayer() || pActor->isBattleNpc() )
          {
            auto dY = std::abs( m_position.y - pActor->getPos().y );

            if( pActor->getBoundEncounterId() != m_id && distance <= radius && dY <= height )
            {
              onEnterRange( pActor );
            }
            else if( pActor->getBoundEncounterId() == m_id && ( distance > radius || dY > height ) )
            {
              onExitRange( pActor );
            }
          }
        }
        m_lastRangeTick = currTime;
      }
      else if( m_setup.encounterShape == EncounterShape::BOX && dtRange >= 1000 )
      {
        auto min = m_setup.position;
        auto max = m_setup.position2;

        // todo:
        // onEnterRange( pActor )
        // onExitRange( pActor )
        m_lastRangeTick = currTime;
      }
    }

    if( m_duration && m_type == EncounterType::Fate && elapsed >= m_duration )
    {
      setStatus( EncounterStatus::FAIL );
    }

    if( m_status == EncounterStatus::FAIL && currTime - m_failTime >= 5000 )
    {
      removeBNpcs( true );
      unbindActors();
    }
    
    m_pTimeline->update( currTime );

    m_lastTick = currTime;
  }

  void Encounter::reset()
  {
    unbindActors();
    removeBNpcs( true );
    m_pTimeline->reset( shared_from_this() );
    init();
  }

  void Encounter::removeBNpcs( bool removeBoss )
  {
    for( auto it = m_bnpcs.begin(); it != m_bnpcs.end(); )
    {
      bool remove = true;
      if( auto bossIt = m_bossBnpcs.find( it->second->getId() ); bossIt != m_bossBnpcs.end() )
      {
        remove = removeBoss;
      }

      if( remove )
      {
        m_pTeri->removeActor( it->second );
        it = m_bnpcs.erase( it );
      }
      else
      {
        ++it;
      }
    }
  }

  void Encounter::setStartTime( uint64_t startTime )
  {
    m_startTime = startTime;
  }

  EncounterStatus Encounter::getStatus() const
  {
    return m_status;
  }

  void Encounter::setStatus( EncounterStatus status )
  {
    onChangeStatus( m_status, status );
    m_status = status;
  }

  void Encounter::addBNpc( Entity::BNpcPtr pBNpc )
  {
    m_bnpcs[ pBNpc->getLayoutId() ] = pBNpc;
  }

  Entity::BNpcPtr Encounter::getBNpc( uint32_t layoutId ) const
  {
    auto bnpc = m_bnpcs.find( layoutId );
    if( bnpc != std::end( m_bnpcs ) )
      return bnpc->second;

    return nullptr;
  }

  void Encounter::removeBNpc( uint32_t layoutId )
  {
    m_bnpcs.erase( layoutId );
  }

  void Encounter::addPlayer( Entity::PlayerPtr pPlayer, bool bind )
  {
    m_playerList.emplace( pPlayer );

    if( bind )
      bindActor( pPlayer );
  }

  void Encounter::removePlayer( Entity::PlayerPtr pPlayer )
  {
    m_playerList.erase( pPlayer );
    unbindActor( pPlayer );
  }

  TerritoryPtr Encounter::getTeriPtr()
  {
    return m_pTeri;
  }

  Event::DirectorPtr Encounter::getDirector()
  {
    return m_pDirector;
  }

  EncounterSetup& Encounter::getSetup()
  {
    return m_setup;
  }

  uint32_t Encounter::getLockoutTime() const
  {
    return m_lockoutTime;
  }

  void Encounter::onEnterRange( Entity::GameObjectPtr pActor )
  {
    // todo: FATE
    /*
     // FATEs
     if( m_type == EncounterType::Fate && !( pActor->getLevel() > m_requiredLevel + 9 ) )
       bindActor( pActor );
    //*/

    // todo: handle bnpcs from overworld that get converted to FATEs

    if( pActor->isPlayer() )
    {
      addPlayer( pActor->getAsPlayer(), true );
    }
    else
    {
      // bindActor( pActor );
    }
  }

  void Encounter::onExitRange( Entity::GameObjectPtr pActor )
  {
    if( pActor->isPlayer() )
    {
      removePlayer( pActor->getAsPlayer() );
    }
    else if( pActor->isBattleNpc() )
    {
      auto pBNpc = pActor->getAsBNpc();
      // only unbind actors that weren't spawned by the encounter
      if( m_bnpcs.find( pBNpc->getLayoutId() ) == m_bnpcs.end() )
        unbindActor( pBNpc );
    }
  }

  void Encounter::onChangeStatus( EncounterStatus oldStatus, EncounterStatus newStatus )
  {
    if( newStatus == EncounterStatus::FAIL )
    {
      m_failTime = Common::Util::getTimeMs();
    }
    else if( newStatus == EncounterStatus::SUCCESS )
    {
      m_finishTime = Common::Util::getTimeMs();
    }
  }

  bool Encounter::canBindActors() const
  {
    auto elapsed = Common::Util::getTimeMs() - m_startTime;

    return m_type == EncounterType::Fate || ( m_setup.hasLockout && elapsed >= 15000 );
  }

  void Encounter::bindActor( Entity::GameObjectPtr pActor )
  {
    pActor->setBoundEncounterId( m_id );
    m_boundActors.emplace( pActor );

    /*
     auto pChara = pActor->getAsChara();
     auto pPlayer = pActor->getAsPlayer();

     if( pChara && pChara->getPet() )
       bindActor( pChara->getPet() );

     if( pPlayer && pPlayer->getCompanion() )
       bindActor( pChara->getCompanion() );
    //*/
  }

  void Encounter::unbindActor( Entity::GameObjectPtr pActor )
  {
    pActor->setBoundEncounterId( 0 );
    m_boundActors.erase( pActor );

    /*
     auto pChara = pActor->getAsChara();
     auto pPlayer = pActor->getAsPlayer();

     if( pChara && pChara->getPet() )
       unbindActor( pChara->getPet() );

     if( pPlayer && pPlayer->getCompanion() )
       unbindActor( pChara->getCompanion() );
    //*/
  }

  void Encounter::unbindActors()
  {
    for( auto& pActor : m_boundActors )
      pActor->setBoundEncounterId( 0 );

    m_boundActors.clear();
  }
}
