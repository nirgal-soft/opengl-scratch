#version 330 core

//interpolated values from the vertex shaders
in vec2 uv;
in vec3 position_world_space;
in vec3 normal_camera_space;
in vec3 eye_direction_camera_space;
in vec3 light_direction_camera_space;

//output data
out vec3 color;

//values that stay constant
uniform sampler2D texture_sampler;
uniform mat4 model_view;
uniform vec3 light_position;

void main()
{
  //Light emission properties
  //should probably be uniforms
  vec3 light_color = vec3(1, 1, 1);
  float light_power = 50.0f;

  //material properties
  vec3 material_diffuse_color = texture(texture_sampler, uv).rgb;
  vec3 material_ambient_color = vec3(0.1, 0.1, 0.1) * material_diffuse_color;
  vec3 material_specular_color = vec3(0.3, 0.3, 0.3);

  //distance to light
  float distance = length(light_position - position_world_space);

  //normal of the computed fragment, in camera space
  vec3 normal = normalize(normal_camera_space);
  //direction of the light (from the fragment to the light)
  vec3 light = normalize(light_direction_camera_space);
  //cosine of the angle between the normal and the light direction
  //clamed above 0
  // - light is at the vertical of the triangle : 1
  // - light is perpendicular to the triangle : 0
  // - light is behind the triangle : 0
  float cos_theta = clamp(dot(normal, light), 0, 1);

  //eye vector
  vec3 eye = normalize(eye_direction_camera_space);
  //direction in which the triangle reflects the light
  vec3 reflection = reflect(-light, normal);
  //cosine of the angle between the eye vector and the reflect vector
  //clamped to 0
  // - looking into the reflection : 1
  // - looking elsewhere : < 1
  float cos_alpha = clamp(dot(eye, reflection), 0, 1);

  color = 
    //Ambient : simulates direct lighting
    material_ambient_color
    + material_diffuse_color * light_color * light_power * cos_theta / (distance*distance)
    + material_specular_color * light_color * light_power * pow(cos_alpha, 5) / (distance*distance);;
}
