#ifndef EXPORTMGR_H
#define EXPORTMGR_H

#include "exporter.h"
#include "navmesh_exporter.h"
#include "obj_exporter.h"
#include "threadpool.h"

class ExportMgr
{
public:
  ExportMgr( unsigned int maxJobs = 1 )
  {
    m_maxJobs = maxJobs;
  }
  ~ExportMgr()
  {

  }

  void exportZone( const ExportedZone& zone, ExportFileType exportFileTypes )
  {
    if( exportFileTypes & ExportFileType::WavefrontObj )
      ObjExporter::exportZone( zone );

    if( exportFileTypes & ExportFileType::Navmesh )
      NavmeshExporter::exportZone( zone, m_maxJobs );
  }

private:
  int m_maxJobs{ 1 };

};

#endif