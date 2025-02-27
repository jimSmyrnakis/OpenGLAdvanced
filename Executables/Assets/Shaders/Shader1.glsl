#type vertex


#version 330 core

layout(location = 0) in vec2 a_Vertex;
out vec4 v_Vertices;

void main(){
    vec4 result = vec4(a_Vertex.x , a_Vertex.y , 0.0 , 1.0 );
    v_Vertices = result;
    gl_Position = result;
}









#type fragment
#version 330 core 

layout(location = 0) out vec4 v_color;
in vec4 v_Vertices;

void main(){
    v_color = vec4(0.1 , 0.1 , 0.1 , 1.0);
}


