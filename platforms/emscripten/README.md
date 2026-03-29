# Building Warzone 2100 for the Web

The Warzone 2100 Web Edition runs in modern web browsers via [WebAssembly](https://webassembly.org) and [WebGL2](https://get.webgl.org/webgl2/).

## Prerequisites:

- **Git**
- [**Emscripten 3.1.58+**](https://emscripten.org/docs/getting_started/downloads.html)
- [**CMake 3.27+**](https://cmake.org/download/#latest)
- [**workbox-cli**](https://developer.chrome.com/docs/workbox/modules/workbox-cli) (to generate a service worker)
- For language support: [_Gettext_](https://www.gnu.org/software/gettext/)
- To generate documentation: [_Asciidoctor_](https://asciidoctor.org/)

## Building:

1. [Install the Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)
2. Install [workbox-cli](https://developer.chrome.com/docs/workbox/modules/workbox-cli)
   ```
   npm install --ignore-scripts workbox-cli --global
   ```
3. Follow the instructions for [Warzone 2100: Getting the Source](https://github.com/Warzone2100/warzone2100#getting-the-source)
4. `mkdir` a new build folder (as a sibling directory to the warzone2100 repo)
5. `cd` into the build folder
6. Clone vcpkg into the build folder
   ```
   git clone https://github.com/microsoft/vcpkg.git vcpkg
   ```
7. Run CMake configure:
   ```shell
   # Specify your own install dir
   export WZ_INSTALL_DIR="~/wz_web/installed"
   cmake -S ../warzone2100/ -B . -DCMAKE_BUILD_TYPE=Release "-DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten" "-DCMAKE_INSTALL_PREFIX:PATH=${WZ_INSTALL_DIR}"
   ```
8. Run CMake build & install:
   ```
   cmake --build . --target install
   ```

## Testing:

1. Run a local web server and open the browser to the compiled WebAssembly version of WZ.  
   From the build directory:
   ```
   emrun --browser chrome src/index.html
   ```
   From the install directory:
   ```shell
   cd "${WZ_INSTALL_DIR}"
   emrun --browser chrome ./index.html
   ```
   Reference: [`emrun` documentation](https://emscripten.org/docs/compiling/Running-html-files-with-emrun.html)

## Browser Compatibility:

<!--ts-->
   * [Browser Compatibility](#browser-compatibility)
   * [Features & Differences](#features--differences)
   * [Persisting Data](#persisting-data)
   * [Campaign Videos](#campaign-videos)
   * [↗ Building](README-build.md)
<!--te-->

To run Warzone 2100 in your web browser, we recommend:
- Recent versions of Chrome, Edge, Firefox, or Safari
  - With JavaScript and modern WebAssembly support enabled
- WebGL 2.0 support
- 4-8+ GiB of RAM
- Minimum 1024 x 768 resolution display / browser window
- Keyboard & mouse are also strongly recommended

The page will automatically perform a basic series of checks for compatibility and inform you if any issues were detected.

## Features & Differences:

This port is able to support most core Warzone 2100 features, including: campaign, challenges, and skirmish.

> [!TIP]
> Some functionality may be limited or not available, due to size constraints or restrictions of the browser environment.

| Feature                        | Web   |  Native  |
| :----------------------------- | :---: |  :---:   |
| Campaign                       | ✅    | ✅      |
| Campaign Videos                | ✅<sup>1</sup>  | ✅     |
| Challenges                     | ✅    | ✅      |
| Skirmish                       | ✅    | ✅      |
| Savegames                      | ✅    | ✅      |
| HQ graphics                    | ❌    | ✅      |
| HQ music                       | ❌    | ✅      |
| Additional music               | ❌    | ✅      |
| Multiplayer (online)           | ❌    | ✅       |
| Mods                           | ❌<sup>2</sup>  | ✅      |
| Multi-language support         | ✅<sup>3</sup>  | ✅      |
| Performance                    | 🆗    | ✅🚀    |

> [!NOTE]
> <sup><sup>1</sup> The Web port supports low-quality video sequences, which it streams on-demand. _An active Internet connection is required._</sup>  
> <sup><sup>2</sup> The Web port does not currently provide an interface for uploading mods into the configuration directory, but support _could_ be added in the future.</sup>  
> <sup><sup>3</sup> The Web port currently supports _most_ of the same languages, but certain languages that require additional large fonts (ex. Chinese, Korean, Japanese) are unsupported.</sup>

The Web Edition also ships with textures that have been optimized for size, at the expense of quality.

> If you want the highest quality textures, and the complete set of features, you should consider downloading the latest [native build for your system](https://github.com/Warzone2100/warzone2100/releases/latest).

## Persisting Data:

The Web Edition can persist Warzone 2100 settings, configuration, savegames and more in your browser storage using technologies such as IndexedDB.

When you explicitly save your game, Warzone 2100 will ask the browser to opt-in to [persistent storage](https://web.dev/articles/persistent-storage).

Depending on your browser, you may receive a prompt (ex. on Firefox), or this may automatically succeed (or be denied by the browser) without any prompt or notice.

> [!TIP]
> By default, browsers store data in a "best-effort" manner.
> This means it may be cleared by the browser:
> - When storage is low
> - If a site hasn't been visited in a while
> - Or for other reasons
>  
> **Persistent storage can help prevent the browser from automatically evicting your saved games and data.**  
> See: [Storage for the Web: Eviction](https://web.dev/articles/storage-for-the-web#eviction)

> [!IMPORTANT]
> If you manually clear your browser's cache / history for all sites, this will still clear your savegames.

## Campaign Videos:

The Web Edition can automatically stream campaign video sequences on-demand (albeit at low-quality).

> [!IMPORTANT]
> If you've never played Warzone 2100 before, the campaign videos provide critical context for the plot of the campaign.  
> **It is strongly recommended you play with an active Internet connection** so these videos can be streamed during gameplay.

If you have a spotty Internet connection, you should strongly consider the native builds instead, which include the campaign videos for offline viewing.
