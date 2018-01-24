#ifndef _BATTLENPCTEMPLATE_H
#define _BATTLENPCTEMPLATE_H

#include <stdint.h>
#include <string>

namespace Core {
namespace Entity {

   /**
    * \brief BattleNpcTemplate - Class which defines a template specific BNpcs can be created from
    */
   class BattleNpcTemplate
   {
   public:
      BattleNpcTemplate();
      BattleNpcTemplate( std::string templateName, uint32_t bnpcBaseId, uint32_t bnpcNameId, uint32_t modelId, std::string aiName );

      ~BattleNpcTemplate();

      uint32_t getBnpcBaseId() const;
      uint32_t getBnpcNameId() const;
      uint32_t getModelId() const;

   private:
      std::string m_templateName;
      std::string m_aiName;
      uint32_t m_bnpcBaseId = 0;
      uint32_t m_bnpcNameId = 0;
      uint32_t m_modelId = 0;
 

   };

}
}

#endif