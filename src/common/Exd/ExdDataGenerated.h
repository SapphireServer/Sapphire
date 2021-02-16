#ifndef GENERATED_EXDDATA_H
#define GENERATED_EXDDATA_H

/* This file has been automatically generated.
   Changes will be lost upon regeneration.
   To change the content edit tools/exd_struct_gen */

#include <GameData.h>
#include <File.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <set>
#include <variant>

#if _WIN32
#undef near
#undef far
#endif

namespace Sapphire::Data {

class ExdDataGenerated;

struct Achievement;
struct AchievementCategory;
struct AchievementHideCondition;
struct AchievementKind;
struct Action;
struct ActionCastTimeline;
struct ActionCastVFX;
struct ActionCategory;
struct ActionComboRoute;
struct ActionIndirection;
struct ActionParam;
struct ActionProcStatus;
struct ActionTimeline;
struct ActionTimelineMove;
struct ActionTimelineReplace;
struct ActionTransient;
struct ActivityFeedButtons;
struct ActivityFeedCaptions;
struct ActivityFeedGroupCaptions;
struct ActivityFeedImages;
struct Addon;
struct Adventure;
struct AdventureExPhase;
struct AetherCurrent;
struct AetherCurrentCompFlgSet;
struct AetherialWheel;
struct Aetheryte;
struct AetheryteSystemDefine;
struct AirshipExplorationLevel;
struct AirshipExplorationLog;
struct AirshipExplorationParamType;
struct AirshipExplorationPart;
struct AirshipExplorationPoint;
struct AnimationLOD;
struct AnimaWeapon5;
struct AnimaWeapon5Param;
struct AnimaWeapon5PatternGroup;
struct AnimaWeapon5SpiritTalk;
struct AnimaWeapon5SpiritTalkParam;
struct AnimaWeapon5TradeItem;
struct AnimaWeaponFUITalk;
struct AnimaWeaponFUITalkParam;
struct AnimaWeaponIcon;
struct AnimaWeaponItem;
struct AozAction;
struct AozActionTransient;
struct AOZArrangement;
struct AOZBoss;
struct AOZContent;
struct AOZContentBriefingBNpc;
struct AquariumFish;
struct AquariumWater;
struct ArrayEventHandler;
struct AttackType;
struct BacklightColor;
struct Ballista;
struct Balloon;
struct BaseParam;
struct BattleLeve;
struct BattleLeveRule;
struct BeastRankBonus;
struct BeastReputationRank;
struct BeastTribe;
struct Behavior;
struct BehaviorPath;
struct BenchmarkOverrideEquipment;
struct BGM;
struct BGMFade;
struct BGMFadeType;
struct BGMScene;
struct BGMSituation;
struct BGMSwitch;
struct BGMSystemDefine;
struct BNpcAnnounceIcon;
struct BNpcBase;
struct BNpcCustomize;
struct BNpcName;
struct BNpcParts;
struct BNpcState;
struct Buddy;
struct BuddyAction;
struct BuddyEquip;
struct BuddyItem;
struct BuddyRank;
struct BuddySkill;
struct Cabinet;
struct CabinetCategory;
struct Calendar;
struct Carry;
struct Channeling;
struct CharaMakeClassEquip;
struct CharaMakeCustomize;
struct CharaMakeName;
struct CharaMakeType;
struct ChocoboRace;
struct ChocoboRaceAbility;
struct ChocoboRaceAbilityType;
struct ChocoboRaceItem;
struct ChocoboRaceRank;
struct ChocoboRaceStatus;
struct ChocoboRaceTerritory;
struct ChocoboRaceTutorial;
struct ChocoboRaceWeather;
struct ChocoboTaxi;
struct ChocoboTaxiStand;
struct CircleActivity;
struct ClassJob;
struct ClassJobCategory;
struct CollectablesShop;
struct CollectablesShopItem;
struct CollectablesShopItemGroup;
struct CollectablesShopRefine;
struct CollectablesShopRewardItem;
struct CollectablesShopRewardScrip;
struct Companion;
struct CompanionMove;
struct CompanionTransient;
struct CompanyAction;
struct CompanyCraftDraft;
struct CompanyCraftDraftCategory;
struct CompanyCraftManufactoryState;
struct CompanyCraftPart;
struct CompanyCraftProcess;
struct CompanyCraftSequence;
struct CompanyCraftSupplyItem;
struct CompanyCraftType;
struct CompanyLeve;
struct CompanyLeveRule;
struct CompleteJournal;
struct CompleteJournalCategory;
struct Condition;
struct ConfigKey;
struct ContentCloseCycle;
struct ContentExAction;
struct ContentFinderCondition;
struct ContentFinderConditionTransient;
struct ContentGauge;
struct ContentGaugeColor;
struct ContentMemberType;
struct ContentNpcTalk;
struct ContentRandomSelect;
struct ContentRoulette;
struct ContentRouletteOpenRule;
struct ContentRouletteRoleBonus;
struct ContentsNote;
struct ContentsTutorial;
struct ContentsTutorialPage;
struct ContentTalk;
struct ContentTalkParam;
struct ContentType;
struct CraftAction;
struct CraftLeve;
struct CraftLevelDifference;
struct CraftType;
struct Credit;
struct CreditBackImage;
struct CreditCast;
struct CreditList;
struct CreditListText;
struct CustomTalk;
struct CustomTalkDynamicIcon;
struct CustomTalkNestHandlers;
struct Cutscene;
struct CutsceneMotion;
struct CutsceneWorkIndex;
struct CutScreenImage;
struct CycleTime;
struct DailySupplyItem;
struct DawnContent;
struct DawnGrowMember;
struct DawnMemberUIParam;
struct DawnQuestAnnounce;
struct DawnQuestMember;
struct DeepDungeon;
struct DeepDungeonBan;
struct DeepDungeonDanger;
struct DeepDungeonEquipment;
struct DeepDungeonFloorEffectUI;
struct DeepDungeonItem;
struct DeepDungeonLayer;
struct DeepDungeonMagicStone;
struct DeepDungeonMap5X;
struct DeepDungeonRoom;
struct DeepDungeonStatus;
struct DefaultTalk;
struct DefaultTalkLipSyncType;
struct DeliveryQuest;
struct Description;
struct DescriptionPage;
struct DescriptionSection;
struct DescriptionString;
struct DisposalShop;
struct DisposalShopFilterType;
struct DisposalShopItem;
struct DpsChallenge;
struct DpsChallengeOfficer;
struct DpsChallengeTransient;
struct DynamicEvent;
struct DynamicEventEnemyType;
struct DynamicEventSingleBattle;
struct DynamicEventType;
struct EmjAddon;
struct EmjDani;
struct Emote;
struct EmoteCategory;
struct EmoteMode;
struct ENpcBase;
struct ENpcDressUp;
struct ENpcDressUpDress;
struct ENpcResident;
struct EObj;
struct EObjName;
struct EquipRaceCategory;
struct EquipSlotCategory;
struct EurekaAetherItem;
struct EurekaAethernet;
struct EurekaGrowData;
struct EurekaLogosMixerProbability;
struct EurekaMagiaAction;
struct EurekaMagiciteItem;
struct EurekaMagiciteItemType;
struct EurekaSphereElementAdjust;
struct EventAction;
struct EventIconPriority;
struct EventIconType;
struct EventItem;
struct EventItemCastTimeline;
struct EventItemHelp;
struct EventItemTimeline;
struct EventSystemDefine;
struct ExportedSG;
struct ExVersion;
struct Fate;
struct FateEvent;
struct FateMode;
struct FateProgressUI;
struct FateTokenType;
struct FCActivity;
struct FCActivityCategory;
struct FCAuthority;
struct FCAuthorityCategory;
struct FCChestName;
struct FCCrestSymbol;
struct FccShop;
struct FCHierarchy;
struct FCProfile;
struct FCRank;
struct FCReputation;
struct FCRights;
struct Festival;
struct FieldMarker;
struct FishingRecordType;
struct FishingRecordTypeTransient;
struct FishingSpot;
struct FishParameter;
struct Frontline03;
struct Frontline04;
struct FurnitureCatalogCategory;
struct FurnitureCatalogItemList;
struct GardeningSeed;
struct GatheringCondition;
struct GatheringExp;
struct GatheringItem;
struct GatheringItemLevelConvertTable;
struct GatheringItemPoint;
struct GatheringLeve;
struct GatheringLeveRoute;
struct GatheringLeveRule;
struct GatheringNotebookList;
struct GatheringPoint;
struct GatheringPointBase;
struct GatheringPointBonus;
struct GatheringPointBonusType;
struct GatheringPointName;
struct GatheringPointTransient;
struct GatheringRarePopTimeTable;
struct GatheringSubCategory;
struct GatheringType;
struct GcArmyCaptureTactics;
struct GcArmyExpedition;
struct GcArmyExpeditionMemberBonus;
struct GcArmyExpeditionType;
struct GcArmyMemberGrow;
struct GcArmyTraining;
struct GCRankGridaniaFemaleText;
struct GCRankGridaniaMaleText;
struct GCRankLimsaFemaleText;
struct GCRankLimsaMaleText;
struct GCRankUldahFemaleText;
struct GCRankUldahMaleText;
struct GCScripShopCategory;
struct GCScripShopItem;
struct GCShop;
struct GCShopItemCategory;
struct GCSupplyDuty;
struct GCSupplyDutyReward;
struct GeneralAction;
struct GFATE;
struct GFateClimbing2;
struct GFateClimbing2Content;
struct GFateClimbing2TotemType;
struct GFateRideShooting;
struct GilShop;
struct GilShopItem;
struct GimmickAccessor;
struct GimmickJump;
struct GimmickRect;
struct GoldSaucerArcadeMachine;
struct GoldSaucerTextData;
struct GrandCompany;
struct GrandCompanyRank;
struct GroupPoseFrame;
struct GroupPoseStamp;
struct GroupPoseStampCategory;
struct GuardianDeity;
struct Guide;
struct GuidePage;
struct GuidePageString;
struct GuideTitle;
struct GuildleveAssignment;
struct GuildleveAssignmentCategory;
struct GuildOrder;
struct GuildOrderGuide;
struct GuildOrderOfficer;
struct HairMakeType;
struct HouseRetainerPose;
struct HousingAethernet;
struct HousingAppeal;
struct HousingEmploymentNpcList;
struct HousingEmploymentNpcRace;
struct HousingExterior;
struct HousingFurniture;
struct HousingLandSet;
struct HousingMapMarkerInfo;
struct HousingMerchantPose;
struct HousingPlacement;
struct HousingPreset;
struct HousingUnitedExterior;
struct HousingYardObject;
struct HowTo;
struct HowToCategory;
struct HowToPage;
struct HugeCraftworksNpc;
struct HugeCraftworksRank;
struct HWDAnnounce;
struct HWDCrafterSupply;
struct HWDCrafterSupplyReward;
struct HWDCrafterSupplyTerm;
struct HWDDevLayerControl;
struct HWDDevLevelUI;
struct HWDDevLively;
struct HWDDevProgress;
struct HWDGathereInspectTerm;
struct HWDGathererInspection;
struct HWDGathererInspectionReward;
struct HWDInfoBoardArticle;
struct HWDInfoBoardArticleTransient;
struct HWDInfoBoardArticleType;
struct HWDLevelChangeDeception;
struct HWDSharedGroup;
struct HWDSharedGroupControlParam;
struct IKDContentBonus;
struct IKDFishParam;
struct IKDRoute;
struct IKDRouteTable;
struct IKDSpot;
struct InclusionShop;
struct InclusionShopCategory;
struct InclusionShopSeries;
struct IndividualWeather;
struct InstanceContent;
struct InstanceContentBuff;
struct InstanceContentCSBonus;
struct InstanceContentGuide;
struct InstanceContentTextData;
struct Item;
struct ItemAction;
struct ItemActionTelepo;
struct ItemBarterCheck;
struct ItemFood;
struct ItemLevel;
struct ItemSearchCategory;
struct ItemSeries;
struct ItemSortCategory;
struct ItemSpecialBonus;
struct ItemUICategory;
struct JobHudManual;
struct JobHudManualPriority;
struct JournalCategory;
struct JournalGenre;
struct JournalSection;
struct Knockback;
struct LegacyQuest;
struct Leve;
struct LeveAssignmentType;
struct LeveClient;
struct Level;
struct LeveRewardItem;
struct LeveRewardItemGroup;
struct LeveString;
struct LeveVfx;
struct Lobby;
struct LogFilter;
struct LogKind;
struct LogMessage;
struct LotteryExchangeShop;
struct MacroIcon;
struct MacroIconRedirectOld;
struct MainCommand;
struct MainCommandCategory;
struct ManeuversArmor;
struct Map;
struct MapMarker;
struct MapMarkerRegion;
struct MapSymbol;
struct Marker;
struct MasterpieceSupplyDuty;
struct MasterpieceSupplyMultiplier;
struct Materia;
struct MateriaJoinRate;
struct MateriaJoinRateGatherCraft;
struct MateriaTomestoneRate;
struct MiniGameRA;
struct MinionRace;
struct MinionRules;
struct MinionSkillType;
struct MobHuntOrder;
struct MobHuntOrderType;
struct MobHuntReward;
struct MobHuntRewardCap;
struct MobHuntTarget;
struct ModelChara;
struct ModelSkeleton;
struct ModelState;
struct MonsterNote;
struct MonsterNoteTarget;
struct MotionTimeline;
struct MotionTimelineBlendTable;
struct Mount;
struct MountAction;
struct MountCustomize;
struct MountFlyingCondition;
struct MountSpeed;
struct MountTransient;
struct MoveTimeline;
struct MoveVfx;
struct MovieStaffList;
struct MovieSubtitle;
struct MovieSubtitle500;
struct MovieSubtitleVoyage;
struct MYCTemporaryItem;
struct MYCTemporaryItemUICategory;
struct MYCWarResultNotebook;
struct NotebookDivision;
struct NotebookDivisionCategory;
struct NotoriousMonster;
struct NpcEquip;
struct NpcYell;
struct Omen;
struct OnlineStatus;
struct OpenContent;
struct OpenContentCandidateName;
struct Opening;
struct Orchestrion;
struct OrchestrionCategory;
struct OrchestrionPath;
struct OrchestrionUiparam;
struct Ornament;
struct ParamGrow;
struct PartyContent;
struct PartyContentCutscene;
struct PartyContentTextData;
struct PatchMark;
struct Perform;
struct PerformTransient;
struct Pet;
struct PetAction;
struct PhysicsGroup;
struct PhysicsWind;
struct Picture;
struct PlaceName;
struct PlantPotFlowerSeed;
struct PreHandler;
struct PresetCamera;
struct PresetCameraAdjust;
struct PublicContent;
struct PublicContentCutscene;
struct PublicContentTextData;
struct Purify;
struct PvPAction;
struct PvPActionSort;
struct PvPRank;
struct PvPSelectTrait;
struct PvPTrait;
struct Quest;
struct QuestBattle;
struct QuestChapter;
struct QuestClassJobReward;
struct QuestClassJobSupply;
struct QuestDerivedClass;
struct QuestRedo;
struct QuestRedoChapterUI;
struct QuestRedoChapterUICategory;
struct QuestRedoChapterUITab;
struct QuestRedoIncompChapter;
struct QuestRepeatFlag;
struct QuestRewardOther;
struct QuickChat;
struct QuickChatTransient;
struct Race;
struct RacingChocoboItem;
struct RacingChocoboName;
struct RacingChocoboNameCategory;
struct RacingChocoboNameInfo;
struct RacingChocoboParam;
struct RecastNavimesh;
struct Recipe;
struct RecipeLevelTable;
struct RecipeLookup;
struct RecipeNotebookList;
struct RecommendContents;
struct Relic;
struct Relic3;
struct RelicItem;
struct RelicNote;
struct RelicNoteCategory;
struct Resident;
struct ResistanceWeaponAdjust;
struct RetainerTask;
struct RetainerTaskLvRange;
struct RetainerTaskNormal;
struct RetainerTaskParameter;
struct RetainerTaskRandom;
struct RideShooting;
struct RideShootingTextData;
struct RPParameter;
struct SatisfactionArbitration;
struct SatisfactionNpc;
struct SatisfactionSupply;
struct SatisfactionSupplyReward;
struct ScenarioTree;
struct ScenarioTreeTips;
struct ScenarioTreeTipsClassQuest;
struct ScenarioType;
struct ScreenImage;
struct SecretRecipeBook;
struct SkyIsland2Mission;
struct SkyIsland2MissionDetail;
struct SkyIsland2MissionType;
struct SkyIsland2RangeType;
struct SnipeTalk;
struct SnipeTalkName;
struct SpearfishingItem;
struct SpearfishingNotebook;
struct SpearfishingRecordPage;
struct SpecialShop;
struct SpecialShopItemCategory;
struct Stain;
struct StainTransient;
struct Status;
struct StatusHitEffect;
struct StatusLoopVFX;
struct Story;
struct SubmarineExploration;
struct SubmarineMap;
struct SubmarinePart;
struct SubmarineRank;
struct SwitchTalk;
struct SwitchTalkVariation;
struct TerritoryType;
struct TerritoryTypeTransient;
struct TextCommand;
struct Title;
struct Tomestones;
struct TomestonesItem;
struct TopicSelect;
struct Town;
struct Trait;
struct TraitRecast;
struct TraitTransient;
struct Transformation;
struct Treasure;
struct TreasureHuntRank;
struct TreasureModel;
struct TreasureSpot;
struct Tribe;
struct TripleTriad;
struct TripleTriadCard;
struct TripleTriadCardRarity;
struct TripleTriadCardResident;
struct TripleTriadCardType;
struct TripleTriadCompetition;
struct TripleTriadRule;
struct Tutorial;
struct TutorialDPS;
struct TutorialHealer;
struct TutorialTank;
struct UIColor;
struct VaseFlower;
struct VFX;
struct Warp;
struct WarpCondition;
struct WarpLogic;
struct WeaponTimeline;
struct Weather;
struct WeatherGroup;
struct WeatherRate;
struct WeatherReportReplace;
struct WebGuidance;
struct WebURL;
struct WeddingBGM;
struct WeeklyBingoOrderData;
struct WeeklyBingoRewardData;
struct WeeklyBingoText;
struct WeeklyLotBonus;
struct World;
struct WorldDCGroupType;
struct YardCatalogCategory;
struct YardCatalogItemList;
struct YKW;
struct ZoneSharedGroup;


struct Achievement
{
  uint8_t achievementCategory;
  std::string name;
  std::string description;
  uint8_t points;
  uint16_t title;
  uint32_t item;
  uint16_t icon;
  uint8_t type;
  int32_t key;
  std::vector< int32_t > data;
  uint16_t order;
  uint8_t achievementHideCondition;

  Achievement( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AchievementCategory
{
  std::string name;
  uint8_t achievementKind;
  bool showComplete;
  bool hideCategory;
  uint8_t order;

  AchievementCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AchievementHideCondition
{
  bool hideAchievement;
  bool hideName;
  bool hideConditions;

  AchievementHideCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AchievementKind
{
  std::string name;
  uint8_t order;

  AchievementKind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Action
{
  std::string name;
  uint16_t icon;
  uint8_t actionCategory;
  uint8_t animationStart;
  uint8_t vFX;
  int16_t animationEnd;
  uint16_t actionTimelineHit;
  int8_t classJob;
  uint8_t behaviourType;
  uint8_t classJobLevel;
  bool isRoleAction;
  int8_t range;
  bool canTargetSelf;
  bool canTargetParty;
  bool canTargetFriendly;
  bool canTargetHostile;
  bool targetArea;
  bool canTargetDead;
  uint8_t castType;
  uint8_t effectRange;
  uint8_t xAxisModifier;
  uint8_t primaryCostType;
  uint16_t primaryCostValue;
  uint8_t secondaryCostType;
  uint16_t secondaryCostValue;
  uint16_t actionCombo;
  bool preservesCombo;
  uint16_t cast100ms;
  uint16_t recast100ms;
  uint8_t cooldownGroup;
  uint8_t maxCharges;
  int8_t attackType;
  uint8_t aspect;
  uint8_t actionProcStatus;
  uint16_t statusGainSelf;
  uint32_t unlockLink;
  uint8_t classJobCategory;
  bool affectsPosition;
  uint16_t omen;
  bool isPvP;
  bool isPlayerAction;

  Action( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionCastTimeline
{
  uint16_t name;
  uint16_t vFX;

  ActionCastTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionCastVFX
{
  uint16_t vFX;

  ActionCastVFX( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionCategory
{
  std::string name;

  ActionCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionComboRoute
{
  std::string name;
  std::vector< uint16_t > action;

  ActionComboRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionIndirection
{
  int32_t name;

  ActionIndirection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionParam
{
  int16_t name;

  ActionParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionProcStatus
{
  uint16_t status;

  ActionProcStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionTimeline
{
  uint8_t type;
  uint8_t priority;
  bool pause;
  uint8_t stance;
  uint8_t slot;
  uint8_t lookAtMode;
  std::string key;
  uint8_t actionTimelineIDMode;
  uint8_t weaponTimeline;
  uint8_t loadType;
  uint8_t startAttach;
  uint8_t residentPap;
  bool resident;
  uint16_t killUpper;
  bool isMotionCanceledByMoving;
  uint8_t isLoop;

  ActionTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionTimelineMove
{

  ActionTimelineMove( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionTimelineReplace
{
  uint16_t old;
  uint16_t _new;

  ActionTimelineReplace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActionTransient
{
  std::string description;

  ActionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActivityFeedButtons
{
  std::string bannerURL;
  std::string description;
  std::string language;
  std::string pictureURL;

  ActivityFeedButtons( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActivityFeedCaptions
{
  std::string jA;
  std::string eN;
  std::string dE;
  std::string fR;

  ActivityFeedCaptions( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActivityFeedGroupCaptions
{
  std::string jA;
  std::string eN;
  std::string dE;
  std::string fR;

  ActivityFeedGroupCaptions( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ActivityFeedImages
{
  std::string expansionImage;
  std::string activityFeedJA;
  std::string activityFeedEN;
  std::string activityFeedDE;
  std::string activityFeedFR;

  ActivityFeedImages( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Addon
{
  std::string text;

  Addon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Adventure
{
  int32_t level;
  int32_t minLevel;
  uint8_t maxLevel;
  uint16_t emote;
  uint16_t minTime;
  uint16_t maxTime;
  int32_t placeName;
  int32_t iconList;
  int32_t iconDiscovered;
  std::string name;
  std::string impression;
  std::string description;
  int32_t iconUndiscovered;
  bool isInitial;

  Adventure( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AdventureExPhase
{
  uint32_t quest;
  uint32_t adventureBegin;
  uint32_t adventureEnd;

  AdventureExPhase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AetherCurrent
{
  uint32_t quest;

  AetherCurrent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AetherCurrentCompFlgSet
{
  int32_t territory;
  std::vector< int32_t > aetherCurrent;

  AetherCurrentCompFlgSet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AetherialWheel
{
  int32_t itemUnprimed;
  int32_t itemPrimed;
  uint8_t grade;
  uint8_t hoursRequired;

  AetherialWheel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Aetheryte
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  uint16_t placeName;
  uint16_t aethernetName;
  uint16_t territory;
  std::vector< uint32_t > level;
  bool isAetheryte;
  uint8_t aethernetGroup;
  uint32_t requiredQuest;
  uint16_t map;
  int16_t aetherstreamX;
  int16_t aetherstreamY;

  Aetheryte( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AetheryteSystemDefine
{
  std::string text;
  uint32_t defineValue;

  AetheryteSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationLevel
{
  uint16_t capacity;
  uint32_t expToNext;

  AirshipExplorationLevel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationLog
{
  std::string text;

  AirshipExplorationLog( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationParamType
{
  std::string name;

  AirshipExplorationParamType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationPart
{
  uint8_t slot;
  uint8_t rank;
  uint8_t components;
  int16_t surveillance;
  int16_t retrieval;
  int16_t speed;
  int16_t range;
  int16_t favor;
  uint16_t _class;
  uint8_t repairMaterials;

  AirshipExplorationPart( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationPoint
{
  std::string name;
  std::string nameShort;
  uint8_t requiredLevel;
  uint16_t requiredFuel;
  uint16_t durationmin;
  uint8_t requiredSurveillance;
  uint32_t expReward;

  AirshipExplorationPoint( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimationLOD
{
  float cameraDistance;
  float sampleInterval;
  int8_t boneLOD;
  std::vector< bool > animationEnable;

  AnimationLOD( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5
{
  int32_t item;
  uint8_t secondaryStatTotal;
  std::vector< uint8_t > parameter;

  AnimaWeapon5( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5Param
{
  uint8_t baseParam;
  std::string name;

  AnimaWeapon5Param( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5PatternGroup
{
  std::string name;

  AnimaWeapon5PatternGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5SpiritTalk
{
  int32_t dialogue;

  AnimaWeapon5SpiritTalk( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5SpiritTalkParam
{
  std::string prologue;
  std::string epilogue;

  AnimaWeapon5SpiritTalkParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5TradeItem
{
  uint32_t crystalSand;
  uint8_t qty;
  uint8_t category;

  AnimaWeapon5TradeItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponFUITalk
{
  int32_t dialogue;

  AnimaWeaponFUITalk( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponFUITalkParam
{
  std::string prologue;
  std::string epilogue;

  AnimaWeaponFUITalkParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponIcon
{
  int32_t hyperconductive;
  int32_t reborn;
  int32_t sharpened;
  int32_t zodiac;
  int32_t zodiacLux;

  AnimaWeaponIcon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponItem
{
  std::vector< uint32_t > item;

  AnimaWeaponItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AozAction
{
  uint32_t action;

  AozAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AozActionTransient
{
  uint8_t number;
  uint32_t icon;
  std::string stats;
  std::string description;
  uint8_t locationKey;
  uint16_t location;
  uint32_t requiredForQuest;
  uint32_t previousQuest;
  bool targetsEnemy;
  bool targetsSelfOrAlly;
  bool causeSlow;
  bool causePetrify;
  bool causeParalysis;
  bool causeInterrupt;
  bool causeBlind;
  bool causeStun;
  bool causeSleep;
  bool causeBind;
  bool causeHeavy;
  bool causeDeath;

  AozActionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AOZArrangement
{
  uint16_t aOZContentBriefingBNpc;
  uint16_t position;

  AOZArrangement( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AOZBoss
{
  uint16_t boss;
  uint16_t position;

  AOZBoss( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AOZContent
{
  uint16_t standardFinishTime;
  uint16_t idealFinishTime;
  uint8_t act1FightType;
  uint16_t act1;
  uint8_t arenaType1;
  uint8_t act2FightType;
  uint16_t act2;
  uint8_t arenaType2;
  uint8_t act3FightType;
  uint16_t act3;
  uint8_t arenaType3;
  uint32_t contentEntry;
  uint8_t order;
  uint16_t gilReward;
  uint16_t alliedSealsReward;
  uint16_t tomestonesReward;

  AOZContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AOZContentBriefingBNpc
{
  uint32_t bNpcName;
  uint32_t targetSmall;
  uint32_t targetLarge;
  bool hideStats;
  uint8_t endurance;
  uint8_t fire;
  uint8_t ice;
  uint8_t wind;
  uint8_t earth;
  uint8_t thunder;
  uint8_t water;
  uint8_t slashing;
  uint8_t piercing;
  uint8_t blunt;
  uint8_t magic;
  bool slowVuln;
  bool petrificationVuln;
  bool paralysisVuln;
  bool interruptionVuln;
  bool blindVuln;
  bool stunVuln;
  bool sleepVuln;
  bool bindVuln;
  bool heavyVuln;
  bool flatOrDeathVuln;

  AOZContentBriefingBNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AquariumFish
{
  uint8_t aquariumWater;
  uint8_t size;
  uint32_t item;

  AquariumFish( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AquariumWater
{
  std::string name;

  AquariumWater( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ArrayEventHandler
{
  std::vector< uint32_t > data;

  ArrayEventHandler( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct AttackType
{
  std::string name;

  AttackType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BacklightColor
{
  uint32_t color;

  BacklightColor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Ballista
{
  uint16_t bNPC;
  int8_t near;
  int8_t far;
  uint16_t angle;
  uint8_t bullet;
  uint16_t action0;
  uint16_t action1;
  uint16_t action2;
  uint16_t action3;

  Ballista( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Balloon
{
  bool slowly;
  std::string dialogue;

  Balloon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BaseParam
{
  int8_t packetIndex;
  std::string name;
  std::string description;
  uint8_t orderPriority;
  uint8_t oneHWpn;
  uint8_t oH;
  uint8_t head;
  uint8_t chest;
  uint8_t hands;
  uint8_t waist;
  uint8_t legs;
  uint8_t feet;
  uint8_t earring;
  uint8_t necklace;
  uint8_t bracelet;
  uint8_t ring;
  uint8_t twoHWpn;
  uint8_t underArmor;
  uint8_t chestHead;
  uint8_t chestHeadLegsFeet;
  uint8_t legsFeet;
  uint8_t headChestHandsLegsFeet;
  uint8_t chestLegsGloves;
  uint8_t chestLegsFeet;
  std::vector< uint8_t > meldParam;

  BaseParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BattleLeve
{
  std::vector< uint16_t > time;
  std::vector< int32_t > baseID;
  std::vector< uint16_t > enemyLevel;
  std::vector< uint32_t > bNpcName;
  std::vector< int32_t > itemsInvolved;
  std::vector< uint8_t > itemsInvolvedQty;
  std::vector< uint8_t > itemDropRate;
  std::vector< uint32_t > toDoNumberInvolved;
  std::vector< uint8_t > toDoSequence;
  int32_t rule;
  uint8_t varient;
  uint16_t objective0;
  uint16_t objective1;
  uint16_t objective2;
  uint16_t help0;
  uint16_t help1;

  BattleLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BattleLeveRule
{
  std::string rule;

  BattleLeveRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BeastRankBonus
{
  uint16_t neutral;
  uint16_t recognized;
  uint16_t friendly;
  uint16_t trusted;
  uint16_t respected;
  uint16_t honored;
  uint16_t sworn;
  uint16_t alliedBloodsworn;
  uint32_t item;
  std::vector< uint8_t > itemQuantity;

  BeastRankBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BeastReputationRank
{
  uint16_t requiredReputation;
  std::string name;
  std::string alliedNames;
  uint32_t color;

  BeastReputationRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BeastTribe
{
  uint8_t minLevel;
  uint8_t beastRankBonus;
  uint32_t iconReputation;
  uint32_t icon;
  uint8_t maxRank;
  uint8_t expansion;
  uint32_t currencyItem;
  uint8_t displayOrder;
  std::string name;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  int8_t dEF;
  std::string nameRelation;

  BeastTribe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Behavior
{
  uint8_t condition0Target;
  uint8_t condition0Type;
  int32_t balloon;
  uint8_t condition1Target;
  uint8_t condition1Type;
  uint32_t contentArgument0;
  uint8_t contentArgument1;

  Behavior( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BehaviorPath
{
  bool isTurnTransition;
  bool isFadeOut;
  bool isFadeIn;
  bool isWalking;
  float speed;

  BehaviorPath( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BenchmarkOverrideEquipment
{
  uint64_t modelMainHand;
  uint8_t dyeMainHand;
  uint64_t modelOffHand;
  uint8_t dyeOffHand;
  uint32_t modelHead;
  uint8_t dyeHead;
  uint32_t modelBody;
  uint8_t dyeBody;
  uint32_t modelHands;
  uint8_t dyeHands;
  uint32_t modelLegs;
  uint8_t dyeLegs;
  uint32_t modelFeet;
  uint8_t dyeFeet;
  uint32_t modelEars;
  uint8_t dyeEars;
  uint32_t modelNeck;
  uint8_t dyeNeck;
  uint32_t modelWrists;
  uint8_t dyeWrists;
  uint32_t modelLeftRing;
  uint8_t dyeLeftRing;
  uint32_t modelRightRing;
  uint8_t dyeRightRing;

  BenchmarkOverrideEquipment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGM
{
  std::string file;
  uint8_t priority;
  bool disableRestartTimeOut;
  bool disableRestart;
  bool passEnd;
  float disableRestartResetTime;
  uint8_t specialMode;

  BGM( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGMFade
{
  int32_t sceneOut;
  int32_t sceneIn;
  int32_t bGMFadeType;

  BGMFade( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGMFadeType
{
  float fadeOutTime;
  float fadeInTime;
  float fadeInStartTime;
  float resumeFadeInTime;

  BGMFadeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGMScene
{
  bool enableDisableRestart;
  bool resume;
  bool enablePassEnd;
  bool forceAutoReset;
  bool ignoreBattle;

  BGMScene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGMSituation
{
  uint16_t daytimeID;
  uint16_t nightID;
  uint16_t battleID;
  uint16_t daybreakID;
  uint16_t twilightID;

  BGMSituation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGMSwitch
{
  uint8_t bGMSystemDefine;
  uint32_t quest;
  uint16_t bGM;

  BGMSwitch( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BGMSystemDefine
{
  float define;

  BGMSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BNpcAnnounceIcon
{
  uint32_t icon;

  BNpcAnnounceIcon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BNpcBase
{
  uint16_t behavior;
  uint8_t battalion;
  uint8_t linkRace;
  uint8_t rank;
  float scale;
  uint16_t modelChara;
  uint16_t bNpcCustomize;
  uint16_t npcEquip;
  uint16_t special;
  uint8_t sEPack;
  int32_t arrayEventHandler;
  uint8_t bNpcParts;
  bool isTargetLine;
  bool isDisplayLevel;

  BNpcBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
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

  BNpcCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BNpcName
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;

  BNpcName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BNpcParts
{
  uint16_t bNpcBase1;
  uint8_t partSlot1;
  float x1;
  float y1;
  float z1;
  float scale1;
  uint16_t bNpcBase2;
  uint8_t partSlot2;
  float x2;
  float y2;
  float z2;
  float scale2;
  uint16_t bNpcBase3;
  uint8_t partSlot3;
  float x3;
  float y3;
  float z3;
  int16_t scale3;
  uint16_t bNpcBase4;
  uint8_t partSlot4;
  float x4;
  float y4;
  float z4;
  float scale4;
  uint16_t bNpcBase5;
  uint8_t partSlot5;
  float x5;
  float y5;
  float z5;
  float scale5;

  BNpcParts( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BNpcState
{
  uint8_t slot;
  int8_t overRay;
  uint16_t idle;
  uint8_t attribute0;
  bool attributeFlag0;
  uint8_t attribute1;
  bool attributeFlag1;
  uint8_t attribute2;
  bool attributeFlag2;
  float scale;
  int32_t loopTimeline;

  BNpcState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Buddy
{
  uint8_t base;
  int32_t questRequirement2;
  int32_t questRequirement1;
  int32_t baseEquip;
  std::string soundEffect4;
  std::string soundEffect3;
  std::string soundEffect2;
  std::string soundEffect1;

  Buddy( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BuddyAction
{
  std::string name;
  std::string description;
  int32_t icon;
  int32_t iconStatus;
  uint16_t reward;
  uint8_t sort;

  BuddyAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BuddyEquip
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string name;
  int32_t modelTop;
  int32_t modelBody;
  int32_t modelLegs;
  uint8_t grandCompany;
  uint16_t iconHead;
  uint16_t iconBody;
  uint16_t iconLegs;
  uint8_t order;

  BuddyEquip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BuddyItem
{
  uint16_t item;
  bool useField;
  bool useTraining;
  uint8_t status;

  BuddyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BuddyRank
{
  uint32_t expRequired;

  BuddyRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct BuddySkill
{
  uint8_t buddyLevel;
  bool isActive;
  uint16_t defender;
  uint16_t attacker;
  uint16_t healer;

  BuddySkill( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Cabinet
{
  int32_t item;
  uint16_t order;
  uint8_t category;

  Cabinet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CabinetCategory
{
  uint8_t menuOrder;
  int32_t icon;
  int32_t category;

  CabinetCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Calendar
{
  std::vector< uint8_t > month;
  std::vector< uint8_t > day;

  Calendar( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Carry
{
  uint64_t model;
  uint8_t timeline;

  Carry( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Channeling
{
  std::string file;
  uint8_t widthScale;
  bool addedIn53;

  Channeling( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CharaMakeClassEquip
{
  uint64_t helmet;
  uint64_t top;
  uint64_t glove;
  uint64_t down;
  uint64_t shoes;
  uint64_t weapon;
  uint64_t subWeapon;
  int32_t _class;

  CharaMakeClassEquip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CharaMakeCustomize
{
  uint8_t featureID;
  uint32_t icon;
  uint16_t data;
  bool isPurchasable;
  uint32_t hint;
  uint32_t hintItem;

  CharaMakeCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CharaMakeName
{
  std::string hyurMidlanderMale;
  std::string hyurMidlanderFemale;
  std::string hyurMidlanderLastName;
  std::string hyurHighlanderMale;
  std::string hyurHighlanderFemale;
  std::string hyurHighlanderLastName;
  std::string elezenMale;
  std::string elezenFemale;
  std::string elezenWildwoodLastName;
  std::string elezenDuskwightLastName;
  std::string miqoteSunMale;
  std::string miqoteSunFemale;
  std::string miqoteSunMaleLastName;
  std::string miqoteSunFemaleLastName;
  std::string miqoteMoonMale;
  std::string miqoteMoonFemale;
  std::string miqoteMoonLastname;
  std::string lalafellPlainsfolkFirstNameStart;
  std::string lalafellPlainsfolkLastNameStart;
  std::string lalafellPlainsfolkEndOfNames;
  std::string lalafellDunesfolkMale;
  std::string lalafellDunesfolkMaleLastName;
  std::string lalafellDunesfolkFemale;
  std::string lalafellDunesfolkFemaleLastName;
  std::string roegadynSeaWolfMale;
  std::string roegadynSeaWolfMaleLastName;
  std::string roegadynSeaWolfFemale;
  std::string roegadynSeaWolfFemaleLastName;
  std::string roegadynHellsguardFirstName;
  std::string roegadynHellsguardMaleLastName;
  std::string roegadynHellsguardFemaleLastName;
  std::string auRaRaenMale;
  std::string auRaRaenFemale;
  std::string auRaRaenLastName;
  std::string auRaXaelaMale;
  std::string auRaXaelaFemale;
  std::string auRaXaelaLastName;
  std::string hrothgarHellionsFirstName;
  std::string hrothgarHellionsLastName;
  std::string hrothgarLostFirstName;
  std::string hrothgarLostLastName;
  std::string vieraFirstName;
  std::string vieraRavaLastName;
  std::string vieraVeenaLastName;

  CharaMakeName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CharaMakeType
{
  int32_t race;
  int32_t tribe;
  int8_t gender;
  std::vector< uint32_t > menu;
  std::vector< uint8_t > initVal;
  std::vector< uint8_t > subMenuType;
  std::vector< uint8_t > subMenuNum;
  std::vector< uint8_t > lookAt;
  std::vector< uint32_t > subMenuMask;
  std::vector< uint32_t > customize;
  std::vector< uint8_t > voiceStruct;

  CharaMakeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRace
{
  uint8_t chocoboRaceRank;
  uint8_t chocoboRaceTerritory;

  ChocoboRace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceAbility
{
  std::string name;
  std::string description;
  uint32_t icon;
  int8_t chocoboRaceAbilityType;
  uint8_t value;

  ChocoboRaceAbility( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceAbilityType
{
  bool isActive;

  ChocoboRaceAbilityType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceItem
{
  std::string name;
  std::string description;
  uint32_t icon;

  ChocoboRaceItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceRank
{
  uint16_t ratingMin;
  uint16_t ratingMax;
  uint16_t name;
  uint16_t fee;
  int32_t icon;

  ChocoboRaceRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceStatus
{
  int32_t status;

  ChocoboRaceStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceTerritory
{
  uint16_t name;
  int32_t icon;

  ChocoboRaceTerritory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceTutorial
{
  std::vector< int32_t > npcYell;

  ChocoboRaceTutorial( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceWeather
{
  int32_t weatherType1;
  int32_t weatherType2;

  ChocoboRaceWeather( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboTaxi
{
  uint32_t location;
  uint8_t fare;
  uint16_t timeRequired;

  ChocoboTaxi( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ChocoboTaxiStand
{
  std::vector< uint16_t > targetLocations;
  std::string placeName;

  ChocoboTaxiStand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CircleActivity
{
  std::string name;
  int32_t icon;
  uint16_t order;

  CircleActivity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ClassJob
{
  std::string name;
  std::string abbreviation;
  uint8_t classJobCategory;
  int8_t expArrayIndex;
  int8_t battleClassIndex;
  uint8_t jobIndex;
  int8_t dohDolJobIndex;
  uint16_t modifierHitPoints;
  uint16_t modifierManaPoints;
  uint16_t modifierStrength;
  uint16_t modifierVitality;
  uint16_t modifierDexterity;
  uint16_t modifierIntelligence;
  uint16_t modifierMind;
  uint16_t modifierPiety;
  uint8_t classJobParent;
  std::string nameEnglish;
  int32_t itemStartingWeapon;
  uint8_t role;
  uint8_t startingTown;
  int8_t monsterNote;
  uint8_t primaryStat;
  uint16_t limitBreak1;
  uint16_t limitBreak2;
  uint16_t limitBreak3;
  uint8_t uIPriority;
  uint32_t itemSoulCrystal;
  uint32_t unlockQuest;
  uint32_t relicQuest;
  uint32_t prerequisite;
  uint8_t startingLevel;
  uint8_t partyBonus;
  bool isLimitedJob;
  bool canQueueForDuty;

  ClassJob( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ClassJobCategory
{
  std::string name;
  bool aDV;
  bool gLA;
  bool pGL;
  bool mRD;
  bool lNC;
  bool aRC;
  bool cNJ;
  bool tHM;
  bool cRP;
  bool bSM;
  bool aRM;
  bool gSM;
  bool lTW;
  bool wVR;
  bool aLC;
  bool cUL;
  bool mIN;
  bool bTN;
  bool fSH;
  bool pLD;
  bool mNK;
  bool wAR;
  bool dRG;
  bool bRD;
  bool wHM;
  bool bLM;
  bool aCN;
  bool sMN;
  bool sCH;
  bool rOG;
  bool nIN;
  bool mCH;
  bool dRK;
  bool aST;
  bool sAM;
  bool rDM;
  bool bLU;
  bool gNB;
  bool dNC;

  ClassJobCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CollectablesShop
{
  std::string name;
  uint32_t quest;
  std::vector< uint16_t > shopItems;

  CollectablesShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CollectablesShopItem
{
  uint32_t item;
  uint8_t collectablesShopItemGroup;
  uint16_t levelMin;
  uint16_t levelMax;
  uint16_t collectablesShopRefine;
  uint16_t collectablesShopRewardScrip;

  CollectablesShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CollectablesShopItemGroup
{
  std::string name;

  CollectablesShopItemGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CollectablesShopRefine
{
  uint16_t lowCollectability;
  uint16_t midCollectability;
  uint16_t highCollectability;

  CollectablesShopRefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CollectablesShopRewardItem
{
  uint32_t item;

  CollectablesShopRewardItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CollectablesShopRewardScrip
{
  uint16_t currency;
  uint16_t lowReward;
  uint16_t midReward;
  uint16_t highReward;
  uint16_t expRatioLow;
  uint16_t expRatioMid;
  uint16_t expRatioHigh;

  CollectablesShopRewardScrip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Companion
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  uint16_t model;
  uint8_t scale;
  uint8_t inactiveIdle0;
  uint8_t inactiveIdle1;
  uint8_t inactiveBattle;
  uint8_t inactiveWandering;
  uint8_t behavior;
  uint8_t special;
  uint8_t wanderingWait;
  uint16_t priority;
  bool roulette;
  bool battle;
  bool lookAt;
  bool poke;
  uint16_t enemy;
  bool stroke;
  bool clapping;
  uint16_t icon;
  uint16_t order;
  uint8_t cost;
  uint16_t hP;
  uint16_t skillAngle;
  uint8_t skillCost;
  uint8_t minionRace;

  Companion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanionMove
{
  std::string name;

  CompanionMove( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanionTransient
{
  std::string description;
  std::string descriptionEnhanced;
  std::string tooltip;
  std::string specialActionName;
  std::string specialActionDescription;
  uint8_t attack;
  uint8_t defense;
  uint8_t speed;
  bool hasAreaAttack;
  bool strengthGate;
  bool strengthEye;
  bool strengthShield;
  bool strengthArcana;
  uint8_t minionSkillType;

  CompanionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyAction
{
  std::string name;
  std::string description;
  int32_t icon;
  uint8_t fCRank;
  uint32_t cost;
  uint8_t order;
  bool purchasable;

  CompanyAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftDraft
{
  std::string name;
  uint8_t companyCraftDraftCategory;
  uint32_t order;

  CompanyCraftDraft( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftDraftCategory
{
  std::string name;

  CompanyCraftDraftCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftManufactoryState
{
  std::string name;

  CompanyCraftManufactoryState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftPart
{
  uint8_t companyCraftType;
  std::vector< uint16_t > companyCraftProcess;

  CompanyCraftPart( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftProcess
{

  CompanyCraftProcess( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftSequence
{
  int32_t resultItem;
  int32_t category;
  int32_t companyCraftDraftCategory;
  int32_t companyCraftType;
  int32_t companyCraftDraft;
  std::vector< uint16_t > companyCraftPart;
  uint32_t order;

  CompanyCraftSequence( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftSupplyItem
{
  uint32_t item;

  CompanyCraftSupplyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftType
{
  std::string name;

  CompanyCraftType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyLeve
{
  std::vector< uint16_t > routePointTime;
  std::vector< int32_t > baseID;
  std::vector< uint16_t > enemyLevel;
  std::vector< uint32_t > bNpcName;
  std::vector< int32_t > itemsInvolved;
  std::vector< uint8_t > itemsInvolvedQty;
  std::vector< uint8_t > itemDropRate;
  std::vector< uint8_t > toDoSequence;
  int32_t rule;
  uint8_t ruleParam;

  CompanyLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompanyLeveRule
{
  std::string type;
  uint16_t objective;
  uint16_t help;

  CompanyLeveRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompleteJournal
{
  uint16_t requiredLevel;
  int32_t icon;
  std::string name;
  std::vector< int32_t > cutscene;

  CompleteJournal( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CompleteJournalCategory
{
  uint32_t firstQuest;
  uint32_t lastQuest;

  CompleteJournalCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Condition
{
  uint32_t logMessage;

  Condition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ConfigKey
{
  std::string label;
  uint8_t param;
  uint8_t platform;
  bool required;
  uint8_t category;
  std::string text;

  ConfigKey( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentCloseCycle
{
  uint32_t unixtime;
  uint32_t timeSeconds;

  ContentCloseCycle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentExAction
{
  uint32_t name;
  uint8_t charges;

  ContentExAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentFinderCondition
{
  std::string shortCode;
  uint16_t territoryType;
  uint8_t contentLinkType;
  uint16_t content;
  bool pvP;
  uint8_t acceptClassJobCategory;
  uint8_t contentMemberType;
  uint32_t unlockQuest;
  uint8_t classJobLevelRequired;
  uint8_t classJobLevelSync;
  uint16_t itemLevelRequired;
  uint16_t itemLevelSync;
  bool addedIn53;
  bool allowUndersized;
  bool allowReplacement;
  bool allowExplorerMode;
  bool unknown54;
  bool highEndDuty;
  bool dutyRecorderAllowed;
  std::string name;
  uint8_t contentType;
  uint8_t transientKey;
  uint32_t transient;
  uint16_t sortKey;
  uint32_t image;
  uint32_t icon;
  bool levelingRoulette;
  bool level506070Roulette;
  bool mSQRoulette;
  bool guildHestRoulette;
  bool expertRoulette;
  bool trialRoulette;
  bool dailyFrontlineChallenge;
  bool level80Roulette;
  bool mentorRoulette;
  bool allianceRoulette;
  bool normalRaidRoulette;

  ContentFinderCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentFinderConditionTransient
{
  std::string description;

  ContentFinderConditionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentGauge
{
  std::string name;
  uint8_t color;
  std::string textString;

  ContentGauge( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentGaugeColor
{
  uint32_t androidColor1;
  uint32_t androidColor2;
  uint32_t androidColor3;

  ContentGaugeColor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentMemberType
{
  uint8_t tanksPerParty;
  uint8_t healersPerParty;
  uint8_t meleesPerParty;
  uint8_t rangedPerParty;
  uint8_t unknown54;

  ContentMemberType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentNpcTalk
{
  int32_t type;
  std::vector< uint32_t > contentTalk;

  ContentNpcTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentRandomSelect
{
  uint16_t name;

  ContentRandomSelect( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentRoulette
{
  std::string name;
  std::string category;
  std::string description;
  std::string dutyType;
  bool isInDutyFinder;
  uint8_t openRule;
  uint8_t requiredLevel;
  uint16_t itemLevelRequired;
  uint32_t icon;
  uint8_t contentRouletteRoleBonus;
  uint16_t rewardTomeA;
  uint16_t rewardTomeB;
  uint16_t rewardTomeC;
  uint8_t sortKey;
  uint8_t contentMemberType;
  bool requireAllDuties;
  uint8_t contentRouletteOpenRule;
  uint16_t instanceContent;

  ContentRoulette( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentRouletteOpenRule
{
  uint32_t type;

  ContentRouletteOpenRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentRouletteRoleBonus
{
  uint32_t itemRewardType;
  uint8_t rewardAmount;

  ContentRouletteRoleBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentsNote
{
  uint8_t contentType;
  int32_t icon;
  uint8_t menuOrder;
  int32_t requiredAmount;
  uint8_t reward0;
  int32_t expMultiplier;
  uint8_t reward1;
  int32_t gilRward;
  uint16_t levelUnlock;
  uint16_t howTo;
  uint32_t reqUnlock;
  std::string name;
  std::string description;
  int32_t expCap;

  ContentsNote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentsTutorial
{
  std::string name;
  std::string description;
  std::vector< int32_t > page;

  ContentsTutorial( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentsTutorialPage
{
  int32_t image;
  std::string description;

  ContentsTutorialPage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentTalk
{
  uint8_t contentTalkParam;
  std::string text;

  ContentTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentTalkParam
{
  bool param;
  uint32_t testAction;

  ContentTalkParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ContentType
{
  std::string name;
  uint32_t icon;
  uint32_t iconDutyFinder;

  ContentType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CraftAction
{
  std::string name;
  std::string description;
  uint16_t animationStart;
  uint16_t animationEnd;
  uint16_t icon;
  int8_t classJob;
  uint8_t classJobCategory;
  uint8_t classJobLevel;
  uint32_t questRequirement;
  bool specialist;
  uint8_t cost;
  int32_t cRP;
  int32_t bSM;
  int32_t aRM;
  int32_t gSM;
  int32_t lTW;
  int32_t wVR;
  int32_t aLC;
  int32_t cUL;

  CraftAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CraftLeve
{
  int32_t leve;
  int32_t craftLeveTalk;
  uint8_t repeats;

  CraftLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CraftLevelDifference
{
  int16_t difference;
  int16_t progressFactor;
  int16_t qualityFactor;

  CraftLevelDifference( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CraftType
{
  uint8_t mainPhysical;
  uint8_t subPhysical;
  std::string name;

  CraftType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Credit
{
  uint16_t roles1;
  uint16_t japaneseCast1;
  uint16_t englishCast1;
  uint16_t frenchCast1;
  uint16_t germanCast1;
  uint16_t roles2;
  uint16_t japaneseCast2;
  uint16_t englishCast2;
  uint16_t frenchCast2;
  uint16_t germanCast2;

  Credit( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CreditBackImage
{
  bool unknown54;
  uint32_t backImage;

  CreditBackImage( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CreditCast
{
  std::string name;

  CreditCast( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CreditList
{
  uint16_t scale;
  uint32_t icon;
  uint32_t font;
  uint32_t cast;

  CreditList( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CreditListText
{
  std::string name;

  CreditListText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CustomTalk
{
  uint32_t iconActor;
  uint32_t iconMap;
  std::string name;
  std::vector< std::string > scriptInstruction;
  std::vector< uint32_t > scriptArg;
  bool text;
  bool unknown54;

  CustomTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CustomTalkDynamicIcon
{
  uint32_t smallIcon;
  uint32_t largeIcon;

  CustomTalkDynamicIcon( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CustomTalkNestHandlers
{
  uint32_t nestHandler;

  CustomTalkNestHandlers( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Cutscene
{
  std::string path;

  Cutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CutsceneMotion
{
  float wALK_LOOP_SPEED;
  float rUN_LOOP_SPEED;
  float sLOWWALK_LOOP_SPEED;
  float sLOWRUN_LOOP_SPEED;
  float bATTLEWALK_LOOP_SPEED;
  float bATTLERUN_LOOP_SPEED;
  float dASH_LOOP_SPEED;
  uint8_t tURN_CW90_FRAME;
  uint8_t tURN_CCW90_FRAME;
  uint8_t tURN_CW180_FRAME;
  uint8_t tURN_CCW180_FRAME;

  CutsceneMotion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CutsceneWorkIndex
{
  uint16_t workIndex;

  CutsceneWorkIndex( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CutScreenImage
{
  int16_t type;
  int32_t image;

  CutScreenImage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct CycleTime
{
  uint32_t firstCycle;
  uint32_t cycle;

  CycleTime( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DailySupplyItem
{

  DailySupplyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DawnContent
{
  uint32_t content;
  uint32_t exp;

  DawnContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DawnGrowMember
{
  uint32_t member;
  uint32_t imageName;
  uint32_t bigImageOld;
  uint32_t bigImageNew;
  uint32_t smallImageOld;
  uint32_t smallImageNew;
  uint8_t _class;

  DawnGrowMember( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DawnMemberUIParam
{
  std::string classSingular;
  uint32_t voiceLine;
  std::string classPlural;

  DawnMemberUIParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DawnQuestAnnounce
{
  uint32_t quest;
  uint8_t content;
  std::vector< uint32_t > eNPC;

  DawnQuestAnnounce( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DawnQuestMember
{
  uint32_t member;
  uint32_t imageName;
  uint32_t bigImageOld;
  uint32_t bigImageNew;
  uint8_t _class;

  DawnQuestMember( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeon
{
  uint8_t aetherpoolArm;
  uint8_t aetherpoolArmor;
  std::vector< uint8_t > pomanderSlot;
  std::vector< uint8_t > magiciteSlot;
  std::string name;
  uint16_t contentFinderConditionStart;

  DeepDungeon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonBan
{
  uint16_t screenImage;
  uint16_t logMessage;
  uint16_t name;

  DeepDungeonBan( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonDanger
{
  uint16_t screenImage;
  uint16_t logMessage;
  uint16_t name;

  DeepDungeonDanger( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonEquipment
{
  uint32_t icon;
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string name;
  std::string description;

  DeepDungeonEquipment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonFloorEffectUI
{
  uint32_t icon;
  std::string name;
  std::string description;

  DeepDungeonFloorEffectUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonItem
{
  uint32_t icon;
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string name;
  std::string tooltip;
  uint32_t action;

  DeepDungeonItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonLayer
{
  uint8_t deepDungeon;
  uint8_t floorSet;
  uint16_t roomA;
  uint16_t roomB;
  uint16_t roomC;
  uint8_t wepMinLv;
  uint8_t armourMinLv;

  DeepDungeonLayer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonMagicStone
{
  uint32_t icon;
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string name;
  std::string tooltip;

  DeepDungeonMagicStone( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonMap5X
{
  std::vector< uint16_t > deepDungeonRoom;

  DeepDungeonMap5X( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonRoom
{
  std::vector< uint32_t > level;

  DeepDungeonRoom( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonStatus
{
  uint16_t screenImage;
  uint16_t logMessage;
  uint16_t name;

  DeepDungeonStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DefaultTalk
{
  std::vector< uint16_t > actionTimelinePose;
  std::vector< std::string > text;

  DefaultTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DefaultTalkLipSyncType
{
  int32_t actionTimeline;

  DefaultTalkLipSyncType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DeliveryQuest
{
  int32_t quest;

  DeliveryQuest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Description
{
  uint32_t quest;
  std::string textLong;
  std::string textShort;
  std::string textCommentary;
  uint32_t section;

  Description( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DescriptionPage
{
  uint32_t quest;
  uint16_t text1;
  uint32_t image1;
  uint16_t text2;
  uint32_t image2;
  uint16_t text3;
  uint32_t image3;
  uint16_t text4;
  uint32_t image4;
  uint16_t text5;
  uint32_t image5;
  uint16_t text6;
  uint32_t image6;
  uint16_t text7;
  uint32_t image7;
  uint16_t text8;
  uint32_t image8;
  uint16_t text9;
  uint32_t image9;

  DescriptionPage( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DescriptionSection
{
  uint16_t string;
  uint16_t page;

  DescriptionSection( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DescriptionString
{
  std::string text;

  DescriptionString( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DisposalShop
{
  std::string shopName;

  DisposalShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DisposalShopFilterType
{
  std::string category;

  DisposalShopFilterType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DisposalShopItem
{
  int32_t itemDisposed;
  int32_t itemReceived;
  uint32_t quantityReceived;

  DisposalShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DpsChallenge
{
  uint16_t playerLevel;
  uint16_t placeName;
  uint32_t icon;
  uint16_t order;
  std::string name;
  std::string description;

  DpsChallenge( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DpsChallengeOfficer
{
  uint32_t unlockQuest;
  std::vector< uint16_t > challengeName;

  DpsChallengeOfficer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DpsChallengeTransient
{
  uint16_t instanceContent;

  DpsChallengeTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DynamicEvent
{
  uint8_t eventType;
  uint8_t enemyType;
  uint32_t lGBEventObject;
  uint32_t lGBMapRange;
  uint32_t quest;
  uint8_t singleBattle;
  uint32_t announce;
  std::string name;
  std::string description;

  DynamicEvent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DynamicEventEnemyType
{
  std::string name;

  DynamicEventEnemyType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DynamicEventSingleBattle
{
  int32_t actionIcon;
  uint32_t icon;
  std::string text;

  DynamicEventSingleBattle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct DynamicEventType
{
  uint32_t iconObjective0;
  uint32_t iconObjective1;

  DynamicEventType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EmjAddon
{
  std::string text;

  EmjAddon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EmjDani
{
  uint32_t icon;

  EmjDani( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Emote
{
  std::string name;
  std::vector< uint16_t > actionTimeline;
  uint8_t emoteCategory;
  uint8_t emoteMode;
  bool hasCancelEmote;
  bool drawsWeapon;
  uint16_t order;
  int32_t textCommand;
  uint16_t icon;
  uint16_t logMessageTargeted;
  uint16_t logMessageUntargeted;
  uint32_t unlockLink;

  Emote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EmoteCategory
{
  std::string name;

  EmoteCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EmoteMode
{
  uint16_t startEmote;
  uint16_t endEmote;
  bool move;
  bool camera;
  bool endOnRotate;
  bool endOnEmote;
  uint8_t conditionMode;

  EmoteMode( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ENpcBase
{
  uint16_t eventHandler;
  bool important;
  std::vector< uint32_t > eNpcData;
  float scale;
  uint16_t modelChara;
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
  uint16_t npcEquip;
  uint16_t behavior;
  uint64_t modelMainHand;
  uint8_t dyeMainHand;
  uint64_t modelOffHand;
  uint8_t dyeOffHand;
  uint32_t modelHead;
  uint8_t dyeHead;
  bool visor;
  uint32_t modelBody;
  uint8_t dyeBody;
  uint32_t modelHands;
  uint8_t dyeHands;
  uint32_t modelLegs;
  uint8_t dyeLegs;
  uint32_t modelFeet;
  uint8_t dyeFeet;
  uint32_t modelEars;
  uint8_t dyeEars;
  uint32_t modelNeck;
  uint8_t dyeNeck;
  uint32_t modelWrists;
  uint8_t dyeWrists;
  uint32_t modelLeftRing;
  uint8_t dyeLeftRing;
  uint32_t modelRightRing;
  uint8_t dyeRightRing;
  uint8_t invisibility;
  uint16_t balloon;
  bool notRewriteHeight;
  uint8_t defaultBalloon;

  ENpcBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ENpcDressUp
{
  uint8_t eNpcDressUpDress;

  ENpcDressUp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ENpcDressUpDress
{
  bool addedIn530;
  uint32_t eNpc;
  uint16_t addedIn531;
  uint16_t behavior;
  uint8_t addedIn532;
  uint64_t modelMainHand;
  uint8_t dyeMainHand;
  uint64_t modelOffHand;
  uint8_t dyeOffHand;
  uint32_t modelHead;
  uint8_t dyeHead;
  uint32_t modelBody;
  uint8_t dyeBody;
  uint32_t modelHands;
  uint8_t dyeHands;
  uint32_t modelLegs;
  uint8_t dyeLegs;
  uint32_t modelFeet;
  uint8_t dyeFeet;

  ENpcDressUpDress( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ENpcResident
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string title;
  uint8_t map;

  ENpcResident( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EObj
{
  uint8_t popType;
  uint32_t data;
  uint8_t invisibility;
  uint16_t sgbPath;
  bool eyeCollision;
  bool directorControl;
  bool target;
  uint8_t eventHighAddition;
  bool addedIn53;

  EObj( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EObjName
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;

  EObjName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EquipRaceCategory
{
  bool hyur;
  bool elezen;
  bool lalafell;
  bool miqote;
  bool roegadyn;
  bool auRa;
  bool male;
  bool female;

  EquipRaceCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EquipSlotCategory
{
  int8_t mainHand;
  int8_t offHand;
  int8_t head;
  int8_t body;
  int8_t gloves;
  int8_t waist;
  int8_t legs;
  int8_t feet;
  int8_t ears;
  int8_t neck;
  int8_t wrists;
  int8_t fingerL;
  int8_t fingerR;
  int8_t soulCrystal;

  EquipSlotCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaAetherItem
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string name;

  EurekaAetherItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaAethernet
{
  uint16_t location;

  EurekaAethernet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaGrowData
{
  uint16_t baseResistance;

  EurekaGrowData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaLogosMixerProbability
{
  uint8_t probability;

  EurekaLogosMixerProbability( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaMagiaAction
{
  uint32_t action;
  uint8_t maxUses;

  EurekaMagiaAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaMagiciteItem
{
  uint8_t eurekaMagiciteItemType;
  uint8_t classJobCategory;
  uint32_t item;

  EurekaMagiciteItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaMagiciteItemType
{
  std::string type;

  EurekaMagiciteItemType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EurekaSphereElementAdjust
{
  uint16_t powerModifier;

  EurekaSphereElementAdjust( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventAction
{
  std::string name;
  uint16_t icon;
  uint8_t castTime;
  std::vector< uint16_t > animation;

  EventAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventIconPriority
{
  std::vector< uint32_t > icon;

  EventIconPriority( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventIconType
{
  uint32_t npcIconAvailable;
  uint32_t mapIconAvailable;
  uint32_t npcIconInvalid;
  uint32_t mapIconInvalid;
  uint8_t iconRange;

  EventIconType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventItem
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string name;
  uint16_t icon;
  uint16_t action;
  uint8_t stackSize;
  uint32_t quest;
  uint8_t castTime;
  uint8_t castTimeline;
  uint8_t timeline;

  EventItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventItemCastTimeline
{
  uint32_t actionTimeline;

  EventItemCastTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventItemHelp
{
  std::string description;

  EventItemHelp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventItemTimeline
{
  uint32_t actionTimeline;

  EventItemTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct EventSystemDefine
{
  std::string text;
  uint32_t defineValue;

  EventSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ExportedSG
{
  std::string sgbPath;

  ExportedSG( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ExVersion
{
  std::string name;
  uint16_t acceptJingle;
  uint16_t completeJingle;

  ExVersion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Fate
{
  uint8_t eurekaFate;
  uint8_t rule;
  uint16_t fateRuleEx;
  uint32_t location;
  uint8_t classJobLevel;
  uint8_t classJobLevelMax;
  uint32_t eventItem;
  std::vector< uint8_t > typeToDoValue;
  uint32_t iconObjective;
  uint32_t iconMap;
  uint32_t iconInactiveMap;
  int32_t music;
  uint32_t lGBGuardNPCLocation;
  uint16_t screenImageAccept;
  uint16_t screenImageComplete;
  uint16_t screenImageFailed;
  bool specialFate;
  uint16_t givenStatus;
  bool adventEvent;
  bool moonFaireEvent;
  uint32_t fATEChain;
  std::string name;
  std::string description;
  std::string objective;
  std::vector< std::string > statusText;
  uint32_t arrayIndex;
  uint32_t reqEventItem;
  uint32_t turnInEventItem;
  std::vector< uint16_t > objectiveIcon;

  Fate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FateEvent
{
  std::vector< uint8_t > turn;
  std::vector< uint32_t > gesture;
  std::vector< int32_t > lipSync;
  std::vector< int32_t > facial;
  std::vector< int32_t > shape;
  std::vector< bool > isAutoShake;
  std::vector< uint8_t > widgetType;
  std::vector< std::string > text;

  FateEvent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FateMode
{
  uint32_t motivationIcon;
  uint32_t motivationMapMarker;
  uint32_t objectiveIcon;
  uint32_t objectiveMapMarker;

  FateMode( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FateProgressUI
{
  int32_t location;
  int32_t achievement;
  uint8_t reqFatesToRank2;
  uint8_t reqFatesToRank3;
  uint8_t displayOrder;

  FateProgressUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FateTokenType
{
  uint32_t currency;

  FateTokenType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCActivity
{
  std::string text;
  uint8_t selfKind;
  uint8_t targetKind;
  uint8_t numParam;
  uint8_t fCActivityCategory;
  int8_t iconType;

  FCActivity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCActivityCategory
{
  uint8_t priority;
  std::string name;

  FCActivityCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCAuthority
{
  std::string name;
  int32_t fCAuthorityCategory;

  FCAuthority( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCAuthorityCategory
{
  std::string name;

  FCAuthorityCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCChestName
{
  std::string name;

  FCChestName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCCrestSymbol
{
  uint8_t colorNum;
  uint8_t fCRight;

  FCCrestSymbol( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FccShop
{
  std::string name;

  FccShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCHierarchy
{
  std::string name;

  FCHierarchy( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCProfile
{
  uint8_t priority;
  std::string name;

  FCProfile( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCRank
{
  uint32_t nextPoint;
  uint32_t currentPoint;
  uint16_t rights;
  uint8_t fCActionActiveNum;
  uint8_t fCActionStockNum;

  FCRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCReputation
{
  uint32_t pointsToNext;
  uint32_t requiredPoints;
  uint8_t discountRate;
  uint32_t color;
  std::string name;

  FCReputation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FCRights
{
  std::string name;
  std::string description;
  uint16_t icon;
  uint8_t fCRank;

  FCRights( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Festival
{
  std::string name;

  Festival( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FieldMarker
{
  int32_t vFX;
  uint16_t icon;

  FieldMarker( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FishingRecordType
{
  int32_t addon;
  uint16_t rankBRequirement;
  uint16_t rankARequirement;
  uint16_t rankAARequirement;
  uint16_t rankAAARequirement;

  FishingRecordType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FishingRecordTypeTransient
{
  int32_t image;

  FishingRecordTypeTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FishingSpot
{
  uint8_t gatheringLevel;
  std::string bigFishOnReach;
  std::string bigFishOnEnd;
  uint8_t fishingSpotCategory;
  bool rare;
  uint16_t territoryType;
  uint16_t placeNameMain;
  uint16_t placeNameSub;
  int16_t x;
  int16_t z;
  uint16_t radius;
  std::vector< int32_t > item;
  uint16_t placeName;
  uint8_t order;

  FishingSpot( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FishParameter
{
  std::string text;
  int32_t item;
  uint16_t gatheringItemLevel;
  bool isHidden;
  uint8_t fishingRecordType;
  int32_t territoryType;
  uint16_t gatheringSubCategory;
  bool isInLog;
  bool timeRestricted;
  bool weatherRestricted;

  FishParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Frontline03
{
  std::vector< uint32_t > emptyIcon;
  std::vector< uint32_t > maelstromIcon;
  std::vector< uint32_t > twinAdderIcon;
  std::vector< uint32_t > immortalFlamesIcon;

  Frontline03( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Frontline04
{
  int32_t level1;
  int32_t level2;
  int32_t level3;
  std::vector< int32_t > unknownLevel;

  Frontline04( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FurnitureCatalogCategory
{
  std::string category;

  FurnitureCatalogCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct FurnitureCatalogItemList
{
  uint16_t category;
  int32_t item;
  uint16_t patch;

  FurnitureCatalogItemList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GardeningSeed
{
  uint32_t item;
  uint16_t modelID;
  uint32_t icon;
  bool sE;

  GardeningSeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringCondition
{
  std::string text;

  GatheringCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringExp
{
  int32_t exp;

  GatheringExp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringItem
{
  int32_t item;
  uint16_t gatheringItemLevel;
  bool isHidden;

  GatheringItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringItemLevelConvertTable
{
  uint8_t gatheringItemLevel;
  uint8_t stars;

  GatheringItemLevelConvertTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringItemPoint
{
  uint32_t gatheringPoint;

  GatheringItemPoint( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringLeve
{
  std::vector< int32_t > route;
  int32_t requiredItem0;
  uint8_t requiredItemQty0;
  int32_t requiredItem1;
  uint8_t requiredItemQty1;
  int32_t requiredItem2;
  uint8_t requiredItemQty2;
  int32_t requiredItem3;
  uint8_t requiredItemQty3;
  uint8_t itemNumber;
  int32_t rule;
  uint8_t varient;
  uint16_t objective0;
  uint16_t objective1;
  int32_t bNpcEntry;
  bool useSecondaryTool;

  GatheringLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringLeveRoute
{

  GatheringLeveRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringLeveRule
{
  std::string rule;

  GatheringLeveRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringNotebookList
{
  std::vector< int32_t > gatheringItem;

  GatheringNotebookList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringPoint
{
  uint8_t type;
  int32_t gatheringPointBase;
  uint8_t count;
  std::vector< uint16_t > gatheringPointBonus;
  uint16_t territoryType;
  uint16_t placeName;
  uint16_t gatheringSubCategory;

  GatheringPoint( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBase
{
  int32_t gatheringType;
  uint8_t gatheringLevel;
  std::vector< int32_t > item;
  bool isLimited;

  GatheringPointBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBonus
{
  uint8_t condition;
  uint32_t conditionValue;
  uint8_t bonusType;
  uint16_t bonusValue;
  bool unknown53;
  uint32_t unknown54;

  GatheringPointBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBonusType
{
  std::string text;

  GatheringPointBonusType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringPointName
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;

  GatheringPointName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringPointTransient
{
  uint16_t ephemeralStartTime;
  uint16_t ephemeralEndTime;
  int32_t gatheringRarePopTimeTable;

  GatheringPointTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringRarePopTimeTable
{

  GatheringRarePopTimeTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringSubCategory
{
  uint8_t gatheringType;
  uint8_t classJob;
  uint16_t division;
  int32_t item;
  std::string folkloreBook;

  GatheringSubCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GatheringType
{
  std::string name;
  int32_t iconMain;
  int32_t iconOff;

  GatheringType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GcArmyCaptureTactics
{
  int32_t name;
  uint8_t hP;
  uint8_t damageDealt;
  uint8_t damageReceived;
  uint32_t tactic;
  uint32_t icon;

  GcArmyCaptureTactics( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GcArmyExpedition
{
  uint8_t requiredFlag;
  uint8_t unlockFlag;
  uint8_t requiredLevel;
  uint16_t requiredSeals;
  uint32_t rewardExperience;
  uint8_t percentBase;
  uint8_t gcArmyExpeditionType;
  std::string name;
  std::string description;

  GcArmyExpedition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GcArmyExpeditionMemberBonus
{
  uint8_t race;
  uint8_t classJob;

  GcArmyExpeditionMemberBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GcArmyExpeditionType
{
  std::string name;

  GcArmyExpeditionType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GcArmyMemberGrow
{
  uint8_t classJob;
  int32_t classBook;

  GcArmyMemberGrow( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GcArmyTraining
{
  int8_t physicalBonus;
  int8_t mentalBonus;
  int8_t tacticalBonus;
  uint32_t experience;
  std::string name;
  std::string description;

  GcArmyTraining( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCRankGridaniaFemaleText
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string nameRank;

  GCRankGridaniaFemaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCRankGridaniaMaleText
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string nameRank;

  GCRankGridaniaMaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCRankLimsaFemaleText
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string nameRank;

  GCRankLimsaFemaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCRankLimsaMaleText
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string nameRank;

  GCRankLimsaMaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCRankUldahFemaleText
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string nameRank;

  GCRankUldahFemaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCRankUldahMaleText
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string nameRank;

  GCRankUldahMaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCScripShopCategory
{
  int8_t grandCompany;
  int8_t tier;
  int8_t subCategory;

  GCScripShopCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCScripShopItem
{
  int32_t item;
  int32_t requiredGrandCompanyRank;
  uint32_t costGCSeals;
  uint8_t sortKey;

  GCScripShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCShop
{
  int8_t grandCompany;

  GCShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCShopItemCategory
{
  std::string name;

  GCShopItemCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCSupplyDuty
{

  GCSupplyDuty( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GCSupplyDutyReward
{
  uint32_t experienceSupply;
  uint32_t experienceProvisioning;
  uint32_t sealsExpertDelivery;
  uint32_t sealsSupply;
  uint32_t sealsProvisioning;

  GCSupplyDutyReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GeneralAction
{
  std::string name;
  std::string description;
  uint16_t action;
  uint16_t unlockLink;
  uint8_t recast;
  uint8_t uIPriority;
  int32_t icon;

  GeneralAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GFATE
{
  std::vector< uint32_t > icon;

  GFATE( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GFateClimbing2
{
  uint32_t contentEntry;

  GFateClimbing2( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GFateClimbing2Content
{
  uint32_t publicContentTextData;

  GFateClimbing2Content( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GFateClimbing2TotemType
{
  uint32_t publicContentTextData;

  GFateClimbing2TotemType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GFateRideShooting
{
  uint32_t contentEntry;

  GFateRideShooting( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GilShop
{
  std::string name;
  uint32_t icon;
  uint32_t quest;
  int32_t acceptTalk;
  int32_t failTalk;

  GilShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GilShopItem
{
  int32_t item;
  std::vector< int32_t > rowRequired;
  uint16_t stateRequired;
  uint16_t patch;

  GilShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GimmickAccessor
{
  int32_t param0;
  uint32_t param1;
  uint32_t param2;
  uint32_t type;

  GimmickAccessor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GimmickJump
{
  uint16_t fallDamage;
  int8_t height;
  uint32_t loopMotion;
  uint32_t endMotion;
  bool startClient;

  GimmickJump( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GimmickRect
{
  uint32_t layoutID;
  uint8_t triggerIn;
  uint32_t param0;
  uint8_t triggerOut;
  uint32_t param1;

  GimmickRect( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GoldSaucerArcadeMachine
{
  uint32_t failImage;
  uint32_t poor;
  uint32_t good;
  uint32_t great;
  uint32_t excellent;

  GoldSaucerArcadeMachine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GoldSaucerTextData
{
  std::string text;

  GoldSaucerTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GrandCompany
{
  std::string name;

  GrandCompany( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GrandCompanyRank
{
  uint8_t tier;
  uint8_t order;
  uint32_t maxSeals;
  uint32_t requiredSeals;
  int32_t iconMaelstrom;
  int32_t iconSerpents;
  int32_t iconFlames;
  int32_t questMaelstrom;
  int32_t questSerpents;
  int32_t questFlames;

  GrandCompanyRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GroupPoseFrame
{
  int32_t image;
  std::string gridText;
  int32_t unknown54;
  std::string text;

  GroupPoseFrame( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GroupPoseStamp
{
  int32_t stampIcon;
  int32_t category;
  int32_t unknown540;
  bool unknown541;
  std::string name;

  GroupPoseStamp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GroupPoseStampCategory
{
  std::string name;

  GroupPoseStampCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuardianDeity
{
  std::string name;
  std::string description;
  uint16_t icon;

  GuardianDeity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Guide
{
  uint16_t guideTitle;
  uint16_t guidePage;

  Guide( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuidePage
{
  uint8_t key;
  uint32_t output;

  GuidePage( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuidePageString
{
  std::string string;

  GuidePageString( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuideTitle
{
  std::string title;

  GuideTitle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuildleveAssignment
{
  uint8_t addedIn53;
  uint32_t assignmentTalk;
  std::vector< uint32_t > quest;

  GuildleveAssignment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuildleveAssignmentCategory
{
  std::vector< int32_t > category;

  GuildleveAssignmentCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuildOrder
{
  uint32_t eNpcName;
  std::string objective;
  std::string description1;
  std::string description2;
  std::string description3;
  uint32_t completionBonusExp;
  uint32_t rewardExp;
  uint32_t completionBonusGil;
  uint32_t rewardGil;

  GuildOrder( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuildOrderGuide
{

  GuildOrderGuide( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct GuildOrderOfficer
{

  GuildOrderOfficer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HairMakeType
{
  int32_t race;
  int32_t tribe;
  int8_t gender;

  HairMakeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HouseRetainerPose
{
  uint16_t actionTimeline;

  HouseRetainerPose( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingAethernet
{
  uint32_t level;
  uint16_t territoryType;
  uint16_t placeName;
  uint8_t order;

  HousingAethernet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingAppeal
{
  std::string tag;
  uint32_t icon;
  uint8_t order;

  HousingAppeal( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingEmploymentNpcList
{
  uint8_t race;
  std::vector< uint32_t > eNpcBase;

  HousingEmploymentNpcList( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingEmploymentNpcRace
{
  std::string race;

  HousingEmploymentNpcRace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingExterior
{
  uint16_t placeName;
  uint8_t housingSize;
  std::string model;

  HousingExterior( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingFurniture
{
  uint16_t modelKey;
  uint8_t housingItemCategory;
  uint8_t usageType;
  uint32_t usageParameter;
  uint8_t aquariumTier;
  uint32_t customTalk;
  uint32_t item;
  bool destroyOnRemoval;
  bool tooltip;

  HousingFurniture( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingLandSet
{
  std::vector< uint8_t > plotSize;
  std::vector< uint32_t > minPrice;
  std::vector< uint32_t > initialPrice;

  HousingLandSet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingMapMarkerInfo
{
  float x;
  float y;
  float z;
  uint16_t map;

  HousingMapMarkerInfo( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingMerchantPose
{
  uint16_t actionTimeline;
  std::string pose;

  HousingMerchantPose( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingPlacement
{
  std::string text;

  HousingPlacement( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingPreset
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  uint16_t placeName;
  uint8_t housingSize;
  int32_t exteriorRoof;
  int32_t exteriorWall;
  int32_t exteriorWindow;
  int32_t exteriorDoor;
  int32_t interiorWall;
  int32_t interiorFlooring;
  int32_t interiorLighting;
  int32_t otherFloorWall;
  int32_t otherFloorFlooring;
  int32_t otherFloorLighting;
  int32_t basementWall;
  int32_t basementFlooring;
  int32_t basementLighting;
  int32_t mansionLighting;

  HousingPreset( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingUnitedExterior
{
  std::vector< uint32_t > item;

  HousingUnitedExterior( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HousingYardObject
{
  uint8_t modelKey;
  uint8_t housingItemCategory;
  uint8_t usageType;
  uint32_t usageParameter;
  uint32_t customTalk;
  uint32_t item;
  bool destroyOnRemoval;

  HousingYardObject( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HowTo
{
  std::vector< int16_t > images;
  int8_t category;

  HowTo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HowToCategory
{
  std::string category;

  HowToCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HowToPage
{
  int32_t image;

  HowToPage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HugeCraftworksNpc
{
  uint32_t eNpcResident;
  uint16_t classJobCategory;
  std::vector< uint32_t > itemRequested;
  std::vector< uint8_t > qtyRequested;
  std::vector< uint32_t > itemReward;
  std::vector< uint8_t > qtyItemReward;
  std::vector< uint32_t > itemUnkown;
  std::vector< uint8_t > qtyItemUnkown;
  std::string transient;

  HugeCraftworksNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HugeCraftworksRank
{
  uint8_t crafterLevel;
  uint32_t expRewardPerItem;

  HugeCraftworksRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDAnnounce
{
  std::string name;
  uint32_t eNPC;

  HWDAnnounce( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDCrafterSupply
{
  std::vector< uint32_t > itemTradeIn;
  std::vector< uint8_t > level;
  std::vector< uint8_t > levelMax;
  std::vector< uint16_t > baseCollectableRating;
  std::vector< uint16_t > midCollectableRating;
  std::vector< uint16_t > highCollectableRating;
  std::vector< uint16_t > baseCollectableReward;
  std::vector< uint16_t > midCollectableReward;
  std::vector< uint16_t > highCollectableReward;
  std::vector< uint16_t > baseCollectableRewardPostPhase;
  std::vector< uint16_t > midCollectableRewardPostPhase;
  std::vector< uint16_t > highCollectableRewardPostPhase;
  std::vector< uint8_t > termName;

  HWDCrafterSupply( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDCrafterSupplyReward
{
  uint16_t scriptRewardAmount;
  uint32_t expReward;
  uint16_t Points;

  HWDCrafterSupplyReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDCrafterSupplyTerm
{
  std::string name;

  HWDCrafterSupplyTerm( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDDevLayerControl
{

  HWDDevLayerControl( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDDevLevelUI
{

  HWDDevLevelUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDDevLively
{
  uint32_t eNPC;

  HWDDevLively( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDDevProgress
{
  bool canGoNext;

  HWDDevProgress( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDGathereInspectTerm
{
  std::string name;

  HWDGathereInspectTerm( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDGathererInspection
{
  std::vector< uint32_t > itemRequired;
  std::vector< uint32_t > fishParameter;
  std::vector< uint8_t > amountRequired;
  std::vector< uint32_t > itemReceived;
  std::vector< uint16_t > reward1;
  std::vector< uint16_t > reward2;
  std::vector< uint8_t > phase;

  HWDGathererInspection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDGathererInspectionReward
{
  uint16_t scrips;
  uint16_t points;

  HWDGathererInspectionReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDInfoBoardArticle
{
  uint8_t type;
  std::string text;

  HWDInfoBoardArticle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDInfoBoardArticleTransient
{
  uint32_t image;
  std::string text;
  std::string npcName;

  HWDInfoBoardArticleTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDInfoBoardArticleType
{
  std::string type;

  HWDInfoBoardArticleType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDLevelChangeDeception
{
  int32_t image;

  HWDLevelChangeDeception( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDSharedGroup
{
  uint32_t lGB;
  uint8_t param;

  HWDSharedGroup( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct HWDSharedGroupControlParam
{
  uint8_t paramValue;

  HWDSharedGroupControlParam( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct IKDContentBonus
{
  std::string objective;
  std::string requirement;
  uint32_t image;
  uint8_t order;

  IKDContentBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct IKDFishParam
{
  uint32_t fish;
  uint8_t iKDContentBonus;
  uint8_t unknown54;

  IKDFishParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct IKDRoute
{
  uint32_t image;
  uint32_t territoryType;
  std::string name;

  IKDRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct IKDRouteTable
{
  uint32_t route;

  IKDRouteTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct IKDSpot
{
  uint32_t spotMain;
  uint32_t spotSub;
  uint32_t placeName;

  IKDSpot( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InclusionShop
{
  std::vector< uint16_t > category;

  InclusionShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InclusionShopCategory
{
  std::string name;
  uint8_t classJobCategory;
  uint16_t inclusionShopSeries;

  InclusionShopCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InclusionShopSeries
{
  uint32_t specialShop;

  InclusionShopSeries( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct IndividualWeather
{
  std::vector< uint8_t > weather;
  uint8_t addedIn530;
  uint8_t addedIn531;
  std::vector< uint32_t > quest;

  IndividualWeather( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InstanceContent
{
  uint8_t instanceContentType;
  uint8_t weekRestriction;
  uint16_t timeLimitmin;
  uint16_t bGM;
  uint16_t winBGM;
  uint32_t cutscene;
  uint16_t order;
  uint8_t colosseum;
  uint32_t instanceContentTextDataBossStart;
  uint32_t instanceContentTextDataBossEnd;
  uint32_t bNpcBaseBoss;
  uint32_t instanceContentTextDataObjectiveStart;
  uint32_t instanceContentTextDataObjectiveEnd;
  uint16_t sortKey;
  uint32_t instanceClearExp;
  uint16_t newPlayerBonusA;
  uint16_t finalBossCurrencyC;
  uint32_t finalBossCurrencyA;
  uint16_t finalBossCurrencyB;
  uint16_t newPlayerBonusB;
  uint32_t instanceClearGil;
  uint32_t instanceContentRewardItem;
  uint8_t finalBossExp;
  uint32_t instanceContentBuff;
  int32_t reqInstance;
  int16_t partyCondition;
  uint16_t unknown540;
  uint16_t unknown541;

  InstanceContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InstanceContentBuff
{
  uint16_t echoStart;
  uint16_t echoDeath;

  InstanceContentBuff( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InstanceContentCSBonus
{
  uint16_t instance;
  uint32_t item;
  uint8_t unknown540;
  uint8_t unknown541;

  InstanceContentCSBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InstanceContentGuide
{
  uint32_t instance;

  InstanceContentGuide( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct InstanceContentTextData
{
  std::string text;

  InstanceContentTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Item
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  std::string description;
  std::string name;
  uint16_t icon;
  uint16_t levelItem;
  uint8_t rarity;
  uint8_t filterGroup;
  uint32_t additionalData;
  uint8_t itemUICategory;
  uint8_t itemSearchCategory;
  uint8_t equipSlotCategory;
  uint8_t itemSortCategory;
  uint32_t stackSize;
  bool isUnique;
  bool isUntradable;
  bool isIndisposable;
  bool lot;
  uint32_t priceMid;
  uint32_t priceLow;
  bool canBeHq;
  bool isDyeable;
  bool isCrestWorthy;
  uint16_t itemAction;
  uint16_t cooldowns;
  uint8_t classJobRepair;
  int32_t itemRepair;
  int32_t itemGlamour;
  uint16_t desynth;
  bool isCollectable;
  bool alwaysCollectable;
  uint16_t aetherialReduce;
  uint16_t unknown54;
  uint8_t levelEquip;
  uint8_t equipRestriction;
  uint8_t classJobCategory;
  uint8_t grandCompany;
  uint8_t itemSeries;
  uint8_t baseParamModifier;
  uint64_t modelMain;
  uint64_t modelSub;
  uint8_t classJobUse;
  uint16_t damagePhys;
  uint16_t damageMag;
  uint16_t delayms;
  uint16_t blockRate;
  uint16_t block;
  uint16_t defensePhys;
  uint16_t defenseMag;
  uint8_t itemSpecialBonus;
  uint8_t itemSpecialBonusParam;
  uint8_t materializeType;
  uint8_t materiaSlotCount;
  bool isAdvancedMeldingPermitted;
  bool isPvP;
  bool isGlamourous;

  struct
  {
    uint8_t baseparam;
    int16_t value;
  } param[6];

  Item( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemAction
{
  uint8_t condLv;
  bool condBattle;
  bool condPVP;
  bool condPVPOnly;
  uint16_t type;
  std::vector< uint16_t > data;
  std::vector< uint16_t > dataHQ;

  ItemAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemActionTelepo
{
  uint32_t requirement;
  uint32_t denyMessage;

  ItemActionTelepo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemBarterCheck
{
  uint16_t category;
  uint32_t question;
  uint32_t confirm;

  ItemBarterCheck( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemFood
{
  uint8_t eXPBonus;

  ItemFood( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemLevel
{
  uint16_t strength;
  uint16_t dexterity;
  uint16_t vitality;
  uint16_t intelligence;
  uint16_t mind;
  uint16_t piety;
  uint16_t hP;
  uint16_t mP;
  uint16_t tP;
  uint16_t gP;
  uint16_t cP;
  uint16_t physicalDamage;
  uint16_t magicalDamage;
  uint16_t delay;
  uint16_t additionalEffect;
  uint16_t attackSpeed;
  uint16_t blockRate;
  uint16_t blockStrength;
  uint16_t tenacity;
  uint16_t attackPower;
  uint16_t defense;
  uint16_t directHitRate;
  uint16_t evasion;
  uint16_t magicDefense;
  uint16_t criticalHitPower;
  uint16_t criticalHitResilience;
  uint16_t criticalHit;
  uint16_t criticalHitEvasion;
  uint16_t slashingResistance;
  uint16_t piercingResistance;
  uint16_t bluntResistance;
  uint16_t projectileResistance;
  uint16_t attackMagicPotency;
  uint16_t healingMagicPotency;
  uint16_t enhancementMagicPotency;
  uint16_t enfeeblingMagicPotency;
  uint16_t fireResistance;
  uint16_t iceResistance;
  uint16_t windResistance;
  uint16_t earthResistance;
  uint16_t lightningResistance;
  uint16_t waterResistance;
  uint16_t magicResistance;
  uint16_t determination;
  uint16_t skillSpeed;
  uint16_t spellSpeed;
  uint16_t haste;
  uint16_t morale;
  uint16_t enmity;
  uint16_t enmityReduction;
  uint16_t carefulDesynthesis;
  uint16_t eXPBonus;
  uint16_t regen;
  uint16_t refresh;
  uint16_t movementSpeed;
  uint16_t spikes;
  uint16_t slowResistance;
  uint16_t petrificationResistance;
  uint16_t paralysisResistance;
  uint16_t silenceResistance;
  uint16_t blindResistance;
  uint16_t poisonResistance;
  uint16_t stunResistance;
  uint16_t sleepResistance;
  uint16_t bindResistance;
  uint16_t heavyResistance;
  uint16_t doomResistance;
  uint16_t reducedDurabilityLoss;
  uint16_t increasedSpiritbondGain;
  uint16_t craftsmanship;
  uint16_t control;
  uint16_t gathering;
  uint16_t perception;

  ItemLevel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemSearchCategory
{
  std::string name;
  int32_t icon;
  uint8_t category;
  uint8_t order;
  int8_t classJob;

  ItemSearchCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemSeries
{
  std::string name;

  ItemSeries( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemSortCategory
{
  uint8_t param;

  ItemSortCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemSpecialBonus
{
  std::string name;

  ItemSpecialBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ItemUICategory
{
  std::string name;
  int32_t icon;
  uint8_t orderMinor;
  uint8_t orderMajor;

  ItemUICategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct JobHudManual
{
  uint32_t action;
  uint16_t guide;

  JobHudManual( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct JobHudManualPriority
{
  std::vector< uint8_t > jobHudManual;

  JobHudManualPriority( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct JournalCategory
{
  std::string name;
  uint8_t separateType;
  uint8_t dataType;
  uint8_t journalSection;

  JournalCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct JournalGenre
{
  int32_t icon;
  uint8_t journalCategory;
  std::string name;

  JournalGenre( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct JournalSection
{
  std::string name;

  JournalSection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Knockback
{
  uint8_t distance;
  uint8_t speed;
  bool motion;
  uint8_t nearDistance;
  uint8_t direction;
  uint8_t directionArg;
  bool cancelMove;

  Knockback( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LegacyQuest
{
  uint16_t legacyQuestID;
  std::string text;
  std::string string;
  uint16_t sortKey;
  uint8_t genre;

  LegacyQuest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Leve
{
  std::string name;
  std::string description;
  int32_t leveClient;
  uint8_t leveAssignmentType;
  int32_t town;
  uint16_t classJobLevel;
  uint8_t timeLimit;
  uint8_t allowanceCost;
  int32_t evaluation;
  int32_t placeNameStart;
  int32_t placeNameIssued;
  uint8_t classJobCategory;
  int32_t journalGenre;
  int32_t placeNameStartZone;
  int32_t iconCityState;
  int32_t dataId;
  bool canCancel;
  uint8_t maxDifficulty;
  float expFactor;
  uint32_t expReward;
  uint32_t gilReward;
  uint16_t leveRewardItem;
  uint8_t leveVfx;
  uint8_t leveVfxFrame;
  uint32_t levelLevemete;
  int32_t iconIssuer;
  bool lockedLeve;
  uint32_t levelStart;
  uint16_t bGM;

  Leve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LeveAssignmentType
{
  bool isFaction;
  int32_t icon;
  std::string name;

  LeveAssignmentType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LeveClient
{
  std::string name;

  LeveClient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Level
{
  float x;
  float y;
  float z;
  float yaw;
  float radius;
  uint8_t type;
  uint32_t object;
  uint16_t map;
  uint32_t eventId;
  uint16_t territory;

  Level( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LeveRewardItem
{

  LeveRewardItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LeveRewardItemGroup
{

  LeveRewardItemGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LeveString
{
  std::string objective;

  LeveString( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LeveVfx
{
  std::string effect;
  int32_t icon;

  LeveVfx( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Lobby
{
  uint32_t tYPE;
  uint32_t pARAM;
  uint32_t lINK;
  std::string text;

  Lobby( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LogFilter
{
  uint8_t logKind;
  uint16_t caster;
  uint16_t target;
  uint8_t category;
  uint8_t displayOrder;
  uint8_t preset;
  std::string name;
  std::string example;

  LogFilter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LogKind
{
  std::string format;

  LogKind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LogMessage
{
  uint16_t logKind;
  std::string text;

  LogMessage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct LotteryExchangeShop
{
  std::vector< int32_t > itemAccepted;
  std::vector< uint32_t > amountAccepted;
  std::vector< uint8_t > unknown540;
  std::vector< uint8_t > unknown541;
  std::string lua;
  std::vector< uint32_t > logMessage;

  LotteryExchangeShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MacroIcon
{
  int32_t icon;

  MacroIcon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MacroIconRedirectOld
{
  uint32_t iconOld;
  int32_t iconNew;

  MacroIconRedirectOld( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MainCommand
{
  int32_t icon;
  uint8_t category;
  uint8_t mainCommandCategory;
  int8_t sortID;
  std::string name;
  std::string description;

  MainCommand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MainCommandCategory
{
  std::string name;

  MainCommandCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ManeuversArmor
{
  std::vector< uint32_t > bNpcBase;
  std::vector< uint32_t > icon;

  ManeuversArmor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Map
{
  uint8_t mapCondition;
  uint8_t priorityCategoryUI;
  uint8_t priorityUI;
  int8_t mapIndex;
  uint8_t hierarchy;
  uint16_t mapMarkerRange;
  std::string id;
  uint16_t sizeFactor;
  int16_t offsetX;
  int16_t offsetY;
  uint16_t placeNameRegion;
  uint16_t placeName;
  uint16_t placeNameSub;
  int16_t discoveryIndex;
  uint32_t discoveryFlag;
  uint16_t territoryType;
  bool discoveryArrayByte;
  bool isEvent;

  Map( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MapMarker
{
  int16_t x;
  int16_t y;
  uint16_t icon;
  uint16_t placeNameSubtext;
  uint8_t subtextOrientation;
  uint8_t mapMarkerRegion;
  uint8_t type;
  uint8_t dataType;
  uint16_t dataKey;

  MapMarker( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MapMarkerRegion
{
  int16_t x;

  MapMarkerRegion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MapSymbol
{
  int32_t icon;
  int32_t placeName;
  bool displayNavi;

  MapSymbol( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Marker
{
  int32_t icon;
  std::string name;

  Marker( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MasterpieceSupplyDuty
{
  uint8_t classJob;
  uint8_t classJobLevel;
  uint16_t rewardCurrency;

  MasterpieceSupplyDuty( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MasterpieceSupplyMultiplier
{
  std::vector< uint16_t > xpMultiplier;
  std::vector< uint16_t > currencyMultiplier;

  MasterpieceSupplyMultiplier( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Materia
{
  std::vector< int32_t > item;
  uint8_t baseParam;
  std::vector< int16_t > value;

  Materia( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MateriaJoinRate
{
  std::vector< float > NQOvermeldSlot;
  std::vector< float > HQOvermeldSlot;

  MateriaJoinRate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MateriaJoinRateGatherCraft
{
  std::vector< float > NQOvermeldSlot;
  std::vector< float > HQOvermeldSlot;

  MateriaJoinRateGatherCraft( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MateriaTomestoneRate
{
  uint32_t rate;

  MateriaTomestoneRate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MiniGameRA
{
  int32_t icon;
  int32_t image;
  int32_t bGM;

  MiniGameRA( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MinionRace
{
  std::string name;

  MinionRace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MinionRules
{
  std::string rule;
  std::string description;

  MinionRules( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MinionSkillType
{
  std::string name;

  MinionSkillType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MobHuntOrder
{
  uint16_t target;
  uint8_t neededKills;
  uint8_t type;
  uint8_t rank;
  uint8_t mobHuntReward;

  MobHuntOrder( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MobHuntOrderType
{
  uint8_t type;
  uint32_t quest;
  uint32_t eventItem;
  uint16_t orderStart;
  uint8_t orderAmount;

  MobHuntOrderType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MobHuntReward
{
  uint32_t expReward;
  uint16_t gilReward;
  uint8_t expansion;
  uint16_t currencyReward;

  MobHuntReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MobHuntRewardCap
{
  uint32_t expCap;

  MobHuntRewardCap( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MobHuntTarget
{
  uint16_t name;
  uint16_t fATE;
  uint32_t icon;
  uint16_t territoryType;
  uint16_t placeName;

  MobHuntTarget( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ModelChara
{
  uint8_t type;
  uint16_t model;
  uint8_t base;
  uint8_t variant;
  uint16_t sEPack;
  bool papVariation;

  ModelChara( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ModelSkeleton
{
  float radius;
  float height;
  float vFXScale;
  float floatHeight;
  float floatDown;
  uint16_t floatUp;
  bool motionBlendType;
  uint8_t loopFlySE;

  ModelSkeleton( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ModelState
{
  uint16_t start;

  ModelState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MonsterNote
{
  std::vector< uint16_t > monsterNoteTarget;
  std::vector< uint8_t > count;
  uint32_t reward;
  std::string name;

  MonsterNote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MonsterNoteTarget
{
  uint16_t bNpcName;
  int32_t icon;
  uint8_t town;

  MonsterNoteTarget( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MotionTimeline
{
  std::string filename;
  uint8_t blendGroup;
  bool isLoop;
  bool isBlinkEnable;
  bool isLipEnable;

  MotionTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MotionTimelineBlendTable
{
  uint8_t destBlendGroup;
  uint8_t srcBlendGroup;
  uint8_t blendFrame_PC;
  uint8_t blendFram_TypeA;
  uint8_t blendFram_TypeB;
  uint8_t blendFram_TypeC;

  MotionTimelineBlendTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Mount
{
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;
  int32_t modelChara;
  uint8_t flyingCondition;
  uint8_t isFlying;
  uint8_t mountCustomize;
  uint16_t rideBGM;
  uint8_t exitMoveDist;
  uint8_t exitMoveSpeed;
  bool isEmote;
  int32_t equipHead;
  int32_t equipBody;
  int32_t equipLeg;
  int32_t equipFoot;
  int16_t order;
  uint16_t icon;
  uint8_t uIPriority;
  uint8_t radiusRate;
  uint8_t baseMotionSpeed_Run;
  uint8_t baseMotionSpeed_Walk;
  uint8_t extraSeats;
  uint16_t mountAction;
  bool isAirborne;
  bool exHotbarEnableConfig;
  bool useEP;
  bool isImmobile;

  Mount( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MountAction
{
  std::vector< uint16_t > action;

  MountAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MountCustomize
{
  uint16_t hyurMaleScale;
  uint16_t hyurFemaleScale;
  uint16_t elezenMaleScale;
  uint16_t elezenFemaleScale;
  uint16_t lalaMaleScale;
  uint16_t lalaFemaleScale;
  uint16_t miqoMaleScale;
  uint16_t miqoFemaleScale;
  uint16_t roeMaleScale;
  uint16_t roeFemaleScale;
  uint16_t auRaMaleScale;
  uint16_t auRaFemaleScale;
  uint16_t hrothgarMaleScale;
  uint16_t hrothgarFemaleScale;
  uint16_t vieraMaleScale;
  uint16_t vieraFemaleScale;
  uint8_t hyurMaleCameraHeight;
  uint8_t hyurFemaleCameraHeight;
  uint8_t elezenMaleCameraHeight;
  uint8_t elezenFemaleCameraHeight;
  uint8_t lalaMaleCameraHeight;
  uint8_t lalaFemaleCameraHeight;
  uint8_t miqoMaleCameraHeight;
  uint8_t miqoFemaleCameraHeight;
  uint8_t roeMaleCameraHeight;
  uint8_t roeFemaleCameraHeight;
  uint8_t auRaMaleCameraHeight;
  uint8_t auRaFemaleCameraHeight;
  uint8_t hrothgarMaleCameraHeight;
  uint8_t hrothgarRoeFemaleCameraHeight;
  uint8_t vieraMaleCameraHeight;
  uint8_t vieraFemaleCameraHeight;

  MountCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MountFlyingCondition
{
  uint32_t quest;

  MountFlyingCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MountSpeed
{
  uint32_t quest;

  MountSpeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MountTransient
{
  std::string description;
  std::string descriptionEnhanced;
  std::string tooltip;

  MountTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MoveTimeline
{
  uint16_t idle;
  uint16_t moveForward;
  uint16_t moveBack;
  uint16_t moveLeft;
  uint16_t moveRight;
  uint16_t moveUp;
  uint16_t moveDown;
  uint16_t moveTurnLeft;
  uint16_t moveTurnRight;
  uint16_t extra;

  MoveTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MoveVfx
{
  uint16_t vFXNormal;
  uint16_t vFXWalking;

  MoveVfx( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MovieStaffList
{
  uint32_t image;
  float startTime;
  float endTime;

  MovieStaffList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MovieSubtitle
{
  float startTime;
  float endTime;

  MovieSubtitle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MovieSubtitle500
{
  float startTime;
  float endTime;

  MovieSubtitle500( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MovieSubtitleVoyage
{
  float startTime;
  float endTime;

  MovieSubtitleVoyage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MYCTemporaryItem
{
  uint8_t category;
  uint8_t type;
  uint32_t action;
  uint8_t max;
  uint8_t weight;
  uint8_t order;

  MYCTemporaryItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MYCTemporaryItemUICategory
{
  std::string name;

  MYCTemporaryItemUICategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct MYCWarResultNotebook
{
  uint8_t number;
  uint8_t unknown540;
  uint8_t unknown541;
  int32_t quest;
  int32_t icon;
  int32_t image;
  uint8_t rarity;
  std::string nameJP;
  std::string name;
  std::string description;

  MYCWarResultNotebook( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct NotebookDivision
{
  std::string name;
  uint8_t notebookDivisionCategory;
  uint8_t craftOpeningLevel;
  uint8_t gatheringOpeningLevel;
  uint32_t questUnlock;
  bool cRPCraft;
  bool bSMCraft;
  bool aRMCraft;
  bool gSMCraft;
  bool lTWCraft;
  bool wVRCraft;
  bool aLCCraft;
  bool cULCraft;

  NotebookDivision( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct NotebookDivisionCategory
{
  std::string name;
  uint8_t index;

  NotebookDivisionCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct NotoriousMonster
{
  int32_t bNpcBase;
  uint8_t rank;
  uint32_t bNpcName;

  NotoriousMonster( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct NpcEquip
{
  uint64_t modelMainHand;
  uint8_t dyeMainHand;
  uint64_t modelOffHand;
  uint8_t dyeOffHand;
  uint32_t modelHead;
  uint8_t dyeHead;
  bool visor;
  uint32_t modelBody;
  uint8_t dyeBody;
  uint32_t modelHands;
  uint8_t dyeHands;
  uint32_t modelLegs;
  uint8_t dyeLegs;
  uint32_t modelFeet;
  uint8_t dyeFeet;
  uint32_t modelEars;
  uint8_t dyeEars;
  uint32_t modelNeck;
  uint8_t dyeNeck;
  uint32_t modelWrists;
  uint8_t dyeWrists;
  uint32_t modelLeftRing;
  uint8_t dyeLeftRing;
  uint32_t modelRightRing;
  uint8_t dyeRightRing;

  NpcEquip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct NpcYell
{
  uint8_t outputType;
  float balloonTime;
  bool isBalloonSlow;
  bool battleTalkTime;
  uint8_t unknown54;
  std::string text;

  NpcYell( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Omen
{
  std::string path;
  std::string pathAlly;
  uint8_t type;
  bool restrictYScale;
  bool largeScale;

  Omen( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct OnlineStatus
{
  bool list;
  uint8_t priority;
  std::string name;
  uint32_t icon;

  OnlineStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct OpenContent
{
  std::vector< uint16_t > content;
  std::vector< uint32_t > candidateName;

  OpenContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct OpenContentCandidateName
{
  std::string name;

  OpenContentCandidateName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Opening
{
  std::string name;
  uint32_t quest;

  Opening( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Orchestrion
{
  std::string name;
  std::string description;

  Orchestrion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct OrchestrionCategory
{
  std::string name;
  uint8_t hideOrder;
  uint32_t icon;
  uint8_t order;

  OrchestrionCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct OrchestrionPath
{
  std::string file;

  OrchestrionPath( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct OrchestrionUiparam
{
  uint8_t orchestrionCategory;
  uint16_t order;

  OrchestrionUiparam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Ornament
{
  uint16_t model;
  int16_t order;
  uint16_t icon;
  uint16_t transient;
  std::string singular;
  int8_t adjective;
  std::string plural;
  int8_t possessivePronoun;
  int8_t startsWithVowel;
  int8_t pronoun;
  int8_t article;

  Ornament( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ParamGrow
{
  int32_t expToNext;
  uint8_t additionalActions;
  uint8_t applyAction;
  uint16_t scaledQuestXP;
  int32_t mpModifier;
  int32_t baseSpeed;
  int32_t levelModifier;
  uint8_t questExpModifier;
  uint16_t hpModifier;
  int32_t huntingLogExpReward;
  int32_t monsterNoteSeals;
  uint16_t itemLevelSync;
  uint16_t properDungeon;
  uint16_t properGuildOrder;
  uint16_t craftingLevel;

  ParamGrow( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PartyContent
{
  uint8_t key;
  uint16_t timeLimit;
  bool name;
  uint32_t textDataStart;
  uint32_t textDataEnd;
  std::vector< uint32_t > lGBEventObject0;
  std::vector< uint32_t > lGBEventRange;
  std::vector< uint32_t > lGBEventObject1;
  uint16_t contentFinderCondition;
  uint32_t image;

  PartyContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PartyContentCutscene
{
  uint32_t cutscene;

  PartyContentCutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PartyContentTextData
{
  std::string data;

  PartyContentTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PatchMark
{
  int8_t category;
  uint8_t subCategoryType;
  uint16_t subCategory;
  uint32_t markID;
  uint8_t version;

  PatchMark( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Perform
{
  std::string name;
  uint64_t modelKey;
  uint16_t animationStart;
  uint16_t animationEnd;
  uint16_t animationIdle;
  uint16_t animationPlay01;
  uint16_t animationPlay02;
  int32_t stopAnimation;
  std::string instrument;
  uint8_t transient;

  Perform( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PerformTransient
{
  std::string text;

  PerformTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Pet
{
  std::string name;

  Pet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PetAction
{
  std::string name;
  std::string description;
  int32_t icon;
  uint16_t action;
  uint8_t pet;
  bool masterOrder;
  bool disableOrder;

  PetAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PhysicsGroup
{
  std::vector< float > simulationTime;
  std::vector< float > pS3SimulationTime;
  bool resetByLookAt;
  float rootFollowingGame;
  float rootFollowingCutScene;
  std::vector< int8_t > configSwitch;
  bool forceAttractByPhysicsOff;

  PhysicsGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PhysicsWind
{
  float threshold;
  float amplitude;
  float amplitudeFrequency;
  float powerMin;
  float powerMax;
  float powerFrequency;

  PhysicsWind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Picture
{
  int32_t item;
  int32_t image;

  Picture( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PlaceName
{
  std::string name;
  std::string nameNoArticle;

  PlaceName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PlantPotFlowerSeed
{
  std::vector< uint32_t > seedIcon;

  PlantPotFlowerSeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PreHandler
{
  uint32_t image;
  uint32_t target;
  uint32_t unlockQuest;
  uint32_t acceptMessage;
  uint32_t denyMessage;

  PreHandler( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PresetCamera
{
  uint16_t eID;
  float posX;
  float posY;
  float posZ;
  float elezen;
  float lalafell;
  float miqote;
  float roe;
  float hrothgar;
  float viera;
  float hyur_F;
  float elezen_F;
  float lalafell_F;
  float miqote_F;
  float roe_F;
  float hrothgar_F;
  float viera_F;

  PresetCamera( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PresetCameraAdjust
{
  float hyur_M;
  float hyur_F;
  float elezen_M;
  float elezen_F;
  float lalafell_M;
  float lalafell_F;
  float miqote_M;
  float miqote_F;
  float roe_M;
  float roe_F;
  float hrothgar_M;
  float hrothgar_F;
  float viera_M;
  float viera_F;

  PresetCameraAdjust( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PublicContent
{
  uint8_t type;
  uint16_t timeLimit;
  uint32_t mapIcon;
  std::string name;
  uint32_t textDataStart;
  uint32_t textDataEnd;
  uint16_t contentFinderCondition;
  uint16_t additionalData;
  int32_t unknown540;
  uint16_t unknown541;
  uint16_t unknown542;

  PublicContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PublicContentCutscene
{
  uint32_t cutscene;
  uint32_t cutscene2;

  PublicContentCutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PublicContentTextData
{
  std::string textData;

  PublicContentTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Purify
{
  uint8_t _class;
  uint8_t level;

  Purify( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PvPAction
{
  uint16_t action;
  std::vector< bool > grandCompany;

  PvPAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PvPActionSort
{
  uint8_t name;
  uint16_t action;

  PvPActionSort( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PvPRank
{
  uint32_t expRequired;

  PvPRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PvPSelectTrait
{
  std::string effect;
  uint32_t icon;
  int16_t value;

  PvPSelectTrait( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct PvPTrait
{
  uint16_t trait1;
  uint16_t trait2;
  uint16_t trait3;

  PvPTrait( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Quest
{
  std::string name;
  std::string id;
  uint8_t expansion;
  uint8_t classJobCategory0;
  uint16_t classJobLevel0;
  uint8_t questLevelOffset;
  uint8_t classJobCategory1;
  uint16_t classJobLevel1;
  uint8_t previousQuestJoin;
  uint32_t previousQuest0;
  uint32_t previousQuest1;
  uint32_t previousQuest2;
  uint8_t questLockJoin;
  std::vector< uint32_t > questLock;
  uint16_t header;
  uint8_t classJobUnlock;
  uint8_t grandCompany;
  uint8_t grandCompanyRank;
  uint8_t instanceContentJoin;
  std::vector< uint32_t > instanceContent;
  uint8_t festival;
  uint8_t festivalBegin;
  uint8_t festivalEnd;
  uint16_t bellStart;
  uint16_t bellEnd;
  uint8_t beastTribe;
  uint8_t beastReputationRank;
  uint16_t beastReputationValue;
  int32_t mountRequired;
  bool isHouseRequired;
  uint8_t deliveryQuest;
  uint32_t issuerStart;
  uint32_t issuerLocation;
  uint16_t clientBehavior;
  uint32_t targetEnd;
  bool isRepeatable;
  uint8_t repeatIntervalType;
  uint8_t questRepeatFlag;
  bool canCancel;
  uint8_t type;
  uint16_t questClassJobSupply;
  std::vector< std::string > scriptInstruction;
  std::vector< uint32_t > scriptArg;
  std::vector< uint8_t > actorSpawnSeq;
  std::vector< uint8_t > actorDespawnSeq;
  std::vector< uint32_t > listener;
  std::vector< uint8_t > questUInt8A;
  std::vector< uint8_t > questUInt8B;
  std::vector< uint8_t > conditionType;
  std::vector< uint32_t > conditionValue;
  std::vector< uint8_t > conditionOperator;
  std::vector< uint16_t > behavior;
  std::vector< bool > visibleBool;
  std::vector< bool > conditionBool;
  std::vector< bool > itemBool;
  std::vector< bool > announceBool;
  std::vector< bool > behaviorBool;
  std::vector< bool > acceptBool;
  std::vector< bool > qualifiedBool;
  std::vector< bool > canTargetBool;
  std::vector< uint8_t > toDoCompleteSeq;
  std::vector< uint8_t > toDoQty;
  std::vector< uint32_t > toDoMainLocation;
  std::vector< uint8_t > countableNum;
  uint8_t levelMax;
  uint8_t classJobRequired;
  uint16_t expFactor;
  uint32_t gilReward;
  uint16_t gCSeals;
  std::vector< uint8_t > itemCatalyst;
  std::vector< uint8_t > itemCountCatalyst;
  uint8_t itemRewardType;
  std::vector< uint32_t > itemReward0;
  std::vector< uint8_t > itemCountReward0;
  std::vector< uint8_t > stainReward0;
  std::vector< uint32_t > itemReward1;
  std::vector< uint8_t > itemCountReward1;
  std::vector< bool > isHQReward1;
  std::vector< uint8_t > stainReward1;
  uint8_t emoteReward;
  uint16_t actionReward;
  std::vector< uint8_t > generalActionReward;
  uint16_t systemReward0;
  uint8_t otherReward;
  uint16_t systemReward1;
  uint16_t gCTypeReward;
  uint32_t instanceContentUnlock;
  uint8_t tomestoneReward;
  uint8_t tomestoneCountReward;
  uint8_t reputationReward;
  uint16_t placeName;
  uint8_t journalGenre;
  uint32_t icon;
  uint32_t iconSpecial;
  bool introduction;
  bool hideOfferIcon;
  uint8_t eventIconType;
  uint16_t sortKey;
  bool unknown54;

  Quest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestBattle
{
  int32_t quest;
  uint8_t questBattleScene;
  uint16_t timeLimit;
  uint16_t levelSync;
  std::vector< std::string > scriptInstruction;
  std::vector< uint32_t > scriptValue;

  QuestBattle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestChapter
{
  uint32_t quest;
  uint16_t redo;

  QuestChapter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestClassJobReward
{
  uint8_t classJobCategory;
  std::vector< uint32_t > rewardItem;
  std::vector< uint8_t > rewardAmount;
  std::vector< uint32_t > requiredItem;
  std::vector< uint8_t > requiredAmount;

  QuestClassJobReward( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestClassJobSupply
{
  uint8_t classJobCategory;
  uint32_t eNpcResident;
  uint32_t item;

  QuestClassJobSupply( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestDerivedClass
{
  uint8_t classJob;

  QuestDerivedClass( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRedo
{
  uint32_t finalQuest;
  uint16_t chapter;
  std::vector< uint32_t > quest;

  QuestRedo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRedoChapterUI
{
  uint32_t quest;
  uint8_t category;
  uint32_t questRedoUISmall;
  uint32_t questRedoUILarge;
  uint32_t questRedoUIWide;
  std::string chapterName;
  std::string chapterPart;
  std::string transient;

  QuestRedoChapterUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRedoChapterUICategory
{
  std::string expac;

  QuestRedoChapterUICategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRedoChapterUITab
{
  uint32_t icon1;
  uint32_t icon2;
  std::string text;

  QuestRedoChapterUITab( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRedoIncompChapter
{
  uint16_t chapter;

  QuestRedoIncompChapter( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRepeatFlag
{
  uint32_t quest;

  QuestRepeatFlag( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuestRewardOther
{
  uint32_t icon;
  std::string name;

  QuestRewardOther( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuickChat
{
  std::string nameAction;
  int32_t icon;
  int32_t addon;
  int8_t quickChatTransient;

  QuickChat( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct QuickChatTransient
{
  std::string textOutput;

  QuickChatTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Race
{
  std::string masculine;
  std::string feminine;
  int32_t rSEMBody;
  int32_t rSEMHands;
  int32_t rSEMLegs;
  int32_t rSEMFeet;
  int32_t rSEFBody;
  int32_t rSEFHands;
  int32_t rSEFLegs;
  int32_t rSEFFeet;
  uint8_t unknown54;
  uint8_t exPac;

  Race( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboItem
{
  int32_t item;
  uint8_t category;
  std::vector< uint8_t > param;

  RacingChocoboItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboName
{
  std::string name;

  RacingChocoboName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboNameCategory
{
  uint8_t sortKey;
  std::string name;

  RacingChocoboNameCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboNameInfo
{
  uint8_t racingChocoboNameCategory;

  RacingChocoboNameInfo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboParam
{
  std::string name;

  RacingChocoboParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RecastNavimesh
{
  float tileSize;
  float cellSize;
  float cellHeight;
  float agentHeight;
  float agentRadius;
  float agentMaxClimb;
  float agentMaxSlope;
  float regionMinSize;
  float regionMergedSize;
  float maxEdgeLength;
  float maxEdgeError;
  float vertsPerPoly;
  float detailMeshSampleDistance;
  float detailMeshMaxSampleError;

  RecastNavimesh( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Recipe
{
  int32_t number;
  int32_t craftType;
  uint16_t recipeLevelTable;
  int32_t itemResult;
  uint8_t amountResult;
  bool isSecondary;
  uint8_t materialQualityFactor;
  uint16_t difficultyFactor;
  uint16_t qualityFactor;
  uint16_t durabilityFactor;
  uint16_t requiredCraftsmanship;
  uint16_t requiredControl;
  uint16_t quickSynthCraftsmanship;
  uint16_t quickSynthControl;
  uint16_t secretRecipeBook;
  bool canQuickSynth;
  bool canHq;
  bool expRewarded;
  int32_t statusRequired;
  int32_t itemRequired;
  bool isSpecializationRequired;
  bool isExpert;
  uint16_t patchNumber;

  Recipe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RecipeLevelTable
{
  uint8_t classJobLevel;
  uint8_t stars;
  uint16_t suggestedCraftsmanship;
  uint16_t suggestedControl;
  uint16_t difficulty;
  uint32_t quality;
  uint16_t durability;
  uint16_t conditionsFlag;

  RecipeLevelTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RecipeLookup
{
  uint16_t cRP;
  uint16_t bSM;
  uint16_t aRM;
  uint16_t gSM;
  uint16_t lTW;
  uint16_t wVR;
  uint16_t aLC;
  uint16_t cUL;

  RecipeLookup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RecipeNotebookList
{
  std::vector< int32_t > recipe;

  RecipeNotebookList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RecommendContents
{
  int32_t level;
  uint8_t classJob;
  uint8_t minLevel;
  uint8_t maxLevel;

  RecommendContents( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Relic
{
  uint32_t itemAtma;
  uint32_t itemAnimus;
  int32_t icon;
  uint16_t materia0;
  uint8_t noteMain0;
  uint8_t noteSub0;
  uint8_t noteSelection10;
  uint16_t materia1;
  uint8_t noteMain1;
  uint8_t noteSub1;
  uint8_t noteSelection1;
  uint16_t materia2;
  uint8_t noteMain2;
  uint8_t noteSub2;
  uint16_t materia3;
  uint8_t noteSelection3;

  Relic( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Relic3
{
  uint32_t itemAnimus;
  uint32_t itemScroll;
  uint8_t materiaLimit;
  uint32_t itemNovus;
  int32_t icon;

  Relic3( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RelicItem
{
  uint32_t gladiatorItem;
  uint32_t pugilistItem;
  uint32_t marauderItem;
  uint32_t lancerItem;
  uint32_t archerItem;
  uint32_t conjurerItem;
  uint32_t thaumaturgeItem;
  uint32_t arcanistSMNItem;
  uint32_t arcanistSCHItem;
  uint32_t shieldItem;
  uint32_t rogueItem;

  RelicItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RelicNote
{
  uint32_t eventItem;
  std::vector< uint16_t > monsterNoteTargetNM;
  std::vector< uint16_t > leve;

  RelicNote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RelicNoteCategory
{
  std::string text;

  RelicNoteCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Resident
{
  uint64_t model;
  int32_t npcYell;
  uint16_t addedIn53;
  uint8_t residentMotionType;

  Resident( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ResistanceWeaponAdjust
{
  uint16_t maxTotalStats;
  uint16_t maxEachStat;
  std::vector< uint8_t > baseParam;
  uint32_t image;

  ResistanceWeaponAdjust( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RetainerTask
{
  bool isRandom;
  uint8_t classJobCategory;
  uint8_t retainerLevel;
  uint16_t retainerTaskParameter;
  uint16_t ventureCost;
  uint16_t maxTimemin;
  int32_t experience;
  uint16_t requiredItemLevel;
  uint8_t conditionParam0;
  uint8_t conditionParam1;
  uint16_t requiredGathering;
  uint16_t task;

  RetainerTask( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskLvRange
{
  uint8_t min;
  uint8_t max;

  RetainerTaskLvRange( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskNormal
{
  int32_t item;
  uint8_t quantity0;
  uint8_t quantity1;
  uint8_t quantity2;
  int16_t gatheringLog;
  int16_t fishingLog;

  RetainerTaskNormal( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskParameter
{
  std::vector< int16_t > itemLevelDoW;
  std::vector< int16_t > gatheringDoL;
  std::vector< int16_t > gatheringFSH;

  RetainerTaskParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskRandom
{
  std::string name;
  int16_t requirement;

  RetainerTaskRandom( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RideShooting
{
  uint16_t gFateRideShooting;
  uint16_t startText;
  std::vector< uint32_t > popRange;
  std::vector< uint32_t > eNpc;
  std::vector< uint8_t > eNpcScale;

  RideShooting( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RideShootingTextData
{
  std::string string;

  RideShootingTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct RPParameter
{
  uint16_t bNpcName;
  uint8_t classJob;

  RPParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SatisfactionArbitration
{
  uint32_t quest;

  SatisfactionArbitration( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SatisfactionNpc
{
  int32_t npc;
  int32_t questRequired;
  uint8_t levelUnlock;
  uint8_t deliveriesPerWeek;
  std::vector< int32_t > supplyIndex;
  std::vector< uint16_t > satisfactionRequired;
  int32_t icon;
  uint8_t addedIn530;
  uint8_t addedIn531;

  SatisfactionNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SatisfactionSupply
{
  uint8_t slot;
  uint8_t probability;
  int32_t item;
  uint16_t collectabilityLow;
  uint16_t collectabilityMid;
  uint16_t collectabilityHigh;
  uint16_t reward;

  SatisfactionSupply( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SatisfactionSupplyReward
{
  uint16_t satisfactionLow;
  uint16_t satisfactionMid;
  uint16_t satisfactionHigh;
  uint16_t gilLow;
  uint16_t gilMid;
  uint16_t gilHigh;

  SatisfactionSupplyReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ScenarioTree
{
  uint8_t type;
  uint16_t image;
  uint32_t unknown540;
  std::string unknown541;
  int32_t unknown542;

  ScenarioTree( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ScenarioTreeTips
{
  uint32_t tips1;
  uint32_t tips2;

  ScenarioTreeTips( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ScenarioTreeTipsClassQuest
{
  uint32_t quest;
  uint16_t requiredLevel;
  uint8_t requiredExpansion;
  uint32_t requiredQuest;

  ScenarioTreeTipsClassQuest( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ScenarioType
{
  std::string type;

  ScenarioType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ScreenImage
{
  uint32_t image;
  int16_t jingle;
  int8_t type;
  bool lang;

  ScreenImage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SecretRecipeBook
{
  int32_t item;
  std::string name;

  SecretRecipeBook( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2Mission
{
  uint32_t item1;
  uint32_t item2;
  uint16_t placeName;
  uint16_t objective1;
  uint32_t popRange0;
  uint8_t requiredAmount1;
  uint16_t objective2;
  uint32_t popRange1;
  uint8_t requiredAmount2;
  uint16_t objective3;
  uint32_t popRange2;
  uint32_t image;

  SkyIsland2Mission( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2MissionDetail
{
  uint8_t type;
  uint8_t range;
  uint32_t eObj;
  std::string objective;

  SkyIsland2MissionDetail( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2MissionType
{
  bool type;

  SkyIsland2MissionType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2RangeType
{
  uint8_t type;

  SkyIsland2RangeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SnipeTalk
{
  uint16_t name;
  std::string text;

  SnipeTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SnipeTalkName
{
  std::string name;

  SnipeTalkName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SpearfishingItem
{
  std::string description;
  int32_t item;
  uint16_t gatheringItemLevel;
  uint8_t fishingRecordType;
  uint16_t territoryType;
  bool isVisible;

  SpearfishingItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SpearfishingNotebook
{
  uint8_t gatheringLevel;
  int32_t territoryType;
  int16_t x;
  int16_t y;
  uint16_t radius;
  uint16_t placeName;
  uint16_t gatheringPointBase;

  SpearfishingNotebook( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SpearfishingRecordPage
{
  int32_t placeName;
  int32_t image;

  SpearfishingRecordPage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SpecialShop
{
  std::string name;
  std::vector< int32_t > questItem;
  std::vector< int32_t > unknown;
  std::vector< int32_t > achievementUnlock;
  std::vector< uint16_t > patchNumber;
  uint8_t useCurrencyType;
  uint32_t questUnlock;
  int32_t completeText;
  int32_t notCompleteText;

  SpecialShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SpecialShopItemCategory
{
  std::string name;

  SpecialShopItemCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Stain
{
  uint32_t color;
  uint8_t shade;
  std::string name;

  Stain( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct StainTransient
{
  uint32_t item1;
  uint32_t item2;

  StainTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Status
{
  std::string name;
  std::string description;
  uint16_t icon;
  uint8_t maxStacks;
  uint8_t category;
  uint8_t hitEffect;
  uint16_t vFX;
  bool lockMovement;
  bool lockActions;
  bool lockControl;
  bool transfiguration;
  bool canDispel;
  bool inflictedByActor;
  bool isPermanent;
  uint8_t partyListPriority;
  uint16_t log;
  bool isFcBuff;
  bool invisibility;

  Status( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct StatusHitEffect
{
  uint16_t location;

  StatusHitEffect( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct StatusLoopVFX
{
  uint16_t vFX;
  uint16_t vFX2;
  uint16_t vFX3;

  StatusLoopVFX( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Story
{
  std::string script;
  std::vector< std::string > instruction;
  std::vector< uint32_t > argument;
  std::vector< uint16_t > sequence;
  std::vector< uint8_t > completedQuestOperator;
  std::vector< uint32_t > completedQuest0;
  std::vector< uint32_t > completedQuest1;
  std::vector< uint32_t > completedQuest2;
  std::vector< uint8_t > acceptedQuestOperator;
  std::vector< uint32_t > acceptedQuest0;
  std::vector< uint8_t > acceptedQuestSequence0;
  std::vector< uint32_t > acceptedQuest1;
  std::vector< uint8_t > acceptedQuestSequence1;
  std::vector< uint32_t > acceptedQuest2;
  std::vector< uint8_t > acceptedQuestSequence2;
  std::vector< uint32_t > layerSet0;
  std::vector< uint32_t > layerSet1;
  std::vector< uint16_t > sequenceBegin;
  std::vector< uint16_t > sequenceEnd;
  std::vector< uint32_t > listener;
  uint16_t layerSetTerritoryType0;
  uint16_t layerSetTerritoryType1;

  Story( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SubmarineExploration
{
  std::string destination;
  std::string location;
  uint8_t map;
  uint8_t stars;
  uint8_t rankReq;
  uint8_t ceruleumTankReq;
  uint16_t durationmin;
  uint8_t distanceForSurvey;
  uint32_t expReward;

  SubmarineExploration( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SubmarineMap
{
  std::string name;
  uint32_t image;

  SubmarineMap( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SubmarinePart
{
  uint8_t slot;
  uint8_t rank;
  uint8_t components;
  int16_t surveillance;
  int16_t retrieval;
  int16_t speed;
  int16_t range;
  int16_t favor;
  uint16_t _class;
  uint8_t repairMaterials;

  SubmarinePart( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SubmarineRank
{
  uint16_t capacity;
  uint32_t expToNext;
  uint8_t surveillanceBonus;
  uint8_t retrievalBonus;
  uint8_t speedBonus;
  uint8_t rangeBonus;
  uint8_t favorBonus;

  SubmarineRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SwitchTalk
{

  SwitchTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct SwitchTalkVariation
{
  uint32_t quest0;
  uint32_t quest1;
  uint32_t defaultTalk;

  SwitchTalkVariation( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TerritoryType
{
  std::string name;
  std::string bg;
  uint8_t battalionMode;
  uint16_t placeNameRegion;
  uint16_t placeNameZone;
  uint16_t placeName;
  uint16_t map;
  uint8_t loadingImage;
  uint8_t exclusiveType;
  uint8_t territoryIntendedUse;
  uint8_t weatherRate;
  bool pCSearch;
  bool stealth;
  bool mount;
  uint16_t bGM;
  int32_t placeNameRegionIcon;
  int32_t placeNameIcon;
  uint32_t arrayEventHandler;
  uint16_t questBattle;
  int32_t aetheryte;
  int32_t fixedTime;
  uint16_t resident;
  int8_t achievementIndex;
  bool isPvpZone;
  uint8_t exVersion;
  uint8_t addedIn53;
  uint8_t mountSpeed;
  bool unknown54;

  TerritoryType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TerritoryTypeTransient
{
  int16_t offsetZ;

  TerritoryTypeTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TextCommand
{
  std::string command;
  std::string shortCommand;
  std::string description;
  std::string alias;
  std::string shortAlias;

  TextCommand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Title
{
  std::string masculine;
  std::string feminine;
  bool isPrefix;
  uint16_t order;

  Title( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Tomestones
{
  uint16_t weeklyLimit;

  Tomestones( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TomestonesItem
{
  int32_t item;
  int32_t tomestones;

  TomestonesItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TopicSelect
{
  std::string name;

  TopicSelect( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Town
{
  std::string name;
  int32_t icon;

  Town( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Trait
{
  std::string name;
  int32_t icon;
  uint8_t classJob;
  uint8_t level;
  uint32_t quest;
  int16_t value;
  uint8_t classJobCategory;

  Trait( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TraitRecast
{
  uint16_t trait;
  uint16_t action;
  uint16_t timeds;

  TraitRecast( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TraitTransient
{
  std::string description;

  TraitTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Transformation
{
  int16_t model;
  uint16_t bNpcName;
  int32_t bNpcCustomize;
  int32_t npcEquip;
  bool exHotbarEnableConfig;
  uint16_t action0;
  uint16_t action1;
  uint16_t action2;
  uint16_t action3;
  uint16_t action4;
  uint16_t action5;
  uint16_t rPParameter;
  uint16_t removeAction;
  float speed;
  float scale;
  bool isPvP;
  bool isEvent;
  bool playerCamera;
  uint16_t startVFX;
  uint16_t endVFX;
  uint32_t action6;
  uint16_t action7;
  bool unknown54;

  Transformation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Treasure
{
  uint32_t item;

  Treasure( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TreasureHuntRank
{
  uint32_t icon;
  int32_t itemName;
  int32_t keyItemName;
  int32_t instanceMap;
  uint8_t maxPartySize;
  uint8_t treasureHuntTexture;

  TreasureHuntRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TreasureModel
{
  std::string path;

  TreasureModel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TreasureSpot
{
  int32_t location;
  float mapOffsetX;
  float mapOffsetY;

  TreasureSpot( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Tribe
{
  std::string masculine;
  std::string feminine;
  int8_t hp;
  int8_t mp;
  int8_t sTR;
  int8_t vIT;
  int8_t dEX;
  int8_t iNT;
  int8_t mND;
  int8_t pIE;

  Tribe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriad
{
  std::vector< uint16_t > tripleTriadCardFixed;
  std::vector< uint16_t > tripleTriadCardVariable;
  std::vector< uint8_t > tripleTriadRule;
  bool usesRegionalRules;
  uint16_t fee;
  uint8_t previousQuestJoin;
  std::vector< uint32_t > previousQuest;
  uint16_t startTime;
  uint16_t endTime;
  uint32_t defaultTalkChallenge;
  uint32_t defaultTalkUnavailable;
  uint32_t defaultTalkNPCWin;
  uint32_t defaultTalkDraw;
  uint32_t defaultTalkPCWin;
  std::vector< uint32_t > itemPossibleReward;

  TripleTriad( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCard
{
  std::string name;
  int8_t startsWithVowel;
  std::string description;

  TripleTriadCard( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCardRarity
{
  uint8_t stars;

  TripleTriadCardRarity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCardResident
{
  uint8_t top;
  uint8_t bottom;
  uint8_t left;
  uint8_t right;
  uint8_t tripleTriadCardRarity;
  uint8_t tripleTriadCardType;
  uint16_t saleValue;
  uint8_t sortKey;
  uint16_t order;
  uint8_t uIPriority;
  bool unknown54;
  uint8_t acquisitionType;
  uint32_t acquisition;
  uint32_t location;
  uint32_t quest;

  TripleTriadCardResident( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCardType
{
  std::string name;

  TripleTriadCardType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCompetition
{
  std::string name;

  TripleTriadCompetition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TripleTriadRule
{
  std::string name;
  std::string description;
  bool unknown54;

  TripleTriadRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Tutorial
{
  uint32_t exp;
  uint32_t gil;
  uint32_t rewardTank;
  uint32_t rewardMelee;
  uint32_t rewardRanged;
  uint32_t objective;

  Tutorial( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TutorialDPS
{
  uint8_t objective;

  TutorialDPS( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TutorialHealer
{
  uint8_t objective;

  TutorialHealer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct TutorialTank
{
  uint8_t objective;

  TutorialTank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct UIColor
{
  uint32_t uIForeground;
  uint32_t uIGlow;

  UIColor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct VaseFlower
{
  uint32_t item;

  VaseFlower( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct VFX
{
  std::string location;

  VFX( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Warp
{
  uint32_t popRange;
  uint16_t territoryType;
  uint32_t conditionSuccessEvent;
  uint32_t conditionFailEvent;
  uint32_t confirmEvent;
  uint16_t warpCondition;
  uint16_t warpLogic;
  uint16_t startCutscene;
  uint16_t endCutscene;
  bool canSkipCutscene;
  std::string name;
  std::string question;

  Warp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WarpCondition
{
  uint16_t gil;
  uint8_t completeParam;
  uint32_t requiredQuest1;
  uint32_t requiredQuest2;
  uint32_t dRequiredQuest3;
  uint32_t requiredQuest4;
  uint16_t questReward;
  uint16_t classLevel;

  WarpCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WarpLogic
{
  std::string warpName;
  bool canSkipCutscene;
  std::vector< std::string > function;
  std::string question;
  std::string responseYes;
  std::string responseNo;

  WarpLogic( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeaponTimeline
{
  std::string file;
  int16_t nextWeaponTimeline;

  WeaponTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct Weather
{
  int32_t icon;
  std::string name;
  std::string description;

  Weather( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeatherGroup
{
  int32_t weatherRate;

  WeatherGroup( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeatherRate
{

  WeatherRate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeatherReportReplace
{
  uint16_t placeNameSub;
  uint16_t placeNameParent;

  WeatherReportReplace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WebGuidance
{
  int32_t image;
  uint8_t url;
  std::string name;
  std::string unknown54;
  std::string description;

  WebGuidance( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WebURL
{
  std::string uRL;

  WebURL( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeddingBGM
{
  uint16_t song;
  std::string songName;

  WeddingBGM( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeeklyBingoOrderData
{
  uint32_t type;
  uint32_t data;
  uint8_t text;
  uint32_t icon;

  WeeklyBingoOrderData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeeklyBingoRewardData
{
  uint32_t rewardItem2;
  bool rewardHQ2;
  uint16_t rewardQuantity2;

  WeeklyBingoRewardData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeeklyBingoText
{
  std::string description;

  WeeklyBingoText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WeeklyLotBonus
{
  std::vector< uint8_t > weeklyLotBonusThreshold;

  WeeklyLotBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct World
{
  std::string name;
  uint8_t userType;
  uint8_t dataCenter;
  bool isPublic;

  World( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct WorldDCGroupType
{
  std::string name;
  uint8_t region;

  WorldDCGroupType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct YardCatalogCategory
{
  std::string category;

  YardCatalogCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct YardCatalogItemList
{
  uint16_t category;
  int32_t item;
  uint16_t patch;

  YardCatalogItemList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct YKW
{
  uint32_t item;
  std::vector< uint16_t > location;

  YKW( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );
};

struct ZoneSharedGroup
{
  uint32_t quest1;
  uint32_t quest2;
  uint32_t quest3;
  uint32_t quest4;
  uint32_t quest5;
  uint32_t quest6;

  ZoneSharedGroup( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );
};



  class ExdDataGenerated
  {
  public:
    ExdDataGenerated();
    ~ExdDataGenerated();

    bool init( const std::string& path );

    xiv::exd::Exd setupDatAccess( const std::string& name, xiv::exd::Language lang );

    template< class T >
    T getField( std::vector< xiv::exd::Field >& fields, uint32_t index )
    {
       return std::get< T >( fields.at( index ) );
    }

    void loadIdList( xiv::exd::Exd& data, std::set< uint32_t >& outIdList );

    std::shared_ptr< xiv::dat::GameData > m_data;
    std::shared_ptr< xiv::exd::ExdData > m_exd_data;

    std::shared_ptr< xiv::dat::GameData > getGameData()
    {
      return m_data;
    }

    template< class T >
    std::shared_ptr< T > get( uint32_t id )
    {
      try
      {
        auto info = std::make_shared< T >( id, this );
        return info;
      }
      catch( ... )
      {
        return nullptr;
      }
      return nullptr;
    }

    template< class T >
    std::shared_ptr< T > get( uint32_t id, uint32_t slotId )
    {
      try
      {
        auto info = std::make_shared< T >( id, slotId, this );
        return info;
      }
      catch( ... )
      {
        return nullptr;
      }
      return nullptr;
    }

     xiv::exd::Exd m_AchievementDat;
     xiv::exd::Exd m_AchievementCategoryDat;
     xiv::exd::Exd m_AchievementHideConditionDat;
     xiv::exd::Exd m_AchievementKindDat;
     xiv::exd::Exd m_ActionDat;
     xiv::exd::Exd m_ActionCastTimelineDat;
     xiv::exd::Exd m_ActionCastVFXDat;
     xiv::exd::Exd m_ActionCategoryDat;
     xiv::exd::Exd m_ActionComboRouteDat;
     xiv::exd::Exd m_ActionIndirectionDat;
     xiv::exd::Exd m_ActionParamDat;
     xiv::exd::Exd m_ActionProcStatusDat;
     xiv::exd::Exd m_ActionTimelineDat;
     xiv::exd::Exd m_ActionTimelineMoveDat;
     xiv::exd::Exd m_ActionTimelineReplaceDat;
     xiv::exd::Exd m_ActionTransientDat;
     xiv::exd::Exd m_ActivityFeedButtonsDat;
     xiv::exd::Exd m_ActivityFeedCaptionsDat;
     xiv::exd::Exd m_ActivityFeedGroupCaptionsDat;
     xiv::exd::Exd m_ActivityFeedImagesDat;
     xiv::exd::Exd m_AddonDat;
     xiv::exd::Exd m_AdventureDat;
     xiv::exd::Exd m_AdventureExPhaseDat;
     xiv::exd::Exd m_AetherCurrentDat;
     xiv::exd::Exd m_AetherCurrentCompFlgSetDat;
     xiv::exd::Exd m_AetherialWheelDat;
     xiv::exd::Exd m_AetheryteDat;
     xiv::exd::Exd m_AetheryteSystemDefineDat;
     xiv::exd::Exd m_AirshipExplorationLevelDat;
     xiv::exd::Exd m_AirshipExplorationLogDat;
     xiv::exd::Exd m_AirshipExplorationParamTypeDat;
     xiv::exd::Exd m_AirshipExplorationPartDat;
     xiv::exd::Exd m_AirshipExplorationPointDat;
     xiv::exd::Exd m_AnimationLODDat;
     xiv::exd::Exd m_AnimaWeapon5Dat;
     xiv::exd::Exd m_AnimaWeapon5ParamDat;
     xiv::exd::Exd m_AnimaWeapon5PatternGroupDat;
     xiv::exd::Exd m_AnimaWeapon5SpiritTalkDat;
     xiv::exd::Exd m_AnimaWeapon5SpiritTalkParamDat;
     xiv::exd::Exd m_AnimaWeapon5TradeItemDat;
     xiv::exd::Exd m_AnimaWeaponFUITalkDat;
     xiv::exd::Exd m_AnimaWeaponFUITalkParamDat;
     xiv::exd::Exd m_AnimaWeaponIconDat;
     xiv::exd::Exd m_AnimaWeaponItemDat;
     xiv::exd::Exd m_AozActionDat;
     xiv::exd::Exd m_AozActionTransientDat;
     xiv::exd::Exd m_AOZArrangementDat;
     xiv::exd::Exd m_AOZBossDat;
     xiv::exd::Exd m_AOZContentDat;
     xiv::exd::Exd m_AOZContentBriefingBNpcDat;
     xiv::exd::Exd m_AquariumFishDat;
     xiv::exd::Exd m_AquariumWaterDat;
     xiv::exd::Exd m_ArrayEventHandlerDat;
     xiv::exd::Exd m_AttackTypeDat;
     xiv::exd::Exd m_BacklightColorDat;
     xiv::exd::Exd m_BallistaDat;
     xiv::exd::Exd m_BalloonDat;
     xiv::exd::Exd m_BaseParamDat;
     xiv::exd::Exd m_BattleLeveDat;
     xiv::exd::Exd m_BattleLeveRuleDat;
     xiv::exd::Exd m_BeastRankBonusDat;
     xiv::exd::Exd m_BeastReputationRankDat;
     xiv::exd::Exd m_BeastTribeDat;
     xiv::exd::Exd m_BehaviorDat;
     xiv::exd::Exd m_BehaviorPathDat;
     xiv::exd::Exd m_BenchmarkOverrideEquipmentDat;
     xiv::exd::Exd m_BGMDat;
     xiv::exd::Exd m_BGMFadeDat;
     xiv::exd::Exd m_BGMFadeTypeDat;
     xiv::exd::Exd m_BGMSceneDat;
     xiv::exd::Exd m_BGMSituationDat;
     xiv::exd::Exd m_BGMSwitchDat;
     xiv::exd::Exd m_BGMSystemDefineDat;
     xiv::exd::Exd m_BNpcAnnounceIconDat;
     xiv::exd::Exd m_BNpcBaseDat;
     xiv::exd::Exd m_BNpcCustomizeDat;
     xiv::exd::Exd m_BNpcNameDat;
     xiv::exd::Exd m_BNpcPartsDat;
     xiv::exd::Exd m_BNpcStateDat;
     xiv::exd::Exd m_BuddyDat;
     xiv::exd::Exd m_BuddyActionDat;
     xiv::exd::Exd m_BuddyEquipDat;
     xiv::exd::Exd m_BuddyItemDat;
     xiv::exd::Exd m_BuddyRankDat;
     xiv::exd::Exd m_BuddySkillDat;
     xiv::exd::Exd m_CabinetDat;
     xiv::exd::Exd m_CabinetCategoryDat;
     xiv::exd::Exd m_CalendarDat;
     xiv::exd::Exd m_CarryDat;
     xiv::exd::Exd m_ChannelingDat;
     xiv::exd::Exd m_CharaMakeClassEquipDat;
     xiv::exd::Exd m_CharaMakeCustomizeDat;
     xiv::exd::Exd m_CharaMakeNameDat;
     xiv::exd::Exd m_CharaMakeTypeDat;
     xiv::exd::Exd m_ChocoboRaceDat;
     xiv::exd::Exd m_ChocoboRaceAbilityDat;
     xiv::exd::Exd m_ChocoboRaceAbilityTypeDat;
     xiv::exd::Exd m_ChocoboRaceItemDat;
     xiv::exd::Exd m_ChocoboRaceRankDat;
     xiv::exd::Exd m_ChocoboRaceStatusDat;
     xiv::exd::Exd m_ChocoboRaceTerritoryDat;
     xiv::exd::Exd m_ChocoboRaceTutorialDat;
     xiv::exd::Exd m_ChocoboRaceWeatherDat;
     xiv::exd::Exd m_ChocoboTaxiDat;
     xiv::exd::Exd m_ChocoboTaxiStandDat;
     xiv::exd::Exd m_CircleActivityDat;
     xiv::exd::Exd m_ClassJobDat;
     xiv::exd::Exd m_ClassJobCategoryDat;
     xiv::exd::Exd m_CollectablesShopDat;
     xiv::exd::Exd m_CollectablesShopItemDat;
     xiv::exd::Exd m_CollectablesShopItemGroupDat;
     xiv::exd::Exd m_CollectablesShopRefineDat;
     xiv::exd::Exd m_CollectablesShopRewardItemDat;
     xiv::exd::Exd m_CollectablesShopRewardScripDat;
     xiv::exd::Exd m_CompanionDat;
     xiv::exd::Exd m_CompanionMoveDat;
     xiv::exd::Exd m_CompanionTransientDat;
     xiv::exd::Exd m_CompanyActionDat;
     xiv::exd::Exd m_CompanyCraftDraftDat;
     xiv::exd::Exd m_CompanyCraftDraftCategoryDat;
     xiv::exd::Exd m_CompanyCraftManufactoryStateDat;
     xiv::exd::Exd m_CompanyCraftPartDat;
     xiv::exd::Exd m_CompanyCraftProcessDat;
     xiv::exd::Exd m_CompanyCraftSequenceDat;
     xiv::exd::Exd m_CompanyCraftSupplyItemDat;
     xiv::exd::Exd m_CompanyCraftTypeDat;
     xiv::exd::Exd m_CompanyLeveDat;
     xiv::exd::Exd m_CompanyLeveRuleDat;
     xiv::exd::Exd m_CompleteJournalDat;
     xiv::exd::Exd m_CompleteJournalCategoryDat;
     xiv::exd::Exd m_ConditionDat;
     xiv::exd::Exd m_ConfigKeyDat;
     xiv::exd::Exd m_ContentCloseCycleDat;
     xiv::exd::Exd m_ContentExActionDat;
     xiv::exd::Exd m_ContentFinderConditionDat;
     xiv::exd::Exd m_ContentFinderConditionTransientDat;
     xiv::exd::Exd m_ContentGaugeDat;
     xiv::exd::Exd m_ContentGaugeColorDat;
     xiv::exd::Exd m_ContentMemberTypeDat;
     xiv::exd::Exd m_ContentNpcTalkDat;
     xiv::exd::Exd m_ContentRandomSelectDat;
     xiv::exd::Exd m_ContentRouletteDat;
     xiv::exd::Exd m_ContentRouletteOpenRuleDat;
     xiv::exd::Exd m_ContentRouletteRoleBonusDat;
     xiv::exd::Exd m_ContentsNoteDat;
     xiv::exd::Exd m_ContentsTutorialDat;
     xiv::exd::Exd m_ContentsTutorialPageDat;
     xiv::exd::Exd m_ContentTalkDat;
     xiv::exd::Exd m_ContentTalkParamDat;
     xiv::exd::Exd m_ContentTypeDat;
     xiv::exd::Exd m_CraftActionDat;
     xiv::exd::Exd m_CraftLeveDat;
     xiv::exd::Exd m_CraftLevelDifferenceDat;
     xiv::exd::Exd m_CraftTypeDat;
     xiv::exd::Exd m_CreditDat;
     xiv::exd::Exd m_CreditBackImageDat;
     xiv::exd::Exd m_CreditCastDat;
     xiv::exd::Exd m_CreditListDat;
     xiv::exd::Exd m_CreditListTextDat;
     xiv::exd::Exd m_CustomTalkDat;
     xiv::exd::Exd m_CustomTalkDynamicIconDat;
     xiv::exd::Exd m_CustomTalkNestHandlersDat;
     xiv::exd::Exd m_CutsceneDat;
     xiv::exd::Exd m_CutsceneMotionDat;
     xiv::exd::Exd m_CutsceneWorkIndexDat;
     xiv::exd::Exd m_CutScreenImageDat;
     xiv::exd::Exd m_CycleTimeDat;
     xiv::exd::Exd m_DailySupplyItemDat;
     xiv::exd::Exd m_DawnContentDat;
     xiv::exd::Exd m_DawnGrowMemberDat;
     xiv::exd::Exd m_DawnMemberUIParamDat;
     xiv::exd::Exd m_DawnQuestAnnounceDat;
     xiv::exd::Exd m_DawnQuestMemberDat;
     xiv::exd::Exd m_DeepDungeonDat;
     xiv::exd::Exd m_DeepDungeonBanDat;
     xiv::exd::Exd m_DeepDungeonDangerDat;
     xiv::exd::Exd m_DeepDungeonEquipmentDat;
     xiv::exd::Exd m_DeepDungeonFloorEffectUIDat;
     xiv::exd::Exd m_DeepDungeonItemDat;
     xiv::exd::Exd m_DeepDungeonLayerDat;
     xiv::exd::Exd m_DeepDungeonMagicStoneDat;
     xiv::exd::Exd m_DeepDungeonMap5XDat;
     xiv::exd::Exd m_DeepDungeonRoomDat;
     xiv::exd::Exd m_DeepDungeonStatusDat;
     xiv::exd::Exd m_DefaultTalkDat;
     xiv::exd::Exd m_DefaultTalkLipSyncTypeDat;
     xiv::exd::Exd m_DeliveryQuestDat;
     xiv::exd::Exd m_DescriptionDat;
     xiv::exd::Exd m_DescriptionPageDat;
     xiv::exd::Exd m_DescriptionSectionDat;
     xiv::exd::Exd m_DescriptionStringDat;
     xiv::exd::Exd m_DisposalShopDat;
     xiv::exd::Exd m_DisposalShopFilterTypeDat;
     xiv::exd::Exd m_DisposalShopItemDat;
     xiv::exd::Exd m_DpsChallengeDat;
     xiv::exd::Exd m_DpsChallengeOfficerDat;
     xiv::exd::Exd m_DpsChallengeTransientDat;
     xiv::exd::Exd m_DynamicEventDat;
     xiv::exd::Exd m_DynamicEventEnemyTypeDat;
     xiv::exd::Exd m_DynamicEventSingleBattleDat;
     xiv::exd::Exd m_DynamicEventTypeDat;
     xiv::exd::Exd m_EmjAddonDat;
     xiv::exd::Exd m_EmjDaniDat;
     xiv::exd::Exd m_EmoteDat;
     xiv::exd::Exd m_EmoteCategoryDat;
     xiv::exd::Exd m_EmoteModeDat;
     xiv::exd::Exd m_ENpcBaseDat;
     xiv::exd::Exd m_ENpcDressUpDat;
     xiv::exd::Exd m_ENpcDressUpDressDat;
     xiv::exd::Exd m_ENpcResidentDat;
     xiv::exd::Exd m_EObjDat;
     xiv::exd::Exd m_EObjNameDat;
     xiv::exd::Exd m_EquipRaceCategoryDat;
     xiv::exd::Exd m_EquipSlotCategoryDat;
     xiv::exd::Exd m_EurekaAetherItemDat;
     xiv::exd::Exd m_EurekaAethernetDat;
     xiv::exd::Exd m_EurekaGrowDataDat;
     xiv::exd::Exd m_EurekaLogosMixerProbabilityDat;
     xiv::exd::Exd m_EurekaMagiaActionDat;
     xiv::exd::Exd m_EurekaMagiciteItemDat;
     xiv::exd::Exd m_EurekaMagiciteItemTypeDat;
     xiv::exd::Exd m_EurekaSphereElementAdjustDat;
     xiv::exd::Exd m_EventActionDat;
     xiv::exd::Exd m_EventIconPriorityDat;
     xiv::exd::Exd m_EventIconTypeDat;
     xiv::exd::Exd m_EventItemDat;
     xiv::exd::Exd m_EventItemCastTimelineDat;
     xiv::exd::Exd m_EventItemHelpDat;
     xiv::exd::Exd m_EventItemTimelineDat;
     xiv::exd::Exd m_EventSystemDefineDat;
     xiv::exd::Exd m_ExportedSGDat;
     xiv::exd::Exd m_ExVersionDat;
     xiv::exd::Exd m_FateDat;
     xiv::exd::Exd m_FateEventDat;
     xiv::exd::Exd m_FateModeDat;
     xiv::exd::Exd m_FateProgressUIDat;
     xiv::exd::Exd m_FateTokenTypeDat;
     xiv::exd::Exd m_FCActivityDat;
     xiv::exd::Exd m_FCActivityCategoryDat;
     xiv::exd::Exd m_FCAuthorityDat;
     xiv::exd::Exd m_FCAuthorityCategoryDat;
     xiv::exd::Exd m_FCChestNameDat;
     xiv::exd::Exd m_FCCrestSymbolDat;
     xiv::exd::Exd m_FccShopDat;
     xiv::exd::Exd m_FCHierarchyDat;
     xiv::exd::Exd m_FCProfileDat;
     xiv::exd::Exd m_FCRankDat;
     xiv::exd::Exd m_FCReputationDat;
     xiv::exd::Exd m_FCRightsDat;
     xiv::exd::Exd m_FestivalDat;
     xiv::exd::Exd m_FieldMarkerDat;
     xiv::exd::Exd m_FishingRecordTypeDat;
     xiv::exd::Exd m_FishingRecordTypeTransientDat;
     xiv::exd::Exd m_FishingSpotDat;
     xiv::exd::Exd m_FishParameterDat;
     xiv::exd::Exd m_Frontline03Dat;
     xiv::exd::Exd m_Frontline04Dat;
     xiv::exd::Exd m_FurnitureCatalogCategoryDat;
     xiv::exd::Exd m_FurnitureCatalogItemListDat;
     xiv::exd::Exd m_GardeningSeedDat;
     xiv::exd::Exd m_GatheringConditionDat;
     xiv::exd::Exd m_GatheringExpDat;
     xiv::exd::Exd m_GatheringItemDat;
     xiv::exd::Exd m_GatheringItemLevelConvertTableDat;
     xiv::exd::Exd m_GatheringItemPointDat;
     xiv::exd::Exd m_GatheringLeveDat;
     xiv::exd::Exd m_GatheringLeveRouteDat;
     xiv::exd::Exd m_GatheringLeveRuleDat;
     xiv::exd::Exd m_GatheringNotebookListDat;
     xiv::exd::Exd m_GatheringPointDat;
     xiv::exd::Exd m_GatheringPointBaseDat;
     xiv::exd::Exd m_GatheringPointBonusDat;
     xiv::exd::Exd m_GatheringPointBonusTypeDat;
     xiv::exd::Exd m_GatheringPointNameDat;
     xiv::exd::Exd m_GatheringPointTransientDat;
     xiv::exd::Exd m_GatheringRarePopTimeTableDat;
     xiv::exd::Exd m_GatheringSubCategoryDat;
     xiv::exd::Exd m_GatheringTypeDat;
     xiv::exd::Exd m_GcArmyCaptureTacticsDat;
     xiv::exd::Exd m_GcArmyExpeditionDat;
     xiv::exd::Exd m_GcArmyExpeditionMemberBonusDat;
     xiv::exd::Exd m_GcArmyExpeditionTypeDat;
     xiv::exd::Exd m_GcArmyMemberGrowDat;
     xiv::exd::Exd m_GcArmyTrainingDat;
     xiv::exd::Exd m_GCRankGridaniaFemaleTextDat;
     xiv::exd::Exd m_GCRankGridaniaMaleTextDat;
     xiv::exd::Exd m_GCRankLimsaFemaleTextDat;
     xiv::exd::Exd m_GCRankLimsaMaleTextDat;
     xiv::exd::Exd m_GCRankUldahFemaleTextDat;
     xiv::exd::Exd m_GCRankUldahMaleTextDat;
     xiv::exd::Exd m_GCScripShopCategoryDat;
     xiv::exd::Exd m_GCScripShopItemDat;
     xiv::exd::Exd m_GCShopDat;
     xiv::exd::Exd m_GCShopItemCategoryDat;
     xiv::exd::Exd m_GCSupplyDutyDat;
     xiv::exd::Exd m_GCSupplyDutyRewardDat;
     xiv::exd::Exd m_GeneralActionDat;
     xiv::exd::Exd m_GFATEDat;
     xiv::exd::Exd m_GFateClimbing2Dat;
     xiv::exd::Exd m_GFateClimbing2ContentDat;
     xiv::exd::Exd m_GFateClimbing2TotemTypeDat;
     xiv::exd::Exd m_GFateRideShootingDat;
     xiv::exd::Exd m_GilShopDat;
     xiv::exd::Exd m_GilShopItemDat;
     xiv::exd::Exd m_GimmickAccessorDat;
     xiv::exd::Exd m_GimmickJumpDat;
     xiv::exd::Exd m_GimmickRectDat;
     xiv::exd::Exd m_GoldSaucerArcadeMachineDat;
     xiv::exd::Exd m_GoldSaucerTextDataDat;
     xiv::exd::Exd m_GrandCompanyDat;
     xiv::exd::Exd m_GrandCompanyRankDat;
     xiv::exd::Exd m_GroupPoseFrameDat;
     xiv::exd::Exd m_GroupPoseStampDat;
     xiv::exd::Exd m_GroupPoseStampCategoryDat;
     xiv::exd::Exd m_GuardianDeityDat;
     xiv::exd::Exd m_GuideDat;
     xiv::exd::Exd m_GuidePageDat;
     xiv::exd::Exd m_GuidePageStringDat;
     xiv::exd::Exd m_GuideTitleDat;
     xiv::exd::Exd m_GuildleveAssignmentDat;
     xiv::exd::Exd m_GuildleveAssignmentCategoryDat;
     xiv::exd::Exd m_GuildOrderDat;
     xiv::exd::Exd m_GuildOrderGuideDat;
     xiv::exd::Exd m_GuildOrderOfficerDat;
     xiv::exd::Exd m_HairMakeTypeDat;
     xiv::exd::Exd m_HouseRetainerPoseDat;
     xiv::exd::Exd m_HousingAethernetDat;
     xiv::exd::Exd m_HousingAppealDat;
     xiv::exd::Exd m_HousingEmploymentNpcListDat;
     xiv::exd::Exd m_HousingEmploymentNpcRaceDat;
     xiv::exd::Exd m_HousingExteriorDat;
     xiv::exd::Exd m_HousingFurnitureDat;
     xiv::exd::Exd m_HousingLandSetDat;
     xiv::exd::Exd m_HousingMapMarkerInfoDat;
     xiv::exd::Exd m_HousingMerchantPoseDat;
     xiv::exd::Exd m_HousingPlacementDat;
     xiv::exd::Exd m_HousingPresetDat;
     xiv::exd::Exd m_HousingUnitedExteriorDat;
     xiv::exd::Exd m_HousingYardObjectDat;
     xiv::exd::Exd m_HowToDat;
     xiv::exd::Exd m_HowToCategoryDat;
     xiv::exd::Exd m_HowToPageDat;
     xiv::exd::Exd m_HugeCraftworksNpcDat;
     xiv::exd::Exd m_HugeCraftworksRankDat;
     xiv::exd::Exd m_HWDAnnounceDat;
     xiv::exd::Exd m_HWDCrafterSupplyDat;
     xiv::exd::Exd m_HWDCrafterSupplyRewardDat;
     xiv::exd::Exd m_HWDCrafterSupplyTermDat;
     xiv::exd::Exd m_HWDDevLayerControlDat;
     xiv::exd::Exd m_HWDDevLevelUIDat;
     xiv::exd::Exd m_HWDDevLivelyDat;
     xiv::exd::Exd m_HWDDevProgressDat;
     xiv::exd::Exd m_HWDGathereInspectTermDat;
     xiv::exd::Exd m_HWDGathererInspectionDat;
     xiv::exd::Exd m_HWDGathererInspectionRewardDat;
     xiv::exd::Exd m_HWDInfoBoardArticleDat;
     xiv::exd::Exd m_HWDInfoBoardArticleTransientDat;
     xiv::exd::Exd m_HWDInfoBoardArticleTypeDat;
     xiv::exd::Exd m_HWDLevelChangeDeceptionDat;
     xiv::exd::Exd m_HWDSharedGroupDat;
     xiv::exd::Exd m_HWDSharedGroupControlParamDat;
     xiv::exd::Exd m_IKDContentBonusDat;
     xiv::exd::Exd m_IKDFishParamDat;
     xiv::exd::Exd m_IKDRouteDat;
     xiv::exd::Exd m_IKDRouteTableDat;
     xiv::exd::Exd m_IKDSpotDat;
     xiv::exd::Exd m_InclusionShopDat;
     xiv::exd::Exd m_InclusionShopCategoryDat;
     xiv::exd::Exd m_InclusionShopSeriesDat;
     xiv::exd::Exd m_IndividualWeatherDat;
     xiv::exd::Exd m_InstanceContentDat;
     xiv::exd::Exd m_InstanceContentBuffDat;
     xiv::exd::Exd m_InstanceContentCSBonusDat;
     xiv::exd::Exd m_InstanceContentGuideDat;
     xiv::exd::Exd m_InstanceContentTextDataDat;
     xiv::exd::Exd m_ItemDat;
     xiv::exd::Exd m_ItemActionDat;
     xiv::exd::Exd m_ItemActionTelepoDat;
     xiv::exd::Exd m_ItemBarterCheckDat;
     xiv::exd::Exd m_ItemFoodDat;
     xiv::exd::Exd m_ItemLevelDat;
     xiv::exd::Exd m_ItemSearchCategoryDat;
     xiv::exd::Exd m_ItemSeriesDat;
     xiv::exd::Exd m_ItemSortCategoryDat;
     xiv::exd::Exd m_ItemSpecialBonusDat;
     xiv::exd::Exd m_ItemUICategoryDat;
     xiv::exd::Exd m_JobHudManualDat;
     xiv::exd::Exd m_JobHudManualPriorityDat;
     xiv::exd::Exd m_JournalCategoryDat;
     xiv::exd::Exd m_JournalGenreDat;
     xiv::exd::Exd m_JournalSectionDat;
     xiv::exd::Exd m_KnockbackDat;
     xiv::exd::Exd m_LegacyQuestDat;
     xiv::exd::Exd m_LeveDat;
     xiv::exd::Exd m_LeveAssignmentTypeDat;
     xiv::exd::Exd m_LeveClientDat;
     xiv::exd::Exd m_LevelDat;
     xiv::exd::Exd m_LeveRewardItemDat;
     xiv::exd::Exd m_LeveRewardItemGroupDat;
     xiv::exd::Exd m_LeveStringDat;
     xiv::exd::Exd m_LeveVfxDat;
     xiv::exd::Exd m_LobbyDat;
     xiv::exd::Exd m_LogFilterDat;
     xiv::exd::Exd m_LogKindDat;
     xiv::exd::Exd m_LogMessageDat;
     xiv::exd::Exd m_LotteryExchangeShopDat;
     xiv::exd::Exd m_MacroIconDat;
     xiv::exd::Exd m_MacroIconRedirectOldDat;
     xiv::exd::Exd m_MainCommandDat;
     xiv::exd::Exd m_MainCommandCategoryDat;
     xiv::exd::Exd m_ManeuversArmorDat;
     xiv::exd::Exd m_MapDat;
     xiv::exd::Exd m_MapMarkerDat;
     xiv::exd::Exd m_MapMarkerRegionDat;
     xiv::exd::Exd m_MapSymbolDat;
     xiv::exd::Exd m_MarkerDat;
     xiv::exd::Exd m_MasterpieceSupplyDutyDat;
     xiv::exd::Exd m_MasterpieceSupplyMultiplierDat;
     xiv::exd::Exd m_MateriaDat;
     xiv::exd::Exd m_MateriaJoinRateDat;
     xiv::exd::Exd m_MateriaJoinRateGatherCraftDat;
     xiv::exd::Exd m_MateriaTomestoneRateDat;
     xiv::exd::Exd m_MiniGameRADat;
     xiv::exd::Exd m_MinionRaceDat;
     xiv::exd::Exd m_MinionRulesDat;
     xiv::exd::Exd m_MinionSkillTypeDat;
     xiv::exd::Exd m_MobHuntOrderDat;
     xiv::exd::Exd m_MobHuntOrderTypeDat;
     xiv::exd::Exd m_MobHuntRewardDat;
     xiv::exd::Exd m_MobHuntRewardCapDat;
     xiv::exd::Exd m_MobHuntTargetDat;
     xiv::exd::Exd m_ModelCharaDat;
     xiv::exd::Exd m_ModelSkeletonDat;
     xiv::exd::Exd m_ModelStateDat;
     xiv::exd::Exd m_MonsterNoteDat;
     xiv::exd::Exd m_MonsterNoteTargetDat;
     xiv::exd::Exd m_MotionTimelineDat;
     xiv::exd::Exd m_MotionTimelineBlendTableDat;
     xiv::exd::Exd m_MountDat;
     xiv::exd::Exd m_MountActionDat;
     xiv::exd::Exd m_MountCustomizeDat;
     xiv::exd::Exd m_MountFlyingConditionDat;
     xiv::exd::Exd m_MountSpeedDat;
     xiv::exd::Exd m_MountTransientDat;
     xiv::exd::Exd m_MoveTimelineDat;
     xiv::exd::Exd m_MoveVfxDat;
     xiv::exd::Exd m_MovieStaffListDat;
     xiv::exd::Exd m_MovieSubtitleDat;
     xiv::exd::Exd m_MovieSubtitle500Dat;
     xiv::exd::Exd m_MovieSubtitleVoyageDat;
     xiv::exd::Exd m_MYCTemporaryItemDat;
     xiv::exd::Exd m_MYCTemporaryItemUICategoryDat;
     xiv::exd::Exd m_MYCWarResultNotebookDat;
     xiv::exd::Exd m_NotebookDivisionDat;
     xiv::exd::Exd m_NotebookDivisionCategoryDat;
     xiv::exd::Exd m_NotoriousMonsterDat;
     xiv::exd::Exd m_NpcEquipDat;
     xiv::exd::Exd m_NpcYellDat;
     xiv::exd::Exd m_OmenDat;
     xiv::exd::Exd m_OnlineStatusDat;
     xiv::exd::Exd m_OpenContentDat;
     xiv::exd::Exd m_OpenContentCandidateNameDat;
     xiv::exd::Exd m_OpeningDat;
     xiv::exd::Exd m_OrchestrionDat;
     xiv::exd::Exd m_OrchestrionCategoryDat;
     xiv::exd::Exd m_OrchestrionPathDat;
     xiv::exd::Exd m_OrchestrionUiparamDat;
     xiv::exd::Exd m_OrnamentDat;
     xiv::exd::Exd m_ParamGrowDat;
     xiv::exd::Exd m_PartyContentDat;
     xiv::exd::Exd m_PartyContentCutsceneDat;
     xiv::exd::Exd m_PartyContentTextDataDat;
     xiv::exd::Exd m_PatchMarkDat;
     xiv::exd::Exd m_PerformDat;
     xiv::exd::Exd m_PerformTransientDat;
     xiv::exd::Exd m_PetDat;
     xiv::exd::Exd m_PetActionDat;
     xiv::exd::Exd m_PhysicsGroupDat;
     xiv::exd::Exd m_PhysicsWindDat;
     xiv::exd::Exd m_PictureDat;
     xiv::exd::Exd m_PlaceNameDat;
     xiv::exd::Exd m_PlantPotFlowerSeedDat;
     xiv::exd::Exd m_PreHandlerDat;
     xiv::exd::Exd m_PresetCameraDat;
     xiv::exd::Exd m_PresetCameraAdjustDat;
     xiv::exd::Exd m_PublicContentDat;
     xiv::exd::Exd m_PublicContentCutsceneDat;
     xiv::exd::Exd m_PublicContentTextDataDat;
     xiv::exd::Exd m_PurifyDat;
     xiv::exd::Exd m_PvPActionDat;
     xiv::exd::Exd m_PvPActionSortDat;
     xiv::exd::Exd m_PvPRankDat;
     xiv::exd::Exd m_PvPSelectTraitDat;
     xiv::exd::Exd m_PvPTraitDat;
     xiv::exd::Exd m_QuestDat;
     xiv::exd::Exd m_QuestBattleDat;
     xiv::exd::Exd m_QuestChapterDat;
     xiv::exd::Exd m_QuestClassJobRewardDat;
     xiv::exd::Exd m_QuestClassJobSupplyDat;
     xiv::exd::Exd m_QuestDerivedClassDat;
     xiv::exd::Exd m_QuestRedoDat;
     xiv::exd::Exd m_QuestRedoChapterUIDat;
     xiv::exd::Exd m_QuestRedoChapterUICategoryDat;
     xiv::exd::Exd m_QuestRedoChapterUITabDat;
     xiv::exd::Exd m_QuestRedoIncompChapterDat;
     xiv::exd::Exd m_QuestRepeatFlagDat;
     xiv::exd::Exd m_QuestRewardOtherDat;
     xiv::exd::Exd m_QuickChatDat;
     xiv::exd::Exd m_QuickChatTransientDat;
     xiv::exd::Exd m_RaceDat;
     xiv::exd::Exd m_RacingChocoboItemDat;
     xiv::exd::Exd m_RacingChocoboNameDat;
     xiv::exd::Exd m_RacingChocoboNameCategoryDat;
     xiv::exd::Exd m_RacingChocoboNameInfoDat;
     xiv::exd::Exd m_RacingChocoboParamDat;
     xiv::exd::Exd m_RecastNavimeshDat;
     xiv::exd::Exd m_RecipeDat;
     xiv::exd::Exd m_RecipeLevelTableDat;
     xiv::exd::Exd m_RecipeLookupDat;
     xiv::exd::Exd m_RecipeNotebookListDat;
     xiv::exd::Exd m_RecommendContentsDat;
     xiv::exd::Exd m_RelicDat;
     xiv::exd::Exd m_Relic3Dat;
     xiv::exd::Exd m_RelicItemDat;
     xiv::exd::Exd m_RelicNoteDat;
     xiv::exd::Exd m_RelicNoteCategoryDat;
     xiv::exd::Exd m_ResidentDat;
     xiv::exd::Exd m_ResistanceWeaponAdjustDat;
     xiv::exd::Exd m_RetainerTaskDat;
     xiv::exd::Exd m_RetainerTaskLvRangeDat;
     xiv::exd::Exd m_RetainerTaskNormalDat;
     xiv::exd::Exd m_RetainerTaskParameterDat;
     xiv::exd::Exd m_RetainerTaskRandomDat;
     xiv::exd::Exd m_RideShootingDat;
     xiv::exd::Exd m_RideShootingTextDataDat;
     xiv::exd::Exd m_RPParameterDat;
     xiv::exd::Exd m_SatisfactionArbitrationDat;
     xiv::exd::Exd m_SatisfactionNpcDat;
     xiv::exd::Exd m_SatisfactionSupplyDat;
     xiv::exd::Exd m_SatisfactionSupplyRewardDat;
     xiv::exd::Exd m_ScenarioTreeDat;
     xiv::exd::Exd m_ScenarioTreeTipsDat;
     xiv::exd::Exd m_ScenarioTreeTipsClassQuestDat;
     xiv::exd::Exd m_ScenarioTypeDat;
     xiv::exd::Exd m_ScreenImageDat;
     xiv::exd::Exd m_SecretRecipeBookDat;
     xiv::exd::Exd m_SkyIsland2MissionDat;
     xiv::exd::Exd m_SkyIsland2MissionDetailDat;
     xiv::exd::Exd m_SkyIsland2MissionTypeDat;
     xiv::exd::Exd m_SkyIsland2RangeTypeDat;
     xiv::exd::Exd m_SnipeTalkDat;
     xiv::exd::Exd m_SnipeTalkNameDat;
     xiv::exd::Exd m_SpearfishingItemDat;
     xiv::exd::Exd m_SpearfishingNotebookDat;
     xiv::exd::Exd m_SpearfishingRecordPageDat;
     xiv::exd::Exd m_SpecialShopDat;
     xiv::exd::Exd m_SpecialShopItemCategoryDat;
     xiv::exd::Exd m_StainDat;
     xiv::exd::Exd m_StainTransientDat;
     xiv::exd::Exd m_StatusDat;
     xiv::exd::Exd m_StatusHitEffectDat;
     xiv::exd::Exd m_StatusLoopVFXDat;
     xiv::exd::Exd m_StoryDat;
     xiv::exd::Exd m_SubmarineExplorationDat;
     xiv::exd::Exd m_SubmarineMapDat;
     xiv::exd::Exd m_SubmarinePartDat;
     xiv::exd::Exd m_SubmarineRankDat;
     xiv::exd::Exd m_SwitchTalkDat;
     xiv::exd::Exd m_SwitchTalkVariationDat;
     xiv::exd::Exd m_TerritoryTypeDat;
     xiv::exd::Exd m_TerritoryTypeTransientDat;
     xiv::exd::Exd m_TextCommandDat;
     xiv::exd::Exd m_TitleDat;
     xiv::exd::Exd m_TomestonesDat;
     xiv::exd::Exd m_TomestonesItemDat;
     xiv::exd::Exd m_TopicSelectDat;
     xiv::exd::Exd m_TownDat;
     xiv::exd::Exd m_TraitDat;
     xiv::exd::Exd m_TraitRecastDat;
     xiv::exd::Exd m_TraitTransientDat;
     xiv::exd::Exd m_TransformationDat;
     xiv::exd::Exd m_TreasureDat;
     xiv::exd::Exd m_TreasureHuntRankDat;
     xiv::exd::Exd m_TreasureModelDat;
     xiv::exd::Exd m_TreasureSpotDat;
     xiv::exd::Exd m_TribeDat;
     xiv::exd::Exd m_TripleTriadDat;
     xiv::exd::Exd m_TripleTriadCardDat;
     xiv::exd::Exd m_TripleTriadCardRarityDat;
     xiv::exd::Exd m_TripleTriadCardResidentDat;
     xiv::exd::Exd m_TripleTriadCardTypeDat;
     xiv::exd::Exd m_TripleTriadCompetitionDat;
     xiv::exd::Exd m_TripleTriadRuleDat;
     xiv::exd::Exd m_TutorialDat;
     xiv::exd::Exd m_TutorialDPSDat;
     xiv::exd::Exd m_TutorialHealerDat;
     xiv::exd::Exd m_TutorialTankDat;
     xiv::exd::Exd m_UIColorDat;
     xiv::exd::Exd m_VaseFlowerDat;
     xiv::exd::Exd m_VFXDat;
     xiv::exd::Exd m_WarpDat;
     xiv::exd::Exd m_WarpConditionDat;
     xiv::exd::Exd m_WarpLogicDat;
     xiv::exd::Exd m_WeaponTimelineDat;
     xiv::exd::Exd m_WeatherDat;
     xiv::exd::Exd m_WeatherGroupDat;
     xiv::exd::Exd m_WeatherRateDat;
     xiv::exd::Exd m_WeatherReportReplaceDat;
     xiv::exd::Exd m_WebGuidanceDat;
     xiv::exd::Exd m_WebURLDat;
     xiv::exd::Exd m_WeddingBGMDat;
     xiv::exd::Exd m_WeeklyBingoOrderDataDat;
     xiv::exd::Exd m_WeeklyBingoRewardDataDat;
     xiv::exd::Exd m_WeeklyBingoTextDat;
     xiv::exd::Exd m_WeeklyLotBonusDat;
     xiv::exd::Exd m_WorldDat;
     xiv::exd::Exd m_WorldDCGroupTypeDat;
     xiv::exd::Exd m_YardCatalogCategoryDat;
     xiv::exd::Exd m_YardCatalogItemListDat;
     xiv::exd::Exd m_YKWDat;
     xiv::exd::Exd m_ZoneSharedGroupDat;


     using AchievementPtr = std::shared_ptr< Achievement >;
     using AchievementCategoryPtr = std::shared_ptr< AchievementCategory >;
     using AchievementHideConditionPtr = std::shared_ptr< AchievementHideCondition >;
     using AchievementKindPtr = std::shared_ptr< AchievementKind >;
     using ActionPtr = std::shared_ptr< Action >;
     using ActionCastTimelinePtr = std::shared_ptr< ActionCastTimeline >;
     using ActionCastVFXPtr = std::shared_ptr< ActionCastVFX >;
     using ActionCategoryPtr = std::shared_ptr< ActionCategory >;
     using ActionComboRoutePtr = std::shared_ptr< ActionComboRoute >;
     using ActionIndirectionPtr = std::shared_ptr< ActionIndirection >;
     using ActionParamPtr = std::shared_ptr< ActionParam >;
     using ActionProcStatusPtr = std::shared_ptr< ActionProcStatus >;
     using ActionTimelinePtr = std::shared_ptr< ActionTimeline >;
     using ActionTimelineMovePtr = std::shared_ptr< ActionTimelineMove >;
     using ActionTimelineReplacePtr = std::shared_ptr< ActionTimelineReplace >;
     using ActionTransientPtr = std::shared_ptr< ActionTransient >;
     using ActivityFeedButtonsPtr = std::shared_ptr< ActivityFeedButtons >;
     using ActivityFeedCaptionsPtr = std::shared_ptr< ActivityFeedCaptions >;
     using ActivityFeedGroupCaptionsPtr = std::shared_ptr< ActivityFeedGroupCaptions >;
     using ActivityFeedImagesPtr = std::shared_ptr< ActivityFeedImages >;
     using AddonPtr = std::shared_ptr< Addon >;
     using AdventurePtr = std::shared_ptr< Adventure >;
     using AdventureExPhasePtr = std::shared_ptr< AdventureExPhase >;
     using AetherCurrentPtr = std::shared_ptr< AetherCurrent >;
     using AetherCurrentCompFlgSetPtr = std::shared_ptr< AetherCurrentCompFlgSet >;
     using AetherialWheelPtr = std::shared_ptr< AetherialWheel >;
     using AetherytePtr = std::shared_ptr< Aetheryte >;
     using AetheryteSystemDefinePtr = std::shared_ptr< AetheryteSystemDefine >;
     using AirshipExplorationLevelPtr = std::shared_ptr< AirshipExplorationLevel >;
     using AirshipExplorationLogPtr = std::shared_ptr< AirshipExplorationLog >;
     using AirshipExplorationParamTypePtr = std::shared_ptr< AirshipExplorationParamType >;
     using AirshipExplorationPartPtr = std::shared_ptr< AirshipExplorationPart >;
     using AirshipExplorationPointPtr = std::shared_ptr< AirshipExplorationPoint >;
     using AnimationLODPtr = std::shared_ptr< AnimationLOD >;
     using AnimaWeapon5Ptr = std::shared_ptr< AnimaWeapon5 >;
     using AnimaWeapon5ParamPtr = std::shared_ptr< AnimaWeapon5Param >;
     using AnimaWeapon5PatternGroupPtr = std::shared_ptr< AnimaWeapon5PatternGroup >;
     using AnimaWeapon5SpiritTalkPtr = std::shared_ptr< AnimaWeapon5SpiritTalk >;
     using AnimaWeapon5SpiritTalkParamPtr = std::shared_ptr< AnimaWeapon5SpiritTalkParam >;
     using AnimaWeapon5TradeItemPtr = std::shared_ptr< AnimaWeapon5TradeItem >;
     using AnimaWeaponFUITalkPtr = std::shared_ptr< AnimaWeaponFUITalk >;
     using AnimaWeaponFUITalkParamPtr = std::shared_ptr< AnimaWeaponFUITalkParam >;
     using AnimaWeaponIconPtr = std::shared_ptr< AnimaWeaponIcon >;
     using AnimaWeaponItemPtr = std::shared_ptr< AnimaWeaponItem >;
     using AozActionPtr = std::shared_ptr< AozAction >;
     using AozActionTransientPtr = std::shared_ptr< AozActionTransient >;
     using AOZArrangementPtr = std::shared_ptr< AOZArrangement >;
     using AOZBossPtr = std::shared_ptr< AOZBoss >;
     using AOZContentPtr = std::shared_ptr< AOZContent >;
     using AOZContentBriefingBNpcPtr = std::shared_ptr< AOZContentBriefingBNpc >;
     using AquariumFishPtr = std::shared_ptr< AquariumFish >;
     using AquariumWaterPtr = std::shared_ptr< AquariumWater >;
     using ArrayEventHandlerPtr = std::shared_ptr< ArrayEventHandler >;
     using AttackTypePtr = std::shared_ptr< AttackType >;
     using BacklightColorPtr = std::shared_ptr< BacklightColor >;
     using BallistaPtr = std::shared_ptr< Ballista >;
     using BalloonPtr = std::shared_ptr< Balloon >;
     using BaseParamPtr = std::shared_ptr< BaseParam >;
     using BattleLevePtr = std::shared_ptr< BattleLeve >;
     using BattleLeveRulePtr = std::shared_ptr< BattleLeveRule >;
     using BeastRankBonusPtr = std::shared_ptr< BeastRankBonus >;
     using BeastReputationRankPtr = std::shared_ptr< BeastReputationRank >;
     using BeastTribePtr = std::shared_ptr< BeastTribe >;
     using BehaviorPtr = std::shared_ptr< Behavior >;
     using BehaviorPathPtr = std::shared_ptr< BehaviorPath >;
     using BenchmarkOverrideEquipmentPtr = std::shared_ptr< BenchmarkOverrideEquipment >;
     using BGMPtr = std::shared_ptr< BGM >;
     using BGMFadePtr = std::shared_ptr< BGMFade >;
     using BGMFadeTypePtr = std::shared_ptr< BGMFadeType >;
     using BGMScenePtr = std::shared_ptr< BGMScene >;
     using BGMSituationPtr = std::shared_ptr< BGMSituation >;
     using BGMSwitchPtr = std::shared_ptr< BGMSwitch >;
     using BGMSystemDefinePtr = std::shared_ptr< BGMSystemDefine >;
     using BNpcAnnounceIconPtr = std::shared_ptr< BNpcAnnounceIcon >;
     using BNpcBasePtr = std::shared_ptr< BNpcBase >;
     using BNpcCustomizePtr = std::shared_ptr< BNpcCustomize >;
     using BNpcNamePtr = std::shared_ptr< BNpcName >;
     using BNpcPartsPtr = std::shared_ptr< BNpcParts >;
     using BNpcStatePtr = std::shared_ptr< BNpcState >;
     using BuddyPtr = std::shared_ptr< Buddy >;
     using BuddyActionPtr = std::shared_ptr< BuddyAction >;
     using BuddyEquipPtr = std::shared_ptr< BuddyEquip >;
     using BuddyItemPtr = std::shared_ptr< BuddyItem >;
     using BuddyRankPtr = std::shared_ptr< BuddyRank >;
     using BuddySkillPtr = std::shared_ptr< BuddySkill >;
     using CabinetPtr = std::shared_ptr< Cabinet >;
     using CabinetCategoryPtr = std::shared_ptr< CabinetCategory >;
     using CalendarPtr = std::shared_ptr< Calendar >;
     using CarryPtr = std::shared_ptr< Carry >;
     using ChannelingPtr = std::shared_ptr< Channeling >;
     using CharaMakeClassEquipPtr = std::shared_ptr< CharaMakeClassEquip >;
     using CharaMakeCustomizePtr = std::shared_ptr< CharaMakeCustomize >;
     using CharaMakeNamePtr = std::shared_ptr< CharaMakeName >;
     using CharaMakeTypePtr = std::shared_ptr< CharaMakeType >;
     using ChocoboRacePtr = std::shared_ptr< ChocoboRace >;
     using ChocoboRaceAbilityPtr = std::shared_ptr< ChocoboRaceAbility >;
     using ChocoboRaceAbilityTypePtr = std::shared_ptr< ChocoboRaceAbilityType >;
     using ChocoboRaceItemPtr = std::shared_ptr< ChocoboRaceItem >;
     using ChocoboRaceRankPtr = std::shared_ptr< ChocoboRaceRank >;
     using ChocoboRaceStatusPtr = std::shared_ptr< ChocoboRaceStatus >;
     using ChocoboRaceTerritoryPtr = std::shared_ptr< ChocoboRaceTerritory >;
     using ChocoboRaceTutorialPtr = std::shared_ptr< ChocoboRaceTutorial >;
     using ChocoboRaceWeatherPtr = std::shared_ptr< ChocoboRaceWeather >;
     using ChocoboTaxiPtr = std::shared_ptr< ChocoboTaxi >;
     using ChocoboTaxiStandPtr = std::shared_ptr< ChocoboTaxiStand >;
     using CircleActivityPtr = std::shared_ptr< CircleActivity >;
     using ClassJobPtr = std::shared_ptr< ClassJob >;
     using ClassJobCategoryPtr = std::shared_ptr< ClassJobCategory >;
     using CollectablesShopPtr = std::shared_ptr< CollectablesShop >;
     using CollectablesShopItemPtr = std::shared_ptr< CollectablesShopItem >;
     using CollectablesShopItemGroupPtr = std::shared_ptr< CollectablesShopItemGroup >;
     using CollectablesShopRefinePtr = std::shared_ptr< CollectablesShopRefine >;
     using CollectablesShopRewardItemPtr = std::shared_ptr< CollectablesShopRewardItem >;
     using CollectablesShopRewardScripPtr = std::shared_ptr< CollectablesShopRewardScrip >;
     using CompanionPtr = std::shared_ptr< Companion >;
     using CompanionMovePtr = std::shared_ptr< CompanionMove >;
     using CompanionTransientPtr = std::shared_ptr< CompanionTransient >;
     using CompanyActionPtr = std::shared_ptr< CompanyAction >;
     using CompanyCraftDraftPtr = std::shared_ptr< CompanyCraftDraft >;
     using CompanyCraftDraftCategoryPtr = std::shared_ptr< CompanyCraftDraftCategory >;
     using CompanyCraftManufactoryStatePtr = std::shared_ptr< CompanyCraftManufactoryState >;
     using CompanyCraftPartPtr = std::shared_ptr< CompanyCraftPart >;
     using CompanyCraftProcessPtr = std::shared_ptr< CompanyCraftProcess >;
     using CompanyCraftSequencePtr = std::shared_ptr< CompanyCraftSequence >;
     using CompanyCraftSupplyItemPtr = std::shared_ptr< CompanyCraftSupplyItem >;
     using CompanyCraftTypePtr = std::shared_ptr< CompanyCraftType >;
     using CompanyLevePtr = std::shared_ptr< CompanyLeve >;
     using CompanyLeveRulePtr = std::shared_ptr< CompanyLeveRule >;
     using CompleteJournalPtr = std::shared_ptr< CompleteJournal >;
     using CompleteJournalCategoryPtr = std::shared_ptr< CompleteJournalCategory >;
     using ConditionPtr = std::shared_ptr< Condition >;
     using ConfigKeyPtr = std::shared_ptr< ConfigKey >;
     using ContentCloseCyclePtr = std::shared_ptr< ContentCloseCycle >;
     using ContentExActionPtr = std::shared_ptr< ContentExAction >;
     using ContentFinderConditionPtr = std::shared_ptr< ContentFinderCondition >;
     using ContentFinderConditionTransientPtr = std::shared_ptr< ContentFinderConditionTransient >;
     using ContentGaugePtr = std::shared_ptr< ContentGauge >;
     using ContentGaugeColorPtr = std::shared_ptr< ContentGaugeColor >;
     using ContentMemberTypePtr = std::shared_ptr< ContentMemberType >;
     using ContentNpcTalkPtr = std::shared_ptr< ContentNpcTalk >;
     using ContentRandomSelectPtr = std::shared_ptr< ContentRandomSelect >;
     using ContentRoulettePtr = std::shared_ptr< ContentRoulette >;
     using ContentRouletteOpenRulePtr = std::shared_ptr< ContentRouletteOpenRule >;
     using ContentRouletteRoleBonusPtr = std::shared_ptr< ContentRouletteRoleBonus >;
     using ContentsNotePtr = std::shared_ptr< ContentsNote >;
     using ContentsTutorialPtr = std::shared_ptr< ContentsTutorial >;
     using ContentsTutorialPagePtr = std::shared_ptr< ContentsTutorialPage >;
     using ContentTalkPtr = std::shared_ptr< ContentTalk >;
     using ContentTalkParamPtr = std::shared_ptr< ContentTalkParam >;
     using ContentTypePtr = std::shared_ptr< ContentType >;
     using CraftActionPtr = std::shared_ptr< CraftAction >;
     using CraftLevePtr = std::shared_ptr< CraftLeve >;
     using CraftLevelDifferencePtr = std::shared_ptr< CraftLevelDifference >;
     using CraftTypePtr = std::shared_ptr< CraftType >;
     using CreditPtr = std::shared_ptr< Credit >;
     using CreditBackImagePtr = std::shared_ptr< CreditBackImage >;
     using CreditCastPtr = std::shared_ptr< CreditCast >;
     using CreditListPtr = std::shared_ptr< CreditList >;
     using CreditListTextPtr = std::shared_ptr< CreditListText >;
     using CustomTalkPtr = std::shared_ptr< CustomTalk >;
     using CustomTalkDynamicIconPtr = std::shared_ptr< CustomTalkDynamicIcon >;
     using CustomTalkNestHandlersPtr = std::shared_ptr< CustomTalkNestHandlers >;
     using CutscenePtr = std::shared_ptr< Cutscene >;
     using CutsceneMotionPtr = std::shared_ptr< CutsceneMotion >;
     using CutsceneWorkIndexPtr = std::shared_ptr< CutsceneWorkIndex >;
     using CutScreenImagePtr = std::shared_ptr< CutScreenImage >;
     using CycleTimePtr = std::shared_ptr< CycleTime >;
     using DailySupplyItemPtr = std::shared_ptr< DailySupplyItem >;
     using DawnContentPtr = std::shared_ptr< DawnContent >;
     using DawnGrowMemberPtr = std::shared_ptr< DawnGrowMember >;
     using DawnMemberUIParamPtr = std::shared_ptr< DawnMemberUIParam >;
     using DawnQuestAnnouncePtr = std::shared_ptr< DawnQuestAnnounce >;
     using DawnQuestMemberPtr = std::shared_ptr< DawnQuestMember >;
     using DeepDungeonPtr = std::shared_ptr< DeepDungeon >;
     using DeepDungeonBanPtr = std::shared_ptr< DeepDungeonBan >;
     using DeepDungeonDangerPtr = std::shared_ptr< DeepDungeonDanger >;
     using DeepDungeonEquipmentPtr = std::shared_ptr< DeepDungeonEquipment >;
     using DeepDungeonFloorEffectUIPtr = std::shared_ptr< DeepDungeonFloorEffectUI >;
     using DeepDungeonItemPtr = std::shared_ptr< DeepDungeonItem >;
     using DeepDungeonLayerPtr = std::shared_ptr< DeepDungeonLayer >;
     using DeepDungeonMagicStonePtr = std::shared_ptr< DeepDungeonMagicStone >;
     using DeepDungeonMap5XPtr = std::shared_ptr< DeepDungeonMap5X >;
     using DeepDungeonRoomPtr = std::shared_ptr< DeepDungeonRoom >;
     using DeepDungeonStatusPtr = std::shared_ptr< DeepDungeonStatus >;
     using DefaultTalkPtr = std::shared_ptr< DefaultTalk >;
     using DefaultTalkLipSyncTypePtr = std::shared_ptr< DefaultTalkLipSyncType >;
     using DeliveryQuestPtr = std::shared_ptr< DeliveryQuest >;
     using DescriptionPtr = std::shared_ptr< Description >;
     using DescriptionPagePtr = std::shared_ptr< DescriptionPage >;
     using DescriptionSectionPtr = std::shared_ptr< DescriptionSection >;
     using DescriptionStringPtr = std::shared_ptr< DescriptionString >;
     using DisposalShopPtr = std::shared_ptr< DisposalShop >;
     using DisposalShopFilterTypePtr = std::shared_ptr< DisposalShopFilterType >;
     using DisposalShopItemPtr = std::shared_ptr< DisposalShopItem >;
     using DpsChallengePtr = std::shared_ptr< DpsChallenge >;
     using DpsChallengeOfficerPtr = std::shared_ptr< DpsChallengeOfficer >;
     using DpsChallengeTransientPtr = std::shared_ptr< DpsChallengeTransient >;
     using DynamicEventPtr = std::shared_ptr< DynamicEvent >;
     using DynamicEventEnemyTypePtr = std::shared_ptr< DynamicEventEnemyType >;
     using DynamicEventSingleBattlePtr = std::shared_ptr< DynamicEventSingleBattle >;
     using DynamicEventTypePtr = std::shared_ptr< DynamicEventType >;
     using EmjAddonPtr = std::shared_ptr< EmjAddon >;
     using EmjDaniPtr = std::shared_ptr< EmjDani >;
     using EmotePtr = std::shared_ptr< Emote >;
     using EmoteCategoryPtr = std::shared_ptr< EmoteCategory >;
     using EmoteModePtr = std::shared_ptr< EmoteMode >;
     using ENpcBasePtr = std::shared_ptr< ENpcBase >;
     using ENpcDressUpPtr = std::shared_ptr< ENpcDressUp >;
     using ENpcDressUpDressPtr = std::shared_ptr< ENpcDressUpDress >;
     using ENpcResidentPtr = std::shared_ptr< ENpcResident >;
     using EObjPtr = std::shared_ptr< EObj >;
     using EObjNamePtr = std::shared_ptr< EObjName >;
     using EquipRaceCategoryPtr = std::shared_ptr< EquipRaceCategory >;
     using EquipSlotCategoryPtr = std::shared_ptr< EquipSlotCategory >;
     using EurekaAetherItemPtr = std::shared_ptr< EurekaAetherItem >;
     using EurekaAethernetPtr = std::shared_ptr< EurekaAethernet >;
     using EurekaGrowDataPtr = std::shared_ptr< EurekaGrowData >;
     using EurekaLogosMixerProbabilityPtr = std::shared_ptr< EurekaLogosMixerProbability >;
     using EurekaMagiaActionPtr = std::shared_ptr< EurekaMagiaAction >;
     using EurekaMagiciteItemPtr = std::shared_ptr< EurekaMagiciteItem >;
     using EurekaMagiciteItemTypePtr = std::shared_ptr< EurekaMagiciteItemType >;
     using EurekaSphereElementAdjustPtr = std::shared_ptr< EurekaSphereElementAdjust >;
     using EventActionPtr = std::shared_ptr< EventAction >;
     using EventIconPriorityPtr = std::shared_ptr< EventIconPriority >;
     using EventIconTypePtr = std::shared_ptr< EventIconType >;
     using EventItemPtr = std::shared_ptr< EventItem >;
     using EventItemCastTimelinePtr = std::shared_ptr< EventItemCastTimeline >;
     using EventItemHelpPtr = std::shared_ptr< EventItemHelp >;
     using EventItemTimelinePtr = std::shared_ptr< EventItemTimeline >;
     using EventSystemDefinePtr = std::shared_ptr< EventSystemDefine >;
     using ExportedSGPtr = std::shared_ptr< ExportedSG >;
     using ExVersionPtr = std::shared_ptr< ExVersion >;
     using FatePtr = std::shared_ptr< Fate >;
     using FateEventPtr = std::shared_ptr< FateEvent >;
     using FateModePtr = std::shared_ptr< FateMode >;
     using FateProgressUIPtr = std::shared_ptr< FateProgressUI >;
     using FateTokenTypePtr = std::shared_ptr< FateTokenType >;
     using FCActivityPtr = std::shared_ptr< FCActivity >;
     using FCActivityCategoryPtr = std::shared_ptr< FCActivityCategory >;
     using FCAuthorityPtr = std::shared_ptr< FCAuthority >;
     using FCAuthorityCategoryPtr = std::shared_ptr< FCAuthorityCategory >;
     using FCChestNamePtr = std::shared_ptr< FCChestName >;
     using FCCrestSymbolPtr = std::shared_ptr< FCCrestSymbol >;
     using FccShopPtr = std::shared_ptr< FccShop >;
     using FCHierarchyPtr = std::shared_ptr< FCHierarchy >;
     using FCProfilePtr = std::shared_ptr< FCProfile >;
     using FCRankPtr = std::shared_ptr< FCRank >;
     using FCReputationPtr = std::shared_ptr< FCReputation >;
     using FCRightsPtr = std::shared_ptr< FCRights >;
     using FestivalPtr = std::shared_ptr< Festival >;
     using FieldMarkerPtr = std::shared_ptr< FieldMarker >;
     using FishingRecordTypePtr = std::shared_ptr< FishingRecordType >;
     using FishingRecordTypeTransientPtr = std::shared_ptr< FishingRecordTypeTransient >;
     using FishingSpotPtr = std::shared_ptr< FishingSpot >;
     using FishParameterPtr = std::shared_ptr< FishParameter >;
     using Frontline03Ptr = std::shared_ptr< Frontline03 >;
     using Frontline04Ptr = std::shared_ptr< Frontline04 >;
     using FurnitureCatalogCategoryPtr = std::shared_ptr< FurnitureCatalogCategory >;
     using FurnitureCatalogItemListPtr = std::shared_ptr< FurnitureCatalogItemList >;
     using GardeningSeedPtr = std::shared_ptr< GardeningSeed >;
     using GatheringConditionPtr = std::shared_ptr< GatheringCondition >;
     using GatheringExpPtr = std::shared_ptr< GatheringExp >;
     using GatheringItemPtr = std::shared_ptr< GatheringItem >;
     using GatheringItemLevelConvertTablePtr = std::shared_ptr< GatheringItemLevelConvertTable >;
     using GatheringItemPointPtr = std::shared_ptr< GatheringItemPoint >;
     using GatheringLevePtr = std::shared_ptr< GatheringLeve >;
     using GatheringLeveRoutePtr = std::shared_ptr< GatheringLeveRoute >;
     using GatheringLeveRulePtr = std::shared_ptr< GatheringLeveRule >;
     using GatheringNotebookListPtr = std::shared_ptr< GatheringNotebookList >;
     using GatheringPointPtr = std::shared_ptr< GatheringPoint >;
     using GatheringPointBasePtr = std::shared_ptr< GatheringPointBase >;
     using GatheringPointBonusPtr = std::shared_ptr< GatheringPointBonus >;
     using GatheringPointBonusTypePtr = std::shared_ptr< GatheringPointBonusType >;
     using GatheringPointNamePtr = std::shared_ptr< GatheringPointName >;
     using GatheringPointTransientPtr = std::shared_ptr< GatheringPointTransient >;
     using GatheringRarePopTimeTablePtr = std::shared_ptr< GatheringRarePopTimeTable >;
     using GatheringSubCategoryPtr = std::shared_ptr< GatheringSubCategory >;
     using GatheringTypePtr = std::shared_ptr< GatheringType >;
     using GcArmyCaptureTacticsPtr = std::shared_ptr< GcArmyCaptureTactics >;
     using GcArmyExpeditionPtr = std::shared_ptr< GcArmyExpedition >;
     using GcArmyExpeditionMemberBonusPtr = std::shared_ptr< GcArmyExpeditionMemberBonus >;
     using GcArmyExpeditionTypePtr = std::shared_ptr< GcArmyExpeditionType >;
     using GcArmyMemberGrowPtr = std::shared_ptr< GcArmyMemberGrow >;
     using GcArmyTrainingPtr = std::shared_ptr< GcArmyTraining >;
     using GCRankGridaniaFemaleTextPtr = std::shared_ptr< GCRankGridaniaFemaleText >;
     using GCRankGridaniaMaleTextPtr = std::shared_ptr< GCRankGridaniaMaleText >;
     using GCRankLimsaFemaleTextPtr = std::shared_ptr< GCRankLimsaFemaleText >;
     using GCRankLimsaMaleTextPtr = std::shared_ptr< GCRankLimsaMaleText >;
     using GCRankUldahFemaleTextPtr = std::shared_ptr< GCRankUldahFemaleText >;
     using GCRankUldahMaleTextPtr = std::shared_ptr< GCRankUldahMaleText >;
     using GCScripShopCategoryPtr = std::shared_ptr< GCScripShopCategory >;
     using GCScripShopItemPtr = std::shared_ptr< GCScripShopItem >;
     using GCShopPtr = std::shared_ptr< GCShop >;
     using GCShopItemCategoryPtr = std::shared_ptr< GCShopItemCategory >;
     using GCSupplyDutyPtr = std::shared_ptr< GCSupplyDuty >;
     using GCSupplyDutyRewardPtr = std::shared_ptr< GCSupplyDutyReward >;
     using GeneralActionPtr = std::shared_ptr< GeneralAction >;
     using GFATEPtr = std::shared_ptr< GFATE >;
     using GFateClimbing2Ptr = std::shared_ptr< GFateClimbing2 >;
     using GFateClimbing2ContentPtr = std::shared_ptr< GFateClimbing2Content >;
     using GFateClimbing2TotemTypePtr = std::shared_ptr< GFateClimbing2TotemType >;
     using GFateRideShootingPtr = std::shared_ptr< GFateRideShooting >;
     using GilShopPtr = std::shared_ptr< GilShop >;
     using GilShopItemPtr = std::shared_ptr< GilShopItem >;
     using GimmickAccessorPtr = std::shared_ptr< GimmickAccessor >;
     using GimmickJumpPtr = std::shared_ptr< GimmickJump >;
     using GimmickRectPtr = std::shared_ptr< GimmickRect >;
     using GoldSaucerArcadeMachinePtr = std::shared_ptr< GoldSaucerArcadeMachine >;
     using GoldSaucerTextDataPtr = std::shared_ptr< GoldSaucerTextData >;
     using GrandCompanyPtr = std::shared_ptr< GrandCompany >;
     using GrandCompanyRankPtr = std::shared_ptr< GrandCompanyRank >;
     using GroupPoseFramePtr = std::shared_ptr< GroupPoseFrame >;
     using GroupPoseStampPtr = std::shared_ptr< GroupPoseStamp >;
     using GroupPoseStampCategoryPtr = std::shared_ptr< GroupPoseStampCategory >;
     using GuardianDeityPtr = std::shared_ptr< GuardianDeity >;
     using GuidePtr = std::shared_ptr< Guide >;
     using GuidePagePtr = std::shared_ptr< GuidePage >;
     using GuidePageStringPtr = std::shared_ptr< GuidePageString >;
     using GuideTitlePtr = std::shared_ptr< GuideTitle >;
     using GuildleveAssignmentPtr = std::shared_ptr< GuildleveAssignment >;
     using GuildleveAssignmentCategoryPtr = std::shared_ptr< GuildleveAssignmentCategory >;
     using GuildOrderPtr = std::shared_ptr< GuildOrder >;
     using GuildOrderGuidePtr = std::shared_ptr< GuildOrderGuide >;
     using GuildOrderOfficerPtr = std::shared_ptr< GuildOrderOfficer >;
     using HairMakeTypePtr = std::shared_ptr< HairMakeType >;
     using HouseRetainerPosePtr = std::shared_ptr< HouseRetainerPose >;
     using HousingAethernetPtr = std::shared_ptr< HousingAethernet >;
     using HousingAppealPtr = std::shared_ptr< HousingAppeal >;
     using HousingEmploymentNpcListPtr = std::shared_ptr< HousingEmploymentNpcList >;
     using HousingEmploymentNpcRacePtr = std::shared_ptr< HousingEmploymentNpcRace >;
     using HousingExteriorPtr = std::shared_ptr< HousingExterior >;
     using HousingFurniturePtr = std::shared_ptr< HousingFurniture >;
     using HousingLandSetPtr = std::shared_ptr< HousingLandSet >;
     using HousingMapMarkerInfoPtr = std::shared_ptr< HousingMapMarkerInfo >;
     using HousingMerchantPosePtr = std::shared_ptr< HousingMerchantPose >;
     using HousingPlacementPtr = std::shared_ptr< HousingPlacement >;
     using HousingPresetPtr = std::shared_ptr< HousingPreset >;
     using HousingUnitedExteriorPtr = std::shared_ptr< HousingUnitedExterior >;
     using HousingYardObjectPtr = std::shared_ptr< HousingYardObject >;
     using HowToPtr = std::shared_ptr< HowTo >;
     using HowToCategoryPtr = std::shared_ptr< HowToCategory >;
     using HowToPagePtr = std::shared_ptr< HowToPage >;
     using HugeCraftworksNpcPtr = std::shared_ptr< HugeCraftworksNpc >;
     using HugeCraftworksRankPtr = std::shared_ptr< HugeCraftworksRank >;
     using HWDAnnouncePtr = std::shared_ptr< HWDAnnounce >;
     using HWDCrafterSupplyPtr = std::shared_ptr< HWDCrafterSupply >;
     using HWDCrafterSupplyRewardPtr = std::shared_ptr< HWDCrafterSupplyReward >;
     using HWDCrafterSupplyTermPtr = std::shared_ptr< HWDCrafterSupplyTerm >;
     using HWDDevLayerControlPtr = std::shared_ptr< HWDDevLayerControl >;
     using HWDDevLevelUIPtr = std::shared_ptr< HWDDevLevelUI >;
     using HWDDevLivelyPtr = std::shared_ptr< HWDDevLively >;
     using HWDDevProgressPtr = std::shared_ptr< HWDDevProgress >;
     using HWDGathereInspectTermPtr = std::shared_ptr< HWDGathereInspectTerm >;
     using HWDGathererInspectionPtr = std::shared_ptr< HWDGathererInspection >;
     using HWDGathererInspectionRewardPtr = std::shared_ptr< HWDGathererInspectionReward >;
     using HWDInfoBoardArticlePtr = std::shared_ptr< HWDInfoBoardArticle >;
     using HWDInfoBoardArticleTransientPtr = std::shared_ptr< HWDInfoBoardArticleTransient >;
     using HWDInfoBoardArticleTypePtr = std::shared_ptr< HWDInfoBoardArticleType >;
     using HWDLevelChangeDeceptionPtr = std::shared_ptr< HWDLevelChangeDeception >;
     using HWDSharedGroupPtr = std::shared_ptr< HWDSharedGroup >;
     using HWDSharedGroupControlParamPtr = std::shared_ptr< HWDSharedGroupControlParam >;
     using IKDContentBonusPtr = std::shared_ptr< IKDContentBonus >;
     using IKDFishParamPtr = std::shared_ptr< IKDFishParam >;
     using IKDRoutePtr = std::shared_ptr< IKDRoute >;
     using IKDRouteTablePtr = std::shared_ptr< IKDRouteTable >;
     using IKDSpotPtr = std::shared_ptr< IKDSpot >;
     using InclusionShopPtr = std::shared_ptr< InclusionShop >;
     using InclusionShopCategoryPtr = std::shared_ptr< InclusionShopCategory >;
     using InclusionShopSeriesPtr = std::shared_ptr< InclusionShopSeries >;
     using IndividualWeatherPtr = std::shared_ptr< IndividualWeather >;
     using InstanceContentPtr = std::shared_ptr< InstanceContent >;
     using InstanceContentBuffPtr = std::shared_ptr< InstanceContentBuff >;
     using InstanceContentCSBonusPtr = std::shared_ptr< InstanceContentCSBonus >;
     using InstanceContentGuidePtr = std::shared_ptr< InstanceContentGuide >;
     using InstanceContentTextDataPtr = std::shared_ptr< InstanceContentTextData >;
     using ItemPtr = std::shared_ptr< Item >;
     using ItemActionPtr = std::shared_ptr< ItemAction >;
     using ItemActionTelepoPtr = std::shared_ptr< ItemActionTelepo >;
     using ItemBarterCheckPtr = std::shared_ptr< ItemBarterCheck >;
     using ItemFoodPtr = std::shared_ptr< ItemFood >;
     using ItemLevelPtr = std::shared_ptr< ItemLevel >;
     using ItemSearchCategoryPtr = std::shared_ptr< ItemSearchCategory >;
     using ItemSeriesPtr = std::shared_ptr< ItemSeries >;
     using ItemSortCategoryPtr = std::shared_ptr< ItemSortCategory >;
     using ItemSpecialBonusPtr = std::shared_ptr< ItemSpecialBonus >;
     using ItemUICategoryPtr = std::shared_ptr< ItemUICategory >;
     using JobHudManualPtr = std::shared_ptr< JobHudManual >;
     using JobHudManualPriorityPtr = std::shared_ptr< JobHudManualPriority >;
     using JournalCategoryPtr = std::shared_ptr< JournalCategory >;
     using JournalGenrePtr = std::shared_ptr< JournalGenre >;
     using JournalSectionPtr = std::shared_ptr< JournalSection >;
     using KnockbackPtr = std::shared_ptr< Knockback >;
     using LegacyQuestPtr = std::shared_ptr< LegacyQuest >;
     using LevePtr = std::shared_ptr< Leve >;
     using LeveAssignmentTypePtr = std::shared_ptr< LeveAssignmentType >;
     using LeveClientPtr = std::shared_ptr< LeveClient >;
     using LevelPtr = std::shared_ptr< Level >;
     using LeveRewardItemPtr = std::shared_ptr< LeveRewardItem >;
     using LeveRewardItemGroupPtr = std::shared_ptr< LeveRewardItemGroup >;
     using LeveStringPtr = std::shared_ptr< LeveString >;
     using LeveVfxPtr = std::shared_ptr< LeveVfx >;
     using LobbyPtr = std::shared_ptr< Lobby >;
     using LogFilterPtr = std::shared_ptr< LogFilter >;
     using LogKindPtr = std::shared_ptr< LogKind >;
     using LogMessagePtr = std::shared_ptr< LogMessage >;
     using LotteryExchangeShopPtr = std::shared_ptr< LotteryExchangeShop >;
     using MacroIconPtr = std::shared_ptr< MacroIcon >;
     using MacroIconRedirectOldPtr = std::shared_ptr< MacroIconRedirectOld >;
     using MainCommandPtr = std::shared_ptr< MainCommand >;
     using MainCommandCategoryPtr = std::shared_ptr< MainCommandCategory >;
     using ManeuversArmorPtr = std::shared_ptr< ManeuversArmor >;
     using MapPtr = std::shared_ptr< Map >;
     using MapMarkerPtr = std::shared_ptr< MapMarker >;
     using MapMarkerRegionPtr = std::shared_ptr< MapMarkerRegion >;
     using MapSymbolPtr = std::shared_ptr< MapSymbol >;
     using MarkerPtr = std::shared_ptr< Marker >;
     using MasterpieceSupplyDutyPtr = std::shared_ptr< MasterpieceSupplyDuty >;
     using MasterpieceSupplyMultiplierPtr = std::shared_ptr< MasterpieceSupplyMultiplier >;
     using MateriaPtr = std::shared_ptr< Materia >;
     using MateriaJoinRatePtr = std::shared_ptr< MateriaJoinRate >;
     using MateriaJoinRateGatherCraftPtr = std::shared_ptr< MateriaJoinRateGatherCraft >;
     using MateriaTomestoneRatePtr = std::shared_ptr< MateriaTomestoneRate >;
     using MiniGameRAPtr = std::shared_ptr< MiniGameRA >;
     using MinionRacePtr = std::shared_ptr< MinionRace >;
     using MinionRulesPtr = std::shared_ptr< MinionRules >;
     using MinionSkillTypePtr = std::shared_ptr< MinionSkillType >;
     using MobHuntOrderPtr = std::shared_ptr< MobHuntOrder >;
     using MobHuntOrderTypePtr = std::shared_ptr< MobHuntOrderType >;
     using MobHuntRewardPtr = std::shared_ptr< MobHuntReward >;
     using MobHuntRewardCapPtr = std::shared_ptr< MobHuntRewardCap >;
     using MobHuntTargetPtr = std::shared_ptr< MobHuntTarget >;
     using ModelCharaPtr = std::shared_ptr< ModelChara >;
     using ModelSkeletonPtr = std::shared_ptr< ModelSkeleton >;
     using ModelStatePtr = std::shared_ptr< ModelState >;
     using MonsterNotePtr = std::shared_ptr< MonsterNote >;
     using MonsterNoteTargetPtr = std::shared_ptr< MonsterNoteTarget >;
     using MotionTimelinePtr = std::shared_ptr< MotionTimeline >;
     using MotionTimelineBlendTablePtr = std::shared_ptr< MotionTimelineBlendTable >;
     using MountPtr = std::shared_ptr< Mount >;
     using MountActionPtr = std::shared_ptr< MountAction >;
     using MountCustomizePtr = std::shared_ptr< MountCustomize >;
     using MountFlyingConditionPtr = std::shared_ptr< MountFlyingCondition >;
     using MountSpeedPtr = std::shared_ptr< MountSpeed >;
     using MountTransientPtr = std::shared_ptr< MountTransient >;
     using MoveTimelinePtr = std::shared_ptr< MoveTimeline >;
     using MoveVfxPtr = std::shared_ptr< MoveVfx >;
     using MovieStaffListPtr = std::shared_ptr< MovieStaffList >;
     using MovieSubtitlePtr = std::shared_ptr< MovieSubtitle >;
     using MovieSubtitle500Ptr = std::shared_ptr< MovieSubtitle500 >;
     using MovieSubtitleVoyagePtr = std::shared_ptr< MovieSubtitleVoyage >;
     using MYCTemporaryItemPtr = std::shared_ptr< MYCTemporaryItem >;
     using MYCTemporaryItemUICategoryPtr = std::shared_ptr< MYCTemporaryItemUICategory >;
     using MYCWarResultNotebookPtr = std::shared_ptr< MYCWarResultNotebook >;
     using NotebookDivisionPtr = std::shared_ptr< NotebookDivision >;
     using NotebookDivisionCategoryPtr = std::shared_ptr< NotebookDivisionCategory >;
     using NotoriousMonsterPtr = std::shared_ptr< NotoriousMonster >;
     using NpcEquipPtr = std::shared_ptr< NpcEquip >;
     using NpcYellPtr = std::shared_ptr< NpcYell >;
     using OmenPtr = std::shared_ptr< Omen >;
     using OnlineStatusPtr = std::shared_ptr< OnlineStatus >;
     using OpenContentPtr = std::shared_ptr< OpenContent >;
     using OpenContentCandidateNamePtr = std::shared_ptr< OpenContentCandidateName >;
     using OpeningPtr = std::shared_ptr< Opening >;
     using OrchestrionPtr = std::shared_ptr< Orchestrion >;
     using OrchestrionCategoryPtr = std::shared_ptr< OrchestrionCategory >;
     using OrchestrionPathPtr = std::shared_ptr< OrchestrionPath >;
     using OrchestrionUiparamPtr = std::shared_ptr< OrchestrionUiparam >;
     using OrnamentPtr = std::shared_ptr< Ornament >;
     using ParamGrowPtr = std::shared_ptr< ParamGrow >;
     using PartyContentPtr = std::shared_ptr< PartyContent >;
     using PartyContentCutscenePtr = std::shared_ptr< PartyContentCutscene >;
     using PartyContentTextDataPtr = std::shared_ptr< PartyContentTextData >;
     using PatchMarkPtr = std::shared_ptr< PatchMark >;
     using PerformPtr = std::shared_ptr< Perform >;
     using PerformTransientPtr = std::shared_ptr< PerformTransient >;
     using PetPtr = std::shared_ptr< Pet >;
     using PetActionPtr = std::shared_ptr< PetAction >;
     using PhysicsGroupPtr = std::shared_ptr< PhysicsGroup >;
     using PhysicsWindPtr = std::shared_ptr< PhysicsWind >;
     using PicturePtr = std::shared_ptr< Picture >;
     using PlaceNamePtr = std::shared_ptr< PlaceName >;
     using PlantPotFlowerSeedPtr = std::shared_ptr< PlantPotFlowerSeed >;
     using PreHandlerPtr = std::shared_ptr< PreHandler >;
     using PresetCameraPtr = std::shared_ptr< PresetCamera >;
     using PresetCameraAdjustPtr = std::shared_ptr< PresetCameraAdjust >;
     using PublicContentPtr = std::shared_ptr< PublicContent >;
     using PublicContentCutscenePtr = std::shared_ptr< PublicContentCutscene >;
     using PublicContentTextDataPtr = std::shared_ptr< PublicContentTextData >;
     using PurifyPtr = std::shared_ptr< Purify >;
     using PvPActionPtr = std::shared_ptr< PvPAction >;
     using PvPActionSortPtr = std::shared_ptr< PvPActionSort >;
     using PvPRankPtr = std::shared_ptr< PvPRank >;
     using PvPSelectTraitPtr = std::shared_ptr< PvPSelectTrait >;
     using PvPTraitPtr = std::shared_ptr< PvPTrait >;
     using QuestPtr = std::shared_ptr< Quest >;
     using QuestBattlePtr = std::shared_ptr< QuestBattle >;
     using QuestChapterPtr = std::shared_ptr< QuestChapter >;
     using QuestClassJobRewardPtr = std::shared_ptr< QuestClassJobReward >;
     using QuestClassJobSupplyPtr = std::shared_ptr< QuestClassJobSupply >;
     using QuestDerivedClassPtr = std::shared_ptr< QuestDerivedClass >;
     using QuestRedoPtr = std::shared_ptr< QuestRedo >;
     using QuestRedoChapterUIPtr = std::shared_ptr< QuestRedoChapterUI >;
     using QuestRedoChapterUICategoryPtr = std::shared_ptr< QuestRedoChapterUICategory >;
     using QuestRedoChapterUITabPtr = std::shared_ptr< QuestRedoChapterUITab >;
     using QuestRedoIncompChapterPtr = std::shared_ptr< QuestRedoIncompChapter >;
     using QuestRepeatFlagPtr = std::shared_ptr< QuestRepeatFlag >;
     using QuestRewardOtherPtr = std::shared_ptr< QuestRewardOther >;
     using QuickChatPtr = std::shared_ptr< QuickChat >;
     using QuickChatTransientPtr = std::shared_ptr< QuickChatTransient >;
     using RacePtr = std::shared_ptr< Race >;
     using RacingChocoboItemPtr = std::shared_ptr< RacingChocoboItem >;
     using RacingChocoboNamePtr = std::shared_ptr< RacingChocoboName >;
     using RacingChocoboNameCategoryPtr = std::shared_ptr< RacingChocoboNameCategory >;
     using RacingChocoboNameInfoPtr = std::shared_ptr< RacingChocoboNameInfo >;
     using RacingChocoboParamPtr = std::shared_ptr< RacingChocoboParam >;
     using RecastNavimeshPtr = std::shared_ptr< RecastNavimesh >;
     using RecipePtr = std::shared_ptr< Recipe >;
     using RecipeLevelTablePtr = std::shared_ptr< RecipeLevelTable >;
     using RecipeLookupPtr = std::shared_ptr< RecipeLookup >;
     using RecipeNotebookListPtr = std::shared_ptr< RecipeNotebookList >;
     using RecommendContentsPtr = std::shared_ptr< RecommendContents >;
     using RelicPtr = std::shared_ptr< Relic >;
     using Relic3Ptr = std::shared_ptr< Relic3 >;
     using RelicItemPtr = std::shared_ptr< RelicItem >;
     using RelicNotePtr = std::shared_ptr< RelicNote >;
     using RelicNoteCategoryPtr = std::shared_ptr< RelicNoteCategory >;
     using ResidentPtr = std::shared_ptr< Resident >;
     using ResistanceWeaponAdjustPtr = std::shared_ptr< ResistanceWeaponAdjust >;
     using RetainerTaskPtr = std::shared_ptr< RetainerTask >;
     using RetainerTaskLvRangePtr = std::shared_ptr< RetainerTaskLvRange >;
     using RetainerTaskNormalPtr = std::shared_ptr< RetainerTaskNormal >;
     using RetainerTaskParameterPtr = std::shared_ptr< RetainerTaskParameter >;
     using RetainerTaskRandomPtr = std::shared_ptr< RetainerTaskRandom >;
     using RideShootingPtr = std::shared_ptr< RideShooting >;
     using RideShootingTextDataPtr = std::shared_ptr< RideShootingTextData >;
     using RPParameterPtr = std::shared_ptr< RPParameter >;
     using SatisfactionArbitrationPtr = std::shared_ptr< SatisfactionArbitration >;
     using SatisfactionNpcPtr = std::shared_ptr< SatisfactionNpc >;
     using SatisfactionSupplyPtr = std::shared_ptr< SatisfactionSupply >;
     using SatisfactionSupplyRewardPtr = std::shared_ptr< SatisfactionSupplyReward >;
     using ScenarioTreePtr = std::shared_ptr< ScenarioTree >;
     using ScenarioTreeTipsPtr = std::shared_ptr< ScenarioTreeTips >;
     using ScenarioTreeTipsClassQuestPtr = std::shared_ptr< ScenarioTreeTipsClassQuest >;
     using ScenarioTypePtr = std::shared_ptr< ScenarioType >;
     using ScreenImagePtr = std::shared_ptr< ScreenImage >;
     using SecretRecipeBookPtr = std::shared_ptr< SecretRecipeBook >;
     using SkyIsland2MissionPtr = std::shared_ptr< SkyIsland2Mission >;
     using SkyIsland2MissionDetailPtr = std::shared_ptr< SkyIsland2MissionDetail >;
     using SkyIsland2MissionTypePtr = std::shared_ptr< SkyIsland2MissionType >;
     using SkyIsland2RangeTypePtr = std::shared_ptr< SkyIsland2RangeType >;
     using SnipeTalkPtr = std::shared_ptr< SnipeTalk >;
     using SnipeTalkNamePtr = std::shared_ptr< SnipeTalkName >;
     using SpearfishingItemPtr = std::shared_ptr< SpearfishingItem >;
     using SpearfishingNotebookPtr = std::shared_ptr< SpearfishingNotebook >;
     using SpearfishingRecordPagePtr = std::shared_ptr< SpearfishingRecordPage >;
     using SpecialShopPtr = std::shared_ptr< SpecialShop >;
     using SpecialShopItemCategoryPtr = std::shared_ptr< SpecialShopItemCategory >;
     using StainPtr = std::shared_ptr< Stain >;
     using StainTransientPtr = std::shared_ptr< StainTransient >;
     using StatusPtr = std::shared_ptr< Status >;
     using StatusHitEffectPtr = std::shared_ptr< StatusHitEffect >;
     using StatusLoopVFXPtr = std::shared_ptr< StatusLoopVFX >;
     using StoryPtr = std::shared_ptr< Story >;
     using SubmarineExplorationPtr = std::shared_ptr< SubmarineExploration >;
     using SubmarineMapPtr = std::shared_ptr< SubmarineMap >;
     using SubmarinePartPtr = std::shared_ptr< SubmarinePart >;
     using SubmarineRankPtr = std::shared_ptr< SubmarineRank >;
     using SwitchTalkPtr = std::shared_ptr< SwitchTalk >;
     using SwitchTalkVariationPtr = std::shared_ptr< SwitchTalkVariation >;
     using TerritoryTypePtr = std::shared_ptr< TerritoryType >;
     using TerritoryTypeTransientPtr = std::shared_ptr< TerritoryTypeTransient >;
     using TextCommandPtr = std::shared_ptr< TextCommand >;
     using TitlePtr = std::shared_ptr< Title >;
     using TomestonesPtr = std::shared_ptr< Tomestones >;
     using TomestonesItemPtr = std::shared_ptr< TomestonesItem >;
     using TopicSelectPtr = std::shared_ptr< TopicSelect >;
     using TownPtr = std::shared_ptr< Town >;
     using TraitPtr = std::shared_ptr< Trait >;
     using TraitRecastPtr = std::shared_ptr< TraitRecast >;
     using TraitTransientPtr = std::shared_ptr< TraitTransient >;
     using TransformationPtr = std::shared_ptr< Transformation >;
     using TreasurePtr = std::shared_ptr< Treasure >;
     using TreasureHuntRankPtr = std::shared_ptr< TreasureHuntRank >;
     using TreasureModelPtr = std::shared_ptr< TreasureModel >;
     using TreasureSpotPtr = std::shared_ptr< TreasureSpot >;
     using TribePtr = std::shared_ptr< Tribe >;
     using TripleTriadPtr = std::shared_ptr< TripleTriad >;
     using TripleTriadCardPtr = std::shared_ptr< TripleTriadCard >;
     using TripleTriadCardRarityPtr = std::shared_ptr< TripleTriadCardRarity >;
     using TripleTriadCardResidentPtr = std::shared_ptr< TripleTriadCardResident >;
     using TripleTriadCardTypePtr = std::shared_ptr< TripleTriadCardType >;
     using TripleTriadCompetitionPtr = std::shared_ptr< TripleTriadCompetition >;
     using TripleTriadRulePtr = std::shared_ptr< TripleTriadRule >;
     using TutorialPtr = std::shared_ptr< Tutorial >;
     using TutorialDPSPtr = std::shared_ptr< TutorialDPS >;
     using TutorialHealerPtr = std::shared_ptr< TutorialHealer >;
     using TutorialTankPtr = std::shared_ptr< TutorialTank >;
     using UIColorPtr = std::shared_ptr< UIColor >;
     using VaseFlowerPtr = std::shared_ptr< VaseFlower >;
     using VFXPtr = std::shared_ptr< VFX >;
     using WarpPtr = std::shared_ptr< Warp >;
     using WarpConditionPtr = std::shared_ptr< WarpCondition >;
     using WarpLogicPtr = std::shared_ptr< WarpLogic >;
     using WeaponTimelinePtr = std::shared_ptr< WeaponTimeline >;
     using WeatherPtr = std::shared_ptr< Weather >;
     using WeatherGroupPtr = std::shared_ptr< WeatherGroup >;
     using WeatherRatePtr = std::shared_ptr< WeatherRate >;
     using WeatherReportReplacePtr = std::shared_ptr< WeatherReportReplace >;
     using WebGuidancePtr = std::shared_ptr< WebGuidance >;
     using WebURLPtr = std::shared_ptr< WebURL >;
     using WeddingBGMPtr = std::shared_ptr< WeddingBGM >;
     using WeeklyBingoOrderDataPtr = std::shared_ptr< WeeklyBingoOrderData >;
     using WeeklyBingoRewardDataPtr = std::shared_ptr< WeeklyBingoRewardData >;
     using WeeklyBingoTextPtr = std::shared_ptr< WeeklyBingoText >;
     using WeeklyLotBonusPtr = std::shared_ptr< WeeklyLotBonus >;
     using WorldPtr = std::shared_ptr< World >;
     using WorldDCGroupTypePtr = std::shared_ptr< WorldDCGroupType >;
     using YardCatalogCategoryPtr = std::shared_ptr< YardCatalogCategory >;
     using YardCatalogItemListPtr = std::shared_ptr< YardCatalogItemList >;
     using YKWPtr = std::shared_ptr< YKW >;
     using ZoneSharedGroupPtr = std::shared_ptr< ZoneSharedGroup >;


     std::set< uint32_t > m_AchievementIdList;
     std::set< uint32_t > m_AchievementCategoryIdList;
     std::set< uint32_t > m_AchievementHideConditionIdList;
     std::set< uint32_t > m_AchievementKindIdList;
     std::set< uint32_t > m_ActionIdList;
     std::set< uint32_t > m_ActionCastTimelineIdList;
     std::set< uint32_t > m_ActionCastVFXIdList;
     std::set< uint32_t > m_ActionCategoryIdList;
     std::set< uint32_t > m_ActionComboRouteIdList;
     std::set< uint32_t > m_ActionIndirectionIdList;
     std::set< uint32_t > m_ActionParamIdList;
     std::set< uint32_t > m_ActionProcStatusIdList;
     std::set< uint32_t > m_ActionTimelineIdList;
     std::set< uint32_t > m_ActionTimelineMoveIdList;
     std::set< uint32_t > m_ActionTimelineReplaceIdList;
     std::set< uint32_t > m_ActionTransientIdList;
     std::set< uint32_t > m_ActivityFeedButtonsIdList;
     std::set< uint32_t > m_ActivityFeedCaptionsIdList;
     std::set< uint32_t > m_ActivityFeedGroupCaptionsIdList;
     std::set< uint32_t > m_ActivityFeedImagesIdList;
     std::set< uint32_t > m_AddonIdList;
     std::set< uint32_t > m_AdventureIdList;
     std::set< uint32_t > m_AdventureExPhaseIdList;
     std::set< uint32_t > m_AetherCurrentIdList;
     std::set< uint32_t > m_AetherCurrentCompFlgSetIdList;
     std::set< uint32_t > m_AetherialWheelIdList;
     std::set< uint32_t > m_AetheryteIdList;
     std::set< uint32_t > m_AetheryteSystemDefineIdList;
     std::set< uint32_t > m_AirshipExplorationLevelIdList;
     std::set< uint32_t > m_AirshipExplorationLogIdList;
     std::set< uint32_t > m_AirshipExplorationParamTypeIdList;
     std::set< uint32_t > m_AirshipExplorationPartIdList;
     std::set< uint32_t > m_AirshipExplorationPointIdList;
     std::set< uint32_t > m_AnimationLODIdList;
     std::set< uint32_t > m_AnimaWeapon5IdList;
     std::set< uint32_t > m_AnimaWeapon5ParamIdList;
     std::set< uint32_t > m_AnimaWeapon5PatternGroupIdList;
     std::set< uint32_t > m_AnimaWeapon5SpiritTalkIdList;
     std::set< uint32_t > m_AnimaWeapon5SpiritTalkParamIdList;
     std::set< uint32_t > m_AnimaWeapon5TradeItemIdList;
     std::set< uint32_t > m_AnimaWeaponFUITalkIdList;
     std::set< uint32_t > m_AnimaWeaponFUITalkParamIdList;
     std::set< uint32_t > m_AnimaWeaponIconIdList;
     std::set< uint32_t > m_AnimaWeaponItemIdList;
     std::set< uint32_t > m_AozActionIdList;
     std::set< uint32_t > m_AozActionTransientIdList;
     std::set< uint32_t > m_AOZArrangementIdList;
     std::set< uint32_t > m_AOZBossIdList;
     std::set< uint32_t > m_AOZContentIdList;
     std::set< uint32_t > m_AOZContentBriefingBNpcIdList;
     std::set< uint32_t > m_AquariumFishIdList;
     std::set< uint32_t > m_AquariumWaterIdList;
     std::set< uint32_t > m_ArrayEventHandlerIdList;
     std::set< uint32_t > m_AttackTypeIdList;
     std::set< uint32_t > m_BacklightColorIdList;
     std::set< uint32_t > m_BallistaIdList;
     std::set< uint32_t > m_BalloonIdList;
     std::set< uint32_t > m_BaseParamIdList;
     std::set< uint32_t > m_BattleLeveIdList;
     std::set< uint32_t > m_BattleLeveRuleIdList;
     std::set< uint32_t > m_BeastRankBonusIdList;
     std::set< uint32_t > m_BeastReputationRankIdList;
     std::set< uint32_t > m_BeastTribeIdList;
     std::set< uint32_t > m_BehaviorIdList;
     std::set< uint32_t > m_BehaviorPathIdList;
     std::set< uint32_t > m_BenchmarkOverrideEquipmentIdList;
     std::set< uint32_t > m_BGMIdList;
     std::set< uint32_t > m_BGMFadeIdList;
     std::set< uint32_t > m_BGMFadeTypeIdList;
     std::set< uint32_t > m_BGMSceneIdList;
     std::set< uint32_t > m_BGMSituationIdList;
     std::set< uint32_t > m_BGMSwitchIdList;
     std::set< uint32_t > m_BGMSystemDefineIdList;
     std::set< uint32_t > m_BNpcAnnounceIconIdList;
     std::set< uint32_t > m_BNpcBaseIdList;
     std::set< uint32_t > m_BNpcCustomizeIdList;
     std::set< uint32_t > m_BNpcNameIdList;
     std::set< uint32_t > m_BNpcPartsIdList;
     std::set< uint32_t > m_BNpcStateIdList;
     std::set< uint32_t > m_BuddyIdList;
     std::set< uint32_t > m_BuddyActionIdList;
     std::set< uint32_t > m_BuddyEquipIdList;
     std::set< uint32_t > m_BuddyItemIdList;
     std::set< uint32_t > m_BuddyRankIdList;
     std::set< uint32_t > m_BuddySkillIdList;
     std::set< uint32_t > m_CabinetIdList;
     std::set< uint32_t > m_CabinetCategoryIdList;
     std::set< uint32_t > m_CalendarIdList;
     std::set< uint32_t > m_CarryIdList;
     std::set< uint32_t > m_ChannelingIdList;
     std::set< uint32_t > m_CharaMakeClassEquipIdList;
     std::set< uint32_t > m_CharaMakeCustomizeIdList;
     std::set< uint32_t > m_CharaMakeNameIdList;
     std::set< uint32_t > m_CharaMakeTypeIdList;
     std::set< uint32_t > m_ChocoboRaceIdList;
     std::set< uint32_t > m_ChocoboRaceAbilityIdList;
     std::set< uint32_t > m_ChocoboRaceAbilityTypeIdList;
     std::set< uint32_t > m_ChocoboRaceItemIdList;
     std::set< uint32_t > m_ChocoboRaceRankIdList;
     std::set< uint32_t > m_ChocoboRaceStatusIdList;
     std::set< uint32_t > m_ChocoboRaceTerritoryIdList;
     std::set< uint32_t > m_ChocoboRaceTutorialIdList;
     std::set< uint32_t > m_ChocoboRaceWeatherIdList;
     std::set< uint32_t > m_ChocoboTaxiIdList;
     std::set< uint32_t > m_ChocoboTaxiStandIdList;
     std::set< uint32_t > m_CircleActivityIdList;
     std::set< uint32_t > m_ClassJobIdList;
     std::set< uint32_t > m_ClassJobCategoryIdList;
     std::set< uint32_t > m_CollectablesShopIdList;
     std::set< uint32_t > m_CollectablesShopItemIdList;
     std::set< uint32_t > m_CollectablesShopItemGroupIdList;
     std::set< uint32_t > m_CollectablesShopRefineIdList;
     std::set< uint32_t > m_CollectablesShopRewardItemIdList;
     std::set< uint32_t > m_CollectablesShopRewardScripIdList;
     std::set< uint32_t > m_CompanionIdList;
     std::set< uint32_t > m_CompanionMoveIdList;
     std::set< uint32_t > m_CompanionTransientIdList;
     std::set< uint32_t > m_CompanyActionIdList;
     std::set< uint32_t > m_CompanyCraftDraftIdList;
     std::set< uint32_t > m_CompanyCraftDraftCategoryIdList;
     std::set< uint32_t > m_CompanyCraftManufactoryStateIdList;
     std::set< uint32_t > m_CompanyCraftPartIdList;
     std::set< uint32_t > m_CompanyCraftProcessIdList;
     std::set< uint32_t > m_CompanyCraftSequenceIdList;
     std::set< uint32_t > m_CompanyCraftSupplyItemIdList;
     std::set< uint32_t > m_CompanyCraftTypeIdList;
     std::set< uint32_t > m_CompanyLeveIdList;
     std::set< uint32_t > m_CompanyLeveRuleIdList;
     std::set< uint32_t > m_CompleteJournalIdList;
     std::set< uint32_t > m_CompleteJournalCategoryIdList;
     std::set< uint32_t > m_ConditionIdList;
     std::set< uint32_t > m_ConfigKeyIdList;
     std::set< uint32_t > m_ContentCloseCycleIdList;
     std::set< uint32_t > m_ContentExActionIdList;
     std::set< uint32_t > m_ContentFinderConditionIdList;
     std::set< uint32_t > m_ContentFinderConditionTransientIdList;
     std::set< uint32_t > m_ContentGaugeIdList;
     std::set< uint32_t > m_ContentGaugeColorIdList;
     std::set< uint32_t > m_ContentMemberTypeIdList;
     std::set< uint32_t > m_ContentNpcTalkIdList;
     std::set< uint32_t > m_ContentRandomSelectIdList;
     std::set< uint32_t > m_ContentRouletteIdList;
     std::set< uint32_t > m_ContentRouletteOpenRuleIdList;
     std::set< uint32_t > m_ContentRouletteRoleBonusIdList;
     std::set< uint32_t > m_ContentsNoteIdList;
     std::set< uint32_t > m_ContentsTutorialIdList;
     std::set< uint32_t > m_ContentsTutorialPageIdList;
     std::set< uint32_t > m_ContentTalkIdList;
     std::set< uint32_t > m_ContentTalkParamIdList;
     std::set< uint32_t > m_ContentTypeIdList;
     std::set< uint32_t > m_CraftActionIdList;
     std::set< uint32_t > m_CraftLeveIdList;
     std::set< uint32_t > m_CraftLevelDifferenceIdList;
     std::set< uint32_t > m_CraftTypeIdList;
     std::set< uint32_t > m_CreditIdList;
     std::set< uint32_t > m_CreditBackImageIdList;
     std::set< uint32_t > m_CreditCastIdList;
     std::set< uint32_t > m_CreditListIdList;
     std::set< uint32_t > m_CreditListTextIdList;
     std::set< uint32_t > m_CustomTalkIdList;
     std::set< uint32_t > m_CustomTalkDynamicIconIdList;
     std::set< uint32_t > m_CustomTalkNestHandlersIdList;
     std::set< uint32_t > m_CutsceneIdList;
     std::set< uint32_t > m_CutsceneMotionIdList;
     std::set< uint32_t > m_CutsceneWorkIndexIdList;
     std::set< uint32_t > m_CutScreenImageIdList;
     std::set< uint32_t > m_CycleTimeIdList;
     std::set< uint32_t > m_DailySupplyItemIdList;
     std::set< uint32_t > m_DawnContentIdList;
     std::set< uint32_t > m_DawnGrowMemberIdList;
     std::set< uint32_t > m_DawnMemberUIParamIdList;
     std::set< uint32_t > m_DawnQuestAnnounceIdList;
     std::set< uint32_t > m_DawnQuestMemberIdList;
     std::set< uint32_t > m_DeepDungeonIdList;
     std::set< uint32_t > m_DeepDungeonBanIdList;
     std::set< uint32_t > m_DeepDungeonDangerIdList;
     std::set< uint32_t > m_DeepDungeonEquipmentIdList;
     std::set< uint32_t > m_DeepDungeonFloorEffectUIIdList;
     std::set< uint32_t > m_DeepDungeonItemIdList;
     std::set< uint32_t > m_DeepDungeonLayerIdList;
     std::set< uint32_t > m_DeepDungeonMagicStoneIdList;
     std::set< uint32_t > m_DeepDungeonMap5XIdList;
     std::set< uint32_t > m_DeepDungeonRoomIdList;
     std::set< uint32_t > m_DeepDungeonStatusIdList;
     std::set< uint32_t > m_DefaultTalkIdList;
     std::set< uint32_t > m_DefaultTalkLipSyncTypeIdList;
     std::set< uint32_t > m_DeliveryQuestIdList;
     std::set< uint32_t > m_DescriptionIdList;
     std::set< uint32_t > m_DescriptionPageIdList;
     std::set< uint32_t > m_DescriptionSectionIdList;
     std::set< uint32_t > m_DescriptionStringIdList;
     std::set< uint32_t > m_DisposalShopIdList;
     std::set< uint32_t > m_DisposalShopFilterTypeIdList;
     std::set< uint32_t > m_DisposalShopItemIdList;
     std::set< uint32_t > m_DpsChallengeIdList;
     std::set< uint32_t > m_DpsChallengeOfficerIdList;
     std::set< uint32_t > m_DpsChallengeTransientIdList;
     std::set< uint32_t > m_DynamicEventIdList;
     std::set< uint32_t > m_DynamicEventEnemyTypeIdList;
     std::set< uint32_t > m_DynamicEventSingleBattleIdList;
     std::set< uint32_t > m_DynamicEventTypeIdList;
     std::set< uint32_t > m_EmjAddonIdList;
     std::set< uint32_t > m_EmjDaniIdList;
     std::set< uint32_t > m_EmoteIdList;
     std::set< uint32_t > m_EmoteCategoryIdList;
     std::set< uint32_t > m_EmoteModeIdList;
     std::set< uint32_t > m_ENpcBaseIdList;
     std::set< uint32_t > m_ENpcDressUpIdList;
     std::set< uint32_t > m_ENpcDressUpDressIdList;
     std::set< uint32_t > m_ENpcResidentIdList;
     std::set< uint32_t > m_EObjIdList;
     std::set< uint32_t > m_EObjNameIdList;
     std::set< uint32_t > m_EquipRaceCategoryIdList;
     std::set< uint32_t > m_EquipSlotCategoryIdList;
     std::set< uint32_t > m_EurekaAetherItemIdList;
     std::set< uint32_t > m_EurekaAethernetIdList;
     std::set< uint32_t > m_EurekaGrowDataIdList;
     std::set< uint32_t > m_EurekaLogosMixerProbabilityIdList;
     std::set< uint32_t > m_EurekaMagiaActionIdList;
     std::set< uint32_t > m_EurekaMagiciteItemIdList;
     std::set< uint32_t > m_EurekaMagiciteItemTypeIdList;
     std::set< uint32_t > m_EurekaSphereElementAdjustIdList;
     std::set< uint32_t > m_EventActionIdList;
     std::set< uint32_t > m_EventIconPriorityIdList;
     std::set< uint32_t > m_EventIconTypeIdList;
     std::set< uint32_t > m_EventItemIdList;
     std::set< uint32_t > m_EventItemCastTimelineIdList;
     std::set< uint32_t > m_EventItemHelpIdList;
     std::set< uint32_t > m_EventItemTimelineIdList;
     std::set< uint32_t > m_EventSystemDefineIdList;
     std::set< uint32_t > m_ExportedSGIdList;
     std::set< uint32_t > m_ExVersionIdList;
     std::set< uint32_t > m_FateIdList;
     std::set< uint32_t > m_FateEventIdList;
     std::set< uint32_t > m_FateModeIdList;
     std::set< uint32_t > m_FateProgressUIIdList;
     std::set< uint32_t > m_FateTokenTypeIdList;
     std::set< uint32_t > m_FCActivityIdList;
     std::set< uint32_t > m_FCActivityCategoryIdList;
     std::set< uint32_t > m_FCAuthorityIdList;
     std::set< uint32_t > m_FCAuthorityCategoryIdList;
     std::set< uint32_t > m_FCChestNameIdList;
     std::set< uint32_t > m_FCCrestSymbolIdList;
     std::set< uint32_t > m_FccShopIdList;
     std::set< uint32_t > m_FCHierarchyIdList;
     std::set< uint32_t > m_FCProfileIdList;
     std::set< uint32_t > m_FCRankIdList;
     std::set< uint32_t > m_FCReputationIdList;
     std::set< uint32_t > m_FCRightsIdList;
     std::set< uint32_t > m_FestivalIdList;
     std::set< uint32_t > m_FieldMarkerIdList;
     std::set< uint32_t > m_FishingRecordTypeIdList;
     std::set< uint32_t > m_FishingRecordTypeTransientIdList;
     std::set< uint32_t > m_FishingSpotIdList;
     std::set< uint32_t > m_FishParameterIdList;
     std::set< uint32_t > m_Frontline03IdList;
     std::set< uint32_t > m_Frontline04IdList;
     std::set< uint32_t > m_FurnitureCatalogCategoryIdList;
     std::set< uint32_t > m_FurnitureCatalogItemListIdList;
     std::set< uint32_t > m_GardeningSeedIdList;
     std::set< uint32_t > m_GatheringConditionIdList;
     std::set< uint32_t > m_GatheringExpIdList;
     std::set< uint32_t > m_GatheringItemIdList;
     std::set< uint32_t > m_GatheringItemLevelConvertTableIdList;
     std::set< uint32_t > m_GatheringItemPointIdList;
     std::set< uint32_t > m_GatheringLeveIdList;
     std::set< uint32_t > m_GatheringLeveRouteIdList;
     std::set< uint32_t > m_GatheringLeveRuleIdList;
     std::set< uint32_t > m_GatheringNotebookListIdList;
     std::set< uint32_t > m_GatheringPointIdList;
     std::set< uint32_t > m_GatheringPointBaseIdList;
     std::set< uint32_t > m_GatheringPointBonusIdList;
     std::set< uint32_t > m_GatheringPointBonusTypeIdList;
     std::set< uint32_t > m_GatheringPointNameIdList;
     std::set< uint32_t > m_GatheringPointTransientIdList;
     std::set< uint32_t > m_GatheringRarePopTimeTableIdList;
     std::set< uint32_t > m_GatheringSubCategoryIdList;
     std::set< uint32_t > m_GatheringTypeIdList;
     std::set< uint32_t > m_GcArmyCaptureTacticsIdList;
     std::set< uint32_t > m_GcArmyExpeditionIdList;
     std::set< uint32_t > m_GcArmyExpeditionMemberBonusIdList;
     std::set< uint32_t > m_GcArmyExpeditionTypeIdList;
     std::set< uint32_t > m_GcArmyMemberGrowIdList;
     std::set< uint32_t > m_GcArmyTrainingIdList;
     std::set< uint32_t > m_GCRankGridaniaFemaleTextIdList;
     std::set< uint32_t > m_GCRankGridaniaMaleTextIdList;
     std::set< uint32_t > m_GCRankLimsaFemaleTextIdList;
     std::set< uint32_t > m_GCRankLimsaMaleTextIdList;
     std::set< uint32_t > m_GCRankUldahFemaleTextIdList;
     std::set< uint32_t > m_GCRankUldahMaleTextIdList;
     std::set< uint32_t > m_GCScripShopCategoryIdList;
     std::set< uint32_t > m_GCScripShopItemIdList;
     std::set< uint32_t > m_GCShopIdList;
     std::set< uint32_t > m_GCShopItemCategoryIdList;
     std::set< uint32_t > m_GCSupplyDutyIdList;
     std::set< uint32_t > m_GCSupplyDutyRewardIdList;
     std::set< uint32_t > m_GeneralActionIdList;
     std::set< uint32_t > m_GFATEIdList;
     std::set< uint32_t > m_GFateClimbing2IdList;
     std::set< uint32_t > m_GFateClimbing2ContentIdList;
     std::set< uint32_t > m_GFateClimbing2TotemTypeIdList;
     std::set< uint32_t > m_GFateRideShootingIdList;
     std::set< uint32_t > m_GilShopIdList;
     std::set< uint32_t > m_GilShopItemIdList;
     std::set< uint32_t > m_GimmickAccessorIdList;
     std::set< uint32_t > m_GimmickJumpIdList;
     std::set< uint32_t > m_GimmickRectIdList;
     std::set< uint32_t > m_GoldSaucerArcadeMachineIdList;
     std::set< uint32_t > m_GoldSaucerTextDataIdList;
     std::set< uint32_t > m_GrandCompanyIdList;
     std::set< uint32_t > m_GrandCompanyRankIdList;
     std::set< uint32_t > m_GroupPoseFrameIdList;
     std::set< uint32_t > m_GroupPoseStampIdList;
     std::set< uint32_t > m_GroupPoseStampCategoryIdList;
     std::set< uint32_t > m_GuardianDeityIdList;
     std::set< uint32_t > m_GuideIdList;
     std::set< uint32_t > m_GuidePageIdList;
     std::set< uint32_t > m_GuidePageStringIdList;
     std::set< uint32_t > m_GuideTitleIdList;
     std::set< uint32_t > m_GuildleveAssignmentIdList;
     std::set< uint32_t > m_GuildleveAssignmentCategoryIdList;
     std::set< uint32_t > m_GuildOrderIdList;
     std::set< uint32_t > m_GuildOrderGuideIdList;
     std::set< uint32_t > m_GuildOrderOfficerIdList;
     std::set< uint32_t > m_HairMakeTypeIdList;
     std::set< uint32_t > m_HouseRetainerPoseIdList;
     std::set< uint32_t > m_HousingAethernetIdList;
     std::set< uint32_t > m_HousingAppealIdList;
     std::set< uint32_t > m_HousingEmploymentNpcListIdList;
     std::set< uint32_t > m_HousingEmploymentNpcRaceIdList;
     std::set< uint32_t > m_HousingExteriorIdList;
     std::set< uint32_t > m_HousingFurnitureIdList;
     std::set< uint32_t > m_HousingLandSetIdList;
     std::set< uint32_t > m_HousingMapMarkerInfoIdList;
     std::set< uint32_t > m_HousingMerchantPoseIdList;
     std::set< uint32_t > m_HousingPlacementIdList;
     std::set< uint32_t > m_HousingPresetIdList;
     std::set< uint32_t > m_HousingUnitedExteriorIdList;
     std::set< uint32_t > m_HousingYardObjectIdList;
     std::set< uint32_t > m_HowToIdList;
     std::set< uint32_t > m_HowToCategoryIdList;
     std::set< uint32_t > m_HowToPageIdList;
     std::set< uint32_t > m_HugeCraftworksNpcIdList;
     std::set< uint32_t > m_HugeCraftworksRankIdList;
     std::set< uint32_t > m_HWDAnnounceIdList;
     std::set< uint32_t > m_HWDCrafterSupplyIdList;
     std::set< uint32_t > m_HWDCrafterSupplyRewardIdList;
     std::set< uint32_t > m_HWDCrafterSupplyTermIdList;
     std::set< uint32_t > m_HWDDevLayerControlIdList;
     std::set< uint32_t > m_HWDDevLevelUIIdList;
     std::set< uint32_t > m_HWDDevLivelyIdList;
     std::set< uint32_t > m_HWDDevProgressIdList;
     std::set< uint32_t > m_HWDGathereInspectTermIdList;
     std::set< uint32_t > m_HWDGathererInspectionIdList;
     std::set< uint32_t > m_HWDGathererInspectionRewardIdList;
     std::set< uint32_t > m_HWDInfoBoardArticleIdList;
     std::set< uint32_t > m_HWDInfoBoardArticleTransientIdList;
     std::set< uint32_t > m_HWDInfoBoardArticleTypeIdList;
     std::set< uint32_t > m_HWDLevelChangeDeceptionIdList;
     std::set< uint32_t > m_HWDSharedGroupIdList;
     std::set< uint32_t > m_HWDSharedGroupControlParamIdList;
     std::set< uint32_t > m_IKDContentBonusIdList;
     std::set< uint32_t > m_IKDFishParamIdList;
     std::set< uint32_t > m_IKDRouteIdList;
     std::set< uint32_t > m_IKDRouteTableIdList;
     std::set< uint32_t > m_IKDSpotIdList;
     std::set< uint32_t > m_InclusionShopIdList;
     std::set< uint32_t > m_InclusionShopCategoryIdList;
     std::set< uint32_t > m_InclusionShopSeriesIdList;
     std::set< uint32_t > m_IndividualWeatherIdList;
     std::set< uint32_t > m_InstanceContentIdList;
     std::set< uint32_t > m_InstanceContentBuffIdList;
     std::set< uint32_t > m_InstanceContentCSBonusIdList;
     std::set< uint32_t > m_InstanceContentGuideIdList;
     std::set< uint32_t > m_InstanceContentTextDataIdList;
     std::set< uint32_t > m_ItemIdList;
     std::set< uint32_t > m_ItemActionIdList;
     std::set< uint32_t > m_ItemActionTelepoIdList;
     std::set< uint32_t > m_ItemBarterCheckIdList;
     std::set< uint32_t > m_ItemFoodIdList;
     std::set< uint32_t > m_ItemLevelIdList;
     std::set< uint32_t > m_ItemSearchCategoryIdList;
     std::set< uint32_t > m_ItemSeriesIdList;
     std::set< uint32_t > m_ItemSortCategoryIdList;
     std::set< uint32_t > m_ItemSpecialBonusIdList;
     std::set< uint32_t > m_ItemUICategoryIdList;
     std::set< uint32_t > m_JobHudManualIdList;
     std::set< uint32_t > m_JobHudManualPriorityIdList;
     std::set< uint32_t > m_JournalCategoryIdList;
     std::set< uint32_t > m_JournalGenreIdList;
     std::set< uint32_t > m_JournalSectionIdList;
     std::set< uint32_t > m_KnockbackIdList;
     std::set< uint32_t > m_LegacyQuestIdList;
     std::set< uint32_t > m_LeveIdList;
     std::set< uint32_t > m_LeveAssignmentTypeIdList;
     std::set< uint32_t > m_LeveClientIdList;
     std::set< uint32_t > m_LevelIdList;
     std::set< uint32_t > m_LeveRewardItemIdList;
     std::set< uint32_t > m_LeveRewardItemGroupIdList;
     std::set< uint32_t > m_LeveStringIdList;
     std::set< uint32_t > m_LeveVfxIdList;
     std::set< uint32_t > m_LobbyIdList;
     std::set< uint32_t > m_LogFilterIdList;
     std::set< uint32_t > m_LogKindIdList;
     std::set< uint32_t > m_LogMessageIdList;
     std::set< uint32_t > m_LotteryExchangeShopIdList;
     std::set< uint32_t > m_MacroIconIdList;
     std::set< uint32_t > m_MacroIconRedirectOldIdList;
     std::set< uint32_t > m_MainCommandIdList;
     std::set< uint32_t > m_MainCommandCategoryIdList;
     std::set< uint32_t > m_ManeuversArmorIdList;
     std::set< uint32_t > m_MapIdList;
     std::set< uint32_t > m_MapMarkerIdList;
     std::set< uint32_t > m_MapMarkerRegionIdList;
     std::set< uint32_t > m_MapSymbolIdList;
     std::set< uint32_t > m_MarkerIdList;
     std::set< uint32_t > m_MasterpieceSupplyDutyIdList;
     std::set< uint32_t > m_MasterpieceSupplyMultiplierIdList;
     std::set< uint32_t > m_MateriaIdList;
     std::set< uint32_t > m_MateriaJoinRateIdList;
     std::set< uint32_t > m_MateriaJoinRateGatherCraftIdList;
     std::set< uint32_t > m_MateriaTomestoneRateIdList;
     std::set< uint32_t > m_MiniGameRAIdList;
     std::set< uint32_t > m_MinionRaceIdList;
     std::set< uint32_t > m_MinionRulesIdList;
     std::set< uint32_t > m_MinionSkillTypeIdList;
     std::set< uint32_t > m_MobHuntOrderIdList;
     std::set< uint32_t > m_MobHuntOrderTypeIdList;
     std::set< uint32_t > m_MobHuntRewardIdList;
     std::set< uint32_t > m_MobHuntRewardCapIdList;
     std::set< uint32_t > m_MobHuntTargetIdList;
     std::set< uint32_t > m_ModelCharaIdList;
     std::set< uint32_t > m_ModelSkeletonIdList;
     std::set< uint32_t > m_ModelStateIdList;
     std::set< uint32_t > m_MonsterNoteIdList;
     std::set< uint32_t > m_MonsterNoteTargetIdList;
     std::set< uint32_t > m_MotionTimelineIdList;
     std::set< uint32_t > m_MotionTimelineBlendTableIdList;
     std::set< uint32_t > m_MountIdList;
     std::set< uint32_t > m_MountActionIdList;
     std::set< uint32_t > m_MountCustomizeIdList;
     std::set< uint32_t > m_MountFlyingConditionIdList;
     std::set< uint32_t > m_MountSpeedIdList;
     std::set< uint32_t > m_MountTransientIdList;
     std::set< uint32_t > m_MoveTimelineIdList;
     std::set< uint32_t > m_MoveVfxIdList;
     std::set< uint32_t > m_MovieStaffListIdList;
     std::set< uint32_t > m_MovieSubtitleIdList;
     std::set< uint32_t > m_MovieSubtitle500IdList;
     std::set< uint32_t > m_MovieSubtitleVoyageIdList;
     std::set< uint32_t > m_MYCTemporaryItemIdList;
     std::set< uint32_t > m_MYCTemporaryItemUICategoryIdList;
     std::set< uint32_t > m_MYCWarResultNotebookIdList;
     std::set< uint32_t > m_NotebookDivisionIdList;
     std::set< uint32_t > m_NotebookDivisionCategoryIdList;
     std::set< uint32_t > m_NotoriousMonsterIdList;
     std::set< uint32_t > m_NpcEquipIdList;
     std::set< uint32_t > m_NpcYellIdList;
     std::set< uint32_t > m_OmenIdList;
     std::set< uint32_t > m_OnlineStatusIdList;
     std::set< uint32_t > m_OpenContentIdList;
     std::set< uint32_t > m_OpenContentCandidateNameIdList;
     std::set< uint32_t > m_OpeningIdList;
     std::set< uint32_t > m_OrchestrionIdList;
     std::set< uint32_t > m_OrchestrionCategoryIdList;
     std::set< uint32_t > m_OrchestrionPathIdList;
     std::set< uint32_t > m_OrchestrionUiparamIdList;
     std::set< uint32_t > m_OrnamentIdList;
     std::set< uint32_t > m_ParamGrowIdList;
     std::set< uint32_t > m_PartyContentIdList;
     std::set< uint32_t > m_PartyContentCutsceneIdList;
     std::set< uint32_t > m_PartyContentTextDataIdList;
     std::set< uint32_t > m_PatchMarkIdList;
     std::set< uint32_t > m_PerformIdList;
     std::set< uint32_t > m_PerformTransientIdList;
     std::set< uint32_t > m_PetIdList;
     std::set< uint32_t > m_PetActionIdList;
     std::set< uint32_t > m_PhysicsGroupIdList;
     std::set< uint32_t > m_PhysicsWindIdList;
     std::set< uint32_t > m_PictureIdList;
     std::set< uint32_t > m_PlaceNameIdList;
     std::set< uint32_t > m_PlantPotFlowerSeedIdList;
     std::set< uint32_t > m_PreHandlerIdList;
     std::set< uint32_t > m_PresetCameraIdList;
     std::set< uint32_t > m_PresetCameraAdjustIdList;
     std::set< uint32_t > m_PublicContentIdList;
     std::set< uint32_t > m_PublicContentCutsceneIdList;
     std::set< uint32_t > m_PublicContentTextDataIdList;
     std::set< uint32_t > m_PurifyIdList;
     std::set< uint32_t > m_PvPActionIdList;
     std::set< uint32_t > m_PvPActionSortIdList;
     std::set< uint32_t > m_PvPRankIdList;
     std::set< uint32_t > m_PvPSelectTraitIdList;
     std::set< uint32_t > m_PvPTraitIdList;
     std::set< uint32_t > m_QuestIdList;
     std::set< uint32_t > m_QuestBattleIdList;
     std::set< uint32_t > m_QuestChapterIdList;
     std::set< uint32_t > m_QuestClassJobRewardIdList;
     std::set< uint32_t > m_QuestClassJobSupplyIdList;
     std::set< uint32_t > m_QuestDerivedClassIdList;
     std::set< uint32_t > m_QuestRedoIdList;
     std::set< uint32_t > m_QuestRedoChapterUIIdList;
     std::set< uint32_t > m_QuestRedoChapterUICategoryIdList;
     std::set< uint32_t > m_QuestRedoChapterUITabIdList;
     std::set< uint32_t > m_QuestRedoIncompChapterIdList;
     std::set< uint32_t > m_QuestRepeatFlagIdList;
     std::set< uint32_t > m_QuestRewardOtherIdList;
     std::set< uint32_t > m_QuickChatIdList;
     std::set< uint32_t > m_QuickChatTransientIdList;
     std::set< uint32_t > m_RaceIdList;
     std::set< uint32_t > m_RacingChocoboItemIdList;
     std::set< uint32_t > m_RacingChocoboNameIdList;
     std::set< uint32_t > m_RacingChocoboNameCategoryIdList;
     std::set< uint32_t > m_RacingChocoboNameInfoIdList;
     std::set< uint32_t > m_RacingChocoboParamIdList;
     std::set< uint32_t > m_RecastNavimeshIdList;
     std::set< uint32_t > m_RecipeIdList;
     std::set< uint32_t > m_RecipeLevelTableIdList;
     std::set< uint32_t > m_RecipeLookupIdList;
     std::set< uint32_t > m_RecipeNotebookListIdList;
     std::set< uint32_t > m_RecommendContentsIdList;
     std::set< uint32_t > m_RelicIdList;
     std::set< uint32_t > m_Relic3IdList;
     std::set< uint32_t > m_RelicItemIdList;
     std::set< uint32_t > m_RelicNoteIdList;
     std::set< uint32_t > m_RelicNoteCategoryIdList;
     std::set< uint32_t > m_ResidentIdList;
     std::set< uint32_t > m_ResistanceWeaponAdjustIdList;
     std::set< uint32_t > m_RetainerTaskIdList;
     std::set< uint32_t > m_RetainerTaskLvRangeIdList;
     std::set< uint32_t > m_RetainerTaskNormalIdList;
     std::set< uint32_t > m_RetainerTaskParameterIdList;
     std::set< uint32_t > m_RetainerTaskRandomIdList;
     std::set< uint32_t > m_RideShootingIdList;
     std::set< uint32_t > m_RideShootingTextDataIdList;
     std::set< uint32_t > m_RPParameterIdList;
     std::set< uint32_t > m_SatisfactionArbitrationIdList;
     std::set< uint32_t > m_SatisfactionNpcIdList;
     std::set< uint32_t > m_SatisfactionSupplyIdList;
     std::set< uint32_t > m_SatisfactionSupplyRewardIdList;
     std::set< uint32_t > m_ScenarioTreeIdList;
     std::set< uint32_t > m_ScenarioTreeTipsIdList;
     std::set< uint32_t > m_ScenarioTreeTipsClassQuestIdList;
     std::set< uint32_t > m_ScenarioTypeIdList;
     std::set< uint32_t > m_ScreenImageIdList;
     std::set< uint32_t > m_SecretRecipeBookIdList;
     std::set< uint32_t > m_SkyIsland2MissionIdList;
     std::set< uint32_t > m_SkyIsland2MissionDetailIdList;
     std::set< uint32_t > m_SkyIsland2MissionTypeIdList;
     std::set< uint32_t > m_SkyIsland2RangeTypeIdList;
     std::set< uint32_t > m_SnipeTalkIdList;
     std::set< uint32_t > m_SnipeTalkNameIdList;
     std::set< uint32_t > m_SpearfishingItemIdList;
     std::set< uint32_t > m_SpearfishingNotebookIdList;
     std::set< uint32_t > m_SpearfishingRecordPageIdList;
     std::set< uint32_t > m_SpecialShopIdList;
     std::set< uint32_t > m_SpecialShopItemCategoryIdList;
     std::set< uint32_t > m_StainIdList;
     std::set< uint32_t > m_StainTransientIdList;
     std::set< uint32_t > m_StatusIdList;
     std::set< uint32_t > m_StatusHitEffectIdList;
     std::set< uint32_t > m_StatusLoopVFXIdList;
     std::set< uint32_t > m_StoryIdList;
     std::set< uint32_t > m_SubmarineExplorationIdList;
     std::set< uint32_t > m_SubmarineMapIdList;
     std::set< uint32_t > m_SubmarinePartIdList;
     std::set< uint32_t > m_SubmarineRankIdList;
     std::set< uint32_t > m_SwitchTalkIdList;
     std::set< uint32_t > m_SwitchTalkVariationIdList;
     std::set< uint32_t > m_TerritoryTypeIdList;
     std::set< uint32_t > m_TerritoryTypeTransientIdList;
     std::set< uint32_t > m_TextCommandIdList;
     std::set< uint32_t > m_TitleIdList;
     std::set< uint32_t > m_TomestonesIdList;
     std::set< uint32_t > m_TomestonesItemIdList;
     std::set< uint32_t > m_TopicSelectIdList;
     std::set< uint32_t > m_TownIdList;
     std::set< uint32_t > m_TraitIdList;
     std::set< uint32_t > m_TraitRecastIdList;
     std::set< uint32_t > m_TraitTransientIdList;
     std::set< uint32_t > m_TransformationIdList;
     std::set< uint32_t > m_TreasureIdList;
     std::set< uint32_t > m_TreasureHuntRankIdList;
     std::set< uint32_t > m_TreasureModelIdList;
     std::set< uint32_t > m_TreasureSpotIdList;
     std::set< uint32_t > m_TribeIdList;
     std::set< uint32_t > m_TripleTriadIdList;
     std::set< uint32_t > m_TripleTriadCardIdList;
     std::set< uint32_t > m_TripleTriadCardRarityIdList;
     std::set< uint32_t > m_TripleTriadCardResidentIdList;
     std::set< uint32_t > m_TripleTriadCardTypeIdList;
     std::set< uint32_t > m_TripleTriadCompetitionIdList;
     std::set< uint32_t > m_TripleTriadRuleIdList;
     std::set< uint32_t > m_TutorialIdList;
     std::set< uint32_t > m_TutorialDPSIdList;
     std::set< uint32_t > m_TutorialHealerIdList;
     std::set< uint32_t > m_TutorialTankIdList;
     std::set< uint32_t > m_UIColorIdList;
     std::set< uint32_t > m_VaseFlowerIdList;
     std::set< uint32_t > m_VFXIdList;
     std::set< uint32_t > m_WarpIdList;
     std::set< uint32_t > m_WarpConditionIdList;
     std::set< uint32_t > m_WarpLogicIdList;
     std::set< uint32_t > m_WeaponTimelineIdList;
     std::set< uint32_t > m_WeatherIdList;
     std::set< uint32_t > m_WeatherGroupIdList;
     std::set< uint32_t > m_WeatherRateIdList;
     std::set< uint32_t > m_WeatherReportReplaceIdList;
     std::set< uint32_t > m_WebGuidanceIdList;
     std::set< uint32_t > m_WebURLIdList;
     std::set< uint32_t > m_WeddingBGMIdList;
     std::set< uint32_t > m_WeeklyBingoOrderDataIdList;
     std::set< uint32_t > m_WeeklyBingoRewardDataIdList;
     std::set< uint32_t > m_WeeklyBingoTextIdList;
     std::set< uint32_t > m_WeeklyLotBonusIdList;
     std::set< uint32_t > m_WorldIdList;
     std::set< uint32_t > m_WorldDCGroupTypeIdList;
     std::set< uint32_t > m_YardCatalogCategoryIdList;
     std::set< uint32_t > m_YardCatalogItemListIdList;
     std::set< uint32_t > m_YKWIdList;
     std::set< uint32_t > m_ZoneSharedGroupIdList;


const std::set< uint32_t >& getAchievementIdList()
{
   if( m_AchievementIdList.size() == 0 )
      loadIdList( m_AchievementDat, m_AchievementIdList );
   return m_AchievementIdList;
}
const std::set< uint32_t >& getAchievementCategoryIdList()
{
   if( m_AchievementCategoryIdList.size() == 0 )
      loadIdList( m_AchievementCategoryDat, m_AchievementCategoryIdList );
   return m_AchievementCategoryIdList;
}
const std::set< uint32_t >& getAchievementHideConditionIdList()
{
   if( m_AchievementHideConditionIdList.size() == 0 )
      loadIdList( m_AchievementHideConditionDat, m_AchievementHideConditionIdList );
   return m_AchievementHideConditionIdList;
}
const std::set< uint32_t >& getAchievementKindIdList()
{
   if( m_AchievementKindIdList.size() == 0 )
      loadIdList( m_AchievementKindDat, m_AchievementKindIdList );
   return m_AchievementKindIdList;
}
const std::set< uint32_t >& getActionIdList()
{
   if( m_ActionIdList.size() == 0 )
      loadIdList( m_ActionDat, m_ActionIdList );
   return m_ActionIdList;
}
const std::set< uint32_t >& getActionCastTimelineIdList()
{
   if( m_ActionCastTimelineIdList.size() == 0 )
      loadIdList( m_ActionCastTimelineDat, m_ActionCastTimelineIdList );
   return m_ActionCastTimelineIdList;
}
const std::set< uint32_t >& getActionCastVFXIdList()
{
   if( m_ActionCastVFXIdList.size() == 0 )
      loadIdList( m_ActionCastVFXDat, m_ActionCastVFXIdList );
   return m_ActionCastVFXIdList;
}
const std::set< uint32_t >& getActionCategoryIdList()
{
   if( m_ActionCategoryIdList.size() == 0 )
      loadIdList( m_ActionCategoryDat, m_ActionCategoryIdList );
   return m_ActionCategoryIdList;
}
const std::set< uint32_t >& getActionComboRouteIdList()
{
   if( m_ActionComboRouteIdList.size() == 0 )
      loadIdList( m_ActionComboRouteDat, m_ActionComboRouteIdList );
   return m_ActionComboRouteIdList;
}
const std::set< uint32_t >& getActionIndirectionIdList()
{
   if( m_ActionIndirectionIdList.size() == 0 )
      loadIdList( m_ActionIndirectionDat, m_ActionIndirectionIdList );
   return m_ActionIndirectionIdList;
}
const std::set< uint32_t >& getActionParamIdList()
{
   if( m_ActionParamIdList.size() == 0 )
      loadIdList( m_ActionParamDat, m_ActionParamIdList );
   return m_ActionParamIdList;
}
const std::set< uint32_t >& getActionProcStatusIdList()
{
   if( m_ActionProcStatusIdList.size() == 0 )
      loadIdList( m_ActionProcStatusDat, m_ActionProcStatusIdList );
   return m_ActionProcStatusIdList;
}
const std::set< uint32_t >& getActionTimelineIdList()
{
   if( m_ActionTimelineIdList.size() == 0 )
      loadIdList( m_ActionTimelineDat, m_ActionTimelineIdList );
   return m_ActionTimelineIdList;
}
const std::set< uint32_t >& getActionTimelineMoveIdList()
{
   if( m_ActionTimelineMoveIdList.size() == 0 )
      loadIdList( m_ActionTimelineMoveDat, m_ActionTimelineMoveIdList );
   return m_ActionTimelineMoveIdList;
}
const std::set< uint32_t >& getActionTimelineReplaceIdList()
{
   if( m_ActionTimelineReplaceIdList.size() == 0 )
      loadIdList( m_ActionTimelineReplaceDat, m_ActionTimelineReplaceIdList );
   return m_ActionTimelineReplaceIdList;
}
const std::set< uint32_t >& getActionTransientIdList()
{
   if( m_ActionTransientIdList.size() == 0 )
      loadIdList( m_ActionTransientDat, m_ActionTransientIdList );
   return m_ActionTransientIdList;
}
const std::set< uint32_t >& getActivityFeedButtonsIdList()
{
   if( m_ActivityFeedButtonsIdList.size() == 0 )
      loadIdList( m_ActivityFeedButtonsDat, m_ActivityFeedButtonsIdList );
   return m_ActivityFeedButtonsIdList;
}
const std::set< uint32_t >& getActivityFeedCaptionsIdList()
{
   if( m_ActivityFeedCaptionsIdList.size() == 0 )
      loadIdList( m_ActivityFeedCaptionsDat, m_ActivityFeedCaptionsIdList );
   return m_ActivityFeedCaptionsIdList;
}
const std::set< uint32_t >& getActivityFeedGroupCaptionsIdList()
{
   if( m_ActivityFeedGroupCaptionsIdList.size() == 0 )
      loadIdList( m_ActivityFeedGroupCaptionsDat, m_ActivityFeedGroupCaptionsIdList );
   return m_ActivityFeedGroupCaptionsIdList;
}
const std::set< uint32_t >& getActivityFeedImagesIdList()
{
   if( m_ActivityFeedImagesIdList.size() == 0 )
      loadIdList( m_ActivityFeedImagesDat, m_ActivityFeedImagesIdList );
   return m_ActivityFeedImagesIdList;
}
const std::set< uint32_t >& getAddonIdList()
{
   if( m_AddonIdList.size() == 0 )
      loadIdList( m_AddonDat, m_AddonIdList );
   return m_AddonIdList;
}
const std::set< uint32_t >& getAdventureIdList()
{
   if( m_AdventureIdList.size() == 0 )
      loadIdList( m_AdventureDat, m_AdventureIdList );
   return m_AdventureIdList;
}
const std::set< uint32_t >& getAdventureExPhaseIdList()
{
   if( m_AdventureExPhaseIdList.size() == 0 )
      loadIdList( m_AdventureExPhaseDat, m_AdventureExPhaseIdList );
   return m_AdventureExPhaseIdList;
}
const std::set< uint32_t >& getAetherCurrentIdList()
{
   if( m_AetherCurrentIdList.size() == 0 )
      loadIdList( m_AetherCurrentDat, m_AetherCurrentIdList );
   return m_AetherCurrentIdList;
}
const std::set< uint32_t >& getAetherCurrentCompFlgSetIdList()
{
   if( m_AetherCurrentCompFlgSetIdList.size() == 0 )
      loadIdList( m_AetherCurrentCompFlgSetDat, m_AetherCurrentCompFlgSetIdList );
   return m_AetherCurrentCompFlgSetIdList;
}
const std::set< uint32_t >& getAetherialWheelIdList()
{
   if( m_AetherialWheelIdList.size() == 0 )
      loadIdList( m_AetherialWheelDat, m_AetherialWheelIdList );
   return m_AetherialWheelIdList;
}
const std::set< uint32_t >& getAetheryteIdList()
{
   if( m_AetheryteIdList.size() == 0 )
      loadIdList( m_AetheryteDat, m_AetheryteIdList );
   return m_AetheryteIdList;
}
const std::set< uint32_t >& getAetheryteSystemDefineIdList()
{
   if( m_AetheryteSystemDefineIdList.size() == 0 )
      loadIdList( m_AetheryteSystemDefineDat, m_AetheryteSystemDefineIdList );
   return m_AetheryteSystemDefineIdList;
}
const std::set< uint32_t >& getAirshipExplorationLevelIdList()
{
   if( m_AirshipExplorationLevelIdList.size() == 0 )
      loadIdList( m_AirshipExplorationLevelDat, m_AirshipExplorationLevelIdList );
   return m_AirshipExplorationLevelIdList;
}
const std::set< uint32_t >& getAirshipExplorationLogIdList()
{
   if( m_AirshipExplorationLogIdList.size() == 0 )
      loadIdList( m_AirshipExplorationLogDat, m_AirshipExplorationLogIdList );
   return m_AirshipExplorationLogIdList;
}
const std::set< uint32_t >& getAirshipExplorationParamTypeIdList()
{
   if( m_AirshipExplorationParamTypeIdList.size() == 0 )
      loadIdList( m_AirshipExplorationParamTypeDat, m_AirshipExplorationParamTypeIdList );
   return m_AirshipExplorationParamTypeIdList;
}
const std::set< uint32_t >& getAirshipExplorationPartIdList()
{
   if( m_AirshipExplorationPartIdList.size() == 0 )
      loadIdList( m_AirshipExplorationPartDat, m_AirshipExplorationPartIdList );
   return m_AirshipExplorationPartIdList;
}
const std::set< uint32_t >& getAirshipExplorationPointIdList()
{
   if( m_AirshipExplorationPointIdList.size() == 0 )
      loadIdList( m_AirshipExplorationPointDat, m_AirshipExplorationPointIdList );
   return m_AirshipExplorationPointIdList;
}
const std::set< uint32_t >& getAnimationLODIdList()
{
   if( m_AnimationLODIdList.size() == 0 )
      loadIdList( m_AnimationLODDat, m_AnimationLODIdList );
   return m_AnimationLODIdList;
}
const std::set< uint32_t >& getAnimaWeapon5IdList()
{
   if( m_AnimaWeapon5IdList.size() == 0 )
      loadIdList( m_AnimaWeapon5Dat, m_AnimaWeapon5IdList );
   return m_AnimaWeapon5IdList;
}
const std::set< uint32_t >& getAnimaWeapon5ParamIdList()
{
   if( m_AnimaWeapon5ParamIdList.size() == 0 )
      loadIdList( m_AnimaWeapon5ParamDat, m_AnimaWeapon5ParamIdList );
   return m_AnimaWeapon5ParamIdList;
}
const std::set< uint32_t >& getAnimaWeapon5PatternGroupIdList()
{
   if( m_AnimaWeapon5PatternGroupIdList.size() == 0 )
      loadIdList( m_AnimaWeapon5PatternGroupDat, m_AnimaWeapon5PatternGroupIdList );
   return m_AnimaWeapon5PatternGroupIdList;
}
const std::set< uint32_t >& getAnimaWeapon5SpiritTalkIdList()
{
   if( m_AnimaWeapon5SpiritTalkIdList.size() == 0 )
      loadIdList( m_AnimaWeapon5SpiritTalkDat, m_AnimaWeapon5SpiritTalkIdList );
   return m_AnimaWeapon5SpiritTalkIdList;
}
const std::set< uint32_t >& getAnimaWeapon5SpiritTalkParamIdList()
{
   if( m_AnimaWeapon5SpiritTalkParamIdList.size() == 0 )
      loadIdList( m_AnimaWeapon5SpiritTalkParamDat, m_AnimaWeapon5SpiritTalkParamIdList );
   return m_AnimaWeapon5SpiritTalkParamIdList;
}
const std::set< uint32_t >& getAnimaWeapon5TradeItemIdList()
{
   if( m_AnimaWeapon5TradeItemIdList.size() == 0 )
      loadIdList( m_AnimaWeapon5TradeItemDat, m_AnimaWeapon5TradeItemIdList );
   return m_AnimaWeapon5TradeItemIdList;
}
const std::set< uint32_t >& getAnimaWeaponFUITalkIdList()
{
   if( m_AnimaWeaponFUITalkIdList.size() == 0 )
      loadIdList( m_AnimaWeaponFUITalkDat, m_AnimaWeaponFUITalkIdList );
   return m_AnimaWeaponFUITalkIdList;
}
const std::set< uint32_t >& getAnimaWeaponFUITalkParamIdList()
{
   if( m_AnimaWeaponFUITalkParamIdList.size() == 0 )
      loadIdList( m_AnimaWeaponFUITalkParamDat, m_AnimaWeaponFUITalkParamIdList );
   return m_AnimaWeaponFUITalkParamIdList;
}
const std::set< uint32_t >& getAnimaWeaponIconIdList()
{
   if( m_AnimaWeaponIconIdList.size() == 0 )
      loadIdList( m_AnimaWeaponIconDat, m_AnimaWeaponIconIdList );
   return m_AnimaWeaponIconIdList;
}
const std::set< uint32_t >& getAnimaWeaponItemIdList()
{
   if( m_AnimaWeaponItemIdList.size() == 0 )
      loadIdList( m_AnimaWeaponItemDat, m_AnimaWeaponItemIdList );
   return m_AnimaWeaponItemIdList;
}
const std::set< uint32_t >& getAozActionIdList()
{
   if( m_AozActionIdList.size() == 0 )
      loadIdList( m_AozActionDat, m_AozActionIdList );
   return m_AozActionIdList;
}
const std::set< uint32_t >& getAozActionTransientIdList()
{
   if( m_AozActionTransientIdList.size() == 0 )
      loadIdList( m_AozActionTransientDat, m_AozActionTransientIdList );
   return m_AozActionTransientIdList;
}
const std::set< uint32_t >& getAOZArrangementIdList()
{
   if( m_AOZArrangementIdList.size() == 0 )
      loadIdList( m_AOZArrangementDat, m_AOZArrangementIdList );
   return m_AOZArrangementIdList;
}
const std::set< uint32_t >& getAOZBossIdList()
{
   if( m_AOZBossIdList.size() == 0 )
      loadIdList( m_AOZBossDat, m_AOZBossIdList );
   return m_AOZBossIdList;
}
const std::set< uint32_t >& getAOZContentIdList()
{
   if( m_AOZContentIdList.size() == 0 )
      loadIdList( m_AOZContentDat, m_AOZContentIdList );
   return m_AOZContentIdList;
}
const std::set< uint32_t >& getAOZContentBriefingBNpcIdList()
{
   if( m_AOZContentBriefingBNpcIdList.size() == 0 )
      loadIdList( m_AOZContentBriefingBNpcDat, m_AOZContentBriefingBNpcIdList );
   return m_AOZContentBriefingBNpcIdList;
}
const std::set< uint32_t >& getAquariumFishIdList()
{
   if( m_AquariumFishIdList.size() == 0 )
      loadIdList( m_AquariumFishDat, m_AquariumFishIdList );
   return m_AquariumFishIdList;
}
const std::set< uint32_t >& getAquariumWaterIdList()
{
   if( m_AquariumWaterIdList.size() == 0 )
      loadIdList( m_AquariumWaterDat, m_AquariumWaterIdList );
   return m_AquariumWaterIdList;
}
const std::set< uint32_t >& getArrayEventHandlerIdList()
{
   if( m_ArrayEventHandlerIdList.size() == 0 )
      loadIdList( m_ArrayEventHandlerDat, m_ArrayEventHandlerIdList );
   return m_ArrayEventHandlerIdList;
}
const std::set< uint32_t >& getAttackTypeIdList()
{
   if( m_AttackTypeIdList.size() == 0 )
      loadIdList( m_AttackTypeDat, m_AttackTypeIdList );
   return m_AttackTypeIdList;
}
const std::set< uint32_t >& getBacklightColorIdList()
{
   if( m_BacklightColorIdList.size() == 0 )
      loadIdList( m_BacklightColorDat, m_BacklightColorIdList );
   return m_BacklightColorIdList;
}
const std::set< uint32_t >& getBallistaIdList()
{
   if( m_BallistaIdList.size() == 0 )
      loadIdList( m_BallistaDat, m_BallistaIdList );
   return m_BallistaIdList;
}
const std::set< uint32_t >& getBalloonIdList()
{
   if( m_BalloonIdList.size() == 0 )
      loadIdList( m_BalloonDat, m_BalloonIdList );
   return m_BalloonIdList;
}
const std::set< uint32_t >& getBaseParamIdList()
{
   if( m_BaseParamIdList.size() == 0 )
      loadIdList( m_BaseParamDat, m_BaseParamIdList );
   return m_BaseParamIdList;
}
const std::set< uint32_t >& getBattleLeveIdList()
{
   if( m_BattleLeveIdList.size() == 0 )
      loadIdList( m_BattleLeveDat, m_BattleLeveIdList );
   return m_BattleLeveIdList;
}
const std::set< uint32_t >& getBattleLeveRuleIdList()
{
   if( m_BattleLeveRuleIdList.size() == 0 )
      loadIdList( m_BattleLeveRuleDat, m_BattleLeveRuleIdList );
   return m_BattleLeveRuleIdList;
}
const std::set< uint32_t >& getBeastRankBonusIdList()
{
   if( m_BeastRankBonusIdList.size() == 0 )
      loadIdList( m_BeastRankBonusDat, m_BeastRankBonusIdList );
   return m_BeastRankBonusIdList;
}
const std::set< uint32_t >& getBeastReputationRankIdList()
{
   if( m_BeastReputationRankIdList.size() == 0 )
      loadIdList( m_BeastReputationRankDat, m_BeastReputationRankIdList );
   return m_BeastReputationRankIdList;
}
const std::set< uint32_t >& getBeastTribeIdList()
{
   if( m_BeastTribeIdList.size() == 0 )
      loadIdList( m_BeastTribeDat, m_BeastTribeIdList );
   return m_BeastTribeIdList;
}
const std::set< uint32_t >& getBehaviorIdList()
{
   if( m_BehaviorIdList.size() == 0 )
      loadIdList( m_BehaviorDat, m_BehaviorIdList );
   return m_BehaviorIdList;
}
const std::set< uint32_t >& getBehaviorPathIdList()
{
   if( m_BehaviorPathIdList.size() == 0 )
      loadIdList( m_BehaviorPathDat, m_BehaviorPathIdList );
   return m_BehaviorPathIdList;
}
const std::set< uint32_t >& getBenchmarkOverrideEquipmentIdList()
{
   if( m_BenchmarkOverrideEquipmentIdList.size() == 0 )
      loadIdList( m_BenchmarkOverrideEquipmentDat, m_BenchmarkOverrideEquipmentIdList );
   return m_BenchmarkOverrideEquipmentIdList;
}
const std::set< uint32_t >& getBGMIdList()
{
   if( m_BGMIdList.size() == 0 )
      loadIdList( m_BGMDat, m_BGMIdList );
   return m_BGMIdList;
}
const std::set< uint32_t >& getBGMFadeIdList()
{
   if( m_BGMFadeIdList.size() == 0 )
      loadIdList( m_BGMFadeDat, m_BGMFadeIdList );
   return m_BGMFadeIdList;
}
const std::set< uint32_t >& getBGMFadeTypeIdList()
{
   if( m_BGMFadeTypeIdList.size() == 0 )
      loadIdList( m_BGMFadeTypeDat, m_BGMFadeTypeIdList );
   return m_BGMFadeTypeIdList;
}
const std::set< uint32_t >& getBGMSceneIdList()
{
   if( m_BGMSceneIdList.size() == 0 )
      loadIdList( m_BGMSceneDat, m_BGMSceneIdList );
   return m_BGMSceneIdList;
}
const std::set< uint32_t >& getBGMSituationIdList()
{
   if( m_BGMSituationIdList.size() == 0 )
      loadIdList( m_BGMSituationDat, m_BGMSituationIdList );
   return m_BGMSituationIdList;
}
const std::set< uint32_t >& getBGMSwitchIdList()
{
   if( m_BGMSwitchIdList.size() == 0 )
      loadIdList( m_BGMSwitchDat, m_BGMSwitchIdList );
   return m_BGMSwitchIdList;
}
const std::set< uint32_t >& getBGMSystemDefineIdList()
{
   if( m_BGMSystemDefineIdList.size() == 0 )
      loadIdList( m_BGMSystemDefineDat, m_BGMSystemDefineIdList );
   return m_BGMSystemDefineIdList;
}
const std::set< uint32_t >& getBNpcAnnounceIconIdList()
{
   if( m_BNpcAnnounceIconIdList.size() == 0 )
      loadIdList( m_BNpcAnnounceIconDat, m_BNpcAnnounceIconIdList );
   return m_BNpcAnnounceIconIdList;
}
const std::set< uint32_t >& getBNpcBaseIdList()
{
   if( m_BNpcBaseIdList.size() == 0 )
      loadIdList( m_BNpcBaseDat, m_BNpcBaseIdList );
   return m_BNpcBaseIdList;
}
const std::set< uint32_t >& getBNpcCustomizeIdList()
{
   if( m_BNpcCustomizeIdList.size() == 0 )
      loadIdList( m_BNpcCustomizeDat, m_BNpcCustomizeIdList );
   return m_BNpcCustomizeIdList;
}
const std::set< uint32_t >& getBNpcNameIdList()
{
   if( m_BNpcNameIdList.size() == 0 )
      loadIdList( m_BNpcNameDat, m_BNpcNameIdList );
   return m_BNpcNameIdList;
}
const std::set< uint32_t >& getBNpcPartsIdList()
{
   if( m_BNpcPartsIdList.size() == 0 )
      loadIdList( m_BNpcPartsDat, m_BNpcPartsIdList );
   return m_BNpcPartsIdList;
}
const std::set< uint32_t >& getBNpcStateIdList()
{
   if( m_BNpcStateIdList.size() == 0 )
      loadIdList( m_BNpcStateDat, m_BNpcStateIdList );
   return m_BNpcStateIdList;
}
const std::set< uint32_t >& getBuddyIdList()
{
   if( m_BuddyIdList.size() == 0 )
      loadIdList( m_BuddyDat, m_BuddyIdList );
   return m_BuddyIdList;
}
const std::set< uint32_t >& getBuddyActionIdList()
{
   if( m_BuddyActionIdList.size() == 0 )
      loadIdList( m_BuddyActionDat, m_BuddyActionIdList );
   return m_BuddyActionIdList;
}
const std::set< uint32_t >& getBuddyEquipIdList()
{
   if( m_BuddyEquipIdList.size() == 0 )
      loadIdList( m_BuddyEquipDat, m_BuddyEquipIdList );
   return m_BuddyEquipIdList;
}
const std::set< uint32_t >& getBuddyItemIdList()
{
   if( m_BuddyItemIdList.size() == 0 )
      loadIdList( m_BuddyItemDat, m_BuddyItemIdList );
   return m_BuddyItemIdList;
}
const std::set< uint32_t >& getBuddyRankIdList()
{
   if( m_BuddyRankIdList.size() == 0 )
      loadIdList( m_BuddyRankDat, m_BuddyRankIdList );
   return m_BuddyRankIdList;
}
const std::set< uint32_t >& getBuddySkillIdList()
{
   if( m_BuddySkillIdList.size() == 0 )
      loadIdList( m_BuddySkillDat, m_BuddySkillIdList );
   return m_BuddySkillIdList;
}
const std::set< uint32_t >& getCabinetIdList()
{
   if( m_CabinetIdList.size() == 0 )
      loadIdList( m_CabinetDat, m_CabinetIdList );
   return m_CabinetIdList;
}
const std::set< uint32_t >& getCabinetCategoryIdList()
{
   if( m_CabinetCategoryIdList.size() == 0 )
      loadIdList( m_CabinetCategoryDat, m_CabinetCategoryIdList );
   return m_CabinetCategoryIdList;
}
const std::set< uint32_t >& getCalendarIdList()
{
   if( m_CalendarIdList.size() == 0 )
      loadIdList( m_CalendarDat, m_CalendarIdList );
   return m_CalendarIdList;
}
const std::set< uint32_t >& getCarryIdList()
{
   if( m_CarryIdList.size() == 0 )
      loadIdList( m_CarryDat, m_CarryIdList );
   return m_CarryIdList;
}
const std::set< uint32_t >& getChannelingIdList()
{
   if( m_ChannelingIdList.size() == 0 )
      loadIdList( m_ChannelingDat, m_ChannelingIdList );
   return m_ChannelingIdList;
}
const std::set< uint32_t >& getCharaMakeClassEquipIdList()
{
   if( m_CharaMakeClassEquipIdList.size() == 0 )
      loadIdList( m_CharaMakeClassEquipDat, m_CharaMakeClassEquipIdList );
   return m_CharaMakeClassEquipIdList;
}
const std::set< uint32_t >& getCharaMakeCustomizeIdList()
{
   if( m_CharaMakeCustomizeIdList.size() == 0 )
      loadIdList( m_CharaMakeCustomizeDat, m_CharaMakeCustomizeIdList );
   return m_CharaMakeCustomizeIdList;
}
const std::set< uint32_t >& getCharaMakeNameIdList()
{
   if( m_CharaMakeNameIdList.size() == 0 )
      loadIdList( m_CharaMakeNameDat, m_CharaMakeNameIdList );
   return m_CharaMakeNameIdList;
}
const std::set< uint32_t >& getCharaMakeTypeIdList()
{
   if( m_CharaMakeTypeIdList.size() == 0 )
      loadIdList( m_CharaMakeTypeDat, m_CharaMakeTypeIdList );
   return m_CharaMakeTypeIdList;
}
const std::set< uint32_t >& getChocoboRaceIdList()
{
   if( m_ChocoboRaceIdList.size() == 0 )
      loadIdList( m_ChocoboRaceDat, m_ChocoboRaceIdList );
   return m_ChocoboRaceIdList;
}
const std::set< uint32_t >& getChocoboRaceAbilityIdList()
{
   if( m_ChocoboRaceAbilityIdList.size() == 0 )
      loadIdList( m_ChocoboRaceAbilityDat, m_ChocoboRaceAbilityIdList );
   return m_ChocoboRaceAbilityIdList;
}
const std::set< uint32_t >& getChocoboRaceAbilityTypeIdList()
{
   if( m_ChocoboRaceAbilityTypeIdList.size() == 0 )
      loadIdList( m_ChocoboRaceAbilityTypeDat, m_ChocoboRaceAbilityTypeIdList );
   return m_ChocoboRaceAbilityTypeIdList;
}
const std::set< uint32_t >& getChocoboRaceItemIdList()
{
   if( m_ChocoboRaceItemIdList.size() == 0 )
      loadIdList( m_ChocoboRaceItemDat, m_ChocoboRaceItemIdList );
   return m_ChocoboRaceItemIdList;
}
const std::set< uint32_t >& getChocoboRaceRankIdList()
{
   if( m_ChocoboRaceRankIdList.size() == 0 )
      loadIdList( m_ChocoboRaceRankDat, m_ChocoboRaceRankIdList );
   return m_ChocoboRaceRankIdList;
}
const std::set< uint32_t >& getChocoboRaceStatusIdList()
{
   if( m_ChocoboRaceStatusIdList.size() == 0 )
      loadIdList( m_ChocoboRaceStatusDat, m_ChocoboRaceStatusIdList );
   return m_ChocoboRaceStatusIdList;
}
const std::set< uint32_t >& getChocoboRaceTerritoryIdList()
{
   if( m_ChocoboRaceTerritoryIdList.size() == 0 )
      loadIdList( m_ChocoboRaceTerritoryDat, m_ChocoboRaceTerritoryIdList );
   return m_ChocoboRaceTerritoryIdList;
}
const std::set< uint32_t >& getChocoboRaceTutorialIdList()
{
   if( m_ChocoboRaceTutorialIdList.size() == 0 )
      loadIdList( m_ChocoboRaceTutorialDat, m_ChocoboRaceTutorialIdList );
   return m_ChocoboRaceTutorialIdList;
}
const std::set< uint32_t >& getChocoboRaceWeatherIdList()
{
   if( m_ChocoboRaceWeatherIdList.size() == 0 )
      loadIdList( m_ChocoboRaceWeatherDat, m_ChocoboRaceWeatherIdList );
   return m_ChocoboRaceWeatherIdList;
}
const std::set< uint32_t >& getChocoboTaxiIdList()
{
   if( m_ChocoboTaxiIdList.size() == 0 )
      loadIdList( m_ChocoboTaxiDat, m_ChocoboTaxiIdList );
   return m_ChocoboTaxiIdList;
}
const std::set< uint32_t >& getChocoboTaxiStandIdList()
{
   if( m_ChocoboTaxiStandIdList.size() == 0 )
      loadIdList( m_ChocoboTaxiStandDat, m_ChocoboTaxiStandIdList );
   return m_ChocoboTaxiStandIdList;
}
const std::set< uint32_t >& getCircleActivityIdList()
{
   if( m_CircleActivityIdList.size() == 0 )
      loadIdList( m_CircleActivityDat, m_CircleActivityIdList );
   return m_CircleActivityIdList;
}
const std::set< uint32_t >& getClassJobIdList()
{
   if( m_ClassJobIdList.size() == 0 )
      loadIdList( m_ClassJobDat, m_ClassJobIdList );
   return m_ClassJobIdList;
}
const std::set< uint32_t >& getClassJobCategoryIdList()
{
   if( m_ClassJobCategoryIdList.size() == 0 )
      loadIdList( m_ClassJobCategoryDat, m_ClassJobCategoryIdList );
   return m_ClassJobCategoryIdList;
}
const std::set< uint32_t >& getCollectablesShopIdList()
{
   if( m_CollectablesShopIdList.size() == 0 )
      loadIdList( m_CollectablesShopDat, m_CollectablesShopIdList );
   return m_CollectablesShopIdList;
}
const std::set< uint32_t >& getCollectablesShopItemIdList()
{
   if( m_CollectablesShopItemIdList.size() == 0 )
      loadIdList( m_CollectablesShopItemDat, m_CollectablesShopItemIdList );
   return m_CollectablesShopItemIdList;
}
const std::set< uint32_t >& getCollectablesShopItemGroupIdList()
{
   if( m_CollectablesShopItemGroupIdList.size() == 0 )
      loadIdList( m_CollectablesShopItemGroupDat, m_CollectablesShopItemGroupIdList );
   return m_CollectablesShopItemGroupIdList;
}
const std::set< uint32_t >& getCollectablesShopRefineIdList()
{
   if( m_CollectablesShopRefineIdList.size() == 0 )
      loadIdList( m_CollectablesShopRefineDat, m_CollectablesShopRefineIdList );
   return m_CollectablesShopRefineIdList;
}
const std::set< uint32_t >& getCollectablesShopRewardItemIdList()
{
   if( m_CollectablesShopRewardItemIdList.size() == 0 )
      loadIdList( m_CollectablesShopRewardItemDat, m_CollectablesShopRewardItemIdList );
   return m_CollectablesShopRewardItemIdList;
}
const std::set< uint32_t >& getCollectablesShopRewardScripIdList()
{
   if( m_CollectablesShopRewardScripIdList.size() == 0 )
      loadIdList( m_CollectablesShopRewardScripDat, m_CollectablesShopRewardScripIdList );
   return m_CollectablesShopRewardScripIdList;
}
const std::set< uint32_t >& getCompanionIdList()
{
   if( m_CompanionIdList.size() == 0 )
      loadIdList( m_CompanionDat, m_CompanionIdList );
   return m_CompanionIdList;
}
const std::set< uint32_t >& getCompanionMoveIdList()
{
   if( m_CompanionMoveIdList.size() == 0 )
      loadIdList( m_CompanionMoveDat, m_CompanionMoveIdList );
   return m_CompanionMoveIdList;
}
const std::set< uint32_t >& getCompanionTransientIdList()
{
   if( m_CompanionTransientIdList.size() == 0 )
      loadIdList( m_CompanionTransientDat, m_CompanionTransientIdList );
   return m_CompanionTransientIdList;
}
const std::set< uint32_t >& getCompanyActionIdList()
{
   if( m_CompanyActionIdList.size() == 0 )
      loadIdList( m_CompanyActionDat, m_CompanyActionIdList );
   return m_CompanyActionIdList;
}
const std::set< uint32_t >& getCompanyCraftDraftIdList()
{
   if( m_CompanyCraftDraftIdList.size() == 0 )
      loadIdList( m_CompanyCraftDraftDat, m_CompanyCraftDraftIdList );
   return m_CompanyCraftDraftIdList;
}
const std::set< uint32_t >& getCompanyCraftDraftCategoryIdList()
{
   if( m_CompanyCraftDraftCategoryIdList.size() == 0 )
      loadIdList( m_CompanyCraftDraftCategoryDat, m_CompanyCraftDraftCategoryIdList );
   return m_CompanyCraftDraftCategoryIdList;
}
const std::set< uint32_t >& getCompanyCraftManufactoryStateIdList()
{
   if( m_CompanyCraftManufactoryStateIdList.size() == 0 )
      loadIdList( m_CompanyCraftManufactoryStateDat, m_CompanyCraftManufactoryStateIdList );
   return m_CompanyCraftManufactoryStateIdList;
}
const std::set< uint32_t >& getCompanyCraftPartIdList()
{
   if( m_CompanyCraftPartIdList.size() == 0 )
      loadIdList( m_CompanyCraftPartDat, m_CompanyCraftPartIdList );
   return m_CompanyCraftPartIdList;
}
const std::set< uint32_t >& getCompanyCraftProcessIdList()
{
   if( m_CompanyCraftProcessIdList.size() == 0 )
      loadIdList( m_CompanyCraftProcessDat, m_CompanyCraftProcessIdList );
   return m_CompanyCraftProcessIdList;
}
const std::set< uint32_t >& getCompanyCraftSequenceIdList()
{
   if( m_CompanyCraftSequenceIdList.size() == 0 )
      loadIdList( m_CompanyCraftSequenceDat, m_CompanyCraftSequenceIdList );
   return m_CompanyCraftSequenceIdList;
}
const std::set< uint32_t >& getCompanyCraftSupplyItemIdList()
{
   if( m_CompanyCraftSupplyItemIdList.size() == 0 )
      loadIdList( m_CompanyCraftSupplyItemDat, m_CompanyCraftSupplyItemIdList );
   return m_CompanyCraftSupplyItemIdList;
}
const std::set< uint32_t >& getCompanyCraftTypeIdList()
{
   if( m_CompanyCraftTypeIdList.size() == 0 )
      loadIdList( m_CompanyCraftTypeDat, m_CompanyCraftTypeIdList );
   return m_CompanyCraftTypeIdList;
}
const std::set< uint32_t >& getCompanyLeveIdList()
{
   if( m_CompanyLeveIdList.size() == 0 )
      loadIdList( m_CompanyLeveDat, m_CompanyLeveIdList );
   return m_CompanyLeveIdList;
}
const std::set< uint32_t >& getCompanyLeveRuleIdList()
{
   if( m_CompanyLeveRuleIdList.size() == 0 )
      loadIdList( m_CompanyLeveRuleDat, m_CompanyLeveRuleIdList );
   return m_CompanyLeveRuleIdList;
}
const std::set< uint32_t >& getCompleteJournalIdList()
{
   if( m_CompleteJournalIdList.size() == 0 )
      loadIdList( m_CompleteJournalDat, m_CompleteJournalIdList );
   return m_CompleteJournalIdList;
}
const std::set< uint32_t >& getCompleteJournalCategoryIdList()
{
   if( m_CompleteJournalCategoryIdList.size() == 0 )
      loadIdList( m_CompleteJournalCategoryDat, m_CompleteJournalCategoryIdList );
   return m_CompleteJournalCategoryIdList;
}
const std::set< uint32_t >& getConditionIdList()
{
   if( m_ConditionIdList.size() == 0 )
      loadIdList( m_ConditionDat, m_ConditionIdList );
   return m_ConditionIdList;
}
const std::set< uint32_t >& getConfigKeyIdList()
{
   if( m_ConfigKeyIdList.size() == 0 )
      loadIdList( m_ConfigKeyDat, m_ConfigKeyIdList );
   return m_ConfigKeyIdList;
}
const std::set< uint32_t >& getContentCloseCycleIdList()
{
   if( m_ContentCloseCycleIdList.size() == 0 )
      loadIdList( m_ContentCloseCycleDat, m_ContentCloseCycleIdList );
   return m_ContentCloseCycleIdList;
}
const std::set< uint32_t >& getContentExActionIdList()
{
   if( m_ContentExActionIdList.size() == 0 )
      loadIdList( m_ContentExActionDat, m_ContentExActionIdList );
   return m_ContentExActionIdList;
}
const std::set< uint32_t >& getContentFinderConditionIdList()
{
   if( m_ContentFinderConditionIdList.size() == 0 )
      loadIdList( m_ContentFinderConditionDat, m_ContentFinderConditionIdList );
   return m_ContentFinderConditionIdList;
}
const std::set< uint32_t >& getContentFinderConditionTransientIdList()
{
   if( m_ContentFinderConditionTransientIdList.size() == 0 )
      loadIdList( m_ContentFinderConditionTransientDat, m_ContentFinderConditionTransientIdList );
   return m_ContentFinderConditionTransientIdList;
}
const std::set< uint32_t >& getContentGaugeIdList()
{
   if( m_ContentGaugeIdList.size() == 0 )
      loadIdList( m_ContentGaugeDat, m_ContentGaugeIdList );
   return m_ContentGaugeIdList;
}
const std::set< uint32_t >& getContentGaugeColorIdList()
{
   if( m_ContentGaugeColorIdList.size() == 0 )
      loadIdList( m_ContentGaugeColorDat, m_ContentGaugeColorIdList );
   return m_ContentGaugeColorIdList;
}
const std::set< uint32_t >& getContentMemberTypeIdList()
{
   if( m_ContentMemberTypeIdList.size() == 0 )
      loadIdList( m_ContentMemberTypeDat, m_ContentMemberTypeIdList );
   return m_ContentMemberTypeIdList;
}
const std::set< uint32_t >& getContentNpcTalkIdList()
{
   if( m_ContentNpcTalkIdList.size() == 0 )
      loadIdList( m_ContentNpcTalkDat, m_ContentNpcTalkIdList );
   return m_ContentNpcTalkIdList;
}
const std::set< uint32_t >& getContentRandomSelectIdList()
{
   if( m_ContentRandomSelectIdList.size() == 0 )
      loadIdList( m_ContentRandomSelectDat, m_ContentRandomSelectIdList );
   return m_ContentRandomSelectIdList;
}
const std::set< uint32_t >& getContentRouletteIdList()
{
   if( m_ContentRouletteIdList.size() == 0 )
      loadIdList( m_ContentRouletteDat, m_ContentRouletteIdList );
   return m_ContentRouletteIdList;
}
const std::set< uint32_t >& getContentRouletteOpenRuleIdList()
{
   if( m_ContentRouletteOpenRuleIdList.size() == 0 )
      loadIdList( m_ContentRouletteOpenRuleDat, m_ContentRouletteOpenRuleIdList );
   return m_ContentRouletteOpenRuleIdList;
}
const std::set< uint32_t >& getContentRouletteRoleBonusIdList()
{
   if( m_ContentRouletteRoleBonusIdList.size() == 0 )
      loadIdList( m_ContentRouletteRoleBonusDat, m_ContentRouletteRoleBonusIdList );
   return m_ContentRouletteRoleBonusIdList;
}
const std::set< uint32_t >& getContentsNoteIdList()
{
   if( m_ContentsNoteIdList.size() == 0 )
      loadIdList( m_ContentsNoteDat, m_ContentsNoteIdList );
   return m_ContentsNoteIdList;
}
const std::set< uint32_t >& getContentsTutorialIdList()
{
   if( m_ContentsTutorialIdList.size() == 0 )
      loadIdList( m_ContentsTutorialDat, m_ContentsTutorialIdList );
   return m_ContentsTutorialIdList;
}
const std::set< uint32_t >& getContentsTutorialPageIdList()
{
   if( m_ContentsTutorialPageIdList.size() == 0 )
      loadIdList( m_ContentsTutorialPageDat, m_ContentsTutorialPageIdList );
   return m_ContentsTutorialPageIdList;
}
const std::set< uint32_t >& getContentTalkIdList()
{
   if( m_ContentTalkIdList.size() == 0 )
      loadIdList( m_ContentTalkDat, m_ContentTalkIdList );
   return m_ContentTalkIdList;
}
const std::set< uint32_t >& getContentTalkParamIdList()
{
   if( m_ContentTalkParamIdList.size() == 0 )
      loadIdList( m_ContentTalkParamDat, m_ContentTalkParamIdList );
   return m_ContentTalkParamIdList;
}
const std::set< uint32_t >& getContentTypeIdList()
{
   if( m_ContentTypeIdList.size() == 0 )
      loadIdList( m_ContentTypeDat, m_ContentTypeIdList );
   return m_ContentTypeIdList;
}
const std::set< uint32_t >& getCraftActionIdList()
{
   if( m_CraftActionIdList.size() == 0 )
      loadIdList( m_CraftActionDat, m_CraftActionIdList );
   return m_CraftActionIdList;
}
const std::set< uint32_t >& getCraftLeveIdList()
{
   if( m_CraftLeveIdList.size() == 0 )
      loadIdList( m_CraftLeveDat, m_CraftLeveIdList );
   return m_CraftLeveIdList;
}
const std::set< uint32_t >& getCraftLevelDifferenceIdList()
{
   if( m_CraftLevelDifferenceIdList.size() == 0 )
      loadIdList( m_CraftLevelDifferenceDat, m_CraftLevelDifferenceIdList );
   return m_CraftLevelDifferenceIdList;
}
const std::set< uint32_t >& getCraftTypeIdList()
{
   if( m_CraftTypeIdList.size() == 0 )
      loadIdList( m_CraftTypeDat, m_CraftTypeIdList );
   return m_CraftTypeIdList;
}
const std::set< uint32_t >& getCreditIdList()
{
   if( m_CreditIdList.size() == 0 )
      loadIdList( m_CreditDat, m_CreditIdList );
   return m_CreditIdList;
}
const std::set< uint32_t >& getCreditBackImageIdList()
{
   if( m_CreditBackImageIdList.size() == 0 )
      loadIdList( m_CreditBackImageDat, m_CreditBackImageIdList );
   return m_CreditBackImageIdList;
}
const std::set< uint32_t >& getCreditCastIdList()
{
   if( m_CreditCastIdList.size() == 0 )
      loadIdList( m_CreditCastDat, m_CreditCastIdList );
   return m_CreditCastIdList;
}
const std::set< uint32_t >& getCreditListIdList()
{
   if( m_CreditListIdList.size() == 0 )
      loadIdList( m_CreditListDat, m_CreditListIdList );
   return m_CreditListIdList;
}
const std::set< uint32_t >& getCreditListTextIdList()
{
   if( m_CreditListTextIdList.size() == 0 )
      loadIdList( m_CreditListTextDat, m_CreditListTextIdList );
   return m_CreditListTextIdList;
}
const std::set< uint32_t >& getCustomTalkIdList()
{
   if( m_CustomTalkIdList.size() == 0 )
      loadIdList( m_CustomTalkDat, m_CustomTalkIdList );
   return m_CustomTalkIdList;
}
const std::set< uint32_t >& getCustomTalkDynamicIconIdList()
{
   if( m_CustomTalkDynamicIconIdList.size() == 0 )
      loadIdList( m_CustomTalkDynamicIconDat, m_CustomTalkDynamicIconIdList );
   return m_CustomTalkDynamicIconIdList;
}
const std::set< uint32_t >& getCustomTalkNestHandlersIdList()
{
   if( m_CustomTalkNestHandlersIdList.size() == 0 )
      loadIdList( m_CustomTalkNestHandlersDat, m_CustomTalkNestHandlersIdList );
   return m_CustomTalkNestHandlersIdList;
}
const std::set< uint32_t >& getCutsceneIdList()
{
   if( m_CutsceneIdList.size() == 0 )
      loadIdList( m_CutsceneDat, m_CutsceneIdList );
   return m_CutsceneIdList;
}
const std::set< uint32_t >& getCutsceneMotionIdList()
{
   if( m_CutsceneMotionIdList.size() == 0 )
      loadIdList( m_CutsceneMotionDat, m_CutsceneMotionIdList );
   return m_CutsceneMotionIdList;
}
const std::set< uint32_t >& getCutsceneWorkIndexIdList()
{
   if( m_CutsceneWorkIndexIdList.size() == 0 )
      loadIdList( m_CutsceneWorkIndexDat, m_CutsceneWorkIndexIdList );
   return m_CutsceneWorkIndexIdList;
}
const std::set< uint32_t >& getCutScreenImageIdList()
{
   if( m_CutScreenImageIdList.size() == 0 )
      loadIdList( m_CutScreenImageDat, m_CutScreenImageIdList );
   return m_CutScreenImageIdList;
}
const std::set< uint32_t >& getCycleTimeIdList()
{
   if( m_CycleTimeIdList.size() == 0 )
      loadIdList( m_CycleTimeDat, m_CycleTimeIdList );
   return m_CycleTimeIdList;
}
const std::set< uint32_t >& getDailySupplyItemIdList()
{
   if( m_DailySupplyItemIdList.size() == 0 )
      loadIdList( m_DailySupplyItemDat, m_DailySupplyItemIdList );
   return m_DailySupplyItemIdList;
}
const std::set< uint32_t >& getDawnContentIdList()
{
   if( m_DawnContentIdList.size() == 0 )
      loadIdList( m_DawnContentDat, m_DawnContentIdList );
   return m_DawnContentIdList;
}
const std::set< uint32_t >& getDawnGrowMemberIdList()
{
   if( m_DawnGrowMemberIdList.size() == 0 )
      loadIdList( m_DawnGrowMemberDat, m_DawnGrowMemberIdList );
   return m_DawnGrowMemberIdList;
}
const std::set< uint32_t >& getDawnMemberUIParamIdList()
{
   if( m_DawnMemberUIParamIdList.size() == 0 )
      loadIdList( m_DawnMemberUIParamDat, m_DawnMemberUIParamIdList );
   return m_DawnMemberUIParamIdList;
}
const std::set< uint32_t >& getDawnQuestAnnounceIdList()
{
   if( m_DawnQuestAnnounceIdList.size() == 0 )
      loadIdList( m_DawnQuestAnnounceDat, m_DawnQuestAnnounceIdList );
   return m_DawnQuestAnnounceIdList;
}
const std::set< uint32_t >& getDawnQuestMemberIdList()
{
   if( m_DawnQuestMemberIdList.size() == 0 )
      loadIdList( m_DawnQuestMemberDat, m_DawnQuestMemberIdList );
   return m_DawnQuestMemberIdList;
}
const std::set< uint32_t >& getDeepDungeonIdList()
{
   if( m_DeepDungeonIdList.size() == 0 )
      loadIdList( m_DeepDungeonDat, m_DeepDungeonIdList );
   return m_DeepDungeonIdList;
}
const std::set< uint32_t >& getDeepDungeonBanIdList()
{
   if( m_DeepDungeonBanIdList.size() == 0 )
      loadIdList( m_DeepDungeonBanDat, m_DeepDungeonBanIdList );
   return m_DeepDungeonBanIdList;
}
const std::set< uint32_t >& getDeepDungeonDangerIdList()
{
   if( m_DeepDungeonDangerIdList.size() == 0 )
      loadIdList( m_DeepDungeonDangerDat, m_DeepDungeonDangerIdList );
   return m_DeepDungeonDangerIdList;
}
const std::set< uint32_t >& getDeepDungeonEquipmentIdList()
{
   if( m_DeepDungeonEquipmentIdList.size() == 0 )
      loadIdList( m_DeepDungeonEquipmentDat, m_DeepDungeonEquipmentIdList );
   return m_DeepDungeonEquipmentIdList;
}
const std::set< uint32_t >& getDeepDungeonFloorEffectUIIdList()
{
   if( m_DeepDungeonFloorEffectUIIdList.size() == 0 )
      loadIdList( m_DeepDungeonFloorEffectUIDat, m_DeepDungeonFloorEffectUIIdList );
   return m_DeepDungeonFloorEffectUIIdList;
}
const std::set< uint32_t >& getDeepDungeonItemIdList()
{
   if( m_DeepDungeonItemIdList.size() == 0 )
      loadIdList( m_DeepDungeonItemDat, m_DeepDungeonItemIdList );
   return m_DeepDungeonItemIdList;
}
const std::set< uint32_t >& getDeepDungeonLayerIdList()
{
   if( m_DeepDungeonLayerIdList.size() == 0 )
      loadIdList( m_DeepDungeonLayerDat, m_DeepDungeonLayerIdList );
   return m_DeepDungeonLayerIdList;
}
const std::set< uint32_t >& getDeepDungeonMagicStoneIdList()
{
   if( m_DeepDungeonMagicStoneIdList.size() == 0 )
      loadIdList( m_DeepDungeonMagicStoneDat, m_DeepDungeonMagicStoneIdList );
   return m_DeepDungeonMagicStoneIdList;
}
const std::set< uint32_t >& getDeepDungeonMap5XIdList()
{
   if( m_DeepDungeonMap5XIdList.size() == 0 )
      loadIdList( m_DeepDungeonMap5XDat, m_DeepDungeonMap5XIdList );
   return m_DeepDungeonMap5XIdList;
}
const std::set< uint32_t >& getDeepDungeonRoomIdList()
{
   if( m_DeepDungeonRoomIdList.size() == 0 )
      loadIdList( m_DeepDungeonRoomDat, m_DeepDungeonRoomIdList );
   return m_DeepDungeonRoomIdList;
}
const std::set< uint32_t >& getDeepDungeonStatusIdList()
{
   if( m_DeepDungeonStatusIdList.size() == 0 )
      loadIdList( m_DeepDungeonStatusDat, m_DeepDungeonStatusIdList );
   return m_DeepDungeonStatusIdList;
}
const std::set< uint32_t >& getDefaultTalkIdList()
{
   if( m_DefaultTalkIdList.size() == 0 )
      loadIdList( m_DefaultTalkDat, m_DefaultTalkIdList );
   return m_DefaultTalkIdList;
}
const std::set< uint32_t >& getDefaultTalkLipSyncTypeIdList()
{
   if( m_DefaultTalkLipSyncTypeIdList.size() == 0 )
      loadIdList( m_DefaultTalkLipSyncTypeDat, m_DefaultTalkLipSyncTypeIdList );
   return m_DefaultTalkLipSyncTypeIdList;
}
const std::set< uint32_t >& getDeliveryQuestIdList()
{
   if( m_DeliveryQuestIdList.size() == 0 )
      loadIdList( m_DeliveryQuestDat, m_DeliveryQuestIdList );
   return m_DeliveryQuestIdList;
}
const std::set< uint32_t >& getDescriptionIdList()
{
   if( m_DescriptionIdList.size() == 0 )
      loadIdList( m_DescriptionDat, m_DescriptionIdList );
   return m_DescriptionIdList;
}
const std::set< uint32_t >& getDescriptionPageIdList()
{
   if( m_DescriptionPageIdList.size() == 0 )
      loadIdList( m_DescriptionPageDat, m_DescriptionPageIdList );
   return m_DescriptionPageIdList;
}
const std::set< uint32_t >& getDescriptionSectionIdList()
{
   if( m_DescriptionSectionIdList.size() == 0 )
      loadIdList( m_DescriptionSectionDat, m_DescriptionSectionIdList );
   return m_DescriptionSectionIdList;
}
const std::set< uint32_t >& getDescriptionStringIdList()
{
   if( m_DescriptionStringIdList.size() == 0 )
      loadIdList( m_DescriptionStringDat, m_DescriptionStringIdList );
   return m_DescriptionStringIdList;
}
const std::set< uint32_t >& getDisposalShopIdList()
{
   if( m_DisposalShopIdList.size() == 0 )
      loadIdList( m_DisposalShopDat, m_DisposalShopIdList );
   return m_DisposalShopIdList;
}
const std::set< uint32_t >& getDisposalShopFilterTypeIdList()
{
   if( m_DisposalShopFilterTypeIdList.size() == 0 )
      loadIdList( m_DisposalShopFilterTypeDat, m_DisposalShopFilterTypeIdList );
   return m_DisposalShopFilterTypeIdList;
}
const std::set< uint32_t >& getDisposalShopItemIdList()
{
   if( m_DisposalShopItemIdList.size() == 0 )
      loadIdList( m_DisposalShopItemDat, m_DisposalShopItemIdList );
   return m_DisposalShopItemIdList;
}
const std::set< uint32_t >& getDpsChallengeIdList()
{
   if( m_DpsChallengeIdList.size() == 0 )
      loadIdList( m_DpsChallengeDat, m_DpsChallengeIdList );
   return m_DpsChallengeIdList;
}
const std::set< uint32_t >& getDpsChallengeOfficerIdList()
{
   if( m_DpsChallengeOfficerIdList.size() == 0 )
      loadIdList( m_DpsChallengeOfficerDat, m_DpsChallengeOfficerIdList );
   return m_DpsChallengeOfficerIdList;
}
const std::set< uint32_t >& getDpsChallengeTransientIdList()
{
   if( m_DpsChallengeTransientIdList.size() == 0 )
      loadIdList( m_DpsChallengeTransientDat, m_DpsChallengeTransientIdList );
   return m_DpsChallengeTransientIdList;
}
const std::set< uint32_t >& getDynamicEventIdList()
{
   if( m_DynamicEventIdList.size() == 0 )
      loadIdList( m_DynamicEventDat, m_DynamicEventIdList );
   return m_DynamicEventIdList;
}
const std::set< uint32_t >& getDynamicEventEnemyTypeIdList()
{
   if( m_DynamicEventEnemyTypeIdList.size() == 0 )
      loadIdList( m_DynamicEventEnemyTypeDat, m_DynamicEventEnemyTypeIdList );
   return m_DynamicEventEnemyTypeIdList;
}
const std::set< uint32_t >& getDynamicEventSingleBattleIdList()
{
   if( m_DynamicEventSingleBattleIdList.size() == 0 )
      loadIdList( m_DynamicEventSingleBattleDat, m_DynamicEventSingleBattleIdList );
   return m_DynamicEventSingleBattleIdList;
}
const std::set< uint32_t >& getDynamicEventTypeIdList()
{
   if( m_DynamicEventTypeIdList.size() == 0 )
      loadIdList( m_DynamicEventTypeDat, m_DynamicEventTypeIdList );
   return m_DynamicEventTypeIdList;
}
const std::set< uint32_t >& getEmjAddonIdList()
{
   if( m_EmjAddonIdList.size() == 0 )
      loadIdList( m_EmjAddonDat, m_EmjAddonIdList );
   return m_EmjAddonIdList;
}
const std::set< uint32_t >& getEmjDaniIdList()
{
   if( m_EmjDaniIdList.size() == 0 )
      loadIdList( m_EmjDaniDat, m_EmjDaniIdList );
   return m_EmjDaniIdList;
}
const std::set< uint32_t >& getEmoteIdList()
{
   if( m_EmoteIdList.size() == 0 )
      loadIdList( m_EmoteDat, m_EmoteIdList );
   return m_EmoteIdList;
}
const std::set< uint32_t >& getEmoteCategoryIdList()
{
   if( m_EmoteCategoryIdList.size() == 0 )
      loadIdList( m_EmoteCategoryDat, m_EmoteCategoryIdList );
   return m_EmoteCategoryIdList;
}
const std::set< uint32_t >& getEmoteModeIdList()
{
   if( m_EmoteModeIdList.size() == 0 )
      loadIdList( m_EmoteModeDat, m_EmoteModeIdList );
   return m_EmoteModeIdList;
}
const std::set< uint32_t >& getENpcBaseIdList()
{
   if( m_ENpcBaseIdList.size() == 0 )
      loadIdList( m_ENpcBaseDat, m_ENpcBaseIdList );
   return m_ENpcBaseIdList;
}
const std::set< uint32_t >& getENpcDressUpIdList()
{
   if( m_ENpcDressUpIdList.size() == 0 )
      loadIdList( m_ENpcDressUpDat, m_ENpcDressUpIdList );
   return m_ENpcDressUpIdList;
}
const std::set< uint32_t >& getENpcDressUpDressIdList()
{
   if( m_ENpcDressUpDressIdList.size() == 0 )
      loadIdList( m_ENpcDressUpDressDat, m_ENpcDressUpDressIdList );
   return m_ENpcDressUpDressIdList;
}
const std::set< uint32_t >& getENpcResidentIdList()
{
   if( m_ENpcResidentIdList.size() == 0 )
      loadIdList( m_ENpcResidentDat, m_ENpcResidentIdList );
   return m_ENpcResidentIdList;
}
const std::set< uint32_t >& getEObjIdList()
{
   if( m_EObjIdList.size() == 0 )
      loadIdList( m_EObjDat, m_EObjIdList );
   return m_EObjIdList;
}
const std::set< uint32_t >& getEObjNameIdList()
{
   if( m_EObjNameIdList.size() == 0 )
      loadIdList( m_EObjNameDat, m_EObjNameIdList );
   return m_EObjNameIdList;
}
const std::set< uint32_t >& getEquipRaceCategoryIdList()
{
   if( m_EquipRaceCategoryIdList.size() == 0 )
      loadIdList( m_EquipRaceCategoryDat, m_EquipRaceCategoryIdList );
   return m_EquipRaceCategoryIdList;
}
const std::set< uint32_t >& getEquipSlotCategoryIdList()
{
   if( m_EquipSlotCategoryIdList.size() == 0 )
      loadIdList( m_EquipSlotCategoryDat, m_EquipSlotCategoryIdList );
   return m_EquipSlotCategoryIdList;
}
const std::set< uint32_t >& getEurekaAetherItemIdList()
{
   if( m_EurekaAetherItemIdList.size() == 0 )
      loadIdList( m_EurekaAetherItemDat, m_EurekaAetherItemIdList );
   return m_EurekaAetherItemIdList;
}
const std::set< uint32_t >& getEurekaAethernetIdList()
{
   if( m_EurekaAethernetIdList.size() == 0 )
      loadIdList( m_EurekaAethernetDat, m_EurekaAethernetIdList );
   return m_EurekaAethernetIdList;
}
const std::set< uint32_t >& getEurekaGrowDataIdList()
{
   if( m_EurekaGrowDataIdList.size() == 0 )
      loadIdList( m_EurekaGrowDataDat, m_EurekaGrowDataIdList );
   return m_EurekaGrowDataIdList;
}
const std::set< uint32_t >& getEurekaLogosMixerProbabilityIdList()
{
   if( m_EurekaLogosMixerProbabilityIdList.size() == 0 )
      loadIdList( m_EurekaLogosMixerProbabilityDat, m_EurekaLogosMixerProbabilityIdList );
   return m_EurekaLogosMixerProbabilityIdList;
}
const std::set< uint32_t >& getEurekaMagiaActionIdList()
{
   if( m_EurekaMagiaActionIdList.size() == 0 )
      loadIdList( m_EurekaMagiaActionDat, m_EurekaMagiaActionIdList );
   return m_EurekaMagiaActionIdList;
}
const std::set< uint32_t >& getEurekaMagiciteItemIdList()
{
   if( m_EurekaMagiciteItemIdList.size() == 0 )
      loadIdList( m_EurekaMagiciteItemDat, m_EurekaMagiciteItemIdList );
   return m_EurekaMagiciteItemIdList;
}
const std::set< uint32_t >& getEurekaMagiciteItemTypeIdList()
{
   if( m_EurekaMagiciteItemTypeIdList.size() == 0 )
      loadIdList( m_EurekaMagiciteItemTypeDat, m_EurekaMagiciteItemTypeIdList );
   return m_EurekaMagiciteItemTypeIdList;
}
const std::set< uint32_t >& getEurekaSphereElementAdjustIdList()
{
   if( m_EurekaSphereElementAdjustIdList.size() == 0 )
      loadIdList( m_EurekaSphereElementAdjustDat, m_EurekaSphereElementAdjustIdList );
   return m_EurekaSphereElementAdjustIdList;
}
const std::set< uint32_t >& getEventActionIdList()
{
   if( m_EventActionIdList.size() == 0 )
      loadIdList( m_EventActionDat, m_EventActionIdList );
   return m_EventActionIdList;
}
const std::set< uint32_t >& getEventIconPriorityIdList()
{
   if( m_EventIconPriorityIdList.size() == 0 )
      loadIdList( m_EventIconPriorityDat, m_EventIconPriorityIdList );
   return m_EventIconPriorityIdList;
}
const std::set< uint32_t >& getEventIconTypeIdList()
{
   if( m_EventIconTypeIdList.size() == 0 )
      loadIdList( m_EventIconTypeDat, m_EventIconTypeIdList );
   return m_EventIconTypeIdList;
}
const std::set< uint32_t >& getEventItemIdList()
{
   if( m_EventItemIdList.size() == 0 )
      loadIdList( m_EventItemDat, m_EventItemIdList );
   return m_EventItemIdList;
}
const std::set< uint32_t >& getEventItemCastTimelineIdList()
{
   if( m_EventItemCastTimelineIdList.size() == 0 )
      loadIdList( m_EventItemCastTimelineDat, m_EventItemCastTimelineIdList );
   return m_EventItemCastTimelineIdList;
}
const std::set< uint32_t >& getEventItemHelpIdList()
{
   if( m_EventItemHelpIdList.size() == 0 )
      loadIdList( m_EventItemHelpDat, m_EventItemHelpIdList );
   return m_EventItemHelpIdList;
}
const std::set< uint32_t >& getEventItemTimelineIdList()
{
   if( m_EventItemTimelineIdList.size() == 0 )
      loadIdList( m_EventItemTimelineDat, m_EventItemTimelineIdList );
   return m_EventItemTimelineIdList;
}
const std::set< uint32_t >& getEventSystemDefineIdList()
{
   if( m_EventSystemDefineIdList.size() == 0 )
      loadIdList( m_EventSystemDefineDat, m_EventSystemDefineIdList );
   return m_EventSystemDefineIdList;
}
const std::set< uint32_t >& getExportedSGIdList()
{
   if( m_ExportedSGIdList.size() == 0 )
      loadIdList( m_ExportedSGDat, m_ExportedSGIdList );
   return m_ExportedSGIdList;
}
const std::set< uint32_t >& getExVersionIdList()
{
   if( m_ExVersionIdList.size() == 0 )
      loadIdList( m_ExVersionDat, m_ExVersionIdList );
   return m_ExVersionIdList;
}
const std::set< uint32_t >& getFateIdList()
{
   if( m_FateIdList.size() == 0 )
      loadIdList( m_FateDat, m_FateIdList );
   return m_FateIdList;
}
const std::set< uint32_t >& getFateEventIdList()
{
   if( m_FateEventIdList.size() == 0 )
      loadIdList( m_FateEventDat, m_FateEventIdList );
   return m_FateEventIdList;
}
const std::set< uint32_t >& getFateModeIdList()
{
   if( m_FateModeIdList.size() == 0 )
      loadIdList( m_FateModeDat, m_FateModeIdList );
   return m_FateModeIdList;
}
const std::set< uint32_t >& getFateProgressUIIdList()
{
   if( m_FateProgressUIIdList.size() == 0 )
      loadIdList( m_FateProgressUIDat, m_FateProgressUIIdList );
   return m_FateProgressUIIdList;
}
const std::set< uint32_t >& getFateTokenTypeIdList()
{
   if( m_FateTokenTypeIdList.size() == 0 )
      loadIdList( m_FateTokenTypeDat, m_FateTokenTypeIdList );
   return m_FateTokenTypeIdList;
}
const std::set< uint32_t >& getFCActivityIdList()
{
   if( m_FCActivityIdList.size() == 0 )
      loadIdList( m_FCActivityDat, m_FCActivityIdList );
   return m_FCActivityIdList;
}
const std::set< uint32_t >& getFCActivityCategoryIdList()
{
   if( m_FCActivityCategoryIdList.size() == 0 )
      loadIdList( m_FCActivityCategoryDat, m_FCActivityCategoryIdList );
   return m_FCActivityCategoryIdList;
}
const std::set< uint32_t >& getFCAuthorityIdList()
{
   if( m_FCAuthorityIdList.size() == 0 )
      loadIdList( m_FCAuthorityDat, m_FCAuthorityIdList );
   return m_FCAuthorityIdList;
}
const std::set< uint32_t >& getFCAuthorityCategoryIdList()
{
   if( m_FCAuthorityCategoryIdList.size() == 0 )
      loadIdList( m_FCAuthorityCategoryDat, m_FCAuthorityCategoryIdList );
   return m_FCAuthorityCategoryIdList;
}
const std::set< uint32_t >& getFCChestNameIdList()
{
   if( m_FCChestNameIdList.size() == 0 )
      loadIdList( m_FCChestNameDat, m_FCChestNameIdList );
   return m_FCChestNameIdList;
}
const std::set< uint32_t >& getFCCrestSymbolIdList()
{
   if( m_FCCrestSymbolIdList.size() == 0 )
      loadIdList( m_FCCrestSymbolDat, m_FCCrestSymbolIdList );
   return m_FCCrestSymbolIdList;
}
const std::set< uint32_t >& getFccShopIdList()
{
   if( m_FccShopIdList.size() == 0 )
      loadIdList( m_FccShopDat, m_FccShopIdList );
   return m_FccShopIdList;
}
const std::set< uint32_t >& getFCHierarchyIdList()
{
   if( m_FCHierarchyIdList.size() == 0 )
      loadIdList( m_FCHierarchyDat, m_FCHierarchyIdList );
   return m_FCHierarchyIdList;
}
const std::set< uint32_t >& getFCProfileIdList()
{
   if( m_FCProfileIdList.size() == 0 )
      loadIdList( m_FCProfileDat, m_FCProfileIdList );
   return m_FCProfileIdList;
}
const std::set< uint32_t >& getFCRankIdList()
{
   if( m_FCRankIdList.size() == 0 )
      loadIdList( m_FCRankDat, m_FCRankIdList );
   return m_FCRankIdList;
}
const std::set< uint32_t >& getFCReputationIdList()
{
   if( m_FCReputationIdList.size() == 0 )
      loadIdList( m_FCReputationDat, m_FCReputationIdList );
   return m_FCReputationIdList;
}
const std::set< uint32_t >& getFCRightsIdList()
{
   if( m_FCRightsIdList.size() == 0 )
      loadIdList( m_FCRightsDat, m_FCRightsIdList );
   return m_FCRightsIdList;
}
const std::set< uint32_t >& getFestivalIdList()
{
   if( m_FestivalIdList.size() == 0 )
      loadIdList( m_FestivalDat, m_FestivalIdList );
   return m_FestivalIdList;
}
const std::set< uint32_t >& getFieldMarkerIdList()
{
   if( m_FieldMarkerIdList.size() == 0 )
      loadIdList( m_FieldMarkerDat, m_FieldMarkerIdList );
   return m_FieldMarkerIdList;
}
const std::set< uint32_t >& getFishingRecordTypeIdList()
{
   if( m_FishingRecordTypeIdList.size() == 0 )
      loadIdList( m_FishingRecordTypeDat, m_FishingRecordTypeIdList );
   return m_FishingRecordTypeIdList;
}
const std::set< uint32_t >& getFishingRecordTypeTransientIdList()
{
   if( m_FishingRecordTypeTransientIdList.size() == 0 )
      loadIdList( m_FishingRecordTypeTransientDat, m_FishingRecordTypeTransientIdList );
   return m_FishingRecordTypeTransientIdList;
}
const std::set< uint32_t >& getFishingSpotIdList()
{
   if( m_FishingSpotIdList.size() == 0 )
      loadIdList( m_FishingSpotDat, m_FishingSpotIdList );
   return m_FishingSpotIdList;
}
const std::set< uint32_t >& getFishParameterIdList()
{
   if( m_FishParameterIdList.size() == 0 )
      loadIdList( m_FishParameterDat, m_FishParameterIdList );
   return m_FishParameterIdList;
}
const std::set< uint32_t >& getFrontline03IdList()
{
   if( m_Frontline03IdList.size() == 0 )
      loadIdList( m_Frontline03Dat, m_Frontline03IdList );
   return m_Frontline03IdList;
}
const std::set< uint32_t >& getFrontline04IdList()
{
   if( m_Frontline04IdList.size() == 0 )
      loadIdList( m_Frontline04Dat, m_Frontline04IdList );
   return m_Frontline04IdList;
}
const std::set< uint32_t >& getFurnitureCatalogCategoryIdList()
{
   if( m_FurnitureCatalogCategoryIdList.size() == 0 )
      loadIdList( m_FurnitureCatalogCategoryDat, m_FurnitureCatalogCategoryIdList );
   return m_FurnitureCatalogCategoryIdList;
}
const std::set< uint32_t >& getFurnitureCatalogItemListIdList()
{
   if( m_FurnitureCatalogItemListIdList.size() == 0 )
      loadIdList( m_FurnitureCatalogItemListDat, m_FurnitureCatalogItemListIdList );
   return m_FurnitureCatalogItemListIdList;
}
const std::set< uint32_t >& getGardeningSeedIdList()
{
   if( m_GardeningSeedIdList.size() == 0 )
      loadIdList( m_GardeningSeedDat, m_GardeningSeedIdList );
   return m_GardeningSeedIdList;
}
const std::set< uint32_t >& getGatheringConditionIdList()
{
   if( m_GatheringConditionIdList.size() == 0 )
      loadIdList( m_GatheringConditionDat, m_GatheringConditionIdList );
   return m_GatheringConditionIdList;
}
const std::set< uint32_t >& getGatheringExpIdList()
{
   if( m_GatheringExpIdList.size() == 0 )
      loadIdList( m_GatheringExpDat, m_GatheringExpIdList );
   return m_GatheringExpIdList;
}
const std::set< uint32_t >& getGatheringItemIdList()
{
   if( m_GatheringItemIdList.size() == 0 )
      loadIdList( m_GatheringItemDat, m_GatheringItemIdList );
   return m_GatheringItemIdList;
}
const std::set< uint32_t >& getGatheringItemLevelConvertTableIdList()
{
   if( m_GatheringItemLevelConvertTableIdList.size() == 0 )
      loadIdList( m_GatheringItemLevelConvertTableDat, m_GatheringItemLevelConvertTableIdList );
   return m_GatheringItemLevelConvertTableIdList;
}
const std::set< uint32_t >& getGatheringItemPointIdList()
{
   if( m_GatheringItemPointIdList.size() == 0 )
      loadIdList( m_GatheringItemPointDat, m_GatheringItemPointIdList );
   return m_GatheringItemPointIdList;
}
const std::set< uint32_t >& getGatheringLeveIdList()
{
   if( m_GatheringLeveIdList.size() == 0 )
      loadIdList( m_GatheringLeveDat, m_GatheringLeveIdList );
   return m_GatheringLeveIdList;
}
const std::set< uint32_t >& getGatheringLeveRouteIdList()
{
   if( m_GatheringLeveRouteIdList.size() == 0 )
      loadIdList( m_GatheringLeveRouteDat, m_GatheringLeveRouteIdList );
   return m_GatheringLeveRouteIdList;
}
const std::set< uint32_t >& getGatheringLeveRuleIdList()
{
   if( m_GatheringLeveRuleIdList.size() == 0 )
      loadIdList( m_GatheringLeveRuleDat, m_GatheringLeveRuleIdList );
   return m_GatheringLeveRuleIdList;
}
const std::set< uint32_t >& getGatheringNotebookListIdList()
{
   if( m_GatheringNotebookListIdList.size() == 0 )
      loadIdList( m_GatheringNotebookListDat, m_GatheringNotebookListIdList );
   return m_GatheringNotebookListIdList;
}
const std::set< uint32_t >& getGatheringPointIdList()
{
   if( m_GatheringPointIdList.size() == 0 )
      loadIdList( m_GatheringPointDat, m_GatheringPointIdList );
   return m_GatheringPointIdList;
}
const std::set< uint32_t >& getGatheringPointBaseIdList()
{
   if( m_GatheringPointBaseIdList.size() == 0 )
      loadIdList( m_GatheringPointBaseDat, m_GatheringPointBaseIdList );
   return m_GatheringPointBaseIdList;
}
const std::set< uint32_t >& getGatheringPointBonusIdList()
{
   if( m_GatheringPointBonusIdList.size() == 0 )
      loadIdList( m_GatheringPointBonusDat, m_GatheringPointBonusIdList );
   return m_GatheringPointBonusIdList;
}
const std::set< uint32_t >& getGatheringPointBonusTypeIdList()
{
   if( m_GatheringPointBonusTypeIdList.size() == 0 )
      loadIdList( m_GatheringPointBonusTypeDat, m_GatheringPointBonusTypeIdList );
   return m_GatheringPointBonusTypeIdList;
}
const std::set< uint32_t >& getGatheringPointNameIdList()
{
   if( m_GatheringPointNameIdList.size() == 0 )
      loadIdList( m_GatheringPointNameDat, m_GatheringPointNameIdList );
   return m_GatheringPointNameIdList;
}
const std::set< uint32_t >& getGatheringPointTransientIdList()
{
   if( m_GatheringPointTransientIdList.size() == 0 )
      loadIdList( m_GatheringPointTransientDat, m_GatheringPointTransientIdList );
   return m_GatheringPointTransientIdList;
}
const std::set< uint32_t >& getGatheringRarePopTimeTableIdList()
{
   if( m_GatheringRarePopTimeTableIdList.size() == 0 )
      loadIdList( m_GatheringRarePopTimeTableDat, m_GatheringRarePopTimeTableIdList );
   return m_GatheringRarePopTimeTableIdList;
}
const std::set< uint32_t >& getGatheringSubCategoryIdList()
{
   if( m_GatheringSubCategoryIdList.size() == 0 )
      loadIdList( m_GatheringSubCategoryDat, m_GatheringSubCategoryIdList );
   return m_GatheringSubCategoryIdList;
}
const std::set< uint32_t >& getGatheringTypeIdList()
{
   if( m_GatheringTypeIdList.size() == 0 )
      loadIdList( m_GatheringTypeDat, m_GatheringTypeIdList );
   return m_GatheringTypeIdList;
}
const std::set< uint32_t >& getGcArmyCaptureTacticsIdList()
{
   if( m_GcArmyCaptureTacticsIdList.size() == 0 )
      loadIdList( m_GcArmyCaptureTacticsDat, m_GcArmyCaptureTacticsIdList );
   return m_GcArmyCaptureTacticsIdList;
}
const std::set< uint32_t >& getGcArmyExpeditionIdList()
{
   if( m_GcArmyExpeditionIdList.size() == 0 )
      loadIdList( m_GcArmyExpeditionDat, m_GcArmyExpeditionIdList );
   return m_GcArmyExpeditionIdList;
}
const std::set< uint32_t >& getGcArmyExpeditionMemberBonusIdList()
{
   if( m_GcArmyExpeditionMemberBonusIdList.size() == 0 )
      loadIdList( m_GcArmyExpeditionMemberBonusDat, m_GcArmyExpeditionMemberBonusIdList );
   return m_GcArmyExpeditionMemberBonusIdList;
}
const std::set< uint32_t >& getGcArmyExpeditionTypeIdList()
{
   if( m_GcArmyExpeditionTypeIdList.size() == 0 )
      loadIdList( m_GcArmyExpeditionTypeDat, m_GcArmyExpeditionTypeIdList );
   return m_GcArmyExpeditionTypeIdList;
}
const std::set< uint32_t >& getGcArmyMemberGrowIdList()
{
   if( m_GcArmyMemberGrowIdList.size() == 0 )
      loadIdList( m_GcArmyMemberGrowDat, m_GcArmyMemberGrowIdList );
   return m_GcArmyMemberGrowIdList;
}
const std::set< uint32_t >& getGcArmyTrainingIdList()
{
   if( m_GcArmyTrainingIdList.size() == 0 )
      loadIdList( m_GcArmyTrainingDat, m_GcArmyTrainingIdList );
   return m_GcArmyTrainingIdList;
}
const std::set< uint32_t >& getGCRankGridaniaFemaleTextIdList()
{
   if( m_GCRankGridaniaFemaleTextIdList.size() == 0 )
      loadIdList( m_GCRankGridaniaFemaleTextDat, m_GCRankGridaniaFemaleTextIdList );
   return m_GCRankGridaniaFemaleTextIdList;
}
const std::set< uint32_t >& getGCRankGridaniaMaleTextIdList()
{
   if( m_GCRankGridaniaMaleTextIdList.size() == 0 )
      loadIdList( m_GCRankGridaniaMaleTextDat, m_GCRankGridaniaMaleTextIdList );
   return m_GCRankGridaniaMaleTextIdList;
}
const std::set< uint32_t >& getGCRankLimsaFemaleTextIdList()
{
   if( m_GCRankLimsaFemaleTextIdList.size() == 0 )
      loadIdList( m_GCRankLimsaFemaleTextDat, m_GCRankLimsaFemaleTextIdList );
   return m_GCRankLimsaFemaleTextIdList;
}
const std::set< uint32_t >& getGCRankLimsaMaleTextIdList()
{
   if( m_GCRankLimsaMaleTextIdList.size() == 0 )
      loadIdList( m_GCRankLimsaMaleTextDat, m_GCRankLimsaMaleTextIdList );
   return m_GCRankLimsaMaleTextIdList;
}
const std::set< uint32_t >& getGCRankUldahFemaleTextIdList()
{
   if( m_GCRankUldahFemaleTextIdList.size() == 0 )
      loadIdList( m_GCRankUldahFemaleTextDat, m_GCRankUldahFemaleTextIdList );
   return m_GCRankUldahFemaleTextIdList;
}
const std::set< uint32_t >& getGCRankUldahMaleTextIdList()
{
   if( m_GCRankUldahMaleTextIdList.size() == 0 )
      loadIdList( m_GCRankUldahMaleTextDat, m_GCRankUldahMaleTextIdList );
   return m_GCRankUldahMaleTextIdList;
}
const std::set< uint32_t >& getGCScripShopCategoryIdList()
{
   if( m_GCScripShopCategoryIdList.size() == 0 )
      loadIdList( m_GCScripShopCategoryDat, m_GCScripShopCategoryIdList );
   return m_GCScripShopCategoryIdList;
}
const std::set< uint32_t >& getGCScripShopItemIdList()
{
   if( m_GCScripShopItemIdList.size() == 0 )
      loadIdList( m_GCScripShopItemDat, m_GCScripShopItemIdList );
   return m_GCScripShopItemIdList;
}
const std::set< uint32_t >& getGCShopIdList()
{
   if( m_GCShopIdList.size() == 0 )
      loadIdList( m_GCShopDat, m_GCShopIdList );
   return m_GCShopIdList;
}
const std::set< uint32_t >& getGCShopItemCategoryIdList()
{
   if( m_GCShopItemCategoryIdList.size() == 0 )
      loadIdList( m_GCShopItemCategoryDat, m_GCShopItemCategoryIdList );
   return m_GCShopItemCategoryIdList;
}
const std::set< uint32_t >& getGCSupplyDutyIdList()
{
   if( m_GCSupplyDutyIdList.size() == 0 )
      loadIdList( m_GCSupplyDutyDat, m_GCSupplyDutyIdList );
   return m_GCSupplyDutyIdList;
}
const std::set< uint32_t >& getGCSupplyDutyRewardIdList()
{
   if( m_GCSupplyDutyRewardIdList.size() == 0 )
      loadIdList( m_GCSupplyDutyRewardDat, m_GCSupplyDutyRewardIdList );
   return m_GCSupplyDutyRewardIdList;
}
const std::set< uint32_t >& getGeneralActionIdList()
{
   if( m_GeneralActionIdList.size() == 0 )
      loadIdList( m_GeneralActionDat, m_GeneralActionIdList );
   return m_GeneralActionIdList;
}
const std::set< uint32_t >& getGFATEIdList()
{
   if( m_GFATEIdList.size() == 0 )
      loadIdList( m_GFATEDat, m_GFATEIdList );
   return m_GFATEIdList;
}
const std::set< uint32_t >& getGFateClimbing2IdList()
{
   if( m_GFateClimbing2IdList.size() == 0 )
      loadIdList( m_GFateClimbing2Dat, m_GFateClimbing2IdList );
   return m_GFateClimbing2IdList;
}
const std::set< uint32_t >& getGFateClimbing2ContentIdList()
{
   if( m_GFateClimbing2ContentIdList.size() == 0 )
      loadIdList( m_GFateClimbing2ContentDat, m_GFateClimbing2ContentIdList );
   return m_GFateClimbing2ContentIdList;
}
const std::set< uint32_t >& getGFateClimbing2TotemTypeIdList()
{
   if( m_GFateClimbing2TotemTypeIdList.size() == 0 )
      loadIdList( m_GFateClimbing2TotemTypeDat, m_GFateClimbing2TotemTypeIdList );
   return m_GFateClimbing2TotemTypeIdList;
}
const std::set< uint32_t >& getGFateRideShootingIdList()
{
   if( m_GFateRideShootingIdList.size() == 0 )
      loadIdList( m_GFateRideShootingDat, m_GFateRideShootingIdList );
   return m_GFateRideShootingIdList;
}
const std::set< uint32_t >& getGilShopIdList()
{
   if( m_GilShopIdList.size() == 0 )
      loadIdList( m_GilShopDat, m_GilShopIdList );
   return m_GilShopIdList;
}
const std::set< uint32_t >& getGilShopItemIdList()
{
   if( m_GilShopItemIdList.size() == 0 )
      loadIdList( m_GilShopItemDat, m_GilShopItemIdList );
   return m_GilShopItemIdList;
}
const std::set< uint32_t >& getGimmickAccessorIdList()
{
   if( m_GimmickAccessorIdList.size() == 0 )
      loadIdList( m_GimmickAccessorDat, m_GimmickAccessorIdList );
   return m_GimmickAccessorIdList;
}
const std::set< uint32_t >& getGimmickJumpIdList()
{
   if( m_GimmickJumpIdList.size() == 0 )
      loadIdList( m_GimmickJumpDat, m_GimmickJumpIdList );
   return m_GimmickJumpIdList;
}
const std::set< uint32_t >& getGimmickRectIdList()
{
   if( m_GimmickRectIdList.size() == 0 )
      loadIdList( m_GimmickRectDat, m_GimmickRectIdList );
   return m_GimmickRectIdList;
}
const std::set< uint32_t >& getGoldSaucerArcadeMachineIdList()
{
   if( m_GoldSaucerArcadeMachineIdList.size() == 0 )
      loadIdList( m_GoldSaucerArcadeMachineDat, m_GoldSaucerArcadeMachineIdList );
   return m_GoldSaucerArcadeMachineIdList;
}
const std::set< uint32_t >& getGoldSaucerTextDataIdList()
{
   if( m_GoldSaucerTextDataIdList.size() == 0 )
      loadIdList( m_GoldSaucerTextDataDat, m_GoldSaucerTextDataIdList );
   return m_GoldSaucerTextDataIdList;
}
const std::set< uint32_t >& getGrandCompanyIdList()
{
   if( m_GrandCompanyIdList.size() == 0 )
      loadIdList( m_GrandCompanyDat, m_GrandCompanyIdList );
   return m_GrandCompanyIdList;
}
const std::set< uint32_t >& getGrandCompanyRankIdList()
{
   if( m_GrandCompanyRankIdList.size() == 0 )
      loadIdList( m_GrandCompanyRankDat, m_GrandCompanyRankIdList );
   return m_GrandCompanyRankIdList;
}
const std::set< uint32_t >& getGroupPoseFrameIdList()
{
   if( m_GroupPoseFrameIdList.size() == 0 )
      loadIdList( m_GroupPoseFrameDat, m_GroupPoseFrameIdList );
   return m_GroupPoseFrameIdList;
}
const std::set< uint32_t >& getGroupPoseStampIdList()
{
   if( m_GroupPoseStampIdList.size() == 0 )
      loadIdList( m_GroupPoseStampDat, m_GroupPoseStampIdList );
   return m_GroupPoseStampIdList;
}
const std::set< uint32_t >& getGroupPoseStampCategoryIdList()
{
   if( m_GroupPoseStampCategoryIdList.size() == 0 )
      loadIdList( m_GroupPoseStampCategoryDat, m_GroupPoseStampCategoryIdList );
   return m_GroupPoseStampCategoryIdList;
}
const std::set< uint32_t >& getGuardianDeityIdList()
{
   if( m_GuardianDeityIdList.size() == 0 )
      loadIdList( m_GuardianDeityDat, m_GuardianDeityIdList );
   return m_GuardianDeityIdList;
}
const std::set< uint32_t >& getGuideIdList()
{
   if( m_GuideIdList.size() == 0 )
      loadIdList( m_GuideDat, m_GuideIdList );
   return m_GuideIdList;
}
const std::set< uint32_t >& getGuidePageIdList()
{
   if( m_GuidePageIdList.size() == 0 )
      loadIdList( m_GuidePageDat, m_GuidePageIdList );
   return m_GuidePageIdList;
}
const std::set< uint32_t >& getGuidePageStringIdList()
{
   if( m_GuidePageStringIdList.size() == 0 )
      loadIdList( m_GuidePageStringDat, m_GuidePageStringIdList );
   return m_GuidePageStringIdList;
}
const std::set< uint32_t >& getGuideTitleIdList()
{
   if( m_GuideTitleIdList.size() == 0 )
      loadIdList( m_GuideTitleDat, m_GuideTitleIdList );
   return m_GuideTitleIdList;
}
const std::set< uint32_t >& getGuildleveAssignmentIdList()
{
   if( m_GuildleveAssignmentIdList.size() == 0 )
      loadIdList( m_GuildleveAssignmentDat, m_GuildleveAssignmentIdList );
   return m_GuildleveAssignmentIdList;
}
const std::set< uint32_t >& getGuildleveAssignmentCategoryIdList()
{
   if( m_GuildleveAssignmentCategoryIdList.size() == 0 )
      loadIdList( m_GuildleveAssignmentCategoryDat, m_GuildleveAssignmentCategoryIdList );
   return m_GuildleveAssignmentCategoryIdList;
}
const std::set< uint32_t >& getGuildOrderIdList()
{
   if( m_GuildOrderIdList.size() == 0 )
      loadIdList( m_GuildOrderDat, m_GuildOrderIdList );
   return m_GuildOrderIdList;
}
const std::set< uint32_t >& getGuildOrderGuideIdList()
{
   if( m_GuildOrderGuideIdList.size() == 0 )
      loadIdList( m_GuildOrderGuideDat, m_GuildOrderGuideIdList );
   return m_GuildOrderGuideIdList;
}
const std::set< uint32_t >& getGuildOrderOfficerIdList()
{
   if( m_GuildOrderOfficerIdList.size() == 0 )
      loadIdList( m_GuildOrderOfficerDat, m_GuildOrderOfficerIdList );
   return m_GuildOrderOfficerIdList;
}
const std::set< uint32_t >& getHairMakeTypeIdList()
{
   if( m_HairMakeTypeIdList.size() == 0 )
      loadIdList( m_HairMakeTypeDat, m_HairMakeTypeIdList );
   return m_HairMakeTypeIdList;
}
const std::set< uint32_t >& getHouseRetainerPoseIdList()
{
   if( m_HouseRetainerPoseIdList.size() == 0 )
      loadIdList( m_HouseRetainerPoseDat, m_HouseRetainerPoseIdList );
   return m_HouseRetainerPoseIdList;
}
const std::set< uint32_t >& getHousingAethernetIdList()
{
   if( m_HousingAethernetIdList.size() == 0 )
      loadIdList( m_HousingAethernetDat, m_HousingAethernetIdList );
   return m_HousingAethernetIdList;
}
const std::set< uint32_t >& getHousingAppealIdList()
{
   if( m_HousingAppealIdList.size() == 0 )
      loadIdList( m_HousingAppealDat, m_HousingAppealIdList );
   return m_HousingAppealIdList;
}
const std::set< uint32_t >& getHousingEmploymentNpcListIdList()
{
   if( m_HousingEmploymentNpcListIdList.size() == 0 )
      loadIdList( m_HousingEmploymentNpcListDat, m_HousingEmploymentNpcListIdList );
   return m_HousingEmploymentNpcListIdList;
}
const std::set< uint32_t >& getHousingEmploymentNpcRaceIdList()
{
   if( m_HousingEmploymentNpcRaceIdList.size() == 0 )
      loadIdList( m_HousingEmploymentNpcRaceDat, m_HousingEmploymentNpcRaceIdList );
   return m_HousingEmploymentNpcRaceIdList;
}
const std::set< uint32_t >& getHousingExteriorIdList()
{
   if( m_HousingExteriorIdList.size() == 0 )
      loadIdList( m_HousingExteriorDat, m_HousingExteriorIdList );
   return m_HousingExteriorIdList;
}
const std::set< uint32_t >& getHousingFurnitureIdList()
{
   if( m_HousingFurnitureIdList.size() == 0 )
      loadIdList( m_HousingFurnitureDat, m_HousingFurnitureIdList );
   return m_HousingFurnitureIdList;
}
const std::set< uint32_t >& getHousingLandSetIdList()
{
   if( m_HousingLandSetIdList.size() == 0 )
      loadIdList( m_HousingLandSetDat, m_HousingLandSetIdList );
   return m_HousingLandSetIdList;
}
const std::set< uint32_t >& getHousingMapMarkerInfoIdList()
{
   if( m_HousingMapMarkerInfoIdList.size() == 0 )
      loadIdList( m_HousingMapMarkerInfoDat, m_HousingMapMarkerInfoIdList );
   return m_HousingMapMarkerInfoIdList;
}
const std::set< uint32_t >& getHousingMerchantPoseIdList()
{
   if( m_HousingMerchantPoseIdList.size() == 0 )
      loadIdList( m_HousingMerchantPoseDat, m_HousingMerchantPoseIdList );
   return m_HousingMerchantPoseIdList;
}
const std::set< uint32_t >& getHousingPlacementIdList()
{
   if( m_HousingPlacementIdList.size() == 0 )
      loadIdList( m_HousingPlacementDat, m_HousingPlacementIdList );
   return m_HousingPlacementIdList;
}
const std::set< uint32_t >& getHousingPresetIdList()
{
   if( m_HousingPresetIdList.size() == 0 )
      loadIdList( m_HousingPresetDat, m_HousingPresetIdList );
   return m_HousingPresetIdList;
}
const std::set< uint32_t >& getHousingUnitedExteriorIdList()
{
   if( m_HousingUnitedExteriorIdList.size() == 0 )
      loadIdList( m_HousingUnitedExteriorDat, m_HousingUnitedExteriorIdList );
   return m_HousingUnitedExteriorIdList;
}
const std::set< uint32_t >& getHousingYardObjectIdList()
{
   if( m_HousingYardObjectIdList.size() == 0 )
      loadIdList( m_HousingYardObjectDat, m_HousingYardObjectIdList );
   return m_HousingYardObjectIdList;
}
const std::set< uint32_t >& getHowToIdList()
{
   if( m_HowToIdList.size() == 0 )
      loadIdList( m_HowToDat, m_HowToIdList );
   return m_HowToIdList;
}
const std::set< uint32_t >& getHowToCategoryIdList()
{
   if( m_HowToCategoryIdList.size() == 0 )
      loadIdList( m_HowToCategoryDat, m_HowToCategoryIdList );
   return m_HowToCategoryIdList;
}
const std::set< uint32_t >& getHowToPageIdList()
{
   if( m_HowToPageIdList.size() == 0 )
      loadIdList( m_HowToPageDat, m_HowToPageIdList );
   return m_HowToPageIdList;
}
const std::set< uint32_t >& getHugeCraftworksNpcIdList()
{
   if( m_HugeCraftworksNpcIdList.size() == 0 )
      loadIdList( m_HugeCraftworksNpcDat, m_HugeCraftworksNpcIdList );
   return m_HugeCraftworksNpcIdList;
}
const std::set< uint32_t >& getHugeCraftworksRankIdList()
{
   if( m_HugeCraftworksRankIdList.size() == 0 )
      loadIdList( m_HugeCraftworksRankDat, m_HugeCraftworksRankIdList );
   return m_HugeCraftworksRankIdList;
}
const std::set< uint32_t >& getHWDAnnounceIdList()
{
   if( m_HWDAnnounceIdList.size() == 0 )
      loadIdList( m_HWDAnnounceDat, m_HWDAnnounceIdList );
   return m_HWDAnnounceIdList;
}
const std::set< uint32_t >& getHWDCrafterSupplyIdList()
{
   if( m_HWDCrafterSupplyIdList.size() == 0 )
      loadIdList( m_HWDCrafterSupplyDat, m_HWDCrafterSupplyIdList );
   return m_HWDCrafterSupplyIdList;
}
const std::set< uint32_t >& getHWDCrafterSupplyRewardIdList()
{
   if( m_HWDCrafterSupplyRewardIdList.size() == 0 )
      loadIdList( m_HWDCrafterSupplyRewardDat, m_HWDCrafterSupplyRewardIdList );
   return m_HWDCrafterSupplyRewardIdList;
}
const std::set< uint32_t >& getHWDCrafterSupplyTermIdList()
{
   if( m_HWDCrafterSupplyTermIdList.size() == 0 )
      loadIdList( m_HWDCrafterSupplyTermDat, m_HWDCrafterSupplyTermIdList );
   return m_HWDCrafterSupplyTermIdList;
}
const std::set< uint32_t >& getHWDDevLayerControlIdList()
{
   if( m_HWDDevLayerControlIdList.size() == 0 )
      loadIdList( m_HWDDevLayerControlDat, m_HWDDevLayerControlIdList );
   return m_HWDDevLayerControlIdList;
}
const std::set< uint32_t >& getHWDDevLevelUIIdList()
{
   if( m_HWDDevLevelUIIdList.size() == 0 )
      loadIdList( m_HWDDevLevelUIDat, m_HWDDevLevelUIIdList );
   return m_HWDDevLevelUIIdList;
}
const std::set< uint32_t >& getHWDDevLivelyIdList()
{
   if( m_HWDDevLivelyIdList.size() == 0 )
      loadIdList( m_HWDDevLivelyDat, m_HWDDevLivelyIdList );
   return m_HWDDevLivelyIdList;
}
const std::set< uint32_t >& getHWDDevProgressIdList()
{
   if( m_HWDDevProgressIdList.size() == 0 )
      loadIdList( m_HWDDevProgressDat, m_HWDDevProgressIdList );
   return m_HWDDevProgressIdList;
}
const std::set< uint32_t >& getHWDGathereInspectTermIdList()
{
   if( m_HWDGathereInspectTermIdList.size() == 0 )
      loadIdList( m_HWDGathereInspectTermDat, m_HWDGathereInspectTermIdList );
   return m_HWDGathereInspectTermIdList;
}
const std::set< uint32_t >& getHWDGathererInspectionIdList()
{
   if( m_HWDGathererInspectionIdList.size() == 0 )
      loadIdList( m_HWDGathererInspectionDat, m_HWDGathererInspectionIdList );
   return m_HWDGathererInspectionIdList;
}
const std::set< uint32_t >& getHWDGathererInspectionRewardIdList()
{
   if( m_HWDGathererInspectionRewardIdList.size() == 0 )
      loadIdList( m_HWDGathererInspectionRewardDat, m_HWDGathererInspectionRewardIdList );
   return m_HWDGathererInspectionRewardIdList;
}
const std::set< uint32_t >& getHWDInfoBoardArticleIdList()
{
   if( m_HWDInfoBoardArticleIdList.size() == 0 )
      loadIdList( m_HWDInfoBoardArticleDat, m_HWDInfoBoardArticleIdList );
   return m_HWDInfoBoardArticleIdList;
}
const std::set< uint32_t >& getHWDInfoBoardArticleTransientIdList()
{
   if( m_HWDInfoBoardArticleTransientIdList.size() == 0 )
      loadIdList( m_HWDInfoBoardArticleTransientDat, m_HWDInfoBoardArticleTransientIdList );
   return m_HWDInfoBoardArticleTransientIdList;
}
const std::set< uint32_t >& getHWDInfoBoardArticleTypeIdList()
{
   if( m_HWDInfoBoardArticleTypeIdList.size() == 0 )
      loadIdList( m_HWDInfoBoardArticleTypeDat, m_HWDInfoBoardArticleTypeIdList );
   return m_HWDInfoBoardArticleTypeIdList;
}
const std::set< uint32_t >& getHWDLevelChangeDeceptionIdList()
{
   if( m_HWDLevelChangeDeceptionIdList.size() == 0 )
      loadIdList( m_HWDLevelChangeDeceptionDat, m_HWDLevelChangeDeceptionIdList );
   return m_HWDLevelChangeDeceptionIdList;
}
const std::set< uint32_t >& getHWDSharedGroupIdList()
{
   if( m_HWDSharedGroupIdList.size() == 0 )
      loadIdList( m_HWDSharedGroupDat, m_HWDSharedGroupIdList );
   return m_HWDSharedGroupIdList;
}
const std::set< uint32_t >& getHWDSharedGroupControlParamIdList()
{
   if( m_HWDSharedGroupControlParamIdList.size() == 0 )
      loadIdList( m_HWDSharedGroupControlParamDat, m_HWDSharedGroupControlParamIdList );
   return m_HWDSharedGroupControlParamIdList;
}
const std::set< uint32_t >& getIKDContentBonusIdList()
{
   if( m_IKDContentBonusIdList.size() == 0 )
      loadIdList( m_IKDContentBonusDat, m_IKDContentBonusIdList );
   return m_IKDContentBonusIdList;
}
const std::set< uint32_t >& getIKDFishParamIdList()
{
   if( m_IKDFishParamIdList.size() == 0 )
      loadIdList( m_IKDFishParamDat, m_IKDFishParamIdList );
   return m_IKDFishParamIdList;
}
const std::set< uint32_t >& getIKDRouteIdList()
{
   if( m_IKDRouteIdList.size() == 0 )
      loadIdList( m_IKDRouteDat, m_IKDRouteIdList );
   return m_IKDRouteIdList;
}
const std::set< uint32_t >& getIKDRouteTableIdList()
{
   if( m_IKDRouteTableIdList.size() == 0 )
      loadIdList( m_IKDRouteTableDat, m_IKDRouteTableIdList );
   return m_IKDRouteTableIdList;
}
const std::set< uint32_t >& getIKDSpotIdList()
{
   if( m_IKDSpotIdList.size() == 0 )
      loadIdList( m_IKDSpotDat, m_IKDSpotIdList );
   return m_IKDSpotIdList;
}
const std::set< uint32_t >& getInclusionShopIdList()
{
   if( m_InclusionShopIdList.size() == 0 )
      loadIdList( m_InclusionShopDat, m_InclusionShopIdList );
   return m_InclusionShopIdList;
}
const std::set< uint32_t >& getInclusionShopCategoryIdList()
{
   if( m_InclusionShopCategoryIdList.size() == 0 )
      loadIdList( m_InclusionShopCategoryDat, m_InclusionShopCategoryIdList );
   return m_InclusionShopCategoryIdList;
}
const std::set< uint32_t >& getInclusionShopSeriesIdList()
{
   if( m_InclusionShopSeriesIdList.size() == 0 )
      loadIdList( m_InclusionShopSeriesDat, m_InclusionShopSeriesIdList );
   return m_InclusionShopSeriesIdList;
}
const std::set< uint32_t >& getIndividualWeatherIdList()
{
   if( m_IndividualWeatherIdList.size() == 0 )
      loadIdList( m_IndividualWeatherDat, m_IndividualWeatherIdList );
   return m_IndividualWeatherIdList;
}
const std::set< uint32_t >& getInstanceContentIdList()
{
   if( m_InstanceContentIdList.size() == 0 )
      loadIdList( m_InstanceContentDat, m_InstanceContentIdList );
   return m_InstanceContentIdList;
}
const std::set< uint32_t >& getInstanceContentBuffIdList()
{
   if( m_InstanceContentBuffIdList.size() == 0 )
      loadIdList( m_InstanceContentBuffDat, m_InstanceContentBuffIdList );
   return m_InstanceContentBuffIdList;
}
const std::set< uint32_t >& getInstanceContentCSBonusIdList()
{
   if( m_InstanceContentCSBonusIdList.size() == 0 )
      loadIdList( m_InstanceContentCSBonusDat, m_InstanceContentCSBonusIdList );
   return m_InstanceContentCSBonusIdList;
}
const std::set< uint32_t >& getInstanceContentGuideIdList()
{
   if( m_InstanceContentGuideIdList.size() == 0 )
      loadIdList( m_InstanceContentGuideDat, m_InstanceContentGuideIdList );
   return m_InstanceContentGuideIdList;
}
const std::set< uint32_t >& getInstanceContentTextDataIdList()
{
   if( m_InstanceContentTextDataIdList.size() == 0 )
      loadIdList( m_InstanceContentTextDataDat, m_InstanceContentTextDataIdList );
   return m_InstanceContentTextDataIdList;
}
const std::set< uint32_t >& getItemIdList()
{
   if( m_ItemIdList.size() == 0 )
      loadIdList( m_ItemDat, m_ItemIdList );
   return m_ItemIdList;
}
const std::set< uint32_t >& getItemActionIdList()
{
   if( m_ItemActionIdList.size() == 0 )
      loadIdList( m_ItemActionDat, m_ItemActionIdList );
   return m_ItemActionIdList;
}
const std::set< uint32_t >& getItemActionTelepoIdList()
{
   if( m_ItemActionTelepoIdList.size() == 0 )
      loadIdList( m_ItemActionTelepoDat, m_ItemActionTelepoIdList );
   return m_ItemActionTelepoIdList;
}
const std::set< uint32_t >& getItemBarterCheckIdList()
{
   if( m_ItemBarterCheckIdList.size() == 0 )
      loadIdList( m_ItemBarterCheckDat, m_ItemBarterCheckIdList );
   return m_ItemBarterCheckIdList;
}
const std::set< uint32_t >& getItemFoodIdList()
{
   if( m_ItemFoodIdList.size() == 0 )
      loadIdList( m_ItemFoodDat, m_ItemFoodIdList );
   return m_ItemFoodIdList;
}
const std::set< uint32_t >& getItemLevelIdList()
{
   if( m_ItemLevelIdList.size() == 0 )
      loadIdList( m_ItemLevelDat, m_ItemLevelIdList );
   return m_ItemLevelIdList;
}
const std::set< uint32_t >& getItemSearchCategoryIdList()
{
   if( m_ItemSearchCategoryIdList.size() == 0 )
      loadIdList( m_ItemSearchCategoryDat, m_ItemSearchCategoryIdList );
   return m_ItemSearchCategoryIdList;
}
const std::set< uint32_t >& getItemSeriesIdList()
{
   if( m_ItemSeriesIdList.size() == 0 )
      loadIdList( m_ItemSeriesDat, m_ItemSeriesIdList );
   return m_ItemSeriesIdList;
}
const std::set< uint32_t >& getItemSortCategoryIdList()
{
   if( m_ItemSortCategoryIdList.size() == 0 )
      loadIdList( m_ItemSortCategoryDat, m_ItemSortCategoryIdList );
   return m_ItemSortCategoryIdList;
}
const std::set< uint32_t >& getItemSpecialBonusIdList()
{
   if( m_ItemSpecialBonusIdList.size() == 0 )
      loadIdList( m_ItemSpecialBonusDat, m_ItemSpecialBonusIdList );
   return m_ItemSpecialBonusIdList;
}
const std::set< uint32_t >& getItemUICategoryIdList()
{
   if( m_ItemUICategoryIdList.size() == 0 )
      loadIdList( m_ItemUICategoryDat, m_ItemUICategoryIdList );
   return m_ItemUICategoryIdList;
}
const std::set< uint32_t >& getJobHudManualIdList()
{
   if( m_JobHudManualIdList.size() == 0 )
      loadIdList( m_JobHudManualDat, m_JobHudManualIdList );
   return m_JobHudManualIdList;
}
const std::set< uint32_t >& getJobHudManualPriorityIdList()
{
   if( m_JobHudManualPriorityIdList.size() == 0 )
      loadIdList( m_JobHudManualPriorityDat, m_JobHudManualPriorityIdList );
   return m_JobHudManualPriorityIdList;
}
const std::set< uint32_t >& getJournalCategoryIdList()
{
   if( m_JournalCategoryIdList.size() == 0 )
      loadIdList( m_JournalCategoryDat, m_JournalCategoryIdList );
   return m_JournalCategoryIdList;
}
const std::set< uint32_t >& getJournalGenreIdList()
{
   if( m_JournalGenreIdList.size() == 0 )
      loadIdList( m_JournalGenreDat, m_JournalGenreIdList );
   return m_JournalGenreIdList;
}
const std::set< uint32_t >& getJournalSectionIdList()
{
   if( m_JournalSectionIdList.size() == 0 )
      loadIdList( m_JournalSectionDat, m_JournalSectionIdList );
   return m_JournalSectionIdList;
}
const std::set< uint32_t >& getKnockbackIdList()
{
   if( m_KnockbackIdList.size() == 0 )
      loadIdList( m_KnockbackDat, m_KnockbackIdList );
   return m_KnockbackIdList;
}
const std::set< uint32_t >& getLegacyQuestIdList()
{
   if( m_LegacyQuestIdList.size() == 0 )
      loadIdList( m_LegacyQuestDat, m_LegacyQuestIdList );
   return m_LegacyQuestIdList;
}
const std::set< uint32_t >& getLeveIdList()
{
   if( m_LeveIdList.size() == 0 )
      loadIdList( m_LeveDat, m_LeveIdList );
   return m_LeveIdList;
}
const std::set< uint32_t >& getLeveAssignmentTypeIdList()
{
   if( m_LeveAssignmentTypeIdList.size() == 0 )
      loadIdList( m_LeveAssignmentTypeDat, m_LeveAssignmentTypeIdList );
   return m_LeveAssignmentTypeIdList;
}
const std::set< uint32_t >& getLeveClientIdList()
{
   if( m_LeveClientIdList.size() == 0 )
      loadIdList( m_LeveClientDat, m_LeveClientIdList );
   return m_LeveClientIdList;
}
const std::set< uint32_t >& getLevelIdList()
{
   if( m_LevelIdList.size() == 0 )
      loadIdList( m_LevelDat, m_LevelIdList );
   return m_LevelIdList;
}
const std::set< uint32_t >& getLeveRewardItemIdList()
{
   if( m_LeveRewardItemIdList.size() == 0 )
      loadIdList( m_LeveRewardItemDat, m_LeveRewardItemIdList );
   return m_LeveRewardItemIdList;
}
const std::set< uint32_t >& getLeveRewardItemGroupIdList()
{
   if( m_LeveRewardItemGroupIdList.size() == 0 )
      loadIdList( m_LeveRewardItemGroupDat, m_LeveRewardItemGroupIdList );
   return m_LeveRewardItemGroupIdList;
}
const std::set< uint32_t >& getLeveStringIdList()
{
   if( m_LeveStringIdList.size() == 0 )
      loadIdList( m_LeveStringDat, m_LeveStringIdList );
   return m_LeveStringIdList;
}
const std::set< uint32_t >& getLeveVfxIdList()
{
   if( m_LeveVfxIdList.size() == 0 )
      loadIdList( m_LeveVfxDat, m_LeveVfxIdList );
   return m_LeveVfxIdList;
}
const std::set< uint32_t >& getLobbyIdList()
{
   if( m_LobbyIdList.size() == 0 )
      loadIdList( m_LobbyDat, m_LobbyIdList );
   return m_LobbyIdList;
}
const std::set< uint32_t >& getLogFilterIdList()
{
   if( m_LogFilterIdList.size() == 0 )
      loadIdList( m_LogFilterDat, m_LogFilterIdList );
   return m_LogFilterIdList;
}
const std::set< uint32_t >& getLogKindIdList()
{
   if( m_LogKindIdList.size() == 0 )
      loadIdList( m_LogKindDat, m_LogKindIdList );
   return m_LogKindIdList;
}
const std::set< uint32_t >& getLogMessageIdList()
{
   if( m_LogMessageIdList.size() == 0 )
      loadIdList( m_LogMessageDat, m_LogMessageIdList );
   return m_LogMessageIdList;
}
const std::set< uint32_t >& getLotteryExchangeShopIdList()
{
   if( m_LotteryExchangeShopIdList.size() == 0 )
      loadIdList( m_LotteryExchangeShopDat, m_LotteryExchangeShopIdList );
   return m_LotteryExchangeShopIdList;
}
const std::set< uint32_t >& getMacroIconIdList()
{
   if( m_MacroIconIdList.size() == 0 )
      loadIdList( m_MacroIconDat, m_MacroIconIdList );
   return m_MacroIconIdList;
}
const std::set< uint32_t >& getMacroIconRedirectOldIdList()
{
   if( m_MacroIconRedirectOldIdList.size() == 0 )
      loadIdList( m_MacroIconRedirectOldDat, m_MacroIconRedirectOldIdList );
   return m_MacroIconRedirectOldIdList;
}
const std::set< uint32_t >& getMainCommandIdList()
{
   if( m_MainCommandIdList.size() == 0 )
      loadIdList( m_MainCommandDat, m_MainCommandIdList );
   return m_MainCommandIdList;
}
const std::set< uint32_t >& getMainCommandCategoryIdList()
{
   if( m_MainCommandCategoryIdList.size() == 0 )
      loadIdList( m_MainCommandCategoryDat, m_MainCommandCategoryIdList );
   return m_MainCommandCategoryIdList;
}
const std::set< uint32_t >& getManeuversArmorIdList()
{
   if( m_ManeuversArmorIdList.size() == 0 )
      loadIdList( m_ManeuversArmorDat, m_ManeuversArmorIdList );
   return m_ManeuversArmorIdList;
}
const std::set< uint32_t >& getMapIdList()
{
   if( m_MapIdList.size() == 0 )
      loadIdList( m_MapDat, m_MapIdList );
   return m_MapIdList;
}
const std::set< uint32_t >& getMapMarkerIdList()
{
   if( m_MapMarkerIdList.size() == 0 )
      loadIdList( m_MapMarkerDat, m_MapMarkerIdList );
   return m_MapMarkerIdList;
}
const std::set< uint32_t >& getMapMarkerRegionIdList()
{
   if( m_MapMarkerRegionIdList.size() == 0 )
      loadIdList( m_MapMarkerRegionDat, m_MapMarkerRegionIdList );
   return m_MapMarkerRegionIdList;
}
const std::set< uint32_t >& getMapSymbolIdList()
{
   if( m_MapSymbolIdList.size() == 0 )
      loadIdList( m_MapSymbolDat, m_MapSymbolIdList );
   return m_MapSymbolIdList;
}
const std::set< uint32_t >& getMarkerIdList()
{
   if( m_MarkerIdList.size() == 0 )
      loadIdList( m_MarkerDat, m_MarkerIdList );
   return m_MarkerIdList;
}
const std::set< uint32_t >& getMasterpieceSupplyDutyIdList()
{
   if( m_MasterpieceSupplyDutyIdList.size() == 0 )
      loadIdList( m_MasterpieceSupplyDutyDat, m_MasterpieceSupplyDutyIdList );
   return m_MasterpieceSupplyDutyIdList;
}
const std::set< uint32_t >& getMasterpieceSupplyMultiplierIdList()
{
   if( m_MasterpieceSupplyMultiplierIdList.size() == 0 )
      loadIdList( m_MasterpieceSupplyMultiplierDat, m_MasterpieceSupplyMultiplierIdList );
   return m_MasterpieceSupplyMultiplierIdList;
}
const std::set< uint32_t >& getMateriaIdList()
{
   if( m_MateriaIdList.size() == 0 )
      loadIdList( m_MateriaDat, m_MateriaIdList );
   return m_MateriaIdList;
}
const std::set< uint32_t >& getMateriaJoinRateIdList()
{
   if( m_MateriaJoinRateIdList.size() == 0 )
      loadIdList( m_MateriaJoinRateDat, m_MateriaJoinRateIdList );
   return m_MateriaJoinRateIdList;
}
const std::set< uint32_t >& getMateriaJoinRateGatherCraftIdList()
{
   if( m_MateriaJoinRateGatherCraftIdList.size() == 0 )
      loadIdList( m_MateriaJoinRateGatherCraftDat, m_MateriaJoinRateGatherCraftIdList );
   return m_MateriaJoinRateGatherCraftIdList;
}
const std::set< uint32_t >& getMateriaTomestoneRateIdList()
{
   if( m_MateriaTomestoneRateIdList.size() == 0 )
      loadIdList( m_MateriaTomestoneRateDat, m_MateriaTomestoneRateIdList );
   return m_MateriaTomestoneRateIdList;
}
const std::set< uint32_t >& getMiniGameRAIdList()
{
   if( m_MiniGameRAIdList.size() == 0 )
      loadIdList( m_MiniGameRADat, m_MiniGameRAIdList );
   return m_MiniGameRAIdList;
}
const std::set< uint32_t >& getMinionRaceIdList()
{
   if( m_MinionRaceIdList.size() == 0 )
      loadIdList( m_MinionRaceDat, m_MinionRaceIdList );
   return m_MinionRaceIdList;
}
const std::set< uint32_t >& getMinionRulesIdList()
{
   if( m_MinionRulesIdList.size() == 0 )
      loadIdList( m_MinionRulesDat, m_MinionRulesIdList );
   return m_MinionRulesIdList;
}
const std::set< uint32_t >& getMinionSkillTypeIdList()
{
   if( m_MinionSkillTypeIdList.size() == 0 )
      loadIdList( m_MinionSkillTypeDat, m_MinionSkillTypeIdList );
   return m_MinionSkillTypeIdList;
}
const std::set< uint32_t >& getMobHuntOrderIdList()
{
   if( m_MobHuntOrderIdList.size() == 0 )
      loadIdList( m_MobHuntOrderDat, m_MobHuntOrderIdList );
   return m_MobHuntOrderIdList;
}
const std::set< uint32_t >& getMobHuntOrderTypeIdList()
{
   if( m_MobHuntOrderTypeIdList.size() == 0 )
      loadIdList( m_MobHuntOrderTypeDat, m_MobHuntOrderTypeIdList );
   return m_MobHuntOrderTypeIdList;
}
const std::set< uint32_t >& getMobHuntRewardIdList()
{
   if( m_MobHuntRewardIdList.size() == 0 )
      loadIdList( m_MobHuntRewardDat, m_MobHuntRewardIdList );
   return m_MobHuntRewardIdList;
}
const std::set< uint32_t >& getMobHuntRewardCapIdList()
{
   if( m_MobHuntRewardCapIdList.size() == 0 )
      loadIdList( m_MobHuntRewardCapDat, m_MobHuntRewardCapIdList );
   return m_MobHuntRewardCapIdList;
}
const std::set< uint32_t >& getMobHuntTargetIdList()
{
   if( m_MobHuntTargetIdList.size() == 0 )
      loadIdList( m_MobHuntTargetDat, m_MobHuntTargetIdList );
   return m_MobHuntTargetIdList;
}
const std::set< uint32_t >& getModelCharaIdList()
{
   if( m_ModelCharaIdList.size() == 0 )
      loadIdList( m_ModelCharaDat, m_ModelCharaIdList );
   return m_ModelCharaIdList;
}
const std::set< uint32_t >& getModelSkeletonIdList()
{
   if( m_ModelSkeletonIdList.size() == 0 )
      loadIdList( m_ModelSkeletonDat, m_ModelSkeletonIdList );
   return m_ModelSkeletonIdList;
}
const std::set< uint32_t >& getModelStateIdList()
{
   if( m_ModelStateIdList.size() == 0 )
      loadIdList( m_ModelStateDat, m_ModelStateIdList );
   return m_ModelStateIdList;
}
const std::set< uint32_t >& getMonsterNoteIdList()
{
   if( m_MonsterNoteIdList.size() == 0 )
      loadIdList( m_MonsterNoteDat, m_MonsterNoteIdList );
   return m_MonsterNoteIdList;
}
const std::set< uint32_t >& getMonsterNoteTargetIdList()
{
   if( m_MonsterNoteTargetIdList.size() == 0 )
      loadIdList( m_MonsterNoteTargetDat, m_MonsterNoteTargetIdList );
   return m_MonsterNoteTargetIdList;
}
const std::set< uint32_t >& getMotionTimelineIdList()
{
   if( m_MotionTimelineIdList.size() == 0 )
      loadIdList( m_MotionTimelineDat, m_MotionTimelineIdList );
   return m_MotionTimelineIdList;
}
const std::set< uint32_t >& getMotionTimelineBlendTableIdList()
{
   if( m_MotionTimelineBlendTableIdList.size() == 0 )
      loadIdList( m_MotionTimelineBlendTableDat, m_MotionTimelineBlendTableIdList );
   return m_MotionTimelineBlendTableIdList;
}
const std::set< uint32_t >& getMountIdList()
{
   if( m_MountIdList.size() == 0 )
      loadIdList( m_MountDat, m_MountIdList );
   return m_MountIdList;
}
const std::set< uint32_t >& getMountActionIdList()
{
   if( m_MountActionIdList.size() == 0 )
      loadIdList( m_MountActionDat, m_MountActionIdList );
   return m_MountActionIdList;
}
const std::set< uint32_t >& getMountCustomizeIdList()
{
   if( m_MountCustomizeIdList.size() == 0 )
      loadIdList( m_MountCustomizeDat, m_MountCustomizeIdList );
   return m_MountCustomizeIdList;
}
const std::set< uint32_t >& getMountFlyingConditionIdList()
{
   if( m_MountFlyingConditionIdList.size() == 0 )
      loadIdList( m_MountFlyingConditionDat, m_MountFlyingConditionIdList );
   return m_MountFlyingConditionIdList;
}
const std::set< uint32_t >& getMountSpeedIdList()
{
   if( m_MountSpeedIdList.size() == 0 )
      loadIdList( m_MountSpeedDat, m_MountSpeedIdList );
   return m_MountSpeedIdList;
}
const std::set< uint32_t >& getMountTransientIdList()
{
   if( m_MountTransientIdList.size() == 0 )
      loadIdList( m_MountTransientDat, m_MountTransientIdList );
   return m_MountTransientIdList;
}
const std::set< uint32_t >& getMoveTimelineIdList()
{
   if( m_MoveTimelineIdList.size() == 0 )
      loadIdList( m_MoveTimelineDat, m_MoveTimelineIdList );
   return m_MoveTimelineIdList;
}
const std::set< uint32_t >& getMoveVfxIdList()
{
   if( m_MoveVfxIdList.size() == 0 )
      loadIdList( m_MoveVfxDat, m_MoveVfxIdList );
   return m_MoveVfxIdList;
}
const std::set< uint32_t >& getMovieStaffListIdList()
{
   if( m_MovieStaffListIdList.size() == 0 )
      loadIdList( m_MovieStaffListDat, m_MovieStaffListIdList );
   return m_MovieStaffListIdList;
}
const std::set< uint32_t >& getMovieSubtitleIdList()
{
   if( m_MovieSubtitleIdList.size() == 0 )
      loadIdList( m_MovieSubtitleDat, m_MovieSubtitleIdList );
   return m_MovieSubtitleIdList;
}
const std::set< uint32_t >& getMovieSubtitle500IdList()
{
   if( m_MovieSubtitle500IdList.size() == 0 )
      loadIdList( m_MovieSubtitle500Dat, m_MovieSubtitle500IdList );
   return m_MovieSubtitle500IdList;
}
const std::set< uint32_t >& getMovieSubtitleVoyageIdList()
{
   if( m_MovieSubtitleVoyageIdList.size() == 0 )
      loadIdList( m_MovieSubtitleVoyageDat, m_MovieSubtitleVoyageIdList );
   return m_MovieSubtitleVoyageIdList;
}
const std::set< uint32_t >& getMYCTemporaryItemIdList()
{
   if( m_MYCTemporaryItemIdList.size() == 0 )
      loadIdList( m_MYCTemporaryItemDat, m_MYCTemporaryItemIdList );
   return m_MYCTemporaryItemIdList;
}
const std::set< uint32_t >& getMYCTemporaryItemUICategoryIdList()
{
   if( m_MYCTemporaryItemUICategoryIdList.size() == 0 )
      loadIdList( m_MYCTemporaryItemUICategoryDat, m_MYCTemporaryItemUICategoryIdList );
   return m_MYCTemporaryItemUICategoryIdList;
}
const std::set< uint32_t >& getMYCWarResultNotebookIdList()
{
   if( m_MYCWarResultNotebookIdList.size() == 0 )
      loadIdList( m_MYCWarResultNotebookDat, m_MYCWarResultNotebookIdList );
   return m_MYCWarResultNotebookIdList;
}
const std::set< uint32_t >& getNotebookDivisionIdList()
{
   if( m_NotebookDivisionIdList.size() == 0 )
      loadIdList( m_NotebookDivisionDat, m_NotebookDivisionIdList );
   return m_NotebookDivisionIdList;
}
const std::set< uint32_t >& getNotebookDivisionCategoryIdList()
{
   if( m_NotebookDivisionCategoryIdList.size() == 0 )
      loadIdList( m_NotebookDivisionCategoryDat, m_NotebookDivisionCategoryIdList );
   return m_NotebookDivisionCategoryIdList;
}
const std::set< uint32_t >& getNotoriousMonsterIdList()
{
   if( m_NotoriousMonsterIdList.size() == 0 )
      loadIdList( m_NotoriousMonsterDat, m_NotoriousMonsterIdList );
   return m_NotoriousMonsterIdList;
}
const std::set< uint32_t >& getNpcEquipIdList()
{
   if( m_NpcEquipIdList.size() == 0 )
      loadIdList( m_NpcEquipDat, m_NpcEquipIdList );
   return m_NpcEquipIdList;
}
const std::set< uint32_t >& getNpcYellIdList()
{
   if( m_NpcYellIdList.size() == 0 )
      loadIdList( m_NpcYellDat, m_NpcYellIdList );
   return m_NpcYellIdList;
}
const std::set< uint32_t >& getOmenIdList()
{
   if( m_OmenIdList.size() == 0 )
      loadIdList( m_OmenDat, m_OmenIdList );
   return m_OmenIdList;
}
const std::set< uint32_t >& getOnlineStatusIdList()
{
   if( m_OnlineStatusIdList.size() == 0 )
      loadIdList( m_OnlineStatusDat, m_OnlineStatusIdList );
   return m_OnlineStatusIdList;
}
const std::set< uint32_t >& getOpenContentIdList()
{
   if( m_OpenContentIdList.size() == 0 )
      loadIdList( m_OpenContentDat, m_OpenContentIdList );
   return m_OpenContentIdList;
}
const std::set< uint32_t >& getOpenContentCandidateNameIdList()
{
   if( m_OpenContentCandidateNameIdList.size() == 0 )
      loadIdList( m_OpenContentCandidateNameDat, m_OpenContentCandidateNameIdList );
   return m_OpenContentCandidateNameIdList;
}
const std::set< uint32_t >& getOpeningIdList()
{
   if( m_OpeningIdList.size() == 0 )
      loadIdList( m_OpeningDat, m_OpeningIdList );
   return m_OpeningIdList;
}
const std::set< uint32_t >& getOrchestrionIdList()
{
   if( m_OrchestrionIdList.size() == 0 )
      loadIdList( m_OrchestrionDat, m_OrchestrionIdList );
   return m_OrchestrionIdList;
}
const std::set< uint32_t >& getOrchestrionCategoryIdList()
{
   if( m_OrchestrionCategoryIdList.size() == 0 )
      loadIdList( m_OrchestrionCategoryDat, m_OrchestrionCategoryIdList );
   return m_OrchestrionCategoryIdList;
}
const std::set< uint32_t >& getOrchestrionPathIdList()
{
   if( m_OrchestrionPathIdList.size() == 0 )
      loadIdList( m_OrchestrionPathDat, m_OrchestrionPathIdList );
   return m_OrchestrionPathIdList;
}
const std::set< uint32_t >& getOrchestrionUiparamIdList()
{
   if( m_OrchestrionUiparamIdList.size() == 0 )
      loadIdList( m_OrchestrionUiparamDat, m_OrchestrionUiparamIdList );
   return m_OrchestrionUiparamIdList;
}
const std::set< uint32_t >& getOrnamentIdList()
{
   if( m_OrnamentIdList.size() == 0 )
      loadIdList( m_OrnamentDat, m_OrnamentIdList );
   return m_OrnamentIdList;
}
const std::set< uint32_t >& getParamGrowIdList()
{
   if( m_ParamGrowIdList.size() == 0 )
      loadIdList( m_ParamGrowDat, m_ParamGrowIdList );
   return m_ParamGrowIdList;
}
const std::set< uint32_t >& getPartyContentIdList()
{
   if( m_PartyContentIdList.size() == 0 )
      loadIdList( m_PartyContentDat, m_PartyContentIdList );
   return m_PartyContentIdList;
}
const std::set< uint32_t >& getPartyContentCutsceneIdList()
{
   if( m_PartyContentCutsceneIdList.size() == 0 )
      loadIdList( m_PartyContentCutsceneDat, m_PartyContentCutsceneIdList );
   return m_PartyContentCutsceneIdList;
}
const std::set< uint32_t >& getPartyContentTextDataIdList()
{
   if( m_PartyContentTextDataIdList.size() == 0 )
      loadIdList( m_PartyContentTextDataDat, m_PartyContentTextDataIdList );
   return m_PartyContentTextDataIdList;
}
const std::set< uint32_t >& getPatchMarkIdList()
{
   if( m_PatchMarkIdList.size() == 0 )
      loadIdList( m_PatchMarkDat, m_PatchMarkIdList );
   return m_PatchMarkIdList;
}
const std::set< uint32_t >& getPerformIdList()
{
   if( m_PerformIdList.size() == 0 )
      loadIdList( m_PerformDat, m_PerformIdList );
   return m_PerformIdList;
}
const std::set< uint32_t >& getPerformTransientIdList()
{
   if( m_PerformTransientIdList.size() == 0 )
      loadIdList( m_PerformTransientDat, m_PerformTransientIdList );
   return m_PerformTransientIdList;
}
const std::set< uint32_t >& getPetIdList()
{
   if( m_PetIdList.size() == 0 )
      loadIdList( m_PetDat, m_PetIdList );
   return m_PetIdList;
}
const std::set< uint32_t >& getPetActionIdList()
{
   if( m_PetActionIdList.size() == 0 )
      loadIdList( m_PetActionDat, m_PetActionIdList );
   return m_PetActionIdList;
}
const std::set< uint32_t >& getPhysicsGroupIdList()
{
   if( m_PhysicsGroupIdList.size() == 0 )
      loadIdList( m_PhysicsGroupDat, m_PhysicsGroupIdList );
   return m_PhysicsGroupIdList;
}
const std::set< uint32_t >& getPhysicsWindIdList()
{
   if( m_PhysicsWindIdList.size() == 0 )
      loadIdList( m_PhysicsWindDat, m_PhysicsWindIdList );
   return m_PhysicsWindIdList;
}
const std::set< uint32_t >& getPictureIdList()
{
   if( m_PictureIdList.size() == 0 )
      loadIdList( m_PictureDat, m_PictureIdList );
   return m_PictureIdList;
}
const std::set< uint32_t >& getPlaceNameIdList()
{
   if( m_PlaceNameIdList.size() == 0 )
      loadIdList( m_PlaceNameDat, m_PlaceNameIdList );
   return m_PlaceNameIdList;
}
const std::set< uint32_t >& getPlantPotFlowerSeedIdList()
{
   if( m_PlantPotFlowerSeedIdList.size() == 0 )
      loadIdList( m_PlantPotFlowerSeedDat, m_PlantPotFlowerSeedIdList );
   return m_PlantPotFlowerSeedIdList;
}
const std::set< uint32_t >& getPreHandlerIdList()
{
   if( m_PreHandlerIdList.size() == 0 )
      loadIdList( m_PreHandlerDat, m_PreHandlerIdList );
   return m_PreHandlerIdList;
}
const std::set< uint32_t >& getPresetCameraIdList()
{
   if( m_PresetCameraIdList.size() == 0 )
      loadIdList( m_PresetCameraDat, m_PresetCameraIdList );
   return m_PresetCameraIdList;
}
const std::set< uint32_t >& getPresetCameraAdjustIdList()
{
   if( m_PresetCameraAdjustIdList.size() == 0 )
      loadIdList( m_PresetCameraAdjustDat, m_PresetCameraAdjustIdList );
   return m_PresetCameraAdjustIdList;
}
const std::set< uint32_t >& getPublicContentIdList()
{
   if( m_PublicContentIdList.size() == 0 )
      loadIdList( m_PublicContentDat, m_PublicContentIdList );
   return m_PublicContentIdList;
}
const std::set< uint32_t >& getPublicContentCutsceneIdList()
{
   if( m_PublicContentCutsceneIdList.size() == 0 )
      loadIdList( m_PublicContentCutsceneDat, m_PublicContentCutsceneIdList );
   return m_PublicContentCutsceneIdList;
}
const std::set< uint32_t >& getPublicContentTextDataIdList()
{
   if( m_PublicContentTextDataIdList.size() == 0 )
      loadIdList( m_PublicContentTextDataDat, m_PublicContentTextDataIdList );
   return m_PublicContentTextDataIdList;
}
const std::set< uint32_t >& getPurifyIdList()
{
   if( m_PurifyIdList.size() == 0 )
      loadIdList( m_PurifyDat, m_PurifyIdList );
   return m_PurifyIdList;
}
const std::set< uint32_t >& getPvPActionIdList()
{
   if( m_PvPActionIdList.size() == 0 )
      loadIdList( m_PvPActionDat, m_PvPActionIdList );
   return m_PvPActionIdList;
}
const std::set< uint32_t >& getPvPActionSortIdList()
{
   if( m_PvPActionSortIdList.size() == 0 )
      loadIdList( m_PvPActionSortDat, m_PvPActionSortIdList );
   return m_PvPActionSortIdList;
}
const std::set< uint32_t >& getPvPRankIdList()
{
   if( m_PvPRankIdList.size() == 0 )
      loadIdList( m_PvPRankDat, m_PvPRankIdList );
   return m_PvPRankIdList;
}
const std::set< uint32_t >& getPvPSelectTraitIdList()
{
   if( m_PvPSelectTraitIdList.size() == 0 )
      loadIdList( m_PvPSelectTraitDat, m_PvPSelectTraitIdList );
   return m_PvPSelectTraitIdList;
}
const std::set< uint32_t >& getPvPTraitIdList()
{
   if( m_PvPTraitIdList.size() == 0 )
      loadIdList( m_PvPTraitDat, m_PvPTraitIdList );
   return m_PvPTraitIdList;
}
const std::set< uint32_t >& getQuestIdList()
{
   if( m_QuestIdList.size() == 0 )
      loadIdList( m_QuestDat, m_QuestIdList );
   return m_QuestIdList;
}
const std::set< uint32_t >& getQuestBattleIdList()
{
   if( m_QuestBattleIdList.size() == 0 )
      loadIdList( m_QuestBattleDat, m_QuestBattleIdList );
   return m_QuestBattleIdList;
}
const std::set< uint32_t >& getQuestChapterIdList()
{
   if( m_QuestChapterIdList.size() == 0 )
      loadIdList( m_QuestChapterDat, m_QuestChapterIdList );
   return m_QuestChapterIdList;
}
const std::set< uint32_t >& getQuestClassJobRewardIdList()
{
   if( m_QuestClassJobRewardIdList.size() == 0 )
      loadIdList( m_QuestClassJobRewardDat, m_QuestClassJobRewardIdList );
   return m_QuestClassJobRewardIdList;
}
const std::set< uint32_t >& getQuestClassJobSupplyIdList()
{
   if( m_QuestClassJobSupplyIdList.size() == 0 )
      loadIdList( m_QuestClassJobSupplyDat, m_QuestClassJobSupplyIdList );
   return m_QuestClassJobSupplyIdList;
}
const std::set< uint32_t >& getQuestDerivedClassIdList()
{
   if( m_QuestDerivedClassIdList.size() == 0 )
      loadIdList( m_QuestDerivedClassDat, m_QuestDerivedClassIdList );
   return m_QuestDerivedClassIdList;
}
const std::set< uint32_t >& getQuestRedoIdList()
{
   if( m_QuestRedoIdList.size() == 0 )
      loadIdList( m_QuestRedoDat, m_QuestRedoIdList );
   return m_QuestRedoIdList;
}
const std::set< uint32_t >& getQuestRedoChapterUIIdList()
{
   if( m_QuestRedoChapterUIIdList.size() == 0 )
      loadIdList( m_QuestRedoChapterUIDat, m_QuestRedoChapterUIIdList );
   return m_QuestRedoChapterUIIdList;
}
const std::set< uint32_t >& getQuestRedoChapterUICategoryIdList()
{
   if( m_QuestRedoChapterUICategoryIdList.size() == 0 )
      loadIdList( m_QuestRedoChapterUICategoryDat, m_QuestRedoChapterUICategoryIdList );
   return m_QuestRedoChapterUICategoryIdList;
}
const std::set< uint32_t >& getQuestRedoChapterUITabIdList()
{
   if( m_QuestRedoChapterUITabIdList.size() == 0 )
      loadIdList( m_QuestRedoChapterUITabDat, m_QuestRedoChapterUITabIdList );
   return m_QuestRedoChapterUITabIdList;
}
const std::set< uint32_t >& getQuestRedoIncompChapterIdList()
{
   if( m_QuestRedoIncompChapterIdList.size() == 0 )
      loadIdList( m_QuestRedoIncompChapterDat, m_QuestRedoIncompChapterIdList );
   return m_QuestRedoIncompChapterIdList;
}
const std::set< uint32_t >& getQuestRepeatFlagIdList()
{
   if( m_QuestRepeatFlagIdList.size() == 0 )
      loadIdList( m_QuestRepeatFlagDat, m_QuestRepeatFlagIdList );
   return m_QuestRepeatFlagIdList;
}
const std::set< uint32_t >& getQuestRewardOtherIdList()
{
   if( m_QuestRewardOtherIdList.size() == 0 )
      loadIdList( m_QuestRewardOtherDat, m_QuestRewardOtherIdList );
   return m_QuestRewardOtherIdList;
}
const std::set< uint32_t >& getQuickChatIdList()
{
   if( m_QuickChatIdList.size() == 0 )
      loadIdList( m_QuickChatDat, m_QuickChatIdList );
   return m_QuickChatIdList;
}
const std::set< uint32_t >& getQuickChatTransientIdList()
{
   if( m_QuickChatTransientIdList.size() == 0 )
      loadIdList( m_QuickChatTransientDat, m_QuickChatTransientIdList );
   return m_QuickChatTransientIdList;
}
const std::set< uint32_t >& getRaceIdList()
{
   if( m_RaceIdList.size() == 0 )
      loadIdList( m_RaceDat, m_RaceIdList );
   return m_RaceIdList;
}
const std::set< uint32_t >& getRacingChocoboItemIdList()
{
   if( m_RacingChocoboItemIdList.size() == 0 )
      loadIdList( m_RacingChocoboItemDat, m_RacingChocoboItemIdList );
   return m_RacingChocoboItemIdList;
}
const std::set< uint32_t >& getRacingChocoboNameIdList()
{
   if( m_RacingChocoboNameIdList.size() == 0 )
      loadIdList( m_RacingChocoboNameDat, m_RacingChocoboNameIdList );
   return m_RacingChocoboNameIdList;
}
const std::set< uint32_t >& getRacingChocoboNameCategoryIdList()
{
   if( m_RacingChocoboNameCategoryIdList.size() == 0 )
      loadIdList( m_RacingChocoboNameCategoryDat, m_RacingChocoboNameCategoryIdList );
   return m_RacingChocoboNameCategoryIdList;
}
const std::set< uint32_t >& getRacingChocoboNameInfoIdList()
{
   if( m_RacingChocoboNameInfoIdList.size() == 0 )
      loadIdList( m_RacingChocoboNameInfoDat, m_RacingChocoboNameInfoIdList );
   return m_RacingChocoboNameInfoIdList;
}
const std::set< uint32_t >& getRacingChocoboParamIdList()
{
   if( m_RacingChocoboParamIdList.size() == 0 )
      loadIdList( m_RacingChocoboParamDat, m_RacingChocoboParamIdList );
   return m_RacingChocoboParamIdList;
}
const std::set< uint32_t >& getRecastNavimeshIdList()
{
   if( m_RecastNavimeshIdList.size() == 0 )
      loadIdList( m_RecastNavimeshDat, m_RecastNavimeshIdList );
   return m_RecastNavimeshIdList;
}
const std::set< uint32_t >& getRecipeIdList()
{
   if( m_RecipeIdList.size() == 0 )
      loadIdList( m_RecipeDat, m_RecipeIdList );
   return m_RecipeIdList;
}
const std::set< uint32_t >& getRecipeLevelTableIdList()
{
   if( m_RecipeLevelTableIdList.size() == 0 )
      loadIdList( m_RecipeLevelTableDat, m_RecipeLevelTableIdList );
   return m_RecipeLevelTableIdList;
}
const std::set< uint32_t >& getRecipeLookupIdList()
{
   if( m_RecipeLookupIdList.size() == 0 )
      loadIdList( m_RecipeLookupDat, m_RecipeLookupIdList );
   return m_RecipeLookupIdList;
}
const std::set< uint32_t >& getRecipeNotebookListIdList()
{
   if( m_RecipeNotebookListIdList.size() == 0 )
      loadIdList( m_RecipeNotebookListDat, m_RecipeNotebookListIdList );
   return m_RecipeNotebookListIdList;
}
const std::set< uint32_t >& getRecommendContentsIdList()
{
   if( m_RecommendContentsIdList.size() == 0 )
      loadIdList( m_RecommendContentsDat, m_RecommendContentsIdList );
   return m_RecommendContentsIdList;
}
const std::set< uint32_t >& getRelicIdList()
{
   if( m_RelicIdList.size() == 0 )
      loadIdList( m_RelicDat, m_RelicIdList );
   return m_RelicIdList;
}
const std::set< uint32_t >& getRelic3IdList()
{
   if( m_Relic3IdList.size() == 0 )
      loadIdList( m_Relic3Dat, m_Relic3IdList );
   return m_Relic3IdList;
}
const std::set< uint32_t >& getRelicItemIdList()
{
   if( m_RelicItemIdList.size() == 0 )
      loadIdList( m_RelicItemDat, m_RelicItemIdList );
   return m_RelicItemIdList;
}
const std::set< uint32_t >& getRelicNoteIdList()
{
   if( m_RelicNoteIdList.size() == 0 )
      loadIdList( m_RelicNoteDat, m_RelicNoteIdList );
   return m_RelicNoteIdList;
}
const std::set< uint32_t >& getRelicNoteCategoryIdList()
{
   if( m_RelicNoteCategoryIdList.size() == 0 )
      loadIdList( m_RelicNoteCategoryDat, m_RelicNoteCategoryIdList );
   return m_RelicNoteCategoryIdList;
}
const std::set< uint32_t >& getResidentIdList()
{
   if( m_ResidentIdList.size() == 0 )
      loadIdList( m_ResidentDat, m_ResidentIdList );
   return m_ResidentIdList;
}
const std::set< uint32_t >& getResistanceWeaponAdjustIdList()
{
   if( m_ResistanceWeaponAdjustIdList.size() == 0 )
      loadIdList( m_ResistanceWeaponAdjustDat, m_ResistanceWeaponAdjustIdList );
   return m_ResistanceWeaponAdjustIdList;
}
const std::set< uint32_t >& getRetainerTaskIdList()
{
   if( m_RetainerTaskIdList.size() == 0 )
      loadIdList( m_RetainerTaskDat, m_RetainerTaskIdList );
   return m_RetainerTaskIdList;
}
const std::set< uint32_t >& getRetainerTaskLvRangeIdList()
{
   if( m_RetainerTaskLvRangeIdList.size() == 0 )
      loadIdList( m_RetainerTaskLvRangeDat, m_RetainerTaskLvRangeIdList );
   return m_RetainerTaskLvRangeIdList;
}
const std::set< uint32_t >& getRetainerTaskNormalIdList()
{
   if( m_RetainerTaskNormalIdList.size() == 0 )
      loadIdList( m_RetainerTaskNormalDat, m_RetainerTaskNormalIdList );
   return m_RetainerTaskNormalIdList;
}
const std::set< uint32_t >& getRetainerTaskParameterIdList()
{
   if( m_RetainerTaskParameterIdList.size() == 0 )
      loadIdList( m_RetainerTaskParameterDat, m_RetainerTaskParameterIdList );
   return m_RetainerTaskParameterIdList;
}
const std::set< uint32_t >& getRetainerTaskRandomIdList()
{
   if( m_RetainerTaskRandomIdList.size() == 0 )
      loadIdList( m_RetainerTaskRandomDat, m_RetainerTaskRandomIdList );
   return m_RetainerTaskRandomIdList;
}
const std::set< uint32_t >& getRideShootingIdList()
{
   if( m_RideShootingIdList.size() == 0 )
      loadIdList( m_RideShootingDat, m_RideShootingIdList );
   return m_RideShootingIdList;
}
const std::set< uint32_t >& getRideShootingTextDataIdList()
{
   if( m_RideShootingTextDataIdList.size() == 0 )
      loadIdList( m_RideShootingTextDataDat, m_RideShootingTextDataIdList );
   return m_RideShootingTextDataIdList;
}
const std::set< uint32_t >& getRPParameterIdList()
{
   if( m_RPParameterIdList.size() == 0 )
      loadIdList( m_RPParameterDat, m_RPParameterIdList );
   return m_RPParameterIdList;
}
const std::set< uint32_t >& getSatisfactionArbitrationIdList()
{
   if( m_SatisfactionArbitrationIdList.size() == 0 )
      loadIdList( m_SatisfactionArbitrationDat, m_SatisfactionArbitrationIdList );
   return m_SatisfactionArbitrationIdList;
}
const std::set< uint32_t >& getSatisfactionNpcIdList()
{
   if( m_SatisfactionNpcIdList.size() == 0 )
      loadIdList( m_SatisfactionNpcDat, m_SatisfactionNpcIdList );
   return m_SatisfactionNpcIdList;
}
const std::set< uint32_t >& getSatisfactionSupplyIdList()
{
   if( m_SatisfactionSupplyIdList.size() == 0 )
      loadIdList( m_SatisfactionSupplyDat, m_SatisfactionSupplyIdList );
   return m_SatisfactionSupplyIdList;
}
const std::set< uint32_t >& getSatisfactionSupplyRewardIdList()
{
   if( m_SatisfactionSupplyRewardIdList.size() == 0 )
      loadIdList( m_SatisfactionSupplyRewardDat, m_SatisfactionSupplyRewardIdList );
   return m_SatisfactionSupplyRewardIdList;
}
const std::set< uint32_t >& getScenarioTreeIdList()
{
   if( m_ScenarioTreeIdList.size() == 0 )
      loadIdList( m_ScenarioTreeDat, m_ScenarioTreeIdList );
   return m_ScenarioTreeIdList;
}
const std::set< uint32_t >& getScenarioTreeTipsIdList()
{
   if( m_ScenarioTreeTipsIdList.size() == 0 )
      loadIdList( m_ScenarioTreeTipsDat, m_ScenarioTreeTipsIdList );
   return m_ScenarioTreeTipsIdList;
}
const std::set< uint32_t >& getScenarioTreeTipsClassQuestIdList()
{
   if( m_ScenarioTreeTipsClassQuestIdList.size() == 0 )
      loadIdList( m_ScenarioTreeTipsClassQuestDat, m_ScenarioTreeTipsClassQuestIdList );
   return m_ScenarioTreeTipsClassQuestIdList;
}
const std::set< uint32_t >& getScenarioTypeIdList()
{
   if( m_ScenarioTypeIdList.size() == 0 )
      loadIdList( m_ScenarioTypeDat, m_ScenarioTypeIdList );
   return m_ScenarioTypeIdList;
}
const std::set< uint32_t >& getScreenImageIdList()
{
   if( m_ScreenImageIdList.size() == 0 )
      loadIdList( m_ScreenImageDat, m_ScreenImageIdList );
   return m_ScreenImageIdList;
}
const std::set< uint32_t >& getSecretRecipeBookIdList()
{
   if( m_SecretRecipeBookIdList.size() == 0 )
      loadIdList( m_SecretRecipeBookDat, m_SecretRecipeBookIdList );
   return m_SecretRecipeBookIdList;
}
const std::set< uint32_t >& getSkyIsland2MissionIdList()
{
   if( m_SkyIsland2MissionIdList.size() == 0 )
      loadIdList( m_SkyIsland2MissionDat, m_SkyIsland2MissionIdList );
   return m_SkyIsland2MissionIdList;
}
const std::set< uint32_t >& getSkyIsland2MissionDetailIdList()
{
   if( m_SkyIsland2MissionDetailIdList.size() == 0 )
      loadIdList( m_SkyIsland2MissionDetailDat, m_SkyIsland2MissionDetailIdList );
   return m_SkyIsland2MissionDetailIdList;
}
const std::set< uint32_t >& getSkyIsland2MissionTypeIdList()
{
   if( m_SkyIsland2MissionTypeIdList.size() == 0 )
      loadIdList( m_SkyIsland2MissionTypeDat, m_SkyIsland2MissionTypeIdList );
   return m_SkyIsland2MissionTypeIdList;
}
const std::set< uint32_t >& getSkyIsland2RangeTypeIdList()
{
   if( m_SkyIsland2RangeTypeIdList.size() == 0 )
      loadIdList( m_SkyIsland2RangeTypeDat, m_SkyIsland2RangeTypeIdList );
   return m_SkyIsland2RangeTypeIdList;
}
const std::set< uint32_t >& getSnipeTalkIdList()
{
   if( m_SnipeTalkIdList.size() == 0 )
      loadIdList( m_SnipeTalkDat, m_SnipeTalkIdList );
   return m_SnipeTalkIdList;
}
const std::set< uint32_t >& getSnipeTalkNameIdList()
{
   if( m_SnipeTalkNameIdList.size() == 0 )
      loadIdList( m_SnipeTalkNameDat, m_SnipeTalkNameIdList );
   return m_SnipeTalkNameIdList;
}
const std::set< uint32_t >& getSpearfishingItemIdList()
{
   if( m_SpearfishingItemIdList.size() == 0 )
      loadIdList( m_SpearfishingItemDat, m_SpearfishingItemIdList );
   return m_SpearfishingItemIdList;
}
const std::set< uint32_t >& getSpearfishingNotebookIdList()
{
   if( m_SpearfishingNotebookIdList.size() == 0 )
      loadIdList( m_SpearfishingNotebookDat, m_SpearfishingNotebookIdList );
   return m_SpearfishingNotebookIdList;
}
const std::set< uint32_t >& getSpearfishingRecordPageIdList()
{
   if( m_SpearfishingRecordPageIdList.size() == 0 )
      loadIdList( m_SpearfishingRecordPageDat, m_SpearfishingRecordPageIdList );
   return m_SpearfishingRecordPageIdList;
}
const std::set< uint32_t >& getSpecialShopIdList()
{
   if( m_SpecialShopIdList.size() == 0 )
      loadIdList( m_SpecialShopDat, m_SpecialShopIdList );
   return m_SpecialShopIdList;
}
const std::set< uint32_t >& getSpecialShopItemCategoryIdList()
{
   if( m_SpecialShopItemCategoryIdList.size() == 0 )
      loadIdList( m_SpecialShopItemCategoryDat, m_SpecialShopItemCategoryIdList );
   return m_SpecialShopItemCategoryIdList;
}
const std::set< uint32_t >& getStainIdList()
{
   if( m_StainIdList.size() == 0 )
      loadIdList( m_StainDat, m_StainIdList );
   return m_StainIdList;
}
const std::set< uint32_t >& getStainTransientIdList()
{
   if( m_StainTransientIdList.size() == 0 )
      loadIdList( m_StainTransientDat, m_StainTransientIdList );
   return m_StainTransientIdList;
}
const std::set< uint32_t >& getStatusIdList()
{
   if( m_StatusIdList.size() == 0 )
      loadIdList( m_StatusDat, m_StatusIdList );
   return m_StatusIdList;
}
const std::set< uint32_t >& getStatusHitEffectIdList()
{
   if( m_StatusHitEffectIdList.size() == 0 )
      loadIdList( m_StatusHitEffectDat, m_StatusHitEffectIdList );
   return m_StatusHitEffectIdList;
}
const std::set< uint32_t >& getStatusLoopVFXIdList()
{
   if( m_StatusLoopVFXIdList.size() == 0 )
      loadIdList( m_StatusLoopVFXDat, m_StatusLoopVFXIdList );
   return m_StatusLoopVFXIdList;
}
const std::set< uint32_t >& getStoryIdList()
{
   if( m_StoryIdList.size() == 0 )
      loadIdList( m_StoryDat, m_StoryIdList );
   return m_StoryIdList;
}
const std::set< uint32_t >& getSubmarineExplorationIdList()
{
   if( m_SubmarineExplorationIdList.size() == 0 )
      loadIdList( m_SubmarineExplorationDat, m_SubmarineExplorationIdList );
   return m_SubmarineExplorationIdList;
}
const std::set< uint32_t >& getSubmarineMapIdList()
{
   if( m_SubmarineMapIdList.size() == 0 )
      loadIdList( m_SubmarineMapDat, m_SubmarineMapIdList );
   return m_SubmarineMapIdList;
}
const std::set< uint32_t >& getSubmarinePartIdList()
{
   if( m_SubmarinePartIdList.size() == 0 )
      loadIdList( m_SubmarinePartDat, m_SubmarinePartIdList );
   return m_SubmarinePartIdList;
}
const std::set< uint32_t >& getSubmarineRankIdList()
{
   if( m_SubmarineRankIdList.size() == 0 )
      loadIdList( m_SubmarineRankDat, m_SubmarineRankIdList );
   return m_SubmarineRankIdList;
}
const std::set< uint32_t >& getSwitchTalkIdList()
{
   if( m_SwitchTalkIdList.size() == 0 )
      loadIdList( m_SwitchTalkDat, m_SwitchTalkIdList );
   return m_SwitchTalkIdList;
}
const std::set< uint32_t >& getSwitchTalkVariationIdList()
{
   if( m_SwitchTalkVariationIdList.size() == 0 )
      loadIdList( m_SwitchTalkVariationDat, m_SwitchTalkVariationIdList );
   return m_SwitchTalkVariationIdList;
}
const std::set< uint32_t >& getTerritoryTypeIdList()
{
   if( m_TerritoryTypeIdList.size() == 0 )
      loadIdList( m_TerritoryTypeDat, m_TerritoryTypeIdList );
   return m_TerritoryTypeIdList;
}
const std::set< uint32_t >& getTerritoryTypeTransientIdList()
{
   if( m_TerritoryTypeTransientIdList.size() == 0 )
      loadIdList( m_TerritoryTypeTransientDat, m_TerritoryTypeTransientIdList );
   return m_TerritoryTypeTransientIdList;
}
const std::set< uint32_t >& getTextCommandIdList()
{
   if( m_TextCommandIdList.size() == 0 )
      loadIdList( m_TextCommandDat, m_TextCommandIdList );
   return m_TextCommandIdList;
}
const std::set< uint32_t >& getTitleIdList()
{
   if( m_TitleIdList.size() == 0 )
      loadIdList( m_TitleDat, m_TitleIdList );
   return m_TitleIdList;
}
const std::set< uint32_t >& getTomestonesIdList()
{
   if( m_TomestonesIdList.size() == 0 )
      loadIdList( m_TomestonesDat, m_TomestonesIdList );
   return m_TomestonesIdList;
}
const std::set< uint32_t >& getTomestonesItemIdList()
{
   if( m_TomestonesItemIdList.size() == 0 )
      loadIdList( m_TomestonesItemDat, m_TomestonesItemIdList );
   return m_TomestonesItemIdList;
}
const std::set< uint32_t >& getTopicSelectIdList()
{
   if( m_TopicSelectIdList.size() == 0 )
      loadIdList( m_TopicSelectDat, m_TopicSelectIdList );
   return m_TopicSelectIdList;
}
const std::set< uint32_t >& getTownIdList()
{
   if( m_TownIdList.size() == 0 )
      loadIdList( m_TownDat, m_TownIdList );
   return m_TownIdList;
}
const std::set< uint32_t >& getTraitIdList()
{
   if( m_TraitIdList.size() == 0 )
      loadIdList( m_TraitDat, m_TraitIdList );
   return m_TraitIdList;
}
const std::set< uint32_t >& getTraitRecastIdList()
{
   if( m_TraitRecastIdList.size() == 0 )
      loadIdList( m_TraitRecastDat, m_TraitRecastIdList );
   return m_TraitRecastIdList;
}
const std::set< uint32_t >& getTraitTransientIdList()
{
   if( m_TraitTransientIdList.size() == 0 )
      loadIdList( m_TraitTransientDat, m_TraitTransientIdList );
   return m_TraitTransientIdList;
}
const std::set< uint32_t >& getTransformationIdList()
{
   if( m_TransformationIdList.size() == 0 )
      loadIdList( m_TransformationDat, m_TransformationIdList );
   return m_TransformationIdList;
}
const std::set< uint32_t >& getTreasureIdList()
{
   if( m_TreasureIdList.size() == 0 )
      loadIdList( m_TreasureDat, m_TreasureIdList );
   return m_TreasureIdList;
}
const std::set< uint32_t >& getTreasureHuntRankIdList()
{
   if( m_TreasureHuntRankIdList.size() == 0 )
      loadIdList( m_TreasureHuntRankDat, m_TreasureHuntRankIdList );
   return m_TreasureHuntRankIdList;
}
const std::set< uint32_t >& getTreasureModelIdList()
{
   if( m_TreasureModelIdList.size() == 0 )
      loadIdList( m_TreasureModelDat, m_TreasureModelIdList );
   return m_TreasureModelIdList;
}
const std::set< uint32_t >& getTreasureSpotIdList()
{
   if( m_TreasureSpotIdList.size() == 0 )
      loadIdList( m_TreasureSpotDat, m_TreasureSpotIdList );
   return m_TreasureSpotIdList;
}
const std::set< uint32_t >& getTribeIdList()
{
   if( m_TribeIdList.size() == 0 )
      loadIdList( m_TribeDat, m_TribeIdList );
   return m_TribeIdList;
}
const std::set< uint32_t >& getTripleTriadIdList()
{
   if( m_TripleTriadIdList.size() == 0 )
      loadIdList( m_TripleTriadDat, m_TripleTriadIdList );
   return m_TripleTriadIdList;
}
const std::set< uint32_t >& getTripleTriadCardIdList()
{
   if( m_TripleTriadCardIdList.size() == 0 )
      loadIdList( m_TripleTriadCardDat, m_TripleTriadCardIdList );
   return m_TripleTriadCardIdList;
}
const std::set< uint32_t >& getTripleTriadCardRarityIdList()
{
   if( m_TripleTriadCardRarityIdList.size() == 0 )
      loadIdList( m_TripleTriadCardRarityDat, m_TripleTriadCardRarityIdList );
   return m_TripleTriadCardRarityIdList;
}
const std::set< uint32_t >& getTripleTriadCardResidentIdList()
{
   if( m_TripleTriadCardResidentIdList.size() == 0 )
      loadIdList( m_TripleTriadCardResidentDat, m_TripleTriadCardResidentIdList );
   return m_TripleTriadCardResidentIdList;
}
const std::set< uint32_t >& getTripleTriadCardTypeIdList()
{
   if( m_TripleTriadCardTypeIdList.size() == 0 )
      loadIdList( m_TripleTriadCardTypeDat, m_TripleTriadCardTypeIdList );
   return m_TripleTriadCardTypeIdList;
}
const std::set< uint32_t >& getTripleTriadCompetitionIdList()
{
   if( m_TripleTriadCompetitionIdList.size() == 0 )
      loadIdList( m_TripleTriadCompetitionDat, m_TripleTriadCompetitionIdList );
   return m_TripleTriadCompetitionIdList;
}
const std::set< uint32_t >& getTripleTriadRuleIdList()
{
   if( m_TripleTriadRuleIdList.size() == 0 )
      loadIdList( m_TripleTriadRuleDat, m_TripleTriadRuleIdList );
   return m_TripleTriadRuleIdList;
}
const std::set< uint32_t >& getTutorialIdList()
{
   if( m_TutorialIdList.size() == 0 )
      loadIdList( m_TutorialDat, m_TutorialIdList );
   return m_TutorialIdList;
}
const std::set< uint32_t >& getTutorialDPSIdList()
{
   if( m_TutorialDPSIdList.size() == 0 )
      loadIdList( m_TutorialDPSDat, m_TutorialDPSIdList );
   return m_TutorialDPSIdList;
}
const std::set< uint32_t >& getTutorialHealerIdList()
{
   if( m_TutorialHealerIdList.size() == 0 )
      loadIdList( m_TutorialHealerDat, m_TutorialHealerIdList );
   return m_TutorialHealerIdList;
}
const std::set< uint32_t >& getTutorialTankIdList()
{
   if( m_TutorialTankIdList.size() == 0 )
      loadIdList( m_TutorialTankDat, m_TutorialTankIdList );
   return m_TutorialTankIdList;
}
const std::set< uint32_t >& getUIColorIdList()
{
   if( m_UIColorIdList.size() == 0 )
      loadIdList( m_UIColorDat, m_UIColorIdList );
   return m_UIColorIdList;
}
const std::set< uint32_t >& getVaseFlowerIdList()
{
   if( m_VaseFlowerIdList.size() == 0 )
      loadIdList( m_VaseFlowerDat, m_VaseFlowerIdList );
   return m_VaseFlowerIdList;
}
const std::set< uint32_t >& getVFXIdList()
{
   if( m_VFXIdList.size() == 0 )
      loadIdList( m_VFXDat, m_VFXIdList );
   return m_VFXIdList;
}
const std::set< uint32_t >& getWarpIdList()
{
   if( m_WarpIdList.size() == 0 )
      loadIdList( m_WarpDat, m_WarpIdList );
   return m_WarpIdList;
}
const std::set< uint32_t >& getWarpConditionIdList()
{
   if( m_WarpConditionIdList.size() == 0 )
      loadIdList( m_WarpConditionDat, m_WarpConditionIdList );
   return m_WarpConditionIdList;
}
const std::set< uint32_t >& getWarpLogicIdList()
{
   if( m_WarpLogicIdList.size() == 0 )
      loadIdList( m_WarpLogicDat, m_WarpLogicIdList );
   return m_WarpLogicIdList;
}
const std::set< uint32_t >& getWeaponTimelineIdList()
{
   if( m_WeaponTimelineIdList.size() == 0 )
      loadIdList( m_WeaponTimelineDat, m_WeaponTimelineIdList );
   return m_WeaponTimelineIdList;
}
const std::set< uint32_t >& getWeatherIdList()
{
   if( m_WeatherIdList.size() == 0 )
      loadIdList( m_WeatherDat, m_WeatherIdList );
   return m_WeatherIdList;
}
const std::set< uint32_t >& getWeatherGroupIdList()
{
   if( m_WeatherGroupIdList.size() == 0 )
      loadIdList( m_WeatherGroupDat, m_WeatherGroupIdList );
   return m_WeatherGroupIdList;
}
const std::set< uint32_t >& getWeatherRateIdList()
{
   if( m_WeatherRateIdList.size() == 0 )
      loadIdList( m_WeatherRateDat, m_WeatherRateIdList );
   return m_WeatherRateIdList;
}
const std::set< uint32_t >& getWeatherReportReplaceIdList()
{
   if( m_WeatherReportReplaceIdList.size() == 0 )
      loadIdList( m_WeatherReportReplaceDat, m_WeatherReportReplaceIdList );
   return m_WeatherReportReplaceIdList;
}
const std::set< uint32_t >& getWebGuidanceIdList()
{
   if( m_WebGuidanceIdList.size() == 0 )
      loadIdList( m_WebGuidanceDat, m_WebGuidanceIdList );
   return m_WebGuidanceIdList;
}
const std::set< uint32_t >& getWebURLIdList()
{
   if( m_WebURLIdList.size() == 0 )
      loadIdList( m_WebURLDat, m_WebURLIdList );
   return m_WebURLIdList;
}
const std::set< uint32_t >& getWeddingBGMIdList()
{
   if( m_WeddingBGMIdList.size() == 0 )
      loadIdList( m_WeddingBGMDat, m_WeddingBGMIdList );
   return m_WeddingBGMIdList;
}
const std::set< uint32_t >& getWeeklyBingoOrderDataIdList()
{
   if( m_WeeklyBingoOrderDataIdList.size() == 0 )
      loadIdList( m_WeeklyBingoOrderDataDat, m_WeeklyBingoOrderDataIdList );
   return m_WeeklyBingoOrderDataIdList;
}
const std::set< uint32_t >& getWeeklyBingoRewardDataIdList()
{
   if( m_WeeklyBingoRewardDataIdList.size() == 0 )
      loadIdList( m_WeeklyBingoRewardDataDat, m_WeeklyBingoRewardDataIdList );
   return m_WeeklyBingoRewardDataIdList;
}
const std::set< uint32_t >& getWeeklyBingoTextIdList()
{
   if( m_WeeklyBingoTextIdList.size() == 0 )
      loadIdList( m_WeeklyBingoTextDat, m_WeeklyBingoTextIdList );
   return m_WeeklyBingoTextIdList;
}
const std::set< uint32_t >& getWeeklyLotBonusIdList()
{
   if( m_WeeklyLotBonusIdList.size() == 0 )
      loadIdList( m_WeeklyLotBonusDat, m_WeeklyLotBonusIdList );
   return m_WeeklyLotBonusIdList;
}
const std::set< uint32_t >& getWorldIdList()
{
   if( m_WorldIdList.size() == 0 )
      loadIdList( m_WorldDat, m_WorldIdList );
   return m_WorldIdList;
}
const std::set< uint32_t >& getWorldDCGroupTypeIdList()
{
   if( m_WorldDCGroupTypeIdList.size() == 0 )
      loadIdList( m_WorldDCGroupTypeDat, m_WorldDCGroupTypeIdList );
   return m_WorldDCGroupTypeIdList;
}
const std::set< uint32_t >& getYardCatalogCategoryIdList()
{
   if( m_YardCatalogCategoryIdList.size() == 0 )
      loadIdList( m_YardCatalogCategoryDat, m_YardCatalogCategoryIdList );
   return m_YardCatalogCategoryIdList;
}
const std::set< uint32_t >& getYardCatalogItemListIdList()
{
   if( m_YardCatalogItemListIdList.size() == 0 )
      loadIdList( m_YardCatalogItemListDat, m_YardCatalogItemListIdList );
   return m_YardCatalogItemListIdList;
}
const std::set< uint32_t >& getYKWIdList()
{
   if( m_YKWIdList.size() == 0 )
      loadIdList( m_YKWDat, m_YKWIdList );
   return m_YKWIdList;
}
const std::set< uint32_t >& getZoneSharedGroupIdList()
{
   if( m_ZoneSharedGroupIdList.size() == 0 )
      loadIdList( m_ZoneSharedGroupDat, m_ZoneSharedGroupIdList );
   return m_ZoneSharedGroupIdList;
}


  };

}

#endif

