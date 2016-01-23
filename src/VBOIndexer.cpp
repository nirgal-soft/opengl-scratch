#include "VBOIndexer.hpp"
#include <cstring>
#include <map>

//returns ture if v1 is equal to v2
bool IsNear(float v1, float v2)
{
  return fabs(v1-v2) < 0.01f;
}

//Searches through all already exported vertices
//for a similar one
//similar = same position + same uvs + smae normal
bool GetSimilarVertexIndex_slow(
    glm::vec3& in_vertex, glm::vec2& in_uv, glm::vec3& in_normal,
    std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals, unsigned short& result)
{
  //linear search
  for(size_t iter = 0; iter < out_vertices.size(); iter++)
  {
    if(
        IsNear(in_vertex.x, out_vertices[iter].x)
        && IsNear(in_vertex.y, out_vertices[iter].y)
        && IsNear(in_vertex.z, out_vertices[iter].z)
        && IsNear(in_uv.x, out_uvs[iter].x)
        && IsNear(in_uv.y, out_uvs[iter].y)
        && IsNear(in_normal.x, out_normals[iter].x)
        && IsNear(in_normal.y, out_normals[iter].y)
        && IsNear(in_normal.z, out_normals[iter].z)
        )
    {
      result = iter;
      return true;
    }
  }

  //No other vertex could be used instead
  //add it to the VBO
  return false;
}

struct PackedVertex
{
  glm::vec3 position;
  glm::vec2 uv;
  glm::vec3 normal;
  bool operator<(const PackedVertex that) const
  {
    return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
  }
};

bool GetSimilarVertexIndex(PackedVertex& packed_vertex,
    std::map<PackedVertex, unsigned short>& vertex_to_out_index, 
    unsigned short& result)
{
  std::map<PackedVertex, unsigned short>::iterator iter = 
    vertex_to_out_index.find(packed_vertex);
  if(vertex_to_out_index.end() == iter)
    return false;
  else
  {
    result = iter->second;
    return true;
  }
}

void IndexVBO(
    std::vector<glm::vec3>& in_vertices,
    std::vector<glm::vec2>& in_uvs,
    std::vector<glm::vec3>& in_normals,
    std::vector<unsigned short>& out_indices,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
    )
{
  std::map<PackedVertex, unsigned short> vertex_to_out_index;

  //for each input vertex
  for(size_t iter = 0; iter < in_vertices.size(); iter++)
  {
    PackedVertex packed_vertex = {in_vertices[iter], in_uvs[iter], in_normals[iter]};

    //try to find similar vertex in out_XXXX
    unsigned short index;
    bool found = GetSimilarVertexIndex(packed_vertex, vertex_to_out_index, index);

    if(found)
      out_indices.push_back(index);
    else
    {
      out_vertices.push_back(in_vertices[iter]);
      out_uvs.push_back(in_uvs[iter]);
      out_normals.push_back(in_normals[iter]);
      unsigned short new_index = (unsigned short)out_vertices.size() - 1;
      out_indices.push_back(new_index);
      vertex_to_out_index[packed_vertex] = new_index;
    }
  }
}
