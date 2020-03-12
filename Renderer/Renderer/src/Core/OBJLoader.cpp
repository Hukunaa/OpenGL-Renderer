#define _CRT_SECURE_NO_DEPRECATE
#include <../include/Core/OBJLoader.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <../include/Resources/Model.h>


using namespace Resources::Model::OBJParser;
using namespace Resources::Model;

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

void OBJLoader::LoadObj(const std::string& path, std::vector<Vec3>& o_vertices, 
												 std::vector<Vec3>& o_uvs, 
												 std::vector<Vec3>& o_normals,
												 std::vector<GLuint>& o_indices, 
												 int slash, const int polyNb)
{
	const char* filePath = path.c_str();
	std::cout << "Loading OBJ file..." << "\n\n\n";
	
	std::vector<Vec3> tmp_vertices;
	std::vector<Vec3> tmp_uvs;
	std::vector<Vec3> tmp_normals;
	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;


	std::ifstream ObjFile(filePath);
	if (ObjFile.is_open() == false)
	{
		std::cout << filePath << '\n';
		std::cout << "Can't Load .Obj file, please check your filePath\n";
		return;
	}

	std::string line;
	while(!ObjFile.eof())
	{
		std::string cs;
		ObjFile >> cs;
		if(cs == "v")
		{
			Vec3 vertex;
			ObjFile >> vertex.mf_x >> vertex.mf_y >> vertex.mf_z;
			//std::cout << "X: " << vertex.mf_x << " Y: " << vertex.mf_y << " Z: " << vertex.mf_z << '\n';
			tmp_vertices.emplace_back(vertex);
		}

		if(cs == "vt")
		{
			Vec3 uv;
			uv.mf_z = 0;
			ObjFile >> uv.mf_x >> uv.mf_y;
			//std::cout << "UV_X: " << uv.mf_x << " UV_Y: " << uv.mf_y << '\n';
			tmp_uvs.emplace_back(uv);
		}

		if(cs == "vn")
		{
			Vec3 normal;
			ObjFile >> normal.mf_x >> normal.mf_y >> normal.mf_z;
			//std::cout << " NORMAL_X: " << normal.mf_x << " NORMAL_Y: " << normal.mf_y << " NORMAL_Z: " << normal.mf_z << '\n';
			tmp_normals.emplace_back(normal);
		}
		
		if (cs == "f")
		{
			char s = '0';
			int index1, index2, index3;
			index1 = 0;
			index3 = 0;
			std::vector<unsigned int> vertexIndex(polyNb), uvIndex(polyNb), normalIndex(polyNb);
			
			for (int i = 0; i < polyNb; i++)
			{
				vertexIndex[i] = 0;
				//uvIndex[i] = 0;
				normalIndex[i] = 0;
			}

			for(int i = 0; i < polyNb; i++)
			{
				if(slash == 0)
					ObjFile >> index1 >> s >> s >> index3;

				if(slash == 1)
					ObjFile >> index1 >> s >> index3;
				
				if(slash == 2)
					ObjFile >> index1 >> s >> index2 >> s >> index3;

				vertexIndex[i] = index1 - 1;
				//uvIndex[i] = index2 - 1;
				normalIndex[i] = index3 - 1;
			}

			/*std::cout << "INDEX: " << vertexIndex[0] << '/' << uvIndex[0] << '/' << normalIndex[0];
			std::cout << ' ' << vertexIndex[1] << '/' << uvIndex[1] << '/' << normalIndex[1];
			std::cout << ' ' << vertexIndex[2] << '/' << uvIndex[2] << '/' << normalIndex[2] << '\n';*/

			for(int i = 0; i < polyNb; ++i)
			{
				vertexIndices.emplace_back(vertexIndex[i]);
				//uvIndices.emplace_back(uvIndex[i]);
				normalIndices.emplace_back(normalIndex[i]);	
			}

		}
		//std::getline(ObjFile, line);
	}

	for (unsigned int i = 0; i < tmp_vertices.size(); ++i)
	{
		o_vertices.emplace_back(tmp_vertices[i]);
	}

	/*for (unsigned int i = 0; i < tmp_normals.size(); ++i)
	{
		o_normals.emplace_back(tmp_normals[i]);
	}*/

	for (int i = 0; i < vertexIndices.size(); ++i)
	{
		o_indices.emplace_back(vertexIndices[i]);
	}
	std::cout << o_indices.size() << '\n';
	/*for (int i = 0; i < o_indices.size(); i += 3)
	{
		if (reverse)
		{
			std::swap(o_indices[i + 1], o_indices[i + 2]);
		}

		reverse = !reverse;
	}*/

	for (unsigned int i = 0; i < normalIndices.size(); ++i)
	{
		o_normals.emplace_back(tmp_normals[normalIndices[i]]);
	}

	std::cout << "\n OBJ file Loaded ! \n";
}
