#ifndef _COMMON_H
#define _COMMON_H

#include <cstdint>
#include <vector>

#include "CommonGen.h"

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

  struct FFXIVARR_POSITION3
  {
    float x;
    float y;
    float z;
  };

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

  enum InventoryOperation : uint8_t
  {
    Discard = 0x07,
    Move = 0x08,
    Swap = 0x09,
    Merge = 0x0C,
    Split = 0x0A
  };

  enum ClientLanguage : uint8_t
  {
    Japanese = 1,
    English = 2,
    German = 4,
    French = 8
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
  struct StatusEffect
  {
    uint16_t effect_id;
    uint16_t unknown1;
    float duration;
    uint32_t sourceActorId;
  };

  enum CharaLook :
    uint8_t
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

  enum MoveType :
    uint8_t
  {
    Running = 0x00,
    Walking = 0x02,
    Strafing = 0x04,
    Jumping = 0x10,
    BackWalk = 0x06,
  };

  enum MoveState :
    uint8_t
  {
    No = 0x00,
    Land = 0x02,
    Fall = 0x04,
  };

  struct QuestActive
  {
    QuestActive()
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
      c.padding = 0;
      c.padding1 = 0;
    }


    union
    {
      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t padding;
        uint8_t BitFlag48;
        uint8_t BitFlag40;
        uint8_t BitFlag32;
        uint8_t BitFlag24;
        uint8_t BitFlag16;
        uint8_t BitFlag8;
        uint8_t padding1;
      } a;

      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t padding;
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
        uint8_t padding1;
      } b;

      struct
      {
        uint16_t questId;
        uint8_t sequence;
        uint8_t flags;
        uint8_t padding;
        uint8_t UI8A;
        uint8_t UI8B;
        uint8_t UI8C;
        uint8_t UI8D;
        uint8_t UI8E;
        uint8_t UI8F;
        uint8_t padding1;
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

  enum struct ActionAspect :
    uint8_t
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

  enum class ActionType :
    int8_t
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

  enum ActionEffectType :
    uint8_t
  {
    Nothing = 0,
    Miss = 1,
    FullResist = 2,
    Damage = 3,
    Heal = 4,
    BlockedDamage = 5,
    ParriedDamage = 6,
    Invulnerable = 7,
    NoEffectText = 8,
    Unknown_0 = 9,
    MpLoss = 10,
    MpGain = 11,
    TpLoss = 12,
    TpGain = 13,
    GpGain = 14,
    Knockback = 33,
    Mount = 38
  };

  enum class ActionHitSeverityType :
    uint8_t
  {
    NormalDamage = 0,
    CritHeal = 0,
    CritDamage = 1,
    NormalHeal = 1,
    DirectHitDamage = 2,
    CritDirectHitDamage = 3
  };

  enum ActionEffectDisplayType :
    uint8_t
  {
    HideActionName = 0,
    ShowActionName = 1,
    ShowItemName = 2,
  };

  enum class ActionCollisionType :
    uint8_t
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

  enum HandleActionType :
    uint8_t
  {
    Event,
    Spell,
    Teleport
  };

  enum HandleSkillType :
    uint8_t
  {
    StdDamage,
    StdHeal,
    StdDot,
  };

  enum InvincibilityType :
    uint8_t
  {
    InvincibilityNone,
    InvincibilityRefill,
    InvincibilityStayAlive,
  };

  enum PlayerStateFlag :
    uint8_t
  {
    HideUILockChar = 0, // as the name suggests, hides the ui and logs the char...
    InCombat = 1, // in Combat, locks gearchange/return/teleport
    Casting = 2,
    InNpcEvent = 7, // when talking to an npc, locks ui giving "occupied" message

    InNpcEvent1 = 10, // Sent together with InNpcEvent, when waiting for input? just a guess...

    BetweenAreas = 24,
    BoundByDuty = 28,
    WatchingCutscene = 50, // this is actually just a dummy, this id is different


  };

  enum struct FateStatus :
    uint8_t
  {
    Active = 2,
    Inactive = 4,
    Preparing = 7,
    Completed = 8,
  };

  enum struct ChatType :
    uint16_t
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

  enum EquipDisplayFlags :
    uint8_t
  {
    HideNothing = 0x0,
    HideHead = 0x1,
    HideWeapon = 0x2,
    HideLegacyMark = 0x4,

    StoreNewItemsInArmouryChest = 0x10,
    StoreCraftedItemsInInventory = 0x20,

    Visor = 0x40,
  };

  enum SkillType :
    uint8_t
  {
    Normal = 0x1,
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

  enum HouseTagSlot
  {
    MainTag,
    SubTag1,
    SubTag2
  };

  enum LandFlagsSlot
  {
    FreeCompany,
    Private,
    Apartment,
    SharedHouse1,
    SharedHouse2
  };

  enum class LandType : uint8_t
  {
    none = 0,
    FreeCompany = 1,
    Private = 2,
  };

  enum LandFlags : uint32_t
  {
    EstateBuilt = 0x1,
    HasAetheryte = 0x2,
    UNKNOWN_1 = 0x4,
    UNKNOWN_2 = 0x8,
    UNKNOWN_3 = 0x10,
  };

  struct LandIdent
  {
    int16_t landId; //00
    int16_t wardNum; //02
    int16_t territoryTypeId; //04
    int16_t worldId; //06
  };

  struct LandFlagSet
  {
    LandIdent landIdent;
    uint32_t landFlags; //08
    uint32_t unkown1; //12
  };

  struct HousingObject
  {
    uint32_t itemId;
    uint32_t padding; // was itemrotation + unknown/pad, looks unused now
    float rotation;
    Common::FFXIVARR_POSITION3 pos;
  };

  enum HouseSize : uint8_t
  {
    Cottage,
    House,
    Mansion
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

  using PlayerStateFlagList = std::vector< PlayerStateFlag >;

}

#endif
