#pragma once
#include "../../../Defs.hpp"
#include <GLFW/glfw3.h>

namespace Game{
    class Window{
        static bool GLFW_has_init;
        public:
            Window(void);
            ~Window(void);

            void Set(u32 width , u32 height , const char* title );

            void Init(void);

        private:
            GLFWwindow* m_WindowPtr;
            u32         m_Width;
            u32         m_Height;
            char*       m_Title;
    };
}
