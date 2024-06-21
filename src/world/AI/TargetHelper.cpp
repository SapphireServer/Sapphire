#include "TargetHelper.h"

#include <algorithm>

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Actor/Player.h>
#include <Manager/PartyMgr.h>
#include <Manager/RNGMgr.h>
#include <Util/UtilMath.h>
#include <Service.h>

namespace Sapphire::World::AI
{

  bool InsideRadiusFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = Common::Util::distance( pSrc->getPos(), pTarget->getPos() ) <= m_distance;
    return m_negate ? !ret : ret;
  }

  bool OutsideRadiusFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = Common::Util::distance( pSrc->getPos(), pTarget->getPos() ) >= m_distance;
    return m_negate ? !ret : ret;
  }

  bool PlayerFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = pTarget->isPlayer();
    return m_negate ? !ret : ret;
  }

  bool AllyFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = false;
    // todo: pets, companions, enpc
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

  bool OwnBattalionFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    return false;
  }

  bool TankFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = pTarget->getRole() == Common::Role::Tank;
    return m_negate ? !ret : ret;
  }

  bool HealerFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = pTarget->getRole() == Common::Role::Healer;
    return m_negate ? !ret : ret;
  }

  bool DpsFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
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

  bool HasStatusEffectFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    auto ret = pTarget->hasStatusEffect( m_statusId );
    return m_negate ? !ret : ret;
  }

  bool TopAggroFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    auto pBNpc = pSrc->getAsBNpc();
    bool ret = false;
    if( pBNpc )
    {
      ret = pBNpc->hateListGetHighest() == pTarget;
    }
    return m_negate ? !ret : ret;
  }

  bool SecondAggroFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
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

  bool PartyMemberFilter::isApplicable( Entity::CharaPtr& pSrc, Entity::CharaPtr& pTarget ) const
  {
    bool ret = false;
    // todo: pets, companions, enpc
    if( auto pPlayer = pSrc->getAsPlayer() )
    {
      if( auto pTargetPlayer = pTarget->getAsPlayer() )
      {
        ret = pPlayer->getPartyId() == pTargetPlayer->getPartyId();
      }
      else if( auto pBNpc = pTarget->getAsBNpc() )
      {
        ret = pBNpc->getBNpcType() == 0;
      }
    }
    else if( auto pBNpc = pSrc->getAsBNpc() )
    {
      if( auto pTargetPlayer = pTarget->getAsPlayer() )
      {
        ret = pPlayer->getPartyId() == pTargetPlayer->getPartyId();
      }
      else if( auto pTargetBNpc = pTarget->getAsBNpc() )
      {
        ret = pBNpc->getBNpcType() == pTargetBNpc->getEnemyType();
      }
    }
    return m_negate ? !ret : ret;
  }

  void Snapshot::createSnapshot( Entity::CharaPtr pSrc, const std::set< Entity::GameObjectPtr >& inRange,
                                 int count, bool fillWithRandom, const std::vector< uint32_t >& exclude )
  {
    m_results.clear();
    m_targetIds.clear();

    auto& RNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
    for( const auto& pActor : inRange )
    {
      auto pChara = pActor->getAsChara();
      if( pChara == nullptr )
        continue;

      // exclude this character from the result set
      auto excludeIt = std::find_if( exclude.begin(), exclude.end(),
        [ pChara ]( uint32_t id ) { return pChara->getId() == id; }
      );
      if( excludeIt != exclude.end() )
        continue;

      bool matches = true;
      for( const auto& filter : m_filters )
      {
        if( !filter->isApplicable( pSrc, pChara ) )
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

        m_results.push_back( entry );
        if( m_results.size() == count ) break;
      }
    }

    // fallback to fill with random entries if we dont have enough valid results
    if( fillWithRandom && m_results.size() < count )
    {
      std::vector< Entity::CharaPtr > remaining;
      for( const auto& pActor : inRange )
      {
        auto pChara = pActor->getAsChara();
        if( pChara == nullptr )
          continue;

        auto excludeIt = std::find_if( exclude.begin(), exclude.end(),
          [ pChara ]( uint32_t id ) { return pChara->getId() == id; }
        );

        if( excludeIt == exclude.end() && std::find_if( m_results.begin(), m_results.end(),
            [ &pChara ]( CharaEntry entry ) { return entry.m_entityId == pChara->getId(); } ) == m_results.end() )
        {
          remaining.push_back( pChara );
        }
      }
      while( m_results.size() < count && !remaining.empty() )
      {
        // idk
        std::shuffle( remaining.begin(), remaining.end(), *RNGMgr.getRNGEngine() );

        auto pChara = remaining.back();
        CharaEntry entry;
        entry.m_entityId = pChara->getId();
        entry.m_pos = pChara->getPos();
        entry.m_rot = pChara->getRot();
        m_results.emplace_back( entry );
        remaining.pop_back();
      }
    }

    // sort by distance at the end always
    auto srcPos = pSrc->getPos();
    std::sort( m_results.begin(), m_results.end(),
      [ srcPos ]( CharaEntry l, CharaEntry r )
      {
        return Common::Util::distance( srcPos, l.m_pos ) < Common::Util::distance( srcPos, r.m_pos );
      }
    );

    // we might want the target ids separately
    m_targetIds.resize( m_results.size() );
    for( auto i = 0; i < m_results.size(); ++i )
      m_targetIds[ i ] = m_results[ i ].m_entityId;
  }

  const std::vector< Snapshot::CharaEntry >& Snapshot::getResults() const
  {
    return m_results;
  }

  const std::vector< uint32_t >& Snapshot::getTargetIds() const
  {
    return m_targetIds;
  }

};// namespace Sapphire::World::AI