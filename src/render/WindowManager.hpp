#pragma once
#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>
namespace DeNgine
{
class WindowManager
{
    WindowManager() = default;
    GLFWwindow* m_window;
    static bool s_initialized;
    std::function<void(unsigned, unsigned)> m_onResize;
public:
    static WindowManager& getInstance()
    {
        static WindowManager wm;
        return wm;
    };
    bool initialize();
    void terminate();
    bool createWindow();
    void deleteWindow();
    void poolEvents() { glfwPollEvents(); }
    bool shouldClose() const {return glfwWindowShouldClose(m_window);};
    void swapBuffers() const { glfwSwapBuffers(m_window); };
    void registerOnResize(std::function<void(unsigned, unsigned)> func)
    {
        m_onResize = func;
    }

    friend void glfwOnResize(GLFWwindow*, unsigned, unsigned);
};
}
