#include <ScriptObject.h>
#include <Actor/Player.h>

#include "DatCategories/InstanceObjectParser.h"
#include "Manager/HousingMgr.h"
#include "Script/NativeScriptApi.h"

using namespace Sapphire;

class S1f2 : public Sapphire::ScriptAPI::ZoneScript
{
public:
  S1f2() : Sapphire::ScriptAPI::ZoneScript( 135 )
  {
  }


};

EXPOSE_SCRIPT( S1f2 );
