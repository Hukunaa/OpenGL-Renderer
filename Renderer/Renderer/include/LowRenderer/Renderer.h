#pragma once

#include <../include/LowRenderer/Mesh.h>
#include <../include/Resources/Shader.h>
#include <../include/LowRenderer/Camera.h>

using namespace Resources::Shader;
using namespace LowRenderer::Camera;
using namespace LowRenderer::Mesh;

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void Render(Mesh& p_mesh, Shader& p_shader, Camera& p_camera, int polyNb);
};

