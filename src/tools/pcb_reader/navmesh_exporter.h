#ifndef OBJ_EXPORTER_H
#define OBJ_EXPORTER_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include <chrono>

#include "exporter.h"

static class ObjExporter : public Exporter
{
public:
  static void exportZone( const ExportedZone& zone )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto fileName = zone.name + ".obj";
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << ( "Finished exporting " + fileName + " in " +
      std::to_string( std::chrono::duration_cast< std::chrono::seconds >( end - start ).count() ) + " seconds\n" );
  }

  static void exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto fileName = zoneName + "_" + group.name + ".obj";

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << ( "Finished exporting " + fileName + " in " +
      std::to_string( std::chrono::duration_cast< std::chrono::seconds >( end - start ).count() ) + " seconds\n" );
  }
private:
  static void exportGroup( const ExportedGroup& group, std::ofstream& of, int& indicesOffset, int& modelCount )
  {

  }
};
#endif // !OBJ_EXPORTER_H
