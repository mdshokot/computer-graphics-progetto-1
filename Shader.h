#pragma once

class Shader
{
public:
	static GLuint createProgram(char* vertexfilename, char* fragmentfilename);
	static char* readShaderSource(const char* shaderFile);

private:
	Shader() {}
};


