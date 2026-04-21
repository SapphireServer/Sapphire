#include "LuaScriptRuntime.h"

#include <algorithm>
#include <cctype>
#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <utility>

#include <Logging/Logger.h>
#include <Service.h>
#include <Common.h>

#include "Actor/BNpc.h"
#include "Actor/Player.h"
#include "Manager/EventMgr.h"
#include "Quest/Quest.h"

namespace fs = std::filesystem;

namespace Sapphire
{
namespace
{
  size_t findTopLevelTokenPosition( const std::string& source, const std::string& key, size_t start = 0 )
  {
    int depth = 0;
    bool inString = false;

    for( size_t i = start; i < source.size(); ++i )
    {
      const auto ch = source[ i ];

      if( ch == '"' && ( i == 0 || source[ i - 1 ] != '\\' ) )
      {
        inString = !inString;
        continue;
      }

      if( inString )
        continue;

      if( ch == '{' )
      {
        ++depth;
        continue;
      }

      if( ch == '}' )
      {
        if( depth > 0 )
          --depth;

        continue;
      }

      if( depth != 0 || i + key.size() > source.size() || source.compare( i, key.size(), key ) != 0 )
        continue;

      const bool startsToken = i == 0 ||
        !( std::isalnum( static_cast< unsigned char >( source[ i - 1 ] ) ) || source[ i - 1 ] == '_' );
      const auto afterKey = i + key.size();
      const bool endsToken = afterKey >= source.size() ||
        !( std::isalnum( static_cast< unsigned char >( source[ afterKey ] ) ) || source[ afterKey ] == '_' );

      if( startsToken && endsToken )
        return i;
    }

    return std::string::npos;
  }

  std::string trimCopy( std::string value )
  {
    auto notSpace = []( unsigned char ch )
    {
      return !std::isspace( ch );
    };

    value.erase( value.begin(), std::find_if( value.begin(), value.end(), notSpace ) );
    value.erase( std::find_if( value.rbegin(), value.rend(), notSpace ).base(), value.end() );
    return value;
  }

  std::string normalizeToken( std::string value )
  {
    value = trimCopy( std::move( value ) );
    std::transform( value.begin(), value.end(), value.begin(),
                    []( unsigned char ch )
                    {
                      if( ch == '-' )
                        return '_';

                      return static_cast< char >( std::tolower( ch ) );
                    } );
    return value;
  }

  bool readFileToString( const std::string& path, std::string& out )
  {
    std::ifstream stream( path );
    if( !stream )
      return false;

    std::ostringstream buffer;
    buffer << stream.rdbuf();
    out = buffer.str();
    return true;
  }

  bool extractFirstTableBody( const std::string& source, std::string& body )
  {
    const auto bracePos = source.find( '{' );
    if( bracePos == std::string::npos )
      return false;

    int depth = 0;
    bool inString = false;

    for( size_t i = bracePos; i < source.size(); ++i )
    {
      const auto ch = source[ i ];

      if( ch == '"' && ( i == 0 || source[ i - 1 ] != '\\' ) )
        inString = !inString;

      if( inString )
        continue;

      if( ch == '{' )
      {
        ++depth;
      }
      else if( ch == '}' )
      {
        --depth;
        if( depth == 0 )
        {
          body = source.substr( bracePos + 1, i - bracePos - 1 );
          return true;
        }
      }
    }

    return false;
  }

  bool extractAnonymousTableList( const std::string& source, std::vector< std::string >& bodies )
  {
    int depth = 0;
    bool inString = false;
    size_t entryStart = std::string::npos;

    for( size_t i = 0; i < source.size(); ++i )
    {
      const auto ch = source[ i ];

      if( ch == '"' && ( i == 0 || source[ i - 1 ] != '\\' ) )
      {
        inString = !inString;
        continue;
      }

      if( inString )
        continue;

      if( ch == '{' )
      {
        if( depth == 0 )
          entryStart = i;

        ++depth;
      }
      else if( ch == '}' )
      {
        --depth;
        if( depth == 0 && entryStart != std::string::npos )
        {
          bodies.push_back( source.substr( entryStart + 1, i - entryStart - 1 ) );
          entryStart = std::string::npos;
        }
      }
    }

    return true;
  }

  bool findAssignmentRhs( const std::string& source, const std::string& key, std::string& rhs )
  {
    const auto keyPos = findTopLevelTokenPosition( source, key );
    if( keyPos != std::string::npos )
    {
      const auto eqPos = source.find( '=', keyPos + key.size() );
      if( eqPos == std::string::npos )
        return false;

      auto valueStart = eqPos + 1;
      while( valueStart < source.size() && std::isspace( static_cast< unsigned char >( source[ valueStart ] ) ) )
        ++valueStart;

      auto valueEnd = valueStart;
      while( valueEnd < source.size() && source[ valueEnd ] != '\r' && source[ valueEnd ] != '\n' &&
             source[ valueEnd ] != ',' )
        ++valueEnd;

      rhs = trimCopy( source.substr( valueStart, valueEnd - valueStart ) );
      return !rhs.empty();
    }

    return false;
  }

  bool findQuotedAssignment( const std::string& source, const std::string& key, std::string& value )
  {
    std::string rhs;
    if( !findAssignmentRhs( source, key, rhs ) )
      return false;

    if( rhs.size() < 2 || rhs.front() != '"' || rhs.back() != '"' )
      return false;

    value = rhs.substr( 1, rhs.size() - 2 );
    return true;
  }

  bool parseUnsignedValue( const std::string& source, uint32_t& value )
  {
    auto token = trimCopy( source );
    if( token.empty() )
      return false;

    try
    {
      size_t processed = 0;
      const auto parsed = std::stoull( token, &processed, 0 );
      if( processed != token.size() )
        return false;

      value = static_cast< uint32_t >( parsed );
      return true;
    }
    catch( const std::exception& )
    {
      return false;
    }
  }

  bool parseSignedValue( const std::string& source, int32_t& value )
  {
    auto token = trimCopy( source );
    if( token.empty() )
      return false;

    try
    {
      size_t processed = 0;
      const auto parsed = std::stoll( token, &processed, 0 );
      if( processed != token.size() )
        return false;

      value = static_cast< int32_t >( parsed );
      return true;
    }
    catch( const std::exception& )
    {
      return false;
    }
  }

  bool parseFloatValue( const std::string& source, float& value )
  {
    auto token = trimCopy( source );
    if( token.empty() )
      return false;

    try
    {
      size_t processed = 0;
      const auto parsed = std::stof( token, &processed );
      if( processed != token.size() )
        return false;

      value = parsed;
      return true;
    }
    catch( const std::exception& )
    {
      return false;
    }
  }

  bool findUnsignedAssignment( const std::string& source, const std::string& key, uint32_t& value )
  {
    std::string rhs;
    return findAssignmentRhs( source, key, rhs ) && parseUnsignedValue( rhs, value );
  }

  bool findSignedAssignment( const std::string& source, const std::string& key, int32_t& value )
  {
    std::string rhs;
    return findAssignmentRhs( source, key, rhs ) && parseSignedValue( rhs, value );
  }

  bool findFloatAssignment( const std::string& source, const std::string& key, float& value )
  {
    std::string rhs;
    return findAssignmentRhs( source, key, rhs ) && parseFloatValue( rhs, value );
  }

  bool extractTableAssignment( const std::string& source, const std::string& key, std::string& body )
  {
    const auto keyPos = findTopLevelTokenPosition( source, key );
    if( keyPos == std::string::npos )
      return false;

    const auto eqPos = source.find( '=', keyPos + key.size() );
    if( eqPos == std::string::npos )
      return false;

    const auto bracePos = source.find( '{', eqPos + 1 );
    if( bracePos == std::string::npos )
      return false;

    int depth = 0;
    bool inString = false;

    for( size_t i = bracePos; i < source.size(); ++i )
    {
      const auto ch = source[ i ];

      if( ch == '"' && ( i == 0 || source[ i - 1 ] != '\\' ) )
        inString = !inString;

      if( inString )
        continue;

      if( ch == '{' )
      {
        ++depth;
      }
      else if( ch == '}' )
      {
        --depth;
        if( depth == 0 )
        {
          body = source.substr( bracePos + 1, i - bracePos - 1 );
          return true;
        }
      }
    }

    return false;
  }

  bool findNumberArrayAssignment( const std::string& source, const std::string& key, std::vector< uint32_t >& values )
  {
    std::string body;
    if( !extractTableAssignment( source, key, body ) )
      return true;

    std::stringstream stream( body );
    std::string token;

    while( std::getline( stream, token, ',' ) )
    {
      token = trimCopy( std::move( token ) );
      if( token.empty() )
        continue;

      uint32_t value = 0;
      if( !parseUnsignedValue( token, value ) )
        return false;

      values.push_back( value );
    }

    return true;
  }

  bool findStringArrayAssignment( const std::string& source, const std::string& key, std::vector< std::string >& values )
  {
    std::string body;
    if( !extractTableAssignment( source, key, body ) )
      return true;

    std::stringstream stream( body );
    std::string token;

    while( std::getline( stream, token, ',' ) )
    {
      token = trimCopy( std::move( token ) );
      if( token.empty() )
        continue;

      if( token.size() < 2 || token.front() != '"' || token.back() != '"' )
        return false;

      values.push_back( token.substr( 1, token.size() - 2 ) );
    }

    return true;
  }

  template< typename TComparison >
  bool parseComparison( const std::string& value, TComparison& comparison )
  {
    const auto normalized = normalizeToken( value );

    if( normalized == "always" )
      comparison = TComparison::Always;
    else if( normalized == "eq" || normalized == "equals" )
      comparison = TComparison::Eq;
    else if( normalized == "neq" || normalized == "not_equals" || normalized == "not_equal" )
      comparison = TComparison::Neq;
    else if( normalized == "gt" )
      comparison = TComparison::Gt;
    else if( normalized == "gte" )
      comparison = TComparison::Gte;
    else if( normalized == "lt" )
      comparison = TComparison::Lt;
    else if( normalized == "lte" )
      comparison = TComparison::Lte;
    else
      return false;

    return true;
  }

  bool parseQuestAvailability( const std::string& value, Sapphire::Event::EventHandler::QuestAvailability& availability )
  {
    const auto normalized = normalizeToken( value );

    if( normalized == "available" )
      availability = Sapphire::Event::EventHandler::QuestAvailability::Available;
    else if( normalized == "locked" )
      availability = Sapphire::Event::EventHandler::QuestAvailability::Locked;
    else if( normalized == "invisible" || normalized == "hidden" )
      availability = Sapphire::Event::EventHandler::QuestAvailability::Invisible;
    else
      return false;

    return true;
  }

  bool parseQuestValueField( const std::string& value, Sapphire::Scripting::LuaQuestValueField& field )
  {
    using Field = Sapphire::Scripting::LuaQuestValueField;

    const auto normalized = normalizeToken( value );

    if( normalized == "ui8a" )
      field = Field::UI8A;
    else if( normalized == "ui8b" )
      field = Field::UI8B;
    else if( normalized == "ui8c" )
      field = Field::UI8C;
    else if( normalized == "ui8d" )
      field = Field::UI8D;
    else if( normalized == "ui8e" )
      field = Field::UI8E;
    else if( normalized == "ui8f" )
      field = Field::UI8F;
    else if( normalized == "ui8ah" )
      field = Field::UI8AH;
    else if( normalized == "ui8bh" )
      field = Field::UI8BH;
    else if( normalized == "ui8ch" )
      field = Field::UI8CH;
    else if( normalized == "ui8dh" )
      field = Field::UI8DH;
    else if( normalized == "ui8eh" )
      field = Field::UI8EH;
    else if( normalized == "ui8fh" )
      field = Field::UI8FH;
    else if( normalized == "ui8al" )
      field = Field::UI8AL;
    else if( normalized == "ui8bl" )
      field = Field::UI8BL;
    else if( normalized == "ui8cl" )
      field = Field::UI8CL;
    else if( normalized == "ui8dl" )
      field = Field::UI8DL;
    else if( normalized == "ui8el" )
      field = Field::UI8EL;
    else if( normalized == "ui8fl" )
      field = Field::UI8FL;
    else
      return false;

    return true;
  }

  bool parseQuestValueFieldArray( const std::vector< std::string >& values,
                                  std::vector< Sapphire::Scripting::LuaQuestValueField >& fields )
  {
    fields.clear();
    fields.reserve( values.size() );

    for( const auto& value : values )
    {
      Sapphire::Scripting::LuaQuestValueField field = Sapphire::Scripting::LuaQuestValueField::Invalid;
      if( !parseQuestValueField( value, field ) )
        return false;

      fields.push_back( field );
    }

    return true;
  }

  template< typename TIndex >
  bool parseQuestRouteStateFilters( const std::string& source, bool& hasSeq, uint8_t& seq,
                                    bool& hasBitFlag8Set, TIndex& bitFlag8Set, bool& hasBitFlag8Clear,
                                    TIndex& bitFlag8Clear )
  {
    uint32_t seqValue = 0;
    if( findUnsignedAssignment( source, "seq", seqValue ) )
    {
      hasSeq = true;
      seq = static_cast< uint8_t >( seqValue );
    }

    uint32_t bitFlagIndex = 0;
    if( findUnsignedAssignment( source, "bit_flag8_set", bitFlagIndex ) )
    {
      hasBitFlag8Set = true;
      bitFlag8Set = static_cast< TIndex >( bitFlagIndex );
    }

    if( findUnsignedAssignment( source, "bit_flag8_clear", bitFlagIndex ) )
    {
      hasBitFlag8Clear = true;
      bitFlag8Clear = static_cast< TIndex >( bitFlagIndex );
    }

    return true;
  }

  bool parseQuestGroundItemTarget( const std::string& source, Sapphire::Scripting::LuaQuestGroundItemTarget& target,
                                   const std::string& context )
  {
    if( !findUnsignedAssignment( source, "id", target.id ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing id.", context );
      return false;
    }

    if( !findUnsignedAssignment( source, "territory", target.territoryId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing territory.", context );
      return false;
    }

    if( !findFloatAssignment( source, "x", target.x ) || !findFloatAssignment( source, "y", target.y ) ||
        !findFloatAssignment( source, "z", target.z ) )
    {
      Logger::error( "LuaScriptRuntime: {0} must define numeric x, y, and z coordinates.", context );
      return false;
    }

    findFloatAssignment( source, "radius", target.radius );
    return true;
  }

  bool parseQuestEventType( const std::string& value, uint8_t& eventType )
  {
    const auto normalized = normalizeToken( value );
    using EventType = Sapphire::Event::EventHandler::EventType;

    if( normalized == "talk" )
      eventType = EventType::Talk;
    else if( normalized == "emote" )
      eventType = EventType::Emote;
    else if( normalized == "item" )
      eventType = EventType::Item;
    else if( normalized == "within_range" )
      eventType = EventType::WithinRange;
    else if( normalized == "outside_range" )
      eventType = EventType::OutsideRange;
    else if( normalized == "enter_territory" )
      eventType = EventType::EnterTerritory;
    else if( normalized == "action_result" )
      eventType = EventType::ActionResult;
    else
      return false;

    return true;
  }

  uint32_t getQuestValueField( Sapphire::World::Quest& quest, Sapphire::Scripting::LuaQuestValueField field )
  {
    using Field = Sapphire::Scripting::LuaQuestValueField;

    switch( field )
    {
      case Field::UI8A:
        return quest.getUI8A();
      case Field::UI8B:
        return quest.getUI8B();
      case Field::UI8C:
        return quest.getUI8C();
      case Field::UI8D:
        return quest.getUI8D();
      case Field::UI8E:
        return quest.getUI8E();
      case Field::UI8F:
        return quest.getUI8F();
      case Field::UI8AH:
        return quest.getUI8AH();
      case Field::UI8BH:
        return quest.getUI8BH();
      case Field::UI8CH:
        return quest.getUI8CH();
      case Field::UI8DH:
        return quest.getUI8DH();
      case Field::UI8EH:
        return quest.getUI8EH();
      case Field::UI8FH:
        return quest.getUI8FH();
      case Field::UI8AL:
        return quest.getUI8AL();
      case Field::UI8BL:
        return quest.getUI8BL();
      case Field::UI8CL:
        return quest.getUI8CL();
      case Field::UI8DL:
        return quest.getUI8DL();
      case Field::UI8EL:
        return quest.getUI8EL();
      case Field::UI8FL:
        return quest.getUI8FL();
      case Field::Invalid:
      default:
        return 0;
    }
  }

  void setQuestValueField( Sapphire::World::Quest& quest, Sapphire::Scripting::LuaQuestValueField field, uint32_t value )
  {
    using Field = Sapphire::Scripting::LuaQuestValueField;
    const auto storedValue = static_cast< uint8_t >( std::min< uint32_t >( value, 0xFF ) );

    switch( field )
    {
      case Field::UI8A:
        quest.setUI8A( storedValue );
        return;
      case Field::UI8B:
        quest.setUI8B( storedValue );
        return;
      case Field::UI8C:
        quest.setUI8C( storedValue );
        return;
      case Field::UI8D:
        quest.setUI8D( storedValue );
        return;
      case Field::UI8E:
        quest.setUI8E( storedValue );
        return;
      case Field::UI8F:
        quest.setUI8F( storedValue );
        return;
      case Field::UI8AH:
        quest.setUI8AH( storedValue );
        return;
      case Field::UI8BH:
        quest.setUI8BH( storedValue );
        return;
      case Field::UI8CH:
        quest.setUI8CH( storedValue );
        return;
      case Field::UI8DH:
        quest.setUI8DH( storedValue );
        return;
      case Field::UI8EH:
        quest.setUI8EH( storedValue );
        return;
      case Field::UI8FH:
        quest.setUI8FH( storedValue );
        return;
      case Field::UI8AL:
        quest.setUI8AL( storedValue );
        return;
      case Field::UI8BL:
        quest.setUI8BL( storedValue );
        return;
      case Field::UI8CL:
        quest.setUI8CL( storedValue );
        return;
      case Field::UI8DL:
        quest.setUI8DL( storedValue );
        return;
      case Field::UI8EL:
        quest.setUI8EL( storedValue );
        return;
      case Field::UI8FL:
        quest.setUI8FL( storedValue );
        return;
      case Field::Invalid:
      default:
        return;
    }
  }

  bool parseActionTable( const std::string& source, Sapphire::Scripting::LuaEventAction& action,
                         const std::string& context )
  {
    using Kind = Sapphire::Scripting::LuaEventAction::Kind;

    std::string actionName;
    if( !findQuotedAssignment( source, "action", actionName ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    const auto normalizedAction = normalizeToken( actionName );

    if( normalizedAction == "play_scene" )
    {
      action.kind = Kind::PlayScene;
      if( !findUnsignedAssignment( source, "scene", action.scene ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing scene.", context );
        return false;
      }

      findUnsignedAssignment( source, "flags", action.flags );
      if( !findNumberArrayAssignment( source, "values", action.values ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid values.", context );
        return false;
      }

      if( !findNumberArrayAssignment( source, "append_result_indices", action.appendResultIndices ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid append_result_indices.", context );
        return false;
      }
    }
    else if( normalizedAction == "event_notice" )
    {
      int32_t noticeId = 0;
      action.kind = Kind::EventNotice;

      if( !findSignedAssignment( source, "notice_id", noticeId ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing notice_id.", context );
        return false;
      }

      action.noticeId = static_cast< int8_t >( noticeId );
      if( !findNumberArrayAssignment( source, "values", action.values ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid values.", context );
        return false;
      }

      if( !findNumberArrayAssignment( source, "append_result_indices", action.appendResultIndices ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid append_result_indices.", context );
        return false;
      }
    }
    else if( normalizedAction == "server_notice" || normalizedAction == "urgent_notice" ||
             normalizedAction == "debug_notice" )
    {
      if( !findQuotedAssignment( source, "message", action.message ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing message.", context );
        return false;
      }

      if( normalizedAction == "server_notice" )
        action.kind = Kind::ServerNotice;
      else if( normalizedAction == "urgent_notice" )
        action.kind = Kind::UrgentNotice;
      else
        action.kind = Kind::DebugNotice;
    }
    else
    {
      Logger::error( "LuaScriptRuntime: {0} uses unsupported action '{1}'.", context, actionName );
      return false;
    }

    std::string onReturnBody;
    if( extractTableAssignment( source, "on_return", onReturnBody ) )
    {
      if( action.kind != Kind::PlayScene )
      {
        Logger::error( "LuaScriptRuntime: {0} uses on_return on an unsupported action.", context );
        return false;
      }

      auto transition = std::make_shared< Sapphire::Scripting::LuaEventTransition >();
      std::string comparisonName;

      if( findQuotedAssignment( onReturnBody, "comparison", comparisonName ) )
      {
        if( !parseComparison( comparisonName, transition->comparison ) )
        {
          Logger::error( "LuaScriptRuntime: {0}.on_return uses unsupported comparison '{1}'.", context,
                         comparisonName );
          return false;
        }
      }

      findUnsignedAssignment( onReturnBody, "result_index", transition->resultIndex );
      findUnsignedAssignment( onReturnBody, "compare_value", transition->compareValue );

      std::string nextBody;
      if( !extractTableAssignment( onReturnBody, "next", nextBody ) )
      {
        Logger::error( "LuaScriptRuntime: {0}.on_return is missing next.", context );
        return false;
      }

      auto nextAction = std::make_shared< Sapphire::Scripting::LuaEventAction >();
      if( !parseActionTable( nextBody, *nextAction, context + ".on_return.next" ) )
        return false;

      transition->nextAction = nextAction;
      action.onReturn = transition;
    }

    return true;
  }

  bool parseQuestActionTable( const std::string& source, Sapphire::Scripting::LuaQuestAction& action,
                              const std::string& context )
  {
    using Kind = Sapphire::Scripting::LuaQuestAction::Kind;

    std::string actionName;
    if( !findQuotedAssignment( source, "action", actionName ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    const auto normalizedAction = normalizeToken( actionName );

    if( normalizedAction == "play_quest_scene" )
    {
      action.kind = Kind::PlayQuestScene;
      if( !findUnsignedAssignment( source, "scene", action.scene ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing scene.", context );
        return false;
      }

      findUnsignedAssignment( source, "flags", action.flags );
    }
    else if( normalizedAction == "set_seq" )
    {
      action.kind = Kind::SetSeq;
      if( !findUnsignedAssignment( source, "seq", action.seq ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing seq.", context );
        return false;
      }
    }
    else if( normalizedAction == "finish_quest" )
    {
      action.kind = Kind::FinishQuest;
      action.useRewardResultIndex = findUnsignedAssignment( source, "reward_result_index", action.rewardResultIndex );

      if( !action.useRewardResultIndex )
        findUnsignedAssignment( source, "reward_choice", action.rewardChoice );
    }
    else if( normalizedAction == "event_notice" )
    {
      int32_t noticeId = 0;
      action.kind = Kind::EventNotice;

      if( !findSignedAssignment( source, "notice_id", noticeId ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing notice_id.", context );
        return false;
      }

      action.noticeId = static_cast< int8_t >( noticeId );
      action.hasNoticeId = true;

      if( !findNumberArrayAssignment( source, "values", action.values ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid values.", context );
        return false;
      }
    }
    else if( normalizedAction == "quest_progress_notice" )
    {
      int32_t noticeId = 0;
      std::string fieldName;
      action.kind = Kind::QuestProgressNotice;

      if( !findSignedAssignment( source, "notice_id", noticeId ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing notice_id.", context );
        return false;
      }

      if( !findQuotedAssignment( source, "field", fieldName ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing field.", context );
        return false;
      }

      if( !parseQuestValueField( fieldName, action.field ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported field '{1}'.", context, fieldName );
        return false;
      }

      if( !findUnsignedAssignment( source, "goal", action.goal ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing goal.", context );
        return false;
      }

      action.noticeId = static_cast< int8_t >( noticeId );
      action.hasNoticeId = true;
    }
    else if( normalizedAction == "set_quest_value" )
    {
      std::string fieldName;
      action.kind = Kind::SetQuestValue;

      if( !findQuotedAssignment( source, "field", fieldName ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing field.", context );
        return false;
      }

      if( !parseQuestValueField( fieldName, action.field ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported field '{1}'.", context, fieldName );
        return false;
      }

      if( !findUnsignedAssignment( source, "value", action.value ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing value.", context );
        return false;
      }
    }
    else if( normalizedAction == "adjust_quest_value" )
    {
      std::string fieldName;
      action.kind = Kind::AdjustQuestValue;

      if( !findQuotedAssignment( source, "field", fieldName ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing field.", context );
        return false;
      }

      if( !parseQuestValueField( fieldName, action.field ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported field '{1}'.", context, fieldName );
        return false;
      }

      if( !findSignedAssignment( source, "amount", action.delta ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing amount.", context );
        return false;
      }
    }
    else if( normalizedAction == "set_bit_flag8" )
    {
      uint32_t rawValue = 0;
      action.kind = Kind::SetBitFlag8;

      if( !findUnsignedAssignment( source, "index", action.bitFlagIndex ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing index.", context );
        return false;
      }

      if( !findUnsignedAssignment( source, "value", rawValue ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing value.", context );
        return false;
      }

      action.bitFlagValue = rawValue != 0;
    }
    else if( normalizedAction == "complete_if_quest_value_at_least" )
    {
      std::string fieldName;
      action.kind = Kind::CompleteIfQuestValueAtLeast;

      if( !findQuotedAssignment( source, "field", fieldName ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing field.", context );
        return false;
      }

      if( !parseQuestValueField( fieldName, action.field ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported field '{1}'.", context, fieldName );
        return false;
      }

      if( !findUnsignedAssignment( source, "goal", action.goal ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing goal.", context );
        return false;
      }

      action.hasCompleteSeq = findUnsignedAssignment( source, "complete_seq", action.completeSeq );

      std::vector< std::string > resetFieldNames;
      if( !findStringArrayAssignment( source, "reset_fields", resetFieldNames ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid reset_fields.", context );
        return false;
      }

      if( !parseQuestValueFieldArray( resetFieldNames, action.resetFields ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported reset_fields.", context );
        return false;
      }

      if( !findNumberArrayAssignment( source, "clear_bit_flags8", action.clearBitFlags8 ) )
      {
        Logger::error( "LuaScriptRuntime: {0} has invalid clear_bit_flags8.", context );
        return false;
      }
    }
    else if( normalizedAction == "start_event" )
    {
      std::string eventTypeName;
      uint32_t actorId = 0;
      action.kind = Kind::StartEvent;
      action.eventType = Event::EventHandler::EventType::ActionResult;

      if( !findUnsignedAssignment( source, "actor", actorId ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing actor.", context );
        return false;
      }

      action.actorId = actorId;

      if( findQuotedAssignment( source, "event_type", eventTypeName ) &&
          !parseQuestEventType( eventTypeName, action.eventType ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported event_type '{1}'.", context, eventTypeName );
        return false;
      }

      uint32_t eventParam = 0;
      if( findUnsignedAssignment( source, "event_param1", eventParam ) )
        action.eventParam1 = static_cast< uint8_t >( eventParam );

      findUnsignedAssignment( source, "event_param2", action.eventParam2 );
    }
    else if( normalizedAction == "advance_kill_counter" )
    {
      std::string fieldName;
      action.kind = Kind::AdvanceKillCounter;

      if( !findQuotedAssignment( source, "field", fieldName ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing field.", context );
        return false;
      }

      if( !parseQuestValueField( fieldName, action.field ) )
      {
        Logger::error( "LuaScriptRuntime: {0} uses unsupported field '{1}'.", context, fieldName );
        return false;
      }

      findUnsignedAssignment( source, "amount", action.amount );

      if( !findUnsignedAssignment( source, "goal", action.goal ) )
      {
        Logger::error( "LuaScriptRuntime: {0} is missing goal.", context );
        return false;
      }

      action.hasCompleteSeq = findUnsignedAssignment( source, "complete_seq", action.completeSeq );

      int32_t noticeId = 0;
      if( findSignedAssignment( source, "notice_id", noticeId ) )
      {
        action.noticeId = static_cast< int8_t >( noticeId );
        action.hasNoticeId = true;
      }
    }
    else
    {
      Logger::error( "LuaScriptRuntime: {0} uses unsupported quest action '{1}'.", context, actionName );
      return false;
    }

    std::string onReturnBody;
    if( extractTableAssignment( source, "on_return", onReturnBody ) )
    {
      if( action.kind != Kind::PlayQuestScene )
      {
        Logger::error( "LuaScriptRuntime: {0} uses on_return on an unsupported quest action.", context );
        return false;
      }

      auto transition = std::make_shared< Sapphire::Scripting::LuaQuestTransition >();
      std::string comparisonName;

      if( findQuotedAssignment( onReturnBody, "comparison", comparisonName ) )
      {
        if( !parseComparison( comparisonName, transition->comparison ) )
        {
          Logger::error( "LuaScriptRuntime: {0}.on_return uses unsupported comparison '{1}'.", context,
                         comparisonName );
          return false;
        }
      }

      findUnsignedAssignment( onReturnBody, "result_index", transition->resultIndex );
      findUnsignedAssignment( onReturnBody, "compare_value", transition->compareValue );

      std::string nextBody;
      if( !extractTableAssignment( onReturnBody, "next", nextBody ) )
      {
        Logger::error( "LuaScriptRuntime: {0}.on_return is missing next.", context );
        return false;
      }

      auto nextAction = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
      if( !parseQuestActionTable( nextBody, *nextAction, context + ".on_return.next" ) )
        return false;

      transition->nextAction = nextAction;
      action.onReturn = transition;
    }

    std::string nextBody;
    if( extractTableAssignment( source, "next", nextBody ) )
    {
      if( action.kind == Kind::PlayQuestScene )
      {
        Logger::error( "LuaScriptRuntime: {0} uses direct next on play_quest_scene. Use on_return.next instead.",
                       context );
        return false;
      }

      auto nextAction = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
      if( !parseQuestActionTable( nextBody, *nextAction, context + ".next" ) )
        return false;

      action.nextAction = nextAction;
    }

    return true;
  }

  bool parseQuestTalkRoute( const std::string& source, Sapphire::Scripting::LuaQuestTalkRoute& route,
                            const std::string& context )
  {
    uint32_t actorId = 0;
    if( !findUnsignedAssignment( source, "actor", actorId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing actor.", context );
      return false;
    }

    route.actorId = actorId;

    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestKillRoute( const std::string& source, Sapphire::Scripting::LuaQuestKillRoute& route,
                            const std::string& context )
  {
    uint32_t bnpcNameId = 0;
    if( !findUnsignedAssignment( source, "enemy", bnpcNameId ) &&
        !findUnsignedAssignment( source, "bnpc_name_id", bnpcNameId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing enemy.", context );
      return false;
    }

    route.bnpcNameId = bnpcNameId;

    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestEventItemRoute( const std::string& source, Sapphire::Scripting::LuaQuestEventItemRoute& route,
                                 const std::string& context )
  {
    uint32_t actorId = 0;
    if( !findUnsignedAssignment( source, "actor", actorId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing actor.", context );
      return false;
    }

    route.actorId = actorId;

    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestEmoteRoute( const std::string& source, Sapphire::Scripting::LuaQuestEmoteRoute& route,
                             const std::string& context )
  {
    uint32_t actorId = 0;
    if( !findUnsignedAssignment( source, "actor", actorId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing actor.", context );
      return false;
    }

    if( !findUnsignedAssignment( source, "emote_id", route.emoteId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing emote_id.", context );
      return false;
    }

    route.actorId = actorId;

    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestEObjHitRoute( const std::string& source, Sapphire::Scripting::LuaQuestEObjHitRoute& route,
                               const std::string& context )
  {
    uint32_t actorId = 0;
    if( !findUnsignedAssignment( source, "actor", actorId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing actor.", context );
      return false;
    }

    if( !findUnsignedAssignment( source, "action_id", route.actionId ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action_id.", context );
      return false;
    }

    route.actorId = actorId;

    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestEventGroundItemRoute( const std::string& source,
                                       Sapphire::Scripting::LuaQuestEventGroundItemRoute& route,
                                       const std::string& context )
  {
    std::string targetBody;
    if( !extractTableAssignment( source, "target", targetBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing target.", context );
      return false;
    }

    if( !parseQuestGroundItemTarget( targetBody, route.target, context + ".target" ) )
      return false;

    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestEnterTerritoryRoute( const std::string& source,
                                      Sapphire::Scripting::LuaQuestEnterTerritoryRoute& route,
                                      const std::string& context )
  {
    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    uint32_t paramValue = 0;
    if( findUnsignedAssignment( source, "param1", paramValue ) )
    {
      route.hasParam1 = true;
      route.param1 = static_cast< uint16_t >( paramValue );
    }

    if( findUnsignedAssignment( source, "param2", paramValue ) )
    {
      route.hasParam2 = true;
      route.param2 = static_cast< uint16_t >( paramValue );
    }

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  bool parseQuestRangeRoute( const std::string& source, Sapphire::Scripting::LuaQuestRangeRoute& route,
                             const std::string& context )
  {
    parseQuestRouteStateFilters( source, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                 route.hasBitFlag8Clear, route.bitFlag8Clear );

    uint32_t param1 = 0;
    if( findUnsignedAssignment( source, "range_id", param1 ) || findUnsignedAssignment( source, "param1", param1 ) )
    {
      route.hasParam1 = true;
      route.param1 = param1;
    }

    std::string actionBody;
    if( !extractTableAssignment( source, "action", actionBody ) )
    {
      Logger::error( "LuaScriptRuntime: {0} is missing action.", context );
      return false;
    }

    auto action = std::make_shared< Sapphire::Scripting::LuaQuestAction >();
    if( !parseQuestActionTable( actionBody, *action, context + ".action" ) )
      return false;

    route.action = action;
    return true;
  }

  class LuaEventScript : public Sapphire::ScriptAPI::EventScript
  {
  public:
    LuaEventScript( uint32_t eventId, Sapphire::Scripting::LuaEventAction onTalkAction ) :
      Sapphire::ScriptAPI::EventScript( eventId ),
      m_onTalkAction( std::make_shared< const Sapphire::Scripting::LuaEventAction >( std::move( onTalkAction ) ) )
    {
    }

    void onTalk( uint32_t eventId, Sapphire::Entity::Player& player, uint64_t actorId ) override
    {
      ( void ) actorId;
      executeAction( m_onTalkAction, player, eventId, nullptr );
    }

  private:
    static std::vector< uint32_t > buildValues( const Sapphire::Scripting::LuaEventAction& action,
                                                const Sapphire::Event::SceneResult* pResult )
    {
      std::vector< uint32_t > values = action.values;
      if( !pResult )
        return values;

      for( const auto resultIndex : action.appendResultIndices )
      {
        if( resultIndex < pResult->results.size() )
          values.push_back( pResult->getResult( resultIndex ) );
        else
          values.push_back( 0 );
      }

      return values;
    }

    static bool shouldRunTransition( const Sapphire::Scripting::LuaEventTransition& transition,
                                     const Sapphire::Event::SceneResult& result )
    {
      if( transition.comparison == Sapphire::Scripting::LuaEventTransition::Comparison::Always )
        return true;

      const auto actual = result.getResult( transition.resultIndex );
      const auto expected = transition.compareValue;

      switch( transition.comparison )
      {
        case Sapphire::Scripting::LuaEventTransition::Comparison::Eq:
          return actual == expected;

        case Sapphire::Scripting::LuaEventTransition::Comparison::Neq:
          return actual != expected;

        case Sapphire::Scripting::LuaEventTransition::Comparison::Gt:
          return actual > expected;

        case Sapphire::Scripting::LuaEventTransition::Comparison::Gte:
          return actual >= expected;

        case Sapphire::Scripting::LuaEventTransition::Comparison::Lt:
          return actual < expected;

        case Sapphire::Scripting::LuaEventTransition::Comparison::Lte:
          return actual <= expected;

        case Sapphire::Scripting::LuaEventTransition::Comparison::Always:
        default:
          return true;
      }
    }

    static void executeAction( const std::shared_ptr< const Sapphire::Scripting::LuaEventAction >& pAction,
                               Sapphire::Entity::Player& player, uint32_t eventId,
                               const Sapphire::Event::SceneResult* pResult )
    {
      if( !pAction )
      {
        Sapphire::World::Manager::PlayerMgr::sendDebug( player, "Lua event action is missing for eventId#{0}",
                                                        eventId );
        return;
      }

      const auto& action = *pAction;
      auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

      switch( action.kind )
      {
        case Sapphire::Scripting::LuaEventAction::Kind::PlayScene:
        {
          auto values = buildValues( action, pResult );

          if( action.onReturn && action.onReturn->nextAction )
          {
            auto transition = action.onReturn;
            auto callback = [ transition ]( Sapphire::Entity::Player& player,
                                            const Sapphire::Event::SceneResult& result )
            {
              if( transition && transition->nextAction && shouldRunTransition( *transition, result ) )
                executeAction( transition->nextAction, player, result.eventId, &result );
            };

            eventMgr.playScene( player, eventId, action.scene, action.flags, std::move( values ), callback );
          }
          else
          {
            eventMgr.playScene( player, eventId, action.scene, action.flags, std::move( values ), nullptr );
          }
          return;
        }

        case Sapphire::Scripting::LuaEventAction::Kind::EventNotice:
          eventMgr.sendNotice( player, eventId, action.noticeId, buildValues( action, pResult ) );
          return;

        case Sapphire::Scripting::LuaEventAction::Kind::ServerNotice:
          Sapphire::World::Manager::PlayerMgr::sendServerNotice( player, action.message );
          return;

        case Sapphire::Scripting::LuaEventAction::Kind::UrgentNotice:
          Sapphire::World::Manager::PlayerMgr::sendUrgent( player, action.message );
          return;

        case Sapphire::Scripting::LuaEventAction::Kind::DebugNotice:
          Sapphire::World::Manager::PlayerMgr::sendDebug( player, action.message );
          return;

        case Sapphire::Scripting::LuaEventAction::Kind::Invalid:
        default:
          Sapphire::World::Manager::PlayerMgr::sendDebug( player, "Lua event action is invalid for eventId#{0}",
                                                          eventId );
          return;
      }
    }

    std::shared_ptr< const Sapphire::Scripting::LuaEventAction > m_onTalkAction;
  };

  class LuaQuestScript : public Sapphire::ScriptAPI::QuestScript
  {
  public:
    LuaQuestScript( uint32_t questId, Sapphire::Event::EventHandler::QuestAvailability availability,
                    std::vector< Sapphire::Scripting::LuaQuestTalkRoute > onTalkRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestKillRoute > onKillRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestEventItemRoute > onEventItemRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestEventGroundItemRoute > onEventGroundItemRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestEnterTerritoryRoute > onEnterTerritoryRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestRangeRoute > onWithinRangeRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestRangeRoute > onOutsideRangeRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestEmoteRoute > onEmoteRoutes,
                    std::vector< Sapphire::Scripting::LuaQuestEObjHitRoute > onEObjHitRoutes ) :
      Sapphire::ScriptAPI::QuestScript( questId ),
      m_availability( availability ),
      m_onTalkRoutes( std::move( onTalkRoutes ) ),
      m_onKillRoutes( std::move( onKillRoutes ) ),
      m_onEventItemRoutes( std::move( onEventItemRoutes ) ),
      m_onEventGroundItemRoutes( std::move( onEventGroundItemRoutes ) ),
      m_onEnterTerritoryRoutes( std::move( onEnterTerritoryRoutes ) ),
      m_onWithinRangeRoutes( std::move( onWithinRangeRoutes ) ),
      m_onOutsideRangeRoutes( std::move( onOutsideRangeRoutes ) ),
      m_onEmoteRoutes( std::move( onEmoteRoutes ) ),
      m_onEObjHitRoutes( std::move( onEObjHitRoutes ) )
    {
    }

    void onTalk( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId ) override
    {
      for( const auto& route : m_onTalkRoutes )
      {
        if( route.actorId != 0 && route.actorId != actorId )
          continue;

        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onBNpcKill( Sapphire::World::Quest& quest, Sapphire::Entity::BNpc& bnpc,
                     Sapphire::Entity::Player& player ) override
    {
      for( const auto& route : m_onKillRoutes )
      {
        if( route.bnpcNameId != 0 && route.bnpcNameId != bnpc.getBNpcNameId() )
          continue;

        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onEventItem( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId ) override
    {
      for( const auto& route : m_onEventItemRoutes )
      {
        if( route.actorId != 0 && route.actorId != actorId )
          continue;

        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onEventGroundItem( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player,
                            Common::Vector3 pos ) override
    {
      for( const auto& route : m_onEventGroundItemRoutes )
      {
        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        if( !matchesGroundItemTarget( route.target, player, pos ) )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onEnterTerritory( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint16_t param1,
                           uint16_t param2 ) override
    {
      for( const auto& route : m_onEnterTerritoryRoutes )
      {
        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        if( route.hasParam1 && route.param1 != param1 )
          continue;

        if( route.hasParam2 && route.param2 != param2 )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onWithinRange( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint32_t eventId,
                        uint32_t param1, float x, float y, float z ) override
    {
      ( void ) eventId;
      ( void ) x;
      ( void ) y;
      ( void ) z;

      for( const auto& route : m_onWithinRangeRoutes )
      {
        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        if( route.hasParam1 && route.param1 != param1 )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onOutsideRange( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint32_t eventId,
                         uint32_t param1, float x, float y, float z ) override
    {
      ( void ) eventId;
      ( void ) x;
      ( void ) y;
      ( void ) z;

      for( const auto& route : m_onOutsideRangeRoutes )
      {
        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        if( route.hasParam1 && route.param1 != param1 )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onEmote( Sapphire::World::Quest& quest, uint64_t actorId, uint32_t emoteId,
                  Sapphire::Entity::Player& player ) override
    {
      for( const auto& route : m_onEmoteRoutes )
      {
        if( route.actorId != 0 && route.actorId != actorId )
          continue;

        if( route.emoteId != emoteId )
          continue;

        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    void onEObjHit( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId,
                    uint32_t actionId ) override
    {
      for( const auto& route : m_onEObjHitRoutes )
      {
        if( route.actorId != 0 && route.actorId != actorId )
          continue;

        if( route.actionId != actionId )
          continue;

        if( !matchesQuestRouteState( quest, route.hasSeq, route.seq, route.hasBitFlag8Set, route.bitFlag8Set,
                                     route.hasBitFlag8Clear, route.bitFlag8Clear ) )
          continue;

        executeAction( route.action, quest, player, getId(), nullptr );
        return;
      }
    }

    Sapphire::Event::EventHandler::QuestAvailability getQuestAvailability( Sapphire::Entity::Player& player,
                                                                           uint32_t eventId ) override
    {
      ( void ) player;
      ( void ) eventId;
      return m_availability;
    }

  private:
    static bool matchesQuestRouteState( Sapphire::World::Quest& quest, bool hasSeq, uint8_t seq, bool hasBitFlag8Set,
                                        uint8_t bitFlag8Set, bool hasBitFlag8Clear, uint8_t bitFlag8Clear )
    {
      if( hasSeq && seq != quest.getSeq() )
        return false;

      if( hasBitFlag8Set && !quest.getBitFlag8( bitFlag8Set ) )
        return false;

      if( hasBitFlag8Clear && quest.getBitFlag8( bitFlag8Clear ) )
        return false;

      return true;
    }

    static bool matchesGroundItemTarget( const Sapphire::Scripting::LuaQuestGroundItemTarget& target,
                                         Sapphire::Entity::Player& player, Common::Vector3 pos )
    {
      Common::QuestEobject eobject = { target.id,
                                       target.territoryId,
                                       Common::Vector3{ target.x, target.y, target.z },
                                       target.radius };
      auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
      return eventMgr.checkHitEobject( player, pos, eobject );
    }

    static std::vector< uint32_t > buildNoticeValues( const Sapphire::Scripting::LuaQuestAction& action )
    {
      return action.values;
    }

    static uint32_t applyQuestDelta( uint32_t currentValue, int32_t delta )
    {
      const auto updatedValue = static_cast< int64_t >( currentValue ) + delta;
      if( updatedValue < 0 )
        return 0;

      return static_cast< uint32_t >( std::min< int64_t >( updatedValue, 0xFF ) );
    }

    static void runNextAction( const std::shared_ptr< Sapphire::Scripting::LuaQuestAction >& pAction,
                               Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint32_t questId,
                               const Sapphire::Event::SceneResult* pResult )
    {
      if( pAction )
        executeAction( pAction, quest, player, questId, pResult );
    }

    static bool shouldRunTransition( const Sapphire::Scripting::LuaQuestTransition& transition,
                                     const Sapphire::Event::SceneResult& result )
    {
      if( transition.comparison == Sapphire::Scripting::LuaQuestTransition::Comparison::Always )
        return true;

      const auto actual = result.getResult( transition.resultIndex );
      const auto expected = transition.compareValue;

      switch( transition.comparison )
      {
        case Sapphire::Scripting::LuaQuestTransition::Comparison::Eq:
          return actual == expected;

        case Sapphire::Scripting::LuaQuestTransition::Comparison::Neq:
          return actual != expected;

        case Sapphire::Scripting::LuaQuestTransition::Comparison::Gt:
          return actual > expected;

        case Sapphire::Scripting::LuaQuestTransition::Comparison::Gte:
          return actual >= expected;

        case Sapphire::Scripting::LuaQuestTransition::Comparison::Lt:
          return actual < expected;

        case Sapphire::Scripting::LuaQuestTransition::Comparison::Lte:
          return actual <= expected;

        case Sapphire::Scripting::LuaQuestTransition::Comparison::Always:
        default:
          return true;
      }
    }

    static void executeAction( const std::shared_ptr< const Sapphire::Scripting::LuaQuestAction >& pAction,
                               Sapphire::World::Quest& quest, Sapphire::Entity::Player& player, uint32_t questId,
                               const Sapphire::Event::SceneResult* pResult )
    {
      if( !pAction )
      {
        Sapphire::World::Manager::PlayerMgr::sendDebug( player, "Lua quest action is missing for questId#{0}",
                                                        questId );
        return;
      }

      const auto& action = *pAction;
      auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

      switch( action.kind )
      {
        case Sapphire::Scripting::LuaQuestAction::Kind::PlayQuestScene:
        {
          if( action.onReturn && action.onReturn->nextAction )
          {
            auto transition = action.onReturn;
            auto callback = [ transition ]( Sapphire::World::Quest& quest, Sapphire::Entity::Player& player,
                                            const Sapphire::Event::SceneResult& result )
            {
              if( transition && transition->nextAction && shouldRunTransition( *transition, result ) )
                executeAction( transition->nextAction, quest, player, result.eventId, &result );
            };

            eventMgr.playQuestScene( player, questId, action.scene, action.flags, callback );
          }
          else
          {
            eventMgr.playQuestScene( player, questId, action.scene, action.flags, nullptr );
          }
          return;
        }

        case Sapphire::Scripting::LuaQuestAction::Kind::SetSeq:
          quest.setSeq( static_cast< uint8_t >( action.seq ) );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::FinishQuest:
        {
          uint32_t rewardChoice = action.rewardChoice;
          if( action.useRewardResultIndex && pResult )
            rewardChoice = pResult->getResult( action.rewardResultIndex );

          player.finishQuest( static_cast< uint16_t >( questId ), rewardChoice );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;
        }

        case Sapphire::Scripting::LuaQuestAction::Kind::EventNotice:
          eventMgr.sendNotice( player, questId, action.noticeId, buildNoticeValues( action ) );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::QuestProgressNotice:
          eventMgr.sendNotice( player, questId, action.noticeId,
                               { getQuestValueField( quest, action.field ), action.goal } );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::SetQuestValue:
          setQuestValueField( quest, action.field, action.value );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::AdjustQuestValue:
          setQuestValueField( quest, action.field, applyQuestDelta( getQuestValueField( quest, action.field ),
                                                                    action.delta ) );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::SetBitFlag8:
          quest.setBitFlag8( static_cast< uint8_t >( action.bitFlagIndex ), action.bitFlagValue );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::CompleteIfQuestValueAtLeast:
          if( getQuestValueField( quest, action.field ) >= action.goal )
          {
            for( const auto resetField : action.resetFields )
              setQuestValueField( quest, resetField, 0 );

            for( const auto bitFlagIndex : action.clearBitFlags8 )
              quest.setBitFlag8( static_cast< uint8_t >( bitFlagIndex ), false );

            if( action.hasCompleteSeq )
              quest.setSeq( static_cast< uint8_t >( action.completeSeq ) );
          }
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::StartEvent:
          eventMgr.eventStart(
            player, action.actorId, questId,
            static_cast< Sapphire::Event::EventHandler::EventType >( action.eventType ),
            action.eventParam1, action.eventParam2 );
          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;

        case Sapphire::Scripting::LuaQuestAction::Kind::AdvanceKillCounter:
        {
          const auto currentValue = getQuestValueField( quest, action.field ) + action.amount;

          if( currentValue >= action.goal )
          {
            if( action.hasCompleteSeq )
              quest.setSeq( static_cast< uint8_t >( action.completeSeq ) );
            else
              setQuestValueField( quest, action.field, action.goal );
          }
          else
          {
            setQuestValueField( quest, action.field, currentValue );
          }

          if( action.hasNoticeId )
            eventMgr.sendNotice( player, questId, action.noticeId, { currentValue, action.goal } );

          runNextAction( action.nextAction, quest, player, questId, pResult );
          return;
        }

        case Sapphire::Scripting::LuaQuestAction::Kind::Invalid:
        default:
          Sapphire::World::Manager::PlayerMgr::sendDebug( player, "Lua quest action is invalid for questId#{0}",
                                                          questId );
          return;
      }
    }

    Sapphire::Event::EventHandler::QuestAvailability m_availability;
    std::vector< Sapphire::Scripting::LuaQuestTalkRoute > m_onTalkRoutes;
    std::vector< Sapphire::Scripting::LuaQuestKillRoute > m_onKillRoutes;
    std::vector< Sapphire::Scripting::LuaQuestEventItemRoute > m_onEventItemRoutes;
    std::vector< Sapphire::Scripting::LuaQuestEventGroundItemRoute > m_onEventGroundItemRoutes;
    std::vector< Sapphire::Scripting::LuaQuestEnterTerritoryRoute > m_onEnterTerritoryRoutes;
    std::vector< Sapphire::Scripting::LuaQuestRangeRoute > m_onWithinRangeRoutes;
    std::vector< Sapphire::Scripting::LuaQuestRangeRoute > m_onOutsideRangeRoutes;
    std::vector< Sapphire::Scripting::LuaQuestEmoteRoute > m_onEmoteRoutes;
    std::vector< Sapphire::Scripting::LuaQuestEObjHitRoute > m_onEObjHitRoutes;
  };
} // namespace
} // namespace Sapphire

namespace Sapphire::Scripting
{
  LuaScriptRuntime::LuaScriptRuntime( std::string scriptRoot, bool hotReload ) :
    m_scriptRoot( std::move( scriptRoot ) ),
    m_hotReload( hotReload )
  {
  }

  void LuaScriptRuntime::unloadAll()
  {
    std::scoped_lock lock( m_mutex );

    std::vector< std::string > moduleNames;
    moduleNames.reserve( m_loadedModules.size() );

    for( const auto& [ moduleName, module ] : m_loadedModules )
      moduleNames.push_back( moduleName );

    for( const auto& moduleName : moduleNames )
      unloadModule( moduleName );

    m_scripts.clear();

    while( !m_scriptLoadQueue.empty() )
      m_scriptLoadQueue.pop();
  }

  bool LuaScriptRuntime::loadScript( const std::string& path )
  {
    std::scoped_lock lock( m_mutex );

    if( !fs::exists( path ) )
    {
      Logger::error( "LuaScriptRuntime: failed to stage Lua script {0}, file does not exist.", path );
      return false;
    }

    std::string source;
    if( !readFileToString( path, source ) )
    {
      Logger::error( "LuaScriptRuntime: failed to read Lua script {0}.", path );
      return false;
    }

    std::string scriptBody;
    if( !extractFirstTableBody( source, scriptBody ) )
    {
      Logger::error( "LuaScriptRuntime: script {0} is missing a root return table.", path );
      return false;
    }

    const auto moduleName = getModuleNameForPath( path );
    if( moduleName.empty() )
    {
      Logger::error( "LuaScriptRuntime: failed to derive a module name for {0}.", path );
      return false;
    }

    if( isModuleLoaded( moduleName ) )
      unloadModule( moduleName );

    std::string scriptType;
    if( !findQuotedAssignment( scriptBody, "type", scriptType ) )
    {
      Logger::error( "LuaScriptRuntime: script {0} is missing a string 'type' field.", path );
      return false;
    }

    LuaModule module;
    module.moduleName = moduleName;
    module.path = path;

    const auto normalizedType = normalizeToken( scriptType );
    bool success = false;

    if( normalizedType == "event" )
      success = loadEventScript( moduleName, scriptBody, module );
    else if( normalizedType == "quest" )
      success = loadQuestScript( moduleName, scriptBody, module );
    else
      Logger::error( "LuaScriptRuntime: unsupported script type '{0}' in {1}.", scriptType, path );

    if( !success )
    {
      for( auto* script : module.scripts )
        delete script;

      return false;
    }

    m_loadedModules[ moduleName ] = std::move( module );
    Logger::debug( "LuaScriptRuntime: loaded Lua module {0} from {1}", moduleName, path );
    return true;
  }

  bool LuaScriptRuntime::unloadScript( const std::string& name )
  {
    std::scoped_lock lock( m_mutex );

    return unloadModule( name );
  }

  void LuaScriptRuntime::queueScriptReload( const std::string& name )
  {
    std::scoped_lock lock( m_mutex );

    m_scriptLoadQueue.push( name );
  }

  void LuaScriptRuntime::findScripts( std::set< ScriptInfo* >& scripts, const std::string& search )
  {
    ( void ) scripts;
    ( void ) search;
  }

  void LuaScriptRuntime::processLoadQueue()
  {
    std::scoped_lock lock( m_mutex );

    while( !m_scriptLoadQueue.empty() )
    {
      const auto moduleName = m_scriptLoadQueue.front();
      m_scriptLoadQueue.pop();

      const auto it = m_loadedModules.find( moduleName );
      if( it == m_loadedModules.end() )
      {
        Logger::debug( "LuaScriptRuntime: skipping reload for unknown Lua module {0}", moduleName );
        continue;
      }

      const auto path = it->second.path;
      unloadModule( moduleName );

      if( !loadScript( path ) )
        Logger::error( "LuaScriptRuntime: failed to reload Lua module {0} from {1}", moduleName, path );
    }
  }

  std::string LuaScriptRuntime::getModuleExtension()
  {
    return ".lua";
  }

  std::string LuaScriptRuntime::getModuleNameForPath( const std::string& path )
  {
    std::scoped_lock lock( m_mutex );

    fs::path scriptPath( path );
    fs::path relativePath = scriptPath;
    std::error_code ec;
    scriptPath = fs::weakly_canonical( scriptPath, ec );
    if( ec )
    {
      ec.clear();
      scriptPath = fs::path( path );
    }

    if( !m_scriptRoot.empty() )
    {
      fs::path rootPath( m_scriptRoot );
      rootPath = fs::weakly_canonical( rootPath, ec );
      if( ec )
      {
        ec.clear();
        rootPath = fs::path( m_scriptRoot );
      }

      relativePath = fs::relative( scriptPath, rootPath, ec );
      if( ec )
        relativePath = scriptPath.filename();
    }

    relativePath.replace_extension();
    return relativePath.generic_string();
  }

  bool LuaScriptRuntime::isModuleLoaded( const std::string& name )
  {
    std::scoped_lock lock( m_mutex );

    return m_loadedModules.find( name ) != m_loadedModules.end();
  }

  ScriptAPI::ScriptObject* LuaScriptRuntime::getScriptObject( std::size_t type, uint32_t scriptId )
  {
    std::scoped_lock lock( m_mutex );

    const auto typeIt = m_scripts.find( type );
    if( typeIt == m_scripts.end() )
      return nullptr;

    const auto scriptIt = typeIt->second.find( scriptId );
    if( scriptIt == typeIt->second.end() )
      return nullptr;

    return scriptIt->second;
  }

  const std::string& LuaScriptRuntime::getScriptRoot() const
  {
    return m_scriptRoot;
  }

  bool LuaScriptRuntime::isHotReloadEnabled() const
  {
    return m_hotReload;
  }

  std::vector< LuaScriptRuntime::LoadedScriptDescriptor > LuaScriptRuntime::getLoadedScriptDescriptors()
  {
    std::scoped_lock lock( m_mutex );

    std::vector< LoadedScriptDescriptor > descriptors;
    descriptors.reserve( m_loadedModules.size() );

    for( const auto& [ moduleName, module ] : m_loadedModules )
    {
      for( const auto* script : module.scripts )
      {
        if( !script )
          continue;

        descriptors.push_back( LoadedScriptDescriptor{ script->getType(), script->getId(), moduleName } );
      }
    }

    return descriptors;
  }

  bool LuaScriptRuntime::loadEventScript( const std::string& moduleName, const std::string& source, LuaModule& module )
  {
    uint32_t eventId = 0;
    if( !findUnsignedAssignment( source, "id", eventId ) )
    {
      Logger::error( "LuaScriptRuntime: event module {0} is missing a numeric 'id' field.", moduleName );
      return false;
    }

    std::string onTalkBody;
    if( !extractTableAssignment( source, "onTalk", onTalkBody ) )
    {
      Logger::error( "LuaScriptRuntime: event module {0} is missing an 'onTalk' table.", moduleName );
      return false;
    }

    LuaEventAction action;
    if( !parseActionTable( onTalkBody, action, "event module " + moduleName + ".onTalk" ) )
      return false;

    auto script = new LuaEventScript( eventId, std::move( action ) );
    auto& scriptsByType = m_scripts[ script->getType() ];

    if( scriptsByType.find( eventId ) != scriptsByType.end() )
    {
      Logger::error( "LuaScriptRuntime: duplicate Lua event script id {0} in module {1}.", eventId, moduleName );
      delete script;
      return false;
    }

    scriptsByType[ eventId ] = script;
    module.scripts.push_back( script );
    return true;
  }

  bool LuaScriptRuntime::loadQuestScript( const std::string& moduleName, const std::string& source, LuaModule& module )
  {
    uint32_t questId = 0;
    if( !findUnsignedAssignment( source, "id", questId ) )
    {
      Logger::error( "LuaScriptRuntime: quest module {0} is missing a numeric 'id' field.", moduleName );
      return false;
    }

    Event::EventHandler::QuestAvailability availability = Event::EventHandler::QuestAvailability::Available;
    std::string availabilityValue;
    if( findQuotedAssignment( source, "availability", availabilityValue ) &&
        !parseQuestAvailability( availabilityValue, availability ) )
    {
      Logger::error( "LuaScriptRuntime: quest module {0} uses unsupported availability '{1}'.", moduleName,
                     availabilityValue );
      return false;
    }

    std::vector< LuaQuestTalkRoute > talkRoutes;
    std::string onTalkBody;
    if( extractTableAssignment( source, "onTalk", onTalkBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onTalkBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onTalk routes.", moduleName );
        return false;
      }

      talkRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestTalkRoute route;
        if( !parseQuestTalkRoute(
              routeBody, route,
              "quest module " + moduleName + ".onTalk[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        talkRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestKillRoute > killRoutes;
    std::string onKillBody;
    if( extractTableAssignment( source, "onBNpcKill", onKillBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onKillBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onBNpcKill routes.", moduleName );
        return false;
      }

      killRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestKillRoute route;
        if( !parseQuestKillRoute(
              routeBody, route,
              "quest module " + moduleName + ".onBNpcKill[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        killRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestEventItemRoute > eventItemRoutes;
    std::string onEventItemBody;
    if( extractTableAssignment( source, "onEventItem", onEventItemBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onEventItemBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onEventItem routes.", moduleName );
        return false;
      }

      eventItemRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestEventItemRoute route;
        if( !parseQuestEventItemRoute(
              routeBody, route,
              "quest module " + moduleName + ".onEventItem[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        eventItemRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestEventGroundItemRoute > eventGroundItemRoutes;
    std::string onEventGroundItemBody;
    if( extractTableAssignment( source, "onEventGroundItem", onEventGroundItemBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onEventGroundItemBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onEventGroundItem routes.",
                       moduleName );
        return false;
      }

      eventGroundItemRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestEventGroundItemRoute route;
        if( !parseQuestEventGroundItemRoute(
              routeBody, route,
              "quest module " + moduleName + ".onEventGroundItem[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        eventGroundItemRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestEnterTerritoryRoute > enterTerritoryRoutes;
    std::string onEnterTerritoryBody;
    if( extractTableAssignment( source, "onEnterTerritory", onEnterTerritoryBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onEnterTerritoryBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onEnterTerritory routes.",
                       moduleName );
        return false;
      }

      enterTerritoryRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestEnterTerritoryRoute route;
        if( !parseQuestEnterTerritoryRoute(
              routeBody, route,
              "quest module " + moduleName + ".onEnterTerritory[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        enterTerritoryRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestRangeRoute > withinRangeRoutes;
    std::string onWithinRangeBody;
    if( extractTableAssignment( source, "onWithinRange", onWithinRangeBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onWithinRangeBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onWithinRange routes.",
                       moduleName );
        return false;
      }

      withinRangeRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestRangeRoute route;
        if( !parseQuestRangeRoute(
              routeBody, route,
              "quest module " + moduleName + ".onWithinRange[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        withinRangeRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestRangeRoute > outsideRangeRoutes;
    std::string onOutsideRangeBody;
    if( extractTableAssignment( source, "onOutsideRange", onOutsideRangeBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onOutsideRangeBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onOutsideRange routes.",
                       moduleName );
        return false;
      }

      outsideRangeRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestRangeRoute route;
        if( !parseQuestRangeRoute(
              routeBody, route,
              "quest module " + moduleName + ".onOutsideRange[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        outsideRangeRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestEmoteRoute > emoteRoutes;
    std::string onEmoteBody;
    if( extractTableAssignment( source, "onEmote", onEmoteBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onEmoteBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onEmote routes.", moduleName );
        return false;
      }

      emoteRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestEmoteRoute route;
        if( !parseQuestEmoteRoute(
              routeBody, route,
              "quest module " + moduleName + ".onEmote[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        emoteRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    std::vector< LuaQuestEObjHitRoute > eObjHitRoutes;
    std::string onEObjHitBody;
    if( extractTableAssignment( source, "onEObjHit", onEObjHitBody ) )
    {
      std::vector< std::string > routeBodies;
      extractAnonymousTableList( onEObjHitBody, routeBodies );
      if( routeBodies.empty() )
      {
        Logger::error( "LuaScriptRuntime: quest module {0} does not define any onEObjHit routes.", moduleName );
        return false;
      }

      eObjHitRoutes.reserve( routeBodies.size() );

      size_t routeIndex = 0;
      for( const auto& routeBody : routeBodies )
      {
        LuaQuestEObjHitRoute route;
        if( !parseQuestEObjHitRoute(
              routeBody, route,
              "quest module " + moduleName + ".onEObjHit[" + std::to_string( routeIndex ) + "]" ) )
          return false;

        eObjHitRoutes.push_back( std::move( route ) );
        ++routeIndex;
      }
    }

    if( talkRoutes.empty() && killRoutes.empty() && eventItemRoutes.empty() && eventGroundItemRoutes.empty() &&
        enterTerritoryRoutes.empty() && withinRangeRoutes.empty() && outsideRangeRoutes.empty() &&
        emoteRoutes.empty() && eObjHitRoutes.empty() )
    {
      Logger::error(
        "LuaScriptRuntime: quest module {0} must define at least one supported hook table such as onTalk, onBNpcKill, onEventItem, onEventGroundItem, onEnterTerritory, onWithinRange, onOutsideRange, onEmote, or onEObjHit.",
        moduleName );
      return false;
    }

    auto script = new LuaQuestScript( questId, availability, std::move( talkRoutes ), std::move( killRoutes ),
                                      std::move( eventItemRoutes ), std::move( eventGroundItemRoutes ),
                                      std::move( enterTerritoryRoutes ), std::move( withinRangeRoutes ),
                                      std::move( outsideRangeRoutes ), std::move( emoteRoutes ),
                                      std::move( eObjHitRoutes ) );
    auto& scriptsByType = m_scripts[ script->getType() ];

    if( scriptsByType.find( questId ) != scriptsByType.end() )
    {
      Logger::error( "LuaScriptRuntime: duplicate Lua quest script id {0} in module {1}.", questId, moduleName );
      delete script;
      return false;
    }

    scriptsByType[ questId ] = script;
    module.scripts.push_back( script );
    return true;
  }

  bool LuaScriptRuntime::unloadModule( const std::string& moduleName )
  {
    const auto moduleIt = m_loadedModules.find( moduleName );
    if( moduleIt == m_loadedModules.end() )
      return false;

    for( auto* script : moduleIt->second.scripts )
    {
      if( !script )
        continue;

      const auto type = script->getType();
      const auto id = script->getId();

      auto typeIt = m_scripts.find( type );
      if( typeIt != m_scripts.end() )
      {
        typeIt->second.erase( id );
        if( typeIt->second.empty() )
          m_scripts.erase( typeIt );
      }

      delete script;
    }

    m_loadedModules.erase( moduleIt );
    return true;
  }

  std::shared_ptr< LuaScriptRuntime > createLuaScriptRuntime( const std::string& scriptRoot, bool hotReload )
  {
    return std::make_shared< LuaScriptRuntime >( scriptRoot, hotReload );
  }
}
