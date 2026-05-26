# LibCppSpc

LibCppSpc is a modern, cross-platform C++ library for reading, writing, and
manipulating SNES SPC music files (`.spc`) and their ID666 metadata tags.

## Features

- Read and write SPC file data, including header, tag, and audio memory.
- Read and write ID666 metadata (song title, game title, artist, track/disc, timing, and more).
- Support pattern-based metadata/filename conversion with `TagToFileName(pattern)` and `FileNameToTag(pattern)`.
- Support extended ID666 tag structures.

## Requirements

- C++17-compatible compiler
- CMake 3.10+

Notes:
- `LibCppBinary` is fetched automatically via CMake (`FetchContent`).
- Unit tests fetch GoogleTest automatically when enabled.

## Getting Started

## Using LibCppSpc In Your Project

This repository currently builds a CMake target named `LibCppSpc`. It is
designed to be included directly into your C++ project, but it can be built
as a separate static or dynamic library as well.

### Option 1: FetchContent

Add the following to the CMakeLists.txt file for your CMake C++ project:

```cmake
include(FetchContent)

FetchContent_Declare(
    LibCppSpc URL https://github.com/stephenbonar/LibCppSpc/archive/HASH.zip 
)

FetchContent_MakeAvailable(LibCppSpc)
target_link_libraries(your_target PRIVATE LibCppSpc)
```

Where HASH is the SHA hash for the specific commit of the library you want to 
include, which most likely should be the commit of the most recent stable 
release version of the library. Replace HASH with the specific commit hash you 
want to use.

### Option 2: Add As A Subdirectory

Alternatively, you can simply add this library's repository as a subdirectory
to your own CMake C++ project and add the following to your CMakeLists.txt.

```cmake
add_subdirectory(path/to/LibCppSpc)
target_link_libraries(your_target PRIVATE LibCppSpc)
```

### Build The Library

If you do want to build the library separately from your own project, perhaps
to modify and test the library, run the following from the root of the 
repository:

```bash
cmake -S . -B build
cmake --build build
```

### Enable And Build Tests

`BUILD_TESTING` is enabled by default through CTest integration.

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
```

### Run Tests

```bash
ctest --test-dir build --output-on-failure
```

### Generate API Docs (Optional)

If Doxygen is installed, the `docs` target is available:

```bash
cmake --build build --target docs
```

Generated output is written under the CMake build directory.

## Quick Example

```cpp
#include <LibCppSpc.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Must specify .SPC file to modify." << std::endl;
        return 1;
    }

    Spc::File spcFile(argv[1]);

    // Load SPC file from disk.
    spcFile.Load();
    std::cout << "Loaded " << spcFile.Path() << std::endl;

    // Retrieve metadata tag values.
    Spc::Id666::Tag tag = spcFile.Tag();
    std::cout << "Song Name : " << tag.SongTitle().ToString() << std::endl;
    std::cout << "Track No  : " << tag.OstTrack().ToString() << std::endl;

    // Change metadata tag values.
    tag.SetSongTitle("New Song Name");
    tag.SetOstTrack("1");
    spcFile.SetTag(tag);

    // Persist changes.
    spcFile.Save();

    // Convert metadata to file name using a pattern.
    spcFile.TagToFileName("%track% - %song%.spc");
    std::cout << "Copied file to new name based on pattern" << std::endl;

    return 0;
}
```

## Repository Layout

- `include/` - public headers (`LibCppSpc.h`, `Spc/*`)
- `src/` - library implementation
- `tests/` - GoogleTest test suite
- `docs/` - generated API documentation output

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE).
