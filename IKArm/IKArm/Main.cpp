#include "../IKArm/Dependencies/glm/glm.hpp"
#include "../IKArm/Dependencies/glm/gtc/matrix_transform.hpp"
#include "../IKArm/Dependencies/glew/glew.h"
#include "../IKArm/Dependencies/glut/glut.h"
#include <math.h>
#include <iostream>
#include <queue>
#include "Arm.h"
#include "TargetPoint.h"      

#define GLFW_KEY_0 48
#define GLFW_KEY_1 49
#define GLFW_KEY_2 50
#define GLFW_KEY_3 51
#define GLFW_KEY_4 52
#define GLFW_KEY_5 53
#define GLFW_KEY_6 54
#define GLFW_KEY_7 55
#define GLFW_KEY_8 56
#define GLFW_KEY_9 57

int w = 700, h = 700;
float minX = -3.0, maxX = 3.0; 
float minY = -3.0, maxY = 3.0;
float minZ = -3.0, maxZ = 11.0;
float targetX = -1.0f;
float targetY = -1.0f;
float targetZ = -1.0f;
Arm* arm;
std::vector<vec3*> grid; 
std::vector<int> gridIndices;
TargetPoint* tp;
std::queue<vec3> interpolatedPoints;


void reshape(int width, int height) 
{
	w = width;
	h = height;
	glViewport(0, 0, w, h);
}

void drawGrid()
{
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < gridIndices.size() - 1; i += 2)
	{
		glBegin(GL_LINES);
		vec3 bottom = *grid[gridIndices[i]];
		vec3 top = *grid[gridIndices[i + 1]];
		glVertex3f(bottom[0], bottom[1], bottom[2]);
		glVertex3f(top[0], top[1], top[2]);
		glEnd();
	}
}

void initialize() 
{
	glEnable(GL_DEPTH_TEST);
	arm = new Arm();
	tp = new TargetPoint();
	vec3* m0 = new vec3(-3.0f, 0.0f, -3.0f); vec3* m1 = new vec3(-3.0f, 0.0f, 3.0f);
	vec3* m2 = new vec3(-2.0f, 0.0f, -3.0f); vec3* m3 = new vec3(-2.0f, 0.0f, 3.0f);
	vec3* m4 = new vec3(-1.0f, 0.0f, -3.0f); vec3* m5 = new vec3(-1.0f, 0.0f, 3.0f);
	vec3* m6 = new vec3(0.0f, 0.0f, -3.0f); vec3* m7 = new vec3(0.0f, 0.0f, 3.0f);
	vec3* m8 = new vec3(1.0f, 0.0f, -3.0f); vec3* m9 = new vec3(1.0f, 0.0f, 3.0f);
	vec3* m10 = new vec3(2.0f, 0.0f, -3.0f); vec3* m11 = new vec3(2.0f, 0.0f, 3.0f);
	vec3* m12 = new vec3(3.0f, 0.0f, -3.0f); vec3* m13 = new vec3(3.0f, 0.0f, 3.0f);
	vec3* m14 = new vec3(-3.0f, 0.0f, -2.0f); vec3* m15 = new vec3(3.0f, 0.0f, -2.0f);
	vec3* m16 = new vec3(-3.0f, 0.0f, -1.0f); vec3* m17 = new vec3(3.0f, 0.0f, -1.0f);
	vec3* m18 = new vec3(-3.0f, 0.0f, 0.0f); vec3* m19 = new vec3(3.0f, 0.0f, 0.0f);
	vec3* m20 = new vec3(-3.0f, 0.0f, 1.0f); vec3* m21 = new vec3(3.0f, 0.0f, 1.0f);
	vec3* m22 = new vec3(-3.0f, 0.0f, 2.0f); vec3* m23 = new vec3(3.0f, 0.0f, 2.0f);
	grid.push_back(m0); grid.push_back(m1); grid.push_back(m2); grid.push_back(m3); grid.push_back(m4); grid.push_back(m5);
	grid.push_back(m6); grid.push_back(m7); grid.push_back(m8); grid.push_back(m9); grid.push_back(m10); grid.push_back(m11);
	grid.push_back(m12); grid.push_back(m13); grid.push_back(m14); grid.push_back(m15); grid.push_back(m16); grid.push_back(m17);
	grid.push_back(m18); grid.push_back(m19); grid.push_back(m20); grid.push_back(m21); grid.push_back(m22); grid.push_back(m23);
	gridIndices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 12, 1, 13 };
}

void display() 
{
	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(minX, maxX, minY, maxY, minZ, maxZ);
	gluLookAt(3, 2, 4, 0, 1, 0, 0, 1, 0);
	arm->drawObject();
	tp->draw();
	drawGrid();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) 
{
	switch (key) 
	{
	case GLFW_KEY_4:
	{
		tp->minusY();
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
		break;
	}
	case GLFW_KEY_2:
	{
		tp->plusZ();
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
		break;
	}
	case GLFW_KEY_6:
	{
		tp->plusY();
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
		break;
	}
	case GLFW_KEY_1:
	{
		tp->minusX();
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
		break;
	}
	case GLFW_KEY_3:
	{
		tp->plusX();
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
		break;
	}
	case GLFW_KEY_5:
	{
		tp->minusZ();
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
		break;
	}
	case GLFW_KEY_7:
	{
		vec3 tipDir = normalize(arm->getTipDirection());
		vec3 temp = normalize(vec3(tipDir[0] - 1.0, tipDir[1] - 1.0, tipDir[2] - 1.0));
		vec3 a = cross(tipDir, temp);
		vec3 b = cross(tipDir, a);
		for (float i = 0; i <= 2 * pi; i += pi / 1000.0f) 
		{
			float x = tp->getPos(0) + (0.75f * cos(i) * a[0]) + (0.75f * sin(i) * b[0]);
			float y = tp->getPos(1) + (0.75f *cos(i) * a[1]) + (0.75f * sin(i) * b[1]);
			float z = tp->getPos(2) + (0.75f * cos(i) * a[2]) + (0.75f * sin(i) * b[2]);
			interpolatedPoints.push(vec3(x, y, z));
		}
		break;
	}
	}
}

void idle() 
{
	if (!interpolatedPoints.empty())
	{
		vec3 temp = interpolatedPoints.front();
		interpolatedPoints.pop();
		tp->set(temp);
		arm->IKToTarget(tp->getPos(0), tp->getPos(1), tp->getPos(2));
		glutPostRedisplay();
	}
}

void printInstructions() 
{
	std::cout << "Numpad Controls:" << std::endl;
	std::cout << "1 = left" << std::endl;
	std::cout << "3 = right" << std::endl;
	std::cout << "2 = forward" << std::endl;
	std::cout << "5 = backward" << std::endl;
	std::cout << "4 = down" << std::endl;
	std::cout << "6 = up" << std::endl;
	std::cout << "7 = follows circular path around current point" << std::endl;
	std::cout << std::endl;
	std::cout << "IKArm follows line on screen - green if point is reachable by arm, red if point is unreachable" << std::endl;
}

int main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("IKArm");
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetString(err) << std::endl;
	}
	printInstructions();
	initialize();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutReshapeWindow(w, h);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
