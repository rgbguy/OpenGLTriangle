#pragma once

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError());
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			": " << file << ": " << line << "" << std::endl;
		return false;
	}
	return true;
}

void CheckShaderStatus(GLint shaderID)
{
	GLint shaderType;
	glGetShaderiv(shaderID, GL_SHADER_TYPE, &shaderType);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	std::string finalType;
	if (shaderType == GL_VERTEX_SHADER) {
		finalType = "Vertex ";
	}
	else if (shaderType == GL_FRAGMENT_SHADER) {
		finalType = "Fragment ";
	}

	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << finalType << "Shader compilation failed: " << infoLog << std::endl;
	}


}