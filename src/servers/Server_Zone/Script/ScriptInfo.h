#ifndef SAPPHIRE_SCRIPTINFO_H
#define SAPPHIRE_SCRIPTINFO_H

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

      std::string script_name;
      ModuleHandle handle;
      ScriptObject* script;
      ScriptType type;
   };
}
}


#endif //SAPPHIRE_SCRIPTINFO_H
