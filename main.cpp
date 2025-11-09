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

    if (Shader::Instance()->SendUniformData("time", 20))
    {
        // warning
    }
    
    // ==============================================================
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

        glBegin(GL_QUADS);
        
            glColor3f(1, 0, 0);
            glVertex3f(xPos - 0.5f, yPos + 0.5f, 0.0f);

            glColor3f(0, 1, 0);
            glVertex3f(xPos + 0.5f, yPos + 0.5f, 0.0f);

            glColor3f(0, 0, 1);
            glVertex3f(xPos + 0.5f, yPos - 0.5f, 0.0f);

            glColor3f(0, 0, 1);
            glVertex3f(xPos - 0.5f, yPos - 0.5f, 0.0f);

        glEnd();

        Screen::Instance()->Present();
    }

    Shader::Instance()->DetachShaders();
    Shader::Instance()->DestroyShaders();
    Shader::Instance()->DestroyProgram();

    Screen::Instance()->Shutdown();

    return 0;
}