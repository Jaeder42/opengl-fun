#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
// Rotate X
double rX = 0;
// Rotate Y
double rY = 0;

const int snowSize = 10000;

struct SnowFlake
{
  float x;
  float y;
  float z;
  float speed;
  int dir;
};

SnowFlake snowFlakes[snowSize] = {};
void display()
{
  // Set Background Color
  glClearColor(0, 0, 0, 1.0);
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();

  // Rotate when user changes rX and rY
  glRotatef(rX, 1.0, 0.0, 0.0);
  glRotatef(rY, 0.0, 1.0, 0.0);

  glBegin(GL_POINTS);
  glColor3f(1, 1, 1);
  int i;
  for (i = 0; i < snowSize; i++)
  {
    glVertex3f(snowFlakes[i].x, snowFlakes[i].y, snowFlakes[i].z);
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(0.5, 0.5, 0.5);
  glVertex3f(0.5, 0.5, -0.5);
  glVertex3f(-0.5, 0.5, -0.5);
  glVertex3f(-0.5, 0.5, 0.5);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(0.5, -0.5, 0.5);
  glVertex3f(0.5, -0.5, -0.5);
  glVertex3f(-0.5, -0.5, -0.5);
  glVertex3f(-0.5, -0.5, 0.5);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(0.5, 0.5, 0.5);
  glVertex3f(0.5, 0.5, -0.5);
  glVertex3f(0.5, -0.5, -0.5);
  glVertex3f(0.5, -0.5, 0.5);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(-0.5, 0.5, 0.5);
  glVertex3f(-0.5, 0.5, -0.5);
  glVertex3f(-0.5, -0.5, -0.5);
  glVertex3f(-0.5, -0.5, 0.5);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

void keyboard(int key, int x, int y)
{

  glutPostRedisplay();
}

void timer(int value)
{
  rX += 0.1;
  rY += 1;

  for (int i = 0; i < snowSize; i++)
  {
    switch (snowFlakes[i].dir)
    {
    // case 0:
    //   snowFlakes[i].x -= snowFlakes[i].speed;
    //   break;
    // case 1:
    //   snowFlakes[i].z -= snowFlakes[i].speed;
    //   break;
    default:
      snowFlakes[i].y -= snowFlakes[i].speed;
    }
    snowFlakes[i].y -= snowFlakes[i].speed;
    if (snowFlakes[i].y < -0.5 || snowFlakes[i].x < -0.5 || snowFlakes[i].z < -0.5)
    {
      snowFlakes[i].y = 0.5; //- ((float)(rand() % 200) * 0.005);
      snowFlakes[i].x = 0.5 - ((float)(rand() % 200) * 0.005);
      snowFlakes[i].z = 0.5 - ((float)(rand() % 200) * 0.005);

      snowFlakes[i].speed = ((float)(rand() % 10 + 20) * 0.0001);
      snowFlakes[i].dir = rand() % 3;
    }
  }

  glutPostRedisplay();
  glutTimerFunc(10, timer, value + 1);
}

void init()
{
  int i = 0;

  for (i = 0; i < snowSize; i++)
  {
    snowFlakes[i].x = 0;
    snowFlakes[i].y = 2;
    snowFlakes[i].z = 0;
    snowFlakes[i].speed = 0.01;
    snowFlakes[i].dir = 0;
  }
}

int main(int argc, char **argv)
{
  // Initialize GLUT and process user parameters
  glutInit(&argc, argv);

  // Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(700, 700);
  glutInitWindowPosition(100, 100);

  // Create window
  glutCreateWindow("Snow render");

  // Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);

  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(keyboard);
  glutTimerFunc(10, timer, 1);

  init();
  // Pass control to GLUT for events
  glutMainLoop();

  return 0;
}