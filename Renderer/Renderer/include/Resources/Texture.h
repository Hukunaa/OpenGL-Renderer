#pragma once
#include <cstdio>
#include <vector>
#include <GL/glew.h>
#include <../include/Core/Math/Vector/Vec3.h>

using namespace Math::Vector;

namespace Resources::Texture
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		static GLuint GenerateVBO(const std::vector<Vec3>& vertices, const std::vector<Vec3>& normals, std::vector<GLfloat>& FloatData);
		static GLuint GenerateVAO();
		static GLuint GenerateEBO(const std::vector<GLuint>& Indices);
	};
}

