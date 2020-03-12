#pragma once
#include "Core/Math/Matrix/Mat4.h"
#include <../include/Resources/Model.h>

using namespace Math::Matrix;
using namespace Resources::Model;

namespace LowRenderer::Mesh
{
	class Mesh
	{
	private:
		Mat4 Transform;
		Mat4 Position;
		Mat4 Rotation;
		Mat4 Scale;

	public:
		Mesh(const std::string& p_source, int slash, int polyNb);
		~Mesh();

		Model meshModel;

		GLuint VBO;
		GLuint VAO;
		GLuint EBO;

		void UpdateRotation(const float& angle, bool Xaxis, bool Yaxis, bool Zaxis);
		void UpdateScale(const float& scale);
		void UpdatePosition(float Xaxis, float Yaxis, float Zaxis);

		Mat4 GetTransform();
		Mat4 GetPosition();
		Mat4 GetRotation();
		Mat4 GetScale();
	};
}

