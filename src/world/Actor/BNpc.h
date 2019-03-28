#ifndef _BNPC_H_
#define _BNPC_H_

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

  /*!
  \class BNpc
  \brief Base class for all BNpcs

  */
  class BNpc : public Npc
  {

  public:
    BNpc( FrameworkPtr pFw );
    BNpc( uint32_t id, BNpcTemplatePtr pTemplate, float posX, float posY, float posZ, float rot,
          uint8_t level, uint32_t maxHp, ZonePtr pZone,FrameworkPtr pFw );

    virtual ~BNpc() override;

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

    float getScale() const;
    float getNaviTargetReachedDistance() const;

    // return true if it reached the position
    bool moveTo( const Common::FFXIVARR_POSITION3& pos );

    // processes movement
    void step();

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

    void update( int64_t currTime ) override;
    void onTick() override;

    void onActionHostile( CharaPtr pSource ) override;

    void onDeath() override;

    uint32_t getTimeOfDeath() const;
    void setTimeOfDeath( uint32_t timeOfDeath );

    void regainHp();

    void checkAggro();

    void pushNearbyBNpcs();

    void setOwner( CharaPtr m_pChara );

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

    float m_scale;
    float m_naviTargetReachedDistance;

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
#endif
