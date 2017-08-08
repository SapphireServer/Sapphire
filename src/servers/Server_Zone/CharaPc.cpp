#include "CharaPc.h"

uint8_t Core::Entity::CharaDetail::getClass() const
{
   return m_class;
}

void Core::Entity::CharaDetail::setClass( uint8_t class_ )
{
   m_class = class_;
}

bool Core::Entity::CharaDetail::getBIsNewGame() const
{
   return m_bIsNewGame;
}

void Core::Entity::CharaDetail::setBIsNewGame( bool isNewGame )
{
   m_bIsNewGame = isNewGame;
}

uint8_t Core::Entity::CharaDetail::getMakeValid() const
{
   return m_makeValid;
}

void Core::Entity::CharaDetail::setMakeValid( uint8_t makeValid )
{
   m_makeValid = makeValid;
}

uint8_t Core::Entity::CharaDetail::getLegacyEmployEnable() const
{
   return m_legacyEmployEnable;
}

void Core::Entity::CharaDetail::setLegacyEmployEnable( uint8_t legacyEmployEnable )
{
   m_legacyEmployEnable = legacyEmployEnable;
}

uint8_t Core::Entity::CharaDetail::getLegacyCompleteFlag() const
{
   return m_legacyCompleteFlag;
}

void Core::Entity::CharaDetail::setLegacyCompleteFlag( uint8_t legacyCompleteFlag )
{
   m_legacyCompleteFlag = legacyCompleteFlag;
}

uint32_t Core::Entity::CharaDetail::getRemakeFlag() const
{
   return m_remakeFlag;
}

void Core::Entity::CharaDetail::setRemakeFlag( uint32_t remakeFlag )
{
   m_remakeFlag = remakeFlag;
}

uint32_t Core::Entity::CharaDetail::getTotalPlayTime() const
{
   return m_totalPlayTime;
}

void Core::Entity::CharaDetail::setTotalPlayTime( uint32_t totalPlayTime )
{
   m_totalPlayTime = totalPlayTime;
}

float Core::Entity::CharaDetail::getTotalPlayTimeSecond() const
{
   return m_totalPlayTimeSecond;
}

void Core::Entity::CharaDetail::setTotalPlayTimeSecond( float totalPlayTimeSecond )
{
   m_totalPlayTimeSecond = totalPlayTimeSecond;
}

uint8_t Core::Entity::CharaDetail::getInvisible() const
{
   return m_invisible;
}

void Core::Entity::CharaDetail::setInvisible( uint8_t invisible )
{
   m_invisible = invisible;
}

uint8_t Core::Entity::CharaDetail::getFirstClass() const
{
   return m_firstClass;
}

void Core::Entity::CharaDetail::setFirstClass( uint8_t firstClass )
{
   m_firstClass = firstClass;
}

uint8_t Core::Entity::CharaDetail::getHomePoint() const
{
   return m_homePoint;
}

void Core::Entity::CharaDetail::setHomePoint( uint8_t homePoint )
{
   m_homePoint = homePoint;
}

uint32_t Core::Entity::CharaDetail::getRestPoint() const
{
   return m_restPoint;
}

void Core::Entity::CharaDetail::setRestPoint( uint32_t restPoint )
{
   m_restPoint = restPoint;
}

float Core::Entity::CharaDetail::getRentalTimer() const
{
   return m_rentalTimer;
}

void Core::Entity::CharaDetail::setRentalTimer( float rentalTimer )
{
   m_rentalTimer = rentalTimer;
}

float Core::Entity::CharaDetail::getBuddyUpdateTimer() const
{
   return m_buddyUpdateTimer;
}

void Core::Entity::CharaDetail::setBuddyUpdateTimer( float buddyUpdateTimer )
{
   m_buddyUpdateTimer = buddyUpdateTimer;
}

float Core::Entity::CharaDetail::getBuddyTimer() const
{
   return m_buddyTimer;
}

void Core::Entity::CharaDetail::setBuddyTimer( float buddyTimer )
{
   m_buddyTimer = buddyTimer;
}

uint8_t Core::Entity::CharaDetail::getBuddyRank() const
{
   return m_buddyRank;
}

void Core::Entity::CharaDetail::setBuddyRank( uint8_t buddyRank )
{
   m_buddyRank = buddyRank;
}

uint8_t Core::Entity::CharaDetail::getBuddyAdditionSkillPoint() const
{
   return m_buddyAdditionSkillPoint;
}

void Core::Entity::CharaDetail::setBuddyAdditionSkillPoint( uint8_t buddyAdditionSkillPoint )
{
   m_buddyAdditionSkillPoint = buddyAdditionSkillPoint;
}

uint32_t Core::Entity::CharaDetail::getBuddyExp() const
{
   return m_buddyExp;
}

void Core::Entity::CharaDetail::setBuddyExp( uint32_t buddyExp )
{
   m_buddyExp = buddyExp;
}

uint32_t Core::Entity::CharaDetail::getBuddyCommand() const
{
   return m_buddyCommand;
}

void Core::Entity::CharaDetail::setBuddyCommand( uint32_t buddyCommand )
{
   m_buddyCommand = buddyCommand;
}

uint32_t Core::Entity::CharaDetail::getBuddyHp() const
{
   return m_buddyHp;
}

void Core::Entity::CharaDetail::setBuddyHp( uint32_t buddyHp )
{
   m_buddyHp = buddyHp;
}

uint8_t Core::Entity::CharaDetail::getGuardianDeity() const
{
   return m_guardianDeity;
}

void Core::Entity::CharaDetail::setGuardianDeity( uint8_t guardianDeity )
{
   m_guardianDeity = guardianDeity;
}

uint8_t Core::Entity::CharaDetail::getBirthMonth() const
{
   return m_birthMonth;
}

void Core::Entity::CharaDetail::setBirthMonth( uint8_t birthMonth )
{
   m_birthMonth = birthMonth;
}

uint8_t Core::Entity::CharaDetail::getBirthday() const
{
   return m_birthday;
}

void Core::Entity::CharaDetail::setBirthday( uint8_t birthday )
{
   m_birthday = birthday;
}

uint8_t Core::Entity::CharaDetail::getStartTown() const
{
   return m_startTown;
}

void Core::Entity::CharaDetail::setStartTown( uint8_t startTown )
{
   m_startTown = startTown;
}

uint16_t Core::Entity::CharaDetail::getActiveTitle() const
{
   return m_activeTitle;
}

void Core::Entity::CharaDetail::setActiveTitle( uint16_t activeTitle )
{
   m_activeTitle = activeTitle;
}

uint16_t Core::Entity::CharaDetail::getEquippedMannequin() const
{
   return m_equippedMannequin;
}

void Core::Entity::CharaDetail::setEquippedMannequin( uint16_t equippedMannequin )
{
   m_equippedMannequin = equippedMannequin;
}

uint32_t Core::Entity::CharaDetail::getTomeStoneCounter() const
{
   return m_tomeStoneCounter;
}

void Core::Entity::CharaDetail::setTomeStoneCounter( uint32_t tomeStoneCounter )
{
   m_tomeStoneCounter = tomeStoneCounter;
}

float Core::Entity::CharaDetail::getTomeStomeTimer() const
{
   return m_tomeStomeTimer;
}

void Core::Entity::CharaDetail::setTomeStomeTimer( float tomeStomeTimer )
{
   m_tomeStomeTimer = tomeStomeTimer;
}

uint16_t Core::Entity::CharaDetail::getConfigFlags() const
{
   return m_configFlags;
}

void Core::Entity::CharaDetail::setConfigFlags( uint16_t configFlags )
{
   m_configFlags = configFlags;
}

uint8_t Core::Entity::CharaDetail::getGmIcon() const
{
   return m_gmIcon;
}

void Core::Entity::CharaDetail::setGmIcon( uint8_t gmIcon )
{
   m_gmIcon = gmIcon;
}

uint8_t Core::Entity::CharaDetail::getGmBind() const
{
   return m_gmBind;
}

void Core::Entity::CharaDetail::setGmBind( uint8_t gmBind )
{
   m_gmBind = gmBind;
}

uint32_t Core::Entity::CharaDetail::getCatchCount() const
{
   return m_catchCount;
}

void Core::Entity::CharaDetail::setCatchCount( uint32_t catchCount )
{
   m_catchCount = catchCount;
}

uint32_t Core::Entity::CharaDetail::getUseBaitCatalogId() const
{
   return m_useBaitCatalogId;
}

void Core::Entity::CharaDetail::setUseBaitCatalogId( uint32_t useBaitCatalogId )
{
   m_useBaitCatalogId = useBaitCatalogId;
}

uint8_t Core::Entity::CharaDetail::getOpeningSequence() const
{
   return m_openingSequence;
}

void Core::Entity::CharaDetail::setOpeningSequence( uint8_t openingSequence )
{
   m_openingSequence = openingSequence;
}

uint8_t Core::Entity::CharaDetail::getLeveTicketNum() const
{
   return m_leveTicketNum;
}

void Core::Entity::CharaDetail::setLeveTicketNum( uint8_t leveTicketNum )
{
   m_leveTicketNum = leveTicketNum;
}

uint32_t Core::Entity::CharaDetail::getLeveTicketLastGetTime() const
{
   return m_leveTicketLastGetTime;
}

void Core::Entity::CharaDetail::setLeveTicketLastGetTime( uint32_t leveTicketLastGetTime )
{
   m_leveTicketLastGetTime = leveTicketLastGetTime;
}

uint16_t Core::Entity::CharaDetail::getLeveAssignmentSeed() const
{
   return m_leveAssignmentSeed;
}

void Core::Entity::CharaDetail::setLeveAssignmentSeed( uint16_t leveAssignmentSeed )
{
   m_leveAssignmentSeed = leveAssignmentSeed;
}

uint8_t Core::Entity::CharaDetail::getLeveAssignmentCount() const
{
   return m_leveAssignmentCount;
}

void Core::Entity::CharaDetail::setLeveAssignmentCount( uint8_t leveAssignmentCount )
{
   m_leveAssignmentCount = leveAssignmentCount;
}

uint16_t Core::Entity::CharaDetail::getGuildleveFactionCreditBr() const
{
   return m_guildleveFactionCreditBr;
}

void Core::Entity::CharaDetail::setGuildleveFactionCreditBr( uint16_t guildleveFactionCreditBr )
{
   m_guildleveFactionCreditBr = guildleveFactionCreditBr;
}

uint16_t Core::Entity::CharaDetail::getGuildleveFactionCreditAz() const
{
   return m_guildleveFactionCreditAz;
}

void Core::Entity::CharaDetail::setGuildleveFactionCreditAz( uint16_t guildleveFactionCreditAz )
{
   m_guildleveFactionCreditAz = guildleveFactionCreditAz;
}

uint16_t Core::Entity::CharaDetail::getGuildleveFactionCreditHo() const
{
   return m_guildleveFactionCreditHo;
}

void Core::Entity::CharaDetail::setGuildleveFactionCreditHo( uint16_t guildleveFactionCreditHo )
{
   m_guildleveFactionCreditHo = guildleveFactionCreditHo;
}

uint8_t Core::Entity::CharaDetail::getGrandCompany() const
{
   return m_grandCompany;
}

void Core::Entity::CharaDetail::setGrandCompany( uint8_t grandCompany )
{
   m_grandCompany = grandCompany;
}

uint8_t Core::Entity::CharaDetail::getGearsetMaxNum() const
{
   return m_gearsetMaxNum;
}

void Core::Entity::CharaDetail::setGearsetMaxNum( uint8_t gearsetMaxNum )
{
   m_gearsetMaxNum = gearsetMaxNum;
}

uint32_t Core::Entity::CharaDetail::getContentJoinTime() const
{
   return m_contentJoinTime;
}

void Core::Entity::CharaDetail::setContentJoinTime( uint32_t contentJoinTime )
{
   m_contentJoinTime = contentJoinTime;
}

uint32_t Core::Entity::CharaDetail::getPathId() const
{
   return m_pathId;
}

void Core::Entity::CharaDetail::setPathId( uint32_t pathId )
{
   m_pathId = pathId;
}

uint16_t Core::Entity::CharaDetail::getStepIndex() const
{
   return m_stepIndex;
}

void Core::Entity::CharaDetail::setStepIndex( uint16_t stepIndex )
{
   m_stepIndex = stepIndex;
}

uint32_t Core::Entity::CharaDetail::getPathIdBackUp() const
{
   return m_pathIdBackUp;
}

void Core::Entity::CharaDetail::setPathIdBackUp( uint32_t pathIdBackUp )
{
   m_pathIdBackUp = pathIdBackUp;
}

uint16_t Core::Entity::CharaDetail::getStepIndexBackUp() const
{
   return m_stepIndexBackUp;
}

void Core::Entity::CharaDetail::setStepIndexBackUp( uint16_t stepIndexBackUp )
{
   m_stepIndexBackUp = stepIndexBackUp;
}

uint8_t Core::Entity::CharaDetail::getGcSupplySeed() const
{
   return m_gcSupplySeed;
}

void Core::Entity::CharaDetail::setGcSupplySeed( uint8_t gcSupplySeed )
{
   m_gcSupplySeed = gcSupplySeed;
}

uint32_t Core::Entity::CharaDetail::getGcSupplyTime() const
{
   return m_gcSupplyTime;
}

void Core::Entity::CharaDetail::setGcSupplyTime( uint32_t gcSupplyTime )
{
   m_gcSupplyTime = gcSupplyTime;
}

uint32_t Core::Entity::CharaDetail::getLayerSet() const
{
   return m_layerSet;
}

void Core::Entity::CharaDetail::setLayerSet( uint32_t layerSet )
{
   m_layerSet = layerSet;
}

uint16_t Core::Entity::CharaDetail::getGcChangeTime() const
{
   return m_gcChangeTime;
}

void Core::Entity::CharaDetail::setGcChangeTime( uint16_t gcChangeTime )
{
   m_gcChangeTime = gcChangeTime;
}

uint8_t Core::Entity::CharaDetail::getFateFlag() const
{
   return m_fateFlag;
}

void Core::Entity::CharaDetail::setFateFlag( uint8_t fateFlag )
{
   m_fateFlag = fateFlag;
}

uint8_t Core::Entity::CharaDetail::getContentRaidCounter() const
{
   return m_contentRaidCounter;
}

void Core::Entity::CharaDetail::setContentRaidCounter( uint8_t contentRaidCounter )
{
   m_contentRaidCounter = contentRaidCounter;
}

uint16_t Core::Entity::CharaDetail::getContentRaidTimer() const
{
   return m_contentRaidTimer;
}

void Core::Entity::CharaDetail::setContentRaidTimer( uint16_t contentRaidTimer )
{
   m_contentRaidTimer = contentRaidTimer;
}

uint64_t Core::Entity::CharaDetail::getId() const
{
   return m_id;
}

void Core::Entity::CharaDetail::setId( uint64_t id )
{
   m_id = id;
}
