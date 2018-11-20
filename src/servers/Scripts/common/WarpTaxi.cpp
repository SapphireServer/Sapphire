#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdDataGenerated.h>
#include <Framework.h>

using namespace Core;

class WarpTaxi : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi() :
    Sapphire::ScriptAPI::EventScript( 0x0002005a )
  {
  }

  void inner( Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.param1 != 256 )
    {
      std::function< void( Entity::Player&, const Event::SceneResult& ) > fn = std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 );

      player.playScene( 1310721, 0, HIDE_HOTBAR, 0, 1, 341, fn );
    }
  }

  void inner2( Entity::Player& player, uint64_t actorId )
  {
    player.eventStart( actorId, 1310721, Event::EventHandler::Nest, 0, 0  );
    std::function< void( Entity::Player&, const Event::SceneResult& ) > fn = std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 );
    player.playScene( 1310721, 0, HIDE_HOTBAR, 0, 1, 341, fn );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto exddata = getFramework()->get< Core::Data::ExdDataGenerated >();
    if( !exddata )
      return;

    auto warp = exddata->get< Core::Data::Warp >( eventId );
    if( !warp )
      return;

    player.eventStart( actorId, warp->defaultTalk1, Event::EventHandler::Nest, 0, 0, std::bind( &WarpTaxi::inner2, this, std::placeholders::_1, std::placeholders::_2 ) );
    player.playScene( warp->defaultTalk1, 0, HIDE_HOTBAR, [warp, this]( Entity::Player& player, const Event::SceneResult& result )
    {

    } );
  }
};