#pragma once

#include <stdint.h>

namespace Sapphire::Network::Packets
{
  namespace LobbyPackets
  {
    ////////////////////////////////////////////////////////////////////////////////
    /// Lobby Connection IPC Codes
    /**
    * Server IPC Lobby Type Codes.
    */
    enum ServerLobbyIpcType : uint16_t
    {
      SyncReply = 0x0001,
      NackReply = 0x0002,
      LoginReply = 0x000C,
      ServiceLoginReply = 0x000D,
      CharaMakeReply = 0x000E,
      GameLoginReply = 0x000F,
      UpdateRetainerSlotsReply = 0x0010,
      DistWorldInfo = 0x0015,
      XiCharacterInfo = 0x0016,
      DistRetainerInfo = 0x0017,

      DebugNullRepl = 0x1F4,
      DebugLoginRepl = 0x1F5,

    };
  }

  namespace WorldPackets::Server
  {
  ////////////////////////////////////////////////////////////////////////////////
  /// Zone Connection IPC Codes
  /**
  * Server IPC Zone Type Codes.
  */
  enum ServerZoneIpcType : uint16_t
  {
      SyncReply = 0x0065, // was 0x0065
      LoginReply = 0x0066, // was 0x0066
      ChatToChannel = 0x0067, // was 0x0067
      RegionInfo = 0x0069, // was 0x0069
      MoveTerritory = 0x006A, // was 0x006A
      MoveInstance = 0x006B, // was 0x006B
      AllienceInviteReplyResult = 0x006C, // was 0x0079
      SetPSNId = 0x0073, // was 0x0073
      SetBillingTime = 0x0075, // was 0x0075
      AllienceInviteResult = 0x007A, // was 0x0078
      UpdateContent = 0x007B, // was 0x2E4
      SuccessFindContentAsMember5 = 0x007C, // was 0x2E6
      Unknown007D = 0x007D, // NEW IN 3.4
      Unknown007F = 0x007F, // NEW IN 3.4
      FinishContentMatchToClient = 0x0080, // was 0x0339
      Unknown0081 = 0x0081, // NEW IN 3.4
      Unknown0082 = 0x0082, // was 0x007A
      Unknown0083 = 0x0083, // was 0x007B
      Unknown0084 = 0x0084, // was 0x007C
      InviteResult = 0x009D, // was 0x00C9
      InviteReplyResult = 0x009E, // was 0x00CA
      InviteUpdate = 0x009F, // was 0x00CB
      GetCommonlistResult = 0x00A0, // was 0x00CC
      GetCommonlistDetailResult = 0x00A1, // was 0x00CD
      SetProfileResult = 0x00A2, // was 0x00CE
      GetProfileResult = 0x00A3, // was 0x00CF
      GetSearchCommentResult = 0x00A4, // was 0x00D0
      GetCharacterNameResult = 0x00A5, // was 0x00D1
      ChatChannelResult = 0x00A6, // was 0x00D2
      SendSystemMessage = 0x00A7, // was 0x00D3
      SendLoginMessage = 0x00A8, // was 0x00D4
      UpdateOnlineStatus = 0x00A9, // was 0x00D5
      GetRecruitSearchListResult = 0x00AA, // was 0x00D7
      GetRecruitDetailResult = 0x00AB, // was 0x00D8
      RequestItemResult = 0x00AC, // was 0x00D9
      AllianceReadyCheckResult = 0x00AD, // was 0x00DA
      GetFcJoinRequestCommentResult = 0x00AE, // was 0x00DB
      PcPartyResult = 0x00AF, // was 0x00DC
      PcPartyUpdate = 0x00B0, // was 0x00DD
      Unknown00B1 = 0x00B1, // NEW IN 3.4
      Unknown00B2 = 0x00B2, // NEW IN 3.4
      InviteCancelResult = 0x00B3, // was 0x00DE
      BlacklistAddResult = 0x00B4, // was 0x00E1
      BlacklistRemoveResult = 0x00B5, // was 0x00E2
      GetBlacklistResult = 0x00B6, // was 0x00E3
      FriendlistRemoveResult = 0x00B9, // was 0x00E6
      PcSearchResult = 0x00BB, // was 0x00EB
      LinkshellResult = 0x00BC, // was 0x00F0
      GetLinkshellListResult = 0x00BD, // was 0x00F1
      LetterResult = 0x00BE, // was 0x00FA
      GetLetterMessageResult = 0x00BF, // was 0x00FB
      GetLetterMessageDetailResult = 0x00C0, // was 0x00FC
      GetLetterStatusResult = 0x00C1, // was 0x00FD
      ItemSearchResult = 0x00C2, // was 0x0104
      GetItemSearchListResult = 0x00C3, // was 0x0105
      GetRetainerListResult = 0x00C4, // was 0x0106
      BuyMarketRetainerResult = 0x00C5, // was 0x0107
      MarketStorageUpdate = 0x00C6, // was 0x0108
      GetItemHistoryResult = 0x00C7, // was 0x0109
      GetRetainerSalesHistoryResult = 0x00C8, // was 0x010A
      MarketRetainerUpdate = 0x00C9, // was 0x010B
      CatalogSearchResult = 0x00CA, // was 0x010C
      FreeCompanyResult = 0x00CB, // was 0x010E
      GetFcStatusResult = 0x00CC, // was 0x010F
      GetFcInviteListResult = 0x00CD, // was 0x0110
      GetFcProfileResult = 0x00CE, // was 0x0111
      GetFcHeaderResult = 0x00CF, // was 0x0112
      GetCompanyBoardResult = 0x00D0, // was 0x0113
      GetFcHierarchyResult = 0x00D1, // was 0x0114
      GetFcActivityListResult = 0x00D2, // was 0x0115
      GetFcHierarchyLiteResult = 0x00D3, // was 0x0116
      GetCompanyMottoResult = 0x00D4, // was 0x0117
      GetFcParamsResult = 0x00D5, // was 0x0118
      PartyRecruitResult = 0x00D6, // was 0x00D6
      GetFcActionResult = 0x00D7, // was 0x0119
      GetFcMemoResult = 0x00D8, // was 0x011A
      HudParam = 0x00DC, // was 0x0140
      Status = 0x00DD, // was 0x0148
      FreeCompany = 0x00DE, // was 0x0149
      RecastGroup = 0x00DF, // was 0x014A
      UpdateAlliance = 0x00E0, // was 0x014B
      PartyPos = 0x00E1, // was 0x014C
      AlliancePos = 0x00E2, // was 0x014D
      GrandCompany = 0x00E4, // was 0x014F
      ActorMove = 0x00F4, // was 0x0192
      Transfer = 0x00F5, // was 0x0193
      Warp = 0x00F6, // was 0x0194
      RequestCast = 0x00F8, // was 0x0196
      UpdateParty = 0x00FA, // was 0x0199
      HateList = 0x00FB, // was 0x019B
      HaterList = 0x00FC, // was 0x019C
      CreateObject = 0x00FD, // was 0x019D
      DeleteObject = 0x00FE, // was 0x019E
      PlayerStatusUpdate = 0x00FF, // was 0x019F
      PlayerStatus = 0x0100, // was 0x01A0
      BaseParam = 0x0101, // was 0x01A1
      FirstAttack = 0x0102, // was 0x01A2
      Condition = 0x0103, // was 0x01A3
      ChangeClass = 0x0104, // was 0x01A4
      Equip = 0x0105, // was 0x01A5
      Inspect = 0x0106, // was 0x01A6
      Name = 0x0107, // was 0x01A7
      AttachMateriaRequest = 0x0108, // was 0x01A9
      RetainerList = 0x0109, // was 0x01AA
      RetainerData = 0x010A, // was 0x01AB
      MarketPriceHeader = 0x010B, // was 0x01AC
      MarketPrice = 0x010C, // was 0x01AD
      ItemStorage = 0x010D, // was 0x01AE
      NormalItem = 0x010E, // was 0x01AF
      ItemSize = 0x010F, // was 0x01B0
      ItemOperationBatch = 0x0110, // was 0x01B1
      ItemOperation = 0x0111, // was 0x01B2
      GilItem = 0x0112, // was 0x01B3
      TradeCommand = 0x0113, // was 0x01B4
      ItemMessage = 0x0114, // was 0x01B5
      UpdateItem = 0x0115, // was 0x01B6
      AliasItem = 0x0116, // was 0x01B7
      OpenTreasure = 0x0117, // was 0x01B8
      LootRight = 0x0118, // was 0x01B9
      LootActionResult = 0x0119, // was 0x01BA
      GameLog = 0x011A, // was 0x01BB
      TreasureOpenRight = 0x011B, // was 0x01BC
      LootItems = 0x011C, // was 0x01BE
      CreateTreasure = 0x011D, // was 0x01BF
      TreasureFadeOut = 0x011E, // was 0x01C0
      MonsterNoteCategory = 0x011F, // was 0x01C1
      EventPlayHeader = 0x0120, // was 0x01C2
      EventPlay2 = 0x0121, // was 0x01C3
      InfoGMCommandResult = 0x0122, // was 0x0122
      EventPlay4 = 0x0123, // was 0x01C4
      EventPlay8 = 0x0124, // was 0x01C5
      EventPlay16 = 0x0125, // was 0x01C6
      EventPlay32 = 0x0126, // was 0x01C7
      EventPlay64 = 0x0127, // was 0x01C8
      EventPlay128 = 0x0128, // was 0x01C9
      EventPlay255 = 0x0129, // was 0x01CA
      DebugActorData = 0x012A, // was 0x01CB
      PushEventState = 0x012B, // was 0x01CC
      SyncTagHeader = 0x012C, // was 0x012C
      SyncTag32 = 0x012D, // was 0x012D
      SyncTag64 = 0x012E, // was 0x012E
      SyncTag128 = 0x012F, // was 0x012F
      SyncTag256 = 0x0130, // was 0x0130
      SyncTag512 = 0x0132, // was 0x0132
      SyncTag768 = 0x0133, // was 0x0133
      SyncTag1024 = 0x0134, // was 0x0134
      SyncTag1536 = 0x0135, // was 0x0135
      SyncTag2048 = 0x0136, // was 0x0136
      SyncTag3072 = 0x0137, // was 0x0137
      PopEventState = 0x0138, // was 0x01CD
      UpdateEventSceneHeader = 0x0139, // was 0x01CE
      UpdateEventScene2 = 0x013A, // was 0x01CF
      UpdateEventScene4 = 0x013B, // was 0x01D0
      UpdateEventScene8 = 0x013C, // was 0x01D1
      UpdateEventScene16 = 0x013D, // was 0x01D2
      UpdateEventScene32 = 0x013E, // was 0x01D3
      UpdateEventScene64 = 0x013F, // was 0x01D4
      UpdateEventScene128 = 0x0140, // was 0x01D5
      ActionIntegrity = 0x0141, // was 0x0141
      Order = 0x0142, // was 0x0142
      OrderMySelf = 0x0143, // was 0x0143
      OrderTarget = 0x0144, // was 0x0144
      Resting = 0x0145, // was 0x0145
      ActionResult1 = 0x0146, // was 0x0146
      ActionResult = 0x0147, // was 0x0147
      UpdateEventScene255 = 0x0148, // was 0x01D6
      ResumeEventSceneHeader = 0x0149, // was 0x01D7
      ResumeEventScene2 = 0x014A, // was 0x01D8
      ResumeEventScene4 = 0x014B, // was 0x01D9
      ResumeEventScene8 = 0x014C, // was 0x01DA
      ResumeEventScene16 = 0x014D, // was 0x01DB
      ResumeEventScene32 = 0x014E, // was 0x01DC
      ResumeEventScene64 = 0x014F, // was 0x01DD
      ResumeEventScene128 = 0x0150, // was 0x01DE
      ResumeEventScene255 = 0x0151, // was 0x01DF
      Quests = 0x0152, // was 0x01E0
      Quest = 0x0153, // was 0x01E1
      QuestCompleteFlags = 0x0154, // was 0x01E2
      QuestCompleteFlag = 0x0155, // was 0x01E3
      Guildleves = 0x0156, // was 0x01E4
      Guildleve = 0x0157, // was 0x01E5
      LeveCompleteFlags = 0x0158, // was 0x01E6
      LeveCompleteFlag = 0x0159, // was 0x01E7
      NoticeHeader = 0x015A, // was 0x01E8
      Notice2 = 0x015B, // was 0x01E9
      Notice4 = 0x015C, // was 0x01EA
      Notice8 = 0x015D, // was 0x01EB
      Notice16 = 0x015E, // was 0x01EC
      Notice32 = 0x015F, // was 0x01ED
      Tracking = 0x0160, // was 0x01EE
      IsMarket = 0x0161, // was 0x01EF
      LegacyQuestCompleteFlags = 0x0162, // was 0x01F0
      ResumeEventSceneHeaderStr = 0x0163, // was 0x01F1
      ResumeEventSceneStr32 = 0x0164, // was 0x01F2
      LogText = 0x0165, // was 0x01F3
      BigData = 0x0166, // was 0x01F6
      DebugOrderHeader = 0x0167, // was 0x01F7
      DebugOrder2 = 0x0168, // was 0x01F8
      DebugOrder4 = 0x0169, // was 0x01F9
      DebugOrder8 = 0x016A, // was 0x01FA
      DebugOrder16 = 0x016B, // was 0x01FB
      DebugOrder32 = 0x016C, // was 0x01FC
      DebugActionRange = 0x016D, // was 0x01FD
      ResumeEventSceneHeaderNumStr = 0x016E, // was 0x01FE
      ResumeEventScene2Str = 0x016F, // was 0x01FF
      Mount = 0x0170, // was 0x0200
      ResumeEventScene4Str = 0x0171, // was 0x0201
      Director = 0x0172, // was 0x0226
      DownDebugPacket = 0x0173, // was 0x0227
      EventLogMessageHeader = 0x0174, // was 0x0258
      EventLogMessage2 = 0x0175, // was 0x0259
      EventLogMessage4 = 0x0176, // was 0x025A
      EventLogMessage8 = 0x0177, // was 0x025B
      EventLogMessage16 = 0x0178, // was 0x025C
      EventLogMessage32 = 0x0179, // was 0x025D
      BattleTalkHeader = 0x017A, // was 0x0262
      BattleTalk2 = 0x017B, // was 0x0263
      BattleTalk4 = 0x017C, // was 0x0264
      BattleTalk8 = 0x017D, // was 0x0265
      EventReject = 0x017E, // was 0x026C
      MapMarker2 = 0x017F, // was 0x026D
      MapMarker4 = 0x0180, // was 0x026E
      MapMarker8 = 0x0181, // was 0x026F
      MapMarker16 = 0x0182, // was 0x0270
      MapMarker32 = 0x0183, // was 0x0271
      MapMarker64 = 0x0184, // was 0x0272
      MapMarker128 = 0x0185, // was 0x0273
      BalloonTalkHeader = 0x0186, // was 0x0276
      BalloonTalk2 = 0x0187, // was 0x0277
      BalloonTalk4 = 0x0188, // was 0x0278
      BalloonTalk8 = 0x0189, // was 0x0279
      GameLoggerMessage = 0x018A, // was 0x0289
      WeatherId = 0x018B, // was 0x028A
      TitleList = 0x018C, // was 0x028B
      DiscoveryReply = 0x018D, // was 0x028C
      TimeOffset = 0x018E, // was 0x028D
      GMOrderHeader = 0x018F, // was 0x028F
      Create = 0x0190,
      Delete = 0x0191,
      ChocoboTaxiStart = 0x0192, // was 0x028E
      GMOrder2 = 0x0193, // was 0x0290
      GMOrder4 = 0x0194, // was 0x0291
      GMOrder8 = 0x0195, // was 0x0292
      GMOrder16 = 0x0196, // was 0x0293
      GMOrder32 = 0x0197, // was 0x0294
      InspectQuests = 0x0198, // was 0x029E
      InspectGuildleves = 0x0199, // was 0x029F
      InitZone = 0x019A,
      InspectReward = 0x019B, // was 0x02A0
      InspectBeastReputation = 0x019C, // was 0x02A1
      Config = 0x019D, // was 0x02C6
      NpcYell = 0x019E, // was 0x02D0
      SwapSystem = 0x019F, // was 0x02D1
      FatePcWork = 0x01A0, // was 0x02D2
      LootResult = 0x01A1, // was 0x02D3
      FateAccessCollectionEventObject = 0x01A2, // was 0x02D4
      FateSyncLimitTime = 0x01A3, // was 0x02D5
      FateDebug = 0x01A4, // was 0x02D8
      FateContextWork = 0x01A5, // was 0x02D9
      FateActiveRange = 0x01A6, // was 0x02DA
      Cabinet = 0x01A7, // was 0x02DC
      Achievement = 0x01A8, // was 0x02DD
      NotifyFindContentStatus = 0x01A9, // was 0x02DE
      ColosseumResult88 = 0x01AA, // was 0x02E0
      ContentClearFlags = 0x01AB, // was 0x02E2
      ContentAttainFlags = 0x01AC, // was 0x02E3
      Text = 0x01AD, // was 0x02E5
      SetEventBehavior = 0x01AE, // was 0x02E8
      BallistaStart = 0x01AF, // was 0x02E9
      RetainerCustomizePreset = 0x01B0, // was 0x02EA
      FateReward = 0x01B1, // was 0x02EB
      HouseList = 0x01B2, // was 0x02EC
      House = 0x01B3, // was 0x02ED
      YardObjectList = 0x01B4, // was 0x02EE
      YardObject = 0x01B5, // was 0x02F0
      Interior = 0x01B6, // was 0x02F1
      HousingAuction = 0x01B7, // was 0x02F2
      HousingProfile = 0x01B8, // was 0x02F3
      HousingHouseName = 0x01B9, // was 0x02F4
      HousingGreeting = 0x01BA, // was 0x02F5
      CharaHousingLandData = 0x01BB, // was 0x02F6
      CharaHousing = 0x01BC, // was 0x02F7
      HousingWelcome = 0x01BD, // was 0x02F8
      FurnitureListS = 0x01BE, // was 0x02F9
      FurnitureListM = 0x01BF, // was 0x02FA
      FurnitureListL = 0x01C0, // was 0x02FB
      Furniture = 0x01C1, // was 0x02FC
      VoteKickConfirm = 0x01C2, // was 0x02FD
      HousingProfileList = 0x01C3, // was 0x02FE
      HousingObjectTransform = 0x01C4, // was 0x02FF
      HousingObjectColor = 0x01C5, // was 0x0300
      HousingObjectTransformMulti = 0x01C6, // was 0x0301
      ConfusionApproach = 0x01C7, // was 0x0302
      ConfusionTurn = 0x01C8, // was 0x0303
      ConfusionTurnCancel = 0x01C9, // was 0x0304
      ConfusionCancel = 0x01CA, // was 0x0305
      MIPMemberList = 0x01CB, // was 0x0306
      HousingGetPersonalRoomProfileListResult = 0x01CC, // was 0x0307
      HousingGetHouseBuddyStableListResult = 0x01CD, // was 0x0308
      HouseTrainBuddyData = 0x01CE, // was 0x0309
      // 0x01CF..0x01D5 were other housing/buddy indices in diff; not present in original
      ContentBonus = 0x01D6, // was 0x0311
      FcChestLog = 0x01D7, // was 0x0316
      SalvageResult = 0x01D8, // was 0x0317
      Unknown01D9 = 0x01D9, // NEW IN 3.4
      DailyQuests = 0x01DA, // was 0x0320
      DailyQuest = 0x01DB, // was 0x0321
      QuestRepeatFlags = 0x01DC, // was 0x0322
      HousingObjectTransformMultiResult = 0x01DD, // was 0x032A
      HousingLogWithHouseName = 0x01DE, // was 0x032B
      TreasureHuntReward = 0x01DF, // was 0x032C
      HousingCombinedObjectStatus = 0x01E0, // was 0x032D
      HouseBuddyModelData = 0x01E1, // was 0x032E
      Marker = 0x01E7, // was 0x0334
      GroundMarker = 0x01E8, // was 0x0335
      Frontline01Result = 0x01E9, // was 0x0336
      Frontline01BaseInfo = 0x01EA, // was 0x0337
      UnMountLink = 0x01ED, // was 0x033E

      // Removed in this version (kept for reference):
      // DebugNull = 0x01F4, // removed
      // DebugLog = 0x01F5, // removed
      // EnableLogout = 0x02D6, // removed
      // LogMessage = 0x02D7, // removed
      // UpdateFindContent = 0x02DB, // removed
      // ColosseumResult44 = 0x02DF, // removed
      // ResponsePenalties = 0x02E1, // removed
      // CancelLogoutCountdown = 0x02E7, // removed
  };

  }

  ////////////////////////////////////////////////////////////////////////////////
  /// Chat Connection IPC Codes
  /**
  * Server IPC Chat Type Codes.
  */
  enum ServerChatIpcType : uint16_t
  {
    //Sync = 0x01, TODO: Fix this cuz name bullshit...
    LoginReply = 0x02,

    ChatFrom = 0x64,
    Chat = 0x65,
    TellNotFound = 0x66,
    RecvBusyStatus = 0x67,
    GetChannelMemberListResult = 0x68,
    GetChannelListResult = 0x69,
    RecvFinderStatus = 0x6A,

    JoinChannelResult = 0xC8,
    LeaveChannelResult = 0xC9
    //FreeCompanyEvent = 0x012C, // not in 2.3
  };



}

