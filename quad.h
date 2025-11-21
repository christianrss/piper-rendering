#ifndef QUAD_H
#define QUAD_H

#include "glad/glad.h"
#include "buffer.h"

class Quad
{
public:

    Quad();
    ~Quad();

    void Render();

private:
    Buffer m_buffer;
};

#endif