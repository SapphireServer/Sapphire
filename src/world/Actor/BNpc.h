#pragma once

#include <Common.h>

#include "Forwards.h"
#include "Chara.h"
#include "Npc.h"
#include <set>
#include <map>
#include <queue>

namespace Sapphire::Entity
{

  struct HateListEntry
  {
    uint32_t m_hateAmount;
    CharaPtr m_pChara;
  };

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
    None = 0,
    Immobile = 1,
    TurningDisabled = 2,
    Invincible = 4,
    InvincibleRefill = 8,
    NoDeaggro = 16,
    Untargetable = 32,
  };

  const std::array< uint32_t, 50 > BnpcBaseHp =
          { 44,51, 59, 68, 91,
            108, 126, 143, 160, 192,
            217, 243, 268, 293, 319,
            344, 369, 394, 420, 413,
            458, 493, 532, 568, 594,
            641, 677,714, 750, 780,
            887, 965, 1055, 1142, 1220,
            1306, 1409, 1515, 1587, 1601,
            1703, 1789, 1872, 2008, 2112,
            2180, 2314, 2383, 2501, 2589
          };

  /*!
  \class BNpc
  \brief Base class for all BNpcs

  */
  class BNpc : public Npc
  {

  public:
    BNpc();

    BNpc( uint32_t id, std::shared_ptr< Common::BNPCInstanceObject > pInfo, TerritoryPtr pZone );
    BNpc( uint32_t id, std::shared_ptr< Common::BNPCInstanceObject > pInfo, TerritoryPtr pZone, uint32_t hp, Common::BNpcType type );

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

    uint8_t getAggressionMode() const;


    float getNaviTargetReachedDistance() const;

    // return true if it reached the position
    bool moveTo( const Common::FFXIVARR_POSITION3& pos );

    bool moveTo( const Entity::Chara& targetChara );

    void sendPositionUpdate();

    BNpcState getState() const;
    void setState( BNpcState state );

    void hateListClear();
    CharaPtr hateListGetHighest();
    void hateListAdd( CharaPtr pChara, int32_t hateAmount );
    void hateListUpdate( CharaPtr pChara, int32_t hateAmount );
    void hateListRemove( CharaPtr pChara );
    bool hateListHasActor( CharaPtr pChara );

    void aggro( CharaPtr pChara );
    void deaggro( CharaPtr pChara );

    void update( uint64_t tickCount ) override;
    void onTick() override;

    void onActionHostile( CharaPtr pSource ) override;

    void onDeath() override;

    void autoAttack( CharaPtr pTarget ) override;

    uint32_t getTimeOfDeath() const;
    void setTimeOfDeath( uint32_t timeOfDeath );

    void regainHp();

    void checkAggro();

    void setOwner( CharaPtr m_pChara );

    void setLevelId( uint32_t levelId );
    uint32_t getLevelId() const;
    uint32_t getBoundInstanceId() const;

    bool hasFlag( uint32_t flag ) const;
    void setFlag( uint32_t flags );

    void calculateStats() override;

    uint32_t getRank() const;

    Common::BNpcType getBNpcType() const;

    uint32_t getLayoutId() const;

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

    uint32_t m_flags;

    Common::BNpcType m_bnpcType;

    float m_naviTargetReachedDistance;

    std::shared_ptr< Common::BNPCInstanceObject > m_pInfo;

    uint32_t m_timeOfDeath;
    uint32_t m_lastRoamTargetReached;

    Common::FFXIVARR_POSITION3 m_spawnPos;
    Common::FFXIVARR_POSITION3 m_roamPos;

    BNpcState m_state;
    std::set< std::shared_ptr< HateListEntry > > m_hateList;

    uint64_t m_naviLastUpdate;
    std::vector< Common::FFXIVARR_POSITION3 > m_naviLastPath;
    uint8_t m_naviPathStep;
    Common::FFXIVARR_POSITION3 m_naviTarget;

    CharaPtr m_pOwner;

  };

}