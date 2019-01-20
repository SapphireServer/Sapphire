#ifndef OBJ_EXPORTER_H
#define OBJ_EXPORTER_H

#include <cstdint>
#include <fstream>
#include <string>

#include <chrono>

#include "exporter.h"

class ObjExporter : public Exporter
{
public:
  static void exportZone( const ExportedZone& zone )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto fileName = zone.name + ".obj";
    std::ofstream of( fileName, std::ios::trunc );
    int indicesOffset = 0;
    int meshesCount = 0;

    if( of.good() )
    {
      of.close();
      of.open( fileName, std::ios::app );
      for( const auto& group : zone.groups )
      {
        exportGroup( group.second, of, indicesOffset, meshesCount );
      }
      of.flush();
      of.close();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << ( "Finished exporting " + fileName + " in " +
      std::to_string( std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() ) + "ms \n" );
  }

  static void exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto fileName = zoneName + "_" + group.name + ".obj";
    std::ofstream of( fileName, std::ios::trunc );
    int indicesOffset = 0;
    int modelCount = 0;

    if( of.good() )
    {
      of.close();
      of.open( fileName, std::ios::app );
      exportGroup( group, of, indicesOffset, modelCount );
      of.flush();
      of.close();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << ( "Finished exporting " + fileName + " in " +
      std::to_string( std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() ) + "ms\n" );
  }
private:
  static void exportGroup( const ExportedGroup& group, std::ofstream& of, int& indicesOffset, int& modelCount )
  {
    int currModelCount = modelCount;

    //of << ( "o " + group.name + "_" + std::to_string( currModelCount ) + "\n" );
    for( const auto& model : group.models )
    {
      of << ( "o " + model.second.name + "_" + std::to_string( currModelCount ) + "_" + std::to_string( modelCount++ ) + "\n" );

      int meshCount = 0;
      for( const auto& mesh : model.second.meshes )
      {
        for( int i = 0; i + 2 < mesh.verts.size(); i += 3 )
        {
          of << (
            "v " + std::to_string( mesh.verts[ i ] ) + " " +
                         std::to_string( mesh.verts[ i + 1 ] ) + " " +
                         std::to_string( mesh.verts[ i + 2 ] ) + "\n"
            );
        }
        //of << ( "g " + model.second.name + "_" +  std::to_string( currModelCount ) + "_" + std::to_string( modelCount ) + "_" + std::to_string( meshCount++ ) + "\n" );
        for( int i = 0; i + 2 < mesh.indices.size(); i += 3 )
        {
          of << (
            "f " + std::to_string( mesh.indices[ i ] + indicesOffset + 1 ) + " " +
            std::to_string( mesh.indices[i + 1] + indicesOffset + 1 ) + " " +
            std::to_string( mesh.indices[i + 2] + indicesOffset + 1 ) + "\n"
            );
        }
        indicesOffset += mesh.indices.size();
      }
    }
  }
};
#endif // !OBJ_EXPORTER_H
