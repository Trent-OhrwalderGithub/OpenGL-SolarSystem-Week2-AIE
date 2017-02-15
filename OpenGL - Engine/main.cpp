#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

int main()
{

	if (glfwInit() == false)
		return -1;

	// Code here

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Game Engine", nullptr, nullptr);

	if (window == nullptr)
		return -1;

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Rest of code goes here.

	int major = ogl_GetMajorVersion();
	int minor = ogl_GetMinorVersion();

	std::cout << "GL Version is " << major << "." << minor << '\n';

	aie::Gizmos::create(64000,64000,64000,64000); // Creates Gizmos

	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), // Creates a matrix position at position 10,10,10 
								 glm::vec3(0, 0, 0),    // and to look at 0,0,0(Screen Centre)
								 glm::vec3(0, 1, 0));	// and 0,1,0 Is the world pos up.
	
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 1280.0f / 720.0f, 0.1f, 1000.0f);	// Setting up a 3D Virtual Camera. 
																										// Field of view of Y. 45 degrees
																										// Aspect ratio of the window(screen)
																										// Near distance for rendering
																										// Far distance for rendering.

	glClearColor(0.25f, 0.25f, 0.25f, 1); // Clears the colour to a base.
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//GL_COLOR_BUFFER_BIT informs OpenGL to wipe the back-buffer colours clean. 
		//GL_DEPTH_BUFFER_BIT informs it to clear the distance to the closest pixels.		

		aie::Gizmos::clear(); // Clears old Gizmos

		aie::Gizmos::addTransform(glm::mat4(1), 3.0f); // Creates a cartesian plane of x,y,z. (R:X,G:Y,B:Z)

		vec4 white(1); vec4 black(0, 0, 0, 1); // White & Black

		for (int i = 0; i < 21; ++i)
		{
			aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
								 glm::vec3(-10 + i, 0, -10),
								 i == 10 ? white : black);
																// Creates the 3D positions in the window.
			aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
								 glm::vec3(-10, 0, -10 + i),
								 i == 10 ? white : black);
		}


		aie::Gizmos::draw(projection * view); // Able to view the transform of Gizmos.
		// Game logic and update code goes here.
		// So does render code.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	aie::Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}