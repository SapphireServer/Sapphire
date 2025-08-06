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

#include <filesystem>

namespace fs = std::filesystem;

class NavmeshExporter
{
public:
  static void exportZone( const ExportedZone& zone )
  {
    auto start = std::chrono::high_resolution_clock::now();

    static auto exportPath = std::filesystem::current_path() / "navi";

    auto objPath = exportPath / zone.name / ( zone.name + ".obj" );

    std::error_code e;
    if( !fs::exists( objPath, e ) )
      ObjExporter::exportZone( zone );

    TiledNavmeshGenerator gen;

    if( !gen.init( objPath.string() ) )
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
