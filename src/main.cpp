#include "Renderer.hpp"
Renderer* renderer = nullptr;

int main(int argc, char** argv)
{
  //Initialize renderer
  renderer = new Renderer();
  renderer->Initialize();

  //run the main loop
  bool running = true;
  while(running)
  {
    //handle events
    sf::Event event;
    while(renderer->GetWindow()->pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        running = false;
      else if(event.type == sf::Event::Resized)
        glViewport(0, 0, event.size.width, event.size.height);
    }

    renderer->Render();
  }

  delete renderer;
  renderer = nullptr;

  return 0;
}
