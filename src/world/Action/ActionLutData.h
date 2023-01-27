#include "ActionLut.h"
#include <nlohmann/json.hpp>

namespace Sapphire::World::Action
{
  class ActionLutData
  {
    public:
      static bool cacheActions();
      static bool reloadActions();
  };

  inline void from_json( const nlohmann::json& j, StatusEntry& statusEntry )
  {
    j.at( "id" ).get_to( statusEntry.id );
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