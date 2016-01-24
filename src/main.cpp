#include "Renderer.hpp"
Renderer* renderer = nullptr;

int main(int argc, char** argv)
{
  //Initialize renderer
  renderer = new Renderer();
  renderer->Initialize();

  SDL_Event event;
  SDL_StartTextInput();
  bool quit = false;

  while(!quit)
  //run the main loop
  {
    while(SDL_PollEvent(&event) != 0)
    {
      ImGui_ImplSdlGL3_ProcessEvent(&event);
      if(event.type == SDL_QUIT)
        quit = true;
      else if(event.type == SDL_TEXTINPUT)
      {

      }
    }
    renderer->Render();
  }
  
  SDL_StopTextInput();
  delete renderer;
  renderer = nullptr;

  return 0;
}
