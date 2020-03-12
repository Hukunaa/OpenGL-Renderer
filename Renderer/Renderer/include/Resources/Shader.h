#pragma once
#include <iostream>
#include <GL/glew.h>
#include "Core/Math/Vector/Vec3.h"

using namespace Math::Vector;

namespace Resources::Shader
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		GLuint shaderProgram;
		GLint ShaderData[6];

		Vec3 Color;

		static GLuint CompileShader(const GLuint& p_type, const std::string& p_source);
		static std::string ShaderProgramSource(const std::string& p_filePath);
		void LoadRainBowShader();
		void SetupRainBowShader();
	};
}
