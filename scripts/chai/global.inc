/////////////////////////////////////////////////////////////////////
// Quest sequence
/////////////////////////////////////////////////////////////////////
global SEQ_COMPLETE = 0xFF

/////////////////////////////////////////////////////////////////////
// SCENE_FLAGS
/////////////////////////////////////////////////////////////////////
global SET_EOBJ_BASE           = 0xF8400EF3
global SET_INVIS_BASE          = 0xF8400FFF
global SET_BASE                = 0xF8400EFB
global INVIS_COMPANION         = 0x80000000
global INVIS_ALLIANCE_BUDDY    = 0x40000000
global INVIS_ALLIANCE_PC       = 0x20000000
global INVIS_AOE               = 0x08000000
global DISABLE_CANCEL_EMOTE    = 0x04000000
global LOCK_HOTBAR             = 0x02000000
global LOCK_HUD                = 0x01000000
global ROLLBACK_HIDE_UI        = 0x00800000
global DISABLE_STEALTH         = 0x00400000
global HIDE_FESTIVAL           = 0x00200000
global DISABLE_SKIP            = 0x00080000
global SILENT_ENTER_TERRI_ALL  = 0x00038000
global SILENT_ENTER_TERRI_SE   = 0x00020000
global SILENT_ENTER_TERRI_BGM  = 0x00010000
global SILENT_ENTER_TERRI_ENV  = 0x00008000
global INVINCIBLE              = 0x00004000
global HIDE_HOTBAR             = 0x00002000
global AUTO_LOC_CAMERA         = 0x00001000
global INVIS_ALL               = 0xF80003FC
global HIDE_UI                 = 0x00000800
global CONDITION_CUTSCENE      = 0x00000400
global INVIS_TREASURE          = 0x00000200
global INVIS_AETHERYTE         = 0x00000100
global INVIS_GATHERING_POINT   = 0x00000080
global INVIS_PARTY_BUDDY       = 0x10000000
global INVIS_PARTY_PC          = 0x00000040
global INVIS_OTHER_PC          = 0x00000020
global INVIS_BNPC              = 0x00000010
global INVIS_EOBJ              = 0x00000008
global INVIS_ENPC              = 0x00000004
global FADE_OUT                = 0x00000002
global NO_DEFAULT_CAMERA       = 0x00000001
global NONE                    = 0x00000000

/////////////////////////////////////////////////////////////////////
// Event Types
/////////////////////////////////////////////////////////////////////
global EVENT_TALK = 1
global EVENT_EMOTE = 2
global EVENT_DISTANCE_BELOW = 3
global EVENT_DISTANCE_OVER = 4
global EVENT_BATTLE_REWARD = 5
global EVENT_CRAFT = 6
global EVENT_NEST = 7
global EVENT_EVENT_ITEM = 8
global EVENT_DROP = 9
global EVENT_WITHIN_RANGE = 10
global EVENT_OUTSIDE_RANGE = 11
global EVENT_GAME_START = 12
global EVENT_GAME_PROGRESS = 13
global EVENT_ENTER_TERRITORY = 15
global EVENT_GAME_COME_BACK = 17
global EVENT_ACTION_RESULT = 18
global EVENT_MATERIA_CRAFT = 19
global EVENT_FISHING = 20
global EVENT_UI = 21
global EVENT_HOUSING = 22
global EVENT_SAY = 23
global EVENT_TABLE_GAME = 24

/////////////////////////////////////////////////////////////////////
// Event finish states
/////////////////////////////////////////////////////////////////////
global UNLOCK     = 1
global KEEPLOCK   = 0

/////////////////////////////////////////////////////////////////////
// Possible Event Types
/////////////////////////////////////////////////////////////////////

global ACTOR_EVENT_ON_CREATE        = 1
global ACTOR_EVENT_ON_SPAWN         = 2
global ACTOR_EVENT_ON_DESPAWN       = 3
global ACTOR_EVENT_ON_AI_TICK       = 4
global ACTOR_EVENT_ON_TALK_DEFAULT  = 5

global MOB_EVENT_ON_DEATH = 1

global REGION_EVENT_ON_CREATE= 1
global REGION_EVENT_ON_ENTER = 2
global REGION_EVENT_ON_LEAVE = 3

global PLAYER_EVENT_ON_FIRST_ENTER_WORLD  = 1
global PLAYER_EVENT_ON_ENTER_WORLD        = 2
global PLAYER_EVENT_ON_DEATH              = 3
global PLAYER_EVENT_ON_LOGIN              = 4
global PLAYER_EVENT_ON_LOGOUT             = 5

// End Event Types

global SLOT_MAINH   = 0
global SLOT_OFFH    = 1
global SLOT_HEAD    = 2
global SLOT_BODY    = 3
global SLOT_GLOVES  = 4
global SLOT_WAIST   = 5
global SLOT_LEGS    = 6
global SLOT_FEET    = 7

global GENDER_MALE     = 0
global GENDER_FEMALE   = 1

global ACTION_EVENT_START        = 1
global ACTION_EVENT_RETURN       = 2
global ACTION_EVENT_TRADE_RETURN = 3
global ACTION_ERANGE_EVENT_START = 4
global ACTION_EVENT_EMOTE        = 5

global ACTION_RETURN    = 0x26
global ACTION_TELEPORT  = 0x29

global EVENTACTION_ATTUNE    = 0x13

global CLASS_GLA = 1
global CLASS_PUG = 2
global CLASS_MRD = 3
global CLASS_LNC = 4
global CLASS_ARC = 5
global CLASS_CON = 6
global CLASS_THM = 7
global CLASS_CRP = 8
global CLASS_BSM = 9
global CLASS_ARM = 10
global CLASS_GLD = 11
global CLASS_TAN = 12
global CLASS_WVR = 13
global CLASS_ALC = 14
global CLASS_CUL = 15
global CLASS_MIN = 16
global CLASS_BOT = 17
global CLASS_FSH = 18
global CLASS_PLD = 19
global CLASS_MNK = 20
global CLASS_WAR = 21
global CLASS_DRG = 22
global CLASS_BRD = 23
global CLASS_WHM = 24
global CLASS_BLM = 25
global CLASS_ACN = 26
global CLASS_SMN = 27
global CLASS_SCH = 28
global CLASS_ROG = 29
global CLASS_NIN = 30
global CLASS_MCH = 31
global CLASS_DRK = 32
global CLASS_AST = 33

///////////////////////////////////////////////////////////////
// Inventory Enums
///////////////////////////////////////////////////////////////
global INVENTORY_BAG0 = 0
global INVENTORY_BAG1 = 1
global INVENTORY_BAG2 = 2
global INVENTORY_BAG3 = 3

global INVENTORY_GEARSET0 = 1000
global INVENTORY_GEARSET1 = 1001

global INVENTORY_CURRENCY = 2000
global INVENTORY_CRYSTAL = 2001
//global INVENTORY_UNKNOWN_0 = 2003
global INVENTORY_KEYITEM = 2004
global INVENTORY_DAMAGEDGEAR = 2007
//global INVENTORY_UNKNOWN_1 = 2008

global INVENTORY_ARMORYOFF = 3200
global INVENTORY_ARMORYHEAD = 3201
global INVENTORY_ARMORYBODY = 3202
global INVENTORY_ARMORYHAND = 3203
global INVENTORY_ARMORYWAIST = 3204
global INVENTORY_ARMORYLEGS = 3205
global INVENTORY_ARMORYFEET = 3206
global INVENTORY_ARMOTYNECK = 3207
global INVENTORY_ARMORYEAR = 3208
global INVENTORY_ARMORYWRIST = 3209
global INVENTORY_ARMORYRING = 3300

global INVENTORY_ARMORYSOULCRYSTAL = 3400
global INVENTORY_ARMORYMAIN = 3500

global INVENTORY_RETAINERBAG0 = 10000
global INVENTORY_RETAINERBAG1 = 10001
global INVENTORY_RETAINERBAG2 = 10002
global INVENTORY_RETAINERBAG3 = 10003
global INVENTORY_RETAINERBAG4 = 10004
global INVENTORY_RETAINERBAG5 = 10005
global INVENTORY_RETAINERBAG6 = 10006
global INVENTORY_RETAINEREQUIPPEDGEAR = 11000
global INVENTORY_RETAINERGIL = 12000
global INVENTORY_RETAINERCRYSTAL = 12001
global INVENTORY_RETAINERMARKET = 12002

global INVENTORY_FREECOMPANYBAG0 = 20000
global INVENTORY_FREECOMPANYBAG1 = 20001
global INVENTORY_FREECOMPANYBAG2 = 20002
global INVENTORY_FREECOMPANYGIL = 22000
global INVENTORY_FREECOMPANYCRYSTAL = 22001

////////////////////////////////////////////////////////////
// Currency types
////////////////////////////////////////////////////////////
global CURRENCY_GIL = 0X01
global CURRENCY_STORMSEAL = 0X02
global CURRENCY_SERPENTSEAL = 0X03
global CURRENCY_FLAMESEAL = 0X04
global CURRENCY_TOMESTONEPHILO = 0X05
global CURRENCY_TOMESTONEMYTHO = 0X06
global CURRENCY_WOLFMARK = 0X07
global CURRENCY_TOMESTONESOLD = 0X08
global CURRENCY_ALLIEDSEAL = 0X09
global CURRENCY_TOMESTONEPOET = 0X0A
global CURRENCY_MGP = 0X0B
global CURRENCY_TOMESTONELAW = 0X0C
global CURRENCY_TOMESTONEESO = 0X0D
global CURRENCY_TOMESTONELORE = 0X0E

////////////////////////////////////////////////////////////
// Skill handle types
////////////////////////////////////////////////////////////
global STD_DAMAGE = 0X03
global STD_HEAL = 0X04
global STD_MP_LOSS = 0X0A
global STD_MP_GAIN = 0X0B
global STD_TP_LOSS = 0X0C
global STD_TP_GAIN = 0X0D