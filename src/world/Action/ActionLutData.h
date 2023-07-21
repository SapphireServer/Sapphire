#include "ActionLut.h"
#include "Common.h"
#include <nlohmann/json.hpp>

namespace Sapphire::World::Action
{
  class ActionLutData
  {
    public:
      static bool cacheActions();
      static bool reloadActions();

      static std::unordered_map< std::string, Common::ParamModifier > m_modifierStringMap;
  };

  inline void from_json( const nlohmann::json& j, StatusModifier& statusModifier )
  {
    auto stringKey = j.at( "modifier" ).get< std::string >();
    j.at( "value" ).get_to( statusModifier.value );

    auto enumKey = ActionLutData::m_modifierStringMap.find( stringKey );
    if( enumKey != ActionLutData::m_modifierStringMap.end() )
    {
      statusModifier.modifier = enumKey->second;
    }
    else
    {
      statusModifier.modifier = Common::ParamModifier::None;
    }
  }

  inline void from_json( const nlohmann::json& j, StatusEntry& statusEntry )
  {
    j.at( "id" ).get_to( statusEntry.id );
    j.at( "duration" ).get_to( statusEntry.duration );
    if( j.contains( "flag" ) )
      j.at( "flag" ).get_to( statusEntry.flag );
    if( j.contains( "canApplyMultipleTimes" ) )
      j.at( "canApplyMultipleTimes" ).get_to( statusEntry.canApplyMultipleTimes ); 
    if( j.contains( "modifiers" ) )
      j.at( "modifiers" ).get_to( statusEntry.modifiers );
  }

  inline void from_json( const nlohmann::json& j, ActionEntry& action )
  {
    j.at( "potency" ).get_to( action.potency );
    j.at( "comboPotency" ).get_to( action.comboPotency );
    j.at( "flankPotency" ).get_to( action.flankPotency );
    j.at( "frontPotency" ).get_to( action.frontPotency );
    j.at( "rearPotency" ).get_to( action.rearPotency );
    j.at( "curePotency" ).get_to( action.curePotency );
    j.at( "restorePercentage" ).get_to( action.restoreMPPercentage );
    j.at( "nextCombo" ).get_to( action.nextCombo );
    j.at( "statuses" ).at( "caster" ).get_to( action.statuses.caster );
    j.at( "statuses" ).at( "target" ).get_to( action.statuses.target );
  }
}