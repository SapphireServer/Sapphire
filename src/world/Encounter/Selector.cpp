#include "Selector.h"

#include <Actor/Chara.h>

namespace Sapphire::Encounter
{
  void Selector::from_json( const nlohmann::json& json )
  {
    const static std::unordered_map< std::string, World::AI::TargetSelectFilter::Type > filterMap =
    {
      { "insideRadius", World::AI::TargetSelectFilter::Type::InsideRadius },
      { "outsideRadius", World::AI::TargetSelectFilter::Type::OutsideRadius },

      { "player", World::AI::TargetSelectFilter::Type::Player },
      { "ally", World::AI::TargetSelectFilter::Type::Ally },
      { "ownBattalion", World::AI::TargetSelectFilter::Type::OwnBattalion },

      { "tank", World::AI::TargetSelectFilter::Type::Tank },
      { "healer", World::AI::TargetSelectFilter::Type::Healer },
      { "dps", World::AI::TargetSelectFilter::Type::Dps },

      { "hasStatusEffect", World::AI::TargetSelectFilter::Type::HasStatusEffect },

      { "topAggro", World::AI::TargetSelectFilter::Type::TopAggro },
      { "secondAggro", World::AI::TargetSelectFilter::Type::SecondAggro },
      { "partyMember", World::AI::TargetSelectFilter::Type::PartyMember }
    };

    m_name = json.at( "name" ).get< std::string >();
    m_fillWithRandom = json.at( "fillRandomEntries" ).get< bool >();
    m_count = json.at( "count" ).get< uint32_t >();

    std::vector< World::AI::TargetSelectFilterPtr > filters;
    auto filtersJ = json.at( "filters" ).items();
    for( const auto& filterJ : filtersJ )
    {
      auto filterV = filterJ.value();
      auto name = filterV.at( "type" ).get< std::string >();
      auto typeId = filterMap.find( name )->second;
      auto negate = filterV.at( "negate" ).get< bool >();

      World::AI::TargetSelectFilterPtr pFilter = nullptr;

      switch( typeId )
      {
        case World::AI::TargetSelectFilter::Type::InsideRadius:
        {
          auto radius = filterV.at( "param" ).get< uint32_t >();
          pFilter = std::make_shared< World::AI::InsideRadiusFilter >( static_cast< float >( radius ), negate );
        }
        break;
        case World::AI::TargetSelectFilter::Type::OutsideRadius:
        {
          auto radius = filterV.at( "param" ).get< uint32_t >();
          pFilter = std::make_shared< World::AI::OutsideRadiusFilter >( static_cast< float >( radius ), negate );
        }
        break;

        case World::AI::TargetSelectFilter::Type::Player:
        {
          pFilter = std::make_shared< World::AI::PlayerFilter >( negate );
        }
        break;
        case World::AI::TargetSelectFilter::Type::Ally:
        {
          pFilter = std::make_shared< World::AI::AllyFilter >( negate );
        }
        break;
        case World::AI::TargetSelectFilter::Type::OwnBattalion:
        {
          pFilter = std::make_shared< World::AI::OwnBattalionFilter >( negate );
        }
        break;

        case World::AI::TargetSelectFilter::Type::Tank:
        {
          pFilter = std::make_shared< World::AI::TankFilter >( negate );
        }
        break;
        case World::AI::TargetSelectFilter::Type::Healer:
        {
          pFilter = std::make_shared< World::AI::HealerFilter >( negate );
        }
        break;
        case World::AI::TargetSelectFilter::Type::Dps:
        {
          pFilter = std::make_shared< World::AI::DpsFilter >( negate );
        }
        break;

        case World::AI::TargetSelectFilter::Type::HasStatusEffect:
        {
          auto statusId = filterV.at( "param" ).get< uint32_t >();
          pFilter = std::make_shared< World::AI::HasStatusEffectFilter >( statusId, negate );
        }
        break;

        case World::AI::TargetSelectFilter::Type::TopAggro:
        {
          pFilter = std::make_shared< World::AI::TopAggroFilter >( negate );
        }
        break;
        case World::AI::TargetSelectFilter::Type::SecondAggro:
        {
          pFilter = std::make_shared< World::AI::SecondAggroFilter >( negate );
        }
        break;

        case World::AI::TargetSelectFilter::Type::PartyMember:
        {
          pFilter = std::make_shared< World::AI::PartyMemberFilter >( negate );
        }
        break;

        default:
          break;
      }
      filters.push_back( pFilter );
    }
    m_snapshot = World::AI::Snapshot( filters );
  }

  void Selector::createSnapshot( Entity::CharaPtr pSrc, const std::vector< uint32_t >& exclude )
  {
    m_snapshot.createSnapshot( pSrc, pSrc->getInRangeActors(), m_count, m_fillWithRandom, exclude );
  }

  const World::AI::Snapshot::Results& Selector::getResults()
  {
    return m_snapshot.getResults();
  }

  const World::AI::Snapshot::TargetIds& Selector::getTargetIds()
  {
    return m_snapshot.getTargetIds();
  }
}// namespace Sapphire::Encounter