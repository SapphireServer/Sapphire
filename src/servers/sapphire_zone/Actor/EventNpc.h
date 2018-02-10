#ifndef _EVENTNPC_H
#define _EVENTNPC_H

#include "Actor.h"

namespace Core {
namespace Entity {

// class for Mobs inheriting from Actor
class EventNpc : public Actor
{
public:
   EventNpc();
   virtual ~EventNpc() override;

   EventNpc( uint32_t enpcId, const Common::FFXIVARR_POSITION3& spawnPos, float rotation );

   // send spawn packets to pTarget
   void spawn( PlayerPtr pTarget ) override;

   // send despawn packets to pTarget
   void despawn( PlayerPtr pTarget ) override;

   uint8_t getLevel() const override;

   void resetPos();

   uint32_t getEnpcId() const;

private:

   static uint32_t m_nextID;
   Common::FFXIVARR_POSITION3 m_posOrigin;
   uint8_t m_level;
   uint32_t m_eNpcId;

};

}
}

#endif
