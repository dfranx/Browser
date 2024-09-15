#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wininet.h>

#include <BrowserJam/Renderer.h>
#include <BrowserJam/Document.h>

#include <myhtml/api.h>


#ifdef main
#undef main
#endif

BOOL FileExists(LPCTSTR szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Browser Jam",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1200, 800,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    // Get SDL2 window hwnd
    SDL_SysWMinfo systemInfo;
    SDL_VERSION(&systemInfo.version);
    SDL_GetWindowWMInfo(window, &systemInfo);

    HWND hwnd = systemInfo.info.win.window;

    sb::Renderer renderer;
    renderer.Create(hwnd);

    sb::Document document(&renderer);

    if (!FileExists("default.css"))
    {
        std::string defaultStyle = sb::StyleFactory::GetDefaultCSS();
        document.LoadDefaultStyles(defaultStyle.c_str(), defaultStyle.size());
    }
    else
    {
        std::ifstream cssFile("default.css");
        std::string cssContent((std::istreambuf_iterator<char>(cssFile)),
            std::istreambuf_iterator<char>());
    }

    std::ifstream htmlFile("web.html");
    std::string html((std::istreambuf_iterator<char>(htmlFile)),
                     std::istreambuf_iterator<char>());
    document.LoadHTML(html.data(), html.size());

    document.InvalidateLayout();

    bool isWindowOpen = true;
    while (isWindowOpen)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {
            if (e.type == SDL_QUIT)
            {
                isWindowOpen = false;
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                document.OnMouseMove(e.motion.x, e.motion.y);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                document.OnMouseDown(e.button.x, e.button.y);
            }

            SDL_UpdateWindowSurface(window);
        }

        document.Render();
    }

    document.Shutdown();
    renderer.Shutdown();

    return 0;
}