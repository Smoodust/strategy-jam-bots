# strategy-jam-bots

C++20 project built with CMake.

## Layout

```
include/sjb/      public headers: game state/move (game.hpp), rules (rules.hpp),
                   bot interface (bot.hpp), simulator (simulator.hpp)
src/               sjb::core sources (rules, simulator — no bot logic, no I/O)
bots/              one header+source pair per bot, each implementing sjb::Bot
                   (random, greedy, heuristic, minimax — all stubs for now)
app/               main executable
tests/             unit tests (GoogleTest, fetched automatically)
tools/visualizer/  replay viewer — deliberately outside the CMake build,
                   reads replay files only, never links against the C++ code
```

## Build

Requires CMake 3.20+ and a C++20 compiler.

```sh
cmake --preset debug          # configure into build/debug
cmake --build --preset debug  # build
ctest --preset debug          # run tests
./build/debug/strategy_jam_bots
```

Release build (tests disabled):

```sh
cmake --preset release
cmake --build --preset release
```

Without presets:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build
```

Options: `-DSJB_BUILD_TESTS=OFF` to skip tests, `-DSJB_WARNINGS_AS_ERRORS=ON` to make warnings fatal.

## Neovim / clangd

`CMAKE_EXPORT_COMPILE_COMMANDS` is on, so every `cmake --preset ...` writes
`build/<preset>/compile_commands.json`. The checked-in `.clangd` points
clangd at `build/debug` for it, so any clangd-based Neovim setup
(`nvim-lspconfig`, `coc-clangd`, ...) picks up the right flags/includes
automatically as long as clangd itself is installed — no other setup needed.

Re-run `cmake --preset debug` (configure only, no need to build) whenever
you add or remove a source file, so clangd's database stays in sync.
