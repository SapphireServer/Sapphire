#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Common.h>
#include <memory>

#include "ForwardsZone.h"
#include <set>
#include <map>
#include <queue>

namespace Sapphire::Entity
{

  /*!
  \class GameObject
  \brief Base class for all actor/objects

  */
  class Actor : public std::enable_shared_from_this< Actor >
  {

  protected:
    /*! Position of the object */
    Common::FFXIVARR_POSITION3 m_pos;
    /*! Rotation of the object */
    float m_rot;
    /*! Id of the actor */
    uint32_t m_id;
    /*! Type of the actor */
    Common::ObjKind m_objKind;
    /*! Id of the zone the actor currently is in */
    uint32_t m_territoryTypeId;
    /*! Ptr to the ZoneObj the actor belongs to */
    TerritoryPtr m_pCurrentTerritory;

    /*! list of various actors in range */
    std::set< ActorPtr > m_inRangeActor;
    std::set< PlayerPtr > m_inRangePlayers;
    std::set< BNpcPtr > m_inRangeBNpc;

    /*! Parent cell in the zone */
    Sapphire::Cell* m_pCell;

  public:
    explicit Actor( Common::ObjKind type );

    virtual ~Actor() {};

    virtual void spawn( PlayerPtr pTarget ) {}

    virtual void despawn( PlayerPtr pTarget ) {}

    uint32_t getId() const;

    void setId( uint32_t id );

    Common::ObjKind getObjKind() const;

    Common::FFXIVARR_POSITION3& getPos();
    const Common::FFXIVARR_POSITION3& getPos() const;

    void setPos( const Common::FFXIVARR_POSITION3& pos, bool broadcastUpdate = true );

    void setPos( float x, float y, float z, bool broadcastUpdate = true );

    float getRot() const;

    void setRot( float rot );

    bool isChara() const;

    bool isPlayer() const;

    bool isEventNpc() const;

    bool isBattleNpc() const;

    bool isRetainer() const;

    bool isCompanion() const;

    bool isEventObj() const;

    bool isHousingEventObj() const;

    bool isAetheryte() const;

    ///// IN RANGE LOGIC ///////////////////////////////
    virtual void onRemoveInRangeActor( Actor& pActor ) {}

    // check if another actor is in the actors in range set
    bool isInRangeSet( ActorPtr pActor ) const;

    CharaPtr getClosestChara();

    void sendToInRangeSet( Network::Packets::FFXIVPacketBasePtr pPacket, bool bToSelf = false );

    // add an actor to in range set
    void addInRangeActor( ActorPtr pActor );

    // remove an actor from the in range set
    void removeInRangeActor( Actor& actor );

    // return true if there is at least one actor in the in range set
    bool hasInRangeActor() const;

    void removeFromInRange();

    // clear the whole in range set, this does no cleanup
    virtual void clearInRangeSet();

    std::set< ActorPtr > getInRangeActors( bool includeSelf = false );

    ////////////////////////////////////////////////////

    CharaPtr getAsChara();

    PlayerPtr getAsPlayer();

    EventObjectPtr getAsEventObj();

    BNpcPtr getAsBNpc();

    TerritoryPtr getCurrentTerritory() const;

    void setCurrentZone( TerritoryPtr currZone );

    InstanceContentPtr getCurrentInstance() const;

    QuestBattlePtr getCurrentQuestBattle() const;

    PublicContentPtr getCurrentPublicContent() const;

    // get the current cell of a region the actor is in
    Cell* getCellPtr();

    // set the current cell
    void setCell( Cell* pCell );

  };

}
#endif
