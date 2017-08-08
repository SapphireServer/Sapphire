#ifndef _CHARA_H_
#define _CHARA_H_

#include <Server_Common/Common.h>
#include <boost/enable_shared_from_this.hpp>

#include "Forwards.h"
#include <set>
#include <map>

namespace Core
{
   namespace Entity
   {

      class CharaDetail
      {

      private:

         // CHARAPC data ------------------------------------------------------------------------------------
         uint8_t  m_class;
         bool     m_bIsNewGame;
         uint8_t  m_makeValid;

         struct RetainerInfo
         {
            uint32_t retainerId;
            char retainerName[32];
            uint32_t createUnixTime;
            bool isActive;
            bool isRename;
            uint8_t status;
         } m_retainerInfo[8];

         uint8_t  m_legacyEmployEnable;
         char     m_platform[32];
         uint8_t  m_legacyCompleteFlag;
         uint32_t m_remakeFlag;
         uint32_t m_totalPlayTime;
         float    m_totalPlayTimeSecond;

         uint8_t  m_invisible;
         uint8_t  m_firstClass;
         uint8_t  m_homePoint;
         uint8_t  m_favoritePoint[3];

         uint32_t m_restPoint;
         float    m_rentalTimer;
         float    m_buddyUpdateTimer;
         float    m_buddyTimer;
         char     m_buddyName[21];
         uint8_t  m_possession[8];
         uint8_t  m_buddyEquip[3];
         uint8_t  m_buddyRank;
         uint8_t  m_buddyAdditionSkillPoint;
         uint8_t  m_buddySkillLine[3];
         uint32_t m_buddyExp;
         uint32_t m_buddyCommand;
         uint32_t m_buddyHp;

         uint8_t  m_guardianDeity;
         uint8_t  m_birthMonth;
         uint8_t  m_birthday;
         uint8_t  m_startTown;
         uint8_t  m_mountList[11];
         uint16_t m_activeTitle;
         uint8_t  m_titleList[32];
         uint8_t  m_reward[16];

         struct HuntingLogInfo
         {
            uint8_t killCount[40];
            uint64_t completeFlags;
            uint8_t currentRank;
            uint32_t isNewFlags;
         } m_huntingLogInfo[10];

         uint8_t m_aetheryteList[12];

         uint8_t  m_howTo[32];
         uint8_t  m_minions[32];
         uint8_t  m_cutScene[64];
         uint16_t m_equippedMannequin;
         uint32_t m_tomeStoneCounter;
         float    m_tomeStomeTimer;

         uint16_t m_configFlags;
         uint8_t  m_gmIcon;
         uint8_t  m_gmBind;

         uint32_t m_catchCount;
         uint8_t  m_isFishCaught[50];
         uint8_t  m_isSpotVisited[25];
         uint8_t  m_lastFishSize[36];
         uint8_t  m_lastFishId[36];
         uint32_t m_useBaitCatalogId;

         uint8_t m_gatheringHistoryPointId[8];
         uint8_t m_gatheringDivisionOpenFlags[40];
         uint8_t m_gatheringItemGetFlags[60];

         uint8_t m_recipeDevisionOpenFlags[80];
         uint8_t m_recipeCreateFlags[250];

         uint8_t m_questCompleteFlags[200];
         uint8_t m_legacyQuestCompleteFlags[40];
         uint8_t m_legacyCompleteFlags[200];

         struct LeveInfo
         {
            uint8_t leves[28];
         } m_leveInfo[16];

         uint8_t m_openingSequence;

         // I really do not know what this is for
         //`Type` TINYINT( 3 ) UNSIGNED,
         //`Index` TINYINT( 3 ) UNSIGNED,
         //Type_0 TINYINT( 3 ) UNSIGNED,
         //Index_0 TINYINT( 3 ) UNSIGNED,
         //Type_1 TINYINT( 3 ) UNSIGNED,
         //Index_1 TINYINT( 3 ) UNSIGNED,
         //Type_2 TINYINT( 3 ) UNSIGNED,
         //Index_2 TINYINT( 3 ) UNSIGNED,
         //Type_3 TINYINT( 3 ) UNSIGNED,
         //Index_3 TINYINT( 3 ) UNSIGNED,

         uint8_t  m_leveTicketNum;
         uint32_t m_leveTicketLastGetTime;
         uint16_t m_leveAssignmentSeed;
         uint8_t  m_leveAssignmentCount;

         uint16_t m_guildleveFactionCreditBr;
         uint16_t m_guildleveFactionCreditAz;
         uint16_t m_guildleveFactionCreditHo;

         uint8_t m_grandCompany;
         uint8_t m_grandCompanyRank[3];
         uint8_t m_gearsetMaxNum;

         uint8_t m_discoveryWork[414];

         uint32_t m_contentJoinTime;
         uint8_t  m_contentRaidClearFlags[28];
         uint8_t  m_contentDungeonClearFlags[18];
         uint8_t  m_contentGuildOrderClearFlags[10];
         uint8_t  m_contentBossBattleClearFlags[6];
         uint8_t  m_contentColosseumClearFlags[2];
         uint8_t  m_contentRaidAttainFlags[28];
         uint8_t  m_contentDungeonAttainFlag[18];
         uint8_t  m_contentGuildOrderAttainFlags[10];
         uint8_t  m_contentBossBattleAttainFlags[6];
         uint8_t  m_contentColosseumAttainFlags[2];

         // related to currently active choco taxi??
         uint32_t m_pathId;
         uint16_t m_stepIndex;
         uint32_t m_pathIdBackUp;

         uint16_t m_stepIndexBackUp;

         uint8_t  m_chocoboTaxiStandFlags[8];
         uint8_t  m_companion[16];

         uint8_t  m_cabinet[32];
         uint8_t  m_contentFinderPenalties[2];
         uint8_t  m_gcSupplyItemFlags[4];
         uint8_t  m_gcSupplySeed;
         uint32_t m_gcSupplyTime;
         uint8_t  m_gcSupplyClassLevel[11];

         uint32_t m_layerSet;
         uint8_t  m_trophyAcquisitionFlags[8];
         uint16_t m_gcChangeTime;
         uint8_t  m_fateFlag;
         uint8_t  m_contentRaidCounter;
         uint16_t m_contentRaidTimer;

         uint64_t m_id;
      public:
         uint8_t getClass() const;
         void setClass( uint8_t class_ );
         bool getBIsNewGame() const;
         void setBIsNewGame( bool isNewGame );
         uint8_t getMakeValid() const;
         void setMakeValid( uint8_t makeValid );
         uint8_t getLegacyEmployEnable() const;
         void setLegacyEmployEnable( uint8_t legacyEmployEnable );
         uint8_t getLegacyCompleteFlag() const;
         void setLegacyCompleteFlag( uint8_t legacyCompleteFlag );
         uint32_t getRemakeFlag() const;
         void setRemakeFlag( uint32_t remakeFlag );
         uint32_t getTotalPlayTime() const;
         void setTotalPlayTime( uint32_t totalPlayTime );
         float getTotalPlayTimeSecond() const;
         void setTotalPlayTimeSecond( float totalPlayTimeSecond );
         uint8_t getInvisible() const;
         void setInvisible( uint8_t invisible );
         uint8_t getFirstClass() const;
         void setFirstClass( uint8_t firstClass );
         uint8_t getHomePoint() const;
         void setHomePoint( uint8_t homePoint );
         uint32_t getRestPoint() const;
         void setRestPoint( uint32_t restPoint );
         float getRentalTimer() const;
         void setRentalTimer( float rentalTimer );
         float getBuddyUpdateTimer() const;
         void setBuddyUpdateTimer( float buddyUpdateTimer );
         float getBuddyTimer() const;
         void setBuddyTimer( float buddyTimer );
         uint8_t getBuddyRank() const;
         void setBuddyRank( uint8_t buddyRank );
         uint8_t getBuddyAdditionSkillPoint() const;
         void setBuddyAdditionSkillPoint( uint8_t buddyAdditionSkillPoint );
         uint32_t getBuddyExp() const;
         void setBuddyExp( uint32_t buddyExp );
         uint32_t getBuddyCommand() const;
         void setBuddyCommand( uint32_t buddyCommand );
         uint32_t getBuddyHp() const;
         void setBuddyHp( uint32_t buddyHp );
         uint8_t getGuardianDeity() const;
         void setGuardianDeity( uint8_t guardianDeity );
         uint8_t getBirthMonth() const;
         void setBirthMonth( uint8_t birthMonth );
         uint8_t getBirthday() const;
         void setBirthday( uint8_t birthday );
         uint8_t getStartTown() const;
         void setStartTown( uint8_t startTown );
         uint16_t getActiveTitle() const;
         void setActiveTitle( uint16_t activeTitle );
         uint16_t getEquippedMannequin() const;
         void setEquippedMannequin( uint16_t equippedMannequin );
         uint32_t getTomeStoneCounter() const;
         void setTomeStoneCounter( uint32_t tomeStoneCounter );
         float getTomeStomeTimer() const;
         void setTomeStomeTimer( float tomeStomeTimer );
         uint16_t getConfigFlags() const;
         void setConfigFlags( uint16_t configFlags );
         uint8_t getGmIcon() const;
         void setGmIcon( uint8_t gmIcon );
         uint8_t getGmBind() const;
         void setGmBind( uint8_t gmBind );
         uint32_t getCatchCount() const;
         void setCatchCount( uint32_t catchCount );
         uint32_t getUseBaitCatalogId() const;
         void setUseBaitCatalogId( uint32_t useBaitCatalogId );
         uint8_t getOpeningSequence() const;
         void setOpeningSequence( uint8_t openingSequence );
         uint8_t getLeveTicketNum() const;
         void setLeveTicketNum( uint8_t leveTicketNum );
         uint32_t getLeveTicketLastGetTime() const;
         void setLeveTicketLastGetTime( uint32_t leveTicketLastGetTime );
         uint16_t getLeveAssignmentSeed() const;
         void setLeveAssignmentSeed( uint16_t leveAssignmentSeed );
         uint8_t getLeveAssignmentCount() const;
         void setLeveAssignmentCount( uint8_t leveAssignmentCount );
         uint16_t getGuildleveFactionCreditBr() const;
         void setGuildleveFactionCreditBr( uint16_t guildleveFactionCreditBr );
         uint16_t getGuildleveFactionCreditAz() const;
         void setGuildleveFactionCreditAz( uint16_t guildleveFactionCreditAz );
         uint16_t getGuildleveFactionCreditHo() const;
         void setGuildleveFactionCreditHo( uint16_t guildleveFactionCreditHo );
         uint8_t getGrandCompany() const;
         void setGrandCompany( uint8_t grandCompany );
         uint8_t getGearsetMaxNum() const;
         void setGearsetMaxNum( uint8_t gearsetMaxNum );
         uint32_t getContentJoinTime() const;
         void setContentJoinTime( uint32_t contentJoinTime );
         uint32_t getPathId() const;
         void setPathId( uint32_t pathId );
         uint16_t getStepIndex() const;
         void setStepIndex( uint16_t stepIndex );
         uint32_t getPathIdBackUp() const;
         void setPathIdBackUp( uint32_t pathIdBackUp );
         uint16_t getStepIndexBackUp() const;
         void setStepIndexBackUp( uint16_t stepIndexBackUp );
         uint8_t getGcSupplySeed() const;
         void setGcSupplySeed( uint8_t gcSupplySeed );
         uint32_t getGcSupplyTime() const;
         void setGcSupplyTime( uint32_t gcSupplyTime );
         uint32_t getLayerSet() const;
         void setLayerSet( uint32_t layerSet );
         uint16_t getGcChangeTime() const;
         void setGcChangeTime( uint16_t gcChangeTime );
         uint8_t getFateFlag() const;
         void setFateFlag( uint8_t fateFlag );
         uint8_t getContentRaidCounter() const;
         void setContentRaidCounter( uint8_t contentRaidCounter );
         uint16_t getContentRaidTimer() const;
         void setContentRaidTimer( uint16_t contentRaidTimer );
         uint64_t getId() const;
         void setId( uint64_t id );

         // CHARAPC data END ------------------------------------------------------------------------------------
      };
   }
}
#endif