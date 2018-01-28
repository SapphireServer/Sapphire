#include <ScriptObject.h>

#include <Session.h>
#include <common/Network/PacketContainer.h>
#include <Network/GameConnection.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/GamePacketNew.h>
#include <servers/sapphire_zone/Network/PacketWrappers/InitUIPacket.h>
#include <cinttypes>

class Set : public DebugCommandScript
{
public:
   Set() : DebugCommandScript( "set", "Executes SET commands", 1 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      player.sendDebug( subCommand );
      player.sendDebug( params );

      if( ( ( subCommand == "pos" ) || ( subCommand == "posr" ) ) && ( params != "" ) )
      {
         int32_t posX;
         int32_t posY;
         int32_t posZ;

         sscanf( params.c_str(), "%d %d %d", &posX, &posY, &posZ );

         if( ( posX == 0xcccccccc ) || ( posY == 0xcccccccc ) || ( posZ == 0xcccccccc ) )
         {
            player.sendUrgent( "Syntaxerror." );
            return;
         }

         if( subCommand == "pos" )
            player.setPosition( static_cast< float >( posX ),
                                static_cast< float >( posY ),
                                static_cast< float >( posZ ) );
         else
            player.setPosition( player.getPos().x + static_cast< float >( posX ),
                                player.getPos().y + static_cast< float >( posY ),
                                player.getPos().z + static_cast< float >( posZ ) );

         Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorSetPos >
            setActorPosPacket( player.getId() );
         setActorPosPacket.data().x = player.getPos().x;
         setActorPosPacket.data().y = player.getPos().y;
         setActorPosPacket.data().z = player.getPos().z;
         player.queuePacket( setActorPosPacket );

      }
      else if( ( subCommand == "tele" ) && ( params != "" ) )
      {
         int32_t aetheryteId;
         sscanf( params.c_str(), "%i", &aetheryteId );

         player.teleport( aetheryteId );
      }
      else if( ( subCommand == "discovery" ) && ( params != "" ) )
      {
         int32_t map_id;
         int32_t discover_id;
         sscanf( params.c_str(), "%i %i", &map_id, &discover_id );

         Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcDiscovery > discoveryPacket( player.getId() );
         discoveryPacket.data().map_id = map_id;
         discoveryPacket.data().map_part_id = discover_id;
         player.queuePacket( discoveryPacket );
      }

//      else if( ( subCommand == "discovery_pos" ) && ( params != "" ) )
//      {
//         int32_t map_id;
//         int32_t discover_id;
//         int32_t pos_id;
//         sscanf( params.c_str(), "%i %i %i", &pos_id, &map_id, &discover_id );
//
//         std::string query2 = "UPDATE IGNORE `discoveryinfo` SET `discover_id` = '" + std::to_string( discover_id ) +
//                              "' WHERE `discoveryinfo`.`id` = " + std::to_string( pos_id ) + ";";
//
//         std::string query1 = "INSERT IGNORE INTO `discoveryinfo` (`id`, `map_id`, `discover_id`) VALUES ('" + std::to_string( pos_id ) +
//                              "', '" + std::to_string( map_id ) +
//                              "', '" + std::to_string( discover_id ) + "')";
//
//         g_charaDb.execute( query1 );
//         g_charaDb.execute( query2 );
//
//      }

      else if( subCommand == "discovery_reset" )
      {
         player.resetDiscovery();
         player.queuePacket( Network::Packets::Server::InitUIPacket( player ) );
      }
      else if( subCommand == "classjob" )
      {
         int32_t id;

         sscanf( params.c_str(), "%d", &id );

         if( player.getLevelForClass( static_cast< Common::ClassJob > ( id ) ) == 0 )
         {
            player.setLevelForClass( 1, static_cast< Common::ClassJob > ( id ) );
            player.setClassJob( static_cast< Common::ClassJob > ( id ) );
         }
         else
            player.setClassJob( static_cast< Common::ClassJob > ( id ) );
      }
      else if ( subCommand == "cfpenalty" )
      {
         int32_t minutes;
         sscanf( params.c_str(), "%d", &minutes );

         player.setCFPenaltyMinutes( minutes );
      }
      else if ( subCommand == "eorzeatime" )
      {
         uint64_t timestamp;
         sscanf( params.c_str(), "%" SCNu64, &timestamp );

         player.setEorzeaTimeOffset( timestamp );
         player.sendNotice( "Eorzea time offset: " + std::to_string( timestamp ) );
      }
      else if ( subCommand == "model" )
      {
         uint32_t slot;
         uint32_t val;
         sscanf( params.c_str(), "%d %d", &slot, &val );

         player.setModelForSlot( static_cast< Inventory::EquipSlot >( slot ), val );
         player.sendModel();
         player.sendDebug( "Model updated" );
      }
      else if ( subCommand == "mount" )
      {
         int32_t id;
         sscanf( params.c_str(), "%d", &id );

         player.dismount();
         player.mount( id );
      }
      else
      {
         player.sendUrgent( subCommand + " is not a valid SET command." );
      }
   }
};