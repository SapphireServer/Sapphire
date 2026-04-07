#pragma once

#include <Common.h>

#include "Chara.h"
#include "Forwards.h"
#include "ForwardsZone.h"
#include "Npc.h"
#include <map>
#include <queue>
#include <unordered_map>

namespace Sapphire::Entity
{

  struct HateListEntry {
    uint32_t m_hateAmount;
    CharaPtr m_pChara;
  };
  using HateListEntryPtr = std::shared_ptr< HateListEntry >;
  using HateList = std::unordered_map< uint32_t, HateListEntryPtr >;

  enum class BNpcState
  {
    Idle,
    Combat,
    Retreat,
    Roaming,
    JustDied,
    Dead,
  };

  enum BNpcFlag
  {
    Immobile = 0x001,
    TurningDisabled = 0x002,
    Invincible = 0x004,
    StayAlive = 0x008,
    NoDeaggro = 0x010,
    Untargetable = 0x020,
    AutoAttackDisabled = 0x040,
    Invisible = 0x080,
    NoRoam = 0x100,

    Intermission = 0x77// for transition phases to ensure boss only moves/acts when scripted
  };

  const std::array< uint32_t, 50 > BnpcBaseHp =
          {
                  44, 51, 59, 68, 91,
                  108, 126, 143, 160, 192,
                  217, 243, 268, 293, 319,
                  344, 369, 394, 420, 413,
                  458, 493, 532, 568, 594,
                  641, 677, 714, 750, 780,
                  887, 965, 1055, 1142, 1220,
                  1306, 1409, 1515, 1587, 1601,
                  1703, 1789, 1872, 2008, 2112,
                  2180, 2314, 2383, 2501, 2589 };

  /*!
  \class BNpc
  \brief Base class for all BNpcs

  */
  class BNpc : public Npc
  {

  public:
    BNpc();

    BNpc( uint32_t id, std::shared_ptr< Common::BNpcCacheEntry > pInfo, const Territory& zone );
    BNpc( uint32_t id, std::shared_ptr< Common::BNpcCacheEntry > pInfo, const Territory& zone, uint32_t hp, Common::BNpcType type );

    virtual ~BNpc() override;

    void init();

    void spawn( PlayerPtr pTarget ) override;
    void despawn( PlayerPtr pTarget ) override;

    uint16_t getModelChara() const;
    uint8_t getLevel() const override;

    uint32_t getBNpcBaseId() const;
    uint32_t getBNpcNameId() const;

    uint8_t getEnemyType() const;

    uint64_t getWeaponMain() const;
    uint64_t getWeaponSub() const;

    const BNpcBaseData& getSenseData() const;

    uint8_t getAggressionMode() const;

    uint32_t getTriggerOwnerId() const;
    void setTriggerOwnerId( uint32_t triggerOwnerId );

    float getNaviTargetReachedDistance() const;
    uint64_t getLastNaviMoveRequest() const;
    bool getNaviIsPathing() const;
    void setNaviIsPathing( bool pathing );
    Common::Vector3 getNaviLastMoveTarget() const;
    Common::Vector3 getNaviMoveTarget() const;

    // return true if it reached the position
    bool moveTo( const Common::Vector3& pos );

    bool moveTo( const Entity::Chara& targetChara );

    void sendPositionUpdate( uint64_t tickCount );

    BNpcState getState() const;
    void setState( BNpcState state );

    float getCurrentSpeed() const;

    const HateList& getHateList() const;
    void hateListClear();
    uint32_t hateListGetValue( const Sapphire::Entity::CharaPtr& pChara );
    uint32_t hateListGetHighestValue();
    CharaPtr hateListGetHighest();
    void hateListAdd( const CharaPtr& pChara, int32_t hateAmount );
    void hateListAddDelayed( const CharaPtr& pChara, int32_t hateAmount );
    void hateListUpdate( const CharaPtr& pChara, int32_t hateAmount );
    void hateListRemove( const CharaPtr& pChara );
    bool hateListHasActor( const CharaPtr& pChara );
    std::vector< CharaPtr > getHateList() override;
    void hateListUpdatePlayers();

    void aggro( const CharaPtr& pChara );
    void deaggro( const CharaPtr& pChara );
    void notifyPlayerDeaggro( const CharaPtr& pChara );

    void update( uint64_t tickCount ) override;
    void onTick() override;

    void onActionHostile( CharaPtr pSource, int32_t aggro ) override;

    void onDeath() override;

    void autoAttack( CharaPtr pTarget ) override;

    uint32_t getTimeOfDeath() const;
    void setTimeOfDeath( uint32_t timeOfDeath );

    void setPos( const Common::Vector3& pos, bool broadcastUpdate = true ) override;
    void setPos( float x, float y, float z, bool broadcastUpdate = true ) override;

    void restHp();

    void checkAggro();

    void setOwner( const CharaPtr& m_pChara );

    void setLevelId( uint32_t levelId );
    uint32_t getLevelId() const;
    uint32_t getBoundInstanceId() const;

    uint32_t getFlags() const;
    bool hasFlag( uint32_t flag ) const;
    void setFlag( uint32_t flags );

    // resets all flags to the given flags
    void resetFlags( uint32_t flags );
    void removeFlag( uint32_t flag );
    void clearFlags();

    void calculateStats() override;

    uint32_t getRank() const;

    Common::BNpcType getBNpcType() const;

    uint32_t getLayoutId() const;

    void processGambits( uint64_t tickCount );

    uint32_t getLastRoamTargetReachedTime() const;
    void setLastRoamTargetReachedTime( uint32_t time );

    std::shared_ptr< Common::BNPCData > getInstanceObjectInfo() const;

    void setRoamTargetReached( bool reached );
    bool isRoamTargetReached() const;

    void setRoamTargetPos( const Common::Vector3& targetPos );

    void updateAggroTarget();

    const Common::Vector3& getRoamTargetPos() const;
    const Common::Vector3& getSpawnPos() const;
    float getSpawnRot() const;

    void initFsm();

    bool getCanSwapTarget();
    void setCanSwapTarget( bool value );

  private:
    uint32_t m_bNpcBaseId;
    uint32_t m_bNpcNameId;
    uint64_t m_weaponMain;
    uint64_t m_weaponSub;
    uint8_t m_aggressionMode;
    uint8_t m_enemyType;
    uint8_t m_onlineStatus;
    uint8_t m_pose;
    uint16_t m_modelChara;
    uint32_t m_displayFlags;
    uint8_t m_level;
    uint32_t m_levelId;
    uint32_t m_rank;
    uint32_t m_boundInstanceId;
    uint32_t m_layoutId;
    uint32_t m_triggerOwnerId;

    uint32_t m_flags;


    BNpcBaseData m_senseData;

    Common::BNpcType m_bnpcType;

    float m_naviTargetReachedDistance;
    uint64_t m_naviLastMoveRequest{ 0 };
    bool m_naviIsPathing{ false };
    Common::Vector3 m_naviLastTarget;

    std::shared_ptr< Common::BNPCData > m_pInfo;

    uint32_t m_timeOfDeath;
    uint32_t m_lastRoamTargetReachedTime;
    bool m_roamTargetReached{ false };

    Common::Vector3 m_spawnPos;
    float m_spawnRot;
    Common::Vector3 m_roamPos;
    Common::Vector3 m_lastPos;
    float m_lastRot;
    uint64_t m_lastPosUpdate{0};

    BNpcState m_state;
    HateList m_hateList;
    bool m_canSwapTarget{ true };

    uint64_t m_naviLastUpdate;
    std::vector< Common::Vector3 > m_naviLastPath;
    uint8_t m_naviPathStep;
    Common::Vector3 m_naviTarget;

    CharaPtr m_pOwner;
    World::AI::GambitPackPtr m_pGambitPack;

    std::shared_ptr< World::AI::Fsm::StateMachine > m_fsm;
  };

}// namespace Sapphire::Entity
