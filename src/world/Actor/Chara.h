#pragma once

#include <Common.h>
#include "Action/ActionLut.h"

#include "Forwards.h"
#include "GameObject.h"
#include <set>
#include <map>
#include <queue>
#include <array>
#include <numeric>

namespace Sapphire::Entity
{

  /*!
  \class Chara
  \brief Base class for all animate actors

  */
  class Chara : public GameObject
  {
  private:
    // array size for baseparam + bonuses arrays, 80 to have some spare room.
    constexpr static uint32_t STAT_ARRAY_SIZE = 80;

  public:

    using ActorStatsArray = std::array< uint32_t, STAT_ARRAY_SIZE >;

    ActorStatsArray m_baseStats{ 0 };
    ActorStatsArray m_bonusStats{ 0 };

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
    World::Action::ActionPtr m_pCurrentAction;
    /*! id of the director this chara is assigned to */
    uint32_t m_directorId;

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

    /*! Detour Crowd AgentId */
    uint32_t m_agentId;

    /*! Detour Crowd actor scale */
    float m_radius;

  public:
    Chara( Common::ObjKind type );

    virtual ~Chara() override;

    virtual void calculateStats() {};

    int64_t getLastUpdateTime() const;

    /// Status effect functions
    void addStatusEffect( StatusEffect::StatusEffectPtr pEffect );

    std::map< uint8_t, StatusEffect::StatusEffectPtr >::iterator removeStatusEffect( uint8_t effectSlotId, bool sendOrder = true );

    void replaceSingleStatusEffectById( uint32_t id );

    void removeSingleStatusEffectById( uint32_t id );

    void removeStatusEffectByFlag( Common::StatusEffectFlag flag );

    void updateStatusEffects();

    bool hasStatusEffect( uint32_t id );

    int8_t getStatusEffectSlotWithIdAndSource( uint8_t statusId, uint32_t sourceId );

    int8_t getStatusEffectSlotWithId( uint8_t statusId );

    int8_t getStatusEffectFreeSlot();

    void statusEffectFreeSlot( uint8_t slotId );

    uint8_t getPose() const;

    void setPose( uint8_t pose );

    std::map< uint8_t, Sapphire::StatusEffect::StatusEffectPtr > getStatusEffectMap() const;

    Sapphire::StatusEffect::StatusEffectPtr getStatusEffectById( uint32_t id ) const;

    void sendStatusEffectUpdate();

    /*! return a const pointer to the look array */
    const uint8_t* getLookArray() const;

    const uint32_t* getModelArray() const;

    // add a status effect by id
    void addStatusEffectById( StatusEffect::StatusEffectPtr pStatus );

    // add a status effect by id if it doesn't exist
    void addStatusEffectByIdIfNotExist( StatusEffect::StatusEffectPtr pStatus );

    // remove a status effect by id
    void removeSingleStatusEffectFromId( uint32_t id );
    /// End Status Effect Functions

    std::string getName() const;

    bool face( const Common::FFXIVARR_POSITION3& p );

    Common::Stance getStance() const;

    void setStance( Common::Stance stance );

    const ActorStatsArray& getStats() const;

    uint32_t getStatValue( Common::BaseParam baseParam ) const;

    float getStatValueFloat( Common::BaseParam baseParam ) const;

    uint32_t getBonusStat( Common::BaseParam baseParam ) const;

    void setStatValue( Common::BaseParam baseParam, uint32_t value );

    float getModifier( Common::ParamModifier paramModifier ) const;

    uint32_t getHp() const;

    uint32_t getHpPercent() const;

    uint32_t getMp() const;

    uint16_t getTp() const;

    uint16_t getGp() const;

    Common::InvincibilityType getInvincibilityType() const;

    Common::ClassJob getClass() const;

    void setClass( Common::ClassJob classJob );

    Common::Role getRole() const;

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

    void setTp( uint32_t tp );

    void setInvincibilityType( Common::InvincibilityType type );

    void die();

    uint64_t getLastAttack() const;

    void setLastAttack( uint64_t tickCount );

    Common::ActorStatus getStatus() const;

    void setStatus( Common::ActorStatus status );

    virtual void autoAttack( CharaPtr pTarget );

    virtual void onDeath() {};

    virtual void onDamageTaken( Chara& pSource ) {};

    virtual void onActionHostile( CharaPtr pSource ) {};

    virtual void onActionFriendly( Chara& pSource ) {};

    virtual void onTick();

    virtual void changeTarget( uint64_t targetId );

    virtual uint8_t getLevel() const;

    virtual void takeDamage( uint32_t damage );

    virtual void heal( uint32_t amount );

    virtual void restoreMP( uint32_t amount );

    virtual bool checkAction();

    virtual void update( uint64_t tickCount );

    World::Action::ActionPtr getCurrentAction() const;

    void setCurrentAction( World::Action::ActionPtr pAction );

    uint32_t getLastComboActionId() const;
    void setLastComboActionId( uint32_t actionId );

    uint32_t getDirectorId() const;
    void setDirectorId( uint32_t directorId );

    uint32_t getAgentId() const;
    void setAgentId( uint32_t agentId );

    float getRadius() const;

    Common::BaseParam getPrimaryStat() const;

  };

}