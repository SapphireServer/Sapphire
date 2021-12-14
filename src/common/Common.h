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

  const uint8_t CLASSJOB_TOTAL = 23;
  const uint8_t CLASSJOB_SLOTS = 23;

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

  enum ACTOR_KIND : int32_t
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

  enum OBJECT_TYPE : int32_t
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

  enum WARP_TYPE : uint8_t
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
    Teleport = 4,
    GearSets = 6,
    HuntingLog = 21,
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
    TomestonePoet = 0x0A,
    Mgp = 0x0B,
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

  enum struct ZoneingType : uint8_t
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
        uint8_t vars[6];
      } packed;

      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
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

  enum ActionEffectType : uint8_t
  {
    CALC_RESULT_TYPE_NONE = 0x0,
    CALC_RESULT_TYPE_MISS = 0x1,
    CALC_RESULT_TYPE_RESIST = 0x2,
    CALC_RESULT_TYPE_DAMAGE_HP = 0x3,
    CALC_RESULT_TYPE_RECOVER_HP = 0x4,
    CALC_RESULT_TYPE_CRITICAL_DAMAGE_HP = 0x5,
    CALC_RESULT_TYPE_CRITICAL_RECOVER_HP = 0x6,
    CALC_RESULT_TYPE_GUARD = 0x7,
    CALC_RESULT_TYPE_PARRY = 0x8,
    CALC_RESULT_TYPE_INVALID = 0x9,
    CALC_RESULT_TYPE_UNEFFECTIVE = 0xA,
    CALC_RESULT_TYPE_NEGLECT = 0xB,
    CALC_RESULT_TYPE_DAMAGE_MP = 0xC,
    CALC_RESULT_TYPE_RECOVER_MP = 0xD,
    CALC_RESULT_TYPE_DAMAGE_TP = 0xE,
    CALC_RESULT_TYPE_RECOVER_TP = 0xF,
    CALC_RESULT_TYPE_RECOVER_GP = 0x10,
    CALC_RESULT_TYPE_SET_STATUS = 0x11,
    CALC_RESULT_TYPE_SET_STATUS_ME = 0x12,
    CALC_RESULT_TYPE_RESET_STATUS = 0x13,
    CALC_RESULT_TYPE_RESET_STATUS_ME = 0x14,
    CALC_RESULT_TYPE_RESET_BAD_STATUS = 0x15,
    CALC_RESULT_TYPE_UNEFFECTIVE_STATUS = 0x16,
    CALC_RESULT_TYPE_HALF_GOOD_STATUS = 0x17,
    CALC_RESULT_TYPE_HATE_DIRECT = 0x18,
    CALC_RESULT_TYPE_HATE_INDIRECTION = 0x19,
    CALC_RESULT_TYPE_HATE_TOP = 0x1A,
    CALC_RESULT_TYPE_HATE_ADD = 0x1B,
    CALC_RESULT_TYPE_HATE_MULT = 0x1C,
    CALC_RESULT_TYPE_COMBO = 0x1D,
    CALC_RESULT_TYPE_COMBO_HIT = 0x1E,
    CALC_RESULT_TYPE_COUNTER = 0x1F,
    CALC_RESULT_TYPE_DESTRUCT = 0x20,
    CALC_RESULT_TYPE_PARALYSIS = 0x21,
    CALC_RESULT_TYPE_KNOCK_BACK = 0x22,
    CALC_RESULT_TYPE_DRAW_UP_CHAIRS = 0x23,
    CALC_RESULT_TYPE_SUCKED = 0x24,
    CALC_RESULT_TYPE_CT_DRAW_UP_CHAIRS = 0x25,
    CALC_RESULT_TYPE_LIVE_CALLBACK = 0x26,
    CALC_RESULT_TYPE_MOUNT = 0x27,
    CALC_RESULT_ARCHER_DOT = 0x28,
    CALC_RESULT_MASTER_DOT = 0x29,
    CALC_RESULT_BLESSINGS_OF_GODDESS = 0x2A,
    CALC_RESULT_BAD_BREATH = 0x2B,
    CALC_RESULT_REVIVAL = 0x2C,
    CALC_RESULT_PET = 0x2D,
    CALC_RESULT_TYPE_BLOW = 0x2E,
    CALC_RESULT_TYPE_STATUS_RESIST = 0x2F,
    CALC_RESULT_TYPE_CLEAR_PHYSICAL = 0x30,
    CALC_RESULT_BNPC_STATE = 0x31,
    CALC_RESULT_TYPE_VFX = 0x32,
    CALC_RESULT_TYPE_HARD_CODE = 0x33,
    CALC_RESULT_CALC_ID = 0x34,
    CALC_RESULT_TYPE_CLEAR_PVP_POINT = 0x35,
    CALC_RESULT_TYPE_CHECK_BARRIER = 0x36,
    CALC_RESULT_TYPE_REFLEC = 0x37,
  };

  enum class ActionHitSeverityType : uint8_t
  {
    NormalDamage = 0,
    CritHeal = 0,
    CritDamage = 1,
    NormalHeal = 1,
    DirectHitDamage = 2,
    CritDirectHitDamage = 3
  };

  enum class ActionEffectResultFlag : uint8_t
  {
    None = 0,
    Absorbed = 0x04,
    EffectOnSource = 0x80,
    Reflected = 0xA0,
  };

  enum ItemActionType : uint16_t
  {
    ItemActionVFX = 852,
    ItemActionVFX2 = 944,
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
    CalcResultParam CalcResultCt[4];
    CalcResultParam CalcResultTg[4];
  };

  struct IntegrityStatus
  {
    uint8_t Slot;
    uint8_t __padding1;
    uint16_t Id;
    int16_t SystemParam;
    uint8_t __padding2;
    uint8_t __padding3;
    float Time;
    uint32_t Source;
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

  enum PlayerStateFlag : uint8_t
  {
    HideUILockChar = 16, // as the name suggests, hides the ui and logs the char...
    InCombat = 17, // in Combat, locks gearchange/return/teleport
    Casting = 18,
    InNpcEvent = 23, // when talking to an npc, locks ui giving "occupied" message

 //   InNpcEvent1 = 10, // Sent together with InNpcEvent, when waiting for input? just a guess...

    BoundByDuty = 26,
    BetweenAreas = 37,
    WatchingCutscene = 51, // this is actually just a dummy, this id is different


  };

  enum struct FateStatus : uint8_t
  {
    Active = 2,
    Inactive = 4,
    Preparing = 7,
    Completed = 8,
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

  enum SkillType : uint8_t
  {
    Normal = 0x1,
    ItemAction = 0x2,
    EventItem = 0x3,
    MountSkill = 0xD,
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

  struct House
  {
    uint8_t size;
    uint8_t status;
    uint8_t flags;
    uint8_t __padding1;
    uint64_t fcCrestId;
    uint8_t patternIds[8];
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
    uint8_t flags;
  };

  struct SimpleProfile
  {
    uint32_t price;
    uint8_t status;
    uint8_t fcTag[7];
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

  enum CastType : uint8_t
  {
    SingleTarget = 1,
    CircularAOE = 2,
    Type3 = 3, // another single target? no idea how to call it
    RectangularAOE = 4,
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

  using PlayerStateFlagList = std::vector< PlayerStateFlag >;


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
