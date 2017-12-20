#ifndef SAPPHIRE_SCRIPTLOADER_H
#define SAPPHIRE_SCRIPTLOADER_H

#include <string>
#include <unordered_map>
#include <set>

#include "NativeScriptApi.h"
#include "ScriptInfo.h"

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
       ScriptInfo* loadModule( const std::string& );
       bool unloadScript( ScriptInfo* );
       bool unloadScript( ModuleHandle );
       ScriptInfo* getScriptInfo( std::string name );
       ScriptObject* getScriptObject( ModuleHandle handle );
       bool isModuleLoaded( std::string name );

       void findScripts( std::set< Core::Scripting::ScriptInfo* >& scripts, const std::string& search );
   };

}
}




#endif //SAPPHIRE_SCRIPTLOADER_H
