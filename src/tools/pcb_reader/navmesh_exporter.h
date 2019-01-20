#ifndef NAVMESH_EXPORTER_H
#define NAVMESH_EXPORTER_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include <chrono>

#include "exporter.h"

#include <recastnavigation/Recast/Include/Recast.h>
#include <recastnavigation/Recast/Include/RecastAlloc.h>
#include <recastnavigation/Detour/Include/DetourNavMesh.h>
#include <recastnavigation/Detour/Include/DetourNavMeshBuilder.h>

class NavmeshExporter : public Exporter
{
public:
  static void exportZone( const ExportedZone& zone )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto fileName = zone.name + ".obj";
    
    auto end = std::chrono::high_resolution_clock::now();
    printf( "[Navmesh] Finished exporting %s in %u ms\n",
      fileName,
      std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
  }

  static void exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto fileName = zoneName + "_" + group.name + ".obj";

    auto end = std::chrono::high_resolution_clock::now();

    printf( "[Navmesh] Finished exporting %s in %u ms\n",
      fileName,
      std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
  }
private:
  static void exportGroup( const ExportedGroup& group, std::ofstream& of, int& indicesOffset, int& modelCount )
  {

  }
};
#endif // !OBJ_EXPORTER_H
