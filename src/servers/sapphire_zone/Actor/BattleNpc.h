#ifndef _BATTLENPC_H
#define _BATTLENPC_H

#include "Actor.h"

namespace Core {
namespace Entity {

enum StateMode
{
   MODE_COMBAT,
   MODE_RETREAT,
   MODE_IDLE,
};

typedef struct
{
   uint32_t m_hateAmount;
   ActorPtr m_pActor;
} HateListEntry;

// class for Mobs inheriting from Actor
class BattleNpc : public Actor
{
public:
   BattleNpc();
   ~BattleNpc();

   BattleNpc( uint16_t modelId, uint16_t nameid, const Common::FFXIVARR_POSITION3& spawnPos, uint16_t bnpcBaseId = 0,
              uint32_t type = 2, uint8_t level = 0, uint8_t behaviour = 1, uint32_t mobType = 0 );

   //BattleNpc( uint32_t modelId, 
   //           uint32_t nameId,
   //           uint32_t bnpcBaseId,
   //           uint32_t level,
   //           const Common::FFXIVARR_POSITION3& spawnPos,
   //           uint32_t type = 2,  uint32_t behaviour = 1, uint32_t mobType = 0 );

   void initStatusEffectContainer();

   // send spawn packets to pTarget
   void spawn( PlayerPtr pTarget ) override;

   // send despawn packets to pTarget
   void despawn( ActorPtr pTarget ) override;

   uint8_t getLevel() const override;

   StateMode getMode() const;

   void setMode( StateMode mode );

   uint8_t getbehavior() const;

   void hateListAdd( ActorPtr pActor, int32_t hateAmount );

   void hateListUpdate( ActorPtr pActor, int32_t hateAmount );
   void hateListRemove( ActorPtr pActor );

   bool hateListHasActor( ActorPtr pActor );

   void resetPos();

   uint32_t getNameId() const;

   void hateListClear();

   ActorPtr hateListGetHighest();

   void aggro( ActorPtr pActor );

   void deaggro( ActorPtr pActor );

   void setOwner( PlayerPtr pPlayer );

   void onDeath() override;

   void onActionHostile( ActorPtr pSource ) override;

   ActorPtr getClaimer() const;

   void sendPositionUpdate();

   // return true if it reached the position
   bool moveTo( Common::FFXIVARR_POSITION3& pos );

   void update( int64_t currTime ) override;

   uint32_t getTimeOfDeath() const;

   void setTimeOfDeath( uint32_t tod );

private:

   static uint32_t m_nextID;
   StateMode m_mode;
   Common::FFXIVARR_POSITION3 m_posOrigin;
   uint8_t m_level;
   uint16_t m_modelId;
   uint16_t m_nameId;
   uint16_t m_bnpcBaseId;
   uint8_t m_behavior;
   uint32_t m_unk1;
   uint32_t m_unk2;
   std::set< HateListEntry* > m_hateList;
   ActorPtr m_pOwner;
   uint32_t m_timeOfDeath;
   uint32_t m_mobType;

};

}
}

#endif
