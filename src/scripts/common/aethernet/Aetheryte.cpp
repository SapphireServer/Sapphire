#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdData.h>
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
      eventMgr().playScene( player, eventId, 2, 0, [ this ]( Entity::Player& player, const Event::SceneResult& result )
      {
        auto destination = result.getResult( 0 );
        if( result.numOfResults == 1 && destination != 0 )
        {
          warpMgr().requestPlayerTeleport( player, destination, 2 );
        }
      } );
    }
    else
    {
      eventMgr().eventActionStart( player, eventId, ACTION_ATTUNE,
                                   [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                   {
                                     player.registerAetheryte( eventId & 0xFFFF );
                                     eventMgr().playScene( player, eventId, 3, NO_DEFAULT_CAMERA );
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
      eventMgr().playScene( player, eventId, 0, 1, { 1, 2 }, [ this ]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.numOfResults == 1 )
        {
          auto cmd = result.getResult( 0 );
          if( cmd == 1 ) // set homepoint
          {
            player.setHomepoint( result.eventId & 0xFFFF );
            eventMgr().sendEventNotice( player, result.eventId, 2, 0xEA, 0, 0 );
          }
          else if( cmd == 5 )
          {
            //TODO: Housing teleport selection
          }
        }
        else if( result.numOfResults == 2 ) // aethernet access
        {
          auto cmd = result.getResult( 0 );
          auto data = result.getResult( 1 );
          if( cmd == 4 && data != 0 )
          {
            warpMgr().requestPlayerTeleport( player, data, 2 );
          }
          else if( cmd == 2 ) // register favored destination
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
      eventMgr().eventActionStart( player, eventId, ACTION_ATTUNE,
                                   [ this ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                   {
                                     player.registerAetheryte( eventId & 0xFFFF );

                                     if( player.hasReward( Common::UnlockEntry::Teleport ) )
                                     {
                                       eventMgr().sendEventNotice( player, eventId, 0, 2, 0, 0 );
                                     }
                                     else
                                     {
                                       eventMgr().sendEventNotice( player, eventId, 0, 1, 1, 0 );
                                       player.setRewardFlag( Common::UnlockEntry::Teleport );
                                     }
                                   },
                                   []( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                   {}, 0 );
    }
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();

    auto aetherInfo = exdData.getRow< Excel::Aetheryte >( eventId & 0xFFFF );
    if( !aetherInfo )
      return;

    if( aetherInfo->data().Telepo )
      aetheryte( eventId, player, actorId );
    else
      aethernet( eventId, player, actorId );
  }
};

EXPOSE_SCRIPT( Aetheryte );