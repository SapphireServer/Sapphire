#ifndef _ACTION_H_
#define _ACTION_H_

#include <Common.h>
#include "ForwardsZone.h"

namespace Sapphire::Data
{
  struct Action;
  using ActionPtr = std::shared_ptr< Action >;
}

namespace Sapphire::Action
{

  class Action
  {

  public:
    Action();
    Action( Entity::CharaPtr caster, uint32_t actionId, Data::ActionPtr action, FrameworkPtr fw );

    virtual ~Action();

    uint32_t getId() const;

    Common::HandleActionType getType() const;
    void setType( Common::HandleActionType type );

    void setTargetChara( Entity::CharaPtr chara );
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
    uint32_t m_id;

    Common::HandleActionType m_type;

    uint64_t m_startTime;
    uint32_t m_castTime;

    Entity::CharaPtr m_pSource;
    Entity::CharaPtr m_pTarget;
    uint64_t m_targetId;

    bool m_bInterrupt;

    FrameworkPtr m_pFw;

  };
}

#endif
