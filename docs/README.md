# CrossZGB repository documentation

## Overview

CrossZGB is a C/assembly game engine for classic handheld consoles and related hardware targets. It is designed around a state-based game loop, sprite management, banked memory, and automatic asset conversion so that game projects can be written in a relatively high-level way while still targeting low-resource systems.

The project is a fork of the original ZGB engine and keeps compatibility with many older ZGB projects while expanding the feature set for modern workflows and additional platforms.

### Supported targets

- Nintendo Game Boy
- Nintendo Game Boy Color
- Analogue Pocket
- Mega Duck / Cougar Boy
- Sega Master System
- Sega Game Gear

### Core capabilities

- State-driven scene management
- Sprite spawning, updates, destruction, and collision handling
- Scroll/camera logic and tile updates
- Automatic asset conversion from source graphics and music files
- Banked code/data management for constrained memory layouts
- Music and sound integration via tracker drivers
- Example-driven development with reusable code patterns

---

## Repository structure

```text
CrossZGB/
├── README.md                   # Project overview and starter docs
├── install.bat                 # Environment setup helper
├── install.txt                 # Installation notes
├── common/                     # Engine core and platform support
│   ├── include/                # Public engine headers
│   ├── src/                   # Core implementation files
│   ├── lib/                   # Platform libraries and engine support modules
│   └── *.props, *.vcxproj     # Native build configuration
├── examples/                   # Sample projects and demos
│   ├── !template/              # Starting point for new games
│   ├── aiming/
│   ├── anim_background/
│   ├── animation/
│   ├── banjo/
│   ├── ...
│   └── z-order/
├── doc files/                  # Project screenshots and media
├── tools/                      # Asset and conversion toolchain utilities
├── common/src/ap/              # Analogue Pocket target logic
├── common/src/duck/            # Mega Duck target logic
├── common/src/gb/              # Game Boy target logic
├── common/src/gg/              # Game Gear target logic
├── common/src/sms/             # Master System target logic
└── docs/                       # This documentation set
```

---

## Quick start

### Prerequisites

CrossZGB depends on the GBDK 2020 toolchain. The repository expects that the build environment is configured so that the path to the engine is available as `ZGB_PATH`.

The root README includes the recommended installation flow:

1. Download the latest release or CI build.
2. Run `install.bat`.
3. Confirm that `ZGB_PATH` points to the `common` directory.

> The project notes suggest keeping the path free of spaces to avoid build issues.

### Create a project

Use the template under [examples/!template](../examples/!template) as a starting point. In most cases, a project includes:

- a main state file or state definitions
- sprite files and animation data
- a project makefile
- asset files such as maps, tiles, music, and fonts

The root README notes that a project can be built from the template by running `build.bat` or `make` from the template source directory.

---

## How the engine is organized

### Core runtime

The main runtime is centered around [common/src/main.c](../common/src/main.c), which sets up the engine loop and switches states each frame. It initializes the display, VBlank handler, sprite manager, and state machinery before entering the main game loop.

Key runtime definitions are exposed in [common/include/main.h](../common/include/main.h), which defines:

- state and sprite callback tables
- fade modes
- memory helpers for banks and SRAM
- import macros for maps, tiles, music, and hicolor data

### State system

The engine is built around states and transition logic. Each scene is a state with lifecycle hooks such as:

- `START()`
- `UPDATE()`
- `DESTROY()`

The engine keeps a `current_state` and dispatches state functions while handling screen transitions and sprite updates.

### Sprite system

Sprites are central to the engine. The lifecycle is controlled by the sprite manager, which tracks spawn, animation, collisions, and removal. Sprites can be added from a state, updated each frame, and disposed when they leave screen limits or are explicitly removed.

The sprite manager and rendering support live in files such as:

- [common/src/SpriteManager.c](../common/src/SpriteManager.c)
- [common/src/Sprite.c](../common/src/Sprite.c)
- [common/src/SpriteRender.c](../common/src/SpriteRender.c)

### Asset and bank system

CrossZGB is designed around a memory-constrained system. The codebase uses bank switching to keep large assets and code segments manageable. Asset macros let the build system import maps, tiles, fonts, and music into the game with minimal manual setup.

Relevant area:

- [common/src/BankManager.c](../common/src/BankManager.c)
- [common/src/MakefileCommon](../common/src/MakefileCommon)
- [tools](../tools)

---

## Build flow

The build system is make-based and uses platform-specific targets. The common makefile includes project configuration and automatically tracks dependencies, recompiling only changed assets or source files.

Typical flow:

1. Define project metadata in a project makefile.
2. Select build targets (for example: `gb`, `gbc`, `gg`, `sms`, `pocket`).
3. Include [common/src/MakefileCommon](../common/src/MakefileCommon).
4. Use the asset conversion tools in [tools](../tools) to generate C data from source art and music.
5. Build the ROM or cartridge output for the chosen platform.

This is one of the repository’s major productivity features: only changed files are rebuilt, reducing iteration time for small game projects.

---

## Example projects

The repository ships with a rich example suite. These examples are the best way to understand the engine in practice.

Examples include:

- [examples/!template](../examples/!template) — base project template
- [examples/animation](../examples/animation) — sprite animation basics
- [examples/banjo](../examples/banjo) — music driver integration
- [examples/coroutines](../examples/coroutines) — coroutine-driven logic
- [examples/hicolor](../examples/hicolor) — Game Boy Color high-color effects
- [examples/pacman](../examples/pacman) — advanced AI and ghost behavior
- [examples/platform](../examples/platform) — physics and collisions
- [examples/print](../examples/print) — text rendering
- [examples/tileupdate](../examples/tileupdate) — tile replacement and animation
- [examples/vwf](../examples/vwf) — proportional text rendering

The Pacman example is especially useful for understanding coroutine-based AI and movement logic, as shown in [examples/pacman/src/ai.c](../examples/pacman/src/ai.c).

---

## Development notes

### Recommended workflow

- Start from the template project.
- Model game flow as states.
- Put gameplay and sprite behavior in dedicated files.
- Use CrossZGB’s sprite APIs instead of manually managing low-level hardware state whenever possible.
- Keep asset imports declarative with the engine macros.

### Common engine files worth reading first

- [README.md](../README.md)
- [common/include/main.h](../common/include/main.h)
- [common/src/main.c](../common/src/main.c)
- [common/src/SpriteManager.c](../common/src/SpriteManager.c)
- [common/src/Scroll.c](../common/src/Scroll.c)
- [examples/!template](../examples/!template)

---

## Further reading

- [README.md](../README.md) — project overview and installation steps
- [docs/architecture.md](../docs/architecture.md) — engine architecture details
- The wiki referenced in the repository README for deeper engine concepts and tutorials
- The GitHub support and Discord channels listed in the project README

---

## Maintainer note

This documentation is intended to help contributors and game developers understand the repository layout, the engine lifecycle, and the supported example work flows without having to reverse-engineer the structure from the source tree alone.
