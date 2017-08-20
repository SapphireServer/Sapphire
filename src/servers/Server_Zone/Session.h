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

      void updateLastDataTime();

      void close();

      uint32_t getId() const;

      bool loadPlayer();

      void update();

      Entity::PlayerPtr getPlayer() const;

   private:
      uint32_t m_sessionId;

      Entity::PlayerPtr m_pPlayer;

      uint32_t m_lastDataTime;

      Network::GameConnectionPtr m_pZoneConnection;
      Network::GameConnectionPtr m_pChatConnection;

   };

}

#endif

