#include <fstream>
#include <iostream>
#include "shader.h"

Shader* Shader::Instance()
{
    static Shader* shaderObject = new Shader();
    return shaderObject;
}

Shader::Shader()
{
    this->m_shaderProgramID = 0;
    this->m_vertexShaderID = 0;
    this->m_fragmentShaderID = 0;
}

bool Shader::CreateProgram()
{
    this->m_shaderProgramID = glCreateProgram();

    if (this->m_shaderProgramID == 0)
    {
        std::cout << "Error creating shader program." << std::endl;
        return false;
    }

    return true;
}

bool Shader::CreateShaders()
{
    this->m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    if (this->m_vertexShaderID == 0)
    {
        std::cout << "Error creating vertex shader object." << std::endl;
        return false;
    }

    this->m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    if (this->m_fragmentShaderID == 0)
    {
        std::cout<< "Error creating fragment shader object." << std::endl;
        return false;
    }

    return true;
}

bool Shader::CompileShaders(const std::string& filename, ShaderType shaderType)
{
    std::fstream file;
    std::string text;
    std::string sourceCode;
    GLuint shaderID;

    shaderID = (shaderType == ShaderType::VERTEX_SHADER) ? this->m_vertexShaderID : this->m_fragmentShaderID;

    file.open(filename);

    if (!file)
    {
        std::cout << "Error reading shader file." << filename << std::endl;
        return false;
    }

    while(!file.eof())
    {
        std::getline(file, text);
        sourceCode += text + "\n";
    }

    file.close();

    const GLchar* finalSourceCode = reinterpret_cast<const GLchar*>(sourceCode.c_str());
    glShaderSource(shaderID, 1, &finalSourceCode, nullptr);

    glCompileShader(shaderID);

    GLint errorCode;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &errorCode);

    if(errorCode == GL_TRUE)
    {
        std::cout << "Shader compilation successful!" << std::endl;
    }

    else
    {
        GLchar errorMessage[1000];
        GLsizei bufferSize = 1000;

        glGetShaderInfoLog(shaderID, bufferSize, &bufferSize, errorMessage);
        std::cout << errorMessage << std::endl;
    }   

    return true;
}

void Shader::AttachShaders()
{
    glAttachShader(this->m_shaderProgramID, this->m_vertexShaderID);
    glAttachShader(this->m_shaderProgramID, this->m_fragmentShaderID);
}

bool Shader::LinkProgram()
{
    glLinkProgram(this->m_shaderProgramID);

    glUseProgram(this->m_shaderProgramID);

    GLint errorCode;

    glGetProgramiv(this->m_shaderProgramID, GL_LINK_STATUS, &errorCode);

    if (errorCode == GL_TRUE)
    {
        std::cout << "Shader linking successful!" << std::endl;
    }
    
    else
    {
        GLchar errorMessage[1000];
        GLsizei bufferSize = 1000;

        glGetProgramInfoLog(this->m_shaderProgramID, bufferSize, &bufferSize, errorMessage);
        std::cout << errorMessage << std::endl;
    }


    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(this->m_shaderProgramID, this->m_vertexShaderID);
    glDetachShader(this->m_shaderProgramID, this->m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(this->m_vertexShaderID);
    glDeleteShader(this->m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
    glDeleteProgram(this->m_shaderProgramID);
}

bool Shader::SendUniformData(const std::string &uniformName, GLint data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
        return false;
    }

    glUniform1i(ID, data);
    return true;
}

bool Shader::SendUniformData(const std::string &uniformName, GLuint data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
        return false;
    }

    glUniform1ui(ID, data);
    return true;
}

bool Shader::SendUniformData(const std::string &uniformName, GLfloat data)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
        return false;
    }

    glUniform1f(ID, data);
    return true;
}

bool Shader::SendUniformData(const std::string &uniformName, GLfloat x, GLfloat y)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
        return false;
    }

    glUniform2f(ID, x, y);
    return true;
}

bool Shader::SendUniformData(const std::string &uniformName, GLfloat x, GLfloat y, GLfloat z)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
        return false;
    }

    glUniform3f(ID, x, y, z);
    return true;
}

bool Shader::SendUniformData(const std::string &uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLint ID = glGetUniformLocation(this->m_shaderProgramID, uniformName.c_str());

    if (ID == -1)
    {
        std::cout << "Shader variable " << uniformName << " not found or not used." << std::endl;
        return false;
    }

    glUniform4f(ID, x, y, z, w);
    return true;
}
