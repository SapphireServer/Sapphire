#pragma once

#include <ForwardsZone.h>
#include <Script/NativeScriptApi.h>

#include <Event/EventDefs.h>

#define EXPOSE_SCRIPT( className ) Sapphire::ScriptAPI::ScriptObject* makeScript##className() { return new className; }

#define MECHANIC_FUNCTION( methodName )                                               \
  ::Sapphire::ScriptAPI::makeMechanicFunction< MechanicSelf,                         \
                                                &MechanicSelf::methodName >( #methodName )

#define EXPOSE_MECHANIC_SCRIPT( className, ... )                                      \
  Sapphire::ScriptAPI::ScriptObject* makeScript##className()                          \
  {                                                                                   \
    using MechanicSelf = className;                                                   \
    return ::Sapphire::ScriptAPI::makeMechanicDefinition< MechanicSelf >(             \
      #className, { __VA_ARGS__ } );                                                  \
  }

