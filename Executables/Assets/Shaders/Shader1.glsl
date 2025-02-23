#type vertex


#version 330 core

layout(location = 0) in vec3 a_Vertex;
layout(location = 1) in vec2 a_TextCoord; 
out vec2 v_TextCoord;
out vec4 v_Vertices;

void main(){
    
    v_TextCoord = a_TextCoord; 
    gl_Position = vec4(a_Vertex , 1.0);
}









#type fragment
#version 330 core 

layout(location = 0) out vec4 v_color;
in vec4 v_Vertices;
in vec2 v_TextCoord;

uniform sampler2D u_Texture;

void main(){
    v_color = v_Vertices;
}
