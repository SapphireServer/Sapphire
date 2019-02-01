#ifndef NAVMESH_EXPORTER_H
#define NAVMESH_EXPORTER_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include <chrono>

#include "exporter.h"
#include "obj_exporter.h"
#include "nav/TiledNavmeshGenerator.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class NavmeshExporter
{
public:
  static void exportZone( const ExportedZone& zone )
  {
    auto start = std::chrono::high_resolution_clock::now();

    static std::string currPath = std::experimental::filesystem::current_path().string();

    auto dir = fs::current_path().string() + "/pcb_export/" + zone.name + "/";
    auto fileName = dir + zone.name;
    auto objName = fileName + ".obj";

    std::error_code e;
    if( !fs::exists( objName, e ) )
      ObjExporter::exportZone( zone );

    TiledNavmeshGenerator gen;

    if( !gen.init( objName ) )
    {
      printf( "[Navmesh] failed to init TiledNavmeshGenerator for file '%s'\n", zone.name.c_str() );
      return;
    }

    if( !gen.buildNavmesh() )
    {
      printf( "[Navmesh] Failed to build navmesh for '%s'\n", zone.name.c_str() );
      return;
    }

    gen.saveNavmesh( zone.name );


    auto end = std::chrono::high_resolution_clock::now();
    printf( "[Navmesh] Finished exporting %s in %lu ms\n", zone.name.c_str(),
            std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
  }

};
#endif // !OBJ_EXPORTER_H
