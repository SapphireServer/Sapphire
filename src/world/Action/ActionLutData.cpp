#include "ActionLut.h"

using namespace Sapphire::World::Action;

ActionLut::Lut ActionLut::m_actionLut =
{
  // attack
  { 7, { 0, 0, 0, 0, 0, 0 } },
  // Shot
  { 8, { 0, 0, 0, 0, 0, 0 } },
  // Fast Blade
  { 9, { 200, 0, 0, 0, 0, 0 } },
  // Riot Blade
  { 15, { 100, 300, 0, 0, 0, 0 } },
  // Shield Bash
  { 16, { 110, 0, 0, 0, 0, 0 } },
  // Sentinel
  { 17, { 0, 0, 0, 0, 0, 0 } },
  // Fight or Flight
  { 20, { 0, 0, 0, 0, 0, 0 } },
  // Rage of Halone
  { 21, { 100, 350, 0, 0, 0, 0 } },
  // Circle of Scorn
  { 23, { 120, 0, 0, 0, 0, 0 } },
  // Shield Lob
  { 24, { 120, 0, 0, 0, 0, 0 } },
  // Cover
  { 27, { 0, 0, 0, 0, 0, 0 } },
  // Iron Will
  { 28, { 0, 0, 0, 0, 0, 0 } },
  // Spirits Within
  { 29, { 370, 0, 0, 0, 0, 0 } },
  // Hallowed Ground
  { 30, { 0, 0, 0, 0, 0, 0 } },
  // Heavy Swing
  { 31, { 200, 0, 0, 0, 0, 0 } },
  // Maim
  { 37, { 100, 300, 0, 0, 0, 0 } },
  // Berserk
  { 38, { 0, 0, 0, 0, 0, 0 } },
  // Thrill of Battle
  { 40, { 0, 0, 0, 0, 0, 0 } },
  // Overpower
  { 41, { 130, 0, 0, 0, 0, 0 } },
  // Storm's Path
  { 42, { 100, 380, 0, 0, 0, 250 } },
  // Holmgang
  { 43, { 0, 0, 0, 0, 0, 0 } },
  // Vengeance
  { 44, { 55, 0, 0, 0, 0, 0 } },
  // Storm's Eye
  { 45, { 100, 380, 0, 0, 0, 0 } },
  // Tomahawk
  { 46, { 140, 0, 0, 0, 0, 0 } },
  // Defiance
  { 48, { 0, 0, 0, 0, 0, 0 } },
  // Inner Beast
  { 49, { 350, 0, 0, 0, 0, 0 } },
  // Steel Cyclone
  { 51, { 220, 0, 0, 0, 0, 0 } },
  // Infuriate
  { 52, { 0, 0, 0, 0, 0, 0 } },
  // Bootshine
  { 53, { 150, 0, 0, 0, 0, 0 } },
  // True Strike
  { 54, { 220, 0, 0, 0, 240, 0 } },
  // Snap Punch
  { 56, { 210, 0, 230, 0, 0, 0 } },
  // Fists of Earth
  { 60, { 0, 0, 0, 0, 0, 0 } },
  // Twin Snakes
  { 61, { 150, 0, 170, 0, 0, 0 } },
  // Arm of the Destroyer
  { 62, { 80, 0, 0, 0, 0, 0 } },
  // Fists of Fire
  { 63, { 0, 0, 0, 0, 0, 0 } },
  // Mantra
  { 65, { 0, 0, 0, 0, 0, 0 } },
  // Demolish
  { 66, { 70, 0, 0, 0, 90, 0 } },
  // Perfect Balance
  { 69, { 0, 0, 0, 0, 0, 0 } },
  // Rockbreaker
  { 70, { 120, 0, 0, 0, 0, 0 } },
  // Shoulder Tackle
  { 71, { 100, 0, 0, 0, 0, 0 } },
  // Fists of Wind
  { 73, { 0, 0, 0, 0, 0, 0 } },
  // Dragon Kick
  { 74, { 180, 0, 200, 0, 0, 0 } },
  // True Thrust
  { 75, { 0, 0, 0, 0, 0, 0 } },
  // Vorpal Thrust
  { 78, { 0, 0, 0, 0, 0, 0 } },
  // Life Surge
  { 83, { 0, 0, 0, 0, 0, 0 } },
  // Full Thrust
  { 84, { 100, 530, 0, 0, 0, 0 } },
  // Lance Charge
  { 85, { 0, 0, 0, 0, 0, 0 } },
  // Doom Spike
  { 86, { 170, 0, 0, 0, 0, 0 } },
  // Disembowel
  { 87, { 0, 0, 0, 0, 0, 0 } },
  // Chaos Thrust
  { 88, { 100, 290, 0, 0, 140, 0 } },
  // Piercing Talon
  { 90, { 150, 0, 0, 0, 0, 0 } },
  // Jump
  { 92, { 310, 0, 0, 0, 0, 0 } },
  // Elusive Jump
  { 94, { 0, 0, 0, 0, 0, 0 } },
  // Spineshatter Dive
  { 95, { 240, 0, 0, 0, 0, 0 } },
  // Dragonfire Dive
  { 96, { 380, 0, 0, 0, 0, 0 } },
  // Heavy Shot
  { 97, { 180, 0, 0, 0, 0, 0 } },
  // Straight Shot
  { 98, { 200, 0, 0, 0, 0, 0 } },
  // Venomous Bite
  { 100, { 100, 0, 0, 0, 0, 0 } },
  // Raging Strikes
  { 101, { 0, 0, 0, 0, 0, 0 } },
  // Quick Nock
  { 106, { 150, 0, 0, 0, 0, 0 } },
  // Barrage
  { 107, { 0, 0, 0, 0, 0, 0 } },
  // Bloodletter
  { 110, { 150, 0, 0, 0, 0, 0 } },
  // Repelling Shot
  { 112, { 0, 0, 0, 0, 0, 0 } },
  // Windbite
  { 113, { 60, 0, 0, 0, 0, 0 } },
  // Mage's Ballad
  { 114, { 100, 0, 0, 0, 0, 0 } },
  // Army's Paeon
  { 116, { 100, 0, 0, 0, 0, 0 } },
  // Rain of Death
  { 117, { 130, 0, 0, 0, 0, 0 } },
  // Battle Voice
  { 118, { 0, 0, 0, 0, 0, 0 } },
  // Stone
  { 119, { 140, 0, 0, 0, 0, 0 } },
  // Cure
  { 120, { 0, 0, 0, 0, 0, 450 } },
  // Aero
  { 121, { 50, 0, 0, 0, 0, 0 } },
  // Medica
  { 124, { 0, 0, 0, 0, 0, 300 } },
  // Raise
  { 125, { 0, 0, 0, 0, 0, 0 } },
  // Stone II
  { 127, { 200, 0, 0, 0, 0, 0 } },
  // Cure III
  { 131, { 0, 0, 0, 0, 0, 550 } },
  // Aero II
  { 132, { 60, 0, 0, 0, 0, 0 } },
  // Medica II
  { 133, { 0, 0, 0, 0, 0, 200 } },
  // Fluid Aura
  { 134, { 0, 0, 0, 0, 0, 0 } },
  // Cure II
  { 135, { 0, 0, 0, 0, 0, 700 } },
  // Presence of Mind
  { 136, { 0, 0, 0, 0, 0, 0 } },
  // Regen
  { 137, { 0, 0, 0, 0, 0, 200 } },
  // Holy
  { 139, { 140, 0, 0, 0, 0, 0 } },
  // Benediction
  { 140, { 0, 0, 0, 0, 0, 0 } },
  // Fire
  { 141, { 180, 0, 0, 0, 0, 0 } },
  // Blizzard
  { 142, { 180, 0, 0, 0, 0, 0 } },
  // Thunder
  { 144, { 30, 0, 0, 0, 0, 0 } },
  // Sleep
  { 145, { 0, 0, 0, 0, 0, 0 } },
  // Blizzard II
  { 146, { 50, 0, 0, 0, 0, 0 } },
  // Fire II
  { 147, { 80, 0, 0, 0, 0, 0 } },
  // Transpose
  { 149, { 0, 0, 0, 0, 0, 0 } },
  // Fire III
  { 152, { 240, 0, 0, 0, 0, 0 } },
  // Thunder III
  { 153, { 70, 0, 0, 0, 0, 0 } },
  // Blizzard III
  { 154, { 240, 0, 0, 0, 0, 0 } },
  // Aetherial Manipulation
  { 155, { 0, 0, 0, 0, 0, 0 } },
  // Scathe
  { 156, { 100, 0, 0, 0, 0, 0 } },
  // Manaward
  { 157, { 0, 0, 0, 0, 0, 0 } },
  // Manafont
  { 158, { 0, 0, 0, 0, 0, 0 } },
  // Freeze
  { 159, { 100, 0, 0, 0, 0, 0 } },
  // Flare
  { 162, { 260, 0, 0, 0, 0, 0 } },
  // Ruin
  { 163, { 80, 0, 0, 0, 0, 0 } },
  // Bio
  { 164, { 0, 0, 0, 0, 0, 0 } },
  // Summon
  { 165, { 0, 0, 0, 0, 0, 0 } },
  // Aetherflow
  { 166, { 0, 0, 0, 0, 0, 0 } },
  // Miasma
  { 168, { 20, 0, 0, 0, 0, 0 } },
  // Summon II
  { 170, { 0, 0, 0, 0, 0, 0 } },
  // Ruin II
  { 172, { 80, 0, 0, 0, 0, 0 } },
  // Resurrection
  { 173, { 0, 0, 0, 0, 0, 0 } },
  // Bane
  { 174, { 0, 0, 0, 0, 0, 0 } },
  // Bio II
  { 178, { 0, 0, 0, 0, 0, 0 } },
  // Summon III
  { 180, { 0, 0, 0, 0, 0, 0 } },
  // Fester
  { 181, { 100, 0, 0, 0, 0, 0 } },
  // Enkindle
  { 184, { 0, 0, 0, 0, 0, 0 } },
  // Adloquium
  { 185, { 0, 0, 0, 0, 0, 300 } },
  // Succor
  { 186, { 0, 0, 0, 0, 0, 180 } },
  // Sacred Soil
  { 188, { 0, 0, 0, 0, 0, 100 } },
  // Lustrate
  { 189, { 0, 0, 0, 0, 0, 600 } },
  // Physick
  { 190, { 0, 0, 0, 0, 0, 400 } },
  // Shield Wall
  { 197, { 0, 0, 0, 0, 0, 0 } },
  // Stronghold
  { 198, { 0, 0, 0, 0, 0, 0 } },
  // Last Bastion
  { 199, { 0, 0, 0, 0, 0, 0 } },
  // Braver
  { 200, { 2400, 0, 0, 0, 0, 0 } },
  // Bladedance
  { 201, { 5250, 0, 0, 0, 0, 0 } },
  // Final Heaven
  { 202, { 9000, 0, 0, 0, 0, 0 } },
  // Skyshard
  { 203, { 1650, 0, 0, 0, 0, 0 } },
  // Starstorm
  { 204, { 3600, 0, 0, 0, 0, 0 } },
  // Meteor
  { 205, { 6150, 0, 0, 0, 0, 0 } },
  // Healing Wind
  { 206, { 0, 0, 0, 0, 0, 0 } },
  // Breath of the Earth
  { 207, { 0, 0, 0, 0, 0, 0 } },
  // Pulse of Life
  { 208, { 0, 0, 0, 0, 0, 0 } },
  // Magitek Cannon
  { 1128, { 0, 0, 0, 0, 0, 0 } },
  // Photon Stream
  { 1129, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 1533, { 0, 0, 0, 0, 0, 0 } },
  // Spinning Edge
  { 2240, { 200, 0, 0, 0, 0, 0 } },
  // Shade Shift
  { 2241, { 0, 0, 0, 0, 0, 0 } },
  // Gust Slash
  { 2242, { 100, 250, 0, 0, 0, 0 } },
  // Hide
  { 2245, { 0, 0, 0, 0, 0, 0 } },
  // Assassinate
  { 2246, { 200, 0, 0, 0, 0, 0 } },
  // Throwing Dagger
  { 2247, { 120, 0, 0, 0, 0, 0 } },
  // Mug
  { 2248, { 150, 0, 0, 0, 0, 0 } },
  // Death Blossom
  { 2254, { 120, 0, 0, 0, 0, 0 } },
  // Aeolian Edge
  { 2255, { 100, 360, 0, 0, 160, 0 } },
  // Shadow Fang
  { 2257, { 100, 200, 0, 0, 0, 0 } },
  // Trick Attack
  { 2258, { 340, 0, 0, 0, 500, 0 } },
  // Ten
  { 2259, { 0, 0, 0, 0, 0, 0 } },
  // Ninjutsu
  { 2260, { 0, 0, 0, 0, 0, 0 } },
  // Chi
  { 2261, { 0, 0, 0, 0, 0, 0 } },
  // Shukuchi
  { 2262, { 0, 0, 0, 0, 0, 0 } },
  // Jin
  { 2263, { 0, 0, 0, 0, 0, 0 } },
  // Kassatsu
  { 2264, { 0, 0, 0, 0, 0, 0 } },
  // Fuma Shuriken
  { 2265, { 280, 0, 0, 0, 0, 0 } },
  // Katon
  { 2266, { 250, 0, 0, 0, 0, 0 } },
  // Raiton
  { 2267, { 400, 0, 0, 0, 0, 0 } },
  // Hyoton
  { 2268, { 140, 0, 0, 0, 0, 0 } },
  // Huton
  { 2269, { 0, 0, 0, 0, 0, 0 } },
  // Doton
  { 2270, { 45, 0, 0, 0, 0, 0 } },
  // Suiton
  { 2271, { 130, 0, 0, 0, 0, 0 } },
  // Rabbit Medium
  { 2272, { 0, 0, 0, 0, 0, 0 } },
  // Rook Autoturret
  { 2864, { 80, 0, 0, 0, 0, 0 } },
  // Split Shot
  { 2866, { 160, 0, 0, 0, 0, 0 } },
  // Slug Shot
  { 2868, { 100, 240, 0, 0, 0, 0 } },
  // Spread Shot
  { 2870, { 180, 0, 0, 0, 0, 0 } },
  // Hot Shot
  { 2872, { 300, 0, 0, 0, 0, 0 } },
  // Clean Shot
  { 2873, { 100, 320, 0, 0, 0, 0 } },
  // Gauss Round
  { 2874, { 150, 0, 0, 0, 0, 0 } },
  // Reassemble
  { 2876, { 0, 0, 0, 0, 0, 0 } },
  // Wildfire
  { 2878, { 0, 0, 0, 0, 0, 0 } },
  // Ricochet
  { 2890, { 150, 0, 0, 0, 0, 0 } },
  // Raiton
  { 3203, { 0, 0, 0, 0, 0, 0 } },
  // Raiton
  { 3204, { 0, 0, 0, 0, 0, 0 } },
  // Kanashibari
  { 3207, { 0, 0, 0, 0, 0, 0 } },
  // Goring Blade
  { 3538, { 100, 390, 0, 0, 0, 0 } },
  // Royal Authority
  { 3539, { 100, 550, 0, 0, 0, 0 } },
  // Divine Veil
  { 3540, { 0, 0, 0, 0, 0, 0 } },
  // Clemency
  { 3541, { 0, 0, 0, 0, 0, 1200 } },
  // Sheltron
  { 3542, { 0, 0, 0, 0, 0, 0 } },
  // Tornado Kick
  { 3543, { 330, 0, 0, 0, 0, 0 } },
  // Elixir Field
  { 3545, { 200, 0, 0, 0, 0, 0 } },
  // Meditation
  { 3546, { 0, 0, 0, 0, 0, 0 } },
  // the Forbidden Chakra
  { 3547, { 370, 0, 0, 0, 0, 0 } },
  // Fell Cleave
  { 3549, { 590, 0, 0, 0, 0, 0 } },
  // Decimate
  { 3550, { 250, 0, 0, 0, 0, 0 } },
  // Raw Intuition
  { 3551, { 0, 0, 0, 0, 0, 0 } },
  // Equilibrium
  { 3552, { 0, 0, 0, 0, 0, 1200 } },
  // Blood of the Dragon
  { 3553, { 0, 0, 0, 0, 0, 0 } },
  // Fang and Claw
  { 3554, { 320, 0, 360, 0, 0, 0 } },
  // Geirskogul
  { 3555, { 270, 0, 0, 0, 0, 0 } },
  // Wheeling Thrust
  { 3556, { 320, 0, 0, 0, 360, 0 } },
  // Battle Litany
  { 3557, { 0, 0, 0, 0, 0, 0 } },
  // Empyreal Arrow
  { 3558, { 230, 0, 0, 0, 0, 0 } },
  // the Wanderer's Minuet
  { 3559, { 100, 0, 0, 0, 0, 0 } },
  // Iron Jaws
  { 3560, { 100, 0, 0, 0, 0, 0 } },
  // the Warden's Paean
  { 3561, { 0, 0, 0, 0, 0, 0 } },
  // Sidewinder
  { 3562, { 100, 0, 0, 0, 0, 0 } },
  // Armor Crush
  { 3563, { 100, 330, 160, 0, 0, 0 } },
  // Dream Within a Dream
  { 3566, { 200, 0, 0, 0, 0, 0 } },
  // Stone III
  { 3568, { 240, 0, 0, 0, 0, 0 } },
  // Asylum
  { 3569, { 0, 0, 0, 0, 0, 100 } },
  // Tetragrammaton
  { 3570, { 0, 0, 0, 0, 0, 700 } },
  // Assize
  { 3571, { 400, 0, 0, 0, 0, 400 } },
  // Ley Lines
  { 3573, { 0, 0, 0, 0, 0, 0 } },
  // Sharpcast
  { 3574, { 0, 0, 0, 0, 0, 0 } },
  // Enochian
  { 3575, { 0, 0, 0, 0, 0, 0 } },
  // Blizzard IV
  { 3576, { 300, 0, 0, 0, 0, 0 } },
  // Fire IV
  { 3577, { 300, 0, 0, 0, 0, 0 } },
  // Painflare
  { 3578, { 150, 0, 0, 0, 0, 0 } },
  // Ruin III
  { 3579, { 100, 0, 0, 0, 0, 0 } },
  // Tri-disaster
  { 3580, { 0, 0, 0, 0, 0, 0 } },
  // Dreadwyrm Trance
  { 3581, { 0, 0, 0, 0, 0, 0 } },
  // Deathflare
  { 3582, { 400, 0, 0, 0, 0, 0 } },
  // Indomitability
  { 3583, { 0, 0, 0, 0, 0, 400 } },
  // Broil
  { 3584, { 240, 0, 0, 0, 0, 0 } },
  // Deployment Tactics
  { 3585, { 0, 0, 0, 0, 0, 0 } },
  // Emergency Tactics
  { 3586, { 0, 0, 0, 0, 0, 0 } },
  // Dissipation
  { 3587, { 0, 0, 0, 0, 0, 0 } },
  // Draw
  { 3590, { 0, 0, 0, 0, 0, 0 } },
  // Redraw
  { 3593, { 0, 0, 0, 0, 0, 0 } },
  // Benefic
  { 3594, { 0, 0, 0, 0, 0, 400 } },
  // Aspected Benefic
  { 3595, { 0, 0, 0, 0, 0, 200 } },
  // Malefic
  { 3596, { 150, 0, 0, 0, 0, 0 } },
  // Malefic II
  { 3598, { 170, 0, 0, 0, 0, 0 } },
  // Combust
  { 3599, { 0, 0, 0, 0, 0, 0 } },
  // Helios
  { 3600, { 0, 0, 0, 0, 0, 330 } },
  // Aspected Helios
  { 3601, { 0, 0, 0, 0, 0, 100 } },
  // Ascend
  { 3603, { 0, 0, 0, 0, 0, 0 } },
  // Diurnal Sect
  { 3604, { 0, 0, 0, 0, 0, 0 } },
  // Nocturnal Sect
  { 3605, { 0, 0, 0, 0, 0, 0 } },
  // Lightspeed
  { 3606, { 0, 0, 0, 0, 0, 0 } },
  // Combust II
  { 3608, { 0, 0, 0, 0, 0, 0 } },
  // Benefic II
  { 3610, { 0, 0, 0, 0, 0, 700 } },
  // Synastry
  { 3612, { 0, 0, 0, 0, 0, 0 } },
  // Collective Unconscious
  { 3613, { 0, 0, 0, 0, 0, 50 } },
  // Essential Dignity
  { 3614, { 0, 0, 0, 0, 0, 400 } },
  // Gravity
  { 3615, { 130, 0, 0, 0, 0, 0 } },
  // Hard Slash
  { 3617, { 200, 0, 0, 0, 0, 0 } },
  // Unleash
  { 3621, { 150, 0, 0, 0, 0, 0 } },
  // Syphon Strike
  { 3623, { 100, 300, 0, 0, 0, 0 } },
  // Unmend
  { 3624, { 150, 0, 0, 0, 0, 0 } },
  // Blood Weapon
  { 3625, { 0, 0, 0, 0, 0, 0 } },
  // Grit
  { 3629, { 0, 0, 0, 0, 0, 0 } },
  // Souleater
  { 3632, { 100, 400, 0, 0, 0, 300 } },
  // Dark Mind
  { 3634, { 0, 0, 0, 0, 0, 0 } },
  // Shadow Wall
  { 3636, { 0, 0, 0, 0, 0, 0 } },
  // Living Dead
  { 3638, { 0, 0, 0, 0, 0, 0 } },
  // Salted Earth
  { 3639, { 60, 0, 0, 0, 0, 0 } },
  // Plunge
  { 3640, { 200, 0, 0, 0, 0, 0 } },
  // Abyssal Drain
  { 3641, { 200, 0, 0, 0, 0, 200 } },
  // Carve and Spit
  { 3643, { 450, 0, 0, 0, 0, 0 } },
  // Big Shot
  { 4238, { 0, 0, 0, 0, 0, 0 } },
  // Desperado
  { 4239, { 0, 0, 0, 0, 0, 0 } },
  // Land Waker
  { 4240, { 0, 0, 0, 0, 0, 0 } },
  // Dark Force
  { 4241, { 0, 0, 0, 0, 0, 0 } },
  // Dragonsong Dive
  { 4242, { 0, 0, 0, 0, 0, 0 } },
  // Chimatsuri
  { 4243, { 0, 0, 0, 0, 0, 0 } },
  // Sagittarius Arrow
  { 4244, { 0, 0, 0, 0, 0, 0 } },
  // Satellite Beam
  { 4245, { 0, 0, 0, 0, 0, 0 } },
  // Teraflare
  { 4246, { 0, 0, 0, 0, 0, 0 } },
  // Angel Feathers
  { 4247, { 0, 0, 0, 0, 0, 0 } },
  // Astral Stasis
  { 4248, { 0, 0, 0, 0, 0, 0 } },
  // Form Shift
  { 4262, { 0, 0, 0, 0, 0, 0 } },
  // Cannonfire
  { 4271, { 0, 0, 0, 0, 0, 0 } },
  // the Balance
  { 4401, { 0, 0, 0, 0, 0, 0 } },
  // the Arrow
  { 4402, { 0, 0, 0, 0, 0, 0 } },
  // the Spear
  { 4403, { 0, 0, 0, 0, 0, 0 } },
  // the Bole
  { 4404, { 0, 0, 0, 0, 0, 0 } },
  // the Ewer
  { 4405, { 0, 0, 0, 0, 0, 0 } },
  // the Spire
  { 4406, { 0, 0, 0, 0, 0, 0 } },
  // Raiton
  { 4977, { 0, 0, 0, 0, 0, 0 } },
  // Raiton
  { 5069, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 5199, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 5846, { 0, 0, 0, 0, 0, 0 } },
  // Stickyloom
  { 5874, { 0, 0, 0, 0, 0, 0 } },
  // Void Fire II
  { 6274, { 0, 0, 0, 0, 0, 0 } },
  // Total Eclipse
  { 7381, { 120, 0, 0, 0, 0, 0 } },
  // Intervention
  { 7382, { 0, 0, 0, 0, 0, 0 } },
  // Requiescat
  { 7383, { 550, 0, 0, 0, 0, 0 } },
  // Holy Spirit
  { 7384, { 350, 0, 0, 0, 0, 0 } },
  // Passage of Arms
  { 7385, { 0, 0, 0, 0, 0, 0 } },
  // Onslaught
  { 7386, { 100, 0, 0, 0, 0, 0 } },
  // Upheaval
  { 7387, { 450, 0, 0, 0, 0, 0 } },
  // Shake It Off
  { 7388, { 0, 0, 0, 0, 0, 0 } },
  // Inner Release
  { 7389, { 0, 0, 0, 0, 0, 0 } },
  // Delirium
  { 7390, { 0, 0, 0, 0, 0, 0 } },
  // Quietus
  { 7391, { 210, 0, 0, 0, 0, 0 } },
  // Bloodspiller
  { 7392, { 600, 0, 0, 0, 0, 0 } },
  // The Blackest Night
  { 7393, { 0, 0, 0, 0, 0, 0 } },
  // Riddle of Earth
  { 7394, { 0, 0, 0, 0, 0, 0 } },
  // Riddle of Fire
  { 7395, { 0, 0, 0, 0, 0, 0 } },
  // Brotherhood
  { 7396, { 0, 0, 0, 0, 0, 0 } },
  // Sonic Thrust
  { 7397, { 100, 200, 0, 0, 0, 0 } },
  // Dragon Sight
  { 7398, { 0, 0, 0, 0, 0, 0 } },
  // Mirage Dive
  { 7399, { 250, 0, 0, 0, 0, 0 } },
  // Nastrond
  { 7400, { 400, 0, 0, 0, 0, 0 } },
  // Hellfrog Medium
  { 7401, { 400, 0, 0, 0, 0, 0 } },
  // Bhavacakra
  { 7402, { 500, 0, 0, 0, 0, 0 } },
  // Ten Chi Jin
  { 7403, { 0, 0, 0, 0, 0, 0 } },
  // Pitch Perfect
  { 7404, { 100, 0, 0, 0, 0, 0 } },
  // Troubadour
  { 7405, { 0, 0, 0, 0, 0, 0 } },
  // Caustic Bite
  { 7406, { 150, 0, 0, 0, 0, 0 } },
  // Stormbite
  { 7407, { 100, 0, 0, 0, 0, 0 } },
  // Nature's Minne
  { 7408, { 0, 0, 0, 0, 0, 0 } },
  // Refulgent Arrow
  { 7409, { 340, 0, 0, 0, 0, 0 } },
  // Heat Blast
  { 7410, { 200, 0, 0, 0, 0, 0 } },
  // Heated Split Shot
  { 7411, { 200, 0, 0, 0, 0, 0 } },
  // Heated Slug Shot
  { 7412, { 100, 300, 0, 0, 0, 0 } },
  // Heated Clean Shot
  { 7413, { 100, 400, 0, 0, 0, 0 } },
  // Barrel Stabilizer
  { 7414, { 0, 0, 0, 0, 0, 0 } },
  // Rook Overdrive
  { 7415, { 0, 0, 0, 0, 0, 0 } },
  // Flamethrower
  { 7418, { 0, 0, 0, 0, 0, 0 } },
  // Between the Lines
  { 7419, { 0, 0, 0, 0, 0, 0 } },
  // Thunder IV
  { 7420, { 50, 0, 0, 0, 0, 0 } },
  // Triplecast
  { 7421, { 0, 0, 0, 0, 0, 0 } },
  // Foul
  { 7422, { 650, 0, 0, 0, 0, 0 } },
  // Aetherpact
  { 7423, { 0, 0, 0, 0, 0, 0 } },
  // Bio III
  { 7424, { 0, 0, 0, 0, 0, 0 } },
  // Miasma III
  { 7425, { 40, 0, 0, 0, 0, 0 } },
  // Ruin IV
  { 7426, { 120, 0, 0, 0, 0, 0 } },
  // Summon Bahamut
  { 7427, { 0, 0, 0, 0, 0, 0 } },
  // Enkindle Bahamut
  { 7429, { 0, 0, 0, 0, 0, 0 } },
  // Thin Air
  { 7430, { 0, 0, 0, 0, 0, 0 } },
  // Stone IV
  { 7431, { 280, 0, 0, 0, 0, 0 } },
  // Divine Benison
  { 7432, { 0, 0, 0, 0, 0, 0 } },
  // Plenary Indulgence
  { 7433, { 0, 0, 0, 0, 0, 200 } },
  // Excogitation
  { 7434, { 0, 0, 0, 0, 0, 800 } },
  // Broil II
  { 7435, { 260, 0, 0, 0, 0, 0 } },
  // Chain Stratagem
  { 7436, { 0, 0, 0, 0, 0, 0 } },
  // Aetherpact
  { 7437, { 0, 0, 0, 0, 0, 0 } },
  // Earthly Star
  { 7439, { 100, 0, 0, 0, 0, 540 } },
  // Malefic III
  { 7442, { 210, 0, 0, 0, 0, 0 } },
  // Minor Arcana
  { 7443, { 0, 0, 0, 0, 0, 0 } },
  // Lord of Crowns
  { 7444, { 0, 0, 0, 0, 0, 0 } },
  // Lady of Crowns
  { 7445, { 0, 0, 0, 0, 0, 0 } },
  // Thunder II
  { 7447, { 30, 0, 0, 0, 0, 0 } },
  // Sleeve Draw
  { 7448, { 0, 0, 0, 0, 0, 0 } },
  // Hakaze
  { 7477, { 170, 0, 0, 0, 0, 0 } },
  // Jinpu
  { 7478, { 100, 320, 0, 0, 0, 0 } },
  // Shifu
  { 7479, { 100, 320, 0, 0, 0, 0 } },
  // Yukikaze
  { 7480, { 100, 400, 0, 0, 0, 0 } },
  // Gekko
  { 7481, { 100, 470, 0, 0, 0, 0 } },
  // Kasha
  { 7482, { 100, 470, 0, 0, 0, 0 } },
  // Fuga
  { 7483, { 100, 0, 0, 0, 0, 0 } },
  // Mangetsu
  { 7484, { 100, 160, 0, 0, 0, 0 } },
  // Oka
  { 7485, { 100, 160, 0, 0, 0, 0 } },
  // Enpi
  { 7486, { 100, 0, 0, 0, 0, 0 } },
  // Midare Setsugekka
  { 7487, { 800, 0, 0, 0, 0, 0 } },
  // Tenka Goken
  { 7488, { 360, 0, 0, 0, 0, 0 } },
  // Higanbana
  { 7489, { 250, 0, 0, 0, 0, 0 } },
  // Hissatsu: Shinten
  { 7490, { 320, 0, 0, 0, 0, 0 } },
  // Hissatsu: Kyuten
  { 7491, { 150, 0, 0, 0, 0, 0 } },
  // Hissatsu: Gyoten
  { 7492, { 100, 0, 0, 0, 0, 0 } },
  // Hissatsu: Yaten
  { 7493, { 100, 0, 0, 0, 0, 0 } },
  // Hissatsu: Kaiten
  { 7494, { 0, 0, 0, 0, 0, 0 } },
  // Hissatsu: Guren
  { 7496, { 850, 0, 0, 0, 0, 0 } },
  // Meditate
  { 7497, { 0, 0, 0, 0, 0, 0 } },
  // Third Eye
  { 7498, { 0, 0, 0, 0, 0, 0 } },
  // Meikyo Shisui
  { 7499, { 0, 0, 0, 0, 0, 0 } },
  // Hissatsu: Seigan
  { 7501, { 220, 0, 0, 0, 0, 0 } },
  // Merciful Eyes
  { 7502, { 0, 0, 0, 0, 0, 200 } },
  // Jolt
  { 7503, { 180, 0, 0, 0, 0, 0 } },
  // Riposte
  { 7504, { 130, 0, 0, 0, 0, 0 } },
  // Verthunder
  { 7505, { 310, 0, 0, 0, 0, 0 } },
  // Corps-a-corps
  { 7506, { 130, 0, 0, 0, 0, 0 } },
  // Veraero
  { 7507, { 310, 0, 0, 0, 0, 0 } },
  // Scatter
  { 7509, { 120, 0, 0, 0, 0, 0 } },
  // Verfire
  { 7510, { 270, 0, 0, 0, 0, 0 } },
  // Verstone
  { 7511, { 270, 0, 0, 0, 0, 0 } },
  // Zwerchhau
  { 7512, { 100, 150, 0, 0, 0, 0 } },
  // Moulinet
  { 7513, { 60, 0, 0, 0, 0, 0 } },
  // Vercure
  { 7514, { 0, 0, 0, 0, 0, 350 } },
  // Displacement
  { 7515, { 0, 0, 0, 0, 0, 0 } },
  // Redoublement
  { 7516, { 100, 230, 0, 0, 0, 0 } },
  // Fleche
  { 7517, { 420, 0, 0, 0, 0, 0 } },
  // Acceleration
  { 7518, { 0, 0, 0, 0, 0, 0 } },
  // Contre Sixte
  { 7519, { 350, 0, 0, 0, 0, 0 } },
  // Embolden
  { 7520, { 0, 0, 0, 0, 0, 0 } },
  // Manafication
  { 7521, { 0, 0, 0, 0, 0, 0 } },
  // Verraise
  { 7523, { 0, 0, 0, 0, 0, 0 } },
  // Jolt II
  { 7524, { 250, 0, 0, 0, 0, 0 } },
  // Verflare
  { 7525, { 600, 0, 0, 0, 0, 0 } },
  // Verholy
  { 7526, { 600, 0, 0, 0, 0, 0 } },
  // Enchanted Riposte
  { 7527, { 210, 0, 0, 0, 0, 0 } },
  // Enchanted Zwerchhau
  { 7528, { 100, 290, 0, 0, 0, 0 } },
  // Enchanted Redoublement
  { 7529, { 100, 470, 0, 0, 0, 0 } },
  // Enchanted Moulinet
  { 7530, { 200, 0, 0, 0, 0, 0 } },
  // Magitek Cannon
  { 7619, { 0, 0, 0, 0, 0, 0 } },
  // Photon Stream
  { 7620, { 0, 0, 0, 0, 0, 0 } },
  // Diffractive Magitek Cannon
  { 7621, { 0, 0, 0, 0, 0, 0 } },
  // High-powered Magitek Cannon
  { 7622, { 0, 0, 0, 0, 0, 0 } },
  // Doom of the Living
  { 7861, { 0, 0, 0, 0, 0, 0 } },
  // Vermilion Scourge
  { 7862, { 0, 0, 0, 0, 0, 0 } },
  // Iaijutsu
  { 7867, { 0, 0, 0, 0, 0, 0 } },
  // Dissolve Union
  { 7869, { 0, 0, 0, 0, 0, 0 } },
  // Stellar Detonation
  { 8324, { 100, 0, 0, 0, 0, 540 } },
  // Broken Ridge
  { 8395, { 0, 0, 0, 0, 0, 0 } },
  // Magitek Pulse
  { 8624, { 0, 0, 0, 0, 0, 0 } },
  // Magitek Thunder
  { 8625, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 8687, { 0, 0, 0, 0, 0, 0 } },
  // Katon
  { 9012, { 0, 0, 0, 0, 0, 0 } },
  // Remove Barrel
  { 9015, { 0, 0, 0, 0, 0, 0 } },
  // Tenka Goken
  { 9143, { 0, 0, 0, 0, 0, 0 } },
  // Thunderous Force
  { 9294, { 0, 0, 0, 0, 0, 0 } },
  // Raiton
  { 9301, { 0, 0, 0, 0, 0, 0 } },
  // Raiton
  { 9302, { 0, 0, 0, 0, 0, 0 } },
  // Bishop Overdrive
  { 9372, { 0, 0, 0, 0, 0, 0 } },
  // Undraw
  { 9629, { 0, 0, 0, 0, 0, 0 } },
  // Self-detonate
  { 9775, { 0, 0, 0, 0, 0, 0 } },
  // Shatterstone
  { 9823, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 9996, { 0, 0, 0, 0, 0, 0 } },
  // Ungarmax
  { 10001, { 0, 0, 0, 0, 0, 0 } },
  // Starstorm
  { 10894, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 10946, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 10947, { 0, 0, 0, 0, 0, 0 } },
  // Ruin III
  { 11191, { 200, 0, 0, 0, 0, 0 } },
  // Physick
  { 11192, { 0, 0, 0, 0, 0, 400 } },
  // Starstorm
  { 11193, { 3600, 0, 0, 0, 0, 0 } },
  // Snort
  { 11383, { 0, 0, 0, 0, 0, 0 } },
  // 4-tonze Weight
  { 11384, { 110, 0, 0, 0, 0, 0 } },
  // Water Cannon
  { 11385, { 120, 0, 0, 0, 0, 0 } },
  // Song of Torment
  { 11386, { 50, 0, 0, 0, 0, 0 } },
  // High Voltage
  { 11387, { 90, 0, 0, 0, 0, 0 } },
  // Bad Breath
  { 11388, { 0, 0, 0, 0, 0, 0 } },
  // Flying Frenzy
  { 11389, { 80, 0, 0, 0, 0, 0 } },
  // Aqua Breath
  { 11390, { 90, 0, 0, 0, 0, 0 } },
  // Plaincracker
  { 11391, { 130, 0, 0, 0, 0, 0 } },
  // Acorn Bomb
  { 11392, { 0, 0, 0, 0, 0, 0 } },
  // Bristle
  { 11393, { 0, 0, 0, 0, 0, 0 } },
  // Mind Blast
  { 11394, { 100, 0, 0, 0, 0, 0 } },
  // Blood Drain
  { 11395, { 20, 0, 0, 0, 0, 0 } },
  // Bomb Toss
  { 11396, { 110, 0, 0, 0, 0, 0 } },
  // 1000 Needles
  { 11397, { 0, 0, 0, 0, 0, 0 } },
  // Drill Cannons
  { 11398, { 120, 0, 0, 0, 0, 0 } },
  // the Look
  { 11399, { 130, 0, 0, 0, 0, 0 } },
  // Sharpened Knife
  { 11400, { 120, 0, 0, 0, 0, 0 } },
  // Loom
  { 11401, { 0, 0, 0, 0, 0, 0 } },
  // Flame Thrower
  { 11402, { 130, 0, 0, 0, 0, 0 } },
  // Faze
  { 11403, { 0, 0, 0, 0, 0, 0 } },
  // Glower
  { 11404, { 130, 0, 0, 0, 0, 0 } },
  // Missile
  { 11405, { 0, 0, 0, 0, 0, 0 } },
  // White Wind
  { 11406, { 0, 0, 0, 0, 0, 0 } },
  // Final Sting
  { 11407, { 1500, 0, 0, 0, 0, 0 } },
  // Self-destruct
  { 11408, { 900, 0, 0, 0, 0, 0 } },
  // Transfusion
  { 11409, { 0, 0, 0, 0, 0, 0 } },
  // Toad Oil
  { 11410, { 0, 0, 0, 0, 0, 0 } },
  // Off-guard
  { 11411, { 0, 0, 0, 0, 0, 0 } },
  // Sticky Tongue
  { 11412, { 0, 0, 0, 0, 0, 0 } },
  // Tail Screw
  { 11413, { 0, 0, 0, 0, 0, 0 } },
  // Level 5 Petrify
  { 11414, { 0, 0, 0, 0, 0, 0 } },
  // Moon Flute
  { 11415, { 0, 0, 0, 0, 0, 0 } },
  // Doom
  { 11416, { 0, 0, 0, 0, 0, 0 } },
  // Mighty Guard
  { 11417, { 0, 0, 0, 0, 0, 0 } },
  // Ice Spikes
  { 11418, { 0, 0, 0, 0, 0, 0 } },
  // the Ram's Voice
  { 11419, { 130, 0, 0, 0, 0, 0 } },
  // the Dragon's Voice
  { 11420, { 110, 0, 0, 0, 0, 0 } },
  // Peculiar Light
  { 11421, { 0, 0, 0, 0, 0, 0 } },
  // Ink Jet
  { 11422, { 120, 0, 0, 0, 0, 0 } },
  // Flying Sardine
  { 11423, { 10, 0, 0, 0, 0, 0 } },
  // Diamondback
  { 11424, { 0, 0, 0, 0, 0, 0 } },
  // Fire Angon
  { 11425, { 100, 0, 0, 0, 0, 0 } },
  // Feather Rain
  { 11426, { 180, 0, 0, 0, 0, 0 } },
  // Eruption
  { 11427, { 220, 0, 0, 0, 0, 0 } },
  // Mountain Buster
  { 11428, { 310, 0, 0, 0, 0, 0 } },
  // Shock Strike
  { 11429, { 310, 0, 0, 0, 0, 0 } },
  // Glass Dance
  { 11430, { 290, 0, 0, 0, 0, 0 } },
  // Veil of the Whorl
  { 11431, { 0, 0, 0, 0, 0, 0 } },
  // Tri-shackle
  { 11482, { 30, 0, 0, 0, 0, 0 } },
  // attack
  { 11784, { 0, 0, 0, 0, 0, 0 } },
  // Stone IV of the Seventh Dawn
  { 13423, { 140, 0, 0, 0, 0, 0 } },
  // Aero II of the Seventh Dawn
  { 13424, { 50, 0, 0, 0, 0, 0 } },
  // Cure II of the Seventh Dawn
  { 13425, { 0, 0, 0, 0, 0, 700 } },
  // Aetherwell
  { 13426, { 0, 0, 0, 0, 0, 0 } },
  // Thunderous Force
  { 14587, { 0, 0, 0, 0, 0, 0 } },
  // Kyokufu
  { 14840, { 180, 0, 0, 0, 0, 0 } },
  // Ajisai
  { 14841, { 100, 0, 0, 0, 0, 0 } },
  // Hissatsu: Gyoten
  { 14842, { 100, 0, 0, 0, 0, 0 } },
  // 冥界恐叫打
  { 14843, { 0, 0, 0, 0, 0, 0 } },
  // Second Wind
  { 15375, { 0, 0, 0, 0, 0, 500 } },
  // Interject
  { 15537, { 0, 0, 0, 0, 0, 0 } },
  // Fight or Flight
  { 15870, { 0, 0, 0, 0, 0, 0 } },
  // Cascade
  { 15989, { 200, 0, 0, 0, 0, 0 } },
  // Fountain
  { 15990, { 100, 250, 0, 0, 0, 0 } },
  // Reverse Cascade
  { 15991, { 300, 0, 0, 0, 0, 0 } },
  // Fountainfall
  { 15992, { 350, 0, 0, 0, 0, 0 } },
  // Windmill
  { 15993, { 150, 0, 0, 0, 0, 0 } },
  // Bladeshower
  { 15994, { 100, 200, 0, 0, 0, 0 } },
  // Rising Windmill
  { 15995, { 250, 0, 0, 0, 0, 0 } },
  // Bloodshower
  { 15996, { 300, 0, 0, 0, 0, 0 } },
  // Standard Step
  { 15997, { 0, 0, 0, 0, 0, 0 } },
  // Technical Step
  { 15998, { 0, 0, 0, 0, 0, 0 } },
  // Emboite
  { 15999, { 0, 0, 0, 0, 0, 0 } },
  // Entrechat
  { 16000, { 0, 0, 0, 0, 0, 0 } },
  // Jete
  { 16001, { 0, 0, 0, 0, 0, 0 } },
  // Pirouette
  { 16002, { 0, 0, 0, 0, 0, 0 } },
  // Standard Finish
  { 16003, { 0, 0, 0, 0, 0, 0 } },
  // Technical Finish
  { 16004, { 0, 0, 0, 0, 0, 0 } },
  // Saber Dance
  { 16005, { 600, 0, 0, 0, 0, 0 } },
  // Closed Position
  { 16006, { 0, 0, 0, 0, 0, 0 } },
  // Fan Dance
  { 16007, { 150, 0, 0, 0, 0, 0 } },
  // Fan Dance II
  { 16008, { 100, 0, 0, 0, 0, 0 } },
  // Fan Dance III
  { 16009, { 200, 0, 0, 0, 0, 0 } },
  // En Avant
  { 16010, { 0, 0, 0, 0, 0, 0 } },
  // Devilment
  { 16011, { 0, 0, 0, 0, 0, 0 } },
  // Shield Samba
  { 16012, { 0, 0, 0, 0, 0, 0 } },
  // Flourish
  { 16013, { 0, 0, 0, 0, 0, 0 } },
  // Improvisation
  { 16014, { 0, 0, 0, 0, 0, 0 } },
  // Curing Waltz
  { 16015, { 0, 0, 0, 0, 0, 200 } },
  // Keen Edge
  { 16137, { 200, 0, 0, 0, 0, 0 } },
  // No Mercy
  { 16138, { 0, 0, 0, 0, 0, 0 } },
  // Brutal Shell
  { 16139, { 100, 300, 0, 0, 0, 150 } },
  // Camouflage
  { 16140, { 0, 0, 0, 0, 0, 0 } },
  // Demon Slice
  { 16141, { 150, 0, 0, 0, 0, 0 } },
  // Royal Guard
  { 16142, { 0, 0, 0, 0, 0, 0 } },
  // Lightning Shot
  { 16143, { 150, 0, 0, 0, 0, 0 } },
  // Danger Zone
  { 16144, { 350, 0, 0, 0, 0, 0 } },
  // Solid Barrel
  { 16145, { 100, 400, 0, 0, 0, 0 } },
  // Gnashing Fang
  { 16146, { 450, 0, 0, 0, 0, 0 } },
  // Savage Claw
  { 16147, { 550, 0, 0, 0, 0, 0 } },
  // Nebula
  { 16148, { 0, 0, 0, 0, 0, 0 } },
  // Demon Slaughter
  { 16149, { 100, 250, 0, 0, 0, 0 } },
  // Wicked Talon
  { 16150, { 650, 0, 0, 0, 0, 0 } },
  // Aurora
  { 16151, { 0, 0, 0, 0, 0, 200 } },
  // Superbolide
  { 16152, { 0, 0, 0, 0, 0, 0 } },
  // Sonic Break
  { 16153, { 300, 0, 0, 0, 0, 0 } },
  // Rough Divide
  { 16154, { 200, 0, 0, 0, 0, 0 } },
  // Continuation
  { 16155, { 0, 0, 0, 0, 0, 0 } },
  // Jugular Rip
  { 16156, { 260, 0, 0, 0, 0, 0 } },
  // Abdomen Tear
  { 16157, { 280, 0, 0, 0, 0, 0 } },
  // Eye Gouge
  { 16158, { 300, 0, 0, 0, 0, 0 } },
  // Bow Shock
  { 16159, { 200, 0, 0, 0, 0, 0 } },
  // Heart of Light
  { 16160, { 0, 0, 0, 0, 0, 0 } },
  // Heart of Stone
  { 16161, { 0, 0, 0, 0, 0, 0 } },
  // Burst Strike
  { 16162, { 500, 0, 0, 0, 0, 0 } },
  // Fated Circle
  { 16163, { 320, 0, 0, 0, 0, 0 } },
  // Bloodfest
  { 16164, { 0, 0, 0, 0, 0, 0 } },
  // Blasting Zone
  { 16165, { 800, 0, 0, 0, 0, 0 } },
  // Single Standard Finish
  { 16191, { 0, 0, 0, 0, 0, 0 } },
  // Double Standard Finish
  { 16192, { 0, 0, 0, 0, 0, 0 } },
  // Single Technical Finish
  { 16193, { 0, 0, 0, 0, 0, 0 } },
  // Double Technical Finish
  { 16194, { 0, 0, 0, 0, 0, 0 } },
  // Triple Technical Finish
  { 16195, { 0, 0, 0, 0, 0, 0 } },
  // Quadruple Technical Finish
  { 16196, { 0, 0, 0, 0, 0, 0 } },
  // Physick
  { 16230, { 0, 0, 0, 0, 0, 400 } },
  // Rightful Sword
  { 16269, { 0, 0, 0, 0, 0, 0 } },
  // Brutal Shell
  { 16418, { 0, 0, 0, 0, 0, 0 } },
  // Keen Edge
  { 16434, { 0, 0, 0, 0, 0, 0 } },
  // Solid Barrel
  { 16435, { 0, 0, 0, 0, 0, 0 } },
  // Soothing Potion
  { 16436, { 0, 0, 0, 0, 0, 0 } },
  // Shining Blade
  { 16437, { 0, 0, 0, 0, 0, 0 } },
  // Perfect Deception
  { 16438, { 0, 0, 0, 0, 0, 0 } },
  // Leap of Faith
  { 16439, { 0, 0, 0, 0, 0, 0 } },
  // Prominence
  { 16457, { 100, 220, 0, 0, 0, 0 } },
  // Holy Circle
  { 16458, { 250, 0, 0, 0, 0, 0 } },
  // Confiteor
  { 16459, { 800, 0, 0, 0, 0, 0 } },
  // Atonement
  { 16460, { 550, 0, 0, 0, 0, 0 } },
  // Intervene
  { 16461, { 200, 0, 0, 0, 0, 0 } },
  // Mythril Tempest
  { 16462, { 100, 200, 0, 0, 0, 0 } },
  // Chaotic Cyclone
  { 16463, { 400, 0, 0, 0, 0, 0 } },
  // Nascent Flash
  { 16464, { 0, 0, 0, 0, 0, 0 } },
  // Inner Chaos
  { 16465, { 920, 0, 0, 0, 0, 0 } },
  // Flood of Darkness
  { 16466, { 250, 0, 0, 0, 0, 0 } },
  // Edge of Darkness
  { 16467, { 350, 0, 0, 0, 0, 0 } },
  // Stalwart Soul
  { 16468, { 100, 160, 0, 0, 0, 0 } },
  // Flood of Shadow
  { 16469, { 300, 0, 0, 0, 0, 0 } },
  // Edge of Shadow
  { 16470, { 500, 0, 0, 0, 0, 0 } },
  // Dark Missionary
  { 16471, { 0, 0, 0, 0, 0, 0 } },
  // Living Shadow
  { 16472, { 0, 0, 0, 0, 0, 0 } },
  // Four-point Fury
  { 16473, { 120, 0, 0, 0, 0, 0 } },
  // Enlightenment
  { 16474, { 220, 0, 0, 0, 0, 0 } },
  // Anatman
  { 16475, { 0, 0, 0, 0, 0, 0 } },
  // Six-sided Star
  { 16476, { 400, 0, 0, 0, 0, 0 } },
  // Coerthan Torment
  { 16477, { 100, 230, 0, 0, 0, 0 } },
  // High Jump
  { 16478, { 400, 0, 0, 0, 0, 0 } },
  // Raiden Thrust
  { 16479, { 330, 0, 0, 0, 0, 0 } },
  // Stardiver
  { 16480, { 550, 0, 0, 0, 0, 0 } },
  // Hissatsu: Senei
  { 16481, { 1100, 0, 0, 0, 0, 0 } },
  // Ikishoten
  { 16482, { 0, 0, 0, 0, 0, 0 } },
  // Tsubame-gaeshi
  { 16483, { 0, 0, 0, 0, 0, 0 } },
  // Kaeshi: Higanbana
  { 16484, { 375, 0, 0, 0, 0, 0 } },
  // Kaeshi: Goken
  { 16485, { 540, 0, 0, 0, 0, 0 } },
  // Kaeshi: Setsugekka
  { 16486, { 1200, 0, 0, 0, 0, 0 } },
  // Shoha
  { 16487, { 0, 0, 0, 0, 0, 0 } },
  // Hakke Mujinsatsu
  { 16488, { 100, 140, 0, 0, 0, 0 } },
  // Meisui
  { 16489, { 0, 0, 0, 0, 0, 0 } },
  // Goka Mekkyaku
  { 16491, { 400, 0, 0, 0, 0, 0 } },
  // Hyosho Ranryu
  { 16492, { 600, 0, 0, 0, 0, 0 } },
  // Bunshin
  { 16493, { 0, 0, 0, 0, 0, 0 } },
  // Shadowbite
  { 16494, { 100, 0, 0, 0, 0, 0 } },
  // Burst Shot
  { 16495, { 230, 0, 0, 0, 0, 0 } },
  // Apex Arrow
  { 16496, { 500, 0, 0, 0, 0, 0 } },
  // Auto Crossbow
  { 16497, { 180, 0, 0, 0, 0, 0 } },
  // Drill
  { 16498, { 700, 0, 0, 0, 0, 0 } },
  // Bioblaster
  { 16499, { 60, 0, 0, 0, 0, 0 } },
  // Air Anchor
  { 16500, { 700, 0, 0, 0, 0, 0 } },
  // Automaton Queen
  { 16501, { 0, 0, 0, 0, 0, 0 } },
  // Queen Overdrive
  { 16502, { 0, 0, 0, 0, 0, 0 } },
  // Despair
  { 16505, { 380, 0, 0, 0, 0, 0 } },
  // Umbral Soul
  { 16506, { 0, 0, 0, 0, 0, 0 } },
  // Xenoglossy
  { 16507, { 750, 0, 0, 0, 0, 0 } },
  // Energy Drain
  { 16508, { 100, 0, 0, 0, 0, 0 } },
  // Egi Assault
  { 16509, { 0, 0, 0, 0, 0, 0 } },
  // Energy Siphon
  { 16510, { 40, 0, 0, 0, 0, 0 } },
  // Outburst
  { 16511, { 70, 0, 0, 0, 0, 0 } },
  // Egi Assault II
  { 16512, { 0, 0, 0, 0, 0, 0 } },
  // Firebird Trance
  { 16513, { 0, 0, 0, 0, 0, 0 } },
  // Fountain of Fire
  { 16514, { 250, 0, 0, 0, 0, 0 } },
  // Brand of Purgatory
  { 16515, { 350, 0, 0, 0, 0, 0 } },
  // Enkindle Phoenix
  { 16516, { 0, 0, 0, 0, 0, 0 } },
  // Verthunder II
  { 16524, { 0, 0, 0, 0, 0, 0 } },
  // Veraero II
  { 16525, { 0, 0, 0, 0, 0, 0 } },
  // Impact
  { 16526, { 220, 0, 0, 0, 0, 0 } },
  // Engagement
  { 16527, { 150, 0, 0, 0, 0, 0 } },
  // Enchanted Reprise
  { 16528, { 220, 0, 0, 0, 0, 0 } },
  // Reprise
  { 16529, { 100, 0, 0, 0, 0, 0 } },
  // Scorch
  { 16530, { 700, 0, 0, 0, 0, 0 } },
  // Afflatus Solace
  { 16531, { 0, 0, 0, 0, 0, 700 } },
  // Dia
  { 16532, { 120, 0, 0, 0, 0, 0 } },
  // Glare
  { 16533, { 300, 0, 0, 0, 0, 0 } },
  // Afflatus Rapture
  { 16534, { 0, 0, 0, 0, 0, 300 } },
  // Afflatus Misery
  { 16535, { 900, 0, 0, 0, 0, 0 } },
  // Temperance
  { 16536, { 0, 0, 0, 0, 0, 0 } },
  // Whispering Dawn
  { 16537, { 0, 0, 0, 0, 0, 0 } },
  // Fey Illumination
  { 16538, { 0, 0, 0, 0, 0, 0 } },
  // Art of War
  { 16539, { 150, 0, 0, 0, 0, 0 } },
  // Biolysis
  { 16540, { 0, 0, 0, 0, 0, 0 } },
  // Broil III
  { 16541, { 280, 0, 0, 0, 0, 0 } },
  // Recitation
  { 16542, { 0, 0, 0, 0, 0, 0 } },
  // Fey Blessing
  { 16543, { 0, 0, 0, 0, 0, 0 } },
  // Summon Seraph
  { 16545, { 0, 0, 0, 0, 0, 0 } },
  // Consolation
  { 16546, { 0, 0, 0, 0, 0, 0 } },
  // Firebird Trance
  { 16549, { 0, 0, 0, 0, 0, 0 } },
  // Divination
  { 16552, { 0, 0, 0, 0, 0, 0 } },
  // Celestial Opposition
  { 16553, { 0, 0, 0, 0, 0, 100 } },
  // Combust III
  { 16554, { 0, 0, 0, 0, 0, 0 } },
  // Malefic IV
  { 16555, { 240, 0, 0, 0, 0, 0 } },
  // Celestial Intersection
  { 16556, { 0, 0, 0, 0, 0, 150 } },
  // Horoscope
  { 16557, { 0, 0, 0, 0, 0, 100 } },
  // Horoscope
  { 16558, { 0, 0, 0, 0, 0, 0 } },
  // Neutral Sect
  { 16559, { 0, 0, 0, 0, 0, 0 } },
  // Ronkan Fire III
  { 16574, { 430, 0, 0, 0, 0, 0 } },
  // Ronkan Blizzard III
  { 16575, { 240, 0, 0, 0, 0, 0 } },
  // Ronkan Thunder III
  { 16576, { 200, 0, 0, 0, 0, 0 } },
  // Ronkan Flare
  { 16577, { 460, 0, 0, 0, 0, 0 } },
  // Falling Star
  { 16578, { 1500, 0, 0, 0, 0, 0 } },
  // Detonator
  { 16766, { 0, 0, 0, 0, 0, 0 } },
  // Fast Blade
  { 16788, { 0, 0, 0, 0, 0, 0 } },
  // Sunshadow
  { 16789, { 0, 0, 0, 0, 0, 0 } },
  // Assault I: Glittering Topaz
  { 16791, { 0, 0, 0, 0, 0, 0 } },
  // Assault II: Shining Topaz
  { 16792, { 0, 0, 0, 0, 0, 0 } },
  // Assault I: Downburst
  { 16793, { 0, 0, 0, 0, 0, 0 } },
  // Assault II: Glittering Emerald
  { 16794, { 0, 0, 0, 0, 0, 0 } },
  // Assault I: Earthen Armor
  { 16795, { 0, 0, 0, 0, 0, 0 } },
  // Assault II: Mountain Buster
  { 16796, { 0, 0, 0, 0, 0, 0 } },
  // Assault I: Aerial Slash
  { 16797, { 0, 0, 0, 0, 0, 0 } },
  // Assault II: Slipstream
  { 16798, { 0, 0, 0, 0, 0, 0 } },
  // Assault I: Crimson Cyclone
  { 16799, { 0, 0, 0, 0, 0, 0 } },
  // Assault II: Flaming Crush
  { 16800, { 0, 0, 0, 0, 0, 0 } },
  // Enkindle: Earthen Fury
  { 16801, { 0, 0, 0, 0, 0, 0 } },
  // Enkindle: Aerial Blast
  { 16802, { 0, 0, 0, 0, 0, 0 } },
  // Enkindle: Inferno
  { 16803, { 0, 0, 0, 0, 0, 0 } },
  // Rough Divide
  { 16804, { 200, 0, 0, 0, 0, 0 } },
  // Tactician
  { 16889, { 0, 0, 0, 0, 0, 0 } },
  // Swashbuckler
  { 16984, { 0, 0, 0, 0, 0, 0 } },
  // Greatest Eclipse
  { 16985, { 0, 0, 0, 0, 0, 0 } },
  // Ronkan Cure II
  { 17000, { 0, 0, 0, 0, 0, 1300 } },
  // Ronkan Medica
  { 17001, { 0, 0, 0, 0, 0, 500 } },
  // Ronkan Esuna
  { 17002, { 0, 0, 0, 0, 0, 0 } },
  // Ronkan Stone II
  { 17003, { 200, 0, 0, 0, 0, 0 } },
  // Ronkan Renew
  { 17004, { 0, 0, 0, 0, 0, 0 } },
  // Play
  { 17055, { 0, 0, 0, 0, 0, 0 } },
  // Gunmetal Soul
  { 17105, { 0, 0, 0, 0, 0, 0 } },
  // Crimson Lotus
  { 17106, { 0, 0, 0, 0, 0, 0 } },
  // Acidic Bite
  { 17122, { 300, 0, 0, 0, 0, 0 } },
  // Heavy Shot
  { 17123, { 550, 0, 0, 0, 0, 0 } },
  // Radiant Arrow
  { 17124, { 1100, 0, 0, 0, 0, 0 } },
  // Dulling Arrow
  { 17125, { 0, 0, 0, 0, 0, 0 } },
  // Aspected Benefic
  { 17151, { 0, 0, 0, 0, 0, 200 } },
  // Aspected Helios
  { 17152, { 0, 0, 0, 0, 0, 100 } },
  // Hypercharge
  { 17209, { 0, 0, 0, 0, 0, 0 } },
  // Summon Eos
  { 17215, { 0, 0, 0, 0, 0, 0 } },
  // Summon Selene
  { 17216, { 0, 0, 0, 0, 0, 0 } },
  // attack
  { 17222, { 0, 0, 0, 0, 0, 0 } },
  // Chivalrous Spirit
  { 17236, { 0, 0, 0, 0, 0, 1200 } },
  // Souldeep Invisibility
  { 17291, { 0, 0, 0, 0, 0, 0 } },
  // Spinning Edge
  { 17413, { 0, 0, 0, 0, 0, 0 } },
  // Gust Slash
  { 17414, { 0, 0, 0, 0, 0, 0 } },
  // Aeolian Edge
  { 17415, { 0, 0, 0, 0, 0, 0 } },
  // Shadow Fang
  { 17416, { 0, 0, 0, 0, 0, 0 } },
  // Armor Crush
  { 17417, { 0, 0, 0, 0, 0, 0 } },
  // Throwing Dagger
  { 17418, { 0, 0, 0, 0, 0, 0 } },
  // Death Blossom
  { 17419, { 0, 0, 0, 0, 0, 0 } },
  // Hakke Mujinsatsu
  { 17420, { 0, 0, 0, 0, 0, 0 } },
  // Hunter's Prudence
  { 17596, { 0, 0, 0, 0, 0, 1000 } },
  // Nebula
  { 17839, { 0, 0, 0, 0, 0, 0 } },
  // Bio
  { 17864, { 0, 0, 0, 0, 0, 0 } },
  // Bio II
  { 17865, { 0, 0, 0, 0, 0, 0 } },
  // Ruin
  { 17869, { 160, 0, 0, 0, 0, 0 } },
  // Ruin II
  { 17870, { 0, 0, 0, 0, 0, 0 } },
  // Smackdown
  { 17901, { 0, 0, 0, 0, 0, 0 } },
  // 攻撃
  { 18034, { 0, 0, 0, 0, 0, 0 } },
  // Ending
  { 18073, { 0, 0, 0, 0, 0, 0 } },
  // Straight Shot
  { 18190, { 0, 0, 0, 0, 0, 0 } },

};