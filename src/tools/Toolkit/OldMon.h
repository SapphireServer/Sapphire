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

// Add Detour includes for navmesh
#include <complex.h>

#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "imgui.h"
#include "Database/DbConnection.h"
#include "datReader/DatCategories/bg/lgb.h"

struct Version
{
  uint32_t version;
  std::string name;
};


struct Packet
{
  uint32_t id;
  uint32_t captureId;
  uint32_t packetSetId;
  uint32_t packetType;
  uint32_t packetAdditional;
  uint32_t isForSelf;
  uint32_t packetSize;
  uint32_t packetTimeStamp;
  uint32_t packetCategory;
  std::vector< uint8_t > data;
  std::string comment;
};

struct PacketSet
{
  uint32_t id;
  uint32_t captureId;
  uint8_t direction;
  uint8_t headerData[ 40 ];
  uint16_t portSrc;
  uint16_t portDst;
  std::vector< Packet > packets;
};

struct Capture
{
  uint32_t id;
  uint32_t versionId;
  std::string name;
  std::string description;
  std::vector< PacketSet > packetSets;
};

class OldMon
{
private:
  uint32_t m_selectedCaptureId{ 0 };
  uint32_t m_selectedVersionIdx{ 0 };
  uint32_t m_selectedCaptureIdx{ 0 };
  uint32_t m_selectedPacketIdx{ 0 };

  Sapphire::Db::ConnectionInfo m_dbConnectionInfo {"root", "", "ffxivmon", "localhost", 3306, 2, 2};
  std::shared_ptr< Sapphire::Db::DbConnection > m_dbConnection;
  bool m_dbConnectionOpen{ false };
  bool m_showDbConfigDialog{ false };

  // Database config buffers for ImGui
  char m_dbUserBuffer[256];
  char m_dbPasswordBuffer[256];
  char m_dbDatabaseBuffer[256];
  char m_dbHostBuffer[256];
  int m_dbPortBuffer;

  // Config file path
  std::filesystem::path m_configFile;

  std::vector< Version > m_versions;
  std::vector< Capture > m_captures;

  // Packet view state
  bool m_showPacketViewer{ false };
  size_t m_selectedByteOffset{ SIZE_MAX }; // Selected byte position for data inspector
  bool m_showDataInspector{ true }; // Toggle for showing data inspector

  std::vector< const Packet * > m_flatPacketList; // Flattened list for easy display
  void buildFlatPacketList(); // Build flattened packet list from selected capture
  void showPacketViewer();

  void showPacketGrid();

  void showHexViewer( const Packet *packet );

  void showDataInspector( const Packet *packet ); // New method for data inspector

  ImU32 getPacketSetColor( uint32_t packetSetId, uint8_t direction, size_t consecutiveIndex );

  const char *getDirectionIcon( uint8_t direction );

  void exportPacketAsBinary( const Packet *packet );

  void exportPacketSetAsBinary( const PacketSet *packetSet );

  void showDbConfigDialog(); // Database configuration dialog

  void initDbConfigBuffers(); // Initialize database config buffers

  bool connectToDatabase(); // Connect to database with current settings

  // Config management
  void loadConfig(); // Load database config from file
  void saveConfig(); // Save database config to file

public:
  OldMon();

  ~OldMon();

  void init();

  // Main interface
  void show();

  void loadVersions();

  void loadCaptures( uint32_t versionId );

  void loadCapture( uint32_t captureId );

  void refresh(); // Force refresh of cached data

  void showVersionComboBox();

  void showCaptureList();

  void onVersionChanged();

  void onCaptureChanged();

  // Getters
  uint32_t getSelectedCaptureId() const;

  uint32_t getSelectedVersionIdx() const { return m_selectedVersionIdx; }

  const Version *getSelectedVersion() const;

  Capture *getSelectedCapture();

  uint32_t getSelectedCaptureIdx() const { return m_selectedCaptureIdx; }
};
