#ifndef OBJ_EXPORTER_H
#define OBJ_EXPORTER_H

#include <chrono>
#include <cstdint>
#include <experimental/filesystem>
#include <fstream>
#include <string>


#include "exporter.h"


class ObjExporter
{
public:
  static std::string exportZone( const ExportedZone& zone )
  {
    static std::string currPath = std::experimental::filesystem::current_path().string();

    auto start = std::chrono::high_resolution_clock::now();

    auto dir = currPath + "/pcb_export/" + zone.name + "/";
    auto fileName = dir + zone.name + ".obj";

    std::error_code e;

    if( !std::experimental::filesystem::exists( dir, e ) )
    {
      if( !std::experimental::filesystem::create_directories( dir, e ) )
      {
        printf( "Unable to create directory '%s'", ( dir ).c_str() );
        return "";
      }
    }
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

    printf( "[Obj] Finished exporting %s in %lu ms\n",
            fileName.substr( fileName.find( "pcb_export" ) - 1 ).c_str(),
            std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
    return fileName;
  }

  static std::string exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {
    static std::string currPath = std::experimental::filesystem::current_path().string();

    auto start = std::chrono::high_resolution_clock::now();

    auto dir = currPath + "/pcb_export/" + zoneName + "/groups/";
    auto fileName = dir + group.name + ".obj";

    std::error_code e;
    if( !std::experimental::filesystem::exists( dir, e ) )
    {
      if( !std::experimental::filesystem::create_directories( dir, e ) )
      {
        printf( "Unable to create directory '%s'", ( dir ).c_str() );
        return "";
      }
    }
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
    printf( "[Obj] Finished exporting %s in %lu ms\n",
            fileName.substr( fileName.find( "pcb_export" ) - 1 ).c_str(),
            std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
    
    return fileName;
  }
private:
  static void exportGroup( const ExportedGroup& group, std::ofstream& of, int& indicesOffset, int& modelCount )
  {
    int currModelCount = modelCount;

    of << "o " << group.name << '_' << std::to_string( currModelCount ) << '\n';
    for( const auto& model : group.models )
    {
      modelCount++;
      of << "o " << model.second.name << '_' << std::to_string( currModelCount ) << '_' << std::to_string( modelCount ) << '\n';

      int meshCount = 0;
      for( const auto& mesh : model.second.meshes )
      {
        for( int i = 0; i < mesh.verts.size(); i += 3 )
        {
          of << "v " <<
            std::to_string( mesh.verts[ i ] ) << ' ' <<
            std::to_string( mesh.verts[ i + 1 ] ) << ' ' <<
            std::to_string( mesh.verts[ i + 2 ] ) << '\n';
        }

        of << "g " <<
          model.second.name << '_' <<
          std::to_string( currModelCount ) << '_' << std::to_string( modelCount ) << '_' << std::to_string( meshCount++ ) << '\n';

        for( int i = 0; i < mesh.indices.size(); i += 3 )
        {
          of << "f " <<
            std::to_string( mesh.indices[ i ] + indicesOffset + 1 ) << ' ' <<
            std::to_string( mesh.indices[ i + 1 ] + indicesOffset + 1 ) << ' ' +
            std::to_string( mesh.indices[ i + 2 ] + indicesOffset + 1 ) << '\n';
        }
        indicesOffset += mesh.verts.size() / 3;
      }
    }
    //of.flush();
  }
};
#endif // !OBJ_EXPORTER_H
