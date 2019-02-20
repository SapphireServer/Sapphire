#include <Actor/Player.h>
#include <ScriptObject.h>

using namespace Sapphire;

// Opening Script: OpeningLimsaLominsa
// Quest Name: OpeningLimsaLominsa
// Quest ID: 1245185

class OpeningLimsa :
  public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto ERANGE_HOWTO_ANN_AND_QUEST = 4101831;
  static constexpr auto ERANGE_HOWTO_QUEST_REWARD = 4102066;
  static constexpr auto ERANGE_SEQ_1_CLOSED_1 = 4101785;
  static constexpr auto POS_SEQ_1_CLOSED_RETURN_1 = 4101797;
  static constexpr auto ERANGE_ALWAYS_CLOSED_1 = 4101744;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_1 = 4101761;
  static constexpr auto ENPC_ALWAYS_CLOSED_1 = 4102038;
  static constexpr auto ERANGE_ALWAYS_CLOSED_2 = 4101746;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_2 = 4101763;
  static constexpr auto ENPC_ALWAYS_CLOSED_2 = 4102036;
  static constexpr auto ERANGE_ALWAYS_CLOSED_3 = 4101967;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_3 = 4101982;
  static constexpr auto ENPC_ALWAYS_CLOSED_3 = 4102033;
  static constexpr auto ERANGE_ALWAYS_CLOSED_4 = 4101970;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_4 = 4101984;
  static constexpr auto ENPC_ALWAYS_CLOSED_4 = 4102031;
  static constexpr auto ERANGE_ALWAYS_CLOSED_5 = 4101973;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_5 = 4101985;
  static constexpr auto ENPC_ALWAYS_CLOSED_5 = 4102007;
  static constexpr auto ERANGE_ALWAYS_CLOSED_6 = 4101979;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_6 = 4101988;
  static constexpr auto ENPC_ALWAYS_CLOSED_6 = 2367400;
  static constexpr auto BGM_MUSIC_ZONE_SEA_TWN = 1020;
  static constexpr auto NCUT_SEA_1 = 200;
  static constexpr auto NCUT_SEA_2 = 132;
  static constexpr auto NCUT_SEA_3 = 201;
  static constexpr auto ENPC_QUEST_OFFER = 4102039;
  static constexpr auto NCUT_LIGHT_ALL = 2;
  static constexpr auto NCUT_LIGHT_SEA_1 = 147;
  static constexpr auto NCUT_LIGHT_SEA_2 = 138;


  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto questionAnswer = result.param2;

      uint16_t itemId = 0;

      switch( questionAnswer )
      {
        case 1:
          itemId = 4423;
          break;
        case 2:
          itemId = 4424;
          break;
        case 3:
          itemId = 4425;
          break;
        case 4:
          itemId = 4426;
          break;
        default:
          itemId = 4426;
          break;
      }

      auto item = player.addItem( itemId, 1, false, true );

      if( item )
        player.equipItem( Common::GearSetSlot::Ring2, item, true );

      player.setOpeningSequence( 1 );
      Scene00001( player );
    };

    player.playScene( getId(), 0, NO_DEFAULT_CAMERA | INVIS_ENPC |
                                  CONDITION_CUTSCENE | HIDE_UI |
                                  HIDE_HOTBAR | SILENT_ENTER_TERRI_ENV | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                  DISABLE_SKIP | DISABLE_STEALTH, 0, 1, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, NO_DEFAULT_CAMERA | HIDE_HOTBAR, 1, 0x32 );
  }

  void Scene00020( Entity::Player& player )
  {
    player.playScene( getId(), 20, NO_DEFAULT_CAMERA | HIDE_HOTBAR, 0, 1 );
  }

  void Scene00030( Entity::Player& player )
  {
    player.playScene( getId(), 30, NO_DEFAULT_CAMERA | HIDE_HOTBAR, 0, 0 );
  }

  void Scene00040( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( player.getOpeningSequence() == 2 )
      {
        // update instance boundaries
        Scene00030( player );
      }
    };

    player.playScene( getId(), 40, NO_DEFAULT_CAMERA, 2, 1, callback );
  }


public:
  OpeningLimsa() :
    Sapphire::ScriptAPI::EventScript( 1245185 )
  {
  }

  void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
    if( player.getOpeningSequence() == 0 )
      Scene00000( player );
    else
      Scene00040( player );
  }

  void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    // todo: handle closed events
  }
};

EXPOSE_SCRIPT( OpeningLimsa );