#include "util.h"

GLFWwindow* window = nullptr;

bool InitGL();

int main(int argc, char** argv)
{
  InitGL();

  //Ensure we can capture the escape key being pressed
  do
  {
    //Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  while(GLFW_PRESS != glfwGetKey(window, GLFW_KEY_ESCAPE) && 
      0 == glfwWindowShouldClose(window));

  return 0;
}

bool InitGL()
{
  if(!glfwInit())
  {
    fprintf(stderr, "Failed to initialized GLFW\n");
    return false;
  }

  //4x anti-aliasing
  glfwWindowHint(GLFW_SAMPLES, 4);
  //OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //OpenGL core profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //Open a window and Create its OpenGL context
  window = glfwCreateWindow(1280, 768, "Modern OpenGL", NULL, NULL);
  if(NULL == window)
  {
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, 3.3 not available\n");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);
  //Experimental needed for core profile
  glewExperimental = true;
  //Initialze GLEW
  if(GLEW_OK != glewInit())
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return false;
  }
  return true;
}
