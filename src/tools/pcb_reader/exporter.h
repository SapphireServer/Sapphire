#ifndef EXPORTER_H
#define EXPORTER_H

#include <atomic>
#include <future>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "threadpool.h"

enum ExportFileType : int
{
  WavefrontObj = 0x01,
  Navmesh = 0x02,
};

enum ExportSplitType
{
  None,
  SplitByGroup,
  SingleZone
};

struct ExportedMesh
{
  std::vector< float > verts;
  std::vector< int > indices;
};

struct ExportedModel
{
  std::string name;
  std::vector< ExportedMesh > meshes;
};

struct ExportedGroup
{
  std::string name;
  std::map< std::string, ExportedModel > models;
};

struct ExportedZone
{
  std::string name;
  std::map< std::string, ExportedGroup > groups;
};

#endif