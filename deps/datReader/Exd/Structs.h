#pragma once

#include "Common.h"
#include <vector>

namespace Component::Excel
{

  template< typename T >
  struct ExcelStruct
  {

    T _data;
    std::vector< std::string > _strings;

    T& data()
    {
      return _data;
    };

    uint8_t* ptr()
    {
      return reinterpret_cast< uint8_t* >( &_data );
    };

    const std::string& getString( Component::Excel::StringOffset offset )
    {
      return _strings[ offset.m_offset ];
    };
  };


  /////////////////////////////////////////////////////////

  /* 3746 */
  struct CraftLeve
  {
    int32_t Leve;
    int32_t Talk;
    int32_t Item[4];
    uint16_t ItemNum[4];
    uint8_t AdditionalTimes;
    bool HQ[4];
    int8_t padding0[3];
  };

  /* 3747 */
  struct CompleteJournalCategory
  {
    uint32_t Begin;
    uint32_t End;
    int32_t SeparateType;
  };

  /* 33329 */
  struct ItemTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset Help;
    Component::Excel::StringOffset UIName;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
  };

  /* 33331 */
  struct Item
  {
    ItemTextStruct Text;
    uint64_t ModelId;
    uint64_t SubModelId;
    uint32_t StackMax;
    uint32_t CategoryArg;
    uint32_t PriceMin;
    uint32_t Price;
    uint32_t PriceMax;
    uint32_t SortId;
    int32_t RepairItem;
    int32_t MirageItem;
    uint16_t Icon;
    uint16_t Trait;
    uint16_t Damage;
    uint16_t MagicDamage;
    uint16_t AttackInterval;
    uint16_t ShieldRate;
    uint16_t ShieldBlockRate;
    uint16_t Defense;
    uint16_t MagicDefense;
    uint16_t RecastTime;
    uint16_t Action;
    uint16_t Salvage;
    int16_t BonusValue[7];
    uint8_t Level;
    uint8_t EquipLevel;
    uint8_t EquipPvPRank;
    uint8_t Category;
    uint8_t UICategory;
    uint8_t SearchCategory;
    uint8_t Rarity;
    uint8_t MaterializeType;
    uint8_t MateriaSocket;
    uint8_t Slot;
    uint8_t BonusType[6];
    uint8_t SpecialBonus;
    uint8_t SpecialBonusType[6];
    uint8_t Repair;
    uint8_t Class;
    uint8_t AttackType;
    uint8_t AttackRange;
    uint8_t CastTime;
    uint8_t CondClassJob;
    uint8_t Series;
    uint8_t SellPriceParam;
    uint8_t CondGrandCompany;
    uint8_t Role;
    int8_t SpecialBonusValue[6];
    bool ConditionRace[5];
    uint8_t DisablePassedOthers : 1;
    uint8_t OnlyOne : 1;
    uint8_t DisableAbandon : 1;
    uint8_t MateriaProhibition : 1;
    uint8_t Crest : 1;
    uint8_t Stain : 1;
    uint8_t Lot : 1;
    uint8_t HQ : 1;
    uint8_t padding1 : 4;
    uint8_t MateriaEffectOnlyInPvP : 1;
    uint8_t ConditionFemale : 1;
    uint8_t ConditionMale : 1;
    uint8_t DisableSameAccount : 1;
    int8_t padding2[4];
  };

  /* 35156 */
  struct AddonTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 35157 */
  struct Addon
  {
    AddonTextStruct Text;
  };

  /* 35338 */
  struct InstanceContentTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 35339 */
  struct InstanceContentRewardStruct
  {
    uint32_t BeginnerBonusGil;
    uint32_t BeginnerBonusExp;
    uint32_t TotalExp;
    uint32_t TotalGil;
    uint32_t Unknown;
    uint16_t BeginnerBonusA;
    uint16_t ClearA;
    uint16_t ClearB;
    uint16_t MiddleA[17];
  };

  /* 35340 */
  struct InstanceContent
  {
    InstanceContentTextStruct Text;
    InstanceContentRewardStruct Reward;
    uint8_t Unknown1;
    uint32_t Unknown2[6];
    uint32_t StartCutscene;
    uint32_t EntranceRect;
    uint32_t TerritoryType;
    uint32_t Image;
    uint32_t BossMessage[2];
    uint32_t BossName;
    uint32_t ContentTextStart;
    uint32_t ContentTextEnd;
    int32_t InstanceBuff;
    int32_t Unknown3;
    uint16_t Time;
    uint16_t Music;
    uint16_t ClearMusic;
    uint16_t Sortkey;
    uint8_t Unknown4;
    uint8_t Type;
    uint8_t RandomContentType;
    uint8_t RewardType;
    uint8_t FinderPartyCondition;
    uint8_t LevelMin;
    uint8_t LevelMax;
    uint8_t PartyMemberCount;
    uint8_t PartyCount;
    uint8_t TankCount;
    uint8_t HealerCount;
    uint8_t AttackerCount;
    uint8_t RangeCount;
    uint8_t ItemLevel;
    uint8_t ItemLevelMax;
    uint8_t ProgressMax;
    int8_t TreasureObtainedFlag;
    uint8_t padding1 : 2;
    uint8_t DisableHalfwayProgress : 1;
    uint8_t Halfway : 1;
    uint8_t EnableFinder : 1;
    uint8_t DifferentiateDPS : 1;
    uint8_t Alliance : 1;
    uint8_t FreeRole : 1;
    uint8_t Unknown5;
  };

  /* 63505 */
  struct ClassJobTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Abbreviation;
    Component::Excel::StringOffset NameFemale;
  };

  /* 63506 */
  struct ClassJob
  {
    ClassJobTextStruct Text;
    int8_t padding0[4];
    uint64_t ModelJobStone;
    Component::Excel::StringOffset EnText;
    uint32_t JobCrystalItemId;
    uint32_t ARRRelicQuestId;
    uint32_t ARRFinalJobQuest;
    int32_t InitWeapon[2];
    uint16_t Hp;
    uint16_t Mp;
    uint16_t STR;
    uint16_t VIT;
    uint16_t DEX;
    uint16_t INT_;
    uint16_t MND;
    uint16_t PIE;
    uint16_t Element[6];
    uint16_t LimitBreakAction[3];
    uint16_t PvpLimitBreakAction[3];
    uint8_t Kind;
    uint8_t UIPriority;
    uint8_t Unknown6;
    uint8_t MainClass;
    uint8_t Role;
    uint8_t Town;
    uint8_t PartyBuff;
    int8_t MonsterNote;
    int8_t StartingLevel;
    int8_t WorkIndex;
    int8_t BattleClassIndex;
    int8_t CraftingClassIndex;
  };

  /* 63507 */
  struct TribeTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset NameFemale;
  };

  /* 63508 */
  struct Tribe
  {
    TribeTextStruct Text;
    int8_t Hp;
    int8_t Mp;
    int8_t STR;
    int8_t VIT;
    int8_t DEX;
    int8_t INT_;
    int8_t MND;
    int8_t PIE;
  };

  /* 66076 */
  struct ActionTimeline
  {
    Component::Excel::StringOffset Filename;
    uint8_t Type;
    uint8_t Priority;
    uint8_t Stance;
    uint8_t Slot;
    uint8_t LookAtMode;
    uint8_t ActionTimelineEIDMode;
    uint8_t WeaponTimeline;
    uint8_t LoadType;
    uint8_t StartAttach;
    uint8_t padding0 : 2;
    uint8_t Pause : 1;
    uint8_t ResidentPap : 1;
    uint8_t Resident : 1;
    uint8_t KillUpper : 1;
    uint8_t IsMotionCanceledByMoving : 1;
    uint8_t IsLoop : 1;
    int8_t padding1[2];
  };

  /* 67373 */
  struct ActionTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 67374 */
  struct Action
  {
    ActionTextStruct Text;
    uint32_t Reward;
    uint16_t Icon;
    uint16_t CastTimeline;
    uint16_t HitTimeline;
    uint16_t CostValue;
    uint16_t CondArg;
    uint16_t ComboParent;
    uint16_t CastTime;
    uint16_t RecastTime;
    uint16_t ResetStatus;
    int16_t Timeline;
    uint8_t Category;
    uint8_t CastVFX;
    uint8_t ArcherTimeline;
    uint8_t Level;
    uint8_t EffectType;
    uint8_t EffectRange;
    uint8_t EffectWidth;
    uint8_t CostType;
    uint8_t Cond;
    uint8_t RecastGroup;
    uint8_t Element;
    uint8_t ProcStatus;
    uint8_t UseClassJob;
    uint8_t Init;
    uint8_t Omen;
    int8_t Learn;
    int8_t SelectRange;
    int8_t SelectCorpse;
    int8_t AttackType;
    uint8_t SelectMyPet : 1;
    uint8_t SelectGround : 1;
    uint8_t SelectENpc : 1;
    uint8_t SelectOthers : 1;
    uint8_t SelectEnemy : 1;
    uint8_t SelectAlliance : 1;
    uint8_t SelectParty : 1;
    uint8_t SelectMyself : 1;
    uint8_t PvPOnly : 1;
    uint8_t InvalidMove : 1;
    uint8_t Silence : 1;
    uint8_t ComboContinue : 1;
    uint8_t EffectEnemy : 1;
    uint8_t CheckDir : 1;
    uint8_t Lay : 1;
    uint8_t SelectPartyPet : 1;
    uint8_t IsTargetLine : 1;
    uint8_t HideCastBar : 1;
    uint8_t ForceVFX : 1;
    uint8_t LogExec : 1;
    uint8_t LogMiss : 1;
    uint8_t LogCast : 1;
    uint8_t IsMove : 1;
    uint8_t IsAvoid : 1;
    int8_t padding0[1];
  };

  /* 75653 */
  struct Recipe
  {
    int32_t CraftType;
    int32_t CraftItemId;
    int32_t MaterialItemId[8];
    int32_t CrystalType[2];
    int32_t NeedStatus;
    int32_t NeedEquipItem;
    uint16_t Category;
    uint16_t WorkRate;
    uint16_t QualityRate;
    uint16_t MaterialPointRate;
    uint16_t NotebookIndex;
    uint16_t NeedCraftmanship;
    uint16_t NeedControl;
    uint16_t NeedSecretRecipeBook;
    uint8_t Level;
    uint8_t CraftNum;
    uint8_t MaterialNum[8];
    uint8_t CrystalNum[2];
    uint8_t Element;
    uint8_t padding0 : 5;
    uint8_t CanHq : 1;
    uint8_t CanAutoCraft : 1;
    uint8_t Sub : 1;
    int8_t padding1[2];
  };

  /* 75654 */
  struct RecipeLevelTable
  {
    uint16_t WorkMax;
    uint16_t QualityMax;
    uint16_t MaterialPoint;
    int8_t padding0[2];
  };

  /* 86192 */
  struct EventItemTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset Help;
    Component::Excel::StringOffset UIName;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 86193 */
  struct EventItem
  {
    EventItemTextStruct Text;
    uint32_t EventHandler;
    int32_t CastTimeline;
    int32_t Timeline;
    uint16_t Icon;
    uint16_t Action;
    uint8_t StackMax;
    uint8_t CastTime;
    int8_t padding1[2];
  };

  /* 100766 */
  struct WeatherTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 100767 */
  struct Weather
  {
    WeatherTextStruct Text;
    int32_t Icon;
  };

  /* 139964 */
  struct WeaponTimeline
  {
    Component::Excel::StringOffset File;
    int16_t NextWeaponTimeline;
    int8_t padding0[2];
  };

  /* 161452 */
  struct MotionTimeline
  {
    Component::Excel::StringOffset filename;
    uint8_t BlendGroup;
    uint8_t padding0 : 5;
    uint8_t IsLipEnable : 1;
    uint8_t IsBlinkEnable : 1;
    uint8_t IsLoop : 1;
    int8_t padding1[2];
  };

  /* 175281 */
  struct ExclusionPreloadStruct
  {
    int32_t Timeline;
  };

  /* 195074 */
  struct CharaMakeTypeLooksStruct
  {
    uint32_t Menu;
    uint32_t SubMenuMask;
    uint32_t Customize;
    uint32_t SubMenuParam[28];
    uint32_t SubMenuGraphic[28];
    uint8_t InitVal;
    uint8_t SubMenuType;
    uint8_t SubMenuNum;
    uint8_t LookAt;
  };

  /* 195075 */
  struct CharaMakeTypeVoiceStruct
  {
    uint8_t SEPackId[12];
  };

  /* 195076 */
  struct CharaMakeTypeFaceOptionStruct
  {
    int32_t Option[7];
  };

  /* 195077 */
  struct CharaMakeTypeEquipStruct
  {
    uint64_t Helmet;
    uint64_t Top;
    uint64_t Glove;
    uint64_t Down;
    uint64_t Shoes;
    uint64_t Weapon;
    uint64_t SubWeapon;
  };

  /* 195078 */
  struct CharaMakeType
  {
    CharaMakeTypeLooksStruct Looks[28];
    CharaMakeTypeVoiceStruct Voice;
    CharaMakeTypeFaceOptionStruct FaceOption[6];
    int8_t padding0[4];
    CharaMakeTypeEquipStruct Equip[3];
    int32_t Race;
    int32_t Tribe;
    int8_t Gender;
    int8_t padding1[7];
  };

  struct BNpcCustomize
  {
    uint8_t race;
    uint8_t gender;
    uint8_t bodyType;
    uint8_t height;
    uint8_t tribe;
    uint8_t face;
    uint8_t hairStyle;
    uint8_t hairHighlight;
    uint8_t skinColor;
    uint8_t eyeHeterochromia;
    uint8_t hairColor;
    uint8_t hairHighlightColor;
    uint8_t facialFeature;
    uint8_t facialFeatureColor;
    uint8_t eyebrows;
    uint8_t eyeColor;
    uint8_t eyeShape;
    uint8_t nose;
    uint8_t jaw;
    uint8_t mouth;
    uint8_t lipColor;
    uint8_t bustOrTone1;
    uint8_t extraFeature1;
    uint8_t extraFeature2OrBust;
    uint8_t facePaint;
    uint8_t facePaintColor;
    uint8_t padding1;
    uint8_t padding2;
  };

  /* 195079 */
  struct HairMakeTypeLooksStruct
  {
    uint32_t Menu;
    uint32_t SubMenuMask;
    uint32_t Customize;
    uint32_t SubMenuParam[40];
    uint32_t SubMenuGraphic[28];
    uint8_t InitVal;
    uint8_t SubMenuType;
    uint8_t SubMenuNum;
    uint8_t LookAt;
  };

  /* 195080 */
  struct HairMakeTypeFaceOptionStruct
  {
    int32_t Option[7];
  };

  /* 195081 */
  struct HairMakeType
  {
    HairMakeTypeLooksStruct Looks[9];
    HairMakeTypeFaceOptionStruct FaceOption[6];
    int32_t Race;
    int32_t Tribe;
    int8_t Gender;
    int8_t padding0[3];
  };

  /* 195083 */
  struct CharaMakeCustomize
  {
    uint32_t Icon;
    uint8_t Graphic;
    uint8_t NeedReward;
    int8_t padding0[2];
  };

  /* 195168 */
  struct EmoteTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 195169 */
  struct Emote
  {
    EmoteTextStruct Text;
    uint32_t Unknown;
    int32_t TimelineID;
    int32_t TimelineID_Begin;
    int32_t TimelineID_End;
    int32_t TimelineID_GroundSitting;
    int32_t TimelineID_ChairSitting;
    int32_t TimelineID_Mounting;
    int32_t TimelineID_Lying;
    int32_t TimelineID_Adjust;
    int32_t TextCommand;
    uint16_t Icon;
    uint16_t Log;
    uint16_t LogSelf;
    uint8_t Category;
    uint8_t Mode;
    uint8_t UI_Priority;
    uint8_t Reward;
    uint8_t IsLoopEmote : 1;
    uint8_t IsPoseEmote : 1;
    uint8_t IsAvailableWhenFishing : 1;
    uint8_t IsAvailableWhenDrawn : 1;
    uint8_t IsAvailableWhenNotDrawn : 1;
    uint8_t IsFacial : 1;
    uint8_t IsRotate : 1;
    uint8_t IsEndEmoteMode : 1;
    int8_t padding0[1];
  };

  /* 195171 */
  struct AetheryteTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 195172 */
  struct Aetheryte
  {
    AetheryteTextStruct Text;
    int32_t EventHandler;
    uint32_t PopRange[4];
    uint16_t TelepoName;
    uint16_t TransferName;
    uint16_t TerritoryType;
    int16_t CostPosX;
    int16_t CostPosY;
    uint8_t Town;
    uint8_t SortKey;
    uint8_t TextIcon;
    uint8_t Telepo : 7;
    uint8_t padding1 : 1;
    int8_t padding2[2];
  };

  /* 195176 */
  struct TerritoryType
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset LVB;
    uint32_t EventHandler;
    int32_t RegionIcon;
    int32_t AreaIcon;
    int32_t Aetheryte;
    int32_t FixedTime;
    uint16_t Region;
    uint16_t SubRegion;
    uint16_t Area;
    uint16_t Map;
    uint16_t BGM;
    uint16_t QuestBattle;
    uint8_t BattalionMode;
    uint8_t ExclusiveType;
    uint8_t IntendedUse;
    uint8_t Breath;
    uint8_t Unknown;
    uint8_t Resident;
    uint8_t Unknown1;
    uint8_t Unknown2;
    uint8_t Unknown3;
    int8_t TreasureObtainedFlag;
    int8_t AchievementIndex;
    uint8_t padding0 : 4;
    uint8_t IsPvPAction : 1;
    uint8_t Mount : 1;
    uint8_t Stealth : 1;
    uint8_t PCSearch : 1;
  };

  /* 195177 */
  struct ItemUICategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 195178 */
  struct ItemUICategory
  {
    ItemUICategoryTextStruct Text;
    int32_t Icon;
    uint8_t Priority;
    uint8_t Kind;
    int8_t padding0[2];
  };

  /* 195791 */
  struct MovieSubtitleTimeStruct
  {
    float StartTime;
    float EndTime;
  };

  /* 195792 */
  struct MovieSubtitle
  {
    MovieSubtitleTimeStruct Time;
  };

  /* 195793 */
  struct HowToTextStruct
  {
    Component::Excel::StringOffset Title;
  };

  /* 195794 */
  struct HowTo
  {
    HowToTextStruct Text;
    int16_t Page[5];
    int16_t PagePad[5];
    uint8_t SortId;
    int8_t Category;
    uint8_t padding0 : 7;
    uint8_t Announce : 1;
    int8_t padding1[1];
  };

  /* 195795 */
  struct AchievementTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 195796 */
  struct Achievement
  {
    AchievementTextStruct Text;
    uint32_t Item;
    int32_t ConditionArg[9];
    uint16_t Title;
    uint16_t Icon;
    uint16_t Priority;
    uint8_t Category;
    uint8_t Point;
    uint8_t ConditionType;
    uint8_t Detail;
    int8_t padding0[2];
  };

  /* 200982 */
  struct Jingle
  {
    Component::Excel::StringOffset Path;
  };

  /* 200983 */
  struct ScreenImage
  {
    uint32_t Image;
    int8_t Jingle;
    int8_t Type;
    uint8_t padding0 : 7;
    uint8_t Lang : 1;
    int8_t padding1[1];
  };

  /* 200984 */
  struct CutScreenImage
  {
    int32_t Type;
    int32_t Icon;
  };

  /* 200985 */
  struct GeneralActionTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 200986 */
  struct GeneralAction
  {
    GeneralActionTextStruct Text;
    int32_t Icon;
    uint16_t Action;
    uint8_t Reward;
    uint8_t Recast;
    uint8_t UIPriority;
    int8_t padding0[3];
  };

  /* 200987 */
  struct CraftActionTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 200988 */
  struct CraftAction
  {
    CraftActionTextStruct Text;
    int32_t Action[8];
    uint16_t Timeline;
    uint16_t SubTimeline;
    uint16_t Icon;
    uint8_t UseClassJob;
    uint8_t Lv;
    uint8_t CostCP;
    int8_t ClassJob;
    int8_t padding0[2];
  };

  /* 200989 */
  struct TraitTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 200990 */
  struct Trait
  {
    TraitTextStruct Text;
    int32_t Icon;
    uint16_t Reward;
    int16_t ParamValue;
    uint8_t ClassJob;
    uint8_t Level;
    uint8_t PvPSkillPoint;
    uint8_t UseClass;
    uint8_t padding0 : 7;
    uint8_t PvPOnly : 1;
    int8_t padding1[3];
  };

  /* 200991 */
  struct FCRightsTextStruct
  {
    Component::Excel::StringOffset Text;
    Component::Excel::StringOffset Help;
  };

  /* 200992 */
  struct FCRights
  {
    FCRightsTextStruct RightsName;
    uint16_t Icon;
    uint8_t SortId;
    int8_t padding0[1];
  };

  /* 200993 */
  struct GrandCompanyRank
  {
    uint32_t CSMax;
    uint32_t NextCS;
    int32_t IconOfLimsa;
    int32_t IconOfGridania;
    int32_t IconOfUldah;
    int32_t RankUpQuestOfLimsa;
    int32_t RankUpQuestOfGridania;
    int32_t RankUpQuestOfUldah;
    uint8_t RankCategory;
    uint8_t LinearRank;
    uint8_t RankOfMonsterNoteCondition;
    int8_t padding0[1];
  };

  /* 200994 */
  struct MonsterNoteTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 200995 */
  struct MonsterNote
  {
    MonsterNoteTextStruct Text;
    uint32_t RewardExp;
    uint16_t Target[4];
    uint8_t NeededKills[4];
  };

  /* 200996 */
  struct MonsterNoteTarget
  {
    int32_t Icon;
    uint16_t Monster;
    uint16_t ZoneName[3];
    uint16_t AreaName[3];
    uint8_t Town;
    int8_t padding0[1];
  };

  /* 200997 */
  struct ParamGrow
  {
    int32_t NextExp;
    int32_t Mp;
    int32_t ParamBase;
    int32_t ParamBaseRating;
    int32_t MonsterNoteExp;
    int32_t MonsterNoteSeals;
    uint16_t PhysicalBonus;
    uint16_t BaseExp;
    uint16_t RepairExp;
    uint16_t ProperDungeon;
    uint16_t ProperGuildOrder;
    uint8_t ApplyAction;
    uint8_t PhysicalBonusLimit;
    uint8_t EventExpRate;
    int8_t padding0[3];
  };

  /* 201000 */
  struct BuddySkill
  {
    uint16_t Line[3];
    uint8_t Point;
    uint8_t padding0 : 7;
    uint8_t IsActive : 1;
  };

  /* 201001 */
  struct PetActionTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 201002 */
  struct PetAction
  {
    PetActionTextStruct Text;
    int32_t Icon;
    uint16_t Action;
    uint8_t Pet;
    uint8_t padding0 : 6;
    uint8_t DisableOrder : 1;
    uint8_t MasterOrder : 1;
  };

  /* 201003 */
  struct EquipSlotCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 201004 */
  struct EquipSlotCategory
  {
    EquipSlotCategoryTextStruct Text;
    int8_t Permit[14];
    int8_t padding0[2];
  };

  /* 201006 */
  struct Stain
  {
    uint32_t Color;
    uint32_t Item;
    uint8_t Category;
    int8_t padding0[3];
  };

  /* 201007 */
  struct MarkerTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 201008 */
  struct Marker
  {
    MarkerTextStruct Text;
    int32_t Icon;
  };

  /* 201009 */
  struct BuddyActionTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 201010 */
  struct BuddyAction
  {
    BuddyActionTextStruct Text;
    int32_t Icon;
    int32_t StatusIcon;
    uint8_t Reward;
    int8_t padding0[3];
  };

  /* 201011 */
  struct MainCommandTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 201012 */
  struct MainCommand
  {
    MainCommandTextStruct Text;
    int32_t Icon;
    uint8_t ActionMenu;
    uint8_t Category;
    int8_t SortId;
    int8_t padding0[1];
  };

  /* 201013 */
  struct FieldMarkerTextStruct
  {
    Component::Excel::StringOffset Help;
  };

  /* 201014 */
  struct FieldMarker
  {
    FieldMarkerTextStruct Text;
    int32_t VFX;
    uint16_t Icon;
    int8_t padding0[2];
  };

  /* 201015 */
  struct CompanionTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset Help;
    Component::Excel::StringOffset Expository;
    Component::Excel::StringOffset Cry;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 201016 */
  struct Companion
  {
    CompanionTextStruct Text;
    uint16_t Model;
    uint16_t Icon;
    uint16_t Enemy;
    uint16_t Priority;
    uint8_t Scale;
    uint8_t InactiveIdle[2];
    uint8_t InactiveBattle;
    uint8_t InactiveWandering;
    uint8_t MoveType;
    uint8_t Special;
    uint8_t WanderingWait;
    uint8_t ChatGroup;
    uint8_t padding1 : 2;
    uint8_t Roulette : 1;
    uint8_t Battle : 1;
    uint8_t LookAt : 1;
    uint8_t Poke : 1;
    uint8_t Stroke : 1;
    uint8_t Clapping : 1;
    int8_t padding2[2];
  };

  /* 201017 */
  struct MountTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset Help;
    Component::Excel::StringOffset Expository;
    Component::Excel::StringOffset Cry;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 201018 */
  struct Mount
  {
    MountTextStruct Text;
    Component::Excel::StringOffset CallSE;
    Component::Excel::StringOffset CallFalseSE;
    Component::Excel::StringOffset ExitSE;
    float Slowdown;
    float MoveAccel_Run;
    float MoveAccel_Walk;
    float MoveSpeed_Run;
    float MoveSpeed_Walk;
    float MoveSpeed_RunLR;
    float MoveSpeed_WalkLR;
    float MoveSpeed_Back;
    float RotateSpeed_FFXIV;
    float RotateSpeed_WOW;
    float RotateSpeed_AutoRun;
    float RotateSpeed_LockOn;
    float RotateAccel_FFXIVRun;
    float RotateAccel_FFXIVWalk;
    float RotateAccel_LockOn;
    float BattleMoveSpeed_Run;
    float BattleMoveSpeed_RunLR;
    float BattleMoveSpeed_Back;
    float ScaleMale[6];
    float ScaleFemale[6];
    int32_t Model;
    int32_t EquipHead;
    int32_t EquipBody;
    int32_t EquipLeg;
    int32_t EquipFoot;
    uint16_t BGM;
    uint16_t Icon;
    uint16_t Action[2];
    uint8_t ExitMoveDist;
    uint8_t ExitMoveSpeed;
    uint8_t UIPriority;
    uint8_t RadiusRate;
    uint8_t BaseMotionSpeed_Run;
    uint8_t BaseMotionSpeed_Walk;
    uint8_t LinkNum;
    int8_t SaveIndex;
    uint8_t padding1 : 5;
    uint8_t ExHotbarEnableConfig : 1;
    uint8_t IsFloat : 1;
    uint8_t IsEmote : 1;
    int8_t padding2[3];
  };

  /* 201019 */
  struct OnlineStatusTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 201020 */
  struct OnlineStatus
  {
    OnlineStatusTextStruct Text;
    uint32_t Icon;
    uint8_t ListOrder;
    uint8_t padding0 : 7;
    uint8_t List : 1;
    int8_t padding1[2];
  };

  /* 201021 */
  struct TitleTextStruct
  {
    Component::Excel::StringOffset Male;
    Component::Excel::StringOffset Female;
    uint8_t padding0 : 7;
    uint8_t Front : 1;
    int8_t padding1[3];
  };

  /* 201022 */
  struct Title
  {
    TitleTextStruct Text;
  };

  /* 201023 */
  struct ENpcTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset Title;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 201024 */
  struct ENpcResident
  {
    ENpcTextStruct Text;
    uint8_t PopType;
    int8_t padding1[3];
  };

  /* 201025 */
  struct PatchMark
  {
    int32_t MarkID;
    uint16_t SubCategory;
    uint16_t Version;
    uint8_t SubCategoryType;
    int8_t Category;
    int8_t padding0[2];
  };

  /* 201026 */
  struct LogFilterTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 201027 */
  struct LogFilter
  {
    LogFilterTextStruct Text;
    uint16_t Caster;
    uint16_t Target;
    uint8_t LogKind;
    uint8_t Category;
    uint8_t DisplayOrder;
    uint8_t Preset;
  };

  /* 201028 */
  struct Cabinet
  {
    int32_t Item;
    uint16_t Priority;
    uint8_t Category;
    int8_t padding0[1];
  };

  /* 201029 */
  struct PlaceNameTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset SWT;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 201030 */
  struct PlaceName
  {
    PlaceNameTextStruct Text;
    uint8_t LocationTitle;
    int8_t padding1[3];
  };

  /* 201031 */
  struct InfoError
  {
    int32_t Message;
  };

  /* 201032 */
  struct FCRank
  {
    uint32_t NextPoint;
    uint32_t CurrentPoint;
    uint16_t Rights[3];
    uint8_t FCActionActiveNum;
    uint8_t FCActionStockNum;
    uint8_t FCChestBoxNum;
    int8_t padding0[3];
  };

  /* 201033 */
  struct FCDefine
  {
    int32_t Value;
  };

  /* 201034 */
  struct FCHierarchyTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 201035 */
  struct FCHierarchy
  {
    FCHierarchyTextStruct Text;
  };

  /* 201036 */
  struct FCReputationTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 201037 */
  struct FCReputation
  {
    FCReputationTextStruct Name;
    uint32_t NextPoint;
    uint32_t CurrentPoint;
    uint32_t Color;
    uint8_t DiscountRate;
    int8_t padding0[3];
  };

  /* 201038 */
  struct TownTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 201039 */
  struct Town
  {
    TownTextStruct Name;
    int32_t Icon;
  };

  /* 201040 */
  struct TerritoryIntendedUse
  {
    uint8_t BuzzType;
    uint8_t EnableReturn : 1;
    uint8_t EnableTeleport : 1;
    uint8_t ImmediatelyLogout : 1;
    uint8_t EnablePet : 1;
    uint8_t EnableBuddy : 1;
    uint8_t ClassJobChange : 1;
    uint8_t Repair : 1;
    uint8_t Craft : 1;
    uint8_t padding0 : 1;
    uint8_t RecastPenalty : 1;
    uint8_t EnableAction : 1;
    uint8_t SELimit : 1;
    uint8_t EnableDiscoveryNotification : 1;
    uint8_t EnableRecommend : 1;
    uint8_t EnableHomePoint : 1;
    uint8_t EnableCompanion : 1;
    int8_t padding1[1];
  };

  /* 223113 */
  struct BNpcTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 223114 */
  struct BNpcName
  {
    BNpcTextStruct Text;
  };

  /* 223115 */
  struct EObjTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 223116 */
  struct EObj
  {
    EObjTextStruct Text;
    float EventHighAddition;
    uint32_t EventHandler;
    uint16_t SharedGroup;
    uint8_t PopType;
    uint8_t Invisibility;
    uint8_t padding1 : 5;
    uint8_t EyeCollision : 1;
    uint8_t DirectorControl : 1;
    uint8_t Target : 1;
    int8_t padding2[3];
  };

  /* 223117 */
  struct TreasureTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 223118 */
  struct Treasure
  {
    TreasureTextStruct Text;
    int32_t Type;
    int32_t KeyItem;
    int32_t Model;
    int32_t Item;
    int32_t SubItem;
    int32_t SharedGroup;
    uint8_t Zone;
    uint8_t Rate;
    int8_t padding1[2];
  };

  /* 223119 */
  struct ExportedSG
  {
    Component::Excel::StringOffset SGFilePath;
  };

  /* 223120 */
  struct Festival
  {
    Component::Excel::StringOffset name;
  };

  /* 228343 */
  struct PhysicsWind
  {
    float Threshold;
    float Amplitude;
    float AmplitudeFrequency;
    float PowerMin;
    float PowerMax;
    float PowerFrequency;
  };

  /* 240362 */
  struct ModelSkeleton
  {
    float Radius;
    float Height;
    float VFXScale;
    float FootScale;
    float WalkSpeed;
    float RunSpeed;
    float FloatHeight[2];
    float FloatDown;
    float FloatUp;
    uint8_t MotionBlendType;
    uint8_t AutoAttackType;
    uint8_t padding0 : 7;
    uint8_t LoopFlySE : 1;
    int8_t padding1[1];
  };

  /* 257957 */
  struct WorldTextStruct
  {
    Component::Excel::StringOffset Help;
  };

  /* 257958 */
  struct World
  {
    WorldTextStruct Text;
    Component::Excel::StringOffset Name;
    uint8_t UserType;
    uint8_t DCGroup;
    uint8_t padding0 : 7;
    uint8_t Public : 1;
    int8_t padding1[1];
  };

  /* 258037 */
  struct GuardianDeityTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 258038 */
  struct GuardianDeity
  {
    GuardianDeityTextStruct Text;
    uint16_t Icon;
    int8_t padding0[2];
  };

  /* 258039 */
  struct MainCommandCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 258040 */
  struct MainCommandCategory
  {
    MainCommandCategoryTextStruct Text;
    int32_t Icon;
  };

  /* 258042 */
  struct CharaMakeClassEquip
  {
    uint64_t Helmet;
    uint64_t Top;
    uint64_t Glove;
    uint64_t Down;
    uint64_t Shoes;
    uint64_t Weapon;
    uint64_t SubWeapon;
    int32_t Class;
    int8_t padding0[4];
  };

  /* 258043 */
  struct CharaMakeNameTextStruct
  {
    Component::Excel::StringOffset HuM_M_;
    Component::Excel::StringOffset HuM_F_;
    Component::Excel::StringOffset HuM_L_;
    Component::Excel::StringOffset HuH_M_;
    Component::Excel::StringOffset HuH_F_;
    Component::Excel::StringOffset HuH_L_;
    Component::Excel::StringOffset El_M_;
    Component::Excel::StringOffset El_F_;
    Component::Excel::StringOffset ElF_L_;
    Component::Excel::StringOffset ElS_L_;
    Component::Excel::StringOffset MqS_M_;
    Component::Excel::StringOffset MqS_F_;
    Component::Excel::StringOffset MqS_ML_;
    Component::Excel::StringOffset MqS_FL_;
    Component::Excel::StringOffset MqM_M_;
    Component::Excel::StringOffset MqM_F_;
    Component::Excel::StringOffset MqM_L_;
    Component::Excel::StringOffset LaP_MF_;
    Component::Excel::StringOffset LaP_ML_;
    Component::Excel::StringOffset LaP_MR_;
    Component::Excel::StringOffset LaD_MN_;
    Component::Excel::StringOffset LaD_MR_;
    Component::Excel::StringOffset LaD_FN_;
    Component::Excel::StringOffset LaD_FR_;
    Component::Excel::StringOffset RoZ_MF_;
    Component::Excel::StringOffset RoZ_ML_;
    Component::Excel::StringOffset RoZ_FF_;
    Component::Excel::StringOffset RoZ_FL_;
    Component::Excel::StringOffset RoR_F_;
    Component::Excel::StringOffset RoR_ML_;
    Component::Excel::StringOffset RoR_FL_;
  };

  /* 258044 */
  struct CharaMakeName
  {
    CharaMakeNameTextStruct TEXT;
  };

  /* 258046 */
  struct LobbyTextStruct
  {
    Component::Excel::StringOffset Text;
    Component::Excel::StringOffset Sub;
    Component::Excel::StringOffset Help;
  };

  /* 258047 */
  struct Lobby
  {
    LobbyTextStruct TEXT;
    uint32_t TYPE;
    uint32_t PARAM;
    uint32_t LINK;
  };

  /* 258048 */
  struct CalendarDaysStruct
  {
    uint8_t Month;
    uint8_t Day;
  };

  /* 258049 */
  struct Calendar
  {
    CalendarDaysStruct Days[32];
  };

  /* 258050 */
  struct WorldDCGroupType
  {
    Component::Excel::StringOffset Name;
  };

  /* 264223 */
  struct MapSymbol
  {
    int32_t Icon;
    int32_t Name;
    uint8_t padding0 : 7;
    uint8_t DisplayNavi : 1;
    int8_t padding1[3];
  };

  /* 264224 */
  struct ItemAction
  {
    uint16_t Action;
    uint16_t Calcu0Arg[3];
    uint16_t Calcu1Arg[3];
    uint16_t Calcu2Arg[3];
    uint16_t HQCalcu0Arg[3];
    uint16_t HQCalcu1Arg[3];
    uint16_t HQCalcu2Arg[3];
    uint8_t CondLv;
    uint8_t padding0 : 5;
    uint8_t CondPVPOnly : 1;
    uint8_t CondPVP : 1;
    uint8_t CondBattle : 1;
  };

  /* 264225 */
  struct Materia
  {
    int32_t Item[10];
    uint8_t Param;
    int8_t ParamValue[10];
    int8_t padding0[1];
  };

  /* 264226 */
  struct ClassJobCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264227 */
  struct ClassJobCategory
  {
    ClassJobCategoryTextStruct Text;
    bool ClassJob[31];
    int8_t padding0[1];
  };

  /* 264228 */
  struct RetainerTask
  {
    int32_t Exp;
    uint16_t TipCost;
    uint16_t Time;
    uint16_t CondItemLv;
    uint16_t ParamA;
    uint16_t ParamB;
    uint16_t TaskNum;
    uint8_t Category;
    uint8_t Level;
    uint8_t CondParamA;
    uint8_t CondParamB;
    uint8_t padding0 : 7;
    uint8_t IsRandom : 1;
    int8_t padding1[3];
  };

  /* 264229 */
  struct HowToPageTextStruct
  {
    Component::Excel::StringOffset Text[3];
  };

  /* 264230 */
  struct HowToPage
  {
    HowToPageTextStruct Text;
    int32_t Icon;
    uint8_t Type;
    uint8_t IconKind;
    uint8_t TextKind;
    int8_t padding0[1];
  };

  /* 264231 */
  struct Map
  {
    Component::Excel::StringOffset Path;
    uint32_t DiscoveryFlag;
    uint16_t Unknown;
    uint16_t Scale;
    uint16_t CategoryNameUI;
    uint16_t NameUI;
    uint16_t FloorNameUI;
    uint16_t TerritoryType;
    int16_t Unknown1;
    int16_t Unknown2;
    int16_t DiscoveryIndex;
    uint8_t PriorityCategoryUI;
    uint8_t PriorityUI;
    uint8_t MapType;
    int8_t PriorityFloorUI;
    uint8_t IsUint16Discovery : 6;
    uint8_t IsEvent : 1;
    uint8_t padding0 : 1;
    int8_t padding1[1];
  };

  /* 264233 */
  struct ContentsNoteTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 264234 */
  struct ContentsNote
  {
    ContentsNoteTextStruct Text;
    int32_t CondArg;
    int32_t RewardArg[2];
    uint16_t OpenLevel;
    uint16_t OpenHowTo;
    uint8_t Category;
    uint8_t UIPriority;
    uint8_t Reward[2];
  };

  /* 264240 */
  struct FCActivityTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 264241 */
  struct FCActivity
  {
    FCActivityTextStruct Text;
    uint8_t SelfKind;
    uint8_t TargetKind;
    uint8_t NumParam;
    uint8_t Category;
    int8_t IconType;
    int8_t padding0[3];
  };

  /* 264318 */
  struct QuestTodoStruct
  {
    uint32_t Marker[8];
    uint8_t TodoSequence;
    uint8_t CountableNum;
    int8_t padding0[2];
  };

  /* 264319 */
  struct QuestTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264320 */
  struct QuestDefineStruct
  {
    Component::Excel::StringOffset Name;
    uint32_t Value;
  };

  /* 264321 */
  struct QuestEventListenerStruct
  {
    uint32_t Listener;
    uint32_t ConditionValue;
    uint16_t Behavior;
    uint8_t Sequence;
    uint8_t Todo;
    uint8_t Event;
    uint8_t ConditionType;
    uint8_t ConditionOperator;
    uint8_t VisibleCallback : 1;
    uint8_t ConditionCallback : 1;
    uint8_t BehaviorCallback : 1;
    uint8_t ItemCallback : 1;
    uint8_t TargetingPossibleCallback : 1;
    uint8_t QualifiedCallback : 1;
    uint8_t AnnounceCallback : 1;
    uint8_t AcceptCallback : 1;
  };

  /* 264322 */
  struct QuestRewardStruct
  {
    uint32_t Gil;
    uint32_t Item[7];
    uint32_t OptionalItem[5];
    uint32_t InstanceContent;
    uint32_t AllaganTomestoneType;
    uint16_t ExpBonus;
    uint16_t CompanyPointNum;
    uint16_t Action;
    uint16_t System[4];
    uint8_t CompanyPointType;
    uint8_t CrystalType[3];
    uint8_t CrystalNum[3];
    uint8_t ItemArrayType;
    uint8_t ItemNum[6];
    uint8_t ItemStainId[6];
    uint8_t OptionalItemNum[5];
    uint8_t OptionalItemStainId[5];
    uint8_t Emote;
    uint8_t GeneralAction[2];
    uint8_t AllaganTomestoneNum;
    uint8_t BeastReputationValueNum;
    int8_t padding1[3];
  };

  /* 264323 */
  struct Quest
  {
    QuestTextStruct Text; //4
    QuestDefineStruct Define[50]; // 194
    QuestEventListenerStruct EventListener[64]; // 594
    QuestTodoStruct QuestTodo[24]; // 8f4
    QuestRewardStruct Reward;
    Component::Excel::StringOffset Script;
    uint32_t PrevQuest[3];
    uint32_t ExcludeQuest[2];
    uint32_t InstanceContent[3];
    uint32_t Client;
    uint32_t Finish;
    uint32_t Header;
    uint32_t Inlay;
    int32_t Mount;
    uint16_t ClassLevel;
    uint16_t ClassLevel2;
    uint16_t AcquiredReward;
    uint16_t TimeBegin;
    uint16_t TimeEnd;
    uint16_t BeastReputationValue;
    uint16_t ClientBehavior;
    uint16_t Area;
    uint16_t Sort;
    uint8_t ClassJob;
    uint8_t QuestLevelOffset;
    uint8_t ClassJob2;
    uint8_t PrevQuestOperator;
    uint8_t ExcludeQuestOperator;
    uint8_t StartTown;
    uint8_t FirstClassOperator;
    uint8_t FirstClass;
    uint8_t GrandCompany;
    uint8_t GrandCompanyRank;
    uint8_t InstanceContentOperator;
    uint8_t Festival;
    uint8_t FestivalPhaseBegin;
    uint8_t FestivalPhaseEnd;
    uint8_t BeastTribe;
    uint8_t BeastReputationRank;
    uint8_t RepeatCycle;
    uint8_t RepeatFlag;
    uint8_t ExpClass;
    uint8_t Genre;
    uint8_t IconType;
    uint8_t Quality;
    uint8_t padding2 : 3;
    uint8_t HideOfferIcon : 1;
    uint8_t Cancellable : 1;
    uint8_t Introduction : 1;
    uint8_t Repeatable : 1;
    uint8_t House : 1;
    int8_t padding3[3];
  };

  /* 264324 */
  struct Level
  {
    float TransX;
    float TransY;
    float TransZ;
    float RotY;
    float RangeOnMap;
    uint32_t BaseId;
    uint32_t Map;
    uint32_t EventHandler;
    uint32_t TerritoryType;
    int32_t eAssetType;
  };

  /* 264325 */
  struct ContentRouletteTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Description;
    Component::Excel::StringOffset Contents;
  };

  /* 264326 */
  struct ContentRoulette
  {
    ContentRouletteTextStruct Text;
    uint32_t Image;
    uint32_t ClearRewardA;
    uint32_t ClearRewardB;
    uint8_t ItemLevel;
    uint8_t PartyMemberCount;
    uint8_t TankCount;
    uint8_t HealerCount;
    uint8_t MeleeDPSCount;
    uint8_t RangedDPSCount;
    uint8_t Sortkey;
    uint8_t padding0 : 6;
    uint8_t AllClearFlag : 1;
    uint8_t EnableFinder : 1;
  };

  /* 264329 */
  struct ActionCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264330 */
  struct ActionCategory
  {
    ActionCategoryTextStruct Text;
  };

  /* 264331 */
  struct StatusTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 264332 */
  struct Status
  {
    StatusTextStruct Text;
    uint16_t Icon;
    uint16_t Log;
    uint8_t Stack;
    uint8_t Category;
    uint8_t HitEffect;
    uint8_t LoopEffect;
    uint8_t PartyListPriority;
    uint8_t SystemParamEffect;
    uint8_t TargetType;
    uint8_t Flag;
    uint8_t InconvenienceClear : 1;
    uint8_t HideTimer : 1;
    uint8_t Forever : 1;
    uint8_t NotLookAt : 1;
    uint8_t ShapeShift : 1;
    uint8_t NotControl : 1;
    uint8_t NotAction : 1;
    uint8_t NotMove : 1;
    uint8_t padding0 : 6;
    uint8_t SemiTransparent : 1;
    uint8_t FcAction : 1;
    int8_t padding1[2];
  };

  /* 264333 */
  struct AchievementKindTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264334 */
  struct AchievementKind
  {
    AchievementKindTextStruct Text;
  };

  /* 264335 */
  struct AchievementCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264336 */
  struct AchievementCategory
  {
    AchievementCategoryTextStruct Text;
    uint8_t Kind;
    uint8_t padding0 : 6;
    uint8_t ShowComplete : 1;
    uint8_t Valid : 1;
    int8_t padding1[2];
  };

  /* 264337 */
  struct RaceTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset NameFemale;
  };

  /* 264338 */
  struct Race
  {
    RaceTextStruct Text;
    int32_t Body[2];
    int32_t Hand[2];
    int32_t Leg[2];
    int32_t Foot[2];
  };

  /* 264339 */
  struct BaseParamTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 264340 */
  struct BaseParam
  {
    BaseParamTextStruct Text;
    uint8_t ItemParamRate[21];
    uint8_t RoleRate[13];
    int8_t PacketIndex;
    int8_t padding0;
  };

  /* 264341 */
  struct MateriaTomestoneRate
  {
    uint32_t Rate;
  };

  /* 264342 */
  struct ItemSearchCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264343 */
  struct ItemSearchCategory
  {
    ItemSearchCategoryTextStruct Text;
    int32_t Icon;
    uint8_t Block;
    uint8_t DisplayOrder;
    int8_t ClassLevel;
    int8_t padding0[1];
  };

  /* 264344 */
  struct ItemSearchClassFilterTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264345 */
  struct ItemSearchClassFilterStruct
  {
    ItemSearchClassFilterTextStruct Text;
    int8_t Class;
    int8_t padding0[3];
  };

  /* 264346 */
  struct ItemFood
  {
    uint8_t Param[3];
    int8_t Value[3];
    int8_t Limit[3];
    int8_t ValueHQ[3];
    int8_t LimitHQ[3];
    bool Rate[3];
    int8_t padding0[2];
  };

  /* 264347 */
  struct CompanionMoveTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264348 */
  struct CompanionMove
  {
    CompanionMoveTextStruct Text;
  };

  /* 264349 */
  struct RoleTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset ShortName;
  };

  /* 264350 */
  struct Role
  {
    RoleTextStruct Text;
    int32_t Icon;
  };

  /* 264351 */
  struct BuddyEquipTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset UIName;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 264352 */
  struct BuddyEquip
  {
    BuddyEquipTextStruct Text;
    int32_t Model[3];
    uint16_t Icon[3];
    uint8_t GrandCompany;
    int8_t padding1[1];
  };

  /* 264353 */
  struct BuddyRank
  {
    uint32_t RankUpExp;
  };

  /* 264354 */
  struct TreasureSpot
  {
    float MapOffsetX;
    float MapOffsetY;
    int32_t Location;
  };

  /* 264355 */
  struct ContentsNoteCategory
  {
    uint8_t ContentType;
    int8_t UIPriority;
    int8_t padding0[2];
  };

  /* 264356 */
  struct Relic
  {
    uint32_t Item;
    uint32_t ExchangeItem;
    int32_t Icon;
    uint16_t Materia[4];
    uint8_t MainNote[3];
    uint8_t SubNote[3];
    uint8_t SelectionANote[2];
    uint8_t SelectionBNote[1];
    int8_t padding0[3];
  };

  /* 264357 */
  struct RelicNote
  {
    uint32_t EventItem;
    uint16_t Target[10];
    uint16_t Boss[4];
    uint16_t Fate[3];
    uint16_t FateTerritoryType[3];
    uint16_t GuildLeve[3];
    uint8_t NeededKills[10];
  };

  /* 264358 */
  struct RelicNoteCategoryTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 264359 */
  struct RelicNoteCategory
  {
    RelicNoteCategoryTextStruct Text;
    int8_t UIPriority;
    int8_t padding0[3];
  };

  /* 264362 */
  struct MobHuntStruct
  {
    uint16_t Target[5];
    uint8_t NeededKills[5];
    uint8_t Rank[5];
  };

  /* 264363 */
  struct MobHuntTarget
  {
    uint16_t Monster;
    uint16_t Fate;
    uint16_t Icon;
    uint16_t ZoneName;
    uint16_t AreaName;
    int8_t padding0[2];
  };

  /* 264364 */
  struct MobHuntRankStruct
  {
    uint16_t Reward[2];
  };

  /* 264365 */
  struct GatheringPoint
  {
    int32_t BaseId;
    int32_t BonusCond;
    int32_t BonusType;
    int32_t AreaId;
    uint16_t BonusVal;
    uint16_t BonusPoint;
    uint16_t PlaceNameId;
    uint8_t Type;
    uint8_t Count;
  };

  /* 264366 */
  struct GatheringPointBase
  {
    int32_t Type;
    int32_t GatheringItemId[8];
    uint8_t Lv;
    uint8_t EffectId;
    int8_t padding0[2];
  };

  /* 264367 */
  struct GatheringPointNameTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 264368 */
  struct GatheringPointName
  {
    GatheringPointNameTextStruct Text;
  };

  /* 264369 */
  struct CraftTypeTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264370 */
  struct CraftType
  {
    CraftTypeTextStruct Text;
    uint8_t MainPhysical;
    uint8_t SubPhysical;
    int8_t padding0[2];
  };

  /* 264371 */
  struct NotebookDivisionTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264372 */
  struct NotebookDivision
  {
    NotebookDivisionTextStruct Text;
    uint8_t CraftOpeningLevel;
    uint8_t GatheringOpeningLevel;
    bool CanUseCraft[8];
    int8_t padding0[2];
  };

  /* 264373 */
  struct LeveTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Objective;
  };

  /* 264374 */
  struct LeveRewardStruct
  {
    float ExpRate;
    uint32_t StaticExp;
    uint32_t Gil;
    int32_t Item;
    int32_t AdditionalItem;
  };

  /* 264375 */
  struct Leve
  {
    LeveTextStruct Text;
    LeveRewardStruct Reward;
    uint32_t TodoListener;
    uint32_t StartMarker;
    int32_t Client;
    int32_t AssignmentType;
    int32_t Town;
    int32_t Evaluation;
    int32_t Location;
    int32_t Genre;
    int32_t Region;
    int32_t Area;
    int32_t PlateRegionIcon;
    int32_t GameData;
    int32_t Header;
    uint16_t ClassLevel;
    uint16_t BGM;
    uint8_t TimeLimit;
    uint8_t ClassJob;
    uint8_t PlateDesignVfx;
    uint8_t PlateFrameVfx;
    uint8_t padding0 : 5;
    uint8_t Cancellable : 1;
    uint8_t Difficulty : 1;
    uint8_t Special : 1;
    int8_t padding1[3];
  };

  /* 264376 */
  struct GatheringLeve
  {
    int32_t Route[4];
    int32_t Item[4];
    int32_t Rule;
    int32_t BNpcEntry;
    uint16_t Objective[2];
    uint8_t ItemNum[4];
    uint8_t Num;
    uint8_t Variation;
    uint8_t padding0 : 7;
    uint8_t UseSubArm : 1;
    int8_t padding1[1];
  };

  /* 264378 */
  struct MapMarker
  {
    int32_t Icon;
    int32_t Name;
    int32_t EventSubArg;
    uint16_t EventArg;
    int16_t PosX;
    int16_t PosY;
    uint8_t Start;
    uint8_t Layout;
    uint8_t TextType;
    uint8_t EventType;
    int8_t padding0[2];
  };

  /* 264379 */
  struct ContentTypeTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264380 */
  struct ContentType
  {
    ContentTypeTextStruct Text;
    uint32_t IconLarge;
    uint32_t IconSmall;
  };

  /* 264381 */
  struct GrandCompanyTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset SWT;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 264382 */
  struct GrandCompany
  {
    GrandCompanyTextStruct Text;
    int8_t MonsterNote;
    int8_t padding1[3];
  };

  /* 264383 */
  struct HowToCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264384 */
  struct HowToCategory
  {
    HowToCategoryTextStruct Text;
  };

  /* 264385 */
  struct ConfigurationKeyTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 264386 */
  struct ConfigKey
  {
    ConfigurationKeyTextStruct Text;
    Component::Excel::StringOffset Label;
    uint8_t Param;
    uint8_t Platform;
    uint8_t Category;
    uint8_t padding0 : 7;
    uint8_t Required : 1;
  };

  /* 264387 */
  struct MacroIcon
  {
    int32_t Icon;
  };

  /* 264388 */
  struct RecommendContents
  {
    int32_t LayoutId;
    uint8_t ClassJob;
    uint8_t LvMin;
    uint8_t LvMax;
    int8_t padding0[1];
  };

  /* 264389 */
  struct AdventureTextStruct
  {
    Component::Excel::StringOffset TitleText;
    Component::Excel::StringOffset HintText;
    Component::Excel::StringOffset FlavorText;
  };

  /* 264390 */
  struct Adventure
  {
    AdventureTextStruct Text;
    int32_t LayoutID;
    int32_t AreaName;
    int32_t SpotIcon;
    int32_t LandscapePicture;
    int32_t RegionPicture;
    uint16_t ClearStartTimeCond;
    uint16_t ClearEndTimeCond;
    uint8_t ClearEmoteCond;
    uint8_t padding0 : 7;
    uint8_t IsShowRegion : 1;
    int8_t padding1[2];
  };

  /* 264391 */
  struct RetainerTaskLvRange
  {
    uint8_t MinLv;
    uint8_t MaxLv;
    int8_t padding0[2];
  };

  /* 264392 */
  struct RetainerTaskNormal
  {
    int32_t Item;
    int16_t GatheringItem;
    int16_t FishParameter;
    uint8_t Stack[3];
    int8_t padding0[1];
  };

  /* 264393 */
  struct RetainerTaskRandomTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264394 */
  struct RetainerTaskRandom
  {
    RetainerTaskRandomTextStruct Text;
    int16_t SortId;
    int8_t padding0[2];
  };

  /* 264395 */
  struct Tomestones
  {
    int32_t CatalogId;
    uint16_t WeeklyCap;
    uint8_t Slot;
    int8_t WorkIndex;
  };

  /* 264396 */
  struct FateTextStruct
  {
    Component::Excel::StringOffset TitleText;
    Component::Excel::StringOffset DescriptionText;
    Component::Excel::StringOffset DescriptionText2;
    Component::Excel::StringOffset TodoName1;
    Component::Excel::StringOffset TodoName2;
    Component::Excel::StringOffset TodoName3;
  };

  /* 264397 */
  struct FateQuest
  {
    uint32_t ResultListener;
  };

  /* 264398 */
  struct Fate
  {
    FateTextStruct Text;
    FateQuest Quest;
    uint32_t TradeItemId;
    uint32_t GuardNpcLayoutId;
    int32_t EventRange;
    int32_t Icon;
    int32_t IconSmall;
    int32_t BGM;
    int32_t StarterTalkNpcLayoutId;
    uint16_t Achivement;
    uint16_t TodoValueType[3];
    uint8_t Rule;
    uint8_t Level;
    uint8_t SyncLv;
    uint8_t AcceptScreenImage;
    uint8_t CompleteScreenImage;
    uint8_t FailedScreenImage;
    uint8_t padding0 : 6;
    uint8_t IsQuest : 1;
    uint8_t Show2DMap : 1;
    int8_t padding1[1];
  };

  /* 264399 */
  struct FCActivityCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264400 */
  struct FCActivityCategory
  {
    FCActivityCategoryTextStruct Text;
    uint8_t Priority;
    int8_t padding0[3];
  };

  /* 264401 */
  struct FCAuthorityTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264402 */
  struct FCAuthority
  {
    FCAuthorityTextStruct Text;
    int32_t Category;
    uint8_t Sort;
    int8_t padding0[3];
  };

  /* 264403 */
  struct FCAuthorityCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264404 */
  struct FCAuthorityCategory
  {
    FCAuthorityCategoryTextStruct Text;
  };

  /* 264405 */
  struct CompanyActionTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Help;
  };

  /* 264406 */
  struct CompanyAction
  {
    CompanyActionTextStruct Text;
    uint32_t Price;
    int32_t Icon;
    uint8_t NeedRank;
    uint8_t UIPriority;
    int8_t padding0[2];
  };

  /* 264407 */
  struct FCCrestSymbol
  {
    uint8_t ColorNum;
    uint8_t FCRight;
    int8_t padding0[2];
  };

  /* 264408 */
  struct FCProfileTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264409 */
  struct FCProfile
  {
    FCProfileTextStruct Text;
    uint8_t Priority;
    int8_t padding0[3];
  };

  /* 264410 */
  struct ItemSeriesTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264411 */
  struct ItemSeries
  {
    ItemSeriesTextStruct Text;
  };

  /* 264412 */
  struct ItemSpecialBonusTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 264413 */
  struct ItemSpecialBonus
  {
    ItemSpecialBonusTextStruct Text;
  };

  /* 264414 */
  struct HousingYardObject
  {
    uint32_t Param;
    uint32_t EventHandler;
    uint32_t Item;
    uint8_t ID;
    uint8_t Category;
    uint8_t UseType;
    uint8_t LayoutLimit;
    uint8_t padding0 : 7;
    uint8_t Disposable : 1;
    int8_t padding1[3];
  };

  /* 264415 */
  struct HousingFurniture
  {
    uint32_t Param;
    uint32_t EventHandler;
    uint32_t Item;
    uint16_t ID;
    uint8_t Category;
    uint8_t UseType;
    uint8_t LayoutLimit;
    uint8_t padding0 : 6;
    uint8_t HasCrest : 1;
    uint8_t Disposable : 1;
    int8_t padding1[2];
  };

  /* 264416 */
  struct HousingExterior
  {
    uint16_t Region;
    uint8_t ID;
    uint8_t Category;
    uint8_t Size;
    int8_t padding0[1];
    int8_t padding1[2];
  };

  /* 264417 */
  struct HousingInterior
  {
    uint8_t ID;
    uint8_t Category;
    uint8_t Material;
    int8_t padding0[1];
  };

  /* 264418 */
  struct BeastTribeTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    Component::Excel::StringOffset ReputationValue;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 264419 */
  struct BeastTribe
  {
    BeastTribeTextStruct Text;
    uint32_t ReputationIcon;
    uint32_t RewardIcon;
  };

  /* 264420 */
  struct BeastReputationRankTextStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 264421 */
  struct BeastReputationRank
  {
    BeastReputationRankTextStruct Text;
    uint32_t Color;
    uint16_t MaxReputationValue;
    int8_t padding1[2];
  };

  /* 271695 */
  struct HousingPresetNameStruct
  {
    Component::Excel::StringOffset SGL;
    Component::Excel::StringOffset PLR;
    int8_t SGG;
    int8_t PLG;
    int8_t VOW;
    int8_t CNT;
    int8_t GEN;
    int8_t DEF;
    int8_t padding0[2];
  };

  /* 271696 */
  struct HousingPreset
  {
    HousingPresetNameStruct Name;
    int32_t Roof;
    int32_t Wall;
    int32_t Window;
    int32_t Door;
    int32_t Interior[10];
    uint16_t Region;
    uint8_t Size;
    int8_t padding1[1];
  };

  /* 271697 */
  struct HousingLayoutLimitStruct
  {
    uint8_t LimitNumSS;
    uint8_t LimitNumS;
    uint8_t LimitNumM;
    uint8_t LimitNumL;
  };

  /* 271698 */
  struct HousingLandStruct
  {
    uint32_t LandRange;
    uint32_t SignboardEObj;
    uint32_t StuckPopRange;
    uint32_t ExitPopRange;
    uint32_t InitPrice;
    uint8_t Size;
    int8_t padding0[3];
  };

  /* 271699 */
  struct HousingLandSet
  {
    HousingLandStruct Lands[60];
  };

  /* 271700 */
  struct GardeningSeed
  {
    uint32_t Crop;
    uint32_t HarvestIcon;
    uint16_t ModelId;
    uint8_t padding0 : 7;
    uint8_t SE : 1;
    int8_t padding1[1];
  };

  /* 271701 */
  struct HousingEmploymentNpcStruct
  {
    uint32_t ENpcId;
  };

  /* 271702 */
  struct HousingEmploymentNpcTypeStruct
  {
    HousingEmploymentNpcStruct ENpcType[10];
  };

  /* 282075 */
  struct PhysicsGroup
  {
    float SimulationTime[6];
    float PS3SimulationTime[6];
    float RootFollowingGame;
    float RootFollowingCutScene;
    int8_t ConfigSwitch[3];
    uint8_t padding0 : 6;
    uint8_t ForceAttractByPhysicsOff : 1;
    uint8_t ResetByLookAt : 1;
  };

  /* 326984 */
  struct Channeling
  {
    Component::Excel::StringOffset File;
    float WidthScale;
    uint8_t LimitDist;
    int8_t padding0[3];
  };

  /* 326985 */
  struct ModelChara
  {
    uint16_t SkeletonId;
    uint16_t SEPack;
    uint8_t ModelType;
    uint8_t PatternId;
    uint8_t ImeChanId;
    uint8_t PapVariation;
  };

  /* 326986 */
  struct BNpcState
  {
    Component::Excel::StringOffset Attribute[3];
    float Scale;
    int32_t LoopTimeline;
    uint16_t Idle;
    uint8_t Slot;
    int8_t OverRay[2];
    bool AttributeFlag[3];
  };

  /* 326987 */
  struct Transformation
  {
    uint16_t Action[2];
    int16_t ModelChara;
    uint8_t padding0 : 7;
    uint8_t ExHotbarEnableConfig : 1;
    int8_t padding1[1];
  };

  /* 326988 */
  struct BNpcBase
  {
    float Scale;
    int32_t EventHandler;
    uint16_t NormalAI;
    uint16_t Model;
    uint16_t Customize;
    uint16_t Equipment;
    uint16_t SEPack;
    uint8_t Battalion;
    uint8_t LinkRace;
    uint8_t Rank;
    uint8_t Special;
    uint8_t Parts;
    uint8_t IsTargetLine : 1;
    uint8_t IsDisplayLevel : 1;
    uint8_t padding0 : 6;
  };

  /* 326989 */
  struct BNpcParts
  {
    Component::Excel::StringOffset Attribute[4];
    float OffsetX[4];
    float OffsetZ[4];
    uint16_t Parts[4];
    bool AttDefault[4];
    bool Timeline[4];
  };

  /* 326991 */
  struct Carry
  {
    uint64_t Model;
    int32_t Timeline;
    int8_t padding0[4];
  };

  /* 326993 */
  struct ENpcEventHandlerStruct
  {
    uint32_t EventHandler;
  };

  /* 326994 */
  struct ENpcBase
  {
    ENpcEventHandlerStruct EventHandler[32];
    uint64_t Weapon;
    uint64_t SubWeapon;
    float Scale;
    uint32_t Equip[10];
    uint16_t IdleTimeline;
    uint16_t Model;
    uint16_t EquipPreset;
    uint16_t Behavior;
    uint16_t DefaultBalloon;
    uint8_t Customize[26];
    uint8_t Voice;
    uint8_t WeaponStain;
    uint8_t SubWeaponStain;
    uint8_t Stain[10];
    uint8_t Invisibility;
    uint8_t padding0 : 5;
    uint8_t Important : 1;
    uint8_t Visor : 1;
    uint8_t NotRewriteHeight : 1;
    int8_t padding1[1];
  };

  /* 326995 */
  struct Battalion
  {
    bool Table[12];
  };

  /* 326996 */
  struct EventActionTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 326997 */
  struct EventAction
  {
    EventActionTextStruct Text;
    uint16_t Icon;
    uint16_t ActionTimeline_Start;
    uint16_t ActionTimeline_Loop;
    uint16_t ActionTimeline_End;
    uint8_t Time;
    int8_t padding0[3];
  };

  /* 326998 */
  struct Omen
  {
    Component::Excel::StringOffset Path;
    Component::Excel::StringOffset PathAlly;
    uint8_t Type;
    uint8_t padding0 : 6;
    uint8_t LargeScale : 1;
    uint8_t RestrictYScale : 1;
    int8_t padding1[2];
  };

  /* 326999 */
  struct NpcEquip
  {
    uint64_t WeaponModel;
    uint64_t SubWeaponModel;
    uint32_t Equip[10];
    uint8_t WeaponStain;
    uint8_t SubWeaponStain;
    uint8_t Stain[10];
    uint8_t padding0 : 7;
    uint8_t Visor : 1;
    int8_t padding1[3];
  };

  /* 335954 */
  struct ChocoboTaxi
  {
    uint32_t Terminus;
    int32_t Territory;
    int32_t Path;
    uint16_t Fare;
    uint8_t TimeRequired;
    int8_t padding0[1];
  };

  /* 335955 */
  struct CutsceneMotion
  {
    float WALK_LOOP_SPEED;
    float RUN_LOOP_SPEED;
    float SLOWWALK_LOOP_SPEED;
    float SLOWRUN_LOOP_SPEED;
    float BATTLEWALK_LOOP_SPEED;
    float BATTLERUN_LOOP_SPEED;
    float DASH_LOOP_SPEED;
    uint8_t TURN_CW90_FRAME;
    uint8_t TURN_CCW90_FRAME;
    uint8_t TURN_CW180_FRAME;
    uint8_t TURN_CCW180_FRAME;
  };

  /* 335956 */
  struct EmoteMode
  {
    uint32_t StartEmote;
    uint32_t EndEmote;
    uint8_t ConditionMode;
    uint8_t padding0 : 4;
    uint8_t Move : 1;
    uint8_t Camera : 1;
    uint8_t EndOnRotate : 1;
    uint8_t EndOnEmote : 1;
    int8_t padding1[2];
  };

  /* 337601 */
  struct GimmickJump
  {
    uint32_t LoopMotion;
    uint32_t EndMotion;
    uint16_t FallDamage;
    int8_t Height;
    uint8_t padding0 : 7;
    uint8_t StartClient : 1;
  };

  /* 339572 */
  struct LinkRace
  {
    bool Link[4];
  };

  /* 342251 */
  struct BGMScene
  {
    uint8_t padding0 : 3;
    uint8_t EnableDisableRestart : 1;
    uint8_t Resume : 1;
    uint8_t EnablePassEnd : 1;
    uint8_t ForceAutoReset : 1;
    uint8_t IgnoreBattle : 1;
    int8_t padding1[3];
  };

  /* 342296 */
  struct VFX
  {
    Component::Excel::StringOffset Path;
  };

  /* 342297 */
  struct Lockon
  {
    Component::Excel::StringOffset File;
  };

  /* 342298 */
  struct Resident
  {
    int32_t Value;
    int32_t Model;
    uint8_t Type;
    int8_t padding0[3];
  };

  /* 342313 */
  struct MotionTimelineAdvanceBlend
  {
    Component::Excel::StringOffset MotionTimelineName;
    Component::Excel::StringOffset NextMotionTimelineName;
  };

  /* 342406 */
  struct BGM
  {
    Component::Excel::StringOffset Path;
    float DisableRestartResetTime;
    uint8_t Priority;
    uint8_t SpecialMode;
    uint8_t padding0 : 5;
    uint8_t DisableRestartTimeOut : 1;
    uint8_t DisableRestart : 1;
    uint8_t PassEnd : 1;
    int8_t padding1[1];
  };

  /* 342407 */
  struct BGMSituation
  {
    uint16_t DaytimeID;
    uint16_t NightID;
    uint16_t BattleID;
    uint16_t DaybreakID;
    uint16_t TwilightID;
    int8_t padding0[2];
  };

  /* 342408 */
  struct BGMFade
  {
    int32_t SceneOut;
    int32_t SceneIn;
    int32_t FadeType;
  };

  /* 342409 */
  struct BGMFadeType
  {
    float FadeOutTime;
    float FadeInTime;
    float FadeInStartTime;
    float ResumeFadeInTime;
  };

  /* 342410 */
  struct BGMSystemDefine
  {
    float ValueFloat;
  };

  /* 342463 */
  struct Ballista
  {
    uint16_t BNpc;
    uint16_t Angle;
    uint16_t Action[2];
    uint8_t Bullet;
    int8_t Near;
    int8_t Far;
    int8_t padding0[1];
  };

  /* 362336 */
  struct SpecialShopItem
  {
    uint32_t SetNum[2];
    uint32_t NumOfCurrency[3];
    int32_t ItemId[2];
    int32_t Category[2];
    int32_t Currency[3];
    int32_t Quest[2];
    int32_t Achievement;
    bool IsCurrencyHq[3];
    int8_t padding0[1];
  };

  /* 362337 */
  struct GuildleveAssignment
  {
    uint32_t Talk;
    uint32_t UnlockQuest;
    uint32_t DecideQuest;
    uint8_t NeedGrandCompanyRank;
    uint8_t padding0 : 5;
    uint8_t HaveImmortalLeve : 1;
    uint8_t HaveTwinAdderLeve : 1;
    uint8_t HaveMaelstromLeve : 1;
    int8_t padding1[2];
  };

  /* 362338 */
  struct GuildleveAssignmentTalkParamStruct
  {
    uint32_t Gesture;
    int32_t Shape;
    uint8_t Turn;
    int8_t LipSync;
    int8_t Facial;
    uint8_t padding0 : 7;
    uint8_t LookAt : 1;
  };

  /* 362339 */
  struct GuildleveAssignmentTalkTextStruct
  {
    Component::Excel::StringOffset Talk[8];
  };

  /* 362340 */
  struct GuildleveAssignmentTalk
  {
    GuildleveAssignmentTalkParamStruct Param[5];
    GuildleveAssignmentTalkTextStruct Text;
  };

  /* 362341 */
  struct EventIconType
  {
    uint32_t Announce;
    uint32_t Map;
    uint8_t Num;
    int8_t padding0[3];
  };

  /* 362342 */
  struct GatheringItem
  {
    int32_t ItemId;
    uint8_t Level;
    uint8_t padding0 : 7;
    uint8_t IsHiddenForNotebook : 1;
    int8_t padding1[2];
  };

  /* 362343 */
  struct DefaultTalkParamStruct
  {
    uint16_t Gesture;
    uint16_t Facial;
    uint8_t Turn;
    uint8_t LipSync;
    uint8_t Shape;
    uint8_t padding0 : 7;
    uint8_t IsAutoShake : 1;
  };

  /* 362344 */
  struct DefaultTalkTextStruct
  {
    Component::Excel::StringOffset Talk[3];
  };

  /* 362345 */
  struct DefaultTalk
  {
    DefaultTalkParamStruct Param[3];
    DefaultTalkTextStruct Text;
  };

  /* 362346 */
  struct CraftLeveTalkParamStruct
  {
    uint32_t Gesture;
    int32_t Shape;
    uint8_t Turn;
    int8_t LipSync;
    int8_t Facial;
    uint8_t padding0 : 7;
    uint8_t LookAt : 1;
  };

  /* 362347 */
  struct CraftLeveTalkTextStruct
  {
    Component::Excel::StringOffset Talk[6];
  };

  /* 362348 */
  struct CraftLeveTalk
  {
    CraftLeveTalkParamStruct Param[6];
    CraftLeveTalkTextStruct Text;
  };

  /* 362349 */
  struct SwitchTalkCaseStruct
  {
    uint32_t CaseCondition;
    uint32_t Talk;
  };

  /* 362350 */
  struct SwitchTalk
  {
    SwitchTalkCaseStruct TalkCase[16];
  };

  /* 362351 */
  struct BattleLeveTimeStruct
  {
    uint16_t RoutePointTime;
  };

  /* 362352 */
  struct BattleLeveEntryStruct
  {
    uint32_t NameId;
    uint32_t Param[6];
    int32_t BaseId;
    int32_t DropEventItemId;
    uint16_t Level;
    uint8_t DropEventItemMax;
    uint8_t DropEventItemRate;
    uint8_t NumOfAppearance[8];
  };

  /* 362353 */
  struct BattleLeveTodoStruct
  {
    uint8_t TodoSequence;
  };

  /* 362354 */
  struct BattleLeve
  {
    BattleLeveTimeStruct RoutePointTime[8];
    BattleLeveEntryStruct Entry[8];
    BattleLeveTodoStruct Todo[8];
    int32_t Rule;
    uint16_t Objective[3];
    uint16_t Help[2];
    uint8_t Variation;
    int8_t padding0[1];
  };

  /* 362355 */
  struct GatheringLeveRoute
  {
    int32_t Point[10];
    int32_t BNpcPopRange[10];
  };

  /* 362356 */
  struct CompanyLeveTimeStruct
  {
    uint16_t RoutePointTime;
  };

  /* 362357 */
  struct CompanyLeveEntryStruct
  {
    uint32_t NameId;
    uint32_t Param[6];
    int32_t BaseId;
    int32_t DropEventItemId;
    uint16_t Level;
    uint8_t DropEventItemMax;
    uint8_t DropEventItemRate;
    uint8_t NumOfAppearance[8];
  };

  /* 362358 */
  struct CompanyLeveTodoStruct
  {
    uint8_t TodoSequence;
  };

  /* 362359 */
  struct CompanyLeve
  {
    CompanyLeveTimeStruct RoutePointTime[8];
    CompanyLeveEntryStruct Entry[8];
    CompanyLeveTodoStruct Todo[8];
    int32_t Rule;
    uint8_t Variation;
    int8_t padding0[3];
  };

  /* 362360 */
  struct QuestBattleDefineStruct
  {
    Component::Excel::StringOffset DefineName;
    uint32_t DefineValue;
  };

  /* 362361 */
  struct QuestBattle
  {
    QuestBattleDefineStruct Define[100];
    int32_t Quest;
    uint16_t LimitTime;
    uint16_t SyncLevel;
    uint8_t SubNo;
    int8_t padding0[3];
  };

  /* 362362 */
  struct CustomTalkDefineStruct
  {
    Component::Excel::StringOffset Name;
    uint32_t Value;
  };

  /* 362363 */
  struct CustomTalkTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362364 */
  struct CustomTalk
  {
    CustomTalkDefineStruct Define[30];
    CustomTalkTextStruct Text;
    Component::Excel::StringOffset Script;
    uint32_t MapIcon;
    uint8_t padding0 : 1;
    uint8_t ListenHousing : 1;
    uint8_t ListenEnterTerritory : 1;
    uint8_t ListenEmote : 1;
    uint8_t TargetingPossibleCallback : 1;
    uint8_t ConditionCallback : 1;
    uint8_t AcceptCallback : 1;
    uint8_t ClientEvent : 1;
    int8_t padding1[3];
  };

  /* 362365 */
  struct StorySequenceStruct
  {
    uint32_t CompletedQuest[3];
    uint32_t AcceptedQuest[3];
    uint32_t LayerSet[2];
    uint16_t Sequence;
    uint8_t CompletedQuestOperator;
    uint8_t AcceptedQuestOperator;
    uint8_t AcceptedQuestSequence[3];
    int8_t padding0[1];
  };

  /* 362366 */
  struct StoryDefineStruct
  {
    Component::Excel::StringOffset Name;
    uint32_t Value;
  };

  /* 362367 */
  struct StoryVisibleListenerStruct
  {
    uint32_t Listener;
    uint16_t SequenceBegin;
    uint16_t SequenceEnd;
  };

  /* 362368 */
  struct Story
  {
    StoryDefineStruct Define[40];
    StorySequenceStruct Sequence[110];
    StoryVisibleListenerStruct VisibleListener[80];
    Component::Excel::StringOffset Script;
    uint16_t LayerSetTerritoryType[2];
  };

  /* 362369 */
  struct CompanyLeveRule
  {
    Component::Excel::StringOffset Script;
    uint16_t Objective;
    uint16_t Help;
  };

  /* 362448 */
  struct AethernetStruct
  {
    uint32_t PopRange;
    uint16_t TransferName;
    int8_t padding0[2];
  };

  /* 362451 */
  struct AetheryteSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    uint32_t DefineValue;
  };

  /* 362452 */
  struct GatheringTypeTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 362453 */
  struct GatheringType
  {
    GatheringTypeTextStruct Text;
    int32_t MapIcon;
    int32_t RareMapIcon;
  };

  /* 362454 */
  struct GatheringConditionTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 362455 */
  struct GatheringCondition
  {
    GatheringConditionTextStruct Text;
  };

  /* 362456 */
  struct GatheringPointBonusTypeTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 362457 */
  struct GatheringPointBonusType
  {
    GatheringPointBonusTypeTextStruct Text;
  };

  /* 362458 */
  struct GatheringExp
  {
    uint16_t Exp;
    int8_t padding0[2];
  };

  /* 362459 */
  struct FishingRecordType
  {
    int32_t NameId;
    uint16_t Rank[2];
  };

  /* 362460 */
  struct QuestSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    int32_t DefineValue;
  };

  /* 362461 */
  struct EventSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    uint32_t DefineValue;
  };

  /* 362462 */
  struct JournalGenreTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362463 */
  struct JournalGenre
  {
    JournalGenreTextStruct Text;
    int32_t Icon;
    uint8_t Category;
    int8_t padding0[3];
  };

  /* 362464 */
  struct LeveSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    int32_t DefineValue;
  };

  /* 362465 */
  struct BattleLeveRule
  {
    Component::Excel::StringOffset Script;
  };

  /* 362466 */
  struct LeveVfx
  {
    Component::Excel::StringOffset Path;
    int32_t Icon;
  };

  /* 362467 */
  struct LeveStringTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362468 */
  struct LeveString
  {
    LeveStringTextStruct Text;
  };

  /* 362469 */
  struct GatheringLeveRule
  {
    Component::Excel::StringOffset Script;
  };

  /* 362470 */
  struct LeveClientTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362471 */
  struct LeveClient
  {
    LeveClientTextStruct Text;
  };

  /* 362472 */
  struct LeveRewardItem
  {
    int32_t ItemGroup[8];
    uint8_t ItemGroupRate[8];
  };

  /* 362473 */
  struct LeveRewardItemGroup
  {
    int32_t Item[8];
    uint16_t Stack[8];
    bool HQ[8];
  };

  /* 362474 */
  struct GuildleveAssignmentCategory
  {
    int32_t Filter[8];
  };

  /* 362475 */
  struct LeveAssignmentTypeTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362476 */
  struct LeveAssignmentType
  {
    LeveAssignmentTypeTextStruct Text;
    int32_t Icon;
    uint8_t padding0 : 7;
    uint8_t Faction : 1;
    int8_t padding1[3];
  };

  /* 362477 */
  struct GuildleveEvaluationTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362478 */
  struct GuildleveEvaluation
  {
    GuildleveEvaluationTextStruct Text;
  };

  /* 362479 */
  struct OpeningSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    uint32_t DefineValue;
  };

  /* 362480 */
  struct StorySystemDefine
  {
    Component::Excel::StringOffset DefineName;
    uint32_t DefineValue;
  };

  /* 362481 */
  struct PresetCamera
  {
    float PosX;
    float PosY;
    float PosZ;
    float Elezene;
    float Lalafell;
    float Migote;
    float Roegadyn;
    float Hyuran_F;
    float Elezene_F;
    float Lalafell_F;
    float Migote_F;
    float Roegadyn_F;
    uint16_t EID;
    int8_t padding0[2];
  };

  /* 362482 */
  struct PresetCameraAdjust
  {
    float Hyuran_M;
    float Hyuran_F;
    float Elezene_M;
    float Elezene_F;
    float Lalafell_M;
    float Lalafell_F;
    float Migote_M;
    float Migote_F;
    float Roegadyn_M;
    float Roegadyn_F;
  };

  /* 362483 */
  struct Cutscene
  {
    Component::Excel::StringOffset Path;
  };

  /* 362484 */
  struct DirectorSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    int32_t DefineValue;
  };

  /* 362485 */
  struct SE
  {
    Component::Excel::StringOffset Path;
  };

  /* 362486 */
  struct RetainerTaskParameter
  {
    int32_t TimeCorrectionNormal;
    int32_t TimeCorrectionRandom;
    int16_t BattleStack[2];
    int16_t GatheringStack[2];
    int16_t FishingStack[2];
  };

  /* 362487 */
  struct ChocoboTaxiStandTextStruct
  {
    Component::Excel::StringOffset Destination;
  };

  /* 362488 */
  struct ChocoboTaxiStand
  {
    ChocoboTaxiStandTextStruct Text;
    uint16_t Taxi[8];
  };

  /* 362489 */
  struct DefaultTalkLipSyncType
  {
    int32_t ActionTimeLine;
  };

  /* 362490 */
  struct GCShopItemCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 362491 */
  struct GCShopItemCategory
  {
    GCShopItemCategoryTextStruct Text;
  };

  /* 362492 */
  struct GCShop
  {
    int32_t ItemStartIndex;
    int32_t ItemEndIndex;
  };

  /* 362493 */
  struct QuestBattleSystemDefine
  {
    Component::Excel::StringOffset DefineName;
    uint32_t DefineValue;
  };

  /* 363134 */
  struct ContentTalkTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 363135 */
  struct ContentTalk
  {
    ContentTalkTextStruct Text;
    uint8_t Param;
    int8_t padding0[3];
  };

  /* 363136 */
  struct ContentTalkParam
  {
    uint32_t Gesture;
    uint8_t Turn;
    uint8_t Shape;
    int8_t LipSync;
    int8_t Facial;
    uint8_t padding0 : 7;
    uint8_t LookAt : 1;
    int8_t padding1[3];
  };

  /* 363137 */
  struct ContentNpcTalk
  {
    uint32_t Talk[8];
    int32_t Type;
  };

  /* 363138 */
  struct GuildOrderOfficer
  {
    uint32_t Talk[6];
  };

  /* 363139 */
  struct GuildOrderGuide
  {
    uint32_t Talk[6];
  };

  /* 363140 */
  struct GimmickRect
  {
    uint32_t LayoutId;
    uint32_t Param0;
    uint32_t Param1;
    uint8_t TriggerIn;
    uint8_t TriggerOut;
    int8_t padding0[2];
  };

  /* 363141 */
  struct GimmickAccessor
  {
    uint32_t Param0;
    uint32_t Param1;
    uint32_t Param2;
    int32_t Type;
  };

  /* 367152 */
  struct ScenarioTextStruct
  {
    Component::Excel::StringOffset Label;
    Component::Excel::StringOffset Text;
  };

  /* 367156 */
  struct ArrayEventHandler
  {
    uint32_t EventHandler[16];
  };

  /* 367157 */
  struct ShopTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 367158 */
  struct ShopStruct
  {
    ShopTextStruct Text;
    uint32_t MapIcon;
    int32_t Quest;
    int32_t QualifiedTalk;
    int32_t UnqualifiedTalk;
    int32_t Item[40];
    uint8_t BeastTribe;
    uint8_t BeastReputationRank;
    uint8_t padding0 : 7;
    uint8_t PriceChangeFlag : 1;
    int8_t padding1[1];
  };

  /* 367159 */
  struct ShopItem
  {
    uint32_t PriceMinParam;
    uint32_t PriceParam;
    uint32_t PriceMaxParam;
    int32_t ItemId;
    int32_t StainId;
    int32_t Quest[2];
    int32_t Achievement;
    uint8_t padding0 : 7;
    uint8_t IsHQ : 1;
    int8_t padding1[3];
  };

  /* 367160 */
  struct GrandCompanySealShopItem
  {
    uint32_t SetNum;
    uint32_t Seal;
    int32_t ItemId;
    int32_t ValidRank;
    int32_t Category;
  };

  /* 367161 */
  struct WarpTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Question;
  };

  /* 367162 */
  struct Warp
  {
    WarpTextStruct Text;
    uint32_t PopRange;
    uint32_t QualifiedPreTalk;
    uint32_t UnqualifiedPreTalk;
    uint32_t UnqualifiedGilPreTalk;
    uint16_t WarpCondition;
    uint16_t Logic;
    uint16_t PreCutScene;
    uint16_t PostCutScene;
    uint8_t padding0 : 7;
    uint8_t SkipCutSceneConfig : 1;
    int8_t padding1[3];
  };

  /* 367163 */
  struct WarpLogicDefineStruct
  {
    Component::Excel::StringOffset Name;
    uint32_t Value;
  };

  /* 367164 */
  struct WarpLogicTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Yes;
    Component::Excel::StringOffset No;
  };

  /* 367165 */
  struct WarpLogic
  {
    WarpLogicDefineStruct Define[10];
    WarpLogicTextStruct Text;
    Component::Excel::StringOffset Script;
    uint32_t MapIcon;
    uint8_t padding0 : 7;
    uint8_t AcceptCallback : 1;
    int8_t padding1[3];
  };

  /* 367166 */
  struct WarpCondition
  {
    uint32_t CompletedQuest[3];
    uint32_t NotAcceptedQuest;
    uint16_t Gil;
    uint16_t Reward;
    uint16_t ClassLevel;
    uint8_t CompletedQuestOperator;
    int8_t padding0[1];
  };

  /* 367167 */
  struct SpecialShopTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 367168 */
  struct SpecialShop
  {
    SpecialShopTextStruct Text;
    SpecialShopItem Item[160];
    int32_t Quest;
    int32_t QualifiedTalk;
    int32_t UnqualifiedTalk;
    uint8_t padding1 : 7;
    uint8_t IsCurrencyType : 1;
    int8_t padding2[3];
  };

  struct Shop
  {
    ShopTextStruct Text;
    uint32_t MapIcon;
    int32_t Quest;
    int32_t QualifiedTalk;
    int32_t UnqualifiedTalk;
    int32_t Item[40];
    uint8_t BeastTribe;
    uint8_t BeastReputationRank;
    uint8_t padding0 : 7;
    uint8_t PriceChangeFlag : 1;
    int8_t padding1[1];
  };

  /* 367169 */
  struct OpeningDefineStruct
  {
    Component::Excel::StringOffset Name;
    uint32_t Value;
  };

  /* 367170 */
  struct Opening
  {
    OpeningDefineStruct Define[40];
    Component::Excel::StringOffset Script;
    uint32_t Quest;
  };

  /* 367972 */
  struct QuestRepeatFlag
  {
    uint32_t Quest;
  };

  /* 367973 */
  struct EventIconPriority
  {
    uint32_t Icon[16];
  };

  /* 370975 */
  struct PvPAction
  {
    uint16_t Action;
    uint16_t Trait[3];
    uint8_t SkillPoint;
    uint8_t Rank;
    bool GrandCompany[3];
    int8_t padding0[1];
    int8_t padding1[2];
  };

  /* 370976 */
  struct PvPTrait
  {
    uint16_t Trait[3];
    int8_t padding0[2];
  };

  /* 370977 */
  struct MateriaJoinRate
  {
    float Rate[4];
    float HQRate[4];
  };

  /* 370978 */
  struct ItemLevel
  {
    uint16_t BaseParam[74];
  };

  /* 370979 */
  struct Buddy
  {
    Component::Excel::StringOffset ActionSE[4];
    int32_t BaseEquip[3];
    uint8_t Base;
    int8_t padding0[3];
  };

  /* 370980 */
  struct BuddyItem
  {
    uint16_t Item;
    uint8_t Status;
    uint8_t padding0 : 6;
    uint8_t UseField : 1;
    uint8_t UseTraining : 1;
  };

  /* 370981 */
  struct PvPRankTextStruct
  {
    Component::Excel::StringOffset PvPTitleMale[3];
    Component::Excel::StringOffset PvPTitleFemale[3];
  };

  /* 370982 */
  struct PvPRank
  {
    PvPRankTextStruct Text;
    uint32_t Point;
  };

  /* 370983 */
  struct RelicMateria
  {
    uint8_t GradeMax;
    int8_t padding0[3];
  };

  /* 370986 */
  struct CraftCrystalTypeStruct
  {
    int32_t ItemId;
  };

  /* 370987 */
  struct RecipeElementTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 370988 */
  struct RecipeElement
  {
    RecipeElementTextStruct Text;
  };

  /* 370989 */
  struct GatheringItemPoint
  {
    uint32_t GatheringPointId;
  };

  /* 370990 */
  struct FishParameterTextStruct
  {
    Component::Excel::StringOffset NoteHelp;
  };

  /* 370991 */
  struct FishParameter
  {
    FishParameterTextStruct Text;
    int32_t ItemId;
    int32_t Territory;
    uint8_t Level;
    uint8_t RecordType;
    uint8_t padding0 : 7;
    uint8_t IsFishPrint : 1;
    int8_t padding1[1];
  };

  /* 370992 */
  struct FishingSpotTextStruct
  {
    Component::Excel::StringOffset SpotName;
  };

  /* 370993 */
  struct FishingSpot
  {
    FishingSpotTextStruct Text;
    int32_t Category;
    int32_t TerritoryType;
    int32_t NameLayout;
    int32_t Target[10];
    uint16_t MakerType;
    uint16_t SpotNameId;
    int16_t MakerPosX;
    int16_t MakerPosY;
    uint8_t Level;
    uint8_t SortKey;
    uint8_t padding0 : 7;
    uint8_t Rare : 1;
    int8_t padding1[1];
  };

  /* 370994 */
  struct JournalCategoryTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 370995 */
  struct JournalCategory
  {
    JournalCategoryTextStruct Text;
    uint8_t SeparateType;
    uint8_t DataType;
    int8_t padding0[2];
  };

  /* 370996 */
  struct InstanceContentType
  {
    uint8_t Sortkey;
    uint8_t Genre;
    uint8_t ContentType;
    int8_t padding0[1];
  };

  /* 370997 */
  struct InstanceContentBuff
  {
    uint16_t ParamBase;
    uint16_t ParamAdd;
  };

  /* 370998 */
  struct GCSupplyDutyReward
  {
    uint32_t ExpOfMunition;
    uint32_t ExpOfSupplies;
    uint32_t SealsOfBooty;
    uint32_t SealsOfMunition;
    uint32_t SealsOfSupplies;
  };

  /* 370999 */
  struct GCSupplyDefine
  {
    uint32_t Value;
  };

  /* 371000 */
  struct CycleTime
  {
    uint32_t FirstCycleOffset;
    uint32_t Cycle;
  };

  /* 371001 */
  struct CutsceneWorkIndex
  {
    uint16_t WorkIndex;
    int8_t padding0[2];
  };

  /* 374114 */
  struct GatheringNotebookList
  {
    int32_t ItemId[100];
    uint8_t ItemNum;
    int8_t padding0[3];
  };

  /* 374115 */
  struct RecipeNotebookList
  {
    int32_t RecipeId[100];
    int32_t RecipeId1[30];
    uint8_t RecipeNum;
    int8_t padding0[3];
  };

  /* 374116 */
  struct CompleteJournalTextStruct
  {
    Component::Excel::StringOffset Name;
  };

  /* 374117 */
  struct CompleteJournal
  {
    CompleteJournalTextStruct Text;
    uint32_t Id;
    uint32_t Separate;
    int32_t Icon;
    int32_t CutScene[24];
    uint16_t Level;
    uint8_t LevelOffset;
    int8_t padding0[1];
  };

  /* 374118 */
  struct LegacyQuestTextStruct
  {
    Component::Excel::StringOffset Name;
    Component::Excel::StringOffset Journal;
  };

  /* 374119 */
  struct LegacyQuest
  {
    LegacyQuestTextStruct Text;
    uint16_t LegacyQuestId;
    uint16_t SortKey;
    uint8_t Genre;
    int8_t padding0[3];
  };

  /* 374121 */
  struct GCSupplyDuty_WoodWorkerStruct
  {
    int32_t Item_wdk[3];
    uint8_t Stack_wdk[3];
    int8_t padding0[1];
  };

  /* 374122 */
  struct GCSupplyDuty_CulinarianStruct
  {
    int32_t Item_cul[3];
    uint8_t Stack_cul[3];
    int8_t padding1[1];
  };

  /* 374123 */
  struct GCSupplyDuty_AlchemistStruct
  {
    int32_t Item_alc[3];
    uint8_t Stack_alc[3];
    int8_t padding2[1];
  };

  /* 374124 */
  struct GCSupplyDuty_ArmourerStruct
  {
    int32_t Item_arm[3];
    uint8_t Stack_arm[3];
    int8_t padding3[1];
  };

  /* 374125 */
  struct GCSupplyDuty_TannerStruct
  {
    int32_t Item_tan[3];
    uint8_t Stack_tan[3];
    int8_t padding4[1];
  };

  /* 374126 */
  struct GCSupplyDuty_GoldSmithStruct
  {
    int32_t Item_gld[3];
    uint8_t Stack_gld[3];
    int8_t padding5[1];
  };

  /* 374127 */
  struct GCSupplyDuty_WeaverStruct
  {
    int32_t Item_wvr[3];
    uint8_t Stack_wvr[3];
    int8_t padding6[1];
  };

  /* 374128 */
  struct GCSupplyDuty_BlackSmithStruct
  {
    int32_t Item_bsm[3];
    uint8_t Stack_bsm[3];
    int8_t padding7[1];
  };

  /* 374129 */
  struct GCSupplyDuty_MinerStruct
  {
    int32_t Item_min[3];
    uint8_t Stack_min[3];
    int8_t padding8[1];
  };

  /* 374130 */
  struct GCSupplyDuty_HarvesterStruct
  {
    int32_t Item_hrv[3];
    uint8_t Stack_hrv[3];
    int8_t padding9[1];
  };

  /* 374131 */
  struct GCSupplyDuty_FishermanStruct
  {
    int32_t Item_fsh[3];
    uint8_t Stack_fsh[3];
    int8_t padding10[1];
  };

  /* 374132 */
  struct GCSupplyDuty
  {
    GCSupplyDuty_WoodWorkerStruct WoodWorker;
    GCSupplyDuty_CulinarianStruct Culinarian;
    GCSupplyDuty_AlchemistStruct Alchemist;
    GCSupplyDuty_ArmourerStruct Armourer;
    GCSupplyDuty_TannerStruct Tanner;
    GCSupplyDuty_GoldSmithStruct GoldSmith;
    GCSupplyDuty_WeaverStruct Weaver;
    GCSupplyDuty_BlackSmithStruct BlackSmith;
    GCSupplyDuty_MinerStruct Miner;
    GCSupplyDuty_HarvesterStruct Harvester;
    GCSupplyDuty_FishermanStruct Fisherman;
  };

  /* 374133 */
  struct GuildOrderTextStruct
  {
    Component::Excel::StringOffset OperationText;
    Component::Excel::StringOffset OrderText[2];
    Component::Excel::StringOffset SummaryText;
  };

  /* 374134 */
  struct GuildOrderRewardStruct
  {
    uint32_t Exp[2];
    uint32_t Gil[2];
    uint32_t Seal[2];
    uint32_t Item[2];
    uint16_t Stack[2];
    bool HQ[2];
    int8_t padding0[2];
  };

  /* 374135 */
  struct GuildOrder
  {
    GuildOrderTextStruct Text;
    GuildOrderRewardStruct Reward;
    uint32_t OfficerBase;
  };

  /* 374137 */
  struct DailySupplyItem
  {
    int32_t Item[8];
    uint8_t Count[8];
    uint8_t Level[8];
  };

  /* 379812 */
  struct BehaviorPath
  {
    uint8_t padding0 : 4;
    uint8_t IsTurnTransition : 1;
    uint8_t IsFadeOut : 1;
    uint8_t IsFadeIn : 1;
    uint8_t IsWalking : 1;
    int8_t padding1[3];
  };

  /* 379813 */
  struct Behavior
  {
    uint32_t Cont0_TypeArg0;
    uint32_t Cont1_TypeArg1;
    int32_t ActionArg;
    uint16_t Balloon;
    uint16_t Cont0_TypeArg1;
    uint16_t Cont1_TypeArg0;
    int16_t ActionArg2;
    uint8_t Pack;
    uint8_t Caster;
    uint8_t Target;
    uint8_t Action;
    uint8_t Cond0_Target;
    uint8_t Cond0_Type;
    uint8_t Cond1_Target;
    uint8_t Cond1_Type;
  };

  /* 383306 */
  struct BalloonTextStruct
  {
    Component::Excel::StringOffset Message;
  };

  /* 383307 */
  struct Balloon
  {
    BalloonTextStruct Text;
    uint8_t padding0 : 7;
    uint8_t Slowly : 1;
    int8_t padding1[3];
  };

  /* 389006 */
  struct Knockback
  {
    float Distance;
    float Speed;
    float NearDistance;
    float DirectionArg;
    uint8_t Direction;
    uint8_t padding0 : 6;
    uint8_t CancelMove : 1;
    uint8_t Motion : 1;
    int8_t padding1[2];
  };

  /* 390890 */
  struct Permission
  {
    bool Flag[58];
    int8_t padding0[2];
  };

  /* 391161 */
  struct InstanceContentTextDataTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 391162 */
  struct InstanceContentTextData
  {
    InstanceContentTextDataTextStruct Text;
  };

  /* 393785 */
  struct InstanceContentGuide
  {
    uint32_t InstanceContent;
    uint32_t EventRange;
  };

  /* 397676 */
  struct GimmickYesNoTextStruct
  {
    Component::Excel::StringOffset Text1;
    Component::Excel::StringOffset Text2;
    Component::Excel::StringOffset Text3;
  };

  /* 397677 */
  struct GimmickYesNo
  {
    GimmickYesNoTextStruct Text;
  };

  /* 397678 */
  struct GimmickBillTextStruct
  {
    Component::Excel::StringOffset Message;
  };

  /* 397679 */
  struct GimmickBill
  {
    GimmickBillTextStruct Text;
  };

  /* 399529 */
  struct FateEventParamStruct
  {
    uint32_t Gesture;
    int32_t LipSync;
    int32_t Facial;
    int32_t Shape;
    uint8_t Turn;
    uint8_t WidgetType;
    uint8_t padding0 : 7;
    uint8_t IsAutoShake : 1;
    int8_t padding1[1];
  };

  /* 399530 */
  struct FateEventTextStruct
  {
    Component::Excel::StringOffset MessageText[8];
  };

  /* 399531 */
  struct FateEvent
  {
    FateEventParamStruct Param[8];
    FateEventTextStruct Text;
  };

  /* 399532 */
  struct NpcYellTextStruct
  {
    Component::Excel::StringOffset Text;
  };

  /* 399533 */
  struct NpcYell
  {
    NpcYellTextStruct NpcText;
    float BalloonTime;
    float BattleTalkTime;
    uint8_t OutputType;
    uint8_t padding0 : 7;
    uint8_t IsBalloonSlow : 1;
    int8_t padding1[2];
  };

  /* 421681 */
  struct AnimationLOD
  {
    float CameraDistance;
    float SampleInterval;
    int8_t BoneLOD;
    bool AnimationEnable[8];
    int8_t padding0[3];
  };

  /* 450837 */
  struct MotionTimelineBlendTable
  {
    uint8_t DestBlendGroup;
    uint8_t SrcBlendGroup;
    uint8_t BlendFrame_PC;
    uint8_t BlendFrame_TypeA;
    uint8_t BlendFrame_TypeB;
    uint8_t BlendFrame_TypeC;
    int8_t padding0[2];
  };



}
