#include <../include/LowRenderer/Camera.h>
#include <Core/Math/Vector/Vec3.h>
#include <Core/Math/Matrix/Mat4.h>

using namespace Math::Vector;
using namespace  Math::Matrix;
using namespace LowRenderer::Camera;

Camera::Camera()
{
	Position = { 0.0f, 0.0f, -20.0f };
	Target = { 0.0f,0.0f,0.0f };
	Up = { 0.0f,-1.0f,0.0f };

	ForwardDir = Position - Target;
	ForwardDir.Normalize();

	RightDir = Vec3::crossProduct(ForwardDir, Up);
	RightDir.Normalize();

	ResultVec = Vec3::crossProduct(ForwardDir, RightDir);

	float Camera[4][4]
	{
		{ RightDir.mf_x, ResultVec.mf_x, ForwardDir.mf_x, Position.mf_x },
		{ RightDir.mf_y, ResultVec.mf_y, ForwardDir.mf_y, Position.mf_y },
		{ RightDir.mf_z, ResultVec.mf_z, ForwardDir.mf_z, Position.mf_z },
		{ 0.0f,0.0f,0.0f,1.0f }
	};

	Transform.SetMatrix(Camera);
}




Camera::~Camera()
{
}


void Camera::UpdatePositionWithKeyBoard(float speed, GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, -speed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, speed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		SetPosition(Vec3(-speed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		SetPosition(Vec3(speed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, 0, speed));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		SetPosition(Vec3(0, 0, -speed));
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Camera::SetPosition(const Vec3& position)
{
	Vec3 addPos = position;
	Position = Position + addPos;

	float Camera[4][4]
	{
		{ RightDir.mf_x, ResultVec.mf_x, ForwardDir.mf_x, Position.mf_x },
	{ RightDir.mf_y, ResultVec.mf_y, ForwardDir.mf_y, Position.mf_y },
	{ RightDir.mf_z, ResultVec.mf_z, ForwardDir.mf_z, Position.mf_z },
	{ 0.0f,0.0f,0.0f,1.0f }
	};

	Transform.SetMatrix(Camera);
}

void Camera::SetTarget(const Vec3& target)
{
	Target = target;

	ForwardDir = Position - Target;
	ForwardDir.Normalize();

	RightDir = Vec3::crossProduct(ForwardDir, Up);
	RightDir.Normalize();

	ResultVec = Vec3::crossProduct(RightDir, ForwardDir);

	float Camera[4][4]
	{
		{ RightDir.mf_x, ResultVec.mf_x, ForwardDir.mf_x, Position.mf_x },
	{ RightDir.mf_y, ResultVec.mf_y, ForwardDir.mf_y, Position.mf_y },
	{ RightDir.mf_z, ResultVec.mf_z, ForwardDir.mf_z, Position.mf_z },
	{ 0.0f,0.0f,0.0f,1.0f }
	};

	Transform.SetMatrix(Camera);
}
