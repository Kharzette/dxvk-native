#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include "../wsi_monitor.h"

namespace dxvk {

  inline bool isDisplayValid(int32_t displayId) {
    const int32_t displayCount = SDL_GetNumVideoDisplays();

    return displayId < displayCount && displayId >= 0;
  }
  
}