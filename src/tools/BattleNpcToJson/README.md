collision data exporter for sapphire

compile with STANDALONE defined to compile without boost and sapphire dependencies

usage:
- regular
 - compile with root sapphire dir cmakelists
 - sapphire/src/tools/bin/pcb_reader2 <territory> "<path/to/game/sqpack/ffxiv>" 
- standalone
 - compile main.cpp with STANDALONE defined in build arg
 - download ffxivexplorer <http://ffxivexplorer.fragmenterworks.com/>
 - ffxivexplorer > path/to/ffxiv's/game/sqpack/ffxiv/0a0000.dat
 - exd/territorytype.exh > `File > Export` and copy `territorytype.exh.csv` from exproted directory to `pcb_reader.exe` directory 
 - ffxivexplorer > path/to/ffxiv's/game/sqpack/ffxiv/020000.dat
 - ctrl click the following: 
  - `bg/ffxiv/[REGION]/common/collision`
  - `bg/ffxiv/[REGION]/[dun|fld|twn|etc..]/common/collision/`
  - `bg/ffxiv/[REGION]/[dun|fld|twn|etc..]/collision/`
  - `bg/ffxiv/region/shared/[for_bg|for_hou]/`
  - `bg/ffxiv/[REGION]/[dun|fld|twn|etc..]/ZONE/level/`
  - `bg/ffxiv/[REGION]/[dun|fld|twn|etc..]/ZONE/collision/`
  - `bgcommon/world/sys/shared/for_bg/`
 and `File > Export Raw` to pcb_reader exe dir (common and shared files are optional but you will be missing a lot of objects if you skip them)
 - note: at this time ffxivexplorer is still missing some hashes, though any tool which can export the exds should work fine
 - main "" <territory>

