#include "Util/Paths.h"

// Based on: https://github.com/Coollab-Art/exe_path (BSL-1.0)

#if defined( _WIN32 )
#include <ShlObj.h>
#include <windows.h>

static auto executable_path_impl() -> std::filesystem::path
{
  char path[ MAX_PATH ];// NOLINT(*avoid-c-arrays)
  GetModuleFileNameA( nullptr, path, MAX_PATH );
  return path;
}
#elif defined( __linux__ )
#include <limits.h>
#if defined( __sun )
#define PROC_SELF_EXE "/proc/self/path/a.out"
#else
#define PROC_SELF_EXE "/proc/self/exe"
#endif

static auto executable_path_impl() -> std::filesystem::path
{
  char buffer[ PATH_MAX ];
  const char* const path = realpath( PROC_SELF_EXE, buffer );
  return path;
}
#elif defined( __APPLE__ )
#include <mach-o/dyld.h>
#include <sys/syslimits.h>

static auto executable_path_impl() -> std::filesystem::path
{
  char raw_path_name[ PATH_MAX ];
  char real_path_name[ PATH_MAX ];
  auto raw_path_size = static_cast< uint32_t >( sizeof( raw_path_name ) );
  if( !_NSGetExecutablePath( raw_path_name, &raw_path_size ) )
  {
    realpath( raw_path_name, real_path_name );
  }
  return real_path_name;
}
#else
#error "Unsupported platform"
#endif

namespace Sapphire::Common::Util
{
  std::filesystem::path executablePath()
  {
    static auto const path = std::filesystem::weakly_canonical( executable_path_impl() );
    return path;
  }
  std::filesystem::path executableDir()
  {
    static auto const path = executablePath().parent_path();
    return path;
  }
}// namespace Sapphire::Common::Util
