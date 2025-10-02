#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "../wsi_monitor.h"

namespace dxvk {

  inline bool isDisplayValid(int32_t displayId) {
    int displayCount;
    SDL_DisplayID *pDID =SDL_GetDisplays(&displayCount);
    if(pDID == NULL)
    {
      return  false;
    }

    bool  bGood =(displayId < displayCount && displayId >= 0);

    SDL_free(pDID);

    return  bGood;
  }  
}