#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <string>

void PrintError(int line_number, std::string file_name);
static bool first_iteration = true;
