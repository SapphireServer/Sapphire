#include <cassert>
#include <ctime>

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


uint32_t FriendList::addMember( uint64_t contentId, FriendEntryType friendEntryType )
{
   assert( contentId != 0 );

   uint32_t logMessage = 0;

   m_members.insert( contentId );

   FriendEntry friendEntry;
   friendEntry.timestamp = std::time( nullptr );
   friendEntry.friendGroup = 0;
   friendEntry.entryStatus = friendEntryType;
   friendEntry.unknown = 0;

   m_entries.insert( friendEntry );

   return logMessage;
}

std::set< FriendEntry >& FriendList::getEntries()
{
   return m_entries;
}

/*
uint32_t Group::addInvite( uint64_t characterId )
{
   assert( characterId != 0 );

   uint32_t logMessage = 0;

   g_fw.get< Logger >()->debug( "here" );

   if( m_groupMembers.find( characterId ) != m_groupMembers.end() || m_groupInvites.find( characterId ) != m_groupInvites.end() )
   {
      // That player is already a friend or has been sent a request.
      logMessage = 312;
      return logMessage;
   }
   
   if( getTotalSize() >= getCapacity() )
   {
      // Unable to send friend request. The other player's friend list is full.
      logMessage = 314;
      return logMessage;
   }


   m_groupInvites.insert( characterId );

   return logMessage;
}
*/
std::vector< PlayerEntry > FriendList::getFriendListEntries( uint16_t entryAmount )
{
   std::vector< PlayerEntry > entryList = {};
   uint16_t limit = 0;

   for ( const auto& member : m_members )
   {
      if ( limit == entryAmount )
         break;

      entryList.push_back( generatePlayerEntry( member ) );
      limit++;
   }

   return entryList;
}


//todo: generalize this for linkshell etc
Core::Network::Packets::Server::PlayerEntry FriendList::generatePlayerEntry( uint64_t contentId )
{
   // We check if player is online. If so, we can pull data from existing session in memory
   // Otherwise, we pull from SQL. We can optimize this later, there are quite a few choices here

   auto pSession = g_fw.get< ServerZone >()->getSession( contentId );
   
   auto dataIndex = m_members.find( contentId );
   auto friendEntry = m_entries;

   // todo: set as offline in one of the unknown values, if session does not exist
   Core::Network::Packets::Server::PlayerEntry entry = {};

   entry.contentId = contentId;
   entry.timestamp = 1517767262;

   // todo: if invite change these

   entry.status = 16;
   entry.unknown = 0;
   //entry.entryIcon = 0xf;  
   entry.unavailable = 0;    // unavailable (other world)
   entry.one = 1;

   if ( pSession )
   {
      auto pPlayer = pSession->getPlayer();
      //entry.contentId = pPlayer->getContentId();
      //entry.bytes[2] = pPlayer->getCurrentZone()->getId();
      
      memcpy( entry.name, pPlayer->getName().c_str(), strlen( pPlayer->getName().c_str() ) );
      
      entry.classJob = pPlayer->getClass();

      entry.level = pPlayer->getLevel();
      entry.zoneId = pPlayer->getCurrentZone()->getTerritoryId();
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

      //todo: this WILL break
      stmt->setUInt( 1, contentId );
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

   g_fw.get< Logger >()->debug( std::to_string( contentId ) );

   //g_fw.get< Logger >()->debug( std::to_string( entry.contentId ) );

   return entry;
}