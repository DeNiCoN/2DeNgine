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
    bool initialize();
    void terminate();
    bool createWindow();
    void deleteWindow();
    inline void poolEvents() { glfwPollEvents(); }
    inline bool shouldClose() const {return glfwWindowShouldClose(m_window);};
    inline void swapBuffers() const { glfwSwapBuffers(m_window); };
};
}
