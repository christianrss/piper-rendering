#ifndef QUAD_H
#define QUAD_H

#include "glad/glad.h"

class Quad
{
public:

    Quad();
    ~Quad();

    void Render();

private:

    GLuint m_VAO;
    GLint m_colorID;
    GLint m_vertexID;
    GLuint m_colorVBO;
    GLuint m_vertexVBO;

};

#endif