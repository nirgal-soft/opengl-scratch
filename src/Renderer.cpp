#include "Renderer.hpp"
#include "Shader.hpp"
#include "Cube.hpp"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::SetWindow(GLFWwindow* window_in)
{
  window = window_in;
}

bool Renderer::Initialize()
{
  if(!glfwInit())
  {
    fprintf(stderr, "Failed to initialized GLFW\n");
    return false;
  }

  //4x anti-aliasing
  glfwWindowHint(GLFW_SAMPLES, 4);
  PrintError(__LINE__, __FILE__);
  //OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  PrintError(__LINE__, __FILE__);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  PrintError(__LINE__, __FILE__);
  //OpenGL core profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  PrintError(__LINE__, __FILE__);

  //Open a window and Create its OpenGL context
  window = glfwCreateWindow(1280, 720, "Modern OpenGL", NULL, NULL);
  PrintError(__LINE__, __FILE__);
  if(NULL == window)
  {
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, 3.3 not available\n");
    glfwTerminate();
    PrintError(__LINE__, __FILE__);
    return false;
  }

  glfwMakeContextCurrent(window);
  PrintError(__LINE__, __FILE__);
  //Experimental needed for core profile
  glewExperimental = true;
  //Initialze GLEW
  if(GLEW_OK != glewInit())
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return false;
  }
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

  //handle input initialization
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwPollEvents();


  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
  PrintError(__LINE__, __FILE__);
  printf("OpenGL shader language version: %s\n", 
    glGetString(GL_SHADING_LANGUAGE_VERSION));
  PrintError(__LINE__, __FILE__);
 
  program_id = LoadShaders("../shaders/SimpleVertexShader.vs", 
      "../shaders/SimpleFragmentShader.fs");

  cube = new Cube();
  cube->Init();
  cube->GetTextureLocation() = glGetUniformLocation(program_id, "texture_sampler");

  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  PrintError(__LINE__, __FILE__);
  glGenVertexArrays(1, &vertex_array_id);
  PrintError(__LINE__, __FILE__);
  glBindVertexArray(vertex_array_id);
  PrintError(__LINE__, __FILE__);

  matrix_id = glGetUniformLocation(program_id, "mvp");
  PrintError(__LINE__, __FILE__);

  //glfwSetCursorPos(window, 1280/2, 720/2);
  
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
  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  cube->Render();

  glfwSwapBuffers(window);
  first_iteration = false;

}

//Compute the matrices from given input
void Renderer::ComputeMatricesFromInputs()
{
  //glfwGetTime is called only once the first time this function is called
  static double last_time = glfwGetTime();

  //Compute time difference between current and last frame
  double current_time = glfwGetTime();
  float delta_time = float(current_time - last_time);

  //Get mouse position
  double mouse_x, mouse_y;
  glfwGetCursorPos(window, &mouse_x, &mouse_y);

  //Reset mouse position for next frame
  //glfwSetCursorPos(window, 1280/2, 720/2);

  //compute new orientation
  horizontal_angle += mouse_speed * float(1280/2 - mouse_x);
  vertical_angle += mouse_speed * float(720/2 - mouse_y);

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
  if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
    position += direction * delta_time * speed;

  //Move backward
  if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
    position -= direction * delta_time * speed;

  //Strafe right
  if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
    position += right * delta_time * speed;

  //Strafe left
  if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
    position -= right * delta_time * speed;

  float fov = initial_fov;

  projection_matrix = glm::perspective(glm::radians(fov), 16.0f/9.0f, 0.1f, 100.0f);

  //Camera matrix
  view_matrix = glm::lookAt(position, position + direction, up);

  //For next frame, the last time will be now
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
