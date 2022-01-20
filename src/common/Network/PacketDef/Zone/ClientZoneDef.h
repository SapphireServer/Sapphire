#pragma once

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire::Network::Packets::WorldPackets::Client
{

struct FFXIVIpcGmCommand : FFXIVIpcBasePacket< GMCommand >
{
  uint32_t Id;
  uint32_t Arg0;
  uint32_t Arg1;
  uint32_t Arg2;
  uint32_t Arg3;
  uint64_t Target;
};

struct FFXIVIpcGmCommandName : FFXIVIpcBasePacket< GMCommandName >
{
  uint32_t Id;
  uint32_t Arg0;
  uint32_t Arg1;
  uint32_t Arg2;
  uint32_t Arg3;
  char Name[32];
};

struct FFXIVIpcClientTrigger : FFXIVIpcBasePacket< Command >
{
  uint32_t Id;
  uint32_t Arg0;
  uint32_t Arg1;
  uint32_t Arg2;
  uint32_t Arg3;
  uint64_t Target;
};

struct FFXIVIpcUpdatePosition : FFXIVIpcBasePacket< Move >
{
  float dir;
  float dirBeforeSlip;
  uint8_t flag;
  uint8_t flag2;
  uint8_t flag_unshared;
  uint8_t __padding1;
  Common::FFXIVARR_POSITION3 pos;
};
  
struct FFXIVIpcUpdatePositionInstance : FFXIVIpcBasePacket< MovePvP >
{
    float dir;
    float predictedDir;
    float dirBeforeSlip;
    uint8_t flag;
    uint8_t flag2;
    uint8_t flag_unshared;
    uint8_t __padding1;
    Common::FFXIVARR_POSITION3 pos;
    Common::FFXIVARR_POSITION3 predictedPos;
};

struct FFXIVIpcActionRequest : FFXIVIpcBasePacket< ActionRequest >
{
  uint8_t ExecProc;
  uint8_t ActionKind;
  uint8_t __padding1;
  uint8_t __padding2;
  uint32_t ActionKey;
  uint32_t RequestId;
  uint16_t Dir;
  uint16_t DirTarget;
  uint64_t Target;
  uint32_t Arg;
};

struct FFXIVIpcSelectGroundActionRequest :  FFXIVIpcBasePacket< SelectGroundActionRequest >
{
  uint8_t ExecProc;
  uint8_t ActionKind;
  uint8_t __padding1;
  uint8_t __padding2;
  uint32_t ActionKey;
  uint32_t RequestId;
  uint16_t Dir;
  uint16_t DirTarget;
  Common::FFXIVARR_POSITION3 Pos;
};

struct FFXIVIpcZoneJump : FFXIVIpcBasePacket< ZoneJump >
{
  uint32_t ExitBox;
  float X;
  float Y;
  float Z;
  int32_t LandSetIndex;
};

struct FFXIVIpcNewDiscovery : FFXIVIpcBasePacket< NewDiscovery >
{
    uint32_t LayoutId;
    float PositionX;
    float PositionY;
    float PositionZ;
};

template< uint32_t Size >
struct FFXIVIpcEventHandlerReturnN
{
  uint32_t handlerId;
  uint16_t sceneId;
  uint8_t errorCode;
  uint8_t numOfResults;
  uint32_t results[Size];
};

struct FFXIVIpcReturnEventSceneHeader : FFXIVIpcBasePacket< ReturnEventSceneHeader >, FFXIVIpcEventHandlerReturnN< 1 >
{
};

struct FFXIVIpcReturnEventScene2 :
  FFXIVIpcBasePacket< ReturnEventScene2 >,
  FFXIVIpcEventHandlerReturnN< 2 >
{
//  /* 0000 */ uint32_t eventId;
//  /* 0004 */ uint16_t scene;
//  /* 0006 */ uint16_t param1;
//  /* 0008 */ uint16_t param2;
//  /* 000A */ uint8_t pad_000A[2];
//  /* 000C */ uint16_t param3;
//  /* 000E */ uint8_t pad_000E[2];
//  /* 0010 */ uint16_t param4;
};

struct FFXIVIpcReturnEventScene4 :
  FFXIVIpcBasePacket< ReturnEventScene4 >,
  FFXIVIpcEventHandlerReturnN< 4 >
{
};

struct FFXIVIpcReturnEventScene8 :
  FFXIVIpcBasePacket< ReturnEventScene8 >,
  FFXIVIpcEventHandlerReturnN< 8 >
{
};

struct FFXIVIpcReturnEventScene16 :
  FFXIVIpcBasePacket< ReturnEventScene16 >,
  FFXIVIpcEventHandlerReturnN< 16 >
{
};

struct FFXIVIpcReturnEventScene32 :
  FFXIVIpcBasePacket< ReturnEventScene32 >,
  FFXIVIpcEventHandlerReturnN< 32 >
{
};

struct FFXIVIpcReturnEventScene64 :
  FFXIVIpcBasePacket< ReturnEventScene64 >,
  FFXIVIpcEventHandlerReturnN< 64 >
{
};

struct FFXIVIpcReturnEventScene128 :
  FFXIVIpcBasePacket< ReturnEventScene128 >,
  FFXIVIpcEventHandlerReturnN< 128 >
{
};

struct FFXIVIpcReturnEventScene255 :
  FFXIVIpcBasePacket< ReturnEventScene255 >,
  FFXIVIpcEventHandlerReturnN< 255 >
{
};

template< uint32_t Size >
struct FFXIVIpcYieldEventSceneN
{
  uint32_t handlerId;
  uint16_t sceneId;
  uint8_t yieldId;
  uint8_t numOfResults;
  uint32_t results[Size];
};

struct FFXIVIpcYieldEventSceneHeader :
  FFXIVIpcBasePacket< YieldEventSceneHeader >,
  FFXIVIpcYieldEventSceneN< 1 >
{
};

struct FFXIVIpcYieldEventScene2 :
  FFXIVIpcBasePacket< YieldEventScene2 >,
  FFXIVIpcYieldEventSceneN< 2 >
{
};

struct FFXIVIpcYieldEventScene4 :
  FFXIVIpcBasePacket< YieldEventScene4 >,
  FFXIVIpcYieldEventSceneN< 4 >
{
};

struct FFXIVIpcYieldEventScene8 :
  FFXIVIpcBasePacket< YieldEventScene8 >,
  FFXIVIpcYieldEventSceneN< 8 >
{
};

struct FFXIVIpcYieldEventScene16 :
  FFXIVIpcBasePacket< YieldEventScene16 >,
  FFXIVIpcYieldEventSceneN< 16 >
{
};

struct FFXIVIpcYieldEventScene32 :
  FFXIVIpcBasePacket< YieldEventScene32 >,
  FFXIVIpcYieldEventSceneN< 32 >
{
};

struct FFXIVIpcYieldEventScene64 :
  FFXIVIpcBasePacket< YieldEventScene64 >,
  FFXIVIpcYieldEventSceneN< 64 >
{
};

struct FFXIVIpcYieldEventScene128 :
  FFXIVIpcBasePacket< YieldEventScene128 >,
  FFXIVIpcYieldEventSceneN< 128 >
{
};

struct FFXIVIpcYieldEventScene255 :
  FFXIVIpcBasePacket< YieldEventScene255 >,
  FFXIVIpcYieldEventSceneN< 255 >
{
};

template< uint32_t Size >
struct YieldEventSceneStringN
{
  uint32_t handlerId;
  uint16_t sceneId;
  uint8_t yieldId;
  char result[Size];
};

struct FFXIVIpcYieldEventSceneStringHeader :
  FFXIVIpcBasePacket< YieldEventSceneStringHeader >,
  YieldEventSceneStringN< 1 >
{
};

struct FFXIVIpcYieldEventSceneString8 :
  FFXIVIpcBasePacket< YieldEventSceneString8 >,
  YieldEventSceneStringN< 8 >
{
};

struct FFXIVIpcYieldEventSceneString16 :
  FFXIVIpcBasePacket< YieldEventSceneString16 >,
  YieldEventSceneStringN< 16 >
{
};

struct FFXIVIpcYieldEventSceneString32 :
  FFXIVIpcBasePacket< YieldEventSceneString32 >,
  YieldEventSceneStringN< 32 >
{
};

struct FFXIVIpcYieldEventSceneIntAndString :
  FFXIVIpcBasePacket< YieldEventSceneIntAndString >
{
  uint32_t handlerId;
  uint16_t sceneId;
  uint8_t yieldId;
  uint8_t __padding1;
  uint64_t integer;
  char str[32];
};

struct FFXIVIpcEnterTerritoryHandler :
  FFXIVIpcBasePacket< StartEnterTerritoryEvent >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint16_t param1;
  /* 0006 */ uint16_t param2;
};

struct FFXIVIpcEventHandlerOutsideRange :
  FFXIVIpcBasePacket< StartOutsideRangeEvent >
{
  /* 0000 */ uint32_t param1;
  /* 0004 */ uint32_t eventId;
  /* 0008 */ Common::FFXIVARR_POSITION3 position;
};

struct FFXIVIpcEventHandlerWithinRange :
  FFXIVIpcBasePacket< StartWithinRangeEvent >
{
  /* 0000 */ uint32_t param1;
  /* 0004 */ uint32_t eventId;
  /* 0008 */ Common::FFXIVARR_POSITION3 position;
};

struct FFXIVIpcEventHandlerEmote :
  FFXIVIpcBasePacket< StartEmoteEvent >
{
  /* 0000 */ uint64_t actorId;
  /* 0008 */ uint32_t eventId;
  /* 000C */ uint16_t emoteId;
};

struct FFXIVIpcEventHandlerTalk :
  FFXIVIpcBasePacket< StartTalkEvent >
{
  /* 0000 */ uint64_t actorId;
  /* 0008 */ uint32_t eventId;
};

struct ZoneProtoUpClientPos
{
  uint32_t originEntityId;
  float pos[3];
  float dir;
};

struct FFXIVIpcPingHandler : FFXIVIpcBasePacket< Sync >
{
  uint32_t clientTimeValue;
  ZoneProtoUpClientPos position;
};

struct FFXIVIpcLoginHandler : FFXIVIpcBasePacket< Login >
{
  uint32_t clientTimeValue;
  uint32_t arg2;
  uint64_t arg3;
  uint64_t arg4;
  int32_t contentFinderStatus;
  int32_t contentFinderFlags;
  char name[32];
  char arg1[48];
};

struct FFXIVIpcFindContent : FFXIVIpcBasePacket< FindContent >
{
  uint16_t territoryType;
  uint8_t acceptHalfway;
  uint8_t language;
};

struct FFXIVIpcFind5Contents : FFXIVIpcBasePacket< Find5Contents >
{
  uint8_t acceptHalfway;
  uint8_t language;
  uint16_t territoryTypes[5];
};

struct FFXIVIpcAcceptContent : FFXIVIpcBasePacket< AcceptContent >
{
  uint8_t accept;
  uint8_t padding1;
  uint16_t territoryType;
  uint64_t territoryId;
};

struct FFXIVIpcCancelFindContent : FFXIVIpcBasePacket< CancelFindContent >
{
  uint8_t cause;
};

  struct FFXIVIpcFindContentAsRandom : FFXIVIpcBasePacket< FindContentAsRandom >
{
  uint8_t randomContentType;
  uint8_t acceptHalfway;
  uint8_t language;
};

struct FFXIVIpcRequestPenalties : FFXIVIpcBasePacket< RequestPenalties >
{
  uint8_t value; //TODO: Is this always 0?
};


struct FFXIVIpcSetSearchInfo : FFXIVIpcBasePacket< SetProfile >
{
  uint64_t OnlineStatus;
  uint64_t SelectClassID;
  uint8_t CurrentSelectClassID;
  uint8_t Region;
  char SearchComment[193];
};

struct FFXIVIpcChatTo : FFXIVIpcBasePacket< ChatTo >
{
  uint8_t type;
  char toName[32];
  char message[1024];
};

struct FFXIVIpcChatToChannel : FFXIVIpcBasePacket< ChatToChannel >
{
  uint64_t channelID;
  char message[1024];
};

struct FFXIVIpcChatHandler : FFXIVIpcBasePacket< ChatHandler >
{
  uint32_t clientTimeValue;
  ZoneProtoUpClientPos position;
  Common::ChatType chatType;
  char message[1024];
};

struct FFXIVIpcJoinChatChannel : FFXIVIpcBasePacket< JoinChatChannel >
{
  uint64_t ChannelID;
};

struct FFXIVIpcLinkshellJoin : FFXIVIpcBasePacket< LinkshellJoin >
{
  uint64_t LinkshellID;
  char MemberCharacterName[32];
};

struct FFXIVIpcLinkshellLeave : FFXIVIpcBasePacket< LinkshellLeave >
{
  uint64_t LinkshellID;
};

struct FFXIVIpcLinkshellJoinOfficial : FFXIVIpcBasePacket< LinkshellJoinOfficial >
{
  uint64_t LinkshellID;
};

struct FFXIVIpcLinkshellChangeMaster : FFXIVIpcBasePacket< LinkshellChangeMaster >
{
  uint64_t LinkshellID;
  uint64_t NextMasterCharacterID;
  char NextMasterCharacterName[32];
};

struct FFXIVIpcLinkshellKick : FFXIVIpcBasePacket< LinkshellKick >
{
  uint64_t LinkshellID;
  uint64_t LeaveCharacterID;
  char LeaveCharacterName[32];
};

struct FFXIVIpcLinkshellAddLeader : FFXIVIpcBasePacket< LinkshellAddLeader >
{
  uint64_t LinkshellID;
  uint64_t MemberCharacterID;
  char MemberCharacterName[32];
};

struct FFXIVIpcLinkshellRemoveLeader : FFXIVIpcBasePacket< LinkshellRemoveLeader >
{
  uint64_t LinkshellID;
  uint64_t MemberCharacterID;
  char MemberCharacterName[32];
};

struct FFXIVIpcLinkshellDeclineLeader : FFXIVIpcBasePacket< LinkshellDeclineLeader >
{
  uint64_t LinkshellID;
};

struct FFXIVIpcShopEventHandler : FFXIVIpcBasePacket< StartUIEvent >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint32_t param;
};

struct FFXIVIpcClientInventoryItemOperation : FFXIVIpcBasePacket< ClientItemOperation >
{
  uint32_t ContextId;
  uint8_t OperationType;
  uint8_t __padding1;
  uint8_t __padding2;
  uint8_t __padding3;
  uint32_t SrcActorId;
  uint32_t SrcStorageId;
  int16_t SrcContainerIndex;
  uint8_t __padding4;
  uint8_t __padding5;
  uint32_t SrcStack;
  uint32_t SrcCatalogId;
  uint32_t DstActorId;
  uint32_t DstStorageId;
  int16_t DstContainerIndex;
  uint8_t __padding6;
  uint8_t __padding7;
  uint32_t DstStack;
  uint32_t DstCatalogId;
};

struct FFXIVIpcHousingExteriorChange : FFXIVIpcBasePacket< HousingExteriorChange >
{
  Common::LandIdent landIdOrIndex;
  uint8_t RemoveFlags;
  uint8_t __padding1;
  uint16_t StorageId[9];
  int16_t ContainerIndex[9];
};

struct FFXIVIpcHousingPlaceYardItem : FFXIVIpcBasePacket< HousingPlaceYardItem >
{
  Common::LandIdent landIdOrIndex;
  uint16_t StorageId;
  int16_t ContainerIndex;
  Common::FFXIVARR_POSITION3 Pos;
  float Rotation;
  uint32_t UserData;
};

struct FFXIVIpcHousingInteriorChange : FFXIVIpcBasePacket< HousingInteriorChange >
{
  Common::LandIdent landIdOrIndex;
  uint16_t StorageId[10];
  int16_t ContainerIndex[10];
};

struct FFXIVIpcMarketBoardRequestItemListings : FFXIVIpcBasePacket< MarketBoardRequestItemListings >
{
  /* 0000 */ uint16_t padding1;
  /* 0002 */ uint16_t itemCatalogId;
  /* 0004 */ uint32_t padding2;
};

struct FFXIVIpcHousingHouseName : FFXIVIpcBasePacket< HousingHouseName >
{
  Common::LandIdent landId;
  char houseName[20];
};

struct FFXIVIpcHousingGreeting : FFXIVIpcBasePacket< HousingGreeting >
{
  Common::LandIdent landId;
  char greeting[193];
};

struct FFXIVIpcHousingChangeLayout : FFXIVIpcBasePacket< HousingChangeLayout >
{
  Common::LandIdent landId;
  uint8_t storageIndex;
  uint8_t __padding1;
  uint8_t __padding2;
  uint8_t __padding3;
  float posX;
  float posY;
  float posZ;
  float rotY;
};

struct FFXIVIpcHousingChangeLayoutMulti : FFXIVIpcBasePacket< HousingChangeLayoutMulti >
{
  Common::LandIdent landId;
  float posXs[10];
  float posYs[10];
  float posZs[10];
  float rotYs[10];
  uint8_t storageIndex[10];
};

struct FFXIVIpcCatalogSearch : FFXIVIpcBasePacket< CatalogSearch >
{
  uint32_t NextIndex;
  uint8_t RequestKey;
  uint8_t Type;
  uint8_t SearchCategory;
  uint8_t MinLevel;
  uint8_t MaxLevel;
  uint8_t ClassJob;
  char ItemName[121];
};

struct FFXIVIpcMarketBoardRequestItemListingInfo : FFXIVIpcBasePacket< MarketBoardRequestItemListingInfo >
{
  /* 0000 */ uint32_t catalogId;
  /* 0000 */ uint32_t requestId;
};

struct FFXIVIpcConfig : FFXIVIpcBasePacket< Config >
{
  uint16_t flag;
};

struct FFXIVIpcGetFcProfile : FFXIVIpcBasePacket< GetFcProfile >
{
  uint64_t TargetCharacterID;
  uint32_t TargetEntityID;
};

struct FFXIVIpcGetBlacklist : FFXIVIpcBasePacket< GetBlacklist >
{
  uint8_t NextIndex;
  uint8_t RequestKey;
};

struct FFXIVIpcBlacklistAdd : FFXIVIpcBasePacket< BlacklistAdd >
{
  char TargetCharacterName[32];
};

struct FFXIVIpcBlacklistRemove : FFXIVIpcBasePacket< BlacklistRemove >
{
  uint64_t TargetCharacterID;
  char TargetCharacterName[32];
};

/* 60986 */
struct FFXIVIpcInvite : FFXIVIpcBasePacket< Invite >
{
  uint8_t AuthType;
  char TargetName[32];
};


/* 60988 */
struct FFXIVIpcInviteReply : FFXIVIpcBasePacket< InviteReply >
{
  uint64_t InviteCharacterID;
  uint8_t AuthType;
  uint8_t Answer;
};

struct FFXIVIpcGetCommonlist : FFXIVIpcBasePacket< GetCommonlist >
{
  uint64_t CommunityID;
  uint16_t NextIndex;
  uint8_t ListType;
  uint8_t RequestKey;
  uint8_t RequestParam;
};

struct FFXIVIpcGetCommonlistDetail : FFXIVIpcBasePacket< GetCommonlistDetail >
{
  uint64_t DetailCharacterID;
  uint64_t CommunityID;
  uint8_t ListType;
};

struct FFXIVIpcFriendlistRemove : FFXIVIpcBasePacket< FriendlistRemove >
{
  uint64_t TargetCharacterID;
  char TargetCharacterName[32];
};

struct FFXIVIpcSetFriendlistGroup : FFXIVIpcBasePacket< SetFriendlistGroup >
{
  uint64_t TargetCharacterID;
  uint8_t group;
};

struct FFXIVIpcPcSearch : FFXIVIpcBasePacket< PcSearch >
{
  uint64_t ClassID;
  uint16_t MinLevel;
  uint16_t MaxLevel;
  uint64_t GrandCompanyID;
  uint64_t Region;
  uint64_t OnlineStatus;
  uint16_t AreaList[50];
  char CharacterName[32];
};

struct FFXIVIpcPcPartyLeave : FFXIVIpcBasePacket< PcPartyLeave >
{
  uint32_t Reserve;
};

struct FFXIVIpcPcPartyDisband : FFXIVIpcBasePacket< PcPartyDisband >
{
  uint32_t Reserve;
};

struct FFXIVIpcPcPartyKick : FFXIVIpcBasePacket< PcPartyKick >
{
  char LeaveCharacterName[32];
};

struct FFXIVIpcPcPartyChangeLeader : FFXIVIpcBasePacket< PcPartyChangeLeader >
{
  char NextLeaderCharacterName[32];
};

}
