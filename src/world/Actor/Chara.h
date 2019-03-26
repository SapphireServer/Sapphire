#ifndef _CHARA_H_
#define _CHARA_H_

#include <Common.h>

#include "Forwards.h"
#include "Actor.h"
#include <set>
#include <map>
#include <queue>
#include <array>

namespace Sapphire::Entity
{

  /*!
  \class Chara
  \brief Base class for all animate actors

  */
  class Chara : public Actor
  {
  public:
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

    // array for bonuses, 80 to have some spare room.
    std::array< uint32_t, 80 > m_bonusStats;

  protected:
    char m_name[34];
    /*! Last tick time for the actor  ( in ms ) */
    int64_t m_lastTickTime;
    /*! Last time the actor performed an autoAttack ( in ms ) */
    uint64_t m_lastAttack;
    /*! Last time the actor was updated ( in ms ) */
    int64_t m_lastUpdate;
    /*! Current stance of the actor */
    Common::Stance m_currentStance;
    /*! Current staus of the actor */
    Common::ActorStatus m_status;
    /*! Max HP of the actor ( based on job / class ) */
    uint32_t m_maxHp;
    /*! Max MP of the actor ( based on job / class ) */
    uint32_t m_maxMp;
    /*! Current HP of the actor */
    uint32_t m_hp;
    /*! Current MP of the actor */
    uint32_t m_mp;
    /*! Current TP of the actor */
    uint16_t m_tp;
    /*! Current GP of the actor */
    uint16_t m_gp;
    /*! Additional look info of the actor */
    uint8_t m_customize[26];
    /*! Additional model info */
    uint32_t m_modelEquip[10];
    /*! Current class of the actor */
    Common::ClassJob m_class;
    /*! Id of the currently selected target actor */
    uint64_t m_targetId;
    /*! Ptr to a queued action */
    Action::ActionPtr m_pCurrentAction;

    /*!
     * @brief the id of the last combo action used (IgnoresCombo)
     */
    uint32_t m_lastComboActionId;

    /*!
     * @brief when the last combo action was used in ms
     */
    uint64_t m_lastComboActionTime;

    /*! Invincibility type */
    Common::InvincibilityType m_invincibilityType;

    uint8_t m_pose;

    /*! Status effects */
    const uint8_t MAX_STATUS_EFFECTS = 30;
    std::queue< uint8_t > m_statusEffectFreeSlotQueue;
    std::vector< std::pair< uint8_t, uint32_t > > m_statusEffectList;
    std::map< uint8_t, StatusEffect::StatusEffectPtr > m_statusEffectMap;
    FrameworkPtr m_pFw;

  public:
    Chara( Common::ObjKind type, FrameworkPtr pFw );

    virtual ~Chara() override;

    virtual void calculateStats() {};

    int64_t getLastUpdateTime() const;

    /// Status effect functions
    void addStatusEffect( StatusEffect::StatusEffectPtr pEffect );

    void removeStatusEffect( uint8_t effectSlotId );

    void removeSingleStatusEffectById( uint32_t id );

    void updateStatusEffects();

    bool hasStatusEffect( uint32_t id );

    int8_t getStatusEffectFreeSlot();

    void statusEffectFreeSlot( uint8_t slotId );

    uint8_t getPose() const;

    void setPose( uint8_t pose );

    std::map< uint8_t, Sapphire::StatusEffect::StatusEffectPtr > getStatusEffectMap() const;

    void sendStatusEffectUpdate();

    /*! return a const pointer to the look array */
    const uint8_t* getLookArray() const;

    const uint32_t* getModelArray() const;

    // add a status effect by id
    void addStatusEffectById( uint32_t id, int32_t duration, Entity::Chara& source, uint16_t param = 0 );

    // add a status effect by id if it doesn't exist
    void addStatusEffectByIdIfNotExist( uint32_t id, int32_t duration, Entity::Chara& source, uint16_t param = 0 );

    // remove a status effect by id
    void removeSingleStatusEffectFromId( uint32_t id );
    /// End Status Effect Functions

    std::string getName() const;

    bool face( const Common::FFXIVARR_POSITION3& p );

    Common::Stance getStance() const;

    void setStance( Common::Stance stance );

    ActorStats getStats() const;

    uint32_t getHp() const;

    uint32_t getMp() const;

    uint16_t getTp() const;

    uint16_t getGp() const;

    Common::InvincibilityType getInvincibilityType() const;

    Common::ClassJob getClass() const;

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

    Common::ActorStatus getStatus() const;

    void setStatus( Common::ActorStatus status );

    virtual void autoAttack( CharaPtr pTarget );

    virtual void onDeath() {};

    virtual void onDamageTaken( Chara& pSource ) {};

    virtual void onActionHostile( CharaPtr pSource ) {};

    virtual void onActionFriendly( Chara& pSource ) {};

    virtual void onTick() {};

    virtual void changeTarget( uint64_t targetId );

    virtual uint8_t getLevel() const;

    virtual void sendStatusUpdate();

    virtual void takeDamage( uint32_t damage );

    virtual void heal( uint32_t amount );

    virtual bool checkAction();

    virtual void update( int64_t currTime );

    Action::ActionPtr getCurrentAction() const;

    void setCurrentAction( Action::ActionPtr pAction );

    uint32_t getLastComboActionId() const;
    void setLastComboActionId( uint32_t actionId );

    uint32_t getBonusStat( Common::BaseParam bonus ) const;

  };

}
#endif
