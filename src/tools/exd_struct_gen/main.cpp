
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <streambuf>
#include <regex>
#include <algorithm>

using namespace Sapphire;

Sapphire::Data::ExdDataGenerated g_exdData;
bool skipUnmapped = true;

std::map< char, std::string > numberToStringMap
  {
    { '0', "zero" },
    { '1', "one" },
    { '2', "two" },
    { '3', "three" },
    { '4', "four" },
    { '5', "five" },
    { '6', "six" },
    { '7', "seven" },
    { '8', "eight" },
    { '9', "nine" },
  };

std::vector< std::string > cppKeyWords
  {
    "new",
    "class"
  };

//std::string datLocation( "/home/mordred/sqpack" );
std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );
std::map< uint8_t, std::string > g_typeMap;


std::string generateDatAccessDecl( const std::string& exd )
{
  return "     xiv::exd::Exd m_" + exd + "Dat;\n";
}

std::string generateIdListDecl( const std::string& exd )
{
  return "     std::set< uint32_t > m_" + exd + "IdList;\n";
}

std::string generateDirectGetters( const std::string& exd )
{
  return "     using " + exd + "Ptr = std::shared_ptr< " + exd + " >;\n";
}

std::string generateIdListGetter( const std::string& exd )
{
  std::string IdListGetter = "const std::set< uint32_t >& get" + exd + "IdList()\n"
                                                                       "{\n"
                                                                       "   if( m_" + exd + "IdList.size() == 0 )\n"
                                                                                           "      loadIdList( m_" +
                             exd + "Dat, m_" + exd + "IdList );\n"
                                                     "   return m_" + exd + "IdList;\n"
                                                                            "}\n";
  return IdListGetter;
}

std::string generateSetDatAccessCall( const std::string& exd )
{
  auto& cat = g_exdData.m_exd_data->get_category( exd );
  auto exh = cat.get_header();

  std::string lang = "xiv::exd::Language::none";
  auto langs = exh.get_languages();
  if( langs.size() > 1 )
    lang = "xiv::exd::Language::en";

  return "      m_" + exd + "Dat = setupDatAccess( \"" + exd + "\", " + lang + " );\n";
}

std::string generateDirectGetterDef()
{
  std::string result = "";
  return result;
}

std::map< uint32_t, std::string > indexToNameMap;
std::map< uint32_t, std::string > indexToTypeMap;
std::map< uint32_t, std::string > indexToTarget;
std::map< uint32_t, bool > indexIsArrayMap;
std::map< uint32_t, uint32_t > indexCountMap;

std::map< std::string, std::string > nameTaken;

std::string generateStruct( const std::string& exd )
{
  auto& cat = g_exdData.m_exd_data->get_category( exd );
  auto exh = cat.get_header();
  auto exhMem = exh.get_exh_members();

  int count = 0;

  auto json = nlohmann::json();

  std::ifstream exJson( "ex.json" );
  exJson >> json;

  for( auto& sheet : json[ "sheets" ] )
  {
    if( sheet[ "sheet" ] != exd )
      continue;
  
    for( auto& definition : sheet[ "definitions" ] )
    {
      uint32_t index;
      std::string converterTarget = "";
      bool isRepeat = false;
      int num = 0;
      try
      {
        index = definition.at( "index" );
      }
      catch( ... )
      {
        index = 0;
      }
 
      try
      {
        std::string fieldName = std::string( definition.at( "name" ) );
        indexToNameMap[ index ] = fieldName;
      }
      catch( ... )
      {
      }

      try
      {
        converterTarget = std::string( definition.at( "converter" ).at( "target" ) );
        if( nameTaken.find( converterTarget ) != nameTaken.end() )
          indexToTarget[ index ] = converterTarget;
      }
      catch( ... )
      {
      }
 
      try
      {
        num = definition.at( "count" );
        isRepeat = true;
        indexIsArrayMap[ index ] = true;
        indexCountMap[ index ] = num;
        std::string fName = definition.at( "definition" ).at( "name" );
        indexToNameMap[ index ] = fName;
      }
      catch( ... )
      {
      }
    }


  }

  std::string result = "struct " + exd + "\n{\n";


  for( auto member : exhMem )
  {
    auto typei = static_cast< uint8_t >( member.type );
    auto it = g_typeMap.find( typei );

    std::string type;
    if( it != g_typeMap.end() )
      type = it->second;
    else
      type = "bool";

    std::string fieldName = "field" + std::to_string( count );
    if( indexToNameMap.find( count ) == indexToNameMap.end() )
    {
      if( skipUnmapped )
      {
        count++;
        continue;
      }
      indexToNameMap[ count ] = fieldName;
    }
    else
    {
      fieldName = indexToNameMap[ count ];
    }
    fieldName[ 0 ] = std::tolower( fieldName[ 0 ] );

    std::string badChars = ",-':![](){}<>% \x02\x1f\x01\x03";
    std::for_each( badChars.begin(), badChars.end(), [ &fieldName ]( const char c ) 
    {
      fieldName.erase( std::remove( fieldName.begin(), fieldName.end(), c ), fieldName.end() );
    });

    for( auto entry : numberToStringMap )
    {
      if( fieldName[ 0 ] == entry.first )
      {
        fieldName.erase( 0, 1 );
        fieldName.insert( 0, entry.second );
      }
    }

    for( std::string keyword : cppKeyWords )
    {
      if( fieldName == keyword )
        fieldName[ 0 ] = toupper( fieldName[ 0 ] );
    }

    indexToNameMap[ count ] = fieldName;
    indexToTypeMap[ count ] = type;
    if( indexToTarget.find( count ) != indexToTarget.end() )
      result += "   std::shared_ptr< " + indexToTarget[ count ] + "> " + fieldName + ";\n";
    else
    {
      if( indexIsArrayMap.find( count ) != indexIsArrayMap.end() )
      {
        type = "std::vector< " + type + " >";
      }
      result += "   " + type + " " + fieldName + ";\n";

    }

    count++;
  }

  auto exhHead = exh.get_header();
  if( exhHead.variant == 2 )
  {
    result += "\n   " + exd + "( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData );\n";
  }
  else
  {
    result += "\n   " + exd + "( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData );\n";
  }
  result += "};\n\n";

  return result;
}

std::string generateConstructorsDecl( const std::string& exd )
{
  std::string result;

  auto& cat = g_exdData.m_exd_data->get_category( exd );
  auto exh = cat.get_header();
  auto exhMem = exh.get_exh_members();

  int count = 0;

  std::string indent = "   ";
  auto exhHead = exh.get_header();
  if( exhHead.variant == 2 )
  {
    result += "\nSapphire::Data::" + exd + "::" + exd + "( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )\n";
    result += "{\n";
    result += indent + "auto row = exdData->m_" + exd + "Dat.get_row( row_id, subRow );\n";
  }
  else
  {
    result += "\nSapphire::Data::" + exd + "::" + exd + "( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )\n";
    result += "{\n";
    result += indent + "auto row = exdData->m_" + exd + "Dat.get_row( row_id );\n";
  }
  for( auto member : exhMem )
  {
    if( indexToNameMap.find( count ) == indexToNameMap.end() )
    {
      count++;
      continue;
    }
    if( indexToTarget.find( count ) != indexToTarget.end() )
      result += indent + indexToNameMap[ count ] + " = std::make_shared< " + indexToTarget[ count ] +
                ">( exdData->getField< " +
                indexToTypeMap[ count ] + " >( row, " + std::to_string( count ) + " ), exdData );\n";
    else
    {
      if( indexIsArrayMap.find( count ) == indexIsArrayMap.end() )
        result += indent + indexToNameMap[ count ] + " = exdData->getField< " + indexToTypeMap[ count ] + " >( row, " +
                  std::to_string( count ) + " );\n";
      else
      {

        uint32_t amount = indexCountMap[ count ];
        for( int i = 0; i < amount; i++ )
        {

          result += indent + indexToNameMap[ count ] + ".push_back( exdData->getField< " + indexToTypeMap[ count ] +
                    " >( row, " + std::to_string( count + i ) + " ) );\n";

        }


      }
    }
    count++;
  }
  result += "}\n";

  indexToNameMap.clear();
  indexToTypeMap.clear();
  indexToTarget.clear();
  indexIsArrayMap.clear();
  indexCountMap.clear();
  return result;
}

int main( int argc, char** argv )
{
  Logger::init( "struct_gen" );
  if( argc > 1 )
  {
    Logger::info( "using dat path: {0}", std::string( argv[ 1 ] ) );
    datLocation = std::string( argv[ 1 ] );
  }


  g_typeMap[ 0 ] = "std::string";
  g_typeMap[ 1 ] = "bool";
  g_typeMap[ 2 ] = "int8_t";
  g_typeMap[ 3 ] = "uint8_t";
  g_typeMap[ 4 ] = "int16_t";
  g_typeMap[ 5 ] = "uint16_t";
  g_typeMap[ 6 ] = "int32_t";
  g_typeMap[ 7 ] = "uint32_t";
  g_typeMap[ 9 ] = "float";
  g_typeMap[ 11 ] = "uint64_t";

  std::ifstream t( "ExdData.h.tmpl" );
  std::string exdH( ( std::istreambuf_iterator< char >( t ) ),
                    std::istreambuf_iterator< char >() );

  std::ifstream s( "ExdData.cpp.tmpl" );
  std::string exdC( ( std::istreambuf_iterator< char >( s ) ),
                    std::istreambuf_iterator< char >() );


  std::ifstream exJson( "ex.json" );

  auto json = nlohmann::json();
  exJson >> json;

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }
  Logger::info( "Generating structs, this may take several minutes..." );
  Logger::info( "Go grab a coffee..." );

  std::string structDefs;
  std::string idListsDecl;
  std::string dataDecl;
  std::string getterDecl;
  std::string datAccCall;
  std::string getterDef;
  std::string constructorDecl;
  std::string forwards;
  std::string idListGetters;

  //BOOST_FOREACH( boost::property_tree::ptree::value_type &sheet, m_propTree.get_child( "sheets" ) )
  //{
  //nameTaken[name] = "1";
  //}
  //
  for( auto& sheet : json[ "sheets" ] )
  { 
      std::string name = sheet[ "sheet" ];
      forwards += "struct " + name + ";\n";
      structDefs += generateStruct( name );
      dataDecl += generateDatAccessDecl( name );
      idListsDecl += generateIdListDecl( name );
      getterDecl += generateDirectGetters( name );
      datAccCall += generateSetDatAccessCall( name );
      constructorDecl += generateConstructorsDecl( name );
      idListGetters += generateIdListGetter( name );
  }

  getterDecl +=
    "\n     template< class T >\n"
    "     std::shared_ptr< T > get( uint32_t id )\n"
    "     {\n"
    "        try\n"
    "        {\n"
    "           auto info = std::make_shared< T >( id, this );\n"
    "           return info;\n"
    "        }\n"
    "        catch( ... )\n"
    "        {\n"
    "           return nullptr;\n"
    "        }\n"
    "        return nullptr;\n"
    "     }\n";

  getterDef += generateDirectGetterDef();

  // for all sheets in the json i guess....

  std::string result;
  result = std::regex_replace( exdH, std::regex( "\\FORWARDS" ), forwards );
  result = std::regex_replace( result, std::regex( "\\STRUCTS" ), structDefs );
  result = std::regex_replace( result, std::regex( "\\DATACCESS" ), dataDecl );
  result = std::regex_replace( result, std::regex( "\\IDLISTS" ), idListsDecl );
  result = std::regex_replace( result, std::regex( "\\DIRECTGETTERS" ), getterDecl );
  result = std::regex_replace( result, std::regex( "\\IDLISTGETTERS" ), idListGetters );


//   g_log.info( result );

  std::ofstream outH( "ExdDataGenerated.h" );
  outH << result;
  outH.close();

  result = std::regex_replace( exdC, std::regex( "\\SETUPDATACCESS" ), datAccCall );
  result = std::regex_replace( result, std::regex( "\\DIRECTGETTERS" ), getterDef );
  result = std::regex_replace( result, std::regex( "\\CONSTRUCTORS" ), constructorDecl );

  std::ofstream outC( "ExdDataGenerated.cpp" );
  outC << result;
  outC.close();

//   g_log.info( result );

  return 0;
}
