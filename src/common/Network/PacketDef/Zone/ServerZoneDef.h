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

namespace Sapphire {
namespace Network {
namespace Packets {
namespace Server {

/**
* Structural representation of the packet sent by the server as response
* to a ping packet
*/
struct FFXIVIpcPing :
  FFXIVIpcBasePacket< Ping >
{
  /* 0000 */ uint64_t timeInMilliseconds;
  /* 0008 */ uint8_t unknown_8[0x38];
};

/**
* Structural representation of the packet sent by the server as response
* to a ping packet
*/
struct FFXIVIpcInit :
  FFXIVIpcBasePacket< Init >
{
  uint64_t unknown;
  uint32_t charId;
  uint32_t unknown1;
};

/**
* Structural representation of the packet sent by the server
* carrying chat messages
*/
struct FFXIVIpcChat :
  FFXIVIpcBasePacket< Chat >
{
  /* 0000 */  uint8_t padding[14]; //Maybe this is SubCode, or some kind of talker ID...
  Common::ChatType chatType;
  char name[32];
  char msg[1012];
};

struct FFXIVIpcChatBanned :
  FFXIVIpcBasePacket< ChatBanned >
{
  uint8_t padding[4]; // I was not sure reinterpreting ZST is valid behavior in C++.
  // client doesn't care about the data (zero sized) for this opcode anyway.
};

/**
* Structural representation of the packet sent by the server
* carrying chat messages
*/
struct FFXIVIpcLogout :
  FFXIVIpcBasePacket< Logout >
{
  uint32_t flags1;
  uint32_t flags2;
};

/**
* Structural representation of the packet sent by the server
* sent to show the play time
*/
struct FFXIVIpcPlayTime :
  FFXIVIpcBasePacket< Playtime >
{
  uint32_t playTimeInMinutes;
  uint32_t padding;
};


/**
* Structural representation of the packet sent by the server
* with a list of players ( party list | friend list | search results )
*/
struct PlayerEntry
{
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

struct FFXIVIpcSocialList :
  FFXIVIpcBasePacket< SocialList >
{
  uint32_t padding;
  uint32_t padding1;
  uint32_t padding2;
  uint8_t type;
  uint8_t sequence;
  uint16_t padding3;

  PlayerEntry entries[10];
};


struct FFXIVIpcSetSearchInfo :
  FFXIVIpcBasePacket< UpdateSearchInfo >
{
  uint64_t onlineStatusFlags;
  uint64_t unknown;
  uint32_t unknown1;
  uint8_t padding;
  uint8_t selectRegion;
  char searchMessage[193];
  uint8_t padding2;
};

struct FFXIVIpcInitSearchInfo :
  FFXIVIpcBasePacket< InitSearchInfo >
{
  uint64_t onlineStatusFlags;
  uint64_t unknown;
  uint8_t unknown1;
  uint8_t selectRegion;
  char searchMessage[193];
  char padding[5];
};

struct FFXIVIpcExamineSearchComment :
  FFXIVIpcBasePacket< ExamineSearchComment >
{
  uint32_t charId;
  // packet only has 196 bytes after the charid
  // likely utf8
  char searchComment[195];
  char padding;
};

/**
* Structural representation of the packet sent by the server
* to display a server notice message
*/
struct FFXIVIpcServerNotice :
  FFXIVIpcBasePacket< ServerNotice >
{
  /* 0000 */ uint8_t padding;
  char message[775];
};

struct FFXIVIpcSetOnlineStatus :
  FFXIVIpcBasePacket< SetOnlineStatus >
{
  uint64_t onlineStatusFlags;
};

struct FFXIVIpcBlackList :
  FFXIVIpcBasePacket< BlackList >
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

struct FFXIVIpcLogMessage :
  FFXIVIpcBasePacket< LogMessage >
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

struct FFXIVIpcLinkshellList :
  FFXIVIpcBasePacket< LinkshellList >
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

/**
* Structural representation of the packet sent by the server
* to send a list of mail the player has
*/
struct FFXIVIpcReqMoogleMailList :
  FFXIVIpcBasePacket< ReqMoogleMailList >
{
  struct letterEntry
  {
    char unk[0x8];
    uint32_t timeStamp; // The time the mail was sent (this also seems to be used as a Id)
    char unk1[0x30]; // This should be items, gil, etc for the letter
    uint8_t read; // 0 = false | 1 = true
    uint8_t type; // 0 = Friends | 1 = Rewards | 2 = GM
    uint8_t unk2;
    char senderName[0x20]; // The name of the sender
    char summary[0x3C]; // The start of the full letter text
    char padding2[0x5];
  } letter[5];
  char unk3[0x08];
};

/**
* Structural representation of the packet sent by the server
* to show the mail delivery notification
*/
struct FFXIVIpcMailLetterNotificationt :
  FFXIVIpcBasePacket< MailLetterNotification >
{
  uint32_t sendbackCount; // The amount of letters sent back since you ran out of room (moogle dialog changes based on this)
  uint16_t friendLetters; // The amount of letters in the friends section of the letterbox
  uint16_t unreadCount; // The amount of unreads in the letterbox (this is the number that shows up)
  uint16_t rewardLetters; // The amount of letters in the rewards section of the letterbox
  uint8_t isGmLetter; // Makes the letter notification flash red
  uint8_t isSupportDesk; // After setting this to 1 we can no longer update mail notifications (more research needed on the support desk)
  char unk2[0x4]; // This has probs something to do with the support desk (inquiry id?)
};

struct FFXIVIpcExamineFreeCompanyInfo :
  FFXIVIpcBasePacket< ExamineFreeCompanyInfo >
{
  char unknown[0x20]; // likely fc allegiance/icon/housing info etc
  uint32_t charId;
  uint32_t fcTimeCreated;
  char unknown2[0x10];
  uint16_t unknown3;
  char fcName[0x14]; // 20 char limit
  uint16_t padding;
  char fcTag[0x05]; // 5 char tag limit
  uint16_t padding2; // null terminator?
  char fcLeader[0x20]; // leader name (32 bytes)
  char fcSlogan[192]; // source: https://ffxiv.gamerescape.com/wiki/Free_Company (packet cap confirms this size also)
  char padding3; // null terminator?
  char fcEstateProfile[20]; // todo: size needs confirmation
  uint32_t padding4;
};

struct FFXIVIpcStatusEffectList :
  FFXIVIpcBasePacket< StatusEffectList >
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

struct FFXIVGCAffiliation :
  FFXIVIpcBasePacket< GCAffiliation >
{
  uint8_t gcId;
  uint8_t gcRank[3];
};

/**
* Structural representation of the packet sent by the server
* add a status effect
*/
struct FFXIVIpcAddStatusEffect :
  FFXIVIpcBasePacket< AddStatusEffect >
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
struct FFXIVIpcActorControl142 :
  FFXIVIpcBasePacket< ActorControl142 >
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
struct FFXIVIpcActorControl143 :
  FFXIVIpcBasePacket< ActorControl143 >
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
struct FFXIVIpcActorControl144 :
  FFXIVIpcBasePacket< ActorControl144 >
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
struct FFXIVIpcUpdateHpMpTp :
  FFXIVIpcBasePacket< UpdateHpMpTp >
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
struct EffectEntry
{
  Common::ActionEffectType effectType;
  Common::ActionHitSeverityType hitSeverity;
  uint8_t param;
  int8_t bonusPercent; // shows an additional percentage in the battle log, will not change the damage number sent & shown
  uint8_t valueMultiplier;      // This multiplies whatever value is in the 'value' param by 10. Possibly a workaround for big numbers
  uint8_t flags;
  int16_t value;
};

struct EffectHeader
{
  uint64_t animationTargetId; // who the animation targets

  uint32_t actionId; // what the casting player casts, shown in battle log/ui
  uint32_t globalEffectCounter; // seems to only increment on retail?

  float animationLockTime; // maybe? doesn't seem to do anything
  uint32_t someTargetId; // always 00 00 00 E0, 0x0E000000 is the internal def for INVALID TARGET ID

  uint16_t hiddenAnimation; // if 0, always shows animation, otherwise hides it. counts up by 1 for each animation skipped on a caster
  uint16_t rotation;
  uint16_t actionAnimationId; // the animation that is played by the casting character
  uint8_t variation; // variation in the animation
  Common::ActionEffectDisplayType effectDisplayType;

  uint8_t unknown20; // is read by handler, runs code which gets the LODWORD of animationLockTime (wtf?)
  uint8_t effectCount; // ignores effects if 0, otherwise parses all of them
  uint16_t padding_21;

};

struct FFXIVIpcEffect : FFXIVIpcBasePacket< Effect >
{
  uint64_t animationTargetId; // who the animation targets

  uint32_t actionId; // what the casting player casts, shown in battle log/ui
  uint32_t globalEffectCounter; // seems to only increment on retail?

  float animationLockTime; // maybe? doesn't seem to do anything
  uint32_t someTargetId; // always 00 00 00 E0, 0x0E000000 is the internal def for INVALID TARGET ID

  uint16_t hiddenAnimation; // if 0, always shows animation, otherwise hides it. counts up by 1 for each animation skipped on a caster
  uint16_t rotation;
  uint16_t actionAnimationId; // the animation that is played by the casting character
  uint8_t variation; // variation in the animation
  Common::ActionEffectDisplayType effectDisplayType;

  uint8_t unknown20; // is read by handler, runs code which gets the LODWORD of animationLockTime (wtf?)
  uint8_t effectCount; // ignores effects if 0, otherwise parses all of them
  uint16_t padding_21;

  uint16_t padding_22[3];

  uint8_t effects[8*8];

  uint16_t padding_6A[3];

  uint32_t effectTargetId; // who the effect targets
  uint32_t effectFlags; // nonzero = effects do nothing, no battle log, no ui text - only shows animations

  uint32_t padding_78;
};

template< int size >
struct FFXIVIpcAoeEffect
{
  EffectHeader header;

  EffectEntry effects[size];

  uint16_t padding_6A[3];

  uint32_t effectTargetId[size];
  Common::FFXIVARR_POSITION3 position;
  uint32_t effectFlags;

  uint32_t padding_78;
};

struct FFXIVIpcAoeEffect8 :
  FFXIVIpcBasePacket< AoeEffect8 >, FFXIVIpcAoeEffect< 8 >
{
};
struct FFXIVIpcAoeEffect16 :
  FFXIVIpcBasePacket< AoeEffect16 >, FFXIVIpcAoeEffect< 16 >
{
};
struct FFXIVIpcAoeEffect24 :
  FFXIVIpcBasePacket< AoeEffect24 >, FFXIVIpcAoeEffect< 24 >
{
};
struct FFXIVIpcAoeEffect32 :
  FFXIVIpcBasePacket< AoeEffect32 >, FFXIVIpcAoeEffect< 32 >
{
};


/**
* Structural representation of the packet sent by the server
* to spawn an actor
*/
struct FFXIVIpcPlayerSpawn :
  FFXIVIpcBasePacket< PlayerSpawn >
{
  uint16_t title;
  uint16_t u1b;
  uint16_t currentWorldId;
  uint16_t homeWorldId;

  uint8_t gmRank;
  uint8_t u3c;
  uint8_t u4;
  uint8_t onlineStatus;

  uint8_t pose;
  uint8_t u5a;
  uint8_t u5b;
  uint8_t u5c;

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
  uint8_t persistentEmote;
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
* to spawn an actor
*/
struct FFXIVIpcNpcSpawn :
  FFXIVIpcBasePacket< NpcSpawn >
{
  uint32_t gimmickId; // needs to be existing in the map, mob will snap to it
  uint8_t u2b;
  uint8_t u2ab;
  uint8_t gmRank;
  uint8_t u3b;

  uint8_t aggressionMode; // 1 passive, 2 aggressive
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
  uint32_t spawnerId;
  uint32_t parentActorId;
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
  uint32_t unk31;
  uint8_t bNPCPartSlot;
  uint8_t unk32;
  uint16_t unk33;
  uint32_t unk34;
};

/**
* Structural representation of the packet sent by the server
* to show player movement
*/
struct FFXIVIpcActorFreeSpawn :
  FFXIVIpcBasePacket< ActorFreeSpawn >
{
  uint32_t spawnId;
  uint32_t actorId;
};

/**
* Structural representation of the packet sent by the server
* to show player movement
*/
struct FFXIVIpcActorMove :
  FFXIVIpcBasePacket< ActorMove >
{
  /* 0000 */ uint8_t rotation;
  /* 0001 */ uint8_t unknown_1;
  /* 0002 */ uint8_t animationType;
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
struct FFXIVIpcActorSetPos :
  FFXIVIpcBasePacket< ActorSetPos >
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
struct FFXIVIpcActorCast : FFXIVIpcBasePacket< ActorCast >
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

struct FFXIVIpcHateList : FFXIVIpcBasePacket< HateList >
{
  uint32_t numEntries;
  struct
  {
    uint32_t actorId;
    uint8_t hatePercent;
    uint8_t unknown;
    uint16_t padding;
  } entry[32];
  uint32_t padding;
};

struct FFXIVIpcUpdateClassInfo : FFXIVIpcBasePacket< UpdateClassInfo >
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
struct FFXIVIpcPlayerTitleList : FFXIVIpcBasePacket< PlayerTitleList >
{
  uint8_t titleList[48];
};

/**
* Structural representation of the packet sent by the server
* to initialize a zone for the player
*/
struct FFXIVIpcInitZone : FFXIVIpcBasePacket< InitZone >
{
  uint16_t serverId;
  uint16_t zoneId;
  uint16_t unknown1;
  uint16_t unknown2;
  uint32_t unknown3;
  uint32_t unknown4;
  uint8_t weatherId;
  uint8_t bitmask;
  uint8_t bitmask1;
  uint8_t unknown5;
  uint16_t festivalId;
  uint16_t additionalFestivalId;
  uint32_t unknown8;
  uint32_t unknown9;
  uint32_t unknown10;
  uint32_t unknown11;
  uint32_t unknown12[4];
  Common::FFXIVARR_POSITION3 pos;
  uint32_t unknown13;
};


/**
* Structural representation of the packet sent by the server to initialize
* the client UI upon initial connection.
*/
struct FFXIVIpcInitUI : FFXIVIpcBasePacket< InitUI >
{
  // plain C types for a bit until the packet is actually fixed.
  // makes conversion between different editors easier.
  uint64_t contentId;
  unsigned int unknown8;
  unsigned int unknownC;
  unsigned int charId;
  unsigned int restedExp;
  unsigned int companionCurrentExp;
  unsigned int unknown1C;
  unsigned int fishCaught;
  unsigned int useBaitCatalogId;
  unsigned int unknown28;
  unsigned short unknownPvp2C;
  unsigned short unknown3;
  unsigned int pvpFrontlineOverallCampaigns;
  unsigned int unknownTimestamp34;
  unsigned int unknownTimestamp38;
  unsigned int unknown3C;
  unsigned int unknown40;
  unsigned int unknown44;
  float companionTimePassed;
  unsigned int unknown4C;
  unsigned short unknown50;
  unsigned short unknownPvp52[4];
  unsigned short playerCommendations;
  unsigned short unknown5C;
  unsigned short unknown5E;
  unsigned short pvpFrontlineWeeklyCampaigns;
  unsigned short enhancedAnimaGlassProgress;
  unsigned short unknown64[4];
  unsigned short pvpRivalWingsTotalMatches;
  unsigned short pvpRivalWingsTotalVictories;
  unsigned short pvpRivalWingsWeeklyMatches;
  unsigned short pvpRivalWingsWeeklyVictories;
  unsigned char maxLevel;
  unsigned char expansion;
  unsigned char unknown76;
  unsigned char race;
  unsigned char tribe;
  unsigned char gender;
  unsigned char currentJob;
  unsigned char currentClass;
  unsigned char deity;
  unsigned char namedayMonth;
  unsigned char namedayDay;
  unsigned char cityState;
  unsigned char homepoint;
  unsigned char unknown81;
  unsigned char petHotBar;
  unsigned char companionRank;
  unsigned char companionStars;
  unsigned char companionSp;
  unsigned char companionUnk86;
  unsigned char companionColor;
  unsigned char companionFavoFeed;
  unsigned char unknown89;
  unsigned char unknown8A[4];
  unsigned char hasRelicBook;
  unsigned char relicBookId;
  unsigned char unknown90[4];
  unsigned char craftingMasterMask;
  unsigned char unknown95[10];
  unsigned char unknown9F[2];
  unsigned char unknownA1[3];
  unsigned int exp[26];
  unsigned int unknown108;
  unsigned int pvpTotalExp;
  unsigned int unknownPvp110;
  unsigned int pvpExp;
  unsigned int pvpFrontlineOverallRanks[3];
  unsigned short levels[26];
  unsigned short unknown15C[9];
  unsigned short u1;
  unsigned short u2;
  unsigned short unknown112[23];
  unsigned short fishingRecordsFish[26];
  unsigned short beastExp[11];
  unsigned short unknown1EA[5];
  unsigned short pvpFrontlineWeeklyRanks[3];
  unsigned short unknownMask1FA[4];
  unsigned char companionName[21];
  unsigned char companionDefRank;
  unsigned char companionAttRank;
  unsigned char companionHealRank;
  unsigned char u19[2];
  unsigned char mountGuideMask[17];
  char name[32];
  unsigned char unknownOword[16];
  unsigned char unknownOw;
  unsigned char unlockBitmask[64];
  unsigned char aetheryte[17];
  unsigned char discovery[421];
  unsigned char howto[34];
  unsigned char minions[42];
  unsigned char chocoboTaxiMask[8];
  unsigned char watchedCutscenes[118];
  unsigned char companionBardingMask[9];
  unsigned char companionEquippedHead;
  unsigned char companionEquippedBody;
  unsigned char companionEquippedLegs;
  unsigned char unknown52A[4];
  unsigned char unknownMask52E[11];
  unsigned char fishingGuideMask[89];
  unsigned char fishingSpotVisited[25];
  unsigned char unknown59A[15];
  unsigned char unknown5A9[5];
  unsigned char beastRank[11];
  unsigned char unknownPvp5AB[11];
  unsigned char unknown5B9[5];
  unsigned char unknown5B91;
  unsigned char pose;
  unsigned char challengeLogComplete[9];
  unsigned char weaponPose;
  unsigned char unknownMask673[10];
  unsigned char unknownMask5DD[28];
  unsigned char relicCompletion[12];
  unsigned char sightseeingMask[26];
  unsigned char huntingMarkMask[55];
  unsigned char tripleTriadCards[32];
  unsigned char u12[11];
  unsigned char u13;
  unsigned char aetherCurrentMask[22];
  unsigned char u10[3];
  unsigned char orchestrionMask[40];
  unsigned char hallOfNoviceCompletion[3];
  unsigned char animaCompletion[11];
  unsigned char u14[16];
  unsigned char u15[13];
  unsigned char unlockedRaids[28];
  unsigned char unlockedDungeons[18];
  unsigned char unlockedGuildhests[10];
  unsigned char unlockedTrials[8];
  unsigned char unlockedPvp[5];
  unsigned char clearedRaids[28];
  unsigned char clearedDungeons[18];
  unsigned char clearedGuildhests[10];
  unsigned char clearedTrials[8];
  unsigned char clearedPvp[5];
  unsigned short fishingRecordsFishWeight[26];
  unsigned int exploratoryMissionNextTimestamp;
  unsigned char pvpLevel;
};


/**
* Structural representation of the packet sent by the server
* to set a players stats
*/
struct FFXIVIpcPlayerStats : FFXIVIpcBasePacket< PlayerStats >
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
struct FFXIVIpcActorOwner :
  FFXIVIpcBasePacket< ActorOwner >
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
struct FFXIVIpcPlayerStateFlags :
  FFXIVIpcBasePacket< PlayerStateFlags >
{
  uint8_t flags[12];
  uint32_t padding;
};

/**
* Structural representation of the packet sent by the server
* containing current class information
*/
struct FFXIVIpcPlayerClassInfo :
  FFXIVIpcBasePacket< PlayerClassInfo >
{
  uint16_t classId;
  uint8_t unknown;
  uint8_t isSpecialist;
  uint16_t syncedLevel;   // Locks actions, equipment, prob more. Player's current level (synced).
  uint16_t classLevel;  // Locks roles, prob more. Player's actual unsynced level.
  uint32_t roleActions[10];
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcModelEquip :
  FFXIVIpcBasePacket< ModelEquip >
{
  /* 0000 */ uint64_t mainWeapon;
  /* 0008 */ uint64_t offWeapon;
  /* 0010 */ uint8_t unk1;
  /* 0011 */ uint8_t classJobId;
  /* 0012 */ uint8_t level;
  /* 0013 */ uint8_t unk2;
  /* 0014 */ uint32_t models[10];
  /* 003C */ uint32_t padding2;
};

struct FFXIVIpcExamine :
  FFXIVIpcBasePacket< Examine >
{
  uint8_t unkFlag1;
  uint8_t unkFlag2;
  char classJob;
  char level;
  uint16_t padding;
  uint16_t titleId;
  char grandCompany;
  char grandCompanyRank;

  char unknown[6];
  uint32_t u6_fromPSpawn;
  uint32_t u7_fromPSpawn;
  char padding1[8];
  uint64_t mainWeaponModel;
  uint64_t secWeaponModel;
  char unknown2[16];
  struct ItemData
  {
    uint32_t catalogId;
    uint32_t appearanceCatalogId;
    uint64_t crafterId;
    uint8_t quality;
    uint8_t unknown[3];
    struct Materia
    {
      uint16_t materiaId;
      uint16_t tier;
    } materia[5];
  } entries[14];
  char name[32];
  char padding2;
  char unk3[16];
  char look[26];
  char padding3[5];
  uint32_t models[10];
  char unknown4[200];
};

struct FFXIVIpcCharaNameReq :
  FFXIVIpcBasePacket< CharaNameReq >
{
  uint64_t contentId;
  char name[32];
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcItemInfo :
  FFXIVIpcBasePacket< ItemInfo >
{
  uint32_t containerSequence;
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
  uint16_t stain;
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
struct FFXIVIpcContainerInfo :
  FFXIVIpcBasePacket< ContainerInfo >
{
  uint32_t containerSequence;
  uint32_t numItems;
  uint32_t containerId;
  uint32_t unknown;
};

/**
* Structural representation of the packet sent by the server
* to update a players appearance
*/
struct FFXIVIpcCurrencyCrystalInfo :
  FFXIVIpcBasePacket< CurrencyCrystalInfo >
{
  uint32_t containerSequence;
  uint16_t containerId;
  uint16_t slot;
  uint32_t quantity;
  uint32_t unknown;
  uint32_t catalogId;
  uint32_t unknown1;
  uint32_t unknown2;
  uint32_t unknown3;
};

struct FFXIVIpcInventoryTransactionFinish :
  FFXIVIpcBasePacket< InventoryTransactionFinish >
{
  uint32_t transactionId;
  uint32_t transactionId1;
  uint64_t padding;
};

struct FFXIVIpcInventoryTransaction :
  FFXIVIpcBasePacket< InventoryTransaction >
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


struct FFXIVIpcInventoryActionAck :
  FFXIVIpcBasePacket< InventoryActionAck >
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
struct FFXIVIpcUpdateInventorySlot :
  FFXIVIpcBasePacket< UpdateInventorySlot >
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
struct FFXIVIpcEventStart :
  FFXIVIpcBasePacket< EventStart >
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
struct FFXIVIpcEventPlay :
  FFXIVIpcBasePacket< EventPlay >
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
struct FFXIVIpcDirectorPlayScene :
  FFXIVIpcBasePacket< DirectorPlayScene >
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
struct FFXIVIpcEventFinish :
  FFXIVIpcBasePacket< EventFinish >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint8_t param1;
  /* 0005 */ uint8_t param2;
  /* 0006 */ uint16_t padding;
  /* 0008 */ uint32_t param3;
  /* 000C */ uint32_t padding1;
};

struct FFXIVIpcEventOpenGilShop :
  FFXIVIpcBasePacket< EventOpenGilShop >
{
  uint64_t actorId;
  uint32_t eventId;
  uint16_t scene;
  uint16_t padding;
  uint32_t sceneFlags;

  uint32_t unknown_wtf[0x101];
};


/**
* Structural representation of the packet sent by the server
* to respond to a linkshell creation event
*/
struct FFXIVIpcEventLinkshell :
  FFXIVIpcBasePacket< EventLinkshell >
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
struct FFXIVIpcQuestActiveList :
  FFXIVIpcBasePacket< QuestActiveList >
{
  Common::QuestActive activeQuests[30];
};

/**
* Structural representation of the packet sent by the server
* to send update a quest slot
*/
struct FFXIVIpcQuestUpdate :
  FFXIVIpcBasePacket< QuestUpdate >
{
  uint16_t slot;
  uint16_t padding;
  Common::QuestActive questInfo;
};

/**
* Structural representation of the packet sent by the server
* to send the completed quests mask
*/
struct FFXIVIpcQuestCompleteList :
  FFXIVIpcBasePacket< QuestCompleteList >
{
  uint8_t questCompleteMask[480];
  uint8_t unknownCompleteMask[32];
};

/**
* Structural representation of the packet sent by the server
* to finish a quest
*/
struct FFXIVIpcQuestFinish :
  FFXIVIpcBasePacket< QuestFinish >
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
struct FFXIVIpcQuestMessage :
  FFXIVIpcBasePacket< QuestMessage >
{
  /* 0000 */ uint32_t questId;
  /* 0000 */ uint8_t msgId;
  /* 0000 */ uint8_t type;
  /* 0000 */ uint16_t padding1;
  /* 0000 */ uint32_t var1;
  /* 0000 */ uint32_t var2;
};

struct FFXIVIpcQuestTracker :
  FFXIVIpcBasePacket< QuestTracker >
{
  struct TrackerEntry
  {
    uint8_t active;
    uint8_t questIndex;
  } entry[5];
  uint16_t padding[3];
};


struct FFXIVIpcWeatherChange :
  FFXIVIpcBasePacket< WeatherChange >
{
  uint32_t weatherId;
  float delay;
};

/**
* Structural representation of the packet sent by the server
* to send a unviel a map
*/
struct FFXIVIpcDiscovery :
  FFXIVIpcBasePacket< Discovery >
{
  /* 0000 */ uint32_t map_part_id;
  /* 0004 */ uint32_t map_id;
};


/**
* UNKOWN TYPE
*/
struct FFXIVARR_IPC_UNK322 :
  FFXIVIpcBasePacket< IPCTYPE_UNK_322 >
{
  /* 0000 */ uint8_t unk[8];
};

/**
* UNKOWN TYPE
*/
struct FFXIVARR_IPC_UNK320 :
  FFXIVIpcBasePacket< IPCTYPE_UNK_320 >
{
  /* 0000 */ uint8_t unk[0x38];
};

/**
* Structural representation of the packet sent by the server
* prepare zoning, showing screenmessage
*/
struct FFXIVIpcPrepareZoning :
  FFXIVIpcBasePacket< PrepareZoning >
{
  uint32_t logMessage;
  uint16_t targetZone;
  uint16_t animation;
  uint8_t param4;
  uint8_t hideChar;
  uint8_t fadeOut;
  uint8_t param7;
  uint8_t fadeOutTime;
  uint8_t unknown; // this changes whether or not the destination zone's name displays during the loading screen. Seems to always be 9 (=hidden) when going to an instance and certain zones, 0 otherwise.
  uint16_t padding;
};

/**
* Structural representation of the packet sent by the server
* to trigger content finder events
*
* See https://gist.github.com/Minoost/c35843c4c8a7a931f31fdaac9bce64c2
*/
struct FFXIVIpcCFNotify :
  FFXIVIpcBasePacket< CFNotify >
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
struct FFXIVIpcCFAvailableContents :
  FFXIVIpcBasePacket< CFAvailableContents >
{
  uint8_t contents[0x48];
};

/**
* Structural representation of the packet sent by the server
* to update adventure in needs in duty roulette
*/
struct FFXIVIpcCFPlayerInNeed :
  FFXIVIpcBasePacket< CFPlayerInNeed >
{
  // Ordered by roulette id
  uint8_t inNeeds[0x10];
};

/**
* Structural representation of the packet sent by the server
* to update duty info in general
*/
struct FFXIVIpcCFDutyInfo :
  FFXIVIpcBasePacket< CFDutyInfo >
{
  uint8_t penaltyTime;
  uint8_t unknown[7];
};

struct FFXIVIpcCFRegisterDuty :
  FFXIVIpcBasePacket< CFRegisterDuty >
{
  uint32_t unknown0; // 0x301
  uint8_t rouletteId; // if it's a daily roulette
  uint8_t unknown1; // 0xDB
  uint16_t contentId;
};


struct FFXIVIpcCFMemberStatus :
  FFXIVIpcBasePacket< CFMemberStatus >
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

struct FFXIVIpcEorzeaTimeOffset :
  FFXIVIpcBasePacket< EorzeaTimeOffset >
{
  uint64_t timestamp;
};

/**
* Structural representation of the packet sent by the server
* to set the gear show/hide status of a character
*/
struct FFXIVIpcEquipDisplayFlags :
  FFXIVIpcBasePacket< EquipDisplayFlags >
{
  uint8_t bitmask;
};

/**
* Structural representation of the packet sent by the server
* to mount a player
*/
struct FFXIVIpcMount : FFXIVIpcBasePacket< Mount >
{
  uint32_t id;
};

/**
* Structural representation of the packet sent by the server
* to mount a player
*/
struct FFXIVIpcDirectorVars : FFXIVIpcBasePacket< DirectorVars >
{
  /*! DirectorType | ContentId */
  uint32_t m_directorId;
  /*! currect sequence */
  uint8_t m_sequence;
  /*! current branch */
  uint8_t m_branch;
  /*! raw storage for flags/vars */
  uint8_t m_unionData[10];
  /*! unknown */
  uint16_t u20;
  uint16_t u22;
  uint16_t u24;
  uint16_t u28;
};


struct FFXIVIpcActorGauge : FFXIVIpcBasePacket< ActorGauge >
{
  uint8_t classJobId;
  uint8_t data[15]; // depends on classJobId
};

struct FFXIVIpcPerformNote : FFXIVIpcBasePacket< PerformNote >
{
  uint8_t data[32];
};

struct FFXIVIpcHousingUpdateLandFlagsSlot : FFXIVIpcBasePacket< HousingUpdateLandFlagsSlot >
{
  uint32_t type;
  uint32_t unknown;
  Common::LandFlagSet flagSet;
};

struct FFXIVIpcHousingLandFlags : FFXIVIpcBasePacket< HousingLandFlags >
{
  Common::LandFlagSet freeCompanyHouse; // 00
  uint64_t unkown1;
  Common::LandFlagSet privateHouse; // 24
  uint64_t unkown2;
  Common::LandFlagSet apartment; // 48
  uint64_t unkown3;
  Common::LandFlagSet sharedHouse[2]; //72
  uint64_t unkown4;
  Common::LandFlagSet unkownHouse;
  uint64_t unkown5;
};

//Structs
struct LandStruct
{
  uint8_t plotSize; //0
  uint8_t houseState; // 2
  uint8_t flags; // bit1 -> hasPublicAccess; bit2 -> isPersonalHouse
  uint8_t iconAddIcon; // 6
  uint32_t fcId; //8
  uint32_t fcIcon;// 12
  uint32_t fcIconColor; // 16
  uint16_t housePart[ 8 ]; // 34
  uint8_t houseColour[ 8 ]; // 36
};

struct FFXIVIpcLandUpdate : FFXIVIpcBasePacket< LandUpdate >
{
  Common::LandIdent landIdent;
  LandStruct land;
};

struct FFXIVIpcLandPriceUpdate :  FFXIVIpcBasePacket< LandPriceUpdate >
{
  uint32_t price;
  uint32_t timeLeft;
};

struct FFXIVIpcLandInfoSign : FFXIVIpcBasePacket< LandInfoSign >
{
  Common::LandIdent landIdent;
  uint64_t ownerId; // ither contentId or fcId
  uint32_t unknow1;
  uint8_t houseIconAdd;
  uint8_t houseSize;
  uint8_t houseType;
  char estateName[23];
  char estateGreeting[193];
  char ownerName[31];
  char fcTag[7];
  uint8_t tag[3];
};

struct FFXIVIpcLandRename : FFXIVIpcBasePacket< LandRename >
{
  Common::LandIdent landIdent;
  char houseName[20];
  uint32_t padding;
};

struct FFXIVIpcLandUpdateHouseName : FFXIVIpcBasePacket< LandUpdateHouseName >
{
  uint32_t unknown[3];
  char houseName[20];
  uint32_t unknown2[2];
};

struct FFXIVIpcLandSetMap : FFXIVIpcBasePacket< LandSetMap >
{
  uint8_t u1;
  uint8_t subdivision;
  uint8_t u3;
  struct
  {
    uint8_t status;
    uint8_t size;
    uint8_t isPrivate;
  } landInfo[ 30 ];
  uint8_t padding[ 3 ];
};

struct FFXIVIpcLandSetInitialize : FFXIVIpcBasePacket< LandSetInitialize >
{
  Common::LandIdent landIdent;
  uint8_t unknown1;
  uint8_t subInstance; //  (default : 1/2)
  uint8_t unknown3;
  uint8_t unknown4;
  uint8_t unknown5;
  uint8_t unknown6;
  uint8_t unknown7;
  uint8_t unknown8;
  LandStruct land[ 30 ];
};

struct FFXIVIpcYardObjectSpawn : FFXIVIpcBasePacket< YardObjectSpawn >
{
  uint8_t landId;
  uint8_t objectArray;
  uint16_t unknown1;
  Common::HousingObject object;
};

struct FFXIVIpcHousingObjectMove : FFXIVIpcBasePacket< HousingObjectMove >
{
  uint16_t itemRotation;
  uint8_t objectArray;
  uint8_t landId;
  Common::FFXIVARR_POSITION3 pos;
  uint16_t unknown1;
  uint16_t unknown2;
  uint16_t unknown3;
};

struct FFXIVIpcHousingObjectInitialize : FFXIVIpcBasePacket< HousingObjectInitialize >
{
  Common::LandIdent landIdent;
  /*!
   * when this is 2, actrl 0x400 will hide the additional quarters door
   * if it's any other value, it will stay there regardless
   */
  int8_t u1; //Outdoor -1 / Indoor 0 - probably indicator
  uint8_t packetNum;
  uint8_t packetTotal;
  uint8_t u2; //Outdoor 0 / Indoor 100(?)
  Common::HousingObject object[100];
  uint32_t unknown4; //unused
};

struct FFXIVIpcHousingInternalObjectSpawn : FFXIVIpcBasePacket< HousingInternalObjectSpawn >
{
  uint16_t containerId;
  uint8_t containerOffset;
  uint8_t pad1;

  Common::HousingObject object;
};

struct FFXIVIpcHousingIndoorInitialize : FFXIVIpcBasePacket< HousingIndoorInitialize >
{
  uint16_t u1;
  uint16_t u2;
  uint16_t u3;
  uint16_t u4;
  uint32_t indoorItems[10];
};


struct FFXIVIpcHousingWardInfo : FFXIVIpcBasePacket< HousingWardInfo >
{
  Common::LandIdent landIdent;

  struct HouseInfoEntry
  {
    uint32_t housePrice;
    uint8_t infoFlags;
    Common::HousingAppeal houseAppeal[3];
    char estateOwnerName[30];
  } houseInfoEntry[60];
};

struct FFXIVIpcHousingEstateGreeting : FFXIVIpcBasePacket< HousingEstateGreeting >
{
  Common::LandIdent landIdent;
  char message[200];
};

struct FFXIVIpcHousingShowEstateGuestAccess :
  FFXIVIpcBasePacket< HousingShowEstateGuestAccess >
{
  uint32_t unknown[2];
  Common::LandIdent ident;
};

/**
* Structural representation of the packet sent by the server
* to show the current shared estate settings
*/
struct FFXIVIpcSharedEstateSettingsResponse :
  FFXIVIpcBasePacket< SharedEstateSettingsResponse >
{
  struct playerEntry
  {
    uint64_t contentId;
    uint8_t permissions;
    char name[0x20];
    char padding[0x7];
  } entry[3];
};

struct FFXIVIpcMSQTrackerProgress :
  FFXIVIpcBasePacket< MSQTrackerProgress >
{
  uint32_t id;
  uint32_t padding;
};

struct FFXIVIpcMSQTrackerComplete :
  FFXIVIpcBasePacket< MSQTrackerComplete >
{
  uint32_t id;
  uint32_t padding1;
  uint64_t padding2;
  uint64_t padding3;
  uint64_t padding4; // last 4 bytes is uint32_t but who cares
};

struct FFXIVIpcObjectSpawn :
  FFXIVIpcBasePacket< ObjectSpawn >
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
  uint32_t housingLink;
  Common::FFXIVARR_POSITION3 position;
  int16_t unknown3C;
  int16_t unknown3E;
};

struct FFXIVIpcObjectDespawn :
  FFXIVIpcBasePacket< ObjectDespawn >
{
  uint8_t spawnIndex;
  uint8_t padding[7];
};

struct FFXIVIpcDuelChallenge :
  FFXIVIpcBasePacket< DuelChallenge >
{
  uint8_t otherClassJobId;
  uint8_t otherLevel; // class job level
  uint8_t challengeByYou; // 0 if the other challenges you, 1 if you challenges the other.
  uint8_t otherItemLevel;

  uint32_t otherActorId;

  char otherName[32];
};

struct FFXIVIpcMarketBoardSearchResult :
  FFXIVIpcBasePacket< MarketBoardSearchResult >
{
    struct MarketBoardItem
    {
        uint32_t itemCatalogId;
        uint16_t quantity;
        uint16_t demand;
    } items[20];

    uint32_t itemIndexEnd;
    uint32_t padding1;
    uint32_t itemIndexStart;
    uint32_t requestId;
};

struct FFFXIVIpcMarketBoardItemListingCount :
  FFXIVIpcBasePacket< MarketBoardItemListingCount >
{
  uint32_t itemCatalogId;
  uint32_t unknown1; // does some shit if nonzero
  uint16_t requestId;
  uint16_t quantity; // high/low u8s read separately?
  uint32_t unknown3;
};

struct FFXIVIpcMarketBoardItemListingHistory :
  FFXIVIpcBasePacket< MarketBoardItemListingHistory >
{
    uint32_t itemCatalogId;
    uint32_t itemCatalogId2;

    struct MarketListing
    {
        uint32_t salePrice;
        uint32_t purchaseTime;
        uint32_t quantity;
        uint8_t isHq;
        uint8_t padding;
        uint8_t onMannequin;

        char buyerName[33];

        uint32_t itemCatalogId;
    } listing[20];
};


} /* Server */
} /* Packets */
} /* Network */
} /* Sapphire */



#endif /*_CORE_NETWORK_PACKETS_SERVER_IPC_H*/
