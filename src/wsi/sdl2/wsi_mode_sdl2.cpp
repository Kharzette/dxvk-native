#include "../wsi_mode.h"

#include "wsi_helpers_sdl2.h"

#include <wsi/native_wsi.h>

#include "../../util/util_string.h"
#include "../../util/log/log.h"

namespace dxvk::wsi {

  static inline uint32_t roundToNextPow2(uint32_t num) {
    if (num-- == 0)
      return 0;

    num |= num >> 1; num |= num >> 2;
    num |= num >> 4; num |= num >> 8;
    num |= num >> 16;

    return ++num;
  }


  static inline void convertMode(const SDL_DisplayMode *pSDLMode, WsiMode* pMode) {
    pMode->width          = uint32_t(pSDLMode->w);
    pMode->height         = uint32_t(pSDLMode->h);
    pMode->refreshRate    = WsiRational{ uint32_t(pSDLMode->refresh_rate) * 1000, 1000 }; 
    // BPP should always be a power of two
    // to match Windows behaviour of including padding.
    pMode->bitsPerPixel   = roundToNextPow2(SDL_BITSPERPIXEL(pSDLMode->format));
    pMode->interlaced     = false;
  }


  bool getDisplayMode(
          HMONITOR         hMonitor,
          uint32_t         ModeNumber,
          WsiMode*         pMode) {
    const int32_t displayId    = fromHmonitor(hMonitor);

    if (!isDisplayValid(displayId))
      return false;

    int numModes;
    const SDL_DisplayMode **pModes  =SDL_GetFullscreenDisplayModes(displayId, &numModes);
    if(pModes == NULL)
    {
      return  false;
    }

    convertMode(pModes[ModeNumber], pMode);

    return true;
  }


  bool getCurrentDisplayMode(
          HMONITOR         hMonitor,
          WsiMode*         pMode) {
    const int32_t displayId    = fromHmonitor(hMonitor);

    if (!isDisplayValid(displayId))
      return false;

    const SDL_DisplayMode *pDMode =SDL_GetCurrentDisplayMode(displayId);
    if(pDMode == NULL)
    {
      Logger::err(str::format("SDL_GetCurrentDisplayMode: ", SDL_GetError()));
      return false;
    }

    convertMode(pDMode, pMode);

    return true;
  }


  bool getDesktopDisplayMode(
          HMONITOR         hMonitor,
          WsiMode*         pMode) {
    const int32_t displayId    = fromHmonitor(hMonitor);

    if (!isDisplayValid(displayId))
      return false;

    const SDL_DisplayMode *pDDMode  =SDL_GetDesktopDisplayMode(displayId);
    if(pDDMode == NULL)
    {
      Logger::err(str::format("SDL_GetCurrentDisplayMode: ", SDL_GetError()));
      return false;
    }

    convertMode(pDDMode, pMode);

    return true;
  }
  
}
