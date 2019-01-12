#ifndef _COMMONACTORCONTROL_H
#define _COMMONACTORCONTROL_H

#include <cstdint>
#include <vector>

#include "CommonGen.h"

// +---------------------------------------------------------------------------
// The following enumerations are structures to require their type be included.
// They are also defined within the Sapphire::Common namespace to avoid collisions.
// +---------------------------------------------------------------------------
namespace Sapphire::Network::ActorControl
{

enum ActorControlType : uint16_t
{
    /*! Toggles weapon status -> Sheathed/UnSheathed
        \param param1 status 0|1 */
      ToggleWeapon = 0x00,
    /*! Toggles Autoattack status on/off
        \param param1 status 0|1 */
      AutoAttack = 0x01,
    SetStatus = 0x02,
    CastStart = 0x03,
    ToggleAggro = 0x04,
    ClassJobChange = 0x05,
    DefeatMsg = 0x06,
    GainExpMsg = 0x07,

    LevelUpEffect = 0x0A,

    ExpChainMsg = 0x0C,
    HpSetStat = 0x0D,
    DeathAnimation = 0x0E,
    CastInterrupt = 0x0F,

    ActionStart = 0x11,

    StatusEffectGain = 0x14,
    StatusEffectLose = 0x15,

    HPFloatingText = 0x17,
    UpdateRestedExp = 0x018,
    Unk2 = 0x19,

    Flee = 0x1B,

    Unk3 = 0x20,                  // Animation related?

    CombatIndicationShow = 0x22,

    SpawnEffect = 0x25,
    ToggleInvisible = 0x26,

    ToggleActionUnlock = 0x29,

    UpdateUiExp = 0x2B,
    DmgTakenMsg = 0x2D,

    SetTarget = 0x32,
    ToggleNameHidden = 0x36,

    LimitbreakStart = 0x47,
    LimitbreakPartyStart = 0x48,
    BubbleText = 0x49,

    DamageEffect = 0x50,
    RaiseAnimation = 0x51,
    TreasureScreenMsg = 0x57,
    SetOwnerId = 0x59,
    ItemRepairMsg = 0x5C,

    DirectorInit = 0x64,
    DirectorClear = 0x65,

    LeveStartAnim = 0x66,
    LeveStartError = 0x67,
    DirectorEObjMod = 0x6A,

    DirectorUpdate = 0x6D,

    ItemObtainMsg = 0x75,
    DutyQuestScreenMsg = 0x7B,

    ItemObtainIcon = 0x84,
    FateItemFailMsg = 0x85,
    ItemFailMsg = 0x86,
    ActionLearnMsg1 = 0x87,

    FreeEventPos = 0x8A,

    SetBGM = 0xA1,

    UnlockAetherCurrentMsg = 0xA4,

    RemoveName = 0xA8,

    ScreenFadeOut = 0xAA,

    ZoneIn = 0xC8,
    ZoneInDefaultPos = 0xC9,

    TeleportStart = 0xCB,

    TeleportDone = 0xCD,
    TeleportDoneFadeOut = 0xCE,
    DespawnZoneScreenMsg = 0xCF,

    InstanceSelectDlg = 0xD2,
    ActorDespawnEffect = 0xD4,

    CompanionUnlock = 0xFD,
    ObtainBarding = 0xFE,
    EquipBarding = 0xFF,

    CompanionMsg1 = 0x102,
    CompanionMsg2 = 0x103,
    ShowPetHotbar = 0x104,

    ActionLearnMsg = 0x109,
    ActorFadeOut = 0x10A,
    ActorFadeIn = 0x10B,
    WithdrawMsg = 0x10C,
    OrderMinion = 0x10D,
    ToggleMinion = 0x10E,
    LearnMinion = 0x10F,
    ActorFateOut1 = 0x110,

    Emote = 0x122,
    EmoteInterrupt = 0x123,

    SetPose = 0x127,

    CraftingUnk = 0x12C,

    GatheringSenseMsg = 0x130,
    PartyMsg = 0x131,
    GatheringSenseMsg1 = 0x132,

    GatheringSenseMsg2 = 0x138,

    FishingMsg = 0x140,

    FishingBaitMsg = 0x145,

    FishingReachMsg = 0x147,
    FishingFailMsg = 0x148,

    MateriaConvertMsg = 0x15E,
    MeldSuccessMsg = 0x15F,
    MeldFailMsg = 0x160,
    MeldModeToggle = 0x161,

    AetherRestoreMsg = 0x163,

    DyeMsg = 0x168,

    ToggleCrestMsg = 0x16A,
    ToggleBulkCrestMsg = 0x16B,
    MateriaRemoveMsg = 0x16C,
    GlamourCastMsg = 0x16D,
    GlamourRemoveMsg = 0x16E,

    RelicInfuseMsg = 0x179,

    AetherReductionDlg = 0x17D,

    Unk6 = 0x19C,
    EObjAnimation = 0x19D,

    SetTitle = 0x1F4,

    SetStatusIcon = 0x1F8,
    LimitBreakGauge = 0x1F9, // Max level, amount, build type (chop sound), lb type(0=pve lb 1=pvp lb)
    SetHomepoint = 0x1FB,
    SetFavorite = 0x1FC,
    LearnTeleport = 0x1FD,

    OpenRecommendationGuide = 0x200,
    ArmoryErrorMsg = 0x201,

    AchievementPopup = 0x203,

    LogMsg = 0x205,                 // LogMessage?
    AchievementMsg = 0x206,

    SetItemLevel = 0x207, //updated 4.5 ( 0x209 before )

    ChallengeEntryCompleteMsg = 0x20B,
    ChallengeEntryUnlockMsg = 0x20C,

    GilTrailMsg = 0x211,

    SetMaxGearSets = 0x230,

    SetCharaGearParamUI = 0x260,
    ToggleWireframeRendering = 0x261,

    ExamineError = 0x2BF,

    GearSetEquipMsg = 0x321,

    SetFestival = 0x386, // param1: festival.exd index

    ToggleOrchestrionUnlock = 0x396,
    Dismount = 0x3A0,

    // Duty Recorder
    BeginReplayAck = 0x3A1,
    EndReplayAck = 0x3A2,

    // Housing
    ShowHousingItemUI = 0x3F7,
    ShowBuildPresetUI = 0x3E9,
    /*!
     * param1 = plot id
     */
    ShowEstateExternalAppearanceUI = 0x3EA,
    ShowEstateInternalAppearanceUI = 0x3EB,
    BuildPresetResponse = 0x3ED,

    /*!
     * param1 = u16 landid
     *          u16 slotid
     */
    RemoveExteriorHousingItem = 0x3EF,

    /*!
     * param1 = object array index
     */
    RemoveInteriorHousingItem = 0x3F1,

    /*!
     * param1 = identity shit
     *          u16 1 - container id
     *          u16 2 - plot id
     * param2 = item shit
     *          u16 1 - slot
     */
    HousingItemMoveConfirm = 0x3F9,
    OpenEstateSettingsUI = 0x3FF,
    HideAdditionalChambersDoor = 0x400,

    /*!
     * param1 = outdoor furnishings
     *          u8 0 - relocation available, 1 = available
     *          u8 1 - outoor furnishings placed
     *          u8 2 - outdoor furnishings in storeroom
     *          u8 3 - outdoor funishings limit
     * param2 = indoor furnishings
     *          u16 0 - relocation available, 1 = available
     *          u16 1 - furnishings placed
     * param3 = indoor furnishings
     *          u16 0 - in storeroom
     *          u16 1 - indoor furnishings limit
     */
    HousingStoreroomStatus = 0x419,

    // PvP Duel
    SetPvPState = 0x5E0, // param3 must be 6 to engage a duel (hardcoded in the client)
    EndDuelSession = 0x5E1, // because someone went oob?
    StartDuelCountdown = 0x5E2, // begins a countdown; also does some duel bgm thing.
    StartDuel = 0x5E3, // actually all it does is set the challenger actor id;
    DuelResultScreen = 0x5E4, // win/lose thing, also reset a target id just like what EndDuelSession does.

    // Duty Action
    SetDutyActionId = 0x5E8,  // ContentExAction
    SetDutyActionHud = 0x5E9, // disable/enable
    SetDutyActionActive = 0x5EA,
    SetDutyActionRemaining = 0x5EB,
  };

  enum ClientTriggerType
  {
    ToggleSheathe = 0x01,
    ToggleAutoAttack = 0x02,
    ChangeTarget = 0x03,

    DismountReq = 0x65,

    RemoveStatusEffect = 0x68,
    CastCancel = 0x69,

    Return = 0xC8, // return dead / accept raise
    FinishZoning = 0xC9,
    Teleport = 0xCA,

    Examine = 0x12C,
    MarkPlayer = 0x12D, // Mark player, visible to party only
    SetTitleReq = 0x12E,
    TitleList = 0x12F,

    UpdatedSeenHowTos = 0x133,
    AllotAttribute = 0x135,

    ClearWaymarks = 0x13A,
    CameraMode = 0x13B, // param12, 1 = camera mode enable, 0 = disable
    CharaNameReq = 0x13D, // requests character name by content id
    HuntingLogDetails = 0x194,

    Timers = 0x1AB,

    DyeItem = 0x1B5,

    RequestChocoboInventory = 0x1C4,

    EmoteReq = 0x1F4,
    EmoteCancel = 0x1F6,
    PersistentEmoteCancel = 0x1F7,
    PoseChange = 0x1F9,
    PoseReapply = 0x1FA,
    PoseCancel = 0x1FB,

    AchievementCrit = 0x202,
    AchievementComp = 0x203,
    AchievementCatChat = 0x206,

    QuestJournalUpdateQuestVisibility = 0x2BE,
    QuestJournalClosed = 0x2BF,

    AbandonQuest = 0x320,

    DirectorInitFinish = 0x321,

    DirectorSync = 0x328, // unsure what exactly triggers it, starts director when returning to instance though

    EnterTerritoryEventFinished = 0x330,
    RequestInstanceLeave = 0x333, // df menu button

    AchievementCritReq = 0x3E8,
    AchievementList = 0x3E9,

    SetEstateLightingLevel = 0x40B, // param1 = light level 0 - 5 maps to UI val 5-0
    RequestHousingBuildPreset = 0x44C,
    RequestEstateExteriorRemodel = 0x044D, // param11 = land id
    RequestEstateInteriorRemodel = 0x44E,
    RequestEstateHallRemoval = 0x44F,
    RequestBuildPreset = 0x450, // no idea what this is, it gets sent with BuildPresetHandler and has the plot id in param1
    RequestLandSignFree = 0x451,
    RequestLandSignOwned = 0x452,
    RequestWardLandInfo = 0x453,
    RequestLandRelinquish = 0x454,
    RequestLandInventory = 0x0458,
    RequestHousingItemRemove = 0x0459,
    RequestEstateRename = 0x45A,
    RequestEstateEditGreeting = 0x45B,
    RequestEstateGreeting = 0x45C, // sends FFXIVIpcHousingEstateGreeting in return
    RequestEstateEditGuestAccessSettings = 0x45D,
    UpdateEstateGuestAccess = 0x45E,
    RequestEstateTagSettings = 0x45F,
    RequestEstateInventory = 0x0461,
    RequestHousingItemUI = 0x463,
    RequestSharedEstateSettings = 0x46F,
    UpdateEstateLightingLevel = 0x471,
    HousingItemSelectedInUI = 0x47E,

    CompanionAction = 0x6A4,
    CompanionSetBarding = 0x6A5,
    CompanionActionUnlock = 0x6A6,

    OpenPerformInstrumentUI = 0x71C,

    StartReplay = 0x7BC,
    EndReplay = 0x7BD, // request for restoring the original player state (actor, buff, gauge, etc..)

    OpenDuelUI = 0x898, // Open a duel ui
    DuelRequestResult = 0x899, // either accept/reject

  };

}

#endif
