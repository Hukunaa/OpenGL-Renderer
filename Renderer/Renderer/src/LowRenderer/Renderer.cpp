#include <../include/LowRenderer/Renderer.h>

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Render(Mesh& p_mesh, Shader& p_shader, Camera& p_camera, int polyNb)
{
	static float dist = 0;
	dist += 0.01f;

	glUseProgram(p_shader.shaderProgram);

	glUniform3f(p_shader.ShaderData[1], p_camera.Position.mf_x, p_camera.Position.mf_y, p_camera.Position.mf_z);
	glUniform3f(p_shader.ShaderData[0], -6 + 4 * cos(dist), -4.0f, -4);
	glUniform3f(p_shader.ShaderData[5], p_shader.Color.mf_x, p_shader.Color.mf_y, p_shader.Color.mf_z);
	glUniformMatrix4fv(p_shader.ShaderData[2], 1, GL_FALSE, Mat4::MatrixToShader(p_mesh.GetTransform()));
	glUniformMatrix4fv(p_shader.ShaderData[3], 1, GL_FALSE, Mat4::MatrixToShader(p_camera.Transform));
	glUniformMatrix4fv(p_shader.ShaderData[4], 1, GL_FALSE, Mat4::MatrixToShader(Mat4::CreatePerspectiveMatrix(75.0f, 1600.0f/900.0f, 0.5f, 1000.0f)));

	glBindVertexArray(p_mesh.VAO);

	if(polyNb == 3)
		glDrawElements(GL_TRIANGLES, p_mesh.meshModel.VerticesIndices.size(), GL_UNSIGNED_INT, nullptr);
	if(polyNb == 4)
		glDrawElements(GL_QUADS, p_mesh.meshModel.VerticesIndices.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}
