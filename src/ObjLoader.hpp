#pragma once
#include <vector>
#include "util.h"

bool LoadObj(const char* path, std::vector<glm::vec3>& out_verts,
    std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);
