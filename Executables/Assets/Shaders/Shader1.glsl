#type vertex
#version 330 core

layout(location = 0) in vec2 a_Vertex;
layout(location = 1) in vec2 a_UV;
out vec4 v_Vertices;
out vec2 v_UV;
void main(){
    vec4 result = vec4(a_Vertex.x , a_Vertex.y , 1.0 , 1.0 );
    v_Vertices = result;
    v_UV = a_UV;
    gl_Position = result;
}









#type fragment
#version 330 core 

layout(location = 0) out vec4 v_color;
in vec4 v_Vertices;
uniform sampler2D u_Texture; 
in vec2 v_UV;
void main(){
    v_color = texture( u_Texture , v_UV );
}


