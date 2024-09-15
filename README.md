# Browser
A simple browser built for https://github.com/BrowserJam/jam001

Works only on Windows (due to Direct2D and DirectWrite).

To build, you must first install SDL2 (I recommend vcpkg)
```vcpkg install sdl2```

Generate project using CMake and build it.
The program loads HTML from a `web.html` file and can load css from `default.css` (it has built in default CSS though and can work without this file).