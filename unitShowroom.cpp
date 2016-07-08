#define GLFW_INCLUDE_GLU

//#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "DrawPrimitives.h"




void resize(GLFWwindow* window, int width, int height) {

	//set screen in a window
	glViewport(0,0, width, height);

	//create perspective projection for a virtual camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, ((GLfloat)width / (GLfloat)height), 0.01, 100);
}

//enemy specs
float enemyHeight = 3;

//turret specs

float turretHeight = 1.5;


void display(GLFWwindow* window) {


	float ratio;
	int width = 640, height = 480;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);

	//clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//select projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(30, ((double)width / (double)height), 0.01, 100);

	//select model matrix
	glMatrixMode(GL_MODELVIEW); //legt fest, welche matrix die aktuelle ist
	glLoadIdentity(); //ersetzt die aktuelle Matrix mit der Identity Matrix (1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1)


	//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_amb[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_dif[] = { 0.8, 0.8, 0.8, 1.0 };
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);


	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	//move local coordinate system
	glTranslatef(0, -3, -17.0);
	glTranslatef(3.0, 0.0, 0.0);

	glPushMatrix();


	const float t = (float)glfwGetTime();
	const float n = 0.6f;
//	glTranslatef(2*sin(n*t * 2), 0, 0.0f);

	glRotatef(t * 20.f, 0.0f, 1.0f, 0.0f);

	//render Turret
	drawTurret(turretHeight);
	
	glPopMatrix();


	glTranslatef(-5.0, 0.0, 0.0);
	glRotatef(t * 40.f, 0.0f, 1.0f, 0.0f);

	drawMannequin(enemyHeight);

	//swap buffers
	glfwSwapBuffers;

}

/*
void keyboardListener(int key)
{
	if (key == GLFW_KEY_UP)
	{
		glTranslatef(0.0, 0.0, 1.0);
		//glutPostRedisplay();
	}
}*/

int main(void) {

	GLFWwindow* window;

	//wenn library init nicht klappt
	if (!glfwInit())
		return -1;


	window = glfwCreateWindow(640, 480, "Snowman", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}



	//make the windows' context current
	glfwMakeContextCurrent(window);

	//initialize opengl
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	//enable and set depth
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);


	//display update timing
	glfwSwapInterval(1);

	//set callback functions for GLFW
	glfwSetFramebufferSizeCallback(window, resize);
	
	

	





	


	//Loop until close
	while (!glfwWindowShouldClose(window))
	{
		//Render caputer image and detect markers here
		display(window);




		//buffer swap
		glfwSwapBuffers(window);

		//poll for process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}