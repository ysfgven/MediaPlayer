# MediaPlayer

A desktop music player built with C++20 and Qt6, featuring a clean architecture that separates the core audio engine from the UI layer.

## Architecture

The project is structured in three layers:

- **Core** — `MediaFile`, `MediaLibrary`, `MediaPlayer` handle track management, state, and playback logic. No Qt dependency.
- **Audio Engine** — `AudioEngine` wraps [miniaudio](https://github.com/mackron/miniaudio) for actual audio playback. Supports play, pause, resume, stop, seek, and volume control.
- **Metadata** — `MetadataReader` uses [TagLib](https://taglib.org/) to parse MP3 ID3 tags (title, artist, duration) without coupling the core to any specific library.
- **UI** — Qt6 layer built with Qt Designer. `MainWindow` connects user interactions to the core via signals and slots.

## Features

- MP3 playback with seek and volume control
- ID3 metadata display (title, artist, duration, file size)
- Playback modes: normal, shuffle, repeat one, repeat all
- Progress slider with click-to-seek
- Dynamic volume icon
- Music library loaded from a user-selected folder, path persisted via `QSettings`
- Live search/filter by track name or artist
- Clean dark UI built with Qt Designer and QSS

## Tech Stack

| | |
|---|---|
| Language | C++20 |
| UI | Qt 6 |
| Audio | miniaudio (header-only) |
| Metadata | TagLib |
| Build | CMake |
| Packages | vcpkg |

## Building

### Requirements

- CMake 3.30+
- Qt 6.x (mingw_64)
- vcpkg

### Setup

```bash
# Install dependencies via vcpkg
vcpkg install taglib:x64-mingw-static

# Configure
cmake -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake \
      -DVCPKG_TARGET_TRIPLET=x64-mingw-static \
      -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/mingw_64 \
      -B build

# Build
cmake --build build
```

## Roadmap

- [ ] Null safety improvements
- [ ] Unit tests 
- [ ] Support for additional formats 

## Third Party Libraries

| Library | License |
|---|---|
| [miniaudio](https://github.com/mackron/miniaudio) | MIT |
| [TagLib](https://taglib.org/) | LGPL / MPL |
| [Qt 6](https://www.qt.io/) | LGPL |

## License

MIT
