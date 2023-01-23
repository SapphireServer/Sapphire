#pragma once

#include "ForwardsZone.h"

#include <Common.h>
#include <Util/SpawnIndexAllocator.h>
#include <spdlog/fmt/fmt.h>
#include <optional>

#include "Chara.h"
#include "Quest/Quest.h"
#include "Event/EventHandler.h"

#include <map>
#include <queue>
#include <array>

namespace Sapphire::Entity
{

  /** Class representing the Player
  *  Inheriting from Actor
  *
  */
  class Player : public Chara
  {
  public:
    using AchievementDataList = std::map< uint32_t, uint32_t >;
    using AchievementList = std::array< uint8_t, 2048 / 8 >; // up to 2048 achievements
    using TitleList = std::array< uint8_t, 48 >;
    using HowToList = std::array< uint8_t, 34 >;
    using MinionList = std::array< uint8_t, 40 >;
    using MountList = std::array< uint8_t, 22 >;
    using QuestComplete = std::array< uint8_t, 342 >;
    using Discovery = std::array< uint8_t, 400 >;
    using AetheryteList = std::array< uint8_t, 21 >;
    using UnlockList = std::array< uint8_t, 64 >;
    using OrchestrionList = std::array< uint8_t, 40 >;
    using StateFlags = std::array< uint8_t, 12 >;

    using ClassList = std::array< uint16_t, 28 >;
    using ExpList = std::array< uint32_t, 28 >;

    /*! Contructor */
    Player();

    /*! Destructor */
    ~Player();

    void autoAttack( CharaPtr pTarget ) override;

    // EventHandlers
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    /*! add an event to the event array */
    void addEvent( Event::EventHandlerPtr pEvent );

    /*! retrieve an event from the event array */
    Event::EventHandlerPtr getEvent( uint32_t eventId ) const;

    /*! get number of active events */
    size_t getEventCount();

    /*! remove an event from the event array */
    void removeEvent( uint32_t eventId );

    /*! return the eventlist */
    std::map< uint32_t, Event::EventHandlerPtr >& getEventListRef();

    // Events
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    /*! Event to be called on update tick */
    void onTick() override;

    /*! Event to be called upon player death */
    void onDeath() override;

    /*! Event called on every session iteration */
    void update( uint64_t tickCount ) override;

    void setLastAttack( uint64_t tickCount );

    // Quest
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! load data for currently active quests */
    bool loadActiveQuests();

    /*! update quest ( register it as active quest if new ) */
    void updateQuest( const World::Quest& quest );

    /*! return true if quest is currently active */
    bool hasQuest( uint32_t questId );

    std::optional< World::Quest > getQuest( uint32_t questId );

    /*! return the index of a given quest in the players quest list */
    int8_t getQuestIndex( uint16_t questId );
    World::Quest& getQuestByIndex( uint16_t questId );

    int16_t getQuestTracking( uint8_t index ) const;

    /*! finish a given quest */
    void finishQuest( uint16_t questId, uint32_t optionalChoice = 0 );

    /*! finish a given quest */
    void unfinishQuest( uint16_t questId );

    /*! remove a given quest */
    void removeQuest( uint16_t questId );

    bool isQuestCompleted( uint32_t questId );

    /*! add a quest to the completed quests mask */
    void updateQuestsCompleted( uint32_t questId );

    /*! remove a quest from the completed quest mask */
    void removeQuestsCompleted( uint32_t questId );

    /*! get the curent opening sequence */
    uint8_t getOpeningSequence() const;

    /*! set te current opening sequence */
    void setOpeningSequence( uint8_t seq );

    std::array< World::Quest, 30 >& getQuestArrayRef();

    QuestComplete& getQuestCompleteFlags();

    // Inventory / Item / Currency / Shop
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! equip an item to a specified slot */
    void equipItem( Common::GearSetSlot equipSlotId, Item& item, bool sendModel );

    /*! remove an item from an equipment slot */
    void unequipItem( Common::GearSetSlot equipSlotId, Item& item, bool sendModel );

    /*! equip a weapon, possibly forcing a job change */
    void equipWeapon( const Item& item );

    /*! equip a soul crystal, possibly forcing a job change*/
    void equipSoulCrystal( const Item& item );

    /*! unequip a soul crystal, returning to the base class*/
    void unequipSoulCrystal();

    /*! get player ilvl */
    uint16_t getItemLevel() const;

    /*! send player ilvl */
    void sendItemLevel();

    /*! get the current main hand model */
    uint64_t getModelMainWeapon() const;

    /*! get the current off hand model */
    uint64_t getModelSubWeapon() const;

    /*! get the current system hand model */
    uint64_t getModelSystemWeapon() const;

    /*! return a const pointer to the model array */
    const uint32_t* getModelArray() const;

    /*! return the equipment model in a specified equipment slot */
    uint32_t getModelForSlot( Common::GearModelSlot slot );

    /*! add amount to the currency of type */
    void addCurrency( Common::CurrencyType type, uint32_t amount );

    /*! remove amount from the currency of type */
    void removeCurrency( Common::CurrencyType type, uint32_t amount );

    /*! return the current amount of crystals of type */
    uint32_t getCrystal( uint8_t type ) const;

    void updateModels( Common::GearSetSlot equipSlotId, const Item& item );

    Common::GearModelSlot equipSlotToModelSlot( Common::GearSetSlot slot );

    bool getFreeInventoryContainerSlot( Inventory::InventoryContainerPair& containerPair ) const;

    void insertInventoryItem( Common::InventoryType type, uint16_t slot, const ItemPtr item );

    /*!
    * Collect real item handins from container
    * @param itemIds a vector of each catalog id to collect
    * @return true if all items were handed in
    */
    bool collectHandInItems( std::vector< uint32_t > itemIds );

    void addSoldItem( uint32_t itemId, uint8_t stackSize );

    std::deque< std::pair< uint32_t, uint8_t > > *getSoldItems();

    void clearSoldItems();

    // Class / Job / Exp
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! returns the level of the currently active class / job */
    uint8_t getLevel() const override;

    /*! returns the level sync of current active class / job */
    uint8_t getLevelSync() const;

    /*! returns the level of the provided class / job */
    uint8_t getLevelForClass( Common::ClassJob pClass ) const;

    /*! returns if the classjob is unlocked */
    bool isClassJobUnlocked( Common::ClassJob classJob ) const;

    /*! returns the exp of the currently active class / job */
    uint32_t getExp() const;

    /*! sets the exp of the currently active class / job */
    void setExp( uint32_t amount );

    /*! adds exp to the currently active class / job */
    void gainExp( uint32_t amount );

    /*! gain a level on the currently active class / job */
    void levelUp();

    /*! set level on the currently active class / job to given level */
    void setLevel( uint8_t level );

    /*! set level on the provided class / job to given level */
    void setLevelForClass( uint8_t level, Common::ClassJob classjob );

    /*! change class or job to given class / job */
    void setClassJob( Common::ClassJob classJob );

    /*! returns a pointer to the class array */
    ClassList& getClassArray();

    /*! returns a pointer to the exp array */
    ExpList& getExpArray();

    // Base Look / Stats / Params
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! return the birth day */
    uint8_t getBirthDay() const;

    /*! return the birth month */
    uint8_t getBirthMonth() const;

    /*! return the guardian diety Id */
    uint8_t getGuardianDeity() const;

    /*! get look at specified index */
    uint8_t getLookAt( uint8_t index ) const;

    /*! return the race */
    uint8_t getRace() const;

    /*! return gender 0 male, 1 female */
    uint8_t getGender() const;

    /*! return the id of the home town */
    uint8_t getStartTown() const;

    /*! return the voice id */
    uint8_t getVoiceId() const;

    /*! return the grand company */
    uint8_t getGc() const;

    /*! return the grand company rank */
    const std::array< uint8_t, 3 >& getGcRankArray() const;

    /*! set look at index */
    void setLookAt( uint8_t index, uint8_t value );

    /*! set the voice Id */
    void setVoiceId( uint8_t voiceId );

    /*! set the grand company */
    void setGc( uint8_t gc );

    /*! set the grand company rank */
    void setGcRankAt( uint8_t index, uint8_t rank );

    /*! returns true if the player is currently in combat */
    bool isInCombat() const;

    /*! sets players combat state */
    void setInCombat( bool mode );

    /*! return current online status depending on current state / activity */
    Common::OnlineStatus getOnlineStatus() const;

    /*! returns the player to their position before zoning into an instance */
    bool exitInstance();

    /*! gets the players territoryTypeId */
    uint32_t getPrevTerritoryTypeId() const;

    void updatePrevTerritory();

    void forceZoneing( uint32_t zoneId );

    /*! change position, sends update too */
    void changePosition( float x, float y, float z, float o );

    /*! return the characterId */
    uint64_t getCharacterId() const;

    /*! return max hp */
    uint32_t getMaxHp();

    /*! return max mp */
    uint32_t getMaxMp();

    /*! return a players total play time */
    uint32_t getPlayTime() const;

    /*! return true if the player has "new adventurere" status */
    bool isNewAdventurer() const;

    /*! change the players "new adventurere" status */
    void setNewAdventurer( bool state );

    /*! sets the list of current online status */
    void setOnlineStatusMask( uint64_t status );

    /*! sets the list of current online status */
    void setOnlineStatusCustomMask( uint64_t status );

    /*! returns the current online status */
    uint64_t getOnlineStatusCustomMask() const;

    void addOnlineStatus( Common::OnlineStatus status );
    void addOnlineStatus( const std::vector< Common::OnlineStatus >& status );
    void removeOnlineStatus( Common::OnlineStatus status );
    void removeOnlineStatus( const std::vector< Common::OnlineStatus >& status );

    /*! returns the current online status */
    uint64_t getOnlineStatusMask() const;

    uint64_t getFullOnlineStatusMask() const;

    /*! perform a teleport of a specified type ( teleport,return,aethernet ) */
    void teleport( uint16_t aetheryteId, uint8_t type = 1 );

    /*! query teleport of a specified type */
    void teleportQuery( uint16_t aetheryteId );

    Common::PlayerTeleportQuery getTeleportQuery() const;

    void clearTeleportQuery();

    void setDyeingInfo( uint32_t itemToDyeContainer, uint32_t itemToDyeSlot, uint32_t dyeBagContainer, uint32_t dyeBagSlot );
    void dyeItemFromDyeingInfo();

    /*! get player's title list (available titles) */
    TitleList& getTitleList();

    /*! get player's active title */
    uint16_t getTitle() const;

    /*! add title to player title list */
    void addTitle( uint16_t titleId );

    /*! change player's active title */
    void setTitle( uint16_t titleId );

    /*! send the players title list */
    void sendTitleList();

    /*! get player's achievement list */
    AchievementList& getAchievementList();

    /*! get player's achievement data list */
    AchievementDataList& getAchievementDataList();

    /*! set number of gear sets */
    void setMaxGearSets( uint8_t amount );

    /*! get number of gear sets */
    uint8_t getMaxGearSets() const;

    /*! change gear param state */
    void setEquipDisplayFlags( uint16_t state );

    /*! get gear param state */
    uint8_t getEquipDisplayFlags() const;

    /*! mount the specified setMount and send the packets */
    void setMount( uint32_t mountId );

    void setCompanion( uint8_t id );

    uint8_t getCurrentCompanion() const;

    /*! get the current setMount */
    uint8_t getCurrentMount() const;

    /*! set current persistent emote */
    void setPersistentEmote( uint32_t emoteId );

    /*! get current persistent emote */
    uint32_t getPersistentEmote() const;

    void calculateStats() override;

    void sendStats();


    // Aetheryte / Action / Attribute bitmasks
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! register aetheryte aetheryteId and send update */
    void registerAetheryte( uint8_t aetheryteId );

    /*! check if aetheryte is already registered */
    bool isAetheryteRegistered( uint8_t aetheryteId ) const;

    /*! return a const pointer to the aetheryte unlock bitmask array */
    uint8_t getAetheryteMaskAt( uint8_t index ) const;

    /*! return a pointer to the aetheryte unlock bitmask array */
    AetheryteList& getAetheryteArray();

    /*! set homepoint */
    void setHomepoint( uint8_t aetheryteId );

    /*! get homepoint */
    uint8_t getHomepoint() const;

    /*! discover subarea subid fo map map_id, also send udpate packet */
    void discover( int16_t map_id, int16_t sub_id );

    /*! return a pointer to the discovery bitmask array */
    Discovery& getDiscoveryBitmask();

    /*! helper/debug function to reset all discovered areas */
    void resetDiscovery();

    /*! get a pointer to the howto bitmask array */
    HowToList& getHowToArray();

    /*! update bitmask for how-to's seen */
    void updateHowtosSeen( uint32_t howToId );

    /*! learn an action / update the unlock bitmask. */
    void setRewardFlag( Common::UnlockEntry unlockId );

    /*! learn a song / update the unlock bitmask. */
    void learnSong( uint8_t songId, uint32_t itemId );

    /*! check if an action is already unlocked in the bitmask. */
    bool hasReward( Common::UnlockEntry unlockId ) const;

    /*! return a const pointer to the unlock bitmask array */
    const UnlockList& getUnlockBitmask() const;

    /*! return a const pointer to the orchestrion bitmask array */
    const OrchestrionList& getOrchestrionBitmask() const;

    /*! unlock a mount */
    void unlockMount( uint32_t mountId );

    /*! return a const pointer to the setMount guide bitmask array */
    MountList& getMountGuideBitmask();

    bool checkAction() override;

    bool hasQueuedAction() const;

    void setQueuedAction( World::Action::ActionPtr pAction );

    void setLastActionTick( uint64_t tick );

    uint64_t getLastActionTick() const;

    void setRecastGroup( uint8_t index, float time );

    float getRecastGroup( uint8_t index ) const;

    void sendRecastGroups();

    void resetRecastGroups();

    // Spawn handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! initialize the spawnId queue */
    void initSpawnIdQueue();

    /*! get the spawn id mapped to a specific actorId */
    uint8_t getSpawnIdForActorId( uint32_t actorId );

    /*! frees the spawnId assigned to the given actor */
    void freePlayerSpawnId( uint32_t actorId );

    /*! checks if the given spawn id is valid */
    bool isActorSpawnIdValid( uint8_t spawnId );

    /*! send spawn packets to pTarget */
    void spawn( PlayerPtr pTarget ) override;

    /*! send despawn packets to pTarget */
    void despawn( PlayerPtr pTarget ) override;

    // Player State Handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /* return a const pointer to the state flag array */
    const StateFlags& getStateFlags() const;

    /* set a specified state flag */
    void setStateFlag( Common::PlayerStateFlag flag );

    /* set a specified state flag */
    void setStateFlags( std::vector< Common::PlayerStateFlag > flags );

    /* check if a specified flag is set */
    bool hasStateFlag( Common::PlayerStateFlag flag ) const;

    /* reset a specified flag */
    void unsetStateFlag( Common::PlayerStateFlag flag );

    /*! return the userlevel */
    uint8_t getUserLevel() const;

    // Player Database Handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! generate the update sql based on update flags */
    void updateSql();

    /*! initialize player data from db, by character id */
    bool loadFromDb( uint64_t characterId );

    /*! unload player from logout */
    void unload();

    /*! load active class data */
    bool loadClassData();

    /*! load search info */
    bool loadSearchInfo();

    /*! load hunting log entries */
    bool loadHuntingLog();

    /*! load friendlist */
    bool loadFriendList();

    /*! load blacklist */
    bool loadBlacklist();

    /*! update latest sync with db */
    bool syncLastDBWrite();

    /*! get latest db write timestamp */
    uint64_t getLastDBWrite() const;

    // Player Network Handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! send current models ( equipment ) */
    void sendModel();

    /*! send active state flags */
    void sendStateFlags( bool updateInRange = true );

    /*! send status update */
    void sendStatusUpdate() override;

    /*! send the entire inventory sequence */
    void sendInventory();

    /*! returns true if loading is complete ( 0x69 has been received ) */
    bool isLoadingComplete() const;

    /*! set the loading complete bool */
    void setLoadingComplete( bool bComplete );

    void sendZonePackets();

    Common::ZoneingType getZoningType() const;

    void setZoningType( Common::ZoneingType zoneingType );

    void setSearchInfo( uint8_t selectRegion, uint8_t selectClass, const char* searchMessage );

    const char* getSearchMessage() const;

    uint8_t getSearchSelectRegion() const;

    uint8_t getSearchSelectClass() const;

    bool isDirectorInitialized() const;

    void setDirectorInitialized( bool isInitialized );

    // Housing Handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void setLandFlags( uint8_t permissionSet, uint32_t landFlags, Common::LandIdent ident );

    void sendLandFlags();
    void sendLandFlagsSlot( Common::LandFlagsSlot slot );

    // Player Battle Handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void initHateSlotQueue();

    void hateListAdd( const BNpc& bnpc );
    void hateListRemove( const BNpc& bnpc );

    bool hateListHasEntry( const BNpc& bnpc );

    const std::map< uint32_t, uint8_t >& getActorIdToHateSlotMap();

    Entity::GameObjectPtr lookupTargetById( uint64_t targetId );

    bool isLogin() const;

    void setIsLogin( bool bIsLogin );

    uint32_t getPrevTerritoryId() const;

    uint8_t getGmRank() const;

    void setGmRank( uint8_t rank );

    bool getGmInvis() const;

    void setGmInvis( bool invis );

    bool isActingAsGm() const;

    uint8_t getMode() const;

    void setMode( uint8_t mode );

    void setAutoattack( bool mode );

    bool isAutoattackOn() const;

    void onMobAggro( const BNpc& bnpc );
    void onMobDeaggro( const BNpc& bnpc );

    // Content Finder handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /*! Get an unix time when the player can register into content finder again. */
    uint32_t getCFPenaltyTimestamp() const;

    /*! Set an unix time when the player can register into content finder again. */
    void setCFPenaltyTimestamp( uint32_t timestamp );

    uint32_t getCFPenaltyMinutes() const;

    void setCFPenaltyMinutes( uint32_t minutes );

    void setEorzeaTimeOffset( uint64_t timestamp );

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // Database
    void updateDbAllQuests() const;

    void deleteDbQuest( uint16_t questId ) const;

    void insertDbQuest( uint16_t questId, uint8_t index, uint8_t seq ) const;

    void insertDbQuest( const World::Quest& quest, uint8_t index ) const;

    void updateDbSearchInfo() const;

    void updateDbClass() const;

    void insertDbClass( const uint8_t classJobIndex, uint8_t level = 1 ) const;

    void updateDbMonsterNote();

    void updateDbFriendList();

    void updateDbBlacklist();

    void updateDbChara() const;

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    void setMarkedForRemoval( bool removal = true );

    bool isMarkedForRemoval() const;

    void setOnEnterEventDone( bool isDone );

    bool isOnEnterEventDone() const;

    /*! gets the next available obj count */
    uint8_t getNextObjSpawnIndexForActorId( uint32_t actorId );

    /*! resets the players obj count */
    void resetObjSpawnIndex();

    /*! frees an obj count to be used by another eobj */
    void freeObjSpawnIndexForActorId( uint32_t actorId );

    /*! checks if a spawn index is valid */
    bool isObjSpawnIndexValid( uint8_t index );


    // Inventory Handling
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void initInventory();

    using InvSlotPair = std::pair< uint16_t, int8_t >;
    using InvSlotPairVec = std::vector< InvSlotPair >;

    ItemPtr createItem( uint32_t catalogId, uint32_t quantity = 1 );

    bool loadInventory();

    InvSlotPairVec getSlotsOfItemsInInventory( uint32_t catalogId );

    InvSlotPair getFreeBagSlot();

    InvSlotPair getFreeContainerSlot( uint32_t containerId );

    ItemPtr addItem( uint32_t catalogId, uint32_t quantity = 1, bool isHq = false, bool slient = false, bool canMerge = true );

    void moveItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot );

    void swapItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot );

    void discardItem( uint16_t fromInventoryId, uint16_t fromSlotId );

    void splitItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot,
                    uint16_t splitCount );

    void mergeItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot );

    ItemPtr getItemAt( uint16_t containerId, uint16_t slotId );

    bool updateContainer( uint16_t storageId, uint16_t slotId, ItemPtr pItem );

    /*! calculate and return player ilvl based off equipped gear */
    uint16_t calculateEquippedGearItemLevel();

    ItemPtr getEquippedWeapon();

    /*! return the current amount of currency of type */
    uint32_t getCurrency( Common::CurrencyType type );

    void writeInventory( Common::InventoryType type );

    void writeItem( ItemPtr pItem ) const;

    void writeCurrencyItem( Common::CurrencyType type );

    void deleteItemDb( ItemPtr pItem ) const;

    /*! return the crystal amount of currency of type */
    uint32_t getCrystal( Common::CrystalType type );

    /*! add amount to the crystal of type */
    void addCrystal( Common::CrystalType type, uint32_t amount );

    /*! remove amount from the crystals of type */
    void removeCrystal( Common::CrystalType type, uint32_t amount );

    bool isObtainable( uint32_t catalogId, uint8_t quantity );

    uint32_t getNextInventorySequence();

    bool findFirstItemWithId( uint32_t catalogId, Inventory::InventoryContainerPair& location, std::initializer_list< Common::InventoryType > bags = { Common::Bag0, Common::Bag1, Common::Bag2, Common::Bag3 } );

    uint16_t getFreeSlotsInBags();

    void setActiveLand( uint8_t land, uint8_t ward );
    Common::ActiveLand getActiveLand() const;

    ItemPtr dropInventoryItem( Common::InventoryType storageId, uint8_t slotId );

    //////////////////////////////////////////////////////////////////////////////////////////////////////

    using FriendListIDVec = std::array< uint64_t, 200 >;
    using FriendListDataVec = std::array< Common::HierarchyData, 200 >;
    using BlacklistIDVec = std::array< uint64_t, 200 >;

    Common::HuntingLogEntry& getHuntingLogEntry( uint8_t index );

    void sendHuntingLog();

    void updateHuntingLog( uint16_t id );

    uint64_t getPartyId() const;
    void setPartyId( uint64_t partyId );

    FriendListIDVec& getFriendListID();
    FriendListDataVec& getFriendListData();

    BlacklistIDVec& getBlacklistID();

    uint64_t m_lastMoveTime{};
    uint8_t m_lastMoveflag{};

    void setFalling( bool state, const Common::FFXIVARR_POSITION3& pos, bool ignoreDamage = false );
    bool isFalling() const;

    // todo: sort this requestkey pcsearch mess
    void setLastPcSearchResult( std::vector< uint32_t > result );
    std::vector< uint32_t >& getLastPcSearchResult();

    const Common::FFXIVARR_POSITION3& getPrevPos() const;
    float getPrevRot() const;

    bool isConnected() const;
    void setConnected( bool isConnected );

  private:
    /*! queue a packet for the player */
    void queuePacket( Network::Packets::FFXIVPacketBasePtr pPacket );

    using InventoryMap = std::map< uint16_t, ItemContainerPtr >;

    uint64_t m_lastDBWrite;

    bool m_bIsLogin;

    uint64_t m_characterId; // This id will be the name of the folder for character settings in "My Games"

    uint8_t m_mode{};

    // falling logic
    bool m_falling;
    Common::FFXIVARR_POSITION3 m_initialFallPos{};

    bool m_markedForRemoval;

    bool m_directorInitialized;

    bool m_onEnterEventDone;

    uint32_t m_inventorySequence{};

    World::Action::ActionPtr m_pQueuedAction;
    uint64_t m_lastActionTick;
    float m_recast[80]{};
    float m_recastMax[80]{};

    InventoryMap m_storageMap;

    Common::FFXIVARR_POSITION3 m_prevPos{};
    uint32_t m_prevTerritoryTypeId{};
    uint32_t m_prevTerritoryId{};
    float m_prevRot{};

    uint8_t m_voice{};

    uint8_t m_equippedMannequin;

    uint64_t m_modelMainWeapon;
    uint64_t m_modelSubWeapon;
    uint64_t m_modelSystemWeapon{};

    bool m_bNewGame{};

    uint8_t m_guardianDeity{};
    uint8_t m_birthDay{};
    uint8_t m_birthMonth{};

    struct RetainerInfo
    {
      uint32_t retainerId;
      char retainerName[32];
      uint32_t createUnixTime;
      bool isActive;
      bool isRename;
      uint8_t status;
    } m_retainerInfo[8]{};

    AchievementList m_achievementList{};
    AchievementDataList m_achievementData{};
    uint16_t m_activeTitle{};
    TitleList m_titleList{};
    HowToList m_howTo{};
    MinionList m_minions{};
    MountList m_mountGuide{};
    QuestComplete m_questCompleteFlags{};
    Discovery m_discovery{};
    AetheryteList m_aetheryte{};
    UnlockList m_unlocks{};
    OrchestrionList m_orchestrion{};
    ClassList m_classArray{};
    ExpList m_expArray{};
    StateFlags m_stateFlags{};

    uint8_t m_homePoint;
    uint8_t m_startTown;
    uint16_t m_townWarpFstFlags;

    uint32_t m_playTime;
    uint8_t m_openingSequence{0};

    uint16_t m_itemLevel{0};
    std::map< uint32_t, Event::EventHandlerPtr > m_eventHandlerMap;

    std::queue< uint8_t > m_freeHateSlotQueue; // queue with "hate slots" free to be assigned
    std::map< uint32_t, uint8_t > m_actorIdTohateSlotMap;

    std::array< World::Quest, 30 > m_quests;
    std::array< int16_t, 5 > m_questTracking{};


    uint8_t m_gmRank{};
    bool m_gmInvis{false};

    uint8_t m_equipDisplayFlags{};

    bool m_bInCombat;
    bool m_bLoadingComplete;
    bool m_bAutoattack;

    bool m_bIsConnected;

    Common::ZoneingType m_zoningType;

    bool m_bNewAdventurer{};
    uint64_t m_onlineStatus;
    uint64_t m_onlineStatusCustom;

    // search info
    char m_searchMessage[193]{}; // searchmessage to show in profile
    uint8_t m_searchSelectRegion{}; // regions selected to show up in profile
    uint8_t m_searchSelectClass{}; // class selected to show up in profile

    // shop info
    std::deque< std::pair< uint32_t, uint8_t > > m_soldItems;

    // housing info
    Common::CharaLandData m_charaLandData[2]{};

    Common::ActiveLand m_activeLand{};

    // gc info
    uint8_t m_gc{};
    std::array< uint8_t, 3 > m_gcRank{};

    // content finder info
    uint32_t m_cfPenaltyUntil{}; // unix time

    uint8_t m_companionId{};
    uint32_t m_mount;
    uint32_t m_emoteMode;

    Common::PlayerTeleportQuery m_teleportQuery{};

    struct PlayerDyeingInfo
    {
      uint32_t itemToDyeContainer;
      uint32_t itemToDyeSlot;
      uint32_t dyeBagContainer;
      uint32_t dyeBagSlot;
    } m_dyeingInfo{};

    Common::Util::SpawnIndexAllocator< uint8_t > m_objSpawnIndexAllocator;
    Common::Util::SpawnIndexAllocator< uint8_t > m_actorSpawnIndexAllocator;

    std::array< Common::HuntingLogEntry, 12 > m_huntingLogEntries{};

    FriendListIDVec m_friendList{};
    FriendListDataVec m_friendInviteList{};

    BlacklistIDVec m_blacklist{};

    uint64_t m_partyId;
    std::vector< uint32_t > m_lastPcSearch;

    bool addQuest( const World::Quest& quest );

    void addQuestTracking( uint8_t idx );

    void removeQuestTracking( int8_t idx );

    int8_t getFreeQuestSlot();

  };

}