#include "ObjLoader.hpp"
#include <cstring>

//this is is no way complete or good. this needs so much more
//research and overhauling. objects should be read in by binary

bool LoadObj(const char* path, std::vector<glm::vec3>& out_verts,
    std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
  printf("Loading .obj file%s: \n", path);

  std::vector<unsigned int> vertex_indices, uv_indices, normal_indices;
  std::vector<glm::vec3> temp_verts;
  std::vector<glm::vec2> temp_uvs;
  std::vector<glm::vec3> temp_normals;

  FILE* file = fopen(path, "r");
  if(NULL == file)
  {
    printf("Impossible to open the file. Are you in the right path?\n");
    getchar();
    return false;
  }

  int temp_loop_counter = 0;
  while(true)
  {
    char line_header[128];
    int res = fscanf(file, "%s", line_header);
    if(EOF == res)
      break;

    if(strcmp(line_header, "v") == 0)
    {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      temp_verts.push_back(vertex);
    }
    else if(strcmp(line_header, "vt") == 0)
    {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      temp_uvs.push_back(uv);
    }
    else if(strcmp(line_header, "vn") == 0)
    {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      temp_normals.push_back(normal);
    }
    else if(strcmp(line_header, "f") == 0)
    {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertex_index[3], uv_index[3], normal_index[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
          &vertex_index[0], &uv_index[0], &normal_index[0],
          &vertex_index[1], &uv_index[1], &normal_index[1],
          &vertex_index[2], &uv_index[2], &normal_index[2]);
      if(9 != matches)
      {
        printf("File can't be read by simple parster\n");
        return false;
      }
      vertex_indices.push_back(vertex_index[0]);
      vertex_indices.push_back(vertex_index[1]);
      vertex_indices.push_back(vertex_index[2]);
      uv_indices.push_back(uv_index[0]);
      uv_indices.push_back(uv_index[1]);
      uv_indices.push_back(uv_index[2]);
      normal_indices.push_back(normal_index[0]);
      normal_indices.push_back(normal_index[1]);
      normal_indices.push_back(normal_index[2]);
    }
    else
    {
      char comment[1000];
      fgets(comment, 1000, file);
    }

    temp_loop_counter++;
  }

  //For each vertex of the triangle
  for(size_t iter = 0; iter < vertex_indices.size(); iter++)
  {
    //Get the indices of its attributes
    unsigned int vertex_index = vertex_indices[iter];
    unsigned int uv_index = uv_indices[iter];
    unsigned int normal_index = normal_indices[iter];

    //Get the attributes thanksto the index
    glm::vec3 vertex = temp_verts[vertex_index - 1];
    glm::vec2 uv = temp_uvs[uv_index - 1];
    glm::vec3 normal = temp_normals[normal_index - 1];

    //Put the attributes in buffers
    out_verts.push_back(vertex);
    out_uvs.push_back(uv);
    out_normals.push_back(normal);
  }

  return true;
}
