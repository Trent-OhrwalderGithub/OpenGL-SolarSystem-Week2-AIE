#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define GLM_SWIZZLE
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>


using glm::vec3;
using glm::vec4;
using glm::mat4;


glm::mat4 sunTransform(1);	// Creating the transform for sun/planet
glm::mat4 planetMercury(1);
glm::mat4 planetVenus(1);
glm::mat4 planetEarth(1);
glm::mat4 planetMars(1);
glm::mat4 planetJupiter(1);
glm::mat4 planetSaturn(1);
glm::mat4 planetUranus(1);
glm::mat4 planetNeptune(1);

void SetupSolaSystem();		// Forward declearing functions below main()
void RenderSolarSystem();


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

	glm::mat4 view = glm::lookAt(glm::vec3(3, 3, 3), // Creates a matrix position at position 10,10,10 
								 glm::vec3(0, 0, 0),    // and to look at 0,0,0(Screen Centre)
								 glm::vec3(0, 1, 0));	// and 0,1,0 Is the world pos up.
	
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 1280.0f / 720.0f, 0.1f, 1000.0f);	// Setting up a 3D Virtual Camera. 
																										// Field of view of Y. 45 degrees
																										// Aspect ratio of the window(screen)
																										// Near distance for rendering
																										// Far distance for rendering.

	glClearColor(0.25f, 0.25f, 0.25f, 1); // Clears the colour to a base.
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	SetupSolaSystem(); // Start up solaSystem by rendering the code.

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) // Main Game Loop
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
		// Adds a ring around to map planets.

		aie::Gizmos::addRing(sunTransform[3].xyz(), 1.16f, 1.18f, 32, white);	//Mercury
		aie::Gizmos::addRing(sunTransform[3].xyz(), 2.16f, 2.18f, 32, white);	//Venus	
		aie::Gizmos::addRing(sunTransform[3].xyz(), 3.0f, 3.02f, 32, white);	//Earth
		aie::Gizmos::addRing(sunTransform[3].xyz(), 4.56f, 4.58f, 32, white);	//Mars
		aie::Gizmos::addRing(sunTransform[3].xyz(), 15.56f, 15.58f, 32, white);	//Jupiter
		aie::Gizmos::addRing(sunTransform[3].xyz(), 28.58f, 28.60f, 32, white);	//Saturn
		aie::Gizmos::addRing(sunTransform[3].xyz(), 57.42f, 57.44f, 32, white);	//Uranus
		aie::Gizmos::addRing(sunTransform[3].xyz(), 90.8f, 90.9f, 32, white);	//Neptune


		// SolarSystem Code for rendering within the screen.
		RenderSolarSystem();


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

void SetupSolaSystem()
{
	// x, y, z of the planet transformation. 
	planetMercury[3]	= glm::vec4(1.16f, 0, 0, 1);	// 58/50
	planetVenus[3]		= glm::vec4(2.16, 0, 0, 1);		// 108/50
	planetEarth[3]		= glm::vec4(3.0f, 0, 0, 1);		// 150/50
	planetMars[3]		= glm::vec4(4.56f, 0, 0, 1);	// 228/50
	planetJupiter[3]	= glm::vec4(15.56f, 0, 0, 1);	// 778/50
	planetSaturn[3]		= glm::vec4(28.58f, 0, 0, 1);	// 1429/50
	planetUranus[3]		= glm::vec4(57.42f, 0, 0, 1);	// 2871/50
	planetNeptune[3]	= glm::vec4(90.8f, 0, 0, 1);	// 4504/50

}

void RenderSolarSystem()
{
	glm::mat4 rotation = glm::rotate(0.00004894f, glm::vec3(0, 1, 0));														// Setting initial rotation.

	// Sun - / 500000
	sunTransform = sunTransform * rotation;																				// Setting the sun to be the centre and rotate around itself.
	aie::Gizmos::addSphere(glm::vec3(0), 1.391, 32, 32, glm::vec4(0.7f, 0.7f, 0.0f, 1), &sunTransform);			// Drawing sun to screen.

	// Mercury - / 500000
	rotation = glm::rotate(0.176f, glm::vec3(0, 1, 0));																	// Resetting Rotation matrix.
	planetMercury = rotation * planetMercury;																			// Rotate planet around sun. Rotate * Planet.
	aie::Gizmos::addSphere(glm::vec3(0), 0.00488f, 32, 32, glm::vec4(0.25f, 0.25f, 0.25f, 1), &planetMercury);	// Drawing planet1 to screen.

	// Venus - / 500000
	rotation = glm::rotate(0.0004494f, glm::vec3(0, 1, 0));
	planetVenus = rotation * planetVenus;
	aie::Gizmos::addSphere(glm::vec3(0), 0.012104f, 32, 32, glm::vec4(0.0f, 0.5f, 0.0f, 1), &planetVenus);

	// Earth - / 500000
	rotation = glm::rotate(0.0007304f, glm::vec3(0, 1, 0));
	planetEarth = rotation * planetEarth;
	aie::Gizmos::addSphere(glm::vec3(0), 0.012742f, 32, 32, glm::vec4(0.0f, glm::pi<float>(), 0.0f, 1), &planetEarth);

	// Mars - / 500000
	rotation = glm::rotate(0.001374f, glm::vec3(0, 1, 0));
	planetMars = rotation * planetMars;
	aie::Gizmos::addSphere(glm::vec3(0), 0.00678f, 32, 32, glm::vec4(0.0f, 0.5f, 0.0f, 1), &planetMars);

	// Jupiter - / 500000
	rotation = glm::rotate(0.008664f, glm::vec3(0, 1, 0));
	planetJupiter = rotation * planetJupiter;
	aie::Gizmos::addSphere(glm::vec3(0), 0.139822f, 32, 32, glm::vec4(0.0f, 0.5f, 0.0f, 1), &planetJupiter);

	// Saturn - / 500000
	rotation = glm::rotate(0.02152f, glm::vec3(0, 1, 0));
	planetSaturn = rotation * planetSaturn;
	aie::Gizmos::addSphere(glm::vec3(0), 0.116464f, 32, 32, glm::vec4(0.0f, 0.5f, 0.0f, 1), &planetSaturn);

	// Uranus - / 500000
	rotation = glm::rotate(0.1204f, glm::vec3(0, 1, 0));
	planetUranus = rotation * planetUranus;
	aie::Gizmos::addSphere(glm::vec3(0), 0.050724f, 32, 32, glm::vec4(0.0f, 0.5f, 0.0f, 1), &planetUranus);

	// Neptune - / 500000
	rotation = glm::rotate(0.1812f, glm::vec3(0, 1, 0));
	planetNeptune = rotation * planetNeptune;
	aie::Gizmos::addSphere(glm::vec3(0), 0.049244f, 32, 32, glm::vec4(0.0f, 0.5f, 0.0f, 1), &planetNeptune);

}