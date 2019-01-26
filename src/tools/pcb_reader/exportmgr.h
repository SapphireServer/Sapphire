#ifndef EXPORTMGR_H
#define EXPORTMGR_H

#include "exporter.h"
#include "navmesh_exporter.h"
#include "obj_exporter.h"
#include "threadpool.h"

class ExportMgr
{
public:
  ExportMgr( unsigned int maxJobs = 0 )
  {
    m_threadpool.addWorkers( maxJobs );
  }
  ~ExportMgr()
  {
    waitForTasks();
  }

  void restart( bool cancel = false, unsigned int maxJobs = 0 )
  {
    if( cancel )
      m_threadpool.cancel();

    m_threadpool.complete();

    m_threadpool.addWorkers( maxJobs );
  }

  void exportZone(const ExportedZone& zone, ExportFileType exportFileTypes)
  {
    m_threadpool.queue( [zone, exportFileTypes]()
    {
      if( exportFileTypes & ExportFileType::WavefrontObj )
        ObjExporter::exportZone( zone );

      if( exportFileTypes & ExportFileType::Navmesh )
        NavmeshExporter::exportZone( zone );
    } );
  }

  void exportGroup( const std::string& zoneName, const ExportedGroup& group, ExportFileType exportFileTypes )
  {
    m_threadpool.queue( [zoneName, group, exportFileTypes]()
    {
      if( exportFileTypes & ExportFileType::WavefrontObj )
      {
        ObjExporter::exportGroup( zoneName, group );
      }
      if( exportFileTypes & ExportFileType::Navmesh )
      {
        NavmeshExporter::exportGroup( zoneName, group );
      }
    });
  }

  void waitForTasks()
  {
    m_threadpool.complete();
  }
private:
  ThreadPool m_threadpool;
};

#endif