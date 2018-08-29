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

/*!
 * @brief An internal class used to track information about loaded modules and their scripts.
 *
 * The main purpose of this is to maintain easy access to the module handle and the pointers to scripts that are loaded.
 * Furthermore, allows for quick and easy cross platform access to the module paths associated with the runtime module cache and its original path.
 */
class ScriptInfo
{
public:
  ScriptInfo() = default;

  /*!
   * @brief The file name of the loaded library.
   *
   * On all platforms, this will be the full filename of the module, eg:
   * - script_instances.dll on Windows
   * - libscript_instances.so on Linux
   */
  std::string library_name;

  /*!
   * @brief The path to the module currently loaded in memory from the cached location.
   */
  std::string cache_path;

  /*!
   * @brief The original path of the module before it was copied to the cache location.
   */
  std::string library_path;

  /*!
   * @brief A handle to the module.
   *
   * The underlying type for this depends on platform. On Windows it's some stupid shit, on everything else it's a void*.
   */
  ModuleHandle handle;

  /*!
   * @brief An internal list of all the pointers to each ScriptObject
   *
   * This is tracked so when we unload this module we can call delete on each ScriptObject and correctly free it from memory.
   */
  std::vector< ScriptObject* > scripts;
};
}
}


#endif //SAPPHIRE_SCRIPTINFO_H
