#include "../wsi_window.h"

#include "wsi_helpers_sdl2.h"

#include <windows.h>
#include <wsi/native_wsi.h>

#include "../../util/util_string.h"
#include "../../util/log/log.h"

namespace dxvk::wsi {

  void getWindowSize(
        HWND      hWindow,
        uint32_t* pWidth,
        uint32_t* pHeight) {
    SDL_Window* window = fromHwnd(hWindow);

    int32_t w, h;
    SDL_GetWindowSize(window, &w, &h);

    if (pWidth)
      *pWidth = uint32_t(w);

    if (pHeight)
      *pHeight = uint32_t(h);
  }


  void resizeWindow(
          HWND             hWindow,
          DxvkWindowState* pState,
          uint32_t         Width,
          uint32_t         Height) {
    SDL_Window* window = fromHwnd(hWindow);

    SDL_SetWindowSize(window, int32_t(Width), int32_t(Height));
  }


  bool setWindowMode(
          HMONITOR         hMonitor,
          HWND             hWindow,
    const WsiMode*         pMode,
          bool             EnteringFullscreen) {
    const int32_t displayId    = fromHmonitor(hMonitor);
    SDL_Window* window         = fromHwnd(hWindow);

    if (!isDisplayValid(displayId))
      return false;

    // TODO: Implement lookup format for bitsPerPixel here.

    SDL_DisplayMode *pCMode;
    
    bool  bSuccess  =SDL_GetClosestFullscreenDisplayMode(displayId, pMode->width, pMode->height,
          pMode->refreshRate.numerator / pMode->refreshRate.denominator, false, pCMode);
          
    if(pCMode == NULL || !bSuccess) {
      Logger::err(str::format("SDL2 WSI: setWindowMode: SDL_GetClosestDisplayMode: ", SDL_GetError()));
      return false;
    }

    if (SDL_SetWindowFullscreenMode(window, pCMode) != 0) {
      Logger::err(str::format("SDL2 WSI: setWindowMode: SDL_SetWindowDisplayMode: ", SDL_GetError()));
      return false;
    }

    return true;
  }



  bool enterFullscreenMode(
          HMONITOR         hMonitor,
          HWND             hWindow,
          DxvkWindowState* pState,
          bool             ModeSwitch) {
    const int32_t displayId    = fromHmonitor(hMonitor);
    SDL_Window* window         = fromHwnd(hWindow);

    if (!isDisplayValid(displayId))
      return false;

    //this will return null if windowed fullscreen is used
    const SDL_DisplayMode *pDM  =SDL_GetWindowFullscreenMode(window);

    // TODO: Set this on the correct monitor.
    // Docs aren't clear on this...
    if (SDL_SetWindowFullscreen(window, (pDM != NULL) ) != 0) {
      Logger::err(str::format("SDL2 WSI: enterFullscreenMode: SDL_SetWindowFullscreen: ", SDL_GetError()));
      return false;
    }

    return true;
  }


  bool leaveFullscreenMode(
          HWND             hWindow,
          DxvkWindowState* pState) {
    SDL_Window* window = fromHwnd(hWindow);

    if (SDL_SetWindowFullscreen(window, 0) != 0) {
      Logger::err(str::format("SDL2 WSI: leaveFullscreenMode: SDL_SetWindowFullscreen: ", SDL_GetError()));
      return false;
    }

    return true;
  }


  bool restoreDisplayMode(HMONITOR hMonitor) {
    const int32_t displayId = fromHmonitor(hMonitor);
    return isDisplayValid(displayId);
  }


  HMONITOR getWindowMonitor(HWND hWindow) {
    SDL_Window* window      = fromHwnd(hWindow);
    const int32_t displayId = SDL_GetDisplayForWindow(window);

    return toHmonitor(displayId);
  }


  bool isWindow(HWND hWindow) {
    SDL_Window* window = fromHwnd(hWindow);
    return window != nullptr;
  }

}