#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube SkyBox;

void main()
{    
    color = texture(SkyBox, TexCoords);
}
  