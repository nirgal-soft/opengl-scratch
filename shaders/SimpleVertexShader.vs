#version 330 core

//input vertex data
layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec2 vertex_uv;

//output data
out vec2 uv;

//values that stay constant for the whole mesh
uniform mat4 mvp;

void main()
{
  gl_Position = mvp * vec4(vertex_position_modelspace, 1);

  uv = vertex_uv;
}
