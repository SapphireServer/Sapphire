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
    struct ActionCostEntry
    {
      Common::ActionCostType m_costType;
      uint16_t m_cost;
    };

    using ActionCostArray = std::array< ActionCostEntry, 2 >;

    Action();
    Action( Entity::CharaPtr caster, uint32_t actionId, Data::ActionPtr action, FrameworkPtr fw );

    virtual ~Action();

    uint32_t getId() const;

    void setPos( Common::FFXIVARR_POSITION3 pos );
    Common::FFXIVARR_POSITION3 getPos() const;

    void setTargetChara( Entity::CharaPtr chara );
    void setResidentTargetId( uint64_t targetId );
    Entity::CharaPtr getTargetChara() const;
    Entity::CharaPtr getActionSource() const;

    bool isInterrupted() const;
    void setInterrupted( Common::ActionInterruptType type );

    uint32_t getCastTime() const;
    void setCastTime( uint32_t castTime );

    /*!
     * @brief Checks if the action *may* target a resident instead of an actor
     * This checks if m_pTarget is nullptr but m_targetId is set
     *
     * @return true if the target *may* be a resident and not an actor, otherwise false.
     */
    bool hasResidentTarget() const;

    const ActionCostArray& getCostArray() const;

    /*!
     * @brief Tests whether the action is instantly usable or has a cast assoc'd with it
     * @return true if action has a cast time
     */
    bool isCastedAction() const;

    /*!
     * @brief Starts the cast. Finishes it immediately if there is no cast time (weaponskills).
     */
    void start();

    void buildEffectPackets();

    /*!
     * @brief Damages a target and adds the effect entry
     * @param potency The amount of damage the target takes
     * @param chara The chara to inflict damage upon
     * @param aspect The aspect of the damage
     */
    void damageTarget( uint32_t potency, Entity::Chara& chara, Common::ActionAspect aspect = Common::ActionAspect::None );
    /*!
     * @brief Heals a target and adds the effect entry
     * @param potency Amount of healing to apply
     * @param chara Chara to receive healing
     */
    void healTarget( uint32_t potency, Entity::Chara& chara );

    virtual void onStart();
    virtual void onFinish();
    virtual void onInterrupt();

    // update action, if returns true, action is done and has to be removed from the actor
    virtual bool update();

  protected:

    void calculateActionCost();
    void calculateMPCost( uint8_t costArrayIndex );

    /*!
     * @brief Some actions are capable of both healing and dealing damage. This identifies them.
     */
    enum EffectPacketIdentity : uint8_t
    {
      DamageEffect,
      HealingEffect,

      MAX_ACTION_EFFECT_PACKET_IDENT
    };

    struct EffectPacketData
    {
      std::vector< Common::EffectEntry > m_entries;
      std::vector< uint32_t > m_hitActors;
    };

    uint32_t m_id;

    Common::ActionCostType m_costType;
    uint16_t m_cost;

    ActionCostArray m_actionCost;

    uint64_t m_startTime;
    uint32_t m_castTime;
    uint16_t m_recastTime;
    uint8_t m_cooldownGroup;

    Entity::CharaPtr m_pSource;
    Entity::CharaPtr m_pTarget;
    uint64_t m_targetId;
    bool m_hasResidentTarget;

    Common::ActionInterruptType m_interruptType;

    FrameworkPtr m_pFw;

    Common::FFXIVARR_POSITION3 m_pos;

    std::array< EffectPacketData, MAX_ACTION_EFFECT_PACKET_IDENT > m_effects;
  };
}

#endif
