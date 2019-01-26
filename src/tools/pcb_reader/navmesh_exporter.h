#ifndef NAVMESH_EXPORTER_H
#define NAVMESH_EXPORTER_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include <chrono>

#include "exporter.h"
#include "nav/TiledNavmeshGenerator.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class NavmeshExporter
{
public:
  static void exportZone( const ExportedZone& zone, bool deleteObj = false )
  {
    static std::string currPath = std::experimental::filesystem::current_path().string();

    auto dir = fs::current_path().string() + "/pcb_export/" + zone.name + "/";
    auto fileName = dir + zone.name + ".obj";

    TiledNavmeshGenerator gen;

    if( !gen.init( fileName ) )
    {
      printf( "[Navmesh] failed to init TiledNavmeshGenerator for file '%s'\n", fileName.c_str() );
      return;
    }

    if( !gen.buildNavmesh() )
    {
      printf( "[Navmesh] Failed to build navmesh for '%s'\n", zone.name.c_str() );
      return;
    }

    gen.saveNavmesh( zone.name );

    auto end = std::chrono::high_resolution_clock::now();
    printf( "[Navmesh] Finished exporting %s in %lu ms\n",
      fileName.c_str(),
      std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
  }

  static void exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {

  }
};
#endif // !OBJ_EXPORTER_H
