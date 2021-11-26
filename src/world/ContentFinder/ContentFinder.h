#pragma once

#include <nlohmann/json.hpp>
#include "../ForwardsZone.h"

namespace Sapphire::World
{

  enum UpdateFindContentKind : uint8_t
  {
    CompleteRegistration = 0, // value1 is used to call setResultFindSuccess if bit1 or bit2 is set, value2 is passed to setFindInfo
    SetResultFailed = 1, // uses value1 as flag list to determine param for setResultFailed
    SetResultFailed1 = 2, // same as 1 but also calls SetResultFailedFindContentAsMember with value1
    SetResultFailed2 = 3, // uses value1 of update packet to setCancelled or setFailed with different params
    SetResultMatched = 4,
    SetResultEclusiveTerritory = 5,
    SetResultReadyToEnter = 6,
    SetResultFailed3 = 7, // param = 1
    ReturnMatching = 8,
    SetResultFailed4 = 9, // param = 4
    SetResultFailed5 = 10, // param = 5
    SetResultFailedAccept = 11,
    LeaveContent = 12
  };

  enum QueuedContentState : uint8_t
  {
    None = 0,
    MatchingInProgress = 1,
    MatchingComplete = 2,
    WaitingForAccept = 3,
    Accepted = 4,
    InProgress = 5,
    InProgressRefill = 6,
    ToBeRemoved = 7
  };

  class QueuedPlayer
  {
    friend class ContentFinder;
  public:
    explicit QueuedPlayer( const Entity::Player& player, uint8_t registerId );
    ~QueuedPlayer() = default;

    Sapphire::Common::Role getRole() const;

    void setActiveRegisterId( uint8_t registerId );
    uint8_t getActiveRegisterId() const;

    uint64_t getCharacterId() const;
    uint32_t getEntityId() const;

  private:
    uint64_t m_characterId;
    uint32_t m_entityId;
    uint32_t m_classJob;
    Common::Role m_role;
    uint8_t m_level;
    bool m_allowInProgress;
    uint8_t m_activeRegisterId;
  };

  class QueuedContent
  {
    friend class ContentFinder;
  public:
    QueuedContent( uint32_t registerId, uint32_t contentId );
    ~QueuedContent() = default;
    uint32_t getRegisterId() const;
    uint32_t getContentId() const;
    uint8_t getRoleCount( Sapphire::Common::Role role ) const;
    void queuePlayer( const std::shared_ptr< QueuedPlayer >& pQPlayer );
    bool withdrawPlayer( const std::shared_ptr< QueuedPlayer >& pQPlayer );

    QueuedContentState getState() const;
    void setState( QueuedContentState state );

  private:
    uint32_t m_registerId;
    uint32_t m_contentId;

    uint32_t m_contentPopTime;

    uint8_t m_partyMemberCount{};
    uint8_t m_partyCount{};
    uint8_t m_tankCount{};
    uint8_t m_healerCount{};
    uint8_t m_attackerCount{};
    uint8_t m_rangeCount{};

    QueuedContentState m_state;

    bool m_isInProgress{ false };

    std::vector< std::shared_ptr < QueuedPlayer > > m_players;
  };

  class ContentFinder
  {
    friend class QueuedContent;
    friend class QueuedPlayer;
  public:
    using QueuedContentPtr = std::shared_ptr< QueuedContent >;
    using QueuedContentPtrList = std::vector< QueuedContentPtr >;

    ContentFinder() = default;
    ~ContentFinder() = default;

    void update();

    void registerContentRequest( Entity::Player& player, uint32_t contentId );
    void registerContentsRequest( Entity::Player& player, const std::vector< uint32_t >& contentIds );
    void registerRandomContentRequest( Entity::Player& player, uint32_t randomContentTypeId );

    QueuedContentPtrList getMatchingContentList( Sapphire::Entity::Player &player, uint32_t contentId );

    void withdraw( Entity::Player& player );

    uint32_t getNextRegisterId();

    std::shared_ptr< QueuedContent > findContentByRegisterId( uint32_t registerId );
    bool removeContentByRegisterId( uint32_t registerId );

  private:
    uint32_t m_nextRegisterId{ 0 };
    std::unordered_map< uint32_t, std::shared_ptr< QueuedContent > > m_queuedContent;
    std::unordered_map< uint32_t, std::shared_ptr< QueuedPlayer > > m_queuedPlayer;

    void queueForContent( Entity::Player &player, const std::vector< uint32_t >& contentIds );

    void completeRegistration( const Entity::Player &player );
  };



}
