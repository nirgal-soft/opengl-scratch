#include "Cube.hpp"
#include "Texture.hpp"
#include "ObjLoader.hpp"
#include <random>

void Cube::Init()
{
  //Load object
  std::string obj_path = "/home/rearden/Documents/projects/modern_opengl/assets/cube.obj";
  if(!LoadObj(obj_path.c_str(), vertices, uvs, normals)) 
    printf("Could not load cube.obj\n");

  glGenBuffers(1, &vertex_buffer);
  PrintError(__LINE__, __FILE__);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  PrintError(__LINE__, __FILE__);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
      &vertices[0], GL_STATIC_DRAW);
  PrintError(__LINE__, __FILE__);

  glGenBuffers(1, &uv_data);
  PrintError(__LINE__, __FILE__);
  glBindBuffer(GL_ARRAY_BUFFER, uv_data);
  PrintError(__LINE__, __FILE__);
  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), 
      &uvs[0], GL_STATIC_DRAW);
  PrintError(__LINE__, __FILE__);

  //Set up texture
  texture = new Texture();
  texture->LoadBMP("/home/rearden/Documents/projects/modern_opengl/assets/uvtemplate.bmp");
}

void Cube::Update()
{

}

void Cube::Render()
{
  //Bind texture
  glActiveTexture(GL_TEXTURE0);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glUniform1i(texture_location, 0);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  //!st attribute buffer : vertices
  glEnableVertexAttribArray(0);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  //2nd atribute buffer : UVs
  glEnableVertexAttribArray(1);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glBindBuffer(GL_ARRAY_BUFFER, uv_data);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  glDrawArrays(GL_TRIANGLES, 0, 36);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  glDisableVertexAttribArray(0);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);
  glDisableVertexAttribArray(1);
  if(first_iteration)
    PrintError(__LINE__, __FILE__);

  first_iteration = false;
}

void Cube::Cleanup()
{
  if(texture)
  {
    texture->FreeTexture();
    delete texture;
    texture = nullptr;
  }
}
