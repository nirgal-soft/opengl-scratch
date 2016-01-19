#include "util.h"

class Texture
{
  public:
    Texture();
    ~Texture();

    bool LoadTextureFromFile(std::string path);
    GLuint LoadBMP(const char* path);
    void FreeTexture();

    GLuint GetTextureID(){return texture_id;}

  private:
    GLuint texture_id = 0;
};
