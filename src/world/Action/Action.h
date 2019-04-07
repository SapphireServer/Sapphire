#ifndef _ACTION_H_
#define _ACTION_H_

#include <Common.h>
#include "Util/ActorFilter.h"
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
    Action( Entity::CharaPtr caster, uint32_t actionId, FrameworkPtr fw );
    Action( Entity::CharaPtr caster, uint32_t actionId, Data::ActionPtr actionData, FrameworkPtr fw );

    virtual ~Action();

    uint32_t getId() const;

    bool init();

    void setPos( Common::FFXIVARR_POSITION3 pos );
    Common::FFXIVARR_POSITION3 getPos() const;

    void setTargetId( uint64_t targetId );
    uint64_t getTargetId() const;
    Entity::CharaPtr getSourceChara() const;

    bool isInterrupted() const;
    void setInterrupted( Common::ActionInterruptType type );

    uint32_t getCastTime() const;
    void setCastTime( uint32_t castTime );

    uint32_t getAdditionalData() const;
    void setAdditionalData( uint32_t data );

    bool isComboAction() const;

    /*!
     * @brief Checks if a chara has enough resources available to cast the action (tp/mp/etc)
     * @return true if they have the required resources
     */
    bool hasResources();

    /*!
     * @brief Checks if a chara has enough resources available to cast the action and then consumes them (tp/mp/etc)
     * @return true if they have the required resources
     */
    bool consumeResources();

    /*!
     * @brief Checks if the action *may* target a resident instead of an actor
     * @return true if the target *may* be a resident and not an actor, otherwise false.
     */
    bool hasClientsideTarget() const;

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
     * @brief Snapshots characters affected by a cast.
     * @param filters A vector of filters to be applied to the in range set of the caster
     * @param actors Actors that match the filters are copied here
     * @return true if actors are hit
     */
    bool snapshotAffectedActors( std::vector< Entity::CharaPtr >& actors );

    /*!
     * @brief Adds an actor filter to this action.
     * @param filter The ptr to the ActorFilter to add
     */
    void addActorFilter( World::Util::ActorFilterPtr filter );

    /*!
     * @brief Adds the default actor filters based on the CastType entry in the Action exd.
     */
    void addDefaultActorFilters();


    std::vector< Entity::CharaPtr >& getHitCharas();

    /*!
     * @brief Returns the first hit actor inside the m_hitActors vector.
     * @return The CharaPtr otherwise nullptr
     */
    Entity::CharaPtr getHitChara();

    /*!
     * @brief Starts the cast. Finishes it immediately if there is no cast time (weaponskills).
     */
    virtual void start();

    /*!
     * @brief Finishes the cast, effected targets are calculated here.
     */
    virtual void execute();

    /*!
     * @brief Called when a cast is interrupted for any reason
     *
     * m_interruptType will have the reason why the action was interrupted (eg. damage, movement, ...)
     */
    virtual void interrupt();

    /*!
     * @brief Called on each player update tick
     * @return true if a cast has finished and should be removed from the owning chara
     */
    virtual bool update();

  protected:

    void calculateActionCost();

    bool primaryCostCheck( bool subtractCosts );
    bool secondaryCostCheck( bool subtractCosts );

    bool playerPrecheck( Entity::Player& player );

    bool preFilterActor( Entity::Actor& actor ) const;

    uint32_t m_id;

    Common::ActionPrimaryCostType m_primaryCostType;
    uint16_t m_primaryCost;

    uint64_t m_startTime;
    uint32_t m_castTimeMs;
    uint32_t m_recastTimeMs;
    uint8_t m_cooldownGroup;
    int8_t m_range;
    uint8_t m_effectRange;
    uint8_t m_xAxisModifier;
    Common::ActionAspect m_aspect;
    Common::CastType m_castType;

    uint32_t m_additionalData;

    Entity::CharaPtr m_pSource;
    Entity::CharaPtr m_pTarget;
    uint64_t m_targetId;

    bool m_canTargetSelf;
    bool m_canTargetParty;
    bool m_canTargetFriendly;
    bool m_canTargetHostile;
    bool m_canTargetDead;

    Common::ActionInterruptType m_interruptType;

    FrameworkPtr m_pFw;
    Data::ActionPtr m_actionData;

    Common::FFXIVARR_POSITION3 m_pos;

    std::vector< World::Util::ActorFilterPtr > m_actorFilters;
    std::vector< Entity::CharaPtr > m_hitActors;
  };
}

#endif
