#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <Windows.h>

#include "MyForm.h"
#include "ClothSimulator.h"
#include "OBJLoader.h"
#include "glut/glut.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 576

OBJLoader* obj1;
ClothSimulator* clothSimulation;
int checkBox = 0;
char* filenameDestinationChar;

void SetupLight()
{
	glEnable(GL_LIGHTING);

	GLfloat light0Ambient[] = { 1.0f, 1.0f, 1.0f , 1.0f };
	GLfloat light0Diffuse[] = { 1.0f , 1.0f , 1.0f , 1.0f };
	GLfloat light0Specular[] = { 1.0f , 1.0f , 1.0f , 1.0f };
	//Light Source from the window
	GLfloat light0_pos[] = { 0.0f, 10.0f,0.0f, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,200.0f);
	glEnable(GL_LIGHT0);

}


void DrawFloor()
{
	//draw floor
	glColor3f(0.2f, 0.2f, 0.2f);
	for (int i = -50; i < 50; i = i + 2)
	{
		for (int j = -50; j < 50; j = j + 2)
		{
			glPushMatrix();
			glTranslatef((float)i, 0.0f, (float)j);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glBegin(GL_QUADS);
			glVertex3f(-2.0f, 0.0f, -2.0f);
			glVertex3f(2.0f, 0.0f, -2.0f);
			glVertex3f(2.0f, 0.0f, 2.0f);
			glVertex3f(-2.0f, 0.0f, 2.0f);
			glEnd();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glPopMatrix();

		}
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glOrtho(-4, 4, -0.5, 4, -10.0f, 10.0f);
	SetupLight();
	gluLookAt(0.0f, 0.3f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

	
	
	DrawFloor();

	if (checkBox == 1)
	{
		if (clothSimulation->cloth->IsLoaded() == true)
		{
			clothSimulation->SimulateStep();
			clothSimulation->cloth->DrawObject();
		}
	}
	else if (checkBox == 2)
	{
		

		if (clothSimulation->cloth->IsLoaded() == true)
		{
			clothSimulation->SimulateStep();
			clothSimulation->cloth->DrawObject();
		}
		glColor3f(0.5f, 0.5f, 0.5f);
		//glm::vec3(0.0f, 0.0f, 0.0f), 0.5f
		glutSolidSphere(0.5f, 16, 16);
	}
	else if (checkBox == 3)
	{

		if (clothSimulation->cloth->IsLoaded() == true)
		{
			clothSimulation->SimulateStepFixedCorners();
			clothSimulation->cloth->DrawObject();
		}
	}
	else if (checkBox == 4)
	{

		if (clothSimulation->cloth->IsLoaded() == true)
		{
			clothSimulation->SimulateStepFixedCorners();
			clothSimulation->cloth->DrawObject();
		}
	}
	else if (checkBox == 0)
	{

		if (obj1->IsLoaded() == true)
		{
			obj1->DrawObject();
		}
	}
	
	//!!!!!!!!!!!!!!!!!!!!!!!!
	//COMMENT THIS IF TO IMPROVE PERFORMANCE
	//THIS SAVES EACH FRAME TO THE .OBJ FILE
	// COMMENT LINES 144 - 149 TO IMPROVE PERFORMANCE
	/*if (clothSimulation->cloth->IsLoaded() == true &&
		filenameDestinationChar != "")
	{
		clothSimulation->cloth->SaveToFile(filenameDestinationChar);
	}*/
	
	glPopMatrix();
	
	glFlush();

}

void idle()
{
	//renderer does nothing outside of timer intervals
}

void FrameLimit(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 120, FrameLimit, 0);
}

void SetupRepeatingFrame()
{
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutTimerFunc(1000 / 120, FrameLimit, 0);
}

void resize(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-newWidth / 2, newWidth / 2, -newHeight / 2, newHeight / 2, -1, 1);
	double aspectRatio = (double)newWidth / (double)newHeight;
	if (aspectRatio > 1.0)
	{
		glOrtho(0, 4, 0, 4, -1, 1);
	}
	else
	{
		glOrtho(0, 4, 0, 4, -1, 1);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw();
}
[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	animationCWK2::MyForm mainForm;
	Application::Run(% mainForm);

	char* myargv[1];
	int myargc = 1;
	myargv[0] = strdup("animationCWK2");

	std::ofstream testOutput;
	testOutput.open("./objs/testOutput.txt");

	if (!testOutput)
	{
		exit(553);
	}

	testOutput << " This file is meant to write output messages to.\n";

	//Getting filenames from Windows form
	String^ filenameSource = mainForm.GetSourceFilePath();
	String^ filenameDestination = mainForm.GetDestinationFilePath();

	//converting from .Net String^ to char*
	char* filenameSourceChar = (char*)(void*)Marshal::StringToHGlobalAnsi(filenameSource);
	filenameDestinationChar = (char*)(void*)Marshal::StringToHGlobalAnsi(filenameDestination);

	float mass, structural, shear, flex, startPos;
	mass = 1.0f;
	structural = 10.0f;
	shear = 10.0f;
	flex = 10.0f;
	glm::vec3 windForce;
	
	if (mainForm.GetSimulation1CheckState() == true)
	{
		windForce = glm::vec3(0.0f, 0.0f, 0.0f);
		startPos = 3.0f;
		clothSimulation = new ClothSimulator(filenameSourceChar, startPos, glm::vec3(0.0f, 0.0f ,0.0f), 0.0f, windForce);
		checkBox = 1;
	}
	else if (mainForm.GetSimulation2CheckState() == true)
	{
		windForce = glm::vec3(0.0f, 0.0f, 0.0f);
		startPos = 3.0f;
		clothSimulation = new ClothSimulator(filenameSourceChar, startPos, glm::vec3(0.0f, 0.0f, 0.0f), 0.5f, windForce);
		checkBox = 2;
	}
	else if (mainForm.GetSimulation3CheckState() == true)
	{
		windForce = glm::vec3(0.0f, 0.0f, 0.0f);
		startPos = 4.0f;
		clothSimulation = new ClothSimulator(filenameSourceChar, startPos, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, windForce);
		checkBox = 3;
	}
	else if (mainForm.GetSimulation4CheckState() == true)
	{
		windForce = glm::vec3(-2.0f, 0.0f, 0.0f);
		startPos = 4.0f;
		clothSimulation = new ClothSimulator(filenameSourceChar, startPos, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, windForce);
		checkBox = 4;
	}
	else if (mainForm.GetSimulation1CheckState() == false
		&& mainForm.GetSimulation2CheckState() == false
		&& mainForm.GetSimulation3CheckState() == false
		&& mainForm.GetSimulation4CheckState() == false)
	{
		obj1 = new OBJLoader(filenameSourceChar);
		obj1->Load();
		//obj1->addTexture("./textures/clothTexture.jpg");
		obj1->SaveToFile(filenameDestinationChar);
		checkBox = 0;
	}
	

	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Cloth");
	
	SetupRepeatingFrame();
	//glutReshapeFunc(resize);

	glutMainLoop();

	testOutput.close();

}