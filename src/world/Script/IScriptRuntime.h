#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <set>
#include <string>
#include <typeinfo>

#include "NativeScriptApi.h"

namespace Sapphire::Scripting
{
  class ScriptInfo;

  class IScriptRuntime
  {
  public:
    virtual ~IScriptRuntime() = default;

    virtual void unloadAll() = 0;
    virtual bool loadScript( const std::string& path ) = 0;
    virtual bool unloadScript( const std::string& name ) = 0;
    virtual void queueScriptReload( const std::string& name ) = 0;
    virtual void findScripts( std::set< ScriptInfo* >& scripts, const std::string& search ) = 0;
    virtual void processLoadQueue() = 0;
    virtual std::string getModuleExtension() = 0;
    virtual std::string getModuleNameForPath( const std::string& path ) = 0;
    virtual bool isModuleLoaded( const std::string& name ) = 0;
    virtual ScriptAPI::ScriptObject* getScriptObject( std::size_t type, uint32_t scriptId ) = 0;

    template< typename T >
    T* getScript( uint32_t scriptId )
    {
      return dynamic_cast< T* >( getScriptObject( typeid( T ).hash_code(), scriptId ) );
    }
  };

  using IScriptRuntimePtr = std::shared_ptr< IScriptRuntime >;
}
