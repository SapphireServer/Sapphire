#ifndef OBJ_EXPORTER_H
#define OBJ_EXPORTER_H

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>


#include "exporter.h"


class ObjExporter
{
public:
  static std::string exportZone( const ExportedZone& zone )
  {
    static auto exportPath = std::filesystem::current_path() / "navi";

    auto start = std::chrono::high_resolution_clock::now();

    auto dir = exportPath / zone.name;
    auto filePath = dir / (zone.name + ".obj");

    std::error_code e;

    if( !std::filesystem::exists( dir, e ) )
    {
      if( !std::filesystem::create_directories( dir, e ) )
      {
        printf( "Unable to create directory '%s'\n", ( dir.string() ).c_str() );
        return "";
      }
    }
    std::ofstream of( filePath, std::ios::trunc );
    int indicesOffset = 0;
    int meshesCount = 0;

    if( of.good() )
    {
      of.close();
      of.open( filePath, std::ios::app );
      for( const auto& group : zone.groups )
      {
        exportGroup( group.second, of, indicesOffset, meshesCount );
      }
      of.flush();
      of.close();
    }

    auto end = std::chrono::high_resolution_clock::now();

    printf( "[Obj] Finished exporting %s in %lu ms\n",
            std::filesystem::relative( filePath, exportPath ).string().c_str(),
            std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
    return filePath.string();
  }

  static std::string exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {
    static auto exportPath = std::filesystem::current_path() / "navi";

    auto start = std::chrono::high_resolution_clock::now();

    auto dir = exportPath / zoneName / "groups";
    auto filePath = dir / ( group.name + ".obj" );

    std::error_code e;
    if( !std::filesystem::exists( dir, e ) )
    {
      if( !std::filesystem::create_directories( dir, e ) )
      {
        printf( "Unable to create directory '%s'\n", ( dir.string() ).c_str() );
        return "";
      }
    }
    std::ofstream of( filePath, std::ios::trunc );
    int indicesOffset = 0;
    int modelCount = 0;

    if( of.good() )
    {
      of.close();
      of.open( filePath, std::ios::app );
      exportGroup( group, of, indicesOffset, modelCount );
      of.flush();
      of.close();
    }

    auto end = std::chrono::high_resolution_clock::now();
    printf( "[Obj] Finished exporting %s in %lu ms\n",
            std::filesystem::relative( filePath, exportPath ).string().c_str(),
            std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
    
    return filePath.string();
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
