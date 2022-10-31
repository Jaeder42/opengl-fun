
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>

double rX = 0;

double posX = 0;
double posY = 0;
double accY = 0;
double accX = 0;
double acc = 0;

double height = 0.1;
double width = 0.1;

int dirX = 0;
int dirY = 0;

double speed = 0.01;
double drag = 0.0002;
double rotSpeed = 2;

bool left = false;
bool right = false;
bool up = false;
bool down = false;

void drawPlayer()
{

  glPushMatrix();
  glTranslatef(posX, posY, 0);
  glRotatef(rX, 0.0, 0.0, 1.0);
  glTranslatef(-posX, -posY, 0);

  glBegin(GL_LINE_LOOP);
  glColor3f(1, 1, 1);
  glVertex3f(posX - width / 2, posY + height / 2, 0);

  glColor3f(1, 0, 1);
  glVertex3f(posX + width / 2, posY + height / 2, 0);
  glVertex3f(posX + width / 2, posY - height / 2, 0);

  glColor3f(1, 1, 1);
  glVertex3f(posX - width / 2, posY - height / 2, 0);
  glEnd();

  glPopMatrix();
}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.01, 0.01, 0.01, 1.0);

  glLoadIdentity();

  // Draw elements;
  drawPlayer();
  glFlush();
}

void loop(int value)
{
  if (left)
  {
    rX += rotSpeed;
  }

  if (right)
  {
    rX -= rotSpeed;
  }
  if (up)
  {
    dirY = 1;
    acc = speed;
  }

  double rad = rX * M_PI / 180;
  accX = cos(rad) * acc;
  accY = sin(rad) * acc;
  posY += accY;
  posX += accX;

  if (acc > 0)
  {
    acc -= drag;
  }
  else
  {
    acc = 0;
  }
  glutPostRedisplay();
  glutTimerFunc(10, loop, value);
}

void keyboard(unsigned char key, int x, int y)
{
  switch ((char)key)
  {
  case 'a':
    left = true;
    break;
  case 'd':
    right = true;
    break;
  case 'w':
    up = true;
    break;
  case 's':
    down = true;
    break;
  }
}

void keyboardUp(unsigned char key, int x, int y)
{
  switch ((char)key)
  {
  case 'a':
    left = false;
    break;
  case 'd':
    right = false;
    break;
  case 'w':
    up = false;
    break;
  case 's':
    down = false;
    break;
  }
}

int main(int argc, char **argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(80, 80);
  glutInitWindowSize(700, 700);
  glutCreateWindow("Testing");
  glutIgnoreKeyRepeat(1);

  glutDisplayFunc(display);
  // glutSpecialFunc(keyboard);
  glutTimerFunc(10, loop, 1);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);

  glutMainLoop();
}