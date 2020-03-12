#pragma once
#include <vector>
#include "Core/Math/Vector/Vec3.h"
#include <GL/glew.h>

using namespace Math::Vector;

namespace Resources::Model
{
	class Model
	{
	public:
		Model();
		~Model();

		std::vector<unsigned int> VerticesIndices;
		std::vector<GLfloat> FloatVertices;

		std::vector<Vec3> vertices;
		std::vector<Vec3> uvs;
		std::vector<Vec3> normals;
	};	
}

