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

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
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

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
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

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class PlayerFilter : public TargetSelectFilter
  {
  public:
    PlayerFilter( bool negate ) :
      TargetSelectFilter( Type::Player, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class AllyFilter : public TargetSelectFilter
  {
  public:
    AllyFilter( bool negate ) :
      TargetSelectFilter( Type::Ally, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class OwnBattalionFilter : public TargetSelectFilter
  {
  public:
    OwnBattalionFilter( bool negate ) :
      TargetSelectFilter( Type::OwnBattalion, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class TankFilter : public TargetSelectFilter
  {
  public:
    TankFilter( bool negate ) :
      TargetSelectFilter( Type::Tank, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class HealerFilter : public TargetSelectFilter
  {
  public:
    HealerFilter( bool negate ) :
      TargetSelectFilter( Type::Healer, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class DpsFilter : public TargetSelectFilter
  {
  public:
    DpsFilter( bool negate ) :
      TargetSelectFilter( Type::Dps, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
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

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class TopAggroFilter : public TargetSelectFilter
  {
  public:
    TopAggroFilter( bool negate ) :
      TargetSelectFilter( Type::TopAggro, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  class SecondAggroFilter : public TargetSelectFilter
  {
  public:
    SecondAggroFilter( bool negate ) :
      TargetSelectFilter( Type::SecondAggro, negate )
    {
    }

    bool isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const;
  };

  //
  // Helpers
  //
  class Snapshot :
    public std::enable_shared_from_this< Snapshot >
  {
    struct CharaEntry
    {
      uint32_t m_entityId;
      Common::FFXIVARR_POSITION3 m_pos;
      float m_rot;
      // todo: status effects?
    };
  private:
    std::vector< TargetSelectFilterPtr > m_filters;
    std::vector< CharaEntry > m_targets;

public:
    Snapshot( const std::vector< TargetSelectFilterPtr > filters ) :
      m_filters( filters )
    {
    }
    void createSnapshot( Entity::CharaPtr pSrc, const std::set< Entity::GameObjectPtr >& inRange,
                         int count, bool fillWithRandom, const std::set< uint32_t >& exclude = {} );

    // returns actors sorted by distance
    const std::vector< CharaEntry >& getResults() const;
    const std::vector< uint32_t > getTargetIds() const;
  };
  using SnapshotPtr = std::shared_ptr< Snapshot >;
}// namespace Sapphire::World::AI

#endif