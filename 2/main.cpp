/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"
using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };
GLfloat xRotated, yRotated, zRotated;
GLdouble size=1;
//My project
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
using namespace std;
#define WIRE 0

GLuint  texture[1];


typedef struct {
	float x;
	float y;
	float z;
} Point;

class xPoint3D
{
public:
	float x, y, z, w;
	xPoint3D() { x = y = z = 0; w = 1; };
};

typedef struct {
	unsigned int ip[3];
} Face;

class TPoint {
public:
	float ip[3];
};

int pnum;
int fnum;
xPoint3D newpt;
xPoint3D pt;
TPoint tpoint;
Point* mpoint = NULL;
Face* mface = NULL;
GLfloat angle = 0; /* in degrees */
int moving;
float scalefactor = 1.0;
int scaling = 0;
float varx = 0.2;
float vary = 0.2;
float varz = 0.2;
float ground = 0.0;
float movex = 0.0;
float movey = 0.0;
float movez = 0.0;
float rotatex = 0.0;
float rotatey = 0.0;
float rotatez = 0.0;
float animatex = 0.0;
float fRotAngle = 0.0;
float mscale = 1.0;
string fname = "./apple.dat";
GLfloat T = 0;
GLfloat xRotAngle = 0;
GLfloat yRotAngle = 0;
GLfloat xLocation = 0, yLocation = 0, zLocation = 0;

int trans;
int beginx, beginy;
GLint TexFilter = GL_LINEAR;
void glTexImage2D();


void DrawModel(float varx, float vary, float varz, float movex,float movey, float movez);
//start Project
void problem1() {
    for (int i = 0; i < 10; i++){
      glMatrixMode(GL_MODELVIEW);
        // clear the identity matrix.
      glLoadIdentity();
      // traslate the draw by z = -3.0
      // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
      glPushMatrix();
        glTranslated(0.5*cos(0.628*i),0.5*sin(0.628*i),-3);
        glColor3f(0.8, 0.2, 0.1); 
        glRotatef(xRotated,1.0,0.0,0.0);
        // rotation about Y axis
        glRotatef(yRotated,0.0,1.0,0.0);
        // rotation about Z axis
        glRotatef(36*i,0.0,0.0,1.0);
        // scaling transfomation 
        glScalef(1.0,1.0,1.0);
      // built-in (freeglut library) function , draw you a Teapot.
      glutSolidTeapot(0.1);
    }
    glPushMatrix();
        glTranslated(0,0,-3);
        glRotated(0,0,0,1);
        glLoadIdentity();
        gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

        glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

        glRotatef(yRot,0,1,0);
}

void problem2() {
  for(int i = 0; i < 15; i++){
    glLoadIdentity();
    glTranslatef(-0.8 + i * 0.1, 0 ,-3);
    glColor3f(0.8, 0.2, 0.1); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(1.0,1.0,1.0);
    glutSolidCube(0.1);
    for(int j = 0; j < i+1; j++){
      for (float x = -2; x < 3; x++){
        for (float z = -2; z < 3; z++){
          glLoadIdentity();
          glTranslatef(-0.8 + i * 0.1 + x * 0.02, 0.05+j*0.01 ,-3 + z * 0.02);
          glColor3f(0.8, 0.2, 0.1); 
          glRotatef(xRotated,1.0,0.0,0.0);
          glRotatef(yRotated,0.0,1.0,0.0);
          glRotatef(zRotated,0.0,0.0,1.0);
          glScalef(1.0,1.0,1.0);
          glutSolidCube(0.02);
        }
      }
    }
  }
    glPushMatrix();
      glTranslated(-0.8,0,-3);
      glLoadIdentity();
      gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

      glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

      glRotatef(yRot,0,1,0);
}

void problem3() {
    glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < 6; i++){
      for( float j = -0.5 * i/2; j <= 0.5 * i/2; j= j + 0.5){
        glLoadIdentity();
        glPushMatrix();
          glTranslatef(j, 0.6 - i * 0.3,-3);
          glColor3f(0.8, 0.2, 0.1); 
          glRotatef(xRotated,1.0,0.0,0.0);
          glRotatef(yRotated,0.0,1.0,0.0);
          glRotatef(zRotated,0.0,0.0,1.0);
          glScalef(1.0,1.0,1.0);
        glutSolidTeapot(0.1);
      }
      
    }
     glPushMatrix();
      glTranslated(0,0,-3);
      glLoadIdentity();
      gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

      glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

      glRotatef(yRot,0,1,0); 
}

void problem4() {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);
  int i;
  glShadeModel(GL_SMOOTH);
  glNewList(1, GL_COMPILE);
  glPushMatrix();
  gluLookAt(400.0, 400.0, 400.0, // eye poisition
		0.0, 0.0, 0.0, // center is at (0,0,0)
		0.0, 1.0, 0.0); // up is in positive Y direction
  glTranslatef(0, -100, 0);
  glRotatef(xRotAngle, 0.0, 1.0, 0.0); glRotatef(yRotAngle, 1.0, 0.0, 0.0);
  glScalef(0.7, 0.7, 0.7);
  DrawModel(varx, vary, varz, movex, movey, movez);
  glEndList();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT |
    GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glCallList(1);
  glutSwapBuffers();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}
//problem 4
void ReadModel()
{
	FILE* f1; char s[81]; int i;
	if (mpoint != NULL) delete mpoint;
	if (mface != NULL) delete mface;
	if ((f1 = fopen(fname.c_str(), "rt")) == NULL) { printf("No file\n"); exit(0); }
	fscanf(f1, "%s", s); printf("%s", s); fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%d", &pnum); printf("%d\n", pnum);
	mpoint = new Point[pnum];
	for (i = 0; i < pnum; i++) {
		fscanf(f1, "%f", &mpoint[i].x); fscanf(f1, "%f", &mpoint[i].y); fscanf(f1, "%f", &mpoint[i].z);
		printf("%f %f %f\n", mpoint[i].x, mpoint[i].y, mpoint[i].z);
	}
	fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%s", s); printf("%s", s);
	fscanf(f1, "%d", &fnum); printf("%d\n", fnum);
	mface = new Face[fnum];
	for (i = 0; i < fnum; i++) {
		fscanf(f1, "%d", &mface[i].ip[0]); fscanf(f1, "%d", &mface[i].ip[1]); fscanf(f1, "%d", &mface[i].ip[2]);
		printf("%d %d %d\n", mface[i].ip[0], mface[i].ip[1], mface[i].ip[2]);
	}
	fscanf(f1, "%s", s); printf("%s", s); fscanf(f1, "%s", s); printf("%s", s); fscanf(f1, "%f", s); printf("%f\n", s);
	fscanf(f1, "%f", &ground); printf("%f\n", ground);
	fclose(f1);
}
//Calculate Normal vector
Point cnormal(Point a, Point b, Point c) {
	Point p, q, r;
	double val;
	p.x = a.x - b.x; p.y = a.y - b.y; p.z = a.z - b.z;
	q.x = c.x - b.x; q.y = c.y - b.y; q.z = c.z - b.z;
	r.x = p.y * q.z - p.z * q.y;
	r.y = p.z * q.x - p.x * q.z;
	r.z = p.x * q.y - p.y * q.x;
	val = sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
	r.x = r.x / val; r.y = r.y / val; r.z = r.z / val;
	return r;
}

GLint EnvMode = GL_REPLACE;
void DrawModel(float varx, float vary, float varz, float movex, float movey, float movez) {
	int i;
	glPushMatrix();
	glRotatef(rotatex, 0.0, 0.0, 1.0);
	glRotatef(rotatey + xRotAngle, 0.0, 1.0, 0.0);
	glRotatef(rotatez + yRotAngle, 1.0, 0.0, 0.0);
	glScalef(1, 1, 1);
	glColor3f(varx, vary, varz);
	for (i = 0; i < fnum; i++) {
		Point norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]], mpoint[mface[i].ip[0]]);
		glBegin(GL_TRIANGLES);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[0]].x , mpoint[mface[i].ip[0]].y, mpoint[mface[i].ip[0]].z);
		glNormal3f(norm.x, norm.y, norm.z);
    glVertex3f(mpoint[mface[i].ip[1]].x , mpoint[mface[i].ip[1]].y, mpoint[mface[i].ip[1]].z);
		glNormal3f(norm.x, norm.y, norm.z);
    glVertex3f(mpoint[mface[i].ip[2]].x , mpoint[mface[i].ip[2]].y, mpoint[mface[i].ip[2]].z);
		glNormal3f(norm.x, norm.y, norm.z);
		glEnd();
	}
	glPopMatrix();

}

void GLSetupRC(void)
{
	glEnable(GL_DEPTH_TEST);
	/* Setup the view and projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, // field of view in degree
		1.0, // aspect ratio
		1.0, // Z near
		2000.0); // Z far
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(600.0, 600.0, 600.0, // eye poisition
		0.0, 0.0, 0.0, // center is at (0,0,0)
		0.0, 1.0, 0.); // up is in positive Y direction
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
  ReadModel();
  
	glutMainLoop();

	return 0;
}
