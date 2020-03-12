#include <../include/Resources/Texture.h>
#include <cstdio>
#include <vector>
#include <GL/glew.h>
#include <stdio.h>
#include <../include/Core/Math/Vector/Vec3.h>
#include <iostream>

using namespace Resources::Texture;

Texture::Texture()
{
}


Texture::~Texture()
{
}

GLuint Texture::GenerateVBO(const std::vector<Vec3>& vertices, const std::vector<Vec3>& normals, std::vector<GLfloat>& FloatData)
{
	for (int i = 0; i < vertices.size(); ++i)
	{
		FloatData.emplace_back(vertices[i].mf_x);
		FloatData.emplace_back(vertices[i].mf_y);
		FloatData.emplace_back(vertices[i].mf_z);
		FloatData.emplace_back(normals[i].mf_x);
		FloatData.emplace_back(normals[i].mf_y);
		FloatData.emplace_back(normals[i].mf_z);
	}

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, FloatData.size() * sizeof(GLfloat), FloatData.data(), GL_STATIC_DRAW);
	return VBO;
}

GLuint Texture::GenerateVAO()
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	return VAO;


}

GLuint Texture::GenerateEBO(const std::vector<GLuint>& Indices)
{
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), Indices.data(), GL_STATIC_DRAW);

	return EBO;
}

