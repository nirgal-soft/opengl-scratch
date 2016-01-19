#version 330 core

//interpolated values from the vertex shaders
in vec2 uv;

out vec3 color;

//values that stay constant
uniform sampler2D texture_sampler;

void main()
{
  color = texture(texture_sampler, uv).rgb;
}
