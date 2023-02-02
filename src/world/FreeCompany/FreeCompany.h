#pragma once

#include <Common.h>
#include <set>
#include <string>

namespace Sapphire
{

  class FreeCompany
  {
  private:
    /*! unique ID of the fc */
    uint64_t m_id;
    /*! ID of the master character */
    uint64_t m_masterCharacterId;
    std::string m_masterCharacterName;
    /*! Name of the fc */
    std::string m_name;
    /*! Tag of the fc */
    std::string m_tag;
    /*! Fc Credit info */
    uint64_t m_credit;
    uint64_t m_creditAccumulated;
    /*! Rank of the fc */
    uint8_t m_rank;
    /*! Points of the fc */
    uint64_t m_points;
    /*! Crest of the fc */
    uint64_t m_crest;
    /*! Creation timestamp of the fc */
    uint32_t m_createDate;
    /*! Current grand company of the fc */
    uint8_t m_gc;
    /*! Grand company reputation array */
    uint64_t m_gcReputation[ 3 ];
    /*! Status of the Company, Common::FreeCompanyStatus */
    Common::FreeCompanyStatus m_status;
    /*! Fc board text */
    std::string m_fcBoard;
    /*! Fc Motto text */
    std::string m_fcMotto;
    /*! Fc Version, unsure what this is used for */
    uint32_t m_fcVersion;
    /*! List of active actions */
    uint64_t m_activeActionId[ 3 ];
    /*! List of remaining action times */
    uint64_t m_activeActionTimeLeft[ 3 ];
    /*! List of actions in stock */
    uint64_t m_actionStock[ 15 ];

    /*! ID list of all members */
    std::set< uint64_t > m_memberIds;
    /*! list of IDs of pending character invites */
    std::set< uint64_t > m_inviteIds;
    /*! chat channel ID associated with fc */
    uint64_t m_chatChannelId;

  public:
    FreeCompany( uint64_t id,
                 std::string name,
                 std::string tag,
                 uint64_t masterId,
                 uint64_t chatChannelId,
                 std::set< uint64_t > members,
                 std::set< uint64_t > invites );

    uint64_t getId() const;

    const std::string& getName() const;
    void setName( std::string name );

    const std::string& getTag() const;
    void setTag( std::string tag );

    uint64_t getMasterId() const;
    void setMasterId( uint64_t masterId );

    uint64_t getCredit() const;
    void setCredit( uint64_t credit );

    uint64_t getCreditAccumulated() const;
    void setCreditAccumulated( uint64_t credit );

    uint8_t getRank() const;
    void setRank( uint8_t );

    uint64_t getPoints() const;
    void setPoints( uint64_t points );

    uint64_t getCrest() const;
    void setCrest( uint64_t crest );

    uint32_t getCreateDate() const;
    void setCreateDate( uint32_t createDate );

    uint8_t getGrandCompany() const;
    void setGrandCompany( uint8_t gcIndex );

    uint64_t getGcReputation( uint8_t gcIndex ) const;
    void setGcReputation( uint8_t gcIndex, uint64_t reputation );

    Common::FreeCompanyStatus getFcStatus() const;
    void setFcStatus( Common::FreeCompanyStatus status );

    const std::string& getFcBoard() const;
    void setFcBoard( const std::string& board );

    const std::string& getFcMotto() const;
    void setFcMotto( const std::string& motto );

    uint32_t getFcVersion() const;
    void setFcVersion( uint32_t version );

    const uint64_t* getActiveActionIdArr() const;
    const uint64_t* getActiveActionTimeLeftArr() const;
    const uint64_t* getActionStockArr() const;

    const std::set< uint64_t >& getMemberIdList() const;
    std::set< uint64_t >& getMemberIdList();

    const std::set< uint64_t >& getInviteIdList() const;
    std::set< uint64_t >& getInviteIdList();

    uint64_t getChatChannel() const;

    void addMember( uint64_t memberId );

    void removeMember( uint64_t memberId );

    void addInvite( uint64_t memberId );

    void removeInvite( uint64_t memberId );

  };

}