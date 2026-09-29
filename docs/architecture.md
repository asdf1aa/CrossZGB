# CrossZGB architecture

## 1. Architecture overview

CrossZGB is a state-oriented engine for low-memory retro consoles. The runtime is intentionally simple:

- a main loop runs continuously
- each screen or scene is represented as a state
- sprites are created and updated by a sprite manager
- asset and bank management keeps code and data in the right memory segment
- platform-specific code handles hardware differences for Game Boy, Master System, Game Gear, and related targets

The engine relies on a set of common patterns that appear in most project files:

- `START()` initializes scene or sprite state
- `UPDATE()` runs once per frame
- `DESTROY()` cleans up when leaving the state
- `SpriteManagerAdd()` creates sprites and registers them to the manager
- `SetState()` changes the current scene

---

## 2. Boot and main loop

The central entry point is [common/src/main.c](../common/src/main.c). In the `main()` function, the engine:

1. initializes platform-specific hardware settings
2. checks for SGB or console-specific features
3. sets up music and OAM state
4. initializes the state table and sprite manager
5. installs the VBlank handler
6. enters the main update loop

The loop is structured like this:

- reset the sprite manager and scroll target
- set `current_state = next_state`
- switch to the correct ROM bank for the new state
- call the state's `START()` function
- optionally show the scene after fade logic
- repeat while `state_running` remains true
- call the state's `DESTROY()` function when leaving the scene

This pattern is the heart of CrossZGB’s runtime design.

---

## 3. State-driven game flow

A CrossZGB game is organized as a set of states. In practice, a developer defines a state file with lifecycle functions and registers the state in a table. The project’s README documents the expected pattern:

```c
#include "Banks/SetAutoBank.h"

void START(void) {
}

void UPDATE(void) {
}
```

State changes are triggered through `SetState()`, which updates the pending state and ensures the engine will switch scene on the next frame. This approach keeps state transitions predictable and simple even in systems with limited memory and limited CPU time.

---

## 4. Sprite system

The sprite system is another foundation of the engine. The runtime exposes functions commonly used in examples and game logic, including:

- `SpriteManagerAdd()` to create a sprite instance
- `SpriteManagerRemove()` or `SpriteManagerRemoveSprite()` to destroy one
- `TranslateSprite()` to move a sprite while testing collisions
- `SetSpriteAnim()` to assign animation sequences
- `CheckCollision()` to detect hitboxes

The engine calls sprite `START()`, `UPDATE()`, and `DESTROY()` callbacks as needed. This makes sprite logic modular and easy to reuse across multiple states.

The Pacman example is a strong demonstration of this design. Its ghost behavior is implemented as coroutine-based logic in [examples/pacman/src/ai.c](../examples/pacman/src/ai.c), showing how sprite behavior can be split into independent update routines that yield control over time.

---

## 5. Coroutines and timing

CrossZGB includes coroutine support for more advanced game logic. This is especially relevant for enemy AI, character movement, and timed behaviors that are easier to express as a step-based state machine than as a fully procedural update loop.

The coroutine machinery is exposed through files such as:

- [common/src/Coroutines.c](../common/src/Coroutines.c)
- [common/src/CoroutinesRunner.c](../common/src/CoroutinesRunner.c)

This style is particularly visible in the Pacman example, where each ghost or enemy follows a path, yields on frames, and resumes from the last execution point. This keeps logic readable without forcing all movement to be hard-coded in a single large `UPDATE()` block.

---

## 6. Bank and memory management

Classic Game Boy-style hardware is heavily constrained by memory and ROM bank layout. CrossZGB addresses this with:

- banked code/data switching
- symbolic asset imports
- save RAM support when enabled
- public helpers for memory references and platform-specific layout differences

The primary definitions are in [common/include/main.h](../common/include/main.h). The bank-related macros and import helpers allow code to declare resource references without manually stitching the linker and memory layout details into every file.

This is a critical part of the engine’s design because many games are built from a mixture of:

- code
- sprite data
- maps
- music
- fonts
- palette and tile data

The build system and macro layer keep such resource boundaries manageable.

---

## 7. Asset pipeline

CrossZGB auto-converts source assets into C data for the engine to consume. The repository supports a broad set of formats, including:

- `.gbr` and `.gbm` for tile/map source art
- `.png` for backgrounds, sprites, and fonts
- `.mod`, `.uge`, `.fur`, `.vgm` for music
- `.sav` and related FX data sources

The engine exposes import macros to make resource declarations consistent across files, such as:

- `IMPORT_MAP(...)`
- `IMPORT_TILES(...)`
- `IMPORT_FONT(...)`
- `IMPORT_HICOLOR(...)`

This keeps asset access ergonomic while retaining low-level control over how the ROM is laid out.

---

## 8. Platform-specific layers

CrossZGB separates generic engine behavior from hardware-specific support. The platform logic is organized under the `common/src` subdirectories:

- [common/src/gb](../common/src/gb)
- [common/src/gg](../common/src/gg)
- [common/src/sms](../common/src/sms)
- [common/src/ap](../common/src/ap)
- [common/src/duck](../common/src/duck)

This convention allows the engine to use shared core code while providing different implementations for hardware differences such as:

- display setup
- input handling
- palette features
- interrupt behavior
- cartridge or memory layout

---

## 9. Build system philosophy

The build system is intentionally project-friendly. A game project can define a small makefile and include the common makefiles from the engine, which automatically:

- identify changed source or asset files
- rebuild only necessary dependencies
- compile for selected targets
- handle target-specific settings like sprite size and bank count

This reduces friction when iterating on game logic and assets, which is important in a real-time retro-game workflow.

---

## 10. Suggested reading order

For contributors or new developers, the recommended reading order is:

1. [README.md](../README.md)
2. [common/include/main.h](../common/include/main.h)
3. [common/src/main.c](../common/src/main.c)
4. [common/src/SpriteManager.c](../common/src/SpriteManager.c)
5. [common/src/Scroll.c](../common/src/Scroll.c)
6. one example project such as [examples/animation](../examples/animation) or [examples/pacman](../examples/pacman)
7. the relevant device folder under [common/src](../common/src)

That sequence gives a practical understanding of engine initialization, runtime behavior, and game logic patterns before diving into deeper platform-specific code.

---

## 11. Summary

CrossZGB is best understood as a hardware-aware game framework built around the classic retro-game workflow: state-driven scenes, sprite management, automatic asset pipelines, and low-level performance constraints. It is intentionally simple to use for small game projects while also supporting advanced logic like coroutines, bank switching, and multi-target builds.
