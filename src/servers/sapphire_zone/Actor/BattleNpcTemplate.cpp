#include "BattleNpcTemplate.h"

Core::Entity::BattleNpcTemplate::BattleNpcTemplate()
{
   
}

Core::Entity::BattleNpcTemplate::BattleNpcTemplate( std::string templateName, uint32_t bnpcBaseId, 
                                                    uint32_t bnpcNameId, uint32_t modelId, std::string aiName ) :
   m_templateName( templateName ),
   m_bnpcBaseId( bnpcBaseId ),
   m_bnpcNameId( bnpcNameId ),
   m_modelId( modelId ),
   m_aiName( aiName )
{
   
}

Core::Entity::BattleNpcTemplate::~BattleNpcTemplate()
{

}

uint32_t Core::Entity::BattleNpcTemplate::getBnpcBaseId() const
{
   return m_bnpcBaseId;
}

uint32_t Core::Entity::BattleNpcTemplate::getBnpcNameId() const
{
   return m_bnpcNameId;
}

uint32_t Core::Entity::BattleNpcTemplate::getModelId() const
{
   return m_modelId;
}
