#pragma once

#include <stdint.h>

namespace Sapphire::Network::Packets
{
  namespace LobbyPackets
  {
    ////////////////////////////////////////////////////////////////////////////////
    /// Lobby Connection IPC Codes
    /**
    * Client IPC Lobby Type Codes.
    */

    enum ClientLobbyIpcType : uint16_t
    {
      Sync = 0x0001,
      Login = 0x0002,
      ServiceLogin = 0x0003,
      GameLogin = 0x0004,
      LoginEx = 0x0005,
      ShandaLogin = 0x0006,

      CharaMake = 0x000B,
      CharaOperation = 0x000C,
      CharaRename = 0x000D,
      CharaDelete = 0x000E,
      UpdateRetainerSlots = 0x000F,

      DebugNull = 0x1F4,
      DebugLogin = 0x1F5,
      DebugLogin2 = 0x1F6,

    };
  }

  namespace WorldPackets::Client
  {
    /**
    * Client IPC Zone Type Codes.
    */
    enum ClientZoneIpcType : uint16_t
    {
      Sync = 0x0065,
      Login = 0x0066,
      ChatHandler = 0x0067,

      SetLanguage = 0x0069,
      Invite = 0xC9,
      InviteReply = 0xCA,
      GetCommonlist = 0x00CB,
      GetCommonlistDetail = 0xCC,
      SetProfile = 0x00CD,
      GetProfile = 0x00CE,
      GetSearchComment = 0xCF,
      PartyRecruitAdd = 0xD0,
      JoinChatChannel = 0xD1,
      LeaveChatChannel = 0xD2,
      PartyRecruitRemove = 0xD3,
      PartyRecruitSearch = 0xD4,
      GetRecruitSearchList = 0xD5,
      GetRecruitDetail = 0xD6,
      InviteReplyRecruitParty = 0xD7,
      PartyRecruitEdit = 0xD8,
      GetPurposeLevel = 0xD9,
      AddRequestItem = 0xDA,
      RemoveRequestItem = 0xDB,
      PcPartyLeave = 0xDC,
      PcPartyDisband = 0xDD,
      PcPartyKick = 0xDE,
      PcPartyChangeLeader = 0xDF,
      GetRequestItem = 0xE0,
      BlacklistAdd = 0xE1,
      BlacklistRemove = 0xE2,
      GetBlacklist = 0x00E3,
      GetRequestItemList = 0xE4,
      SendReadyCheck = 0xE5,
      FriendlistRemove = 0xE6,
      ReplyReadyCheck = 0xE7,
      GetPartyRecruitCount = 0xE8,
      FcAddJoinRequest = 0xE9,
      FcRemoveJoinRequest = 0xEA,
      PcSearch = 0xEB,
      GetFcJoinRequestComment = 0xEC,
      InviteCancel = 0xED,
      LinkshellJoin = 0xF0,
      LinkshellJoinOfficial = 0xF1,
      LinkshellLeave = 0xF2,
      LinkshellChangeMaster = 0xF4,
      LinkshellKick = 0xF5,
      GetLinkshellList = 0x00F6,
      LinkshellAddLeader = 0xF7,
      LinkshellRemoveLeader = 0xF8,
      LinkshellDeclineLeader = 0xF9,
      LetterSendMessage = 0xFA,
      LetterRemoveMessage = 0xFB,
      GetLetterMessage = 0xFC,
      GetLetterMessageDetail = 0xFD,
      LetterMoveAppendItem = 0xFF,
      CheckGiftMail = 0x100,
      ItemSearch = 0x104,
      GetItemSearchList = 0x105,
      GetRetainerList = 0x106,
      BuyMarketRetainer = 0x107,
      GetRetainerSalesHistory = 0x108,
      CatalogSearch = 0x109,
      FreeCompanyLeave = 0x10E,
      FreeCompanyKick = 0x10F,
      FcSetHierarchyName = 0x111,
      FcSetAuthorityList = 0x112,
      FcMoveHierarchyMember = 0x113,
      FcAddHierarchy = 0x114,
      FcRemoveHierarchy = 0x115,
      FcSortHierarchy = 0x116,
      GetFcStatus = 0x117,
      FcForceDisband = 0x118,
      GetFcInviteList = 0x119,
      GetFcProfile = 0x11A,
      GetFcHeader = 0x11B,
      SetCompanyBoard = 0x11C,
      GetCompanyBoard = 0x11D,
      GetFcHierarchy = 0x11E,
      FcChangeMaster = 0x11F,
      GetFcActivityList = 0x120,
      SetCompanyMotto = 0x121,
      GetCompanyMotto = 0x122,
      GetFcParams = 0x123,
      SetCrestID = 0x124,
      BuyFcAction = 0x125,
      FcActionCommand = 0x126,
      GetFcAction = 0x127,
      SetFcMemo = 0x128,
      GetFcMemo = 0x129,
      InfoGMCommand = 0x12A,
      DebugInfoCommand = 0x12B,
      RequestSyncTag = 0x12C,

      ZoneJump = 0x0190,
      Command = 0x191,
      PhysicalBonus = 0x193,
      NewDiscovery = 0x0194,
      TargetPosCommand = 0x195,
      ActionRequest = 0x196,
      GMCommand = 0x197,
      GMCommandName = 0x198,
      SelectGroundActionRequest = 0x199,
      Move = 0x019A,
      GMCommandBuddyName = 0x19B,
      GMCommandNameBuddyName = 0x19C,
      RequestStorageItems = 0x1A4,
      ExchangeAttachedInactiveMateria = 0x1A5,
      RetainerCustomize = 0x1A6,
      ClientItemOperation = 0x01AE,
      GearSetEquip = 0x1AF,
      HousingExteriorChange = 0x01B0,
      HousingPlaceYardItem = 0x01B1,
      HousingInteriorChange = 0x01B2,
      TradeCommand = 0x1B3,
      TreasureCheckCommand = 0x1B4,
      SelectLootAction = 0x1B5,
      OpenTreasureWithKey = 0x1B6,

      StartTalkEvent = 0x01C2,
      StartEmoteEvent = 0x01C3,
      StartWithinRangeEvent = 0x01C4,
      StartOutsideRangeEvent = 0x01C5,
      StartEnterTerritoryEvent = 0x01C6,
      StartActionResultEvent = 0x01C7,
      StartUIEvent = 0x01C8,
      StartSayEvent = 0x01C9,

      ReturnEventSceneHeader = 0x01D6,
      ReturnEventScene2 = 0x01D7,
      ReturnEventScene4 = 0x01D8,
      ReturnEventScene8 = 0x01D9,
      ReturnEventScene16 = 0x01DA,
      ReturnEventScene32 = 0x01DB,
      ReturnEventScene64 = 0x01DC,
      ReturnEventScene128 = 0x01DD,
      ReturnEventScene255 = 0x01DE,

      YieldEventSceneHeader = 0x01DF,
      YieldEventScene2 = 0x01E0,
      YieldEventScene4 = 0x01E1,
      YieldEventScene8 = 0x01E2,
      YieldEventScene16 = 0x01E3,
      YieldEventScene32 = 0x01E4,
      YieldEventScene64 = 0x01E5,
      YieldEventScene128 = 0x01E6,
      YieldEventScene255 = 0x01E7,

      YieldEventSceneStringHeader = 0x1EA,
      YieldEventSceneString8 = 0x1EB,
      YieldEventSceneString16 = 0x1EC,
      YieldEventSceneString32 = 0x1ED,
      YieldEventSceneIntAndString = 0x1EE,

      DebugNull = 0x1F4,
      DebugCommand = 0x1F5,
      DebugBnpcControl = 0x1F6,
      DebugMessage = 0x1F7,
      FindContent = 0x1F9,
      DebugFinishContent = 0x1FA,

      AcceptContent = 0x1FB,
      CancelFindContent = 0x1FC,
      Find5Contents = 0x1FD,
      FindContentAsRandom = 0x1FE,
      ChocoboTaxiPathEnd = 0x258,
      ChocoboTaxiSetStep = 0x259,
      ChocoboTaxiUnmount = 0x25A,

      Config = 0x0262,
      StartLogoutCountdown = 0x263,
      CancelLogoutCountdown = 0x264,
      FateDebugCommand = 0x265,
      ContentAction = 0x266,
      RequestPenalties = 0x267,
      Logout = 0x269,

      HousingHouseName = 0x026A,
      HousingGreeting = 0x026B,
      HousingChangeLayout = 0x026C,
      VoteKickStart = 0x26D,
      MVPRequest = 0x26E,
      HousingChangeLayoutMulti = 0x026F,

      ConfusionApproachEnd = 0x276,
      ConfusionTurnEnd = 0x277,
      MovePvP = 0x278,

      //////////////////////////////////////

      CFCommenceHandler = 0x0078, // updated 5.21 hotfix

      //CFRegisterDuty = 0x1118, // updated 5.21 hotfix

      MarketBoardRequestItemListingInfo = 0x1102, // updated 4.5
      MarketBoardRequestItemListings = 0x1103, // updated 4.5

      ReqExamineFcInfo = 0x1113, // updated 4.1

    };

  }
  ////////////////////////////////////////////////////////////////////////////////
  /// Chat Connection IPC Codes
  /**
  * Client IPC Chat Type Codes.
  */
  enum ClientChatIpcType : uint16_t
  {
    //Sync = 0x01, TODO: Fix this cuz name bullshit...
    Login = 0x02,

    ChatTo = 0x64,
    ChatToChannel = 0x65, // TODO: Fix this cuz name bullshit... -- old name: Chat
    SendBusyStatus = 0x66,
    GetChannelMemberList = 0x67,
    GetChannelList = 0x68,
    SendFinderStatus = 0x69,
    ChatToCharacterID = 0x6A,

    JoinChannel = 0xC8,
    LeaveChannel = 0xC9,
    RenameChannel = 0xCA,
    GmLogin = 0xCB,
    GmLogout = 0xCc
    //TellReq = 0x0064,
  };


}

