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
float vertices[100] = {0, 0, 0};
double points = 10;
double step = 1 / points;
double width = 700;
double height = 700;

void drawSquare(double x, double y, double z)
{
  glBegin(GL_TRIANGLES);
  // glColor3f(0.3, 0, 0.6);
  glVertex3f(x, y, z);
  glVertex3f(x + step, y, z);
  glVertex3f(x + step, y, z + step);
  glEnd();

  glBegin(GL_TRIANGLES);
  // glColor3f(0.3, 0, 0.3);
  glVertex3f(x, y, z);
  glVertex3f(x, y, z + step);
  glVertex3f(x + step, y, z + step);
  glEnd();
}

void drawOutline()
{
  glBegin(GL_LINE_LOOP);
  glColor3f(0.3, 0, 1);
  glVertex3f(-0.5, 0, -0.5);
  glVertex3f(-0.5, 0, 0.5);
  glVertex3f(0.5, 0, 0.5);
  glVertex3f(0.5, 0, -0.5);
  glEnd();
}

void display()
{
  // Set Background Color
  glClearColor(0.2, 0.2, 0.2, 1.0);
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();

  // Rotate when user changes rX and rY
  glRotatef(rX, 1.0, 0.0, 0.0);
  glRotatef(rY, 0.0, 1.0, 0.0);

  // double x;
  // double z;
  // double start = -0.5;
  // // glBegin(GL_POINTS);
  // for (x = 0; x < points; x++)
  // {

  //   for (z = 0; z < points; z++)
  //   {
  //     glColor3f(x * step / 2, 0, z * step);

  //     drawSquare(start + (x * step), 0, start + (z * step));
  //   }
  // }
  // drawOutline();

  double x;
  double y;
  double start = -0.5;
  int i = 0;
  int vertSize = 3 * (points * points);

  float coords[vertSize] = {};
  float colors[vertSize] = {};
  for (x = 0; x < points; x++)
  {
    for (y = 0; y < points; y++)
    {
      coords[i] = start + (x * step);
      coords[i + 1] = start + (y * step);
      coords[i + 2] = 0;

      colors[i] = x * step;
      colors[i + 2] = y * step;
      colors[i + 1] = 0;
      i += 3;
      // printf("%d\n", vertSize);
    }
  }
  // float coords[12] = {-0.1, -0.1, 0, -0.1, 0.1, 0, 0.1, 0.1, 0, 0.1, -0.1, 0};
  // float colors[vertSize] = {0, 0, 0};

  glVertexPointer(3, GL_FLOAT, 0, coords); // Set data type and location.
  glColorPointer(3, GL_FLOAT, 0, colors);

  glEnableClientState(GL_VERTEX_ARRAY); // Enable use of arrays.
  glEnableClientState(GL_COLOR_ARRAY);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 100); // Use X vertices, starting with vertex 0.

  glFlush();
  glutSwapBuffers();
}

void keyboard(int key, int x, int y)
{
  if (key == GLUT_KEY_RIGHT)
  {
    rY += 5;
  }
  else if (key == GLUT_KEY_LEFT)
  {
    rY -= 5;
  }
  else if (key == GLUT_KEY_DOWN)
  {
    rX -= 5;
  }
  else if (key == GLUT_KEY_UP)
  {
    rX += 5;
  }

  // Request display update
  glutPostRedisplay();
}

void timer(int value)
{
  // rX += 1;
  // rY += 2;
  glutPostRedisplay();
  glutTimerFunc(10, timer, 1);
}
void reshape(int x, int y)
{
  if (y == 0 || x == 0)
    return; // Nothing is visible then, so return
  // Set a new projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Angle of view:40 degrees
  // Near clipping plane distance: 0.5
  // Far clipping plane distance: 20.0
  gluPerspective(0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
  glViewport(0, 0, x, y); // Use the whole window for rendering
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{

  // Initialize GLUT and process user parameters
  glutInit(&argc, argv);

  // Request double buffered true color window with Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(700, 700);
  glutInitWindowPosition(300, 100);

  // Create window
  glutCreateWindow("Test terrain render");

  // Enable Z-buffer depth test
  glEnable(GL_DEPTH_TEST);

  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(keyboard);
  glutTimerFunc(10, timer, 1);
  glutReshapeFunc(reshape);

  // Pass control to GLUT for events
  glutMainLoop();

  return 0;
}