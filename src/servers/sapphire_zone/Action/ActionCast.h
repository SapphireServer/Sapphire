#ifndef _ACTIONCAST_H_
#define _ACTIONCAST_H_

#include "../Forwards.h"
#include "Action.h"

namespace Core {
namespace Action {

   class ActionCast : public Action
   {
   private:
      uint32_t m_idOverride;

      uint32_t getOverrideId() const;

   public:
      ActionCast();
      ~ActionCast() = default;
      
      ActionCast( Entity::CharaPtr pActor, Entity::CharaPtr pTarget, uint32_t actionId );

      void setIdOverride( uint32_t param );
      uint32_t getIdOverride() const;

      void onStart() override;
      void onFinish() override;
      void onInterrupt() override;

   };

}
}

#endif
