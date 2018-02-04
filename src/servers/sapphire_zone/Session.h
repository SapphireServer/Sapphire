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

      int64_t getLastDataTime() const;
      int64_t getLastSqlTime() const;

      void updateLastDataTime();
      void updateLastSqlTime();

      void startReplay( const std::string& folderpath );
      void stopReplay();
      void processReplay();
      void sendReplayInfo();

      void close();

      uint32_t getId() const;

      bool loadPlayer();

      void update();

      bool isValid() const;

      Entity::PlayerPtr getPlayer() const;

   private:
      uint32_t m_sessionId;

      Entity::PlayerPtr m_pPlayer;

      int64_t m_lastDataTime;

      int64_t m_lastSqlTime;
      bool m_isValid;

      bool m_isReplaying;
      std::vector< std::tuple< uint64_t, std::string > > m_replayCache;

      Network::GameConnectionPtr m_pZoneConnection;
      Network::GameConnectionPtr m_pChatConnection;

   };

}

#endif

