#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class TheSpiritIsWilling : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4081071;
  static constexpr auto INIT_POP_01A_01 = 4081077;
  static constexpr auto INIT_POP_01A_02 = 4081078;
  static constexpr auto INIT_POP_01A_03 = 4081080;
  static constexpr auto INIT_POP_01A_04 = 4081081;
  static constexpr auto INIT_POP_01A_05 = 4081081;
  static constexpr auto INIT_POP_02A_01 = 4081099;
  static constexpr auto INIT_POP_02A_02 = 4081100;
  static constexpr auto INIT_POP_02C_02 = 4081102;
  static constexpr auto INIT_POP_02C_01 = 4081103;
  static constexpr auto INIT_POP_02B_02 = 4081104;
  static constexpr auto INIT_POP_02B_01 = 4081105;
  static constexpr auto INIT_POP_03C_01 = 4081113;
  static constexpr auto INIT_POP_03C_02 = 4081114;
  static constexpr auto INIT_POP_03C_03 = 4081115;
  static constexpr auto INIT_POP_03C_04 = 4081116;
  static constexpr auto INIT_POP_03D_01 = 4081117;
  static constexpr auto BNPC_C_TYPE = 690;
  static constexpr auto LOC_POS_ACTOR1 = 4087447;
  static constexpr auto LOC_POS_ACTOR2 = 4087454;
  static constexpr auto LOC_POS_ACTOR3 = 4087458;
  static constexpr auto LOC_POS_ACTOR4 = 4087478;
  static constexpr auto LOC_ACTOR0 = 1003827;
  static constexpr auto LOC_ACTOR1 = 1003817;
  static constexpr auto LOC_ACTOR2 = 1006011;
  static constexpr auto LOC_BNPC1 = 1005971;
  static constexpr auto LOC_BNPC2 = 1005972;
  static constexpr auto LOC_BNPC3 = 1005973;
  static constexpr auto LOC_BNPC4 = 1002997;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto NCUT_15010 = 164;
  static constexpr auto INIT_ENPC_POP_01 = 4107478;
  static constexpr auto INIT_ENPC_POP_02 = 4107479;

  static constexpr uint32_t flags = NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                                                HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                                DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                                // todo: wtf is 0x00100000
                                                DISABLE_CANCEL_EMOTE;

public:
  TheSpiritIsWilling() : Sapphire::ScriptAPI::QuestBattleScript( 30 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2000608, 3909641, 4324057, 4, { 25.295130f, -5.799999f, -3.123501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2000608, 3909640, 4324063, 4, { 27.000000f, -5.799999f, -28.538910f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Mormosurn", 2001471, 0, 4033684, 4, { 100.938400f, -24.093990f, 257.007599f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2001593, 0, 4092809, 4, { 55.677589f, -19.217951f, 326.845490f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2001594, 0, 4092810, 4, { 52.504971f, -19.345751f, 333.577209f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2001595, 0, 4092811, 4, { 51.615070f, -19.372410f, 329.040192f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2001593, 0, 4092812, 4, { 56.083569f, -19.316870f, 333.995697f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2001593, 0, 4092813, 4, { 110.684799f, -26.871759f, 302.023712f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2001594, 0, 4092814, 4, { 110.805199f, -26.792940f, 298.242188f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2001595, 0, 4092815, 4, { 115.046097f, -27.339991f, 302.750000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2001594, 0, 4092816, 4, { 113.256401f, -27.037060f, 298.989410f }, 1.000000f, 0.782489f, 0); 
    instance.addEObj( "unknown_10", 2001596, 0, 4092818, 4, { 102.250702f, -24.216129f, 254.413696f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2001596, 0, 4092820, 4, { 104.661598f, -24.307680f, 254.901993f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2001596, 0, 4092817, 4, { 103.990196f, -24.338131f, 256.549896f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_13", 2001596, 0, 4092819, 4, { 99.015747f, -23.971979f, 256.214203f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_14", 2001762, 0, 4185128, 4, { 100.938400f, -24.094000f, 257.007599f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "unknown_15", 2001510, 0, 4036621, 4, { 183.194199f, 3.453069f, -340.226501f }, 1.000000f, 0.767694f, 0); 
    instance.addEObj( "unknown_16", 2002332, 0, 5901009, 4, { 430.142609f, -64.423027f, 203.900696f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Captivepilgrims", 2005823, 0, 5892004, 4, { -72.824303f, -22.267281f, 264.870209f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2004281, 0, 4754286, 4, { -339.600891f, -12.095690f, -251.714706f }, 1.000000f, -0.358635f, 0); 
    instance.addEObj( "unknown_18", 2004264, 0, 4754298, 4, { -321.864899f, -10.790970f, -250.264206f }, 0.850000f, 0.839579f, 0); 
    instance.addEObj( "unknown_19", 2004265, 0, 4755201, 4, { -328.595398f, -11.400010f, -244.478302f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "LaughingAlchemistcauldron", 2004283, 0, 4755209, 4, { -323.506012f, -9.724042f, -248.446503f }, 1.000000f, 0.819717f, 0); 
    instance.addEObj( "Muddybottle", 2003004, 0, 4512258, 4, { -206.468506f, -37.627800f, 187.375595f }, 1.000000f, 1.195421f, 0); 
    instance.addEObj( "Holeypot", 2003005, 0, 4512259, 4, { -220.874405f, -37.857670f, 166.002808f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Muddypebble", 2003006, 0, 4512260, 4, { -208.545105f, -37.890240f, 151.873001f }, 1.200000f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2003009, 0, 4514613, 4, { -217.999603f, -37.868229f, 155.739807f }, 0.991760f, -0.867009f, 0); 
    instance.addEObj( "unknown_21", 2001430, 0, 3982560, 4, { -220.050400f, -38.210670f, 66.781914f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "unknown_22", 2001431, 0, 3982561, 4, { -226.920700f, -38.657612f, 63.937840f }, 1.000000f, 0.557633f, 0); 
    instance.addEObj( "unknown_23", 2001432, 0, 3982562, 4, { -223.187195f, -38.517841f, 64.349747f }, 1.000000f, 0.709120f, 0); 
    instance.addEObj( "unknown_24", 2001433, 0, 3985699, 4, { -222.780106f, -38.340981f, 67.320610f }, 1.000000f, -0.497652f, 0); 
    instance.addEObj( "unknown_25", 2001742, 0, 4165180, 4, { -520.494324f, -21.461479f, 123.343697f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2001743, 0, 4165381, 4, { -19.986641f, -30.999981f, -33.921829f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2005429, 0, 5852396, 4, { -527.009216f, -20.816959f, 103.394096f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Indentation", 2001389, 0, 3956085, 4, { -242.397400f, -26.127050f, 229.198593f }, 0.808681f, 0.000623f, 0); 
    instance.addEObj( "Indentation_1", 2001390, 0, 3995974, 4, { -228.835800f, -27.794350f, 250.158600f }, 0.808681f, 0.000623f, 0); 
    instance.addEObj( "Indentation_2", 2001391, 0, 3996067, 4, { -215.982300f, -29.480539f, 203.788300f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Armoredwartransport", 2001498, 0, 4074124, 4, { -366.277008f, -34.983299f, 293.579803f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Armoredwartransport_1", 2001511, 0, 4074125, 4, { -366.277008f, -34.983299f, 293.579803f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2001759, 0, 4175137, 4, { -365.898407f, -34.987450f, 295.465912f }, 0.700000f, 0.200967f, 0); 
    instance.addEObj( "Armoredwartransport_2", 2001499, 0, 4074134, 4, { -366.277008f, -34.983299f, 293.579803f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Armoredwartransport_3", 2001512, 0, 4074135, 4, { -366.277008f, -34.983299f, 293.579803f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_29", 2001760, 0, 4175138, 4, { -365.898407f, -34.987499f, 295.465912f }, 0.700000f, 0.200968f, 0); 
    instance.addEObj( "Destination", 2001470, 0, 4009272, 4, { -24.865419f, -25.333040f, 321.962189f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2001757, 0, 4175163, 4, { 184.919998f, 3.180800f, -338.641113f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2002699, 0, 4374426, 4, { -337.483490f, -22.360310f, 437.051514f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2001960, 0, 4269142, 4, { -0.259460f, -30.935020f, -43.686649f }, 0.991760f, 0.873936f, 0); 
    instance.addEObj( "Destination_2", 2001961, 0, 4269143, 4, { -20.309811f, -30.999981f, -32.852779f }, 0.991760f, 1.561893f, 0); 
    instance.addEObj( "Destination_3", 2001962, 0, 4269144, 4, { -7.766907f, -31.036160f, -8.133057f }, 0.991760f, 1.469248f, 0); 
    instance.addEObj( "Destination_4", 2001963, 0, 4269145, 4, { 0.228821f, -7.165798f, -41.397770f }, 0.991760f, 0.602500f, 0); 
    instance.addEObj( "Undecipherableletter", 2001964, 0, 4269168, 4, { 97.917107f, -10.235720f, 155.963104f }, 0.991760f, -1.214307f, 0); 
    instance.addEObj( "Destination_5", 2001965, 0, 4269998, 4, { 313.479401f, 23.192711f, -253.566193f }, 1.000000f, 1.364205f, 0); 
    instance.addEObj( "Destination_6", 2002101, 0, 4296759, 4, { -80.796570f, -58.185429f, 152.402298f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "MarkoftheWarden", 2002103, 0, 4296783, 4, { 149.028793f, -3.055883f, 408.463104f }, 0.991760f, 1.556079f, 0); 
    instance.addEObj( "unknown_31", 2002321, 0, 4296831, 4, { -463.671997f, -28.227530f, 324.194489f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2002104, 0, 4296982, 4, { -237.018799f, -35.812500f, 160.970398f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Corruptedcluster", 2002327, 0, 4299848, 4, { 423.189392f, -62.441299f, 213.425705f }, 1.000000f, -1.313014f, 0); 
    instance.addEObj( "Corruptedcrystal", 2002501, 0, 4335308, 4, { 423.189392f, -62.441299f, 213.425705f }, 1.000000f, -1.313013f, 0); 
    instance.addEObj( "unknown_32", 2005107, 0, 5580820, 4, { 192.943695f, -27.072790f, 203.604706f }, 1.000000f, 0.466001f, 0); 
    instance.addEObj( "Destination_8", 2005112, 0, 5581446, 4, { 199.717896f, -14.711510f, 162.489899f }, 0.991789f, 0.072877f, 0); 
    instance.addEObj( "Woodencrate", 2005113, 0, 5581649, 4, { 192.904404f, -26.651560f, 203.616196f }, 1.000000f, 0.433475f, 0); 
    instance.addEObj( "unknown_33", 2005114, 0, 5581764, 4, { 192.942902f, -27.072800f, 203.603394f }, 1.000000f, 0.471239f, 0); 
    instance.addEObj( "unknown_34", 2005430, 0, 5852858, 4, { -380.812408f, -23.064751f, 388.627106f }, 0.600000f, 0.000000f, 0); 
    instance.addEObj( "Destination_9", 2006314, 0, 5940617, 4, { 143.064102f, -6.127447f, 412.116089f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Planarfissure", 2002429, 0, 4308038, 4, { -72.650002f, -32.036369f, -46.820000f }, 1.000000f, -0.453177f, 0); 
    instance.addEObj( "Planarfissure_1", 2002533, 0, 4323975, 4, { -72.650002f, -32.036362f, -46.820000f }, 1.000000f, -0.453178f, 0); 
    instance.addEObj( "Planarfissure_2", 2002437, 0, 4308798, 4, { 220.874298f, 5.599976f, -269.977905f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Planarfissure_3", 2002537, 0, 4323994, 4, { 220.874298f, 5.628700f, -269.977905f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_35", 2005467, 0, 5854628, 4, { 186.251297f, 3.180922f, -335.215088f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2005473, 0, 5854935, 4, { 385.274994f, -18.753361f, 273.090698f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_10", 2002365, 0, 4305464, 4, { 272.070007f, 18.902500f, -164.509995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_11", 2006295, 0, 5922964, 4, { 298.670288f, -11.756180f, 159.977203f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_37", 2006296, 0, 5922968, 4, { -200.301895f, -28.334400f, 324.772186f }, 1.000000f, 0.285213f, 0); 
    instance.addEObj( "unknown_38", 2006334, 0, 5939503, 4, { -367.119995f, -56.000000f, 107.110001f }, 1.000000f, -0.827047f, 0); 
    instance.addEObj( "Ironbrazier", 2002347, 0, 4302938, 4, { 175.829697f, -10.426730f, 84.946899f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_39", 2005968, 0, 5900130, 4, { -193.472397f, -36.826302f, 26.056601f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_12", 2003994, 0, 4637056, 4, { -336.833313f, -22.360300f, 435.612701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_13", 2002105, 0, 4296977, 4, { -444.419006f, -27.179010f, 15.953280f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_14", 2001592, 0, 4092602, 4, { -356.685394f, -10.396880f, -242.506195f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Liavinnesgrave", 2004329, 0, 4771796, 4, { -409.050690f, -30.444420f, 36.784771f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_40", 2004105, 0, 4696208, 4, { -239.362701f, -37.791969f, 104.304703f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "MarkoftheWarden_1", 2004596, 0, 4982865, 4, { 148.871704f, -3.654412f, 408.649109f }, 1.000000f, -1.327534f, 0); 
    instance.addEObj( "unknown_41", 2004668, 0, 5018673, 4, { 31.840719f, -4.913074f, -1.321251f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_42", 2004681, 0, 5018674, 4, { 134.998703f, -12.855730f, 154.864807f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004122, 0, 4722776, 4, { -320.149506f, -5.972897f, -209.002808f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_43", 2004897, 0, 5102098, 4, { -154.368103f, -31.788401f, 244.784393f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_44", 2004865, 0, 5072291, 4, { -381.688812f, -58.400002f, 167.752502f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_15", 2004864, 0, 5072293, 4, { -381.688812f, -58.400002f, 167.752502f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "OnthePropertiesofAspectConversion", 2004866, 0, 5072295, 4, { -382.223297f, -58.400002f, 168.658005f }, 0.991760f, 1.022462f, 0);
    instance.addEObj( "unknown_45", 2004867, 0, 5072296, 4, { -382.223297f, -58.400002f, 168.658005f }, 0.991760f, 1.022461f, 0); 
    instance.addEObj( "Destination_16", 2004868, 0, 5072370, 4, { 438.638214f, 12.456440f, 137.634705f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Corruptedcrystal_1", 2004869, 0, 5072379, 4, { 438.638214f, 12.456400f, 137.634705f }, 1.000000f, 0.000047f, 0); 
    instance.addEObj( "Destination_17", 2004877, 0, 5072771, 4, { -299.471008f, -40.664742f, 7.096815f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_46", 2005105, 0, 5580297, 4, { -438.149994f, -54.799999f, 101.871902f }, 1.000000f, 0.357216f, 0); 
    instance.addEObj( "unknown_47", 2001665, 0, 4103612, 4, { -343.602905f, -36.976570f, 233.177795f }, 1.000000f, -1.366650f, 0); 
    instance.addEObj( "unknown_48", 2001663, 0, 4103613, 4, { -336.218903f, -37.103951f, 238.914703f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_49", 2001664, 0, 4103614, 4, { -339.730591f, -37.411732f, 241.866592f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_50", 2001663, 0, 4103615, 4, { -345.598114f, -37.359821f, 238.051498f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_51", 2001663, 0, 4103616, 4, { -344.769897f, -37.285980f, 236.785995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_52", 2001664, 0, 4103617, 4, { -346.628387f, -37.277851f, 236.754105f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_53", 2001663, 0, 4103618, 4, { -344.283997f, -37.855579f, 246.169098f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_54", 2001866, 0, 4219531, 4, { -338.515900f, -37.478802f, 243.745193f }, 1.300000f, 0.000000f, 0); 
    instance.addEObj( "Gravesite", 2001657, 0, 4101645, 4, { -541.160522f, -5.256700f, 46.112202f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Embalmedcorpse", 2001658, 0, 4101646, 4, { -541.174377f, -5.153560f, 46.063290f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_55", 2001868, 0, 4219544, 4, { -421.658295f, -0.497081f, -278.404510f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Queerleaflet", 2001410, 0, 3975264, 4, { -95.152420f, -27.008730f, 274.013214f }, 0.700000f, 0.256097f, 0); 
    instance.addEObj( "Simplegrave", 2001413, 0, 3975274, 4, { -483.882690f, -17.256559f, -1.493163f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Simplegrave_1", 2001414, 0, 3975275, 4, { -527.672180f, -19.012680f, 81.864616f }, 0.991760f, 0.047123f, 0); 
    instance.addEObj( "Simplegrave_2", 2001415, 0, 3975276, 4, { -481.192291f, -20.251610f, 52.513771f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Simplegrave_3", 2001416, 0, 3975279, 4, { -521.006775f, -16.789810f, 20.921680f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Simplegrave_4", 2001417, 0, 3975281, 4, { -477.769287f, -25.394779f, 89.107758f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Cloudmarble", 2001418, 0, 3975318, 4, { -389.184387f, -22.342970f, -44.826920f }, 4.989685f, 0.000048f, 0); 
    instance.addEObj( "unknown_56", 2001867, 0, 4219545, 4, { -388.215607f, -21.927311f, -41.003460f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Althyklavender", 2001419, 0, 3975394, 4, { -77.958366f, -57.804932f, 144.792801f }, 0.800000f, 1.235581f, 0); 
    instance.addEObj( "Althyklavender_1", 2001428, 0, 3982621, 4, { -77.917091f, -58.580929f, 154.205704f }, 0.800000f, 0.000000f, 0); 
    instance.addEObj( "Althyklavender_2", 2001429, 0, 3982622, 4, { -76.598961f, -58.656109f, 168.634598f }, 0.800000f, -0.495300f, 0); 
    instance.addEObj( "Destination_18", 2001423, 0, 3975426, 4, { -550.771301f, 0.585678f, -185.813705f }, 1.000000f, 0.636426f, 0); 
    instance.addEObj( "Destination_19", 2001424, 0, 3975427, 4, { -530.777222f, 6.277578f, -257.101501f }, 1.000000f, 1.027346f, 0); 
    instance.addEObj( "Destination_20", 2001425, 0, 3975432, 4, { -558.767029f, 5.782024f, -260.385803f }, 0.991760f, -0.342627f, 0); 
    instance.addEObj( "Primelocation", 2001453, 0, 3995424, 4, { -571.345215f, 6.171966f, -243.141098f }, 0.991760f, -1.400306f, 0); 
    instance.addEObj( "Primelocation_1", 2001454, 0, 3995429, 4, { -525.311096f, 6.771607f, -286.168701f }, 1.000000f, -0.009292f, 0); 
    instance.addEObj( "Cloudmarble_1", 2001420, 0, 3976223, 4, { -314.013489f, -9.990700f, -240.501404f }, 1.200000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmarble_2", 2001599, 0, 4096862, 4, { -333.855286f, -12.066690f, -232.767899f }, 1.200000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmarble_3", 2001600, 0, 4096863, 4, { -357.263794f, -10.051410f, -231.452393f }, 1.200000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmarble_4", 2001601, 0, 4096864, 4, { -336.997711f, -12.141850f, -254.665298f }, 1.200000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmarble_5", 2001602, 0, 4096865, 4, { -327.084290f, -12.218360f, -234.935196f }, 1.200000f, 0.000000f, 0); 
    instance.addEObj( "Destination_21", 2001421, 0, 3976241, 4, { 146.720398f, -5.583645f, 408.659210f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "MarkoftheWarden_2", 2001603, 0, 4097006, 4, { 146.720398f, -5.583600f, 408.659210f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypool", 2001422, 0, 3976247, 4, { -212.010406f, -37.496380f, 164.960403f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vilekineggs", 2001446, 0, 3985721, 4, { -80.372643f, -58.337872f, 167.431396f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Vilekineggs_1", 2001447, 0, 3985722, 4, { -78.538208f, -58.364429f, 153.104202f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Vilekineggs_2", 2001448, 0, 3985723, 4, { -72.679314f, -58.273312f, 151.203003f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vilekineggs_3", 2001449, 0, 3985724, 4, { -76.015518f, -57.900681f, 147.074493f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thickbramble", 2001450, 0, 3985725, 4, { -79.232780f, -57.943211f, 148.358002f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thickbramble_1", 2001451, 0, 3985726, 4, { -75.822121f, -58.640461f, 166.369095f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Thickbramble_2", 2001452, 0, 3985727, 4, { -74.740646f, -58.284130f, 151.580902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldoffering", 2001438, 0, 3985728, 4, { -525.047913f, -18.624990f, 36.176399f }, 0.991760f, -0.000297f, 0); 
    instance.addEObj( "Oldoffering_1", 2001439, 0, 3985730, 4, { -488.083588f, -20.140869f, 34.128860f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldoffering_2", 2001440, 0, 3985731, 4, { -494.419800f, -20.180771f, 52.474560f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldoffering_3", 2001441, 0, 3985732, 4, { -493.727692f, -17.368690f, 27.128519f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldoffering_4", 2001444, 0, 3985735, 4, { -518.370483f, -18.480459f, 53.367840f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldoffering_5", 2001445, 0, 3985736, 4, { -526.778076f, -16.480370f, 28.685230f }, 1.000000f, 0.000000f, 0); 

  }

  void setupPhaseTwo( QuestBattle& instance )
  {
    auto pPlayer = instance.getPlayerPtr();
    auto chu = instance.getActiveBNpcByLayoutId( INIT_P_POP_01 );

    instance.setDirectorVar( SET_1_SPAWNED, 0 );
    instance.setDirectorVar( SET_2_SPAWNED, 1 );

    auto b1 = instance.createBNpcFromLayoutId( INIT_POP_02A_01, 1440, Common::BNpcType::Enemy );
    auto b2 = instance.createBNpcFromLayoutId( INIT_POP_02A_02, 1440, Common::BNpcType::Enemy );
    auto b3 = instance.createBNpcFromLayoutId( INIT_POP_02C_02, 1440, Common::BNpcType::Enemy );
    auto b4 = instance.createBNpcFromLayoutId( INIT_POP_02C_01, 1440, Common::BNpcType::Enemy );
    auto b5 = instance.createBNpcFromLayoutId( INIT_POP_02B_02, 1440, Common::BNpcType::Enemy );
    auto b6 = instance.createBNpcFromLayoutId( INIT_POP_02B_01, 1440, Common::BNpcType::Enemy );

    b1->setFlag( Entity::NoDeaggro );
    b2->setFlag( Entity::NoDeaggro );
    b3->setFlag( Entity::NoDeaggro );
    b4->setFlag( Entity::NoDeaggro );
    b5->setFlag( Entity::NoDeaggro );
    b6->setFlag( Entity::NoDeaggro );

    chu->hateListAdd( b1, 10000 );
    chu->hateListAdd( b2, 10000 );
    chu->hateListAdd( b3, 10000 );
    chu->hateListAdd( b4, 10000 );
    /* chu->hateListAdd( b5, 10000 );
    chu->hateListAdd( b6, 10000 );*/

    b1->hateListAdd( chu, 10000 );
    b2->hateListAdd( chu, 10000 );
    b3->hateListAdd( chu, 10000 );
    b4->hateListAdd( chu, 10000 );
    b5->hateListAdd( pPlayer, 10000 );
    b6->hateListAdd( pPlayer, 10000 );
  }

  void setupPhaseThree( QuestBattle& instance )
  {
    auto pPlayer = instance.getPlayerPtr();
    auto chu = instance.getActiveBNpcByLayoutId( INIT_P_POP_01 );

    instance.setDirectorVar( SET_2_SPAWNED, 0 );
    instance.setDirectorVar( SET_3_SPAWNED, 1 );

    auto c1 = instance.createBNpcFromLayoutId( INIT_POP_03C_01, 1440, Common::BNpcType::Enemy );
    auto c2 = instance.createBNpcFromLayoutId( INIT_POP_03C_02, 1440, Common::BNpcType::Enemy );
    auto c3 = instance.createBNpcFromLayoutId( INIT_POP_03C_03, 1440, Common::BNpcType::Enemy );
    auto c4 = instance.createBNpcFromLayoutId( INIT_POP_03C_04, 1440, Common::BNpcType::Enemy );
    auto c5 = instance.createBNpcFromLayoutId( INIT_POP_03D_01, 1440, Common::BNpcType::Enemy );

    c1->setFlag( Entity::NoDeaggro );
    c2->setFlag( Entity::NoDeaggro );
    c3->setFlag( Entity::NoDeaggro );
    c4->setFlag( Entity::NoDeaggro );
    c5->setFlag( Entity::NoDeaggro );

    chu->hateListAdd( c1, 10000 );
    chu->hateListAdd( c2, 10000 );
    chu->hateListAdd( c3, 10000 );
    chu->hateListAdd( c4, 10000 );
    chu->hateListAdd( c5, 10000 );

    c1->hateListAdd( chu, 10000 );
    c2->hateListAdd( chu, 10000 );
    c3->hateListAdd( chu, 10000 );
    c4->hateListAdd( chu, 10000 );
    c5->hateListAdd( chu, 10000 );
  }

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    player.setRot( -0.375134f );
    player.setPos( { -243.577f, 6.54697f, -24.7088f } );
  }

  enum vars
  {
    SET_1_SPAWNED,
    SET_2_SPAWNED,
    SET_3_SPAWNED,
    SUCCESS_CALLED,
  };

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {
    auto pPlayer = instance.getPlayerPtr();
    auto chu = instance.getActiveBNpcByLayoutId( INIT_P_POP_01 );

    auto phaseOne = instance.getDirectorVar( SET_1_SPAWNED );
    auto phaseTwo = instance.getDirectorVar( SET_2_SPAWNED );
    auto phaseThree = instance.getDirectorVar( SET_3_SPAWNED );
    auto completed = instance.getDirectorVar( SUCCESS_CALLED );

    if( ( pPlayer && !pPlayer->isAlive() ) || ( chu && !chu->isAlive() ) )
    {
      instance.fail();
      return;
    }

    if( phaseOne )
    {
      auto a1 = instance.getActiveBNpcByLayoutId( INIT_POP_01A_01 );
      auto a2 = instance.getActiveBNpcByLayoutId( INIT_POP_01A_02 );
      auto a3 = instance.getActiveBNpcByLayoutId( INIT_POP_01A_03 );
      auto a4 = instance.getActiveBNpcByLayoutId( INIT_POP_01A_04 );
      auto a5 = instance.getActiveBNpcByLayoutId( INIT_POP_01A_05 );

      if ( !a1 && !a2 && !a3 && !a4 && !a5 )
        setupPhaseTwo( instance );

    }
    else if ( phaseTwo )
    {
      auto b1 = instance.getActiveBNpcByLayoutId( INIT_POP_02A_01 );
      auto b2 = instance.getActiveBNpcByLayoutId( INIT_POP_02A_02 );
      auto b3 = instance.getActiveBNpcByLayoutId( INIT_POP_02C_02 );
      auto b4 = instance.getActiveBNpcByLayoutId( INIT_POP_02C_01 );

      if( !b1 && !b2 && !b3 && !b4 /* && ( !b5 && b5->getHpPercent() == 0 ) && ( !b6 && b6->getHpPercent() == 0 )*/ )
        setupPhaseThree( instance );
    }
    else if ( phaseThree )
    {
      auto c1 = instance.getActiveBNpcByLayoutId( INIT_POP_03C_01 );
      auto c2 = instance.getActiveBNpcByLayoutId( INIT_POP_03C_02 );
      auto c3 = instance.getActiveBNpcByLayoutId( INIT_POP_03C_03 );
      auto c4 = instance.getActiveBNpcByLayoutId( INIT_POP_03C_04 );
      auto c5 = instance.getActiveBNpcByLayoutId( INIT_POP_03D_01 );

      auto b5 = instance.getActiveBNpcByLayoutId( INIT_POP_02B_02 );
      auto b6 = instance.getActiveBNpcByLayoutId( INIT_POP_02B_01 );

      if( !c1 && !c2 && !c3 && !c4 && !c5 && !b5 && !b6 )
      {
        instance.setDirectorVar( SET_3_SPAWNED, 0 );
      }
    }
    else if( !phaseOne && !phaseTwo && !phaseThree && !completed )
    {
      instance.setDirectorVar( SUCCESS_CALLED, 1 );
      instance.success( 7 );
      return;
    }
  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
    eventMgr().playScene( player, instance.getDirectorId(), 1, flags, [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        player.setOnEnterEventDone( true );
      } );
  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
      auto idx = player.getQuestIndex( instance.getQuestId() );
      if( idx == -1 )
        return;
      auto& quest = player.getQuestByIndex( idx );
      quest.setSeq( 6 );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    auto chu = instance.createBNpcFromLayoutId( INIT_P_POP_01, 27780, Common::BNpcType::Friendly );

    auto a1 = instance.createBNpcFromLayoutId( INIT_POP_01A_01, 1440, Common::BNpcType::Enemy );
    auto a2 = instance.createBNpcFromLayoutId( INIT_POP_01A_02, 1440, Common::BNpcType::Enemy );
    auto a3 = instance.createBNpcFromLayoutId( INIT_POP_01A_03, 1440, Common::BNpcType::Enemy );
    auto a4 = instance.createBNpcFromLayoutId( INIT_POP_01A_04, 1440, Common::BNpcType::Enemy );
    auto a5 = instance.createBNpcFromLayoutId( INIT_POP_01A_05, 1440, Common::BNpcType::Enemy );

    /* Doesnt work with enpcs
    TODO: create ENpc from layoutId*/
    auto e1 = instance.createBNpcFromLayoutId( INIT_ENPC_POP_01, 1440, Common::BNpcType::Friendly ); // Hamon
    auto e2 = instance.createBNpcFromLayoutId( INIT_ENPC_POP_02, 1440, Common::BNpcType::Friendly ); // Rurukuta

    chu->setFlag( Entity::NoDeaggro );
    a1->setFlag( Entity::NoDeaggro );
    a2->setFlag( Entity::NoDeaggro );
    a3->setFlag( Entity::NoDeaggro );
    a4->setFlag( Entity::NoDeaggro );
    a5->setFlag( Entity::NoDeaggro );

    chu->hateListAdd( a1, 10000 );
    chu->hateListAdd( a2, 10000 );
    chu->hateListAdd( a3, 10000 );
    chu->hateListAdd( a4, 10000 );
    chu->hateListAdd( a5, 10000 );

    a1->hateListAdd( chu, 10000 );
    a2->hateListAdd( chu, 10000 );
    a3->hateListAdd( chu, 10000 );
    a4->hateListAdd( chu, 10000 );
    a5->hateListAdd( chu, 10000 );

    instance.setDirectorVar( SET_1_SPAWNED, 1 );
  }
};

EXPOSE_SCRIPT( TheSpiritIsWilling );