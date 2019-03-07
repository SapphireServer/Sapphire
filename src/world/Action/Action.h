#ifndef _ACTION_H_
#define _ACTION_H_

#include <Common.h>
#include "ForwardsZone.h"
#include <array>

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
    Action( Entity::CharaPtr caster, uint32_t actionId, Data::ActionPtr actionData, FrameworkPtr fw );

    virtual ~Action();

    uint32_t getId() const;

    void setPos( Common::FFXIVARR_POSITION3 pos );
    Common::FFXIVARR_POSITION3 getPos() const;

    void setTargetChara( Entity::CharaPtr chara );
    void setResidentTargetId( uint64_t targetId );
    Entity::CharaPtr getTargetChara() const;
    Entity::CharaPtr getSourceChara() const;

    bool isInterrupted() const;
    void setInterrupted( Common::ActionInterruptType type );

    uint32_t getCastTime() const;
    void setCastTime( uint32_t castTime );

    /*!
     * @brief Checks if the action *may* target a resident instead of an actor
     * @return true if the target *may* be a resident and not an actor, otherwise false.
     */
    bool hasResidentTarget() const;

    /*!
     * @brief Tests whether the action is instantly usable or has a cast assoc'd with it
     * @return true if action has a cast time
     */
    bool hasCastTime() const;

    /*!
     * @brief Tests if an action is castable by the current source chara
     * @return true if castable, false if the caster doesn't meet the requirements
     */
    bool precheck();

    /*!
     * @brief Starts the cast. Finishes it immediately if there is no cast time (weaponskills).
     */
    virtual void onStart();

    /*!
     * @brief Finishes the cast, effected targets are calculated here.
     */
    virtual void onExecute();

    /*!
     * @brief Called when a cast is interrupted for any reason
     *
     * m_interruptType will have the reason why the action was interrupted (eg. damage, movement, ...)
     */
    virtual void onInterrupt();

    // update action, if returns true, action is done and has to be removed from the actor
    virtual bool update();

  protected:

    void calculateActionCost();
    void calculateMPCost( uint16_t baseCost );

    bool playerPrecheck( Entity::Player& player );

    uint32_t m_id;

    Common::ActionPrimaryCostType m_primaryCostType;
    uint16_t m_primaryCost;

    uint64_t m_startTime;
    uint32_t m_castTime;
    uint16_t m_recastTime;
    uint8_t m_cooldownGroup;
    int8_t m_range;
    uint8_t m_effectRange;
    Common::ActionAspect m_aspect;


    Entity::CharaPtr m_pSource;
    Entity::CharaPtr m_pTarget;
    uint64_t m_targetId;
    bool m_hasResidentTarget;

    Common::ActionInterruptType m_interruptType;

    FrameworkPtr m_pFw;
    Data::ActionPtr m_actionData;

    Common::FFXIVARR_POSITION3 m_pos;
  };
}

#endif
