#ifndef _ACTION_H_
#define _ACTION_H_

#include <Common.h>
#include <Forwards.h>

#include <vector>

namespace Core {
namespace Action {

   class Action 
   {

   public:
      virtual ~Action() = default;

      Action() = default;
      Action( Entity::CharaPtr caster, Entity::CharaPtr target, uint32_t actionId );

      uint32_t getId() const;

      Common::HandleActionType getHandleActionType() const;

      Entity::CharaPtr getTargetChara() const;

      /*!
       * @brief Has the action been interrupted
       * @return true if it has
       */
      bool isInterrupted() const;
      /*!
       * @brief Set an action as interrupted
       */
      void setInterrupted();

      uint64_t getStartTime() const;
      void setStartTime( uint64_t startTime );

      uint32_t getCastTime() const;
      void setCastTime( uint32_t castTime );

      bool hasCastTime() const;

      uint32_t getParam() const;
      void setParam( uint32_t param );

      Common::SkillType getSkillType() const;
      void setSkillType( uint8_t skillType );

      /*!
       * @brief Gets the action cooldown
       * @return the action cooldown in milliseconds
       */
      uint16_t getCooldown() const;

      /*!
       * @brief Sets the action cooldown
       * @param cooldown The action cooldown in milliseconds
       */
      void setCooldown( uint16_t cooldown );

      Entity::CharaPtr getActionSource() const;

      /*!
       * @brief Start casting an action immediately
       *
       * This just sets the start time to now and then calls the onStart virtual
       */
      void startAction();

      /*!
       * @brief Called when an action's cast has started
       *
       * Regardless of whether there is a cooldown or not, this will be called first
       *
       * This event is raised inside scripts from this virtual.
       */
      virtual void onStart();

      /*!
       * @brief Called when an action's cast has finished
       *
       * If an action has no cast time, this will be called immediately after onStart is called
       * Otherwise, it'll be called after the cast has finished successfully
       *
       * This event is raised inside scripts from this virtual.
       */
      virtual void onFinish();

      /*!
       * @brief Called when an action's cast has been interrupted by moving or some other means
       *
       * This event is raised inside scripts from this virtual.
       */
      virtual void onInterrupt();

      // update action, if returns true, action is done and has to be removed from the actor
      virtual bool update();

   protected:
      uint32_t	m_id;
      Common::HandleActionType m_handleActionType;
      Common::SkillType m_skillType;
      uint32_t m_param;

      uint64_t	m_startTime;
      uint32_t	m_castTime;

      Entity::CharaPtr m_pSource;
      Entity::CharaPtr m_pTarget;

      bool m_bInterrupt;

      uint16_t m_cooldown;
   };
}
}

#endif
