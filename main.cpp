#include <iostream>
#include "screen.h"
#include "input.h"
#include "glad/glad.h"
#include "shader.h"

bool isAppRunning = true;

int main(int argc, char* argv[])
{
    Screen::Instance()->Initialize();

    if (!Shader::Instance()->CreateProgram())
    {
        return 0;
    }

    if (!Shader::Instance()->CreateShaders())
    {
        return 0;
    }

    if(!Shader::Instance()->CompileShaders("Shaders/Main.vert", Shader::ShaderType::VERTEX_SHADER))
    {
        // TODO
    }

    if (!Shader::Instance()->CompileShaders("Shaders/Main.frag", Shader::ShaderType::FRAGMENT_SHADER))
    {
        // TODO
    }

    Shader::Instance()->AttachShaders();
    
    if (!Shader::Instance()->LinkProgram())
    {
        // TODO
    }

    float xPos = 0.0f;
    float yPos = 0.0f;

    //==============================================================
    // data that represents vertices for quad
    GLfloat vertices[] = {
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, // triangle 1

        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f // triangle 2
    };

    // data that represents color for quad
    GLfloat colors[] = {
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 1.0f, 1.0f, // triangle 1

         1.0f, 1.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 1.0f, 1.0f // triangle 2
    };

    GLuint shaderProgramID = Shader::Instance()->GetShaderProgramID();

    GLint vertexID = glGetAttribLocation(shaderProgramID, "vertexIn");
    GLint colorID = glGetAttribLocation(shaderProgramID, "colorIn");

    GLuint vertexVBO;
    GLuint colorVBO;
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &colorVBO);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(vertexID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vertexID);

        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(colorID);

    glBindVertexArray(0);
    //==============================================================
    while (isAppRunning)
    {
        Screen::Instance()->ClearScreen();

        Input::Instance()->Update();

        char keyPressed = Input::Instance()->GetKeyDown();

        isAppRunning = !Input::Instance()->IsXClicked();

        if (Input::Instance()->IsKeyPressed())
        {
        
            if (Input::Instance()->GetKeyDown() == 'a')
            {
                xPos -= 0.01f;
            } 

            else if (Input::Instance()->GetKeyDown() == 'd')
            {
                xPos += 0.01f;
            }

            else if (Input::Instance()->GetKeyDown() == 'w')
            {
                yPos += 0.01f;
            }

            else if (Input::Instance()->GetKeyDown() == 's')
            {
                yPos -= 0.01f;
            }
        
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        Screen::Instance()->Present();
    }

    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &colorVBO);
    glDeleteVertexArrays(1, &VAO);

    glDisableVertexAttribArray(vertexID);
    glDisableVertexAttribArray(colorID);

    Shader::Instance()->DetachShaders();
    Shader::Instance()->DestroyShaders();
    Shader::Instance()->DestroyProgram();

    Screen::Instance()->Shutdown();

    return 0;
}