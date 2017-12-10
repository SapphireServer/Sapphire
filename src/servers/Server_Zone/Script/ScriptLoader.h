#ifndef SAPPHIRE_SCRIPTLOADER_H
#define SAPPHIRE_SCRIPTLOADER_H

#include <string>
#include "NativeScriptApi.h"

#ifdef _WIN32
#include <windows.h>
#include <unordered_map>

typedef HMODULE ModuleHandle;
#else
#include <dlfcn.h>
typedef void* ModuleHandle;
#endif

namespace Core {
namespace Scripting {

   class ScriptLoader {
   protected:
       std::unordered_map< std::string, ModuleHandle > m_moduleMap;

       bool unloadModule( ModuleHandle );

   public:
       ScriptLoader() = default;

       const std::string getModuleExtension();
       ModuleHandle loadModule( std::string );
       bool unloadScript( std::string );
       bool unloadScript( ModuleHandle );

       template< typename T >
       T* getScriptObject( ModuleHandle );
   };

}
}




#endif //SAPPHIRE_SCRIPTLOADER_H
