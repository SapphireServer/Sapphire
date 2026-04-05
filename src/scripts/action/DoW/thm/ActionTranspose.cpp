#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>



using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTranspose : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTranspose() : Sapphire::ScriptAPI::ActionScript( ActionSkill::Transpose )
  {
  }
    
  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    Logger::debug( "Transpose not yet implemented!" );
  }
};

EXPOSE_SCRIPT( ActionTranspose );