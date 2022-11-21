#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
// Rotate X
double rX = -80;
// Rotate Y
double rY = 0;
double rZ = 90;
const int points = 200;
double step = (1 / points);
double width = 700;
double height = 700;
float terrain[points][points];
double scale = (double)1 / (double)points * 2;

void display()
{
  // Set Background Color
  glClearColor(0.2, 0.2, 0.2, 1.0);
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();
  glTranslatef(0, 0, -0.4);

  // Rotate when user changes rX and rY
  glRotatef(rX, 1.0, 0.0, 0.0);
  glRotatef(rY, 0.0, 1.0, 0.0);
  glRotatef(rZ, 0.0, 0.0, 1.0);

  int x;
  int y;

  double start = -0.5 * scale * points;

  for (y = 0; y < points; y++)
  {
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_TRIANGLE_STRIP);
    for (x = 0; x < points; x++)
    {
      glVertex3f(start + (x * scale), start + y * scale, terrain[x][y]);
      glVertex3f(start + (x)*scale, start + (y + 1) * scale, terrain[x][y + 1]);
    }
    glEnd();
  }
  glFlush();
  glutSwapBuffers();
}

void reshape()
{

  for (int i = 0; i < points; i++)
  {
    for (int j = 0; j < points; j++)
    {
      terrain[i][j] = (rand() % 100) * scale * -0.01;
    }
  }
}
void stepThroughTerrain()
{
  for (int i = 0; i < points - 1; i++)
  {
    float tmp[points];
    for (int x = 0; x < points; x++)
    {
      tmp[x] = terrain[i + 1][x];
    }
    for (int x = 0; x < points; x++)
    {
      terrain[i + 1][x] = terrain[i][x];
    }
    for (int x = 0; x < points; x++)
    {
      terrain[i][x] = tmp[x];
    }
  }
}
void keyboard(int key, int x, int y)
{
  glutPostRedisplay();
}

void timer(int value)
{
  // rX += 1;
  // rY += 1;
  // rZ += 1;
  stepThroughTerrain();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glutPostRedisplay();
  glutTimerFunc(16, timer, 1);
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
  gluPerspective(50, (double)x / (double)y, 0.1, 20.0);
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
  // Use the whole window for rendering

  glutReshapeFunc(reshape);

  // Callback functions
  glutDisplayFunc(display);
  glutSpecialFunc(keyboard);
  glutTimerFunc(10, timer, 1);

  reshape();
  // Pass control to GLUT for events
  glutMainLoop();

  return 0;
}