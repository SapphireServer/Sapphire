#include "MechanicRegistry.h"

namespace Sapphire::Scripting
{
  bool MechanicRegistry::registerDefinition( ScriptAPI::MechanicScriptDefinition& definition )
  {
    return m_definitions.emplace( definition.getName(), &definition ).second;
  }

  void MechanicRegistry::unregisterDefinition( const ScriptAPI::MechanicScriptDefinition& definition )
  {
    auto it = m_definitions.find( definition.getName() );
    if( it != m_definitions.end() && it->second == &definition )
      m_definitions.erase( it );
  }

  void MechanicRegistry::clear()
  {
    m_definitions.clear();
  }

  bool MechanicRegistry::contains( std::string_view scriptName ) const
  {
    return m_definitions.find( std::string( scriptName ) ) != m_definitions.end();
  }

  std::shared_ptr< ScriptAPI::MechanicScript > MechanicRegistry::create( std::string_view scriptName ) const
  {
    auto it = m_definitions.find( std::string( scriptName ) );
    return it != m_definitions.end() ? it->second->createInstance() : nullptr;
  }

  bool MechanicRegistry::invoke( std::string_view scriptName,
                                 ScriptAPI::MechanicScript& instance,
                                 std::string_view function,
                                 const nlohmann::json& args,
                                 World::Encounter::TimelinePack& pack,
                                 World::Encounter::EncounterPtr pEncounter ) const
  {
    auto definitionIt = m_definitions.find( std::string( scriptName ) );
    if( definitionIt == m_definitions.end() )
      return false;

    auto handler = definitionIt->second->findFunction( function );
    if( !handler )
      return false;

    handler( instance, args, pack, pEncounter );
    return true;
  }
}
