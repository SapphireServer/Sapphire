#ifndef SAPPHIRE_CONFIGMGR_H
#define SAPPHIRE_CONFIGMGR_H

#include <memory>
#include <type_traits>
#include <inih/INIReader.h>
#include <string>
#include <stdint.h>
#include "ConfigDef.h"

namespace Sapphire::Common
{
    class ConfigMgr
    {
    public:
      ConfigMgr() = default;
      ~ConfigMgr() = default;

      bool loadConfig( const std::string& configName );
      bool loadGlobalConfig( Common::Config::GlobalConfig& config, const std::string& configName = "global.ini" );

      template< class T > struct always_false : std::false_type {};

      template< class T >
      T getValue( const std::string& section, const std::string& name, T defaultValue = T() )
      {
        if constexpr ( std::is_same_v< T, uint32_t > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, int32_t > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, uint16_t > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, int16_t > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, uint8_t > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, int8_t > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, long > )
          return m_pInih->GetInteger( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, double > )
          return m_pInih->GetReal( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, float > )
          return m_pInih->GetReal( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, std::string > )
          return m_pInih->Get( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, bool > )
          return m_pInih->GetBoolean( section, name, defaultValue );
        else
          static_assert( always_false< T >::value, "non-exhaustive getter!" );
      }

      template< class T >
      void setValue( const std::string& name, T defaultValue = T() )
      {
        // TODO: reimplement this...
        //m_propTree.put( name, defaultValue );
      }

    private:
      bool copyDefaultConfig( const std::string& configName );

      std::unique_ptr< INIReader > m_pInih;

      const std::string m_globalConfigFile = "global.ini";
      const std::string m_configFolderRoot = "./config/";
      const std::string m_configDefaultSuffix = ".default";
  };
}

#endif //SAPPHIRE_CONFIGMGR_H
