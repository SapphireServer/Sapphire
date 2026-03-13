#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "commonshader.h"
#include "Exd/ExdData.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <Navi/NaviProvider.h>
#include "Engine/GfxApi.h"


#include "imgui.h"
#include "datReader/DatCategories/bg/lgb.h"

// Forward declare the Field type - adjust this based on your actual Field type
using Field = std::variant< std::string, bool, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, float, uint64_t >;

struct CachedExdData
{
  std::map< uint32_t, std::vector< Field > > rows;
  int columnCount;
  std::string fileName;
  bool isValid;

  CachedExdData() : columnCount( 0 ), isValid( false )
  {
  }
};


class ExdView
{
private:
  std::vector< std::string > m_exdFiles;
  std::string m_selectedExdFile;
  std::string m_loadedExdFile; // Track which file is currently loaded
  int m_cachedColumnCount; // Cache the column count
  CachedExdData m_cachedData;
  char m_filterText[ 256 ]; // Buffer for filter input


public:
  ExdView();

  ~ExdView();

  void init();

  // Main interface
  void show();

  void showExdSelector();

  void showExdDetails();

  // Selection callback
  void onSelectionChanged( const std::string& selectedPath );

private:
  void loadExdData();

  bool passesFilter( const std::string& path ) const;
};
