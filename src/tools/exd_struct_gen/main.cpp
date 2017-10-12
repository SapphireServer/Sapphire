
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
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <fstream>
#include <streambuf>
#include <regex>


Core::Logger g_log;
Core::Data::ExdData g_exdData;


const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
//const std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv" );
std::map< uint8_t, std::string > g_typeMap;


std::string generateDatAccessDecl( const std::string &exd )
{
   return "     xiv::exd::Exd m_" + exd + "Dat;\n";
}

std::string generateDirectGetters( const std::string& exd )
{
   return "     boost::shared_ptr< " + exd + " > get" + exd + "( uint32_t " + exd + "Id );";
}

std::string generateSetDatAccessCall( const std::string &exd )
{
   auto& cat = g_exdData.m_exd_data->get_category( exd );
   auto exh = cat.get_header();

   std::string lang = "xiv::exd::Language::none";
   auto langs = exh.get_languages();
   if( langs.size() > 1 )
      lang = "xiv::exd::Language::en";

   return "      m_" + exd + "Dat = setupDatAccess( \"" + exd + "\", " + lang + " );";
}

std::string generateDirectGetterDef( const std::string& exd )
{
   std::string result = "";
   result =
      "boost::shared_ptr< Core::Data::" + exd + " >\n"
      "   Core::Data::ExdDataGenerated::get" + exd + "( uint32_t " + exd + "Id )\n"
      "{\n"
      "   try\n"
      "   {\n"
      "      auto row = m_" + exd + "Dat.get_row( " + exd + "Id );\n"
      "      auto info = boost::make_shared< " + exd + " >( " + exd + "Id, this );\n"

      "      return info;\n"
      "   }\n"
      "   catch( ... )\n"
      "   {\n"
      "      return nullptr;\n"
      "   }\n"

      "   return nullptr;\n"

      "}\n";
   return result;
}

std::string generateStruct( const std::string &exd )
{
   auto& cat = g_exdData.m_exd_data->get_category( exd );
   auto exh = cat.get_header();
   auto exhMem = exh.get_exh_members();

   std::map< uint32_t, std::string > indexToNameMap;
   std::map< uint32_t, std::string > indexToTypeMap;
   int count = 0;

   std::string result = "   struct " + exd +"\n   {\n";

   for( auto member : exhMem )
   {
      auto typei = static_cast< uint8_t >( member.type );
      auto it = g_typeMap.find( typei );

      std::string type;
      if( it != g_typeMap.end() )
         type = it->second; 
      else
         type = "bool";

      std::string fieldName = " field" + std::to_string( count );

      indexToNameMap[count] = fieldName;
      indexToTypeMap[count] = type;
     
      result += "   " + type + " " + fieldName + ";\n";
   
      count++;
   }

   result += "\n      " + exd + "( uint32_t id, Core::Data::ExdDataGenerated* exdData );\n";
   result += "   };\n";
   
   return result;
}

std::string generateConstructorsDecl( const std::string& exd )
{
   std::string result;

   auto& cat = g_exdData.m_exd_data->get_category( exd );
   auto exh = cat.get_header();
   auto exhMem = exh.get_exh_members();

   std::map< uint32_t, std::string > indexToNameMap;
   std::map< uint32_t, std::string > indexToTypeMap;
   int count = 0;


   for( auto member : exhMem )
   {
      auto typei = static_cast< uint8_t >( member.type );
      auto it = g_typeMap.find( typei );

      std::string type;
      if( it != g_typeMap.end() )
         type = it->second;
      else
         type = "bool";

      std::string fieldName = " field" + std::to_string( count );

      indexToNameMap[count] = fieldName;
      indexToTypeMap[count] = type;

      count++;
   }

   result += "\n      Core::Data::" + exd + "::" + exd + "( uint32_t id, Core::Data::ExdDataGenerated* exdData )\n";
   result += "      {\n";
   count = 0;
   std::string indent = "         ";
   result += indent + "   auto row = exdData->m_" + exd + "Dat.get_row( id );\n";
   for( auto member : exhMem )
   {
      result += indent + indexToNameMap[count] + " = exdData->getField< " + indexToTypeMap[count] + " >( row, " + std::to_string( count) + " );\n";
      count++;
   }
   result += "      }\n";

   return result;
}

int main()
{
   g_typeMap[0] = "std::string";
   g_typeMap[1] = "bool";
   g_typeMap[2] = "int8_t";
   g_typeMap[3] = "uint8_t";
   g_typeMap[4] = "int16_t";
   g_typeMap[5] = "uint16_t";
   g_typeMap[6] = "int32_t";
   g_typeMap[7] = "uint32_t";
   g_typeMap[9] = "float";
   g_typeMap[11] = "uint64_t";

   std::ifstream t( "ExdData.h.tmpl" );
   std::string exdH( ( std::istreambuf_iterator<char>( t ) ),
                       std::istreambuf_iterator<char>() );

   std::ifstream s( "ExdData.cpp.tmpl" );
   std::string exdC( ( std::istreambuf_iterator<char>( s ) ),
                       std::istreambuf_iterator<char>() );

   g_log.init();

   g_log.info( "Setting up EXD data" );
   if( !g_exdData.init( datLocation ) )
   {
      g_log.fatal( "Error setting up EXD data " );
      return 0;
   }
  
   std::string structDefs;
   std::string dataDecl;
   std::string getterDecl;
   std::string datAccCall;
   std::string getterDef;
   std::string constructorDecl;

   // for all sheets in the json i guess....
   structDefs += generateStruct( "TerritoryType" );
   dataDecl += generateDatAccessDecl( "TerritoryType" );
   getterDecl += generateDirectGetters( "TerritoryType" );
   datAccCall += generateSetDatAccessCall( "TerritoryType" );
   getterDef += generateDirectGetterDef( "TerritoryType" );
   constructorDecl += generateConstructorsDecl( "TerritoryType" );

   std::string result;
   result = std::regex_replace( exdH, std::regex( "\\STRUCTS" ), structDefs );
   result = std::regex_replace( result, std::regex( "\\DATACCESS" ), dataDecl );
   result = std::regex_replace( result, std::regex( "\\DIRECTGETTERS" ), getterDecl );

   g_log.info( result );

   std::ofstream outH("ExdDataGenerated.h");
   outH << result;
   outH.close();

   result = std::regex_replace( exdC, std::regex( "\\SETUPDATACCESS" ), datAccCall );
   result = std::regex_replace( result, std::regex( "\\DIRECTGETTERS" ), getterDef );
   result = std::regex_replace( result, std::regex( "\\CONSTRUCTORS" ), constructorDecl );
   
   std::ofstream outC("ExdDataGenerated.cpp");
   outC << result;
   outC.close();
   
   g_log.info( result );

   return 0;
}
