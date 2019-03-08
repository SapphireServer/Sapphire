#ifndef _QUESTMESSAGE_H
#define _QUESTMESSAGE_H

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief Packet to display a quest specific info message.
  */
  class QuestMessagePacket : public ZoneChannelPacket< FFXIVIpcQuestMessage >
  {
  public:
    QuestMessagePacket( Entity::ActorPtr pActor, uint32_t questId, int8_t msgId,
                        uint8_t type = 0, uint32_t var1 = 0, uint32_t var2 = 0 ) :
      ZoneChannelPacket< FFXIVIpcQuestMessage >( pActor->getId(), pActor->getId() )
    {
      initialize( questId, msgId, type, var1, var2 );
    };

  private:
    void initialize( uint32_t questId, int8_t msgId, uint8_t type, uint32_t var1, uint32_t var2 )
    {
      m_data.questId = questId;
      m_data.msgId = msgId;
      m_data.type = type;
      m_data.var1 = var1;
      m_data.var2 = var2;
    };
  };

}

#endif /* _QUESTMESSAGE_H */
