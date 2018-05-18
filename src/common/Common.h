#ifndef _COMMON_H
#define _COMMON_H

#include <cstdint>
#include <vector>

#include <boost/make_shared.hpp>
#include "CommonGen.h"

// +---------------------------------------------------------------------------
// The following enumerations are structures to require their type be included.
// They are also defined within the Core::Common namespace to avoid collisions.
// +---------------------------------------------------------------------------
namespace Core {
namespace Common {

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

   enum EquipSlot : uint8_t
   {
      MainHand = 0,
      OffHand = 1,
      Head = 2,
      Body = 3,
      Hands = 4,
      Waist = 5,
      Legs = 6,
      Feet = 7,
      Neck = 8,
      Ear = 9,
      Wrist = 10,
      Ring1 = 11,
      Ring2 = 12,
      SoulCrystal = 13,
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
      DamagedGear = 2007,
      //UNKNOWN_1 = 2008,

      ArmoryOff = 3200,
      ArmoryHead = 3201,
      ArmoryBody = 3202,
      ArmoryHand = 3203,
      ArmoryWaist = 3204,
      ArmoryLegs = 3205,
      ArmoryFeet = 3206,
      ArmotyNeck = 3207,
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
      FreeCompanyCrystal = 22001
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

   enum MoveType : uint16_t
   {
      Run = 0x00,
      Walk = 0x02,
      Strafe = 0x04,
      Jump = 0x100,
      Fall = 0x400,
      Land = 0x200,
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
      Mount = 38
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
   };

   enum PlayerStateFlag : uint8_t
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

   enum struct FateStatus : uint8_t
   {
      Active = 2,
      Inactive = 4,
      Preparing = 7,
      Completed = 8,
   };

   enum ActorControlType : uint16_t
   {
      ToggleWeapon = 0x01,
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

      SetTitle = 0x1F4,

      SetStatusIcon = 0x1F8,
      LimitBreakGauge = 0x1F9, // Max level, amount, build type (chop sound), lb type(0=pve lb 1=pvp lb)
      SetHomepoint = 0x1FB,
      SetFavorite = 0x1FC,
      LearnTeleport = 0x1FD,

      ArmoryErrorMsg = 0x201,

      AchievementPopup = 0x203,

      Unk7 = 0x205,                 // LogMessage?
      AchievementMsg = 0x206,

      SetItemLevel = 0x209,

      ChallengeEntryCompleteMsg = 0x20B,
      ChallengeEntryUnlockMsg = 0x20C,

      GilTrailMsg = 0x211,

      SetMaxGearSets = 0x230,

      SetCharaGearParamUI = 0x260,

      GearSetEquipMsg = 0x321,

      SetFestival = 0x386, // param1: festival.exd index

      ToggleOrchestrionUnlock = 0x396,
      Dismount = 0x3A0,

      // Duty Recorder
      BeginReplayAck = 0x3A1,
      EndReplayAck = 0x3A2,

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

      Visor = 0x40,
   };

   enum SkillType : uint8_t
   {
      Normal = 0x1,
      MountSkill = 0xD,
   };

   typedef std::vector< PlayerStateFlag > PlayerStateFlagList;

} /* Common */
} /* Core */

#endif
