#ifndef CORE_SCRIPTLOADER_H
#define CORE_SCRIPTLOADER_H

#include <unordered_map>
#include <set>

#include "NativeScriptApi.h"
#include "ScriptInfo.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

#include <winbase.h>

using ModuleHandle = HMODULE;
#else
#include <dlfcn.h>
using ModuleHandle = void*;
#endif

namespace Core {
namespace Scripting {

/*!
 * @brief Provides low level functionality for loading modules on different platforms along with managing those loaded modules.
 */
class ScriptLoader
{
protected:
  /*!
   * @brief The internal list of all modules that are loaded.
   */
  std::unordered_map< std::string, ScriptInfo* > m_scriptMap;

  /*!
   * @brief Unload a loaded module from it's ModuleHandle
   *
   * @return true if the unload was successful, false if not
   */
  bool unloadModule( ModuleHandle );

public:
  ScriptLoader() = default;

  /*!
   * @brief Gets the module file extention for the current platform (windows, linux, osx)
   *
   * @return The file extension for the current platform
   */
  const std::string getModuleExtension();

  /*!
   * @brief Load a module from a path
   *
   * Internally, this will also copy the module from it's original folder into the cache folder.
   *
   * @return A pointer to ScriptInfo if the load was successful, nullptr if it failed
   */
  ScriptInfo* loadModule( const std::string& );

  /*!
   * @brief Unload a script from it's ScriptInfo object
   *
   * @return true if successful, false if not
   */
  bool unloadScript( ScriptInfo* );

  /*!
   * @brief Unload a script via it's module handle
   *
   * @return true if successful, false if not
   */
  bool unloadScript( ModuleHandle );

  /*!
   * @brief Look up a ScriptInfo* by a module name
   *
   * @param name The exact module name to search for, case-sensitive
   * @return The ScriptInfo ptr if successful, nullptr if it wasn't found
   */
  ScriptInfo* getScriptInfo( std::string name );

  /*!
   * @brief Get all scripts assoicated with a module
   *
   * @param handle The handle to the module
   * @return An array of unknown size ending with nullptr if success, nullptr if not
   */
  ScriptObject** getScripts( ModuleHandle handle );

  /*!
   * @brief Checks to see if a module with the specified name exists
   *
   * @param name The module name to lookup
   * @return true if loaded, false if not
   */
  bool isModuleLoaded( std::string name );

  /*!
   * @brief Case-insensitive search for modules, useful for debug commands
   *
   * @param scripts a set of ScriptInfo ptrs
   * @param search the search term
   */
  void findScripts( std::set< Core::Scripting::ScriptInfo* >& scripts, const std::string& search );
};

}
}


#endif // CORE_SCRIPTLOADER_H
