#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SaintMociannesArboretum : public InstanceContentScript
{
public:
   SaintMociannesArboretum() : InstanceContentScript( 41 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 6038834, 4, { -14.984150f, -350.000000f, -10.860330f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 10.788090f, -350.026703f, 7.522644f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { -16.401690f, -350.000000f, -11.633360f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2006520, 6041801, 4, { 113.481300f, 2.975464f, 19.363649f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2006521, 6047538, 4, { 67.640343f, 0.000000f, -71.112350f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2006586, 0, 4, { 85.017906f, -0.020000f, -58.585030f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2006522, 5966533, 4, { -125.780197f, -12.375120f, -188.891495f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2006523, 6037786, 4, { -234.627304f, -29.692921f, -182.589401f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2006594, 6068325, 4, { -244.373505f, -37.105370f, -163.858002f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2006524, 6046538, 4, { -102.066101f, -349.342285f, 55.198681f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2006526, 6046053, 4, { -86.535728f, -356.521301f, -4.785355f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2006527, 6046055, 4, { -104.847900f, -356.059692f, 4.146202f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2006525, 6046572, 4, { -47.545761f, -359.815613f, -33.600189f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2006596, 6058396, 4, { -262.334015f, -39.551819f, -111.790802f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2006597, 6077036, 4, { -248.226898f, -46.000000f, -133.086304f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2006598, 6077035, 4, { -283.791992f, -46.000000f, -122.796700f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006609, 6084794, 4, { -242.938904f, -44.861469f, -84.336670f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2002872, 6037810, 4, { 15.731990f, 3.000000f, -89.860413f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2002735, 0, 4, { 18.234501f, 3.097534f, -90.928528f }, 0.991760f );
      instance->registerEObj( "Unknown18", 2006531, 6037814, 4, { -17.876730f, 3.000000f, -82.649872f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2002872, 6041100, 4, { -245.545395f, -36.853828f, -164.052200f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2002735, 0, 4, { -245.869705f, -36.958050f, -162.887695f }, 0.991760f );
      instance->registerEObj( "Unknown21", 2006532, 6082449, 4, { -260.975098f, -44.815800f, -108.476402f }, 0.991760f );
      instance->registerEObj( "Unknown22", 2006566, 0, 4, { -263.891296f, -44.889751f, -114.578796f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6034530, 5, { 0.231333f, 0.000002f, 140.623901f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 4.219861f, 0.000001f, 131.545197f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};