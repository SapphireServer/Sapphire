# Event object and instance script generator

`event_object_parser` generates C++ instance and quest-battle skeletons from an
FFXIV installation. It reads EXD metadata and the zone LGB/SGB layout files,
then fills `instance.tmpl` or `questbattle.tmpl` with `addEObj` calls and
quest-battle definitions.

The generated files are starting points. They do not contain complete encounter
or quest-battle behavior and are not regenerated as part of a normal Sapphire
build.

## Build and run

Build the tool normally:

```text
cmake --build build --target event_object_parser
```

CMake copies `instance.tmpl` and `questbattle.tmpl` next to the executable. Run
it with the current directory set to that directory because output paths are
relative to the current directory:

```text
cd bin/tools
event_object_parser "E:/Sapphire/game/sqpack"
```

Output is written below `instances/`, grouped by instance-content type. In
particular, quest battles are written to `instances/questbattles/`.

The optional second argument is currently ineffective: the generator iterates
all known instance-content and quest-battle rows.

## Data flow

1. `ExdData` loads `InstanceContent`, `QuestBattle`, `Quest`, `TerritoryType`,
   and `EObj` rows from the supplied game data.
2. Territory names are resolved to layout paths.
3. `bg.lgb`, `planmap.lgb`, and `planevent.lgb` are parsed for event objects and
   shared groups.
4. Referenced SGB files are inspected for timelines and collision geometry.
5. EXD object names, layout IDs, transforms, states, and collision data are
   emitted into the C++ template.

Related but separate tools:

- `quest_parser` extracts quest Lua bytecode, decompiles it with the bundled
  `unluac_2015_06_13.jar`, and generates normal quest-script templates.
- `questbattle_bruteforce` locates and decompiles quest-battle Lua files, but
  does not generate the C++ instance skeletons.

## Generated string literals

Names are byte strings supplied by the game data. Generated C++ source escapes
non-ASCII and control bytes as `\xHH`. Consecutive escapes can remain in one
literal because the next backslash terminates the preceding escape:

```cpp
"\xE4\xBB\xAE"
```

A C++ `\x` escape consumes all following hexadecimal digits, so an adjacent
literal boundary is inserted only when an ordinary hexadecimal character
follows an escape:

```cpp
"\x97""ClsExc250"
```

Adjacent literals are concatenated by the compiler, so the runtime string still
contains exactly the original bytes. Quotes, backslashes, and common whitespace
controls are escaped separately.

## Known data-version constraints

The parser uses the Win32 sqpack reader. It was reproduced successfully against
a 3.x installation (`ffxivgame.ver` 2016.07.05 and `ex1.ver` 2016.05.21).
