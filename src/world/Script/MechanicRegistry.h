#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include "NativeScriptApi.h"

namespace Sapphire::Scripting
{
  class NativeScriptMgr;

  class MechanicRegistry
  {
  public:
    bool contains( std::string_view scriptName ) const;
    std::shared_ptr< ScriptAPI::MechanicScript > create( std::string_view scriptName ) const;

    bool invoke( std::string_view scriptName,
                 ScriptAPI::MechanicScript& instance,
                 std::string_view function,
                 const nlohmann::json& args,
                 World::Encounter::TimelinePack& pack,
                 World::Encounter::EncounterPtr pEncounter ) const;

  private:
    friend class NativeScriptMgr;

    bool registerDefinition( ScriptAPI::MechanicScriptDefinition& definition );
    void unregisterDefinition( const ScriptAPI::MechanicScriptDefinition& definition );
    void clear();

    std::unordered_map< std::string, ScriptAPI::MechanicScriptDefinition* > m_definitions;
  };
}
