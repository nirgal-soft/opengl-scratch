#include "Renderer.hpp"
#include "Shader.hpp"
#include "Cube.hpp"

Renderer::Renderer()
{
  
}

Renderer::~Renderer()
{

}

void Renderer::SetWindow(sf::Window* window_in)
{
  window = window_in;
}

bool Renderer::Initialize()
{
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 3;
  
  //create the window
  window = new sf::Window(sf::VideoMode(1280, 720), "Modern OpenGL with SFML",
      sf::Style::Default, settings);
  window->setVerticalSyncEnabled(true);
  PrintError(__LINE__, __FILE__);
 
  glewExperimental = true;
  PrintError(__LINE__, __FILE__);
  if(GLEW_OK != glewInit())
    printf("Could not initialize GLEW\n");
  PrintError(__LINE__, __FILE__);

  //Enable depth test
  glEnable(GL_DEPTH_TEST);
  PrintError(__LINE__, __FILE__);

  //Accept fragment it is closer to the camera than the former one
  glDepthFunc(GL_LESS);
  PrintError(__LINE__, __FILE__);

  //Cull triangles which normals are not toward the camear
  glEnable(GL_CULL_FACE);
  PrintError(__LINE__, __FILE__);

  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
  PrintError(__LINE__, __FILE__);
  printf("OpenGL shader language version: %s\n", 
    glGetString(GL_SHADING_LANGUAGE_VERSION));
  PrintError(__LINE__, __FILE__);

  std::string vert_shader_path = "/home/rearden/Documents/projects/modern_opengl/shaders/SimpleVertexShader.vs";
  std::string frag_shader_path = "/home/rearden/Documents/projects/modern_opengl/shaders/SimpleFragmentShader.fs";
  program_id = LoadShaders(vert_shader_path.c_str(), 
      frag_shader_path.c_str());;

  cube = new Cube();
  cube->Init();
  cube->GetTextureLocation() = glGetUniformLocation(program_id, "texture_sampler");

  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  PrintError(__LINE__, __FILE__);
  glGenVertexArrays(1, &vertex_array_id);
  PrintError(__LINE__, __FILE__);
  glBindVertexArray(vertex_array_id);
  PrintError(__LINE__, __FILE__);

  mvp_id = glGetUniformLocation(program_id, "mvp");
  PrintError(__LINE__, __FILE__);
  view_matrix_id = glGetUniformLocation(program_id, "view_matrix");
  PrintError(__LINE__, __FILE__);
  model_matrix_id = glGetUniformLocation(program_id, "model_matrix");
  PrintError(__LINE__, __FILE__);
  light_id = glGetUniformLocation(program_id, "light_position");
  PrintError(__LINE__, __FILE__);

  sf::Mouse::setPosition(sf::Vector2i(1280/2, 720/2), *window);
  
  return true;
}

void Renderer::Update(float delta_time)
{

}

void Renderer::Render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  //select shader pair to use
  glUseProgram(program_id);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  ComputeMatricesFromInputs();
  glm::mat4 proj = projection_matrix;
  glm::mat4 view = view_matrix;
  glm::mat4 model = *cube->GetModelMatrix();
  mvp = proj * view * model;

  //send our transformation to the shader pair
  glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &model[0][0]);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view[0][0]);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  glm::vec3 light_position = glm::vec3(mvp[3]);
  glUniform3f(light_id, light_position.x, light_position.y, light_position.z);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  cube->Render();

  window->display();
  first_iteration = false;
}

//Compute the matrices from given input
void Renderer::ComputeMatricesFromInputs()
{
  //GetTime is called only once the first time this function is called
  static sf::Time last_time = clock.getElapsedTime();

  //Compute time difference between current and last frame
  sf::Time current_time = clock.getElapsedTime();
  float delta_time = sf::Time(current_time - last_time).asSeconds();

  //get mouse position
  sf::Vector2i cursor_pos = sf::Mouse::getPosition(*window);
  sf::Mouse::setPosition(sf::Vector2i(1280/2, 720/2), *window);

  //compute new orientation
  horizontal_angle += mouse_speed * float(1280/2 - cursor_pos.x);
  vertical_angle += mouse_speed * float(720/2 - cursor_pos.y);

  //Direction
  glm::vec3 direction(
      cos(vertical_angle) * sin(horizontal_angle),
      sin(vertical_angle),
      cos(vertical_angle) * cos(horizontal_angle));

  //Right vector
  glm::vec3 right = glm::vec3(
      sin(horizontal_angle - 3.14f/2.0f),
      0, cos(horizontal_angle - 3.14f/2.0f));

  //up vector
  glm::vec3 up = glm::cross(right, direction);

  //Move forward
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    position += direction * delta_time * speed;

  //Move backward
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    position -= direction * delta_time * speed;

  //Strafe right
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    position += right * delta_time * speed;

  //Strafe left
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    position -= right * delta_time * speed;

  float fov = initial_fov;

  projection_matrix = glm::perspective(glm::radians(fov), 16.0f/9.0f, 0.1f, 100.0f);

  //Camera matrix
  view_matrix = glm::lookAt(position, position + direction, up);

  //set last time to current time
  last_time = current_time;
}

void Renderer::CleanUp()
{
  cube->Cleanup();
  if(cube)
  {
    delete cube;
    cube = nullptr;
  }
  
  glDeleteProgram(program_id);
  PrintError(__LINE__, __FILE__);
}
