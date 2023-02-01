/**
* IPC Packet Definitions (Server IPC Packets)
* Structural definitions for the various server IPC packet types.
* IMPORTANT NOTE: Do not use these for parsing IPC packets sent by the
* client. See the Client namespace for those types!
*/
#pragma once

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  struct ZoneProtoDownServerPos
  {
    uint32_t originEntityId;
    float pos[3];
    float dir;
  };

  /**
  * Structural representation of the packet sent by the server as response
  * to a ping packet
  */
  struct FFXIVIpcSync : FFXIVIpcBasePacket< SyncReply >
  {
    uint32_t clientTimeValue;
    uint32_t transmissionInterval;
    ZoneProtoDownServerPos position;
  };

  /**
  * Structural representation of the packet sent by the server as response
  * to a ping packet
  */
  struct FFXIVIpcLogin : FFXIVIpcBasePacket< LoginReply >
  {
    uint32_t clientTimeValue;
    uint32_t loginTicketId;
    uint32_t playerActorId;
  };

  /**
  * Structural representation of the packet sent by the server
  * carrying chat messages
  */
  struct FFXIVIpcChat : FFXIVIpcBasePacket< Chat >
  {
    uint16_t type;
    uint8_t __padding1;
    uint8_t __padding2;
    uint32_t entityId;
    uint64_t characterId;
    uint32_t __unknown3;
    char speakerName[32];
    char message[1024];
  };

  struct FFXIVIpcEnableLogout : FFXIVIpcBasePacket< EnableLogout >
  {
    uint8_t content;
  };


  /**
  * Structural representation of the packet sent by the server
  * with a list of players ( party list | friend list | search results )
  * 3.0 Update: 64bit TerritoryID -> 32bit Timestamp, 32bit TerritoryID
  */
  struct PlayerEntry
  {
    uint64_t CharacterID;
    uint32_t Timestamp;
    uint32_t TerritoryID;
    uint8_t HierarchyStatus;
    uint8_t HierarchyType;
    uint8_t HierarchyGroup;
    uint8_t IsDeleted;
    uint16_t TerritoryType;
    uint8_t GrandCompanyID;
    uint8_t Region;
    uint8_t SelectRegion;
    uint8_t IsSearchComment;
    uint8_t __padding1;
    uint8_t __padding2;
    uint64_t OnlineStatus;
    uint8_t CurrentClassID;
    uint8_t SelectClassID;
    uint16_t CurrentLevel;
    uint16_t SelectLevel;
    uint8_t Identity;
    char CharacterName[32];
    char FcTag[7];
  };

  struct FFXIVIpcGetCommonlistResult : FFXIVIpcBasePacket< GetCommonlistResult >
  {
    uint64_t CommunityID;
    uint16_t NextIndex;
    uint16_t Index;
    uint8_t ListType;
    uint8_t RequestKey;
    uint8_t RequestParam;
    uint8_t __padding1;

    PlayerEntry entries[10];
  };

  struct FFXIVIpcGetCommonlistDetailResult : FFXIVIpcBasePacket< GetCommonlistDetailResult >
  {
    uint64_t DetailCharacterID;
    uint64_t CommunityID;
    uint64_t SelectClassID;
    uint64_t CrestID;
    uint8_t ListType;

    char SearchComment[193];
    char FreeCompanyName[23];
    uint8_t GrandCompanyRank[3];

    struct ClassJobEntry
    {
      uint16_t id;
      uint16_t level;
    } ClassData[34]; // ClassJob::MAX
  };

  struct FFXIVIpcPcSearchResult : FFXIVIpcBasePacket< PcSearchResult >
  {
    int16_t ResultCount;
  };

  struct FFXIVIpcLinkshellResult : FFXIVIpcBasePacket< LinkshellResult >
  {
    uint64_t LinkshellID;
    uint64_t TargetCharacterID;
    uint32_t UpPacketNo;
    uint32_t Result;
    uint8_t UpdateStatus;
    uint8_t Identity;
    char LinkshellName[32];
    char TargetName[32];
  };
  
  struct FFXIVIpcInviteResult : FFXIVIpcBasePacket< InviteResult >
  {
    uint32_t Result;
    uint8_t AuthType;
    uint8_t Identity;
    char TargetName[32];
  };

  struct FFXIVIpcInviteReplyResult : FFXIVIpcBasePacket< InviteReplyResult >
  {
    uint32_t Result;
    uint8_t AuthType;
    uint8_t Answer;
    uint8_t Identity;
    char InviteCharacterName[32];
  };

  struct FFXIVIpcInviteUpdate : FFXIVIpcBasePacket< InviteUpdate >
  {
    uint64_t InviteCharacterID;
    uint32_t InviteTime;
    uint8_t AuthType;
    uint8_t InviteCount;
    uint8_t Result;
    uint8_t Identity;
    char InviteName[32];
  };

  struct FFXIVIpcFriendlistRemoveResult : FFXIVIpcBasePacket< FriendlistRemoveResult >
  {
    uint64_t RemovedCharacterID;
    uint32_t Result;
    uint8_t Identity;
    char RemovedCharacterName[32];
  };

  struct FFXIVIpcFreeCompanyResult : FFXIVIpcBasePacket< FreeCompanyResult >
  {
    uint64_t FreeCompanyID;
    uint64_t TargetCharacterID;
    uint32_t Type;
    uint32_t Result;
    uint8_t UpdateStatus;
    uint8_t Identity;
    char FreeCompanyName[46];
    char TargetName[32];
  };

  struct FFXIVIpcGetFcStatusResult : FFXIVIpcBasePacket< GetFcStatusResult >
  {
    uint64_t FreeCompanyID;
    uint64_t AuthorityList;
    uint64_t ChannelID;
    uint64_t CrestID;
    uint64_t CharaFcState;
    uint64_t CharaFcParam;
    uint16_t Param;
    uint8_t FcStatus;
    uint8_t GrandCompanyID;
    uint8_t HierarchyType;
    uint8_t FcRank;
    uint8_t IsCrest;
    uint8_t IsDecal;
    uint8_t IsFcAction;
    uint8_t IsChestExt1;
    uint8_t IsChestLock;
  };

  struct FFXIVIpcSetProfileResult : FFXIVIpcBasePacket< SetProfileResult >
  {
    uint64_t OnlineStatus;
    uint64_t SelectClassID;
    uint32_t Result;
    uint8_t CurrentSelectClassID;
    uint8_t Region;
    char SearchComment[193];
  };

  struct FFXIVIpcGetProfileResult : FFXIVIpcBasePacket< GetProfileResult >
  {
    uint64_t OnlineStatus;
    uint64_t SelectClassID;
    uint8_t CurrentSelectClassID;
    uint8_t Region;
    char SearchComment[193];
  };

  struct FFXIVIpcGetSearchCommentResult : FFXIVIpcBasePacket< GetSearchCommentResult >
  {
    uint32_t TargetEntityID;
    char SearchComment[193];
  };

  struct FFXIVIpcGetCharacterNameResult : FFXIVIpcBasePacket< GetCharacterNameResult >
  {
    uint64_t CharacterID;
    char CharacterName[32];
  };

  /**
  * Structural representation of the packet sent by the server
  * to display a server notice message
  */
  struct FFXIVIpcSendSystemMessage : FFXIVIpcBasePacket< SendSystemMessage >
  {
    /*!
     * 0 = chat log
     * 2 = nothing
     * 4 = on screen message
     * 5 = on screen message + chat log
     */
    uint8_t MessageParam;
    char Message[769];
  };

  struct FFXIVIpcSendLoginMessage : FFXIVIpcBasePacket< SendLoginMessage >
  {
    /*!
     * 0 = chat log
     * 2 = nothing
     * 4 = on screen message
     * 5 = on screen message + chat log
     */
    uint8_t MessageParam;
    char Message[769];
  };

  struct FFXIVIpcSetOnlineStatus : FFXIVIpcBasePacket< UpdateOnlineStatus >
  {
    uint64_t onlineStatusFlags;
  };

  struct BlacklistCharacter
  {
    uint64_t CharacterID;
    char CharacterName[32];
  };

  struct FFXIVIpcBlacklistAddResult : FFXIVIpcBasePacket< BlacklistAddResult >
  {
    BlacklistCharacter AddedCharacter;
    uint32_t Result;
    uint8_t Identity;
  };

  struct FFXIVIpcBlacklistRemoveResult : FFXIVIpcBasePacket< BlacklistRemoveResult >
  {
    BlacklistCharacter RemovedCharacter;
    uint32_t Result;
    uint8_t Identity;
  };

  struct FFXIVIpcGetBlacklistResult : FFXIVIpcBasePacket< GetBlacklistResult >
  {
    BlacklistCharacter Blacklist[20];
    uint8_t NextIndex;
    uint8_t Index;
    uint8_t RequestKey;
  };

  struct FFXIVIpcGetLinkshellListResult : FFXIVIpcBasePacket< GetLinkshellListResult >
  {
    struct ZoneProtoDownLinkshell
    {
      uint64_t LinkshellID;
      uint64_t ChannelID;
      uint32_t HierarchyID;
      char LinkshellName[32];
    } LinkshellList[8];
  };

  struct FFXIVIpcChatChannelResult : FFXIVIpcBasePacket< ChatChannelResult >
  {
    uint64_t ChannelID;
    uint64_t CommunityID;
    uint64_t TargetCharacterID;
    uint32_t UpPacketNo;
    uint32_t Result;
  };

  struct FFXIVIpcAchievement : FFXIVIpcBasePacket< Achievement >
  {
    uint8_t complete[256]; // bitmask of achievements, up to 8 * 256 (2048) achvs
    uint16_t history[5];   // last 5 achievement IDs
  };

  struct ZoneProtoDownLetterBoxAppendItemBase
  {
    uint32_t CatalogID;
    uint32_t Stack;
  };

  struct ZoneProtoDownLetterBoxAppendItem
  {
    ZoneProtoDownLetterBoxAppendItemBase ItemList[5];
    ZoneProtoDownLetterBoxAppendItemBase Gil;
  };

  struct FFXIVIpcGetLetterMessageResult :
    FFXIVIpcBasePacket< GetLetterMessageResult >
  {
    struct ZoneProtoDownLetterMessage
    {
      uint64_t SenderCharacterID;
      uint32_t Date;
      ZoneProtoDownLetterBoxAppendItem AppendItem;
      uint8_t IsRead;
      uint8_t Type;
      uint8_t IsMessageEnd;
      char SenderCharacterName[32];
      char Message[61];
    } LetterMessage[5];

    uint8_t NextIndex;
    uint8_t Index;
    uint8_t RequestKey;
  };

  struct FFXIVIpcGetLetterMessageDetailResult :
    FFXIVIpcBasePacket< GetLetterMessageDetailResult >
  {
    uint64_t SenderCharacterID;
    uint32_t Date;
    char Message[601];
  };

  struct FFXIVIpcLetterResult :
    FFXIVIpcBasePacket< LetterResult >
  {
    uint32_t UpPacketNo;
    uint64_t SenderCharacterID;
    uint32_t Date;
    ZoneProtoDownLetterBoxAppendItem AppendItem;
    uint32_t Result;
  };

  /**
  * Structural representation of the packet sent by the server
  * to show the mail delivery notification
  */
  struct FFXIVIpcGetLetterStatusResult : FFXIVIpcBasePacket< GetLetterStatusResult >
  {
    uint32_t NoreceiveCount;
    uint16_t ItemCount;
    uint8_t UnreadCount;
    uint8_t TotalCount;
    uint8_t GiftCount;
    uint8_t GmCount;
    uint8_t UnreadGmCount;
    uint8_t SupportCount;
  };

  struct FFFXIVIpcItemSearchResult : FFXIVIpcBasePacket< ItemSearchResult >
  {
    uint32_t CatalogID;
    uint32_t Result;
    uint8_t SubQuality;
    uint8_t MateriaCount;
    uint8_t Count;
  };

  struct ZoneProtoDownItemSearchData
  {
    uint64_t ItemID;
    uint64_t SellRetainerID;
    uint64_t OwnerCharacterID;
    uint64_t SignatureID;
    uint32_t SellPrice;
    uint32_t BuyTax;
    uint32_t Stack;
    uint32_t CatalogID;
    uint32_t SellRealDate;
    uint16_t StorageID;
    uint16_t ContainerIndex;
    uint16_t Durability;
    uint16_t Refine;
    uint16_t Materia[8];
    char SellRetainerName[32];
    uint8_t SubQuality;
    uint8_t MateriaCount;
    uint8_t RegisterMarket;
    uint8_t Stain;
  };

  struct FFXIVIpcGetItemSearchListResult : FFXIVIpcBasePacket< GetItemSearchListResult >
  {
    ZoneProtoDownItemSearchData ItemSearchList[10];
    uint8_t NextIndex;
    uint8_t Index;
    uint8_t RequestKey;
  };

  struct ZoneProtoDownItemHistoryData
  {
    uint32_t CatalogID;
    uint32_t SellPrice;
    uint32_t BuyRealDate;
    uint32_t Stack;
    uint8_t SubQuality;
    uint8_t MateriaCount;
    char BuyCharacterName[32];
  };

  struct FFXIVIpcGetItemHistoryResult : FFXIVIpcBasePacket< GetItemHistoryResult >
  {
    uint32_t CatalogID;
    ZoneProtoDownItemHistoryData ItemHistoryList[20];
  };

  struct ZoneProtoDownCatalogSearchData
  {
    uint32_t CatalogID;
    uint16_t StockCount;
    uint16_t RequestItemCount;
  };

  struct FFXIVIpcCatalogSearchResult : FFXIVIpcBasePacket< CatalogSearchResult >
  {
    ZoneProtoDownCatalogSearchData CatalogList[20];
    uint32_t NextIndex;
    uint32_t Result;
    uint32_t Index;
    uint8_t RequestKey;
    uint8_t Type;
  };

  /**
  * Structural representation of the packet sent by the server
  * add a status effect
  */
  struct FFXIVIpcActionIntegrity : FFXIVIpcBasePacket< ActionIntegrity >
  {
    uint32_t ResultId;
    uint32_t Target;
    uint8_t ResultIndex;
    uint8_t ClassJob;
    uint8_t __padding1;
    uint8_t __padding2;
    uint32_t Hp;
    uint16_t Mp;
    uint16_t Tp;
    uint32_t HpMax;
    uint16_t MpMax;
    uint8_t StatusCount;
    uint8_t __padding3;
    Common::IntegrityStatus Status[4];
  };

  /**
  * Structural representation of the packet sent by the server
  * to update certain player details / status
  */
  struct FFXIVIpcActorControl : FFXIVIpcBasePacket< Order >
  {
    /* 0000 */ uint16_t category;
    /* 0002 */ uint16_t padding;
    /* 0004 */ uint32_t param1;
    /* 0008 */ uint32_t param2;
    /* 000C */ uint32_t param3;
    /* 0010 */ uint32_t param4;
  };

  /**
  * Structural representation of the packet sent by the server
  * to update certain player details / status
  */
  struct FFXIVIpcActorControlSelf : FFXIVIpcBasePacket< OrderMySelf >
  {
    /* 0000 */ uint16_t category;
    /* 0002 */ uint16_t padding;
    /* 0004 */ uint32_t param1;
    /* 0008 */ uint32_t param2;
    /* 000C */ uint32_t param3;
    /* 0010 */ uint32_t param4;
    /* 0014 */ uint32_t param5;
    /* 0018 */ uint32_t param6;
  };

  /**
  * Structural representation of the packet sent by the server
  * to update certain player details / status
  */
  struct FFXIVIpcActorControlTarget : FFXIVIpcBasePacket< OrderTarget >
  {
    /* 0000 */ uint16_t category;
    /* 0002 */ uint16_t padding;
    /* 0004 */ uint32_t param1;
    /* 0008 */ uint32_t param2;
    /* 000C */ uint32_t param3;
    /* 0010 */ uint32_t param4;
    /* 0018 */ uint64_t targetId;
  };

  /**
  * Structural representation of the packet sent by the server
  * to update HP / MP / TP
  */
  struct FFXIVIpcResting : FFXIVIpcBasePacket< Resting >
  {
    /* 0000 */ uint32_t Hp;
    /* 0004 */ uint16_t Mp;
    /* 0006 */ uint16_t Tp;
    /* 0008 */ uint16_t Gp;
  };

  struct FFXIVIpcRecastGroup : FFXIVIpcBasePacket< RecastGroup >
  {
    float Recast[80];
    float RecastMax[80];
  };

  struct FFXIVIpcHudParam : FFXIVIpcBasePacket< HudParam >
  {
    uint8_t ClassJob;
    uint8_t Lv;
    uint8_t OrgLv;
    uint8_t LvSync;
    uint32_t Hp;
    uint32_t HpMax;
    uint16_t Mp;
    uint16_t MpMax;
    uint16_t Tp;
    uint8_t __padding1;
    uint8_t __padding2;
    Common::StatusWork effect[30];
  };

  struct FFXIVIpcActionResult : FFXIVIpcBasePacket< ActionResult >
  {
    uint64_t MainTarget;
    uint16_t Action;
    uint8_t ActionArg;
    uint8_t ActionKind;
    uint32_t ActionKey;
    uint32_t RequestId;
    uint32_t ResultId;
    float LockTime;
    uint16_t DirTarget;
    uint8_t Flag;
    uint8_t TargetCount;
    uint32_t BallistaEntityId;
    Common::CalcResult CalcResult[16];
    uint64_t Target[16];
    uint16_t TargetPos[3];
  };

  struct FFXIVIpcActionResult1 : FFXIVIpcBasePacket< ActionResult1 >
  {
    uint64_t MainTarget;
    uint16_t Action;
    uint8_t ActionArg;
    uint8_t ActionKind;
    uint32_t ActionKey;
    uint32_t RequestId;
    uint32_t ResultId;
    float LockTime;
    uint8_t Flag;
    uint8_t __padding1;
    uint16_t DirTarget;
    uint64_t Target;
    uint32_t BallistaEntityId;
    Common::CalcResult CalcResult;
  };

  struct MountStruct
  {
    uint8_t Id;
    uint8_t EquipmentHead;
    uint8_t EquipmentBody;
    uint8_t EquipmentLeg;
    uint8_t Stain;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    float Time;
  };

  /**
  * Structural representation of the packet sent by the server
  * to spawn an actor
  */
  struct FFXIVIpcPlayerSpawn : FFXIVIpcBasePacket< Create >
  {
    uint32_t LayoutId;
    uint32_t NameId;
    uint32_t NpcId;
    uint32_t BindId;
    uint32_t ContentId;
    uint32_t OwnerId;
    uint32_t TriggerId;
    uint32_t ChannelingTarget;
    uint64_t MainTarget;
    uint16_t FATE;
    uint16_t WorldId;
    uint8_t GMRank;
    uint8_t Index;
    uint8_t Mode;
    uint8_t ModeArgs;
    uint8_t ActiveType;
    uint8_t Rank;
    uint8_t ObjKind;
    uint8_t ObjType;
    uint32_t ParentId;
    uint8_t Voice;
    uint8_t BuddyScale;
    uint8_t CrestEnable;
    uint8_t Channeling;
    uint32_t Padding__;
    uint64_t Crest;
    uint64_t MainWeapon;
    uint64_t SubWeapon;
    uint64_t SystemWeapon;
    uint16_t Dir;
    uint16_t ModelCharaId;
    uint16_t Title;
    uint8_t Battalion;
    uint8_t Companion;
    uint8_t GrandCompany;
    uint8_t GrandCompanyRank;
    uint8_t Lv;
    uint8_t ClassJob;
    uint32_t Hp;
    uint16_t Mp;
    uint16_t Tp;
    uint32_t HpMax;
    uint16_t MpMax;
    uint16_t NormalAI;
    uint8_t OnlineStatus;
    uint8_t PermissionInvisibility;
    uint8_t PermissionInvisibility1; // makes player invisible too
    uint8_t FirstAttackType;
    uint64_t FirstAttackId;
    uint8_t LinkReply;
    uint8_t LinkCountLimit;
    uint8_t LinkGroup;
    uint8_t LinkRange;
    uint8_t LinkFamily;
    uint8_t LinkParent;
    uint8_t PoseEmote;
    uint8_t __padding1;
    uint16_t Flag;
    uint8_t __padding2;
    uint8_t __padding3;
    Common::StatusWork Status[30];
    MountStruct Mount;
    uint8_t Name[32];
    uint8_t Customize[26];
    uint32_t Equipment[10];
    float Pos[3];
    uint8_t FreeCompanyTag[6];
    uint8_t PartsState[3];
    uint8_t State[3];
  };

  /**
  * Structural representation of the packet sent by the server
  * to show player movement
  */
  struct FFXIVIpcActorFreeSpawn : FFXIVIpcBasePacket< Delete >
  {
    uint32_t spawnId;
    uint32_t actorId;
  };

  /**
  * Structural representation of the packet sent by the server
  * to show player movement
  */
  struct FFXIVIpcActorMove : FFXIVIpcBasePacket< ActorMove >
  {
    uint8_t dir;
    uint8_t dirBeforeSlip;
    uint8_t flag;
    uint8_t flag2;
    uint8_t speed;
    uint8_t __padding1;
    uint16_t pos[3];
  };

  struct FFXIVIpcTransfer : FFXIVIpcBasePacket< Transfer >
  {
    uint16_t dir;
    uint8_t padding1;
    uint8_t padding2;
    float duration;
    uint8_t flag;
    uint8_t padding3;
    uint16_t pos[3];
  };

  /**
  * Structural representation of the packet sent by the server
  * to set an actors position
  */
  struct FFXIVIpcWarp : FFXIVIpcBasePacket< Warp >
  {
    uint16_t Dir;
    uint8_t Type;
    uint8_t TypeArg;
    uint32_t LayerSet;
    float x;
    float y;
    float z;
  };


  /**
  * Structural representation of the packet sent by the server
  * to start an actors casting
  */
  struct FFXIVIpcActorCast : FFXIVIpcBasePacket< RequestCast >
  {
    uint16_t Action;
    uint8_t ActionKind;
    uint8_t __padding1;
    uint32_t ActionKey;
    float CastTime;
    uint32_t Target;
    float Dir;
    uint32_t BallistaEntityId;
    uint16_t TargetPos[3];
  };

  struct FFXIVIpcHaterList : FFXIVIpcBasePacket< HaterList >
  {
    uint8_t Count;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;

    struct ZoneProtoDownHater
    {
      uint32_t Id;
      uint8_t Rate;
    } List[32];
  };

  struct FFXIVIpcHateList : FFXIVIpcBasePacket< HateList >
  {
    uint8_t Count;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;

    struct ZoneProtoDownHate
    {
      uint32_t Id;
      uint32_t Value;
    } List[32];

  };



  /**
   * Structural representation of the packet sent by the server
   * to send the titles available to the player
   */
  struct FFXIVIpcTitleList : FFXIVIpcBasePacket< TitleList >
  {
    uint8_t TitleFlagsArray[32];
  };

  /**
  * Structural representation of the packet sent by the server
  * to initialize a zone for the player
  */
  struct FFXIVIpcInitZone : FFXIVIpcBasePacket< InitZone >
  {
    uint16_t ZoneId;
    uint16_t TerritoryType;
    uint16_t TerritoryIndex;
    uint8_t __padding1;
    uint8_t __padding2;
    uint32_t LayerSetId;
    uint32_t LayoutId;
    uint8_t WeatherId;
    uint8_t Flag;
    uint16_t FestivalEid0;
    uint16_t FestivalPid0;
    uint16_t FestivalEid1;
    uint16_t FestivalPid1;
    uint8_t __padding3;
    uint8_t __padding4;
    float Pos[3];
  };


  /**
  * Structural representation of the packet sent by the server to initialize
  * the client UI upon initial connection.
  */
  struct FFXIVIpcPlayerStatus : FFXIVIpcBasePacket< PlayerStatus >
  {
    uint64_t CharaId;
    uint64_t Crest;
    uint32_t EntityId;
    uint32_t RestPoint;
    uint8_t Unknown8;
    uint8_t Unknown9;
    uint8_t Unknown10;
    uint8_t ExpansionLevel;
    uint8_t Race;
    uint8_t Tribe;
    uint8_t Sex;
    uint8_t ClassJob;
    uint8_t FirstClass;
    uint8_t GuardianDeity;
    uint8_t BirthMonth;
    uint8_t Birthday;
    uint8_t StartTown;
    uint8_t GrandCompany;
    uint8_t HomePoint;
    uint8_t Pet;
    uint8_t BuddyRank;
    uint8_t BuddyRankExceeded;
    uint8_t BuddySkillPoint;
    uint8_t BuddyCommand;
    uint8_t BuddyStain;
    uint8_t BuddyFavorite;
    uint8_t LegacyCompleteFlag;
    float BuddyTimer;
    uint32_t BuddyExp;
    uint32_t GCSupplySeed;
    uint32_t CatchCount;
    uint32_t UseBaitCatalogId;
    uint32_t PvPWeeklyPoint;
    uint16_t PvPMatchCount;
    uint16_t PvPWinCount;
    uint16_t PvPWeeklyMatchCount;
    uint16_t PvPWeeklyWinCount;
    uint16_t MVPPoint;
    uint16_t DailyQuestLastAcceptTime;
    uint8_t DailyQuestSeed;
    uint8_t TreasureObtainedFlag;
    uint8_t RelicKey;
    uint8_t RelicNoteKey;
    uint8_t AdventureNotePhase;
    uint8_t RetainerCount;
    uint8_t Unknown4;
    uint8_t __padding5;
    uint32_t Frontline01MatchCount;
    uint16_t Frontline01WeeklyMatchCount;
    uint8_t Unknown1[10];
    uint8_t Anima;
    uint8_t Unknown11;
    uint8_t MobHuntWeeklyOrder;
    uint8_t Name[32];
    uint8_t PSNId[17];
    uint16_t Lv[23];
    uint32_t Exp[23];
    uint8_t Reward[64];
    uint8_t Aetheryte[12];
    uint8_t FavoritePoint[3];
    uint8_t SuperFavoritePoint[1];
    uint8_t Discovery16[320];
    uint8_t Discovery32[80];
    uint8_t HowTo[32];
    uint8_t Companion[28];
    uint8_t ChocoboTaxiStand[8];
    uint8_t CutScene[91];
    uint8_t BuddyPossession[8];
    uint8_t BuddyEquip[3];
    uint8_t GCSupplyItemFlags[4];
    uint8_t GCSupplyClassLevel[11];
    char BuddyName[21];
    char BuddySkillLine[3];

    char MountList[9];

    uint8_t IsFishCatched[61];
    uint8_t IsSpotVisited[25];
    uint8_t __padding6;
    uint16_t ListFishId[18];
    uint16_t ListFishSize[18];
    uint32_t PvPPoint[3];
    uint8_t PvPRank[3];
    uint8_t PvPSkillPoint[3];
    uint8_t __padding9;
    uint8_t __padding10;
    uint32_t PvPAction[10];
    uint8_t BeastReputationRank[8];
    uint8_t __padding11;
    uint16_t BeastReputationValue[8];
    uint8_t RandomContentRewardCounter[9];
    uint16_t CycleTime[2];
    uint8_t PoseEmoteType[5];
    uint8_t __padding_;
    uint8_t Unknown[5];
    uint8_t SystemFlag[2];
    uint8_t ContentsNoteComplete[6];
    uint8_t GuildOrderClassClearFlags[28];
    uint8_t Unknown2[5];
    uint8_t RelicNoteCount[10];
    uint8_t RelicNoteFlags[2];
    uint8_t AdventureNoteSpotClearFlags[19];
    uint32_t Frontline01RankCount[3];
    uint16_t Frontline01WeeklyRankCount[3];
    uint8_t MobHuntOrderState[3];
    uint8_t MobHuntKillsCount[29];
    uint8_t TripleTriadAcquireFlags[20];
    uint8_t SecretRecipeAcquireFlags[2];

    uint8_t padding[100];
  };


  /**
  * Structural representation of the packet sent by the server
  * to set a players stats
  */
  struct FFXIVIpcBaseParam : FFXIVIpcBasePacket< BaseParam >
  {
    uint32_t Param[50];
    uint32_t OriginalParam[6];
  };

  /**
  * Structural representation of the packet sent by the server
  * to set an actors current owner
  */
  struct FFXIVIpcFirstAttack : FFXIVIpcBasePacket< FirstAttack >
  {
    uint8_t Type;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint64_t Id;
  };

  /**
  * Structural representation of the packet sent by the server
  * to set a players state
  */
  struct FFXIVIpcPlayerStateFlags : FFXIVIpcBasePacket< Condition >
  {
    uint8_t flags[12];
    uint32_t padding;
  };

  /**
  * Structural representation of the packet sent by the server
  * containing current class information
  */
  struct FFXIVIpcPlayerStatusUpdate : FFXIVIpcBasePacket< PlayerStatusUpdate >
  {
    uint8_t ClassJob;
    uint8_t __padding1;
    uint16_t Lv;
    uint16_t Lv1;
    uint16_t LvSync;
    uint32_t Exp;
    uint32_t RestPoint;
  };

  struct FFXIVIpcChangeClass : FFXIVIpcBasePacket< ChangeClass >
  {
    uint8_t ClassJob;
    uint8_t Penalty;
    uint8_t Login;
    uint8_t __padding1;
    uint16_t Lv;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t BorrowAction[10];
    uint8_t PhysicalBonus[6];
  };

  struct FFXIVIpcStatus : FFXIVIpcBasePacket< Status >
  {
    Common::StatusWork effect[30];
  };

  /**
  * Structural representation of the packet sent by the server
  * to update a players appearance
  */
  struct FFXIVIpcEquip : FFXIVIpcBasePacket< Equip >
  {
    uint64_t MainWeapon;
    uint64_t SubWeapon;
    uint8_t CrestEnable;
    uint8_t __padding1;
    uint16_t PatternInvalid;
    uint32_t Equipment[10];
  };

;

  struct ZoneProtoDownEquipWork
  {
    uint32_t CatalogId;
    uint32_t Pattern;
    uint64_t Signature;
    uint8_t HQ;
    uint8_t Stain;

    struct ZoneProtoDownMateriaWork
    {
      uint16_t Type;
      uint8_t Grade;
    } Materia[5];
  };

  struct FFXIVIpcInspect : FFXIVIpcBasePacket< Inspect >
  {
    uint8_t ObjType;
    uint8_t Sex;
    uint8_t ClassJob;
    uint8_t Lv;
    uint8_t LvSync;
    uint8_t __padding1;
    uint16_t Title;
    uint8_t GrandCompany;
    uint8_t GrandCompanyRank;
    uint8_t Flag;
    uint8_t __padding2;
    uint64_t Crest;
    uint8_t CrestEnable;
    uint8_t __padding3;
    uint8_t __padding4;
    uint8_t __padding5;
    uint64_t MainWeaponModelId;
    uint64_t SubWeaponModelId;
    uint16_t PatternInvalid;
    uint8_t Rank;
    uint8_t __padding6;
    uint32_t Exp;
    uint8_t ItemLv;
    uint8_t __padding7;
    uint8_t __padding8;
    uint8_t __padding9;
    ZoneProtoDownEquipWork Equipment[14];
    char Name[32];
    uint8_t PSNId[17];
    uint8_t Customize[26];
    uint8_t __padding10;
    uint8_t __padding11;
    uint8_t __padding12;
    uint32_t ModelId[10];
    uint8_t MasterName[32];
    uint8_t SkillLv[3];
    uint8_t __padding13;
    uint32_t BaseParam[50];
  };

  struct FFXIVIpcName : FFXIVIpcBasePacket< Name >
  {
    uint64_t contentId;
    char name[32];
  };

  struct ZoneProtoDownItemStorage
  {
    uint32_t storageId;
    uint16_t type;
    int16_t index;
    uint32_t containerSize;
  };

  struct ZoneProtoDownNormalItem
  {
    uint16_t storageId;
    uint16_t containerIndex;
    uint32_t stack;
    uint32_t catalogId;
    uint64_t signatureId;
    uint8_t flags;
    uint8_t __padding1;
    uint16_t durability;
    uint16_t refine;
    uint8_t stain;
    uint8_t __padding2;
    uint32_t pattern;
    uint16_t materiaType[5];
    uint8_t materiaGrade[5];
    uint8_t buffer[5];
  };

  struct ZoneProtoDownGilItem
  {
    uint16_t storageId;
    uint16_t containerIndex;
    uint32_t stack;
    uint8_t subquarity;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t catalogId;
    uint16_t buffer[4];
  };

  /**
  * Structural representation of the packet sent by the server
  * to update a players appearance
  */
  struct FFXIVIpcNormalItem : FFXIVIpcBasePacket< NormalItem >
  {
    uint32_t contextId;
    ZoneProtoDownNormalItem item;
  };

  struct FFXIVIpcItemSize : FFXIVIpcBasePacket< ItemSize >
  {
    uint32_t contextId;
    int32_t size;
    uint32_t storageId;
  };

  struct FFXIVIpcItemStorage : FFXIVIpcBasePacket< ItemStorage >
  {
    uint32_t contextId;
    ZoneProtoDownItemStorage storage;
  };

  struct FFXIVIpcGilItem : FFXIVIpcBasePacket< GilItem >
  {
    uint32_t contextId;
    ZoneProtoDownGilItem item;
  };

  struct FFXIVIpcItemOperationBatch : FFXIVIpcBasePacket< ItemOperationBatch >
  {
    uint32_t contextId;
    uint32_t operationId;
    uint8_t operationType;
    uint8_t errorType;
    uint8_t packetNum;
  };

  struct FFXIVIpcItemOperation : FFXIVIpcBasePacket< ItemOperation >
  {
    uint32_t contextId;
    uint8_t operationType;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t srcEntity;
    uint32_t srcStorageId;
    int16_t srcContainerIndex;
    uint8_t __padding4;
    uint8_t __padding5;
    uint32_t srcStack;
    uint32_t srcCatalogId;
    uint32_t dstEntity;
    uint32_t dstStorageId;
    int16_t dstContainerIndex;
    uint8_t __padding6;
    uint8_t __padding7;
    uint32_t dstStack;
    uint32_t dstCatalogId;
  };


  /**
  * Structural representation of the packet sent by the server
  * to start an event, not actually playing it, but registering
  */
  struct FFXIVIpcEventStart : FFXIVIpcBasePacket< PushEventState >
  {
    uint64_t targetId;
    uint32_t handlerId;
    uint8_t event;
    uint8_t flags;
    uint8_t __padding1;
    uint8_t __padding2;
    uint32_t eventArg;
  };

  /**
  * Structural representation of the packet sent by the server
  * to fill a huntin log entry
  */
  struct FFXIVIpcMonsterNoteCategory : FFXIVIpcBasePacket< MonsterNoteCategory >
  {
    uint32_t contextId;
    uint8_t currentRank;
    uint8_t categoryIndex;
    uint8_t killCount[40];
    uint8_t __padding1;
    uint8_t __padding2;
    uint64_t completeFlags;
    uint32_t isNewFlags;
  };

  template< int ArgCount >
  struct FFXIVIpcMapMarkerN
  {
    uint8_t numOfMarkers;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t iconIds[ArgCount];
    uint32_t layoutIds[ArgCount];
    uint32_t handlerIds[ArgCount];
  };

  struct FFXIVIpcMapMarker2 : FFXIVIpcBasePacket< MapMarker2 >, FFXIVIpcMapMarkerN< 2 > {};
  struct FFXIVIpcMapMarker4 : FFXIVIpcBasePacket< MapMarker4 >, FFXIVIpcMapMarkerN< 4 > {};
  struct FFXIVIpcMapMarker8 : FFXIVIpcBasePacket< MapMarker8 >, FFXIVIpcMapMarkerN< 8 > {};
  struct FFXIVIpcMapMarker16 : FFXIVIpcBasePacket< MapMarker16 >, FFXIVIpcMapMarkerN< 16 > {};
  struct FFXIVIpcMapMarker32 : FFXIVIpcBasePacket< MapMarker32 >, FFXIVIpcMapMarkerN< 32 > {};
  struct FFXIVIpcMapMarker64 : FFXIVIpcBasePacket< MapMarker64 >, FFXIVIpcMapMarkerN< 64 > {};
  struct FFXIVIpcMapMarker128 : FFXIVIpcBasePacket< MapMarker128 >, FFXIVIpcMapMarkerN< 128 > {};

  template< int ArgCount >
  struct FFXIVIpcBattleTalkN
  {
    uint32_t handlerId;
    uint64_t talkerId;
    uint8_t kind;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t nameId;
    uint32_t battleTalkId;
    uint32_t time;
    uint8_t numOfArgs;
    uint8_t __padding4;
    uint8_t __padding5;
    uint8_t __padding6;
    uint32_t args[ArgCount];
  };

  struct FFXIVIpcBattleTalkHeader : FFXIVIpcBasePacket< BattleTalkHeader >, FFXIVIpcBattleTalkN< 1 > {};
  struct FFXIVIpcBattleTalk2 : FFXIVIpcBasePacket< BattleTalk2 >, FFXIVIpcBattleTalkN< 2 > {};
  struct FFXIVIpcBattleTalk4 : FFXIVIpcBasePacket< BattleTalk4 >, FFXIVIpcBattleTalkN< 4 > {};
  struct FFXIVIpcBattleTalk8 : FFXIVIpcBasePacket< BattleTalk8 >, FFXIVIpcBattleTalkN< 8 > {};

  template< int ArgCount >
  struct FFXIVIpcEventLogMessageN
  {
    uint32_t handlerId;
    uint32_t messageId;
    uint8_t numOfArgs;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t args[ArgCount];
    uint32_t unknown_1;
  };

  struct FFXIVIpcEventLogMessageHeader : FFXIVIpcBasePacket< EventLogMessageHeader >, FFXIVIpcEventLogMessageN< 1 > {};
  struct FFXIVIpcEventLogMessage2 : FFXIVIpcBasePacket< EventLogMessage2 >, FFXIVIpcEventLogMessageN< 2 > {};
  struct FFXIVIpcEventLogMessage4 : FFXIVIpcBasePacket< EventLogMessage4 >, FFXIVIpcEventLogMessageN< 4 > {};
  struct FFXIVIpcEventLogMessage8 : FFXIVIpcBasePacket< EventLogMessage8 >, FFXIVIpcEventLogMessageN< 8 > {};
  struct FFXIVIpcEventLogMessage16 : FFXIVIpcBasePacket< EventLogMessage16 >, FFXIVIpcEventLogMessageN< 16 > {};
  struct FFXIVIpcEventLogMessage32 : FFXIVIpcBasePacket< EventLogMessage32 >, FFXIVIpcEventLogMessageN< 32 > {};

  template< int ArgCount >
  struct FFXIVIpcUpdateEventSceneN
  {
    uint32_t handlerId;
    uint16_t sceneId;
    uint8_t numOfArgs;
    uint8_t __padding1;
    uint32_t args[ArgCount];
  };

  struct FFXIVIpcUpdateEventSceneHeader : FFXIVIpcBasePacket< UpdateEventSceneHeader >, FFXIVIpcUpdateEventSceneN< 1 > {};
  struct FFXIVIpcUpdateEventScene2 : FFXIVIpcBasePacket< UpdateEventScene2 >, FFXIVIpcUpdateEventSceneN< 2 > {};
  struct FFXIVIpcUpdateEventScene4 : FFXIVIpcBasePacket< UpdateEventScene4 >, FFXIVIpcUpdateEventSceneN< 4 > {};
  struct FFXIVIpcUpdateEventScene8 : FFXIVIpcBasePacket< UpdateEventScene8 >, FFXIVIpcUpdateEventSceneN< 8 > {};
  struct FFXIVIpcUpdateEventScene16 : FFXIVIpcBasePacket< UpdateEventScene16 >, FFXIVIpcUpdateEventSceneN< 16 > {};
  struct FFXIVIpcUpdateEventScene32 : FFXIVIpcBasePacket< UpdateEventScene32 >, FFXIVIpcUpdateEventSceneN< 32 > {};
  struct FFXIVIpcUpdateEventScene64 : FFXIVIpcBasePacket< UpdateEventScene64 >, FFXIVIpcUpdateEventSceneN< 64 > {};
  struct FFXIVIpcUpdateEventScene128 : FFXIVIpcBasePacket< UpdateEventScene128 >, FFXIVIpcUpdateEventSceneN< 128 > {};
  struct FFXIVIpcUpdateEventScene255 : FFXIVIpcBasePacket< UpdateEventScene255 >, FFXIVIpcUpdateEventSceneN< 255 > {};

  template< int ArgCount >
  struct FFXIVIpcPlayEventSceneN
  {
    uint64_t actorId;
    uint32_t eventId;
    uint16_t scene;
    uint16_t padding;
    uint32_t sceneFlags;
    uint8_t paramCount;
    uint8_t padding2[3];
    uint32_t params[ArgCount];
  };

  /**
  * Structural representation of the packet sent by the server
  * to play an event
  */
  struct FFXIVIpcPlayEventSceneHeader : FFXIVIpcBasePacket< EventPlayHeader >, FFXIVIpcPlayEventSceneN< 1 > {};
  struct FFXIVIpcPlayEventScene2 : FFXIVIpcBasePacket< EventPlay2 >, FFXIVIpcPlayEventSceneN< 2 > {};
  struct FFXIVIpcPlayEventScene4 : FFXIVIpcBasePacket< EventPlay4 >, FFXIVIpcPlayEventSceneN< 4 > {};
  struct FFXIVIpcPlayEventScene8 : FFXIVIpcBasePacket< EventPlay8 >, FFXIVIpcPlayEventSceneN< 8 > {};
  struct FFXIVIpcPlayEventScene16 : FFXIVIpcBasePacket< EventPlay16 >, FFXIVIpcPlayEventSceneN< 16 > {};
  struct FFXIVIpcPlayEventScene32 : FFXIVIpcBasePacket< EventPlay32 >, FFXIVIpcPlayEventSceneN< 32 > {};
  struct FFXIVIpcPlayEventScene64 : FFXIVIpcBasePacket< EventPlay64 >, FFXIVIpcPlayEventSceneN< 64 > {};
  struct FFXIVIpcPlayEventScene128 : FFXIVIpcBasePacket< EventPlay128 >, FFXIVIpcPlayEventSceneN< 128 > {};
  struct FFXIVIpcPlayEventScene255 : FFXIVIpcBasePacket< EventPlay255 >, FFXIVIpcPlayEventSceneN< 255 > {};

  /**
  * Structural representation of the packet sent by the server
  * to play an event
  */
  struct FFXIVIpcDirectorPlayScene : FFXIVIpcBasePacket< EventPlay32 >
  {
    uint64_t actorId;
    uint32_t eventId;
    uint16_t scene;
    uint16_t padding;
    uint32_t flags;
    uint32_t param3;
    uint8_t param4;
    uint8_t padding1[3];
    uint32_t param5;
    uint8_t unknown8[0x08];
    uint8_t unknown[0x38];
  };

  /**
  * Structural representation of the packet sent by the server
  * to finish an event
  */
  struct FFXIVIpcEventFinish : FFXIVIpcBasePacket< PopEventState >
  {
    uint32_t handlerId;
    uint8_t event;
    uint8_t result;
    uint8_t __padding1;
    uint8_t __padding2;
    uint32_t eventArg;
  };

  template< int ArgCount >
  struct FFXIVIpcResumeEventSceneN
  {
    uint32_t handlerId;
    uint16_t sceneId;
    uint8_t resumeId;
    uint8_t numOfArgs;
    uint32_t args[ArgCount];
  };

  struct FFXIVIpcResumeEventSceneHeader : FFXIVIpcBasePacket< ResumeEventSceneHeader >, FFXIVIpcResumeEventSceneN< 1 > {};
  struct FFXIVIpcResumeEventScene2 : FFXIVIpcBasePacket< ResumeEventScene2 >, FFXIVIpcResumeEventSceneN< 2 > {};
  struct FFXIVIpcResumeEventScene4 : FFXIVIpcBasePacket< ResumeEventScene4 >, FFXIVIpcResumeEventSceneN< 4 > {};
  struct FFXIVIpcResumeEventScene8 : FFXIVIpcBasePacket< ResumeEventScene8 >, FFXIVIpcResumeEventSceneN< 8 > {};
  struct FFXIVIpcResumeEventScene16 : FFXIVIpcBasePacket< ResumeEventScene16 >, FFXIVIpcResumeEventSceneN< 16 > {};
  struct FFXIVIpcResumeEventScene32 : FFXIVIpcBasePacket< ResumeEventScene32 >, FFXIVIpcResumeEventSceneN< 32 > {};
  struct FFXIVIpcResumeEventScene64 : FFXIVIpcBasePacket< ResumeEventScene64 >, FFXIVIpcResumeEventSceneN< 64 > {};
  struct FFXIVIpcResumeEventScene128 : FFXIVIpcBasePacket< ResumeEventScene128 >, FFXIVIpcResumeEventSceneN< 128 > {};
  struct FFXIVIpcResumeEventScene255 : FFXIVIpcBasePacket< ResumeEventScene255 >, FFXIVIpcResumeEventSceneN< 255 > {};

  /**
  * Structural representation of the packet sent by the server
  * to send the active quests
  */
  struct FFXIVIpcQuests : FFXIVIpcBasePacket< Quests >
  {
    Common::QuestData activeQuests[30];
  };

  /**
  * Structural representation of the packet sent by the server
  * to send update a quest slot
  */
  struct FFXIVIpcQuest : FFXIVIpcBasePacket< Quest >
  {
    uint8_t index;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    Common::QuestData questInfo;
  };

  /**
  * Structural representation of the packet sent by the server
  * to send the completed quests mask
  */
  struct FFXIVIpcQuestCompleteList : FFXIVIpcBasePacket< QuestCompleteFlags >
  {
    uint8_t questCompleteMask[310];
    uint8_t unknownCompleteMask[32];
  };

  /**
  * Structural representation of the packet sent by the server
  * to finish a quest
  */
  struct FFXIVIpcQuestFinish : FFXIVIpcBasePacket< QuestCompleteFlag >
  {
    uint16_t questId;
    uint8_t flag1;
    uint8_t flag2;
    uint32_t padding;
  };

  template< int Size >
  struct FFXIVIpcNoticeN
  {
    uint32_t handlerId;
    uint8_t noticeId;
    uint8_t numOfArgs;
    uint8_t __padding1;
    uint8_t __padding2;
    uint32_t args[Size];
  };


  /*!
   * Structural representation of the packet sent by the server
   * to send a quest message
   * type 0 default
   * type 1 icon
   * type 5 status
   */
  struct FFXIVIpcNoticeHeader : FFXIVIpcBasePacket< NoticeHeader >, FFXIVIpcNoticeN< 1 > {};
  struct FFXIVIpcNotice2 : FFXIVIpcBasePacket< Notice2 >, FFXIVIpcNoticeN< 2 > {};
  struct FFXIVIpcNotice4 : FFXIVIpcBasePacket< Notice4 >, FFXIVIpcNoticeN< 4 > {};
  struct FFXIVIpcNotice8 : FFXIVIpcBasePacket< Notice8 >, FFXIVIpcNoticeN< 8 > {};
  struct FFXIVIpcNotice16 : FFXIVIpcBasePacket< Notice16 >, FFXIVIpcNoticeN< 16 > {};
  struct FFXIVIpcNotice32 : FFXIVIpcBasePacket< Notice32 >, FFXIVIpcNoticeN< 32 > {};

  struct FFXIVIpcQuestTracker : FFXIVIpcBasePacket< Tracking >
  {
    struct TrackerEntry
    {
      uint8_t active;
      uint8_t questIndex;
    } entry[5];
    uint16_t padding[3];
  };


  struct FFXIVIpcWeatherId : FFXIVIpcBasePacket< WeatherId >
  {
    uint8_t WeatherId;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    float TransitionTime;
  };

  /**
  * Structural representation of the packet sent by the server
  * to send a unviel a map
  */
  struct FFXIVIpcDiscoveryReply : FFXIVIpcBasePacket< DiscoveryReply >
  {
    /* 0000 */ uint32_t mapPartId;
    /* 0004 */ uint32_t mapId;
  };

  struct FFXIVIpcMoveTerritory : FFXIVIpcBasePacket< MoveTerritory >
  {
    int16_t index;
    uint8_t territoryType;
    uint8_t zoneId;
    uint16_t worldId;
    uint16_t worldId1;
    int64_t landSetId;
    int64_t landId;
    int64_t landTerritoryId;
    char worldName[32];
  };

  struct FFXIVIpcMoveInstance : FFXIVIpcBasePacket< MoveInstance >
  {
    uint64_t characterId;
    uint32_t entityId;
    uint16_t worldId;
    uint16_t worldId1;
    uint64_t unknown1;
    uint64_t unknown2;
    //TODO... TO BE MAPPED
  };

  /**
  *
  */
  struct FFXIVIpcQuestRepeatFlags : FFXIVIpcBasePacket< QuestRepeatFlags >
  {
    uint8_t update;
    uint8_t repeatFlagArray[1];
  };

  /**
  *
  */
  struct DailyQuest
  {
    uint16_t questId;
    uint8_t flags;
  };

  struct FFXIVIpcDailyQuests : FFXIVIpcBasePacket< DailyQuests >
  {
    uint8_t update;
    uint8_t __padding1;
    uint8_t __padding2;
    struct DailyQuest dailyQuestArray[6];
  };


  /**
  * Structural representation of the packet sent by the server
  * to trigger content finder events
  *
  * See https://gist.github.com/Minoost/c35843c4c8a7a931f31fdaac9bce64c2
  */
  struct FFXIVIpcUpdateContent : FFXIVIpcBasePacket< UpdateContent >
  {
    uint16_t territoryType;
    uint16_t padding;
    uint32_t kind;
    uint32_t value1;
    uint32_t value2;
  };

  struct FFXIVIpcUpdateFindContent : FFXIVIpcBasePacket< UpdateFindContent >
  {
    uint32_t kind;
    uint32_t value1;
    uint32_t value2;
    uint32_t value3;
    uint32_t value4;
    uint16_t Unknown;
    uint16_t territoryType;
    uint16_t Unknown1;
    uint16_t Unknown2;
    uint16_t Unknown3;
    uint16_t Unknown4;
  };

  struct FFXIVIpcNotifyFindContentStatus : FFXIVIpcBasePacket< NotifyFindContentStatus >
  {
    uint16_t territoryType;
    uint16_t padding;
    uint8_t status;
    uint8_t tankRoleCount;
    uint8_t dpsRoleCount;
    uint8_t healerRoleCount;
    uint8_t matchingTime;
    uint8_t unknown;
    uint8_t unknown1;
    uint8_t unknown2;
    uint8_t unknown3;
  };

  /**
  * Structural representation of the packet sent by the server
  * to update contents available in duty finder or raid finder
  *
  * Do note that this packet has to come early in login phase (around initui packet)
  * or it won't be applied until you reconnect
  */
  struct FFXIVIpcContentAttainFlags : FFXIVIpcBasePacket< ContentAttainFlags >
  {
    uint8_t raidAttainFlag[28];
    uint8_t dungeonAttainFlag[18];
    uint8_t guildOrderAttainFlag[10];
    uint8_t bossBattleAttainFlag[6];
    uint8_t colosseumAttainFlag[2];
  };

  /**
  * Structural representation of the packet sent by the server
  * to update adventure in needs in duty roulette
  */
  struct FFXIVIpcContentBonus : FFXIVIpcBasePacket< ContentBonus >
  {
    // Ordered by roulette id
    uint8_t bonusRoles[8];
  };

  /**
  * Structural representation of the packet sent by the server
  * to update duty info in general
  */
  struct FFXIVIpcResponsePenalties : FFXIVIpcBasePacket< ResponsePenalties >
  {
    uint8_t penalties[2];
  };

  /**
  * Structural representation of the packet sent by the server
  * to set the gear show/hide status of a character
  */
  struct FFXIVIpcConfig : FFXIVIpcBasePacket< Config >
  {
    uint16_t flag;
  };

struct FFXIVIpcEorzeaTimeOffset : FFXIVIpcBasePacket< TimeOffset >
{
  uint64_t timestamp;
};

  /**
  * Structural representation of the packet sent by the server
  * to setMount a player
  */
  struct FFXIVIpcMount : FFXIVIpcBasePacket< Mount >
  {
    uint32_t id;
  };

  /**
  * Structural representation of the packet sent by the server
  * to setMount a player
  */
  struct FFXIVIpcDirectorVars : FFXIVIpcBasePacket< Director >
  {
    uint32_t directorId;
    uint8_t sequence;
    uint8_t flags;
    uint8_t vars[10];
  };



  struct FFXIVIpcHouseList : FFXIVIpcBasePacket< HouseList >
  {
    Common::LandIdent LandSetId;
    uint32_t Subdivision;
    uint32_t unknown1;
    Common::House Houses[30];
  };

  struct FFXIVIpcHouse : FFXIVIpcBasePacket< House >
  {
    uint16_t Block;
    uint16_t __padding1;
    uint16_t __padding2;
    uint16_t __padding3;
    Common::House House;
  };

  struct FFXIVIpcYardObjectList : FFXIVIpcBasePacket< YardObjectList >
  {
    uint8_t PacketIndex;
    uint8_t PacketEnd;
    uint8_t PacketEnd1;
    uint8_t PacketEnd2;
    Common::Furniture YardObjects[400];
  };

  struct FFXIVIpcYardObject : FFXIVIpcBasePacket< YardObject >
  {
    uint8_t PacketIndex;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    Common::Furniture YardObject;
  };

  struct FFXIVIpcInterior : FFXIVIpcBasePacket< Interior >
  {
    uint16_t Window;
    uint16_t WindowColor;
    uint16_t Door;
    uint16_t DoorColor;
    uint32_t Interior[10];
  };

  struct FFXIVIpcHousingAuction : FFXIVIpcBasePacket< HousingAuction >
  {
    uint32_t Price;
    uint32_t Timer;
  };

  struct FFXIVIpcHousingProfile : FFXIVIpcBasePacket< HousingProfile >
  {
    Common::LandIdent LandId;
    uint64_t OwnerId;
    uint32_t Like;
    uint8_t Welcome;
    uint8_t Size;
    uint8_t Padding;
    char Name[23];
    char Greeting[193];
    char OwnerName[31];
    char FCTag[7];
  };

  struct FFXIVIpcHousingHouseName : FFXIVIpcBasePacket< HousingHouseName >
  {
    Common::LandIdent LandId;
    char Name[23];
  };

  struct FFXIVIpcHousingGreeting : FFXIVIpcBasePacket< HousingGreeting >
  {
    Common::LandIdent LandId;
    uint8_t Greeting[193];
  };

  struct FFXIVIpcCharaHousingLandData : FFXIVIpcBasePacket< CharaHousingLandData >
  {
    uint8_t Index;
    uint32_t unknown;
    Common::CharaLandData LandData;
  };

  struct FFXIVIpcCharaHousing : FFXIVIpcBasePacket< CharaHousing >
  {
    Common::CharaLandData FcLands;
    uint64_t padding;
    Common::CharaLandData CharaLands;
    uint64_t padding1;
    Common::CharaLandData apartment;
    uint64_t padding2;
    Common::CharaLandData sharedHouse[2];
  };

  struct FFXIVIpcHousingWelcome : FFXIVIpcBasePacket< HousingWelcome >
  {
    uint8_t Welcome;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    Common::LandIdent LandId;
  };

  struct FFXIVIpcFurnitureListS : FFXIVIpcBasePacket< FurnitureListS >
  {
    Common::LandIdent LandId;
    int8_t u1; //Outdoor -1 / Indoor 0 - probably indicator
    uint8_t packetNum;
    uint8_t packetTotal;
    uint8_t u2; //Outdoor 0 / Indoor 100(?)
    Common::Furniture Furnitures[100];
  };

  struct FFXIVIpcFurnitureListM : FFXIVIpcBasePacket< FurnitureListM >
  {
    Common::LandIdent LandId;
    int8_t u1; //Outdoor -1 / Indoor 0 - probably indicator
    uint8_t packetNum;
    uint8_t packetTotal;
    uint8_t u2; //Outdoor 0 / Indoor 100(?)
    Common::Furniture Furnitures[150];
  };

  struct FFXIVIpcFurnitureListL : FFXIVIpcBasePacket< FurnitureListL >
  {
    Common::LandIdent LandId;
    int8_t u1; //Outdoor -1 / Indoor 0 - probably indicator
    uint8_t packetNum;
    uint8_t packetTotal;
    uint8_t u2; //Outdoor 0 / Indoor 100(?)
    Common::Furniture Furnitures[200];
  };

  struct FFXIVIpcFurniture : FFXIVIpcBasePacket< Furniture >
  {
    uint16_t StorageId;
    uint8_t ContainerIndex;
    uint8_t __padding1;
    Common::Furniture Furniture;
  };

  struct FFXIVIpcHousingProfileList : FFXIVIpcBasePacket< HousingProfileList >
  {
    Common::LandIdent LandSetId;
    Common::SimpleProfile ProfileList[30];
  };

  struct FFXIVIpcHousingObjectTransform : FFXIVIpcBasePacket< HousingObjectTransform >
  {
    uint16_t Dir;
    uint8_t UserData1;
    uint8_t UserData2;
    uint8_t ContainerIndex;
    uint8_t __padding1;
    uint16_t Pos[3];
  };

  struct FFXIVIpcHousingObjectColor : FFXIVIpcBasePacket< HousingObjectColor >
  {
    uint8_t Color;
    uint8_t __padding1;
    uint16_t StorageId;
    uint8_t ContainerIndex;
    uint8_t UserData;
  };

  struct FFXIVIpcHousingObjectTransformMulti : FFXIVIpcBasePacket< HousingObjectTransformMulti >
  {
    Common::LandIdent LandId;
    Common::HousingLayout LayoutInfos[10];
  };

  struct FFXIVIpcHousingGetPersonalRoomProfileListResult : FFXIVIpcBasePacket< HousingGetPersonalRoomProfileListResult >
  {
    uint64_t CharacterID;
    Common::LandIdent HouseLandID;
    uint16_t TopRoomID;
    uint8_t __padding1;
    uint8_t __padding2;
    Common::HousingPersonalRoomProfileData ProfileList[15];
  };

  struct FFXIVIpcHousingGetHouseBuddyStableListResult : FFXIVIpcBasePacket< HousingGetHouseBuddyStableListResult >
  {
    uint64_t CharacterID;
    Common::LandIdent LandID;
    uint8_t Page;
    uint8_t IsMyBuddy;
    uint8_t __padding1;
    uint8_t __padding2;
    Common::HouseBuddyStableData BuddyList[15];
  };

  struct FFXIVIpcHouseTrainBuddyData : FFXIVIpcBasePacket< HouseTrainBuddyData >
  {
    uint8_t OwnerRace;
    uint8_t OwnerSex;
    uint8_t Stain;
    uint8_t Equips[3];
  };

  struct FFXIVIpcHousingObjectTransformMultiResult : FFXIVIpcBasePacket< HousingObjectTransformMultiResult >
  {
    Common::LandIdent LandId;
    uint8_t Result;
    uint8_t __padding1;
    uint16_t FixIndexes[10];
  };

  struct FFXIVIpcHousingLogWithHouseName : FFXIVIpcBasePacket< HousingLogWithHouseName >
  {
    uint32_t LogId;
    uint8_t Name[23];
  };

  struct FFXIVIpcHousingCombinedObjectStatus : FFXIVIpcBasePacket< HousingCombinedObjectStatus >
  {
    uint16_t AddressData;
    uint16_t Kind[8];
    uint8_t Step[8];
    uint8_t Status[8];
  };

  struct FFXIVIpcHouseBuddyModelData : FFXIVIpcBasePacket< HouseBuddyModelData >
  {
    uint16_t AddressData;
    uint8_t BuddyScale;
    uint8_t Stain;
    uint8_t Invisibility;
    uint8_t __padding1;
    uint8_t __padding2;
    uint8_t __padding3;
    uint32_t ModelEquips[3];
  };

  struct FFXIVIpcCreateObject : FFXIVIpcBasePacket< CreateObject >
  {
    uint8_t Index;
    uint8_t Kind;
    uint8_t Flag;
    uint8_t __padding1;
    uint32_t BaseId;
    uint32_t EntityId;
    uint32_t LayoutId;
    uint32_t ContentId;
    uint32_t OwnerId;
    uint32_t BindLayoutId;
    float Scale;
    uint16_t SharedGroupTimelineState;
    uint16_t Dir;
    uint16_t FATE;
    uint8_t PermissionInvisibility;
    uint8_t Args;
    uint32_t Args2;
    uint32_t Args3;
    Common::FFXIVARR_POSITION3 Pos;
  };

  struct FFXIVIpcDeleteObject : FFXIVIpcBasePacket< DeleteObject >
  {
    uint8_t Index;
  };

  struct FcInviteCharacter
  {
    uint64_t CharacterID;
    uint64_t OnlineStatus;
    uint8_t GrandCompanyID;
    uint8_t Region;
    uint8_t SelectRegion;
    uint8_t Identity;
    char CharacterName[32];
    uint8_t GrandCompanyRank[3];
  };

  struct FFXIVIpcGetFcInviteListResult : FFXIVIpcBasePacket< GetFcInviteListResult >
  {
    uint64_t FreeCompanyID;
    uint64_t CrestID;
    uint32_t CreateDate;
    uint8_t GrandCompanyID;
    char FcTag[7];
    FcInviteCharacter MasterCharacter;
    uint8_t __padding1;
    FcInviteCharacter InviteCharacter[3];
    char FreeCompanyName[22];
  };

  struct FFXIVIpcGetFcProfileResult : FFXIVIpcBasePacket< GetFcProfileResult >
  {
    uint64_t TargetCharacterID;
    uint64_t FreeCompanyID;
    uint64_t CrestID;
    uint64_t LandID;
    uint32_t TargetEntityID;
    uint32_t CreateDate;
    uint32_t Reputation;
    uint16_t TotalMemberCount;
    uint16_t OnlineMemberCount;
    uint16_t FcActivity;
    uint16_t FcRole;
    uint8_t FcActiveTimeFlag;
    uint8_t FcJoinRequestFlag;
    uint8_t GrandCompanyID;
    uint8_t FcStatus;
    uint8_t FcRank;
    uint8_t JoinRequestCount;
    char FreeCompanyName[22];
    char FcTag[7];
    char MasterCharacterName[32];
    char CompanyMotto[193];
    char HouseName[23];
  };

  struct FFXIVIpcGetFcHeaderResult : FFXIVIpcBasePacket< GetFcHeaderResult >
  {
    uint64_t FreeCompanyID;
    uint64_t CrestID;
    uint64_t FcPoint;
    uint64_t FcCredit;
    uint32_t Reputation;
    uint32_t NextPoint;
    uint32_t CurrentPoint;
    uint16_t TotalMemberCount;
    uint16_t OnlineMemberCount;
    uint8_t GrandCompanyID;
    uint8_t FcRank;
    char FreeCompanyName[22];
    char FcTag[7];
  };

  struct FFXIVIpcGetCompanyBoardResult : FFXIVIpcBasePacket< GetCompanyBoardResult >
  {
    uint8_t Type;
    char CompanyBoard[193];
  };

  struct FcHierarchy
  {
    uint64_t AuthorityList;
    uint16_t Count;
    uint8_t SortNo;
    char HierarchyName[46];
  };

  struct FFXIVIpcGetFcHierarchyResult : FFXIVIpcBasePacket< GetFcHierarchyResult >
  {
    char MasterCharacterName[32];
    FcHierarchy FcHierarchyList[16];
  };

  struct FcActivityList
  {
    uint64_t ID;
    uint32_t Date;
    uint32_t Param;
    uint16_t Type;
    uint8_t Sex;
    char CharacterName[32];
    char HierarchyName[46];
  };

  struct FFXIVIpcGetFcActivityListResult : FFXIVIpcBasePacket< GetFcActivityListResult >
  {
    uint16_t NextIndex;
    uint8_t Index;
    uint8_t RequestKey;
    FcActivityList ActivityList[5];
  };

  struct FcHierarchyLite
  {
    uint64_t AuthorityList;
    uint16_t Count;
    uint8_t SortNo;
  };

  struct FFXIVIpcGetFcHierarchyLiteResult : FFXIVIpcBasePacket< GetFcHierarchyLiteResult >
  {
    FcHierarchyLite FcHierarchyList[16];
  };

  struct FFXIVIpcGetCompanyMottoResult : FFXIVIpcBasePacket< GetCompanyMottoResult >
  {
    uint16_t FcActivity;
    uint16_t FcRole;
    uint8_t Type;
    uint8_t FcActiveTimeFlag;
    uint8_t FcJoinRequestFlag;
    uint8_t JoinRequestCount;
    char CompanyMotto[193];
  };

  struct FFXIVIpcGetFcParamsResult : FFXIVIpcBasePacket< GetFcParamsResult >
  {
    uint64_t CharacterID;
    uint64_t FcPoint;
    uint64_t FcCredit;
    uint64_t FcCreditAccumu;
    uint32_t CreateDate;
    uint32_t NextPoint;
    uint32_t CurrentPoint;
    uint32_t Reputation[3];
    uint8_t FcRank;
  };

  struct FFXIVIpcGetFcActionResult : FFXIVIpcBasePacket< GetFcActionResult >
  {
    uint64_t CharacterID;
    uint32_t ActiveActionList[3];
    uint32_t ActiveActionLeftTime[3];
    uint32_t StockActionList[15];
  };

  struct FFXIVIpcGetFcMemoResult : FFXIVIpcBasePacket< GetFcMemoResult >
  {
    uint64_t CharacterID;
    uint32_t UIParam;
    uint32_t UpdateDate;
    char FcMemo[97];
  };

  struct FFXIVIpcFreeCompany : FFXIVIpcBasePacket< FreeCompany >
  {
    uint64_t Crest;
    char Tag[6];
  };

  struct FFXIVIpcPcPartyResult : FFXIVIpcBasePacket< PcPartyResult >
  {
    uint32_t UpPacketNo;
    uint32_t Result;
  };

  struct FFXIVIpcPcPartyUpdate : FFXIVIpcBasePacket< PcPartyUpdate >
  {
    uint64_t ExecuteCharacterID;
    uint64_t TargetCharacterID;
    uint8_t ExecuteIdentity;
    uint8_t TargetIdentity;
    uint8_t UpdateStatus;
    uint8_t Count;
    char ExecuteCharacterName[32];
    char TargetCharacterName[32];
  };

  struct FFXIVIpcPartyRecruitResult : FFXIVIpcBasePacket< PartyRecruitResult >
  {
    uint64_t TargetCharacterID;
    uint64_t Param;
    uint32_t Type;
    uint32_t Result;
    uint8_t Identity;
    char TargetName[32];
  };

  struct ZoneProtoDownStatusWork
  {
    uint16_t Id;
    int16_t SystemParam;
    float Time;
    uint32_t Source;
  };

  struct ZoneProtoDownPartyMember
  {
    char Name[32];
    uint64_t CharaId;
    uint32_t EntityId;
    uint32_t ParentEntityId;
    uint8_t Valid;
    uint8_t ClassJob;
    uint8_t Sex;
    uint8_t Role;
    uint8_t Lv;
    uint8_t LvSync;
    uint8_t ObjType;
    uint8_t BuddyCommand;
    uint32_t Hp;
    uint32_t HpMax;
    uint16_t Mp;
    uint16_t MpMax;
    uint16_t Tp;
    uint16_t TerritoryType;
    uint32_t PetEntityId;
    ZoneProtoDownStatusWork Status[30];
  };

  struct FFXIVIpcUpdateParty : FFXIVIpcBasePacket< UpdateParty >
  {
    ZoneProtoDownPartyMember Member[8];
    uint64_t PartyID;
    uint64_t ChatChannel;
    uint8_t LeaderIndex;
    uint8_t PartyCount;
    uint8_t __padding1;
    uint8_t __padding2;
    ZoneProtoDownStatusWork PetStatus[30];
  };

  struct ZoneProtoDownMemberPos
  {
    uint8_t Valid;
    uint8_t __padding1;
    uint16_t Pos[3];
  };

  struct FFXIVIpcPartyPos : FFXIVIpcBasePacket< PartyPos >
  {
    ZoneProtoDownMemberPos Member[8];
  };

  struct FFXIVIpcGrandCompany : FFXIVIpcBasePacket< GrandCompany >
  {
    uint8_t ActiveCompanyId;
    uint8_t MaelstromRank;
    uint8_t TwinAdderRank;
    uint8_t ImmortalFlamesRank;
  };
}
