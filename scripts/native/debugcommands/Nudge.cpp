#include <ScriptObject.h>
#include <common/Util/UtilMath.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/GamePacketNew.h>

class Nudge : public DebugCommandScript
{
public:
   Nudge() : DebugCommandScript( "nudge", "Nudge player in a direction", 1 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      // check if the command has parameters
      std::string tmpCommand = std::string( data.c_str() + m_cmd.length() + 1 );

      std::size_t spos = tmpCommand.find_first_of( " " );

      auto& pos = player.getPos();

      int32_t offset = 0;
      char direction[20];
      memset( direction, 0, 20 );

      sscanf( tmpCommand.c_str(), "%d %s", &offset, direction );

      if( direction[0] == 'u' || direction[0] == '+' )
      {
         pos.y += offset;
         player.sendNotice( "nudge: Placing up " + std::to_string( offset ) + " yalms" );
      }
      else if( direction[0] == 'd' || direction[0] == '-' )
      {
         pos.y -= offset;
         player.sendNotice( "nudge: Placing down " + std::to_string( offset ) + " yalms" );

      }
      else
      {
         float angle = player.getRotation() + ( PI / 2 );
         pos.x -= offset * cos( angle );
         pos.z += offset * sin( angle );
         player.sendNotice( "nudge: Placing forward " + std::to_string( offset ) + " yalms" );
      }
      if( offset != 0 )
      {
         Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorSetPos >
            setActorPosPacket( player.getId() );
         setActorPosPacket.data().x = player.getPos().x;
         setActorPosPacket.data().y = player.getPos().y;
         setActorPosPacket.data().z = player.getPos().z;
         setActorPosPacket.data().r16 = Math::Util::floatToUInt16Rot( player.getRotation() );
         player.queuePacket( setActorPosPacket );
      }
   }
};