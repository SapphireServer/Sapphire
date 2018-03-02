#ifndef CORE_SCRIPTINFO_H
#define CORE_SCRIPTINFO_H

#include <vector>

#include "NativeScriptApi.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef HMODULE ModuleHandle;
#else
typedef void* ModuleHandle;
#endif

namespace Core {
namespace Scripting {

   class ScriptInfo
   {
   public:
      ScriptInfo() = default;

      std::string library_name;
      std::string cache_path;
      std::string library_path;

      ModuleHandle handle;
      std::vector< ScriptObject* > scripts;
   };
}
}


#endif //SAPPHIRE_SCRIPTINFO_H
