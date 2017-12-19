#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <Server_Common/Common.h>
#include <boost/enable_shared_from_this.hpp>

#include "Forwards.h"
#include <set>
#include <map>
#include <queue>

namespace Core {
namespace Entity {

/*!
\class Actor
\brief Base class for all actors

\author Mordred
*/
class Actor : public boost::enable_shared_from_this< Actor >
{
public:
   enum ObjKind : uint8_t
   {
      None = 0x00,
      Player = 0x01,
      BattleNpc = 0x02,
      EventNpc = 0x03,
      Treasure = 0x04,
      Aetheryte = 0x05,
      GatheringPoint = 0x06,
      EventObj = 0x07,
      Mount = 0x08,
      Companion = 0x09,
      Retainer = 0x0A,
      Area = 0x0B,
      Housing = 0x0C,
      Cutscene = 0x0D,
      CardStand = 0x0E,
   };

   enum Stance : uint8_t
   {
      Passive = 0,
      Active = 1,
   };

   enum DisplayFlags : uint16_t
   {
      ActiveStance = 0x001,
      Invisible = 0x020,
      HideHead = 0x040,
      HideWeapon = 0x080,
      Faded = 0x100,
      Visor = 0x800,
   };

   enum struct ActorStatus : uint8_t
   {
      Idle = 0x01,
      Dead = 0x02,
      Sitting = 0x03,
      Mounted = 0x04,
      Crafting = 0x05,
      Gathering = 0x06,
      Melding = 0x07,
      SMachine = 0x08
   };

   struct ActorStats
   {
      uint32_t max_mp = 0;
      uint32_t max_hp = 0;

      uint32_t str = 0;
      uint32_t dex = 0;
      uint32_t vit = 0;
      uint32_t inte = 0;
      uint32_t mnd = 0;
      uint32_t pie = 0;

      uint32_t tenacity = 0;
      uint32_t attack = 0;
      uint32_t defense = 0;
      uint32_t accuracy = 0;
      uint32_t spellSpeed = 0;
      uint32_t magicDefense = 0;
      uint32_t critHitRate = 0;
      uint32_t resistSlash = 0;
      uint32_t resistPierce = 0;
      uint32_t resistBlunt = 0;
      uint32_t attackPotMagic = 0;
      uint32_t healingPotMagic = 0;
      uint32_t determination = 0;
      uint32_t skillSpeed = 0;

      uint32_t resistSlow = 0;
      uint32_t resistSilence = 0;
      uint32_t resistBlind = 0;
      uint32_t resistPoison = 0;
      uint32_t resistStun = 0;
      uint32_t resistSleep = 0;
      uint32_t resistBind = 0;
      uint32_t resistHeavy = 0;

      uint32_t resistFire = 0;
      uint32_t resistIce = 0;
      uint32_t resistWind = 0;
      uint32_t resistEarth = 0;
      uint32_t resistLightning = 0;
      uint32_t resistWater = 0;

   } m_baseStats;

protected:
   // TODO: The position class should probably be abolished and
   //       the FFXIV_POS struct used instead ( the functions in there
   //       could be moved to a FFXIV_POS_Helper namespace and rotation to 
   //       its own member )
   /*! Position of the actor */
   Common::FFXIVARR_POSITION3 m_pos;
   float m_rot;
   /*! Name of the actor */
   char                 m_name[34];
   /*! Id of the zone the actor currently is in */
   uint32_t	            m_zoneId;
   /*! Id of the actor */
   uint32_t             m_id;
   /*! Type of the actor */
   ObjKind              m_objKind;
   /*! Ptr to the ZoneObj the actor belongs to */
   ZonePtr              m_pCurrentZone;
   /*! Last tick time for the actor  ( in ms ) */
   uint64_t             m_lastTickTime;
   /*! Last time the actor performed an autoAttack ( in ms ) */
   uint64_t	            m_lastAttack;
   /*! Last time the actor was updated ( in ms ) */
   uint64_t             m_lastUpdate;
   /*! Current stance of the actor */
   Stance               m_currentStance;
   /*! Current staus of the actor */
   ActorStatus          m_status;
   /*! Max HP of the actor ( based on job / class ) */
   uint32_t             m_maxHp;
   /*! Max MP of the actor ( based on job / class ) */
   uint32_t             m_maxMp;
   /*! Current HP of the actor */
   uint32_t	            m_hp;
   /*! Current MP of the actor */
   uint32_t             m_mp;
   /*! Current TP of the actor */
   uint16_t             m_tp;
   /*! Current GP of the actor */
   uint16_t             m_gp;
   /*! Additional look info of the actor */
   uint8_t              m_customize[26];
   /*! Current class of the actor */
   Common::ClassJob     m_class;
   /*! Id of the currently selected target actor */
   uint64_t             m_targetId;
   /*! Ptr to a queued action */
   Action::ActionPtr    m_pCurrentAction;
   /*! Invincibility type */
   Common::InvincibilityType m_invincibilityType;

   /*! Status effects */
   const uint8_t MAX_STATUS_EFFECTS = 30;
   std::queue< uint8_t > m_statusEffectFreeSlotQueue;
   std::vector< std::pair< uint8_t, uint32_t> > m_statusEffectList;
   std::map< uint8_t, StatusEffect::StatusEffectPtr > m_statusEffectMap;

public:
   Actor();

   virtual ~Actor();

   virtual void calculateStats() {};

   uint32_t getId() const;

   /// Status effect functions 
   void addStatusEffect( StatusEffect::StatusEffectPtr pEffect );
   void removeStatusEffect( uint8_t effectSlotId );
   void removeSingleStatusEffectById( uint32_t id );
   void updateStatusEffects();

   bool hasStatusEffect( uint32_t id );

   int8_t getStatusEffectFreeSlot();
   void statusEffectFreeSlot( uint8_t slotId );

   std::map< uint8_t, Core::StatusEffect::StatusEffectPtr > getStatusEffectMap() const;

   void sendStatusEffectUpdate();
   // add a status effect by id
   void addStatusEffectById( uint32_t id, int32_t duration, Entity::Actor& pSource, uint16_t param = 0 );

   // add a status effect by id if it doesn't exist
   void addStatusEffectByIdIfNotExist( uint32_t id, int32_t duration, Entity::Actor& pSource, uint16_t param = 0 );

   // remove a status effect by id
   void removeSingleStatusEffectFromId( uint32_t id );
   /// End Status Effect Functions

   void setPosition( const Common::FFXIVARR_POSITION3& pos );
   void setPosition( float x, float y, float z );

   void setRotation( float rot );

   float getRotation() const;

   Common::FFXIVARR_POSITION3& getPos();

   std::string getName() const;

   bool isPlayer() const;

   bool isMob() const;

   std::set< ActorPtr > getInRangeActors( bool includeSelf = false );

   bool face( const Common::FFXIVARR_POSITION3& p );

   Stance getStance() const;

   void setStance( Stance stance );

   ActorStats getStats() const;

   uint32_t getHp() const;

   uint32_t getMp() const;

   uint16_t getTp() const;

   uint16_t getGp() const;

   Common::InvincibilityType getInvincibilityType() const;

   Common::ClassJob getClass() const;

   uint8_t getClassAsInt() const;

   void setClass( Common::ClassJob classJob );

   void setTargetId( uint64_t targetId );

   uint64_t getTargetId() const;

   bool isAlive() const;

   virtual uint32_t getMaxHp() const;

   virtual uint32_t getMaxMp() const;

   void resetHp();

   void resetMp();

   void setHp( uint32_t hp );

   void setMp( uint32_t mp );

   void setGp( uint32_t gp );

   void setInvincibilityType( Common::InvincibilityType type );

   void die();

   ActorStatus getStatus() const;

   void setStatus( ActorStatus  status );

   void handleScriptSkill( uint32_t type, uint16_t actionId, uint64_t param1, uint64_t param2, Entity::Actor& target );

   virtual void autoAttack( ActorPtr pTarget );

   virtual void spawn( PlayerPtr pTarget ) {}
   virtual void despawn( ActorPtr pTarget ) {}

   virtual void onRemoveInRangeActor( ActorPtr pActor ) {}
   virtual void onDeath() {};
   virtual void onDamageTaken( Actor& pSource ) {};
   virtual void onActionHostile( Core::Entity::ActorPtr pSource ) {};
   virtual void onActionFriendly( Actor& pSource ) {};
   virtual void onTick() {};

   virtual void changeTarget( uint64_t targetId );
   virtual uint8_t getLevel() const;
   virtual void sendStatusUpdate( bool toSelf = true );
   virtual void takeDamage( uint32_t damage );
   virtual void heal( uint32_t amount );
   virtual bool checkAction();
   virtual void update( int64_t currTime ) {};
   
   PlayerPtr getAsPlayer();
   BattleNpcPtr getAsBattleNpc();

   Action::ActionPtr getCurrentAction() const;

   void setCurrentAction( Action::ActionPtr pAction );

   ///// IN RANGE LOGIC /////

   // check if another actor is in the actors in range set
   bool isInRangeSet( ActorPtr pActor ) const;

   ActorPtr getClosestActor();

   void sendToInRangeSet( Network::Packets::GamePacketPtr pPacket, bool bToSelf = false );

   // add an actor to in range set
   virtual void addInRangeActor( ActorPtr pActor );

   // remove an actor from the in range set
   void removeInRangeActor( ActorPtr pActor );

   // return true if there is at least one actor in the in range set
   bool hasInRangeActor() const;

   // clear the whole in range set, this does no cleanup
   virtual void clearInRangeSet();

   ZonePtr getCurrentZone() const;

   void setCurrentZone( ZonePtr currZone );

   // get the current cell of a region the actor is in
   Cell* getCell() const;

   // set the current cell
   void setCell( Cell* pCell );


   // TODO: Why did i even declare them publicly here?!
   std::set< ActorPtr >            m_inRangeActors;
   std::set< PlayerPtr >           m_inRangePlayers;
   std::map< uint32_t, ActorPtr >  m_inRangeActorMap;

   Core::Cell*          m_pCell;

};

}
}
#endif
