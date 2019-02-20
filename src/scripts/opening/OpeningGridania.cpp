#include <Actor/Player.h>
#include <ScriptObject.h>

using namespace Sapphire;

class OpeningGridania : public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto ERANGE_HOWTO_ANN_AND_QUEST = 2117539;
  static constexpr auto ERANGE_HOWTO_QUEST_REWARD = 2366417;
  static constexpr auto ERANGE_SEQ_1_CLOSED_1 = 2351918;
  static constexpr auto POS_SEQ_1_CLOSED_RETURN_1 = 2351921;
  static constexpr auto ERANGE_SEQ_1_CLOSED_2 = 2351919;
  static constexpr auto POS_SEQ_1_CLOSED_RETURN_2 = 2351921;
  static constexpr auto ERANGE_ALWAYS_CLOSED_1 = 2280846;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_1 = 2320804;
  static constexpr auto ENPC_ALWAYS_CLOSED_1 = 2367988;
  static constexpr auto ERANGE_ALWAYS_CLOSED_3 = 2280851;
  static constexpr auto POS_ALWAYS_CLOSED_RETURN_3 = 2320811;
  static constexpr auto ENPC_ALWAYS_CLOSED_3 = 2563491;
  static constexpr auto BGM_MUSIC_ZONE_FST_TWN = 1003;
  static constexpr auto NCUT_FST_1 = 3;
  static constexpr auto NCUT_FST_2 = 53;
  static constexpr auto NCUT_FST_3 = 226;
  static constexpr auto ENPC_QUEST_OFFER = 1985150;
  static constexpr auto NCUT_LIGHT_ALL = 2;
  static constexpr auto NCUT_LIGHT_FST_1 = 147;
  static constexpr auto NCUT_LIGHT_FST_2 = 146;

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

      //if( item )
      //  player.equipItem( Common::GearSetSlot::Ring2, item, true );

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
    player.playScene( getId(), 1, NO_DEFAULT_CAMERA | HIDE_HOTBAR, 0, 0 );
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
        // update the instance boundaries
        Scene00030( player );
      }
    };

    player.playScene( getId(), 40, 1, 2, 1, callback );
  }

public:
  OpeningGridania() :
    Sapphire::ScriptAPI::EventScript( 1245186 )
  {
  }

  void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
    if( player.getOpeningSequence() == 0 )
    {
      Scene00000( player );
    }
    else
    {
      Scene00040( player );
    }
  }

  void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    if( param1 == ERANGE_SEQ_1_CLOSED_1 || param1 == ERANGE_SEQ_1_CLOSED_2 )
    {
      Scene00020( player );
    }
  }
};

EXPOSE_SCRIPT( OpeningGridania );