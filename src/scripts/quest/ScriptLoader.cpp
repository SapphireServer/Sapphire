#include <Script/NativeScriptApi.h>

#include "ManFst001.cpp"
#include "ManFst002.cpp"
#include "ManFst003.cpp"
#include "ManFst004.cpp"
#include "ManSea001.cpp"
#include "ManSea002.cpp"
#include "ManSea003.cpp"
#include "ManWil001.cpp"
#include "ManWil002.cpp"
#include "subquest/gridania/SubFst001.cpp"
#include "subquest/gridania/SubFst002.cpp"
#include "subquest/gridania/SubFst003.cpp"
#include "subquest/gridania/SubFst004.cpp"
#include "subquest/gridania/SubFst005.cpp"
#include "subquest/gridania/SubFst008.cpp"
#include "subquest/gridania/SubFst009.cpp"
#include "subquest/gridania/SubFst010.cpp"
#include "subquest/gridania/SubFst011.cpp"
#include "subquest/gridania/SubFst013.cpp"
#include "subquest/gridania/SubFst014.cpp"
#include "subquest/gridania/SubFst015.cpp"
#include "subquest/gridania/SubFst019.cpp"
#include "subquest/gridania/SubFst026.cpp"
#include "subquest/gridania/SubFst029.cpp"
#include "subquest/gridania/SubFst030.cpp"
#include "subquest/gridania/SubFst041.cpp"
#include "subquest/gridania/SubFst045.cpp"
#include "subquest/limsa/SubSea001.cpp"
#include "subquest/limsa/SubSea012.cpp"
#include "subquest/uldah/SubWil000.cpp"
#include "subquest/uldah/SubWil001.cpp"
#include "subquest/uldah/SubWil002.cpp"
#include "subquest/uldah/SubWil004.cpp"
#include "subquest/uldah/SubWil006.cpp"
#include "subquest/uldah/SubWil007.cpp"
#include "subquest/uldah/SubWil018.cpp"
#include "subquest/uldah/SubWil019.cpp"
#include "subquest/uldah/SubWil021.cpp"
#include "subquest/uldah/SubWil022.cpp"
#include "subquest/uldah/SubWil027.cpp"
#include "subquest/uldah/SubWil028.cpp"
#include "subquest/uldah/SubWil029.cpp"

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManFst001 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManFst002 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManFst003 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManFst004 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManSea001 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManSea002 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManSea003 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManWil001 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ManWil002 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst001 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst002 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst003 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst004 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst005 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst008 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst009 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst010 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst011 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst013 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst014 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst015 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst019 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst026 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst029 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst030 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst041 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubFst045 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubSea001 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubSea012 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil000 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil001 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil002 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil004 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil006 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil007 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil018 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil019 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil021 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil022 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil027 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil028 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SubWil029 ),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
