#ifndef _SESSION_H_
#define _SESSION_H_
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "Forwards.h"

namespace Core {

   class Session : public boost::enable_shared_from_this< Session >
   {
   public:
      Session( uint32_t sessionId );
      ~Session();

      void setZoneConnection( Network::GameConnectionPtr zoneCon );

      void setChatConnection( Network::GameConnectionPtr chatCon );

      Network::GameConnectionPtr getZoneConnection() const;
      Network::GameConnectionPtr getChatConnection() const;

      uint32_t getLastDataTime() const;
      uint32_t getLastSqlTime() const;

      void updateLastDataTime();
      void updateLastSqlTime();

      void close();

      uint32_t getId() const;

      bool loadPlayer();

      void update();

      bool isValid() const;

      Entity::PlayerPtr getPlayer() const;

   private:
      uint32_t m_sessionId;

      Entity::PlayerPtr m_pPlayer;

      uint32_t m_lastDataTime;

      uint32_t m_lastSqlTime;
      bool m_isValid;

      Network::GameConnectionPtr m_pZoneConnection;
      Network::GameConnectionPtr m_pChatConnection;

   };

}

#endif

