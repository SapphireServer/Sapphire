#pragma once

#include <ForwardsZone.h>
#include <Script/NativeScriptApi.h>

#include <Event/EventDefs.h>

#define EXPOSE_SCRIPT( className ) Sapphire::ScriptAPI::ScriptObject* makeScript##className() { return new className; }

