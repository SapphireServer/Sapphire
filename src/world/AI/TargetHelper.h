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
      AllianceC,

      IsDead
    };

  protected:
    Type m_type;
    bool m_negate{ false };
    bool m_enforceOnRandom{ false };

  public:
    TargetSelectFilter( Type type, bool negate, bool enforceOnRandom ) :
      m_type( type ),
      m_negate( negate ),
      m_enforceOnRandom( enforceOnRandom )
    {
    }

    TargetSelectFilter( Type type ) :
      m_type( type )
    {
    }

    virtual ~TargetSelectFilter()
    {
    }

    virtual bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
    {
      return false;
    };

    void setNegate( bool val )
    {
      m_negate = val;
    }

    bool isNegate() const
    {
      return m_negate;
    }

    bool isEnforcedOnRandomFill() const
    {
      return m_enforceOnRandom;
    }

    void setEnforcedOnRandomFill( bool val )
    {
      m_enforceOnRandom = val;
    }
  };
  using TargetSelectFilterPtr = std::shared_ptr< TargetSelectFilter >;

  class InsideRadiusFilter : public TargetSelectFilter
  {
  private:
    float m_distance{ 0 };

  public:
    InsideRadiusFilter( float distance ) :
      TargetSelectFilter( Type::InsideRadius ),
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
    OutsideRadiusFilter( float distance ) :
      TargetSelectFilter( Type::OutsideRadius ),
      m_distance( distance )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class PlayerFilter : public TargetSelectFilter
  {
  public:
    PlayerFilter() :
      TargetSelectFilter( Type::Player )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class AllyFilter : public TargetSelectFilter
  {
  public:
    AllyFilter() :
      TargetSelectFilter( Type::Ally )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class OwnBattalionFilter : public TargetSelectFilter
  {
  public:
    OwnBattalionFilter() :
      TargetSelectFilter( Type::OwnBattalion )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class TankFilter : public TargetSelectFilter
  {
  public:
    TankFilter() :
      TargetSelectFilter( Type::Tank )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class HealerFilter : public TargetSelectFilter
  {
  public:
    HealerFilter() :
      TargetSelectFilter( Type::Healer )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class DpsFilter : public TargetSelectFilter
  {
  public:
    DpsFilter() :
      TargetSelectFilter( Type::Dps )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class HasStatusEffectFilter : public TargetSelectFilter
  {
  private:
    uint32_t m_statusId{ 0 };
  public:
    HasStatusEffectFilter( uint32_t statusId ) :
      TargetSelectFilter( Type::HasStatusEffect ),
      m_statusId( statusId )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class TopAggroFilter : public TargetSelectFilter
  {
  public:
    TopAggroFilter() :
      TargetSelectFilter( Type::TopAggro )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class SecondAggroFilter : public TargetSelectFilter
  {
  public:
    SecondAggroFilter() :
      TargetSelectFilter( Type::SecondAggro )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class PartyMemberFilter : public TargetSelectFilter
  {
  public:
    PartyMemberFilter() :
      TargetSelectFilter( Type::PartyMember )
    {
    }

    bool isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const override;
  };

  class IsDeadFilter : public TargetSelectFilter
  {
  public:
    IsDeadFilter() :
      TargetSelectFilter( Type::IsDead )
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