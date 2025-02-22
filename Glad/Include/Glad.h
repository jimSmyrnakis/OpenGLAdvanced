#ifndef FINAL_GLAD_H
#define FINAL_GLAD_H

    #if    defined(DESKTOP_PC) 
        #include "glad/gl.h"
    #elif  defined(RASBERY_PY)
        #include "glad/gles2.h"
    #else 
        #error "Undefined OpenGL Platform !!! Is not Supported yet "
    #endif 

#endif 