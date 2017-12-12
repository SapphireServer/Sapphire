#ifndef SAPPHIRE_SCRIPTLOADER_H
#define SAPPHIRE_SCRIPTLOADER_H

#include <string>
#include "NativeScriptApi.h"
#include "ScriptInfo.h"
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
typedef HMODULE ModuleHandle;
#else
#include <dlfcn.h>
typedef void* ModuleHandle;
#endif

namespace Core {
namespace Scripting {

   class ScriptLoader {
   protected:
       std::unordered_map< std::string, ScriptInfo* > m_scriptMap;

       bool unloadModule( ModuleHandle );

   public:
       ScriptLoader();

       const std::string getModuleExtension();
       ScriptInfo* loadModule( std::string );
       bool unloadScript( ScriptInfo* );
       bool unloadScript( ModuleHandle );
       ScriptInfo* getScriptInfo( std::string name );
       ScriptObject* getScriptObjectExport( ModuleHandle handle, std::string name );
       bool isModuleLoaded( std::string name );

       template< typename T >
       T* getScriptObject( ModuleHandle handle, std::string name )
       {
          return static_cast< T* >( getScriptObjectExport( handle, name ) );
       }
   };

}
}




#endif //SAPPHIRE_SCRIPTLOADER_H
