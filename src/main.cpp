#include "Renderer.hpp"
#include <random>

Renderer* renderer = nullptr;

int main(int argc, char** argv)
{

  renderer = new Renderer();
  renderer->Initialize();

  //Ensure we can capture the escape key being pressed
  do
  {
    renderer->Render();
    glfwPollEvents();
  }
  while(GLFW_PRESS != glfwGetKey(renderer->GetWindow(), GLFW_KEY_ESCAPE) && 
      0 == glfwWindowShouldClose(renderer->GetWindow()));

  return 0;
}
