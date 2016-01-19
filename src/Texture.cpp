#include "Texture.hpp"
#include <stdexcept>

//stb_image
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

bool Texture::LoadTextureFromFile(std::string path)
{
  bool success = true;

  int comp, width, height;

  //Load the image
  unsigned char* image = stbi_load(path.c_str(), & width, & height,
      &comp, STBI_rgb);

  //Check if the image was loaded
  if(!image)
    throw std::runtime_error(stbi_failure_reason());

  glGenTextures(1, &texture_id);
  PrintError(__LINE__, __FILE__);

  glBindTexture(GL_TEXTURE_2D, texture_id);
  PrintError(__LINE__, __FILE__);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  PrintError(__LINE__, __FILE__);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  PrintError(__LINE__, __FILE__);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
      GL_BGR, GL_UNSIGNED_BYTE, image);
  PrintError(__LINE__, __FILE__);

  glBindTexture(GL_TEXTURE_2D, 0);
  PrintError(__LINE__, __FILE__);

  stbi_image_free(image);

  return success;
}

GLuint Texture::LoadBMP(const char* path)
{
  printf("Reading image %s\n", path);

  //Data from the header of the BMP file
  unsigned char header[54];
  unsigned int data_pos;
  unsigned int image_size;
  unsigned int width, height;
  //Actual RGB data
  unsigned char* data;

  //Open the file
  FILE* file = fopen(path, "rb");
  if(!file)
  {
    printf("%s could not be opened.\n", path);
    getchar();
    return 0;
  }
  
  //Read the header, the first 54 bytes
  //If less than 54 bytes are read, there is an issue
  if(54 != fread(header, 1, 54, file))
  {
    printf("Not a correct BMP file\n");
    return 0;
  }

  //A bmp file always begins with "BM"
  if('B' != header[0] || 'M' != header[1])
  {
    printf("Not a correct BMP file\n");
    return 0;
  }

  //Make sure this is a 24bpp file
  if(0 != *(int*)&(header[0x1E]))
  {
    printf("Not a correct BMP file\n");
    return 0;
  }
  if(24 != *(int*)&(header[0x1C]))
  {
    printf("Not a correct BMP file\n");
    return 0;
  }

  //Read the information about the image
  data_pos = *(int*)&(header[0x0A]);
  image_size = *(int*)&(header[0x22]);
  width = *(int*)&(header[0x12]);
  height = *(int*)&(header[0x16]);

  //Some BMP files are misformatted, guess missing information
  if(0 == image_size)
    image_size = width * height * 3;
  if(0 == data_pos)
    data_pos = 54;

  //Create a buffer
  data = new unsigned char[image_size];

  //Read the data from the file into the buffer
  fread(data, 1, image_size, file);

  //Everything is in memory now, the file can be closed
  fclose(file);

  //Create on OpenGL texture
  glGenTextures(1, &texture_id);
  
  //Bind the newly created texture
  glBindTexture(GL_TEXTURE_2D, texture_id);

  //Give the image to opengl
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  //OpenGL has now copied that data, free the buffer
  delete[] data;

  //Trilenear filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  //Return the id of the texture
  return texture_id;
}

void Texture::FreeTexture()
{
  if(0 != texture_id)
  {
    glDeleteTextures(1, &texture_id);
    PrintError(__LINE__, __FILE__);
    texture_id = 0;
  }
}
