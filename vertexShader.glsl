#version 330 core

layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 inColor; // the color variable has attribute position 1

out vec4 outColor; // output a color to the fragment shader
uniform mat4 Projection;  //vARIABILE DI TIPO uniform, rimane la stessa per ogni vertice della primitiva e viene passata dall'esterno
uniform mat4 Model;

void main()
{
    gl_Position = Projection*Model*vec4(aPos, 1.0);
    outColor = inColor; // set ourColor to the input color we got from the vertex data
}