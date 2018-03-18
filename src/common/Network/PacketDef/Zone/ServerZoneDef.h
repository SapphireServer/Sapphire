/**
* IPC Packet Definitions (Server IPC Packets)
* Structural definitions for the various server IPC packet types.
* IMPORTANT NOTE: Do not use these for parsing IPC packets sent by the
* client. See the Client namespace for those types!
*/
#ifndef _CORE_NETWORK_PACKETS_ZONE_SERVER_IPC_H
#define _CORE_NETWORK_PACKETS_ZONE_SERVER_IPC_H

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* Structural representation of the packet sent by the server as response
* to a ping packet
*/
struct FFXIVIpcPing : FFXIVIpcBasePacket<Ping>
{
   /* 0000 */ uint64_t timeInMilliseconds;
   /* 0008 */ uint8_t unknown_8[0x38];
};

/**
* Structural representation of the packet sent by the server as response
* to a ping packet
*/
struct FFXIVIpcInit : FFXIVIpcBasePacket<Init>
{
   uint64_t unknown;
   uint32_t charId;
   uint32_t unknown1;
};

/**
* Structural representation of the packet sent by the server
* carrying chat messages
*/
struct FFXIVIpcChat : FFXIVIpcBasePacket<Chat>
{
   /* 0000 */  uint8_t padding[14]; //Maybe this is SubCode, or some kind of talker ID...
   Common::ChatType chatType;
   char name[32];
   char msg[1012];
};

struct FFXIVIpcChatBanned : FFXIVIpcBasePacket<ChatBanned>
{
   uint8_t padding[4]; // I was not sure reinterpreting ZST is valid behavior in C++.
                     // client doesn't care about the data (zero sized) for this opcode anyway.
};

/**
* Structural representation of the packet sent by the server
* carrying chat messages
*/
struct FFXIVIpcLogout : FFXIVIpcBasePacket<Logout>
{
   uint32_t flags1;
   uint32_t flags2;
};

/**
* Structural representation of the packet sent by the server
* sent to show the play time
*/
struct FFXIVIpcPlayTime : FFXIVIpcBasePacket<Playtime>
{
   uint32_t playTimeInMinutes;
   uint32_t padding;
};


/**
* Structural representation of the packet sent by the server
* with a list of players ( party list | friend list | search results )
*/
struct PlayerEntry {
   uint64_t contentId;
   uint8_t bytes[12];
   uint16_t zoneId;
   uint16_t zoneId1;
   char bytes1[8];
   uint64_t onlineStatusMask;
   uint8_t classJob;
   uint8_t padding;
   uint8_t level;
   uint8_t padding1;
   uint16_t padding2;
   uint8_t one;
   char name[0x20];
   char fcTag[9];
};

struct FFXIVIpcSocialList : FFXIVIpcBasePacket<SocialList>
{
   uint32_t padding;
   uint32_t padding1;
   uint32_t padding2;
   uint8_t type;
   uint8_t sequence;
   uint16_t padding3;

   PlayerEntry entries[10];
};


struct FFXIVIpcSetSearchInfo : FFXIVIpcBasePacket<UpdateSearchInfo>
{
   uint64_t onlineStatusFlags;
   uint64_t unknown;
   uint32_t unknown1;
   uint8_t padding;
   uint8_t selectRegion;
   char searchMessage[193];
   uint8_t padding2;
};

struct FFXIVIpcInitSearchInfo : FFXIVIpcBasePacket<InitSearchInfo>
{
   uint64_t onlineStatusFlags;
   uint64_t unknown;
   uint8_t unknown1;
   uint8_t selectRegion;
   char searchMessage[193];
   char padding[5];
};

/**
* Structural representation of the packet sent by the server
* to display a server notice message
*/
struct FFXIVIpcServerNotice : FFXIVIpcBasePacket<ServerNotice>
{
   /* 0000 */ uint8_t padding;
   char message[307];
};

struct FFXIVIpcSetOnlineStatus : FFXIVIpcBasePacket<SetOnlineStatus>
{
   uint64_t onlineStatusFlags;
};

struct FFXIVIpcBlackList : FFXIVIpcBasePacket<BlackList>
{
   struct BlEntry
   {
      uint64_t contentId;
      char name[32];
   } entry[20];
   uint8_t padding;
   uint8_t padding1;
   uint16_t sequence;
   uint32_t padding2;
};

struct FFXIVIpcLogMessage : FFXIVIpcBasePacket<LogMessage>
{
   uint32_t field_0;
   uint32_t field_4;
   uint32_t field_8;
   uint32_t field_12;
   uint32_t category;
   uint32_t logMessage;
   uint8_t field_24;
   uint8_t field_25;
   uint8_t field_26[32];
   uint32_t field_58;
};

struct FFXIVIpcLinkshellList : FFXIVIpcBasePacket<LinkshellList>
{
   struct LsEntry
   {
      uint64_t lsId;
      uint64_t unknownId;
      uint8_t unknown;
      uint8_t rank;
      uint16_t padding;
      uint8_t lsName[20];
   } entry[8];
};

struct FFXIVIpcStatusEffectList : FFXIVIpcBasePacket<StatusEffectList>
{
   uint8_t classId;
   uint8_t level1;
   uint16_t level;
   uint32_t current_hp;
   uint32_t max_hp;
   uint16_t current_mp;
   uint16_t max_mp;
   uint16_t currentTp;
   uint16_t unknown1;
   Common::StatusEffect effect[30];
   uint32_t padding;
};

struct FFXIVGCAffiliation : FFXIVIpcBasePacket<GCAffiliation>
{
   uint8_t gcId;
   uint8_t gcRank[3];
};

/**
* Structural representation of the packet sent by the server
* add a status effect
*/
struct FFXIVIpcAddStatusEffect : FFXIVIpcBasePacket<AddStatusEffect>
{
   uint32_t unknown;
   uint32_t actor_id;
   uint8_t unknown1;
   uint8_t unknown2;
   uint16_t padding1;
   uint32_t current_hp;
   uint16_t current_mp;
   uint16_t current_tp;
   uint32_t max_hp;
   uint16_t max_mp;
   uint16_t max_something;
   uint8_t effect_index; // which position do i display this
   uint8_t unknown3;
   uint16_t effect_id;
   uint16_t param;
   uint16_t unknown5;    // Sort this out (old right half of power/param property)
   float duration;
   uint32_t actor_id1;
   uint8_t unknown4[52];
};

/**
* Structural representation of the packet sent by the server
* to update certain player details / status
*/
struct FFXIVIpcActorControl142 : FFXIVIpcBasePacket<ActorControl142>
{
   /* 0000 */ uint16_t category;
   /* 0002 */ uint16_t padding;
   /* 0004 */ uint32_t param1;
   /* 0008 */ uint32_t param2;
   /* 000C */ uint32_t param3;
   /* 0010 */ uint32_t param4;
   /* 0014 */ uint32_t padding1;
};

/**
* Structural representation of the packet sent by the server
* to update certain player details / status
*/
struct FFXIVIpcActorControl143 : FFXIVIpcBasePacket<ActorControl143>
{
   /* 0000 */ uint16_t category;
   /* 0002 */ uint16_t padding;
   /* 0004 */ uint32_t param1;
   /* 0008 */ uint32_t param2;
   /* 000C */ uint32_t param3;
   /* 0010 */ uint32_t param4;
   /* 0014 */ uint32_t param5;
   /* 0018 */ uint32_t param6;
   /* 0018 */ uint32_t padding1;
};

/**
* Structural representation of the packet sent by the server
* to update certain player details / status
*/
struct FFXIVIpcActorControl144 : FFXIVIpcBasePacket<ActorControl144>
{
   /* 0000 */ uint16_t category;
   /* 0002 */ uint16_t padding;
   /* 0004 */ uint32_t param1;
   /* 0008 */ uint32_t param2;
   /* 000C */ uint32_t param3;
   /* 0010 */ uint32_t param4;
   /* 0014 */ uint32_t padding1;
   /* 0018 */ uint64_t targetId;
};

/**
* Structural representation of the packet sent by the server
* to update HP / MP / TP
*/
struct FFXIVIpcUpdateHpMpTp : FFXIVIpcBasePacket<UpdateHpMpTp>
{
   /* 0000 */ uint32_t hp;
   /* 0004 */ uint16_t mp;
   /* 0006 */ uint16_t tp;
   /* 0008 */ uint32_t unknown_8;
   /* 000C */ uint32_t unknown_12;
};


/**
* Structural representation of the packet sent by the server
* for battle actions
*/
struct effectEntry
{
   Common::ActionEffectType effectType;
   Common::ActionHitSeverityType hitSeverity;
   uint8_t unknown_3;
   int8_t bonusPercent;
   int16_t value;
   uint8_t valueMultiplier;      // This multiplies whatever value is in the 'value' param by 10. Possibly a workaround for big numbers
   uint8_t unknown_6;
};

struct FFXIVIpcEffect : FFXIVIpcBasePacket<Effect>
{
   uint32_t targetId;
   uint32_t unknown_1;
   uint32_t actionAnimationId;
   uint32_t unknown_2;
   uint32_t unknown_5;
   uint32_t unknown_6;
   uint32_t effectTargetId;
   uint16_t rotation;
   uint16_t actionTextId;
   uint8_t unknown_61;
   uint8_t unknown_62;
   uint8_t unknown_10;
   uint8_t numEffects;
   uint32_t u11;
   effectEntry effects[8];
   uint32_t effectTarget;
   uint64_t unknown_8;
};


/**
* Structural representation of the packet sent by the server
* to spawn an actor
*/
struct FFXIVIpcPlayerSpawn : FFXIVIpcBasePacket<PlayerSpawn>
{
   uint16_t title;
   uint16_t u1b;
   uint8_t u2b;
   uint8_t u2ab;
   uint8_t gmRank;
   uint8_t u3b;

   uint8_t u3a;
   uint8_t onlineStatus;
   uint8_t u3c;
   uint8_t pose;

   uint32_t u4;

   uint64_t targetId;
   uint32_t u6;
   uint32_t u7;
   uint64_t mainWeaponModel;
   uint64_t secWeaponModel;
   uint64_t craftToolModel;

   uint32_t u14;
   uint32_t u15;
   uint32_t bNPCBase;
   uint32_t bNPCName;
   uint32_t u18;
   uint32_t u19;
   uint32_t directorId;
   uint32_t ownerId;
   uint32_t u22;
   uint32_t hPMax;
   uint32_t hPCurr;
   uint32_t displayFlags;
   uint16_t fateID;
   uint16_t mPCurr;
   uint16_t tPCurr;
   uint16_t mPMax;
   uint16_t tPMax;
   uint16_t modelChara;
   uint16_t rotation;
   uint16_t activeMinion;
   uint8_t spawnIndex;
   uint8_t state;
   uint8_t persistantEmote;
   uint8_t modelType; // modelType -> eventSystemDefine
   uint8_t subtype;
   uint8_t voice;
   uint16_t u25c;
   uint8_t enemyType;
   uint8_t level;
   uint8_t classJob;
   uint8_t u26d;
   uint16_t u27a;
   uint8_t currentMount;
   uint8_t mountHead;
   uint8_t mountBody;
   uint8_t mountFeet;
   uint8_t mountColor;
   uint8_t scale;
   uint32_t u29b;
   uint32_t u30b;
   Common::StatusEffect effect[30];
   Common::FFXIVARR_POSITION3 pos;
   uint32_t models[10];
   char name[32];
   uint8_t look[26];
   char fcTag[6];
   uint32_t unk30;
};

/**
* Structural representation of the packet sent by the server
* to spawn an actor
*/
struct FFXIVIpcNpcSpawn : FFXIVIpcBasePacket<NpcSpawn>
{
   uint32_t gimmickId; // needs to be existing in the map, mob will snap to it
   uint8_t u2b;
   uint8_t u2ab;
   uint8_t gmRank;
   uint8_t u3b;

   uint8_t u3a;
   uint8_t onlineStatus;
   uint8_t u3c;
   uint8_t pose;

   uint32_t u4;

   uint64_t targetId;
   uint32_t u6;
   uint32_t u7;
   uint64_t mainWeaponModel;
   uint64_t secWeaponModel;
   uint64_t craftToolModel;

   uint32_t u14;
   uint32_t u15;
   uint32_t bNPCBase;
   uint32_t bNPCName;
   uint32_t u18;
   uint32_t u19;
   uint32_t directorId;
   uint32_t ownerId;
   uint32_t u22;
   uint32_t hPMax;
   uint32_t hPCurr;
   uint32_t displayFlags;
   uint16_t fateID;
   uint16_t mPCurr;
   uint16_t tPCurr;
   uint16_t mPMax;
   uint16_t tPMax;
   uint16_t modelChara;
   uint16_t rotation;
   uint16_t activeMinion;
   uint8_t spawnIndex;
   uint8_t state;
   uint8_t persistantEmote;
   uint8_t modelType;
   uint8_t subtype;
   uint8_t voice;
   uint16_t u25c;
   uint8_t enemyType;
   uint8_t level;
   uint8_t classJob;
   uint8_t u26d;
   uint16_t u27a;
   uint8_t currentMount;
   uint8_t mountHead;
   uint8_t mountBody;
   uint8_t mountFeet;
   uint8_t mountColor;
   uint8_t scale;
   uint32_t u29b;
   uint32_t u30b;
   Common::StatusEffect effect[30];
   Common::FFXIVARR_POSITION3 pos;
   uint32_t models[10];
   char name[32];
   uint8_t look[26];
   char fcTag[6];
   uint32_t unk30;
};

/**
* Structural representation of the packet sent by the server
* to show player movement
*/
struct FFXIVIpcActorFreeSpawn : FFXIVIpcBasePacket<ActorFreeSpawn>
{
   uint32_t spawnId;
   uint32_t actorId;
};

/**
* Structural representation of the packet sent by the server
* to show player movement
*/
struct FFXIVIpcActorMove : FFXIVIpcBasePacket<ActorMove>
{
   /* 0000 */ uint8_t rotation;
   /* 0001 */ uint8_t unknown_1;
   /* 0002 */ uint8_t unknown_2;
   /* 0003 */ uint8_t unknown_3;
   /* 0004 */ uint16_t unknown_4;
   /* 0006 */ uint16_t posX;
   /* 0008 */ uint16_t posY;
   /* 000a */ uint16_t posZ;
   /* 000C */ uint32_t unknown_12;
};

/**
* Structural representation of the packet sent by the server
* to set an actors position
*/
struct FFXIVIpcActorSetPos : FFXIVIpcBasePacket<ActorSetPos>
{
   uint16_t r16;
   uint8_t waitForLoad;
   uint8_t unknown1;
   uint32_t unknown2;
   float x;
   float y;
   float z;
   uint32_t unknown3;

};



/**
* Structural representation of the packet sent by the server
* to start an actors casting
*/
struct FFXIVIpcActorCast : FFXIVIpcBasePacket<ActorCast>
{
   uint16_t action_id;
   Common::SkillType skillType;
   uint8_t unknown;
   uint32_t unknown_1; // Also action id
   float cast_time;
   uint32_t target_id;
   float rotation; // In radians
   uint32_t unknown_2;
   uint16_t posX;
   uint16_t posY;
   uint16_t posZ;
   uint16_t unknown_3;
};

struct FFXIVIpcHateList : FFXIVIpcBasePacket<HateList>
{
   uint32_t numEntries;
   struct LsEntry
   {
      uint32_t actorId;
      uint8_t hatePercent;
      uint8_t unknown;
      uint16_t padding;
   } entry[32];
   uint32_t padding;
};

struct FFXIVIpcUpdateClassInfo : FFXIVIpcBasePacket<UpdateClassInfo>
{
   uint8_t classId;
   uint8_t level1;
   uint16_t level;
   uint32_t nextLevelIndex;
   uint32_t currentExp;
   uint32_t restedExp;
};

/**
 * Structural representation of the packet sent by the server
 * to send the titles available to the player
 */
struct FFXIVIpcPlayerTitleList : FFXIVIpcBasePacket<PlayerTitleList>
{
   uint8_t titleList[48];
};

/**
* Structural representation of the packet sent by the server
* to initialize a zone for the player
*/
struct FFXIVIpcInitZone : FFXIVIpcBasePacket<InitZone>
{
   uint16_t serverId;
   uint16_t zoneId;
   uint16_t unknown1;
   uint16_t unknown2;
   uint32_t unknown3;
   uint32_t unknown4;
   uint8_t weatherId;
   uint8_t bitmask;
   uint16_t unknown5;
   uint16_t festivalId;
   uint16_t unknown7;
   uint32_t unknown8;
   Common::FFXIVARR_POSITION3 pos;
};


/**
* Structural representation of the packet sent by the server to initialize
* the client UI upon initial connection.
*/
struct FFXIVIpcInitUI : FFXIVIpcBasePacket<InitUI>
{
   uint64_t contentId;
   uint32_t unknown8;
   uint32_t unknownC;
   uint32_t charId;
   uint32_t restedExp;
   uint16_t currentLevel;
   uint8_t maxLevel;
   uint8_t expansion;
   uint8_t unknown1A;
   uint8_t race;
   uint8_t tribe;
   uint8_t gender;
   uint8_t currentJob;
   uint8_t currentClass;
   uint8_t deity;
   uint8_t namedayMonth;
   uint8_t namedayDay;
   uint8_t cityState;
   uint8_t homepoint;
   uint8_t unknown26; // 2 if "warrior of light"
   uint8_t petHotBar;
   uint8_t companionRank;
   uint8_t companionStars;
   uint8_t companionSp;
   uint8_t companionUnk2B;
   uint8_t companionColor;
   uint8_t companionFavoFeed;
   uint8_t companionUnk2E;
   float companionTimePassed;
   uint32_t companionCurrentExp;
   uint32_t unknown38;
   uint32_t unknown3C;
   uint32_t fishCaught;
   uint32_t useBaitCatalogId;
   uint32_t pvpWolfFoldMatches;
   uint16_t pvpWolfFoldWeeklyMatches;
   uint16_t pvpWolfFoldWeeklyVictories;
   uint16_t pvpStats[6];
   uint16_t playerCommendations;
   uint16_t pvpStats1;
   uint8_t frontlineCampaigns[4];
   uint16_t frontlineCampaignsWeekly;
   uint8_t currentRelic;
   uint8_t currentBook;
   uint8_t masterCrafterMask;
   uint8_t unknown69;
   uint8_t unknown6A;
   uint8_t unknown6B;
   uint8_t unknown6C[4];
   uint8_t unknown70[61];
   uint8_t preNamePadding;
   char name[32];
   uint8_t unknownOword[16];
   uint8_t unknownDE[2];
   uint16_t levels[25];
   uint16_t levelsPadding;
   uint32_t exp[25];
   uint8_t unlockBitmask[64];
   uint8_t aetheryte[16];
   uint8_t discovery[421];
   uint8_t howto[33];
   uint8_t minions[37];
   uint8_t chocoboTaxiMask[8];
   uint8_t contentClearMask[108];
   uint8_t contentClearPadding;
   uint16_t unknown428[8];
   uint8_t companionBardingMask[8];
   uint8_t companionEquippedHead;
   uint8_t companionEquippedBody;
   uint8_t companionEquippedFeet;
   uint8_t companionUnk4[4];
   uint8_t companion_fields[11];
   uint8_t companion_name[21];
   uint8_t companionDefRank;
   uint8_t companionAttRank;
   uint8_t companionHealRank;
   uint8_t mountGuideMask[15];
   uint8_t fishingGuideMask[89];
   uint8_t fishingSpotVisited[25];
   uint16_t fishingRecordsFish[26];
   uint16_t fishingRecordsFishWeight[26];
   uint8_t unknownMask554[15];
   uint8_t unknownMask4Padding;
   uint8_t unknown564[19];
   uint8_t rankAmalJaa;
   uint8_t rankSylph;
   uint8_t rankKobold;
   uint8_t rankSahagin;
   uint8_t rankIxal;
   uint8_t rankVanu;
   uint8_t rankVath;
   uint8_t rankMoogle;
   uint8_t rankKojin;
   uint8_t rankAnata;
   uint16_t expAmalJaa;
   uint16_t expSylph;
   uint16_t expKobold;
   uint16_t expSahagin;
   uint16_t expIxal;
   uint16_t expVanu;
   uint16_t expVath;
   uint16_t expMoogle;
   uint16_t expKojin;
   uint16_t expAnata;
   uint8_t unknown596[10];
   uint16_t unknown5A0[5];
   uint8_t unknownMask59E[5];
   uint8_t unknown5A3[18];
   uint8_t unknownMask5C1[28];
   uint8_t unknown_03411;
   uint32_t unknownDword5E0;
   uint8_t relicBookCompletion[12];
   uint8_t sightseeingMask[26];
   uint16_t unknown_XXX;
   uint32_t pvpFrontlineOverall1st;
   uint32_t pvpFrontlineOverall2nd;
   uint32_t pvpFrontlineOverall3rd;
   uint16_t pvpFrontlineWeekly1st;
   uint16_t pvpFrontlineWeekly2nd;
   uint16_t pvpFrontlineWeekly3rd;
   uint8_t unknown61E;
   uint8_t centurioSealHunts[32];
   uint8_t alliedSealHunts[22];
   uint8_t tripleTriadCards[28];
   uint8_t unknown671[11];
   uint8_t unknownMask67C[22];
   uint8_t unknown692[3];
   uint8_t orchestrionMask[40];
   uint8_t hallOfNoviceCompleteMask[3];
   uint8_t unknownMask6C0[11];
   uint8_t animaRelicMask[16]; // [2] = anima glass key item, [1] = ulan's note key item
   uint8_t unknown6DB[14];
   uint8_t unlockedRaids[28];
   uint8_t unlockedDungeons[18];
   uint8_t unlockedGuildhests[10];
   uint8_t unlockedTrials[7];
   uint8_t unlockedPvp[5];
   uint8_t unknownMask72D[28];
   uint8_t unknownMask749[18];
   uint8_t unknown749[23];
};

/**
* Structural representation of the packet sent by the server
* to set a players stats
*/
struct FFXIVIpcPlayerStats : FFXIVIpcBasePacket<PlayerStats>
{
   uint32_t strength;
   uint32_t dexterity;
   uint32_t vitality;
   uint32_t intelligence;
   uint32_t mind;
   uint32_t piety;
   uint32_t hp;
   uint32_t mp;
   uint32_t tp;
   uint32_t unknown;
   uint32_t unknown_1;
   uint32_t unknown_2;
   uint32_t tenacity;
   uint32_t attack;
   uint32_t defense;
   uint32_t accuracy;
   uint32_t spellSpeed;
   uint32_t magicDefense;
   uint32_t criticalHitRate;
   uint32_t resistanceSlashing;
   uint32_t resistancePiercing;
   uint32_t resistanceBlunt;
   uint32_t attackMagicPotency;
   uint32_t healingMagicPotency;
   uint32_t fire;
   uint32_t ice;
   uint32_t wind;
   uint32_t earth;
   uint32_t lightning;
   uint32_t water;
   uint32_t determination;
   uint32_t skillSpeed;
   uint32_t spellSpeed1;
   uint32_t spellSpeedMod;
   uint32_t unknown_6;
   uint32_t craftsmanship;
   uint32_t control;
   uint32_t gathering;
   uint32_t perception;
   uint32_t resistanceSlow;
   uint32_t resistanceSilence;
   uint32_t resistanceBlind;
   uint32_t resistancePoison;
   uint32_t resistanceStun;
   uint32_t resistanceSleep;
   uint32_t resistanceBind;
   uint32_t resistanceHeavy;
   uint32_t unknown_7[9]; // possibly level sync stats.
};

/**
* Structural representation of the packet sent by the server
* to set an actors current owner
*/
struct FFXIVIpcActorOwner : FFXIVIpcBasePacket<ActorOwner>
{
   uint8_t type;
   uint8_t padding[7];
   uint32_t actorId;
   uint32_t actorId2;
};

/**
* Structural representation of the packet sent by the server
* to set a players state
*/
struct FFXIVIpcPlayerStateFlags : FFXIVIpcBasePacket<PlayerStateFlags>
{
   uint8_t flags[12];
   uint32_t padding;
};

/**
* Structural representation of the packet sent by the server
* containing current class information
*/
struct FFXIVIpcPlayerClassInfo : FFXIVIpcBasePacket<PlayerClassInfo>
{
   uint16_t classId;
   uint8_t unknown;
   uint8_t isSpecialist;
   uint16_t level;   // Locks actions, equipment, prob more
   uint16_t level1;  // Locks roles, prob more
   uint32_t roleActions[10];
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcModelEquip : FFXIVIpcBasePacket<ModelEquip>
{
   /* 0000 */ uint64_t mainWeapon;
   /* 0008 */ uint64_t offWeapon;
   /* 0010 */ uint32_t padding1;
   /* 0014 */ uint32_t models[10];
   /* 003C */ uint32_t padding2;
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcItemInfo : FFXIVIpcBasePacket<ItemInfo>
{
   uint32_t sequence;
   uint32_t unknown;
   uint16_t containerId;
   uint16_t slot;
   uint32_t quantity;
   uint32_t catalogId;
   uint32_t reservedFlag;
   uint64_t signatureId;
   uint8_t hqFlag;
   uint8_t unknown2;
   uint16_t condition;
   uint16_t spiritBond;
   uint16_t color;
   uint32_t glamourCatalogId;
   uint16_t materia1;
   uint16_t materia2;
   uint16_t materia3;
   uint16_t materia4;
   uint16_t materia5;
   uint8_t buffer1;
   uint8_t buffer2;
   uint8_t buffer3;
   uint8_t buffer4;
   uint8_t buffer5;
   uint8_t padding;
   uint32_t unknown10;
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcContainerInfo : FFXIVIpcBasePacket<ContainerInfo>
{
   uint32_t sequence;
   uint32_t numItems;
   uint32_t containerId;
   uint32_t unknown;
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcCurrencyCrystalInfo : FFXIVIpcBasePacket<CurrencyCrystalInfo>
{
   uint32_t sequence;
   uint16_t containerId;
   uint16_t slot;
   uint32_t quantity;
   uint32_t unknown;
   uint32_t catalogId;
   uint32_t unknown1;
   uint32_t unknown2;
   uint32_t unknown3;
};

struct FFXIVIpcInventoryTransactionFinish : FFXIVIpcBasePacket<InventoryTransactionFinish>
{
   uint32_t transactionId;
   uint32_t transactionId1;
   uint64_t padding;
};

struct FFXIVIpcInventoryTransaction : FFXIVIpcBasePacket<InventoryTransaction>
{
   uint32_t transactionId;
   uint8_t type;
   uint8_t padding;
   uint16_t padding1;
   uint32_t ownerId;
   uint32_t storageId;
   uint16_t slotId;
   uint16_t padding2;
   uint32_t stackSize;
   uint32_t catalogId;
   uint32_t someActorId;
   int32_t targetStorageId;
   uint32_t padding3[3];
};


struct FFXIVIpcInventoryActionAck : FFXIVIpcBasePacket<InventoryActionAck>
{
   uint32_t sequence;
   uint16_t type;
   uint16_t padding;
   uint32_t padding1;
   uint32_t padding2;
};


/**
* Structural representation of the packet sent by the server
* to update a slot in the inventory
*/
struct FFXIVIpcUpdateInventorySlot : FFXIVIpcBasePacket<UpdateInventorySlot>
{
   uint32_t sequence;
   uint32_t unknown;
   uint16_t containerId;
   uint16_t slot;
   uint32_t quantity;
   uint32_t catalogId;
   uint32_t reservedFlag;
   uint64_t signatureId;
   uint16_t hqFlag;
   uint16_t condition;
   uint16_t spiritBond;
   uint16_t color;
   uint32_t glamourCatalogId;
   uint16_t materia1;
   uint16_t materia2;
   uint16_t materia3;
   uint16_t materia4;
   uint16_t materia5;
   uint8_t buffer1;
   uint8_t buffer2;
   uint8_t buffer3;
   uint8_t buffer4;
   uint8_t buffer5;
   uint8_t padding;
   uint32_t unknown10;
};

/**
* Structural representation of the packet sent by the server
* to start an event, not actually playing it, but registering
*/
struct FFXIVIpcEventStart : FFXIVIpcBasePacket<EventStart>
{
   /* 0000 */ uint64_t actorId;
   /* 0008 */ uint32_t eventId;
   /* 000C */ uint8_t param1;
   /* 000D */ uint8_t param2;
   /* 000E */ uint16_t padding;
   /* 0010 */ uint32_t param3;
   /* 0014 */ uint32_t padding1;
};


/**
* Structural representation of the packet sent by the server
* to play an event
*/
struct FFXIVIpcEventPlay : FFXIVIpcBasePacket<EventPlay>
{
   uint64_t actorId;
   uint32_t eventId;
   uint16_t scene;
   uint16_t padding;
   uint32_t flags;
   uint32_t param3;
   uint8_t param4;
   uint8_t padding1[3];
   uint32_t param5;
   uint8_t unknown[8];
};

   /**
* Structural representation of the packet sent by the server
* to play an event
*/
struct FFXIVIpcDirectorPlayScene : FFXIVIpcBasePacket<DirectorPlayScene>
{
   uint64_t actorId;
   uint32_t eventId;
   uint16_t scene;
   uint16_t padding;
   uint32_t flags;
   uint32_t param3;
   uint8_t param4;
   uint8_t padding1[3];
   uint32_t param5;
   uint8_t unknown8[0x08];
   uint8_t unknown[0x38];
};

/**
* Structural representation of the packet sent by the server
* to finish an event
*/
struct FFXIVIpcEventFinish : FFXIVIpcBasePacket<EventFinish>
{
   /* 0000 */ uint32_t eventId;
   /* 0004 */ uint8_t param1;
   /* 0005 */ uint8_t param2;
   /* 0006 */ uint16_t padding;
   /* 0008 */ uint32_t param3;
   /* 000C */ uint32_t padding1;
};


/**
* Structural representation of the packet sent by the server
* to respond to a linkshell creation event
*/
struct FFXIVIpcEventLinkshell : FFXIVIpcBasePacket<EventLinkshell>
{
   uint32_t eventId;
   uint8_t scene;
   uint8_t param1;
   uint8_t param2;
   uint8_t param3;
   uint32_t unknown1;
   uint32_t unknown2;
   uint32_t unknown3;
   uint32_t unknown4;
};

/**
* Structural representation of the packet sent by the server
* to send the active quests
*/
struct FFXIVIpcQuestActiveList : FFXIVIpcBasePacket<QuestActiveList>
{
   Common::QuestActive activeQuests[30];
};

/**
* Structural representation of the packet sent by the server
* to send update a quest slot
*/
struct FFXIVIpcQuestUpdate : FFXIVIpcBasePacket<QuestUpdate>
{
   uint16_t slot;
   uint16_t padding;
   Common::QuestActive questInfo;
};

/**
* Structural representation of the packet sent by the server
* to send the completed quests mask
*/
struct FFXIVIpcQuestCompleteList : FFXIVIpcBasePacket<QuestCompleteList>
{
   uint8_t questCompleteMask[396];
   uint8_t unknownCompleteMask[32];
};

/**
* Structural representation of the packet sent by the server
* to finish a quest
*/
struct FFXIVIpcQuestFinish : FFXIVIpcBasePacket<QuestFinish>
{
   uint16_t questId;
   uint8_t flag1;
   uint8_t flag2;
   uint32_t padding;
};

/**
* Structural representation of the packet sent by the server
* to send a quest message
* type 0 default
* type 1 icon
* type 5 status
*/
struct FFXIVIpcQuestMessage : FFXIVIpcBasePacket<QuestMessage>
{
   /* 0000 */ uint32_t questId;
   /* 0000 */ uint8_t msgId;
   /* 0000 */ uint8_t type;
   /* 0000 */ uint16_t padding1;
   /* 0000 */ uint32_t var1;
   /* 0000 */ uint32_t var2;
};

struct FFXIVIpcQuestTracker : FFXIVIpcBasePacket<QuestTracker>
{
   struct TrackerEntry
   {
      uint8_t active;
      uint8_t questIndex;
   } entry[5];
   uint16_t padding[3];
};


struct FFXIVIpcWeatherChange : FFXIVIpcBasePacket<WeatherChange>
{
   uint32_t weatherId;
   float delay;
};

/**
* Structural representation of the packet sent by the server
* to send a unviel a map
*/
struct FFXIVIpcDiscovery : FFXIVIpcBasePacket<Discovery>
{
   /* 0000 */ uint32_t map_part_id;
   /* 0004 */ uint32_t map_id;
};


/**
* UNKOWN TYPE
*/
struct FFXIVARR_IPC_UNK322 : FFXIVIpcBasePacket<IPCTYPE_UNK_322>
{
   /* 0000 */ uint8_t unk[8];
};

/**
* UNKOWN TYPE
*/
struct FFXIVARR_IPC_UNK320 : FFXIVIpcBasePacket<IPCTYPE_UNK_320>
{
   /* 0000 */ uint8_t unk[0x38];
};

/**
* Structural representation of the packet sent by the server
* prepare zoning, showing screenmessage
*/
struct FFXIVIpcPrepareZoning : FFXIVIpcBasePacket<PrepareZoning>
{
   uint32_t logMessage;
   uint16_t targetZone;
   uint16_t animation;
   uint8_t param4;
   uint8_t hideChar;
   uint8_t fadeOut;
   uint8_t param7;
   uint8_t fadeOutTime;
   uint8_t unknown;
   uint16_t padding;
};

/**
* Structural representation of the packet sent by the server
* to trigger content finder events
*
* See https://gist.github.com/Minoost/c35843c4c8a7a931f31fdaac9bce64c2
*/
struct FFXIVIpcCFNotify : FFXIVIpcBasePacket<CFNotify>
{
    uint32_t state1; // 3 = cancelled, 4 = duty ready
    uint32_t state2; // if state1 == 3, state2 is cancelled reason

    uint32_t param1; // usually classJobId
    uint32_t param2; // usually flag
    uint32_t param3; // usually languages, sometimes join in progress timestamp

    uint16_t param4; // usually roulette id
    uint16_t contents[5];
};

/**
* Structural representation of the packet sent by the server
* to update contents available in duty finder or raid finder
*
* Do note that this packet has to come early in login phase (around initui packet)
* or it won't be applied until you reconnect
*/
struct FFXIVIpcCFAvailableContents : FFXIVIpcBasePacket<CFAvailableContents>
{
    uint8_t contents[0x48];
};

/**
* Structural representation of the packet sent by the server
* to update adventure in needs in duty roulette
*/
struct FFXIVIpcCFPlayerInNeed : FFXIVIpcBasePacket<CFPlayerInNeed>
{
    // Ordered by roulette id
    uint8_t inNeeds[0x10];
};

/**
* Structural representation of the packet sent by the server
* to update duty info in general
*/
struct FFXIVIpcCFDutyInfo : FFXIVIpcBasePacket<CFDutyInfo>
{
    uint8_t penaltyTime;
    uint8_t unknown[7];
};

struct FFXIVIpcCFRegisterDuty : FFXIVIpcBasePacket<CFRegisterDuty>
{
    uint32_t unknown0; // 0x301
    uint8_t rouletteId; // if it's a daily roulette
    uint8_t unknown1; // 0xDB
    uint16_t contentId;
};


struct FFXIVIpcCFMemberStatus : FFXIVIpcBasePacket<CFMemberStatus>
{
   uint16_t contentId;
   uint16_t unknown1;
   uint8_t status;
   uint8_t currentTank;
   uint8_t currentDps;
   uint8_t currentHealer;
   uint8_t estimatedTime;
   uint8_t unknown2[3];
   uint32_t unknown3;
};

struct FFXIVIpcEorzeaTimeOffset : FFXIVIpcBasePacket<EorzeaTimeOffset>
{
   uint64_t timestamp;
};

/**
* Structural representation of the packet sent by the server
* to set the gear show/hide status of a character
*/
struct FFXIVIpcEquipDisplayFlags : FFXIVIpcBasePacket<EquipDisplayFlags>
{
   uint8_t bitmask;
};

/**
* Structural representation of the packet sent by the server
* to mount a player
*/
struct FFXIVIpcMount : FFXIVIpcBasePacket<Mount>
{
   uint32_t id;
};

/**
* Structural representation of the packet sent by the server
* to mount a player
*/
struct FFXIVIpcDirectorVars : FFXIVIpcBasePacket<DirectorVars>
{
   /*! DirectorType | ContentId */
   uint32_t m_directorId;
   /*! currect sequence */
   uint8_t m_sequence;
   /*! current branch */
   uint8_t m_branch;
   /*! raw storage for flags/vars */
   uint8_t m_unionData[10];
};


struct FFXIVIpcActorGauge : FFXIVIpcBasePacket<ActorGauge>
{
   uint8_t classJobId;
   uint8_t data[15]; // depends on classJobId
};

struct FFXIVIpcPerformNote : FFXIVIpcBasePacket<PerformNote>
{
   uint8_t data[32];
};

struct FFXIVIpcMSQTrackerProgress : FFXIVIpcBasePacket<MSQTrackerProgress>
{
   uint32_t id;
   uint32_t padding;
};

struct FFXIVIpcMSQTrackerComplete : FFXIVIpcBasePacket<MSQTrackerComplete>
{
   uint32_t id;
   uint32_t padding1;
   uint64_t padding2;
   uint64_t padding3;
   uint64_t padding4; // last 4 bytes is uint32_t but who cares
};

struct FFXIVIpcObjectSpawn : FFXIVIpcBasePacket<ObjectSpawn>
{
   uint8_t spawnIndex;
   uint8_t objKind;
   uint8_t state;
   uint8_t unknown3;
   uint32_t objId;
   uint32_t actorId;
   uint32_t levelId;
   uint32_t unknown10;
   uint32_t someActorId14;
   uint32_t gimmickId;
   float scale;
   int16_t unknown20a;
   uint16_t rotation;
   int16_t unknown24a;
   int16_t unknown24b;
   uint16_t unknown28a;
   int16_t unknown28c;
   uint32_t unknown2C;
   Common::FFXIVARR_POSITION3 position;
   int16_t unknown3C;
   int16_t unknown3E;
};

struct FFXIVIpcObjectDespawn : FFXIVIpcBasePacket<ObjectDespawn>
{
   uint8_t spawnIndex;
   uint8_t padding[7];
};

struct FFXIVIpcDuelChallenge : FFXIVIpcBasePacket<DuelChallenge>
{
   uint8_t otherClassJobId;
   uint8_t otherLevel; // class job level
   uint8_t challengeByYou; // 0 if the other challenges you, 1 if you challenges the other.
   uint8_t otherItemLevel;

   uint32_t otherActorId;

   char otherName[32];
};


} /* Server */
} /* Packets */
} /* Network */
} /* Core */



#endif /*_CORE_NETWORK_PACKETS_SERVER_IPC_H*/
