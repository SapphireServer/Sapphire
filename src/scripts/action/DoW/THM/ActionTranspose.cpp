#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>
#include <Action/Job/THM/AstralUmbral.h>


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
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( auto pAstral = THM::getAstralFire( pSource ) )
    {
      THM::setUmbralIce( pSource, pActionBuilder, 1 );
    }
    else if( auto pUmbral = THM::getUmbralIce( pSource ) )
    {
      THM::setAstralFire( pSource, pActionBuilder, 1 );
    }
  }
};

EXPOSE_SCRIPT( ActionTranspose );