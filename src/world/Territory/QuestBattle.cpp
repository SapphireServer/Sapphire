
#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonActorControl.h>

#include "Event/Director.h"
#include "Event/EventDefs.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Actor/BNpc.h"
#include "Actor/BNpcTemplate.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"


#include "Event/EventHandler.h"

#include "QuestBattle.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::QuestBattle::QuestBattle( std::shared_ptr< Sapphire::Data::QuestBattle > pBattleDetails,
                                    uint16_t territoryType,
                                    uint32_t guId,
                                    const std::string& internalName,
                                    const std::string& contentName,
                                    uint32_t questBattleId,
                                    FrameworkPtr pFw ) :
  Zone( static_cast< uint16_t >( territoryType ), guId, internalName, contentName, pFw ),
  Director( Event::Director::QuestBattle, questBattleId ),
  m_pBattleDetails( pBattleDetails ),
  m_questBattleId( questBattleId ),
  m_state( Created ),
  m_instanceCommenceTime( 0 )
{

}

bool Sapphire::QuestBattle::init()
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInstanceInit( getAsQuestBattle() );

  return true;
}

uint32_t Sapphire::QuestBattle::getQuestBattleId() const
{
  return m_questBattleId;
}

Sapphire::Data::ExdDataGenerated::QuestBattlePtr Sapphire::QuestBattle::getQuestBattleDetails() const
{
  return m_pBattleDetails;
}

void Sapphire::QuestBattle::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "QuestBattle::onPlayerZoneIn: Zone#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  m_pPlayer = player.getAsPlayer();

  // mark player as "bound by duty"
  player.setStateFlag( PlayerStateFlag::BoundByDuty );

  sendDirectorInit( player );

}

void Sapphire::QuestBattle::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "QuestBattle::onLeaveTerritory: Zone#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  clearDirector( player );
}

void Sapphire::QuestBattle::onEnterSceneFinish( Entity::Player& player )
{
  player.eventStart( player.getId(), getDirectorId(), Event::EventHandler::GameProgress, 1, 0 );
  player.playScene( getDirectorId(), 60000, 0x40000 /*unmapped*/ );
  setSequence( 2 );
}

void Sapphire::QuestBattle::onUpdate( uint64_t tickCount )
{
  if( !m_pPlayer )
    return;

  switch( m_state )
  {
    case Created:
    {


      if( !m_pPlayer->isLoadingComplete() ||
          !m_pPlayer->isDirectorInitialized() ||
          !m_pPlayer->isOnEnterEventDone() ||
          m_pPlayer->hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
        return;

      if( m_instanceCommenceTime == 0 )
      {
        m_instanceCommenceTime = Util::getTimeMs() + instanceStartDelay;
        return;
      }
      else if( Util::getTimeMs() < m_instanceCommenceTime )
        return;

      onEnterSceneFinish( *m_pPlayer );

      m_state = DutyInProgress;
      m_instanceExpireTime = Util::getTimeSeconds() + ( m_pBattleDetails->timeLimit * 60u );
      break;
    }

    case DutyReset:
      break;

    case DutyInProgress:
      break;

    case DutyFinished:
      break;

    case DutyFailed:
    {
      if( getSequence() != 0xFE )
      {
        setSequence( 0xFE );
        m_instanceFailTime = tickCount;
      }

      if( ( static_cast< int64_t >( tickCount ) - static_cast< int64_t >( m_instanceFailTime ) ) > 6000 )
      {
        m_pPlayer->exitInstance();
        m_pPlayer.reset();
      }
      break;
    }
  }

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInstanceUpdate( getAsQuestBattle(), tickCount );
}

void Sapphire::QuestBattle::onFinishLoading( Entity::Player& player )
{

}

void Sapphire::QuestBattle::onInitDirector( Entity::Player& player )
{
  player.sendQuestMessage( getDirectorId(), 0, 2, Util::getTimeSeconds(), 0x0708 );
  sendDirectorVars( player );
  player.setDirectorInitialized( true );
}

void Sapphire::QuestBattle::onDirectorSync( Entity::Player& player )
{
  player.queuePacket( makeActorControl143( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}

void Sapphire::QuestBattle::setVar( uint8_t index, uint8_t value )
{
  if( index > 19 )
    return;

  switch( index )
  {
    case 0:
      setDirectorUI8AL( value );
      break;
    case 1:
      setDirectorUI8AH( value );
      break;
    case 2:
      setDirectorUI8BL( value );
      break;
    case 3:
      setDirectorUI8BH( value );
      break;
    case 4:
      setDirectorUI8CL( value );
      break;
    case 5:
      setDirectorUI8CH( value );
      break;
    case 6:
      setDirectorUI8DL( value );
      break;
    case 7:
      setDirectorUI8DH( value );
      break;
    case 8:
      setDirectorUI8EL( value );
      break;
    case 9:
      setDirectorUI8EH( value );
      break;
    case 10:
      setDirectorUI8FL( value );
      break;
    case 11:
      setDirectorUI8FH( value );
      break;
    case 12:
      setDirectorUI8GL( value );
      break;
    case 13:
      setDirectorUI8GH( value );
      break;
    case 14:
      setDirectorUI8HL( value );
      break;
    case 15:
      setDirectorUI8HH( value );
      break;
    case 16:
      setDirectorUI8IL( value );
      break;
    case 17:
      setDirectorUI8IH( value );
      break;
    case 18:
      setDirectorUI8JL( value );
      break;
    case 19:
      setDirectorUI8JH( value );
      break;

  }

  sendDirectorVars( *m_pPlayer );
}

void Sapphire::QuestBattle::setSequence( uint8_t value )
{
  setDirectorSequence( value );
  sendDirectorVars( *m_pPlayer );
}

void Sapphire::QuestBattle::setBranch( uint8_t value )
{
  setDirectorBranch( value );
  sendDirectorVars( *m_pPlayer );
}

void Sapphire::QuestBattle::startQte()
{
  m_pPlayer->queuePacket( makeActorControl143( m_pPlayer->getId(), DirectorUpdate, getDirectorId(), 0x8000000A ) );
}

void Sapphire::QuestBattle::startEventCutscene()
{
  m_pPlayer->queuePacket( makeActorControl143( m_pPlayer->getId(), DirectorUpdate, getDirectorId(), 0x80000008 ) );
}

void Sapphire::QuestBattle::endEventCutscene()
{
  m_pPlayer->queuePacket( makeActorControl143( m_pPlayer->getId(), DirectorUpdate, getDirectorId(), 0x80000009 ) );
}

void Sapphire::QuestBattle::onRegisterEObj( Entity::EventObjectPtr object )
{
  if( object->getName() != "none" )
    m_eventObjectMap[ object->getName() ] = object;

  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto objData = pExdData->get< Sapphire::Data::EObj >( object->getObjectId() );
  if( objData )
    // todo: data should be renamed to eventId
    m_eventIdToObjectMap[ objData->data ] = object;
  else
    Logger::error( "InstanceContent::onRegisterEObj Zone " +
                   m_internalName + ": No EObj data found for EObj with ID: " +
                   std::to_string( object->getObjectId() ) );
}

Sapphire::Event::Director::DirectorState Sapphire::QuestBattle::getState() const
{
  return m_state;
}

void Sapphire::QuestBattle::onBeforePlayerZoneIn( Sapphire::Entity::Player& player )
{
  player.setRot( PI );
  player.setPos( { 0.f, 0.f, 0.f } );
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onPlayerSetup( *this, player );

  player.resetObjSpawnIndex();
}

Sapphire::Entity::EventObjectPtr Sapphire::QuestBattle::getEObjByName( const std::string& name )
{
  auto it = m_eventObjectMap.find( name );
  if( it == m_eventObjectMap.end() )
    return nullptr;

  return it->second;
}

void Sapphire::QuestBattle::onTalk( Sapphire::Entity::Player& player, uint32_t eventId, uint64_t actorId )
{
  // todo: handle exit (and maybe shortcut?) behaviour here

  auto it = m_eventIdToObjectMap.find( eventId );
  if( it == m_eventIdToObjectMap.end() )
    return;

  if( auto onTalkHandler = it->second->getOnTalkHandler() )
    onTalkHandler( player, it->second, getAsQuestBattle(), actorId );
  else
    player.sendDebug( "No onTalk handler found for interactable eobj with EObjID#{0}, eventId#{1}  ",
                      it->second->getObjectId(), eventId );
}

void
Sapphire::QuestBattle::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInstanceEnterTerritory( getAsQuestBattle(), player, eventId, param1, param2 );
}

void Sapphire::QuestBattle::clearDirector( Entity::Player& player )
{
  sendDirectorClear( player );

  player.setDirectorInitialized( false );
  // remove "bound by duty" state
  player.unsetStateFlag( PlayerStateFlag::BoundByDuty );
}

void Sapphire::QuestBattle::success()
{

  m_pPlayer->eventStart( m_pPlayer->getId(), getDirectorId(), Event::EventHandler::GameProgress, 1, 0 );
  m_pPlayer->playScene( getDirectorId(), 60001, 0x40000,
    [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.eventFinish( getDirectorId(), 1 );
      player.eventStart( player.getId(), getDirectorId(), Event::EventHandler::GameProgress, 1, 0 );
      player.playScene( getDirectorId(), 6, HIDE_HOTBAR | NO_DEFAULT_CAMERA,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.eventFinish( getDirectorId(), 1 );
                          auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
                          pScriptMgr->onDutyComplete( getAsQuestBattle(), *m_pPlayer );
                          player.exitInstance();
                        } );

    } );
}

void Sapphire::QuestBattle::fail()
{
  m_state = DutyFailed;
}

uint32_t Sapphire::QuestBattle::getQuestId() const
{
  return m_pBattleDetails->quest;
}

Sapphire::Entity::BNpcPtr
  Sapphire::QuestBattle::createBNpcFromLevelEntry( uint32_t levelId, uint8_t level, uint8_t type,
                                                   uint32_t hp, uint16_t nameId, uint32_t directorId,
                                                   uint8_t bnpcType )
{
  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto levelData = pExdData->get< Sapphire::Data::Level >( levelId );
  if( !levelData )
    return nullptr;

  if( levelData->type != 9 )
    return nullptr;

  auto bnpcBaseId = levelData->object;

  auto bnpcBaseData = pExdData->get< Sapphire::Data::BNpcBase >( bnpcBaseId );
  if( !bnpcBaseData )
    return nullptr;

  //BNpcTemplate( uint32_t id, uint32_t baseId, uint32_t nameId, uint64_t weaponMain, uint64_t weaponSub,
  //  uint8_t aggressionMode, uint8_t enemyType, uint8_t onlineStatus, uint8_t pose,
  //  uint16_t modelChara, uint32_t displayFlags, uint32_t* modelEquip,
  //  uint8_t* customize )

  std::vector< uint8_t > customize( 26 );
  if( bnpcBaseData->bNpcCustomize != 0 )
  {
    auto bnpcCustomizeData = pExdData->get< Sapphire::Data::BNpcCustomize >( bnpcBaseData->bNpcCustomize );
    if( bnpcCustomizeData )
    {
      customize[0] = bnpcCustomizeData->race;
      customize[1] = bnpcCustomizeData->gender;
      customize[2] = bnpcCustomizeData->bodyType;
      customize[3] = bnpcCustomizeData->height;
      customize[4] = bnpcCustomizeData->tribe;
      customize[5] = bnpcCustomizeData->face;
      customize[6] = bnpcCustomizeData->hairStyle;
      customize[7] = bnpcCustomizeData->hairHighlight;
      customize[8] = bnpcCustomizeData->skinColor;
      customize[9] = bnpcCustomizeData->eyeHeterochromia;
      customize[10] = bnpcCustomizeData->hairColor;
      customize[11] = bnpcCustomizeData->hairHighlightColor;
      customize[12] = bnpcCustomizeData->facialFeature;
      customize[13] = bnpcCustomizeData->facialFeatureColor;
      customize[14] = bnpcCustomizeData->eyebrows;
      customize[15] = bnpcCustomizeData->eyeColor;
      customize[16] = bnpcCustomizeData->eyeShape;
      customize[17] = bnpcCustomizeData->nose;
      customize[18] = bnpcCustomizeData->jaw;
      customize[19] = bnpcCustomizeData->mouth;
      customize[20] = bnpcCustomizeData->lipColor;
      customize[21] = bnpcCustomizeData->bustOrTone1;
      customize[22] = bnpcCustomizeData->extraFeature1;
      customize[23] = bnpcCustomizeData->extraFeature2OrBust;
      customize[24] = bnpcCustomizeData->facePaint;
      customize[25] = bnpcCustomizeData->facePaintColor;
    }
  }

  std::vector< uint32_t > models( 10 );
  uint64_t modelMain = 0;
  uint64_t modeloff = 0;
  if( bnpcBaseData->npcEquip != 0 )
  {
    auto npcEquipData = pExdData->get< Sapphire::Data::NpcEquip >( bnpcBaseData->npcEquip );
    if( npcEquipData )
    {
      modelMain = npcEquipData->modelMainHand;
      modeloff = npcEquipData->modelOffHand;

      models[0] = npcEquipData->modelHead;
      models[1] = npcEquipData->modelBody;
      models[2] = npcEquipData->modelHands;
      models[3] = npcEquipData->modelLegs;
      models[4] = npcEquipData->modelFeet;
      models[5] = npcEquipData->modelEars;
      models[6] = npcEquipData->modelNeck;
      models[7] = npcEquipData->modelWrists;
      models[8] = npcEquipData->modelLeftRing;
      models[9] = npcEquipData->modelRightRing;
    }
  }

  auto tmp = std::make_shared< Entity::BNpcTemplate >( 0, bnpcBaseId, nameId, modelMain, modeloff, 1, bnpcType, 0, 4,
                                                       bnpcBaseData->modelChara, 0, &models[0], &customize[0] );

  auto bnpc = std::make_shared< Entity::BNpc >( getNextActorId(), tmp, levelData->x, levelData->y, levelData->z,
                                                levelData->yaw, level, hp, shared_from_this(), m_pFw );

  bnpc->setDirectorId( directorId );
  return bnpc;
}
