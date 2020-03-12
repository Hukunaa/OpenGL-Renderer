#include <../include/Resources/Shader.h>
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace Resources::Shader;

Shader::Shader()
{
	shaderProgram = glCreateProgram();
}


Shader::~Shader()
{

}

GLuint Shader::CompileShader(const GLuint& p_type, const std::string& p_source)
{

	const char* vertexShaderChar = p_source.c_str();
	GLuint vertexShaderId = glCreateShader(p_type);

	glShaderSource(vertexShaderId, 1, &vertexShaderChar, nullptr);
	glCompileShader(vertexShaderId);

	int success;
	char infoLog[512];
	glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "Error Vertex shader compilation failed\n" << infoLog << std::endl;
	}
	return vertexShaderId;
}

std::string Shader::ShaderProgramSource(const std::string& p_filePath)
{
	std::string code;
	std::ifstream file;
	std::stringstream dataStream;

	try
	{
		file.open(p_filePath);
		dataStream << file.rdbuf();
		code = dataStream.str();
		file.close();
	}
	catch (std::ifstream::failure& exception)
	{
		std::cout << "Issue occured with specified file\n";
		std::cout << exception.what() << '\n';
	}

	return code;
}

void Shader::LoadRainBowShader()
{
	GLuint vertexShaderId = CompileShader(GL_VERTEX_SHADER, ShaderProgramSource("res/Shaders/VerticesShader.vert"));
	GLuint fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, ShaderProgramSource("res/Shaders/FragmentShader.frag"));
	glAttachShader(shaderProgram, vertexShaderId);
	glAttachShader(shaderProgram, fragmentShaderId);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::SetupRainBowShader()
{

	const GLint lightPos = glGetUniformLocation(shaderProgram, "lightPos");
	const GLint viewPos = glGetUniformLocation(shaderProgram, "viewPos");
	const GLint ModelMatrix = glGetUniformLocation(shaderProgram, "ModelMatrix");
	const GLint Camera = glGetUniformLocation(shaderProgram, "CameraMatrix");
	const GLint Projection = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
	const GLint lightColor = glGetUniformLocation(shaderProgram, "lightColor");

	ShaderData[0] = lightPos;
	ShaderData[1] = viewPos;
	ShaderData[2] = ModelMatrix;
	ShaderData[3] = Camera;
	ShaderData[4] = Projection;
	ShaderData[5] = lightColor;
	
}
