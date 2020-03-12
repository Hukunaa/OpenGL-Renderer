#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <../include/Resources/Shader.h>
#include <../include/Core/Math/Vector/Vec3.h>
#include <../include/Core/OBJLoader.h>
#include <Core/Math/Matrix/Mat4.h>
#include <../include/LowRenderer/Mesh.h>
#include <../include/LowRenderer/Camera.h>
#include <../include/Resources/Texture.h>
#include <../include/Resources/Model.h>
#include <../include/LowRenderer/Renderer.h>

using namespace Math::Vector;
using namespace Math::Matrix;
using namespace Resources::Model::OBJParser;
using namespace Resources::Texture;
using namespace Resources::Model;

int main()
{
	//---------------------------------------------Creating Window and Initializing Glew/GLFW---------------------------------------------
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1600, 900, "Emini Renderer", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cerr << "Error initGLEW\n";

	std::cout << glGetString(GL_VERSION) << "\n";

	//---------------------------------------------Creating GameObjects---------------------------------------------
	Camera mainCamera;

	Mesh Tank("res/OBJ/TigerTank.obj", 2, 3);
	Mesh Table("res/OBJ/BarrocTable.obj", 0, 4);
	Mesh MiniTable("res/OBJ/BarrocMiniTable.obj", 2, 4);

	/*
	
	If you want to test:
	> Mesh(path, Mode, PolygonMode)

		-----Mode-----
		if OBJ index format is:

			vertex//normals -> put '0'
			vertex/normals -> put '1'
			vertex/uv/normals -> put '2'

		-----PolygonMode-----
		if OBJ PolygonMode is:

			Triangles : put '3';
			Quads : put '4';

	*/

	//---------------------------------------------Create Shader---------------------------------------------
	Shader BasicShader;
	
	//Only Setting Available is LightColor for now;
	BasicShader.Color = { 1.0, 165.0f / 255.0f, 0.0f };
	BasicShader.LoadRainBowShader();
	BasicShader.SetupRainBowShader();


	//---------------------------------------------Setup DrawMode---------------------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//---------------------------------------------Main Loop---------------------------------------------
	while (!glfwWindowShouldClose(window))
	{

		static float distance;
		distance += 0.01f;

		//Doing Modifications on GameObjects Transform
		Tank.UpdatePosition(0, -8, -6);
		Tank.UpdateRotation(distance * 60, 0, 1, 0);
		Tank.UpdateScale(1.0f);
		
		Table.UpdatePosition(6, -8, 0);
		Table.UpdateRotation(distance * 60, 0, 1, 0);
		Table.UpdateScale(0.5f);
		
		MiniTable.UpdatePosition(-6, -8, 0);
		MiniTable.UpdateScale(0.03f);



//---------------------------------------------Rendering Section---------------------------------------------

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1);

		//Activating Camera Controls and DrawMode selection
		mainCamera.UpdatePositionWithKeyBoard(0.1f, window);

		//Renderering each GameObject
		Renderer::Render(Tank, BasicShader, mainCamera, 3);
		Renderer::Render(Table, BasicShader, mainCamera, 4);
		Renderer::Render(MiniTable, BasicShader, mainCamera, 4);

		/*
		If you want to test:
			Renderer::Render(Mesh, Shader, Camera, PolygonMode);

			Mesh is your mesh instantiated
			Shader is your Shader instantiated
			Camera is your MainCamera, only one camera can exist in the scene

			!!! if you select the wrong Polygon DrawMode, your mesh can appears as messed up !!!
			PolygonMode is the mode of your Mesh (Triangles or Quads -> '3' or '4');
		
		*/

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}