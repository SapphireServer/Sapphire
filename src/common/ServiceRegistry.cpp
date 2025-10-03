#include "ServiceRegistry.h"

#ifdef _WIN32
#include <Windows.h>
#include <cwchar>
#endif

namespace Sapphire::Common::detail
{
  struct Registry
  {
    std::unordered_map< std::string, std::shared_ptr< void > > map;
    std::mutex mtx;
  };

  static Registry *get_registry() noexcept
  {
#ifdef _WIN32
    // Share the registry pointer across all modules in the process using
    // the process environment block as a simple key-value store.
    // This avoids per-module statics while keeping implementation minimal.
    wchar_t buf[ 64 ] = { 0 };
    DWORD n = GetEnvironmentVariableW( L"SAPPHIRE_SVC_REG_PTR", buf, static_cast< DWORD >( std::size( buf ) ) );
    if( n > 0 && n < std::size( buf ) )
    {
      unsigned long long val = 0ULL;
      if( swscanf_s( buf, L"%llx", &val ) == 1 )
        return reinterpret_cast< Registry * >( static_cast< uintptr_t >( val ) );
    }
    // Not set yet: allocate and publish
    Registry *reg = new( std::nothrow ) Registry();
    if( !reg )
      return nullptr;
    wchar_t out[ 64 ] = { 0 };
    unsigned long long addr = static_cast< unsigned long long >( reinterpret_cast< uintptr_t >( reg ) );
    _ui64tow_s( addr, out, std::size( out ), 16 );
    SetEnvironmentVariableW( L"SAPPHIRE_SVC_REG_PTR", out );
    return reg;
#else
    // Fallback for non-Windows: regular process-wide static
    static Registry reg;
    return &reg;
#endif
  }

  std::shared_ptr< void >& service_slot_by_name( const std::string& key ) noexcept
  {
    Registry *reg = get_registry();
    // In extremely low-memory conditions, reg could be null; handle gracefully
    static std::shared_ptr< void > dummy;
    if( !reg )
      return dummy;

    std::lock_guard< std::mutex > lock( reg->mtx );
    auto it = reg->map.find( key );
    if( it == reg->map.end() )
    {
      it = reg->map.emplace( key, std::shared_ptr< void >{} ).first;
    }
    return it->second;
  }
}
