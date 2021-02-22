#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdDataGenerated.h>
#include <Service.h>


using namespace Sapphire;

class Aetheryte :
  public Sapphire::ScriptAPI::EventScript
{
private:
  constexpr static auto ACTION_ATTUNE = 0x13;
  constexpr static auto ACTION_TELEPORT = 0x4;

  constexpr static auto AETHERYTE_MENU_AETHERNET = 1;
  constexpr static auto AETHERYTE_MENU_HOUSING = 2;
  constexpr static auto AETHERYTE_MENU_HOME_POINT = 3;
  constexpr static auto AETHERYTE_MENU_FAVORITE_POINT = 4;
  constexpr static auto AETHERYTE_MENU_FAVORITE_POINT_SECURITY_TOKEN = 5;

public:
  Aetheryte() :
    Sapphire::ScriptAPI::EventScript( 0x00050000 )
  {
  }

  void aethernet( uint32_t eventId, Entity::Player& player, uint64_t actorId )
  {
    if( player.isAetheryteRegistered( eventId & 0xFFFF ) )
    {
      player.playScene( eventId, 2, 0, [this]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param1 == 256 && result.param2 != 0 )
        {
          player.teleport( result.param2, 2 );
        }
      } );
    }
    else
    {
      player.eventActionStart( eventId, ACTION_ATTUNE,
                               []( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 player.registerAetheryte( eventId & 0xFFFF );
                                 player.playScene( eventId, 3, 0, 0, 0 );
                               },
                               []( Entity::Player& ply, uint32_t evntId, uint64_t additional )
                               {

                               }, 0 );

    }
  }

  void aetheryte( uint32_t eventId, Entity::Player& player, uint64_t actorId )
  {
    if( player.isAetheryteRegistered( eventId & 0xFFFF ) )
    {
      // eventParam4 (or params[1] if using EventPlay8, which is actually used on retail) anything bigger than 1 will show select instance menu item
      player.playScene( eventId, 0, 1, 0, 1, 2, [this]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param1 == 256 ) // set homepoint
        {
          player.setHomepoint( result.eventId & 0xFFFF );
          player.sendQuestMessage( result.eventId, 2, 0xEA, 0, 0 );
        }
        else if( result.param1 == 512 ) // aethernet access
        {
          if( result.param2 == 4 && result.param3 != 0 )
          {
            player.teleport( result.param3, 2 );
          }
          else if( result.param2 == 2 ) // register favored destination
          {

          }
//               else if( param2 == 0xC3E1 ) // register free destination
//               {
//
//               }

        }
      } );
    }
    else
    {
      player.eventActionStart( eventId, ACTION_ATTUNE,
                               [this]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 player.registerAetheryte( eventId & 0xFFFF );

                                 if( player.isActionLearned( ACTION_TELEPORT ) )
                                 {
                                   player.sendQuestMessage( eventId, 0, 2, 0, 0 );
                                 }
                                 else
                                 {
                                   player.sendQuestMessage( eventId, 0, 1, 1, 0 );
                                   player.learnAction( ACTION_TELEPORT );
                                 }
                               },
                               []( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {}, 0 );
    }
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& exdData = Common::Service< Sapphire::Data::ExdDataGenerated >::ref();

    auto aetherInfo = exdData.get< Sapphire::Data::Aetheryte >( eventId & 0xFFFF );
    if( !aetherInfo )
      return;

    if( aetherInfo->isAetheryte )
      aetheryte( eventId, player, actorId );
    else
      aethernet( eventId, player, actorId );
  }
};

EXPOSE_SCRIPT( Aetheryte );