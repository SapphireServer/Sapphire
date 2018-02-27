#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheLostCityofAmdapor : public InstanceContentScript
{
public:
   TheLostCityofAmdapor() : InstanceContentScript( 22 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 4579298, 4, { 9.791200f, -279.967285f, 21.616301f }, 0.700000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { 8.967742f, -279.844086f, 22.640949f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -6.668615f, -279.989990f, -16.121090f }, 1.000000f );
      instance->registerEObj( "Diabolicalgate", 2003262, 0, 4, { -11.735310f, -279.600006f, 1.146639f }, 1.000000f );
      instance->registerEObj( "Diabolicalgate", 2003263, 0, 4, { -5.801897f, -279.600006f, -2.180922f }, 1.000000f );
      instance->registerEObj( "Diabolicalgate", 2003264, 0, 4, { -9.593593f, -279.600006f, 5.704061f }, 1.000000f );
      instance->registerEObj( "Diabolicalgate", 2003265, 0, 4, { -3.149769f, -279.600006f, 2.478353f }, 1.000000f );
      instance->registerEObj( "Dubiouscoffer", 2003266, 0, 4, { 8.612234f, -279.989990f, -20.760429f }, 1.000000f );
      instance->registerEObj( "Dubiouscoffer", 2003267, 0, 4, { 20.769291f, -279.989990f, -8.610124f }, 1.000000f );
      instance->registerEObj( "Dubiouscoffer", 2003268, 0, 4, { -20.776131f, -279.989990f, 8.642863f }, 0.991760f );
      instance->registerEObj( "Dubiouscoffer", 2003269, 0, 4, { -20.738871f, -279.989990f, -8.552890f }, 1.000000f );
      instance->registerEObj( "Dubiouscoffer", 2003270, 0, 4, { 20.683531f, -279.989990f, 8.612939f }, 1.000000f );
      instance->registerEObj( "Dubiouscoffer", 2003271, 0, 4, { -8.611513f, -279.989990f, 20.715059f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2003361, 4538596, 4, { 146.386597f, 68.131821f, -32.655411f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2003431, 4577623, 4, { 141.929794f, 66.690971f, -22.680590f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2003362, 4577620, 4, { 124.650101f, 58.000000f, 21.475590f }, 1.000000f );
      instance->registerEObj( "Treasurecoffer", 2003800, 0, 4, { 125.169800f, 58.259232f, 24.765381f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2003364, 4538597, 4, { 1.248910f, 34.305920f, -96.145103f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2003432, 4577625, 4, { 7.652231f, 33.999989f, -83.909409f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2003365, 4572307, 4, { 16.420071f, 30.172510f, -53.162449f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2003366, 4629067, 4, { 13.762910f, 27.170670f, -29.499069f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2003367, 4577622, 4, { -35.077301f, 20.181410f, -5.543382f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2003368, 4572310, 4, { -36.282841f, 10.771230f, 27.777269f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2003369, 4629073, 4, { -38.452469f, 10.771230f, 26.955620f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2003370, 4538791, 4, { 11.000470f, 7.980469f, 18.231581f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2003371, 4572309, 4, { 15.090590f, 6.133745f, 32.735611f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2003372, 4629074, 4, { 11.812460f, 6.045094f, 32.012810f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2003433, 4577626, 4, { 25.308140f, 6.141701f, 43.055359f }, 1.000000f );
      instance->registerEObj( "Treasurecoffer", 2003801, 0, 4, { -39.169922f, 18.680960f, -1.968445f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2003374, 4583478, 4, { 23.827320f, -252.500000f, -65.956993f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2003375, 4583476, 4, { 9.536644f, -252.394394f, -55.117130f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2003376, 4583473, 4, { 47.898071f, -270.801910f, 54.428829f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2003377, 4583472, 4, { 35.751831f, -270.679901f, 43.045650f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2003378, 4583471, 4, { 42.832031f, -270.801910f, 35.995972f }, 0.991760f );
      instance->registerEObj( "Unknown21", 2003379, 4583474, 4, { 54.564331f, -270.899994f, 47.591949f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2002872, 4577505, 4, { 100.376602f, 43.960560f, 2.708986f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2002735, 0, 4, { 97.980797f, 42.137150f, -0.222000f }, 0.900000f );
      instance->registerEObj( "Unknown24", 2003363, 4578411, 4, { 86.630951f, 42.801220f, -47.240730f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2003373, 4578103, 4, { -38.428570f, 12.100000f, 70.544273f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2002872, 4578066, 4, { 6.156913f, 11.249960f, 70.316727f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2002735, 0, 4, { 4.235116f, 12.085570f, 69.965263f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2003360, 0, 4, { 284.752808f, 100.000000f, -31.765209f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4574610, 5, { 270.581207f, 100.000000f, -17.202379f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 265.173615f, 100.000000f, -32.604542f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};