#include "TargetHelper.h"

#include <algorithm>

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Manager/RNGMgr.h>
#include <Util/UtilMath.h>
#include <Service.h>

namespace Sapphire::World::AI
{

  bool InsideRadiusFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = Common::Util::distance( pSrc->getPos(), pTarget->getPos() ) <= m_distance;
    return m_negate ? !ret : ret;
  }

  bool OutsideRadiusFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = Common::Util::distance( pSrc->getPos(), pTarget->getPos() ) >= m_distance;
    return m_negate ? !ret : ret;
  }

  bool PlayerFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = pTarget->isPlayer();
    return m_negate ? !ret : ret;
  }

  bool AllyFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = false;
    if( pSrc->isPlayer() )
    {
      auto pBNpcTarget = pTarget->getAsBNpc();
      if( pBNpcTarget && pBNpcTarget->getEnemyType() == 0 )
        ret = true;
      else if( pTarget->isPlayer() )
        ret = true;
    }
    else if( pSrc->isBattleNpc() )
    {
      auto pBNpcTarget = pTarget->getAsBNpc();
      if( pBNpcTarget && pBNpcTarget->getEnemyType() == 0 )
        ret = true;
      else if( pTarget->isPlayer() )
        ret = true;
    }

    return m_negate ? !ret : ret;
  }

  bool OwnBattalionFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    return false;
  }

  bool TankFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = pTarget->getRole() == Common::Role::Tank;
    return m_negate ? !ret : ret;
  }

  bool HealerFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = pTarget->getRole() == Common::Role::Healer;
    return m_negate ? !ret : ret;
  }

  bool DpsFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = true;
    switch( pTarget->getRole() )
    {
      case Common::Role::Melee:
      case Common::Role::RangedMagical:
      case Common::Role::RangedPhysical:
        ret = true;
        break;
      default:
        ret = false;
        break;
    }
    return m_negate ? !ret : ret;
  }

  bool HasStatusEffectFilter::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    auto ret = pTarget->hasStatusEffect( m_statusId );
    return m_negate ? !ret : ret;
  }

  bool TopAggroFilter ::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    auto pBNpc = pSrc->getAsBNpc();
    bool ret = false;
    if( pBNpc )
    {
      ret = pBNpc->hateListGetHighest() == pTarget;
    }
    return m_negate ? !ret : ret;
  }

  bool SecondAggroFilter ::isConditionMet( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    auto pBNpc = pSrc->getAsBNpc();
    bool ret = false;
    if( pBNpc )
    {
      // todo: this is so dumb

      auto hateList = pBNpc->getHateList();
      std::vector sorted( hateList.begin(), hateList.end() );
      std::sort( sorted.begin(), sorted.end(), []( Entity::HateListEntryPtr a, Entity::HateListEntryPtr b ) {
        return a->m_hateAmount > b->m_hateAmount; } );

      Entity::CharaPtr pChara = nullptr;
      auto topIt = sorted.begin();
      if( topIt != sorted.end() && ++topIt != sorted.end() )
        pChara = topIt->get()->m_pChara;

      ret = pChara == pTarget;
    }
    return m_negate ? !ret : ret;
  }

  void Snapshot::createSnapshot( Entity::CharaPtr pSrc, const std::set< Entity::GameObjectPtr >& inRange,
                                 int count, bool fillWithRandom, const std::set< uint32_t >& exclude )
  {
    m_targets.clear();

    auto& RNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
    for( const auto& pActor : inRange )
    {
      auto pChara = pActor->getAsChara();
      if( pChara == nullptr )
        continue;

      if( exclude.find( pChara->getId() ) != exclude.end() ) continue;

      bool matches = true;
      for( const auto& filter : m_filters )
      {
        if( !filter->isConditionMet( pSrc, pChara ) )
        {
          matches = false;
          break;
        }
      }

      if( matches )
      {
        CharaEntry entry;
        entry.m_entityId = pChara->getId();
        entry.m_pos = pChara->getPos();
        entry.m_rot = pChara->getRot();

        m_targets.push_back( entry );
        if( m_targets.size() == count ) break;
      }
    }

    if( fillWithRandom && m_targets.size() < count )
    {
      std::vector< Entity::CharaPtr > remaining;
      for( const auto& pActor : inRange )
      {
        auto pChara = pActor->getAsChara();
        if( pChara == nullptr )
          continue;

        if( exclude.find( pChara->getId() ) == exclude.end() && std::find_if( m_targets.begin(), m_targets.end(),
            [ &pChara ]( CharaEntry entry ) { return entry.m_entityId == pChara->getId(); } ) == m_targets.end() )
        {
          remaining.push_back( pChara );
        }
      }
      while( m_targets.size() < count && !remaining.empty() )
      {
        // idk
        std::shuffle( remaining.begin(), remaining.end(), *RNGMgr.getRNGEngine().get() );

        auto pChara = remaining.back();
        CharaEntry entry;
        entry.m_entityId = pChara->getId();
        entry.m_pos = pChara->getPos();
        entry.m_rot = pChara->getRot();
        m_targets.emplace_back( entry );
        remaining.pop_back();
      }
    }

    // sort by distance at the end always
    auto srcPos = pSrc->getPos();
    std::sort( m_targets.begin(), m_targets.end(),
      [ srcPos ]( CharaEntry l, CharaEntry r )
      {
        return Common::Util::distance( srcPos, l.m_pos ) < Common::Util::distance( srcPos, r.m_pos );
      }
    );
  }

  const std::vector< Snapshot::CharaEntry >& Snapshot::getResults() const
  {
    return m_targets;
  }

  const std::vector< uint32_t > Snapshot::getTargetIds() const
  {
    std::vector< uint32_t > ret( m_targets.size() );
    for( auto i = 0; i < m_targets.size(); ++i )
      ret[ i ] = m_targets[ i ].m_entityId;
    return ret;
  }

};// namespace Sapphire::World::AI