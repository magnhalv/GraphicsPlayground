#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
  
uniform vec3 modifiedPos;
out vec3 ourColor; // output a color to the fragment shader
out vec3 ourPosition;

void main()
{
    vec3 pos = vec3(aPos.x + modifiedPos.x, aPos.y + modifiedPos.y, aPos.z);
    gl_Position = vec4(pos, 1.0);
    ourPosition = pos;
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}  