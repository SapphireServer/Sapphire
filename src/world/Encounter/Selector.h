#pragma once

#include <cstdint>
#include <AI/TargetHelper.h>

#include <nlohmann/json.hpp>

namespace Sapphire::World::Encounter
{
  class Selector
  {
  private:
    std::string m_name;
    bool m_fillWithRandom{ true };
    uint32_t m_count{ 0 };
    std::vector< World::AI::TargetSelectFilterPtr > m_filters;
    World::AI::Snapshot m_snapshot;

  public:
    Selector(){}
    void createSnapshot( Entity::Chara& src, const std::vector< uint32_t >& exclude = {} );
    const World::AI::Snapshot::Results& getResults();
    const World::AI::Snapshot::TargetIds& getTargetIds();

    uint32_t getResultTargetIdAt( int32_t index ) const;
    const World::AI::Snapshot::CharaEntry& getResultAt( int32_t index ) const;

    void clearResults();
    void from_json( const nlohmann::json& json );
  };
};// namespace Sapphire::Encounter