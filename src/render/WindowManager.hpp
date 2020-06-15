#pragma once
#include <GLFW/glfw3.h>
namespace DeNgine
{
class WindowManager
{
private:
    GLFWwindow* m_window;
    static bool s_initialized;
public:
    static bool initialize();
    static void finalize();
    bool createWindow();
    inline bool shouldClose() const {return glfwWindowShouldClose(m_window);};
};
}
