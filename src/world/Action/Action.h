#pragma once

#include <Common.h>
#include "ActionLut.h"
#include "Util/ActorFilter.h"
#include "ForwardsZone.h"
#include "EffectBuilder.h"
#include "Exd/Structs.h"

namespace Sapphire::World::Action
{

  class Action
  {

  public:

    Action() = default;
    Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t requestId );
    Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t requestId, std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData );

    virtual ~Action() = default;

    uint32_t getId() const;

    bool init();

    void setPos( const Common::FFXIVARR_POSITION3& pos );
    const Common::FFXIVARR_POSITION3& getPos() const;

    void setTargetId( uint64_t targetId );
    uint64_t getTargetId() const;
    Entity::CharaPtr getSourceChara() const;

    bool isInterrupted() const;
    Common::ActionInterruptType getInterruptType() const;
    void setInterrupted( Common::ActionInterruptType type );

    uint32_t getCastTime() const;
    void setCastTime( uint32_t castTime );

    uint32_t getAdditionalData() const;
    void setAdditionalData( uint32_t data );

    bool isCorrectCombo() const;

    bool isComboAction() const;

    uint8_t getActionKind() const;
    void setActionKind( uint8_t actionKind );

    void setAggroMultiplier( float aggroMultiplier );

    uint64_t getCastTimeRest() const;

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
     * @brief Tests whether the action is an ability/oGCD
     * @return true if action is an ability
     */
    bool isAbility() const;

    /*!
     * @brief Tests whether the action is a weaponskill
     * @return true if action is an weaponskill
     */
    bool isWeaponskill() const;

    /*!
     * @brief Tests if an action is castable by the current source chara
     * @return true if castable, false if the caster doesn't meet the requirements
     */
    virtual bool preCheck();

    /*!
     * @brief Snapshots characters affected by a cast.
     * @param filters A vector of filters to be applied to the in range set of the caster
     * @param actors Actors that match the filters are copied here
     * @return true if actors are hit
     */
    bool snapshotAffectedActors( std::vector< Entity::CharaPtr >& actors );

    EffectBuilderPtr getEffectbuilder();

    void handleAction();

    void handleStatusEffects();

    /*!
     * @brief Adds an actor filter to this action.
     * @param filter The ptr to the ActorFilter to add
     */
    void addActorFilter( World::Util::ActorFilterPtr filter );

    /*!
     * @brief Adds the default actor filters based on the CastType entry in the Action exd.
     */
    void addDefaultActorFilters();

    std::pair< uint32_t, Common::ActionHitSeverityType > calcDamage( uint32_t potency );

    std::pair< uint32_t, Common::ActionHitSeverityType > calcHealing( uint32_t potency );


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

    virtual void onInterrupt();
    virtual void onStart();

  protected:

    bool primaryCostCheck( bool subtractCosts );
    bool secondaryCostCheck( bool subtractCosts );

    bool playerPreCheck( Entity::Player& player );

    bool preFilterActor( Entity::GameObject& actor ) const;

    bool hasValidLutEntry() const;

    uint32_t m_id{};
    uint8_t m_actionKind{};

    uint16_t m_requestId{};

    Common::ActionPrimaryCostType m_primaryCostType;
    uint16_t m_primaryCost{};

    float m_aggroMultiplier{ 1.f };

    uint64_t m_startTime{};
    uint64_t m_castTimeRestMs{};
    uint32_t m_castTimeMs{};
    uint32_t m_recastTimeMs{};
    uint8_t m_cooldownGroup{};
    int8_t m_range{};
    uint8_t m_effectRange{};
    uint8_t m_xAxisModifier{};
    Common::ActionAspect m_aspect;
    Common::CastType m_castType;
    Common::ActionCategory m_category;

    uint32_t m_additionalData{};

    Entity::CharaPtr m_pSource;
    Entity::CharaPtr m_pTarget;
    uint64_t m_targetId{};

    bool m_canTargetSelf{};
    bool m_canTargetParty{};
    bool m_canTargetFriendly{};
    bool m_canTargetHostile{};
    bool m_canTargetDead{};

    Common::ActionInterruptType m_interruptType;

    std::shared_ptr< Excel::ExcelStruct< Excel::Action > > m_actionData;

    Common::FFXIVARR_POSITION3 m_pos{};

    EffectBuilderPtr m_effectBuilder;

    std::vector< World::Util::ActorFilterPtr > m_actorFilters;
    std::vector< Entity::CharaPtr > m_hitActors;

    ActionEntry m_lutEntry;
  };
}
