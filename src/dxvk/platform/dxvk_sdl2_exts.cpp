#include "../dxvk_platform_exts.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

namespace dxvk {

  DxvkPlatformExts DxvkPlatformExts::s_instance;

  std::string_view DxvkPlatformExts::getName() {
    return "SDL2 WSI";
  }


  DxvkNameSet DxvkPlatformExts::getInstanceExtensions() {
    SDL_Window* window = SDL_CreateWindow(
      "Dummy Window",
      1, 1,
      SDL_WINDOW_HIDDEN | SDL_WINDOW_VULKAN);

    if (window == nullptr)
      throw DxvkError(str::format("SDL2 WSI: Failed to create dummy window. ", SDL_GetError()));

    uint32_t extensionCount = 0;

    DxvkNameSet names;

    const char * const *pNames  =SDL_Vulkan_GetInstanceExtensions(&extensionCount);
    for(uint32_t i=0;i < extensionCount;i++)
    {
      names.add(pNames[i]);
    }

    SDL_DestroyWindow(window);

    return names;
  }


  DxvkNameSet DxvkPlatformExts::getDeviceExtensions(
          uint32_t      adapterId) {
    return DxvkNameSet();
  }
  

  void DxvkPlatformExts::initInstanceExtensions() {

  }


  void DxvkPlatformExts::initDeviceExtensions(
    const DxvkInstance* instance) {

  }

}