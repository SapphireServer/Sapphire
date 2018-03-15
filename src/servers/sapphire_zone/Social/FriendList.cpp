#include <cassert>
#include <boost/shared_ptr.hpp>
#include <Logging/Logger.h>

#include <sapphire_zone/Session.h>
#include <Network/PacketDef/Ipcs.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <sapphire_zone/Actor/Actor.h>
#include <sapphire_zone/Actor/Player.h>
#include <sapphire_zone/ServerZone.h>
#include <sapphire_zone/Zone/Zone.h>

#include <Database/DatabaseDef.h>
#include <Network/GamePacketNew.h>
#include "Group.h"
#include "FriendList.h"

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

using namespace Core::Social;

std::vector< PlayerEntry > Core::Social::FriendList::getFriendListEntries( uint16_t entryAmount )
{
   std::vector< PlayerEntry > entryList = {};
   uint16_t limit = 0;

   for ( const auto& member : m_groupMembers )
   {
      if ( limit == entryAmount )
         break;

      entryList.push_back( generatePlayerEntry( member, false ) );
      limit++;
   }

   for ( const auto& invite : m_groupInvites )
   {
      if ( limit == entryAmount )
         break;

      entryList.push_back( generatePlayerEntry( invite, true ) );
      limit++;
   }

   return entryList;
}


//todo: generalize this for linkshell etc
Core::Network::Packets::Server::PlayerEntry FriendList::generatePlayerEntry( uint64_t characterId, bool isInvite )
{
   // We check if player is online. If so, we can pull data from existing session in memory
   // Otherwise, we pull from SQL. We can optimize this later, there are quite a few choices here

   auto pSession = g_fw.get< ServerZone >()->getSession( characterId );

   // todo: set as offline in one of the unknown values, if session does not exist
   Core::Network::Packets::Server::PlayerEntry entry = {};

   entry.contentId = characterId;
   entry.timestamp = 1512799339;

   // todo: if invite change these
   entry.status = 2;
   entry.unknown = 0;
   //entry.entryIcon = 0xf;  
   entry.unavailable = 0;    // unavailable (other world)
   entry.one = 0;

   if ( pSession )
   {
      auto pPlayer = pSession->getPlayer();
      //entry.contentId = pPlayer->getContentId();
      //entry.bytes[2] = pPlayer->getCurrentZone()->getId();
      
      memcpy( entry.name, pPlayer->getName().c_str(), strlen( pPlayer->getName().c_str() ) );
      
      entry.classJob = pPlayer->getClass();

      entry.level = pPlayer->getLevel();
      entry.zoneId = pPlayer->getCurrentZone()->getGuId();
      entry.grandCompany = pPlayer->getGc();
      memcpy( &entry.fcTag[0], "Meme", 4 );
      entry.clientLanguage = 2;
      entry.knownLanguages = 0x0F;
      entry.onlineStatusMask = pPlayer->getOnlineStatusMask();

      g_fw.get< Logger >()->debug( std::to_string( pPlayer->getContentId() ) );
   }
   else
   {
      //todo: lets grab it from the db
      auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();

      //const std::string char_id_str = std::to_string( characterId );

      auto stmt = pDb->getPreparedStatement( Db::CharaDbStatements::CHARA_SEL );

      stmt->setUInt( 1, characterId );
      auto res = pDb->query( stmt );

      // todo: Is this correct? Seems so judging from retail
      if ( !res->next() )
      {
         entry.unavailable = 1;
      }
      else
      {
         // Todo: Can we make PlayerSQL a static function and use it for this?


         auto name = res->getString( "Name" );
         strcpy( entry.name, name.c_str() );
         //memcpy( entry.name, res->getString( "Name" ), strlen( pPlayer->getName().c_str() ) );

         //todo: pull actual FC name
         memcpy( &entry.fcTag[0], "Ao", 4 );
         entry.clientLanguage = res->getUInt8( "Language" );
         entry.knownLanguages = 0x0F;
         //entry.onlineStatusMask = pPlayer->getOnlineStatusMask();
      }


   }

   // TODO: no idea what this does - me neither
   //listPacket.data().entries[0].one = 1;

   g_fw.get< Logger >()->debug( std::to_string( characterId ) );

   //g_fw.get< Logger >()->debug( std::to_string( entry.contentId ) );

   return entry;
}