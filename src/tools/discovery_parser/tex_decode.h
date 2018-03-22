#ifndef _TEX_DECODE_H
#define _TEX_DECODE_H

#include <cstdint>
#include <vector>

#include "tex.h"

// all credit to Ioncannon
// copied/pasted from https://bitbucket.org/Ioncannon/ffxiv-explorer/src/9330429c1540cf35f947fe7321739d857f4f31a7/src/com/fragmenterworks/ffxivextract/helpers/ImageDecoding.java

struct Colour
{
   uint8_t r, g, b, a;

   Colour( int r, int g, int b, int a )
   {
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
   }

   uint32_t getRGB()
   {
      return ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | ( b << 0 );
   }
};

struct ImageHeader
{
   uint32_t height;
   uint32_t width;
};

struct Image
{
   uint32_t height, width;
   std::vector< std::vector< uint32_t > > data;

   Image()
   {

   }

   Image( int height, int width )
   {
      this->height = height;
      this->width = width;
   }

   Image( char* buf )
   {
      height = *reinterpret_cast< uint32_t* >( buf + 0 );
      width = *reinterpret_cast< uint32_t* >( buf + 4 );
      data.resize( *reinterpret_cast< uint32_t* >( buf + 8 ) );

      auto offset = 12;
      for( auto y = 0; y < data.size(); ++y )
      {
         auto row = *reinterpret_cast< uint32_t* >( buf + offset );
         auto entries = *reinterpret_cast< uint32_t* >( buf + offset + 4 );
         data[y].resize( entries );
         offset += 8;

         for( auto x = 0; x < entries; ++x )
            data[y][x] = *reinterpret_cast< uint32_t* >( buf + offset + ( x * 4 ) );
         offset += entries * 4;
      }
   }

   void toFile( const std::string& path )
   {
      std::ofstream out( path.c_str(), std::ios::trunc );
      out.close();
      out.open( path, std::ios::binary | std::ios::app );

      out.write( reinterpret_cast< char* >( &height ), 4 ); // 0
      out.write( reinterpret_cast< char* >( &width ), 4 );  // 4

      auto size = data.size();
      out.write( reinterpret_cast< char* >( &size ), 4 );   // 8

      for( auto y = 0; y < data.size(); ++y )
      {
         out.write( reinterpret_cast< char* >( &y ), 4 );
         auto entries = data[y].size();
         out.write( reinterpret_cast< char* >( &entries ), 4);
         for( auto x = 0; x < data[y].size(); ++x )
         {
            out.write( reinterpret_cast< char* >( &data[y][x] ), 4 );
         }
      }
      out.close();
   }

   void setRGB( unsigned int x, unsigned int y, uint32_t colour )
   {
      if( data.size() <= y )
         data.resize( y + 1 );
      if( data[y].size() <= x )
         data[y].resize( x + 1 );
      data[y][x] = colour;
   }

};


void DecompressBlockDTX1( int x, const int y, const int width, const int color0, const int color1, const int txl1, const int txl2, Image& img )
{
   float temp = ((color0 >> 11) * 255.0f) + 16.0f;
   const float r0 = (((temp / 32.0f) + temp) / 32.0f);
   temp = (((color0 & 0x07E0) >> 5) * 255.0f) + 32.0f;
   const float g0 = (((temp / 64.0f) + temp) / 64.0f);
   temp = ((color0 & 0x001F) * 255.0f) + 16.0f;
   const float b0 = (((temp / 32.0f) + temp) / 32.0f);
   temp = ((color1 >> 11) * 255.0f) + 16.0f;
   const float r1 = (((temp / 32.0f) + temp) / 32.0f);
   temp = (((color1 & 0x07E0) >> 5) * 255.0f) + 32.0f;
   const float g1 = (((temp / 64.0f) + temp) / 64.0f);
   temp = ((color1 & 0x001F) * 255.0f) + 16.0f;
   const float b1 = (((temp / 32.0f) + temp) / 32.0f);
   for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
         // Color FinalColor;
         const int d = (4 * j) + i;
         int positionCode;
         if ((d * 2) >= 16) {
            positionCode = (txl2 >> ((d * 2) % 16)) & 0x03;
         } else {
            positionCode = (txl1 >> (d * 2)) & 0x03;
         }
         float fr, fg, fb, fa;
         if (color0 > color1) {
            switch (positionCode) {
               case 0: {
                  fr = r0;
                  fg = g0;
                  fb = b0;
                  fa = 0;
                  break;
               }
               case 1: {
                  fr = r1;
                  fg = g1;
                  fb = b1;
                  fa = 0;
                  break;
               }
               case 2: {
                  fr = ((2.0f * (float) r0) + (float) r1) / 3.0f;
                  fg = ((2.0f * (float) g0) + (float) g1) / 3.0f;
                  fb = ((2.0f * (float) b0) + (float) b1) / 3.0f;
                  fa = 0;
                  break;
               }
               case 3: {
                  fr = ((float) r0 + (2.0f * (float) r1)) / 3.0f;
                  fg = ((float) g0 + (2.0f * (float) g1)) / 3.0f;
                  fb = ((float) b0 + (2.0f * (float) b1)) / 3.0f;
                  fa = 0;
                  break;
               }
               default: {
                  fr = 0;
                  fg = 0;
                  fb = 0;
                  fa = 0;
               }
            }
         } else {
            switch (positionCode) {
               case 0: {
                  fr = r0;
                  fg = g0;
                  fb = b0;
                  fa = 0xff;
                  break;
               }
               case 1: {
                  fr = r1;
                  fg = g1;
                  fb = b1;
                  fa = 0xff;
                  break;
               }
               case 2: {
                  fr = ((float) r0 + (float) r1) / 2.0f;
                  fg = ((float) g0 + (float) g1) / 2.0f;
                  fb = ((float) b0 + (float) b1) / 2.0f;
                  fa = 0xff;
                  break;
               }
               case 3: {
                  fr = 0;
                  fg = 0;
                  fb = 0;
                  fa = 0xff;
                  break;
               }
               default: {
                  fr = 0;
                  fg = 0;
                  fb = 0;
                  fa = 0;
               }
            }
         }
         if ((x + i) < width) {
            int alpha = 0;
            if ((fr == fg) && (fr == fb) && (fr == 0)) {
               alpha = 0xff;
            }
            img.setRGB(x + i, y + j, Colour((int) fr, (int) fg, (int) fb, 255 - alpha).getRGB());
         }
      }
   }
}

Image DecodeTexDXT1( const TEX_FILE& tex, uint32_t offset, uint32_t targetHeight, uint32_t targetWidth,
   uint32_t compressedHeight, uint32_t compressedWidth  )
{
   if( offset > tex.data.size() )
      throw std::runtime_error( "Unable to decode TEX file " + tex.name + ": offset too large" );
   else if( tex.data.size() < ( ( targetHeight * targetWidth ) / 2 ) )
      throw std::runtime_error( "Unable to decode TEX file " + tex.name + ": data too small" );

   std::vector< char > ret;
   auto data = tex.data.data() + offset;
   int pos = 0;

   Image img( targetHeight, targetWidth );

   for( int y = 0; y < compressedHeight; y++ )
   {
      for( int x = 0; x < compressedWidth; x++ )
      {
         const int t0 = *reinterpret_cast< const uint16_t* >( data + pos + 0 ) & 0xffff;
         const int t1 = *reinterpret_cast< const uint16_t* >( data + pos + 2 ) & 0xffff;
         const int t2 = *reinterpret_cast< const uint16_t* >( data + pos + 4 ) & 0xffff;
         const int t3 = *reinterpret_cast< const uint16_t* >( data + pos + 6 ) & 0xffff;

         pos += 8;
         DecompressBlockDTX1( x * 4, y * 4, targetWidth, t0, t1, t2, t3, img );
      }
   }
   return img;
}

#endif