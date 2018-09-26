#ifndef _BNPC_H_
#define _BNPC_H_

#include <Common.h>
#include <boost/enable_shared_from_this.hpp>

#include "Forwards.h"
#include "Chara.h"
#include "Npc.h"
#include <set>
#include <map>
#include <queue>

namespace Core {
namespace Entity {

/*!
\class BNpc
\brief Base class for all BNpcs

*/
class BNpc : public Npc
{

public:
  BNpc();
  BNpc( BNpcTemplatePtr pTemplate, float posX, float posY, float posZ, uint8_t level  );

  virtual ~BNpc() override;

  void spawn( PlayerPtr pTarget ) override;

  uint16_t getModelChara() const;
  uint8_t getLevel() const override;

  uint32_t getBNpcBaseId() const;
  uint32_t getBNpcNameId() const;

  uint8_t getEnemyType() const;

  uint64_t getWeaponMain() const;
  uint64_t getWeaponSub() const;

  uint8_t getAggressionMode() const;

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

};

}
}
#endif
