#include "bparse.h"

std::string xiv::utils::bparse::extract_cstring( std::istream& i_stream, const std::string& i_name )
{
  // Using a stringstream and reading character by character avoids this issue and ensures all input is processed correctly.
  std::stringstream ss;
  char c;
  while( i_stream.get( c ) && c != '\0' )
  {
    ss << c;
  }
  return ss.str();
}