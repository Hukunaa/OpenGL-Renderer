#pragma once
#include "Core/Math/Matrix/Mat4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Math::Matrix;
using namespace Math::Vector;


namespace LowRenderer::Camera
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		Vec3 Position;
		Vec3 Target;
		Vec3 Up;
		Vec3 RightDir;
		Vec3 ForwardDir;
		Vec3 ResultVec;

		Mat4 Transform;


		void UpdatePositionWithKeyBoard(float speed, GLFWwindow* window);
		void SetPosition(const Vec3& position);
		void SetTarget(const Vec3& target);
	};
}

