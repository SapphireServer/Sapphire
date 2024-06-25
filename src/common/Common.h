#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "CommonGen.h"
#include "Vector3.h"

// +---------------------------------------------------------------------------
// The following enumerations are structures to require their type be included.
// They are also defined within the Sapphire::Common namespace to avoid collisions.
// +---------------------------------------------------------------------------
namespace Sapphire::Common
{

  // 99 is the last spawn id that seems to spawn any actor
  const uint8_t MAX_DISPLAYED_ACTORS = 99;
  const uint8_t MAX_DISPLAYED_EOBJS = 40;

  const int32_t INVALID_GAME_OBJECT_ID = 0xE0000000;
  const uint64_t INVALID_GAME_OBJECT_ID64 = 0xE0000000;

  const uint16_t MAX_PLAYER_LEVEL = 60;
  const uint8_t CURRENT_EXPANSION_ID = 1;

  const uint8_t CLASSJOB_TOTAL = 34;

  const uint16_t ARRSIZE_CLASSJOB = 23u;
  const uint16_t ARRSIZE_TITLELIST = 48u;
  const uint16_t ARRSIZE_HOWTO = 32u;
  const uint16_t ARRSIZE_MINIONS = 28u;
  const uint16_t ARRSIZE_MOUNTS = 9u;
  const uint16_t ARRSIZE_DISCOVERY = 400u;
  const uint16_t ARRSIZE_QUESTCOMPLETE = 342u;
  const uint16_t ARRSIZE_AETHERYTES = 12u;
  const uint16_t ARRSIZE_UNLOCKS = 64u;
  const uint16_t ARRSIZE_ORCHESTRION = 40u;
  const uint16_t ARRSIZE_MONSTERNOTE = 12u;
  const uint16_t ARRSIZE_BORROWACTION = 10u;

  const uint8_t TOWN_COUNT = 6;

  /// Version value used in lobby encryption
  const uint16_t FFXIV_ENC_VERSION = 3000;

  /// Default service ID name
  const std::string SERVICE_ACCOUNT_DEFAULT_NAME = "FINAL FANTASY XIV";

  /// Lobby char list settings
  const uint16_t MAX_CREATE_CHARACTER = 8;
  const uint16_t MAX_CHARACTER_LIST = 8;

  /*!
   * @brief The maximum length (in ms) of a combo before it is canceled/voided.
   *
   * The client has a combo timer of about 12 seconds, with a 0.5 second grace on top for latency considerations.
   */
  const uint16_t MAX_COMBO_LENGTH = 12500;

  struct FFXIVARR_POSITION3_U16
  {
    uint16_t x;
    uint16_t y;
    uint16_t z;
  };

  struct ActiveLand
  {
    uint8_t ward;
    uint8_t plot;
  };

  enum INSTANCE_CONTENT_VOTE_TYPE : uint32_t
  {
    INSTANCE_CONTENT_VOTE_TYPE_KICK = 0x0,
    INSTANCE_CONTENT_VOTE_TYPE_GIVEUP = 0x1,
    INSTANCE_CONTENT_VOTE_TYPE_TREASURE = 0x2,
    INSTANCE_CONTENT_VOTE_TYPE_MAX = 0x3,
  };

  enum ITEM_OPERATION_TYPE : uint8_t
  {
    ITEM_OPERATION_TYPE_NONE = 0x0,
    ITEM_OPERATION_TYPE_CREATESTORAGE = 0x1,
    ITEM_OPERATION_TYPE_DELETESTORAGE = 0x2,
    ITEM_OPERATION_TYPE_COMPACTSTORAGE = 0x3,
    ITEM_OPERATION_TYPE_RESYNCSTORAGE = 0x4,
    ITEM_OPERATION_TYPE_CREATEITEM = 0x5,
    ITEM_OPERATION_TYPE_UPDATEITEM = 0x6,
    ITEM_OPERATION_TYPE_DELETEITEM = 0x7,
    ITEM_OPERATION_TYPE_MOVEITEM = 0x8,
    ITEM_OPERATION_TYPE_SWAPITEM = 0x9,
    ITEM_OPERATION_TYPE_SPLITITEM = 0xA,
    ITEM_OPERATION_TYPE_SPLITTOMERGE = 0xB,
    ITEM_OPERATION_TYPE_MERGEITEM = 0xC,
    ITEM_OPERATION_TYPE_REPAIRITEM = 0xD,
    ITEM_OPERATION_TYPE_NPC_REPAIRITEM = 0xE,
    ITEM_OPERATION_TYPE_REPAIRMANNEQUIN = 0xF,
    ITEM_OPERATION_TYPE_NPC_REPAIRMANNEQUIN = 0x10,
    ITEM_OPERATION_TYPE_REPAIRINVENTORY = 0x11,
    ITEM_OPERATION_TYPE_NPC_REPAIRINVENTORY = 0x12,
    ITEM_OPERATION_TYPE_EQUIPMANNEQUIN = 0x13,
    ITEM_OPERATION_TYPE_BRINGOUTLEGACYITEM = 0x14,
    ITEM_OPERATION_TYPE_GIVETORETAINER = 0x15,
    ITEM_OPERATION_TYPE_TAKEFROMRETAINER = 0x16,
    ITEM_OPERATION_TYPE_SETRETAINERGIL = 0x17,
    ITEM_OPERATION_TYPE_TRADECOMMAND = 0x18,
    ITEM_OPERATION_TYPE_MOVETRADE = 0x19,
    ITEM_OPERATION_TYPE_SETGILTRADE = 0x1A,
    ITEM_OPERATION_TYPE_SETTRADESTACK = 0x1B,
    ITEM_OPERATION_TYPE_UPDATEPARTNERBOX = 0x1C,
    ITEM_OPERATION_TYPE_CREATEMATERIA = 0x1D,
    ITEM_OPERATION_TYPE_ATTACHMATERIA = 0x1E,
    ITEM_OPERATION_TYPE_REMOVEMATERIA = 0x1F,
    ITEM_OPERATION_TYPE_ASKATTACHMATERIA = 0x20,
    ITEM_OPERATION_TYPE_DEBUG_ADDITEM = 0x21,
    ITEM_OPERATION_TYPE_DEBUG_SETITEM = 0x22,
    ITEM_OPERATION_TYPE_DEBUG_SETSTACK = 0x23,
    ITEM_OPERATION_TYPE_DEBUG_SETREFINE = 0x24,
    ITEM_OPERATION_TYPE_DEBUG_SETDURABILITY = 0x25,
    ITEM_OPERATION_TYPE_ALIASITEM = 0x26,
    ITEM_OPERATION_TYPE_UNALIASITEM = 0x27,
    ITEM_OPERATION_TYPE_MOVEALIAS = 0x28,
    ITEM_OPERATION_TYPE_SWAPALIAS = 0x29,
    ITEM_OPERATION_TYPE_TAKEFROMFCCHEST = 0x2A,
    ITEM_OPERATION_TYPE_FATEREWARD = 0x2B,
    ITEM_OPERATION_TYPE_QUESTREWARD = 0x2C,
    ITEM_OPERATION_TYPE_LEVEREWARD = 0x2D,
    ITEM_OPERATION_TYPE_SPECIALSHOPTRADE = 0x2E,
    ITEM_OPERATION_TYPE_CRAFTLEVETRADE = 0x2F,
    ITEM_OPERATION_TYPE_QUESTTRADE = 0x30,
    ITEM_OPERATION_TYPE_GATHERING = 0x31,
    ITEM_OPERATION_TYPE_CRAFT = 0x32,
    ITEM_OPERATION_TYPE_FISHING = 0x33,
    ITEM_OPERATION_TYPE_GCSUPPLY = 0x34,
    ITEM_OPERATION_TYPE_CABINET_TAKE = 0x35,
    ITEM_OPERATION_TYPE_CABINET_GIVE = 0x36,
    ITEM_OPERATION_TYPE_SHOPBUYBACK = 0x37,
    ITEM_OPERATION_TYPE_TELEPO = 0x38,
    ITEM_OPERATION_TYPE_VENTURE_START = 0x39,
    ITEM_OPERATION_TYPE_VENTURE_END = 0x3A,
    ITEM_OPERATION_TYPE_GARDENING_HARVEST = 0x3B,
    ITEM_OPERATION_TYPE_SALVAGE_RESULT = 0x3C,
    ITEM_OPERATION_TYPE_TREASURE_PUBLIC = 0x3D,
    ITEM_OPERATION_TYPE_TREASURE_GUILD_LEAD = 0x3E,
    ITEM_OPERATION_TYPE_TREASURE_RAID = 0x3F,
    ITEM_OPERATION_TYPE_TREASURE_MONSTER = 0x40,
    ITEM_OPERATION_TYPE_TREASURE_HUNT = 0x41,
    ITEM_OPERATION_TYPE_TREASURE_DEBUG_DROP_TABLE = 0x42,
    ITEM_OPERATION_TYPE_TREASURE_DEBUG_DROP_PACK = 0x43,
    ITEM_OPERATION_TYPE_TREASURE_DEBUG_DROP_TREASURE = 0x44,
    ITEM_OPERATION_TYPE_TREASURE_DEBUG_DROP_PACK_TREASURE = 0x45,
    ITEM_OPERATION_TYPE_RANDOM_ITEM = 0x46,
    ITEM_OPERATION_TYPE_SPECIALSHOPBUYITEM = 0x47,
    ITEM_OPERATION_TYPE_EPICWEAPON020TRADE = 0x48,
    ITEM_OPERATION_TYPE_EPICWEAPON030TREASUREMAP = 0x49,
    ITEM_OPERATION_TYPE_MATERIA_SLOT = 0x4A,
    ITEM_OPERATION_TYPE_ACHIEVEMENT_REWARD = 0x4B,
    ITEM_OPERATION_TYPE_NUM = 0x4C,
  };

  enum ITEM_OPERATION_ERROR_TYPE : uint8_t
  {
    ITEM_OPERATION_ERROR_TYPE_NONE = 0x0,
    ITEM_OPERATION_ERROR_TYPE_TERRITORYNOTFOUND = 0x1,
    ITEM_OPERATION_ERROR_TYPE_ACTORNOTFOUND = 0x2,
    ITEM_OPERATION_ERROR_TYPE_STORAGENOTFOUND = 0x3,
    ITEM_OPERATION_ERROR_TYPE_ITEMNOTFOUND = 0x4,
    ITEM_OPERATION_ERROR_TYPE_COMPACTIONFAILED = 0x5,
    ITEM_OPERATION_ERROR_TYPE_LOADINGDATA = 0x6,
    ITEM_OPERATION_ERROR_TYPE_INVALIDSTACK = 0x7,
    ITEM_OPERATION_ERROR_TYPE_INVALIDGIL = 0x8,
    ITEM_OPERATION_ERROR_TYPE_CREATEFAILED = 0x9,
    ITEM_OPERATION_ERROR_TYPE_MOVEFAILED = 0xA,
    ITEM_OPERATION_ERROR_TYPE_SWAPFAILED = 0xB,
    ITEM_OPERATION_ERROR_TYPE_MERGEFAILED = 0xC,
    ITEM_OPERATION_ERROR_TYPE_SPLITFAILED = 0xD,
    ITEM_OPERATION_ERROR_TYPE_DISCARDFAILED = 0xE,
    ITEM_OPERATION_ERROR_TYPE_EQUIPFAILED = 0xF,
    ITEM_OPERATION_ERROR_TYPE_NO_WEAPON = 0x10,
    ITEM_OPERATION_ERROR_TYPE_NO_UNDERSHIRT = 0x11,
    ITEM_OPERATION_ERROR_TYPE_NO_UNDERGARMENT = 0x12,
    ITEM_OPERATION_ERROR_TYPE_TRADELOCK = 0x13,
    ITEM_OPERATION_ERROR_TYPE_TRADEFAILED = 0x14,
    ITEM_OPERATION_ERROR_TYPE_SUCCESSMOVETRADE = 0x15,
    ITEM_OPERATION_ERROR_TYPE_PARTNERBUSY = 0x16,
    ITEM_OPERATION_ERROR_TYPE_TRADECANCELED = 0x17,
    ITEM_OPERATION_ERROR_TYPE_STORAGEFULL = 0x18,
    ITEM_OPERATION_ERROR_TYPE_GILFULL = 0x19,
    ITEM_OPERATION_ERROR_TYPE_CRYSTALFULL = 0x1A,
    ITEM_OPERATION_ERROR_TYPE_UNIQUEITEM = 0x1B,
    ITEM_OPERATION_ERROR_TYPE_EXTYPE = 0x1C,
    ITEM_OPERATION_ERROR_TYPE_NEED_DURABILITY = 0x1D,
    ITEM_OPERATION_ERROR_TYPE_HAS_VANITY = 0x1E,
    ITEM_OPERATION_ERROR_TYPE_NOTMATERIALIZABLE = 0x1F,
    ITEM_OPERATION_ERROR_TYPE_MELDFAILED = 0x20,
    ITEM_OPERATION_ERROR_TYPE_INVALIDFONDNESS = 0x21,
    ITEM_OPERATION_ERROR_TYPE_REPAIRFAILED = 0x22,
    ITEM_OPERATION_ERROR_TYPE_NEED_REPAIR_KIT_I = 0x23,
    ITEM_OPERATION_ERROR_TYPE_NEED_REPAIR_KIT_II = 0x24,
    ITEM_OPERATION_ERROR_TYPE_NEED_REPAIR_KIT_III = 0x25,
    ITEM_OPERATION_ERROR_TYPE_NEED_REPAIR_KIT_IV = 0x26,
    ITEM_OPERATION_ERROR_TYPE_NEED_REPAIR_KIT_V = 0x27,
    ITEM_OPERATION_ERROR_TYPE_OPERATIONTOOMUCH = 0x28,
    ITEM_OPERATION_ERROR_TYPE_ADDICTION_LEVEL_1 = 0x29,
    ITEM_OPERATION_ERROR_TYPE_ADDICTION_LEVEL_2 = 0x2A,
    ITEM_OPERATION_ERROR_TYPE_NUM = 0x2B,
  };

  enum GmRank : uint8_t
  {
    GM_RANK_1 = 1,
    GM_RANK_EVENT_JUNIOR = 3,
    GM_RANK_EVENT_SENIOR = 4,
    GM_RANK_SUPPORT = 5,
    GM_RANK_SENIOR = 7,
    GM_RANK_DEBUG = 90
  };

  enum ClientLanguage : uint8_t
  {
    Japanese = 1,
    English = 2,
    German = 4,
    French = 8
  };

  enum ChatFromType : uint8_t
  {
    GmTellMsg = 0x1,
  };

  enum ChatChannelType : uint16_t
  {
    CWLinkshellChat = 0x0,
    PartyChat = 0x1,
    LinkshellChat = 0x2,
    FreeCompanyChat = 0x3,
    NoviceNetworkChat = 0x4
  };

  enum BNpcType : uint8_t
  {
    Friendly = 0,
    Enemy = 4,
  };

  enum ActorKind : int32_t
  {
    ACTOR_KIND_PC = 0x0,
    ACTOR_KIND_NPC = 0x1,
    ACTOR_KIND_RETAINER = 0x2,
    ACTOR_KIND_BATTLE = 0x3,
    ACTOR_KIND_BATTLE_FRIEND = 0x4,
    ACTOR_KIND_OBJECT = 0x5,
    ACTOR_KIND_TREASURE = 0x6,
    ACTOR_KIND_GATHERING = 0x7,
    ACTOR_KIND_MAX = 0x8,
  };

  enum ObjectType : int32_t
  {
    OBJECT_TYPE_CAMERA = 0x0,
    OBJECT_TYPE_CAMERA_MAYA = 0x1,
    OBJECT_TYPE_LIGHT = 0x2,
    OBJECT_TYPE_PLAYER = 0x3,
    OBJECT_TYPE_WEAPON = 0x4,
    OBJECT_TYPE_MONSTER = 0x5,
    OBJECT_TYPE_TERRAIN = 0x6,
    OBJECT_TYPE_BG_OBJECT = 0x7,
    OBJECT_TYPE_ENV_LOCATION = 0x8,
    OBJECT_TYPE_ENV_SPACE = 0x9,
    OBJECT_TYPE_VFX_OBJECT = 0xA,
    OBJECT_TYPE_COUNT_MAX = 0xB,
  };

  enum WarpType : uint8_t
  {
    WARP_TYPE_NON = 0x0,
    WARP_TYPE_NORMAL = 0x1,
    WARP_TYPE_NORMAL_POS = 0x2,
    WARP_TYPE_EXIT_RANGE = 0x3,
    WARP_TYPE_TELEPO = 0x4,
    WARP_TYPE_REISE = 0x5,
    WARP_TYPE_ = 0x6,
    WARP_TYPE_DESION = 0x7,
    WARP_TYPE_HOME_POINT = 0x8,
    WARP_TYPE_RENTAL_CHOCOBO = 0x9,
    WARP_TYPE_CHOCOBO_TAXI = 0xA,
    WARP_TYPE_INSTANCE_CONTENT = 0xB,
    WARP_TYPE_REJECT = 0xC,
    WARP_TYPE_CONTENT_END_RETURN = 0xD,
    WARP_TYPE_TOWN_TRANSLATE = 0xE,
    WARP_TYPE_GM = 0xF,
    WARP_TYPE_LOGIN = 0x10,
    WARP_TYPE_LAYER_SET = 0x11,
    WARP_TYPE_EMOTE = 0x12,
    WARP_TYPE_HOUSING_TELEPO = 0x13,
    WARP_TYPE_DEBUG = 0x14,
  };

  enum ObjKind : uint8_t
  {
    None = 0x00,
    Player = 0x01,
    BattleNpc = 0x02,
    EventNpc = 0x03,
    Treasure = 0x04,
    Aetheryte = 0x05,
    GatheringPoint = 0x06,
    EventObj = 0x07,
    MountType = 0x08,
    Companion = 0x09, // this probably actually means minion
    Retainer = 0x0A,
    Area = 0x0B,
    Housing = 0x0C,
    Cutscene = 0x0D,
    CardStand = 0x0E,
  };

  enum Stance : uint8_t
  {
    Passive = 0,
    Active = 1,
  };

  enum class DisplayFlags : uint16_t
  {
    ActiveStance = 0x001,
    Invisible = 0x020,
    HideHead = 0x040,
    HideWeapon = 0x080,
    Faded = 0x100,
    Visor = 0x800,
  };

  enum struct ActorStatus : uint8_t
  {
    Idle = 0x01,
    Dead = 0x02,
    Sitting = 0x03,
    Mounted = 0x04,
    Crafting = 0x05,
    Gathering = 0x06,
    Melding = 0x07,
    SMachine = 0x08,
    Carry = 0x09,
    EmoteMode = 0x0B
  };

  enum GearSetSlot : uint8_t
  {
    MainHand = 0,
    OffHand = 1,
    Head = 2,
    Body = 3,
    Hands = 4,
    Waist = 5,
    Legs = 6,
    Feet = 7,
    Ear = 8,
    Neck = 9,
    Wrist = 10,
    Ring1 = 11,
    Ring2 = 12,
    SoulCrystal = 13,
  };

  enum GearModelSlot : int8_t
  {
    ModelInvalid = -1,
    ModelHead = 0,
    ModelBody = 1,
    ModelHands = 2,
    ModelLegs = 3,
    ModelFeet = 4,
    ModelEar = 5,
    ModelNeck = 6,
    ModelWrist = 7,
    ModelRing1 = 8,
    ModelRing2 = 9
  };

  enum EquipSlotCategory : uint8_t
  {
    Unequippable = 0,

    // main slots

    CharaMainHand = 1,
    CharaOffHand = 2,
    CharaHead = 3,
    CharaBody = 4,
    CharaHands = 5,
    CharaWaist = 6,
    CharaLegs = 7,
    CharaFeet = 8,
    CharaEars = 9,
    CharaNeck = 10,
    CharaWrist = 11,
    CharaRing = 12,
    CharaSoulCrystal = 17,

    // specials

    /*! Cannot equip gear to offhand slot */
      MainTwoHandedWeapon = 13,
    /*! Can be equipped in either main or offhand slot */
      MainOrOffHand = 14, // unused
    /*! Cannot equip gear to head */
      BodyDisallowHead = 15,
    /*! Cannot equip gear to hands, legs and feet slots */
      BodyDisallowHandsLegsFeet = 16,
    /*! Cannot equip gear to feet slot */
      LegsDisallowFeet = 18,
    /*! Cannot equp gear to head, hands, legs, feet slots */
      BodyDisallowAll = 19,
    /*! Cannot equip gear to hands slot */
      BodyDisallowHands = 20,
    /*! Cannot equip gear to legs & feet slots */
      BodyDisallowLegsFeet = 21,
  };

  enum InventoryType : uint16_t
  {
    Bag0 = 0,
    Bag1 = 1,
    Bag2 = 2,
    Bag3 = 3,

    GearSet0 = 1000,
    GearSet1 = 1001,

    Currency = 2000,
    Crystal = 2001,
    //UNKNOWN_0 = 2003,
      KeyItem = 2004,
    HandIn = 2005,
    DamagedGear = 2007,
    //UNKNOWN_1 = 2008,

    ArmoryOff = 3200,
    ArmoryHead = 3201,
    ArmoryBody = 3202,
    ArmoryHand = 3203,
    ArmoryWaist = 3204,
    ArmoryLegs = 3205,
    ArmoryFeet = 3206,
    ArmoryNeck = 3207,
    ArmoryEar = 3208,
    ArmoryWrist = 3209,
    ArmoryRing = 3300,

    ArmorySoulCrystal = 3400,
    ArmoryMain = 3500,

    RetainerBag0 = 10000,
    RetainerBag1 = 10001,
    RetainerBag2 = 10002,
    RetainerBag3 = 10003,
    RetainerBag4 = 10004,
    RetainerBag5 = 10005,
    RetainerBag6 = 10006,
    RetainerEquippedGear = 11000,
    RetainerGil = 12000,
    RetainerCrystal = 12001,
    RetainerMarket = 12002,

    FreeCompanyBag0 = 20000,
    FreeCompanyBag1 = 20001,
    FreeCompanyBag2 = 20002,
    FreeCompanyGil = 22000,
    FreeCompanyCrystal = 22001,

    // housing interior containers
    HousingInteriorAppearance = 25002,

    // 50 in each container max, 400 slots max
    HousingInteriorPlacedItems1 = 25003,
    HousingInteriorPlacedItems2 = 25004,
    HousingInteriorPlacedItems3 = 25005,
    HousingInteriorPlacedItems4 = 25006,
    HousingInteriorPlacedItems5 = 25007,
    HousingInteriorPlacedItems6 = 25008,
    HousingInteriorPlacedItems7 = 25009,
    HousingInteriorPlacedItems8 = 25010,

    // 50 max per container, 400 slots max
    // slot limit increased 'temporarily' for relocation for all estates
    // see: https://na.finalfantasyxiv.com/lodestone/topics/detail/d781e0d538428aef93b8bed4b50dd62c3c50fc74
    HousingInteriorStoreroom1 = 27001,
    HousingInteriorStoreroom2 = 27002,
    HousingInteriorStoreroom3 = 27003,
    HousingInteriorStoreroom4 = 27004,
    HousingInteriorStoreroom5 = 27005,
    HousingInteriorStoreroom6 = 27006,
    HousingInteriorStoreroom7 = 27007,
    HousingInteriorStoreroom8 = 27008,


    // housing exterior containers
    HousingExteriorAppearance = 25000,
    HousingExteriorPlacedItems = 25001,
    HousingExteriorStoreroom = 27000,


  };

  struct HuntingLogEntry
  {
    uint8_t rank;
    uint8_t entries[10][4];
  };

  enum class UnlockEntry : uint16_t
  {
    Return = 1,
    InnRoom = 2,
    Teleport = 4,
    GearSets = 6,
    MateriaMelding = 11,
    AdvancedMateriaMelding = 12,
    MateriaAssimilating = 13,
    Dye = 14,
    Glamour = 15,
    CompanionMenu = 17,
    Companion = 18,
    Decipher = 19,
    Dig = 20,
    HuntingLog = 21,
    EmoteImperialSalute = 23,
    EmoteThrowSnowball = 24,
    TreasureHunt = 25,
    EmoteStepDance = 27,
    EmoteHarvestDance = 28,
    EmoteBallDance = 29,
    EmoteMadervilleDance = 30,
    ChallengeLog = 92,
    Desynth = 95,
    SightseeingLogMenuItem = 97, //Needs another unlock ID to fill it out? Or relog?
    EmoteBombDance = 98,
    EmoteHuzzah = 225,
    EmoteEmbrace = 229,
    EmoteMostGentlemanly = 244,
    AetherialReduction = 256,
    EmoteFistBump = 259
  };

  enum ContainerType : uint16_t
  {
    Unknown = 0,
    Bag = 1,
    GearSet = 2,
    CurrencyCrystal = 3,
    Armory = 4
  };


  enum CurrencyType : uint8_t
  {
    Gil = 0x01,
    StormSeal = 0x02,
    SerpentSeal = 0x03,
    FlameSeal = 0x04,
    TomestonePhilo = 0x05,
    TomestoneMytho = 0x06,
    WolfMark = 0x07,
    TomestoneSold = 0x08,
    AlliedSeal = 0x09,
    Mgp = 0x0A,
    TomestonePoet = 0x0B,
    TomestoneLaw = 0x0C,
    TomestoneEso = 0x0D,
    TomestoneLore = 0x0E
  };

  enum CrystalType : uint8_t
  {
    FireShard = 0x01,
    IceShard = 0x02,
    WindShard = 0x03,
    EarthShard = 0x04,
    LightningShard = 0x05,
    WaterShard = 0x06,

    FireCrystal = 0x07,
    IceCrystal = 0x08,
    WindCrystal = 0x09,
    EarthCrystal = 0x0A,
    LightningCrystal = 0x0B,
    WaterCrystal = 0x0C,

    FireCluster = 0x0D,
    IceCluster = 0x0E,
    WindCluster = 0x0F,
    EarthCluster = 0x10,
    LightningCluster = 0x11,
    WaterCluster = 0x12
  };

  enum struct ZoningType : uint8_t
  {
    None = 1,
    Teleport = 2,
    Return = 3,
    ReturnDead = 4,
    FadeIn = 5,
  };

  enum struct ResurrectType : uint8_t
  {
    None = 0,
    RaiseSpell = 5,
    Return = 8
  };

  enum Gender : uint8_t
  {
    Male = 0,
    Female = 1,
  };


  enum struct GCRank : uint8_t
  {
    None = 0,
    PrivateThirdClass = 1,
    PrivateSecondClass = 2,
    PrivateFirstClass = 3,
    Corporal = 4,
    SergeantThirdClass = 5,
    SergeantSecondClass = 6,
    SergeantFirstClass = 7,
    ChiefSergeant = 8,
    SecondLieutenant = 9,
    FirstLieutenant = 10,
    Captain = 11,
    SecondCommander = 12,
    FirstCommander = 13,
    HighCommander = 14,
    RearMarshal = 15,
    ViceMarshal = 16,
    Marshal = 17,
    GrandMarshal = 18,
    Champion = 19,
  };

  /**
  * Structural representation of the packet sent by the server
  * Send the entire StatusEffect list
  */
  struct StatusWork
  {
    uint16_t Id;
    int16_t SystemParam;
    float Time;
    uint32_t Source;
  };

  enum CharaLook : uint8_t
  {
    Race = 0x00,
    Gender = 0x01,
    Tribe = 0x04,
    Height = 0x03,
    ModelType = 0x02, // Au Ra: changes horns/tails, everything else: seems to drastically change appearance (flip between two sets, odd/even numbers). sometimes retains hairstyle and other features
    FaceType = 0x05,
    HairStyle = 0x06,
    HasHighlights = 0x07, // negative to enable, positive to disable
    SkinColor = 0x08,
    EyeColor = 0x09, // color of character's right eye
    HairColor = 0x0A, // main color
    HairColor2 = 0x0B, // highlights color
    FaceFeatures = 0x0C, // seems to be a toggle, (-odd and +even for large face covering), opposite for small
    FaceFeaturesColor = 0x0D,
    Eyebrows = 0x0E,
    EyeColor2 = 0x0F, // color of character's left eye
    EyeShape = 0x10,
    NoseShape = 0x11,
    JawShape = 0x12,
    LipStyle = 0x13, // lip colour depth and shape (negative values around -120 darker/more noticeable, positive no colour)
    LipColor = 0x14,
    RaceFeatureSize = 0x15,
    RaceFeatureType = 0x16, // negative or out of range tail shapes for race result in no tail (e.g. Au Ra has max of 4 tail shapes), incorrect value can crash client
    BustSize = 0x17, // char creator allows up to max of 100, i set to 127 cause who wouldnt but no visible difference
    Facepaint = 0x18,
    FacepaintColor = 0x19,

  };

  enum MoveType : uint8_t
  {
    Running = 0x00,
    Walking = 0x02,
    Strafing = 0x04,
    Jumping = 0x10,
  };

  enum MoveState : uint8_t
  {
    No = 0x00,
    LeaveCollision = 0x01,
    EnterCollision = 0x02,
    StartFalling = 0x04,
  };

  enum MoveSpeed : uint8_t
  {
    Walk = 24,
    Run = 60,
  };

  struct QuestData
  {
    QuestData()
    {
      c.questId = 0;
      c.sequence = 0;
      c.flags = 0;
      c.UI8A = 0;
      c.UI8B = 0;
      c.UI8C = 0;
      c.UI8D = 0;
      c.UI8E = 0;
      c.UI8F = 0;
    }
    union
    {
      /*!
       * default SE struct
       */
      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t unknown1;
        uint8_t vars[6];
      } packed;

      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t unknown1;
        uint8_t BitFlag48;
        uint8_t BitFlag40;
        uint8_t BitFlag32;
        uint8_t BitFlag24;
        uint8_t BitFlag16;
        uint8_t BitFlag8;
      } a;

      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t unknown1;
        uint8_t UI8AL : 4;
        uint8_t UI8AH : 4;
        uint8_t UI8BL : 4;
        uint8_t UI8BH : 4;
        uint8_t UI8CL : 4;
        uint8_t UI8CH : 4;
        uint8_t UI8DL : 4;
        uint8_t UI8DH : 4;
        uint8_t UI8EL : 4;
        uint8_t UI8EH : 4;
        uint8_t UI8FL : 4;
        uint8_t UI8FH : 4;
      } b;

      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t unknown1;
        uint8_t UI8A;
        uint8_t UI8B;
        uint8_t UI8C;
        uint8_t UI8D;
        uint8_t UI8E;
        uint8_t UI8F;
      } c;

      //struct
      //{
      //   uint16_t questId;
      //   uint8_t sequence;
      //   uint8_t flags;
      //   uint8_t padding;
      //   uint16_t UI16A;
      //   uint16_t UI16B;
      //   uint16_t UI16C;
      //   uint8_t padding1;
      //} d;

      //struct
      //{
      //   uint8_t padding;
      //   uint32_t UI32A;
      //   uint16_t padding2;
      //} e;
    };


  };

  enum class ParamModifier : uint16_t
  {
    None = 0,
    Strength = 1,
    Dexterity = 2,
    Vitality = 3,
    Intelligence = 4,
    Mind = 5,
    Piety = 6,
    HP = 7,
    MP = 8,
    TP = 9,
    GP = 10,
    CP = 11,
    PhysicalDamage = 12,
    MagicDamage = 13,
    Delay = 14,
    AdditionalEffect = 15,
    AttackSpeed = 16,
    BlockRate = 17,
    BlockStrength = 18,
    Parry = 19,
    AttackPower = 20,
    Defense = 21,
    Accuracy = 22,
    Evasion = 23,
    MagicDefense = 24,
    CriticalHitPower = 25,
    CriticalHitResilience = 26,
    CriticalHit = 27,
    CriticalHitEvasion = 28,
    SlashingResistance = 29,
    PiercingResistance = 30,
    BluntResistance = 31,
    ProjectileResistance = 32,
    AttackMagicPotency = 33,
    HealingMagicPotency = 34,
    EnhancementMagicPotency = 35,
    ElementalBonus = 36,
    FireResistance = 37,
    IceResistance = 38,
    WindResistance = 39,
    EarthResistance = 40,
    LightningResistance = 41,
    WaterResistance = 42,
    MagicResistance = 43,
    Determination = 44,
    SkillSpeed = 45,
    SpellSpeed = 46,
    Haste = 47,
    Morale = 48,
    Enmity = 49,
    EnmityReduction = 50,
    CarefulDesynthesis = 51,
    EXPBonus = 52,
    Regen = 53,
    Refresh = 54,
    MainAttribute = 55,
    SecondaryAttribute = 56,
    SlowResistance = 57,
    PetrificationResistance = 58,
    ParalysisResistance = 59,
    SilenceResistance = 60,
    BlindResistance = 61,
    PoisonResistance = 62,
    StunResistance = 63,
    SleepResistance = 64,
    BindResistance = 65,
    HeavyResistance = 66,
    DoomResistance = 67,
    ReducedDurabilityLoss = 68,
    IncreasedSpiritbondGain = 69,
    Craftsmanship = 70,
    Control = 71,
    Gathering = 72,
    Perception = 73,

    // Unique modifiers
    TickHeal = 1000,
    TickDamage = 1001,
    StrengthPercent = 1002,
    DexterityPercent = 1003,
    VitalityPercent = 1004,
    IntelligencePercent = 1005,
    MindPercent = 1006,
    PietyPercent = 1007,
    HPPercent = 1008,
    MPPercent = 1009,
    TPPercent = 1010,
    GPPercent = 1011,
    CPPercent = 1012,
    PhysicalDamagePercent = 1013,
    MagicDamagePercent = 1014,
    AttackPowerPercent = 1015,
    DefensePercent = 1016,
    AccuracyPercent = 1017,
    EvasionPercent = 1018,
    MagicDefensePercent = 1019,
    CriticalHitPowerPercent = 1020,
    CriticalHitResiliencePercent = 1021,
    CriticalHitPercent = 1022,
    EnmityPercent = 1023,
    DamageDealtPercent = 1024,
    DamageTakenPercent = 1025,
    HealingMagicRecoveryPercent = 1026,
    SlashingResistancePercent = 1027,
    PiercingResistancePercent = 1028,
    BluntResistancePercent = 1029,
    ProjectileResistancePercent = 1030,
    ParryPercent = 1031
  };

  enum class StatusEffectFlag : uint32_t
  {
    BuffCategory = 1,
    DebuffCategory = 2,
    Permanent = 4,
    IsGaze = 8,
    Transfiguration = 16,
    CanDispel = 32,
    LockActions = 64,
    LockControl = 128,
    LockMovement = 256,
    Invisibilty = 512,
    CanStatusOff = 1024,
    FcBuff = 2048,
    RemoveOnSuccessfulHit = 4096
  };

  enum struct ActionAspect : uint8_t
  {
    None = 0,   // Doesn't imply unaspected
    Fire = 1,
    Ice = 2,
    Wind = 3,
    Stone = 4,
    Lightning = 5,
    Water = 6,
    Unaspected = 7    // Doesn't imply magical unaspected damage - could be unaspected physical
  };

  enum class ActionPrimaryCostType : uint8_t
  {
    None = 0, // ?
    MagicPoints = 3,
    TacticsPoints = 5,
    TacticsPoints1 = 6,
    StatusEffect = 10,
    Sprint = 18,
//    WARGauge = 22,
//    DRKGauge = 25,
//    AetherflowStack = 30,
//    Status = 32,
//    PLDGauge = 41,
//    RDMGaugeBoth = 74,
////  RDMGaugeBlack = 75, // not right?
//    DRGGauge3Eyes = 76,
  };

  enum class ActionType : int8_t
  {
    WeaponOverride = -1, // Needs more investigation (takes the damage type of the equipped weapon)?
    Unknown_0 = 0,
    Slashing = 1,
    Piercing = 2,
    Blunt = 3,
    Unknown_4 = 4,
    Magical = 5,
    Darkness = 6,
    Unknown_7 = 7,
    LimitBreak = 8,
  };

  enum CalcResultType : uint8_t
  {
    TypeNone = 0x0,
    TypeMiss = 0x1,
    TypeResist = 0x2,
    TypeDamageHp = 0x3,
    TypeRecoverHp = 0x4,
    TypeCriticalDamageHp = 0x5,
    TypeCriticalRecoverHp = 0x6,
    TypeGuard = 0x7,
    TypeParry = 0x8,
    TypeInvalid = 0x9,
    TypeUneffective = 0xA,
    TypeNeglect = 0xB,
    TypeDamageMp = 0xC,
    TypeRecoverMp = 0xD,
    TypeDamageTp = 0xE,
    TypeRecoverTp = 0xF,
    TypeRecoverGp = 0x10,
    TypeSetStatus = 0x11,
    TypeSetStatusMe = 0x12,
    TypeResetStatus = 0x13,
    TypeResetStatusMe = 0x14,
    TypeResetBadStatus = 0x15,
    TypeUneffectiveStatus = 0x16,
    TypeHalfGoodStatus = 0x17,
    TypeHateDirect = 0x18,
    TypeHateIndirection = 0x19,
    TypeHateTop = 0x1A,
    TypeHateAdd = 0x1B,
    TypeHateMult = 0x1C,
    TypeCombo = 0x1D,
    TypeComboHit = 0x1E,
    TypeCounter = 0x1F,
    TypeDestruct = 0x20,
    TypeParalysis = 0x21,
    TypeKnockBack = 0x22,
    TypeDrawUpChairs = 0x23,
    TypeSucked = 0x24,
    TypeCtDrawUpChairs = 0x25,
    TypeLiveCallback = 0x26,
    TypeMount = 0x27,
    TypeArcherDot = 0x28,
    TypeMasterDot = 0x29,
    TypeBlessingOfGoddess = 0x2A,
    TypeBadBreath = 0x2B,
    TypeRevival = 0x2C,
    TypePet = 0x2D,
    TypeBlow = 0x2E,
    TypeStatusResist = 0x2F,
    TypeClearPhysical = 0x30,
    TypeBNpcState = 0x31,
    TypeVfx = 0x32,
    TypeHardCode = 0x33,
    TypeCalcId = 0x34,
    TypeClearPvpPoint = 0x35,
    TypeCheckBarrier = 0x36,
    TypeReflect = 0x37,
  };

  enum class ActionResultFlag : uint8_t
  {
    None = 0,
    Absorbed = 0x04,
    EffectOnSource = 0x80,
    Reflected = 0xA0,
  };

  enum ItemActionType : uint16_t
  {
    KeyItemAction = 1,
    ItemActionVFX = 852,
    ItemActionCompanion = 853,
    ItemActionVFX2 = 944,
    ItemActionMount = 1322,
    ItemActionSong = 5845,
  };

  enum ActionEffectDisplayType : uint8_t
  {
    HideActionName = 0,
    ShowActionName = 1,
    ShowItemName = 2,
  };

  struct CalcResultParam
  {
    uint8_t Type;
    uint8_t Arg0;
    uint8_t Arg1;
    uint8_t Arg2;
    int16_t Value;
    uint8_t Flag;
    uint8_t Padding;
  };

  struct CalcResult
  {
    CalcResultParam CalcResultTg[4];
    CalcResultParam CalcResultCt[4];
  };

  enum class ActionCollisionType : uint8_t
  {
    None,
    SingleTarget,
    Circle,
    Cone,
    Box,
    Unknown,
    Unknown2,
    PersistentArea, // for when you set aoe like asylum
    Unknown3
  };

  enum class ActionInterruptType : uint8_t
  {
    None,
    RegularInterrupt,
    DamageInterrupt,
  };

  enum HandleActionType : uint8_t
  {
    Event,
    Spell,
    Teleport
  };

  enum HandleSkillType : uint8_t
  {
    StdDamage,
    StdHeal,
    StdDot,
  };

  enum InvincibilityType : uint8_t
  {
    InvincibilityNone,
    InvincibilityRefill,
    InvincibilityStayAlive,
    InvincibilityIgnoreDamage,
  };

  namespace Achievement
  {
    enum class Type : uint8_t
    {
      None,
      General,
      LinkedAchievement,
      Classjob,
      Unknown_4,// Materia related? id 304
      Unknown_5,// Hunt related? id 1259
      Quest, // Quests that need all required args met
      Unknown_7,
      Unknown_8,// Map discovery related
      QuestAny,// Quests that need any required args met
      ChocoboRank,
      PvPRank,
      WolvesDenMatches,
      WolvesDenWins,
      InstanceContent,
      BeastTribeReputation,
      Unknown_16,
      FrontlineMatches,
      FrontlineWinsGC,
      FrontlineWinsAll,
      AetherCurrent,
    };

    namespace GeneralSubtype
    {
      enum AchievementGeneralSubtype : int32_t
      {
        EnemyDefeatCount = 11,
        GilEnemySource = 12,
        GilLevequestSource = 13,
        FactionLevequestCompleted = 14,
        GuildhestCompleted = 15,
        MateriaAffixCount = 16,
        SpiritboundMateriaCount = 17,
        RegionalBattleLevequestCompleted = 18,
        LocalTradeLevequestCompleted = 19,

        // Legacy subtypes - skipping

        #pragma region Synth 1 -50 Recipes
        SynthWoodworkingLv01to10Recipes = 23,
        SynthWoodworkingLv11to20Recipes = 24,
        SynthWoodworkingLv21to30Recipes = 25,
        SynthWoodworkingLv31to40Recipes = 26,
        SynthWoodworkingLv41to50Recipes = 27,
        SynthSmithingLv01to10Recipes = 28,
        SynthSmithingLv11to20Recipes = 29,
        SynthSmithingLv21to30Recipes = 30,
        SynthSmithingLv31to40Recipes = 31,
        SynthSmithingLv41to50Recipes = 32,
        SynthArmorcraftLv01to10Recipes = 33,
        SynthArmorcraftLv11to20Recipes = 34,
        SynthArmorcraftLv21to30Recipes = 35,
        SynthArmorcraftLv31to40Recipes = 36,
        SynthArmorcraftLv41to50Recipes = 37,
        SynthGoldsmithingLv01to10Recipes = 38,
        SynthGoldsmithingLv11to20Recipes = 39,
        SynthGoldsmithingLv21to30Recipes = 40,
        SynthGoldsmithingLv31to40Recipes = 41,
        SynthGoldsmithingLv41to50Recipes = 42,
        SynthLeatherworkingLv01to10Recipes = 43,
        SynthLeatherworkingLv11to20Recipes = 44,
        SynthLeatherworkingLv21to30Recipes = 45,
        SynthLeatherworkingLv31to40Recipes = 46,
        SynthLeatherworkingLv41to50Recipes = 47,
        SynthClothcraftLv01to10Recipes = 48,
        SynthClothcraftLv11to20Recipes = 49,
        SynthClothcraftLv21to30Recipes = 50,
        SynthClothcraftLv31to40Recipes = 51,
        SynthClothcraftLv41to50Recipes = 52,
        SynthAlchemyLv01to10Recipes = 53,
        SynthAlchemyLv11to20Recipes = 54,
        SynthAlchemyLv21to30Recipes = 55,
        SynthAlchemyLv31to40Recipes = 56,
        SynthAlchemyLv41to50Recipes = 57,
        SynthCookingLv01to10Recipes = 58,
        SynthCookingLv11to20Recipes = 59,
        SynthCookingLv21to30Recipes = 60,
        SynthCookingLv31to40Recipes = 61,
        SynthCookingLv41to50Recipes = 62,
        #pragma endregion

        // TODO: Map gathering subtypes 63 to 128

        GCStormSeals = 138,
        GCSerpentSeals = 139,
        GCFlameSeals = 140,

        MaelstromLevequestCompleted = 141,
        TwinAdderLevequestCompleted = 142,
        ImmortalFlamesLevequestCompleted = 143,

        MaelstromSupplyCompleted = 144,
        TwinAdderSupplyCompleted = 145,
        ImmortalFlamesSupplyCompleted = 146,

        MaelstromProvisioningCompleted = 147,
        TwinAdderProvisioningCompleted = 148,
        ImmortalFlamesProvisioningCompleted = 149,

        // Legacy subtypes - skipping

        FieldLevequestCompleted = 179,
        UniqueBattleLevequestCompleted = 180,

        // TODO: Map leve subtypes 181 to 201

        UniqueFishCaughtCount = 202,

        // TODO: Map craft subtypes 203 to 213

        UniqueQuestsCompleted = 214,
        InstanceContentCompleted = 215,      // Instanced dungeons, raids or trials
        UniqueInstanceContentCompleted = 216,// Unique instanced dungeons, raids or trials

        BindingCoilCompleted = 217,
        UniqueGuildhestCompleted = 218,
        FateCompleted = 219,

        // TODO: Map subtypes 220 to 235

        ChocoboRidePimpedOut = 236,

        MaelstromUniqueLeveCompleted = 238,
        TwinAdderUniqueLeveCompleted = 239,
        ImmortalFlamesUniqueLeveCompleted = 240,

        EnlistGCMaelstrom = 241,
        EnlistGCTwinAdder = 242,
        EnlistGCImmortalFlames = 243,

        CommendationCount = 244,

        // TODO: Map subtypes 245 to 250

        ResurrectStrangers = 251,
        SecondCoilCompleted = 266,
        UniqueBigFishCaught = 267,
        RetainerVentureCompleted = 268,

        HighLvlDutyPaladinCompleted = 277,
        HighLvlDutyWarriorCompleted = 278,

        RelicAnimus = 279,
        RelicNovus = 280,

        HigherGradeMateriaFromTransmutation = 281,
        ARRSightseeingLogCount = 284,

        InterceptorDroneDefeated = 285,
        InterceptorNodeDefeated = 286,

        TrainAnotherChocoboCount = 287,

        HuntRankBDefeated = 290,
        HuntRankADefeated = 291,
        HuntRankSDefeated = 292,

        LootCofferLeatherMap = 293,

        DesynthesizeItemCount = 294,

        RelicNexus = 347,
        FinalCoilCompleted = 348,
        RelicZodiac = 349,
        RelicZeta = 350,

        TripleTriadUniqueCardCount = 352,
        TripleTriadNPCDefeatedCount = 353,
        TripleTriadRouletteWin = 354,
        TripleTriadTournamentWin = 355,

        MgpGoldSaucerAttractionSource = 356,
        ChocoboRaceCount = 357,
        ChocoboRaceWin = 358,
        ChocoboCovering = 359,
        ChocoboPedigreeLevel = 360,
        ChocoboRating = 361,

        FrontlineEnemyDispatched = 362,

        GATECompleted = 363,

        // TODO: Map subtypes 364 to 368

        HighLvlDutyDarkKnightCompleted = 369,

        GordiasCompleted = 370,
        GordiasSavageCompleted = 371,

        // TODO: Map subtypes 372 to X
      };
    }
  }

  union AchievementDataKey
  {
    uint32_t u32;

    struct AchievementPackedKey {
      uint8_t type;
      uint16_t subtype;
      uint8_t padding0;
    } key;
  };

  enum HierarchyType : uint8_t
  {
    NONE_2 = 0x0,
    PCPARTY = 0x1,
    FRIENDLIST = 0x2,
    AUTOPARTY = 0x3,
    FCCREATE = 0x4,
    FREECOMPANY = 0x5,
    FCJOINREQUEST = 0x6,
    PARTYCANCEL = 0x7,
    MAX_1 = 0xFF,
  };

  enum HierarchyStatus : uint8_t
  {
    Invalid = 0,
    Added = 0x10,
    SentRequest = 0x20,
    ReceivedRequest = 0x30
  };

  namespace Ls
  {
    enum LinkshellHierarchy : int32_t
    {
      None1 = 0x0,
      Master = 0x1,
      Leader = 0x2,
      Member = 0x3,
      Invite = 0x4,
    };
  }

  union HierarchyData
  {
    uint64_t u64;

    struct HierarchyPackedData {
      uint32_t dateAdded;
      uint8_t status;
      uint8_t type;
      uint8_t group;
      uint8_t unavailable;
    } data;

    struct Hierarchy32 {
      uint32_t date;
      uint32_t rawId;
    } u32;
  };

  /* 61719 */
  enum InviteReplyType : int32_t
  {
    DENY = 0x0,
    ACCEPT = 0x1,
    CANCEL = 0x2,
  };

  enum InviteUpdateType : uint8_t
  {
    NEW_INVITE = 0x01,
    INVITE_CANCEL = 0x02,
    JOINED_PARTY = 0x03,
    ACCEPT_INVITE = 0x04,
    REJECT_INVITE = 0x05,
  };

  enum PlayerCondition : uint8_t
  {
    None1 = 0,
    HideUILockChar = 1, // as the name suggests, hides the ui and logs the char...
    InCombat = 18, // in Combat, locks gearchange/return/teleport
    Casting = 19,
    EventAction = 22,
    InNpcEvent = 24, // when talking to an npc, locks ui giving "occupied" message

 //   InNpcEvent1 = 10, // Sent together with InNpcEvent, when waiting for input? just a guess...

    BoundByDuty = 10,
    BetweenAreas = 21,
    WatchingCutscene = 34,

  };

  enum struct FateStatus : uint8_t
  {
    Active = 2,
    Inactive = 4,
    Preparing = 7,
    Completed = 8,
  };

  enum struct FreeCompanyStatus : uint8_t
  {
    Invalid = 0x0,
    InviteStart = 0x1,
    InviteComplete = 0x2,
    Normal= 0x3,
    Freeze = 0x4,
  };

  enum struct ChatType : uint16_t
  {
    LogKindError,
    ServerDebug,
    ServerUrgent,
    ServerNotice,
    Unused4,
    Unused5,
    Unused6,
    Unused7,
    Unused8,
    Unused9,
    Say,
    Shout,
    Tell,
    TellReceive,
    Party,
    Alliance,
    LS1,
    LS2,
    LS3,
    LS4,
    LS5,
    LS6,
    LS7,
    LS8,
    FreeCompany,
    Unused25,
    Unused26,
    NoviceNetwork,
    CustomEmote,
    StandardEmote,
    Yell,
    Unknown31,
    PartyUnk2,
    Unused33,
    Unused34,
    Unused35,
    Unused36,
    Unused37,
    Unused38,
    Unused39,
    Unused40,
    BattleDamage,
    BattleFailed,
    BattleActions,
    BattleItems,
    BattleHealing,
    BattleBeneficial,
    BattleDetrimental,
    BattleUnk48,
    BattleUnk49,
    Unused50,
    Unused51,
    Unused52,
    Unused53,
    Unused54,
    Unused55,
    Echo,
    SystemMessage,
    SystemErrorMessage,
    BattleSystem,
    GatheringSystem,
    NPCMessage,
    LootMessage,
    Unused63,
    CharProgress,
    Loot,
    Crafting,
    Gathering,
    NPCAnnouncement,
    FCAnnouncement,
    FCLogin,
    RetainerSale,
    PartySearch,
    PCSign,
    DiceRoll,
    NoviceNetworkNotice,
    Unknown76,
    Unused77,
    Unused78,
    Unused79,
    GMTell,
    GMSay,
    GMShout,
    GMYell,
    GMParty,
    GMFreeCompany,
    GMLS1,
    GMLS2,
    GMLS3,
    GMLS4,
    GMLS5,
    GMLS6,
    GMLS7,
    GMLS8,
    GMNoviceNetwork,
    Unused95,
    Unused96,
    Unused97,
    Unused98,
    Unused99,
    Unused100
  };

  enum EquipDisplayFlags : uint8_t
  {
    HideNothing = 0x0,
    HideHead = 0x1,
    HideWeapon = 0x2,
    HideLegacyMark = 0x4,

    StoreNewItemsInArmouryChest = 0x10,
    StoreCraftedItemsInInventory = 0x20,

    Visor = 0x40,
  };

  enum ActionKind : uint8_t
  {
    ACTION_KIND_NOTHING = 0x0,
    ACTION_KIND_NORMAL = 0x1,
    ACTION_KIND_ITEM = 0x2,
    ACTION_KIND_EVENT_ITEM = 0x3,
    ACTION_KIND_EVENT_ACTION = 0x4,
    ACTION_KIND_GENERAL = 0x5,
    ACTION_KIND_BUDDY = 0x6,
    ACTION_KIND_COMMAND = 0x7,
    ACTION_KIND_COMPANION = 0x8,
    ACTION_KIND_CRAFT = 0x9,
    ACTION_KIND_FISHING = 0xA,
    ACTION_KIND_PET = 0xB,
    ACTION_KIND_COMPANY_ACTION = 0xC,
    ACTION_KIND_MOUNT = 0xD,
    ACTION_KIND_PVP_ACTION = 0xE,
    ACTION_KIND_FIELD_MARKER = 0xF,
  };



  enum HouseExteriorSlot
  {
    HousePermit,
    ExteriorRoof,
    ExteriorWall,
    ExteriorWindow,
    ExteriorDoor,
    ExteriorRoofDecoration,
    ExteriorWallDecoration,
    ExteriorPlacard,
    ExteriorFence
  };

  enum HouseInteriorSlot
  {
    InteriorWall,
    InteriorFloor,
    InteriorLight,
    InteriorWall_Attic,
    InteriorFloor_Attic,
    InteriorLight_Attic,
    InteriorWall_Basement,
    InteriorFloor_Basement,
    InteriorLight_Basement,
    InteriorLight_Mansion
  };

  enum LandFlagsSlot
  {
    FreeCompany,
    Private
  };

  enum class LandType : uint8_t
  {
    none = 0,
    FreeCompany = 1,
    Private = 2,
  };

  enum BuildingMenu : uint32_t
  {
    BUILDING_MENU_BUY_DEED = 0x0,
    BUILDING_MENU_BUILD = 0x1,
    BUILDING_MENU_DESTROY = 0x2,
    BUILDING_MENU_MAX = 0x3,
  };

  enum HousingProfileStatus : uint32_t
  {
    HOUSING_PROFILE_STATUS_SOLD = 0x1,
    HOUSING_PROFILE_STATUS_WELCOME = 0x2,
    HOUSING_PROFILE_STATUS_HAS_GREETING = 0x4,
    HOUSING_PROFILE_STATUS_HAS_HOUSE = 0x8,
  };

  enum HOUSING_LAND_STATUS : uint8_t
  {
    HOUSING_LAND_STATUS_NOINIT = 0x0,
    HOUSING_LAND_STATUS_NONE = 0x1,
    HOUSING_LAND_STATUS_BUYLAND = 0x2,
    HOUSING_LAND_STATUS_BUILDHOUSE = 0x3,
  };

  enum HOUSING_SAVE_FLAG : uint8_t
  {
    HOUSING_SAVE_FLAG_NONE = 0x0,
    HOUSING_SAVE_FLAG_LAND = 0x1,
    HOUSING_SAVE_FLAG_HOUSE = 0x2,
    HOUSING_SAVE_FLAG_BUDDYSTABLE = 0x4,
    HOUSING_SAVE_FLAG_LAND_HOUSE = 0x3,
  };

  enum HOUSING_AETHERYTE_BITFLAG : uint8_t
  {
    HOUSING_AETHERYTE_BITFLAG_NONE = 0x0,
    HOUSING_AETHERYTE_BITFLAG_PRIVATEAETHERYTE = 0x1,
    HOUSING_AETHERYTE_BITFLAG_BUDDYSTABLE = 0x2,
  };

  enum HOUSING_ACCESSLOCK : uint8_t
  {
    HOUSING_ACCESSLOCK_NONE = 0x0,
    HOUSING_ACCESSLOCK_LOCK = 0x1,
    HOUSING_ACCESSLOCK_FORCEREMOVE = 0x2,
    HOUSING_ACCESSLOCK_AUTOREMOVE = 0x3,
    HOUSING_ACCESSLOCK_NUM = 0x4,
  };

  enum HOUSING_AUTOREMOVEDLAND_STATUS : uint8_t
  {
    HOUSING_AUTOREMOVELAND_STATUS_NONE = 0x0,
    HOUSING_AUTOREMOVELAND_STATUS_FORCE = 0x1,
    HOUSING_AUTOREMOVELAND_STATUS_AUTO = 0x2,
  };

  enum HOUSING_ENTERLIMIT : uint8_t
  {
    HOUSING_ENTERLIMIT_S = 0x40,
    HOUSING_ENTERLIMIT_M = 0x60,
    HOUSING_ENTERLIMIT_L = 0x80,
  };

  enum HOUSING_PRICEDOWN : uint16_t
  {
    HOUSING_PRICEDOWN_FINAL = 0x1FF,
    HOUSING_PRICEDOWN_RESET = 0x200,
    HOUSING_PRICEDOWN_UPDATETIME = 0x201,
  };

  enum HOUSING_PERSONALROOM : uint16_t
  {
    HOUSING_PERSONALROOM_INITIALPRICE = 0x2710,
  };

  enum HOUSING_TEMP_BUFFER_ITEMS : uint8_t
  {
    HOUSING_TEMP_BUFFER_ITEMS_MAX = 0xA,
  };

  enum LandFlags : uint8_t
  {
    CHARA_HOUSING_LAND_DATA_FLAG_HOUSE = 0x1,
    CHARA_HOUSING_LAND_DATA_FLAG_AETHERYTE = 0x2,
  };

  enum HouseSize : uint8_t
  {
    HOUSE_SIZE_S = 0x0,
    HOUSE_SIZE_M = 0x1,
    HOUSE_SIZE_L = 0x2,
    HOUSE_SIZE_ALL = 0xFE,
    INVALID_HOUSE_SIZE = 0xFF,
  };

  struct LandIdent
  {
    int16_t landId; //00
    int16_t wardNum; //02
    int16_t territoryTypeId; //04
    int16_t worldId; //06
  };

  union TerritoryIdent
  {
    struct
    {
      uint16_t instanceId;
      uint16_t territoryTypeId;
    };

    uint32_t id;
  };

  struct House
  {
    uint8_t size;
    uint8_t status;
    uint8_t flags;
    uint8_t __padding1;
    uint32_t fcId;
    uint32_t fcCrestId;
    uint32_t fcCrestId1;
    uint16_t patternIds[8];
    uint8_t colors[8];
  };

  struct Furniture
  {
    uint16_t patternId;
    uint8_t color;
    uint8_t status;
    uint16_t dir;
    uint16_t pos[3];
  };

  struct CharaLandData
  {
    LandIdent landId;
    uint32_t landFlags;
    uint32_t unkown1;
  };

  struct SimpleProfile
  {
    uint32_t price;
    uint8_t status;
    uint8_t name[32];
    uint8_t padding[3];
  };

  struct HousingLayout
  {
    uint8_t storageIndex;
    uint8_t __padding1;
    uint16_t dir;
    uint16_t pos[3];
  };

  struct HousingPersonalRoomProfileData
  {
    uint64_t OnlineStatus;
    uint16_t TerritoryType;
    uint8_t Welcome;
    char OwnerName[32];
    char HouseCommentSimple[49];
  };

  struct HouseBuddyStableData
  {
    uint32_t LastTrainingTime;
    uint8_t Rank;
    uint8_t __padding1;
    uint16_t HouseBuddyRoomId;
    uint8_t SkillLines[3];
    char OwnerName[32];
    char BuddyName[21];
  };

  enum HouseStatus : uint8_t
  {
    none,
    ForSale,
    Sold,
    PrivateEstate,
    FreeCompanyEstate,
  };

  enum HouseIconAdd : uint8_t
  {
    heart = 0x06
  };

  enum WardlandFlags : uint8_t
  {
    IsEstateOwned = 1,
    IsPublicEstate = 2,
    HasEstateGreeting = 4,
    EstateFlagUnknown = 8,
    IsFreeCompanyEstate = 16,
  };

  struct PlayerTeleportQuery
  {
    uint16_t targetAetheryte;
    uint16_t cost;
    bool useAetheryteTicket{ false };
  };

  enum EventSceneError : uint8_t
  {
    EVENT_SCENE_SUCCESS = 0x0,
    EVENT_SCENE_ERROR_LUA_ERRRUN = 0x2,
    EVENT_SCENE_ERROR_LUA_ERRSYNTAX = 0x3,
    EVENT_SCENE_ERROR_LUA_ERRMEM = 0x4,
    EVENT_SCENE_ERROR_LUA_ERRERR = 0x5,
    EVENT_SCENE_ERROR_USER_CANCEL = 0x32,
    EVENT_SCENE_ERROR_SERVER_ABORT = 0x33,
    EVENT_SCENE_ERROR_RELOAD = 0x34,
    EVENT_SCENE_ERROR_LUA_THREAD_BUSY = 0x35,
    EVENT_SCENE_ERROR_TARGET_CHANGED = 0x36,
    EVENT_SCENE_ERROR_CLIENT_ABORT = 0x37,
    EVENT_SCENE_ERROR_TARGET_LOST = 0x38,
    EVENT_SCENE_ERROR_BEFORE_PLAY = 0x39,
    EVENT_SCENE_ERROR_BIND_CHARACTER = 0x3A,
    EVENT_SCENE_ERROR_TARGET_MOVE = 0x3B,
    EVENT_SCENE_ERROR_SCRIPT_NOT_READY = 0x3C,
    EVENT_SCENE_ERROR_TARGET_WARP = 0x3D,
    EVENT_SCENE_ERROR_BIND_OBJECT = 0x3E,
    EVENT_SCENE_ERROR_MAX = 0xFF,
  };

  enum LevelTableEntry : uint8_t
  {
    MAIN,
    SUB,
    DIV,
    HP,
    ELMT,
    THREAT
  };

  // todo: fill this out (Action.exd EffectType)
  enum CastType : uint8_t
  {
    SingleTarget = 1,
    CircularAOE = 2,
    RectangularAOE = 3,
    ConeAOE = 4,
    CircularAoEPlaced = 7
  };

  enum class Role : uint8_t
  {
    None,
    Tank,
    Healer,
    RangedPhysical,
    RangedMagical,
    Melee,
    Crafter,
    Gatherer
  };

  using PlayerStateFlagList = std::vector< PlayerCondition >;

  struct BNPCInstanceObject
  {
    uint16_t territoryType;
    std::string bnpcName;
    uint32_t instanceId;
    uint32_t nameOffset;
    float x;
    float y;
    float z;
    float rotation;
    uint32_t BaseId;
    uint32_t PopWeather;
    uint8_t PopTimeStart;
    uint8_t PopTimeEnd;
    uint32_t MoveAI;
    uint8_t WanderingRange;
    uint8_t Route;
    uint16_t EventGroup;
    uint32_t NameId;
    uint32_t DropItem;
    float SenseRangeRate;
    uint16_t Level;
    uint8_t ActiveType;
    uint8_t PopInterval;
    uint8_t PopRate;
    uint8_t PopEvent;
    uint8_t LinkGroup;
    uint8_t LinkFamily;
    uint8_t LinkRange;
    uint8_t LinkCountLimit;
    int8_t NonpopInitZone;
    int8_t InvalidRepop;
    int8_t LinkParent;
    int8_t LinkOverride;
    int8_t LinkReply;
    int8_t Nonpop;
    float HorizontalPopRange;
    float VerticalPopRange;
    int32_t BNpcBaseData;
    uint8_t RepopId;
    uint8_t BNPCRankId;
    uint16_t TerritoryRange;
    uint32_t BoundInstanceID;
    uint32_t FateLayoutLabelId;
    uint32_t NormalAI;
    uint32_t ServerPathId;
    uint32_t EquipmentID;
    uint32_t CustomizeID;
  };

  /*
   * CellId is used to identify a cell in the cell container of a zone
   */
  struct CellId
  {
    uint32_t x{ 0 };
    uint32_t y{ 0 };
  };

}
