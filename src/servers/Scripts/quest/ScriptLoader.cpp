#include <Script/NativeScriptApi.h>

#include "ManFst004.cpp"
#include "ManSea002.cpp"
#include "ManFst002.cpp"
#include "ManFst003.cpp"
#include "ManWil001.cpp"
#include "ManWil002.cpp"
#include "ManFst001.cpp"
#include "subquest/gridania/SubFst002.cpp"
#include "subquest/gridania/SubFst013.cpp"
#include "subquest/gridania/SubFst001.cpp"
#include "subquest/gridania/SubFst010.cpp"
#include "ManSea001.cpp"

const ScriptObject* ptrs[] =
{
   static_cast< ScriptObject* >( new ManFst004 ),
   static_cast< ScriptObject* >( new ManSea002 ),
   static_cast< ScriptObject* >( new ManFst002 ),
   static_cast< ScriptObject* >( new ManFst003 ),
   static_cast< ScriptObject* >( new ManWil001 ),
   static_cast< ScriptObject* >( new ManWil002 ),
   static_cast< ScriptObject* >( new ManFst001 ),
   static_cast< ScriptObject* >( new SubFst002 ),
   static_cast< ScriptObject* >( new SubFst013 ),
   static_cast< ScriptObject* >( new SubFst001 ),
   static_cast< ScriptObject* >( new SubFst010 ),
   static_cast< ScriptObject* >( new ManSea001 ),

   nullptr
};

extern "C" EXPORT const ScriptObject** getScripts()
{
   return ptrs;
}
