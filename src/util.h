#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl_gl3.h"
#include <GL/gl3w.h>
#include <GL/glu.h>
#include <SDL.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <string>

void PrintError(int line_number, std::string file_name);
static bool first_iteration = true;
