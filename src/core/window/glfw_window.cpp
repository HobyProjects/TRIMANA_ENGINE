#include "glfw_window.hpp"
#include "log.hpp"

namespace trimana::core{

    bool glfw_service_api::init(){
        if(!glfwInit()){
            TRIMANA_CORE_CRITICAL("Failed to initialize GLFW");
            return (m_initialized = false);
        }

        TRIMANA_CORE_INFO("GLFW initialized successfully");
        return (m_initialized = true);
    }

    void glfw_service_api::quit(){
        if(m_initialized){
            glfwTerminate();
            m_initialized = false;
        }
    }

    glfw_window::glfw_window(const std::string& title){
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        if(mode != nullptr){
            m_properties.width = mode->width;
            m_properties.height = mode->height;
            m_properties.fixed_width = mode->width;
            m_properties.fixed_height = mode->height;
            m_properties.min_width = 1024;
            m_properties.min_height = 720;
            m_properties.red_color_bits = mode->redBits;
            m_properties.green_color_bits = mode->greenBits;
            m_properties.blue_color_bits = mode->blueBits;
            m_properties.alpha_color_bits = 8;
            m_properties.refresh_rate = mode->refreshRate;

        }else{
            TRIMANA_CORE_WARN("Failed to get video mode, using default values");
            m_properties.width = 1280;
            m_properties.height = 720;
            m_properties.fixed_width = 0;
            m_properties.fixed_height = 0;
            m_properties.min_width = 1024;
            m_properties.min_height = 720;
            m_properties.red_color_bits = 8;
            m_properties.green_color_bits = 8;
            m_properties.blue_color_bits = 8;
            m_properties.alpha_color_bits = 8;
            m_properties.refresh_rate = 60;
        }

        m_properties.title = title;

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

        glfwWindowHint(GLFW_RED_BITS, m_properties.red_color_bits);
        glfwWindowHint(GLFW_GREEN_BITS, m_properties.green_color_bits);
        glfwWindowHint(GLFW_BLUE_BITS, m_properties.blue_color_bits);
        glfwWindowHint(GLFW_ALPHA_BITS, m_properties.alpha_color_bits);
        glfwWindowHint(GLFW_REFRESH_RATE, m_properties.refresh_rate);
        glfwWindowHint(GLFW_DEPTH_BITS, m_properties.depth_color_bits);
        glfwWindowHint(GLFW_STENCIL_BITS, m_properties.stencil_color_bits);

        m_window = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.c_str(), nullptr, nullptr);
        if(m_window != nullptr){
            TRIMANA_CORE_INFO("GLFW window created successfully");
            glfwSetWindowSizeLimits(m_window, m_properties.min_width, m_properties.min_height, GLFW_DONT_CARE, GLFW_DONT_CARE);
            glfwGetFramebufferSize(m_window, &m_properties.framebuffer_width, &m_properties.framebuffer_height);
            glfwMakeContextCurrent(m_window);
            glfwSwapInterval(1);

            m_properties.is_active = true;
            m_properties.is_focused = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
            m_properties.is_vsync_enabled = true;
        }
        else{
            
            TRIMANA_CORE_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
        }
    }

    glfw_window::~glfw_window(){
        if(m_window != nullptr){
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
    }

    void glfw_window::swap_buffers() const{
        if(m_window != nullptr){
            if(m_properties.is_vsync_enabled)
                glfwSwapBuffers(m_window);
        }
    }
}