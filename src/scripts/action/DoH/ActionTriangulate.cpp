#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>
#include <Actor/BNpc.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTriangulate : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTriangulate() : Sapphire::ScriptAPI::ActionScript( Triangulate )
  {
  }

  static constexpr auto Flags = static_cast< uint32_t >( Common::StatusEffectFlag::Permanent ) |
                                static_cast< uint32_t >( Common::StatusEffectFlag::CanStatusOff );

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( pSource->hasStatusEffect( TriangulateStatus ) )
      pSource->removeSingleStatusEffectById( TriangulateStatus );
    else
      pActionBuilder->applyStatusEffectSelf( TriangulateStatus, 0, 0, {}, Flags, false );// Todo: missing something...
  }
};

EXPOSE_SCRIPT( ActionTriangulate );