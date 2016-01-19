#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Shader.hpp"

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
  //Create the shaders
  GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

  //Read the vertex shader code from the file
  std::string vertex_shader_code;
  std::ifstream vertex_shader_stream(vertex_file_path, std::ios::in);
  if(vertex_shader_stream.is_open())
  {
    std::string line = "";
    while(getline(vertex_shader_stream, line))
      vertex_shader_code += "\n" + line;
    vertex_shader_stream.close();
  }
  else
  {
    printf("Impossible to open %s", vertex_file_path);
    getchar();
    return 0;
  }

  //Read fragment shader code from the file
  std::string fragment_shader_code;
  std::ifstream fragment_shader_stream(fragment_file_path, std::ios::in);
  if(fragment_shader_stream.is_open())
  {
    std::string line = "";
    while(getline(fragment_shader_stream, line))
      fragment_shader_code += "\n" + line;
    fragment_shader_stream.close();
  }
  else
  {
    printf("Impossible to open %s", fragment_file_path);
    getchar();
    return 0;
  }

  GLint result = GL_FALSE;
  int info_log_length;

  //Compile vertex shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const* vertex_source_pointer = vertex_shader_code.c_str();
  glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, NULL);
  PrintError(__LINE__, __FILE__);
  glCompileShader(vertex_shader_id);
  PrintError(__LINE__, __FILE__);

  //Check vertex shader
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
  PrintError(__LINE__, __FILE__);
  glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
  PrintError(__LINE__, __FILE__);
  if(0 < info_log_length)
  {
    std::vector<char> vertex_shader_error_message(info_log_length + 1);
    glGetShaderInfoLog(vertex_shader_id, info_log_length, NULL, 
        &vertex_shader_error_message[0]);
    PrintError(__LINE__, __FILE__);
    printf("%s\n", &vertex_shader_error_message[0]);
  }

  //Compile fragment shader
  printf("Compiling shader :  %s\n", fragment_file_path);
  char const* fragment_source_poiner = fragment_shader_code.c_str();
  glShaderSource(fragment_shader_id, 1, &fragment_source_poiner, NULL);
  PrintError(__LINE__, __FILE__);
  glCompileShader(fragment_shader_id);
  PrintError(__LINE__, __FILE__);

  //Check fragment shader
  glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
  PrintError(__LINE__, __FILE__);
  glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
  PrintError(__LINE__, __FILE__);
  if(0 < info_log_length)
  {
    std::vector<char> fragment_shader_error_message(info_log_length + 1);
    glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, 
        &fragment_shader_error_message[0]);
    PrintError(__LINE__, __FILE__);
    printf("%s\n", &fragment_shader_error_message[0]);
  }

  //Link the program
  printf("Linking program\n");
  GLuint program_id  = glCreateProgram();
  PrintError(__LINE__, __FILE__);
  glAttachShader(program_id, vertex_shader_id);
  PrintError(__LINE__, __FILE__);
  glAttachShader(program_id, fragment_shader_id);
  PrintError(__LINE__, __FILE__);
  glLinkProgram(program_id);
  PrintError(__LINE__, __FILE__);

  //Check the program
  glGetProgramiv(program_id, GL_LINK_STATUS, &result);
  PrintError(__LINE__, __FILE__);
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
  PrintError(__LINE__, __FILE__);
  if(0 < info_log_length)
  {
    std::vector<char> program_error_message(info_log_length + 1);
    glGetProgramInfoLog(program_id, info_log_length, NULL, &program_error_message[0]);
    PrintError(__LINE__, __FILE__);
    printf("%s\n", &program_error_message[0]);
  }

  glDetachShader(program_id, vertex_shader_id);
  PrintError(__LINE__, __FILE__);
  glDetachShader(program_id, fragment_shader_id);
  PrintError(__LINE__, __FILE__);

  glDeleteShader(vertex_shader_id);
  PrintError(__LINE__, __FILE__);
  glDeleteShader(fragment_shader_id);
  PrintError(__LINE__, __FILE__);

  return program_id;
}
