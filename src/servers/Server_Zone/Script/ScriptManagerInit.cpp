#include <chaiscript/chaiscript.hpp>

#include <Server_Common/Config/XMLConfig.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Script/ChaiscriptStdLib.h>

#include "ServerZone.h"

#include "Script/ScriptManager.h"

#include "Zone/Zone.h"
#include "Actor/Player.h"
#include "Actor/BattleNpc.h"
#include "Event/Event.h"
#include "Event/EventHelper.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "StatusEffect/StatusEffect.h"

#include <boost/lexical_cast.hpp>

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;

int Core::Scripting::ScriptManager::init()
{
   // ACTOR / PLAYER BINDINGS
   /////////////////////////////////////////////////////////////////////////////////////////////
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getName ), "getName" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getId ), "getId" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getHp ), "getHp" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getMp ), "getMp" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getTp ), "getTp" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getLevel ), "getLevel" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::getTargetId ), "getTargetId" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::addStatusEffect ), "addStatusEffect" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::addStatusEffectById ), "addStatusEffectById" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::addStatusEffectByIdIfNotExist ), "addStatusEffectByIdIfNotExist" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Actor::takeDamage ), "takeDamage" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::forceZoneing ), "setZone" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getClassAsInt ), "getClass" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getRace ), "getRace" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getGender ), "getGender" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::gainExp ), "gainExp" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::unlock ), "unlock" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::registerAetheryte ), "aetheryteRegister" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::learnAction ), "learnAction" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getHomepoint ), "getHomepoint" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setHomepoint ), "setHomepoint" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::returnToHomepoint ), "returnToHomepoint" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::teleport ), "teleport" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::prepareZoning ), "prepareZoning" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::isInCombat ), "isInCombat" );
   
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getCurrency ), "getCurrency" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::addCurrency ), "addCurrency" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::removeCurrency ), "removeCurrency" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getCrystal ), "getCrystals" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::addCrystal ), "addCrystals" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::removeCrystal ), "removeCrystals" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::updateQuest ), "questUpdate" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::finishQuest ), "questFinish" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::sendQuestMessage ), "questMessage" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestSeq ), "questGetSeq" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::hasQuest ), "hasQuest" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getZoneId ), "getZoneId" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::handleScriptSkill ), "handleScriptSkill" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getOpeningSequence ), "getOpeningSequence" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setOpeningSequence ), "setOpeningSequence" );

   m_pChaiHandler->add( chaiscript::fun( &Core::Event::mapEventActorToRealActor ), "mapActor" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8A ), "getQuestUI8A" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8B ), "getQuestUI8B" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8C ), "getQuestUI8C" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8D ), "getQuestUI8D" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8E ), "getQuestUI8E" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8F ), "getQuestUI8F" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8AH ), "getQuestUI8AH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8BH ), "getQuestUI8BH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8CH ), "getQuestUI8CH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8DH ), "getQuestUI8DH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8EH ), "getQuestUI8EH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8FH ), "getQuestUI8FH" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8AL ), "getQuestUI8AL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8BL ), "getQuestUI8BL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8CL ), "getQuestUI8CL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8DL ), "getQuestUI8DL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8EL ), "getQuestUI8EL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI8FL ), "getQuestUI8FL" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI16A ), "getQuestUI16A" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI16B ), "getQuestUI16B" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI16C ), "getQuestUI16C" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestUI32A ), "getQuestUI32A" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestBitFlag8 ), "getQuestBitFlag8" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestBitFlag16 ), "getQuestBitFlag16" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestBitFlag24 ), "getQuestBitFlag24" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestBitFlag32 ), "getQuestBitFlag32" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestBitFlag40 ), "getQuestBitFlag40" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::getQuestBitFlag48 ), "getQuestBitFlag48" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8A ), "setQuestUI8A" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8B ), "setQuestUI8B" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8C ), "setQuestUI8C" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8D ), "setQuestUI8D" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8E ), "setQuestUI8E" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8F ), "setQuestUI8F" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8AH ), "setQuestUI8AH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8BH ), "setQuestUI8BH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8CH ), "setQuestUI8CH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8DH ), "setQuestUI8DH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8EH ), "setQuestUI8EH" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8FH ), "setQuestUI8FH" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8AL ), "setQuestUI8AL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8BL ), "setQuestUI8BL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8CL ), "setQuestUI8CL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8DL ), "setQuestUI8DL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8EL ), "setQuestUI8EL" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI8FL ), "setQuestUI8FL" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI16A ), "setQuestUI16A" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI16B ), "setQuestUI16B" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI16C ), "setQuestUI16C" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestUI32A ), "setQuestUI32A" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestBitFlag8 ), "setQuestBitFlag8" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestBitFlag16 ), "setQuestBitFlag16" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestBitFlag24 ), "setQuestBitFlag24" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestBitFlag32 ), "setQuestBitFlag32" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestBitFlag40 ), "setQuestBitFlag40" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::setQuestBitFlag48 ), "setQuestBitFlag48" );

   m_pChaiHandler->add(chaiscript::fun(&Entity::Player::giveQuestRewards), "giveQuestRewards");

   m_pChaiHandler->add( chaiscript::fun< void, Entity::Player, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t >( &Entity::Player::eventPlay ), "eventPlay" );
   m_pChaiHandler->add( chaiscript::fun< void, Entity::Player, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, EventReturnCallback >( &Entity::Player::eventPlay ), "eventPlay" );
   m_pChaiHandler->add( chaiscript::fun< void, Entity::Player, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, EventReturnCallback >( &Entity::Player::eventPlay ), "eventPlay" );
   m_pChaiHandler->add( chaiscript::fun< void, Entity::Player, uint32_t, uint32_t, uint32_t, EventReturnCallback >( &Entity::Player::eventPlay ), "eventPlay" );
   m_pChaiHandler->add( chaiscript::fun< void, Entity::Player, uint32_t, uint32_t, uint32_t >( &Entity::Player::eventPlay ), "eventPlay" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::eventActionStart ), "eventActionStart" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::eventItemActionStart ), "eventItemActionStart" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::changePosition ), "changePos" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::tryAddItem ), "tryAddItem" );

   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::isAetheryteRegistered ), "isAetheryteRegistered" );
   m_pChaiHandler->add( chaiscript::fun( &Entity::Player::isActionLearned ), "isActionLearned" );

   m_pChaiHandler->add( chaiscript::base_class< Entity::Actor, Entity::Player >() );
   m_pChaiHandler->add( chaiscript::base_class< Entity::Actor, Entity::BattleNpc >() );
   m_pChaiHandler->add( chaiscript::user_type< Entity::Actor >(), "Actor" );
   m_pChaiHandler->add( chaiscript::user_type< Entity::Player >(), "Player" );
   m_pChaiHandler->add( chaiscript::user_type< Entity::BattleNpc >(), "BattleNpc" );
   m_pChaiHandler->add( chaiscript::user_type< StatusEffect::StatusEffect >(), "StatusEffect" );

   m_pChaiHandler->add( chaiscript::fun( &StatusEffect::StatusEffect::registerTickEffect ), "registerTickEffect" );

   m_pChaiHandler->add( chaiscript::user_type< Zone >(), "Zone" );
   m_pChaiHandler->add( chaiscript::fun( &Zone::getName ), "getName" );

   m_pChaiHandler->add( chaiscript::fun( &registerBnpcTemplate ), "registerBnpcTemplate" );

   // EVENT BINDINGS
   /////////////////////////////////////////////////////////////////////////////////////////////

   std::set< std::string > chaiFiles;

   loadDir( g_serverZone.getConfig()->getValue< std::string >( "Settings.General.ScriptPath", "../scripts/chai" ), chaiFiles );

   uint16_t scriptCount = 0;
   uint16_t errorCount = 0;
   for( auto itr = chaiFiles.begin(); itr != chaiFiles.end(); ++itr )
   {
      auto& fileName = *itr;

      try
      {
         m_pChaiHandler->eval_file( fileName );
         scriptCount++;
      }
      catch( std::exception& e )
      {
         g_log.Log( LoggingSeverity::error, e.what() );
         errorCount++;
      }

   }

   g_log.info( "\tloaded " + std::to_string( scriptCount ) +
               " scripts, " + std::to_string( errorCount ) + " errors." );

   std::function<std::string( Entity::Player& ) > f =
      m_pChaiHandler->eval< std::function<std::string( Entity::Player& ) > >( "onFirstEnterWorld" );

   m_onFirstEnterWorld = f;


   return true;
}

