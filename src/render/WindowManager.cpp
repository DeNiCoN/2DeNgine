#include "render/WindowManager.hpp"
#include <cassert>

using namespace DeNgine;

namespace DeNgine
{
bool WindowManager::s_initialized = false;
}
bool WindowManager::initialize()
{
   assert(!s_initialized && "Glfw already initialized");
   if (!glfwInit())
   {
      //TODO Logging
      return false;
   }
   s_initialized = true;
   return true;
}

void WindowManager::finalize()
{
   glfwTerminate();
}

bool WindowManager::createWindow()
{
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
   m_window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
   if (!m_window)
   {
      //TODO Logging
      return false;
   }
   return true;
}
