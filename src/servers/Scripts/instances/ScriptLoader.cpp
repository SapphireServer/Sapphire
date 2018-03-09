#include <Script/NativeScriptApi.h>

#include "pvp/TheFeastTeamRanked.cpp"
#include "pvp/SealRockSeize.cpp"
#include "pvp/TheFeast4on4Ranked.cpp"
#include "pvp/TheFeast4on4LightParty.cpp"
#include "pvp/TheFeastRanked.cpp"
#include "pvp/TheFieldsofGloryShatter.cpp"
#include "pvp/TheFeastTraining.cpp"
#include "pvp/Astragalos.cpp"
#include "pvp/TheFeast4on4Training.cpp"
#include "pvp/TheFeastCustomMatchFeastingGrounds.cpp"
#include "pvp/TheFeastCustomMatchLichenweed.cpp"
#include "pvp/TheBorderlandRuinsSecure.cpp"
#include "pvp/TheFeastCustomMatchCrystalTower.cpp"
#include "dungeons/TheTamTaraDeepcroft.cpp"
#include "dungeons/DomaCastle.cpp"
#include "dungeons/HullbreakerIsleHard.cpp"
#include "dungeons/Snowcloak.cpp"
#include "dungeons/TheGreatGubalLibrary.cpp"
#include "dungeons/TheWanderersPalace.cpp"
#include "dungeons/Xelphatol.cpp"
#include "dungeons/TheLostCityofAmdaporHard.cpp"
#include "dungeons/SaintMociannesArboretum.cpp"
#include "dungeons/BardamsMettle.cpp"
#include "dungeons/TheTamTaraDeepcroftHard.cpp"
#include "dungeons/KuganeCastle.cpp"
#include "dungeons/TheDrownedCityofSkalla.cpp"
#include "dungeons/ShisuioftheVioletTides.cpp"
#include "dungeons/CuttersCry.cpp"
#include "dungeons/HellsLid.cpp"
#include "dungeons/TheVault.cpp"
#include "dungeons/TheStoneVigilHard.cpp"
#include "dungeons/Sastasha.cpp"
#include "dungeons/TheFractalContinuum.cpp"
#include "dungeons/TheLostCityofAmdapor.cpp"
#include "dungeons/TheAurumVale.cpp"
#include "dungeons/SohrKhai.cpp"
#include "dungeons/TheSunkenTempleofQarnHard.cpp"
#include "dungeons/Neverreap.cpp"
#include "dungeons/TheAntitower.cpp"
#include "dungeons/Halatali.cpp"
#include "dungeons/TheAery.cpp"
#include "dungeons/PharosSiriusHard.cpp"
#include "dungeons/CastrumMeridianum.cpp"
#include "dungeons/TheGreatGubalLibraryHard.cpp"
#include "dungeons/SohmAl.cpp"
#include "dungeons/TheTempleoftheFist.cpp"
#include "dungeons/TheKeeperoftheLake.cpp"
#include "dungeons/AmdaporKeepHard.cpp"
#include "dungeons/TheWanderersPalaceHard.cpp"
#include "dungeons/CastrumAbania.cpp"
#include "dungeons/AlaMhigo.cpp"
#include "dungeons/PharosSirius.cpp"
#include "dungeons/TheStoneVigil.cpp"
#include "dungeons/TheThousandMawsofTotoRak.cpp"
#include "dungeons/BrayfloxsLongstopHard.cpp"
#include "dungeons/DzemaelDarkhold.cpp"
#include "dungeons/SohmAlHard.cpp"
#include "dungeons/HaukkeManor.cpp"
#include "dungeons/HullbreakerIsle.cpp"
#include "dungeons/TheFractalContinuumHard.cpp"
#include "dungeons/TheSirensongSea.cpp"
#include "dungeons/BaelsarsWall.cpp"
#include "dungeons/HalataliHard.cpp"
#include "dungeons/TheAetherochemicalResearchFacility.cpp"
#include "dungeons/SastashaHard.cpp"
#include "dungeons/CopperbellMinesHard.cpp"
#include "dungeons/TheSunkenTempleofQarn.cpp"
#include "dungeons/AmdaporKeep.cpp"
#include "dungeons/TheDuskVigil.cpp"
#include "dungeons/BrayfloxsLongstop.cpp"
#include "dungeons/HaukkeManorHard.cpp"
#include "dungeons/CopperbellMines.cpp"
#include "dungeons/ThePraetorium.cpp"
#include "questbattles/RaisingtheSword.cpp"
#include "questbattles/InterdimensionalRift.cpp"
#include "questbattles/CuriousGorgeMeetsHisMatch.cpp"
#include "questbattles/WithHeartandSteel.cpp"
#include "questbattles/OneLifeforOneWorld.cpp"
#include "questbattles/ABloodyReunion.cpp"
#include "questbattles/MatsubaMayhem.cpp"
#include "questbattles/BloodontheDeck.cpp"
#include "questbattles/OurCompromise.cpp"
#include "questbattles/Naadam.cpp"
#include "questbattles/InThalsName.cpp"
#include "questbattles/TheResonant.cpp"
#include "questbattles/OurUnsungHeroes.cpp"
#include "questbattles/DarkwingDragon.cpp"
#include "questbattles/BloodDragoon.cpp"
#include "questbattles/ASpectaclefortheAges.cpp"
#include "questbattles/ItsProbablyaTrap.cpp"
#include "questbattles/TheBattleonBekko.cpp"
#include "questbattles/TheHeartoftheProblem.cpp"
#include "questbattles/TheOrphansandtheBrokenBlade.cpp"
#include "questbattles/TheCarteneauFlatsHeliodrome.cpp"
#include "questbattles/ReturnoftheBull.cpp"
#include "questbattles/TheFaceofTrueEvil.cpp"
#include "questbattles/WhenClansCollide.cpp"
#include "raids/AlexanderTheArmoftheSonSavage.cpp"
#include "raids/TheLabyrinthoftheAncients.cpp"
#include "raids/SigmascapeV30.cpp"
#include "raids/TheVoidArk.cpp"
#include "raids/SyrcusTower.cpp"
#include "raids/DeltascapeV20.cpp"
#include "raids/TheFinalCoilofBahamutTurn1.cpp"
#include "raids/SigmascapeV20Savage.cpp"
#include "raids/TheFinalCoilofBahamutTurn3.cpp"
#include "raids/SigmascapeV30Savage.cpp"
#include "raids/TheBindingCoilofBahamutTurn2.cpp"
#include "raids/AlexanderTheSouloftheCreatorSavage.cpp"
#include "raids/DunScaith.cpp"
#include "raids/DeltascapeV40Savage.cpp"
#include "raids/TheSecondCoilofBahamutTurn1.cpp"
#include "raids/AlexanderTheHeartoftheCreatorSavage.cpp"
#include "raids/DeltascapeV40.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn2.cpp"
#include "raids/TheSecondCoilofBahamutTurn3.cpp"
#include "raids/TheUnendingCoilofBahamutUltimate.cpp"
#include "raids/TheSecondCoilofBahamutTurn2.cpp"
#include "raids/TheWorldofDarkness.cpp"
#include "raids/SigmascapeV10.cpp"
#include "raids/AlexanderTheBurdenoftheSonSavage.cpp"
#include "raids/TheFinalCoilofBahamutTurn2.cpp"
#include "raids/AlexanderTheBurdenoftheFatherSavage.cpp"
#include "raids/AlexanderTheHeartoftheCreator.cpp"
#include "raids/TheBindingCoilofBahamutTurn4.cpp"
#include "raids/AlexanderTheBreathoftheCreatorSavage.cpp"
#include "raids/AlexanderTheEyesoftheCreatorSavage.cpp"
#include "raids/AlexanderTheArmoftheFatherSavage.cpp"
#include "raids/DeltascapeV30.cpp"
#include "raids/AlexanderTheFistoftheFather.cpp"
#include "raids/DeltascapeV10.cpp"
#include "raids/DeltascapeV10Savage.cpp"
#include "raids/SigmascapeV40Savage.cpp"
#include "raids/AlexanderTheCuffoftheSon.cpp"
#include "raids/AlexanderTheFistoftheSonSavage.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn3.cpp"
#include "raids/AlexanderTheArmoftheFather.cpp"
#include "raids/AlexanderTheCuffoftheSonSavage.cpp"
#include "raids/TheBindingCoilofBahamutTurn5.cpp"
#include "raids/SigmascapeV20.cpp"
#include "raids/AlexanderTheCuffoftheFather.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn1.cpp"
#include "raids/TheBindingCoilofBahamutTurn1.cpp"
#include "raids/AlexanderTheBurdenoftheSon.cpp"
#include "raids/AlexanderTheBreathoftheCreator.cpp"
#include "raids/TheFinalCoilofBahamutTurn4.cpp"
#include "raids/DeltascapeV30Savage.cpp"
#include "raids/AlexanderTheFistoftheSon.cpp"
#include "raids/AlexanderTheFistoftheFatherSavage.cpp"
#include "raids/AlexanderTheArmoftheSon.cpp"
#include "raids/TheBindingCoilofBahamutTurn3.cpp"
#include "raids/SigmascapeV40.cpp"
#include "raids/TheSecondCoilofBahamutTurn4.cpp"
#include "raids/AlexanderTheCuffoftheFatherSavage.cpp"
#include "raids/SigmascapeV10Savage.cpp"
#include "raids/DeltascapeV20Savage.cpp"
#include "raids/TheWeepingCityofMhach.cpp"
#include "raids/TheRoyalCityofRabanastre.cpp"
#include "raids/AlexanderTheBurdenoftheFather.cpp"
#include "raids/AlexanderTheEyesoftheCreator.cpp"
#include "raids/TheSecondCoilofBahamutSavageTurn4.cpp"
#include "raids/AlexanderTheSouloftheCreator.cpp"
#include "AkhAfahAmphitheatreExtreme.cpp"
#include "guildhests/HeroontheHalfShell.cpp"
#include "guildhests/BasicTrainingEnemyStrongholds.cpp"
#include "guildhests/ShadowandClaw.cpp"
#include "guildhests/AnnoytheVoid.cpp"
#include "guildhests/StingingBack.cpp"
#include "guildhests/FlickingSticksandTakingNames.cpp"
#include "guildhests/SolemnTrinity.cpp"
#include "guildhests/UndertheArmor.cpp"
#include "guildhests/LongLivetheQueen.cpp"
#include "guildhests/AllsWellthatEndsintheWell.cpp"
#include "guildhests/MorethanaFeeler.cpp"
#include "guildhests/PullingPoisonPosies.cpp"
#include "guildhests/WardUp.cpp"
#include "guildhests/BasicTrainingEnemyParties.cpp"
#include "trials/TheStrikingTreeHard.cpp"
#include "trials/TheJadeStoaExtreme.cpp"
#include "trials/TheMinstrelsBalladThordansReign.cpp"
#include "trials/TheBowlofEmbersHard.cpp"
#include "trials/TheSingularityReactor.cpp"
#include "trials/ContainmentBayS1T7Extreme.cpp"
#include "trials/ContainmentBayS1T7.cpp"
#include "trials/TheHowlingEyeHard.cpp"
#include "trials/TheStrikingTreeExtreme.cpp"
#include "trials/Emanation.cpp"
#include "trials/SpecialEventI.cpp"
#include "trials/TheLimitlessBlueExtreme.cpp"
#include "trials/ThePoolofTributeExtreme.cpp"
#include "trials/BattleontheBigBridge.cpp"
#include "trials/TheRoyalMenagerie.cpp"
#include "trials/BattleintheBigKeep.cpp"
#include "trials/UrthsFount.cpp"
#include "trials/EmanationExtreme.cpp"
#include "trials/TheJadeStoa.cpp"
#include "trials/TheHowlingEyeExtreme.cpp"
#include "trials/TheBowlofEmbers.cpp"
#include "trials/TheChrysalis.cpp"
#include "trials/TheStepsofFaith.cpp"
#include "trials/ARelicReborntheChimera.cpp"
#include "trials/ContainmentBayP1T6.cpp"
#include "trials/TheMinstrelsBalladNidhoggsRage.cpp"
#include "trials/ThokastThokExtreme.cpp"
#include "trials/ThornmarchExtreme.cpp"
#include "trials/TheLimitlessBlueHard.cpp"
#include "trials/ContainmentBayP1T6Extreme.cpp"
#include "trials/TheNavelExtreme.cpp"
#include "trials/SpecialEventII.cpp"
#include "trials/TheWhorleaterExtreme.cpp"
#include "trials/TheMinstrelsBalladUltimasBane.cpp"
#include "trials/ContainmentBayZ1T9.cpp"
#include "trials/TheFinalStepsofFaith.cpp"
#include "trials/ThokastThokHard.cpp"
#include "trials/AkhAfahAmphitheatreHard.cpp"
#include "trials/CapeWestwind.cpp"
#include "trials/TheMinstrelsBalladShinryusDomain.cpp"
#include "trials/ContainmentBayZ1T9Extreme.cpp"
#include "trials/SpecialEventIII.cpp"
#include "trials/ThornmarchHard.cpp"
#include "trials/TheDragonsNeck.cpp"
#include "trials/TheNavelHard.cpp"
#include "trials/TheWhorleaterHard.cpp"
#include "trials/TheNavel.cpp"
#include "trials/TheBowlofEmbersExtreme.cpp"
#include "trials/ARelicReborntheHydra.cpp"
#include "trials/ThePoolofTribute.cpp"
#include "trials/TheHowlingEye.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors181190.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors6170.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors151160.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors4150.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors5160.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors3140.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors1120.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors110.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors141150.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors161170.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors131140.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors7180.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors101110.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors171180.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors2130.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors191200.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors121130.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors111120.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors91100.cpp"
#include "deepdungeon/ThePalaceoftheDeadFloors8190.cpp"
#include "treasurehunt/TheAquapolis.cpp"
#include "treasurehunt/TheLostCanalsofUznair.cpp"
#include "treasurehunt/TheHiddenCanalsofUznair.cpp"
#include "hallofthenovice/InteractwiththeBattlefield.cpp"
#include "hallofthenovice/AvoidEngagedTargets.cpp"
#include "hallofthenovice/AvoidAreaofEffectAttacks.cpp"
#include "hallofthenovice/HealMultipleAllies.cpp"
#include "hallofthenovice/ExecuteaCombotoIncreaseEnmity.cpp"
#include "hallofthenovice/AssistAlliesinDefeatingaTarget.cpp"
#include "hallofthenovice/HealanAlly.cpp"
#include "hallofthenovice/EngageMultipleTargets.cpp"
#include "hallofthenovice/FinalExercise.cpp"
#include "hallofthenovice/EngageEnemyReinforcements.cpp"
#include "hallofthenovice/ExecuteaRangedAttacktoIncreaseEnmity.cpp"
#include "hallofthenovice/ExecuteaComboinBattle.cpp"
#include "hallofthenovice/DefeatanOccupiedTarget.cpp"
#include "hallofthenovice/AccrueEnmityfromMultipleTargets.cpp"
#include "events/TheValentionesCeremony.cpp"
#include "events/TheHauntedManor.cpp"

const ScriptObject* ptrs[] =
{
   static_cast< ScriptObject* >( new TheFeastTeamRanked ),
   static_cast< ScriptObject* >( new SealRockSeize ),
   static_cast< ScriptObject* >( new TheFeast4on4Ranked ),
   static_cast< ScriptObject* >( new TheFeast4on4LightParty ),
   static_cast< ScriptObject* >( new TheFeastRanked ),
   static_cast< ScriptObject* >( new TheFieldsofGloryShatter ),
   static_cast< ScriptObject* >( new TheFeastTraining ),
   static_cast< ScriptObject* >( new Astragalos ),
   static_cast< ScriptObject* >( new TheFeast4on4Training ),
   static_cast< ScriptObject* >( new TheFeastCustomMatchFeastingGrounds ),
   static_cast< ScriptObject* >( new TheFeastCustomMatchLichenweed ),
   static_cast< ScriptObject* >( new TheBorderlandRuinsSecure ),
   static_cast< ScriptObject* >( new TheFeastCustomMatchCrystalTower ),
   static_cast< ScriptObject* >( new TheTamTaraDeepcroft ),
   static_cast< ScriptObject* >( new DomaCastle ),
   static_cast< ScriptObject* >( new HullbreakerIsleHard ),
   static_cast< ScriptObject* >( new Snowcloak ),
   static_cast< ScriptObject* >( new TheGreatGubalLibrary ),
   static_cast< ScriptObject* >( new TheWanderersPalace ),
   static_cast< ScriptObject* >( new Xelphatol ),
   static_cast< ScriptObject* >( new TheLostCityofAmdaporHard ),
   static_cast< ScriptObject* >( new SaintMociannesArboretum ),
   static_cast< ScriptObject* >( new BardamsMettle ),
   static_cast< ScriptObject* >( new TheTamTaraDeepcroftHard ),
   static_cast< ScriptObject* >( new KuganeCastle ),
   static_cast< ScriptObject* >( new TheDrownedCityofSkalla ),
   static_cast< ScriptObject* >( new ShisuioftheVioletTides ),
   static_cast< ScriptObject* >( new CuttersCry ),
   static_cast< ScriptObject* >( new HellsLid ),
   static_cast< ScriptObject* >( new TheVault ),
   static_cast< ScriptObject* >( new TheStoneVigilHard ),
   static_cast< ScriptObject* >( new Sastasha ),
   static_cast< ScriptObject* >( new TheFractalContinuum ),
   static_cast< ScriptObject* >( new TheLostCityofAmdapor ),
   static_cast< ScriptObject* >( new TheAurumVale ),
   static_cast< ScriptObject* >( new SohrKhai ),
   static_cast< ScriptObject* >( new TheSunkenTempleofQarnHard ),
   static_cast< ScriptObject* >( new Neverreap ),
   static_cast< ScriptObject* >( new TheAntitower ),
   static_cast< ScriptObject* >( new Halatali ),
   static_cast< ScriptObject* >( new TheAery ),
   static_cast< ScriptObject* >( new PharosSiriusHard ),
   static_cast< ScriptObject* >( new CastrumMeridianum ),
   static_cast< ScriptObject* >( new TheGreatGubalLibraryHard ),
   static_cast< ScriptObject* >( new SohmAl ),
   static_cast< ScriptObject* >( new TheTempleoftheFist ),
   static_cast< ScriptObject* >( new TheKeeperoftheLake ),
   static_cast< ScriptObject* >( new AmdaporKeepHard ),
   static_cast< ScriptObject* >( new TheWanderersPalaceHard ),
   static_cast< ScriptObject* >( new CastrumAbania ),
   static_cast< ScriptObject* >( new AlaMhigo ),
   static_cast< ScriptObject* >( new PharosSirius ),
   static_cast< ScriptObject* >( new TheStoneVigil ),
   static_cast< ScriptObject* >( new TheThousandMawsofTotoRak ),
   static_cast< ScriptObject* >( new BrayfloxsLongstopHard ),
   static_cast< ScriptObject* >( new DzemaelDarkhold ),
   static_cast< ScriptObject* >( new SohmAlHard ),
   static_cast< ScriptObject* >( new HaukkeManor ),
   static_cast< ScriptObject* >( new HullbreakerIsle ),
   static_cast< ScriptObject* >( new TheFractalContinuumHard ),
   static_cast< ScriptObject* >( new TheSirensongSea ),
   static_cast< ScriptObject* >( new BaelsarsWall ),
   static_cast< ScriptObject* >( new HalataliHard ),
   static_cast< ScriptObject* >( new TheAetherochemicalResearchFacility ),
   static_cast< ScriptObject* >( new SastashaHard ),
   static_cast< ScriptObject* >( new CopperbellMinesHard ),
   static_cast< ScriptObject* >( new TheSunkenTempleofQarn ),
   static_cast< ScriptObject* >( new AmdaporKeep ),
   static_cast< ScriptObject* >( new TheDuskVigil ),
   static_cast< ScriptObject* >( new BrayfloxsLongstop ),
   static_cast< ScriptObject* >( new HaukkeManorHard ),
   static_cast< ScriptObject* >( new CopperbellMines ),
   static_cast< ScriptObject* >( new ThePraetorium ),
   static_cast< ScriptObject* >( new RaisingtheSword ),
   static_cast< ScriptObject* >( new InterdimensionalRift ),
   static_cast< ScriptObject* >( new CuriousGorgeMeetsHisMatch ),
   static_cast< ScriptObject* >( new WithHeartandSteel ),
   static_cast< ScriptObject* >( new OneLifeforOneWorld ),
   static_cast< ScriptObject* >( new ABloodyReunion ),
   static_cast< ScriptObject* >( new MatsubaMayhem ),
   static_cast< ScriptObject* >( new BloodontheDeck ),
   static_cast< ScriptObject* >( new OurCompromise ),
   static_cast< ScriptObject* >( new Naadam ),
   static_cast< ScriptObject* >( new InThalsName ),
   static_cast< ScriptObject* >( new TheResonant ),
   static_cast< ScriptObject* >( new OurUnsungHeroes ),
   static_cast< ScriptObject* >( new DarkwingDragon ),
   static_cast< ScriptObject* >( new BloodDragoon ),
   static_cast< ScriptObject* >( new ASpectaclefortheAges ),
   static_cast< ScriptObject* >( new ItsProbablyaTrap ),
   static_cast< ScriptObject* >( new TheBattleonBekko ),
   static_cast< ScriptObject* >( new TheHeartoftheProblem ),
   static_cast< ScriptObject* >( new TheOrphansandtheBrokenBlade ),
   static_cast< ScriptObject* >( new TheCarteneauFlatsHeliodrome ),
   static_cast< ScriptObject* >( new ReturnoftheBull ),
   static_cast< ScriptObject* >( new TheFaceofTrueEvil ),
   static_cast< ScriptObject* >( new WhenClansCollide ),
   static_cast< ScriptObject* >( new AlexanderTheArmoftheSonSavage ),
   static_cast< ScriptObject* >( new TheLabyrinthoftheAncients ),
   static_cast< ScriptObject* >( new SigmascapeV30 ),
   static_cast< ScriptObject* >( new TheVoidArk ),
   static_cast< ScriptObject* >( new SyrcusTower ),
   static_cast< ScriptObject* >( new DeltascapeV20 ),
   static_cast< ScriptObject* >( new TheFinalCoilofBahamutTurn1 ),
   static_cast< ScriptObject* >( new SigmascapeV20Savage ),
   static_cast< ScriptObject* >( new TheFinalCoilofBahamutTurn3 ),
   static_cast< ScriptObject* >( new SigmascapeV30Savage ),
   static_cast< ScriptObject* >( new TheBindingCoilofBahamutTurn2 ),
   static_cast< ScriptObject* >( new AlexanderTheSouloftheCreatorSavage ),
   static_cast< ScriptObject* >( new DunScaith ),
   static_cast< ScriptObject* >( new DeltascapeV40Savage ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutTurn1 ),
   static_cast< ScriptObject* >( new AlexanderTheHeartoftheCreatorSavage ),
   static_cast< ScriptObject* >( new DeltascapeV40 ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutSavageTurn2 ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutTurn3 ),
   static_cast< ScriptObject* >( new TheUnendingCoilofBahamutUltimate ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutTurn2 ),
   static_cast< ScriptObject* >( new TheWorldofDarkness ),
   static_cast< ScriptObject* >( new SigmascapeV10 ),
   static_cast< ScriptObject* >( new AlexanderTheBurdenoftheSonSavage ),
   static_cast< ScriptObject* >( new TheFinalCoilofBahamutTurn2 ),
   static_cast< ScriptObject* >( new AlexanderTheBurdenoftheFatherSavage ),
   static_cast< ScriptObject* >( new AlexanderTheHeartoftheCreator ),
   static_cast< ScriptObject* >( new TheBindingCoilofBahamutTurn4 ),
   static_cast< ScriptObject* >( new AlexanderTheBreathoftheCreatorSavage ),
   static_cast< ScriptObject* >( new AlexanderTheEyesoftheCreatorSavage ),
   static_cast< ScriptObject* >( new AlexanderTheArmoftheFatherSavage ),
   static_cast< ScriptObject* >( new DeltascapeV30 ),
   static_cast< ScriptObject* >( new AlexanderTheFistoftheFather ),
   static_cast< ScriptObject* >( new DeltascapeV10 ),
   static_cast< ScriptObject* >( new DeltascapeV10Savage ),
   static_cast< ScriptObject* >( new SigmascapeV40Savage ),
   static_cast< ScriptObject* >( new AlexanderTheCuffoftheSon ),
   static_cast< ScriptObject* >( new AlexanderTheFistoftheSonSavage ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutSavageTurn3 ),
   static_cast< ScriptObject* >( new AlexanderTheArmoftheFather ),
   static_cast< ScriptObject* >( new AlexanderTheCuffoftheSonSavage ),
   static_cast< ScriptObject* >( new TheBindingCoilofBahamutTurn5 ),
   static_cast< ScriptObject* >( new SigmascapeV20 ),
   static_cast< ScriptObject* >( new AlexanderTheCuffoftheFather ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutSavageTurn1 ),
   static_cast< ScriptObject* >( new TheBindingCoilofBahamutTurn1 ),
   static_cast< ScriptObject* >( new AlexanderTheBurdenoftheSon ),
   static_cast< ScriptObject* >( new AlexanderTheBreathoftheCreator ),
   static_cast< ScriptObject* >( new TheFinalCoilofBahamutTurn4 ),
   static_cast< ScriptObject* >( new DeltascapeV30Savage ),
   static_cast< ScriptObject* >( new AlexanderTheFistoftheSon ),
   static_cast< ScriptObject* >( new AlexanderTheFistoftheFatherSavage ),
   static_cast< ScriptObject* >( new AlexanderTheArmoftheSon ),
   static_cast< ScriptObject* >( new TheBindingCoilofBahamutTurn3 ),
   static_cast< ScriptObject* >( new SigmascapeV40 ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutTurn4 ),
   static_cast< ScriptObject* >( new AlexanderTheCuffoftheFatherSavage ),
   static_cast< ScriptObject* >( new SigmascapeV10Savage ),
   static_cast< ScriptObject* >( new DeltascapeV20Savage ),
   static_cast< ScriptObject* >( new TheWeepingCityofMhach ),
   static_cast< ScriptObject* >( new TheRoyalCityofRabanastre ),
   static_cast< ScriptObject* >( new AlexanderTheBurdenoftheFather ),
   static_cast< ScriptObject* >( new AlexanderTheEyesoftheCreator ),
   static_cast< ScriptObject* >( new TheSecondCoilofBahamutSavageTurn4 ),
   static_cast< ScriptObject* >( new AlexanderTheSouloftheCreator ),
   static_cast< ScriptObject* >( new AkhAfahAmphitheatreExtreme ),
   static_cast< ScriptObject* >( new HeroontheHalfShell ),
   static_cast< ScriptObject* >( new BasicTrainingEnemyStrongholds ),
   static_cast< ScriptObject* >( new ShadowandClaw ),
   static_cast< ScriptObject* >( new AnnoytheVoid ),
   static_cast< ScriptObject* >( new StingingBack ),
   static_cast< ScriptObject* >( new FlickingSticksandTakingNames ),
   static_cast< ScriptObject* >( new SolemnTrinity ),
   static_cast< ScriptObject* >( new UndertheArmor ),
   static_cast< ScriptObject* >( new LongLivetheQueen ),
   static_cast< ScriptObject* >( new AllsWellthatEndsintheWell ),
   static_cast< ScriptObject* >( new MorethanaFeeler ),
   static_cast< ScriptObject* >( new PullingPoisonPosies ),
   static_cast< ScriptObject* >( new WardUp ),
   static_cast< ScriptObject* >( new BasicTrainingEnemyParties ),
   static_cast< ScriptObject* >( new TheStrikingTreeHard ),
   static_cast< ScriptObject* >( new TheJadeStoaExtreme ),
   static_cast< ScriptObject* >( new TheMinstrelsBalladThordansReign ),
   static_cast< ScriptObject* >( new TheBowlofEmbersHard ),
   static_cast< ScriptObject* >( new TheSingularityReactor ),
   static_cast< ScriptObject* >( new ContainmentBayS1T7Extreme ),
   static_cast< ScriptObject* >( new ContainmentBayS1T7 ),
   static_cast< ScriptObject* >( new TheHowlingEyeHard ),
   static_cast< ScriptObject* >( new TheStrikingTreeExtreme ),
   static_cast< ScriptObject* >( new Emanation ),
   static_cast< ScriptObject* >( new SpecialEventI ),
   static_cast< ScriptObject* >( new TheLimitlessBlueExtreme ),
   static_cast< ScriptObject* >( new ThePoolofTributeExtreme ),
   static_cast< ScriptObject* >( new BattleontheBigBridge ),
   static_cast< ScriptObject* >( new TheRoyalMenagerie ),
   static_cast< ScriptObject* >( new BattleintheBigKeep ),
   static_cast< ScriptObject* >( new UrthsFount ),
   static_cast< ScriptObject* >( new EmanationExtreme ),
   static_cast< ScriptObject* >( new TheJadeStoa ),
   static_cast< ScriptObject* >( new TheHowlingEyeExtreme ),
   static_cast< ScriptObject* >( new TheBowlofEmbers ),
   static_cast< ScriptObject* >( new TheChrysalis ),
   static_cast< ScriptObject* >( new TheStepsofFaith ),
   static_cast< ScriptObject* >( new ARelicReborntheChimera ),
   static_cast< ScriptObject* >( new ContainmentBayP1T6 ),
   static_cast< ScriptObject* >( new TheMinstrelsBalladNidhoggsRage ),
   static_cast< ScriptObject* >( new ThokastThokExtreme ),
   static_cast< ScriptObject* >( new ThornmarchExtreme ),
   static_cast< ScriptObject* >( new TheLimitlessBlueHard ),
   static_cast< ScriptObject* >( new ContainmentBayP1T6Extreme ),
   static_cast< ScriptObject* >( new TheNavelExtreme ),
   static_cast< ScriptObject* >( new SpecialEventII ),
   static_cast< ScriptObject* >( new TheWhorleaterExtreme ),
   static_cast< ScriptObject* >( new TheMinstrelsBalladUltimasBane ),
   static_cast< ScriptObject* >( new ContainmentBayZ1T9 ),
   static_cast< ScriptObject* >( new TheFinalStepsofFaith ),
   static_cast< ScriptObject* >( new ThokastThokHard ),
   static_cast< ScriptObject* >( new AkhAfahAmphitheatreHard ),
   static_cast< ScriptObject* >( new CapeWestwind ),
   static_cast< ScriptObject* >( new TheMinstrelsBalladShinryusDomain ),
   static_cast< ScriptObject* >( new ContainmentBayZ1T9Extreme ),
   static_cast< ScriptObject* >( new SpecialEventIII ),
   static_cast< ScriptObject* >( new ThornmarchHard ),
   static_cast< ScriptObject* >( new TheDragonsNeck ),
   static_cast< ScriptObject* >( new TheNavelHard ),
   static_cast< ScriptObject* >( new TheWhorleaterHard ),
   static_cast< ScriptObject* >( new TheNavel ),
   static_cast< ScriptObject* >( new TheBowlofEmbersExtreme ),
   static_cast< ScriptObject* >( new ARelicReborntheHydra ),
   static_cast< ScriptObject* >( new ThePoolofTribute ),
   static_cast< ScriptObject* >( new TheHowlingEye ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors181190 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors6170 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors151160 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors4150 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors5160 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors3140 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors1120 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors110 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors141150 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors161170 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors131140 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors7180 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors101110 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors171180 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors2130 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors191200 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors121130 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors111120 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors91100 ),
   static_cast< ScriptObject* >( new ThePalaceoftheDeadFloors8190 ),
   static_cast< ScriptObject* >( new TheAquapolis ),
   static_cast< ScriptObject* >( new TheLostCanalsofUznair ),
   static_cast< ScriptObject* >( new TheHiddenCanalsofUznair ),
   static_cast< ScriptObject* >( new InteractwiththeBattlefield ),
   static_cast< ScriptObject* >( new AvoidEngagedTargets ),
   static_cast< ScriptObject* >( new AvoidAreaofEffectAttacks ),
   static_cast< ScriptObject* >( new HealMultipleAllies ),
   static_cast< ScriptObject* >( new ExecuteaCombotoIncreaseEnmity ),
   static_cast< ScriptObject* >( new AssistAlliesinDefeatingaTarget ),
   static_cast< ScriptObject* >( new HealanAlly ),
   static_cast< ScriptObject* >( new EngageMultipleTargets ),
   static_cast< ScriptObject* >( new FinalExercise ),
   static_cast< ScriptObject* >( new EngageEnemyReinforcements ),
   static_cast< ScriptObject* >( new ExecuteaRangedAttacktoIncreaseEnmity ),
   static_cast< ScriptObject* >( new ExecuteaComboinBattle ),
   static_cast< ScriptObject* >( new DefeatanOccupiedTarget ),
   static_cast< ScriptObject* >( new AccrueEnmityfromMultipleTargets ),
   static_cast< ScriptObject* >( new TheValentionesCeremony ),
   static_cast< ScriptObject* >( new TheHauntedManor ),

   nullptr
};

extern "C" EXPORT const ScriptObject** getScripts()
{
   return ptrs;
}
