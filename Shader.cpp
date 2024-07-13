#include <iostream>
#include <fstream>
#include <GL/glew.h>  
#include "Shader.h"   

#pragma warning(disable : 4996)

char* Shader::readShaderSource(const char* shaderFile)
{
    // Open the file in binary mode
    std::ifstream file(shaderFile, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        // File couldn't be opened
        return nullptr;
    }

    // Get the file size
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory to hold the file content
    char* buf = new char[size + 1];

    // Read the file content into the buffer
    if (file.read(buf, size))
    {
        buf[size] = '\0'; // Null-terminate the string
    }
    else
    {
        // Reading failed, clean up and return nullptr
        delete[] buf;
        return nullptr;
    }

    return buf;
}


GLuint Shader::createProgram(GLchar* vertexfilename, GLchar* fragmentfilename)
{
    GLenum ErrorCheckValue = glGetError();
    GLint success;
    GLchar infoLog[512];

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Leggiamo il codice del Vertex Shader
    GLchar* VertexShader = readShaderSource(vertexfilename);

    // Generiamo un identificativo per il vertex shader
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    // Associamo all'identificativo il codice del vertex shader
    glShaderSource(vertexShaderId, 1, (const GLchar**)&VertexShader, NULL);

    // Compiliamo il Vertex Shader
    glCompileShader(vertexShaderId);

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    // Leggiamo il codice del Fragment Shader
    GLchar* FragmentShader = readShaderSource(fragmentfilename);

    // Generiamo un identificativo per il FRAGMENT shader
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, (const GLchar**)&FragmentShader, NULL);

    // Compiliamo il FRAGMENT Shader
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    ErrorCheckValue = glGetError();
    std::cout << ErrorCheckValue;

    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(stderr, "ERROR: Could not create the shaders: %s \n", gluErrorString(ErrorCheckValue));
        exit(-1);
    }

    // Creiamo un identificativo di un eseguibile e gli colleghiamo i due shader compilati
    GLuint programId = glCreateProgram();

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    return programId;
}
