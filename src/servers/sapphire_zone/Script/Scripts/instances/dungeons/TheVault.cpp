#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheVault : public InstanceContentScript
{
public:
   TheVault() : InstanceContentScript( 34 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 5588600, 4, { 0.359463f, 300.000000f, 26.171600f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { 0.428600f, 300.000000f, 24.562250f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005580, 5873754, 4, { 0.360928f, 300.000000f, -15.306860f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2006743, 5474300, 4, { 39.139400f, -300.007690f, 29.587160f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2006744, 5474303, 4, { 43.961182f, -299.855103f, -30.197689f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2006745, 6143050, 4, { -34.927921f, -300.007690f, -80.460876f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2006746, 6147782, 4, { -38.559631f, -300.007690f, -72.068359f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2006747, 6147781, 4, { -38.986820f, -300.007690f, -30.014530f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2006748, 6143048, 4, { 52.795311f, -299.984589f, -36.063671f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2006749, 6147791, 4, { 0.604760f, -291.999908f, -117.413803f }, 1.000000f );
      instance->registerEObj( "Bonds", 2006752, 0, 4, { -52.262211f, -300.000793f, -27.878300f }, 0.991760f );
      instance->registerEObj( "Bonds", 2006752, 0, 4, { 56.960300f, -299.984589f, -73.657806f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2002872, 5581166, 4, { -18.416611f, -292.000000f, -99.614120f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2002735, 0, 4, { -20.099001f, -292.000000f, -98.859291f }, 0.700000f );
      instance->registerEObj( "Unknown12", 2005106, 5581173, 4, { -0.494135f, -292.000000f, -117.713799f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2002735, 0, 4, { 18.757099f, 0.000000f, 72.079903f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2002872, 5583050, 4, { 17.161560f, 0.000000f, 73.880867f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2005087, 5474300, 4, { 37.735470f, -300.007690f, 30.228149f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2005088, 5499954, 4, { 51.884090f, -300.000000f, -35.577080f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2005089, 5474303, 4, { 44.255379f, -300.000000f, -31.015051f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2005090, 5474308, 4, { -36.242680f, -300.000000f, -29.871010f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2005091, 5474306, 4, { -37.591751f, -300.000000f, -69.819733f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2005092, 5499959, 4, { -33.701191f, -300.000000f, -79.843872f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2005093, 5499966, 4, { 6.953651f, -281.975708f, -150.744995f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2005094, 5476161, 4, { 101.518402f, -263.140503f, -12.115350f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2005095, 5476162, 4, { 101.390800f, -263.204315f, 11.842000f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2005096, 5474532, 4, { 99.222763f, -264.000000f, -0.362554f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2005097, 5499987, 4, { 22.634041f, 0.000000f, 71.960167f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2005098, 5499980, 4, { -17.585621f, 0.000000f, 72.136276f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2005099, 5444302, 4, { -92.607063f, -0.015320f, 0.076233f }, 0.991760f );
      instance->registerEObj( "Unknown28", 2005100, 5499663, 4, { -52.663239f, 291.000000f, 42.623951f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2005101, 5499660, 4, { -67.359016f, 291.000000f, 42.656231f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2005102, 5499645, 4, { -66.869476f, 291.000000f, 55.587841f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2005103, 5499653, 4, { -53.398609f, 291.000000f, 55.570320f }, 1.000000f );
      instance->registerEObj( "Unknown32", 2005104, 5499600, 4, { -46.140011f, 291.000000f, 48.667049f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5578486, 5, { -5.010592f, -300.000000f, 86.198753f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 11.135890f, -300.000000f, 78.862717f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.136796f, 299.977112f, -9.654591f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};