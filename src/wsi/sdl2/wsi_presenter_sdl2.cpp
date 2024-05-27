#include "../wsi_presenter.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <wsi/native_wsi.h>

namespace dxvk::wsi {

  VkResult createSurface(
          HWND                hWindow,
    const Rc<vk::InstanceFn>& vki,
          VkSurfaceKHR*       pSurface) {
    SDL_Window* window = fromHwnd(hWindow);

    return SDL_Vulkan_CreateSurface(window, vki->instance(), NULL, pSurface)
         ? VK_SUCCESS
         : VK_ERROR_OUT_OF_HOST_MEMORY;
  }

}