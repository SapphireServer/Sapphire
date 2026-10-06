#pragma once

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <vector>

#include <ForwardsZone.h>
#include <Vector3.h>
#include <Util/Util.h>

#include <AI/Fsm/StateMachine.h>

namespace Sapphire::World::AI::Controller
{
  class Controller
  {
  public:
    enum class PathType : uint32_t
    {
      None,
      FixedPos,
      PointList,
      TargetId,
      ServerPath
    };

    enum PathFlags : uint32_t
    {
      None = 0x00,
      Infinite = 0x01,
      Interruptible = 0x02,
      CanReversePath = 0x04,
      IgnoreNavmesh = 0x08,
      RecalculatePerTick = 0x10,
      IgnoreActorCollision = 0x20,
      // todo:
      PathToExactPos = 0x40,
      RestoreDefaultPathOnExit = 0x80
    };

    struct Path
    {
      PathType m_type{ PathType::None };
      PathType m_defaultType{ PathType::None };
      PathFlags m_flags{ 0 };
      PathFlags m_defaultFlags{ 0 };
      bool m_active{ false };
      uint32_t m_targetId{ 0xE0000000 };
      Common::Vector3 m_targetPos;
      uint32_t m_currPointIndex{ 0 };
      uint32_t m_prevPointIndex{ 0 };
      uint32_t m_serverPathId{ 0 };
      uint32_t m_defaultServerPathId{ 0 };
      std::vector< Common::Vector3 > m_points;
      std::vector< std::vector< Common::Vector3 > > m_calcPoints;
      uint32_t m_maxLoops{ 0 };
      uint32_t m_loopCount{ 0 };
      bool m_isReversePath{ false };
      float m_targetReachedDist;
      bool m_restoreDefaultPathOnExit{ true };

      Path()
      {
        reset();
      }

      void reset()
      {
        m_type = PathType::None;
        m_flags = PathFlags::None;
        m_active = false;
        m_targetId = 0xE0000000;
        m_currPointIndex = 0;
        m_prevPointIndex = 0;
        m_points.clear();
        m_maxLoops = 0;
        m_loopCount = 0;
        m_isReversePath = false;
        m_targetReachedDist = std::numeric_limits< float >::max();
      }
    };

    explicit Controller( Entity::GameObject& owner ) : m_lastTick( Common::Util::getTimeMs() ),
                                                       m_stateMachine( owner ),
                                                       m_owner( owner )
    {
    }

    virtual ~Controller() = default;

    virtual void initialize();
    virtual void onDetach();

    virtual bool tryAggro( uint32_t targetId );
    virtual void aggro( uint32_t targetId, uint32_t hateAmount = 1 );
    virtual void autoAttack( uint32_t targetId );
    virtual void rangedAutoAttack( uint32_t targetId );
    virtual void deaggro();
    virtual void clearEnmityList();
    virtual void pathTo( const Common::Vector3& pos, float targetReachedDist, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint = {}, const std::function< void() >& onReachDestination = {} );
    virtual void followPath( const std::vector< Common::Vector3 >& path, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint = {}, const std::function< void() >& onReachDestination = {} );
    virtual void followTarget( uint32_t targetId, bool followDuringCombat = false );
    virtual void stopFollowingTarget();
    virtual void followServerPath( uint32_t serverPathId, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint = {}, const std::function< void() >& onReachDestination = {} );

    // todo: process gambits here instead of through BNpc::processGambit in StateCombat?
    virtual void processGambits( uint64_t tick );

    Controller::Path& getPath();
    void setPath( const Controller::Path& path );

    GambitPackPtr getGambitPack() const;
    void setGambitPack( GambitPackPtr& pGambitPack );

    Fsm::StatePtr getCurrentState();

    virtual void update( uint64_t tick );

    template< typename T, typename = std::enable_if_t< std::is_base_of< Fsm::State, T >::value > >
    bool isCurrentState()
    {
      return m_stateMachine.isCurrentState< T >();
    }

  protected:
    void updateFollowTarget( uint64_t tick );

    uint64_t m_lastTick;
    Fsm::StateMachine m_stateMachine;
    GambitPackPtr m_pGambitPack;
    Entity::GameObject& m_owner;
    Controller::Path m_path;
    bool m_followTargetActive{ false };
    bool m_followTargetDuringCombat{ false };
  };
};
