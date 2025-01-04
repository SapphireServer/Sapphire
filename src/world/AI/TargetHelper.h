#ifndef _TARGETHELPER_H
#define _TARGETHELPER_H

#include <memory>
#include <unordered_map>
#include <set>
#include <vector>

#include <ForwardsZone.h>

namespace Sapphire::World::AI
{
  //
  // Filters
  //
  class TargetSelectFilter :
    public std::enable_shared_from_this< TargetSelectFilter >
  {
  public:
    enum class Type
    {
      InsideRadius,
      OutsideRadius,

      Player,
      Ally,
      OwnBattalion,

      Tank,
      Healer,
      Dps,

      HasStatusEffect,

      TopAggro,
      SecondAggro,

      PartyMember,

      AllianceA,
      AllianceB,
      AllianceC
    };

  protected:
    Type m_type;
    bool m_negate{ false };

  public:
    TargetSelectFilter( Type type, bool negate ) :
      m_type( type ),
      m_negate( negate )
    {
    }
    virtual ~TargetSelectFilter()
    {
    }

    virtual bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
    {
      return false;
    };

    bool isNegate() const
    {
      return m_negate;
    }
  };
  using TargetSelectFilterPtr = std::shared_ptr< TargetSelectFilter >;

  class InsideRadiusFilter : public TargetSelectFilter
  {
  private:
    float m_distance{ 0 };

  public:
    InsideRadiusFilter( float distance, bool negate ) :
      TargetSelectFilter( Type::InsideRadius, negate ),
      m_distance( distance )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class OutsideRadiusFilter : public TargetSelectFilter
  {
  private:
    float m_distance{ 0 };
  public:
    OutsideRadiusFilter( float distance, bool negate ) :
      TargetSelectFilter( Type::OutsideRadius, negate ),
      m_distance( distance )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class PlayerFilter : public TargetSelectFilter
  {
  public:
    PlayerFilter( bool negate ) :
      TargetSelectFilter( Type::Player, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class AllyFilter : public TargetSelectFilter
  {
  public:
    AllyFilter( bool negate ) :
      TargetSelectFilter( Type::Ally, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class OwnBattalionFilter : public TargetSelectFilter
  {
  public:
    OwnBattalionFilter( bool negate ) :
      TargetSelectFilter( Type::OwnBattalion, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class TankFilter : public TargetSelectFilter
  {
  public:
    TankFilter( bool negate ) :
      TargetSelectFilter( Type::Tank, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class HealerFilter : public TargetSelectFilter
  {
  public:
    HealerFilter( bool negate ) :
      TargetSelectFilter( Type::Healer, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class DpsFilter : public TargetSelectFilter
  {
  public:
    DpsFilter( bool negate ) :
      TargetSelectFilter( Type::Dps, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class HasStatusEffectFilter : public TargetSelectFilter
  {
  private:
    uint32_t m_statusId{ 0 };
  public:
    HasStatusEffectFilter( uint32_t statusId, bool negate ) :
      TargetSelectFilter( Type::HasStatusEffect, negate ),
      m_statusId( statusId )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class TopAggroFilter : public TargetSelectFilter
  {
  public:
    TopAggroFilter( bool negate ) :
      TargetSelectFilter( Type::TopAggro, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class SecondAggroFilter : public TargetSelectFilter
  {
  public:
    SecondAggroFilter( bool negate ) :
      TargetSelectFilter( Type::SecondAggro, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class PartyMemberFilter : public TargetSelectFilter
  {
  public:
    PartyMemberFilter( bool negate ) :
      TargetSelectFilter( Type::PartyMember, negate )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  //
  // Helpers
  //
  class Snapshot :
    public std::enable_shared_from_this< Snapshot >
  {
  public:
    struct CharaEntry
    {
      uint32_t m_entityId;
      Common::FFXIVARR_POSITION3 m_pos;
      float m_rot;
      // todo: status effects?
    };
    using Results = std::vector< CharaEntry >;
    using TargetIds = std::vector< uint32_t >;
  private:
    std::vector< CharaEntry > m_results;
    std::vector< uint32_t > m_targetIds;

  public:
    Snapshot() {}

    void createSnapshot( Entity::CharaPtr pSrc, const std::set< Entity::GameObjectPtr >& inRange,
                         uint32_t count, bool fillWithRandom,
                         const std::vector< TargetSelectFilterPtr >& filters,
                         const std::vector< uint32_t >& exclude = {} );

    // returns actors sorted by distance
    const std::vector< CharaEntry >& getResults() const;
    const std::vector< uint32_t >& getTargetIds() const;
    void clearResults();
  };
  using SnapshotPtr = std::shared_ptr< Snapshot >;
}// namespace Sapphire::World::AI

#endif