#include "bparse.h"

std::string xiv::utils::bparse::extract_cstring( std::istream& i_stream, const std::string& i_name )
{
   std::string temp_str;
   std::getline( i_stream, temp_str, '\0' );
   return temp_str;
}