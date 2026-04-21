#pragma once

#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <mutex>
#include <cstdint>
#include <vector>

#include "IScriptRuntime.h"

namespace Sapphire::Scripting
{
  struct LuaEventTransition;
  struct LuaQuestTransition;
  enum class LuaQuestValueField
  {
    Invalid,
    UI8A,
    UI8B,
    UI8C,
    UI8D,
    UI8E,
    UI8F,
    UI8AH,
    UI8BH,
    UI8CH,
    UI8DH,
    UI8EH,
    UI8FH,
    UI8AL,
    UI8BL,
    UI8CL,
    UI8DL,
    UI8EL,
    UI8FL,
  };

  struct LuaEventAction
  {
    enum class Kind
    {
      Invalid,
      PlayScene,
      EventNotice,
      ServerNotice,
      UrgentNotice,
      DebugNotice,
    };

    Kind kind{ Kind::Invalid };
    uint32_t scene{ 0 };
    uint32_t flags{ 0 };
    int8_t noticeId{ 0 };
    std::vector< uint32_t > values;
    std::vector< uint32_t > appendResultIndices;
    std::string message;
    std::shared_ptr< LuaEventTransition > onReturn;
  };

  struct LuaEventTransition
  {
    enum class Comparison
    {
      Always,
      Eq,
      Neq,
      Gt,
      Gte,
      Lt,
      Lte,
    };

    Comparison comparison{ Comparison::Always };
    uint32_t resultIndex{ 0 };
    uint32_t compareValue{ 0 };
    std::shared_ptr< LuaEventAction > nextAction;
  };

  struct LuaQuestAction
  {
    enum class Kind
    {
      Invalid,
      PlayQuestScene,
      SetSeq,
      FinishQuest,
      EventNotice,
      QuestProgressNotice,
      SetQuestValue,
      AdjustQuestValue,
      SetBitFlag8,
      CompleteIfQuestValueAtLeast,
      StartEvent,
      AdvanceKillCounter,
    };

    Kind kind{ Kind::Invalid };
    uint32_t scene{ 0 };
    uint32_t flags{ 0 };
    uint32_t seq{ 0 };
    uint32_t rewardChoice{ 0 };
    uint32_t rewardResultIndex{ 0 };
    bool useRewardResultIndex{ false };
    int8_t noticeId{ 0 };
    bool hasNoticeId{ false };
    LuaQuestValueField field{ LuaQuestValueField::Invalid };
    uint32_t value{ 0 };
    int32_t delta{ 0 };
    uint32_t amount{ 1 };
    uint32_t goal{ 0 };
    uint32_t completeSeq{ 0 };
    bool hasCompleteSeq{ false };
    uint32_t bitFlagIndex{ 0 };
    bool bitFlagValue{ false };
    uint64_t actorId{ 0 };
    uint8_t eventType{ 0 };
    uint8_t eventParam1{ 0 };
    uint32_t eventParam2{ 0 };
    std::vector< uint32_t > values;
    std::vector< LuaQuestValueField > resetFields;
    std::vector< uint32_t > clearBitFlags8;
    std::shared_ptr< LuaQuestTransition > onReturn;
    std::shared_ptr< LuaQuestAction > nextAction;
  };

  struct LuaQuestTransition
  {
    using Comparison = LuaEventTransition::Comparison;

    Comparison comparison{ Comparison::Always };
    uint32_t resultIndex{ 0 };
    uint32_t compareValue{ 0 };
    std::shared_ptr< LuaQuestAction > nextAction;
  };

  struct LuaQuestTalkRoute
  {
    uint64_t actorId{ 0 };
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestKillRoute
  {
    uint32_t bnpcNameId{ 0 };
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestEventItemRoute
  {
    uint64_t actorId{ 0 };
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestEmoteRoute
  {
    uint64_t actorId{ 0 };
    uint32_t emoteId{ 0 };
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestEObjHitRoute
  {
    uint64_t actorId{ 0 };
    uint32_t actionId{ 0 };
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestGroundItemTarget
  {
    uint32_t id{ 0 };
    uint32_t territoryId{ 0 };
    float x{ 0.0f };
    float y{ 0.0f };
    float z{ 0.0f };
    float radius{ 1.0f };
  };

  struct LuaQuestEventGroundItemRoute
  {
    LuaQuestGroundItemTarget target;
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestEnterTerritoryRoute
  {
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    bool hasParam1{ false };
    uint16_t param1{ 0 };
    bool hasParam2{ false };
    uint16_t param2{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  struct LuaQuestRangeRoute
  {
    bool hasSeq{ false };
    uint8_t seq{ 0 };
    bool hasBitFlag8Set{ false };
    uint8_t bitFlag8Set{ 0 };
    bool hasBitFlag8Clear{ false };
    uint8_t bitFlag8Clear{ 0 };
    bool hasParam1{ false };
    uint32_t param1{ 0 };
    std::shared_ptr< LuaQuestAction > action;
  };

  class LuaScriptRuntime : public IScriptRuntime
  {
  public:
    struct LoadedScriptDescriptor
    {
      std::size_t type;
      uint32_t id;
      std::string moduleName;
    };

    LuaScriptRuntime( std::string scriptRoot, bool hotReload );

    void unloadAll() override;
    bool loadScript( const std::string& path ) override;
    bool unloadScript( const std::string& name ) override;
    void queueScriptReload( const std::string& name ) override;
    void findScripts( std::set< ScriptInfo* >& scripts, const std::string& search ) override;
    void processLoadQueue() override;
    std::string getModuleExtension() override;
    std::string getModuleNameForPath( const std::string& path ) override;
    bool isModuleLoaded( const std::string& name ) override;
    ScriptAPI::ScriptObject* getScriptObject( std::size_t type, uint32_t scriptId ) override;

    const std::string& getScriptRoot() const;
    bool isHotReloadEnabled() const;
    std::vector< LoadedScriptDescriptor > getLoadedScriptDescriptors();

  private:
    struct LuaModule
    {
      std::string moduleName;
      std::string path;
      std::vector< ScriptAPI::ScriptObject* > scripts;
    };

    std::string m_scriptRoot;
    bool m_hotReload;
    std::unordered_map< std::size_t, std::unordered_map< uint32_t, ScriptAPI::ScriptObject* > > m_scripts;
    std::unordered_map< std::string, LuaModule > m_loadedModules;
    std::queue< std::string > m_scriptLoadQueue;
    std::recursive_mutex m_mutex;

    bool loadEventScript( const std::string& moduleName, const std::string& source, LuaModule& module );
    bool loadQuestScript( const std::string& moduleName, const std::string& source, LuaModule& module );
    bool unloadModule( const std::string& moduleName );
  };

  std::shared_ptr< LuaScriptRuntime > createLuaScriptRuntime( const std::string& scriptRoot, bool hotReload );
}
