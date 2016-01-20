#pragma once
#include "util.h"

class Cube;

class Renderer
{
  public:
    Renderer();
    ~Renderer();

    bool Initialize();
    void Update(float delta_time);
    void Render();
    void CleanUp();

    void ComputeMatricesFromInputs();

    glm::mat4 GetViewMatrix(){return view_matrix;}
    glm::mat4 GetProjectionMatrix(){return projection_matrix;}
    glm::mat4 GetMVP(){return mvp;}
    sf::Window* GetWindow(){return window;}

    void SetViewMatrix(glm::mat4 vm){view_matrix = vm;}
    void SetProjectionMatrix(glm::mat4 pm){projection_matrix = pm;}
    void SetMVP(glm::mat4 m){mvp = m;}
    void SetWindow(sf::Window* w);

  private:
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
    glm::mat4 mvp;
    sf::Window* window = nullptr;

    sf::Clock clock;

    //Initial position on +z
    glm::vec3 position = glm::vec3(0, 0, 5);
    //Initial horizontal angle toward -Z
    float horizontal_angle = 3.14f;
    //Initial vertical angle
    float vertical_angle = 0.0f;
    //Initial field of view
    float initial_fov = 45.0f;

    float speed = 3.0f;
    float mouse_speed = 0.00005f;

    //Shader program
    GLuint program_id = 0;
    GLuint vertex_array_id = 0;
    GLuint matrix_id = 0;

    //Cube for testing
    Cube* cube = nullptr;
};
