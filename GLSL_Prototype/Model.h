#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include "ObjectLoader.h"

class Model
{
    public:

    Model();

    void loadFromFile(const char* filePath, const char* mtlPath);

    void draw();

    void deleteBuffers() {
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &uvbuffer);
        glDeleteBuffers(1, &normalbuffer);
        glDeleteBuffers(1, &colourbuffer);
        glDeleteTextures(1, &texture);
    }

    private:

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colours;

    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint colourbuffer;
    GLuint texture;


    GLuint getProgramID() {
        GLuint i = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)(&i));
        return i;
    }
};