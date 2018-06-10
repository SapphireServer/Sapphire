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
#include <boost/make_shared.hpp>

namespace Core {
namespace Data {

class ExdDataGenerated;

struct Achievement;
struct AchievementCategory;
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
struct ActionTimelineReplace;
struct ActionTransient;
struct Addon;
struct Adventure;
struct AdventureExPhase;
struct AetherCurrent;
struct AetherCurrentCompFlgSet;
struct AetherialWheel;
struct Aetheryte;
struct AirshipExplorationLevel;
struct AirshipExplorationLog;
struct AirshipExplorationParamType;
struct AirshipExplorationPart;
struct AirshipExplorationPoint;
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
struct AquariumFish;
struct AquariumWater;
struct AttackType;
struct Balloon;
struct BaseParam;
struct BattleLeve;
struct BeastRankBonus;
struct BeastReputationRank;
struct BeastTribe;
struct Behavior;
struct BGM;
struct BNpcAnnounceIcon;
struct BNpcBase;
struct BNpcCustomize;
struct BNpcName;
struct Buddy;
struct BuddyAction;
struct BuddyEquip;
struct BuddyItem;
struct BuddyRank;
struct BuddySkill;
struct Cabinet;
struct CabinetCategory;
struct Calendar;
struct CharaMakeCustomize;
struct CharaMakeType;
struct ChocoboRace;
struct ChocoboRaceAbility;
struct ChocoboRaceAbilityType;
struct ChocoboRaceItem;
struct ChocoboRaceRank;
struct ChocoboRaceStatus;
struct ChocoboRaceTerritory;
struct ChocoboTaxi;
struct ChocoboTaxiStand;
struct ClassJob;
struct ClassJobCategory;
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
struct CompleteJournal;
struct CompleteJournalCategory;
struct ContentExAction;
struct ContentFinderCondition;
struct ContentFinderConditionTransient;
struct ContentMemberType;
struct ContentNpcTalk;
struct ContentRoulette;
struct ContentsNote;
struct ContentsNoteCategory;
struct ContentTalk;
struct ContentTalkParam;
struct ContentType;
struct CraftAction;
struct CraftLeve;
struct CraftType;
struct Currency;
struct CustomTalk;
struct Cutscene;
struct CutScreenImage;
struct DailySupplyItem;
struct DeepDungeonBan;
struct DeepDungeonDanger;
struct DeepDungeonEquipment;
struct DeepDungeonFloorEffectUI;
struct DeepDungeonItem;
struct DeepDungeonStatus;
struct DefaultTalk;
struct DeliveryQuest;
struct DisposalShop;
struct DisposalShopFilterType;
struct DisposalShopItem;
struct DpsChallenge;
struct DpsChallengeOfficer;
struct DpsChallengeTransient;
struct Emote;
struct EmoteCategory;
struct ENpcBase;
struct ENpcResident;
struct EObj;
struct EObjName;
struct EquipRaceCategory;
struct EquipSlotCategory;
struct EurekaAethernet;
struct EurekaGrowData;
struct EurekaSphereElementAdjust;
struct EventAction;
struct EventIconPriority;
struct EventIconType;
struct EventItem;
struct EventItemHelp;
struct ExVersion;
struct Fate;
struct FCActivity;
struct FCActivityCategory;
struct FCAuthority;
struct FCAuthorityCategory;
struct FCChestName;
struct FccShop;
struct FCHierarchy;
struct FCProfile;
struct FCReputation;
struct FCRights;
struct FieldMarker;
struct FishingSpot;
struct FishParameter;
struct GardeningSeed;
struct GatheringCondition;
struct GatheringExp;
struct GatheringItem;
struct GatheringItemLevelConvertTable;
struct GatheringItemPoint;
struct GatheringNotebookList;
struct GatheringPoint;
struct GatheringPointBase;
struct GatheringPointBonus;
struct GatheringPointBonusType;
struct GatheringPointName;
struct GatheringSubCategory;
struct GatheringType;
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
struct GilShop;
struct GilShopItem;
struct GoldSaucerTextData;
struct GrandCompany;
struct GrandCompanyRank;
struct GuardianDeity;
struct GuildleveAssignment;
struct GuildOrderGuide;
struct GuildOrderOfficer;
struct HouseRetainerPose;
struct HousingFurniture;
struct HousingYardObject;
struct InstanceContent;
struct InstanceContentBuff;
struct InstanceContentTextData;
struct Item;
struct ItemAction;
struct ItemFood;
struct ItemSearchCategory;
struct ItemSeries;
struct ItemSpecialBonus;
struct ItemUICategory;
struct JournalCategory;
struct JournalGenre;
struct JournalSection;
struct Leve;
struct LeveAssignmentType;
struct LeveClient;
struct Level;
struct LeveRewardItem;
struct LeveRewardItemGroup;
struct LeveVfx;
struct LogFilter;
struct LogKind;
struct LogKindCategoryText;
struct LogMessage;
struct MacroIcon;
struct MacroIconRedirectOld;
struct MainCommand;
struct MainCommandCategory;
struct Map;
struct MapMarker;
struct MapMarkerRegion;
struct MapSymbol;
struct Marker;
struct MasterpieceSupplyDuty;
struct MasterpieceSupplyMultiplier;
struct Materia;
struct MinionRace;
struct MinionRules;
struct MinionSkillType;
struct MobHuntTarget;
struct ModelChara;
struct MonsterNote;
struct MonsterNoteTarget;
struct Mount;
struct MountAction;
struct MoveTimeline;
struct MoveVfx;
struct NpcEquip;
struct Omen;
struct OnlineStatus;
struct Opening;
struct Orchestrion;
struct OrchestrionCategory;
struct OrchestrionPath;
struct OrchestrionUiparam;
struct ParamGrow;
struct Perform;
struct PerformTransient;
struct Pet;
struct PetAction;
struct Picture;
struct PlaceName;
struct PublicContent;
struct PvPActionSort;
struct Quest;
struct QuestClassJobReward;
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
struct Recipe;
struct RecipeElement;
struct RecipeLevelTable;
struct RecipeNotebookList;
struct RecommendContents;
struct Relic;
struct Relic3;
struct RelicItem;
struct RelicNote;
struct RelicNoteCategory;
struct RetainerTask;
struct RetainerTaskLvRange;
struct RetainerTaskNormal;
struct RetainerTaskParameter;
struct RetainerTaskRandom;
struct Salvage;
struct SatisfactionNpc;
struct SatisfactionSupply;
struct SatisfactionSupplyReward;
struct ScenarioTree;
struct ScenarioTreeTips;
struct ScenarioTreeTipsClassQuest;
struct ScenarioTreeTipsQuest;
struct ScenarioType;
struct ScreenImage;
struct SecretRecipeBook;
struct SkyIsland2Mission;
struct SkyIsland2MissionDetail;
struct SkyIsland2MissionType;
struct SkyIsland2RangeType;
struct SpearfishingItem;
struct SpearfishingNotebook;
struct SpecialShop;
struct SpecialShopItemCategory;
struct Stain;
struct StainTransient;
struct Status;
struct StatusHitEffect;
struct StatusLoopVFX;
struct Story;
struct SubmarineExploration;
struct SubmarinePart;
struct SubmarineRank;
struct SwitchTalk;
struct TerritoryType;
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
struct VaseFlower;
struct VFX;
struct Warp;
struct WarpCondition;
struct Weather;
struct WeatherGroup;
struct WeatherRate;
struct WeddingBGM;
struct WeeklyBingoOrderData;
struct WeeklyBingoRewardData;
struct WeeklyBingoText;
struct World;
struct WorldDCGroupType;
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
   std::vector< int32_t > data;
   uint16_t order;

   Achievement( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AchievementCategory
{
   std::string name;
   uint8_t achievementKind;

   AchievementCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AchievementKind
{
   std::string name;

   AchievementKind( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   uint8_t costType;
   uint16_t cost;
   uint16_t actionCombo;
   bool preservesCombo;
   uint16_t cast100ms;
   uint16_t recast100ms;
   uint8_t cooldownGroup;
   int8_t attackType;
   uint8_t aspect;
   uint8_t actionProcStatus;
   uint16_t statusGainSelf;
   uint32_t actionData;
   uint8_t classJobCategory;
   bool affectsPosition;
   uint8_t omen;
   bool isPvP;

   Action( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionCastTimeline
{
   uint16_t name;
   uint16_t vFX;

   ActionCastTimeline( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionCastVFX
{
   uint16_t vFX;

   ActionCastVFX( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionCategory
{
   std::string name;

   ActionCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionComboRoute
{
   std::string name;
   std::vector< uint16_t > action;

   ActionComboRoute( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionIndirection
{
   int32_t name;

   ActionIndirection( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionParam
{
   int16_t name;

   ActionParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionProcStatus
{
   uint16_t status;

   ActionProcStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionTimeline
{
   std::string key;

   ActionTimeline( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionTimelineReplace
{
   uint16_t old;
   uint16_t new1;

   ActionTimelineReplace( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionTransient
{
   std::string description;

   ActionTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Addon
{
   std::string text;

   Addon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Adventure
{
   int32_t level;
   uint8_t emote;
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

   Adventure( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AdventureExPhase
{
   uint32_t quest;
   uint32_t adventureBegin;
   uint32_t adventureEnd;

   AdventureExPhase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AetherCurrent
{
   uint32_t quest;

   AetherCurrent( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AetherCurrentCompFlgSet
{
   int32_t territory;
   std::vector< int32_t > aetherCurrent;

   AetherCurrentCompFlgSet( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AetherialWheel
{
   int32_t itemUnprimed;
   int32_t itemPrimed;
   uint8_t grade;
   uint8_t hoursRequired;

   AetherialWheel( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Aetheryte
{
   uint16_t placeName;
   uint16_t aethernetName;
   uint16_t territory;
   std::vector< uint32_t > level;
   bool isAetheryte;
   uint8_t aethernetGroup;
   uint16_t map;
   int16_t aetherstreamX;
   int16_t aetherstreamY;

   Aetheryte( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationLevel
{
   uint32_t expToNext;

   AirshipExplorationLevel( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationLog
{
   std::string text;

   AirshipExplorationLog( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationParamType
{
   std::string name;

   AirshipExplorationParamType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AirshipExplorationPart
{
   uint8_t rank;
   uint8_t components;
   int16_t surveillance;
   int16_t retrieval;
   int16_t speed;
   int16_t range;
   int16_t favor;
   uint8_t repairMaterials;

   AirshipExplorationPart( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   AirshipExplorationPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5
{
   int32_t item;
   uint8_t secondaryStatTotal;
   std::vector< uint8_t > parameter;

   AnimaWeapon5( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5Param
{
   uint8_t baseParam;
   std::string name;

   AnimaWeapon5Param( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5PatternGroup
{
   std::string name;

   AnimaWeapon5PatternGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5SpiritTalk
{
   int32_t dialogue;

   AnimaWeapon5SpiritTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5SpiritTalkParam
{
   std::string prologue;
   std::string epilogue;

   AnimaWeapon5SpiritTalkParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeapon5TradeItem
{
   uint32_t crystalSand;
   uint8_t qty;
   uint8_t category;

   AnimaWeapon5TradeItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponFUITalk
{
   int32_t dialogue;

   AnimaWeaponFUITalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponFUITalkParam
{
   std::string prologue;
   std::string epilogue;

   AnimaWeaponFUITalkParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponIcon
{
   int32_t hyperconductive;
   int32_t reborn;
   int32_t sharpened;
   int32_t zodiac;
   int32_t zodiacLux;

   AnimaWeaponIcon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AnimaWeaponItem
{
   std::vector< uint32_t > item;

   AnimaWeaponItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AquariumFish
{
   uint8_t aquariumWater;
   uint8_t size;
   uint32_t item;

   AquariumFish( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AquariumWater
{
   std::string name;

   AquariumWater( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct AttackType
{
   std::string name;

   AttackType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Balloon
{
   std::string dialogue;

   Balloon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BaseParam
{
   std::string name;
   std::string description;
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
   uint8_t chestHead;
   uint8_t chestHeadLegsFeet;
   uint8_t legsFeet;
   uint8_t headChestHandsLegsFeet;
   uint8_t chestLegsGloves;
   uint8_t chestLegsFeet;

   BaseParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BattleLeve
{
   std::vector< uint16_t > enemyLevel;
   std::vector< uint32_t > bNpcName;
   std::vector< int32_t > itemsInvolved;
   std::vector< uint8_t > itemsInvolvedQty;
   std::vector< uint8_t > itemDropRate;

   BattleLeve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BeastRankBonus
{
   uint32_t item;
   std::vector< uint8_t > itemQuantity;

   BeastRankBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BeastReputationRank
{
   uint16_t requiredReputation;
   std::string name;

   BeastReputationRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BeastTribe
{
   uint8_t minLevel;
   uint8_t maxLevel;
   uint8_t beastRankBonus;
   uint32_t iconReputation;
   uint32_t icon;
   uint8_t maxRank;
   uint32_t alliedBeastTribeQuest;
   uint8_t expansion;
   uint32_t currencyItem;
   uint8_t displayOrder;
   std::string name;
   std::string nameRelation;

   BeastTribe( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Behavior
{
   uint16_t balloon;

   Behavior( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BGM
{
   std::string file;

   BGM( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BNpcAnnounceIcon
{
   uint32_t icon;

   BNpcAnnounceIcon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BNpcBase
{
   float scale;
   uint16_t modelChara;
   uint16_t bNpcCustomize;
   uint16_t npcEquip;
   int32_t arrayEventHandler;

   BNpcBase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   BNpcCustomize( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BNpcName
{
   std::string singular;
   std::string plural;

   BNpcName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Buddy
{
   int32_t questRequirement2;
   int32_t questRequirement1;
   std::string soundEffect4;
   std::string soundEffect3;
   std::string soundEffect2;
   std::string soundEffect1;

   Buddy( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BuddyAction
{
   std::string name;
   std::string description;
   int32_t icon;
   int32_t iconStatus;

   BuddyAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BuddyEquip
{
   std::string singular;
   std::string plural;
   std::string name;
   int32_t modelTop;
   int32_t modelBody;
   int32_t modelLegs;
   uint8_t grandCompany;
   uint16_t iconHead;
   uint16_t iconBody;
   uint16_t iconLegs;

   BuddyEquip( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BuddyItem
{
   uint16_t name;

   BuddyItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BuddyRank
{
   uint32_t expRequired;

   BuddyRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BuddySkill
{
   uint8_t buddyLevel;
   bool isActive;
   uint16_t defender;
   uint16_t attacker;
   uint16_t healer;

   BuddySkill( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Cabinet
{
   int32_t item;
   uint16_t order;
   uint8_t category;

   Cabinet( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CabinetCategory
{
   uint8_t menuOrder;
   int32_t icon;
   int32_t category;

   CabinetCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Calendar
{
   std::vector< uint8_t > month;
   std::vector< uint8_t > day;

   Calendar( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CharaMakeCustomize
{
   uint32_t icon;
   uint16_t data;
   bool isPurchasable;

   CharaMakeCustomize( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CharaMakeType
{
   int32_t race;
   int32_t tribe;
   int8_t gender;
   std::vector< int32_t > facialFeatureIcon;

   CharaMakeType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRace
{
   uint8_t chocoboRaceRank;
   uint8_t chocoboRaceTerritory;

   ChocoboRace( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceAbility
{
   std::string name;
   std::string description;
   uint32_t icon;
   int8_t chocoboRaceAbilityType;
   uint8_t value;

   ChocoboRaceAbility( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceAbilityType
{
   bool isActive;

   ChocoboRaceAbilityType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceItem
{
   std::string name;
   std::string description;
   uint32_t icon;

   ChocoboRaceItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceRank
{
   uint16_t ratingMin;
   uint16_t ratingMax;
   uint16_t name;
   uint16_t fee;
   int32_t icon;

   ChocoboRaceRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceStatus
{
   int32_t status;

   ChocoboRaceStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboRaceTerritory
{
   uint16_t name;
   int32_t icon;

   ChocoboRaceTerritory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboTaxi
{
   uint32_t location;

   ChocoboTaxi( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChocoboTaxiStand
{
   std::string placeName;

   ChocoboTaxiStand( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ClassJob
{
   std::string name;
   std::string abbreviation;
   uint8_t classJobCategory;
   int8_t expArrayIndex;
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
   uint16_t limitBreak1;
   uint16_t limitBreak2;
   uint16_t limitBreak3;
   uint32_t itemSoulCrystal;
   uint32_t unlockQuest;
   uint32_t relicQuest;
   uint32_t prerequisite;
   uint8_t startingLevel;

   ClassJob( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   ClassJobCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Companion
{
   std::string singular;
   std::string plural;
   uint8_t behavior;
   uint16_t icon;
   uint8_t cost;
   uint16_t hP;
   uint16_t skillAngle;
   uint8_t skillCost;
   uint8_t minionRace;

   Companion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanionMove
{
   std::string name;

   CompanionMove( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   CompanionTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   CompanyAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftDraft
{
   std::string name;
   uint8_t companyCraftDraftCategory;
   uint32_t order;

   CompanyCraftDraft( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftDraftCategory
{
   std::string name;

   CompanyCraftDraftCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftManufactoryState
{
   std::string name;

   CompanyCraftManufactoryState( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftPart
{
   uint8_t companyCraftType;
   std::vector< uint16_t > companyCraftProcess;

   CompanyCraftPart( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftProcess
{

   CompanyCraftProcess( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftSequence
{
   int32_t resultItem;
   int32_t companyCraftDraftCategory;
   int32_t companyCraftType;
   int32_t companyCraftDraft;
   std::vector< uint16_t > companyCraftPart;

   CompanyCraftSequence( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftSupplyItem
{
   uint32_t item;

   CompanyCraftSupplyItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompanyCraftType
{
   std::string name;

   CompanyCraftType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompleteJournal
{
   std::string name;
   std::vector< int32_t > cutscene;

   CompleteJournal( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CompleteJournalCategory
{
   uint32_t firstQuest;
   uint32_t lastQuest;

   CompleteJournalCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentExAction
{
   uint32_t name;
   uint8_t charges;

   ContentExAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentFinderCondition
{
   uint16_t instanceContent;
   uint8_t contentMemberType;
   uint8_t classJobLevelRequired;
   uint8_t classJobLevelSync;
   uint16_t itemLevelRequired;
   uint16_t itemLevelSync;
   uint8_t contentIndicator;
   uint8_t contentType;
   uint32_t icon;

   ContentFinderCondition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentFinderConditionTransient
{
   std::string description;

   ContentFinderConditionTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentMemberType
{
   uint8_t tanksPerParty;
   uint8_t healersPerParty;
   uint8_t meleesPerParty;
   uint8_t rangedPerParty;

   ContentMemberType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentNpcTalk
{
   std::vector< uint32_t > contentTalk;

   ContentNpcTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentRoulette
{
   std::string name;
   std::string description;
   std::string dutyType;
   bool isInDutyFinder;
   uint16_t itemLevelRequired;
   uint32_t icon;
   uint16_t rewardTomeA;
   uint16_t rewardTomeB;
   uint16_t rewardTomeC;
   uint8_t sortKey;
   uint8_t contentMemberType;
   bool requireAllDuties;

   ContentRoulette( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentsNote
{
   uint8_t contentType;
   int32_t requiredAmount;

   ContentsNote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentsNoteCategory
{
   uint8_t type;

   ContentsNoteCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentTalk
{
   uint8_t contentTalkParam;
   std::string text;

   ContentTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentTalkParam
{
   bool param;
   uint32_t testAction;

   ContentTalkParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ContentType
{
   std::string name;
   uint32_t icon;
   uint32_t iconDutyFinder;

   ContentType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   CraftAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CraftLeve
{
   int32_t leve;
   uint8_t repeats;

   CraftLeve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CraftType
{
   std::string name;

   CraftType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Currency
{
   uint32_t item;
   uint32_t limit;

   Currency( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CustomTalk
{
   uint32_t iconActor;
   uint32_t iconMap;
   std::string name;
   std::vector< std::string > scriptInstruction;
   std::vector< uint32_t > scriptArg;
   bool text;

   CustomTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Cutscene
{
   std::string path;

   Cutscene( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CutScreenImage
{
   int32_t image;

   CutScreenImage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DailySupplyItem
{

   DailySupplyItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonBan
{
   uint16_t screenImage;
   uint16_t logMessage;
   uint16_t name;

   DeepDungeonBan( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonDanger
{
   uint16_t screenImage;
   uint16_t logMessage;
   uint16_t name;

   DeepDungeonDanger( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonEquipment
{
   uint32_t icon;
   std::string singular;
   std::string plural;
   std::string name;
   std::string description;

   DeepDungeonEquipment( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonFloorEffectUI
{
   uint32_t icon;
   std::string name;
   std::string description;

   DeepDungeonFloorEffectUI( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonItem
{
   uint32_t icon;
   std::string singular;
   std::string plural;
   std::string name;
   std::string tooltip;
   uint32_t action;

   DeepDungeonItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeepDungeonStatus
{
   uint16_t screenImage;
   uint16_t logMessage;
   uint16_t name;

   DeepDungeonStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DefaultTalk
{
   std::vector< uint16_t > actionTimelinePose;
   std::vector< std::string > text;

   DefaultTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DeliveryQuest
{
   int32_t quest;

   DeliveryQuest( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DisposalShop
{
   std::string shopName;

   DisposalShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DisposalShopFilterType
{
   std::string category;

   DisposalShopFilterType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DisposalShopItem
{
   int32_t itemDisposed;
   int32_t itemReceived;
   uint32_t quantityReceived;

   DisposalShopItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DpsChallenge
{
   uint16_t playerLevel;
   uint16_t placeName;
   uint32_t icon;
   uint16_t order;
   std::string name;
   std::string description;

   DpsChallenge( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DpsChallengeOfficer
{
   uint32_t unlockQuest;
   std::vector< uint16_t > challengeName;

   DpsChallengeOfficer( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct DpsChallengeTransient
{
   uint16_t instanceContent;

   DpsChallengeTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Emote
{
   std::string name;
   uint8_t emoteCategory;
   int32_t textCommand;
   uint16_t icon;
   uint16_t logMessageTargeted;
   uint16_t logMessageUntargeted;

   Emote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EmoteCategory
{
   std::string name;

   EmoteCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ENpcBase
{
   std::vector< uint32_t > eNpcData;
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
   uint16_t balloon;

   ENpcBase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ENpcResident
{
   std::string singular;
   std::string plural;
   std::string title;
   uint8_t map;

   ENpcResident( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EObj
{
   uint32_t data;

   EObj( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EObjName
{
   std::string singular;

   EObjName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   EquipRaceCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   EquipSlotCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EurekaAethernet
{
   uint16_t location;

   EurekaAethernet( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EurekaGrowData
{
   uint16_t baseResistance;

   EurekaGrowData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EurekaSphereElementAdjust
{
   uint16_t powerModifier;

   EurekaSphereElementAdjust( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EventAction
{
   std::string name;
   uint16_t icon;
   uint8_t castTime;

   EventAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EventIconPriority
{
   std::vector< uint32_t > icon;

   EventIconPriority( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EventIconType
{
   uint32_t npcIconAvailable;
   uint32_t mapIconAvailable;
   uint32_t npcIconInvalid;
   uint32_t mapIconInvalid;
   uint8_t iconRange;

   EventIconType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EventItem
{
   std::string singular;
   std::string plural;
   int8_t rarity;
   std::string name;
   uint16_t icon;
   uint8_t stackSize;
   uint32_t quest;
   uint8_t castTime;

   EventItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EventItemHelp
{
   std::string description;

   EventItemHelp( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ExVersion
{
   std::string name;

   ExVersion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Fate
{
   uint8_t eurekaFate;
   uint32_t location;
   uint8_t classJobLevel;
   uint8_t classJobLevelMax;
   uint32_t eventItem;
   uint32_t iconObjective;
   uint32_t iconMap;
   int32_t music;
   std::string name;
   std::string description;
   std::string objective;
   std::vector< std::string > statusText;
   uint32_t arrayIndex;

   Fate( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCActivity
{
   std::string text;
   uint8_t fCActivityCategory;

   FCActivity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCActivityCategory
{
   std::string name;

   FCActivityCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCAuthority
{
   std::string name;
   int32_t fCAuthorityCategory;

   FCAuthority( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCAuthorityCategory
{
   std::string name;

   FCAuthorityCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCChestName
{
   std::string name;

   FCChestName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FccShop
{
   std::string name;

   FccShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCHierarchy
{
   std::string name;

   FCHierarchy( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCProfile
{
   std::string name;

   FCProfile( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCReputation
{
   uint32_t pointsToNext;
   uint32_t requiredPoints;
   std::string name;

   FCReputation( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCRights
{
   std::string name;
   std::string description;
   uint16_t icon;
   uint8_t fCRank;

   FCRights( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FieldMarker
{
   int32_t vFX;
   uint16_t icon;

   FieldMarker( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FishingSpot
{
   uint8_t gatheringLevel;
   std::string bigFishOnReach;
   std::string bigFishOnEnd;
   uint8_t fishingSpotCategory;
   uint16_t territoryType;
   int16_t x;
   int16_t z;
   uint16_t radius;
   std::vector< int32_t > item;
   uint16_t placeName;

   FishingSpot( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FishParameter
{
   std::string text;
   int32_t item;
   uint16_t gatheringItemLevel;
   int32_t territoryType;
   bool isFish;
   uint16_t gatheringSubCategory;

   FishParameter( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GardeningSeed
{
   uint32_t item;
   uint32_t icon;

   GardeningSeed( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringCondition
{
   std::string text;

   GatheringCondition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringExp
{
   uint16_t exp;

   GatheringExp( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringItem
{
   int32_t item;
   uint16_t gatheringItemLevel;
   bool isHidden;

   GatheringItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringItemLevelConvertTable
{
   uint8_t gatheringItemLevel;
   uint8_t stars;

   GatheringItemLevelConvertTable( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringItemPoint
{
   uint32_t gatheringPoint;

   GatheringItemPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringNotebookList
{
   std::vector< int32_t > gatheringItem;

   GatheringNotebookList( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPoint
{
   int32_t gatheringPointBase;
   std::vector< uint16_t > gatheringPointBonus;
   uint16_t territoryType;
   uint16_t placeName;
   uint16_t gatheringSubCategory;

   GatheringPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBase
{
   int32_t gatheringType;
   uint8_t gatheringLevel;
   std::vector< int32_t > item;
   bool isLimited;

   GatheringPointBase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBonus
{
   uint8_t condition;
   uint16_t conditionValue;
   uint8_t bonusType;
   uint16_t bonusValue;

   GatheringPointBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBonusType
{
   std::string text;

   GatheringPointBonusType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPointName
{
   std::string singular;
   std::string plural;

   GatheringPointName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringSubCategory
{
   int32_t item;
   std::string folkloreBook;

   GatheringSubCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringType
{
   std::string name;
   int32_t iconMain;
   int32_t iconOff;

   GatheringType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   GcArmyExpedition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GcArmyExpeditionMemberBonus
{
   uint8_t race;
   uint8_t classJob;

   GcArmyExpeditionMemberBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GcArmyExpeditionType
{
   std::string name;

   GcArmyExpeditionType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GcArmyMemberGrow
{
   uint8_t classJob;
   int32_t classBook;

   GcArmyMemberGrow( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GcArmyTraining
{
   int8_t physicalBonus;
   int8_t mentalBonus;
   int8_t tacticalBonus;
   uint32_t experience;
   std::string name;
   std::string description;

   GcArmyTraining( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCRankGridaniaFemaleText
{
   std::string name;
   std::string plural;
   std::string nameRank;

   GCRankGridaniaFemaleText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCRankGridaniaMaleText
{
   std::string name;
   std::string plural;
   std::string nameRank;

   GCRankGridaniaMaleText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCRankLimsaFemaleText
{
   std::string name;
   std::string plural;
   std::string nameRank;

   GCRankLimsaFemaleText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCRankLimsaMaleText
{
   std::string name;
   std::string plural;
   std::string nameRank;

   GCRankLimsaMaleText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCRankUldahFemaleText
{
   std::string name;
   std::string plural;
   std::string nameRank;

   GCRankUldahFemaleText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCRankUldahMaleText
{
   std::string name;
   std::string plural;
   std::string nameRank;

   GCRankUldahMaleText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCScripShopCategory
{
   int8_t grandCompany;
   int8_t tier;
   int8_t subCategory;

   GCScripShopCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCScripShopItem
{
   int32_t item;
   int32_t requiredGrandCompanyRank;
   uint32_t costGCSeals;
   uint8_t sortKey;

   GCScripShopItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCShop
{
   int8_t grandCompany;

   GCShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCShopItemCategory
{
   std::string name;

   GCShopItemCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCSupplyDuty
{

   GCSupplyDuty( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GCSupplyDutyReward
{
   uint32_t experienceSupply;
   uint32_t experienceProvisioning;
   uint32_t sealsExpertDelivery;
   uint32_t sealsSupply;
   uint32_t sealsProvisioning;

   GCSupplyDutyReward( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GeneralAction
{
   std::string name;
   std::string description;
   uint16_t action;
   int32_t icon;

   GeneralAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GilShop
{
   std::string name;

   GilShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GilShopItem
{
   int32_t item;
   std::vector< int32_t > rowRequired;
   uint16_t stateRequired;
   uint16_t patch;

   GilShopItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GoldSaucerTextData
{
   std::string text;

   GoldSaucerTextData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GrandCompany
{
   std::string name;

   GrandCompany( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   GrandCompanyRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GuardianDeity
{
   std::string name;
   std::string description;
   uint16_t icon;

   GuardianDeity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GuildleveAssignment
{
   std::vector< uint32_t > quest;

   GuildleveAssignment( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GuildOrderGuide
{

   GuildOrderGuide( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GuildOrderOfficer
{

   GuildOrderOfficer( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct HouseRetainerPose
{
   uint16_t actionTimeline;

   HouseRetainerPose( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct HousingFurniture
{
   uint16_t modelKey;
   uint8_t housingItemCategory;
   uint8_t usageType;
   uint32_t usageParameter;
   uint8_t housingLayoutLimit;
   uint32_t event;
   uint32_t item;
   bool destroyOnRemoval;

   HousingFurniture( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct HousingYardObject
{
   uint8_t modelKey;
   uint8_t housingItemCategory;
   uint8_t usageType;
   uint32_t usageParameter;
   uint8_t housingLayoutLimit;
   uint32_t event;
   uint32_t item;
   bool destroyOnRemoval;

   HousingYardObject( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct InstanceContent
{
   uint8_t instanceContentType;
   uint8_t weekRestriction;
   uint16_t timeLimitmin;
   std::string name;
   uint16_t bGM;
   uint32_t territoryType;
   uint32_t instanceContentTextDataBossStart;
   uint32_t instanceContentTextDataBossEnd;
   uint32_t bNpcBaseBoss;
   uint32_t instanceContentTextDataObjectiveStart;
   uint32_t instanceContentTextDataObjectiveEnd;
   uint16_t sortKey;
   uint16_t newPlayerBonusA;
   uint16_t newPlayerBonusB;
   uint16_t finalBossCurrencyA;
   uint16_t finalBossCurrencyB;
   uint16_t finalBossCurrencyC;
   int32_t instanceContentBuff;
   uint8_t partyCondition;

   InstanceContent( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct InstanceContentBuff
{
   uint16_t echoStart;
   uint16_t echoDeath;

   InstanceContentBuff( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct InstanceContentTextData
{
   std::string text;

   InstanceContentTextData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Item
{
   std::string singular;
   std::string plural;
   int8_t startsWithVowel;
   std::string description;
   std::string name;
   uint16_t icon;
   uint16_t levelItem;
   uint8_t rarity;
   uint8_t filterGroup;
   uint32_t stain;
   uint8_t itemUICategory;
   uint8_t itemSearchCategory;
   uint8_t equipSlotCategory;
   uint32_t stackSize;
   bool isUnique;
   bool isUntradable;
   bool isIndisposable;
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
   uint16_t salvage;
   bool isCollectable;
   uint16_t aetherialReduce;
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

   Item( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ItemAction
{
   uint16_t type;
   std::vector< uint16_t > data;
   std::vector< uint16_t > dataHQ;

   ItemAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ItemFood
{

   ItemFood( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ItemSearchCategory
{
   std::string name;
   int32_t icon;
   uint8_t category;
   uint8_t order;
   int8_t classJob;

   ItemSearchCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ItemSeries
{
   std::string name;

   ItemSeries( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ItemSpecialBonus
{
   std::string name;

   ItemSpecialBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ItemUICategory
{
   std::string name;
   int32_t icon;
   uint8_t orderMinor;
   uint8_t orderMajor;

   ItemUICategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct JournalCategory
{
   std::string name;
   uint8_t journalSection;

   JournalCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct JournalGenre
{
   int32_t icon;
   uint8_t journalCategory;
   std::string name;

   JournalGenre( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct JournalSection
{
   std::string name;

   JournalSection( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Leve
{
   std::string name;
   std::string description;
   int32_t leveClient;
   int32_t leveAssignmentType;
   uint16_t classJobLevel;
   uint8_t allowanceCost;
   int32_t placeNameStart;
   int32_t placeNameIssued;
   uint8_t classJobCategory;
   int32_t journalGenre;
   int32_t placeNameStartZone;
   int32_t iconCityState;
   int32_t dataId;
   uint32_t expReward;
   uint32_t gilReward;
   uint16_t leveRewardItem;
   uint8_t leveVfx;
   uint8_t leveVfxFrame;
   uint32_t levelLevemete;
   int32_t iconIssuer;
   uint32_t levelStart;
   uint16_t bGM;

   Leve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LeveAssignmentType
{
   bool isFaction;
   int32_t icon;
   std::string name;

   LeveAssignmentType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LeveClient
{
   std::string name;

   LeveClient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Level
{
   float x;
   float y;
   float z;
   float yaw;
   float radius;
   uint8_t type;
   uint32_t objectKey;
   uint16_t map;
   uint32_t eventId;
   uint16_t territory;

   Level( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LeveRewardItem
{

   LeveRewardItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LeveRewardItemGroup
{

   LeveRewardItemGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LeveVfx
{
   std::string effect;
   int32_t icon;

   LeveVfx( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LogFilter
{
   uint16_t logKind;
   std::string name;
   std::string example;

   LogFilter( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LogKind
{
   std::string format;
   std::string name;
   std::string example;
   uint8_t logKindCategoryText;

   LogKind( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LogKindCategoryText
{
   std::string text;

   LogKindCategoryText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct LogMessage
{
   uint16_t logKind;
   std::string text;

   LogMessage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MacroIcon
{
   int32_t icon;

   MacroIcon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MacroIconRedirectOld
{
   uint32_t iconOld;
   int32_t iconNew;

   MacroIconRedirectOld( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MainCommand
{
   int32_t icon;
   uint8_t mainCommandCategory;
   std::string name;
   std::string description;

   MainCommand( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MainCommandCategory
{
   std::string name;

   MainCommandCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Map
{
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
   uint16_t territoryType;
   bool discoveryArrayByte;

   Map( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   MapMarker( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MapMarkerRegion
{
   int16_t x;

   MapMarkerRegion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MapSymbol
{
   int32_t icon;
   int32_t placeName;

   MapSymbol( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Marker
{
   int32_t icon;
   std::string name;

   Marker( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MasterpieceSupplyDuty
{
   uint8_t classJob;
   uint8_t classJobLevel;
   uint16_t rewardCurrency;

   MasterpieceSupplyDuty( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MasterpieceSupplyMultiplier
{
   std::vector< uint16_t > xpMultiplier;
   std::vector< uint16_t > currencyMultiplier;

   MasterpieceSupplyMultiplier( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Materia
{
   std::vector< int32_t > item;
   uint8_t baseParam;
   std::vector< uint8_t > value;

   Materia( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MinionRace
{
   std::string name;

   MinionRace( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MinionRules
{
   std::string rule;
   std::string description;

   MinionRules( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MinionSkillType
{
   std::string name;

   MinionSkillType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MobHuntTarget
{
   uint16_t name;
   uint16_t fATE;
   uint32_t icon;
   uint16_t territoryType;
   uint16_t placeName;

   MobHuntTarget( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ModelChara
{
   uint8_t type;
   uint16_t model;
   uint8_t base;
   uint8_t variant;

   ModelChara( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MonsterNote
{
   std::vector< uint16_t > monsterNoteTarget;
   std::vector< uint8_t > count;
   uint32_t reward;
   std::string name;

   MonsterNote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MonsterNoteTarget
{
   uint16_t bNpcName;
   int32_t icon;

   MonsterNoteTarget( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Mount
{
   std::string singular;
   std::string plural;
   uint8_t flyingCondition;
   uint8_t isFlying;
   uint16_t rideBGM;
   int16_t order;
   uint16_t icon;

   Mount( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MountAction
{
   std::vector< uint16_t > action;

   MountAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   MoveTimeline( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MoveVfx
{
   uint16_t zero;
   uint16_t one;

   MoveVfx( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   NpcEquip( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Omen
{
   std::string fileName;

   Omen( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct OnlineStatus
{
   uint8_t priority;
   std::string name;
   uint32_t icon;

   OnlineStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Opening
{
   std::string name;

   Opening( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Orchestrion
{
   std::string name;
   std::string description;

   Orchestrion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct OrchestrionCategory
{
   std::string name;

   OrchestrionCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct OrchestrionPath
{
   std::string file;

   OrchestrionPath( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct OrchestrionUiparam
{
   uint8_t orchestrionCategory;
   uint16_t order;

   OrchestrionUiparam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ParamGrow
{
   int32_t expToNext;
   uint8_t additionalActions;
   int32_t mpModifier;
   int32_t baseSpeed;
   int32_t levelModifier;
   uint8_t questExpModifier;
   uint16_t hpModifier;
   int32_t huntingLogExpReward;

   ParamGrow( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   Perform( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct PerformTransient
{
   std::string text;

   PerformTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Pet
{
   std::string name;

   Pet( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct PetAction
{
   std::string name;
   std::string description;
   uint16_t action;
   uint8_t pet;

   PetAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Picture
{
   int32_t item;
   int32_t image;
   int32_t signature;

   Picture( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct PlaceName
{
   std::string name;
   std::string nameNoArticle;

   PlaceName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct PublicContent
{
   uint16_t timeLimit;
   uint32_t mapIcon;
   std::string name;
   uint16_t territoryType;

   PublicContent( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct PvPActionSort
{
   uint8_t name;
   uint16_t action;

   PvPActionSort( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   uint8_t classJobUnlock;
   uint8_t grandCompany;
   uint8_t grandCompanyRank;
   uint8_t instanceContentJoin;
   std::vector< uint32_t > instanceContent;
   uint16_t bellStart;
   uint16_t bellEnd;
   uint8_t beastTribe;
   uint8_t beastReputationRank;
   int32_t mountRequired;
   bool isHouseRequired;
   uint32_t eNpcResidentStart;
   uint32_t eNpcResidentEnd;
   bool isRepeatable;
   uint8_t repeatIntervalType;
   std::vector< std::string > scriptInstruction;
   std::vector< uint32_t > scriptArg;
   std::vector< uint32_t > level;
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
   uint8_t otherReward;
   uint32_t instanceContentUnlock;
   uint8_t tomestoneReward;
   uint8_t tomestoneCountReward;
   uint8_t reputationReward;
   uint16_t placeName;
   uint8_t journalGenre;
   uint32_t icon;
   uint32_t iconSpecial;
   uint8_t eventIconType;
   uint16_t sortKey;

   Quest( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct QuestClassJobReward
{
   uint8_t classJobCategory;
   std::vector< uint32_t > rewardItem;
   std::vector< uint8_t > rewardAmount;
   std::vector< uint32_t > requiredItem;
   std::vector< uint8_t > requiredAmount;

   QuestClassJobReward( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct QuestRepeatFlag
{
   uint32_t quest;

   QuestRepeatFlag( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct QuestRewardOther
{
   std::string name;

   QuestRewardOther( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct QuickChat
{
   std::string nameAction;
   int32_t icon;
   int32_t addon;
   int8_t quickChatTransient;

   QuickChat( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct QuickChatTransient
{
   std::string textOutput;

   QuickChatTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   Race( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboItem
{
   int32_t item;
   uint8_t category;
   std::vector< uint8_t > param;

   RacingChocoboItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboName
{
   std::string name;

   RacingChocoboName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboNameCategory
{
   uint8_t sortKey;
   std::string name;

   RacingChocoboNameCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboNameInfo
{
   uint8_t racingChocoboNameCategory;

   RacingChocoboNameInfo( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RacingChocoboParam
{
   std::string name;

   RacingChocoboParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Recipe
{
   int32_t craftType;
   uint16_t recipeLevelTable;
   int32_t itemResult;
   uint8_t amountResult;
   uint8_t recipeElement;
   bool isSecondary;
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

   Recipe( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RecipeElement
{
   std::string name;

   RecipeElement( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RecipeLevelTable
{
   uint8_t classJobLevel;
   uint8_t stars;
   uint16_t difficulty;
   int16_t quality;
   uint16_t durability;

   RecipeLevelTable( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RecipeNotebookList
{
   std::vector< int32_t > recipe;

   RecipeNotebookList( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RecommendContents
{
   int32_t level;

   RecommendContents( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Relic
{
   uint32_t itemAtma;
   uint32_t itemAnimus;
   int32_t icon;

   Relic( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Relic3
{
   uint32_t itemAnimus;
   uint32_t itemScroll;
   uint8_t materiaLimit;
   uint32_t itemNovus;
   int32_t icon;

   Relic3( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   RelicItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RelicNote
{
   uint32_t eventItem;
   std::vector< uint16_t > monsterNoteTargetNM;
   std::vector< uint16_t > leve;

   RelicNote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RelicNoteCategory
{
   std::string text;

   RelicNoteCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   uint16_t requiredGathering;
   uint16_t task;

   RetainerTask( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskLvRange
{
   uint8_t min;
   uint8_t max;

   RetainerTaskLvRange( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskNormal
{
   int32_t item;
   uint8_t quantity0;
   uint8_t quantity1;
   uint8_t quantity2;
   int16_t gatheringLog;
   int16_t fishingLog;

   RetainerTaskNormal( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskParameter
{
   std::vector< int16_t > itemLevelDoW;
   std::vector< int16_t > gatheringDoL;
   std::vector< int16_t > gatheringFSH;

   RetainerTaskParameter( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskRandom
{
   std::string name;
   int16_t requirement;

   RetainerTaskRandom( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Salvage
{
   uint16_t optimalSkill;

   Salvage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SatisfactionNpc
{
   int32_t npc;
   int32_t questRequired;
   uint8_t deliveriesPerWeek;
   std::vector< int32_t > supplyIndex;
   std::vector< uint16_t > satisfactionRequired;
   int32_t icon;

   SatisfactionNpc( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   SatisfactionSupply( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SatisfactionSupplyReward
{
   uint16_t satisfactionLow;
   uint16_t satisfactionMid;
   uint16_t satisfactionHigh;
   uint16_t gilLow;
   uint16_t gilMid;
   uint16_t gilHigh;

   SatisfactionSupplyReward( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ScenarioTree
{
   uint8_t type;
   uint16_t image;

   ScenarioTree( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ScenarioTreeTips
{
   uint32_t tips1;
   uint32_t tips2;

   ScenarioTreeTips( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ScenarioTreeTipsClassQuest
{
   uint32_t quest;
   uint16_t requiredLevel;
   uint8_t requiredExpansion;
   uint32_t requiredQuest;

   ScenarioTreeTipsClassQuest( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ScenarioTreeTipsQuest
{
   uint32_t level;

   ScenarioTreeTipsQuest( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ScenarioType
{
   std::string type;

   ScenarioType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ScreenImage
{
   uint32_t image;

   ScreenImage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SecretRecipeBook
{
   int32_t item;
   std::string name;

   SecretRecipeBook( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2Mission
{
   uint32_t item1;
   uint32_t item2;
   uint16_t objective1;
   uint8_t requiredAmount1;
   uint16_t objective2;
   uint8_t requiredAmount2;
   uint16_t objective3;
   uint32_t image;

   SkyIsland2Mission( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2MissionDetail
{
   uint8_t type;
   uint8_t range;
   uint32_t eObj;
   std::string objective;

   SkyIsland2MissionDetail( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2MissionType
{
   bool type;

   SkyIsland2MissionType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SkyIsland2RangeType
{
   uint8_t type;

   SkyIsland2RangeType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SpearfishingItem
{
   std::string description;
   int32_t item;
   uint16_t gatheringItemLevel;
   uint16_t territoryType;
   bool isVisible;

   SpearfishingItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   SpearfishingNotebook( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SpecialShop
{
   std::string name;
   std::vector< int32_t > questItem;
   int32_t questShop;

   SpecialShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SpecialShopItemCategory
{
   std::string name;

   SpecialShopItemCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Stain
{
   uint32_t color;
   uint8_t shade;
   std::string name;

   Stain( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct StainTransient
{
   uint32_t item1;
   uint32_t item2;

   StainTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Status
{
   std::string name;
   std::string description;
   uint16_t icon;
   uint8_t maxStacks;
   uint8_t category;
   uint8_t hitEffect;
   uint8_t vFX;
   bool lockMovement;
   bool lockActions;
   bool lockControl;
   bool transfiguration;
   bool canDispel;
   bool inflictedByActor;
   bool isPermanent;
   bool isFcBuff;
   bool invisibility;

   Status( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct StatusHitEffect
{
   uint16_t location;

   StatusHitEffect( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct StatusLoopVFX
{
   uint16_t location;

   StatusLoopVFX( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Story
{

   Story( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SubmarineExploration
{
   std::string destination;
   std::string location;
   uint8_t rankReq;
   uint8_t ceruleumTankReq;
   uint16_t durationmin;
   uint8_t distanceForSurvey;
   uint32_t expReward;

   SubmarineExploration( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   uint8_t repairMaterials;

   SubmarinePart( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SubmarineRank
{
   uint16_t rank;
   uint32_t expToNext;

   SubmarineRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SwitchTalk
{
   std::vector< uint32_t > quest;
   std::vector< uint32_t > defaultTalk;

   SwitchTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TerritoryType
{
   std::string name;
   std::string bg;
   uint16_t placeNameRegion;
   uint16_t placeNameZone;
   uint16_t placeName;
   uint16_t map;
   uint8_t territoryIntendedUse;
   uint8_t weatherRate;
   uint32_t arrayEventHandler;
   int32_t aetheryte;

   TerritoryType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TextCommand
{
   std::string command;
   std::string shortCommand;
   std::string description;
   std::string alias;
   std::string shortAlias;

   TextCommand( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Title
{
   std::string masculine;
   std::string feminine;
   bool isPrefix;

   Title( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Tomestones
{
   uint16_t weeklyLimit;

   Tomestones( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TomestonesItem
{
   int32_t item;
   int32_t tomestones;

   TomestonesItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TopicSelect
{
   std::string name;

   TopicSelect( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Town
{
   std::string name;
   int32_t icon;

   Town( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Trait
{
   std::string name;
   int32_t icon;
   uint8_t classJob;
   uint8_t level;
   int16_t value;
   uint8_t classJobCategory;

   Trait( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TraitRecast
{
   uint16_t trait;
   uint16_t action;
   uint16_t timeds;

   TraitRecast( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TraitTransient
{
   std::string description;

   TraitTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Transformation
{
   int16_t model;
   int32_t bNpcCustomize;
   int32_t bNpcEquip;
   std::vector< uint16_t > action;
   float speed;
   float scale;
   bool isPvP;
   bool isEvent;
   bool playerCamera;

   Transformation( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Treasure
{
   uint32_t item;

   Treasure( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TreasureHuntRank
{
   uint32_t icon;
   int32_t itemName;
   int32_t keyItemName;
   int32_t instanceMap;
   uint8_t maxPartySize;
   uint8_t minPartySize;

   TreasureHuntRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Tribe
{
   std::string masculine;
   std::string feminine;
   int8_t sTR;
   int8_t dEX;
   int8_t vIT;
   int8_t iNT;
   int8_t mND;
   int8_t pIE;

   Tribe( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   TripleTriad( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCard
{
   std::string name;
   int8_t startsWithVowel;
   std::string description;

   TripleTriadCard( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCardRarity
{
   uint8_t stars;

   TripleTriadCardRarity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   TripleTriadCardResident( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCardType
{
   std::string name;

   TripleTriadCardType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TripleTriadCompetition
{
   std::string name;

   TripleTriadCompetition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TripleTriadRule
{
   std::string name;

   TripleTriadRule( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Tutorial
{
   uint32_t exp;
   uint32_t gil;
   uint32_t rewardTank;
   uint32_t rewardMelee;
   uint32_t rewardRanged;
   uint32_t objective;

   Tutorial( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TutorialDPS
{
   uint8_t objective;

   TutorialDPS( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TutorialHealer
{
   uint8_t objective;

   TutorialHealer( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct TutorialTank
{
   uint8_t objective;

   TutorialTank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct VaseFlower
{
   uint32_t item;

   VaseFlower( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct VFX
{
   std::string location;

   VFX( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Warp
{
   uint32_t level;
   uint16_t placeName;
   uint32_t defaultTalk1;
   uint32_t defaultTalk2;
   uint32_t defaultTalk3;
   uint16_t warpCondition;
   uint16_t warpLogic;

   Warp( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WarpCondition
{
   uint32_t requiredQuest1;
   uint32_t requiredQuest2;
   uint32_t dRequiredQuest3;
   uint32_t requiredQuest4;

   WarpCondition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Weather
{
   int32_t icon;
   std::string name;
   std::string description;

   Weather( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WeatherGroup
{
   int32_t weatherRate;

   WeatherGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WeatherRate
{

   WeatherRate( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WeddingBGM
{
   uint16_t song;
   std::string songName;

   WeddingBGM( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WeeklyBingoOrderData
{
   uint32_t data;
   uint8_t text;
   uint32_t icon;

   WeeklyBingoOrderData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WeeklyBingoRewardData
{
   uint32_t rewardItem2;
   bool rewardHQ2;
   uint16_t rewardQuantity2;

   WeeklyBingoRewardData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WeeklyBingoText
{
   std::string description;

   WeeklyBingoText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct World
{
   uint8_t dataCenter;

   World( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct WorldDCGroupType
{
   std::string name;

   WorldDCGroupType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct YKW
{
   uint32_t item;
   std::vector< uint16_t > location;

   YKW( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ZoneSharedGroup
{
   uint32_t quest1;
   uint32_t quest2;
   uint32_t quest3;
   uint32_t quest4;
   uint32_t quest5;
   uint32_t quest6;

   ZoneSharedGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
        return *boost::get< T >( &fields.at( index ) );
     }

     void loadIdList( xiv::exd::Exd& data, std::set< uint32_t >& outIdList );

     boost::shared_ptr< xiv::dat::GameData > m_data;
     boost::shared_ptr< xiv::exd::ExdData > m_exd_data;

     xiv::exd::Exd m_AchievementDat;
     xiv::exd::Exd m_AchievementCategoryDat;
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
     xiv::exd::Exd m_ActionTimelineReplaceDat;
     xiv::exd::Exd m_ActionTransientDat;
     xiv::exd::Exd m_AddonDat;
     xiv::exd::Exd m_AdventureDat;
     xiv::exd::Exd m_AdventureExPhaseDat;
     xiv::exd::Exd m_AetherCurrentDat;
     xiv::exd::Exd m_AetherCurrentCompFlgSetDat;
     xiv::exd::Exd m_AetherialWheelDat;
     xiv::exd::Exd m_AetheryteDat;
     xiv::exd::Exd m_AirshipExplorationLevelDat;
     xiv::exd::Exd m_AirshipExplorationLogDat;
     xiv::exd::Exd m_AirshipExplorationParamTypeDat;
     xiv::exd::Exd m_AirshipExplorationPartDat;
     xiv::exd::Exd m_AirshipExplorationPointDat;
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
     xiv::exd::Exd m_AquariumFishDat;
     xiv::exd::Exd m_AquariumWaterDat;
     xiv::exd::Exd m_AttackTypeDat;
     xiv::exd::Exd m_BalloonDat;
     xiv::exd::Exd m_BaseParamDat;
     xiv::exd::Exd m_BattleLeveDat;
     xiv::exd::Exd m_BeastRankBonusDat;
     xiv::exd::Exd m_BeastReputationRankDat;
     xiv::exd::Exd m_BeastTribeDat;
     xiv::exd::Exd m_BehaviorDat;
     xiv::exd::Exd m_BGMDat;
     xiv::exd::Exd m_BNpcAnnounceIconDat;
     xiv::exd::Exd m_BNpcBaseDat;
     xiv::exd::Exd m_BNpcCustomizeDat;
     xiv::exd::Exd m_BNpcNameDat;
     xiv::exd::Exd m_BuddyDat;
     xiv::exd::Exd m_BuddyActionDat;
     xiv::exd::Exd m_BuddyEquipDat;
     xiv::exd::Exd m_BuddyItemDat;
     xiv::exd::Exd m_BuddyRankDat;
     xiv::exd::Exd m_BuddySkillDat;
     xiv::exd::Exd m_CabinetDat;
     xiv::exd::Exd m_CabinetCategoryDat;
     xiv::exd::Exd m_CalendarDat;
     xiv::exd::Exd m_CharaMakeCustomizeDat;
     xiv::exd::Exd m_CharaMakeTypeDat;
     xiv::exd::Exd m_ChocoboRaceDat;
     xiv::exd::Exd m_ChocoboRaceAbilityDat;
     xiv::exd::Exd m_ChocoboRaceAbilityTypeDat;
     xiv::exd::Exd m_ChocoboRaceItemDat;
     xiv::exd::Exd m_ChocoboRaceRankDat;
     xiv::exd::Exd m_ChocoboRaceStatusDat;
     xiv::exd::Exd m_ChocoboRaceTerritoryDat;
     xiv::exd::Exd m_ChocoboTaxiDat;
     xiv::exd::Exd m_ChocoboTaxiStandDat;
     xiv::exd::Exd m_ClassJobDat;
     xiv::exd::Exd m_ClassJobCategoryDat;
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
     xiv::exd::Exd m_CompleteJournalDat;
     xiv::exd::Exd m_CompleteJournalCategoryDat;
     xiv::exd::Exd m_ContentExActionDat;
     xiv::exd::Exd m_ContentFinderConditionDat;
     xiv::exd::Exd m_ContentFinderConditionTransientDat;
     xiv::exd::Exd m_ContentMemberTypeDat;
     xiv::exd::Exd m_ContentNpcTalkDat;
     xiv::exd::Exd m_ContentRouletteDat;
     xiv::exd::Exd m_ContentsNoteDat;
     xiv::exd::Exd m_ContentsNoteCategoryDat;
     xiv::exd::Exd m_ContentTalkDat;
     xiv::exd::Exd m_ContentTalkParamDat;
     xiv::exd::Exd m_ContentTypeDat;
     xiv::exd::Exd m_CraftActionDat;
     xiv::exd::Exd m_CraftLeveDat;
     xiv::exd::Exd m_CraftTypeDat;
     xiv::exd::Exd m_CurrencyDat;
     xiv::exd::Exd m_CustomTalkDat;
     xiv::exd::Exd m_CutsceneDat;
     xiv::exd::Exd m_CutScreenImageDat;
     xiv::exd::Exd m_DailySupplyItemDat;
     xiv::exd::Exd m_DeepDungeonBanDat;
     xiv::exd::Exd m_DeepDungeonDangerDat;
     xiv::exd::Exd m_DeepDungeonEquipmentDat;
     xiv::exd::Exd m_DeepDungeonFloorEffectUIDat;
     xiv::exd::Exd m_DeepDungeonItemDat;
     xiv::exd::Exd m_DeepDungeonStatusDat;
     xiv::exd::Exd m_DefaultTalkDat;
     xiv::exd::Exd m_DeliveryQuestDat;
     xiv::exd::Exd m_DisposalShopDat;
     xiv::exd::Exd m_DisposalShopFilterTypeDat;
     xiv::exd::Exd m_DisposalShopItemDat;
     xiv::exd::Exd m_DpsChallengeDat;
     xiv::exd::Exd m_DpsChallengeOfficerDat;
     xiv::exd::Exd m_DpsChallengeTransientDat;
     xiv::exd::Exd m_EmoteDat;
     xiv::exd::Exd m_EmoteCategoryDat;
     xiv::exd::Exd m_ENpcBaseDat;
     xiv::exd::Exd m_ENpcResidentDat;
     xiv::exd::Exd m_EObjDat;
     xiv::exd::Exd m_EObjNameDat;
     xiv::exd::Exd m_EquipRaceCategoryDat;
     xiv::exd::Exd m_EquipSlotCategoryDat;
     xiv::exd::Exd m_EurekaAethernetDat;
     xiv::exd::Exd m_EurekaGrowDataDat;
     xiv::exd::Exd m_EurekaSphereElementAdjustDat;
     xiv::exd::Exd m_EventActionDat;
     xiv::exd::Exd m_EventIconPriorityDat;
     xiv::exd::Exd m_EventIconTypeDat;
     xiv::exd::Exd m_EventItemDat;
     xiv::exd::Exd m_EventItemHelpDat;
     xiv::exd::Exd m_ExVersionDat;
     xiv::exd::Exd m_FateDat;
     xiv::exd::Exd m_FCActivityDat;
     xiv::exd::Exd m_FCActivityCategoryDat;
     xiv::exd::Exd m_FCAuthorityDat;
     xiv::exd::Exd m_FCAuthorityCategoryDat;
     xiv::exd::Exd m_FCChestNameDat;
     xiv::exd::Exd m_FccShopDat;
     xiv::exd::Exd m_FCHierarchyDat;
     xiv::exd::Exd m_FCProfileDat;
     xiv::exd::Exd m_FCReputationDat;
     xiv::exd::Exd m_FCRightsDat;
     xiv::exd::Exd m_FieldMarkerDat;
     xiv::exd::Exd m_FishingSpotDat;
     xiv::exd::Exd m_FishParameterDat;
     xiv::exd::Exd m_GardeningSeedDat;
     xiv::exd::Exd m_GatheringConditionDat;
     xiv::exd::Exd m_GatheringExpDat;
     xiv::exd::Exd m_GatheringItemDat;
     xiv::exd::Exd m_GatheringItemLevelConvertTableDat;
     xiv::exd::Exd m_GatheringItemPointDat;
     xiv::exd::Exd m_GatheringNotebookListDat;
     xiv::exd::Exd m_GatheringPointDat;
     xiv::exd::Exd m_GatheringPointBaseDat;
     xiv::exd::Exd m_GatheringPointBonusDat;
     xiv::exd::Exd m_GatheringPointBonusTypeDat;
     xiv::exd::Exd m_GatheringPointNameDat;
     xiv::exd::Exd m_GatheringSubCategoryDat;
     xiv::exd::Exd m_GatheringTypeDat;
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
     xiv::exd::Exd m_GilShopDat;
     xiv::exd::Exd m_GilShopItemDat;
     xiv::exd::Exd m_GoldSaucerTextDataDat;
     xiv::exd::Exd m_GrandCompanyDat;
     xiv::exd::Exd m_GrandCompanyRankDat;
     xiv::exd::Exd m_GuardianDeityDat;
     xiv::exd::Exd m_GuildleveAssignmentDat;
     xiv::exd::Exd m_GuildOrderGuideDat;
     xiv::exd::Exd m_GuildOrderOfficerDat;
     xiv::exd::Exd m_HouseRetainerPoseDat;
     xiv::exd::Exd m_HousingFurnitureDat;
     xiv::exd::Exd m_HousingYardObjectDat;
     xiv::exd::Exd m_InstanceContentDat;
     xiv::exd::Exd m_InstanceContentBuffDat;
     xiv::exd::Exd m_InstanceContentTextDataDat;
     xiv::exd::Exd m_ItemDat;
     xiv::exd::Exd m_ItemActionDat;
     xiv::exd::Exd m_ItemFoodDat;
     xiv::exd::Exd m_ItemSearchCategoryDat;
     xiv::exd::Exd m_ItemSeriesDat;
     xiv::exd::Exd m_ItemSpecialBonusDat;
     xiv::exd::Exd m_ItemUICategoryDat;
     xiv::exd::Exd m_JournalCategoryDat;
     xiv::exd::Exd m_JournalGenreDat;
     xiv::exd::Exd m_JournalSectionDat;
     xiv::exd::Exd m_LeveDat;
     xiv::exd::Exd m_LeveAssignmentTypeDat;
     xiv::exd::Exd m_LeveClientDat;
     xiv::exd::Exd m_LevelDat;
     xiv::exd::Exd m_LeveRewardItemDat;
     xiv::exd::Exd m_LeveRewardItemGroupDat;
     xiv::exd::Exd m_LeveVfxDat;
     xiv::exd::Exd m_LogFilterDat;
     xiv::exd::Exd m_LogKindDat;
     xiv::exd::Exd m_LogKindCategoryTextDat;
     xiv::exd::Exd m_LogMessageDat;
     xiv::exd::Exd m_MacroIconDat;
     xiv::exd::Exd m_MacroIconRedirectOldDat;
     xiv::exd::Exd m_MainCommandDat;
     xiv::exd::Exd m_MainCommandCategoryDat;
     xiv::exd::Exd m_MapDat;
     xiv::exd::Exd m_MapMarkerDat;
     xiv::exd::Exd m_MapMarkerRegionDat;
     xiv::exd::Exd m_MapSymbolDat;
     xiv::exd::Exd m_MarkerDat;
     xiv::exd::Exd m_MasterpieceSupplyDutyDat;
     xiv::exd::Exd m_MasterpieceSupplyMultiplierDat;
     xiv::exd::Exd m_MateriaDat;
     xiv::exd::Exd m_MinionRaceDat;
     xiv::exd::Exd m_MinionRulesDat;
     xiv::exd::Exd m_MinionSkillTypeDat;
     xiv::exd::Exd m_MobHuntTargetDat;
     xiv::exd::Exd m_ModelCharaDat;
     xiv::exd::Exd m_MonsterNoteDat;
     xiv::exd::Exd m_MonsterNoteTargetDat;
     xiv::exd::Exd m_MountDat;
     xiv::exd::Exd m_MountActionDat;
     xiv::exd::Exd m_MoveTimelineDat;
     xiv::exd::Exd m_MoveVfxDat;
     xiv::exd::Exd m_NpcEquipDat;
     xiv::exd::Exd m_OmenDat;
     xiv::exd::Exd m_OnlineStatusDat;
     xiv::exd::Exd m_OpeningDat;
     xiv::exd::Exd m_OrchestrionDat;
     xiv::exd::Exd m_OrchestrionCategoryDat;
     xiv::exd::Exd m_OrchestrionPathDat;
     xiv::exd::Exd m_OrchestrionUiparamDat;
     xiv::exd::Exd m_ParamGrowDat;
     xiv::exd::Exd m_PerformDat;
     xiv::exd::Exd m_PerformTransientDat;
     xiv::exd::Exd m_PetDat;
     xiv::exd::Exd m_PetActionDat;
     xiv::exd::Exd m_PictureDat;
     xiv::exd::Exd m_PlaceNameDat;
     xiv::exd::Exd m_PublicContentDat;
     xiv::exd::Exd m_PvPActionSortDat;
     xiv::exd::Exd m_QuestDat;
     xiv::exd::Exd m_QuestClassJobRewardDat;
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
     xiv::exd::Exd m_RecipeDat;
     xiv::exd::Exd m_RecipeElementDat;
     xiv::exd::Exd m_RecipeLevelTableDat;
     xiv::exd::Exd m_RecipeNotebookListDat;
     xiv::exd::Exd m_RecommendContentsDat;
     xiv::exd::Exd m_RelicDat;
     xiv::exd::Exd m_Relic3Dat;
     xiv::exd::Exd m_RelicItemDat;
     xiv::exd::Exd m_RelicNoteDat;
     xiv::exd::Exd m_RelicNoteCategoryDat;
     xiv::exd::Exd m_RetainerTaskDat;
     xiv::exd::Exd m_RetainerTaskLvRangeDat;
     xiv::exd::Exd m_RetainerTaskNormalDat;
     xiv::exd::Exd m_RetainerTaskParameterDat;
     xiv::exd::Exd m_RetainerTaskRandomDat;
     xiv::exd::Exd m_SalvageDat;
     xiv::exd::Exd m_SatisfactionNpcDat;
     xiv::exd::Exd m_SatisfactionSupplyDat;
     xiv::exd::Exd m_SatisfactionSupplyRewardDat;
     xiv::exd::Exd m_ScenarioTreeDat;
     xiv::exd::Exd m_ScenarioTreeTipsDat;
     xiv::exd::Exd m_ScenarioTreeTipsClassQuestDat;
     xiv::exd::Exd m_ScenarioTreeTipsQuestDat;
     xiv::exd::Exd m_ScenarioTypeDat;
     xiv::exd::Exd m_ScreenImageDat;
     xiv::exd::Exd m_SecretRecipeBookDat;
     xiv::exd::Exd m_SkyIsland2MissionDat;
     xiv::exd::Exd m_SkyIsland2MissionDetailDat;
     xiv::exd::Exd m_SkyIsland2MissionTypeDat;
     xiv::exd::Exd m_SkyIsland2RangeTypeDat;
     xiv::exd::Exd m_SpearfishingItemDat;
     xiv::exd::Exd m_SpearfishingNotebookDat;
     xiv::exd::Exd m_SpecialShopDat;
     xiv::exd::Exd m_SpecialShopItemCategoryDat;
     xiv::exd::Exd m_StainDat;
     xiv::exd::Exd m_StainTransientDat;
     xiv::exd::Exd m_StatusDat;
     xiv::exd::Exd m_StatusHitEffectDat;
     xiv::exd::Exd m_StatusLoopVFXDat;
     xiv::exd::Exd m_StoryDat;
     xiv::exd::Exd m_SubmarineExplorationDat;
     xiv::exd::Exd m_SubmarinePartDat;
     xiv::exd::Exd m_SubmarineRankDat;
     xiv::exd::Exd m_SwitchTalkDat;
     xiv::exd::Exd m_TerritoryTypeDat;
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
     xiv::exd::Exd m_VaseFlowerDat;
     xiv::exd::Exd m_VFXDat;
     xiv::exd::Exd m_WarpDat;
     xiv::exd::Exd m_WarpConditionDat;
     xiv::exd::Exd m_WeatherDat;
     xiv::exd::Exd m_WeatherGroupDat;
     xiv::exd::Exd m_WeatherRateDat;
     xiv::exd::Exd m_WeddingBGMDat;
     xiv::exd::Exd m_WeeklyBingoOrderDataDat;
     xiv::exd::Exd m_WeeklyBingoRewardDataDat;
     xiv::exd::Exd m_WeeklyBingoTextDat;
     xiv::exd::Exd m_WorldDat;
     xiv::exd::Exd m_WorldDCGroupTypeDat;
     xiv::exd::Exd m_YKWDat;
     xiv::exd::Exd m_ZoneSharedGroupDat;


     using AchievementPtr =  boost::shared_ptr< Achievement >;
     using AchievementCategoryPtr =  boost::shared_ptr< AchievementCategory >;
     using AchievementKindPtr =  boost::shared_ptr< AchievementKind >;
     using ActionPtr =  boost::shared_ptr< Action >;
     using ActionCastTimelinePtr =  boost::shared_ptr< ActionCastTimeline >;
     using ActionCastVFXPtr =  boost::shared_ptr< ActionCastVFX >;
     using ActionCategoryPtr =  boost::shared_ptr< ActionCategory >;
     using ActionComboRoutePtr =  boost::shared_ptr< ActionComboRoute >;
     using ActionIndirectionPtr =  boost::shared_ptr< ActionIndirection >;
     using ActionParamPtr =  boost::shared_ptr< ActionParam >;
     using ActionProcStatusPtr =  boost::shared_ptr< ActionProcStatus >;
     using ActionTimelinePtr =  boost::shared_ptr< ActionTimeline >;
     using ActionTimelineReplacePtr =  boost::shared_ptr< ActionTimelineReplace >;
     using ActionTransientPtr =  boost::shared_ptr< ActionTransient >;
     using AddonPtr =  boost::shared_ptr< Addon >;
     using AdventurePtr =  boost::shared_ptr< Adventure >;
     using AdventureExPhasePtr =  boost::shared_ptr< AdventureExPhase >;
     using AetherCurrentPtr =  boost::shared_ptr< AetherCurrent >;
     using AetherCurrentCompFlgSetPtr =  boost::shared_ptr< AetherCurrentCompFlgSet >;
     using AetherialWheelPtr =  boost::shared_ptr< AetherialWheel >;
     using AetherytePtr =  boost::shared_ptr< Aetheryte >;
     using AirshipExplorationLevelPtr =  boost::shared_ptr< AirshipExplorationLevel >;
     using AirshipExplorationLogPtr =  boost::shared_ptr< AirshipExplorationLog >;
     using AirshipExplorationParamTypePtr =  boost::shared_ptr< AirshipExplorationParamType >;
     using AirshipExplorationPartPtr =  boost::shared_ptr< AirshipExplorationPart >;
     using AirshipExplorationPointPtr =  boost::shared_ptr< AirshipExplorationPoint >;
     using AnimaWeapon5Ptr =  boost::shared_ptr< AnimaWeapon5 >;
     using AnimaWeapon5ParamPtr =  boost::shared_ptr< AnimaWeapon5Param >;
     using AnimaWeapon5PatternGroupPtr =  boost::shared_ptr< AnimaWeapon5PatternGroup >;
     using AnimaWeapon5SpiritTalkPtr =  boost::shared_ptr< AnimaWeapon5SpiritTalk >;
     using AnimaWeapon5SpiritTalkParamPtr =  boost::shared_ptr< AnimaWeapon5SpiritTalkParam >;
     using AnimaWeapon5TradeItemPtr =  boost::shared_ptr< AnimaWeapon5TradeItem >;
     using AnimaWeaponFUITalkPtr =  boost::shared_ptr< AnimaWeaponFUITalk >;
     using AnimaWeaponFUITalkParamPtr =  boost::shared_ptr< AnimaWeaponFUITalkParam >;
     using AnimaWeaponIconPtr =  boost::shared_ptr< AnimaWeaponIcon >;
     using AnimaWeaponItemPtr =  boost::shared_ptr< AnimaWeaponItem >;
     using AquariumFishPtr =  boost::shared_ptr< AquariumFish >;
     using AquariumWaterPtr =  boost::shared_ptr< AquariumWater >;
     using AttackTypePtr =  boost::shared_ptr< AttackType >;
     using BalloonPtr =  boost::shared_ptr< Balloon >;
     using BaseParamPtr =  boost::shared_ptr< BaseParam >;
     using BattleLevePtr =  boost::shared_ptr< BattleLeve >;
     using BeastRankBonusPtr =  boost::shared_ptr< BeastRankBonus >;
     using BeastReputationRankPtr =  boost::shared_ptr< BeastReputationRank >;
     using BeastTribePtr =  boost::shared_ptr< BeastTribe >;
     using BehaviorPtr =  boost::shared_ptr< Behavior >;
     using BGMPtr =  boost::shared_ptr< BGM >;
     using BNpcAnnounceIconPtr =  boost::shared_ptr< BNpcAnnounceIcon >;
     using BNpcBasePtr =  boost::shared_ptr< BNpcBase >;
     using BNpcCustomizePtr =  boost::shared_ptr< BNpcCustomize >;
     using BNpcNamePtr =  boost::shared_ptr< BNpcName >;
     using BuddyPtr =  boost::shared_ptr< Buddy >;
     using BuddyActionPtr =  boost::shared_ptr< BuddyAction >;
     using BuddyEquipPtr =  boost::shared_ptr< BuddyEquip >;
     using BuddyItemPtr =  boost::shared_ptr< BuddyItem >;
     using BuddyRankPtr =  boost::shared_ptr< BuddyRank >;
     using BuddySkillPtr =  boost::shared_ptr< BuddySkill >;
     using CabinetPtr =  boost::shared_ptr< Cabinet >;
     using CabinetCategoryPtr =  boost::shared_ptr< CabinetCategory >;
     using CalendarPtr =  boost::shared_ptr< Calendar >;
     using CharaMakeCustomizePtr =  boost::shared_ptr< CharaMakeCustomize >;
     using CharaMakeTypePtr =  boost::shared_ptr< CharaMakeType >;
     using ChocoboRacePtr =  boost::shared_ptr< ChocoboRace >;
     using ChocoboRaceAbilityPtr =  boost::shared_ptr< ChocoboRaceAbility >;
     using ChocoboRaceAbilityTypePtr =  boost::shared_ptr< ChocoboRaceAbilityType >;
     using ChocoboRaceItemPtr =  boost::shared_ptr< ChocoboRaceItem >;
     using ChocoboRaceRankPtr =  boost::shared_ptr< ChocoboRaceRank >;
     using ChocoboRaceStatusPtr =  boost::shared_ptr< ChocoboRaceStatus >;
     using ChocoboRaceTerritoryPtr =  boost::shared_ptr< ChocoboRaceTerritory >;
     using ChocoboTaxiPtr =  boost::shared_ptr< ChocoboTaxi >;
     using ChocoboTaxiStandPtr =  boost::shared_ptr< ChocoboTaxiStand >;
     using ClassJobPtr =  boost::shared_ptr< ClassJob >;
     using ClassJobCategoryPtr =  boost::shared_ptr< ClassJobCategory >;
     using CompanionPtr =  boost::shared_ptr< Companion >;
     using CompanionMovePtr =  boost::shared_ptr< CompanionMove >;
     using CompanionTransientPtr =  boost::shared_ptr< CompanionTransient >;
     using CompanyActionPtr =  boost::shared_ptr< CompanyAction >;
     using CompanyCraftDraftPtr =  boost::shared_ptr< CompanyCraftDraft >;
     using CompanyCraftDraftCategoryPtr =  boost::shared_ptr< CompanyCraftDraftCategory >;
     using CompanyCraftManufactoryStatePtr =  boost::shared_ptr< CompanyCraftManufactoryState >;
     using CompanyCraftPartPtr =  boost::shared_ptr< CompanyCraftPart >;
     using CompanyCraftProcessPtr =  boost::shared_ptr< CompanyCraftProcess >;
     using CompanyCraftSequencePtr =  boost::shared_ptr< CompanyCraftSequence >;
     using CompanyCraftSupplyItemPtr =  boost::shared_ptr< CompanyCraftSupplyItem >;
     using CompanyCraftTypePtr =  boost::shared_ptr< CompanyCraftType >;
     using CompleteJournalPtr =  boost::shared_ptr< CompleteJournal >;
     using CompleteJournalCategoryPtr =  boost::shared_ptr< CompleteJournalCategory >;
     using ContentExActionPtr =  boost::shared_ptr< ContentExAction >;
     using ContentFinderConditionPtr =  boost::shared_ptr< ContentFinderCondition >;
     using ContentFinderConditionTransientPtr =  boost::shared_ptr< ContentFinderConditionTransient >;
     using ContentMemberTypePtr =  boost::shared_ptr< ContentMemberType >;
     using ContentNpcTalkPtr =  boost::shared_ptr< ContentNpcTalk >;
     using ContentRoulettePtr =  boost::shared_ptr< ContentRoulette >;
     using ContentsNotePtr =  boost::shared_ptr< ContentsNote >;
     using ContentsNoteCategoryPtr =  boost::shared_ptr< ContentsNoteCategory >;
     using ContentTalkPtr =  boost::shared_ptr< ContentTalk >;
     using ContentTalkParamPtr =  boost::shared_ptr< ContentTalkParam >;
     using ContentTypePtr =  boost::shared_ptr< ContentType >;
     using CraftActionPtr =  boost::shared_ptr< CraftAction >;
     using CraftLevePtr =  boost::shared_ptr< CraftLeve >;
     using CraftTypePtr =  boost::shared_ptr< CraftType >;
     using CurrencyPtr =  boost::shared_ptr< Currency >;
     using CustomTalkPtr =  boost::shared_ptr< CustomTalk >;
     using CutscenePtr =  boost::shared_ptr< Cutscene >;
     using CutScreenImagePtr =  boost::shared_ptr< CutScreenImage >;
     using DailySupplyItemPtr =  boost::shared_ptr< DailySupplyItem >;
     using DeepDungeonBanPtr =  boost::shared_ptr< DeepDungeonBan >;
     using DeepDungeonDangerPtr =  boost::shared_ptr< DeepDungeonDanger >;
     using DeepDungeonEquipmentPtr =  boost::shared_ptr< DeepDungeonEquipment >;
     using DeepDungeonFloorEffectUIPtr =  boost::shared_ptr< DeepDungeonFloorEffectUI >;
     using DeepDungeonItemPtr =  boost::shared_ptr< DeepDungeonItem >;
     using DeepDungeonStatusPtr =  boost::shared_ptr< DeepDungeonStatus >;
     using DefaultTalkPtr =  boost::shared_ptr< DefaultTalk >;
     using DeliveryQuestPtr =  boost::shared_ptr< DeliveryQuest >;
     using DisposalShopPtr =  boost::shared_ptr< DisposalShop >;
     using DisposalShopFilterTypePtr =  boost::shared_ptr< DisposalShopFilterType >;
     using DisposalShopItemPtr =  boost::shared_ptr< DisposalShopItem >;
     using DpsChallengePtr =  boost::shared_ptr< DpsChallenge >;
     using DpsChallengeOfficerPtr =  boost::shared_ptr< DpsChallengeOfficer >;
     using DpsChallengeTransientPtr =  boost::shared_ptr< DpsChallengeTransient >;
     using EmotePtr =  boost::shared_ptr< Emote >;
     using EmoteCategoryPtr =  boost::shared_ptr< EmoteCategory >;
     using ENpcBasePtr =  boost::shared_ptr< ENpcBase >;
     using ENpcResidentPtr =  boost::shared_ptr< ENpcResident >;
     using EObjPtr =  boost::shared_ptr< EObj >;
     using EObjNamePtr =  boost::shared_ptr< EObjName >;
     using EquipRaceCategoryPtr =  boost::shared_ptr< EquipRaceCategory >;
     using EquipSlotCategoryPtr =  boost::shared_ptr< EquipSlotCategory >;
     using EurekaAethernetPtr =  boost::shared_ptr< EurekaAethernet >;
     using EurekaGrowDataPtr =  boost::shared_ptr< EurekaGrowData >;
     using EurekaSphereElementAdjustPtr =  boost::shared_ptr< EurekaSphereElementAdjust >;
     using EventActionPtr =  boost::shared_ptr< EventAction >;
     using EventIconPriorityPtr =  boost::shared_ptr< EventIconPriority >;
     using EventIconTypePtr =  boost::shared_ptr< EventIconType >;
     using EventItemPtr =  boost::shared_ptr< EventItem >;
     using EventItemHelpPtr =  boost::shared_ptr< EventItemHelp >;
     using ExVersionPtr =  boost::shared_ptr< ExVersion >;
     using FatePtr =  boost::shared_ptr< Fate >;
     using FCActivityPtr =  boost::shared_ptr< FCActivity >;
     using FCActivityCategoryPtr =  boost::shared_ptr< FCActivityCategory >;
     using FCAuthorityPtr =  boost::shared_ptr< FCAuthority >;
     using FCAuthorityCategoryPtr =  boost::shared_ptr< FCAuthorityCategory >;
     using FCChestNamePtr =  boost::shared_ptr< FCChestName >;
     using FccShopPtr =  boost::shared_ptr< FccShop >;
     using FCHierarchyPtr =  boost::shared_ptr< FCHierarchy >;
     using FCProfilePtr =  boost::shared_ptr< FCProfile >;
     using FCReputationPtr =  boost::shared_ptr< FCReputation >;
     using FCRightsPtr =  boost::shared_ptr< FCRights >;
     using FieldMarkerPtr =  boost::shared_ptr< FieldMarker >;
     using FishingSpotPtr =  boost::shared_ptr< FishingSpot >;
     using FishParameterPtr =  boost::shared_ptr< FishParameter >;
     using GardeningSeedPtr =  boost::shared_ptr< GardeningSeed >;
     using GatheringConditionPtr =  boost::shared_ptr< GatheringCondition >;
     using GatheringExpPtr =  boost::shared_ptr< GatheringExp >;
     using GatheringItemPtr =  boost::shared_ptr< GatheringItem >;
     using GatheringItemLevelConvertTablePtr =  boost::shared_ptr< GatheringItemLevelConvertTable >;
     using GatheringItemPointPtr =  boost::shared_ptr< GatheringItemPoint >;
     using GatheringNotebookListPtr =  boost::shared_ptr< GatheringNotebookList >;
     using GatheringPointPtr =  boost::shared_ptr< GatheringPoint >;
     using GatheringPointBasePtr =  boost::shared_ptr< GatheringPointBase >;
     using GatheringPointBonusPtr =  boost::shared_ptr< GatheringPointBonus >;
     using GatheringPointBonusTypePtr =  boost::shared_ptr< GatheringPointBonusType >;
     using GatheringPointNamePtr =  boost::shared_ptr< GatheringPointName >;
     using GatheringSubCategoryPtr =  boost::shared_ptr< GatheringSubCategory >;
     using GatheringTypePtr =  boost::shared_ptr< GatheringType >;
     using GcArmyExpeditionPtr =  boost::shared_ptr< GcArmyExpedition >;
     using GcArmyExpeditionMemberBonusPtr =  boost::shared_ptr< GcArmyExpeditionMemberBonus >;
     using GcArmyExpeditionTypePtr =  boost::shared_ptr< GcArmyExpeditionType >;
     using GcArmyMemberGrowPtr =  boost::shared_ptr< GcArmyMemberGrow >;
     using GcArmyTrainingPtr =  boost::shared_ptr< GcArmyTraining >;
     using GCRankGridaniaFemaleTextPtr =  boost::shared_ptr< GCRankGridaniaFemaleText >;
     using GCRankGridaniaMaleTextPtr =  boost::shared_ptr< GCRankGridaniaMaleText >;
     using GCRankLimsaFemaleTextPtr =  boost::shared_ptr< GCRankLimsaFemaleText >;
     using GCRankLimsaMaleTextPtr =  boost::shared_ptr< GCRankLimsaMaleText >;
     using GCRankUldahFemaleTextPtr =  boost::shared_ptr< GCRankUldahFemaleText >;
     using GCRankUldahMaleTextPtr =  boost::shared_ptr< GCRankUldahMaleText >;
     using GCScripShopCategoryPtr =  boost::shared_ptr< GCScripShopCategory >;
     using GCScripShopItemPtr =  boost::shared_ptr< GCScripShopItem >;
     using GCShopPtr =  boost::shared_ptr< GCShop >;
     using GCShopItemCategoryPtr =  boost::shared_ptr< GCShopItemCategory >;
     using GCSupplyDutyPtr =  boost::shared_ptr< GCSupplyDuty >;
     using GCSupplyDutyRewardPtr =  boost::shared_ptr< GCSupplyDutyReward >;
     using GeneralActionPtr =  boost::shared_ptr< GeneralAction >;
     using GilShopPtr =  boost::shared_ptr< GilShop >;
     using GilShopItemPtr =  boost::shared_ptr< GilShopItem >;
     using GoldSaucerTextDataPtr =  boost::shared_ptr< GoldSaucerTextData >;
     using GrandCompanyPtr =  boost::shared_ptr< GrandCompany >;
     using GrandCompanyRankPtr =  boost::shared_ptr< GrandCompanyRank >;
     using GuardianDeityPtr =  boost::shared_ptr< GuardianDeity >;
     using GuildleveAssignmentPtr =  boost::shared_ptr< GuildleveAssignment >;
     using GuildOrderGuidePtr =  boost::shared_ptr< GuildOrderGuide >;
     using GuildOrderOfficerPtr =  boost::shared_ptr< GuildOrderOfficer >;
     using HouseRetainerPosePtr =  boost::shared_ptr< HouseRetainerPose >;
     using HousingFurniturePtr =  boost::shared_ptr< HousingFurniture >;
     using HousingYardObjectPtr =  boost::shared_ptr< HousingYardObject >;
     using InstanceContentPtr =  boost::shared_ptr< InstanceContent >;
     using InstanceContentBuffPtr =  boost::shared_ptr< InstanceContentBuff >;
     using InstanceContentTextDataPtr =  boost::shared_ptr< InstanceContentTextData >;
     using ItemPtr =  boost::shared_ptr< Item >;
     using ItemActionPtr =  boost::shared_ptr< ItemAction >;
     using ItemFoodPtr =  boost::shared_ptr< ItemFood >;
     using ItemSearchCategoryPtr =  boost::shared_ptr< ItemSearchCategory >;
     using ItemSeriesPtr =  boost::shared_ptr< ItemSeries >;
     using ItemSpecialBonusPtr =  boost::shared_ptr< ItemSpecialBonus >;
     using ItemUICategoryPtr =  boost::shared_ptr< ItemUICategory >;
     using JournalCategoryPtr =  boost::shared_ptr< JournalCategory >;
     using JournalGenrePtr =  boost::shared_ptr< JournalGenre >;
     using JournalSectionPtr =  boost::shared_ptr< JournalSection >;
     using LevePtr =  boost::shared_ptr< Leve >;
     using LeveAssignmentTypePtr =  boost::shared_ptr< LeveAssignmentType >;
     using LeveClientPtr =  boost::shared_ptr< LeveClient >;
     using LevelPtr =  boost::shared_ptr< Level >;
     using LeveRewardItemPtr =  boost::shared_ptr< LeveRewardItem >;
     using LeveRewardItemGroupPtr =  boost::shared_ptr< LeveRewardItemGroup >;
     using LeveVfxPtr =  boost::shared_ptr< LeveVfx >;
     using LogFilterPtr =  boost::shared_ptr< LogFilter >;
     using LogKindPtr =  boost::shared_ptr< LogKind >;
     using LogKindCategoryTextPtr =  boost::shared_ptr< LogKindCategoryText >;
     using LogMessagePtr =  boost::shared_ptr< LogMessage >;
     using MacroIconPtr =  boost::shared_ptr< MacroIcon >;
     using MacroIconRedirectOldPtr =  boost::shared_ptr< MacroIconRedirectOld >;
     using MainCommandPtr =  boost::shared_ptr< MainCommand >;
     using MainCommandCategoryPtr =  boost::shared_ptr< MainCommandCategory >;
     using MapPtr =  boost::shared_ptr< Map >;
     using MapMarkerPtr =  boost::shared_ptr< MapMarker >;
     using MapMarkerRegionPtr =  boost::shared_ptr< MapMarkerRegion >;
     using MapSymbolPtr =  boost::shared_ptr< MapSymbol >;
     using MarkerPtr =  boost::shared_ptr< Marker >;
     using MasterpieceSupplyDutyPtr =  boost::shared_ptr< MasterpieceSupplyDuty >;
     using MasterpieceSupplyMultiplierPtr =  boost::shared_ptr< MasterpieceSupplyMultiplier >;
     using MateriaPtr =  boost::shared_ptr< Materia >;
     using MinionRacePtr =  boost::shared_ptr< MinionRace >;
     using MinionRulesPtr =  boost::shared_ptr< MinionRules >;
     using MinionSkillTypePtr =  boost::shared_ptr< MinionSkillType >;
     using MobHuntTargetPtr =  boost::shared_ptr< MobHuntTarget >;
     using ModelCharaPtr =  boost::shared_ptr< ModelChara >;
     using MonsterNotePtr =  boost::shared_ptr< MonsterNote >;
     using MonsterNoteTargetPtr =  boost::shared_ptr< MonsterNoteTarget >;
     using MountPtr =  boost::shared_ptr< Mount >;
     using MountActionPtr =  boost::shared_ptr< MountAction >;
     using MoveTimelinePtr =  boost::shared_ptr< MoveTimeline >;
     using MoveVfxPtr =  boost::shared_ptr< MoveVfx >;
     using NpcEquipPtr =  boost::shared_ptr< NpcEquip >;
     using OmenPtr =  boost::shared_ptr< Omen >;
     using OnlineStatusPtr =  boost::shared_ptr< OnlineStatus >;
     using OpeningPtr =  boost::shared_ptr< Opening >;
     using OrchestrionPtr =  boost::shared_ptr< Orchestrion >;
     using OrchestrionCategoryPtr =  boost::shared_ptr< OrchestrionCategory >;
     using OrchestrionPathPtr =  boost::shared_ptr< OrchestrionPath >;
     using OrchestrionUiparamPtr =  boost::shared_ptr< OrchestrionUiparam >;
     using ParamGrowPtr =  boost::shared_ptr< ParamGrow >;
     using PerformPtr =  boost::shared_ptr< Perform >;
     using PerformTransientPtr =  boost::shared_ptr< PerformTransient >;
     using PetPtr =  boost::shared_ptr< Pet >;
     using PetActionPtr =  boost::shared_ptr< PetAction >;
     using PicturePtr =  boost::shared_ptr< Picture >;
     using PlaceNamePtr =  boost::shared_ptr< PlaceName >;
     using PublicContentPtr =  boost::shared_ptr< PublicContent >;
     using PvPActionSortPtr =  boost::shared_ptr< PvPActionSort >;
     using QuestPtr =  boost::shared_ptr< Quest >;
     using QuestClassJobRewardPtr =  boost::shared_ptr< QuestClassJobReward >;
     using QuestRepeatFlagPtr =  boost::shared_ptr< QuestRepeatFlag >;
     using QuestRewardOtherPtr =  boost::shared_ptr< QuestRewardOther >;
     using QuickChatPtr =  boost::shared_ptr< QuickChat >;
     using QuickChatTransientPtr =  boost::shared_ptr< QuickChatTransient >;
     using RacePtr =  boost::shared_ptr< Race >;
     using RacingChocoboItemPtr =  boost::shared_ptr< RacingChocoboItem >;
     using RacingChocoboNamePtr =  boost::shared_ptr< RacingChocoboName >;
     using RacingChocoboNameCategoryPtr =  boost::shared_ptr< RacingChocoboNameCategory >;
     using RacingChocoboNameInfoPtr =  boost::shared_ptr< RacingChocoboNameInfo >;
     using RacingChocoboParamPtr =  boost::shared_ptr< RacingChocoboParam >;
     using RecipePtr =  boost::shared_ptr< Recipe >;
     using RecipeElementPtr =  boost::shared_ptr< RecipeElement >;
     using RecipeLevelTablePtr =  boost::shared_ptr< RecipeLevelTable >;
     using RecipeNotebookListPtr =  boost::shared_ptr< RecipeNotebookList >;
     using RecommendContentsPtr =  boost::shared_ptr< RecommendContents >;
     using RelicPtr =  boost::shared_ptr< Relic >;
     using Relic3Ptr =  boost::shared_ptr< Relic3 >;
     using RelicItemPtr =  boost::shared_ptr< RelicItem >;
     using RelicNotePtr =  boost::shared_ptr< RelicNote >;
     using RelicNoteCategoryPtr =  boost::shared_ptr< RelicNoteCategory >;
     using RetainerTaskPtr =  boost::shared_ptr< RetainerTask >;
     using RetainerTaskLvRangePtr =  boost::shared_ptr< RetainerTaskLvRange >;
     using RetainerTaskNormalPtr =  boost::shared_ptr< RetainerTaskNormal >;
     using RetainerTaskParameterPtr =  boost::shared_ptr< RetainerTaskParameter >;
     using RetainerTaskRandomPtr =  boost::shared_ptr< RetainerTaskRandom >;
     using SalvagePtr =  boost::shared_ptr< Salvage >;
     using SatisfactionNpcPtr =  boost::shared_ptr< SatisfactionNpc >;
     using SatisfactionSupplyPtr =  boost::shared_ptr< SatisfactionSupply >;
     using SatisfactionSupplyRewardPtr =  boost::shared_ptr< SatisfactionSupplyReward >;
     using ScenarioTreePtr =  boost::shared_ptr< ScenarioTree >;
     using ScenarioTreeTipsPtr =  boost::shared_ptr< ScenarioTreeTips >;
     using ScenarioTreeTipsClassQuestPtr =  boost::shared_ptr< ScenarioTreeTipsClassQuest >;
     using ScenarioTreeTipsQuestPtr =  boost::shared_ptr< ScenarioTreeTipsQuest >;
     using ScenarioTypePtr =  boost::shared_ptr< ScenarioType >;
     using ScreenImagePtr =  boost::shared_ptr< ScreenImage >;
     using SecretRecipeBookPtr =  boost::shared_ptr< SecretRecipeBook >;
     using SkyIsland2MissionPtr =  boost::shared_ptr< SkyIsland2Mission >;
     using SkyIsland2MissionDetailPtr =  boost::shared_ptr< SkyIsland2MissionDetail >;
     using SkyIsland2MissionTypePtr =  boost::shared_ptr< SkyIsland2MissionType >;
     using SkyIsland2RangeTypePtr =  boost::shared_ptr< SkyIsland2RangeType >;
     using SpearfishingItemPtr =  boost::shared_ptr< SpearfishingItem >;
     using SpearfishingNotebookPtr =  boost::shared_ptr< SpearfishingNotebook >;
     using SpecialShopPtr =  boost::shared_ptr< SpecialShop >;
     using SpecialShopItemCategoryPtr =  boost::shared_ptr< SpecialShopItemCategory >;
     using StainPtr =  boost::shared_ptr< Stain >;
     using StainTransientPtr =  boost::shared_ptr< StainTransient >;
     using StatusPtr =  boost::shared_ptr< Status >;
     using StatusHitEffectPtr =  boost::shared_ptr< StatusHitEffect >;
     using StatusLoopVFXPtr =  boost::shared_ptr< StatusLoopVFX >;
     using StoryPtr =  boost::shared_ptr< Story >;
     using SubmarineExplorationPtr =  boost::shared_ptr< SubmarineExploration >;
     using SubmarinePartPtr =  boost::shared_ptr< SubmarinePart >;
     using SubmarineRankPtr =  boost::shared_ptr< SubmarineRank >;
     using SwitchTalkPtr =  boost::shared_ptr< SwitchTalk >;
     using TerritoryTypePtr =  boost::shared_ptr< TerritoryType >;
     using TextCommandPtr =  boost::shared_ptr< TextCommand >;
     using TitlePtr =  boost::shared_ptr< Title >;
     using TomestonesPtr =  boost::shared_ptr< Tomestones >;
     using TomestonesItemPtr =  boost::shared_ptr< TomestonesItem >;
     using TopicSelectPtr =  boost::shared_ptr< TopicSelect >;
     using TownPtr =  boost::shared_ptr< Town >;
     using TraitPtr =  boost::shared_ptr< Trait >;
     using TraitRecastPtr =  boost::shared_ptr< TraitRecast >;
     using TraitTransientPtr =  boost::shared_ptr< TraitTransient >;
     using TransformationPtr =  boost::shared_ptr< Transformation >;
     using TreasurePtr =  boost::shared_ptr< Treasure >;
     using TreasureHuntRankPtr =  boost::shared_ptr< TreasureHuntRank >;
     using TribePtr =  boost::shared_ptr< Tribe >;
     using TripleTriadPtr =  boost::shared_ptr< TripleTriad >;
     using TripleTriadCardPtr =  boost::shared_ptr< TripleTriadCard >;
     using TripleTriadCardRarityPtr =  boost::shared_ptr< TripleTriadCardRarity >;
     using TripleTriadCardResidentPtr =  boost::shared_ptr< TripleTriadCardResident >;
     using TripleTriadCardTypePtr =  boost::shared_ptr< TripleTriadCardType >;
     using TripleTriadCompetitionPtr =  boost::shared_ptr< TripleTriadCompetition >;
     using TripleTriadRulePtr =  boost::shared_ptr< TripleTriadRule >;
     using TutorialPtr =  boost::shared_ptr< Tutorial >;
     using TutorialDPSPtr =  boost::shared_ptr< TutorialDPS >;
     using TutorialHealerPtr =  boost::shared_ptr< TutorialHealer >;
     using TutorialTankPtr =  boost::shared_ptr< TutorialTank >;
     using VaseFlowerPtr =  boost::shared_ptr< VaseFlower >;
     using VFXPtr =  boost::shared_ptr< VFX >;
     using WarpPtr =  boost::shared_ptr< Warp >;
     using WarpConditionPtr =  boost::shared_ptr< WarpCondition >;
     using WeatherPtr =  boost::shared_ptr< Weather >;
     using WeatherGroupPtr =  boost::shared_ptr< WeatherGroup >;
     using WeatherRatePtr =  boost::shared_ptr< WeatherRate >;
     using WeddingBGMPtr =  boost::shared_ptr< WeddingBGM >;
     using WeeklyBingoOrderDataPtr =  boost::shared_ptr< WeeklyBingoOrderData >;
     using WeeklyBingoRewardDataPtr =  boost::shared_ptr< WeeklyBingoRewardData >;
     using WeeklyBingoTextPtr =  boost::shared_ptr< WeeklyBingoText >;
     using WorldPtr =  boost::shared_ptr< World >;
     using WorldDCGroupTypePtr =  boost::shared_ptr< WorldDCGroupType >;
     using YKWPtr =  boost::shared_ptr< YKW >;
     using ZoneSharedGroupPtr =  boost::shared_ptr< ZoneSharedGroup >;

     template< class T >
     boost::shared_ptr< T > get( uint32_t id )
     {
        try
        {
           auto info = boost::make_shared< T >( id, this );
           return info;
        }
        catch( ... )
        {
           return nullptr;
        }
        return nullptr;
     }


     std::set< uint32_t > m_AchievementIdList;
     std::set< uint32_t > m_AchievementCategoryIdList;
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
     std::set< uint32_t > m_ActionTimelineReplaceIdList;
     std::set< uint32_t > m_ActionTransientIdList;
     std::set< uint32_t > m_AddonIdList;
     std::set< uint32_t > m_AdventureIdList;
     std::set< uint32_t > m_AdventureExPhaseIdList;
     std::set< uint32_t > m_AetherCurrentIdList;
     std::set< uint32_t > m_AetherCurrentCompFlgSetIdList;
     std::set< uint32_t > m_AetherialWheelIdList;
     std::set< uint32_t > m_AetheryteIdList;
     std::set< uint32_t > m_AirshipExplorationLevelIdList;
     std::set< uint32_t > m_AirshipExplorationLogIdList;
     std::set< uint32_t > m_AirshipExplorationParamTypeIdList;
     std::set< uint32_t > m_AirshipExplorationPartIdList;
     std::set< uint32_t > m_AirshipExplorationPointIdList;
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
     std::set< uint32_t > m_AquariumFishIdList;
     std::set< uint32_t > m_AquariumWaterIdList;
     std::set< uint32_t > m_AttackTypeIdList;
     std::set< uint32_t > m_BalloonIdList;
     std::set< uint32_t > m_BaseParamIdList;
     std::set< uint32_t > m_BattleLeveIdList;
     std::set< uint32_t > m_BeastRankBonusIdList;
     std::set< uint32_t > m_BeastReputationRankIdList;
     std::set< uint32_t > m_BeastTribeIdList;
     std::set< uint32_t > m_BehaviorIdList;
     std::set< uint32_t > m_BGMIdList;
     std::set< uint32_t > m_BNpcAnnounceIconIdList;
     std::set< uint32_t > m_BNpcBaseIdList;
     std::set< uint32_t > m_BNpcCustomizeIdList;
     std::set< uint32_t > m_BNpcNameIdList;
     std::set< uint32_t > m_BuddyIdList;
     std::set< uint32_t > m_BuddyActionIdList;
     std::set< uint32_t > m_BuddyEquipIdList;
     std::set< uint32_t > m_BuddyItemIdList;
     std::set< uint32_t > m_BuddyRankIdList;
     std::set< uint32_t > m_BuddySkillIdList;
     std::set< uint32_t > m_CabinetIdList;
     std::set< uint32_t > m_CabinetCategoryIdList;
     std::set< uint32_t > m_CalendarIdList;
     std::set< uint32_t > m_CharaMakeCustomizeIdList;
     std::set< uint32_t > m_CharaMakeTypeIdList;
     std::set< uint32_t > m_ChocoboRaceIdList;
     std::set< uint32_t > m_ChocoboRaceAbilityIdList;
     std::set< uint32_t > m_ChocoboRaceAbilityTypeIdList;
     std::set< uint32_t > m_ChocoboRaceItemIdList;
     std::set< uint32_t > m_ChocoboRaceRankIdList;
     std::set< uint32_t > m_ChocoboRaceStatusIdList;
     std::set< uint32_t > m_ChocoboRaceTerritoryIdList;
     std::set< uint32_t > m_ChocoboTaxiIdList;
     std::set< uint32_t > m_ChocoboTaxiStandIdList;
     std::set< uint32_t > m_ClassJobIdList;
     std::set< uint32_t > m_ClassJobCategoryIdList;
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
     std::set< uint32_t > m_CompleteJournalIdList;
     std::set< uint32_t > m_CompleteJournalCategoryIdList;
     std::set< uint32_t > m_ContentExActionIdList;
     std::set< uint32_t > m_ContentFinderConditionIdList;
     std::set< uint32_t > m_ContentFinderConditionTransientIdList;
     std::set< uint32_t > m_ContentMemberTypeIdList;
     std::set< uint32_t > m_ContentNpcTalkIdList;
     std::set< uint32_t > m_ContentRouletteIdList;
     std::set< uint32_t > m_ContentsNoteIdList;
     std::set< uint32_t > m_ContentsNoteCategoryIdList;
     std::set< uint32_t > m_ContentTalkIdList;
     std::set< uint32_t > m_ContentTalkParamIdList;
     std::set< uint32_t > m_ContentTypeIdList;
     std::set< uint32_t > m_CraftActionIdList;
     std::set< uint32_t > m_CraftLeveIdList;
     std::set< uint32_t > m_CraftTypeIdList;
     std::set< uint32_t > m_CurrencyIdList;
     std::set< uint32_t > m_CustomTalkIdList;
     std::set< uint32_t > m_CutsceneIdList;
     std::set< uint32_t > m_CutScreenImageIdList;
     std::set< uint32_t > m_DailySupplyItemIdList;
     std::set< uint32_t > m_DeepDungeonBanIdList;
     std::set< uint32_t > m_DeepDungeonDangerIdList;
     std::set< uint32_t > m_DeepDungeonEquipmentIdList;
     std::set< uint32_t > m_DeepDungeonFloorEffectUIIdList;
     std::set< uint32_t > m_DeepDungeonItemIdList;
     std::set< uint32_t > m_DeepDungeonStatusIdList;
     std::set< uint32_t > m_DefaultTalkIdList;
     std::set< uint32_t > m_DeliveryQuestIdList;
     std::set< uint32_t > m_DisposalShopIdList;
     std::set< uint32_t > m_DisposalShopFilterTypeIdList;
     std::set< uint32_t > m_DisposalShopItemIdList;
     std::set< uint32_t > m_DpsChallengeIdList;
     std::set< uint32_t > m_DpsChallengeOfficerIdList;
     std::set< uint32_t > m_DpsChallengeTransientIdList;
     std::set< uint32_t > m_EmoteIdList;
     std::set< uint32_t > m_EmoteCategoryIdList;
     std::set< uint32_t > m_ENpcBaseIdList;
     std::set< uint32_t > m_ENpcResidentIdList;
     std::set< uint32_t > m_EObjIdList;
     std::set< uint32_t > m_EObjNameIdList;
     std::set< uint32_t > m_EquipRaceCategoryIdList;
     std::set< uint32_t > m_EquipSlotCategoryIdList;
     std::set< uint32_t > m_EurekaAethernetIdList;
     std::set< uint32_t > m_EurekaGrowDataIdList;
     std::set< uint32_t > m_EurekaSphereElementAdjustIdList;
     std::set< uint32_t > m_EventActionIdList;
     std::set< uint32_t > m_EventIconPriorityIdList;
     std::set< uint32_t > m_EventIconTypeIdList;
     std::set< uint32_t > m_EventItemIdList;
     std::set< uint32_t > m_EventItemHelpIdList;
     std::set< uint32_t > m_ExVersionIdList;
     std::set< uint32_t > m_FateIdList;
     std::set< uint32_t > m_FCActivityIdList;
     std::set< uint32_t > m_FCActivityCategoryIdList;
     std::set< uint32_t > m_FCAuthorityIdList;
     std::set< uint32_t > m_FCAuthorityCategoryIdList;
     std::set< uint32_t > m_FCChestNameIdList;
     std::set< uint32_t > m_FccShopIdList;
     std::set< uint32_t > m_FCHierarchyIdList;
     std::set< uint32_t > m_FCProfileIdList;
     std::set< uint32_t > m_FCReputationIdList;
     std::set< uint32_t > m_FCRightsIdList;
     std::set< uint32_t > m_FieldMarkerIdList;
     std::set< uint32_t > m_FishingSpotIdList;
     std::set< uint32_t > m_FishParameterIdList;
     std::set< uint32_t > m_GardeningSeedIdList;
     std::set< uint32_t > m_GatheringConditionIdList;
     std::set< uint32_t > m_GatheringExpIdList;
     std::set< uint32_t > m_GatheringItemIdList;
     std::set< uint32_t > m_GatheringItemLevelConvertTableIdList;
     std::set< uint32_t > m_GatheringItemPointIdList;
     std::set< uint32_t > m_GatheringNotebookListIdList;
     std::set< uint32_t > m_GatheringPointIdList;
     std::set< uint32_t > m_GatheringPointBaseIdList;
     std::set< uint32_t > m_GatheringPointBonusIdList;
     std::set< uint32_t > m_GatheringPointBonusTypeIdList;
     std::set< uint32_t > m_GatheringPointNameIdList;
     std::set< uint32_t > m_GatheringSubCategoryIdList;
     std::set< uint32_t > m_GatheringTypeIdList;
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
     std::set< uint32_t > m_GilShopIdList;
     std::set< uint32_t > m_GilShopItemIdList;
     std::set< uint32_t > m_GoldSaucerTextDataIdList;
     std::set< uint32_t > m_GrandCompanyIdList;
     std::set< uint32_t > m_GrandCompanyRankIdList;
     std::set< uint32_t > m_GuardianDeityIdList;
     std::set< uint32_t > m_GuildleveAssignmentIdList;
     std::set< uint32_t > m_GuildOrderGuideIdList;
     std::set< uint32_t > m_GuildOrderOfficerIdList;
     std::set< uint32_t > m_HouseRetainerPoseIdList;
     std::set< uint32_t > m_HousingFurnitureIdList;
     std::set< uint32_t > m_HousingYardObjectIdList;
     std::set< uint32_t > m_InstanceContentIdList;
     std::set< uint32_t > m_InstanceContentBuffIdList;
     std::set< uint32_t > m_InstanceContentTextDataIdList;
     std::set< uint32_t > m_ItemIdList;
     std::set< uint32_t > m_ItemActionIdList;
     std::set< uint32_t > m_ItemFoodIdList;
     std::set< uint32_t > m_ItemSearchCategoryIdList;
     std::set< uint32_t > m_ItemSeriesIdList;
     std::set< uint32_t > m_ItemSpecialBonusIdList;
     std::set< uint32_t > m_ItemUICategoryIdList;
     std::set< uint32_t > m_JournalCategoryIdList;
     std::set< uint32_t > m_JournalGenreIdList;
     std::set< uint32_t > m_JournalSectionIdList;
     std::set< uint32_t > m_LeveIdList;
     std::set< uint32_t > m_LeveAssignmentTypeIdList;
     std::set< uint32_t > m_LeveClientIdList;
     std::set< uint32_t > m_LevelIdList;
     std::set< uint32_t > m_LeveRewardItemIdList;
     std::set< uint32_t > m_LeveRewardItemGroupIdList;
     std::set< uint32_t > m_LeveVfxIdList;
     std::set< uint32_t > m_LogFilterIdList;
     std::set< uint32_t > m_LogKindIdList;
     std::set< uint32_t > m_LogKindCategoryTextIdList;
     std::set< uint32_t > m_LogMessageIdList;
     std::set< uint32_t > m_MacroIconIdList;
     std::set< uint32_t > m_MacroIconRedirectOldIdList;
     std::set< uint32_t > m_MainCommandIdList;
     std::set< uint32_t > m_MainCommandCategoryIdList;
     std::set< uint32_t > m_MapIdList;
     std::set< uint32_t > m_MapMarkerIdList;
     std::set< uint32_t > m_MapMarkerRegionIdList;
     std::set< uint32_t > m_MapSymbolIdList;
     std::set< uint32_t > m_MarkerIdList;
     std::set< uint32_t > m_MasterpieceSupplyDutyIdList;
     std::set< uint32_t > m_MasterpieceSupplyMultiplierIdList;
     std::set< uint32_t > m_MateriaIdList;
     std::set< uint32_t > m_MinionRaceIdList;
     std::set< uint32_t > m_MinionRulesIdList;
     std::set< uint32_t > m_MinionSkillTypeIdList;
     std::set< uint32_t > m_MobHuntTargetIdList;
     std::set< uint32_t > m_ModelCharaIdList;
     std::set< uint32_t > m_MonsterNoteIdList;
     std::set< uint32_t > m_MonsterNoteTargetIdList;
     std::set< uint32_t > m_MountIdList;
     std::set< uint32_t > m_MountActionIdList;
     std::set< uint32_t > m_MoveTimelineIdList;
     std::set< uint32_t > m_MoveVfxIdList;
     std::set< uint32_t > m_NpcEquipIdList;
     std::set< uint32_t > m_OmenIdList;
     std::set< uint32_t > m_OnlineStatusIdList;
     std::set< uint32_t > m_OpeningIdList;
     std::set< uint32_t > m_OrchestrionIdList;
     std::set< uint32_t > m_OrchestrionCategoryIdList;
     std::set< uint32_t > m_OrchestrionPathIdList;
     std::set< uint32_t > m_OrchestrionUiparamIdList;
     std::set< uint32_t > m_ParamGrowIdList;
     std::set< uint32_t > m_PerformIdList;
     std::set< uint32_t > m_PerformTransientIdList;
     std::set< uint32_t > m_PetIdList;
     std::set< uint32_t > m_PetActionIdList;
     std::set< uint32_t > m_PictureIdList;
     std::set< uint32_t > m_PlaceNameIdList;
     std::set< uint32_t > m_PublicContentIdList;
     std::set< uint32_t > m_PvPActionSortIdList;
     std::set< uint32_t > m_QuestIdList;
     std::set< uint32_t > m_QuestClassJobRewardIdList;
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
     std::set< uint32_t > m_RecipeIdList;
     std::set< uint32_t > m_RecipeElementIdList;
     std::set< uint32_t > m_RecipeLevelTableIdList;
     std::set< uint32_t > m_RecipeNotebookListIdList;
     std::set< uint32_t > m_RecommendContentsIdList;
     std::set< uint32_t > m_RelicIdList;
     std::set< uint32_t > m_Relic3IdList;
     std::set< uint32_t > m_RelicItemIdList;
     std::set< uint32_t > m_RelicNoteIdList;
     std::set< uint32_t > m_RelicNoteCategoryIdList;
     std::set< uint32_t > m_RetainerTaskIdList;
     std::set< uint32_t > m_RetainerTaskLvRangeIdList;
     std::set< uint32_t > m_RetainerTaskNormalIdList;
     std::set< uint32_t > m_RetainerTaskParameterIdList;
     std::set< uint32_t > m_RetainerTaskRandomIdList;
     std::set< uint32_t > m_SalvageIdList;
     std::set< uint32_t > m_SatisfactionNpcIdList;
     std::set< uint32_t > m_SatisfactionSupplyIdList;
     std::set< uint32_t > m_SatisfactionSupplyRewardIdList;
     std::set< uint32_t > m_ScenarioTreeIdList;
     std::set< uint32_t > m_ScenarioTreeTipsIdList;
     std::set< uint32_t > m_ScenarioTreeTipsClassQuestIdList;
     std::set< uint32_t > m_ScenarioTreeTipsQuestIdList;
     std::set< uint32_t > m_ScenarioTypeIdList;
     std::set< uint32_t > m_ScreenImageIdList;
     std::set< uint32_t > m_SecretRecipeBookIdList;
     std::set< uint32_t > m_SkyIsland2MissionIdList;
     std::set< uint32_t > m_SkyIsland2MissionDetailIdList;
     std::set< uint32_t > m_SkyIsland2MissionTypeIdList;
     std::set< uint32_t > m_SkyIsland2RangeTypeIdList;
     std::set< uint32_t > m_SpearfishingItemIdList;
     std::set< uint32_t > m_SpearfishingNotebookIdList;
     std::set< uint32_t > m_SpecialShopIdList;
     std::set< uint32_t > m_SpecialShopItemCategoryIdList;
     std::set< uint32_t > m_StainIdList;
     std::set< uint32_t > m_StainTransientIdList;
     std::set< uint32_t > m_StatusIdList;
     std::set< uint32_t > m_StatusHitEffectIdList;
     std::set< uint32_t > m_StatusLoopVFXIdList;
     std::set< uint32_t > m_StoryIdList;
     std::set< uint32_t > m_SubmarineExplorationIdList;
     std::set< uint32_t > m_SubmarinePartIdList;
     std::set< uint32_t > m_SubmarineRankIdList;
     std::set< uint32_t > m_SwitchTalkIdList;
     std::set< uint32_t > m_TerritoryTypeIdList;
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
     std::set< uint32_t > m_VaseFlowerIdList;
     std::set< uint32_t > m_VFXIdList;
     std::set< uint32_t > m_WarpIdList;
     std::set< uint32_t > m_WarpConditionIdList;
     std::set< uint32_t > m_WeatherIdList;
     std::set< uint32_t > m_WeatherGroupIdList;
     std::set< uint32_t > m_WeatherRateIdList;
     std::set< uint32_t > m_WeddingBGMIdList;
     std::set< uint32_t > m_WeeklyBingoOrderDataIdList;
     std::set< uint32_t > m_WeeklyBingoRewardDataIdList;
     std::set< uint32_t > m_WeeklyBingoTextIdList;
     std::set< uint32_t > m_WorldIdList;
     std::set< uint32_t > m_WorldDCGroupTypeIdList;
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
const std::set< uint32_t >& getAttackTypeIdList()
{
   if( m_AttackTypeIdList.size() == 0 )
      loadIdList( m_AttackTypeDat, m_AttackTypeIdList );
   return m_AttackTypeIdList;
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
const std::set< uint32_t >& getBGMIdList()
{
   if( m_BGMIdList.size() == 0 )
      loadIdList( m_BGMDat, m_BGMIdList );
   return m_BGMIdList;
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
const std::set< uint32_t >& getCharaMakeCustomizeIdList()
{
   if( m_CharaMakeCustomizeIdList.size() == 0 )
      loadIdList( m_CharaMakeCustomizeDat, m_CharaMakeCustomizeIdList );
   return m_CharaMakeCustomizeIdList;
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
const std::set< uint32_t >& getContentRouletteIdList()
{
   if( m_ContentRouletteIdList.size() == 0 )
      loadIdList( m_ContentRouletteDat, m_ContentRouletteIdList );
   return m_ContentRouletteIdList;
}
const std::set< uint32_t >& getContentsNoteIdList()
{
   if( m_ContentsNoteIdList.size() == 0 )
      loadIdList( m_ContentsNoteDat, m_ContentsNoteIdList );
   return m_ContentsNoteIdList;
}
const std::set< uint32_t >& getContentsNoteCategoryIdList()
{
   if( m_ContentsNoteCategoryIdList.size() == 0 )
      loadIdList( m_ContentsNoteCategoryDat, m_ContentsNoteCategoryIdList );
   return m_ContentsNoteCategoryIdList;
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
const std::set< uint32_t >& getCraftTypeIdList()
{
   if( m_CraftTypeIdList.size() == 0 )
      loadIdList( m_CraftTypeDat, m_CraftTypeIdList );
   return m_CraftTypeIdList;
}
const std::set< uint32_t >& getCurrencyIdList()
{
   if( m_CurrencyIdList.size() == 0 )
      loadIdList( m_CurrencyDat, m_CurrencyIdList );
   return m_CurrencyIdList;
}
const std::set< uint32_t >& getCustomTalkIdList()
{
   if( m_CustomTalkIdList.size() == 0 )
      loadIdList( m_CustomTalkDat, m_CustomTalkIdList );
   return m_CustomTalkIdList;
}
const std::set< uint32_t >& getCutsceneIdList()
{
   if( m_CutsceneIdList.size() == 0 )
      loadIdList( m_CutsceneDat, m_CutsceneIdList );
   return m_CutsceneIdList;
}
const std::set< uint32_t >& getCutScreenImageIdList()
{
   if( m_CutScreenImageIdList.size() == 0 )
      loadIdList( m_CutScreenImageDat, m_CutScreenImageIdList );
   return m_CutScreenImageIdList;
}
const std::set< uint32_t >& getDailySupplyItemIdList()
{
   if( m_DailySupplyItemIdList.size() == 0 )
      loadIdList( m_DailySupplyItemDat, m_DailySupplyItemIdList );
   return m_DailySupplyItemIdList;
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
const std::set< uint32_t >& getDeliveryQuestIdList()
{
   if( m_DeliveryQuestIdList.size() == 0 )
      loadIdList( m_DeliveryQuestDat, m_DeliveryQuestIdList );
   return m_DeliveryQuestIdList;
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
const std::set< uint32_t >& getENpcBaseIdList()
{
   if( m_ENpcBaseIdList.size() == 0 )
      loadIdList( m_ENpcBaseDat, m_ENpcBaseIdList );
   return m_ENpcBaseIdList;
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
const std::set< uint32_t >& getEventItemHelpIdList()
{
   if( m_EventItemHelpIdList.size() == 0 )
      loadIdList( m_EventItemHelpDat, m_EventItemHelpIdList );
   return m_EventItemHelpIdList;
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
const std::set< uint32_t >& getFieldMarkerIdList()
{
   if( m_FieldMarkerIdList.size() == 0 )
      loadIdList( m_FieldMarkerDat, m_FieldMarkerIdList );
   return m_FieldMarkerIdList;
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
const std::set< uint32_t >& getGuardianDeityIdList()
{
   if( m_GuardianDeityIdList.size() == 0 )
      loadIdList( m_GuardianDeityDat, m_GuardianDeityIdList );
   return m_GuardianDeityIdList;
}
const std::set< uint32_t >& getGuildleveAssignmentIdList()
{
   if( m_GuildleveAssignmentIdList.size() == 0 )
      loadIdList( m_GuildleveAssignmentDat, m_GuildleveAssignmentIdList );
   return m_GuildleveAssignmentIdList;
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
const std::set< uint32_t >& getHouseRetainerPoseIdList()
{
   if( m_HouseRetainerPoseIdList.size() == 0 )
      loadIdList( m_HouseRetainerPoseDat, m_HouseRetainerPoseIdList );
   return m_HouseRetainerPoseIdList;
}
const std::set< uint32_t >& getHousingFurnitureIdList()
{
   if( m_HousingFurnitureIdList.size() == 0 )
      loadIdList( m_HousingFurnitureDat, m_HousingFurnitureIdList );
   return m_HousingFurnitureIdList;
}
const std::set< uint32_t >& getHousingYardObjectIdList()
{
   if( m_HousingYardObjectIdList.size() == 0 )
      loadIdList( m_HousingYardObjectDat, m_HousingYardObjectIdList );
   return m_HousingYardObjectIdList;
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
const std::set< uint32_t >& getItemFoodIdList()
{
   if( m_ItemFoodIdList.size() == 0 )
      loadIdList( m_ItemFoodDat, m_ItemFoodIdList );
   return m_ItemFoodIdList;
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
const std::set< uint32_t >& getLeveVfxIdList()
{
   if( m_LeveVfxIdList.size() == 0 )
      loadIdList( m_LeveVfxDat, m_LeveVfxIdList );
   return m_LeveVfxIdList;
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
const std::set< uint32_t >& getLogKindCategoryTextIdList()
{
   if( m_LogKindCategoryTextIdList.size() == 0 )
      loadIdList( m_LogKindCategoryTextDat, m_LogKindCategoryTextIdList );
   return m_LogKindCategoryTextIdList;
}
const std::set< uint32_t >& getLogMessageIdList()
{
   if( m_LogMessageIdList.size() == 0 )
      loadIdList( m_LogMessageDat, m_LogMessageIdList );
   return m_LogMessageIdList;
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
const std::set< uint32_t >& getNpcEquipIdList()
{
   if( m_NpcEquipIdList.size() == 0 )
      loadIdList( m_NpcEquipDat, m_NpcEquipIdList );
   return m_NpcEquipIdList;
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
const std::set< uint32_t >& getParamGrowIdList()
{
   if( m_ParamGrowIdList.size() == 0 )
      loadIdList( m_ParamGrowDat, m_ParamGrowIdList );
   return m_ParamGrowIdList;
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
const std::set< uint32_t >& getPublicContentIdList()
{
   if( m_PublicContentIdList.size() == 0 )
      loadIdList( m_PublicContentDat, m_PublicContentIdList );
   return m_PublicContentIdList;
}
const std::set< uint32_t >& getPvPActionSortIdList()
{
   if( m_PvPActionSortIdList.size() == 0 )
      loadIdList( m_PvPActionSortDat, m_PvPActionSortIdList );
   return m_PvPActionSortIdList;
}
const std::set< uint32_t >& getQuestIdList()
{
   if( m_QuestIdList.size() == 0 )
      loadIdList( m_QuestDat, m_QuestIdList );
   return m_QuestIdList;
}
const std::set< uint32_t >& getQuestClassJobRewardIdList()
{
   if( m_QuestClassJobRewardIdList.size() == 0 )
      loadIdList( m_QuestClassJobRewardDat, m_QuestClassJobRewardIdList );
   return m_QuestClassJobRewardIdList;
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
const std::set< uint32_t >& getRecipeIdList()
{
   if( m_RecipeIdList.size() == 0 )
      loadIdList( m_RecipeDat, m_RecipeIdList );
   return m_RecipeIdList;
}
const std::set< uint32_t >& getRecipeElementIdList()
{
   if( m_RecipeElementIdList.size() == 0 )
      loadIdList( m_RecipeElementDat, m_RecipeElementIdList );
   return m_RecipeElementIdList;
}
const std::set< uint32_t >& getRecipeLevelTableIdList()
{
   if( m_RecipeLevelTableIdList.size() == 0 )
      loadIdList( m_RecipeLevelTableDat, m_RecipeLevelTableIdList );
   return m_RecipeLevelTableIdList;
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
const std::set< uint32_t >& getSalvageIdList()
{
   if( m_SalvageIdList.size() == 0 )
      loadIdList( m_SalvageDat, m_SalvageIdList );
   return m_SalvageIdList;
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
const std::set< uint32_t >& getScenarioTreeTipsQuestIdList()
{
   if( m_ScenarioTreeTipsQuestIdList.size() == 0 )
      loadIdList( m_ScenarioTreeTipsQuestDat, m_ScenarioTreeTipsQuestIdList );
   return m_ScenarioTreeTipsQuestIdList;
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
const std::set< uint32_t >& getTerritoryTypeIdList()
{
   if( m_TerritoryTypeIdList.size() == 0 )
      loadIdList( m_TerritoryTypeDat, m_TerritoryTypeIdList );
   return m_TerritoryTypeIdList;
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
}

#endif

