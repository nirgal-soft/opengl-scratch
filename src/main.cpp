#include "Renderer.hpp"
Renderer* renderer = nullptr;

int main(int argc, char** argv)
{
  //Initialize renderer
  renderer = new Renderer();
  renderer->Initialize();

  //run the main loop
  while(renderer->GetWindow()->isOpen())
  {
    //handle events
    sf::Event event;
    while(renderer->GetWindow()->pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          renderer->GetWindow()->close();
          break;
        case sf::Event::KeyPressed:
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            renderer->GetWindow()->close();
          break;
      }
    }

    renderer->Render();

  }

  delete renderer;
  renderer = nullptr;

  return 0;
}
