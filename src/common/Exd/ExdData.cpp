#include "ExdData.h"
#include <boost/make_shared.hpp>

#include <boost/variant.hpp>

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



Core::Data::ExdData::ExdData()
{
}

Core::Data::ExdData::~ExdData( void )
{
}

xiv::exd::Exd Core::Data::ExdData::setupDatAccess( const std::string& name, xiv::exd::Language lang )
{
   auto& cat = m_exd_data->get_category( name );
   return static_cast< xiv::exd::Exd >( cat.get_data_ln( lang ) );
};

bool Core::Data::ExdData::init( const std::string& path )
{
   try
   {
      m_data = boost::make_shared< xiv::dat::GameData >( path );
      m_exd_data = boost::make_shared< xiv::exd::ExdData >( *m_data );

      m_questDat = setupDatAccess( "Quest", xiv::exd::Language::en );
      m_openingDat = setupDatAccess( "Opening", xiv::exd::Language::none );
      m_customTalkDat = setupDatAccess( "CustomTalk", xiv::exd::Language::en );
      m_aetheryteDat = setupDatAccess( "Aetheryte", xiv::exd::Language::en );
      m_levelDat = setupDatAccess( "Level", xiv::exd::Language::none );
      m_placeNameDat = setupDatAccess( "PlaceName", xiv::exd::Language::en );
      m_itemsDat = setupDatAccess( "Item", xiv::exd::Language::en );
      m_classJobCatDat = setupDatAccess( "ClassJobCategory", xiv::exd::Language::en );
      m_raceDat = setupDatAccess( "Race", xiv::exd::Language::en );
      m_eventItemDat = setupDatAccess( "EventItem", xiv::exd::Language::en );
   }
   catch( std::runtime_error )
   {
      return false;
   }

   return true;
}

bool Core::Data::ExdData::loadZoneInfo()
{
   auto territoryTypeData  = setupDatAccess( "TerritoryType",  xiv::exd::Language::none );
   auto placeNameData      = setupDatAccess( "PlaceName",      xiv::exd::Language::en );
   auto mapData            = setupDatAccess( "Map",            xiv::exd::Language::none );
   auto weatherRate        = setupDatAccess( "WeatherRate",    xiv::exd::Language::none );

   auto territoryTypeDataRows = territoryTypeData.get_rows();

   for( auto row : territoryTypeDataRows )
   {
      auto& fields = row.second;
      uint32_t id = row.first;

      uint16_t place_id          = getField< uint16_t >( fields, 5 );
      uint16_t map_id            = getField< uint16_t >( fields, 6 );
      std::string zoneStr        = getField< std::string >( fields, 0 );

      if( zoneStr.empty() )
         continue;

      auto placeNameDataFields   = placeNameData.get_row( place_id );
      std::string zone_str       = getField< std::string >( placeNameDataFields, 0 );

      auto mapDataFields         = mapData.get_row( map_id );
      int16_t map_index          = getField< int16_t >( mapDataFields, 12 );
      bool is_two_bytes          = getField< bool >( mapDataFields, 15 );

      uint8_t weather_rate       = getField< uint8_t >( fields, 12 ) > 75 ? 0 : getField< uint8_t >( fields, 12 );
      auto weatherRateFields     = weatherRate.get_row( weather_rate );

      int32_t aetheryte_index = getField< int32_t >( fields, 23 );
      uint8_t zoneType = getField< uint8_t >( fields, 9 );


      ZoneInfo info{ 0 };
      info.id              = id;
      info.zone_name       = zoneStr;
      info.zone_str        = zone_str;
      info.layout_id       = id;
      info.discovery_index = map_index;
      info.is_two_byte     = is_two_bytes;
      info.map_id          = map_id;
      info.weather_rate    = weather_rate; // TODO: deal with weather groups
      info.aetheryte_index = aetheryte_index;
      info.zone_type       = zoneType;


      uint8_t sumPc = 0;
      for( size_t i = 0; i < 16; )
      {
         int32_t weatherId = getField< int32_t >( weatherRateFields, i );

         if( weatherId == 0 )
            break;

         sumPc += getField< uint8_t >( weatherRateFields, i + 1 );
         info.weather_rate_map[sumPc] = weatherId;

         i += 2;
      }

      m_zoneInfoMap[id] = info;

   }

   return true;
}

bool Core::Data::ExdData::loadStatusEffectInfo()
{
   auto StatusDat = setupDatAccess( "Status", xiv::exd::Language::en );
   auto rows1 = StatusDat.get_rows();

   for( auto row : rows1 )
   {
      auto& fields = row.second;
      uint32_t id = row.first;

      StatusEffectInfo info { 0 };
      info.id = id;
      info.name = getField< std::string >( fields, 0 );
      info.lock_movement =      getField< bool >( fields, 7 );  // 7
      info.lock_actions =       getField< bool >( fields, 9 );  // 9
      info.lock_control =       getField< bool >( fields, 10 ); // 10
      info.transfiguration =    getField< bool >( fields, 11 ); // 11
      info.can_dispel =         getField< bool >( fields, 13 ); // 13
      info.is_permanent =       getField< bool >( fields, 15 ); // 15
      info.inflicted_by_actor = getField< bool >( fields, 17 ); // 17
      info.is_fc_buff =         getField< bool >( fields, 21 ); // 21
      info.invisibility =       getField< bool >( fields, 22 ); // 22

      m_statusEffectInfoMap[id] = info;
   }

   return true;
}

bool Core::Data::ExdData::loadAetheryteInfo()
{
   auto AetheryteDat = setupDatAccess( "Aetheryte", xiv::exd::Language::en );
   auto rows = AetheryteDat.get_rows();

   for( auto row : rows )
   {
      auto& fields = row.second;
      auto info = boost::make_shared< AetheryteInfo >();
      info->id = row.first;
      info->target_zone = getField< uint16_t >( fields, 10 );

      info->isAetheryte = getField< bool >( fields, 15 );

      uint16_t placename = getField< uint16_t >( fields, 8 );
      auto placeNameInfo = getPlaceNameInfo( placename );

      if( placeNameInfo )
      {
         info->placename = placeNameInfo->placename;
      }


      uint16_t placename_aethernet = getField< uint16_t >( fields, 9 );

      auto placename_aethernetInfo = getPlaceNameInfo( placename_aethernet );

      if( placename_aethernetInfo )
      {
         info->placename_aethernet = placename_aethernetInfo->placename;
      }

      info->levelId = getField< uint32_t >( fields, 11 );

      info->map_coord_x = getField< int16_t >( fields, 20 );
      info->map_coord_y = getField< int16_t >( fields, 21 );
      m_aetheryteInfoMap.emplace( std::make_pair( info->id, info ) );
   }
   return true;
}

bool Core::Data::ExdData::loadClassJobInfo()
{
   auto ClassJobDat = setupDatAccess( "ClassJob", xiv::exd::Language::en );
   auto rows = ClassJobDat.get_rows();

   for( auto row : rows )
   {
      auto& fields = row.second;
      ClassJobInfo info { 0 };

      uint32_t id = row.first;

      if( id == 0 )
         continue;

      std::string name        = getField< std::string >( fields, 0 );
      std::string short_name  = getField< std::string >( fields, 1 );
      int8_t exp_idx          = getField< int8_t >( fields, 4 );

      
      info.id              = id;
      info.name            = name;
      info.name_short      = short_name;
      info.exp_idx         = exp_idx;
      info.start_weapon_id = getField< int32_t >( fields, 28 );
      info.mod_hp          = getField< uint16_t >( fields, 9 );
      info.mod_mpcpgp      = getField< uint16_t >( fields, 10 );
      info.mod_str         = getField< uint16_t >( fields, 11 );
      info.mod_vit         = getField< uint16_t >( fields, 12 );
      info.mod_dex         = getField< uint16_t >( fields, 13 );
      info.mod_int         = getField< uint16_t >( fields, 14 );
      info.mod_mnd         = getField< uint16_t >( fields, 15 );
      info.mod_pie         = getField< uint16_t >( fields, 16 );

      m_classJobInfoMap[id] = info;
   }

   return true;
}

bool Core::Data::ExdData::loadParamGrowInfo()
{
   auto ParamGrowDat = setupDatAccess( "ParamGrow", xiv::exd::Language::none );
   auto rows = ParamGrowDat.get_rows();

   for( auto row : rows )
   {
      auto& fields = row.second;

      ParamGrowthInfo info { 0 };
      uint32_t id       = row.first;
      info.level        = id;
      info.needed_exp   = getField< int32_t >( fields, 0 );
      info.mp_mod = getField< uint16_t >( fields, 3 ); // 3
      info.mp_const     = getField< int32_t >( fields, 4 );  // 4
      info.base_secondary = getField< int32_t >( fields, 5 );// 5
      info.quest_exp_mod = getField< uint8_t >( fields, 7 ); // 7
      info.hp_mod = getField< uint16_t >(fields, 8);         // 8


      m_paramGrowthInfoMap[id] = info;
   }

   return true;
}

bool Core::Data::ExdData::loadTribeInfo()
{
   auto tribeDat = setupDatAccess( "Tribe", xiv::exd::Language::en );
   auto rows = tribeDat.get_rows();

   for( auto row : rows )
   {
      auto& fields = row.second;

      TribeInfo info { 0 };
      uint32_t id = row.first;
      info.id = id;
      info.name = getField< std::string >( fields, 0 );
      info.mod_str = getField< int8_t >( fields, 4 );
      info.mod_vit = getField< int8_t >( fields, 5 );
      info.mod_dex = getField< int8_t >( fields, 6 );
      info.mod_int = getField< int8_t >( fields, 7 );
      info.mod_mnd = getField< int8_t >( fields, 8 );
      info.mod_pie = getField< int8_t >( fields, 9 );

      m_tribeInfoMap[id] = info;
   }

   return true;
}

bool Core::Data::ExdData::loadEventActionInfo()
{
   auto EventActionDat = setupDatAccess( "EventAction", xiv::exd::Language::en );
   auto rows = EventActionDat.get_rows();

   for( auto row : rows )
   {
      auto& fields = row.second;

      EventActionInfo info { 0 };

      uint32_t id = row.first;

      if( id == 0 )
      {
         continue;
      }

      std::string name = getField< std::string >( fields, 0 );
      uint8_t time     = getField< uint8_t >( fields, 2 );

      info.id = id;
      info.name = name;
      info.castTime = time * 1000;

      m_EventActionInfoMap[id] = info;

   }

   return true;
}

bool Core::Data::ExdData::loadActionInfo()
{
   auto ActionDat = setupDatAccess( "Action", xiv::exd::Language::en );
   auto rows = ActionDat.get_rows();

   for( auto row : rows )
   {
      auto& fields = row.second;
      auto info = boost::make_shared< ActionInfo >();

      uint32_t id = row.first;
      if( id == 0 )
      {
         continue;
      }

      std::string name          = getField< std::string >( fields, 0 );  // 0
      uint8_t category          = getField< uint8_t >( fields, 3 );      // 3

      int8_t class_job          = getField< int8_t >( fields, 10 );      // 10
      uint8_t unlock_level      = getField< uint8_t >( fields, 11 );     // 11
      int8_t range              = getField< int8_t >( fields, 14 );      // 13
      bool can_target_self      = getField< bool >( fields, 15 );        // 14
      bool can_target_party     = getField< bool>( fields, 16 );         // 15
      bool can_target_friendly  = getField< bool >( fields, 17 );        // 16
      bool can_target_enemy     = getField< bool >( fields, 18 );        // 17

      bool is_ground_aoe        = getField< bool >( fields, 21 );        // 20
      // Column 23: Seems to be related to raising skills (Raise, Resurrection, Reanimate)
      bool can_target_ko        = getField< bool >( fields, 25 );        // 24

      uint8_t aoe_type          = getField< uint8_t >( fields, 27 );     // 26
      uint8_t aoe_range         = getField< uint8_t >( fields, 28 );     // 27
      uint8_t aoe_width         = getField< uint8_t >( fields, 29 );     // 28

      uint8_t points_type       = getField< uint8_t >( fields, 31 );     // 30
      uint16_t points_cost      = getField< uint16_t >( fields, 32 );    // 31

      bool is_instant           = getField< bool >( fields, 36 );        // 35
      uint16_t cast_time        = getField< uint16_t >( fields, 37 );    // 36
      uint16_t recast_time      = getField< uint16_t >( fields, 38 );    // 37

      int8_t model              = getField< int8_t >( fields, 40 );      // 39
      uint8_t aspect            = getField< uint8_t >( fields, 41 );     // 40

      uint16_t toggle_status_id = getField< uint16_t >( fields, 43 );    // 42
      bool affects_position     = getField< bool >( fields, 48 );        // 47

      bool no_effect_in_battle  = getField< bool >( fields, 61 );        // 60


      info->id                  = id;
      info->name                = name;
      info->category            = category;

      info->class_job           = class_job;
      info->unlock_level        = unlock_level;
      info->range               = range;
      info->can_target_self     = can_target_self;
      info->can_target_party    = can_target_party;
      info->can_target_friendly = can_target_friendly;
      info->can_target_enemy    = can_target_enemy;

      info->can_target_ko       = can_target_ko;

      info->is_ground_aoe       = is_ground_aoe;


      info->aoe_type            = aoe_type;
      info->aoe_range           = aoe_range;
      info->aoe_width           = aoe_width;

      info->points_type         = points_type;
      info->points_cost         = points_cost;

      info->is_instant          = is_instant;
      info->cast_time           = cast_time * 100;
      info->recast_time         = recast_time * 100;

      info->model               = model;
      info->aspect              = aspect;

      info->toggle_status_id    = toggle_status_id;
      info->affects_position    = affects_position;

      info->no_effect_in_battle = no_effect_in_battle;

      // If action type is SingleTarget with an AoE radius set, or if action type isn't SingleTarget
      info->is_aoe              = ( info->aoe_type == 1 && info->aoe_width != 0 ) || ( info->aoe_type != 1 );

      m_actionInfoMap.emplace( std::make_pair( info->id, info ) );

   }

   return true;
}

boost::shared_ptr< Core::Data::PlaceNameInfo >
   Core::Data::ExdData::getPlaceNameInfo( uint32_t placeNameId )
{
   try
   {
      auto row = m_placeNameDat.get_row( placeNameId );
      auto info = boost::make_shared< PlaceNameInfo >();
      info->id = placeNameId;
      info->placename = getField< std::string >( row, 0 );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;

}

boost::shared_ptr< Core::Data::ItemInfo >
   Core::Data::ExdData::getItemInfo( uint32_t catalogId )
{
   try
   {
      auto row = m_itemsDat.get_row( catalogId );
      auto info = boost::make_shared< ItemInfo >();
      info->id = catalogId;
      info->name = getField< std::string >( row, 0 );
      info->item_level = getField< uint16_t >( row, 11 );
      info->required_level = getField< uint8_t >( row, 12 );
      info->ui_category = getField< uint8_t >( row, 17 );
      info->stack_size = getField< uint32_t >( row, 19 );
      info->is_hqable = getField< bool >( row, 20 );
      info->model_primary = getField< uint64_t >( row, 45 );
      info->model_secondary = getField< uint64_t >( row, 46 );
      info->physical_damage = getField< uint16_t >( row, 49 );
      info->magical_damage = getField< uint16_t >( row, 50 );
      info->delayMs = getField< uint16_t >( row, 51 );
      info->is_unique = getField< int16_t >( row, 64 ) != 0 ? true : false;
      info->is_untradeable = getField< uint8_t >( row, 65 ) != 0 ? true : false;

      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;
}

boost::shared_ptr< Core::Data::AetheryteInfo >
   Core::Data::ExdData::getAetheryteInfo( uint32_t aetheryteId )
{
   try
   {
      return m_aetheryteInfoMap[aetheryteId];
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;

}

boost::shared_ptr< Core::Data::ActionInfo >
Core::Data::ExdData::getActionInfo( uint32_t actionId )
{
   try
   {
      return m_actionInfoMap[actionId];
   }
   catch ( ... )
   {
      return nullptr;
   }

   return nullptr;

}

boost::shared_ptr< Core::Data::CustomTalkInfo >
   Core::Data::ExdData::getCustomTalkInfo( uint32_t customTalkId )
{

   try
   {
      auto row = m_customTalkDat.get_row( customTalkId );
      auto info = boost::make_shared< CustomTalkInfo >();
      info->id = customTalkId;
      info->name_intern = getField< std::string >( row, 2 );

      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;

}

boost::shared_ptr< Core::Data::QuestInfo >
   Core::Data::ExdData::getQuestInfo( uint32_t questId )
{


   try
   {
      auto row = m_questDat.get_row( questId );
      auto info = boost::make_shared< QuestInfo >();
      info->id = questId;
      info->name = getField< std::string >( row, 0 );
      info->name_intern = getField< std::string >( row, 1 );

      info->quest_level = getField< uint16_t >( row, 4 );

      info->enpc_resident_start = getField< uint32_t >( row, 40 );
      info->enpc_resident_end = getField< uint32_t >( row, 42 );

      info->reward_exp_factor = getField< uint16_t >( row, 1439 );
      info->reward_gil = getField< uint32_t >( row, 1440 );
      info->reward_gc_seals = getField< uint16_t >( row, 1442 );

      info->reward_item_type = getField< uint8_t >( row, 1449 );

      for( uint32_t i = 0; i < 6; i++ )
      {
         uint32_t entry = getField< uint32_t >( row, i + 1450 );
         if( entry > 0 )
            info->reward_item.push_back( entry );

         uint8_t entry1 = getField< uint8_t >( row, i + 1457 );
         if( entry1 > 0 )
            info->reward_item_count.push_back( entry1 );

         uint8_t entry2 = getField< uint8_t >( row, i + 1464 );
         if( entry2 > 0 )
            info->reward_item_stain.push_back( entry2 );

      }

      for( uint32_t i = 0; i < 5; i++ )
      {
         uint32_t entry = getField< uint32_t >( row, i + 1471 );
         if( entry > 0 )
            info->reward_item_optional.push_back( entry );

         uint8_t entry1 = getField< uint8_t >( row, i + 1476 );
         if( entry1 > 0 )
            info->reward_item_optional_count.push_back( entry1 );

         uint8_t entry2 = getField< uint8_t >( row, i + 1486 );
         if( entry2 > 0 )
            info->reward_item_optional_stain.push_back( entry2 );
      }

      info->reward_emote = getField< uint8_t >( row, 1491 );
      info->reward_action = getField< uint16_t >( row, 1492 );
      info->reward_action_general1 = getField< uint8_t >( row, 1493 );
      info->reward_action_general2 = getField< uint8_t >( row, 1494 );
      info->reward_other = getField< uint8_t >( row, 1496 );

      info->instanced_content_unlock = getField< uint32_t >( row, 1499 );

      info->reward_tome_type = getField< uint8_t >( row, 1501 );
      info->reward_tome_count = getField< uint8_t >( row, 1502 );

      info->reward_reputation = getField< uint8_t >( row, 1503 );

      for( uint32_t i = 0; i < 50; i++ )
      {
         std::string entry = getField< std::string >( row, i + 49 );
         if( entry.size() > 0 )
         {
            info->script_entity.push_back( entry );
            uint32_t entry1 = getField< uint32_t >( row, i + 99 );
            info->script_value.push_back( entry1 );
         }
      }

      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;

}

boost::shared_ptr< Core::Data::EventItemInfo >
   Core::Data::ExdData::getEventItemInfo( uint32_t eventItemId )
{

   try
   {
      auto row = m_eventItemDat.get_row( eventItemId );
      auto info = boost::make_shared< EventItemInfo >();
      info->id = eventItemId;
      info->name = getField< std::string >( row, 0 );
      info->eventId = getField< uint32_t >( row, 14 );
      info->castTime = getField< uint8_t >( row, 15 ) * 1000;
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;

}

boost::shared_ptr< Core::Data::LevelInfo >
   Core::Data::ExdData::getLevelInfo( uint32_t levelId )
{
   try
   {
      auto row = m_levelDat.get_row( levelId );
      auto info = boost::make_shared< LevelInfo >();
      info->id = levelId;
      info->x = getField< float >( row, 0 );
      info->y = getField< float >( row, 1 );
      info->z = getField< float >( row, 2 );
      info->r = getField< float >( row, 3 );
      info->actor_id = getField< uint32_t >( row, 6 );
      info->zone_id = getField< uint16_t >( row, 9 );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;
}

const std::vector<boost::shared_ptr< Core::Data::AetheryteInfo > > Core::Data::ExdData::getAetheryteInfoForZone( uint16_t zoneId )
{
   std::vector< boost::shared_ptr< AetheryteInfo > > aetheryteList;

   for( auto& aetheryteInfo : m_aetheryteInfoMap )
   {
      if( aetheryteInfo.second->target_zone == zoneId )
      {
         aetheryteList.push_back( aetheryteInfo.second );
      }
   }
   return aetheryteList;
}


boost::shared_ptr< Core::Data::OpeningInfo >
   Core::Data::ExdData::getOpeningInfo( uint32_t openingId )
{
   try
   {
      auto row = m_openingDat.get_row( openingId );
      auto info = boost::make_shared< OpeningInfo >();
      info->id = openingId;
      info->name = getField< std::string >( row, 0 );

      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;
}

boost::shared_ptr< Core::Data::RaceInfo >
   Core::Data::ExdData::getRaceInfo( uint32_t raceId )
{
   try
   {

      auto row = m_raceDat.get_row( raceId );
      auto info = boost::make_shared< RaceInfo >();
      info->id = raceId;
      info->name = getField< std::string >( row, 0 );
      info->male_body = getField< int32_t >( row, 2 );
      info->male_hands = getField< int32_t >( row, 3 );
      info->male_legs = getField< int32_t >( row, 4 );
      info->male_feet = getField< int32_t >( row, 5 );
      info->female_body = getField< int32_t >( row, 6 );
      info->female_hands = getField< int32_t >( row, 7 );
      info->female_legs = getField< int32_t >( row, 8 );
      info->female_feet = getField< int32_t >( row, 9 );

      return info;
   }
   catch( ... )
   {
      return nullptr;
   }

   return nullptr;
}
