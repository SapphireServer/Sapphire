#ifndef SAPPHIRE_SCRIPTINFO_H
#define SAPPHIRE_SCRIPTINFO_H

#include <vector>

#include "NativeScriptApi.h"

#ifdef _WIN32
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
      ScriptType type;
   };
}
}


#endif //SAPPHIRE_SCRIPTINFO_H
