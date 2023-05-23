#ifndef _CORE_NETWORK_PACKETS_IPCS_H
#define _CORE_NETWORK_PACKETS_IPCS_H

#include <stdint.h>

namespace Sapphire::Network::Packets
{

    ////////////////////////////////////////////////////////////////////////////////
    /// Lobby Connection IPC Codes
    /**
     * Server IPC Lobby Type Codes.
     */
    enum ServerLobbyIpcType : uint16_t
    {
        LobbyError = 0x0002,
        LobbyServiceAccountList = 0x000C,
        LobbyCharList = 0x000D,
        LobbyCharCreate = 0x000E,
        LobbyEnterWorld = 0x000F,
        LobbyServerList = 0x0015,
        LobbyRetainerList = 0x0017,

    };

    /**
     * Client IPC Lobby Type Codes.
     */
    enum ClientLobbyIpcType : uint16_t
    {
        ReqCharList = 0x0003,
        ReqEnterWorld = 0x0004,
        ClientVersionInfo = 0x0005,

        ReqCharDelete = 0x000A,
        ReqCharCreate = 0x000B,
    };

    ////////////////////////////////////////////////////////////////////////////////
    /// Zone Connection IPC Codes
    /**
     * Server IPC Zone Type Codes.
     */
    enum ServerZoneIpcType : uint16_t
    {
        Ping = 0x2c0, // updated 6.40
        Init = 0x12a, // updated 6.40

        ActorFreeSpawn = 0x8a, // updated 6.40

        InitZone = 0x347,      // updated 6.40
        PrepareZoning = 0x17a, // updated 6.40

        EffectResult = 0x3b4,      // updated 6.40
        EffectResultBasic = 0x295, // updated 6.40

        ActorControl = 0x381,       // updated 6.40
        ActorControlTarget = 0x131, // updated 6.40
        ActorControlSelf = 0x14f,   // updated 6.40
        ActorCast = 0x31c,          // updated 6.40
        ActorSetPos = 0xea,        // updated 6.40
        ActorMove = 0x2a9,          // updated 6.40
        ActorGauge = 0x164,         // updated 6.40

        /*!
         * @brief Used when resting
         */
        UpdateHpMpTp = 0x21a,    // updated 6.40
        UpdateClassInfo = 0x380, // updated 6.40

        ///////////////////////////////////////////////////

        ChatBanned = 0xF06B,
        Playtime = 0x181,  // updated 6.40
        Logout = 0x18a,   // updated 6.40
        CFNotify = 0x3e0, // updated 6.40
        CFMemberStatus = 0x0079,
        CFDutyInfo = 0xe0, // updated 6.40
        CFPlayerInNeed = 0xF07F,
        CFPreferredRole = 0x221, // updated 6.40
        CFCancel = 0x77,       // updated 6.40
        SocialRequestError = 0xF0AD,

        CFRegistered = 0x029F,          // updated 5.58h
        SocialRequestResponse = 0x323,  // updated 6.40
        SocialMessage = 0x03CB,         // updated 5.58h
        SocialMessage2 = 0x01D7,        // updated 5.58h
        CancelAllianceForming = 0xF0C6, // updated 4.2

        LogMessage = 0x113, // updated 6.40

        Chat = 0x335, // updated 6.40
        PartyChat = 0x0065,

        WorldVisitList = 0xF0FE, // added 4.5

        SocialList = 0x281, // updated 6.40

        ExamineSearchInfo = 0x2b0,    // updated 6.40
        UpdateSearchInfo = 0x339,     // updated 6.40
        InitSearchInfo = 0x37f,       // updated 6.40
        ExamineSearchComment = 0x314, // updated 6.40

        ServerNoticeShort = 0x0333, // updated 5.58h
        ServerNotice = 0x273,        // updated 6.40
        SystemLogMessage = 0x19b,   // updated 6.40
        SetOnlineStatus = 0xb1,    // updated 6.40

        CountdownInitiate = 0x292, // updated 6.40
        CountdownCancel = 0x2ba,   // updated 6.40

        PlayerAddedToBlacklist = 0x3be,     // updated 6.40
        PlayerRemovedFromBlacklist = 0x8b, // updated 6.40
        BlackList = 0x2ad,                   // updated 6.40

        LinkshellList = 0x287,           // updated 6.40
        CrossWorldLinkshellList = 0x358, // updated 6.40
        FellowshipList = 0x238,          // updated 6.40

        MailDeleteRequest = 0x2e3, // updated 6.40

        // 12D - 137 - constant gap between 4.5x -> 5.0
        ReqMoogleMailList = 0xF138,      // updated 5.0
        ReqMoogleMailLetter = 0xF139,    // updated 5.0
        MailLetterNotification = 0x013A, // updated 5.0

        MarketTaxRates = 0x01F8, // updated 5.35h

        MarketBoardSearchResult = 0x197,        // updated 6.40
        MarketBoardItemListingCount = 0x1a4,   // updated 6.40
        MarketBoardItemListingHistory = 0x2b4, // updated 6.40
        MarketBoardItemListing = 0xa7,        // updated 6.40
        MarketBoardPurchase = 0x120,           // updated 6.40
        ItemMarketBoardInfo = 0x3c4,           // updated 6.40

        CharaFreeCompanyTag = 0x013B,   // updated 4.5
        FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
        FreeCompanyInfo = 0x1ce,        // updated 6.40
        FreeCompanyDialog = 0x2a1,      // updated 6.40
        ExamineFreeCompanyInfo = 0x229, // updated 6.40

        FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

        StatusEffectList = 0x13f,       // updated 6.40
        EurekaStatusEffectList = 0x25d, // updated 6.40
        BossStatusEffectList = 0x1b0,    // updated 6.40
        StatusEffectList2 = 0x149,      // updated 6.40
        StatusEffectList3 = 0xe7,      // updated 6.40
        Effect = 0x3c9,                  // updated 6.40
        AoeEffect8 = 0x21e,             // updated 6.40
        AoeEffect16 = 0x34c,            // updated 6.40
        AoeEffect24 = 0x379,             // updated 6.40
        AoeEffect32 = 0x33f,            // updated 6.40
        PersistantEffect = 0xe7,       // updated 6.40

        PlaceFieldMarker = 0xd8,       // updated 6.40
        PlaceFieldMarkerPreset = 0xFFFF, // updated 6.40

        GCAffiliation = 0x159, // updated 6.40

        PlayerSpawn = 0x2cf, // updated 6.40
        NpcSpawn = 0x1c4,   // updated 6.40
        NpcSpawn2 = 0x123,  // updated 6.40

        SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

        PartyList = 0x110,          // updated 6.40
        PartyMessage = 0x374,        // updated 6.40
        HateRank = 0x22d,            // updated 6.40
        HateList = 0x22e,            // updated 6.40
        ObjectSpawn = 0x184,        // updated 6.40
        ObjectDespawn = 0xb8,      // updated 6.40
        SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
        PlayerSetup = 0x218,        // updated 6.40
        PlayerStats = 0x1a3,        // updated 6.40
        ActorOwner = 0x218,         // updated 6.40
        PlayerStateFlags = 0x37a,   // updated 6.40
        PlayerClassInfo = 0xd9,    // updated 6.40
        PlayerUpdateLook = 0x1a7,   // updated 6.40
        CharaVisualEffect = 0x1ef,  // updated 6.40

        ModelEquip = 0x297,   // updated 6.40
        Examine = 0x364,      // updated 6.40
        CharaNameReq = 0xc1, // updated 6.40

        // nb: see #565 on github
        UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
        RetainerSaleHistory = 0x16d,          // updated 6.40
        RetainerInformation = 0x39c,          // updated 6.40

        SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

        ItemInfo = 0x128,                   // updated 6.40
        ContainerInfo = 0x122,              // updated 6.40
        InventoryTransactionFinish = 0x2d9, // updated 6.40
        InventoryTransaction = 0x2e9,       // updated 6.40
        CurrencyCrystalInfo = 0x2be,        // updated 6.40

        InventoryActionAck = 0x19c,  // updated 6.40
        UpdateInventorySlot = 0x119, // updated 6.40

        HuntingLogEntry = 0xec, // updated 6.40

        EventPlay = 0xfb,    // updated 6.40
        EventPlay4 = 0x307,    // updated 6.40
        EventPlay8 = 0x252,   // updated 6.40
        EventPlay16 = 0x214,   // updated 6.40
        EventPlay32 = 0x6c,   // updated 6.40
        EventPlay64 = 0x223,   // updated 6.40
        EventPlay128 = 0x340, // updated 6.40
        EventPlay255 = 0x3dc, // updated 6.40
        EventStart = 0x1a2,    // updated 6.40
        EventFinish = 0x2b2,  // updated 6.40

        EventContinue = 0x298, // updated 6.40

        EventLinkshell = 0x1169,

        QuestActiveList = 0x11d,    // updated 6.40
        QuestUpdate = 0x92,       // updated 6.40
        QuestCompleteList = 0x36f, // updated 6.40

        QuestFinish = 0x13a,         // updated 6.40
        MSQTrackerComplete = 0x28c,  // updated 6.40
        MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

        QuestMessage = 0x0220, // updated 5.58h

        QuestTracker = 0x1b5, // updated 6.40

        Mount = 0x3c0, // updated 6.40

        DirectorVars = 0x27e,       // updated 6.40
        SomeDirectorUnk1 = 0x0084,  // updated 5.18
        SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
        SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
        SomeDirectorUnk8 = 0x028A,  // updated 5.18
        SomeDirectorUnk16 = 0x028C, // updated 5.18
        DirectorPopUp = 0x03DF,     // updated 5.58h
        DirectorPopUp4 = 0x019B,    // updated 5.58h
        DirectorPopUp8 = 0x0271,    // updated 5.58h

        CFAvailableContents = 0xF1FD, // updated 4.2

        WeatherChange = 0x1d2,   // updated 6.40
        PlayerTitleList = 0x22f, // updated 6.40
        Discovery = 0x22c,       // updated 6.40

        EorzeaTimeOffset = 0x1b8, // updated 6.40

        EquipDisplayFlags = 0x38c, // updated 6.40

        MiniCactpotInit = 0x0286, // added 5.31
        ShopMessage = 0x0287,     // updated 5.58h
        LootMessage = 0x319,       // updated 6.40
        ResultDialog = 0x1cb,     // updated 6.40
        DesynthResult = 0x1ba,    // updated 6.40

        /// Housing //////////////////////////////////////

        LandSetInitialize = 0x24d,             // updated 6.40
        LandUpdate = 0x232,                   // updated 6.40
        LandAvailability = 0x67,              // updated 6.40
        YardObjectSpawn = 0x1e3,              // updated 6.40
        HousingIndoorInitialize = 0x22b,      // updated 6.40
        LandPriceUpdate = 0x345,              // updated 6.40
        LandInfoSign = 0x1dc,                  // updated 6.40
        LandRename = 0xf2,                   // updated 6.40
        HousingEstateGreeting = 0x3d1,         // updated 6.40
        HousingUpdateLandFlagsSlot = 0x1b4,   // updated 6.40
        HousingLandFlags = 0x32c,             // updated 6.40
        HousingShowEstateGuestAccess = 0x36c, // updated 6.40

        HousingObjectInitialize = 0x330,     // updated 6.40
        HousingInternalObjectSpawn = 0x327, // updated 6.40

        HousingWardInfo = 0x320,   // updated 6.40
        HousingObjectMove = 0x245, // updated 6.40
        HousingObjectDye = 0x28b,  // updated 6.40

        SharedEstateSettingsResponse = 0x2d1, // updated 6.40

        LandUpdateHouseName = 0x233, // updated 6.40
        LandSetMap = 0x34b,          // updated 6.40

        CeremonySetActorAppearance = 0x362, // updated 6.40

        //////////////////////////////////////////////////

        DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
        PerformNote = 0x1df,     // updated 6.40

        DutyGauge = 0x02E5, // updated 5.58h

        // daily quest info -> without them sent,  login will take longer...
        DailyQuests = 0x11f,           // updated 6.40
        DailyQuestRepeatFlags = 0x1c0, // updated 6.40

        MapUpdate = 0x392,    // updated 6.40
        MapUpdate4 = 0x237,   // updated 6.40
        MapUpdate8 = 0xd5,   // updated 6.40
        MapUpdate16 = 0x36e,  // updated 6.40
        MapUpdate32 = 0x2df,   // updated 6.40
        MapUpdate64 = 0x2b6,  // updated 6.40
        MapUpdate128 = 0x3ac, // updated 6.40

        /// Doman Mahjong //////////////////////////////////////
        MahjongOpenGui = 0x02A4,       // only available in mahjong instance
        MahjongNextRound = 0x02BD,     // initial hands(baipai), # of riichi(wat), winds, honba, score and stuff
        MahjongPlayerAction = 0x02BE,  // tsumo(as in drawing a tile) called chi/pon/kan/riichi
        MahjongEndRoundTsumo = 0x02BF, // called tsumo
        MahjongEndRoundRon = 0x2C0,    // called ron or double ron (waiting for action must be flagged from discard packet to call)
        MahjongTileDiscard = 0x02C1,   // giri (discarding a tile.) chi(1)/pon(2)/kan(4)/ron(8) flags etc..
        MahjongPlayersInfo = 0xF2C2,   // actor id, name, rating and stuff..
        // 2C3 and 2C4 are currently unknown
        MahjongEndRoundDraw = 0x02C5, // self explanatory
        MahjongEndGame = 0x02C6,      // finished oorasu(all-last) round; shows a result screen.

        /// Airship & Submarine //////////////////////////////////////
        AirshipTimers = 0x132,            // updated 6.40
        AirshipStatus = 0x1eb,            // updated 6.40
        AirshipStatusList = 0x2cb,        // updated 6.40
        AirshipExplorationResult = 0x2c4, // updated 6.40

        SubmarineTimers = 0x2b7,            // updated 6.40
        SubmarineProgressionStatus = 0x385, // updated 6.40
        SubmarineStatusList = 0x81,        // updated 6.40
        SubmarineExplorationResult = 0x2c9, // updated 6.40

        EnvironmentControl = 0x108,         // updated 6.40
        IslandWorkshopSupplyDemand = 0x1b7, // updated 6.40

    };

    /**
     * Client IPC Zone Type Codes.
     */
    enum ClientZoneIpcType : uint16_t
    {
        PingHandler = 0x272, // updated 6.40
        InitHandler = 0x397, // updated 6.40

        FinishLoadingHandler = 0x12a, // updated 6.40

        CFCommenceHandler = 0x0381, // updated 5.58h

        CFCancelHandler = 0x02B2,    // updated 5.58h
        CFRegisterDuty = 0x01BD,     // updated 5.58h
        CFRegisterRoulette = 0x037A, // updated 5.58h
        PlayTimeHandler = 0x02B7,    // updated 5.58h
        LogoutHandler = 0xac,      // updated 6.40
        CancelLogout = 0x01e3,       // updated 6.31h
        CFDutyInfoHandler = 0xF078,  // updated 4.2

        SocialReqSendHandler = 0x00D7,  // updated 5.58h
        SocialResponseHandler = 0x023B, // updated 5.58h
        CreateCrossWorldLS = 0x035D,    // updated 5.58h

        ChatHandler = 0xd3, // updated 6.40
        PartyChatHandler = 0x0065,
        PartySetLeaderHandler = 0x036C,  // updated 5.58h
        LeavePartyHandler = 0x019D,      // updated 5.58h
        KickPartyMemberHandler = 0x0262, // updated 5.58h
        DisbandPartyHandler = 0x0276,    // updated 5.58h

        SocialListHandler = 0x0200,              // updated 6.31
        SetSearchInfoHandler = 0x3b6,           // updated 6.40
        ReqSearchInfoHandler = 0x03b0,           // updated 6.31h
        ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

        ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
        BlackListHandler = 0x010c,             // updated 6.31h
        PlayerSearchHandler = 0x037D,          // updated 5.58h

        LinkshellListHandler = 0x03B6, // updated 5.58h

        MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58h
        MarketBoardRequestItemListings = 0x0122,    // updated 5.58h
        MarketBoardSearch = 0x0082,                 // updated 5.58h
        MarketBoardPurchaseHandler = 0x323,        // updated 6.40

        ReqExamineFcInfo = 0xF37B, // updated 5.58h (prepended F. Conflicts with FinishLoadingHandler 6.38)

        FcInfoReqHandler = 0x9999, // unknown

        FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

        ReqMarketWishList = 0x00C3, // updated 5.58h

        ReqJoinNoviceNetwork = 0x0129, // updated 4.2

        ReqCountdownInitiate = 0x03e1, // updated 6.31h
        ReqCountdownCancel = 0x023a,   // updated 6.31h

        ZoneLineHandler = 0x00ce,  // updated 6.31h
        ClientTrigger = 0x1c1,    // updated 6.40
        DiscoveryHandler = 0x038B, // updated 5.58h

        SkillHandler = 0x0228,    // updated 6.40
        GMCommand1 = 0x0139,      // updated 6.40
        GMCommand2 = 0x0195,      // updated 6.40
        AoESkillHandler = 0x016f, // updated 6.40

        UpdatePositionHandler = 0xae, // updated 6.40

        InventoryModifyHandler = 0x278, // updated 6.40

        InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

        ReqPlaceHousingItem = 0x02D4, // updated 5.58h
        BuildPresetHandler = 0x0223,  // updated 5.58h

        TalkEventHandler = 0x295,         // updated 6.40
        EmoteEventHandler = 0x00B0,        // updated 5.58h
        WithinRangeEventHandler = 0x02B6,  // updated 5.58h
        OutOfRangeEventHandler = 0x00b4,   // updated 6.31h
        EnterTeriEventHandler = 0x208,    // updated 6.40
        ShopEventHandler = 0x0384,         // updated 5.58h
        ReturnEventHandler = 0x21a,       // updated 6.40
        TradeReturnEventHandler = 0x3c9,  // updated 6.40
        TradeReturnEventHandler2 = 0x023C, // updated 5.58h
        EventYield2Handler = 0x021D,       // updated 5.58h
        EventYield16Handler = 0x0207,      // updated 5.58h

        LinkshellEventHandler = 0x9999,  // unknown
        LinkshellEventHandler1 = 0x9999, // unknown

        ReqEquipDisplayFlagsChange = 0x03BC, // updated 6.30h

        LandRenameHandler = 0x028E,           // updated 5.58h
        HousingUpdateHouseGreeting = 0x0343,  // updated 5.58h
        HousingUpdateObjectPosition = 0x9999, // unknown
        HousingEditExterior = 0x027B,         // updated 5.58h
        HousingEditInterior = 0x02E3,         // updated 5.58h

        SetSharedEstateSettings = 0x00D2, // updated 5.58h

        UpdatePositionInstance = 0x346, // updated 6.40

        PerformNoteHandler = 0x0243, // updated 5.58h

        WorldInteractionHandler = 0x0274, // updated 5.58h
        Dive = 0x018C,                    // updated 6.30h
    };

    ////////////////////////////////////////////////////////////////////////////////
    /// Chat Connection IPC Codes
    /**
     * Server IPC Chat Type Codes.
     */
    enum ServerChatIpcType : uint16_t
    {
        Tell = 0x0064,              // updated for sb
        PublicContentTell = 0xF0FB, // added 4.5, this is used when receiving a /tell in PublicContent instances such as Eureka or Bozja (prepended F conflicts with TradeReturnEventHandler 6.38)
        TellErrNotFound = 0x0066,

        FreeCompanyEvent = 0x012C, // added 5.0
    };

    /**
     * Client IPC Chat Type Codes.
     */
    enum ClientChatIpcType : uint16_t
    {
        TellReq = 0x0064,
        PublicContentTellReq = 0x0326, // updated 5.35 hotfix, this is used when sending a /tell in PublicContent instances such as Eureka or Bozja
    };

}

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
