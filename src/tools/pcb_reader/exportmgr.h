#ifndef EXPORTMGR_H
#define EXPORTMGR_H

#include "exporter.h"
#include "obj_exporter.h"
#include "threadpool.h"

class ExportMgr
{
public:
  ExportMgr(){}
  ~ExportMgr()
  {
    waitForTasks();
  }

  void exportZone(const ExportedZone& zone, ExportFileType exportFileTypes)
  {
    if( exportFileTypes & ExportFileType::WavefrontObj )
    {
      m_threadpool.queue( [zone](){ ObjExporter::exportZone( zone ); } );
    }
  }

  void exportGroup( const std::string& zoneName, const ExportedGroup& group, ExportFileType exportFileTypes )
  {
    if( exportFileTypes & ExportFileType::WavefrontObj )
    {
      m_threadpool.queue( [zoneName, group](){ ObjExporter::exportGroup( zoneName, group ); } );
    }
  }

  void waitForTasks()
  {
    m_threadpool.complete();
  }
private:
  ThreadPool m_threadpool;
};

#endif