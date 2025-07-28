#pragma once

#include "TimelineActorState.h"
#include "Forwards.h"

#include <cstdint>
#include <string>
#include <vector>

#include <ForwardsZone.h>

#include <nlohmann/json.hpp>

namespace Sapphire
{
  enum class TimepointDataType : uint32_t
  {
    Idle,
    CastAction,
    SetPos,
    ActionTimeline,

    LogMessage,
    BattleTalk,

    DirectorVar,
    DirectorVarLR,
    DirectorSeq,
    DirectorFlags,

    AddStatusEffect,
    RemoveStatusEffect,

    BNpcSpawn,
    BNpcDespawn,
    BNpcFlags,
    SetEObjState,
    SetBgm,

    SetCondition,

    Snapshot
  };

  enum class ActionTargetType : uint32_t
  {
    None,
    Self,
    Target,
    Selector
  };

  enum class MoveType : uint32_t
  {
    WalkPath,
    Teleport,
    SetPos
  };

  enum class SetPosType : uint32_t
  {
    Absolute,
    Relative
  };

  enum class SetPosTargetType : uint32_t
  {
    None,
    Self,
    Target,
    Selector
  };

  enum class DirectorOpId
  {
    Set,// idx = val
    Add,// idx += val
    Sub,// idx -= val
    Mul,// idx *= val
    Div,// idx /= val
    Mod,// idx %= val
    Sll,// idx << val
    Srl,// idx >> val
    Or, // idx |= val
    Xor,// idx ^= val
    Nor,// idx ~= val
    And // idx &= val
  };

  //
  // Timepoint.m_pData objects
  //
  struct TimepointData : public std::enable_shared_from_this< TimepointData > {
    TimepointData( TimepointDataType type ) : m_type( type ) {}
    virtual ~TimepointData(){};
    TimepointDataType m_type{ 0 };
  };
  using TimepointDataPtr = std::shared_ptr< TimepointData >;

  struct TimepointDataIdle : public TimepointData {
    uint64_t m_durationMs;

    TimepointDataIdle( uint64_t durationMs ) :
      TimepointData( TimepointDataType::Idle ),
      m_durationMs( durationMs )
    {
    }
  };

  struct TimepointDataAction : public TimepointData
  {
    std::string m_sourceRef;
    uint32_t m_actionId;
    ActionTargetType m_targetType;
    std::string m_selectorRef;
    uint32_t m_selectorIndex;

    TimepointDataAction( const std::string& sourceRef, uint32_t actionId,
                         ActionTargetType type, const std::string& selectorRef,
                         uint32_t selectorIndex = 0 ) :
      TimepointData( TimepointDataType::CastAction ),
      m_sourceRef( sourceRef ),
      m_actionId( actionId ),
      m_targetType( type ),
      m_selectorRef( selectorRef ),
      m_selectorIndex( selectorIndex )
    {
    }
  };

  struct TimepointDataActionTimeLine : public TimepointData {
    std::string m_actorRef;
    uint32_t m_actionId;

    TimepointDataActionTimeLine( const std::string& actorRef, uint32_t action ) :
      TimepointData( TimepointDataType::ActionTimeline ),
      m_actorRef( actorRef ),
      m_actionId( action )
    {
    }
  };

  struct TimepointDataSetPos : public TimepointData {
    // todo: use internal id
    std::string m_actorRef;
    MoveType m_moveType;
    SetPosType m_posType;
    SetPosTargetType m_targetType;
    std::string m_selectorName;
    uint32_t m_selectorIndex;
    float m_x, m_y, m_z, m_rot;

    TimepointDataSetPos( const std::string& actorRef,
                        SetPosType type, SetPosTargetType targetType, MoveType moveType,
                        const std::string& selectorName, uint32_t selectorIndex,
                        float x, float y, float z, float rot ) :
      TimepointData( TimepointDataType::SetPos ),
      m_actorRef( actorRef ),
      m_posType( type ),
      m_moveType( moveType ),
      m_selectorName( selectorName), m_selectorIndex( selectorIndex ),
      m_x( x ), m_y( y ), m_z( z ), m_rot( rot )
    {
    }
  };

  struct TimepointDataLogMessage : public TimepointData {
    uint32_t m_messageId;
    uint32_t m_params[ 5 ]{ 0 };

    TimepointDataLogMessage( uint32_t messageId, const std::vector< uint32_t >& params ) :
      TimepointData( TimepointDataType::LogMessage ),
      m_messageId( messageId )
    {
      for( auto i = 0; i < params.size() && i < 5; ++i )
        m_params[ i ] = params[ i ];
    }
  };

  struct TimepointDataBattleTalk : public TimepointData {
    uint32_t m_battleTalkId;
    std::string m_handlerRef;
    uint32_t m_kind;
    uint32_t m_nameId;
    std::string m_talkerRef;
    uint32_t m_length{ 0 };

    uint32_t m_params[ 8 ]{ 0 };

    TimepointDataBattleTalk( const std::vector< uint32_t >& params ) :
      TimepointData( TimepointDataType::BattleTalk )
    {
      for( auto i = 0; i < params.size() && i < 8; ++i )
        m_params[ i ] = params[ i ];
    }
  };

  struct TimepointDataDirector : public TimepointData
  {
    DirectorOpId m_directorOp{ 0 };
    union
    {
      struct
      {
        uint8_t index;
        union
        {
          uint8_t val;
          struct
          {
            uint8_t left, right;
          };
        } value;
      };
      uint8_t seq;
      uint8_t flags;
    } m_data{ 0 };

    TimepointDataDirector( TimepointDataType type, DirectorOpId op ) :
      TimepointData( type ),
      m_directorOp( op )
    {
    }
  };

  struct TimepointDataBNpcDespawn : public TimepointData
  {
    uint32_t m_layoutId{ 0xE0000000 };

    TimepointDataBNpcDespawn( uint32_t layoutId ) :
    TimepointData( TimepointDataType::BNpcDespawn ),
    m_layoutId( layoutId )
    {
    }
  };

  struct TimepointDataBNpcSpawn : public TimepointData
  {
    uint32_t m_layoutId{ 0xE0000000 };
    uint32_t m_flags{ 0 };
    uint32_t m_type{ 0 };

    // todo: hate type, source

    TimepointDataBNpcSpawn( uint32_t layoutId, uint32_t flags, uint32_t type ) :
      TimepointData( TimepointDataType::BNpcSpawn ),
      m_layoutId( layoutId ),
      m_flags( flags ),
      m_type( type )
    {
    }
  };

  struct TimepointDataBNpcFlags : public TimepointData
  {
    uint32_t m_layoutId{ 0xE0000000 };
    uint32_t m_flags{ 0 };

    TimepointDataBNpcFlags( uint32_t layoutId, uint32_t flags ) :
      TimepointData( TimepointDataType::BNpcFlags ),
      m_layoutId( layoutId ),
      m_flags( flags )
    {
    }
  };

  struct TimepointDataEObjState : public TimepointData
  {
    uint32_t m_eobjId{ 0xE0000000 };
    uint32_t m_state{ 0 };

    TimepointDataEObjState( uint32_t eobjId, uint32_t state ) :
      TimepointData( TimepointDataType::SetEObjState ),
      m_eobjId( eobjId ),
      m_state( state )
    {
    }
  };

  struct TimepointDataBGM : public TimepointData
  {
    uint32_t m_bgmId{ 0 };

    TimepointDataBGM( uint32_t bgmId ) :
      TimepointData( TimepointDataType::SetBgm ),
      m_bgmId( bgmId )
    {
    }
  };

  struct TimepointDataCondition : public TimepointData
  {
    // todo: rng?
    uint32_t m_conditionId;
    bool m_enabled;

    TimepointDataCondition( uint32_t conditionId, bool enabled ) :
      TimepointData( TimepointDataType::SetCondition ),
      m_conditionId( conditionId ),
      m_enabled( enabled )
    {
    }
  };

  struct TimepointDataSnapshot : public TimepointData
  {
    // todo: rng?
    std::string m_selector;
    std::string m_actorRef;
    std::string m_excludeSelector;

    TimepointDataSnapshot( const std::string& selector, const std::string& actorRef, const std::string& excludeSelector ) :
      TimepointData( TimepointDataType::Snapshot ),
      m_selector( selector ),
      m_actorRef( actorRef ),
      m_excludeSelector( excludeSelector )
    {
    }
  };

  // todo: refactor all this to allow solo actor to use
  class Timepoint : public std::enable_shared_from_this< Timepoint >
  {
  public:
    TimepointDataType m_type;
    uint64_t m_offset{ 0 };
    TimepointDataPtr m_pData;
    std::string m_description;

    // todo: repeatable?

    const TimepointDataPtr getData() const;
    void reset( TimepointState& state ) const;

    void from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor >& actors, uint32_t selfLayoutId );
    // todo: separate execute/update into onStart and onTick?
    bool update( TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const;
    bool execute( TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const;
  };
}// namespace Sapphire::Encounter