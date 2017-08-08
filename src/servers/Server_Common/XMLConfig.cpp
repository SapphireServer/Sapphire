#include "XMLConfig.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

namespace Core {
   // instanciate and load a config
   XMLConfig::XMLConfig()
   {

   }

   XMLConfig::~XMLConfig()
   {

   }

   using boost::property_tree::ptree;
   const ptree& empty_ptree()
   {
      static ptree t;
      return t;
   };

   bool XMLConfig::loadConfig( const std::string& fileName )
   {

      boost::property_tree::read_xml( fileName, m_propTree );
      return true;
   }

}
