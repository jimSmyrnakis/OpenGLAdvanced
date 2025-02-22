#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <iostream>

int main(void){
    std::cout << "Hello World (glfw is compiled , linked and translate to executable ) :) !!!" << std::endl;
    std::cin.get();
    

    GLFWwindow* window;

    /* Initialize the glfw library */
    if (!glfwInit())
        return -1;
    


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status == 0)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: Glad failed to initiallize !!!" );
    }


    GLuint     bufferID ;
    GLushort   numOfBuffers = 1;
    float positions[6] = {
         -0.5f , -0.5f ,
         +0.5f , -0.5f ,
         +0.0f , +0.5f 
    };
    GLsizeiptr bufferSize = sizeof(positions);
    // size is in bytes 

    /*Creates a buffer id so it can handle it for sending to gpu VRAM */
    glGenBuffers(numOfBuffers , &bufferID);
    /*Binds or otherwise we could say choose this buffer and what form of buffer this is */
    glBindBuffer(GL_ARRAY_BUFFER , bufferID);
    /*all this good but we need to specify what the size type and data are (right? :) ) 
      The glDataBuffer does that with the buffer we bind with */
    glBufferData(GL_ARRAY_BUFFER , bufferSize , positions , GL_STATIC_DRAW );
    /*bufferUssage is static (buffer gona setup once and used repeatetly ) and draw (buffer is specified for drawing on the screen - so OpenGL says this shader results
      in for example the vram area that is for the drawing pixels etc. )*/

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        

        /*Make a triangle */
        glDrawArrays(GL_TRIANGLES , 0 , 3);
        /*start from vertex 0 (the two first float positions ) and count three next */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}