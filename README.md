# strategy-jam-bots

C++20 project built with CMake.

## Layout

```
include/sjb/   public headers of the core library
src/           core library sources (sjb::core)
app/           main executable
tests/         unit tests (GoogleTest, fetched automatically)
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
