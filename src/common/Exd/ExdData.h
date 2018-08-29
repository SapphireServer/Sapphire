#ifndef _EXDDATA_H
#define _EXDDATA_H

#include <GameData.h>
#include <File.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

/* TYPES !!
case DataType::boolean: 1
case DataType::int8: 2
case DataType::uint8: 3
case DataType::int16: 4
case DataType::uint16: 5
case DataType::int32: 6
case DataType::uint32: 7
case DataType::float32: 8
case DataType::uint64: 9
*/


namespace Core {

namespace Data {

struct ZoneInfo
{
  uint16_t id;
  std::string zone_str;
  std::string zone_name;
  uint32_t layout_id;
  uint16_t map_id;
  int16_t discovery_index;
  bool is_two_byte;
  uint16_t weather_rate;
  std::map< uint8_t, int32_t > weather_rate_map;

  int32_t aetheryte_index;
  uint8_t zone_type;
};

struct ClassJobInfo
{
  uint8_t id;
  std::string name;
  std::string name_short;
  uint8_t exp_idx;
  uint32_t start_weapon_id;
  uint16_t mod_hp;
  uint16_t mod_mpcpgp;
  uint16_t mod_str;
  uint16_t mod_vit;
  uint16_t mod_dex;
  uint16_t mod_int;
  uint16_t mod_mnd;
  uint16_t mod_pie;
};

struct QuestInfo
{
  uint32_t id;
  std::string name;
  std::string name_intern;
  uint16_t quest_level;
  uint32_t enpc_resident_start;
  uint32_t enpc_resident_end;
  uint16_t reward_exp_factor;
  uint32_t reward_gil;
  uint16_t reward_gc_seals;
  uint8_t reward_item_type;

  std::vector< uint32_t > reward_item;
  std::vector< uint8_t > reward_item_count;
  std::vector< uint8_t > reward_item_stain;

  std::vector< uint32_t > reward_item_optional;
  std::vector< uint8_t > reward_item_optional_count;
  std::vector< uint8_t > reward_item_optional_stain;

  uint8_t reward_emote;
  uint16_t reward_action;
  uint8_t reward_action_general1;
  uint8_t reward_action_general2;

  uint8_t reward_other;

  uint32_t instanced_content_unlock;

  uint8_t reward_tome_type;
  uint8_t reward_tome_count;

  uint8_t reward_reputation;


  std::vector< std::string > script_entity;
  std::vector< uint32_t > script_value;
};

struct EventActionInfo
{
  uint32_t id;
  std::string name;
  uint32_t castTime;
};

struct OpeningInfo
{
  uint32_t id;
  std::string name;
};

struct ParamGrowthInfo
{
  uint32_t level;
  uint32_t needed_exp;
  int16_t hp_mod;
  int32_t mp_const;
  int16_t mp_mod;
  int32_t base_secondary;
  uint16_t quest_exp_mod;
};

struct CustomTalkInfo
{
  uint32_t id;
  std::string name_intern;
};

struct PlaceNameInfo
{
  uint32_t id;
  std::string placename;
};

struct AetheryteInfo
{
  uint32_t id;
  std::string placename;
  std::string placename_aethernet;
  int32_t target_zone;
  int32_t levelId;
  bool isAetheryte;

  int16_t map_coord_x;
  int16_t map_coord_y;
};

struct RaceInfo
{
  uint32_t id;
  std::string name;
  uint32_t male_body;
  uint32_t male_hands;
  uint32_t male_legs;
  uint32_t male_feet;
  uint32_t female_body;
  uint32_t female_hands;
  uint32_t female_legs;
  uint32_t female_feet;

  int8_t mod_str;
  int8_t mod_dex;
  int8_t mod_vit;
  int8_t mod_int;
  int8_t mod_mnd;
  int8_t mod_pie;
};

struct TribeInfo
{
  uint32_t id;
  std::string name;

  int8_t mod_str;
  int8_t mod_dex;
  int8_t mod_vit;
  int8_t mod_int;
  int8_t mod_mnd;
  int8_t mod_pie;
};

struct LevelInfo
{
  uint32_t id;
  float x;
  float y;
  float z;
  float r;
  uint32_t actor_id;
  uint32_t zone_id;
};

struct ClassJobCategoryInfo
{
  uint32_t id;
  // should they add new jobs, this needs to be changed
  bool can_equip[0x33];
};

struct ItemInfo
{
  uint32_t id;
  std::string name;                //0
  uint16_t item_level;             //11
  uint8_t required_level;          //12
  uint16_t unknown_category;       //15
  uint16_t ui_category;            //17
  uint32_t stack_size;             //19
  bool is_hqable;                  //20
  uint64_t model_primary;          //28
  uint64_t model_secondary;        //29
  uint16_t physical_damage;        //49
  uint16_t magical_damage;         //50
  uint16_t delayMs;                //51
  uint32_t class_job_requirement;  //58
  bool is_unique;                  //72
  bool is_untradeable;             //73
  uint32_t class_job_index;        //86
};

struct ActionInfo
{
  uint32_t id;
  std::string name;          // 0
  uint16_t category;         // 3

  int8_t class_job;          // 10
  uint8_t unlock_level;      // 11
  int8_t range;              // 13
  bool can_target_self;      // 14
  bool can_target_party;     // 15
  bool can_target_friendly;  // 16
  bool can_target_enemy;     // 17

  bool is_ground_aoe;        // 20

  bool can_target_ko;        // 24

  uint8_t aoe_type;          // 26
  uint8_t aoe_range;         // 27
  uint8_t aoe_width;         // 28

  uint8_t points_type;       // 30
  uint16_t points_cost;      // 31

  bool is_instant;           // 35
  uint32_t cast_time;        // 36
  uint32_t recast_time;      // 37

  int8_t model;              // 39
  uint8_t aspect;            // 40

  uint16_t toggle_status_id; // 42

  bool affects_position;     // 47

  bool no_effect_in_battle;  // 60


  bool is_aoe;               // Internal only

};

struct EventItemInfo
{
  uint32_t id;
  std::string name; //0
  uint32_t eventId;
  uint32_t castTime;
};

struct StatusEffectInfo
{
  uint32_t id;
  std::string name;        // 0
  bool lock_movement;      // 7
  bool lock_actions;       // 9
  bool lock_control;       // 10
  bool transfiguration;    // 11
  bool can_dispel;         // 13
  bool is_permanent;       // 15
  bool inflicted_by_actor; // 17
  bool is_fc_buff;         // 21
  bool invisibility;       // 22
};

class ExdData
{
public:
  ExdData();

  ~ExdData( void );

  bool init( const std::string& path );

  xiv::exd::Exd setupDatAccess( const std::string& name, xiv::exd::Language lang );

  template< class T >
  T getField( std::vector< xiv::exd::Field >& fields, uint32_t index )
  {
    return *boost::get< T >( &fields.at( index ) );
  }

  boost::shared_ptr< xiv::dat::GameData > m_data;
  boost::shared_ptr< xiv::exd::ExdData > m_exd_data;

  xiv::exd::Exd m_questDat;
  xiv::exd::Exd m_openingDat;
  xiv::exd::Exd m_customTalkDat;
  xiv::exd::Exd m_aetheryteDat;
  xiv::exd::Exd m_levelDat;
  xiv::exd::Exd m_placeNameDat;
  xiv::exd::Exd m_itemsDat;
  xiv::exd::Exd m_classJobCatDat;
  xiv::exd::Exd m_raceDat;
  xiv::exd::Exd m_eventItemDat;

  std::map< uint32_t, ZoneInfo > m_zoneInfoMap;
  std::map< uint8_t, ClassJobInfo > m_classJobInfoMap;
  std::map< uint32_t, ParamGrowthInfo > m_paramGrowthInfoMap;
  std::map< uint16_t, EventActionInfo > m_EventActionInfoMap;
  std::map< uint16_t, boost::shared_ptr< ActionInfo > > m_actionInfoMap;
  std::map< uint16_t, StatusEffectInfo > m_statusEffectInfoMap;
  std::map< uint32_t, boost::shared_ptr< AetheryteInfo > > m_aetheryteInfoMap;
  std::map< uint32_t, TribeInfo > m_tribeInfoMap;

  bool loadZoneInfo();

  bool loadClassJobInfo();

  bool loadParamGrowInfo();

  bool loadEventActionInfo();

  bool loadActionInfo();

  bool loadStatusEffectInfo();

  bool loadAetheryteInfo();

  bool loadTribeInfo();

  boost::shared_ptr< QuestInfo > getQuestInfo( uint32_t questId );

  boost::shared_ptr< OpeningInfo > getOpeningInfo( uint32_t openingId );

  boost::shared_ptr< CustomTalkInfo > getCustomTalkInfo( uint32_t customTalkId );

  boost::shared_ptr< AetheryteInfo > getAetheryteInfo( uint32_t aetheryteId );

  boost::shared_ptr< ActionInfo > getActionInfo( uint32_t actionId );

  boost::shared_ptr< PlaceNameInfo > getPlaceNameInfo( uint32_t placeNameId );

  boost::shared_ptr< ItemInfo > getItemInfo( uint32_t catalogId );

  boost::shared_ptr< RaceInfo > getRaceInfo( uint32_t raceId );

  boost::shared_ptr< EventItemInfo > getEventItemInfo( uint32_t eventItemId );

  boost::shared_ptr< LevelInfo > getLevelInfo( uint32_t levelId );

  const std::vector< boost::shared_ptr< AetheryteInfo > > getAetheryteInfoForZone( uint16_t zoneId );

};

}
}

#endif

