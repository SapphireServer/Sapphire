#ifndef _ACTION_H_
#define _ACTION_H_

#include <Common.h>
#include "ForwardsZone.h"

namespace Sapphire::Action
{

  class Action
  {

  public:
    Action();
    Action( Entity::CharaPtr caster, Entity::CharaPtr target, uint16_t actionId, FrameworkPtr fw );

    virtual ~Action();

    uint16_t getId() const;

    Entity::CharaPtr getTargetChara() const;
    Entity::CharaPtr getActionSource() const;

    bool isInterrupted() const;
    void setInterrupted();

    uint32_t getCastTime() const;
    void setCastTime( uint32_t castTime );

    /*!
     * @brief Tests whether the action is instantly usable or has a cast assoc'd with it
     * @return true if action has a cast time
     */
    bool isCastedAction() const;

    void start();

    virtual void onStart();
    virtual void onFinish();
    virtual void onInterrupt();

    // update action, if returns true, action is done and has to be removed from the actor
    virtual bool update();

  protected:
    uint16_t m_id;

    uint64_t m_startTime;
    uint32_t m_castTime;

    Entity::CharaPtr m_pSource;
    Entity::CharaPtr m_pTarget;

    bool m_bInterrupt;

    FrameworkPtr m_pFw;

  };
}

#endif
