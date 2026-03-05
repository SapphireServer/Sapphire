#include "Encounter.h"

#include "TimelinePack.h"
#include "Actor/BNpc.h"
#include "Actor/EventObject.h"
#include "Actor/GameObject.h"
#include "Actor/Player.h"

#include "Manager/PlayerMgr.h"

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
    m_position = { 0, 0, 0 };
    m_setup.timelineName = timelineName;
    m_id = m_pTeri->getNextEncounterId();
  }

  Encounter::~Encounter()
  {
    unbindActors();
    removeBNpcs( true );
    removePlayers();
    removeEObjs();
  }

  uint32_t Encounter::getId() const
  {
    return m_id;
  }

  void Encounter::init()
  {
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
    m_placeName = m_setup.placeName;

    // todo: probably add invisible untargetable BNpc for FATEs?
    for( const auto& actor : m_setup.bnpcSetupList )
    {
      auto pBNpc = m_pTeri->getActiveBNpcByLayoutId( actor.layoutId );
      if( !pBNpc )
        pBNpc = m_pTeri->createBNpcFromLayoutId( actor.layoutId, actor.hp, actor.type );

      pBNpc->resetFlags( actor.flags );
      pBNpc->init();
      addBNpc( pBNpc );

      if( actor.isBoss )
        m_bossBnpcs.emplace( pBNpc->getId(), pBNpc );
    }

    for( const auto& eobj : m_setup.eobjSetupList )
    {
      auto pEObj = m_pTeri->getEObj( eobj.baseId );

      if( !pEObj )
      {
        pEObj = m_pTeri->addEObj( eobj.name, eobj.baseId, eobj.boundInstanceId, eobj.instanceId, eobj.state,
                                  eobj.pos, eobj.scale, eobj.rotation, eobj.permissionInvisibility );
      }
      // todo:
      if( pEObj )
      {
        pEObj->setPos( eobj.pos );
        pEObj->setRot( eobj.rotation );
        pEObj->setScale( eobj.scale );
        pEObj->setState( eobj.state );
        pEObj->setPermissionInvisibility( eobj.permissionInvisibility );

        m_eobjs.emplace( pEObj );
      }
    }

    // setup entrance eobjs
    for( const auto& entrance : m_setup.lockoutEntrances )
    {

      auto pEObj = m_pTeri->getEObj( entrance.baseId );
      if( !pEObj )
      {
        pEObj = m_pTeri->addEObj( entrance.name, entrance.baseId, entrance.boundInstanceId, entrance.instanceId, entrance.state,
                                  entrance.pos, entrance.scale, entrance.rotation, entrance.permissionInvisibility );
      }

      if( pEObj )
      {
        pEObj->setPos( entrance.pos );
        pEObj->setRot( entrance.rotation );
        pEObj->setScale( entrance.scale );
        pEObj->setState( entrance.state );
        pEObj->setPermissionInvisibility( entrance.permissionInvisibility );

        m_entranceEObjs.emplace( pEObj );
        m_eobjs.emplace( pEObj );
      }
    }

    // setup exit eobjs
    for( const auto& exit : m_setup.lockoutExits )
    {
      auto pEObj = m_pTeri->getEObj( exit.baseId );
      if( !pEObj )
      {
        pEObj = m_pTeri->addEObj( exit.name, exit.baseId, exit.boundInstanceId, exit.instanceId, exit.state,
                                  exit.pos, exit.scale, exit.rotation, exit.permissionInvisibility );
      }

      if( pEObj )
      {
        pEObj->setPos( exit.pos );
        pEObj->setRot( exit.rotation );
        pEObj->setScale( exit.scale );
        pEObj->setState( exit.state );
        pEObj->setPermissionInvisibility( exit.permissionInvisibility );

        m_exitEObjs.emplace( pEObj );
        m_eobjs.emplace( pEObj );
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

    if( dtRange >= 1000 )
    {
      if( m_setup.encounterShape == EncounterShape::CYLINDER )
      {
        // todo: this is hacky, ideally we'd have an actor at m_position coords 
        auto pCell = m_pTeri->getCellByCoords( m_position.x, m_position.z );
        std::set< Entity::GameObjectPtr > inRange;

        if( pCell && pCell->getActorCount() > 0 )
          inRange = ( *pCell->begin() )->getInRangeActors( true );

        for( auto& pActor : inRange )
        {
          // dont bind bnpcs that we didnt spawn
          //if( pActor->isBattleNpc() && m_bnpcs.find( pActor->getAsBNpc()->getLayoutId() ) == m_bnpcs.end() )
          //  continue;
          // if( pActor->isPlayer() || pActor->isBattleNpc() )
          {
            if( pActor->getBoundEncounterId() != m_id && isPositionInside( pActor->getPos() ) )
            {
              onEnterRange( pActor );
            }
            else if( pActor->getBoundEncounterId() == m_id && !isPositionInside( pActor->getPos() ) )
            {
              onExitRange( pActor );
            }
          }
        }
        m_lastRangeTick = currTime;
      }
      else if( m_setup.encounterShape == EncounterShape::BOX )
      {
        auto min = m_setup.position;
        auto max = m_setup.position2;

        // find centre of arena
        auto pos = ( min + max ) / 2.f ;
        auto pCell = m_pTeri->getCellByCoords( pos.x, pos.z );
        std::set< Entity::GameObjectPtr > inRange;

        // todo: this is hacky, ideally we'd have an actor at m_position coords 
        if( pCell && pCell->getActorCount() > 0 )
          inRange = ( *pCell->begin() )->getInRangeActors( true );

        for( auto& pActor : inRange )
        {
          if( pActor->getBoundEncounterId() != m_id && isPositionInside( pActor->getPos() ) )
          {
            onEnterRange( pActor );
          }
          else if( pActor->getBoundEncounterId() == m_id && !isPositionInside( pActor->getPos() ) )
          {
            onExitRange( pActor );
          }
        }
        m_lastRangeTick = currTime;
      }
    }
    
    m_pTimeline->update( currTime );

    // remove any players that have left the zone
    {
      std::set< Entity::PlayerPtr > toRemove;

      for( auto& pPlayer : m_playersInside )
        if( pPlayer->getTerritoryId() != m_pTeri->getGuId() )
          toRemove.emplace( pPlayer );

      for( auto& pPlayer : toRemove )
        removePlayer( pPlayer );
    }

    // reset if no players remaining
    if( m_status == EncounterStatus::ACTIVE && ( m_playerList.empty() && m_playersInside.empty() ) )
      setStatus( EncounterStatus::IDLE );

    if( m_setup.hasLockout && !isLocked() && canBindActors() )
    {
      onLockout();
    }

    m_lastTick = currTime;
  }

  void Encounter::reset()
  {
    unbindActors();
    removeBNpcs( true );
    removeEObjs();
    removePlayers();
    m_actorsInside.clear();
    m_pTimeline->reset( shared_from_this() );

    init();

    setEntranceEObjLocked( false );
    setExitEObjLocked( true );
  }

  void Encounter::removeBNpcs( bool removeBoss )
  {
    for( auto it = m_bnpcs.begin(); it != m_bnpcs.end(); )
    {
      bool remove = true;
      if( auto bossIt = m_bossBnpcs.find( it->second->getId() ); bossIt != m_bossBnpcs.end() )
      {
        remove = removeBoss;

        if( remove )
          m_bossBnpcs.erase( bossIt );
      }

      if( remove )
      {
        if( it->second->getBoundEncounterId() == m_id )
          unbindActor( it->second );

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
    m_status = status;
    onChangeStatus( m_status, status );
  }

  void Encounter::addBNpc( Entity::BNpcPtr pBNpc, bool bind )
  {
    m_bnpcs[ pBNpc->getLayoutId() ] = pBNpc;

    if( bind )
      bindActor( pBNpc );
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
    Entity::BNpcPtr pBNpc;
    if( auto it = m_bnpcs.find( layoutId ); it != m_bnpcs.end() )
      pBNpc = it->second;

    m_bnpcs.erase( layoutId );

    if( pBNpc )
      unbindActor( pBNpc );
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
    m_playersInside.erase( pPlayer );
    unbindActor( pPlayer );
  }

  void Encounter::removePlayers()
  {
    std::set< Entity::PlayerPtr > toRemove = m_playersInside;
    for( auto& pPlayer : toRemove )
      removePlayer( pPlayer );

    m_playerList.clear();
    m_playersInside.clear();
  }

  const std::set< Entity::PlayerPtr >& Encounter::getPlayers() const
  {
    // todo: should this be playersInside?
    return m_playerList;
  }

  const std::set< Entity::PlayerPtr >& Encounter::getPlayersInside() const
  {
    return m_playersInside;
  }

  const std::set< Entity::GameObjectPtr >& Encounter::getActorsInside() const
  {
    return m_actorsInside;
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

  uint64_t Encounter::getLockoutTime() const
  {
    return m_lockoutTime;
  }

  bool Encounter::isLocked() const
  {
    return m_lockoutTime != 0;
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
      auto pPlayer = pActor->getAsPlayer();
      addPlayer( pPlayer, isLocked() );
      m_playersInside.emplace( pPlayer );
    }
    else if( !pActor->isPlayer() && canBindActors() )
    {
      bindActor( pActor );
    }
    m_actorsInside.emplace( pActor );
  }

  void Encounter::onExitRange( Entity::GameObjectPtr pActor )
  {
    if( pActor->isPlayer() )
    {
      auto pPlayer = pActor->getAsPlayer();
      removePlayer( pPlayer );
      m_playersInside.erase( pPlayer );
    }
    else if( pActor->isBattleNpc() )
    {
      auto pBNpc = pActor->getAsBNpc();
      // only unbind actors that weren't spawned by the encounter
      // todo: is this correct?
      unbindActor( pBNpc );
    }
    m_actorsInside.erase( pActor );
  }

  void Encounter::onChangeStatus( EncounterStatus oldStatus, EncounterStatus newStatus )
  {
    if( newStatus == EncounterStatus::FAIL )
    {
      // todo: reset(), init() will just clear the failTime anyway so should this be here?
      m_failTime = Common::Util::getTimeMs();
      // todo: FATEs should just despawn rather than reset
      reset();

      if( m_setup.placeName != 0 )
        if( auto pInstance = m_pTeri->getAsInstanceContent() )
          for( auto [ id, pPlayer ] : m_pTeri->getPlayers() )
            pInstance->sendEventLogMessage( *pPlayer, *pInstance, static_cast< uint32_t >( EncounterLogMessage::IsNoLongerSealed ), { m_setup.placeName } );

      // todo: change and send bgm
      // todo: should this be set for overworld FATEs too?
    }
    else if( newStatus == EncounterStatus::SUCCESS )
    {
      m_finishTime = Common::Util::getTimeMs();
      unbindActors();

      if( m_setup.placeName != 0 )
        if( auto pInstance = m_pTeri->getAsInstanceContent() )
          for( auto [ id, pPlayer ] : m_pTeri->getPlayers() )
            pInstance->sendEventLogMessage( *pPlayer, *pInstance, static_cast< uint32_t >( EncounterLogMessage::IsNoLongerSealed ), { m_setup.placeName } );


      // todo: change and send bgm
      // todo: should this be set for overworld FATEs too?
    }
    else if( newStatus == EncounterStatus::IDLE )
    {
      reset();
    }
    else if( newStatus == EncounterStatus::ACTIVE )
    {
      m_startTime = Common::Util::getTimeMs();

      if( m_setup.placeName != 0 )
        if( auto pInstance = m_pTeri->getAsInstanceContent() )
          for( auto [ id, pPlayer ] : m_pTeri->getPlayers() )
            pInstance->sendEventLogMessage( *pPlayer, *pInstance, static_cast< uint32_t >( EncounterLogMessage::WillBeSealed ), { m_setup.placeName } );

      // todo: change and send bgm
      // todo: should this be set for overworld FATEs too?
    }
  }

  void Encounter::onLockout()
  {
    m_playerList = m_playersInside;

    for( auto& pActor : m_actorsInside )
      bindActor( pActor );

    if( m_setup.placeName != 0 )
      if( auto pInstance = m_pTeri->getAsInstanceContent() )
       for( auto [ id, pPlayer ] : m_pTeri->getPlayers() )
          pInstance->sendEventLogMessage( *pPlayer, *pInstance, static_cast< uint32_t >( EncounterLogMessage::IsSealed ), { m_setup.placeName } );

    setEntranceEObjLocked( true );
    setExitEObjLocked( true );
    m_lockoutTime = Common::Util::getTimeMs();
  }

  void Encounter::setEntranceEObjLocked( bool locked )
  {
    for( auto& pEObj : m_entranceEObjs )
    {
      if( pEObj )
      {
        // todo: map eobj states to vfx
        // todo: map eobj to lgb collisionbox
        // todo: pNaviProvider->toggleDoor
        if( locked )
        {
          pEObj->setPermissionInvisibility( 0 );
          pEObj->setCollisionEnabled( true );
        }
        else
        {
          pEObj->setPermissionInvisibility( 1 );
          pEObj->setCollisionEnabled( false );
        }
      }
    }
  }

  void Encounter::setExitEObjLocked( bool locked )
  {
    for( auto& pEObj : m_exitEObjs )
    {
      if( pEObj )
      {
        // todo: map eobj states to vfx
        // todo: map eobj to lgb collisionbox
        // todo: pNaviProvider->toggleDoor
        if( locked )
        {
          pEObj->setPermissionInvisibility( 0 );
          pEObj->setCollisionEnabled( true );
        }
        else
        {
          pEObj->setPermissionInvisibility( 1 );
          pEObj->setCollisionEnabled( false );
        }
      }
    }
  }

  bool Encounter::isPositionInside( const Common::Vector3& pos ) const
  {
    switch( m_setup.encounterShape )
    {
      case EncounterShape::CYLINDER:
      {
        auto radius = m_setup.position2.x;
        auto height = m_setup.position2.y;

        auto distance = Common::Util::distance2D( m_position.x, m_position.z, pos.x, pos.z );
        volatile auto dY = std::fabs( m_position.y - pos.y );

        return distance <= radius && dY <= height;
      }
      break;
      case EncounterShape::BOX:
      {
        auto min = m_setup.position;
        auto max = m_setup.position2;

        return ( pos.x >= min.x && pos.x <= max.x ) &&
               ( pos.y >= min.x && pos.y <= max.y ) &&
               ( pos.z >= min.z && pos.z <= max.z );
      }
      break;
      default:
        break;
    }
    return false;
  }

  Entity::EventObjectPtr Encounter::getEObj( uint32_t baseId ) const
  {
    for( const auto& pEObj : m_eobjs )
      if( pEObj->getBaseId() == baseId )
        return pEObj;
    return nullptr;
  }

  void Encounter::removeEObj( Entity::EventObjectPtr pEObj )
  {
    m_entranceEObjs.erase( pEObj );
    m_exitEObjs.erase( pEObj );
    m_eobjs.erase( pEObj );

    unbindActor( pEObj );
    m_pTeri->removeActor( pEObj );
  }

  void Encounter::removeEObjs()
  {
    for( auto& pEObj : m_eobjs )
    {
      unbindActor( pEObj );
      m_pTeri->removeActor( pEObj );
    }

    m_entranceEObjs.clear();
    m_exitEObjs.clear();
    m_eobjs.clear();
  }

  bool Encounter::canBindActors() const
  {
    auto elapsed = Common::Util::getTimeMs() - m_startTime;

    return ( m_startTime > 0 && m_setup.hasLockout && elapsed >= 15000 );
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
    if( pActor->getBoundEncounterId() == m_id )
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

  bool Encounter::isActorBound( Entity::GameObjectPtr pActor ) const
  {
    return m_boundActors.find( pActor ) != m_boundActors.end();
  }
}
