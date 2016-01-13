#include "util.h"

void PrintError(int line_number, std::string file_name)
{
  GLenum error = glGetError();
  if(GL_NO_ERROR != error)
    printf("Error at line %d in %s: %s\n", line_number, file_name.c_str(),
        gluErrorString(error));
}
