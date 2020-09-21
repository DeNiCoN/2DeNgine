#include "render/WindowManager.hpp"
#include <easylogging++.h>
#include <cassert>

using namespace DeNgine;

namespace DeNgine
{
bool WindowManager::s_initialized = false;

void glfwOnResize(GLFWwindow*, unsigned p_width, unsigned p_height)
{
   WindowManager::getInstance().m_onResize(p_width, p_height);
}

bool WindowManager::initialize()
{
   assert(!s_initialized && "Glfw already initialized");
   if (!glfwInit())
   {
      LOG(FATAL) << "Failed to initialize glad";
      return false;
   }
   s_initialized = true;
   return true;
}

void WindowManager::terminate()
{
   assert(s_initialized && "Window manager not initialized");
   glfwTerminate();
}

bool WindowManager::createWindow()
{
   assert(s_initialized && "Window manager not initialized");
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
   m_window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
   if (!m_window)
   {
      LOG(FATAL) << "Failed to create window";
      return false;
   }
   glfwMakeContextCurrent(m_window);
   return true;
}
void WindowManager::deleteWindow()
{
   glfwDestroyWindow(m_window);
}
}
