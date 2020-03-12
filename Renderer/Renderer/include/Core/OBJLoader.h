#pragma once
#include <cstdio>
#include <vector>
#include <Core/Math/Vector/Vec3.h>
#include <GL/glew.h>

using namespace Math::Vector;

namespace Resources::Model::OBJParser
{
	class OBJLoader
	{
	public:
		OBJLoader();
		~OBJLoader();

		static void LoadObj(const	std::string& path, 
									std::vector<Vec3>& o_vertices,
									std::vector<Vec3>& o_uvs, 
									std::vector<Vec3>& o_normals,
									std::vector<GLuint>& o_indices, int slash, const int polyNb);
	};
}
