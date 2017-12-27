#ifndef __XMLCONFIG_H
#define __XMLCONFIG_H

#include <stdint.h>

#include <boost/property_tree/ptree.hpp>

#include <map>

namespace Core {

   // very simple XML parser class
   // this hasn't gotten much attention yet as it works good as it is.
   class XMLConfig
   {
   public:
      typedef std::map<std::string, std::string> SettingMap;
      typedef std::map<std::string, SettingMap> CategoryMap;

      // instanciate and load a config
      XMLConfig();

      ~XMLConfig();

      // load a config file
      bool loadConfig( const std::string& fileName );

      template< class T >
      T getValue( const std::string& name, T defaultValue = T() )
      {
         try
         {
            return m_propTree.get< T >( name );
         }
         catch( ... )
         {
            return defaultValue;
         }
      }

      template< class T >
      void setValue( const std::string& name, T defaultValue = T() )
      {
         m_propTree.put( name, defaultValue );
      }

      template< class T >
      T getAttrValue( boost::property_tree::ptree node, const std::string& name, T defaultValue = T() )
      {
         try
         {
            T outVal = node.get< T >( "<xmlattr>." + name );
            return outVal;
         }
         catch( const std::runtime_error& )
         {
            T outVal = defaultValue;
            return outVal;
         }
      }

      boost::property_tree::ptree getChild( const std::string& name )
      {
         auto val = m_propTree.get_child( name );
         return val;
      }

   private:
      boost::property_tree::ptree m_propTree;
   };

}
#endif
