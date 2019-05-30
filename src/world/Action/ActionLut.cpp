#include "ActionLut.h"

using namespace Sapphire::World::Action;

ActionLut::Lut ActionLut::m_actionLut =
{
  // attack
  { 7, { 0, 0, 0, 0, 0 } },
  // Shot
  { 8, { 0, 0, 0, 0, 0 } },
  // Fast Blade
  { 9, { 160, 0, 0, 0, 0 } },
  // Savage Blade
  { 11, { 100, 0, 0, 0, 0 } },
  // Flash
  { 14, { 0, 0, 0, 0, 0 } },
  // Riot Blade
  { 15, { 100, 0, 0, 0, 0 } },
  // Shield Bash
  { 16, { 110, 0, 0, 0, 0 } },
  // Sentinel
  { 17, { 0, 0, 0, 0, 0 } },
  // Tempered Will
  { 19, { 0, 0, 0, 0, 0 } },
  // Fight or Flight
  { 20, { 0, 0, 0, 0, 0 } },
  // Rage of Halone
  { 21, { 100, 0, 0, 0, 0 } },
  // Bulwark
  { 22, { 0, 0, 0, 0, 0 } },
  // Circle of Scorn
  { 23, { 100, 0, 0, 0, 0 } },
  // Shield Lob
  { 24, { 120, 0, 0, 0, 0 } },
  // Shield Swipe
  { 25, { 100, 0, 0, 0, 0 } },
  // Sword Oath
  { 26, { 75, 0, 0, 0, 0 } },
  // Cover
  { 27, { 0, 0, 0, 0, 0 } },
  // Shield Oath
  { 28, { 0, 0, 0, 0, 0 } },
  // Spirits Within
  { 29, { 300, 0, 0, 0, 0 } },
  // Hallowed Ground
  { 30, { 0, 0, 0, 0, 0 } },
  // Heavy Swing
  { 31, { 160, 0, 0, 0, 0 } },
  // Skull Sunder
  { 35, { 100, 0, 0, 0, 0 } },
  // Maim
  { 37, { 100, 0, 0, 0, 0 } },
  // Berserk
  { 38, { 0, 0, 0, 0, 0 } },
  // Thrill of Battle
  { 40, { 0, 0, 0, 0, 0 } },
  // Overpower
  { 41, { 130, 0, 0, 0, 0 } },
  // Storm's Path
  { 42, { 100, 0, 0, 0, 0 } },
  // Holmgang
  { 43, { 0, 0, 0, 0, 0 } },
  // Vengeance
  { 44, { 55, 0, 0, 0, 0 } },
  // Storm's Eye
  { 45, { 100, 0, 0, 0, 0 } },
  // Tomahawk
  { 46, { 140, 0, 0, 0, 0 } },
  // Butcher's Block
  { 47, { 100, 0, 0, 0, 0 } },
  // Defiance
  { 48, { 0, 0, 0, 0, 0 } },
  // Inner Beast
  { 49, { 350, 0, 0, 0, 0 } },
  // Unchained
  { 50, { 0, 0, 0, 0, 0 } },
  // Steel Cyclone
  { 51, { 200, 0, 0, 0, 0 } },
  // Infuriate
  { 52, { 0, 0, 0, 0, 0 } },
  // Bootshine
  { 53, { 140, 0, 0, 0, 0 } },
  // True Strike
  { 54, { 160, 0, 0, 180, 0 } },
  // Snap Punch
  { 56, { 150, 170, 0, 0, 0 } },
  // Internal Release
  { 59, { 0, 0, 0, 0, 0 } },
  // Fists of Earth
  { 60, { 0, 0, 0, 0, 0 } },
  // Twin Snakes
  { 61, { 110, 130, 0, 0, 0 } },
  // Arm of the Destroyer
  { 62, { 50, 0, 0, 0, 0 } },
  // Fists of Fire
  { 63, { 0, 0, 0, 0, 0 } },
  // Steel Peak
  { 64, { 150, 0, 0, 0, 0 } },
  // Mantra
  { 65, { 0, 0, 0, 0, 0 } },
  // Demolish
  { 66, { 50, 0, 0, 70, 0 } },
  // Howling Fist
  { 67, { 210, 0, 0, 0, 0 } },
  // Perfect Balance
  { 69, { 0, 0, 0, 0, 0 } },
  // Rockbreaker
  { 70, { 130, 0, 0, 0, 0 } },
  // Shoulder Tackle
  { 71, { 100, 0, 0, 0, 0 } },
  // One Ilm Punch
  { 72, { 120, 0, 0, 0, 0 } },
  // Fists of Wind
  { 73, { 0, 0, 0, 0, 0 } },
  // Dragon Kick
  { 74, { 120, 140, 0, 0, 0 } },
  // True Thrust
  { 75, { 160, 0, 0, 0, 0 } },
  // Vorpal Thrust
  { 78, { 100, 0, 0, 0, 0 } },
  // Heavy Thrust
  { 79, { 150, 190, 0, 0, 0 } },
  // Impulse Drive
  { 81, { 200, 0, 0, 0, 0 } },
  // Life Surge
  { 83, { 0, 0, 0, 0, 0 } },
  // Full Thrust
  { 84, { 100, 0, 0, 0, 0 } },
  // Blood for Blood
  { 85, { 0, 0, 0, 0, 0 } },
  // Doom Spike
  { 86, { 140, 0, 0, 0, 0 } },
  // Disembowel
  { 87, { 100, 0, 0, 0, 0 } },
  // Chaos Thrust
  { 88, { 100, 0, 0, 140, 0 } },
  // Piercing Talon
  { 90, { 120, 0, 0, 0, 0 } },
  // Jump
  { 92, { 260, 0, 0, 0, 0 } },
  // Elusive Jump
  { 94, { 0, 0, 0, 0, 0 } },
  // Spineshatter Dive
  { 95, { 210, 0, 0, 0, 0 } },
  // Dragonfire Dive
  { 96, { 320, 0, 0, 0, 0 } },
  // Heavy Shot
  { 97, { 150, 0, 0, 0, 0 } },
  // Straight Shot
  { 98, { 140, 0, 0, 0, 0 } },
  // Venomous Bite
  { 100, { 100, 0, 0, 0, 0 } },
  // Raging Strikes
  { 101, { 0, 0, 0, 0, 0 } },
  // Misery's End
  { 103, { 190, 0, 0, 0, 0 } },
  // Quick Nock
  { 106, { 110, 0, 0, 0, 0 } },
  // Barrage
  { 107, { 0, 0, 0, 0, 0 } },
  // Bloodletter
  { 110, { 130, 0, 0, 0, 0 } },
  // Repelling Shot
  { 112, { 0, 0, 0, 0, 0 } },
  // Windbite
  { 113, { 60, 0, 0, 0, 0 } },
  // Mage's Ballad
  { 114, { 100, 0, 0, 0, 0 } },
  // Foe Requiem
  { 115, { 0, 0, 0, 0, 0 } },
  // Army's Paeon
  { 116, { 100, 0, 0, 0, 0 } },
  // Rain of Death
  { 117, { 100, 0, 0, 0, 0 } },
  // Battle Voice
  { 118, { 0, 0, 0, 0, 0 } },
  // Stone
  { 119, { 140, 0, 0, 0, 0 } },
  // Cure
  { 120, { 0, 0, 0, 0, 450 } },
  // Aero
  { 121, { 50, 0, 0, 0, 0 } },
  // Medica
  { 124, { 0, 0, 0, 0, 300 } },
  // Raise
  { 125, { 0, 0, 0, 0, 0 } },
  // Stone II
  { 127, { 200, 0, 0, 0, 0 } },
  // Repose
  { 128, { 0, 0, 0, 0, 0 } },
  // Cure III
  { 131, { 0, 0, 0, 0, 550 } },
  // Aero II
  { 132, { 50, 0, 0, 0, 0 } },
  // Medica II
  { 133, { 0, 0, 0, 0, 200 } },
  // Fluid Aura
  { 134, { 0, 0, 0, 0, 0 } },
  // Cure II
  { 135, { 0, 0, 0, 0, 700 } },
  // Presence of Mind
  { 136, { 0, 0, 0, 0, 0 } },
  // Regen
  { 137, { 0, 0, 0, 0, 150 } },
  // Holy
  { 139, { 200, 0, 0, 0, 0 } },
  // Benediction
  { 140, { 0, 0, 0, 0, 0 } },
  // Fire
  { 141, { 180, 0, 0, 0, 0 } },
  // Blizzard
  { 142, { 180, 0, 0, 0, 0 } },
  // Thunder
  { 144, { 30, 0, 0, 0, 0 } },
  // Sleep
  { 145, { 0, 0, 0, 0, 0 } },
  // Blizzard II
  { 146, { 50, 0, 0, 0, 0 } },
  // Fire II
  { 147, { 80, 0, 0, 0, 0 } },
  // Transpose
  { 149, { 0, 0, 0, 0, 0 } },
  // Fire III
  { 152, { 240, 0, 0, 0, 0 } },
  // Thunder III
  { 153, { 70, 0, 0, 0, 0 } },
  // Blizzard III
  { 154, { 240, 0, 0, 0, 0 } },
  // Aetherial Manipulation
  { 155, { 0, 0, 0, 0, 0 } },
  // Scathe
  { 156, { 100, 0, 0, 0, 0 } },
  // Manaward
  { 157, { 0, 0, 0, 0, 0 } },
  // Convert
  { 158, { 0, 0, 0, 0, 0 } },
  // Freeze
  { 159, { 100, 0, 0, 0, 0 } },
  // Flare
  { 162, { 260, 0, 0, 0, 0 } },
  // Ruin
  { 163, { 100, 0, 0, 0, 0 } },
  // Bio
  { 164, { 0, 0, 0, 0, 0 } },
  // Summon
  { 165, { 0, 0, 0, 0, 0 } },
  // Aetherflow
  { 166, { 0, 0, 0, 0, 0 } },
  // Energy Drain
  { 167, { 150, 0, 0, 0, 0 } },
  // Miasma
  { 168, { 20, 0, 0, 0, 0 } },
  // Summon II
  { 170, { 0, 0, 0, 0, 0 } },
  // Sustain
  { 171, { 0, 0, 0, 0, 0 } },
  // Ruin II
  { 172, { 100, 0, 0, 0, 0 } },
  // Resurrection
  { 173, { 0, 0, 0, 0, 0 } },
  // Bane
  { 174, { 0, 0, 0, 0, 0 } },
  // Rouse
  { 176, { 0, 0, 0, 0, 0 } },
  // Miasma II
  { 177, { 100, 0, 0, 0, 0 } },
  // Bio II
  { 178, { 0, 0, 0, 0, 0 } },
  // Shadow Flare
  { 179, { 50, 0, 0, 0, 0 } },
  // Summon III
  { 180, { 0, 0, 0, 0, 0 } },
  // Fester
  { 181, { 150, 0, 0, 0, 0 } },
  // Tri-bind
  { 182, { 30, 0, 0, 0, 0 } },
  // Enkindle
  { 184, { 0, 0, 0, 0, 0 } },
  // Adloquium
  { 185, { 0, 0, 0, 0, 300 } },
  // Succor
  { 186, { 0, 0, 0, 0, 150 } },
  // Sacred Soil
  { 188, { 0, 0, 0, 0, 0 } },
  // Lustrate
  { 189, { 0, 0, 0, 0, 600 } },
  // Physick
  { 190, { 0, 0, 0, 0, 400 } },
  // Shield Wall
  { 197, { 0, 0, 0, 0, 0 } },
  // Stronghold
  { 198, { 0, 0, 0, 0, 0 } },
  // Last Bastion
  { 199, { 0, 0, 0, 0, 0 } },
  // Braver
  { 200, { 2400, 0, 0, 0, 0 } },
  // Bladedance
  { 201, { 5250, 0, 0, 0, 0 } },
  // Final Heaven
  { 202, { 9000, 0, 0, 0, 0 } },
  // Skyshard
  { 203, { 1650, 0, 0, 0, 0 } },
  // Starstorm
  { 204, { 3600, 0, 0, 0, 0 } },
  // Meteor
  { 205, { 6150, 0, 0, 0, 0 } },
  // Healing Wind
  { 206, { 0, 0, 0, 0, 0 } },
  // Breath of the Earth
  { 207, { 0, 0, 0, 0, 0 } },
  // Pulse of Life
  { 208, { 0, 0, 0, 0, 0 } },
  // Magitek Cannon
  { 1128, { 0, 0, 0, 0, 0 } },
  // Photon Stream
  { 1129, { 0, 0, 0, 0, 0 } },
  // attack
  { 1533, { 0, 0, 0, 0, 0 } },
  // Spinning Edge
  { 2240, { 150, 0, 0, 0, 0 } },
  // Shade Shift
  { 2241, { 0, 0, 0, 0, 0 } },
  // Gust Slash
  { 2242, { 100, 0, 0, 0, 0 } },
  // Hide
  { 2245, { 0, 0, 0, 0, 0 } },
  // Assassinate
  { 2246, { 200, 0, 0, 0, 0 } },
  // Throwing Dagger
  { 2247, { 120, 0, 0, 0, 0 } },
  // Mug
  { 2248, { 140, 0, 0, 0, 0 } },
  // Hide
  { 2253, { 0, 0, 0, 0, 0 } },
  // Death Blossom
  { 2254, { 110, 0, 0, 0, 0 } },
  // Aeolian Edge
  { 2255, { 100, 0, 0, 160, 0 } },
  // Jugulate
  { 2256, { 80, 0, 0, 0, 0 } },
  // Shadow Fang
  { 2257, { 100, 0, 0, 0, 0 } },
  // Trick Attack
  { 2258, { 240, 0, 0, 400, 0 } },
  // Ten
  { 2259, { 0, 0, 0, 0, 0 } },
  // Ninjutsu
  { 2260, { 0, 0, 0, 0, 0 } },
  // Chi
  { 2261, { 0, 0, 0, 0, 0 } },
  // Shukuchi
  { 2262, { 0, 0, 0, 0, 0 } },
  // Jin
  { 2263, { 0, 0, 0, 0, 0 } },
  // Kassatsu
  { 2264, { 0, 0, 0, 0, 0 } },
  // Fuma Shuriken
  { 2265, { 240, 0, 0, 0, 0 } },
  // Katon
  { 2266, { 250, 0, 0, 0, 0 } },
  // Raiton
  { 2267, { 360, 0, 0, 0, 0 } },
  // Hyoton
  { 2268, { 140, 0, 0, 0, 0 } },
  // Huton
  { 2269, { 0, 0, 0, 0, 0 } },
  // Doton
  { 2270, { 45, 0, 0, 0, 0 } },
  // Suiton
  { 2271, { 180, 0, 0, 0, 0 } },
  // Rabbit Medium
  { 2272, { 0, 0, 0, 0, 0 } },
  // Rook Autoturret
  { 2864, { 80, 0, 0, 0, 0 } },
  // Bishop Autoturret
  { 2865, { 60, 0, 0, 0, 0 } },
  // Split Shot
  { 2866, { 160, 0, 0, 0, 0 } },
  // Reload
  { 2867, { 0, 0, 0, 0, 0 } },
  // Slug Shot
  { 2868, { 100, 0, 0, 0, 0 } },
  // Spread Shot
  { 2870, { 80, 0, 0, 0, 0 } },
  // Hot Shot
  { 2872, { 120, 0, 0, 0, 0 } },
  // Clean Shot
  { 2873, { 100, 0, 0, 0, 0 } },
  // Gauss Round
  { 2874, { 210, 0, 0, 0, 0 } },
  // Heartbreak
  { 2875, { 240, 0, 0, 0, 0 } },
  // Reassemble
  { 2876, { 0, 0, 0, 0, 0 } },
  // Wildfire
  { 2878, { 0, 0, 0, 0, 0 } },
  // Quick Reload
  { 2879, { 0, 0, 0, 0, 0 } },
  // Gauss Barrel
  { 2880, { 0, 0, 0, 0, 0 } },
  // Rapid Fire
  { 2881, { 0, 0, 0, 0, 0 } },
  // Hypercharge
  { 2885, { 0, 0, 0, 0, 0 } },
  // Dismantle
  { 2887, { 0, 0, 0, 0, 0 } },
  // Blank
  { 2888, { 0, 0, 0, 0, 0 } },
  // Ricochet
  { 2890, { 320, 0, 0, 0, 0 } },
  // Raiton
  { 3203, { 0, 0, 0, 0, 0 } },
  // Raiton
  { 3204, { 0, 0, 0, 0, 0 } },
  // Kanashibari
  { 3207, { 0, 0, 0, 0, 0 } },
  // Turret Retrieval
  { 3487, { 0, 0, 0, 0, 0 } },
  // Goring Blade
  { 3538, { 100, 0, 0, 0, 0 } },
  // Royal Authority
  { 3539, { 100, 0, 0, 0, 0 } },
  // Divine Veil
  { 3540, { 0, 0, 0, 0, 0 } },
  // Clemency
  { 3541, { 0, 0, 0, 0, 1200 } },
  // Sheltron
  { 3542, { 0, 0, 0, 0, 0 } },
  // Tornado Kick
  { 3543, { 330, 0, 0, 0, 0 } },
  // Purification
  { 3544, { 0, 0, 0, 0, 0 } },
  // Elixir Field
  { 3545, { 220, 0, 0, 0, 0 } },
  // Meditation
  { 3546, { 0, 0, 0, 0, 0 } },
  // the Forbidden Chakra
  { 3547, { 250, 0, 0, 0, 0 } },
  // Deliverance
  { 3548, { 0, 0, 0, 0, 0 } },
  // Fell Cleave
  { 3549, { 520, 0, 0, 0, 0 } },
  // Decimate
  { 3550, { 280, 0, 0, 0, 0 } },
  // Raw Intuition
  { 3551, { 0, 0, 0, 0, 0 } },
  // Equilibrium
  { 3552, { 0, 0, 0, 0, 1200 } },
  // Blood of the Dragon
  { 3553, { 0, 0, 0, 0, 0 } },
  // Fang and Claw
  { 3554, { 260, 300, 0, 0, 0 } },
  // Geirskogul
  { 3555, { 230, 0, 0, 0, 0 } },
  // Wheeling Thrust
  { 3556, { 260, 0, 0, 300, 0 } },
  // Battle Litany
  { 3557, { 0, 0, 0, 0, 0 } },
  // Empyreal Arrow
  { 3558, { 230, 0, 0, 0, 0 } },
  // the Wanderer's Minuet
  { 3559, { 100, 0, 0, 0, 0 } },
  // Iron Jaws
  { 3560, { 100, 0, 0, 0, 0 } },
  // the Warden's Paean
  { 3561, { 0, 0, 0, 0, 0 } },
  // Sidewinder
  { 3562, { 100, 0, 0, 0, 0 } },
  // Armor Crush
  { 3563, { 100, 160, 0, 0, 0 } },
  // Shadewalker
  { 3564, { 0, 0, 0, 0, 0 } },
  // Smoke Screen
  { 3565, { 0, 0, 0, 0, 0 } },
  // Dream Within a Dream
  { 3566, { 150, 0, 0, 0, 0 } },
  // Duality
  { 3567, { 0, 0, 0, 0, 0 } },
  // Stone III
  { 3568, { 210, 0, 0, 0, 0 } },
  // Asylum
  { 3569, { 0, 0, 0, 0, 100 } },
  // Tetragrammaton
  { 3570, { 0, 0, 0, 0, 700 } },
  // Assize
  { 3571, { 400, 0, 0, 0, 400 } },
  // Aero III
  { 3572, { 50, 0, 0, 0, 0 } },
  // Ley Lines
  { 3573, { 0, 0, 0, 0, 0 } },
  // Sharpcast
  { 3574, { 0, 0, 0, 0, 0 } },
  // Enochian
  { 3575, { 0, 0, 0, 0, 0 } },
  // Blizzard IV
  { 3576, { 260, 0, 0, 0, 0 } },
  // Fire IV
  { 3577, { 300, 0, 0, 0, 0 } },
  // Painflare
  { 3578, { 180, 0, 0, 0, 0 } },
  // Ruin III
  { 3579, { 120, 0, 0, 0, 0 } },
  // Tri-disaster
  { 3580, { 0, 0, 0, 0, 0 } },
  // Dreadwyrm Trance
  { 3581, { 0, 0, 0, 0, 0 } },
  // Deathflare
  { 3582, { 400, 0, 0, 0, 0 } },
  // Indomitability
  { 3583, { 0, 0, 0, 0, 500 } },
  // Broil
  { 3584, { 190, 0, 0, 0, 0 } },
  // Deployment Tactics
  { 3585, { 0, 0, 0, 0, 0 } },
  // Emergency Tactics
  { 3586, { 0, 0, 0, 0, 0 } },
  // Dissipation
  { 3587, { 0, 0, 0, 0, 0 } },
  // Draw
  { 3590, { 0, 0, 0, 0, 0 } },
  // Royal Road
  { 3591, { 0, 0, 0, 0, 0 } },
  // Spread
  { 3592, { 0, 0, 0, 0, 0 } },
  // Redraw
  { 3593, { 0, 0, 0, 0, 0 } },
  // Benefic
  { 3594, { 0, 0, 0, 0, 400 } },
  // Aspected Benefic
  { 3595, { 0, 0, 0, 0, 200 } },
  // Malefic
  { 3596, { 150, 0, 0, 0, 0 } },
  // Malefic II
  { 3598, { 180, 0, 0, 0, 0 } },
  // Combust
  { 3599, { 0, 0, 0, 0, 0 } },
  // Helios
  { 3600, { 0, 0, 0, 0, 300 } },
  // Aspected Helios
  { 3601, { 0, 0, 0, 0, 200 } },
  // Ascend
  { 3603, { 0, 0, 0, 0, 0 } },
  // Diurnal Sect
  { 3604, { 0, 0, 0, 0, 0 } },
  // Nocturnal Sect
  { 3605, { 0, 0, 0, 0, 0 } },
  // Lightspeed
  { 3606, { 0, 0, 0, 0, 0 } },
  // Combust II
  { 3608, { 0, 0, 0, 0, 0 } },
  // Benefic II
  { 3610, { 0, 0, 0, 0, 650 } },
  // Time Dilation
  { 3611, { 0, 0, 0, 0, 0 } },
  // Synastry
  { 3612, { 0, 0, 0, 0, 0 } },
  // Collective Unconscious
  { 3613, { 0, 0, 0, 0, 150 } },
  // Essential Dignity
  { 3614, { 0, 0, 0, 0, 400 } },
  // Gravity
  { 3615, { 200, 0, 0, 0, 0 } },
  // Celestial Opposition
  { 3616, { 0, 0, 0, 0, 0 } },
  // Hard Slash
  { 3617, { 150, 0, 0, 0, 0 } },
  // Spinning Slash
  { 3619, { 100, 0, 0, 0, 0 } },
  // Unleash
  { 3621, { 50, 0, 0, 0, 0 } },
  // Syphon Strike
  { 3623, { 100, 0, 0, 0, 0 } },
  // Unmend
  { 3624, { 150, 0, 0, 0, 0 } },
  // Blood Weapon
  { 3625, { 0, 0, 0, 0, 0 } },
  // Power Slash
  { 3627, { 100, 0, 0, 0, 0 } },
  // Darkside
  { 3628, { 0, 0, 0, 0, 0 } },
  // Grit
  { 3629, { 0, 0, 0, 0, 0 } },
  // Blood Price
  { 3631, { 0, 0, 0, 0, 0 } },
  // Souleater
  { 3632, { 100, 0, 0, 0, 0 } },
  // Dark Passenger
  { 3633, { 140, 0, 0, 0, 0 } },
  // Dark Mind
  { 3634, { 0, 0, 0, 0, 0 } },
  // Dark Arts
  { 3635, { 0, 0, 0, 0, 0 } },
  // Shadow Wall
  { 3636, { 0, 0, 0, 0, 0 } },
  // Living Dead
  { 3638, { 0, 0, 0, 0, 0 } },
  // Salted Earth
  { 3639, { 75, 0, 0, 0, 0 } },
  // Plunge
  { 3640, { 200, 0, 0, 0, 0 } },
  // Abyssal Drain
  { 3641, { 120, 0, 0, 0, 0 } },
  // Sole Survivor
  { 3642, { 0, 0, 0, 0, 0 } },
  // Carve and Spit
  { 3643, { 100, 0, 0, 0, 0 } },
  // Big Shot
  { 4238, { 0, 0, 0, 0, 0 } },
  // Desperado
  { 4239, { 0, 0, 0, 0, 0 } },
  // Land Waker
  { 4240, { 0, 0, 0, 0, 0 } },
  // Dark Force
  { 4241, { 0, 0, 0, 0, 0 } },
  // Dragonsong Dive
  { 4242, { 0, 0, 0, 0, 0 } },
  // Chimatsuri
  { 4243, { 0, 0, 0, 0, 0 } },
  // Sagittarius Arrow
  { 4244, { 0, 0, 0, 0, 0 } },
  // Satellite Beam
  { 4245, { 0, 0, 0, 0, 0 } },
  // Teraflare
  { 4246, { 0, 0, 0, 0, 0 } },
  // Angel Feathers
  { 4247, { 0, 0, 0, 0, 0 } },
  // Astral Stasis
  { 4248, { 0, 0, 0, 0, 0 } },
  // Form Shift
  { 4262, { 0, 0, 0, 0, 0 } },
  // Cannonfire
  { 4271, { 0, 0, 0, 0, 0 } },
  // the Balance
  { 4401, { 0, 0, 0, 0, 0 } },
  // the Bole
  { 4402, { 0, 0, 0, 0, 0 } },
  // the Arrow
  { 4403, { 0, 0, 0, 0, 0 } },
  // the Spear
  { 4404, { 0, 0, 0, 0, 0 } },
  // the Ewer
  { 4405, { 0, 0, 0, 0, 0 } },
  // the Spire
  { 4406, { 0, 0, 0, 0, 0 } },
  // the Balance
  { 4407, { 0, 0, 0, 0, 0 } },
  // the Bole
  { 4408, { 0, 0, 0, 0, 0 } },
  // the Arrow
  { 4409, { 0, 0, 0, 0, 0 } },
  // the Spear
  { 4410, { 0, 0, 0, 0, 0 } },
  // the Ewer
  { 4411, { 0, 0, 0, 0, 0 } },
  // the Spire
  { 4412, { 0, 0, 0, 0, 0 } },
  // the Balance
  { 4413, { 0, 0, 0, 0, 0 } },
  // the Bole
  { 4414, { 0, 0, 0, 0, 0 } },
  // the Arrow
  { 4415, { 0, 0, 0, 0, 0 } },
  // the Spear
  { 4416, { 0, 0, 0, 0, 0 } },
  // the Ewer
  { 4417, { 0, 0, 0, 0, 0 } },
  // the Spire
  { 4418, { 0, 0, 0, 0, 0 } },
  // the Balance
  { 4419, { 0, 0, 0, 0, 0 } },
  // the Bole
  { 4420, { 0, 0, 0, 0, 0 } },
  // the Arrow
  { 4421, { 0, 0, 0, 0, 0 } },
  // the Spear
  { 4422, { 0, 0, 0, 0, 0 } },
  // the Ewer
  { 4423, { 0, 0, 0, 0, 0 } },
  // the Spire
  { 4424, { 0, 0, 0, 0, 0 } },
  // Empty Road
  { 4645, { 0, 0, 0, 0, 0 } },
  // Undraw Spread
  { 4646, { 0, 0, 0, 0, 0 } },
  // Raiton
  { 4977, { 0, 0, 0, 0, 0 } },
  // Raiton
  { 5069, { 0, 0, 0, 0, 0 } },
  // attack
  { 5199, { 0, 0, 0, 0, 0 } },
  // attack
  { 5846, { 0, 0, 0, 0, 0 } },
  // Stickyloom
  { 5874, { 0, 0, 0, 0, 0 } },
  // Void Fire II
  { 6274, { 0, 0, 0, 0, 0 } },
  // Total Eclipse
  { 7381, { 110, 0, 0, 0, 0 } },
  // Intervention
  { 7382, { 0, 0, 0, 0, 0 } },
  // Requiescat
  { 7383, { 350, 0, 0, 0, 0 } },
  // Holy Spirit
  { 7384, { 380, 0, 0, 0, 0 } },
  // Passage of Arms
  { 7385, { 0, 0, 0, 0, 0 } },
  // Onslaught
  { 7386, { 100, 0, 0, 0, 0 } },
  // Upheaval
  { 7387, { 300, 0, 0, 0, 0 } },
  // Shake It Off
  { 7388, { 0, 0, 0, 0, 0 } },
  // Inner Release
  { 7389, { 0, 0, 0, 0, 0 } },
  // Delirium
  { 7390, { 0, 0, 0, 0, 0 } },
  // Quietus
  { 7391, { 160, 0, 0, 0, 0 } },
  // Bloodspiller
  { 7392, { 400, 0, 0, 0, 0 } },
  // The Blackest Night
  { 7393, { 0, 0, 0, 0, 0 } },
  // Riddle of Earth
  { 7394, { 0, 0, 0, 0, 0 } },
  // Riddle of Fire
  { 7395, { 0, 0, 0, 0, 0 } },
  // Brotherhood
  { 7396, { 0, 0, 0, 0, 0 } },
  // Sonic Thrust
  { 7397, { 100, 0, 0, 0, 0 } },
  // Dragon Sight
  { 7398, { 0, 0, 0, 0, 0 } },
  // Mirage Dive
  { 7399, { 210, 0, 0, 0, 0 } },
  // Nastrond
  { 7400, { 330, 0, 0, 0, 0 } },
  // Hellfrog Medium
  { 7401, { 400, 0, 0, 0, 0 } },
  // Bhavacakra
  { 7402, { 600, 0, 0, 0, 0 } },
  // Ten Chi Jin
  { 7403, { 0, 0, 0, 0, 0 } },
  // Pitch Perfect
  { 7404, { 100, 0, 0, 0, 0 } },
  // Troubadour
  { 7405, { 0, 0, 0, 0, 0 } },
  // Caustic Bite
  { 7406, { 120, 0, 0, 0, 0 } },
  // Stormbite
  { 7407, { 120, 0, 0, 0, 0 } },
  // Nature's Minne
  { 7408, { 0, 0, 0, 0, 0 } },
  // Refulgent Arrow
  { 7409, { 300, 0, 0, 0, 0 } },
  // Cooldown
  { 7410, { 150, 0, 0, 0, 0 } },
  // Heated Split Shot
  { 7411, { 190, 0, 0, 0, 0 } },
  // Heated Slug Shot
  { 7412, { 100, 0, 0, 0, 0 } },
  // Heated Clean Shot
  { 7413, { 100, 0, 0, 0, 0 } },
  // Barrel Stabilizer
  { 7414, { 0, 0, 0, 0, 0 } },
  // Rook Overdrive
  { 7415, { 0, 0, 0, 0, 0 } },
  // Flamethrower
  { 7418, { 0, 0, 0, 0, 0 } },
  // Between the Lines
  { 7419, { 0, 0, 0, 0, 0 } },
  // Thunder IV
  { 7420, { 50, 0, 0, 0, 0 } },
  // Triplecast
  { 7421, { 0, 0, 0, 0, 0 } },
  // Foul
  { 7422, { 650, 0, 0, 0, 0 } },
  // Aetherpact
  { 7423, { 0, 0, 0, 0, 0 } },
  // Bio III
  { 7424, { 0, 0, 0, 0, 0 } },
  // Miasma III
  { 7425, { 50, 0, 0, 0, 0 } },
  // Ruin IV
  { 7426, { 200, 0, 0, 0, 0 } },
  // Summon Bahamut
  { 7427, { 0, 0, 0, 0, 0 } },
  // Enkindle Bahamut
  { 7429, { 0, 0, 0, 0, 0 } },
  // Thin Air
  { 7430, { 0, 0, 0, 0, 0 } },
  // Stone IV
  { 7431, { 250, 0, 0, 0, 0 } },
  // Divine Benison
  { 7432, { 0, 0, 0, 0, 0 } },
  // Plenary Indulgence
  { 7433, { 0, 0, 0, 0, 0 } },
  // Excogitation
  { 7434, { 0, 0, 0, 0, 800 } },
  // Broil II
  { 7435, { 230, 0, 0, 0, 0 } },
  // Chain Stratagem
  { 7436, { 0, 0, 0, 0, 0 } },
  // Aetherpact
  { 7437, { 0, 0, 0, 0, 0 } },
  // Earthly Star
  { 7439, { 150, 0, 0, 0, 540 } },
  // Malefic III
  { 7442, { 220, 0, 0, 0, 0 } },
  // Minor Arcana
  { 7443, { 0, 0, 0, 0, 0 } },
  // Lord of Crowns
  { 7444, { 300, 0, 0, 0, 0 } },
  // Lady of Crowns
  { 7445, { 0, 0, 0, 0, 500 } },
  // Thunder II
  { 7447, { 30, 0, 0, 0, 0 } },
  // Sleeve Draw
  { 7448, { 0, 0, 0, 0, 0 } },
  // Hakaze
  { 7477, { 150, 0, 0, 0, 0 } },
  // Jinpu
  { 7478, { 100, 0, 0, 0, 0 } },
  // Shifu
  { 7479, { 100, 0, 0, 0, 0 } },
  // Yukikaze
  { 7480, { 100, 0, 0, 0, 0 } },
  // Gekko
  { 7481, { 100, 0, 0, 0, 0 } },
  // Kasha
  { 7482, { 100, 0, 0, 0, 0 } },
  // Fuga
  { 7483, { 100, 0, 0, 0, 0 } },
  // Mangetsu
  { 7484, { 100, 0, 0, 0, 0 } },
  // Oka
  { 7485, { 100, 0, 0, 0, 0 } },
  // Enpi
  { 7486, { 100, 0, 0, 0, 0 } },
  // Midare Setsugekka
  { 7487, { 720, 0, 0, 0, 0 } },
  // Tenka Goken
  { 7488, { 360, 0, 0, 0, 0 } },
  // Higanbana
  { 7489, { 240, 0, 0, 0, 0 } },
  // Hissatsu: Shinten
  { 7490, { 300, 0, 0, 0, 0 } },
  // Hissatsu: Kyuten
  { 7491, { 150, 0, 0, 0, 0 } },
  // Hissatsu: Gyoten
  { 7492, { 100, 0, 0, 0, 0 } },
  // Hissatsu: Yaten
  { 7493, { 100, 0, 0, 0, 0 } },
  // Hissatsu: Kaiten
  { 7494, { 0, 0, 0, 0, 0 } },
  // Hagakure
  { 7495, { 0, 0, 0, 0, 0 } },
  // Hissatsu: Guren
  { 7496, { 800, 0, 0, 0, 0 } },
  // Meditate
  { 7497, { 0, 0, 0, 0, 0 } },
  // Third Eye
  { 7498, { 0, 0, 0, 0, 0 } },
  // Meikyo Shisui
  { 7499, { 0, 0, 0, 0, 0 } },
  // Ageha
  { 7500, { 250, 0, 0, 0, 0 } },
  // Hissatsu: Seigan
  { 7501, { 200, 0, 0, 0, 0 } },
  // Merciful Eyes
  { 7502, { 0, 0, 0, 0, 200 } },
  // Jolt
  { 7503, { 180, 0, 0, 0, 0 } },
  // Riposte
  { 7504, { 130, 0, 0, 0, 0 } },
  // Verthunder
  { 7505, { 310, 0, 0, 0, 0 } },
  // Corps-a-corps
  { 7506, { 130, 0, 0, 0, 0 } },
  // Veraero
  { 7507, { 310, 0, 0, 0, 0 } },
  // Tether
  { 7508, { 0, 0, 0, 0, 0 } },
  // Scatter
  { 7509, { 100, 0, 0, 0, 0 } },
  // Verfire
  { 7510, { 270, 0, 0, 0, 0 } },
  // Verstone
  { 7511, { 270, 0, 0, 0, 0 } },
  // Zwerchhau
  { 7512, { 100, 0, 0, 0, 0 } },
  // Moulinet
  { 7513, { 60, 0, 0, 0, 0 } },
  // Vercure
  { 7514, { 0, 0, 0, 0, 350 } },
  // Displacement
  { 7515, { 130, 0, 0, 0, 0 } },
  // Redoublement
  { 7516, { 100, 0, 0, 0, 0 } },
  // Fleche
  { 7517, { 420, 0, 0, 0, 0 } },
  // Acceleration
  { 7518, { 0, 0, 0, 0, 0 } },
  // Contre Sixte
  { 7519, { 350, 0, 0, 0, 0 } },
  // Embolden
  { 7520, { 0, 0, 0, 0, 0 } },
  // Manafication
  { 7521, { 0, 0, 0, 0, 0 } },
  // Impact
  { 7522, { 270, 0, 0, 0, 0 } },
  // Verraise
  { 7523, { 0, 0, 0, 0, 0 } },
  // Jolt II
  { 7524, { 240, 0, 0, 0, 0 } },
  // Verflare
  { 7525, { 600, 0, 0, 0, 0 } },
  // Verholy
  { 7526, { 600, 0, 0, 0, 0 } },
  // Enchanted Riposte
  { 7527, { 210, 0, 0, 0, 0 } },
  // Enchanted Zwerchhau
  { 7528, { 100, 0, 0, 0, 0 } },
  // Enchanted Redoublement
  { 7529, { 100, 0, 0, 0, 0 } },
  // Enchanted Moulinet
  { 7530, { 200, 0, 0, 0, 0 } },
  // Magitek Cannon
  { 7619, { 0, 0, 0, 0, 0 } },
  // Photon Stream
  { 7620, { 0, 0, 0, 0, 0 } },
  // Diffractive Magitek Cannon
  { 7621, { 0, 0, 0, 0, 0 } },
  // High-powered Magitek Cannon
  { 7622, { 0, 0, 0, 0, 0 } },
  // Doom of the Living
  { 7861, { 0, 0, 0, 0, 0 } },
  // Vermillion Scourge
  { 7862, { 0, 0, 0, 0, 0 } },
  // Earth Tackle
  { 7864, { 100, 0, 0, 0, 0 } },
  // Wind Tackle
  { 7865, { 65, 0, 0, 0, 0 } },
  // Fire Tackle
  { 7866, { 130, 0, 0, 0, 0 } },
  // Iaijutsu
  { 7867, { 0, 0, 0, 0, 0 } },
  // Riddle of Wind
  { 7868, { 65, 0, 0, 0, 0 } },
  // Dissolve Union
  { 7869, { 0, 0, 0, 0, 0 } },
  // Stellar Detonation
  { 8324, { 150, 0, 0, 0, 540 } },
  // Broken Ridge
  { 8395, { 0, 0, 0, 0, 0 } },
  // Magitek Pulse
  { 8624, { 0, 0, 0, 0, 0 } },
  // Magitek Thunder
  { 8625, { 0, 0, 0, 0, 0 } },
  // attack
  { 8687, { 0, 0, 0, 0, 0 } },
  // Katon
  { 9012, { 0, 0, 0, 0, 0 } },
  // Remove Barrel
  { 9015, { 0, 0, 0, 0, 0 } },
  // Tenka Goken
  { 9143, { 0, 0, 0, 0, 0 } },
  // Thunderous Force
  { 9294, { 0, 0, 0, 0, 0 } },
  // Raiton
  { 9301, { 0, 0, 0, 0, 0 } },
  // Raiton
  { 9302, { 0, 0, 0, 0, 0 } },
  // Bishop Overdrive
  { 9372, { 0, 0, 0, 0, 0 } },
  // Undraw
  { 9629, { 0, 0, 0, 0, 0 } },
  // Self-detonate
  { 9775, { 0, 0, 0, 0, 0 } },
  // Shatterstone
  { 9823, { 0, 0, 0, 0, 0 } },
  // attack
  { 9996, { 0, 0, 0, 0, 0 } },
  // Ungarmax
  { 10001, { 0, 0, 0, 0, 0 } },
  // Starstorm
  { 10894, { 0, 0, 0, 0, 0 } },
  // attack
  { 10946, { 0, 0, 0, 0, 0 } },
  // attack
  { 10947, { 0, 0, 0, 0, 0 } },
  // Ruin III
  { 11191, { 200, 0, 0, 0, 0 } },
  // Physick
  { 11192, { 0, 0, 0, 0, 400 } },
  // Starstorm
  { 11193, { 3600, 0, 0, 0, 0 } },
  // Snort
  { 11383, { 0, 0, 0, 0, 0 } },
  // 4-tonze Weight
  { 11384, { 110, 0, 0, 0, 0 } },
  // Water Cannon
  { 11385, { 120, 0, 0, 0, 0 } },
  // Song of Torment
  { 11386, { 50, 0, 0, 0, 0 } },
  // High Voltage
  { 11387, { 90, 0, 0, 0, 0 } },
  // Bad Breath
  { 11388, { 0, 0, 0, 0, 0 } },
  // Flying Frenzy
  { 11389, { 80, 0, 0, 0, 0 } },
  // Aqua Breath
  { 11390, { 90, 0, 0, 0, 0 } },
  // Plaincracker
  { 11391, { 130, 0, 0, 0, 0 } },
  // Acorn Bomb
  { 11392, { 0, 0, 0, 0, 0 } },
  // Bristle
  { 11393, { 0, 0, 0, 0, 0 } },
  // Mind Blast
  { 11394, { 100, 0, 0, 0, 0 } },
  // Blood Drain
  { 11395, { 20, 0, 0, 0, 0 } },
  // Bomb Toss
  { 11396, { 110, 0, 0, 0, 0 } },
  // 1000 Needles
  { 11397, { 0, 0, 0, 0, 0 } },
  // Drill Cannons
  { 11398, { 120, 0, 0, 0, 0 } },
  // the Look
  { 11399, { 130, 0, 0, 0, 0 } },
  // Sharpened Knife
  { 11400, { 120, 0, 0, 0, 0 } },
  // Loom
  { 11401, { 0, 0, 0, 0, 0 } },
  // Flame Thrower
  { 11402, { 130, 0, 0, 0, 0 } },
  // Faze
  { 11403, { 0, 0, 0, 0, 0 } },
  // Glower
  { 11404, { 130, 0, 0, 0, 0 } },
  // Missile
  { 11405, { 0, 0, 0, 0, 0 } },
  // White Wind
  { 11406, { 0, 0, 0, 0, 0 } },
  // Final Sting
  { 11407, { 1500, 0, 0, 0, 0 } },
  // Self-destruct
  { 11408, { 900, 0, 0, 0, 0 } },
  // Transfusion
  { 11409, { 0, 0, 0, 0, 0 } },
  // Toad Oil
  { 11410, { 0, 0, 0, 0, 0 } },
  // Off-guard
  { 11411, { 0, 0, 0, 0, 0 } },
  // Sticky Tongue
  { 11412, { 0, 0, 0, 0, 0 } },
  // Tail Screw
  { 11413, { 0, 0, 0, 0, 0 } },
  // Level 5 Petrify
  { 11414, { 0, 0, 0, 0, 0 } },
  // Moon Flute
  { 11415, { 0, 0, 0, 0, 0 } },
  // Doom
  { 11416, { 0, 0, 0, 0, 0 } },
  // Mighty Guard
  { 11417, { 0, 0, 0, 0, 0 } },
  // Ice Spikes
  { 11418, { 0, 0, 0, 0, 0 } },
  // the Ram's Voice
  { 11419, { 130, 0, 0, 0, 0 } },
  // the Dragon's Voice
  { 11420, { 110, 0, 0, 0, 0 } },
  // Peculiar Light
  { 11421, { 0, 0, 0, 0, 0 } },
  // Ink Jet
  { 11422, { 120, 0, 0, 0, 0 } },
  // Flying Sardine
  { 11423, { 10, 0, 0, 0, 0 } },
  // Diamondback
  { 11424, { 0, 0, 0, 0, 0 } },
  // Fire Angon
  { 11425, { 100, 0, 0, 0, 0 } },
  // Feather Rain
  { 11426, { 180, 0, 0, 0, 0 } },
  // Eruption
  { 11427, { 220, 0, 0, 0, 0 } },
  // Mountain Buster
  { 11428, { 310, 0, 0, 0, 0 } },
  // Shock Strike
  { 11429, { 310, 0, 0, 0, 0 } },
  // Glass Dance
  { 11430, { 290, 0, 0, 0, 0 } },
  // Veil of the Whorl
  { 11431, { 0, 0, 0, 0, 0 } },
  // Tri-shackle
  { 11482, { 30, 0, 0, 0, 0 } },
  // attack
  { 11784, { 0, 0, 0, 0, 0 } },
  // Stone of the Seventh Dawn
  { 13423, { 140, 0, 0, 0, 0 } },
  // Aero of the Seventh Dawn
  { 13424, { 50, 0, 0, 0, 0 } },
  // Cure of the Seventh Dawn
  { 13425, { 0, 0, 0, 0, 700 } },
  // Aetherwell
  { 13426, { 0, 0, 0, 0, 0 } },
  // Thunderous Force
  { 14587, { 0, 0, 0, 0, 0 } },
  // Kyokufu
  { 14840, { 180, 0, 0, 0, 0 } },
  // Ajisai
  { 14841, { 100, 0, 0, 0, 0 } },
  // Hissatsu: Gyoten
  { 14842, { 100, 0, 0, 0, 0 } },
  // 冥界恐叫打
  { 14843, { 0, 0, 0, 0, 0 } },
  // Second Wind
  { 15375, { 0, 0, 0, 0, 500 } },

};