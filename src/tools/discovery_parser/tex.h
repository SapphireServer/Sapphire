#ifndef _TEX_H
#define _TEX_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// ported Ioncannon's tex file parsing
// https://bitbucket.org/Ioncannon/ffxiv-explorer/src/9330429c1540cf35f947fe7321739d857f4f31a7/src/com/fragmenterworks/ffxivextract/models/Texture_File.java

struct TEX_HEADER
{
  uint32_t unknown;            // 00
  uint16_t compressionType;    // 04
  uint16_t unknown2;           // 06
  uint16_t uncompressedWidth;  // 08
  uint16_t uncompressedHeight; // 0A
  uint16_t unknown5;           // 0C
  uint16_t numMipMaps;         // 0F
  uint16_t unknown4[0x0B];     // 11 - 0x1C
  std::vector< uint32_t > mipMaps;
};

struct TEX_FILE
{
  std::string name;
  TEX_HEADER header;
  std::vector< char > data;

  TEX_FILE( const std::string& path )
  {
    name = path;
    std::ifstream in( path, std::ios::binary );
    if( in.good() )
    {
      std::size_t size = 0;
      in.seekg( 0, in.end );
      size = in.tellg();
      in.seekg( 0, in.beg );
      data.resize( size );
      in.read( &data[ 0 ], size );

      header = *reinterpret_cast< TEX_HEADER* >( &data[ 0 ] );

      header.mipMaps.clear();

      for( auto i = 0; i < header.numMipMaps; ++i )
        header.mipMaps.push_back( *reinterpret_cast< uint32_t* >( &data[ 0x1C + ( i * 4 ) ] ) );

      std::cout << path << "\n\tcompressionType " << header.compressionType << " uncompressedWidth " <<
                header.uncompressedWidth << " uncompressedHeight " << header.uncompressedHeight << " numMipMaps " <<
                header.numMipMaps << " mipMaps " << header.mipMaps.size() << "\n";
    }
    else
    {
      std::string errorStr( "Unable to open " + path );
      throw std::runtime_error( errorStr.c_str() );
    }
  }
};

#endif