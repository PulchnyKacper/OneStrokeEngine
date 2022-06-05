#include "ose_window.h"
#include <stdexcept>

namespace ose {
    OseWindow::OseWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
        initWindow();
    }
    OseWindow::~OseWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    void OseWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void OseWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to craete window surface");
        }
    }

    void OseWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto oseWindow = reinterpret_cast<OseWindow*>(glfwGetWindowUserPointer(window));
        oseWindow->framebufferResized = true;
        oseWindow->width = width;
        oseWindow->height = height;
    }

}