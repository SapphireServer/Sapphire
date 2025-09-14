#ifndef _SESSION_H_
#define _SESSION_H_

#include <memory>

#include "ForwardsZone.h"

namespace Sapphire::World
{

  class Session : public std::enable_shared_from_this< Session >
  {
  public:
    Session( uint32_t entityId );

    ~Session() = default;

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

    void processOutQueue();

    void processChatQueues();

    void processInQueue();

    bool isValid() const;

    Entity::PlayerPtr getPlayer() const;

    /*! set timestamp for last received ping */
    void setLastPing( uint32_t lastPing );

    /*! get timestamp of last received ping */
    uint32_t getLastPing() const;

  private:
    uint32_t m_entityId;

    Entity::PlayerPtr m_pPlayer;

    uint32_t m_lastDataTime;

    uint32_t m_lastSqlTime;
    uint32_t m_lastPing;
    bool m_isValid;

    bool m_isReplaying;
    std::vector< std::tuple< uint64_t, std::string > > m_replayCache;

    Network::GameConnectionPtr m_pZoneConnection;
    Network::GameConnectionPtr m_pChatConnection;

  };

}

#endif

