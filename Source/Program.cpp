#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>

#include "Systems/Renderer/GraphicsApi/Shader/Shader.hpp"
#include "Systems/Renderer/GraphicsApi/VBuffer/VBuffer.hpp"
#include "Systems/Renderer/GraphicsApi/VBuffer/VLayout.hpp"
#include "Systems/Renderer/GraphicsApi/IBuffer/IBuffer.hpp"
#include "Systems/Renderer/GraphicsApi/VABuffer/VABuffer.hpp"
#include "Systems/Renderer/GraphicsApi/FBuffer/FBuffer.hpp"

void ReadShader(const std::string ShaderPath , std::string& source ){
    std::ifstream ShaderFile(ShaderPath, std::ios::in | std::ios::binary);
    if (!ShaderFile)
        ASSERT(0 , "Shader File can't loaded !!!" );
    std::string* ShaderCode = new std::string();
    ShaderFile.seekg(0 , std::ios::end);
    ShaderCode->resize(ShaderFile.tellg());
    ShaderFile.seekg(0 , std::ios::beg);
    ShaderFile.read(&((*ShaderCode)[0]) , ShaderCode->size());
    ShaderFile.close();
    source = *ShaderCode;
}

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


    
    float positions[] = {
         -0.5f , -0.5f ,
         +0.5f , -0.5f ,
         +0.0f , +0.5f 
    };

    Game::u32  indices[] = {
        0 , 1 , 2
    };

    Game::VBuffer           vertex_buffer;
    Game::IBuffer           index_buffer ;
    Game::FBuffer           frame_buffer ;
    Game::VABuffer          va_buffer    ;
    Game::Shader            shader       ;
    Game::VertexLayout      layout       ;
    Game::VertexAttribute   attribute    ;
    
    //Set Attribute
    attribute.Type          = Game::ShaderDataType::Float2;
    attribute.Size          = Game::SizeOfShaderDataType(attribute.Type);
    attribute.Normallized   = true;

    //Set Layout
    layout.AddAttribute(attribute);

    //Set Vertex buffer layout
    vertex_buffer.SetLayout(layout);
    //Set Vertex Buffer data
    vertex_buffer.SetData(positions , sizeof(positions));
    
    //Set Index Buffer
    index_buffer.SetData(indices , sizeof(indices));

    //Set Vertex Array Buffer , add Vertex Buffer
    va_buffer.AddVertexBuffer(vertex_buffer);
    //Set Vertex Array Buffer , set Index Buffer
    va_buffer.SetIndexBuffer(index_buffer);


    //Read Shader Source Code from file and set to the Shader class
    std::string src ;
    ReadShader("./Assets/Shaders/Shader1.glsl", src );
    shader.SetShader(src.c_str());

    //Set Frame Buffer and cReate
    frame_buffer.SetColorBuffer({.r = 1.0f , .g = 0.1f , .b = 0.1f , .a = 1.0f} ,  Game::ImageFormat::RGBA8  );
    frame_buffer.SetDepthBuffer(1.0f , Game::DepthFormat::DEPTH24);
    frame_buffer.SetSize(1000 , 1000);
    frame_buffer.Create();
    frame_buffer.Bind();
    glViewport(0,0,100,100);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Game::i32 wWidth , wHeight;
        glfwGetWindowSize(window , &wWidth , &wHeight);
        //GLCALL( glViewport(0 , 0 , wWidth , wHeight) );
        /* Clear Buffer's */
        frame_buffer.Clear();
        

        

        /*Set Graphics State */
        vertex_buffer.Bind();
        index_buffer.Bind();
        va_buffer.Bind();
        shader.Bind();    
        //Draw elements
        GLCALL( glDrawElements(GL_TRIANGLES , sizeof(indices) / sizeof(Game::u32) , GL_UNSIGNED_INT , nullptr) );
        /*start from vertex 0 (the two first float positions ) and count three next */
        
        //Before Swaping Color Buffers Copy the Image from the off screen color buffer
        frame_buffer.Copy(0 , 0 , wWidth , wHeight);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}