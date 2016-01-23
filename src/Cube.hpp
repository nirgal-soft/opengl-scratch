#pragma once
#include "util.h"
#include <vector>

class Texture;

class Cube
{
  public:
    void Init();
    void LoadTexture(std::string path);
    void Update();
    void Render();
    void Cleanup();

    glm::mat4* GetModelMatrix(){return &model_matrix;}
    GLuint& GetTextureLocation(){return texture_location;}

  private:
    glm::mat4 model_matrix = glm::mat4(1.0f);

    GLuint vertex_buffer = 0;
    GLuint color_buffer = 0;
    GLuint uv_data = 0;
    GLuint normal_data = 0;
    GLuint index_buffer = 0;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<unsigned short> indices;

    Texture* texture = nullptr;
    GLuint texture_location = 0;
};
