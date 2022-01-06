#pragma once

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
    SetBattle = 0x04,
    /*!
     * param1 = ClassJob ID
     */
    ClassJobChange = 0x05,
    DefeatMsg = 0x06,
    GainExpMsg = 0x07,

    LevelUpEffect = 0x0A,

    ExpChainMsg = 0x0C,
    HpSetStat = 0x0D,
    DeathAnimation = 0x0E,
    CastInterrupt = 0x0F,

    /*!
     * @brief Sent when a player uses an action
     *
     * param1 Seems to be always 1 from what I've seen, needs more research
     * param2 The actionid
     * param3 The action cooldown in ms / 10
     */
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
    SetFallDamage = 0x2D,

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
    BluActionLearn = 0x63, // Displays "Action Learned!" animation. Only used for visual, doesn't actually unlock it. param1: actionId. param2: 0 = text only, 1 = text+animation. Verification needed

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

    DailyQuestSeed = 0x90, // param1 = the daily quest seed

    SetBGM = 0xA1,

    UnlockAetherCurrentMsg = 0xA4,

    RemoveName = 0xA8,

    ScreenFadeOut = 0xAA,

    Appear = 0xC8,
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
    OrderCompanion = 0x10D,
    ToggleCompanion = 0x10E,
    LearnCompanion = 0x10F,
    ActorFateOut1 = 0x110,

    Emote = 0x122,
    EmoteInterrupt = 0x123,

    SetPose = 0x127,

    /*!
     * This is used for general crafting events, I found some of them but some are missing:
     * 
     * param1 = event type, the rest of the struct depends on this param.
     *  - 18 & 19: Quicksynth result, 19 means HQ result item, item ID is param2 and is + 1 000 000 when HQ. 
     *             Quantity is param3 (possible quicksynth that gives more than one item in the future?)
     * 
     * All the other values have unkown behavior for now. 
     */
    CraftingUnk = 0x12C,

    GatheringSenseMsg = 0x130,
    PartyMsg = 0x131,
    GatheringSenseMsg1 = 0x132,

    GatheringSenseMsg2 = 0x138,

    FishingMsg = 0x140,

    FishingTotalFishCaught = 0x142,
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


    /*!
     * Sent as result of an aetherial reduction.
     * param1 = Reduced item ID + 500 000 (idk what this 500 000 is but it's always here no matter what)
     * param2 = First result item id (+ 1 000 000 if HQ)
     * param3 = First result item quantity
     * param4 = (Optional) Second result item id (+ 1 000 000 if HQ)
     * param5 = (Optional) Second result item quantity
     */ 
    AetherReductionDlg = 0x17D,

    /*!
     * param1 = state
     * param2 = actorid
     */
    EObjSetState = 0x199,
    Unk6 = 0x19C,
    EObjAnimation = 0x19D,

    SetTitle = 0x1F4,

    SetHateLetter = 0x1F7,
    SetStatusIcon = 0x1F8,
    LimitBreakGauge = 0x1F9, // Max level, amount, build type (chop sound), lb type(0=pve lb 1=pvp lb)
    SetHomepoint = 0x1FB,
    SetFavorite = 0x1FC,
    LearnTeleport = 0x1FD,

    OpenRecommendationGuide = 0x200,
    ArmoryErrorMsg = 0x201,

    AchievementPopup = 0x203,
    SetCutsceneFlag = 0x204,

    LogMsg = 0x205,                 // LogMessage?
    AchievementMsg = 0x206,

    SetItemLevel = 0x209,

    ChallengeEntryCompleteMsg = 0x20B,
    ChallengeEntryUnlockMsg = 0x20C,

    /*!
     * Sent when a player desynths an item, one packet per result type (one for consumed item, one for each obtained items, and one for exp if the player received exp)
     * param1 = result type
     *          4921 => Desynth item consumed
     *          4922 => Desynth item obtained
     *          4925 => Desynth exp obtained)
     *          3553 => Reduction item used
     *          3555 => Reduction item obtained
     * param3 = u32 item id (+100 000 if item is HQ)
     * param4 = item amount (used only for reduction it seems)
     * param5 = exp amount (x 100)
     * 
     * Idk exactly how reduce's param3 is formatted, it seems like it's item id + 500 000 but it seems too... shady.
     */
    DesynthOrReductionResult = 0x20F,

    GilTrailMsg = 0x211,

    HuntingLogRankUnlock = 0x21D,
    HuntingLogEntryUpdate = 0x21E,
    HuntingLogSectionFinish = 0x21F,
    HuntingLogRankFinish = 0x220,

    SetMaxGearSets = 0x320,

    SetCharaGearParamUI = 0x260,
    ToggleWireframeRendering = 0x261,

    ExamineError = 0x2BF,

    GearSetEquipMsg = 0x321,

    SetBait = 0x325, // param1: bait ID

    SetFestival = 0x386, // param1: festival.exd index

    ToggleOrchestrionUnlock = 0x396,

    EventBattleDialog = 0x39C,

    /*!
    * param1 = mountSpeed
    * Retail sends 12 for mount speed star 1 unlocked and 15 for setMount speed star 2 unlocked
    * This also has to be sent before mounting finishes for it to take effect
    */
    SetMountSpeed = 0x39F,

    Dismount = 0x3A1, // updated 4.5

    // Duty Recorder
    BeginReplayAck = 0x3A2,
    EndReplayAck = 0x3A3,

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

    EurekaStep = 0x73A, // alters the progress of the player on Eureka (is used for all the eureka zones)
  };

  enum PacketCommand
  {
/*  ToggleSheathe = 0x01,
    ToggleAutoAttack = 0x02,
    ChangeTarget = 0x03,

    DismountReq = 0x65,
    SpawnCompanionReq = 0x66,
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
    SetCutscene = 0x134,
    AllotAttribute = 0x135,

    ClearFieldMarkers = 0x13A,
    CameraMode = 0x13B, // param12, 1 = camera mode enable, 0 = disable
    CharaNameReq = 0x13D, // requests character name by content id
    HuntingLogDetails = 0x194,

    Timers = 0x1AB,

    DyeItem = 0x1B0, // updated 5.21

    RequestChocoboInventory = 0x1C4,

    EmoteReq = 0x1F4,
    EmoteCancel = 0x1F6,
    PersistentEmoteCancel = 0x1F7,
    //
    // * param2 = pose ID
    // *      0 = idle pose 0 (just standing)
    // *      1 = idle pose 1
    // *    2-4 = idle poses 2-4
    //
    PoseChange = 0x1F9,
    PoseReapply = 0x1FA,
    PoseCancel = 0x1FB,

    AchievementCrit = 0x202,
    AchievementComp = 0x203,
    AchievementCatChat = 0x206,

    RequestEventBattle = 0x232C,

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
*/
      DRAWN_SWORD = 0x1,
      AUTO_ATTACK = 0x2,
      TARGET_DECIDE = 0x3,
      REQUEST_ACTION = 0x64,
      CANCEL_MOUNT = 0x65,
      COMPANION = 0x66,
      COMPANION_CANCEL = 0x67,
      REQUEST_STATUS_RESET = 0x68,
      CANCEL_CAST = 0x69,
      MOUNT_LINK = 0x6A,
      UNMOUNT_LINK = 0x6B,
      BALLISTA_ACCESS = 0x6C,
      REVIVE = 0xC8,
      FINISH_LOADING = 0xC9,
      TELEPO_INQUIRY = 0xCA,
      TELEPO_INVITATION_ANSWER = 0xCB,
      TELEPO_CANCEL = 0xCC,
      RAISE_CANCEL = 0xCD,
      WARP_REPLY = 0xCE,
      REQUEST_MODE = 0xCF,
      PUBLIC_INSTANCE = 0xD0,
      NEWBIE_TELEPO_INQUIRY = 0xD1,
      INSPECT = 0x12C,
      MARKING = 0x12D,
      ACTIVE_TITLE = 0x12E,
      TITLE_LIST = 0x12F,
      BORROW_ACTION = 0x130,
      RANDOM = 0x131,
      NAME = 0x132,
      SET_HOWTO = 0x133,
      SET_CUTSCENE = 0x134,
      PHYSICAL_BONUS = 0x135,
      GROUND_MARKING = 0x136,
      CONTENTS_NOTE_REQUEST = 0x137,
      BAHAMUTGUIDE_AGREEMENT_CHECK_REPLY = 0x138,
      SET_MARKET_PRICE = 0x190,
      DEPOP_RETAINER = 0x191,
      MARKET_EDIT_START = 0x192,
      MARKET_EDIT_END = 0x193,
      MONSTER_NOTE_RANK_NEW_FLAG = 0x194,
      CHANGE_ITEM_COLOR = 0x195,
      LOAD_LEGACY_ITEM = 0x196,
      BRING_OUT_LEGACY_ITEM = 0x197,
      FCCHEST_LOAD = 0x198,
      FCCHEST_LOCK = 0x199,
      FCCHEST_UNLOCK = 0x19A,
      START_MATERIA_CRAFT = 0x19B,
      PREPARE_MATERIA_CRAFT = 0x19C,
      CANCEL_MATERIA_CRAFT = 0x19D,
      ACCEPT_MATERIA_REQUEST = 0x19E,
      CANCEL_ATTACH_MATERIA_REQUEST = 0x19F,
      CHECK_FOR_MATERIA_REQUEST = 0x1A0,
      EXCHANGE_INACTIVE_MATERIA = 0x1A1,
      DECAL_ITEM = 0x1A2,
      DECAL_MANNEQUIN = 0x1A3,
      DECAL_STORAGE_GROUP = 0x1A4,
      SELL_INACTIVE_MATERIA = 0x1A5,
      MATERIA_REQUEST_CLASS_CHANGED = 0x1A6,
      ITEM_RESYNC = 0x1A7,
      FCCHEST_GIL_DEPOSIT = 0x1A8,
      FCCHEST_GIL_TAKE = 0x1A9,
      FCCHEST_LOAD_LOG = 0x1AA,
      SET_VANITY_PATTERN = 0x1AB,
      REQUEST_RETAINER_LIST = 0x1AC,
      REMOVE_VANITY_PATTERN = 0x1AD,
      CABINET_REQUEST = 0x1AE,
      CABINET_STORAGE = 0x1AF,
      CABINET_TAKEOUT = 0x1B0,
      SALVAGE = 0x1B1,
      REQUEST_SALVAGE_SUCCESS_RATE = 0x1B2,
      MOBHUNT_RECEIPT_ORDER = 0x1B3,
      MOBHUNT_BREAK_ORDER = 0x1B4,
      EMOTE = 0x1F4,
      EMOTE_WITH_WARP = 0x1F5,
      EMOTE_CANCEL = 0x1F6,
      EMOTE_MODE_CANCEL = 0x1F7,
      EMOTE_MODE_CANCEL_WITH_WARP = 0x1F8,
      POSE_EMOTE_CONFIG = 0x1F9,
      POSE_EMOTE_WORK = 0x1FA,
      POSE_EMOTE_CANCEL = 0x1FB,
      JUMP_START = 0x258,
      JUMP_LANDING = 0x259,
      GIMMICK_JUMP_END = 0x25A,
      START_CRAFT = 0x2BC,
      FISHING = 0x2BD,
      PACKET_COMMOND_TRACKING = 0x2BE,
      PACKET_COMMOND_JOURNAL_CONFIG = 0x2BF,
      GATHERING_NOTEBOOK_START = 0x2C0,
      GATHERING_NOTEBOOK_DIVISION = 0x2C1,
      GATHERING_NOTEBOOK_AREA = 0x2C2,
      RECIPE_NOTEBOOK_START = 0x2C3,
      RECIPE_NOTEBOOK_DIVISION = 0x2C4,
      END_AUTO_CRAFT = 0x2C5,
      CANCEL_QUEST = 0x320,
      DIRECTOR_INIT_RETURN = 0x321,
      CANCEL_GUILDLEVE = 0x322,
      RETRY_GUILDLEVE = 0x323,
      START_GUILDLEVE = 0x324,
      RETIRE_GUILDLEVE = 0x325,
      CHANGE_GUILDLEVE_DIFFICULTY = 0x326,
      SYNC_DIRECTOR = 0x327,
      EVENT_HANDLER = 0x328,
      FATE_START = 0x329,
      FATE_INIT_RETURN = 0x32A,
      FATE_CREATE_CHARACTER_RETURN = 0x32B,
      FATE_SYNC_CONTEXT_WORK = 0x32C,
      FATE_LEVEL_SYNC = 0x32D,
      FATE_INIT_CHARACTER_RETURN = 0x32E,
      ACHIEVEMENT_REQUEST_RATE = 0x3E8,
      ACHIEVEMENT_REQUEST = 0x3E9,
      TROPHY_RECEPTION = 0x3EA,
      TROPHY_ACQUISITION = 0x3EB,
      HOUSING_LOCK_LAND_BY_BUILD = 0x44C,
      HOUSING_LOCK_LAND_BY_EXTERIOR = 0x44D,
      HOUSING_LOCK_LAND_BY_INTERIOR = 0x44E,
      HOUSING_LOCK_LAND_BY_BREAK = 0x44F,
      HOUSING_UNLOCK_HOUSE = 0x450,
      HOUSING_AUCTION_INFO = 0x451,
      HOUSING_GET_PROFILE = 0x452,
      HOUSING_GET_PROFILE_LIST = 0x453,
      HOUSING_RELEASE = 0x454,
      HOUSING_BUILD = 0x455,
      HOUSING_BREAK = 0x456,
      HOUSING_LOAD_PARTS = 0x457,
      HOUSING_LOAD_ROOM = 0x458,
      HOUSING_LOAD_YARD = 0x459,
      HOUSING_UNPLACE = 0x45A,
      HOUSING_HOUSE_NAME = 0x45B,
      HOUSING_GREETING = 0x45C,
      HOUSING_GREETING_BY_ADDRESS = 0x45D,
      HOUSING_WELCOME = 0x45E,
      HOUSING_EDIT_WELCOME = 0x45F,
      HOUSING_LOAD_FURNITURE = 0x460,
      HOUSING_WARP_TO_SAFE = 0x461,
      HOUSING_LAYOUTMODE = 0x462,
      HOUSING_RELEASE_PERSONAL_ROOM = 0x463,
      HOUSING_GET_PERSONAL_ROOM_PROFILE_LIST = 0x464,
      HOUSING_GET_PERSONAL_ROOM_PROFILE = 0x465,
      HOUSING_GET_BUDDY_STABLE_LIST = 0x466,
      HOUSING_TRAIN_BUDDY = 0x467,
      HOUSING_FEED_BUDDY = 0x468,
      PVP_LEARN_ACTION = 0x4B0,
      PVP_LEARN_ACTION_TRAIT = 0x4B1,
      PVP_LEARN_TRAIT = 0x4B2,
      PVP_ACTION = 0x4B3,
      PVP_RESET_REWARD = 0x4B4,
      DISCARD_TREASURE_MAP = 0x514,
      TREASURE_HUNT_GET_MAP_TIME = 0x515,
      SET_RETAINER_TASK = 0x578,
      CANCEL_RETAINER_TASK = 0x579,
      SET_VENTURE_TUTORIAL_FLAGS = 0x57A,
      SET_RETAINER_FLAGS = 0x57B,
      RELIC_NOTE_CLEAR = 0x5DC,
      RELIC_GEM_ABSORB_MATERIA = 0x5DD,
      REPAIR_ITEM = 0x640,
      REPAIR_ITEM_NPC = 0x641,
      REPAIR_STORAGE_GROUP = 0x642,
      REPAIR_STORAGE_GROUP_NPC = 0x643,
      REPAIR_MANNEQUIN = 0x644,
      REPAIR_MANNEQUIN_NPC = 0x645,
      BUDDY_ACTION = 0x6A4,
      BUDDY_EQUIP = 0x6A5,
      BUDDY_INCREASE_SKILL_LINE = 0x6A6,
      PET_COMMAND = 0x708,
      SCREEN_SHOT = 0x7D0,
      MAX = 0x7D1,

  };

}
