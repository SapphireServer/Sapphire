#include "ActionLut.h"

using namespace Sapphire::World::Action;

ActionLut::Lut ActionLut::m_actionLut =
{
  //Fast Blade, ファストブレード
  //has damage: potency 200, combo potency 0, directional potency 0
  { 9, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fight or Flight, ファイト・オア・フライト
  //applies to self: Fight or Flight, ファイト・オア・フライト, duration 25000, param 0
  { 20, { 0, 0, 0, 0, 76, 25000, 0, 0, 0, 0, 0, 0, 0 } },

  //Riot Blade, ライオットソード
  //has damage: potency 100, combo potency 300, directional potency 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 10
  //bonus effect requirement: RequireCorrectCombo
  { 15, { 100, 300, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 10 } },

  //Total Eclipse, トータルエクリプス
  //has damage: potency 120, combo potency 0, directional potency 0
  { 7381, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shield Bash, シールドバッシュ
  //has damage: potency 110, combo potency 0, directional potency 0
  //applies to targets: Stun, スタン, duration 6000, param 0
  { 16, { 110, 0, 0, 0, 0, 0, 0, 2, 6000, 0, 0, 0, 0 } },

  //Iron Will, アイアンウィル
  //applies to targets: Iron Will, アイアンウィル, duration 0, param 0
  { 28, { 0, 0, 0, 0, 0, 0, 0, 79, 0, 0, 0, 0, 0 } },

  //Shield Lob, シールドロブ
  //has damage: potency 120, combo potency 0, directional potency 0
  //has enmity: increase
  { 24, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rage of Halone, レイジ・オブ・ハルオーネ
  //has damage: potency 100, combo potency 350, directional potency 0
  //has enmity: increase
  { 21, { 100, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sentinel, センチネル
  //applies to self: Sentinel, センチネル, duration 10000, param 0
  { 17, { 0, 0, 0, 0, 74, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Circle of Scorn, サークル・オブ・ドゥーム
  //has damage: potency 120, combo potency 0, directional potency 0
  //applies to targets: Circle of Scorn, サークル・オブ・ドゥーム, duration 15000, param 0
  { 23, { 120, 0, 0, 0, 0, 0, 0, 248, 15000, 0, 0, 0, 0 } },

  //Spirits Within, スピリッツウィズイン
  //has damage: potency 370, combo potency 0, directional potency 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 5
  //comment: potency set to max for now
  { 29, { 370, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 5 } },

  //Sheltron, シェルトロン
  //applies to self: Sheltron, シェルトロン, duration 6000, param 0
  { 3542, { 0, 0, 0, 0, 1856, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //Prominence, プロミネンス
  //has damage: potency 100, combo potency 220, directional potency 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 5
  //bonus effect requirement: RequireCorrectCombo
  { 16457, { 100, 220, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 5 } },

  //Cover, かばう
  //applies to self: Cover, かばう, duration 12000, param 0
  //applies to targets: Covered, かばう［被］, duration 12000, param 0
  { 27, { 0, 0, 0, 0, 80, 12000, 0, 81, 12000, 0, 0, 0, 0 } },

  //Hallowed Ground, インビンシブル
  //applies to self: Hallowed Ground, インビンシブル, duration 10000, param 0
  { 30, { 0, 0, 0, 0, 82, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Goring Blade, ゴアブレード
  //has damage: potency 100, combo potency 390, directional potency 0
  //applies to targets: Goring Blade, ゴアブレード, duration 21000, param 0
  { 3538, { 100, 390, 0, 0, 0, 0, 0, 725, 21000, 0, 0, 0, 0 } },

  //Divine Veil, ディヴァインヴェール
  //applies to targets: Divine Veil, ディヴァインヴェール［バリア］, duration 0, param 0
  { 3540, { 0, 0, 0, 0, 0, 0, 0, 727, 0, 0, 0, 0, 0 } },

  //Clemency, クレメンシー
  { 3541, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Royal Authority, ロイヤルアソリティ
  //has damage: potency 100, combo potency 550, directional potency 0
  //applies to self: Sword Oath, 忠義の剣, duration 15000, param 0
  { 3539, { 100, 550, 0, 0, 1902, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Intervention, インターベンション
  { 7382, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Holy Spirit, ホーリースピリット
  //has damage: potency 350, combo potency 0, directional potency 0
  { 7384, { 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Requiescat, レクイエスカット
  //has damage: potency 550, combo potency 0, directional potency 0
  //applies to self: Requiescat, レクイエスカット, duration 12000, param 0
  //comment: potency set to max for now
  { 7383, { 550, 0, 0, 0, 1368, 12000, 0, 0, 0, 0, 0, 0, 0 } },

  //Passage of Arms, パッセージ・オブ・アームズ
  //applies to self: Passage of Arms, パッセージ・オブ・アームズ, duration 18000, param 0
  { 7385, { 0, 0, 0, 0, 1175, 18000, 0, 0, 0, 0, 0, 0, 0 } },

  //Holy Circle, ホーリーサークル
  //has damage: potency 250, combo potency 0, directional potency 0
  { 16458, { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Intervene, インターヴィーン
  //has damage: potency 200, combo potency 0, directional potency 0
  { 16461, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Atonement, ロイエ
  //has damage: potency 550, combo potency 0, directional potency 0
  //has bonus effect: GainMPPercentage, 4
  { 16460, { 550, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4 } },

  //Confiteor, コンフィテオル
  //has damage: potency 800, combo potency 0, directional potency 0
  { 16459, { 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Heavy Swing, ヘヴィスウィング
  //has damage: potency 200, combo potency 0, directional potency 0
  { 31, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Maim, メイム
  //has damage: potency 100, combo potency 300, directional potency 0
  //has bonus effect: GainJobResource, 169148416
  //bonus effect requirement: RequireCorrectCombo
  { 37, { 100, 300, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 169148416 } },

  //Berserk, バーサク
  //applies to self: Berserk, バーサク, duration 10000, param 0
  { 38, { 0, 0, 0, 0, 86, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Overpower, オーバーパワー
  //has damage: potency 130, combo potency 0, directional potency 0
  { 41, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Defiance, ディフェンダー
  //applies to self: Defiance, ディフェンダー, duration 0, param 0
  { 48, { 0, 0, 0, 0, 91, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Tomahawk, トマホーク
  //has damage: potency 140, combo potency 0, directional potency 0
  //has enmity: increase
  { 46, { 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Storm's Path, シュトルムヴィント
  //has damage: potency 100, combo potency 380, directional potency 0
  //has bonus effect: 24, 336920826
  //bonus effect requirement: RequireCorrectCombo
  { 42, { 100, 380, 0, 0, 0, 0, 0, 0, 0, 0, 24, 1, 336920826 } },

  //Thrill of Battle, スリル・オブ・バトル
  //applies to targets: Thrill of Battle, スリル・オブ・バトル, duration 20000, param 0
  { 40, { 0, 0, 0, 0, 0, 0, 0, 87, 20000, 0, 0, 0, 0 } },

  //Vengeance, ヴェンジェンス
  //applies to self: Vulnerability Down, 被ダメージ低下, duration 15000, param 0
  //applies to targets: Vengeance, ヴェンジェンス, duration 15000, param 0
  //comment: This is a cheat to make vengeance working. Does not match retail packet but end result is the same. Have to script it if that matters.
  { 44, { 0, 0, 0, 0, 912, 15000, 0, 89, 15000, 0, 0, 0, 0 } },

  //Holmgang, ホルムギャング
  //applies to self: Holmgang, ホルムギャング, duration 8000, param 0
  //applies to targets: Holmgang, ホルムギャング, duration 8000, param 0
  { 43, { 0, 0, 0, 0, 409, 8000, 0, 88, 8000, 0, 0, 0, 0 } },

  //Storm's Eye, シュトルムブレハ
  //has damage: potency 100, combo potency 380, directional potency 0
  //applies to self: Storm's Eye, シュトルムブレハ, duration 30000, param 0
  //has bonus effect: GainJobResource, 169148416
  //bonus effect requirement: RequireCorrectCombo
  { 45, { 100, 380, 0, 0, 90, 30000, 0, 0, 0, 0, 8, 1, 169148416 } },

  //Inner Beast, 原初の魂
  //has damage: potency 350, combo potency 0, directional potency 0
  { 49, { 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mythril Tempest, ミスリルテンペスト
  //has damage: potency 100, combo potency 200, directional potency 0
  { 16462, { 100, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Steel Cyclone, スチールサイクロン
  //has damage: potency 220, combo potency 0, directional potency 0
  { 51, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Infuriate, ウォークライ
  //comment: status removed need script
  { 52, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fell Cleave, フェルクリーヴ
  //has damage: potency 590, combo potency 0, directional potency 0
  { 3549, { 590, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Raw Intuition, 原初の直感
  //applies to self: Raw Intuition, 原初の直感, duration 6000, param 0
  { 3551, { 0, 0, 0, 0, 735, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //Equilibrium, エクリブリウム
  //has heal: potency 1200
  { 3552, { 0, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Decimate, デシメート
  //has damage: potency 250, combo potency 0, directional potency 0
  { 3550, { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Onslaught, オンスロート
  //has damage: potency 100, combo potency 0, directional potency 0
  { 7386, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Upheaval, アップヒーバル
  //has damage: potency 450, combo potency 0, directional potency 0
  { 7387, { 450, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shake It Off, シェイクオフ
  //applies to targets: Shake It Off, シェイクオフ, duration 15000, param 0
  { 7388, { 0, 0, 0, 0, 0, 0, 0, 1457, 15000, 0, 0, 0, 0 } },

  //Inner Release, 原初の解放
  //applies to self: Inner Release, 原初の解放, duration 10000, param 65436
  { 7389, { 0, 0, 0, 0, 1177, 10000, 65436, 0, 0, 0, 0, 0, 0 } },

  //Chaotic Cyclone, カオティックサイクロン
  //has damage: potency 400, combo potency 0, directional potency 0
  //has bonus effect: 3, 100
  { 16463, { 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 100 } },

  //Nascent Flash, 原初の猛り
  //applies to targets: Sleep, 睡眠, duration 30000, param 0
  { 16464, { 0, 0, 0, 0, 0, 0, 0, 3, 30000, 0, 0, 0, 0 } },

  //Inner Chaos, インナーカオス
  //has damage: potency 920, combo potency 0, directional potency 0
  //has bonus effect: 3, 100
  { 16465, { 920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 100 } },

  //Hard Slash, ハードスラッシュ
  //has damage: potency 200, combo potency 0, directional potency 0
  { 3617, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Syphon Strike, サイフォンストライク
  //has damage: potency 100, combo potency 300, directional potency 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 6
  { 3623, { 100, 300, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 6 } },

  //Unleash, アンリーシュ
  //has damage: potency 150, combo potency 0, directional potency 0
  { 3621, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Grit, グリットスタンス
  //applies to targets: Grit, グリットスタンス, duration 0, param 0
  { 3629, { 0, 0, 0, 0, 0, 0, 0, 743, 0, 0, 0, 0, 0 } },

  //Unmend, アンメンド
  //has damage: potency 150, combo potency 0, directional potency 0
  //has enmity: increase
  { 3624, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Souleater, ソウルイーター
  //has damage: potency 100, combo potency 400, directional potency 0
  //has bonus effect: 24, 169869612
  //bonus effect requirement: RequireCorrectCombo
  { 3632, { 100, 400, 0, 0, 0, 0, 0, 0, 0, 0, 24, 1, 169869612 } },

  //Flood of Darkness, 暗黒の波動
  //has damage: potency 250, combo potency 0, directional potency 0
  //has bonus effect: GainJobTimer, 2127152
  { 16466, { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 2127152 } },

  //Blood Weapon, ブラッドウェポン
  //applies to self: Blood Weapon, ブラッドウェポン, duration 10000, param 0
  { 3625, { 0, 0, 0, 0, 742, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Shadow Wall, シャドウウォール
  //applies to self: Shadow Wall, シャドウウォール, duration 15000, param 0
  { 3636, { 0, 0, 0, 0, 747, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Edge of Darkness, 暗黒の剣
  //has damage: potency 350, combo potency 0, directional potency 0
  //has bonus effect: GainJobTimer, 2127152
  { 16467, { 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 2127152 } },

  //Dark Mind, ダークマインド
  //applies to targets: Dark Mind, ダークマインド, duration 10000, param 0
  { 3634, { 0, 0, 0, 0, 0, 0, 0, 746, 10000, 0, 0, 0, 0 } },

  //Living Dead, リビングデッド
  //applies to targets: Walking Dead, ウォーキングデッド, duration 0, param 0
  { 3638, { 0, 0, 0, 0, 0, 0, 0, 811, 0, 0, 0, 0, 0 } },

  //Salted Earth, ソルトアース
  //applies to targets: Salted Earth, ソルトアース, duration 21000, param 0
  { 3639, { 0, 0, 0, 0, 0, 0, 0, 749, 21000, 0, 0, 0, 0 } },

  //Plunge, プランジカット
  //has damage: potency 200, combo potency 0, directional potency 0
  { 3640, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Abyssal Drain, アビサルドレイン
  //has damage: potency 200, combo potency 0, directional potency 0
  //has bonus effect: SelfHeal, 200
  { 3641, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 200 } },

  //Carve and Spit, カーヴ・アンド・スピット
  //has damage: potency 450, combo potency 0, directional potency 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 6
  { 3643, { 450, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 6 } },

  //Bloodspiller, ブラッドスピラー
  //has damage: potency 600, combo potency 0, directional potency 0
  { 7392, { 600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Quietus, クワイタス
  //has damage: potency 210, combo potency 0, directional potency 0
  { 7391, { 210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Delirium, ブラッドデリリアム
  //applies to self: Delirium, ブラッドデリリアム, duration 10000, param 65436
  { 7390, { 0, 0, 0, 0, 1972, 10000, 65436, 0, 0, 0, 0, 0, 0 } },

  //The Blackest Night, ブラックナイト
  //comment: status removed need script
  { 7393, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Stalwart Soul, ストルワートソウル
  //has damage: potency 300, combo potency 0, directional potency 0
  //has bonus effect: GainMPPercentage, 6
  { 16468, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 6 } },

  //Edge of Shadow, 漆黒の剣
  //has damage: potency 500, combo potency 0, directional potency 0
  //has bonus effect: GainJobTimer, 2127152
  { 16470, { 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 2127152 } },

  //Dark Missionary, ダークミッショナリー
  //applies to targets: Dark Missionary, ダークミッショナリー, duration 15000, param 0
  { 16471, { 0, 0, 0, 0, 0, 0, 0, 1894, 15000, 0, 0, 0, 0 } },

  //Living Shadow, 影身具現
  { 16472, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Keen Edge, キーンエッジ
  //has damage: potency 200, combo potency 0, directional potency 0
  { 16137, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //No Mercy, ノー・マーシー
  //applies to self: No Mercy, ノー・マーシー, duration 20000, param 0
  { 16138, { 0, 0, 0, 0, 1831, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Brutal Shell, ブルータルシェル
  //has damage: potency 100, combo potency 300, directional potency 0
  { 16139, { 100, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Camouflage, カモフラージュ
  //applies to self: Camouflage, カモフラージュ, duration 20000, param 0
  { 16140, { 0, 0, 0, 0, 1832, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Demon Slice, デーモンスライス
  //has damage: potency 150, combo potency 0, directional potency 0
  { 16141, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Royal Guard, ロイヤルガード
  //applies to self: Royal Guard, ロイヤルガード, duration 0, param 0
  { 16142, { 0, 0, 0, 0, 1833, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Lightning Shot, サンダーバレット
  //has damage: potency 150, combo potency 0, directional potency 0
  //has enmity: increase
  { 16143, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Danger Zone, デンジャーゾーン
  //has damage: potency 350, combo potency 0, directional potency 0
  { 16144, { 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Solid Barrel, ソリッドバレル
  //has damage: potency 100, combo potency 400, directional potency 0
  //has bonus effect: GainJobResource, 19202048
  //bonus effect requirement: RequireCorrectCombo
  { 16145, { 100, 400, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 19202048 } },

  //Burst Strike, バーストストライク
  //has damage: potency 500, combo potency 0, directional potency 0
  { 16162, { 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Nebula, ネビュラ
  //applies to self: Nebula, ネビュラ, duration 15000, param 0
  { 16148, { 0, 0, 0, 0, 1834, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Demon Slaughter, デーモンスローター
  //has damage: potency 100, combo potency 250, directional potency 0
  //has bonus effect: GainJobResource, 19202048
  //bonus effect requirement: RequireCorrectCombo
  { 16149, { 100, 250, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 19202048 } },

  //Aurora, オーロラ
  //applies to targets: Aurora, オーロラ, duration 18000, param 0
  { 16151, { 0, 0, 0, 0, 0, 0, 0, 1835, 18000, 0, 0, 0, 0 } },

  //Superbolide, ボーライド
  //applies to self: Superbolide, ボーライド, duration 8000, param 0
  { 16152, { 0, 0, 0, 0, 1836, 8000, 0, 0, 0, 0, 0, 0, 0 } },

  //Sonic Break, ソニックブレイク
  //has damage: potency 300, combo potency 0, directional potency 0
  //applies to targets: Sonic Break, ソニックブレイク, duration 30000, param 0
  { 16153, { 300, 0, 0, 0, 0, 0, 0, 1837, 30000, 0, 0, 0, 0 } },

  //Rough Divide, ラフディバイド
  //has damage: potency 200, combo potency 0, directional potency 0
  { 16154, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Gnashing Fang, ビートファング
  //has damage: potency 450, combo potency 0, directional potency 0
  //comment: status removed need script
  { 16146, { 450, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Savage Claw, サベッジクロウ
  //has damage: potency 550, combo potency 0, directional potency 0
  //comment: status removed need script
  { 16147, { 550, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Wicked Talon, ウィケッドタロン
  //has damage: potency 650, combo potency 0, directional potency 0
  //comment: status removed need script
  { 16150, { 650, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bow Shock, バウショック
  //has damage: potency 200, combo potency 0, directional potency 0
  //applies to targets: Bow Shock, バウショック, duration 15000, param 0
  { 16159, { 200, 0, 0, 0, 0, 0, 0, 1838, 15000, 0, 0, 0, 0 } },

  //Heart of Light, ハート・オブ・ライト
  //applies to targets: Heart of Light, ハート・オブ・ライト, duration 15000, param 0
  { 16160, { 0, 0, 0, 0, 0, 0, 0, 1839, 15000, 0, 0, 0, 0 } },

  //Heart of Stone, ハート・オブ・ストーン
  //applies to targets: Heart of Stone, ハート・オブ・ストーン, duration 7000, param 0
  { 16161, { 0, 0, 0, 0, 0, 0, 0, 1840, 7000, 0, 0, 0, 0 } },

  //Continuation, コンティニュエーション
  { 16155, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Jugular Rip, ジャギュラーリップ
  //has damage: potency 260, combo potency 0, directional potency 0
  { 16156, { 260, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Abdomen Tear, アブドメンテアー
  //has damage: potency 280, combo potency 0, directional potency 0
  { 16157, { 280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Eye Gouge, アイガウジ
  //has damage: potency 300, combo potency 0, directional potency 0
  { 16158, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fated Circle, フェイテッドサークル
  //has damage: potency 320, combo potency 0, directional potency 0
  { 16163, { 320, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bloodfest, ブラッドソイル
  { 16164, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Blasting Zone, ブラスティングゾーン
  //has damage: potency 800, combo potency 0, directional potency 0
  { 16165, { 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bootshine, 連撃
  //applies to self: Raptor Form, 弐の型：走竜, duration 15000, param 0
  { 53, { 0, 0, 0, 0, 108, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //True Strike, 正拳突き
  //has damage: potency 220, combo potency 240, directional potency 0
  //applies to self: Coeurl Form, 参の型：猛虎, duration 15000, param 0
  { 54, { 220, 240, 0, 0, 109, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Snap Punch, 崩拳
  //has damage: potency 210, combo potency 230, directional potency 0
  //applies to self: Opo-opo Form, 壱の型：魔猿, duration 15000, param 0
  { 56, { 210, 230, 0, 0, 107, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Fists of Earth, 金剛の構え
  //applies to self: Fists of Earth, 金剛の構え, duration 0, param 0
  { 60, { 0, 0, 0, 0, 104, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Twin Snakes, 双掌打
  //has damage: potency 150, combo potency 170, directional potency 0
  //applies to self: Coeurl Form, 参の型：猛虎, duration 15000, param 0
  { 61, { 150, 170, 0, 0, 109, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Arm of the Destroyer, 壊神衝
  //applies to self: Raptor Form, 弐の型：走竜, duration 15000, param 0
  { 62, { 0, 0, 0, 0, 108, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Demolish, 破砕拳
  //has damage: potency 70, combo potency 90, directional potency 0
  //applies to self: Opo-opo Form, 壱の型：魔猿, duration 15000, param 0
  //applies to targets: Demolish, 破砕拳, duration 18000, param 0
  { 66, { 70, 90, 0, 0, 107, 15000, 0, 246, 18000, 0, 0, 0, 0 } },

  //Fists of Wind, 疾風の構え
  //applies to self: Fists of Wind, 疾風の構え, duration 0, param 0
  { 73, { 0, 0, 0, 0, 105, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mantra, マントラ
  //applies to targets: Mantra, マントラ, duration 15000, param 0
  { 65, { 0, 0, 0, 0, 0, 0, 0, 102, 15000, 0, 0, 0, 0 } },

  //Perfect Balance, 踏鳴
  //applies to self: Perfect Balance, 踏鳴, duration 10000, param 0
  { 69, { 0, 0, 0, 0, 110, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Rockbreaker, 地烈斬
  //has damage: potency 120, combo potency 0, directional potency 0
  //applies to self: Opo-opo Form, 壱の型：魔猿, duration 15000, param 0
  { 70, { 120, 0, 0, 0, 107, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Shoulder Tackle, 羅刹衝
  //has damage: potency 100, combo potency 0, directional potency 0
  { 71, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fists of Fire, 紅蓮の構え
  //applies to self: Fists of Fire, 紅蓮の構え, duration 0, param 0
  { 63, { 0, 0, 0, 0, 103, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Four-point Fury, 四面脚
  //has damage: potency 120, combo potency 0, directional potency 0
  //applies to self: Twin Snakes, 双掌打, duration 15000, param 0
  { 16473, { 120, 0, 0, 0, 101, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Dragon Kick, 双竜脚
  //has damage: potency 180, combo potency 200, directional potency 0
  //applies to self: Raptor Form, 弐の型：走竜, duration 15000, param 0
  { 74, { 180, 200, 0, 0, 108, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Form Shift, 演武
  { 4262, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Meditation, 闘気
  //applies to self: Meditation, 剣圧, duration 30000, param 0
  { 3546, { 0, 0, 0, 0, 1865, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //the Forbidden Chakra, 陰陽闘気斬
  //has damage: potency 370, combo potency 0, directional potency 0
  { 3547, { 370, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Elixir Field, 蒼気砲
  //has damage: potency 200, combo potency 0, directional potency 0
  { 3545, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Tornado Kick, 闘魂旋風脚
  //has damage: potency 330, combo potency 0, directional potency 0
  { 3543, { 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Riddle of Earth, 金剛の極意
  //applies to self: Earth's Reply, 金剛の決意, duration 30000, param 0
  { 7394, { 0, 0, 0, 0, 1180, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Riddle of Fire, 紅蓮の極意
  //applies to self: Riddle of Fire, 紅蓮の極意, duration 20000, param 0
  { 7395, { 0, 0, 0, 0, 1181, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Brotherhood, 桃園結義
  //applies to self: Meditative Brotherhood, 桃園結義：闘気, duration 15000, param 0
  //applies to targets: Brotherhood, 桃園結義：攻撃, duration 15000, param 0
  { 7396, { 0, 0, 0, 0, 1182, 15000, 0, 1185, 15000, 0, 0, 0, 0 } },

  //Enlightenment, 万象闘気圏
  //has damage: potency 220, combo potency 0, directional potency 0
  { 16474, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Anatman, 無我
  //applies to self: Anatman, 無我, duration 30000, param 0
  { 16475, { 0, 0, 0, 0, 1862, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Six-sided Star, 六合星導脚
  //has damage: potency 400, combo potency 0, directional potency 0
  { 16476, { 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //True Thrust, トゥルースラスト
  //has damage: potency 290, combo potency 0, directional potency 0
  { 75, { 290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Vorpal Thrust, ボーパルスラスト
  //has damage: potency 140, combo potency 350, directional potency 0
  { 78, { 140, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Life Surge, ライフサージ
  //applies to self: Life Surge, ライフサージ, duration 5000, param 0
  { 83, { 0, 0, 0, 0, 116, 5000, 0, 0, 0, 0, 0, 0, 0 } },

  //Piercing Talon, ピアシングタロン
  //has damage: potency 150, combo potency 0, directional potency 0
  { 90, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Disembowel, ディセムボウル
  //has damage: potency 150, combo potency 320, directional potency 0
  //applies to self: Disembowel, ディセムボウル, duration 30000, param 0
  { 87, { 150, 320, 0, 0, 1914, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Full Thrust, フルスラスト
  //has damage: potency 100, combo potency 530, directional potency 0
  //applies to self: Sharper Fang and Claw, 竜牙竜爪効果アップ, duration 10000, param 0
  { 84, { 100, 530, 0, 0, 802, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Lance Charge, ランスチャージ
  //applies to self: Lance Charge, ランスチャージ, duration 20000, param 0
  { 85, { 0, 0, 0, 0, 1864, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Chaos Thrust, 桜華狂咲
  //has damage: potency 100, combo potency 290, directional potency 330
  //applies to self: Enhanced Wheeling Thrust, 竜尾大車輪効果アップ, duration 10000, param 0
  //applies to targets: Chaos Thrust, 桜華狂咲, duration 24000, param 0
  { 88, { 100, 290, 330, 0, 803, 10000, 0, 118, 24000, 0, 0, 0, 0 } },

  //Jump, ジャンプ
  //applies to self: Dive Ready, ミラージュダイブ実行可, duration 15000, param 0
  { 92, { 0, 0, 0, 0, 1243, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Elusive Jump, イルーシブジャンプ
  { 94, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Doom Spike, ドゥームスパイク
  //has damage: potency 170, combo potency 0, directional potency 0
  { 86, { 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Spineshatter Dive, スパインダイブ
  { 95, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Dragonfire Dive, ドラゴンダイブ
  //has damage: potency 380, combo potency 0, directional potency 0
  { 96, { 380, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Battle Litany, バトルリタニー
  //applies to targets: Battle Litany, バトルリタニー, duration 20000, param 0
  { 3557, { 0, 0, 0, 0, 0, 0, 0, 786, 20000, 0, 0, 0, 0 } },

  //Blood of the Dragon, 蒼の竜血
  { 3553, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fang and Claw, 竜牙竜爪
  //applies to self: Raiden Thrust Ready, 竜眼雷電実行可, duration 10000, param 0
  { 3554, { 0, 0, 0, 0, 1863, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Wheeling Thrust, 竜尾大車輪
  { 3556, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Geirskogul, ゲイルスコグル
  //has damage: potency 300, combo potency 0, directional potency 0
  { 3555, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sonic Thrust, ソニックスラスト
  //has damage: potency 100, combo potency 200, directional potency 0
  { 7397, { 100, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Dragon Sight, ドラゴンサイト
  //applies to targets: Right Eye, 竜の右眼, duration 20000, param 0
  { 7398, { 0, 0, 0, 0, 0, 0, 0, 1910, 20000, 0, 0, 0, 0 } },

  //Mirage Dive, ミラージュダイブ
  //has damage: potency 300, combo potency 0, directional potency 0
  { 7399, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Nastrond, ナーストレンド
  //has damage: potency 400, combo potency 0, directional potency 0
  { 7400, { 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Coerthan Torment, クルザントーメント
  //has damage: potency 100, combo potency 230, directional potency 0
  { 16477, { 100, 230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //High Jump, ハイジャンプ
  //applies to self: Dive Ready, ミラージュダイブ実行可, duration 15000, param 0
  { 16478, { 0, 0, 0, 0, 1243, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Raiden Thrust, 竜眼雷電
  //has damage: potency 330, combo potency 0, directional potency 0
  { 16479, { 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Stardiver, スターダイバー
  { 16480, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Spinning Edge, 双刃旋
  //has damage: potency 220, combo potency 0, directional potency 0
  { 2240, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shade Shift, 残影
  //applies to targets: Shade Shift, 残影, duration 5000, param 0
  { 2241, { 0, 0, 0, 0, 0, 0, 0, 488, 5000, 0, 0, 0, 0 } },

  //Gust Slash, 風断ち
  //has damage: potency 100, combo potency 330, directional potency 0
  { 2242, { 100, 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hide, かくれる
  { 2245, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Throwing Dagger, 投刃
  //has damage: potency 120, combo potency 0, directional potency 0
  { 2247, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mug, ぶんどる
  //has damage: potency 140, combo potency 0, directional potency 0
  { 2248, { 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Trick Attack, だまし討ち
  //has damage: potency 350, combo potency 500, directional potency 0
  //applies to targets: Vulnerability Up, 被ダメージ上昇, duration 15000, param 0
  { 2258, { 350, 500, 0, 0, 0, 0, 0, 638, 15000, 0, 0, 0, 0 } },

  //Aeolian Edge, 旋風刃
  { 2255, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shadow Fang, 影牙
  //has damage: potency 200, combo potency 0, directional potency 0
  //applies to targets: Shadow Fang, 影牙, duration 30000, param 0
  { 2257, { 200, 0, 0, 0, 0, 0, 0, 508, 30000, 0, 0, 0, 0 } },

  //Death Blossom, 血花五月雨
  //has damage: potency 120, combo potency 0, directional potency 0
  { 2254, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ten, 天の印
  //applies to self: Mudra, 印, duration 6000, param 0
  { 2259, { 0, 0, 0, 0, 496, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //Ninjutsu, 忍術
  { 2260, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Chi, 地の印
  //applies to self: Mudra, 印, duration 6000, param 0
  { 2261, { 0, 0, 0, 0, 496, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //Shukuchi, 縮地
  { 2262, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Jin, 人の印
  //applies to self: Mudra, 印, duration 6000, param 0
  { 2263, { 0, 0, 0, 0, 496, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //Kassatsu, 活殺自在
  //applies to self: Kassatsu, 活殺自在, duration 15000, param 0
  { 2264, { 0, 0, 0, 0, 497, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Hakke Mujinsatsu, 八卦無刃殺
  //has damage: potency 100, combo potency 140, directional potency 0
  { 16488, { 100, 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Armor Crush, 強甲破点突
  { 3563, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Dream Within a Dream, 夢幻三段
  //has damage: potency 200, combo potency 0, directional potency 0
  //applies to targets: Assassinate Ready, 終撃実行可, duration 0, param 0
  { 3566, { 200, 0, 0, 0, 0, 0, 0, 1955, 0, 0, 0, 0, 0 } },

  //Assassinate, 終撃
  //has damage: potency 200, combo potency 0, directional potency 0
  { 2246, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hellfrog Medium, 口寄せの術・大蝦蟇
  { 7401, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bhavacakra, 六道輪廻
  { 7402, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ten Chi Jin, 天地人
  //applies to self: Ten Chi Jin, 天地人, duration 10000, param 0
  { 7403, { 0, 0, 0, 0, 1186, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Meisui, 命水
  { 16489, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bunshin, 分身の術
  //applies to self: Bunshin, 分身の術, duration 30000, param 0
  { 16493, { 0, 0, 0, 0, 1954, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Fuma Shuriken, 風魔手裏剣
  //has damage: potency 500, combo potency 0, directional potency 0
  { 2265, { 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Katon, 火遁の術
  //has damage: potency 50, combo potency 0, directional potency 0
  { 2266, { 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Raiton, 雷遁の術
  //has damage: potency 800, combo potency 0, directional potency 0
  { 2267, { 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hyoton, 氷遁の術
  //has damage: potency 400, combo potency 0, directional potency 0
  { 2268, { 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Huton, 風遁の術
  //applies to self: Huton, 風遁の術, duration 0, param 0
  { 2269, { 0, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Doton, 土遁の術
  //applies to self: Doton, 土遁の術, duration 24000, param 0
  //applies to targets: Doton Heavy, ヘヴィ, duration 5000, param 0
  { 2270, { 0, 0, 0, 0, 501, 24000, 0, 502, 5000, 0, 0, 0, 0 } },

  //Suiton, 水遁の術
  //has damage: potency 600, combo potency 0, directional potency 0
  //applies to self: Suiton, 水遁の術, duration 10000, param 0
  { 2271, { 600, 0, 0, 0, 507, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Goka Mekkyaku, 劫火滅却の術
  //has damage: potency 750, combo potency 0, directional potency 0
  { 16491, { 750, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hyosho Ranryu, 氷晶乱流の術
  //has damage: potency 1200, combo potency 0, directional potency 0
  { 16492, { 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rabbit Medium, 口寄せの術
  { 2272, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hakaze, 刃風
  //has damage: potency 200, combo potency 0, directional potency 0
  { 7477, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Jinpu, 陣風
  //has damage: potency 100, combo potency 320, directional potency 0
  //applies to self: Jinpu, 陣風, duration 40000, param 0
  { 7478, { 100, 320, 0, 0, 1298, 40000, 0, 0, 0, 0, 0, 0, 0 } },

  //Third Eye, 心眼
  //applies to self: Third Eye, 心眼, duration 3000, param 0
  { 7498, { 0, 0, 0, 0, 1232, 3000, 0, 0, 0, 0, 0, 0, 0 } },

  //Enpi, 燕飛
  //has damage: potency 100, combo potency 320, directional potency 0
  { 7486, { 100, 320, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shifu, 士風
  //has damage: potency 100, combo potency 320, directional potency 0
  //applies to self: Shifu, 士風, duration 40000, param 0
  { 7479, { 100, 320, 0, 0, 1299, 40000, 0, 0, 0, 0, 0, 0, 0 } },

  //Fuga, 風雅
  //has damage: potency 100, combo potency 0, directional potency 0
  { 7483, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Gekko, 月光
  //has damage: potency 100, combo potency 480, directional potency 0
  { 7481, { 100, 480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Iaijutsu, 居合術
  { 7867, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mangetsu, 満月
  //has damage: potency 100, combo potency 160, directional potency 0
  { 7484, { 100, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Kasha, 花車
  //has damage: potency 100, combo potency 480, directional potency 0
  { 7482, { 100, 480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Oka, 桜花
  //has damage: potency 100, combo potency 160, directional potency 0
  { 7485, { 100, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Yukikaze, 雪風
  //has damage: potency 100, combo potency 360, directional potency 0
  { 7480, { 100, 360, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Meikyo Shisui, 明鏡止水
  //applies to self: Meikyo Shisui, 明鏡止水, duration 15000, param 3
  { 7499, { 0, 0, 0, 0, 1233, 15000, 3, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Kaiten, 必殺剣・回天
  //applies to self: Kaiten, 必殺剣・回天, duration 10000, param 0
  { 7494, { 0, 0, 0, 0, 1229, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Gyoten, 必殺剣・暁天
  //has damage: potency 100, combo potency 0, directional potency 0
  { 7492, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Yaten, 必殺剣・夜天
  //has damage: potency 100, combo potency 0, directional potency 0
  //applies to self: Enhanced Enpi, 燕飛効果アップ, duration 15000, param 0
  { 7493, { 100, 0, 0, 0, 1236, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Merciful Eyes, 慈眼
  //has bonus effect: SelfHeal, 200
  { 7502, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 200 } },

  //Meditate, 黙想
  //applies to self: Meditate, 黙想, duration 15000, param 0
  { 7497, { 0, 0, 0, 0, 1231, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Shinten, 必殺剣・震天
  //has damage: potency 320, combo potency 0, directional potency 0
  { 7490, { 320, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Kyuten, 必殺剣・九天
  //has damage: potency 150, combo potency 0, directional potency 0
  { 7491, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Seigan, 必殺剣・星眼
  //has damage: potency 220, combo potency 0, directional potency 0
  { 7501, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ikishoten, 意気衝天
  { 16482, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Guren, 必殺剣・紅蓮
  //has damage: potency 850, combo potency 0, directional potency 0
  { 7496, { 850, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hissatsu: Senei, 必殺剣・閃影
  //has damage: potency 1100, combo potency 0, directional potency 0
  { 16481, { 1100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Tsubame-gaeshi, 燕返し
  { 16483, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shoha, 照破
  { 16487, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Higanbana, 彼岸花
  //has damage: potency 250, combo potency 0, directional potency 0
  //applies to targets: Higanbana, 彼岸花, duration 60000, param 0
  { 7489, { 250, 0, 0, 0, 0, 0, 0, 1228, 60000, 0, 0, 0, 0 } },

  //Tenka Goken, 天下五剣
  //has damage: potency 360, combo potency 0, directional potency 0
  { 7488, { 360, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Midare Setsugekka, 乱れ雪月花
  //has damage: potency 800, combo potency 0, directional potency 0
  { 7487, { 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Kaeshi: Higanbana, 返し彼岸花
  //has damage: potency 375, combo potency 0, directional potency 0
  //applies to targets: Higanbana, 彼岸花, duration 60000, param 0
  { 16484, { 375, 0, 0, 0, 0, 0, 0, 1228, 60000, 0, 0, 0, 0 } },

  //Kaeshi: Goken, 返し五剣
  //has damage: potency 540, combo potency 0, directional potency 0
  { 16485, { 540, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Kaeshi: Setsugekka, 返し雪月花
  //has damage: potency 1200, combo potency 0, directional potency 0
  { 16486, { 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Heavy Shot, ヘヴィショット
  //has damage: potency 180, combo potency 0, directional potency 0
  //comment: status removed need script
  { 97, { 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Straight Shot, ストレートショット
  //has damage: potency 200, combo potency 0, directional potency 0
  { 98, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Raging Strikes, 猛者の撃
  //applies to self: Raging Strikes, 猛者の撃, duration 20000, param 0
  { 101, { 0, 0, 0, 0, 125, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Venomous Bite, ベノムバイト
  //has damage: potency 100, combo potency 0, directional potency 0
  //applies to targets: Venomous Bite, ベノムバイト, duration 30000, param 0
  { 100, { 100, 0, 0, 0, 0, 0, 0, 124, 30000, 0, 0, 0, 0 } },

  //Bloodletter, ブラッドレッター
  //has damage: potency 150, combo potency 0, directional potency 0
  { 110, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Repelling Shot, リペリングショット
  { 112, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Quick Nock, クイックノック
  //has damage: potency 150, combo potency 0, directional potency 0
  { 106, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Windbite, ウィンドバイト
  //has damage: potency 60, combo potency 0, directional potency 0
  //applies to targets: Windbite, ウィンドバイト, duration 30000, param 0
  { 113, { 60, 0, 0, 0, 0, 0, 0, 129, 30000, 0, 0, 0, 0 } },

  //Barrage, 乱れ撃ち
  //applies to self: Barrage, 乱れ撃ち, duration 10000, param 0
  { 107, { 0, 0, 0, 0, 128, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Mage's Ballad, 賢人のバラード
  //has damage: potency 100, combo potency 0, directional potency 0
  { 114, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //the Warden's Paean, 時神のピーアン
  //applies to targets: The Warden's Paean, 時神のピーアン, duration 0, param 0
  { 3561, { 0, 0, 0, 0, 0, 0, 0, 866, 0, 0, 0, 0, 0 } },

  //Army's Paeon, 軍神のパイオン
  //has damage: potency 100, combo potency 0, directional potency 0
  { 116, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rain of Death, レイン・オブ・デス
  //has damage: potency 130, combo potency 0, directional potency 0
  { 117, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Battle Voice, バトルボイス
  //applies to self: Battle Voice, バトルボイス, duration 20000, param 0
  { 118, { 0, 0, 0, 0, 141, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //the Wanderer's Minuet, 旅神のメヌエット
  //has damage: potency 100, combo potency 0, directional potency 0
  { 3559, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Pitch Perfect, ピッチパーフェクト
  { 8842, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Empyreal Arrow, エンピリアルアロー
  //has damage: potency 230, combo potency 0, directional potency 0
  { 3558, { 230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Iron Jaws, アイアンジョー
  //has damage: potency 100, combo potency 0, directional potency 0
  //applies to targets: Windbite, ウィンドバイト, duration 30000, param 0
  { 3560, { 100, 0, 0, 0, 0, 0, 0, 129, 30000, 0, 0, 0, 0 } },

  //Sidewinder, サイドワインダー
  { 3562, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Troubadour, トルバドゥール
  //applies to targets: Troubadour, トルバドゥール, duration 15000, param 0
  { 7405, { 0, 0, 0, 0, 0, 0, 0, 1934, 15000, 0, 0, 0, 0 } },

  //Caustic Bite, コースティックバイト
  //has damage: potency 150, combo potency 0, directional potency 0
  //applies to targets: Caustic Bite, コースティックバイト, duration 30000, param 0
  { 7406, { 150, 0, 0, 0, 0, 0, 0, 1200, 30000, 0, 0, 0, 0 } },

  //Stormbite, ストームバイト
  //has damage: potency 100, combo potency 0, directional potency 0
  //applies to targets: Stormbite, ストームバイト, duration 30000, param 0
  { 7407, { 100, 0, 0, 0, 0, 0, 0, 1201, 30000, 0, 0, 0, 0 } },

  //Nature's Minne, 地神のミンネ
  //applies to targets: Nature's Minne, 地神のミンネ, duration 15000, param 0
  { 7408, { 0, 0, 0, 0, 0, 0, 0, 1202, 15000, 0, 0, 0, 0 } },

  //Refulgent Arrow, リフルジェントアロー
  //has damage: potency 330, combo potency 0, directional potency 0
  { 7409, { 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shadowbite, シャドウバイト
  { 16494, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Burst Shot, バーストショット
  //has damage: potency 230, combo potency 0, directional potency 0
  { 16495, { 230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Apex Arrow, エイペックスアロー
  { 16496, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Split Shot, スプリットショット
  //has damage: potency 180, combo potency 0, directional potency 0
  { 2866, { 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Slug Shot, スラッグショット
  //has damage: potency 100, combo potency 260, directional potency 0
  { 2868, { 100, 260, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hot Shot, ホットショット
  //has damage: potency 300, combo potency 0, directional potency 0
  { 2872, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Reassemble, 整備
  //applies to targets: Reassembled, 整備, duration 5000, param 0
  { 2876, { 0, 0, 0, 0, 0, 0, 0, 851, 5000, 0, 0, 0, 0 } },

  //Gauss Round, ガウスラウンド
  //has damage: potency 150, combo potency 0, directional potency 0
  { 2874, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Spread Shot, スプレッドショット
  //has damage: potency 180, combo potency 0, directional potency 0
  { 2870, { 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Clean Shot, クリーンショット
  //has damage: potency 100, combo potency 0, directional potency 0
  { 2873, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Hypercharge, ハイパーチャージ
  //applies to self: Hypercharge, ハイパーチャージ, duration 8000, param 0
  { 2885, { 0, 0, 0, 0, 688, 8000, 0, 0, 0, 0, 0, 0, 0 } },

  //Heat Blast, ヒートブラスト
  //has damage: potency 220, combo potency 0, directional potency 0
  { 7410, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rook Autoturret, オートタレット・ルーク
  { 2864, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rook Overdrive, オーバードライブ・ルーク
  { 7415, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rook Overload, オーバーロード・ルーク
  //has damage: potency 400, combo potency 0, directional potency 0
  { 7416, { 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Wildfire, ワイルドファイア
  //applies to targets: Wildfire, ワイルドファイア, duration 10000, param 0
  { 2878, { 0, 0, 0, 0, 0, 0, 0, 861, 10000, 0, 0, 0, 0 } },

  //Detonator, デトネーター
  { 16766, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ricochet, リコシェット
  { 2890, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Auto Crossbow, オートボウガン
  //has damage: potency 180, combo potency 0, directional potency 0
  { 16497, { 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Heated Split Shot, ヒートスプリットショット
  //has damage: potency 220, combo potency 0, directional potency 0
  { 7411, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Tactician, タクティシャン
  //applies to targets: Tactician, タクティシャン, duration 15000, param 0
  { 16889, { 0, 0, 0, 0, 0, 0, 0, 1951, 15000, 0, 0, 0, 0 } },

  //Drill, ドリル
  //has damage: potency 700, combo potency 0, directional potency 0
  { 16498, { 700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Heated Slug Shot, ヒートスラッグショット
  //has damage: potency 100, combo potency 330, directional potency 0
  { 7412, { 100, 330, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Heated Clean Shot, ヒートクリーンショット
  //has damage: potency 100, combo potency 440, directional potency 0
  { 7413, { 100, 440, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Barrel Stabilizer, バレルヒーター
  { 7414, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Flamethrower, フレイムスロアー
  //applies to targets: Flamethrower, フレイムスロアー, duration 10000, param 0
  { 7418, { 0, 0, 0, 0, 0, 0, 0, 1205, 10000, 0, 0, 0, 0 } },

  //Bioblaster, バイオブラスト
  //has damage: potency 60, combo potency 0, directional potency 0
  //applies to targets: Bioblaster, バイオブラスト, duration 15000, param 0
  { 16499, { 60, 0, 0, 0, 0, 0, 0, 1866, 15000, 0, 0, 0, 0 } },

  //Air Anchor, エアアンカー
  //has damage: potency 700, combo potency 0, directional potency 0
  { 16500, { 700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Automaton Queen, オートマトン・クイーン
  { 16501, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Queen Overdrive, オーバードライブ・クイーン
  { 16502, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Arm Punch, クイーン・アームパンチ
  //has damage: potency 150, combo potency 0, directional potency 0
  { 16504, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Roller Dash, クイーン・ローラーダッシュ
  //has damage: potency 300, combo potency 0, directional potency 0
  { 17206, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Pile Bunker, クイーン・パイルバンカー
  { 16503, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Cascade, カスケード
  //has damage: potency 250, combo potency 0, directional potency 0
  //applies to self: Flourishing Cascade, リバースカスケード実行可, duration 20000, param 0
  { 15989, { 250, 0, 0, 0, 1814, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Fountain, ファウンテン
  //has damage: potency 100, combo potency 300, directional potency 0
  //applies to self: Flourishing Fountain, ファウンテンフォール実行可, duration 20000, param 0
  { 15990, { 100, 300, 0, 0, 1815, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Windmill, ウィンドミル
  //has damage: potency 150, combo potency 0, directional potency 0
  //applies to self: Flourishing Windmill, ライジングウィンドミル実行可, duration 20000, param 0
  { 15993, { 150, 0, 0, 0, 1816, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Standard Step, スタンダードステップ
  //applies to self: Standard Step, スタンダードステップ, duration 15000, param 0
  { 15997, { 0, 0, 0, 0, 1818, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Double Standard Finish, ダブル・スタンダードフィニッシュ
  //applies to self: Esprit, エスプリ, duration 60000, param 0
  //applies to targets: Standard Finish, スタンダードフィニッシュ, duration 60000, param 0
  { 16192, { 0, 0, 0, 0, 1847, 60000, 0, 1821, 60000, 0, 0, 0, 0 } },

  //Reverse Cascade, リバースカスケード
  //has damage: potency 300, combo potency 0, directional potency 0
  { 15991, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bladeshower, ブレードシャワー
  //has damage: potency 100, combo potency 200, directional potency 0
  //applies to self: Flourishing Shower, ブラッドシャワー実行可, duration 20000, param 0
  { 15994, { 100, 200, 0, 0, 1817, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Fan Dance, 扇の舞い【序】
  //has damage: potency 150, combo potency 0, directional potency 0
  //applies to self: Flourishing Fan Dance, 扇の舞い【急】実行可, duration 20000, param 0
  { 16007, { 150, 0, 0, 0, 1820, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Rising Windmill, ライジングウィンドミル
  { 15995, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fountainfall, ファウンテンフォール
  //has damage: potency 350, combo potency 0, directional potency 0
  { 15992, { 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bloodshower, ブラッドシャワー
  { 15996, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fan Dance II, 扇の舞い【破】
  //has damage: potency 100, combo potency 0, directional potency 0
  //applies to self: Flourishing Fan Dance, 扇の舞い【急】実行可, duration 20000, param 0
  { 16008, { 100, 0, 0, 0, 1820, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //En Avant, アン・アヴァン
  { 16010, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Curing Waltz, 癒やしのワルツ
  //has heal: potency 300
  { 16015, { 0, 0, 0, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shield Samba, 守りのサンバ
  //applies to targets: Shield Samba, 守りのサンバ, duration 15000, param 0
  { 16012, { 0, 0, 0, 0, 0, 0, 0, 1826, 15000, 0, 0, 0, 0 } },

  //Closed Position, クローズドポジション
  { 16006, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ending, クローズドポジション解除
  { 18073, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Devilment, 攻めのタンゴ
  //applies to targets: Devilment, 攻めのタンゴ, duration 20000, param 0
  { 16011, { 0, 0, 0, 0, 0, 0, 0, 1825, 20000, 0, 0, 0, 0 } },

  //Fan Dance III, 扇の舞い【急】
  //applies to self: Flourishing Fan Dance, 扇の舞い【急】実行可, duration 20000, param 0
  { 16009, { 0, 0, 0, 0, 1820, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Technical Step, テクニカルステップ
  //applies to self: Technical Step, テクニカルステップ, duration 15000, param 0
  { 15998, { 0, 0, 0, 0, 1819, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Quadruple Technical Finish, クワッド・テクニカルフィニッシュ
  //applies to targets: Esprit, エスプリ, duration 20000, param 0
  { 16196, { 0, 0, 0, 0, 0, 0, 0, 1848, 20000, 0, 0, 0, 0 } },

  //Flourish, フラリッシュ
  { 16013, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Saber Dance, 剣の舞い
  { 16005, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Improvisation, インプロビゼーション
  //applies to self: Improvisation, インプロビゼーション, duration 15000, param 0
  { 16014, { 0, 0, 0, 0, 1827, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Emboite, 薔薇のアンボワテ
  { 15999, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Entrechat, 小鳥のアントルシャ
  { 16000, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Jete, 緑葉のジュテ
  { 16001, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Pirouette, 金冠のピルエッテ
  { 16002, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Blizzard, ブリザド
  { 142, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fire, ファイア
  //applies to self: Firestarter, ファイガ効果アップ, duration 12000, param 0
  { 141, { 0, 0, 0, 0, 165, 12000, 0, 0, 0, 0, 0, 0, 0 } },

  //Transpose, トランス
  { 149, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Thunder, サンダー
  //has damage: potency 30, combo potency 0, directional potency 0
  //applies to self: Thundercloud, サンダー系魔法効果アップ, duration 18000, param 0
  //applies to targets: Thunder, サンダー, duration 18000, param 0
  { 144, { 30, 0, 0, 0, 164, 18000, 0, 161, 18000, 0, 0, 0, 0 } },

  //Sleep, スリプル
  //applies to targets: Sleep, 睡眠, duration 30000, param 0
  { 145, { 0, 0, 0, 0, 0, 0, 0, 3, 30000, 0, 0, 0, 0 } },

  //Blizzard II, ブリザラ
  { 146, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Scathe, コラプス
  { 156, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fire II, ファイラ
  { 147, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Thunder II, サンダラ
  //has damage: potency 30, combo potency 0, directional potency 0
  //applies to self: Thundercloud, サンダー系魔法効果アップ, duration 18000, param 0
  //applies to targets: Thunder II, サンダラ, duration 12000, param 0
  { 7447, { 30, 0, 0, 0, 164, 18000, 0, 162, 12000, 0, 0, 0, 0 } },

  //Manaward, マバリア
  //applies to targets: Manaward, マバリア, duration 20000, param 0
  { 157, { 0, 0, 0, 0, 0, 0, 0, 168, 20000, 0, 0, 0, 0 } },

  //Fire III, ファイガ
  { 152, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aetherial Manipulation, エーテリアルステップ
  { 155, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Manafont, マナフォント
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 30
  { 158, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 30 } },

  //Freeze, フリーズ
  { 159, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Blizzard III, ブリザガ
  { 154, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Thunder III, サンダガ
  //has damage: potency 70, combo potency 0, directional potency 0
  //applies to self: Thundercloud, サンダー系魔法効果アップ, duration 18000, param 0
  //applies to targets: Thunder III, サンダガ, duration 24000, param 0
  { 153, { 70, 0, 0, 0, 164, 18000, 0, 163, 24000, 0, 0, 0, 0 } },

  //Flare, フレア
  { 162, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ley Lines, 黒魔紋
  //applies to self: Ley Lines, 黒魔紋, duration 0, param 0
  { 3573, { 0, 0, 0, 0, 737, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sharpcast, 激成魔
  //applies to self: Sharpcast, 激成魔, duration 0, param 0
  { 3574, { 0, 0, 0, 0, 867, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enochian, エノキアン
  //applies to self: Enochian, エノキアン, duration 0, param 0
  { 3575, { 0, 0, 0, 0, 868, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Blizzard IV, ブリザジャ
  { 3576, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fire IV, ファイジャ
  { 3577, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Between the Lines, ラインズステップ
  { 7419, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Thunder IV, サンダジャ
  //has damage: potency 50, combo potency 0, directional potency 0
  //applies to self: Thundercloud, サンダー系魔法効果アップ, duration 18000, param 0
  //applies to targets: Thunder IV, サンダジャ, duration 18000, param 0
  { 7420, { 50, 0, 0, 0, 164, 18000, 0, 1210, 18000, 0, 0, 0, 0 } },

  //Triplecast, 三連魔
  //applies to self: Triplecast, 三連魔, duration 15000, param 0
  { 7421, { 0, 0, 0, 0, 1211, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Foul, ファウル
  { 7422, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Despair, デスペア
  { 16505, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Umbral Soul, アンブラルソウル
  { 16506, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Xenoglossy, ゼノグロシー
  //has damage: potency 750, combo potency 0, directional potency 0
  { 16507, { 750, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ruin, ルイン
  //has damage: potency 180, combo potency 0, directional potency 0
  { 163, { 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bio, バイオ
  //applies to targets: Bio, バイオ, duration 30000, param 0
  { 164, { 0, 0, 0, 0, 0, 0, 0, 179, 30000, 0, 0, 0, 0 } },

  //Physick, フィジク
  //has heal: potency 400
  { 190, { 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Summon, サモン
  { 165, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Miasma, ミアズマ
  //has damage: potency 20, combo potency 0, directional potency 0
  //applies to targets: Miasma, ミアズマ, duration 30000, param 0
  { 168, { 20, 0, 0, 0, 0, 0, 0, 180, 30000, 0, 0, 0, 0 } },

  //Resurrection, リザレク
  { 173, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Summon II, サモンII
  { 170, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fester, ミアズマバースト
  //has damage: potency 100, combo potency 0, directional potency 0
  { 181, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Energy Drain, エナジードレイン
  //has damage: potency 100, combo potency 0, directional potency 0
  { 16508, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bio II, バイオラ
  //applies to targets: Bio II, バイオラ, duration 30000, param 0
  { 178, { 0, 0, 0, 0, 0, 0, 0, 189, 30000, 0, 0, 0, 0 } },

  //Bane, ベイン
  //applies to targets: Miasma III, ミアズガ, duration 30000, param 0
  { 174, { 0, 0, 0, 0, 0, 0, 0, 1215, 30000, 0, 0, 0, 0 } },

  //Ruin II, ルインラ
  //has damage: potency 160, combo potency 0, directional potency 0
  { 172, { 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Summon III, サモンIII
  { 180, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Energy Siphon, エナジーサイフォン
  //has damage: potency 40, combo potency 0, directional potency 0
  { 16510, { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Outburst, アウトバースト
  //has damage: potency 70, combo potency 0, directional potency 0
  { 16511, { 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enkindle, エンキンドル
  { 184, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Painflare, ペインフレア
  //has damage: potency 130, combo potency 0, directional potency 0
  { 3578, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ruin III, ルインガ
  //has damage: potency 200, combo potency 0, directional potency 0
  { 3579, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Tri-disaster, トライディザスター
  //has damage: potency 300, combo potency 0, directional potency 0
  //applies to targets: Miasma III, ミアズガ, duration 30000, param 0
  { 3580, { 300, 0, 0, 0, 0, 0, 0, 1215, 30000, 0, 0, 0, 0 } },

  //Dreadwyrm Trance, トランス・バハムート
  { 3581, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Deathflare, デスフレア
  { 3582, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ruin IV, ルインジャ
  //has damage: potency 300, combo potency 0, directional potency 0
  { 7426, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aetherpact, エーテルパクト
  { 7423, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Devotion, エギの加護
  //applies to targets: Devotion, エギの加護, duration 15000, param 0
  { 7450, { 0, 0, 0, 0, 0, 0, 0, 1213, 15000, 0, 0, 0, 0 } },

  //Bio III, バイオガ
  //applies to targets: Bio III, バイオガ, duration 30000, param 0
  { 7424, { 0, 0, 0, 0, 0, 0, 0, 1214, 30000, 0, 0, 0, 0 } },

  //Miasma III, ミアズガ
  //has damage: potency 50, combo potency 0, directional potency 0
  //applies to targets: Miasma III, ミアズガ, duration 30000, param 0
  { 7425, { 50, 0, 0, 0, 0, 0, 0, 1215, 30000, 0, 0, 0, 0 } },

  //Summon Bahamut, サモン・バハムート
  { 7427, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Wyrmwave, ウィルムウェーブ
  //has damage: potency 150, combo potency 0, directional potency 0
  { 7428, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enkindle Bahamut, エンキンドル・バハムート
  { 7429, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Akh Morn, アク・モーン
  { 7449, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Firebird Trance, トランス・フェニックス
  { 16513, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fountain of Fire, 霊泉の炎
  //has damage: potency 250, combo potency 0, directional potency 0
  //applies to self: Hellish Conduit, 霊泉, duration 10000, param 0
  { 16514, { 250, 0, 0, 0, 1867, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Brand of Purgatory, 煉獄の炎
  { 16515, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enkindle Phoenix, エンキンドル・フェニックス
  { 16516, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Everlasting Flight, 不死鳥の翼
  //applies to targets: Everlasting Flight, 不死鳥の翼, duration 21000, param 0
  { 16517, { 0, 0, 0, 0, 0, 0, 0, 1868, 21000, 0, 0, 0, 0 } },

  //Scarlet Flame, 火焔
  //has damage: potency 150, combo potency 0, directional potency 0
  { 16519, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Revelation, リヴァレーション
  { 16518, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Gust, ガスト
  //has damage: potency 20, combo potency 0, directional potency 0
  { 637, { 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Downburst, ダウンバースト
  //has damage: potency 100, combo potency 0, directional potency 0
  { 639, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Glittering Emerald, エメラルドの煌き
  //has damage: potency 30, combo potency 0, directional potency 0
  { 16521, { 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Gouge, ひっかき
  //has damage: potency 40, combo potency 0, directional potency 0
  { 633, { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Glittering Topaz, トパーズの煌き
  { 16520, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shining Topaz, トパーズの輝き
  //has damage: potency 200, combo potency 0, directional potency 0
  { 634, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Wind Blade, ウィンドブレード
  //has damage: potency 30, combo potency 0, directional potency 0
  { 792, { 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aerial Slash, エリアルスラッシュ
  //has damage: potency 150, combo potency 0, directional potency 0
  { 794, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Slipstream, スリップストリーム
  //has damage: potency 50, combo potency 0, directional potency 0
  //applies to targets: Gale Enforcer, 螺旋気流, duration 9000, param 0
  { 16523, { 50, 0, 0, 0, 0, 0, 0, 1869, 9000, 0, 0, 0, 0 } },

  //Aerial Blast, エリアルブラスト
  //has damage: potency 350, combo potency 0, directional potency 0
  { 796, { 350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rock Buster, ロックバスター
  //has damage: potency 60, combo potency 0, directional potency 0
  { 787, { 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Earthen Armor, 大地の鎧
  //applies to targets: Stone Wall, 防護障壁, duration 30000, param 0
  { 16522, { 0, 0, 0, 0, 0, 0, 0, 1936, 30000, 0, 0, 0, 0 } },

  //Mountain Buster, マウンテンバスター
  //has damage: potency 250, combo potency 0, directional potency 0
  { 788, { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Earthen Fury, 大地の怒り
  //has damage: potency 300, combo potency 0, directional potency 0
  //applies to targets: Razed Earth, 大地の怒り, duration 15000, param 0
  { 791, { 300, 0, 0, 0, 0, 0, 0, 312, 15000, 0, 0, 0, 0 } },

  //Burning Strike, バーニングストライク
  { 798, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Crimson Cyclone, クリムゾンサイクロン
  { 797, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Flaming Crush, フレイミングクラッシュ
  { 800, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Inferno, 地獄の火炎
  //has damage: potency 300, combo potency 0, directional potency 0
  //applies to targets: Inferno, 地獄の火炎, duration 15000, param 0
  { 801, { 300, 0, 0, 0, 0, 0, 0, 314, 15000, 0, 0, 0, 0 } },

  //Riposte, リポスト
  //has damage: potency 130, combo potency 0, directional potency 0
  { 7504, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Jolt, ジョルト
  //has damage: potency 180, combo potency 0, directional potency 0
  { 7503, { 180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verthunder, ヴァルサンダー
  //has damage: potency 350, combo potency 0, directional potency 0
  //applies to self: Verfire Ready, ヴァルファイア効果アップ, duration 30000, param 0
  { 7505, { 350, 0, 0, 0, 1234, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Corps-a-corps, コル・ア・コル
  //has damage: potency 130, combo potency 0, directional potency 0
  { 7506, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Veraero, ヴァルエアロ
  //has damage: potency 350, combo potency 0, directional potency 0
  //applies to self: Verstone Ready, ヴァルストーン効果アップ, duration 30000, param 0
  { 7507, { 350, 0, 0, 0, 1235, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Scatter, スキャッター
  //has damage: potency 120, combo potency 0, directional potency 0
  { 7509, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verthunder II, ヴァルサンダラ
  //has damage: potency 120, combo potency 0, directional potency 0
  { 16524, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Veraero II, ヴァルエアロラ
  //has damage: potency 120, combo potency 0, directional potency 0
  { 16525, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verfire, ヴァルファイア
  //has damage: potency 300, combo potency 0, directional potency 0
  { 7510, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verstone, ヴァルストーン
  //has damage: potency 300, combo potency 0, directional potency 0
  { 7511, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Zwerchhau, ツヴェルクハウ
  //has damage: potency 100, combo potency 150, directional potency 0
  { 7512, { 100, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Displacement, デプラスマン
  //has damage: potency 200, combo potency 0, directional potency 0
  { 7515, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fleche, フレッシュ
  //has damage: potency 420, combo potency 0, directional potency 0
  { 7517, { 420, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Redoublement, ルドゥブルマン
  //has damage: potency 100, combo potency 230, directional potency 0
  { 7516, { 100, 230, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Acceleration, アクセラレーション
  //applies to self: Acceleration, アクセラレーション, duration 20000, param 0
  { 7518, { 0, 0, 0, 0, 1238, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Moulinet, ムーリネ
  //has damage: potency 60, combo potency 0, directional potency 0
  { 7513, { 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Vercure, ヴァルケアル
  //has heal: potency 350
  { 7514, { 0, 0, 0, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Contre Sixte, コントルシクスト
  { 7519, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Embolden, エンボルデン
  //applies to self: Embolden, エンボルデン, duration 20000, param 0
  //applies to targets: Embolden, エンボルデン, duration 20000, param 0
  { 7520, { 0, 0, 0, 0, 1239, 20000, 0, 1297, 20000, 0, 0, 0, 0 } },

  //Manafication, マナフィケーション
  //applies to self: Manafication, マナフィケーション, duration 10000, param 0
  { 7521, { 0, 0, 0, 0, 1971, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Jolt II, ジョルラ
  //has damage: potency 280, combo potency 0, directional potency 0
  { 7524, { 280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verraise, ヴァルレイズ
  { 7523, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Impact, インパクト
  //has damage: potency 220, combo potency 0, directional potency 0
  { 16526, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verflare, ヴァルフレア
  //has damage: potency 600, combo potency 0, directional potency 0
  { 7525, { 600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Verholy, ヴァルホーリー
  //has damage: potency 600, combo potency 0, directional potency 0
  { 7526, { 600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Engagement, アンガジェマン
  //has damage: potency 150, combo potency 0, directional potency 0
  { 16527, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Reprise, ルプリーズ
  //has damage: potency 100, combo potency 0, directional potency 0
  { 16529, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Scorch, スコーチ
  //has damage: potency 700, combo potency 0, directional potency 0
  { 16530, { 700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enchanted Riposte, エンリポスト
  //has damage: potency 300, combo potency 0, directional potency 0
  { 7527, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enchanted Zwerchhau, エンツヴェルクハウ
  //has damage: potency 100, combo potency 290, directional potency 0
  { 7528, { 100, 290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enchanted Redoublement, エンルドゥブルマン
  //has damage: potency 100, combo potency 470, directional potency 0
  { 7529, { 100, 470, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enchanted Moulinet, エンムーリネ
  //has damage: potency 200, combo potency 0, directional potency 0
  { 7530, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Enchanted Reprise, エンルプリーズ
  //has damage: potency 250, combo potency 0, directional potency 0
  { 16528, { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Stone, ストーン
  //has damage: potency 140, combo potency 0, directional potency 0
  { 119, { 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Cure, ケアル
  //has heal: potency 450
  //comment: status removed need script
  { 120, { 0, 0, 0, 450, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aero, エアロ
  //has damage: potency 50, combo potency 0, directional potency 0
  //applies to targets: Aero, エアロ, duration 18000, param 0
  { 121, { 50, 0, 0, 0, 0, 0, 0, 143, 18000, 0, 0, 0, 0 } },

  //Medica, メディカ
  //has heal: potency 300
  { 124, { 0, 0, 0, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Raise, レイズ
  //applies to targets: Raise, 蘇生, duration 1000, param 0
  { 125, { 0, 0, 0, 0, 0, 0, 0, 148, 1000, 0, 0, 0, 0 } },

  //Fluid Aura, アクアオーラ
  //applies to targets: Bind, バインド, duration 6000, param 0
  { 134, { 0, 0, 0, 0, 0, 0, 0, 13, 6000, 0, 0, 0, 0 } },

  //Stone II, ストンラ
  //has damage: potency 200, combo potency 0, directional potency 0
  { 127, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Cure II, ケアルラ
  //has heal: potency 700
  { 135, { 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aero II, エアロラ
  //has damage: potency 60, combo potency 0, directional potency 0
  //applies to targets: Aero II, エアロラ, duration 18000, param 0
  { 132, { 60, 0, 0, 0, 0, 0, 0, 144, 18000, 0, 0, 0, 0 } },

  //Medica II, メディカラ
  //has heal: potency 200
  //applies to targets: Medica II, メディカラ, duration 15000, param 0
  { 133, { 0, 0, 0, 200, 0, 0, 0, 150, 15000, 0, 0, 0, 0 } },

  //Presence of Mind, 神速魔
  //applies to self: Presence of Mind, 神速魔, duration 15000, param 0
  { 136, { 0, 0, 0, 0, 157, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Regen, リジェネ
  //applies to targets: Regen, リジェネ, duration 18000, param 0
  { 137, { 0, 0, 0, 0, 0, 0, 0, 158, 18000, 0, 0, 0, 0 } },

  //Cure III, ケアルガ
  //has heal: potency 550
  { 131, { 0, 0, 0, 550, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Holy, ホーリー
  //has damage: potency 140, combo potency 0, directional potency 0
  //applies to targets: Stun, スタン, duration 4000, param 0
  { 139, { 140, 0, 0, 0, 0, 0, 0, 2, 4000, 0, 0, 0, 0 } },

  //Benediction, ベネディクション
  { 140, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Afflatus Solace, ハート・オブ・ソラス
  //has heal: potency 700
  { 16531, { 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Asylum, アサイラム
  //applies to self: Asylum, アサイラム, duration 24000, param 0
  //applies to targets: Asylum, アサイラム：効果, duration 5000, param 0
  { 3569, { 0, 0, 0, 0, 1911, 24000, 0, 1912, 5000, 0, 0, 0, 0 } },

  //Stone III, ストンガ
  //has damage: potency 240, combo potency 0, directional potency 0
  { 3568, { 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Assize, アサイズ
  //has damage: potency 400, combo potency 0, directional potency 0
  //has heal: potency 400
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 5
  { 3571, { 400, 0, 0, 400, 0, 0, 0, 0, 0, 0, 4, 0, 5 } },

  //Thin Air, シンエアー
  //applies to self: Thin Air, シンエアー, duration 12000, param 65436
  { 7430, { 0, 0, 0, 0, 1217, 12000, 65436, 0, 0, 0, 0, 0, 0 } },

  //Tetragrammaton, テトラグラマトン
  //has heal: potency 700
  { 3570, { 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Stone IV, ストンジャ
  //has damage: potency 280, combo potency 0, directional potency 0
  { 7431, { 280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Divine Benison, ディヴァインベニゾン
  //applies to targets: Divine Benison, ディヴァインベニゾン, duration 15000, param 0
  { 7432, { 0, 0, 0, 0, 0, 0, 0, 1218, 15000, 0, 0, 0, 0 } },

  //Plenary Indulgence, インドゥルゲンティア
  //applies to targets: Confession, インドゥルゲンティア, duration 10000, param 0
  { 7433, { 0, 0, 0, 0, 0, 0, 0, 1219, 10000, 0, 0, 0, 0 } },

  //Dia, ディア
  //has damage: potency 120, combo potency 0, directional potency 0
  //applies to targets: Dia, ディア, duration 30000, param 0
  { 16532, { 120, 0, 0, 0, 0, 0, 0, 1871, 30000, 0, 0, 0, 0 } },

  //Glare, グレア
  //has damage: potency 300, combo potency 0, directional potency 0
  { 16533, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Afflatus Misery, ハート・オブ・ミゼリ
  //has damage: potency 900, combo potency 0, directional potency 0
  //has bonus effect: DamageFallOff, 75
  { 16535, { 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 75 } },

  //Afflatus Rapture, ハート・オブ・ラプチャー
  //has heal: potency 300
  { 16534, { 0, 0, 0, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Temperance, テンパランス
  //applies to targets: Temperance, テンパランス：効果, duration 20000, param 0
  { 16536, { 0, 0, 0, 0, 0, 0, 0, 1873, 20000, 0, 0, 0, 0 } },

  //Ruin, ルイン
  //has damage: potency 160, combo potency 0, directional potency 0
  { 17869, { 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bio, バイオ
  //applies to targets: Bio, バイオ, duration 30000, param 0
  { 17864, { 0, 0, 0, 0, 0, 0, 0, 179, 30000, 0, 0, 0, 0 } },

  //Summon Selene, サモン・セレネ
  { 17216, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Whispering Dawn, 光の囁き
  { 16537, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bio II, バイオラ
  //applies to targets: Bio II, バイオラ, duration 30000, param 0
  { 17865, { 0, 0, 0, 0, 0, 0, 0, 189, 30000, 0, 0, 0, 0 } },

  //Adloquium, 鼓舞激励の策
  //has heal: potency 300
  //applies to targets: Catalyze, 激励, duration 30000, param 0
  { 185, { 0, 0, 0, 300, 0, 0, 0, 1918, 30000, 0, 0, 0, 0 } },

  //Succor, 士気高揚の策
  //has heal: potency 180
  //applies to targets: Galvanize, 鼓舞, duration 30000, param 0
  { 186, { 0, 0, 0, 180, 0, 0, 0, 297, 30000, 0, 0, 0, 0 } },

  //Ruin II, ルインラ
  //has damage: potency 200, combo potency 0, directional potency 0
  { 17870, { 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fey Illumination, フェイイルミネーション
  { 16538, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aetherflow, エーテルフロー
  //applies to targets: Aetherflow, エーテルフロー, duration 0, param 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 10
  { 166, { 0, 0, 0, 0, 0, 0, 0, 304, 0, 0, 4, 0, 10 } },

  //Lustrate, 生命活性法
  //has heal: potency 600
  { 189, { 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Art of War, 破陣法
  //has damage: potency 160, combo potency 0, directional potency 0
  { 16539, { 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sacred Soil, 野戦治療の陣
  //applies to self: Sacred Soil, 野戦治療の陣, duration 15000, param 0
  //applies to targets: Sacred Soil, 野戦治療の陣：効果, duration 5000, param 0
  { 188, { 0, 0, 0, 0, 1944, 15000, 0, 299, 5000, 0, 0, 0, 0 } },

  //Indomitability, 不撓不屈の策
  //has heal: potency 400
  { 3583, { 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Broil, 気炎法
  //has damage: potency 240, combo potency 0, directional potency 0
  { 3584, { 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Deployment Tactics, 展開戦術
  { 3585, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Emergency Tactics, 応急戦術
  //applies to self: Emergency Tactics, 応急戦術, duration 15000, param 0
  { 3586, { 0, 0, 0, 0, 792, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Dissipation, 転化
  //applies to self: Dissipation, 転化, duration 30000, param 0
  { 3587, { 0, 0, 0, 0, 791, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Excogitation, 深謀遠慮の策
  //applies to targets: Excogitation, 深謀遠慮の策, duration 0, param 0
  { 7434, { 0, 0, 0, 0, 0, 0, 0, 1220, 0, 0, 0, 0, 0 } },

  //Broil II, 魔炎法
  //has damage: potency 260, combo potency 0, directional potency 0
  { 7435, { 260, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Chain Stratagem, 連環計
  //applies to targets: Chain Stratagem, 連環計, duration 15000, param 0
  { 7436, { 0, 0, 0, 0, 0, 0, 0, 1221, 15000, 0, 0, 0, 0 } },

  //Aetherpact, エーテルパクト
  { 7437, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Dissolve Union, フェイユニオン解除
  { 7869, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Biolysis, 蠱毒法
  //applies to targets: Biolysis, 蠱毒法, duration 30000, param 0
  { 16540, { 0, 0, 0, 0, 0, 0, 0, 1895, 30000, 0, 0, 0, 0 } },

  //Broil III, 死炎法
  //has damage: potency 280, combo potency 0, directional potency 0
  { 16541, { 280, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Recitation, 秘策
  //applies to self: Recitation, 秘策, duration 15000, param 0
  { 16542, { 0, 0, 0, 0, 1896, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Fey Blessing, フェイブレッシング
  { 16543, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Summon Seraph, サモン・セラフィム
  { 16545, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Consolation, コンソレイション
  { 16546, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Embrace, 光の癒し
  //has heal: potency 150
  { 802, { 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Whispering Dawn, 光の囁き
  //applies to targets: Whispering Dawn, 光の囁き, duration 21000, param 0
  { 803, { 0, 0, 0, 0, 0, 0, 0, 315, 21000, 0, 0, 0, 0 } },

  //Fey Illumination, フェイイルミネーション
  //applies to targets: Fey Illumination, フェイイルミネーション, duration 20000, param 0
  { 805, { 0, 0, 0, 0, 0, 0, 0, 317, 20000, 0, 0, 0, 0 } },

  //Fey Union, フェイユニオン
  //applies to targets: Fey Union, フェイユニオン［被］, duration 60000, param 0
  { 7438, { 0, 0, 0, 0, 0, 0, 0, 1223, 60000, 0, 0, 0, 0 } },

  //Fey Blessing, フェイブレッシング
  //has heal: potency 350
  { 16544, { 0, 0, 0, 350, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Seraphic Veil, セラフィックヴェール
  //has heal: potency 200
  //applies to targets: Seraphic Veil, セラフィックヴェール, duration 30000, param 0
  { 16548, { 0, 0, 0, 200, 0, 0, 0, 1917, 30000, 0, 0, 0, 0 } },

  //Angel's Whisper, 光輝の囁き
  //applies to targets: Angel's Whisper, 光輝の囁き, duration 21000, param 0
  { 16550, { 0, 0, 0, 0, 0, 0, 0, 1874, 21000, 0, 0, 0, 0 } },

  //Seraphic Illumination, セラフィックイルミネーション
  //applies to targets: Seraphic Illumination, セラフィックイルミネーション, duration 20000, param 0
  { 16551, { 0, 0, 0, 0, 0, 0, 0, 1875, 20000, 0, 0, 0, 0 } },

  //Consolation, コンソレイション
  //has heal: potency 300
  //applies to targets: Seraphic Veil, セラフィックヴェール, duration 30000, param 0
  { 16547, { 0, 0, 0, 300, 0, 0, 0, 1917, 30000, 0, 0, 0, 0 } },

  //Malefic, マレフィク
  //has damage: potency 150, combo potency 0, directional potency 0
  { 3596, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Benefic, ベネフィク
  //has heal: potency 400
  //applies to self: Enhanced Benefic II, ベネフィラ効果アップ, duration 0, param 0
  { 3594, { 0, 0, 0, 400, 815, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Combust, コンバス
  //applies to targets: Combust, コンバス, duration 18000, param 0
  { 3599, { 0, 0, 0, 0, 0, 0, 0, 838, 18000, 0, 0, 0, 0 } },

  //Lightspeed, ライトスピード
  //applies to self: Lightspeed, ライトスピード, duration 15000, param 0
  { 3606, { 0, 0, 0, 0, 841, 15000, 0, 0, 0, 0, 0, 0, 0 } },

  //Helios, ヘリオス
  //has heal: potency 330
  { 3600, { 0, 0, 0, 330, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ascend, アセンド
  //applies to targets: Raise, 蘇生, duration 1000, param 0
  { 3603, { 0, 0, 0, 0, 0, 0, 0, 148, 1000, 0, 0, 0, 0 } },

  //Essential Dignity, ディグニティ
  { 3614, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Benefic II, ベネフィラ
  //has heal: potency 700
  { 3610, { 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Draw, ドロー
  //applies to self: Spire Drawn, ドロー：ビエルゴの塔, duration 30000, param 0
  { 3590, { 0, 0, 0, 0, 918, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Diurnal Sect, ダイアーナルセクト
  //applies to targets: Diurnal Sect, ダイアーナルセクト, duration 0, param 0
  { 3604, { 0, 0, 0, 0, 0, 0, 0, 839, 0, 0, 0, 0, 0 } },

  //Undraw, アルカナ破棄
  { 9629, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aspected Benefic, アスペクト・ベネフィク
  //has heal: potency 200
  //applies to self: Diurnal Balance, ニュートラルセクト［日］, duration 30000, param 0
  //applies to targets: Nocturnal Balance, ニュートラルセクト［夜］, duration 30000, param 0
  { 3595, { 0, 0, 0, 200, 1920, 30000, 0, 1921, 30000, 0, 0, 0, 0 } },

  //Aspected Benefic, アスペクト・ベネフィク
  //has heal: potency 200
  //applies to targets: Nocturnal Field, ノクターナルフィールド, duration 30000, param 0
  { 17151, { 0, 0, 0, 200, 0, 0, 0, 837, 30000, 0, 0, 0, 0 } },

  //Redraw, リドロー
  { 3593, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aspected Helios, アスペクト・ヘリオス
  //has heal: potency 200
  //applies to self: Diurnal Balance, ニュートラルセクト［日］, duration 30000, param 0
  //applies to targets: Nocturnal Balance, ニュートラルセクト［夜］, duration 30000, param 0
  { 3601, { 0, 0, 0, 200, 1920, 30000, 0, 1921, 30000, 0, 0, 0, 0 } },

  //Aspected Helios, アスペクト・ヘリオス
  //has heal: potency 200
  //applies to self: Horoscope Helios, ホロスコープ・ヘリオス, duration 30000, param 0
  //applies to targets: Nocturnal Balance, ニュートラルセクト［夜］, duration 30000, param 0
  { 17152, { 0, 0, 0, 200, 1891, 30000, 0, 1921, 30000, 0, 0, 0, 0 } },

  //Gravity, グラビデ
  //has damage: potency 140, combo potency 0, directional potency 0
  { 3615, { 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Combust II, コンバラ
  //applies to targets: Combust II, コンバラ, duration 30000, param 0
  { 3608, { 0, 0, 0, 0, 0, 0, 0, 843, 30000, 0, 0, 0, 0 } },

  //Nocturnal Sect, ノクターナルセクト
  { 3605, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Synastry, シナストリー
  //applies to self: Synastry, シナストリー, duration 0, param 0
  //applies to targets: Synastry, シナストリー［被］, duration 0, param 0
  { 3612, { 0, 0, 0, 0, 845, 0, 0, 846, 0, 0, 0, 0, 0 } },

  //Minor Arcana, マイナーアルカナ
  { 7443, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Divination, ディヴィネーション
  //applies to targets: Divination, ディヴィネーション, duration 15000, param 0
  { 16552, { 0, 0, 0, 0, 0, 0, 0, 1878, 15000, 0, 0, 0, 0 } },

  //Malefic II, マレフィラ
  //has damage: potency 170, combo potency 0, directional potency 0
  { 3598, { 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Collective Unconscious, 運命の輪
  //applies to self: Collective Unconscious, 運命の輪, duration 18000, param 0
  //applies to targets: Wheel of Fortune, 運命の輪, duration 15000, param 0
  { 3613, { 0, 0, 0, 0, 848, 18000, 0, 956, 15000, 0, 0, 0, 0 } },

  //Celestial Opposition, 星天対抗
  //applies to targets: Nocturnal Opposition, 星天対抗［夜］, duration 30000, param 0
  { 16553, { 0, 0, 0, 0, 0, 0, 0, 1880, 30000, 0, 0, 0, 0 } },

  //Earthly Star, アーサリースター
  //applies to self: Earthly Dominance, 星の支配者, duration 10000, param 0
  { 7439, { 0, 0, 0, 0, 1224, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Stellar Detonation, ステラデトネーション
  //has damage: potency 150, combo potency 0, directional potency 0
  //has heal: potency 540
  { 8324, { 150, 0, 0, 540, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Malefic III, マレフィガ
  //has damage: potency 210, combo potency 0, directional potency 0
  { 7442, { 210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sleeve Draw, スリーヴドロー
  //applies to self: Sleeve Draw, スリーヴドロー, duration 30000, param 0
  { 7448, { 0, 0, 0, 0, 1926, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Combust III, コンバガ
  //applies to targets: Combust III, コンバガ, duration 30000, param 0
  { 16554, { 0, 0, 0, 0, 0, 0, 0, 1881, 30000, 0, 0, 0, 0 } },

  //Malefic IV, マレフィジャ
  //has damage: potency 250, combo potency 0, directional potency 0
  { 16555, { 250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Celestial Intersection, 星天交差
  //has heal: potency 200
  //applies to targets: Nocturnal Intersection, 星天交差［夜］, duration 30000, param 0
  { 16556, { 0, 0, 0, 200, 0, 0, 0, 1889, 30000, 0, 0, 0, 0 } },

  //Horoscope, ホロスコープ
  //applies to targets: Horoscope, ホロスコープ, duration 10000, param 0
  { 16558, { 0, 0, 0, 0, 0, 0, 0, 1890, 10000, 0, 0, 0, 0 } },

  //Neutral Sect, ニュートラルセクト
  //applies to self: Neutral Sect, ニュートラルセクト, duration 20000, param 0
  { 16559, { 0, 0, 0, 0, 1892, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //the Balance, アーゼマの均衡
  //applies to targets: The Balance, アーゼマの均衡, duration 15000, param 0
  { 4419, { 0, 0, 0, 0, 0, 0, 0, 1882, 15000, 0, 0, 0, 0 } },

  //the Spear, ハルオーネの槍
  //applies to targets: The Arrow, オシュオンの矢, duration 15000, param 0
  { 4403, { 0, 0, 0, 0, 0, 0, 0, 1884, 15000, 0, 0, 0, 0 } },

  //the Spear, ハルオーネの槍
  //applies to targets: The Spear, ハルオーネの槍, duration 15000, param 0
  { 4422, { 0, 0, 0, 0, 0, 0, 0, 1885, 15000, 0, 0, 0, 0 } },

  //the Arrow, オシュオンの矢
  //applies to targets: The Bole, 世界樹の幹, duration 15000, param 0
  { 4402, { 0, 0, 0, 0, 0, 0, 0, 1883, 15000, 0, 0, 0, 0 } },

  //the Ewer, サリャクの水瓶
  //applies to targets: The Ewer, サリャクの水瓶, duration 15000, param 0
  { 4405, { 0, 0, 0, 0, 0, 0, 0, 1886, 15000, 0, 0, 0, 0 } },

  //the Spire, ビエルゴの塔
  //applies to targets: The Spire, ビエルゴの塔, duration 15000, param 0
  { 4406, { 0, 0, 0, 0, 0, 0, 0, 1887, 15000, 0, 0, 0, 0 } },

  //Lord of Crowns, クラウンロード
  //applies to targets: Lord of Crowns, クラウンロード, duration 15000, param 0
  { 7444, { 0, 0, 0, 0, 0, 0, 0, 1876, 15000, 0, 0, 0, 0 } },

  //Lady of Crowns, クラウンレディ
  //applies to targets: Lady of Crowns, クラウンレディ, duration 15000, param 0
  { 7445, { 0, 0, 0, 0, 0, 0, 0, 1877, 15000, 0, 0, 0, 0 } },

  //Water Cannon, 水鉄砲
  //has damage: potency 120, combo potency 0, directional potency 0
  { 11385, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Off-guard, ガードオファ
  //applies to targets: Off-guard, ガードオファ, duration 30000, param 0
  { 11411, { 0, 0, 0, 0, 0, 0, 0, 1717, 30000, 0, 0, 0, 0 } },

  //Bomb Toss, 爆弾投げ
  //has damage: potency 110, combo potency 0, directional potency 0
  { 11396, { 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Blood Drain, 吸血
  //has damage: potency 20, combo potency 0, directional potency 0
  { 11395, { 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Faze, 猫だまし
  //applies to targets: Pacification, ＷＳ不可, duration 0, param 0
  { 11403, { 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0 } },

  //Ice Spikes, アイススパイク
  //applies to targets: Ice Spikes, アイススパイク, duration 0, param 0
  { 11418, { 0, 0, 0, 0, 0, 0, 0, 1720, 0, 0, 0, 0, 0 } },

  //Self-destruct, 自爆
  //has damage: potency 900, combo potency 0, directional potency 0
  { 11408, { 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Final Sting, ファイナルスピア
  //has damage: potency 1500, combo potency 0, directional potency 0
  { 11407, { 1500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Acorn Bomb, どんぐり爆弾
  { 11392, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bristle, 怒髪天
  //applies to targets: Boost, 力溜め, duration 0, param 0
  { 11393, { 0, 0, 0, 0, 0, 0, 0, 1716, 0, 0, 0, 0, 0 } },

  //Sticky Tongue, スティッキータン
  { 11412, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Toad Oil, ガマの脂
  { 11410, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //1000 Needles, 針千本
  { 11397, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Flying Sardine, フライングサーディン
  //has damage: potency 10, combo potency 0, directional potency 0
  { 11423, { 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bad Breath, 臭い息
  { 11388, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Peculiar Light, 不思議な光
  //applies to targets: Peculiar Light, 不思議な光, duration 10000, param 0
  { 11421, { 0, 0, 0, 0, 0, 0, 0, 1721, 10000, 0, 0, 0, 0 } },

  //Drill Cannons, ドリルキャノン
  //has damage: potency 120, combo potency 0, directional potency 0
  { 11398, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Plaincracker, プレーンクラッカー
  //has damage: potency 130, combo potency 0, directional potency 0
  { 11391, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //White Wind, ホワイトウィンド
  { 11406, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mighty Guard, マイティガード
  //applies to self: Mighty Guard, マイティガード, duration 0, param 0
  { 11417, { 0, 0, 0, 0, 1719, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Transfusion, 融合
  { 11409, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Loom, ルーム
  { 11401, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mind Blast, マインドブラスト
  //has damage: potency 100, combo potency 0, directional potency 0
  { 11394, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Level 5 Petrify, レベル5石化
  { 11414, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //the Dragon's Voice, 雷電の咆哮
  //has damage: potency 110, combo potency 0, directional potency 0
  { 11420, { 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //the Ram's Voice, 氷結の咆哮
  //has damage: potency 130, combo potency 0, directional potency 0
  { 11419, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Glower, グラワー
  //has damage: potency 130, combo potency 0, directional potency 0
  { 11404, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Flying Frenzy, 狂乱
  //has damage: potency 80, combo potency 0, directional potency 0
  { 11389, { 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Song of Torment, 苦悶の歌
  //has damage: potency 50, combo potency 0, directional potency 0
  //applies to targets: Bleeding, ペイン, duration 30000, param 0
  { 11386, { 50, 0, 0, 0, 0, 0, 0, 1714, 30000, 0, 0, 0, 0 } },

  //Sharpened Knife, とぎたて
  { 11400, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //the Look, 怪視線
  //has damage: potency 130, combo potency 0, directional potency 0
  { 11399, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Doom, 死の宣告
  //applies to targets: Doom, 死の宣告, duration 0, param 0
  { 11416, { 0, 0, 0, 0, 0, 0, 0, 1738, 0, 0, 0, 0, 0 } },

  //Moon Flute, 月の笛
  //applies to targets: Waxing Nocturne, 狂戦士化, duration 0, param 0
  { 11415, { 0, 0, 0, 0, 0, 0, 0, 1718, 0, 0, 0, 0, 0 } },

  //Flame Thrower, 火炎放射
  //has damage: potency 130, combo potency 0, directional potency 0
  { 11402, { 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Feather Rain, フェザーレイン
  //has damage: potency 180, combo potency 0, directional potency 0
  //applies to targets: Windburn, 裂傷, duration 6000, param 0
  { 11426, { 180, 0, 0, 0, 0, 0, 0, 1723, 6000, 0, 0, 0, 0 } },

  //Eruption, エラプション
  //has damage: potency 220, combo potency 0, directional potency 0
  { 11427, { 220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mountain Buster, マウンテンバスター
  { 11428, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Diamondback, 超硬化
  //applies to targets: Diamondback, 超硬化, duration 0, param 0
  { 11424, { 0, 0, 0, 0, 0, 0, 0, 1722, 0, 0, 0, 0, 0 } },

  //High Voltage, 高圧電流
  //has damage: potency 90, combo potency 0, directional potency 0
  { 11387, { 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //4-tonze Weight, 4トンズ
  //has damage: potency 110, combo potency 0, directional potency 0
  { 11384, { 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ink Jet, インクジェット
  //has damage: potency 120, combo potency 0, directional potency 0
  { 11422, { 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Snort, 鼻息
  { 11383, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Tail Screw, テールスクリュー
  { 11413, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Veil of the Whorl, 水神のヴェール
  //applies to targets: Veil of the Whorl, 水神のヴェール, duration 0, param 0
  { 11431, { 0, 0, 0, 0, 0, 0, 0, 1724, 0, 0, 0, 0, 0 } },

  //Shock Strike, ショックストライク
  { 11429, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Fire Angon, ファイアアンゴン
  //has damage: potency 100, combo potency 0, directional potency 0
  { 11425, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Missile, ミサイル
  { 11405, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Glass Dance, 氷雪乱舞
  { 11430, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Rampart, ランパート
  //applies to targets: Rampart, ランパート, duration 20000, param 0
  { 7531, { 0, 0, 0, 0, 0, 0, 0, 1191, 20000, 0, 0, 0, 0 } },

  //Low Blow, ロウブロウ
  { 7540, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Provoke, 挑発
  //has enmity: increase
  { 7533, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Interject, インタージェクト
  { 7538, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Reprisal, リプライザル
  //applies to targets: Reprisal, リプライザル, duration 10000, param 0
  { 7535, { 0, 0, 0, 0, 0, 0, 0, 1193, 10000, 0, 0, 0, 0 } },

  //Shirk, シャーク
  { 7537, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Second Wind, 内丹
  //has bonus effect: SelfHeal, 500
  { 7541, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 500 } },

  //Leg Sweep, レッグスウィープ
  //applies to targets: Stun, スタン, duration 4000, param 0
  { 7863, { 0, 0, 0, 0, 0, 0, 0, 2, 4000, 0, 0, 0, 0 } },

  //Bloodbath, ブラッドバス
  //applies to self: Bloodbath, ブラッドバス, duration 20000, param 0
  { 7542, { 0, 0, 0, 0, 84, 20000, 0, 0, 0, 0, 0, 0, 0 } },

  //Feint, 牽制
  //applies to targets: Feint, 牽制, duration 10000, param 0
  { 7549, { 0, 0, 0, 0, 0, 0, 0, 1195, 10000, 0, 0, 0, 0 } },

  //Arm's Length, アームズレングス
  //applies to self: Arm's Length, アームズレングス, duration 6000, param 0
  { 7548, { 0, 0, 0, 0, 1209, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //True North, トゥルーノース
  //applies to self: True North, トゥルーノース, duration 10000, param 0
  { 7546, { 0, 0, 0, 0, 1250, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Leg Graze, レッググレイズ
  //applies to targets: Heavy, ヘヴィ, duration 10000, param 0
  { 7554, { 0, 0, 0, 0, 0, 0, 0, 14, 10000, 0, 0, 0, 0 } },

  //Foot Graze, フットグレイズ
  { 7553, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Peloton, プロトン
  //applies to targets: Peloton, プロトン, duration 30000, param 0
  { 7557, { 0, 0, 0, 0, 0, 0, 0, 1199, 30000, 0, 0, 0, 0 } },

  //Head Graze, ヘッドグレイズ
  { 7551, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Addle, アドル
  { 7560, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Esuna, エスナ
  { 7568, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Swiftcast, 迅速魔
  //applies to self: Swiftcast, 迅速魔, duration 10000, param 0
  { 7561, { 0, 0, 0, 0, 167, 10000, 0, 0, 0, 0, 0, 0, 0 } },

  //Lucid Dreaming, ルーシッドドリーム
  //applies to targets: Lucid Dreaming, ルーシッドドリーム, duration 21000, param 0
  { 7562, { 0, 0, 0, 0, 0, 0, 0, 1204, 21000, 0, 0, 0, 0 } },

  //Surecast, 堅実魔
  //applies to self: Surecast, 堅実魔, duration 6000, param 0
  { 7559, { 0, 0, 0, 0, 160, 6000, 0, 0, 0, 0, 0, 0, 0 } },

  //Rescue, 救出
  { 7571, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Slash, チョコスラッシュ
  //has damage: potency 150, combo potency 0, directional potency 0
  { 824, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Beak, チョコビーク
  //has damage: potency 130, combo potency 0, directional potency 0
  //applies to targets: Choco Beak, チョコビーク, duration 18000, param 0
  { 823, { 130, 0, 0, 0, 0, 0, 0, 236, 18000, 0, 0, 0, 0 } },

  //Choco Rush, チョコラッシュ
  //has damage: potency 130, combo potency 0, directional potency 0
  //applies to targets: Stun, スタン, duration 0, param 0
  { 822, { 130, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 } },

  //Choco Blast, チョコブラスト
  //has damage: potency 170, combo potency 0, directional potency 0
  { 821, { 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Drop, チョコドロップ
  //has damage: potency 150, combo potency 0, directional potency 0
  //has enmity: increase
  { 820, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Kick, チョコキック
  //has damage: potency 130, combo potency 0, directional potency 0
  //applies to targets: Slow, スロウ, duration 12000, param 0
  { 819, { 130, 0, 0, 0, 0, 0, 0, 9, 12000, 0, 0, 0, 0 } },

  //Choco Guard, チョコガード
  { 818, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Strike, チョコストライク
  //has damage: potency 150, combo potency 0, directional potency 0
  //has enmity: increase
  { 817, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Medica, チョコメディカ
  //has heal: potency 150
  { 825, { 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Surge, チョコサージ
  //applies to self: Choco Surge, チョコサージ, duration 30000, param 0
  { 826, { 0, 0, 0, 0, 238, 30000, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Cure, チョコケアル
  //has heal: potency 300
  { 827, { 0, 0, 0, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Choco Regen, チョコリジェネ
  //applies to targets: Choco Regen, チョコリジェネ, duration 18000, param 0
  { 828, { 0, 0, 0, 0, 0, 0, 0, 237, 18000, 0, 0, 0, 0 } },

  //Aether Mortar, エーテルモーター
  { 2892, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Volley Fire, ボレーファイア
  //has damage: potency 80, combo potency 0, directional potency 0
  { 2891, { 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Charged Aether Mortar, チャージドモーター
  //applies to targets: Vulnerability Up, 被ダメージ上昇, duration 10000, param 0
  { 3589, { 0, 0, 0, 0, 0, 0, 0, 1208, 10000, 0, 0, 0, 0 } },

  //Charged Volley Fire, チャージドファイア
  //applies to targets: Vulnerability Up, 被ダメージ上昇, duration 10000, param 0
  { 3588, { 0, 0, 0, 0, 0, 0, 0, 1208, 10000, 0, 0, 0, 0 } },

  //Stellar Burst, ステラバースト
  { 7440, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Stellar Explosion, ステラエクスプロージョン
  { 7441, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Logos Action, ロゴスアクション
  { 12870, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Focus L, ロゴス・チャージ
  //applies to targets: Boost, 力溜め, duration 0, param 0
  { 12972, { 0, 0, 0, 0, 0, 0, 0, 1656, 0, 0, 0, 0, 0 } },

  //Magic Burst L, ロゴス・マジックバースト
  //applies to targets: Magic Burst L, ロゴス・マジックバースト, duration 0, param 0
  { 13005, { 0, 0, 0, 0, 0, 0, 0, 1652, 0, 0, 0, 0, 0 } },

  //Bravery L, ロゴス・ブレイブ
  //applies to targets: Bravery L, ロゴス・ブレイブ, duration 0, param 0
  { 12997, { 0, 0, 0, 0, 0, 0, 0, 1646, 0, 0, 0, 0, 0 } },

  //Double Edge L, ロゴス・ダブルエッジ
  //applies to targets: Double Edge L, ロゴス・ダブルエッジ, duration 0, param 0
  { 13006, { 0, 0, 0, 0, 0, 0, 0, 1653, 0, 0, 0, 0, 0 } },

  //Wisdom of the Aetherweaver, 術士の記憶
  //applies to targets: Wisdom of the Aetherweaver, 術士の記憶, duration 0, param 0
  { 12958, { 0, 0, 0, 0, 0, 0, 0, 1631, 0, 0, 0, 0, 0 } },

  //Wisdom of the Martialist, 闘士の記憶
  //applies to targets: Wisdom of the Martialist, 闘士の記憶, duration 0, param 0
  { 12959, { 0, 0, 0, 0, 0, 0, 0, 1632, 0, 0, 0, 0, 0 } },

  //Wisdom of the Skirmisher, 武人の記憶
  //applies to targets: Wisdom of the Skirmisher, 武人の記憶, duration 0, param 0
  { 12963, { 0, 0, 0, 0, 0, 0, 0, 1636, 0, 0, 0, 0, 0 } },

  //Wisdom of the Watcher, 斥候の記憶
  //applies to targets: Wisdom of the Watcher, 斥候の記憶, duration 0, param 0
  { 12964, { 0, 0, 0, 0, 0, 0, 0, 1637, 0, 0, 0, 0, 0 } },

  //Wisdom of the Templar, 聖騎士の記憶
  //applies to targets: Wisdom of the Templar, 聖騎士の記憶, duration 0, param 0
  { 12965, { 0, 0, 0, 0, 0, 0, 0, 1638, 0, 0, 0, 0, 0 } },

  //Wisdom of the Duelist, 剣豪の記憶
  //applies to targets: Wisdom of the Duelist, 剣豪の記憶, duration 0, param 0
  { 14478, { 0, 0, 0, 0, 0, 0, 0, 1740, 0, 0, 0, 0, 0 } },

  //Wisdom of the Elder, 賢者の記憶
  //applies to targets: Wisdom of the Elder, 賢者の記憶, duration 0, param 0
  { 14477, { 0, 0, 0, 0, 0, 0, 0, 1739, 0, 0, 0, 0, 0 } },

  //Wisdom of the Fiendhunter, 弓聖の記憶
  //applies to targets: Wisdom of the Fiendhunter, 弓聖の記憶, duration 0, param 0
  { 14479, { 0, 0, 0, 0, 0, 0, 0, 1741, 0, 0, 0, 0, 0 } },

  //Braver, ブレイバー
  { 200, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bladedance, ブレードダンス
  { 201, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Final Heaven, ファイナルヘヴン
  { 202, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Skyshard, スカイシャード
  { 203, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Starstorm, プチメテオ
  { 204, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Meteor, メテオ
  { 205, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Healing Wind, 癒しの風
  //has powerheal: 
  { 206, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Breath of the Earth, 大地の息吹
  //has powerheal: 
  { 207, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Pulse of Life, 生命の鼓動
  //has powerheal: 
  { 208, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shield Wall, シールドウォール
  { 197, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Stronghold, ストロングホールド
  { 198, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Last Bastion, ラストバスティオン
  //applies to targets: Last Bastion, ラストバスティオン, duration 12000, param 0
  { 199, { 0, 0, 0, 0, 0, 0, 0, 196, 12000, 0, 0, 0, 0 } },

  //Land Waker, 原初の大地
  //applies to targets: Land Waker, 原初の大地, duration 12000, param 0
  { 4240, { 0, 0, 0, 0, 0, 0, 0, 863, 12000, 0, 0, 0, 0 } },

  //Dark Force, ダークフォース
  //applies to targets: Dark Force, ダークフォース, duration 12000, param 0
  { 4241, { 0, 0, 0, 0, 0, 0, 0, 864, 12000, 0, 0, 0, 0 } },

  //Dragonsong Dive, 蒼天のドラゴンダイブ
  { 4242, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Chimatsuri, 月遁血祭
  { 4243, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Desperado, デスペラード
  { 4239, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Big Shot, ビッグショット
  { 4238, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Satellite Beam, サテライトビーム
  { 4245, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sagittarius Arrow, サジタリウスアロー
  { 4244, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Teraflare, テラフレア
  { 4246, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Angel Feathers, エンジェルフェザー
  //has powerheal: 
  { 4247, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Astral Stasis, 星天開門
  //has powerheal: 
  { 4248, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Doom of the Living, 生者必滅
  { 7861, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Vermilion Scourge, ヴァーミリオンスカージ
  { 7862, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Crimson Lotus, クリムゾンロータス
  { 17106, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Gunmetal Soul, ソウルガンメタル
  //applies to targets: Gunmetal Soul, ソウルガンメタル, duration 0, param 0
  { 17105, { 0, 0, 0, 0, 0, 0, 0, 1931, 0, 0, 0, 0, 0 } },

  //Digest, 消化
  { 724, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Lunatic Voice, ルナティックボイス
  { 1485, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Putrid Cloud, 不浄な瘴気
  { 1659, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Immortalize, 怒りの咆吼
  { 694, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bravery, ブレイブ
  //applies to self: Damage Up, ダメージ上昇, duration 60000, param 0
  { 1836, { 0, 0, 0, 0, 263, 60000, 0, 0, 0, 0, 0, 0, 0 } },

  //Infernal Fetters, 炎獄の鎖
  //applies to targets: Infernal Fetters, 炎獄の鎖, duration 0, param 0
  { 1534, { 0, 0, 0, 0, 0, 0, 0, 377, 0, 0, 0, 0, 0 } },

  //Death Sentence, デスセンテンス
  //applies to targets: Infirmity, 虚弱, duration 0, param 0
  { 1242, { 0, 0, 0, 0, 0, 0, 0, 172, 0, 0, 0, 0, 0 } },

  //Disseminate, ディスセミネイト
  //applies to targets: Disseminate, ディスセミネイト, duration 40000, param 0
  { 1212, { 0, 0, 0, 0, 0, 0, 0, 348, 40000, 0, 0, 0, 0 } },

  //Blood Sword, ブラッドソード
  { 1610, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Pom Cure, ポンポンケアル
  { 2058, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ripe Banana, バナナ喰い
  //applies to targets: Damage Up, ダメージ上昇, duration 60000, param 0
  { 2204, { 0, 0, 0, 0, 0, 0, 0, 443, 60000, 0, 0, 0, 0 } },

  //Aura Curtain, オーラカーテン
  //applies to targets: Reflect, リフレク, duration 0, param 0
  { 2438, { 0, 0, 0, 0, 0, 0, 0, 518, 0, 0, 0, 0, 0 } },

  //Lunar Dynamo, ルナダイナモ
  { 2010, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Mantle of the Whorl, 水神のマント
  //applies to self: Mantle of the Whorl, 水神のマント, duration 0, param 0
  { 2164, { 0, 0, 0, 0, 477, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Veil of the Whorl, 水神のヴェール
  //applies to self: Veil of the Whorl, 水神のヴェール, duration 0, param 0
  { 2165, { 0, 0, 0, 0, 478, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Drain, ドレイン
  { 2339, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Head over Heels, 首っ丈
  { 2404, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Lunar Dynamo, ルナダイナモ
  { 2559, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Frost Blade, 凍てつく剣
  //applies to self: Frost Blade, 凍てつく剣, duration 0, param 0
  { 2451, { 0, 0, 0, 0, 526, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Bluefire, 青碧の炎
  //applies to targets: Bluefire, 青碧の炎, duration 0, param 0
  { 2961, { 0, 0, 0, 0, 0, 0, 0, 591, 0, 0, 0, 0, 0 } },

  //Mini, ミニマム
  //applies to targets: Minimum, ミニマム, duration 0, param 0
  { 3249, { 0, 0, 0, 0, 0, 0, 0, 438, 0, 0, 0, 0, 0 } },

  //Mini, ミニマム
  //applies to targets: Minimum, ミニマム, duration 60000, param 0
  { 2371, { 0, 0, 0, 0, 0, 0, 0, 438, 60000, 0, 0, 0, 0 } },

  //Marrow Drain, マロードレイン
  { 3342, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Aetherial Distribution, エーテル分配
  { 3419, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Ice Spikes, アイススパイク
  //applies to targets: Ice Spikes, アイススパイク, duration 0, param 0
  { 859, { 0, 0, 0, 0, 0, 0, 0, 198, 0, 0, 0, 0, 0 } },

  //Bang Toss, 音響爆弾
  //applies to targets: Blaze Spikes, ブレイズスパイク, duration 0, param 0
  { 990, { 0, 0, 0, 0, 0, 0, 0, 197, 0, 0, 0, 0, 0 } },

  //Sanguine Bite, サングインバイト
  { 5068, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Soul Drain, ソウルドレイン
  { 342, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Guzzle, ガブ飲み
  //applies to targets: Bigbulge Biggerbrain, マッチョサイエンティスト, duration 60000, param 0
  { 5528, { 0, 0, 0, 0, 0, 0, 0, 1003, 60000, 0, 0, 0, 0 } },

  //Retribution, 懲罰
  //applies to targets: Vulnerability Up, 被ダメージ上昇, duration 0, param 0
  { 5940, { 0, 0, 0, 0, 0, 0, 0, 202, 0, 0, 0, 0, 0 } },

  //Seed of the Sky, シード・オブ・スカイ
  //applies to targets: Damage Down, ダメージ低下, duration 65000, param 0
  { 5937, { 0, 0, 0, 0, 0, 0, 0, 1016, 65000, 0, 0, 0, 0 } },

  //Reset, 初期化
  //applies to targets: Damage Down, ダメージ低下, duration 30000, param 0
  { 13738, { 0, 0, 0, 0, 0, 0, 0, 1016, 30000, 0, 0, 0, 0 } },

  //Critical Storage Violation, 記憶汚染爆発S
  //applies to targets: Damage Down, ダメージ低下, duration 30000, param 0
  { 12921, { 0, 0, 0, 0, 0, 0, 0, 1016, 30000, 0, 0, 0, 0 } },

  //Scorpion Avatar, 光焔の化身
  //applies to targets: Offensive Optimization, 攻撃形態, duration 0, param 0
  { 3713, { 0, 0, 0, 0, 0, 0, 0, 681, 0, 0, 0, 0, 0 } },

  //Dragonfly Avatar, 武辺の化身
  { 3712, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Beetle Avatar, 甲殻の化身
  //applies to targets: Defensive Optimization, 防御形態, duration 0, param 0
  { 3714, { 0, 0, 0, 0, 0, 0, 0, 682, 0, 0, 0, 0, 0 } },

  //Warlord Shell, 武神甲
  //applies to targets: Blessing of Earth, 土の加護, duration 0, param 0
  { 3761, { 0, 0, 0, 0, 0, 0, 0, 683, 0, 0, 0, 0, 0 } },

  //Brainhurt Breakblock, ブレインブレイクブロック
  //applies to targets: Magic Vulnerability Down, 被魔法ダメージ軽減, duration 0, param 0
  { 4903, { 0, 0, 0, 0, 0, 0, 0, 812, 0, 0, 0, 0, 0 } },

  //Meltyspume, 強酸弾
  //applies to targets: Vulnerability Up, 被ダメージ上昇, duration 0, param 0
  { 4908, { 0, 0, 0, 0, 0, 0, 0, 714, 0, 0, 0, 0, 0 } },

  //Brainshaker, ブレインシェーカー
  //applies to targets: Healing Potency Down, 魔法回復力ダウン, duration 0, param 0
  { 5071, { 0, 0, 0, 0, 0, 0, 0, 933, 0, 0, 0, 0, 0 } },

  //Explosion, 爆発
  //applies to targets: Fire Resistance Down, 火属性耐性低下, duration 0, param 0
  { 4060, { 0, 0, 0, 0, 0, 0, 0, 670, 0, 0, 0, 0, 0 } },

  //Bloodstain, ブラッドステイン
  { 4747, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Sprint, スプリント
  //applies to self: Sprint, スプリント, duration 10000, param 30
  { 3, { 0, 0, 0, 0, 50, 10000, 30, 0, 0, 0, 0, 0, 0 } },

  //Teleport, テレポ
  { 5, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Energy Drain, エナジードレイン
  //has damage: potency 150, combo potency 0, directional potency 0
  //has powerheal: 
  //has bonus effect: GainMPPercentage, 5
  { 167, { 150, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 5 } },

  //Hagakure, 葉隠
  { 7495, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //attack, 攻撃
  //has damage: potency 110, combo potency 0, directional potency 0
  { 7, { 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Shot, ショット
  //has damage: potency 100, combo potency 0, directional potency 0
  { 8, { 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },

  //Flood of Shadow, 漆黒の波動
  //has damage: potency 300, combo potency 0, directional potency 0
  //has bonus effect: GainJobTimer, 2127152
  { 16469, { 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 2127152 } },

};

ActionLut::StatusEffectTable ActionLut::m_statusEffectTable =
{
  //Fight or Flight, ファイト・オア・フライト: DamageMultiplier, Physical, 25%
  { 76, { 1, 1, 25, 0, 0 } },

  //Sentinel, センチネル: DamageReceiveMultiplier, All, -30%
  { 74, { 2, 255, -30, 0, 0 } },
  //more than 1 effect is found
  //Sentinel, センチネル: DamageReceiveMultiplier, All, -30%
  //{ 74, { 2, 255, -30, 0, 0 } },

  //Circle of Scorn, サークル・オブ・ドゥーム: Dot, Physical, potency 35
  { 248, { 4, 1, 35, 0, 0 } },

  //Goring Blade, ゴアブレード: Dot, Physical, potency 85
  { 725, { 4, 1, 85, 0, 0 } },

  //Requiescat, レクイエスカット: DamageMultiplier, Magical, 50%
  { 1368, { 1, 2, 50, 0, 0 } },

  //Vengeance, ヴェンジェンス: DamageReceiveTrigger, ReflectDamage, Physical, potency 55
  { 89, { 8, 1, 55, 1, 0 } },
  //more than 1 effect is found
  //Vengeance, ヴェンジェンス: DamageReceiveTrigger, ReflectDamage, Physical, potency 55
  //{ 89, { 8, 1, 55, 1, 0 } },

  //Vulnerability Down, 被ダメージ低下: DamageReceiveMultiplier, All, -30%
  { 912, { 2, 255, -30, 0, 0 } },
  //more than 1 effect is found
  //Vulnerability Down, 被ダメージ低下: DamageReceiveMultiplier, All, -30%
  //{ 912, { 2, 255, -30, 0, 0 } },

  //Storm's Eye, シュトルムブレハ: DamageMultiplier, All, 10%
  { 90, { 1, 255, 10, 0, 0 } },

  //Raw Intuition, 原初の直感: DamageReceiveMultiplier, All, -20%
  { 735, { 2, 255, -20, 0, 0 } },
  //more than 1 effect is found
  //Raw Intuition, 原初の直感: DamageReceiveMultiplier, All, -20%
  //{ 735, { 2, 255, -20, 0, 0 } },

  //Nascent Flash, 原初の猛り: DamageDealtTrigger, AbsorbHP, 50%
  { 1857, { 9, 0, 50, 2, 0 } },

  //Nascent Glint, 原初の猛り［被］: DamageReceiveMultiplier, All, -10%
  { 1858, { 2, 255, -10, 0, 0 } },

  //Darkside, 暗黒: DamageMultiplier, All, 10%
  { 751, { 1, 255, 10, 0, 0 } },
  //more than 1 effect is found
  //Darkside, 暗黒: DamageMultiplier, All, 10%
  //{ 751, { 1, 255, 10, 0, 0 } },
  //Darkside, 暗黒: DamageMultiplier, All, 10%
  //{ 751, { 1, 255, 10, 0, 0 } },
  //Darkside, 暗黒: DamageMultiplier, All, 10%
  //{ 751, { 1, 255, 10, 0, 0 } },

  //Shadow Wall, シャドウウォール: DamageReceiveMultiplier, All, -30%
  { 747, { 2, 255, -30, 0, 0 } },
  //more than 1 effect is found
  //Shadow Wall, シャドウウォール: DamageReceiveMultiplier, All, -30%
  //{ 747, { 2, 255, -30, 0, 0 } },

  //Dark Missionary, ダークミッショナリー: DamageReceiveMultiplier, All, -10%
  { 1894, { 2, 255, -10, 0, 0 } },

  //No Mercy, ノー・マーシー: DamageMultiplier, All, 20%
  { 1831, { 1, 255, 20, 0, 0 } },

  //Camouflage, カモフラージュ: DamageReceiveMultiplier, All, -10%
  { 1832, { 2, 255, -10, 0, 0 } },

  //Nebula, ネビュラ: DamageReceiveMultiplier, All, -30%
  { 1834, { 2, 255, -30, 0, 0 } },
  //more than 1 effect is found
  //Nebula, ネビュラ: DamageReceiveMultiplier, All, -30%
  //{ 1834, { 2, 255, -30, 0, 0 } },

  //Aurora, オーロラ: Hot, potency 200
  { 1835, { 3, 0, 200, 0, 0 } },

  //Sonic Break, ソニックブレイク: Dot, Unknown, potency 90
  { 1837, { 4, 0, 90, 0, 0 } },

  //Bow Shock, バウショック: Dot, Unknown, potency 90
  { 1838, { 4, 0, 90, 0, 0 } },

  //Heart of Light, ハート・オブ・ライト: DamageReceiveMultiplier, All, -10%
  { 1839, { 2, 255, -10, 0, 0 } },

  //Heart of Stone, ハート・オブ・ストーン: DamageReceiveMultiplier, All, -7%
  { 1840, { 2, 255, -7, 0, 0 } },

  //Fists of Earth, 金剛の構え: DamageReceiveMultiplier, All, -10%
  { 104, { 2, 255, -10, 0, 0 } },

  //Twin Snakes, 双掌打: DamageMultiplier, All, 10%
  { 101, { 1, 255, 10, 0, 0 } },
  //more than 1 effect is found
  //Twin Snakes, 双掌打: DamageMultiplier, All, 10%
  //{ 101, { 1, 255, 10, 0, 0 } },
  //Twin Snakes, 双掌打: DamageMultiplier, All, 10%
  //{ 101, { 1, 255, 10, 0, 0 } },

  //Demolish, 破砕拳: Dot, Physical, potency 65
  { 246, { 4, 1, 65, 0, 0 } },
  //more than 1 effect is found
  //Demolish, 破砕拳: Dot, Physical, potency 65
  //{ 246, { 4, 1, 65, 0, 0 } },

  //Mantra, マントラ: HealReceiveMultiplier, 10%
  { 102, { 5, 0, 10, 0, 0 } },
  //more than 1 effect is found
  //Mantra, マントラ: HealReceiveMultiplier, 20%
  //{ 102, { 5, 0, 20, 0, 0 } },

  //Fists of Fire, 紅蓮の構え: DamageMultiplier, All, 10%
  { 103, { 1, 255, 10, 0, 0 } },

  //Earth's Reply, 金剛の決意: DamageReceiveMultiplier, All, -10%
  { 1180, { 2, 255, -10, 0, 0 } },

  //Riddle of Fire, 紅蓮の極意: DamageMultiplier, All, 25%
  { 1181, { 1, 255, 25, 0, 0 } },
  //more than 1 effect is found
  //Riddle of Fire, 紅蓮の極意: DamageMultiplier, All, 30%
  //{ 1181, { 1, 255, 30, 0, 0 } },

  //Brotherhood, 桃園結義：攻撃: DamageMultiplier, Physical, 5%
  { 1185, { 1, 1, 5, 0, 0 } },

  //Disembowel, ディセムボウル: DamageMultiplier, All, 10%
  { 1914, { 1, 255, 10, 0, 0 } },

  //Lance Charge, ランスチャージ: DamageMultiplier, All, 15%
  { 1864, { 1, 255, 15, 0, 0 } },

  //Chaos Thrust, 桜華狂咲: Dot, Physical, potency 45
  { 118, { 4, 1, 45, 0, 0 } },

  //Battle Litany, バトルリタニー: CritDHRateBonus, Damage, crit 10%, dh 0%
  { 786, { 7, 1, 10, 0, 0 } },

  //Left Eye, 竜の左眼: DamageMultiplier, All, 5%
  { 1454, { 1, 255, 5, 0, 0 } },

  //Right Eye, 竜の右眼: DamageMultiplier, All, 10%
  { 1453, { 1, 255, 10, 0, 0 } },

  //Right Eye, 竜の右眼: DamageMultiplier, All, 10%
  { 1910, { 1, 255, 10, 0, 0 } },

  //Vulnerability Up, 被ダメージ上昇: DamageReceiveMultiplier, All, 5%
  { 638, { 2, 255, 5, 0, 0 } },
  //more than 1 effect is found
  //Vulnerability Up, 被ダメージ上昇: DamageReceiveMultiplier, All, 10%
  //{ 638, { 2, 255, 10, 0, 0 } },

  //Shadow Fang, 影牙: Dot, Physical, potency 90
  { 508, { 4, 1, 90, 0, 0 } },
  //more than 1 effect is found
  //Shadow Fang, 影牙: Dot, Physical, potency 70
  //{ 508, { 4, 1, 70, 0, 0 } },
  //Shadow Fang, 影牙: Dot, Physical, potency 50
  //{ 508, { 4, 1, 50, 0, 0 } },

  //Kassatsu, 活殺自在: DamageMultiplier, All, 30%
  { 497, { 1, 255, 30, 0, 0 } },

  //Ten Chi Jin, 天地人: DamageMultiplier, All, 150%
  { 1186, { 1, 255, 150, 0, 0 } },

  //Jinpu, 陣風: DamageMultiplier, All, 13%
  { 1298, { 1, 255, 13, 0, 0 } },
  //more than 1 effect is found
  //Jinpu, 陣風: DamageMultiplier, All, 13%
  //{ 1298, { 1, 255, 13, 0, 0 } },
  //Jinpu, 陣風: DamageMultiplier, All, 13%
  //{ 1298, { 1, 255, 13, 0, 0 } },

  //Kaiten, 必殺剣・回天: PotencyMultiplier, 1 uses, 50%
  { 1229, { 17, 1, 0, 3, 50 } },

  //Higanbana, 彼岸花: Dot, Physical, potency 60
  { 1228, { 4, 1, 60, 0, 0 } },
  //more than 1 effect is found
  //Higanbana, 彼岸花: Dot, Physical, potency 40
  //{ 1228, { 4, 1, 40, 0, 0 } },
  //Higanbana, 彼岸花: Dot, Physical, potency 52
  //{ 1228, { 4, 1, 52, 0, 0 } },
  //Higanbana, 彼岸花: Dot, Physical, potency 35
  //{ 1228, { 4, 1, 35, 0, 0 } },

  //Raging Strikes, 猛者の撃: DamageMultiplier, All, 10%
  { 125, { 1, 255, 10, 0, 0 } },

  //Venomous Bite, ベノムバイト: Dot, Physical, potency 30
  { 124, { 4, 1, 30, 0, 0 } },
  //more than 1 effect is found
  //Venomous Bite, ベノムバイト: Dot, Physical, potency 40
  //{ 124, { 4, 1, 40, 0, 0 } },

  //Windbite, ウィンドバイト: Dot, Physical, potency 40
  { 129, { 4, 1, 40, 0, 0 } },
  //more than 1 effect is found
  //Windbite, ウィンドバイト: Dot, Physical, potency 40
  //{ 129, { 4, 1, 40, 0, 0 } },
  //Windbite, ウィンドバイト: Dot, Physical, potency 50
  //{ 129, { 4, 1, 50, 0, 0 } },
  //Windbite, ウィンドバイト: Dot, Physical, potency 50
  //{ 129, { 4, 1, 50, 0, 0 } },

  //Caustic Bite, コースティックバイト: Dot, Physical, potency 40
  { 1200, { 4, 1, 40, 0, 0 } },
  //more than 1 effect is found
  //Caustic Bite, コースティックバイト: Dot, Physical, potency 40
  //{ 1200, { 4, 1, 40, 0, 0 } },
  //Caustic Bite, コースティックバイト: Dot, Physical, potency 50
  //{ 1200, { 4, 1, 50, 0, 0 } },
  //Caustic Bite, コースティックバイト: Dot, Physical, potency 50
  //{ 1200, { 4, 1, 50, 0, 0 } },

  //Troubadour, トルバドゥール: DamageReceiveMultiplier, All, -10%
  { 1934, { 2, 255, -10, 0, 0 } },

  //Stormbite, ストームバイト: Dot, Physical, potency 50
  { 1201, { 4, 1, 50, 0, 0 } },
  //more than 1 effect is found
  //Stormbite, ストームバイト: Dot, Physical, potency 60
  //{ 1201, { 4, 1, 60, 0, 0 } },

  //Nature's Minne, 地神のミンネ: HealReceiveMultiplier, 20%
  { 1202, { 5, 0, 20, 0, 0 } },

  //Tactician, タクティシャン: DamageReceiveMultiplier, All, -10%
  { 1951, { 2, 255, -10, 0, 0 } },

  //Bioblaster, バイオブラスト: Dot, Physical, potency 60
  { 1866, { 4, 1, 60, 0, 0 } },

  //Standard Finish, スタンダードフィニッシュ: DamageMultiplier, All, 5%
  { 1821, { 1, 255, 5, 0, 0 } },

  //Shield Samba, 守りのサンバ: DamageReceiveMultiplier, All, -10%
  { 1826, { 2, 255, -10, 0, 0 } },

  //Technical Finish, テクニカルフィニッシュ: DamageMultiplier, All, 5%
  { 1822, { 1, 255, 5, 0, 0 } },

  //Thunder, サンダー: Dot, Magical, potency 40
  { 161, { 4, 2, 40, 0, 0 } },

  //Thunder II, サンダラ: Dot, Magical, potency 30
  { 162, { 4, 2, 30, 0, 0 } },

  //Thunder III, サンダガ: Dot, Magical, potency 40
  { 163, { 4, 2, 40, 0, 0 } },

  //Enochian, エノキアン: DamageMultiplier, Magical, 15%
  { 868, { 1, 2, 15, 0, 0 } },

  //Thunder IV, サンダジャ: Dot, Magical, potency 30
  { 1210, { 4, 2, 30, 0, 0 } },

  //Bio, バイオ: Dot, Magical, potency 20
  { 179, { 4, 2, 20, 0, 0 } },
  //more than 1 effect is found
  //Bio, バイオ: Dot, Magical, potency 20
  //{ 179, { 4, 2, 20, 0, 0 } },
  //Bio, バイオ: Dot, Magical, potency 20
  //{ 179, { 4, 2, 20, 0, 0 } },
  //Bio, バイオ: Dot, Magical, potency 20
  //{ 179, { 4, 2, 20, 0, 0 } },

  //Miasma, ミアズマ: Dot, Magical, potency 20
  { 180, { 4, 2, 20, 0, 0 } },
  //more than 1 effect is found
  //Miasma, ミアズマ: Dot, Magical, potency 20
  //{ 180, { 4, 2, 20, 0, 0 } },
  //Miasma, ミアズマ: Dot, Magical, potency 20
  //{ 180, { 4, 2, 20, 0, 0 } },

  //Bio II, バイオラ: Dot, Magical, potency 30
  { 189, { 4, 2, 30, 0, 0 } },
  //more than 1 effect is found
  //Bio II, バイオラ: Dot, Magical, potency 30
  //{ 189, { 4, 2, 30, 0, 0 } },
  //Bio II, バイオラ: Dot, Magical, potency 30
  //{ 189, { 4, 2, 30, 0, 0 } },
  //Bio II, バイオラ: Dot, Magical, potency 30
  //{ 189, { 4, 2, 30, 0, 0 } },

  //Bio III, バイオガ: Dot, Magical, potency 50
  { 1214, { 4, 2, 50, 0, 0 } },
  //more than 1 effect is found
  //Bio III, バイオガ: Dot, Magical, potency 50
  //{ 1214, { 4, 2, 50, 0, 0 } },
  //Bio III, バイオガ: Dot, Magical, potency 50
  //{ 1214, { 4, 2, 50, 0, 0 } },
  //Bio III, バイオガ: Dot, Magical, potency 40
  //{ 1214, { 4, 2, 40, 0, 0 } },
  //Bio III, バイオガ: Dot, Magical, potency 40
  //{ 1214, { 4, 2, 40, 0, 0 } },
  //Bio III, バイオガ: Dot, Magical, potency 40
  //{ 1214, { 4, 2, 40, 0, 0 } },

  //Miasma III, ミアズガ: Dot, Magical, potency 50
  { 1215, { 4, 2, 50, 0, 0 } },
  //more than 1 effect is found
  //Miasma III, ミアズガ: Dot, Magical, potency 50
  //{ 1215, { 4, 2, 50, 0, 0 } },
  //Miasma III, ミアズガ: Dot, Magical, potency 50
  //{ 1215, { 4, 2, 50, 0, 0 } },
  //Miasma III, ミアズガ: Dot, Magical, potency 40
  //{ 1215, { 4, 2, 40, 0, 0 } },
  //Miasma III, ミアズガ: Dot, Magical, potency 40
  //{ 1215, { 4, 2, 40, 0, 0 } },
  //Miasma III, ミアズガ: Dot, Magical, potency 40
  //{ 1215, { 4, 2, 40, 0, 0 } },

  //Devotion, エギの加護: DamageMultiplier, All, 5%
  { 1213, { 1, 255, 5, 0, 0 } },

  //Everlasting Flight, 不死鳥の翼: Hot, potency 100
  { 1868, { 3, 0, 100, 0, 0 } },
  //more than 1 effect is found
  //Everlasting Flight, 不死鳥の翼: Hot, potency 100
  //{ 1868, { 3, 0, 100, 0, 0 } },

  //Inferno, 地獄の火炎: Dot, Magical, potency 20
  { 314, { 4, 2, 20, 0, 0 } },
  //more than 1 effect is found
  //Inferno, 地獄の火炎: Dot, Magical, potency 20
  //{ 314, { 4, 2, 20, 0, 0 } },

  //Embolden, エンボルデン: DamageMultiplier, Magical, 2%
  { 1239, { 1, 2, 2, 0, 0 } },

  //Embolden, エンボルデン: DamageMultiplier, Physical, 2%
  { 1297, { 1, 1, 2, 0, 0 } },

  //Manafication, マナフィケーション: DamageMultiplier, All, 5%
  { 1971, { 1, 255, 5, 0, 0 } },

  //Aero, エアロ: Dot, Magical, potency 30
  { 143, { 4, 2, 30, 0, 0 } },

  //Aero II, エアロラ: Dot, Magical, potency 60
  { 144, { 4, 2, 60, 0, 0 } },

  //Medica II, メディカラ: Hot, potency 100
  { 150, { 3, 0, 100, 0, 0 } },

  //Regen, リジェネ: Hot, potency 200
  { 158, { 3, 0, 200, 0, 0 } },

  //Confession, インドゥルゲンティア: Hot, potency 200
  { 1219, { 3, 0, 200, 0, 0 } },

  //Dia, ディア: Dot, Magical, potency 60
  { 1871, { 4, 2, 60, 0, 0 } },

  //Temperance, テンパランス: HealCastMultiplier, 20%
  { 1872, { 6, 0, 20, 0, 0 } },

  //Temperance, テンパランス：効果: DamageReceiveMultiplier, All, 10%
  { 1873, { 2, 255, 10, 0, 0 } },

  //Dissipation, 転化: HealCastMultiplier, 20%
  { 791, { 6, 0, 20, 0, 0 } },

  //Biolysis, 蠱毒法: Dot, Magical, potency 60
  { 1895, { 4, 2, 60, 0, 0 } },

  //Whispering Dawn, 光の囁き: Hot, potency 120
  { 315, { 3, 0, 120, 0, 0 } },

  //Fey Illumination, フェイイルミネーション: HealCastMultiplier, 10%
  { 317, { 6, 0, 10, 0, 0 } },

  //Angel's Whisper, 光輝の囁き: Hot, potency 120
  { 1874, { 3, 0, 120, 0, 0 } },

  //Seraphic Illumination, セラフィックイルミネーション: HealCastMultiplier, 10%
  { 1875, { 6, 0, 10, 0, 0 } },

  //Combust, コンバス: Dot, Magical, potency 40
  { 838, { 4, 2, 40, 0, 0 } },
  //more than 1 effect is found
  //Combust, コンバス: Dot, Magical, potency 30
  //{ 838, { 4, 2, 30, 0, 0 } },

  //Aspected Benefic, アスペクト・ベネフィク: Hot, potency 200
  { 835, { 3, 0, 200, 0, 0 } },

  //Aspected Helios, アスペクト・ヘリオス: Hot, potency 100
  { 836, { 3, 0, 100, 0, 0 } },
  //more than 1 effect is found
  //Aspected Helios, アスペクト・ヘリオス: Hot, potency 100
  //{ 836, { 3, 0, 100, 0, 0 } },

  //Horoscope Helios, ホロスコープ・ヘリオス: Hot, potency 100
  { 1891, { 3, 0, 100, 0, 0 } },
  //more than 1 effect is found
  //Horoscope Helios, ホロスコープ・ヘリオス: Hot, potency 100
  //{ 1891, { 3, 0, 100, 0, 0 } },

  //Combust II, コンバラ: Dot, Magical, potency 50
  { 843, { 4, 2, 50, 0, 0 } },
  //more than 1 effect is found
  //Combust II, コンバラ: Dot, Magical, potency 35
  //{ 843, { 4, 2, 35, 0, 0 } },

  //Divination, ディヴィネーション: DamageMultiplier, All, 0%
  { 1878, { 1, 255, 0, 0, 0 } },

  //Wheel of Fortune, 運命の輪: Hot, potency 50
  { 956, { 3, 0, 50, 0, 0 } },
  //more than 1 effect is found
  //Wheel of Fortune, 運命の輪: Hot, potency 50
  //{ 956, { 3, 0, 50, 0, 0 } },

  //Diurnal Opposition, 星天対抗［日］: Hot, potency 100
  { 1879, { 3, 0, 100, 0, 0 } },
  //more than 1 effect is found
  //Diurnal Opposition, 星天対抗［日］: Hot, potency 60
  //{ 1879, { 3, 0, 60, 0, 0 } },

  //Combust III, コンバガ: Dot, Magical, potency 60
  { 1881, { 4, 2, 60, 0, 0 } },
  //more than 1 effect is found
  //Combust III, コンバガ: Dot, Magical, potency 45
  //{ 1881, { 4, 2, 45, 0, 0 } },

  //Diurnal Intersection, 星天交差［日］: Hot, potency 150
  { 1888, { 3, 0, 150, 0, 0 } },
  //more than 1 effect is found
  //Diurnal Intersection, 星天交差［日］: Hot, potency 80
  //{ 1888, { 3, 0, 80, 0, 0 } },

  //Neutral Sect, ニュートラルセクト: HealCastMultiplier, 20%
  { 1892, { 6, 0, 20, 0, 0 } },

  //The Balance, アーゼマの均衡: DamageMultiplier, All, 6%
  { 1882, { 1, 255, 6, 0, 0 } },

  //The Arrow, オシュオンの矢: DamageMultiplier, All, 6%
  { 1884, { 1, 255, 6, 0, 0 } },

  //The Spear, ハルオーネの槍: DamageMultiplier, All, 6%
  { 1885, { 1, 255, 6, 0, 0 } },

  //The Bole, 世界樹の幹: DamageMultiplier, All, 6%
  { 1883, { 1, 255, 6, 0, 0 } },

  //The Ewer, サリャクの水瓶: DamageMultiplier, All, 6%
  { 1886, { 1, 255, 6, 0, 0 } },

  //The Spire, ビエルゴの塔: DamageMultiplier, All, 6%
  { 1887, { 1, 255, 6, 0, 0 } },

  //Lord of Crowns, クラウンロード: DamageMultiplier, All, 8%
  { 1876, { 1, 255, 8, 0, 0 } },

  //Lady of Crowns, クラウンレディ: DamageMultiplier, All, 8%
  { 1877, { 1, 255, 8, 0, 0 } },

  //Off-guard, ガードオファ: DamageReceiveMultiplier, All, 50%
  { 1717, { 2, 255, 50, 0, 0 } },

  //Boost, 力溜め: DamageMultiplier, All, 50%
  { 1716, { 1, 255, 50, 0, 0 } },

  //Peculiar Light, 不思議な光: DamageReceiveMultiplier, Magical, 30%
  { 1721, { 2, 2, 30, 0, 0 } },

  //Mighty Guard, マイティガード: DamageMultiplier, All, -70%
  { 1719, { 1, 255, -70, 0, 0 } },
  //more than 1 effect is found
  //Mighty Guard, マイティガード: DamageReceiveMultiplier, All, -40%
  //{ 1719, { 2, 255, -40, 0, 0 } },

  //Bleeding, ペイン: Dot, Magical, potency 25
  { 1714, { 4, 2, 25, 0, 0 } },

  //Waxing Nocturne, 狂戦士化: DamageMultiplier, All, 50%
  { 1718, { 1, 255, 50, 0, 0 } },

  //Windburn, 裂傷: Dot, Magical, potency 20
  { 1723, { 4, 2, 20, 0, 0 } },

  //Diamondback, 超硬化: DamageReceiveMultiplier, All, -90%
  { 1722, { 2, 255, -90, 0, 0 } },

  //Reprisal, リプライザル: DamageMultiplier, All, -10%
  { 1193, { 1, 255, -10, 0, 0 } },
  //more than 1 effect is found
  //Reprisal, リプライザル: DamageMultiplier, All, -10%
  //{ 1193, { 1, 255, -10, 0, 0 } },

  //Bloodbath, ブラッドバス: DamageDealtTrigger, AbsorbHP, 25%
  { 84, { 9, 0, 25, 2, 0 } },

  //Choco Beak, チョコビーク: Dot, Physical, potency 20
  { 236, { 4, 1, 20, 0, 0 } },

  //Choco Surge, チョコサージ: HealCastMultiplier, 30%
  { 238, { 6, 0, 30, 0, 0 } },

  //Choco Regen, チョコリジェネ: Hot, potency 25
  { 237, { 3, 0, 25, 0, 0 } },

  //Vulnerability Up, 被ダメージ上昇: DamageReceiveMultiplier, All, 5%
  { 1208, { 2, 255, 5, 0, 0 } },
  //more than 1 effect is found
  //Vulnerability Up, 被ダメージ上昇: DamageReceiveMultiplier, All, 5%
  //{ 1208, { 2, 255, 5, 0, 0 } },

  //Boost, 力溜め: DamageMultiplier, All, 30%
  { 1656, { 1, 255, 30, 0, 0 } },

  //Magic Burst L, ロゴス・マジックバースト: DamageMultiplier, Magical, 1%
  { 1652, { 1, 2, 1, 0, 0 } },

  //Bravery L, ロゴス・ブレイブ: DamageMultiplier, All, 10%
  { 1646, { 1, 255, 10, 0, 0 } },

  //Double Edge L, ロゴス・ダブルエッジ: DamageMultiplier, Physical, 15%
  { 1653, { 1, 1, 15, 0, 0 } },

  //Wisdom of the Aetherweaver, 術士の記憶: DamageMultiplier, Magical, 60%
  { 1631, { 1, 2, 60, 0, 0 } },

  //Wisdom of the Martialist, 闘士の記憶: DamageMultiplier, All, 40%
  { 1632, { 1, 255, 40, 0, 0 } },

  //Wisdom of the Skirmisher, 武人の記憶: DamageMultiplier, All, 20%
  { 1636, { 1, 255, 20, 0, 0 } },

  //Wisdom of the Watcher, 斥候の記憶: DamageMultiplier, All, -5%
  { 1637, { 1, 255, -5, 0, 0 } },

  //Wisdom of the Templar, 聖騎士の記憶: DamageMultiplier, All, -5%
  { 1638, { 1, 255, -5, 0, 0 } },

  //Wisdom of the Duelist, 剣豪の記憶: DamageMultiplier, Physical, 40%
  { 1740, { 1, 1, 40, 0, 0 } },
  //more than 1 effect is found
  //Wisdom of the Duelist, 剣豪の記憶: DamageMultiplier, Magical, 30%
  //{ 1740, { 1, 2, 30, 0, 0 } },

  //Wisdom of the Elder, 賢者の記憶: DamageMultiplier, Magical, 35%
  { 1739, { 1, 2, 35, 0, 0 } },

  //Wisdom of the Fiendhunter, 弓聖の記憶: DamageMultiplier, Physical, 25%
  { 1741, { 1, 1, 25, 0, 0 } },

  //Last Bastion, ラストバスティオン: DamageReceiveMultiplier, All, -50%
  { 196, { 2, 255, -50, 0, 0 } },

  //Land Waker, 原初の大地: DamageReceiveMultiplier, All, -50%
  { 863, { 2, 255, -50, 0, 0 } },

  //Dark Force, ダークフォース: DamageReceiveMultiplier, All, -50%
  { 864, { 2, 255, -50, 0, 0 } },

  //Damage Up, ダメージ上昇: DamageReceiveMultiplier, All, -15%
  { 263, { 2, 255, -15, 0, 0 } },

  //Infernal Fetters, 炎獄の鎖: DamageMultiplier, All, -10%
  { 377, { 1, 255, -10, 0, 0 } },

  //Infirmity, 虚弱: HealReceiveMultiplier, -50%
  { 172, { 5, 0, -50, 0, 0 } },

  //Disseminate, ディスセミネイト: DamageReceiveMultiplier, All, 25%
  { 348, { 2, 255, 25, 0, 0 } },

  //Damage Up, ダメージ上昇: DamageMultiplier, All, 25%
  { 443, { 1, 255, 25, 0, 0 } },
  //more than 1 effect is found
  //Damage Up, ダメージ上昇: DamageMultiplier, All, 15%
  //{ 443, { 1, 255, 15, 0, 0 } },
  //Damage Up, ダメージ上昇: DamageMultiplier, All, 25%
  //{ 443, { 1, 255, 25, 0, 0 } },

  //Mantle of the Whorl, 水神のマント: DamageReceiveTrigger, ReflectDamage, Physical, potency 50
  { 477, { 8, 1, 50, 1, 0 } },

  //Veil of the Whorl, 水神のヴェール: DamageReceiveTrigger, ReflectDamage, Physical, potency 50
  { 478, { 8, 1, 50, 1, 0 } },

  //Frost Blade, 凍てつく剣: DamageReceiveMultiplier, All, -10%
  { 526, { 2, 255, -10, 0, 0 } },

  //Bluefire, 青碧の炎: HealReceiveMultiplier, -80%
  { 591, { 5, 0, -80, 0, 0 } },
  //more than 1 effect is found
  //Bluefire, 青碧の炎: DamageMultiplier, All, -90%
  //{ 591, { 1, 255, -90, 0, 0 } },

  //Minimum, ミニマム: DamageMultiplier, All, -50%
  { 438, { 1, 255, -50, 0, 0 } },
  //more than 1 effect is found
  //Minimum, ミニマム: DamageReceiveMultiplier, All, 50%
  //{ 438, { 2, 255, 50, 0, 0 } },
  //Minimum, ミニマム: DamageReceiveMultiplier, All, 45%
  //{ 438, { 2, 255, 45, 0, 0 } },
  //Minimum, ミニマム: DamageMultiplier, All, -90%
  //{ 438, { 1, 255, -90, 0, 0 } },
  //Minimum, ミニマム: DamageReceiveMultiplier, All, 50%
  //{ 438, { 2, 255, 50, 0, 0 } },
  //Minimum, ミニマム: DamageMultiplier, All, -50%
  //{ 438, { 1, 255, -50, 0, 0 } },
  //Minimum, ミニマム: DamageMultiplier, All, -50%
  //{ 438, { 1, 255, -50, 0, 0 } },
  //Minimum, ミニマム: DamageReceiveMultiplier, All, 50%
  //{ 438, { 2, 255, 50, 0, 0 } },
  //Minimum, ミニマム: DamageReceiveMultiplier, All, 45%
  //{ 438, { 2, 255, 45, 0, 0 } },
  //Minimum, ミニマム: DamageMultiplier, All, -90%
  //{ 438, { 1, 255, -90, 0, 0 } },
  //Minimum, ミニマム: DamageReceiveMultiplier, All, 50%
  //{ 438, { 2, 255, 50, 0, 0 } },
  //Minimum, ミニマム: DamageMultiplier, All, -50%
  //{ 438, { 1, 255, -50, 0, 0 } },

  //Ice Spikes, アイススパイク: DamageReceiveTrigger, ReflectDamage, Physical, potency 50
  { 198, { 8, 1, 50, 1, 0 } },

  //Blaze Spikes, ブレイズスパイク: DamageReceiveTrigger, ReflectDamage, Physical, potency 50
  { 197, { 8, 1, 50, 1, 0 } },

  //Bigbulge Biggerbrain, マッチョサイエンティスト: DamageReceiveMultiplier, All, -30%
  { 1003, { 2, 255, -30, 0, 0 } },

  //Damage Down, ダメージ低下: DamageMultiplier, All, -3%
  { 1016, { 1, 255, -3, 0, 0 } },
  //more than 1 effect is found
  //Damage Down, ダメージ低下: DamageMultiplier, All, -3%
  //{ 1016, { 1, 255, -3, 0, 0 } },
  //Damage Down, ダメージ低下: DamageMultiplier, All, -10%
  //{ 1016, { 1, 255, -10, 0, 0 } },
  //Damage Down, ダメージ低下: DamageMultiplier, All, -10%
  //{ 1016, { 1, 255, -10, 0, 0 } },

  //Vulnerability Up, 被ダメージ上昇: DamageReceiveMultiplier, All, 10%
  { 202, { 2, 255, 10, 0, 0 } },

  //Offensive Optimization, 攻撃形態: DamageReceiveMultiplier, All, 50%
  { 681, { 2, 255, 50, 0, 0 } },

  //Defensive Optimization, 防御形態: DamageReceiveMultiplier, All, -50%
  { 682, { 2, 255, -50, 0, 0 } },

  //Blessing of Earth, 土の加護: DamageReceiveMultiplier, All, -40%
  { 683, { 2, 255, -40, 0, 0 } },

  //Magic Vulnerability Down, 被魔法ダメージ軽減: DamageReceiveMultiplier, Magical, -25%
  { 812, { 2, 2, -25, 0, 0 } },

  //Vulnerability Up, 被ダメージ上昇: DamageReceiveMultiplier, All, 10%
  { 714, { 2, 255, 10, 0, 0 } },

  //Healing Potency Down, 魔法回復力ダウン: HealCastMultiplier, -30%
  { 933, { 6, 0, -30, 0, 0 } },

  //Rampart, ランパート: DamageReceiveMultiplier, All, -20%
  { 1191, { 2, 255, -20, 0, 0 } },

  //Berserk, バーサク: CritDHRateBonus, Damage, crit 100%, dh 100%
  { 86, { 7, 1, 100, 100, 0 } },

  //Inner Release, 原初の解放: CritDHRateBonus, Damage, crit 100%, dh 100%
  { 1177, { 7, 1, 100, 100, 0 } },

  //Devilment, 攻めのタンゴ: CritDHRateBonus, Damage, crit 20%, dh 20%
  { 1825, { 7, 1, 20, 20, 0 } },

  //Lucid Dreaming, ルーシッドドリーム: MPRestore, value 50
  { 1204, { 11, 50, 0, 0, 0 } },

  //Presence of Mind, 神速魔: Haste, 20%
  { 157, { 12, 20, 0, 0, 0 } },

  //Swiftcast, 迅速魔: InstantCast, 1 casts
  { 167, { 13, 1, 0, 0, 0 } },

  //Sheltron, シェルトロン: BlockParryRateBonus, block 100%, parry 0%
  { 1856, { 14, 0, 100, 0, 0 } },

  //Blood Weapon, ブラッドウェポン: MPRestorePerGCD, 6%
  { 742, { 15, 6, 0, 0, 0 } },

  //Delirium, ブラッドデリリアム: MPRestorePerGCD, 2%
  { 1972, { 15, 2, 7392, 7391, 0 } },

  //Meikyo Shisui, 明鏡止水: AlwaysCombo, 3 uses
  { 1233, { 16, 3, 0, 3, 0 } },

  //Shifu, 士風: Haste, 13%
  { 1299, { 12, 13, 0, 0, 0 } },

};
