#include <../include/LowRenderer/Mesh.h>
#include <../include/Core/OBJLoader.h>
#include <../include/Resources/Texture.h>

using namespace Resources::Texture;
using namespace LowRenderer::Mesh;


Mesh::Mesh(const std::string& p_source, int slash, int polyNb)
{
	Model model;
	OBJParser::OBJLoader::LoadObj(p_source, model.vertices, model.uvs, model.normals, model.VerticesIndices, slash, polyNb);
	meshModel = model;

	Position = Mat4::CreateTranslationMatrix({0,0,0});
	Rotation = Mat4::CreateRotationMatrix(0.0f, 0, 1, 0);
	Scale = Mat4::CreateScaleMatrix(1.0f);

	Transform = Position* Rotation * Scale;

	VBO = Texture::GenerateVBO(meshModel.vertices, meshModel.normals, meshModel.FloatVertices);
	VAO = Texture::GenerateVAO();
	EBO = Texture::GenerateEBO(meshModel.VerticesIndices);
}


Mesh::~Mesh()
{
}

void Mesh::UpdateRotation(const float& angle, bool Xaxis, bool Yaxis, bool Zaxis)
{
	Rotation = Mat4::CreateRotationMatrix(angle, Xaxis, Yaxis, Zaxis);
	Transform = Position * Rotation * Scale;
}

void Mesh::UpdateScale(const float& scale)
{
	Scale = Mat4::CreateScaleMatrix(scale);
	Transform = Position * Rotation * Scale;
}


void Mesh::UpdatePosition(const float Xaxis, float Yaxis, float Zaxis)
{
	Position = Mat4::CreateTranslationMatrix({ Xaxis, Yaxis, Zaxis });
	Transform = Position * Rotation * Scale;
}

Mat4 LowRenderer::Mesh::Mesh::GetTransform()
{
	return Transform;
}

Mat4 LowRenderer::Mesh::Mesh::GetPosition()
{
	return Position;
}

Mat4 LowRenderer::Mesh::Mesh::GetRotation()
{
	return Rotation;
}

Mat4 LowRenderer::Mesh::Mesh::GetScale()
{
	return Scale;
}

