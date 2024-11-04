#include "Main.h"
#include "Figure.h"
#include "UserInterface.h"
#include <iostream>
#include "../headers/glfw3.h"
using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress;
CUserInterface * userInterface;
vector <CFigure *> figures;
FigureType figureSelected;
float ax1, ay1;
float cax1, cay1, cax2, cay2, cax3, cay3;
int nCurves = 0;
bool fill;

void display()
{
	glClearColor(255.0, 255.0, 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(5);

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->draw();
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_I:
			std::cout << "esto es una prueba \n";	
			break;
		case GLFW_KEY_U:
			figureSelected = NONE;
			//userInterface->hide();
			break;
		case GLFW_KEY_KP_SUBTRACT:
			userInterface->hide();
			break;
		}


	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);


	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if (state == GLFW_PRESS)
	{

		float ax = float(x);
		float ay = gHeight - float(y);
		CFigure *pixel;
		pixel = new CFigure(1);
		pixel->setVertex(0, ax, ay);
		figures.push_back(pixel);
	
	}

}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;

	if (gPress)
	{


		
	}
}

void reshape(GLFWwindow* window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}


void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "ICG - Plantilla", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();
	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();
		
		TwDraw();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();


	}

	destroy();

	return EXIT_SUCCESS;
}