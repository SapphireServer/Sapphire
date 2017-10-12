#ifndef _EXDDATA_H
#define _EXDDATA_H

/* This file has been automatically generated.
   Changes will be lost upon regeneration.
   To change the content edit tools/exd_struct_gen */

#include <GameData.h>
#include <File.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

namespace Core {
namespace Data {

class ExdDataGenerated;

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
   int16_t actionTimelineUse;
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

struct ActionCategory
{
   std::string name;

   ActionCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionComboRoute
{
   std::string name;

   ActionComboRoute( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ActionIndirection
{
   int32_t name;

   ActionIndirection( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   BaseParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BattleLeve
{

   BattleLeve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct BeastRankBonus
{
   uint32_t item;

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
   uint8_t beastRankBonus;
   uint32_t iconReputation;
   uint32_t icon;
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

   Calendar( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct ChainBonus
{
   uint8_t bonus;
   uint8_t timeouts;

   ChainBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CharaMakeCustomize
{
   uint32_t icon;
   uint16_t data;

   CharaMakeCustomize( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct CharaMakeType
{
   int32_t race;
   int32_t tribe;
   int8_t gender;

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
   uint16_t modifierHitPoints;
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
   uint8_t contentIndicator;
   uint16_t instanceContent;
   uint8_t contentMemberType;
   uint8_t classJobLevel;
   uint16_t itemLevelRequired;
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

struct ContentRoulette
{
   std::string name;
   std::string description;
   std::string dutyType;
   bool isInDutyFinder;
   bool requireAllDuties;
   uint16_t itemLevelRequired;
   uint32_t icon;
   uint16_t rewardTomeA;
   uint16_t rewardTomeB;
   uint16_t rewardTomeC;
   uint8_t sortKey;
   uint8_t contentMemberType;

   ContentRoulette( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   int8_t singular;
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

struct EventAction
{
   std::string name;
   uint16_t icon;

   EventAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct EventIconPriority
{

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
   uint8_t classJobLevel;
   uint8_t classJobLevelMax;
   uint32_t eventItem;
   uint32_t iconObjective;
   uint32_t iconMap;
   std::string name;
   std::string description;
   std::string objective;

   Fate( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct FCActivity
{
   std::string text;

   FCActivity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   GatheringNotebookList( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPoint
{
   int32_t gatheringPointBase;
   uint16_t territoryType;
   uint16_t placeName;
   uint16_t gatheringSubCategory;

   GatheringPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct GatheringPointBase
{
   int32_t gatheringType;
   uint8_t gatheringLevel;
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

struct GCScripShopItem
{
   int32_t item;
   int32_t requiredRank;
   uint32_t costGCSeals;

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
   uint8_t classJobLevelSync;
   std::string name;
   uint16_t bGM;
   uint16_t itemLevelSync;
   uint32_t territoryType;
   uint32_t icon;
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

struct InstanceContentType
{
   uint8_t sortKey;
   uint8_t contentType;

   InstanceContentType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   int32_t journalCategory;
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
   uint16_t territoryType;

   Map( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MapMarker
{
   int16_t x;
   int16_t y;
   uint16_t icon;
   uint16_t placeNameSubtext;
   uint8_t subtextOrientation;
   uint8_t type;
   uint8_t dataType;
   uint16_t dataKey;

   MapMarker( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MapSymbol
{
   int32_t icon;
   int32_t placeName;

   MapSymbol( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MasterpieceSupplyDuty
{
   uint8_t classJob;
   uint8_t classJobLevel;
   uint16_t rewardCurrency;

   MasterpieceSupplyDuty( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Materia
{
   uint8_t baseParam;

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
   uint16_t icon;

   Mount( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct MountAction
{

   MountAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   std::string name;
   uint32_t icon;

   OnlineStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Orchestrion
{
   std::string name;
   std::string description;

   Orchestrion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct OrchestrionPath
{
   std::string file;

   OrchestrionPath( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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
   uint8_t classJobUnlock;
   uint8_t grandCompany;
   uint8_t grandCompanyRank;
   uint8_t instanceContentJoin;
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
   uint8_t classJobRequired;
   uint16_t expFactor;
   uint32_t gilReward;
   uint16_t gCSeals;
   uint8_t itemRewardType;
   uint8_t emoteReward;
   uint16_t actionReward;
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

struct QuestRewardOther
{
   std::string name;

   QuestRewardOther( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

   RecipeNotebookList( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

struct RetainerTaskNormal
{
   int32_t item;
   uint8_t quantity0;
   uint8_t quantity1;
   uint8_t quantity2;

   RetainerTaskNormal( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct RetainerTaskParameter
{

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

struct Status
{
   std::string name;
   std::string description;
   uint16_t icon;
   uint8_t maxStacks;
   bool lockMovement;
   bool lockActions;
   bool lockControl;
   bool transfiguration;
   bool canDispel;
   bool isPermanent;
   bool inflictedByActor;
   bool isFcBuff;
   bool invisibility;

   Status( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct Story
{

   Story( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
};

struct SwitchTalk
{

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
   uint8_t weatherRate;
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
   bool usesRegionalRules;
   uint16_t fee;
   uint8_t previousQuestJoin;
   uint16_t startTime;
   uint16_t endTime;
   uint32_t defaultTalkChallenge;
   uint32_t defaultTalkUnavailable;
   uint32_t defaultTalkNPCWin;
   uint32_t defaultTalkDraw;
   uint32_t defaultTalkPCWin;

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

struct WorldDCGroupType
{
   std::string name;

   WorldDCGroupType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData );
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

     boost::shared_ptr< xiv::dat::GameData > m_data;
     boost::shared_ptr< xiv::exd::ExdData > m_exd_data;

     xiv::exd::Exd m_AchievementDat;
     xiv::exd::Exd m_AchievementCategoryDat;
     xiv::exd::Exd m_AchievementKindDat;
     xiv::exd::Exd m_ActionDat;
     xiv::exd::Exd m_ActionCategoryDat;
     xiv::exd::Exd m_ActionComboRouteDat;
     xiv::exd::Exd m_ActionIndirectionDat;
     xiv::exd::Exd m_ActionProcStatusDat;
     xiv::exd::Exd m_ActionTimelineDat;
     xiv::exd::Exd m_ActionTransientDat;
     xiv::exd::Exd m_AddonDat;
     xiv::exd::Exd m_AdventureDat;
     xiv::exd::Exd m_AdventureExPhaseDat;
     xiv::exd::Exd m_AetherCurrentDat;
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
     xiv::exd::Exd m_BuddyActionDat;
     xiv::exd::Exd m_BuddyEquipDat;
     xiv::exd::Exd m_BuddyItemDat;
     xiv::exd::Exd m_BuddyRankDat;
     xiv::exd::Exd m_BuddySkillDat;
     xiv::exd::Exd m_CabinetDat;
     xiv::exd::Exd m_CabinetCategoryDat;
     xiv::exd::Exd m_CalendarDat;
     xiv::exd::Exd m_ChainBonusDat;
     xiv::exd::Exd m_CharaMakeCustomizeDat;
     xiv::exd::Exd m_CharaMakeTypeDat;
     xiv::exd::Exd m_ChocoboRaceDat;
     xiv::exd::Exd m_ChocoboRaceAbilityDat;
     xiv::exd::Exd m_ChocoboRaceAbilityTypeDat;
     xiv::exd::Exd m_ChocoboRaceItemDat;
     xiv::exd::Exd m_ChocoboRaceRankDat;
     xiv::exd::Exd m_ChocoboRaceStatusDat;
     xiv::exd::Exd m_ChocoboRaceTerritoryDat;
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
     xiv::exd::Exd m_ContentRouletteDat;
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
     xiv::exd::Exd m_EquipSlotCategoryDat;
     xiv::exd::Exd m_EventActionDat;
     xiv::exd::Exd m_EventIconPriorityDat;
     xiv::exd::Exd m_EventIconTypeDat;
     xiv::exd::Exd m_EventItemDat;
     xiv::exd::Exd m_EventItemHelpDat;
     xiv::exd::Exd m_ExVersionDat;
     xiv::exd::Exd m_FateDat;
     xiv::exd::Exd m_FCActivityDat;
     xiv::exd::Exd m_FCAuthorityDat;
     xiv::exd::Exd m_FCAuthorityCategoryDat;
     xiv::exd::Exd m_FCChestNameDat;
     xiv::exd::Exd m_FccShopDat;
     xiv::exd::Exd m_FCHierarchyDat;
     xiv::exd::Exd m_FCReputationDat;
     xiv::exd::Exd m_FCRightsDat;
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
     xiv::exd::Exd m_InstanceContentTypeDat;
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
     xiv::exd::Exd m_MapSymbolDat;
     xiv::exd::Exd m_MasterpieceSupplyDutyDat;
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
     xiv::exd::Exd m_NpcEquipDat;
     xiv::exd::Exd m_OmenDat;
     xiv::exd::Exd m_OnlineStatusDat;
     xiv::exd::Exd m_OrchestrionDat;
     xiv::exd::Exd m_OrchestrionPathDat;
     xiv::exd::Exd m_ParamGrowDat;
     xiv::exd::Exd m_PetDat;
     xiv::exd::Exd m_PetActionDat;
     xiv::exd::Exd m_PictureDat;
     xiv::exd::Exd m_PlaceNameDat;
     xiv::exd::Exd m_QuestDat;
     xiv::exd::Exd m_QuestRewardOtherDat;
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
     xiv::exd::Exd m_RelicDat;
     xiv::exd::Exd m_Relic3Dat;
     xiv::exd::Exd m_RelicItemDat;
     xiv::exd::Exd m_RelicNoteDat;
     xiv::exd::Exd m_RelicNoteCategoryDat;
     xiv::exd::Exd m_RetainerTaskDat;
     xiv::exd::Exd m_RetainerTaskNormalDat;
     xiv::exd::Exd m_RetainerTaskParameterDat;
     xiv::exd::Exd m_RetainerTaskRandomDat;
     xiv::exd::Exd m_SalvageDat;
     xiv::exd::Exd m_SatisfactionNpcDat;
     xiv::exd::Exd m_SatisfactionSupplyDat;
     xiv::exd::Exd m_SatisfactionSupplyRewardDat;
     xiv::exd::Exd m_ScreenImageDat;
     xiv::exd::Exd m_SecretRecipeBookDat;
     xiv::exd::Exd m_SpearfishingItemDat;
     xiv::exd::Exd m_SpearfishingNotebookDat;
     xiv::exd::Exd m_SpecialShopDat;
     xiv::exd::Exd m_SpecialShopItemCategoryDat;
     xiv::exd::Exd m_StainDat;
     xiv::exd::Exd m_StatusDat;
     xiv::exd::Exd m_StoryDat;
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
     xiv::exd::Exd m_WarpDat;
     xiv::exd::Exd m_WeatherDat;
     xiv::exd::Exd m_WeatherGroupDat;
     xiv::exd::Exd m_WeatherRateDat;
     xiv::exd::Exd m_WeeklyBingoOrderDataDat;
     xiv::exd::Exd m_WeeklyBingoRewardDataDat;
     xiv::exd::Exd m_WeeklyBingoTextDat;
     xiv::exd::Exd m_WorldDCGroupTypeDat;


     boost::shared_ptr< Achievement > getAchievement( uint32_t AchievementId );     boost::shared_ptr< AchievementCategory > getAchievementCategory( uint32_t AchievementCategoryId );     boost::shared_ptr< AchievementKind > getAchievementKind( uint32_t AchievementKindId );     boost::shared_ptr< Action > getAction( uint32_t ActionId );     boost::shared_ptr< ActionCategory > getActionCategory( uint32_t ActionCategoryId );     boost::shared_ptr< ActionComboRoute > getActionComboRoute( uint32_t ActionComboRouteId );     boost::shared_ptr< ActionIndirection > getActionIndirection( uint32_t ActionIndirectionId );     boost::shared_ptr< ActionProcStatus > getActionProcStatus( uint32_t ActionProcStatusId );     boost::shared_ptr< ActionTimeline > getActionTimeline( uint32_t ActionTimelineId );     boost::shared_ptr< ActionTransient > getActionTransient( uint32_t ActionTransientId );     boost::shared_ptr< Addon > getAddon( uint32_t AddonId );     boost::shared_ptr< Adventure > getAdventure( uint32_t AdventureId );     boost::shared_ptr< AdventureExPhase > getAdventureExPhase( uint32_t AdventureExPhaseId );     boost::shared_ptr< AetherCurrent > getAetherCurrent( uint32_t AetherCurrentId );     boost::shared_ptr< AetherialWheel > getAetherialWheel( uint32_t AetherialWheelId );     boost::shared_ptr< Aetheryte > getAetheryte( uint32_t AetheryteId );     boost::shared_ptr< AirshipExplorationLevel > getAirshipExplorationLevel( uint32_t AirshipExplorationLevelId );     boost::shared_ptr< AirshipExplorationLog > getAirshipExplorationLog( uint32_t AirshipExplorationLogId );     boost::shared_ptr< AirshipExplorationParamType > getAirshipExplorationParamType( uint32_t AirshipExplorationParamTypeId );     boost::shared_ptr< AirshipExplorationPart > getAirshipExplorationPart( uint32_t AirshipExplorationPartId );     boost::shared_ptr< AirshipExplorationPoint > getAirshipExplorationPoint( uint32_t AirshipExplorationPointId );     boost::shared_ptr< AnimaWeapon5 > getAnimaWeapon5( uint32_t AnimaWeapon5Id );     boost::shared_ptr< AnimaWeapon5Param > getAnimaWeapon5Param( uint32_t AnimaWeapon5ParamId );     boost::shared_ptr< AnimaWeapon5PatternGroup > getAnimaWeapon5PatternGroup( uint32_t AnimaWeapon5PatternGroupId );     boost::shared_ptr< AnimaWeapon5SpiritTalk > getAnimaWeapon5SpiritTalk( uint32_t AnimaWeapon5SpiritTalkId );     boost::shared_ptr< AnimaWeapon5SpiritTalkParam > getAnimaWeapon5SpiritTalkParam( uint32_t AnimaWeapon5SpiritTalkParamId );     boost::shared_ptr< AnimaWeapon5TradeItem > getAnimaWeapon5TradeItem( uint32_t AnimaWeapon5TradeItemId );     boost::shared_ptr< AnimaWeaponFUITalk > getAnimaWeaponFUITalk( uint32_t AnimaWeaponFUITalkId );     boost::shared_ptr< AnimaWeaponFUITalkParam > getAnimaWeaponFUITalkParam( uint32_t AnimaWeaponFUITalkParamId );     boost::shared_ptr< AnimaWeaponIcon > getAnimaWeaponIcon( uint32_t AnimaWeaponIconId );     boost::shared_ptr< AnimaWeaponItem > getAnimaWeaponItem( uint32_t AnimaWeaponItemId );     boost::shared_ptr< AquariumFish > getAquariumFish( uint32_t AquariumFishId );     boost::shared_ptr< AquariumWater > getAquariumWater( uint32_t AquariumWaterId );     boost::shared_ptr< AttackType > getAttackType( uint32_t AttackTypeId );     boost::shared_ptr< Balloon > getBalloon( uint32_t BalloonId );     boost::shared_ptr< BaseParam > getBaseParam( uint32_t BaseParamId );     boost::shared_ptr< BattleLeve > getBattleLeve( uint32_t BattleLeveId );     boost::shared_ptr< BeastRankBonus > getBeastRankBonus( uint32_t BeastRankBonusId );     boost::shared_ptr< BeastReputationRank > getBeastReputationRank( uint32_t BeastReputationRankId );     boost::shared_ptr< BeastTribe > getBeastTribe( uint32_t BeastTribeId );     boost::shared_ptr< Behavior > getBehavior( uint32_t BehaviorId );     boost::shared_ptr< BGM > getBGM( uint32_t BGMId );     boost::shared_ptr< BNpcAnnounceIcon > getBNpcAnnounceIcon( uint32_t BNpcAnnounceIconId );     boost::shared_ptr< BNpcBase > getBNpcBase( uint32_t BNpcBaseId );     boost::shared_ptr< BNpcCustomize > getBNpcCustomize( uint32_t BNpcCustomizeId );     boost::shared_ptr< BNpcName > getBNpcName( uint32_t BNpcNameId );     boost::shared_ptr< BuddyAction > getBuddyAction( uint32_t BuddyActionId );     boost::shared_ptr< BuddyEquip > getBuddyEquip( uint32_t BuddyEquipId );     boost::shared_ptr< BuddyItem > getBuddyItem( uint32_t BuddyItemId );     boost::shared_ptr< BuddyRank > getBuddyRank( uint32_t BuddyRankId );     boost::shared_ptr< BuddySkill > getBuddySkill( uint32_t BuddySkillId );     boost::shared_ptr< Cabinet > getCabinet( uint32_t CabinetId );     boost::shared_ptr< CabinetCategory > getCabinetCategory( uint32_t CabinetCategoryId );     boost::shared_ptr< Calendar > getCalendar( uint32_t CalendarId );     boost::shared_ptr< ChainBonus > getChainBonus( uint32_t ChainBonusId );     boost::shared_ptr< CharaMakeCustomize > getCharaMakeCustomize( uint32_t CharaMakeCustomizeId );     boost::shared_ptr< CharaMakeType > getCharaMakeType( uint32_t CharaMakeTypeId );     boost::shared_ptr< ChocoboRace > getChocoboRace( uint32_t ChocoboRaceId );     boost::shared_ptr< ChocoboRaceAbility > getChocoboRaceAbility( uint32_t ChocoboRaceAbilityId );     boost::shared_ptr< ChocoboRaceAbilityType > getChocoboRaceAbilityType( uint32_t ChocoboRaceAbilityTypeId );     boost::shared_ptr< ChocoboRaceItem > getChocoboRaceItem( uint32_t ChocoboRaceItemId );     boost::shared_ptr< ChocoboRaceRank > getChocoboRaceRank( uint32_t ChocoboRaceRankId );     boost::shared_ptr< ChocoboRaceStatus > getChocoboRaceStatus( uint32_t ChocoboRaceStatusId );     boost::shared_ptr< ChocoboRaceTerritory > getChocoboRaceTerritory( uint32_t ChocoboRaceTerritoryId );     boost::shared_ptr< ChocoboTaxiStand > getChocoboTaxiStand( uint32_t ChocoboTaxiStandId );     boost::shared_ptr< ClassJob > getClassJob( uint32_t ClassJobId );     boost::shared_ptr< ClassJobCategory > getClassJobCategory( uint32_t ClassJobCategoryId );     boost::shared_ptr< Companion > getCompanion( uint32_t CompanionId );     boost::shared_ptr< CompanionMove > getCompanionMove( uint32_t CompanionMoveId );     boost::shared_ptr< CompanionTransient > getCompanionTransient( uint32_t CompanionTransientId );     boost::shared_ptr< CompanyAction > getCompanyAction( uint32_t CompanyActionId );     boost::shared_ptr< CompanyCraftDraft > getCompanyCraftDraft( uint32_t CompanyCraftDraftId );     boost::shared_ptr< CompanyCraftDraftCategory > getCompanyCraftDraftCategory( uint32_t CompanyCraftDraftCategoryId );     boost::shared_ptr< CompanyCraftManufactoryState > getCompanyCraftManufactoryState( uint32_t CompanyCraftManufactoryStateId );     boost::shared_ptr< CompanyCraftPart > getCompanyCraftPart( uint32_t CompanyCraftPartId );     boost::shared_ptr< CompanyCraftProcess > getCompanyCraftProcess( uint32_t CompanyCraftProcessId );     boost::shared_ptr< CompanyCraftSequence > getCompanyCraftSequence( uint32_t CompanyCraftSequenceId );     boost::shared_ptr< CompanyCraftSupplyItem > getCompanyCraftSupplyItem( uint32_t CompanyCraftSupplyItemId );     boost::shared_ptr< CompanyCraftType > getCompanyCraftType( uint32_t CompanyCraftTypeId );     boost::shared_ptr< CompleteJournal > getCompleteJournal( uint32_t CompleteJournalId );     boost::shared_ptr< CompleteJournalCategory > getCompleteJournalCategory( uint32_t CompleteJournalCategoryId );     boost::shared_ptr< ContentExAction > getContentExAction( uint32_t ContentExActionId );     boost::shared_ptr< ContentFinderCondition > getContentFinderCondition( uint32_t ContentFinderConditionId );     boost::shared_ptr< ContentFinderConditionTransient > getContentFinderConditionTransient( uint32_t ContentFinderConditionTransientId );     boost::shared_ptr< ContentMemberType > getContentMemberType( uint32_t ContentMemberTypeId );     boost::shared_ptr< ContentRoulette > getContentRoulette( uint32_t ContentRouletteId );     boost::shared_ptr< ContentType > getContentType( uint32_t ContentTypeId );     boost::shared_ptr< CraftAction > getCraftAction( uint32_t CraftActionId );     boost::shared_ptr< CraftLeve > getCraftLeve( uint32_t CraftLeveId );     boost::shared_ptr< CraftType > getCraftType( uint32_t CraftTypeId );     boost::shared_ptr< Currency > getCurrency( uint32_t CurrencyId );     boost::shared_ptr< CustomTalk > getCustomTalk( uint32_t CustomTalkId );     boost::shared_ptr< Cutscene > getCutscene( uint32_t CutsceneId );     boost::shared_ptr< CutScreenImage > getCutScreenImage( uint32_t CutScreenImageId );     boost::shared_ptr< DailySupplyItem > getDailySupplyItem( uint32_t DailySupplyItemId );     boost::shared_ptr< DeepDungeonBan > getDeepDungeonBan( uint32_t DeepDungeonBanId );     boost::shared_ptr< DeepDungeonDanger > getDeepDungeonDanger( uint32_t DeepDungeonDangerId );     boost::shared_ptr< DeepDungeonEquipment > getDeepDungeonEquipment( uint32_t DeepDungeonEquipmentId );     boost::shared_ptr< DeepDungeonFloorEffectUI > getDeepDungeonFloorEffectUI( uint32_t DeepDungeonFloorEffectUIId );     boost::shared_ptr< DeepDungeonItem > getDeepDungeonItem( uint32_t DeepDungeonItemId );     boost::shared_ptr< DeepDungeonStatus > getDeepDungeonStatus( uint32_t DeepDungeonStatusId );     boost::shared_ptr< DefaultTalk > getDefaultTalk( uint32_t DefaultTalkId );     boost::shared_ptr< DeliveryQuest > getDeliveryQuest( uint32_t DeliveryQuestId );     boost::shared_ptr< DisposalShop > getDisposalShop( uint32_t DisposalShopId );     boost::shared_ptr< DisposalShopFilterType > getDisposalShopFilterType( uint32_t DisposalShopFilterTypeId );     boost::shared_ptr< DisposalShopItem > getDisposalShopItem( uint32_t DisposalShopItemId );     boost::shared_ptr< DpsChallenge > getDpsChallenge( uint32_t DpsChallengeId );     boost::shared_ptr< DpsChallengeOfficer > getDpsChallengeOfficer( uint32_t DpsChallengeOfficerId );     boost::shared_ptr< DpsChallengeTransient > getDpsChallengeTransient( uint32_t DpsChallengeTransientId );     boost::shared_ptr< Emote > getEmote( uint32_t EmoteId );     boost::shared_ptr< EmoteCategory > getEmoteCategory( uint32_t EmoteCategoryId );     boost::shared_ptr< ENpcBase > getENpcBase( uint32_t ENpcBaseId );     boost::shared_ptr< ENpcResident > getENpcResident( uint32_t ENpcResidentId );     boost::shared_ptr< EObj > getEObj( uint32_t EObjId );     boost::shared_ptr< EquipSlotCategory > getEquipSlotCategory( uint32_t EquipSlotCategoryId );     boost::shared_ptr< EventAction > getEventAction( uint32_t EventActionId );     boost::shared_ptr< EventIconPriority > getEventIconPriority( uint32_t EventIconPriorityId );     boost::shared_ptr< EventIconType > getEventIconType( uint32_t EventIconTypeId );     boost::shared_ptr< EventItem > getEventItem( uint32_t EventItemId );     boost::shared_ptr< EventItemHelp > getEventItemHelp( uint32_t EventItemHelpId );     boost::shared_ptr< ExVersion > getExVersion( uint32_t ExVersionId );     boost::shared_ptr< Fate > getFate( uint32_t FateId );     boost::shared_ptr< FCActivity > getFCActivity( uint32_t FCActivityId );     boost::shared_ptr< FCAuthority > getFCAuthority( uint32_t FCAuthorityId );     boost::shared_ptr< FCAuthorityCategory > getFCAuthorityCategory( uint32_t FCAuthorityCategoryId );     boost::shared_ptr< FCChestName > getFCChestName( uint32_t FCChestNameId );     boost::shared_ptr< FccShop > getFccShop( uint32_t FccShopId );     boost::shared_ptr< FCHierarchy > getFCHierarchy( uint32_t FCHierarchyId );     boost::shared_ptr< FCReputation > getFCReputation( uint32_t FCReputationId );     boost::shared_ptr< FCRights > getFCRights( uint32_t FCRightsId );     boost::shared_ptr< FishingSpot > getFishingSpot( uint32_t FishingSpotId );     boost::shared_ptr< FishParameter > getFishParameter( uint32_t FishParameterId );     boost::shared_ptr< GardeningSeed > getGardeningSeed( uint32_t GardeningSeedId );     boost::shared_ptr< GatheringCondition > getGatheringCondition( uint32_t GatheringConditionId );     boost::shared_ptr< GatheringExp > getGatheringExp( uint32_t GatheringExpId );     boost::shared_ptr< GatheringItem > getGatheringItem( uint32_t GatheringItemId );     boost::shared_ptr< GatheringItemLevelConvertTable > getGatheringItemLevelConvertTable( uint32_t GatheringItemLevelConvertTableId );     boost::shared_ptr< GatheringItemPoint > getGatheringItemPoint( uint32_t GatheringItemPointId );     boost::shared_ptr< GatheringNotebookList > getGatheringNotebookList( uint32_t GatheringNotebookListId );     boost::shared_ptr< GatheringPoint > getGatheringPoint( uint32_t GatheringPointId );     boost::shared_ptr< GatheringPointBase > getGatheringPointBase( uint32_t GatheringPointBaseId );     boost::shared_ptr< GatheringPointBonus > getGatheringPointBonus( uint32_t GatheringPointBonusId );     boost::shared_ptr< GatheringPointBonusType > getGatheringPointBonusType( uint32_t GatheringPointBonusTypeId );     boost::shared_ptr< GatheringPointName > getGatheringPointName( uint32_t GatheringPointNameId );     boost::shared_ptr< GatheringSubCategory > getGatheringSubCategory( uint32_t GatheringSubCategoryId );     boost::shared_ptr< GatheringType > getGatheringType( uint32_t GatheringTypeId );     boost::shared_ptr< GcArmyExpedition > getGcArmyExpedition( uint32_t GcArmyExpeditionId );     boost::shared_ptr< GcArmyExpeditionMemberBonus > getGcArmyExpeditionMemberBonus( uint32_t GcArmyExpeditionMemberBonusId );     boost::shared_ptr< GcArmyExpeditionType > getGcArmyExpeditionType( uint32_t GcArmyExpeditionTypeId );     boost::shared_ptr< GcArmyMemberGrow > getGcArmyMemberGrow( uint32_t GcArmyMemberGrowId );     boost::shared_ptr< GcArmyTraining > getGcArmyTraining( uint32_t GcArmyTrainingId );     boost::shared_ptr< GCScripShopItem > getGCScripShopItem( uint32_t GCScripShopItemId );     boost::shared_ptr< GCShop > getGCShop( uint32_t GCShopId );     boost::shared_ptr< GCShopItemCategory > getGCShopItemCategory( uint32_t GCShopItemCategoryId );     boost::shared_ptr< GCSupplyDuty > getGCSupplyDuty( uint32_t GCSupplyDutyId );     boost::shared_ptr< GCSupplyDutyReward > getGCSupplyDutyReward( uint32_t GCSupplyDutyRewardId );     boost::shared_ptr< GeneralAction > getGeneralAction( uint32_t GeneralActionId );     boost::shared_ptr< GilShop > getGilShop( uint32_t GilShopId );     boost::shared_ptr< GilShopItem > getGilShopItem( uint32_t GilShopItemId );     boost::shared_ptr< GoldSaucerTextData > getGoldSaucerTextData( uint32_t GoldSaucerTextDataId );     boost::shared_ptr< GrandCompany > getGrandCompany( uint32_t GrandCompanyId );     boost::shared_ptr< GrandCompanyRank > getGrandCompanyRank( uint32_t GrandCompanyRankId );     boost::shared_ptr< GuardianDeity > getGuardianDeity( uint32_t GuardianDeityId );     boost::shared_ptr< GuildleveAssignment > getGuildleveAssignment( uint32_t GuildleveAssignmentId );     boost::shared_ptr< GuildOrderGuide > getGuildOrderGuide( uint32_t GuildOrderGuideId );     boost::shared_ptr< GuildOrderOfficer > getGuildOrderOfficer( uint32_t GuildOrderOfficerId );     boost::shared_ptr< HouseRetainerPose > getHouseRetainerPose( uint32_t HouseRetainerPoseId );     boost::shared_ptr< HousingFurniture > getHousingFurniture( uint32_t HousingFurnitureId );     boost::shared_ptr< HousingYardObject > getHousingYardObject( uint32_t HousingYardObjectId );     boost::shared_ptr< InstanceContent > getInstanceContent( uint32_t InstanceContentId );     boost::shared_ptr< InstanceContentBuff > getInstanceContentBuff( uint32_t InstanceContentBuffId );     boost::shared_ptr< InstanceContentTextData > getInstanceContentTextData( uint32_t InstanceContentTextDataId );     boost::shared_ptr< InstanceContentType > getInstanceContentType( uint32_t InstanceContentTypeId );     boost::shared_ptr< Item > getItem( uint32_t ItemId );     boost::shared_ptr< ItemAction > getItemAction( uint32_t ItemActionId );     boost::shared_ptr< ItemFood > getItemFood( uint32_t ItemFoodId );     boost::shared_ptr< ItemSearchCategory > getItemSearchCategory( uint32_t ItemSearchCategoryId );     boost::shared_ptr< ItemSeries > getItemSeries( uint32_t ItemSeriesId );     boost::shared_ptr< ItemSpecialBonus > getItemSpecialBonus( uint32_t ItemSpecialBonusId );     boost::shared_ptr< ItemUICategory > getItemUICategory( uint32_t ItemUICategoryId );     boost::shared_ptr< JournalCategory > getJournalCategory( uint32_t JournalCategoryId );     boost::shared_ptr< JournalGenre > getJournalGenre( uint32_t JournalGenreId );     boost::shared_ptr< JournalSection > getJournalSection( uint32_t JournalSectionId );     boost::shared_ptr< Leve > getLeve( uint32_t LeveId );     boost::shared_ptr< LeveAssignmentType > getLeveAssignmentType( uint32_t LeveAssignmentTypeId );     boost::shared_ptr< LeveClient > getLeveClient( uint32_t LeveClientId );     boost::shared_ptr< Level > getLevel( uint32_t LevelId );     boost::shared_ptr< LeveRewardItem > getLeveRewardItem( uint32_t LeveRewardItemId );     boost::shared_ptr< LeveRewardItemGroup > getLeveRewardItemGroup( uint32_t LeveRewardItemGroupId );     boost::shared_ptr< LeveVfx > getLeveVfx( uint32_t LeveVfxId );     boost::shared_ptr< LogFilter > getLogFilter( uint32_t LogFilterId );     boost::shared_ptr< LogKind > getLogKind( uint32_t LogKindId );     boost::shared_ptr< LogKindCategoryText > getLogKindCategoryText( uint32_t LogKindCategoryTextId );     boost::shared_ptr< LogMessage > getLogMessage( uint32_t LogMessageId );     boost::shared_ptr< MacroIcon > getMacroIcon( uint32_t MacroIconId );     boost::shared_ptr< MacroIconRedirectOld > getMacroIconRedirectOld( uint32_t MacroIconRedirectOldId );     boost::shared_ptr< MainCommand > getMainCommand( uint32_t MainCommandId );     boost::shared_ptr< MainCommandCategory > getMainCommandCategory( uint32_t MainCommandCategoryId );     boost::shared_ptr< Map > getMap( uint32_t MapId );     boost::shared_ptr< MapMarker > getMapMarker( uint32_t MapMarkerId );     boost::shared_ptr< MapSymbol > getMapSymbol( uint32_t MapSymbolId );     boost::shared_ptr< MasterpieceSupplyDuty > getMasterpieceSupplyDuty( uint32_t MasterpieceSupplyDutyId );     boost::shared_ptr< Materia > getMateria( uint32_t MateriaId );     boost::shared_ptr< MinionRace > getMinionRace( uint32_t MinionRaceId );     boost::shared_ptr< MinionRules > getMinionRules( uint32_t MinionRulesId );     boost::shared_ptr< MinionSkillType > getMinionSkillType( uint32_t MinionSkillTypeId );     boost::shared_ptr< MobHuntTarget > getMobHuntTarget( uint32_t MobHuntTargetId );     boost::shared_ptr< ModelChara > getModelChara( uint32_t ModelCharaId );     boost::shared_ptr< MonsterNote > getMonsterNote( uint32_t MonsterNoteId );     boost::shared_ptr< MonsterNoteTarget > getMonsterNoteTarget( uint32_t MonsterNoteTargetId );     boost::shared_ptr< Mount > getMount( uint32_t MountId );     boost::shared_ptr< MountAction > getMountAction( uint32_t MountActionId );     boost::shared_ptr< NpcEquip > getNpcEquip( uint32_t NpcEquipId );     boost::shared_ptr< Omen > getOmen( uint32_t OmenId );     boost::shared_ptr< OnlineStatus > getOnlineStatus( uint32_t OnlineStatusId );     boost::shared_ptr< Orchestrion > getOrchestrion( uint32_t OrchestrionId );     boost::shared_ptr< OrchestrionPath > getOrchestrionPath( uint32_t OrchestrionPathId );     boost::shared_ptr< ParamGrow > getParamGrow( uint32_t ParamGrowId );     boost::shared_ptr< Pet > getPet( uint32_t PetId );     boost::shared_ptr< PetAction > getPetAction( uint32_t PetActionId );     boost::shared_ptr< Picture > getPicture( uint32_t PictureId );     boost::shared_ptr< PlaceName > getPlaceName( uint32_t PlaceNameId );     boost::shared_ptr< Quest > getQuest( uint32_t QuestId );     boost::shared_ptr< QuestRewardOther > getQuestRewardOther( uint32_t QuestRewardOtherId );     boost::shared_ptr< Race > getRace( uint32_t RaceId );     boost::shared_ptr< RacingChocoboItem > getRacingChocoboItem( uint32_t RacingChocoboItemId );     boost::shared_ptr< RacingChocoboName > getRacingChocoboName( uint32_t RacingChocoboNameId );     boost::shared_ptr< RacingChocoboNameCategory > getRacingChocoboNameCategory( uint32_t RacingChocoboNameCategoryId );     boost::shared_ptr< RacingChocoboNameInfo > getRacingChocoboNameInfo( uint32_t RacingChocoboNameInfoId );     boost::shared_ptr< RacingChocoboParam > getRacingChocoboParam( uint32_t RacingChocoboParamId );     boost::shared_ptr< Recipe > getRecipe( uint32_t RecipeId );     boost::shared_ptr< RecipeElement > getRecipeElement( uint32_t RecipeElementId );     boost::shared_ptr< RecipeLevelTable > getRecipeLevelTable( uint32_t RecipeLevelTableId );     boost::shared_ptr< RecipeNotebookList > getRecipeNotebookList( uint32_t RecipeNotebookListId );     boost::shared_ptr< Relic > getRelic( uint32_t RelicId );     boost::shared_ptr< Relic3 > getRelic3( uint32_t Relic3Id );     boost::shared_ptr< RelicItem > getRelicItem( uint32_t RelicItemId );     boost::shared_ptr< RelicNote > getRelicNote( uint32_t RelicNoteId );     boost::shared_ptr< RelicNoteCategory > getRelicNoteCategory( uint32_t RelicNoteCategoryId );     boost::shared_ptr< RetainerTask > getRetainerTask( uint32_t RetainerTaskId );     boost::shared_ptr< RetainerTaskNormal > getRetainerTaskNormal( uint32_t RetainerTaskNormalId );     boost::shared_ptr< RetainerTaskParameter > getRetainerTaskParameter( uint32_t RetainerTaskParameterId );     boost::shared_ptr< RetainerTaskRandom > getRetainerTaskRandom( uint32_t RetainerTaskRandomId );     boost::shared_ptr< Salvage > getSalvage( uint32_t SalvageId );     boost::shared_ptr< SatisfactionNpc > getSatisfactionNpc( uint32_t SatisfactionNpcId );     boost::shared_ptr< SatisfactionSupply > getSatisfactionSupply( uint32_t SatisfactionSupplyId );     boost::shared_ptr< SatisfactionSupplyReward > getSatisfactionSupplyReward( uint32_t SatisfactionSupplyRewardId );     boost::shared_ptr< ScreenImage > getScreenImage( uint32_t ScreenImageId );     boost::shared_ptr< SecretRecipeBook > getSecretRecipeBook( uint32_t SecretRecipeBookId );     boost::shared_ptr< SpearfishingItem > getSpearfishingItem( uint32_t SpearfishingItemId );     boost::shared_ptr< SpearfishingNotebook > getSpearfishingNotebook( uint32_t SpearfishingNotebookId );     boost::shared_ptr< SpecialShop > getSpecialShop( uint32_t SpecialShopId );     boost::shared_ptr< SpecialShopItemCategory > getSpecialShopItemCategory( uint32_t SpecialShopItemCategoryId );     boost::shared_ptr< Stain > getStain( uint32_t StainId );     boost::shared_ptr< Status > getStatus( uint32_t StatusId );     boost::shared_ptr< Story > getStory( uint32_t StoryId );     boost::shared_ptr< SwitchTalk > getSwitchTalk( uint32_t SwitchTalkId );     boost::shared_ptr< TerritoryType > getTerritoryType( uint32_t TerritoryTypeId );     boost::shared_ptr< TextCommand > getTextCommand( uint32_t TextCommandId );     boost::shared_ptr< Title > getTitle( uint32_t TitleId );     boost::shared_ptr< Tomestones > getTomestones( uint32_t TomestonesId );     boost::shared_ptr< TomestonesItem > getTomestonesItem( uint32_t TomestonesItemId );     boost::shared_ptr< TopicSelect > getTopicSelect( uint32_t TopicSelectId );     boost::shared_ptr< Town > getTown( uint32_t TownId );     boost::shared_ptr< Trait > getTrait( uint32_t TraitId );     boost::shared_ptr< TraitRecast > getTraitRecast( uint32_t TraitRecastId );     boost::shared_ptr< TraitTransient > getTraitTransient( uint32_t TraitTransientId );     boost::shared_ptr< Tribe > getTribe( uint32_t TribeId );     boost::shared_ptr< TripleTriad > getTripleTriad( uint32_t TripleTriadId );     boost::shared_ptr< TripleTriadCard > getTripleTriadCard( uint32_t TripleTriadCardId );     boost::shared_ptr< TripleTriadCardRarity > getTripleTriadCardRarity( uint32_t TripleTriadCardRarityId );     boost::shared_ptr< TripleTriadCardResident > getTripleTriadCardResident( uint32_t TripleTriadCardResidentId );     boost::shared_ptr< TripleTriadCardType > getTripleTriadCardType( uint32_t TripleTriadCardTypeId );     boost::shared_ptr< TripleTriadCompetition > getTripleTriadCompetition( uint32_t TripleTriadCompetitionId );     boost::shared_ptr< TripleTriadRule > getTripleTriadRule( uint32_t TripleTriadRuleId );     boost::shared_ptr< Tutorial > getTutorial( uint32_t TutorialId );     boost::shared_ptr< TutorialDPS > getTutorialDPS( uint32_t TutorialDPSId );     boost::shared_ptr< TutorialHealer > getTutorialHealer( uint32_t TutorialHealerId );     boost::shared_ptr< TutorialTank > getTutorialTank( uint32_t TutorialTankId );     boost::shared_ptr< Warp > getWarp( uint32_t WarpId );     boost::shared_ptr< Weather > getWeather( uint32_t WeatherId );     boost::shared_ptr< WeatherGroup > getWeatherGroup( uint32_t WeatherGroupId );     boost::shared_ptr< WeatherRate > getWeatherRate( uint32_t WeatherRateId );     boost::shared_ptr< WeeklyBingoOrderData > getWeeklyBingoOrderData( uint32_t WeeklyBingoOrderDataId );     boost::shared_ptr< WeeklyBingoRewardData > getWeeklyBingoRewardData( uint32_t WeeklyBingoRewardDataId );     boost::shared_ptr< WeeklyBingoText > getWeeklyBingoText( uint32_t WeeklyBingoTextId );     boost::shared_ptr< WorldDCGroupType > getWorldDCGroupType( uint32_t WorldDCGroupTypeId );

  };

}
}

#endif

