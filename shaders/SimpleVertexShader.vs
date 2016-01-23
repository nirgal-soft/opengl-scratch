#version 330 core

//input vertex data
layout(location = 0) in vec3 vertex_position_model_space;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 normal_model_space;

//output data
out vec2 uv;
out vec3 position_world_space;
out vec3 normal_camera_space;
out vec3 eye_direction_camera_space;
out vec3 light_direction_camera_space;

//values that stay constant for the whole mesh
uniform mat4 mvp;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform vec3 light_position;

void main()
{
  //output position of vertex in clip space : mvp * position
  gl_Position = mvp * vec4(vertex_position_model_space, 1);

  //position of vertex in world space : model_matrix * position
  position_world_space = (model_matrix * vec4(vertex_position_model_space, 1)).xyz;

  //vector that goes from the vertex to the camera, in camera space
  //in camear space, the camera is at the origin (0,0,0)
  vec3 vertex_position_camera_space = (view_matrix * model_matrix *
      vec4(vertex_position_model_space, 1)).xyz;
  eye_direction_camera_space = vec3(0, 0, 0) - vertex_position_camera_space;

  //vector that goes from the vertex to the light, in camera space
  //model_matrix is omitted because it is an identity matrix
  vec3 light_position_camera_space = (view_matrix * vec4(light_position, 1)).xyz;
  light_direction_camera_space = light_position_camera_space + eye_direction_camera_space;

  //normal of the vertex in camera space
  normal_camera_space = (view_matrix * model_matrix * vec4(vertex_position_model_space, 0)).xyz;

  uv = vertex_uv;
}
