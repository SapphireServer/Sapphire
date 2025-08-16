#pragma once

#include <memory>
#include <type_traits>
#include <inih/INIReader.h>
#include <string>
#include <stdint.h>
#include "ConfigDef.h"
#include "Util/Paths.h"

namespace Sapphire::Common
{
    class ConfigMgr
    {
    public:
      explicit ConfigMgr( std::filesystem::path configFolderRoot = Util::executableDir() / "config" );
      ~ConfigMgr() = default;

      bool loadConfig( const std::string& configName );
      bool loadGlobalConfig( Common::Config::GlobalConfig& config, const std::string& configName = "global.ini" );

      template< class T > struct always_false : std::false_type {};

      template< class T >
      T getValue( const std::string& section, const std::string& name, T defaultValue = T() )
      {
        if constexpr ( std::is_same_v< T, uint32_t > )
          return m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) );
        else if constexpr ( std::is_same_v< T, int32_t > )
          return m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) );
        else if constexpr ( std::is_same_v< T, uint16_t > )
          return static_cast< T >( m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) ) );
        else if constexpr ( std::is_same_v< T, int16_t > )
          return static_cast< T >( m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) ) );
        else if constexpr ( std::is_same_v< T, uint8_t > )
          return static_cast< T >( m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) ) );
        else if constexpr ( std::is_same_v< T, int8_t > )
          return static_cast< T >( m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) ) );
        else if constexpr ( std::is_same_v< T, long > )
          return static_cast< T >( m_pInih->GetInteger( section, name, static_cast< long >( defaultValue ) ) );
        else if constexpr ( std::is_same_v< T, double > )
          return m_pInih->GetReal( section, name, defaultValue );
        else if constexpr ( std::is_same_v< T, float > )
          return static_cast< T >( m_pInih->GetReal( section, name, static_cast< double >( defaultValue ) ) );
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
      const std::filesystem::path m_configFolderRoot;
      const std::string m_configDefaultSuffix = ".default";
  };
}