#include <Script/NativeScriptApi.h>

#include "deepdungeon/ThePalaceoftheDeadFloors101110.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors110.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors111120.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors1120.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors121130.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors131140.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors141150.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors151160.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors161170.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors171180.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors181190.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors191200.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors2130.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors3140.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors4150.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors5160.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors6170.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors7180.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors8190.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors91100.cpp"
#include "dungeons/AlaMhigo.cpp"
#include "dungeons/AmdaporKeep.cpp"
#include "dungeons/AmdaporKeepHard.cpp"
#include "dungeons/BaelsarsWall.cpp"
#include "dungeons/BardamsMettle.cpp"
#include "dungeons/BrayfloxsLongstop.cpp"
#include "dungeons/BrayfloxsLongstopHard.cpp"
#include "dungeons/CastrumAbania.cpp"
#include "dungeons/CastrumMeridianum.cpp"
#include "dungeons/CopperbellMines.cpp"
#include "dungeons/CopperbellMinesHard.cpp"
#include "dungeons/CuttersCry.cpp"
#include "dungeons/DomaCastle.cpp"
#include "dungeons/DzemaelDarkhold.cpp"
#include "dungeons/Halatali.cpp"
#include "dungeons/HalataliHard.cpp"
#include "dungeons/HaukkeManor.cpp"
#include "dungeons/HaukkeManorHard.cpp"
#include "dungeons/HellsLid.cpp"
#include "dungeons/HullbreakerIsle.cpp"
#include "dungeons/HullbreakerIsleHard.cpp"
#include "dungeons/KuganeCastle.cpp"
#include "dungeons/Neverreap.cpp"
#include "dungeons/PharosSirius.cpp"
#include "dungeons/PharosSiriusHard.cpp"
#include "dungeons/SaintMociannesArboretum.cpp"
#include "dungeons/Sastasha.cpp"
#include "dungeons/SastashaHard.cpp"
#include "dungeons/ShisuioftheVioletTides.cpp"
#include "dungeons/Snowcloak.cpp"
#include "dungeons/SohmAl.cpp"
#include "dungeons/SohmAlHard.cpp"
#include "dungeons/SohrKhai.cpp"
#include "dungeons/TheAery.cpp"
#include "dungeons/TheAetherochemicalResearchFacility.cpp"
#include "dungeons/TheAntitower.cpp"
#include "dungeons/TheAurumVale.cpp"
#include "dungeons/TheDrownedCityofSkalla.cpp"
#include "dungeons/TheDuskVigil.cpp"
#include "dungeons/TheFractalContinuum.cpp"
#include "dungeons/TheFractalContinuumHard.cpp"
#include "dungeons/TheGreatGubalLibrary.cpp"
#include "dungeons/TheGreatGubalLibraryHard.cpp"
#include "dungeons/TheKeeperoftheLake.cpp"
#include "dungeons/TheLostCityofAmdapor.cpp"
#include "dungeons/TheLostCityofAmdaporHard.cpp"
#include "dungeons/ThePraetorium.cpp"
#include "dungeons/TheSirensongSea.cpp"
#include "dungeons/TheStoneVigil.cpp"
#include "dungeons/TheStoneVigilHard.cpp"
#include "dungeons/TheSunkenTempleofQarn.cpp"
#include "dungeons/TheSunkenTempleofQarnHard.cpp"
#include "dungeons/TheTamTaraDeepcroft.cpp"
#include "dungeons/TheTamTaraDeepcroftHard.cpp"
#include "dungeons/TheTempleoftheFist.cpp"
#include "dungeons/TheThousandMawsofTotoRak.cpp"
#include "dungeons/TheVault.cpp"
#include "dungeons/TheWanderersPalace.cpp"
#include "dungeons/TheWanderersPalaceHard.cpp"
#include "dungeons/Xelphatol.cpp"
#include "events/TheHauntedManor.cpp"
#include "events/TheValentionesCeremony.cpp"
#include "guildhests/AllsWellthatEndsintheWell.cpp"
#include "guildhests/AnnoytheVoid.cpp"
#include "guildhests/BasicTrainingEnemyParties.cpp"
#include "guildhests/BasicTrainingEnemyStrongholds.cpp"
#include "guildhests/FlickingSticksandTakingNames.cpp"
#include "guildhests/HeroontheHalfShell.cpp"
#include "guildhests/LongLivetheQueen.cpp"
#include "guildhests/MorethanaFeeler.cpp"
#include "guildhests/PullingPoisonPosies.cpp"
#include "guildhests/ShadowandClaw.cpp"
#include "guildhests/SolemnTrinity.cpp"
#include "guildhests/StingingBack.cpp"
#include "guildhests/UndertheArmor.cpp"
#include "guildhests/WardUp.cpp"
#include "hallofthenovice/AccrueEnmityfromMultipleTargets.cpp"
#include "hallofthenovice/AssistAlliesinDefeatingaTarget.cpp"
#include "hallofthenovice/AvoidAreaofEffectAttacks.cpp"
#include "hallofthenovice/AvoidEngagedTargets.cpp"
#include "hallofthenovice/DefeatanOccupiedTarget.cpp"
#include "hallofthenovice/EngageEnemyReinforcements.cpp"
#include "hallofthenovice/EngageMultipleTargets.cpp"
#include "hallofthenovice/ExecuteaComboinBattle.cpp"
#include "hallofthenovice/ExecuteaCombotoIncreaseEnmity.cpp"
#include "hallofthenovice/ExecuteaRangedAttacktoIncreaseEnmity.cpp"
#include "hallofthenovice/FinalExercise.cpp"
#include "hallofthenovice/HealMultipleAllies.cpp"
#include "hallofthenovice/HealanAlly.cpp"
#include "hallofthenovice/InteractwiththeBattlefield.cpp"
#include "pvp/Astragalos.cpp"
#include "pvp/SealRockSeize.cpp"
#include "pvp/TheBorderlandRuinsSecure.cpp"
#include "pvp/TheFeast4on4LightParty.cpp"
#include "pvp/TheFeast4on4Ranked.cpp"
#include "pvp/TheFeast4on4Training.cpp"
#include "pvp/TheFeastCustomMatchCrystalTower.cpp"
#include "pvp/TheFeastCustomMatchFeastingGrounds.cpp"
#include "pvp/TheFeastCustomMatchLichenweed.cpp"
#include "pvp/TheFeastRanked.cpp"
#include "pvp/TheFeastTeamRanked.cpp"
#include "pvp/TheFeastTraining.cpp"
#include "pvp/TheFieldsofGloryShatter.cpp"
#include "questbattles/ABloodyReunion.cpp"
#include "questbattles/ASpectaclefortheAges.cpp"
#include "questbattles/BloodDragoon.cpp"
#include "questbattles/BloodontheDeck.cpp"
#include "questbattles/CuriousGorgeMeetsHisMatch.cpp"
#include "questbattles/DarkwingDragon.cpp"
#include "questbattles/InThalsName.cpp"
#include "questbattles/InterdimensionalRift.cpp"
#include "questbattles/ItsProbablyaTrap.cpp"
#include "questbattles/MatsubaMayhem.cpp"
#include "questbattles/Naadam.cpp"
#include "questbattles/OneLifeforOneWorld.cpp"
#include "questbattles/OurCompromise.cpp"
#include "questbattles/OurUnsungHeroes.cpp"
#include "questbattles/RaisingtheSword.cpp"
#include "questbattles/ReturnoftheBull.cpp"
#include "questbattles/TheBattleonBekko.cpp"
#include "questbattles/TheCarteneauFlatsHeliodrome.cpp"
#include "questbattles/TheFaceofTrueEvil.cpp"
#include "questbattles/TheHeartoftheProblem.cpp"
#include "questbattles/TheOrphansandtheBrokenBlade.cpp"
#include "questbattles/TheResonant.cpp"
#include "questbattles/WhenClansCollide.cpp"
#include "questbattles/WithHeartandSteel.cpp"
#include "raids/AlexanderTheArmoftheFather.cpp"
#include "raids/AlexanderTheArmoftheFatherSavage.cpp"
#include "raids/AlexanderTheArmoftheSon.cpp"
#include "raids/AlexanderTheArmoftheSonSavage.cpp"
#include "raids/AlexanderTheBreathoftheCreator.cpp"
#include "raids/AlexanderTheBreathoftheCreatorSavage.cpp"
#include "raids/AlexanderTheBurdenoftheFather.cpp"
#include "raids/AlexanderTheBurdenoftheFatherSavage.cpp"
#include "raids/AlexanderTheBurdenoftheSon.cpp"
#include "raids/AlexanderTheBurdenoftheSonSavage.cpp"
#include "raids/AlexanderTheCuffoftheFather.cpp"
#include "raids/AlexanderTheCuffoftheFatherSavage.cpp"
#include "raids/AlexanderTheCuffoftheSon.cpp"
#include "raids/AlexanderTheCuffoftheSonSavage.cpp"
#include "raids/AlexanderTheEyesoftheCreator.cpp"
#include "raids/AlexanderTheEyesoftheCreatorSavage.cpp"
#include "raids/AlexanderTheFistoftheFather.cpp"
#include "raids/AlexanderTheFistoftheFatherSavage.cpp"
#include "raids/AlexanderTheFistoftheSon.cpp"
#include "raids/AlexanderTheFistoftheSonSavage.cpp"
#include "raids/AlexanderTheHeartoftheCreator.cpp"
#include "raids/AlexanderTheHeartoftheCreatorSavage.cpp"
#include "raids/AlexanderTheSouloftheCreator.cpp"
#include "raids/AlexanderTheSouloftheCreatorSavage.cpp"
#include "raids/DeltascapeV10.cpp"
#include "raids/DeltascapeV10Savage.cpp"
#include "raids/DeltascapeV20.cpp"
#include "raids/DeltascapeV20Savage.cpp"
#include "raids/DeltascapeV30.cpp"
#include "raids/DeltascapeV30Savage.cpp"
#include "raids/DeltascapeV40.cpp"
#include "raids/DeltascapeV40Savage.cpp"
#include "raids/DunScaith.cpp"
#include "raids/SigmascapeV10.cpp"
#include "raids/SigmascapeV10Savage.cpp"
#include "raids/SigmascapeV20.cpp"
#include "raids/SigmascapeV20Savage.cpp"
#include "raids/SigmascapeV30.cpp"
#include "raids/SigmascapeV30Savage.cpp"
#include "raids/SigmascapeV40.cpp"
#include "raids/SigmascapeV40Savage.cpp"
#include "raids/SyrcusTower.cpp"
#include "raids/TheBindingCoilofBahamutTurn1.cpp"
#include "raids/TheBindingCoilofBahamutTurn2.cpp"
#include "raids/TheBindingCoilofBahamutTurn3.cpp"
#include "raids/TheBindingCoilofBahamutTurn4.cpp"
#include "raids/TheBindingCoilofBahamutTurn5.cpp"
#include "raids/TheFinalCoilofBahamutTurn1.cpp"
#include "raids/TheFinalCoilofBahamutTurn2.cpp"
#include "raids/TheFinalCoilofBahamutTurn3.cpp"
#include "raids/TheFinalCoilofBahamutTurn4.cpp"
#include "raids/TheLabyrinthoftheAncients.cpp"
#include "raids/TheRoyalCityofRabanastre.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn1.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn2.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn3.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn4.cpp"
#include "raids/TheSecondCoilofBahamutTurn1.cpp"
#include "raids/TheSecondCoilofBahamutTurn2.cpp"
#include "raids/TheSecondCoilofBahamutTurn3.cpp"
#include "raids/TheSecondCoilofBahamutTurn4.cpp"
#include "raids/TheUnendingCoilofBahamutUltimate.cpp"
#include "raids/TheVoidArk.cpp"
#include "raids/TheWeaponsRefrainUltimate.cpp"
#include "raids/TheWeepingCityofMhach.cpp"
#include "raids/TheWorldofDarkness.cpp"
#include "treasurehunt/TheAquapolis.cpp"
#include "treasurehunt/TheHiddenCanalsofUznair.cpp"
#include "treasurehunt/TheLostCanalsofUznair.cpp"
#include "trials/ARelicReborntheChimera.cpp"
#include "trials/ARelicReborntheHydra.cpp"
#include "trials/AkhAfahAmphitheatreExtreme.cpp"
#include "trials/AkhAfahAmphitheatreHard.cpp"
#include "trials/BattleintheBigKeep.cpp"
#include "trials/BattleontheBigBridge.cpp"
#include "trials/CapeWestwind.cpp"
#include "trials/ContainmentBayP1T6.cpp"
#include "trials/ContainmentBayP1T6Extreme.cpp"
#include "trials/ContainmentBayS1T7.cpp"
#include "trials/ContainmentBayS1T7Extreme.cpp"
#include "trials/ContainmentBayZ1T9.cpp"
#include "trials/ContainmentBayZ1T9Extreme.cpp"
#include "trials/Emanation.cpp"
#include "trials/EmanationExtreme.cpp"
#include "trials/SpecialEventI.cpp"
#include "trials/SpecialEventII.cpp"
#include "trials/SpecialEventIII.cpp"
#include "trials/TheBowlofEmbers.cpp"
#include "trials/TheBowlofEmbersExtreme.cpp"
#include "trials/TheBowlofEmbersHard.cpp"
#include "trials/TheChrysalis.cpp"
#include "trials/TheDragonsNeck.cpp"
#include "trials/TheFinalStepsofFaith.cpp"
#include "trials/TheHowlingEye.cpp"
#include "trials/TheHowlingEyeExtreme.cpp"
#include "trials/TheHowlingEyeHard.cpp"
#include "trials/TheJadeStoa.cpp"
#include "trials/TheJadeStoaExtreme.cpp"
#include "trials/TheLimitlessBlueExtreme.cpp"
#include "trials/TheLimitlessBlueHard.cpp"
#include "trials/TheMinstrelsBalladNidhoggsRage.cpp"
#include "trials/TheMinstrelsBalladShinryusDomain.cpp"
#include "trials/TheMinstrelsBalladThordansReign.cpp"
#include "trials/TheMinstrelsBalladUltimasBane.cpp"
#include "trials/TheNavel.cpp"
#include "trials/TheNavelExtreme.cpp"
#include "trials/TheNavelHard.cpp"
#include "trials/ThePoolofTribute.cpp"
#include "trials/ThePoolofTributeExtreme.cpp"
#include "trials/TheRoyalMenagerie.cpp"
#include "trials/TheSingularityReactor.cpp"
#include "trials/TheStepsofFaith.cpp"
#include "trials/TheStrikingTreeExtreme.cpp"
#include "trials/TheStrikingTreeHard.cpp"
#include "trials/TheWhorleaterExtreme.cpp"
#include "trials/TheWhorleaterHard.cpp"
#include "trials/ThokastThokExtreme.cpp"
#include "trials/ThokastThokHard.cpp"
#include "trials/ThornmarchExtreme.cpp"
#include "trials/ThornmarchHard.cpp"
#include "trials/UrthsFount.cpp"

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors101110 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors110 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors111120 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors1120 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors121130 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors131140 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors141150 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors151160 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors161170 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors171180 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors181190 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors191200 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors2130 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors3140 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors4150 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors5160 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors6170 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors7180 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors8190 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePalaceoftheDeadFloors91100 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlaMhigo ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AmdaporKeep ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AmdaporKeepHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BaelsarsWall ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BardamsMettle ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BrayfloxsLongstop ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BrayfloxsLongstopHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CastrumAbania ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CastrumMeridianum ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CopperbellMines ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CopperbellMinesHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CuttersCry ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DomaCastle ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DzemaelDarkhold ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Halatali ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HalataliHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HaukkeManor ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HaukkeManorHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HellsLid ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HullbreakerIsle ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HullbreakerIsleHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new KuganeCastle ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Neverreap ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new PharosSirius ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new PharosSiriusHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SaintMociannesArboretum ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Sastasha ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SastashaHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ShisuioftheVioletTides ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Snowcloak ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SohmAl ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SohmAlHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SohrKhai ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheAery ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheAetherochemicalResearchFacility ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheAntitower ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheAurumVale ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheDrownedCityofSkalla ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheDuskVigil ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFractalContinuum ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFractalContinuumHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheGreatGubalLibrary ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheGreatGubalLibraryHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheKeeperoftheLake ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheLostCityofAmdapor ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheLostCityofAmdaporHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePraetorium ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSirensongSea ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheStoneVigil ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheStoneVigilHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSunkenTempleofQarn ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSunkenTempleofQarnHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheTamTaraDeepcroft ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheTamTaraDeepcroftHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheTempleoftheFist ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheThousandMawsofTotoRak ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheVault ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWanderersPalace ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWanderersPalaceHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Xelphatol ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheHauntedManor ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheValentionesCeremony ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AllsWellthatEndsintheWell ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AnnoytheVoid ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BasicTrainingEnemyParties ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BasicTrainingEnemyStrongholds ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new FlickingSticksandTakingNames ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HeroontheHalfShell ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new LongLivetheQueen ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new MorethanaFeeler ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new PullingPoisonPosies ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ShadowandClaw ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SolemnTrinity ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new StingingBack ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new UndertheArmor ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new WardUp ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AccrueEnmityfromMultipleTargets ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AssistAlliesinDefeatingaTarget ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AvoidAreaofEffectAttacks ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AvoidEngagedTargets ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DefeatanOccupiedTarget ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new EngageEnemyReinforcements ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new EngageMultipleTargets ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ExecuteaComboinBattle ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ExecuteaCombotoIncreaseEnmity ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ExecuteaRangedAttacktoIncreaseEnmity ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new FinalExercise ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HealMultipleAllies ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HealanAlly ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new InteractwiththeBattlefield ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Astragalos ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SealRockSeize ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBorderlandRuinsSecure ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeast4on4LightParty ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeast4on4Ranked ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeast4on4Training ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeastCustomMatchCrystalTower ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeastCustomMatchFeastingGrounds ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeastCustomMatchLichenweed ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeastRanked ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeastTeamRanked ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFeastTraining ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFieldsofGloryShatter ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ABloodyReunion ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ASpectaclefortheAges ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BloodDragoon ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BloodontheDeck ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CuriousGorgeMeetsHisMatch ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DarkwingDragon ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new InThalsName ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new InterdimensionalRift ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ItsProbablyaTrap ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new MatsubaMayhem ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Naadam ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new OneLifeforOneWorld ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new OurCompromise ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new OurUnsungHeroes ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new RaisingtheSword ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ReturnoftheBull ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBattleonBekko ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheCarteneauFlatsHeliodrome ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFaceofTrueEvil ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheHeartoftheProblem ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheOrphansandtheBrokenBlade ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheResonant ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new WhenClansCollide ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new WithHeartandSteel ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheArmoftheFather ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheArmoftheFatherSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheArmoftheSon ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheArmoftheSonSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheBreathoftheCreator ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheBreathoftheCreatorSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheBurdenoftheFather ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheBurdenoftheFatherSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheBurdenoftheSon ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheBurdenoftheSonSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheCuffoftheFather ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheCuffoftheFatherSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheCuffoftheSon ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheCuffoftheSonSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheEyesoftheCreator ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheEyesoftheCreatorSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheFistoftheFather ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheFistoftheFatherSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheFistoftheSon ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheFistoftheSonSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheHeartoftheCreator ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheHeartoftheCreatorSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheSouloftheCreator ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AlexanderTheSouloftheCreatorSavage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV10 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV10Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV20 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV20Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV30 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV30Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV40 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DeltascapeV40Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new DunScaith ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV10 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV10Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV20 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV20Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV30 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV30Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV40 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SigmascapeV40Savage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SyrcusTower ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBindingCoilofBahamutTurn1 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBindingCoilofBahamutTurn2 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBindingCoilofBahamutTurn3 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBindingCoilofBahamutTurn4 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBindingCoilofBahamutTurn5 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFinalCoilofBahamutTurn1 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFinalCoilofBahamutTurn2 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFinalCoilofBahamutTurn3 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFinalCoilofBahamutTurn4 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheLabyrinthoftheAncients ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheRoyalCityofRabanastre ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutSavageTurn1 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutSavageTurn2 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutSavageTurn3 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutSavageTurn4 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutTurn1 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutTurn2 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutTurn3 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSecondCoilofBahamutTurn4 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheUnendingCoilofBahamutUltimate ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheVoidArk ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWeaponsRefrainUltimate ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWeepingCityofMhach ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWorldofDarkness ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheAquapolis ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheHiddenCanalsofUznair ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheLostCanalsofUznair ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ARelicReborntheChimera ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ARelicReborntheHydra ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AkhAfahAmphitheatreExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new AkhAfahAmphitheatreHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BattleintheBigKeep ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new BattleontheBigBridge ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CapeWestwind ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ContainmentBayP1T6 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ContainmentBayP1T6Extreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ContainmentBayS1T7 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ContainmentBayS1T7Extreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ContainmentBayZ1T9 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ContainmentBayZ1T9Extreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Emanation ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new EmanationExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SpecialEventI ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SpecialEventII ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new SpecialEventIII ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBowlofEmbers ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBowlofEmbersExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheBowlofEmbersHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheChrysalis ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheDragonsNeck ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheFinalStepsofFaith ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheHowlingEye ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheHowlingEyeExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheHowlingEyeHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheJadeStoa ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheJadeStoaExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheLimitlessBlueExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheLimitlessBlueHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheMinstrelsBalladNidhoggsRage ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheMinstrelsBalladShinryusDomain ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheMinstrelsBalladThordansReign ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheMinstrelsBalladUltimasBane ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheNavel ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheNavelExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheNavelHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePoolofTribute ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThePoolofTributeExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheRoyalMenagerie ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheSingularityReactor ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheStepsofFaith ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheStrikingTreeExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheStrikingTreeHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWhorleaterExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new TheWhorleaterHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThokastThokExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThokastThokHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThornmarchExtreme ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ThornmarchHard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new UrthsFount ),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
