
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>

double rX = 0;

double frame = 10;

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
double rotSpeed = 0.5;

bool left = false;
bool right = false;
bool up = false;
bool down = false;

double goalX = 0;
double goalY = 0;
double goalA = 0;
double angleAccuracy = 5;
double accuracy = 0.01;
double distance = 0;

void drawPlayer()
{

  glPushMatrix();
  glTranslatef(posX, posY, 0);
  glRotatef(rX, 0.0, 0.0, 1.0);
  glTranslatef(-posX, -posY, 0);

  glBegin(GL_POLYGON);
  glColor3f(0.5, 0, 1);
  glVertex3f(posX - width / 2, posY + height / 2, 0);

  glColor3f(0.5, 1, 0.5);
  glVertex3f(posX + width / 2, posY + height / 2, 0);
  glVertex3f(posX + width / 2, posY - height / 2, 0);

  glColor3f(0.5, 0, 1);

  glVertex3f(posX - width / 2, posY - height / 2, 0);
  glEnd();

  glPopMatrix();
}

void drawGoal()
{
  glPushMatrix();
  glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  glVertex3f(goalX - 0.02, goalY - 0.02, 0);
  glColor3f(0, 0, 1);
  glVertex3f(goalX - 0.02, goalY + 0.02, 0);
  glColor3f(0, 1, 0);
  glVertex3f(goalX + 0.02, goalY + 0.02, 0);
  glColor3f(0, 0, 1);
  glVertex3f(goalX + 0.02, goalY - 0.02, 0);

  glEnd();
  glPopMatrix();
}

void drawAngle()
{

  glPushMatrix();

  glBegin(GL_LINES);

  glColor3f(1, 0, 0);
  glVertex3f(posX, posY, 0);
  glVertex3f(goalX, goalY, 0);

  glEnd();

  glPopMatrix();
}
void display()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.1, 0.01, 0.1, 1.0);

  glLoadIdentity();
  drawAngle();

  // Draw elements;
  drawPlayer();
  drawGoal();
  glFlush();
}

void loop(int value)
{
  // So hacky, but it works
  double near = abs(goalX - posX);
  double far = abs(goalY - posY);
  double offset = 0;
  if (posX > goalX)
  {
    near *= -1;
    offset = 180;
  }
  if (posY > goalY)
  {
    far *= -1;
  }

  goalA = atan((far / near)) * (180 / M_PI) + offset;

  distance = sqrt((far * far) + (near * near));
  if (distance > accuracy)
  {
    acc = 0.001;
  }

  double diff = abs(goalA - rX);
  if (diff > 180)
  {
    goalA = rX + 360 - diff;
  }

  if (rX < goalA - 5)
  {
    rX += rotSpeed;
  }
  else if (rX > goalA + 5)
  {
    rX -= rotSpeed;
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
  glutTimerFunc(frame, loop, value);
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

void mouseFunc(int button, int state, int x, int y)
{
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    goalX = ((double)(x - 350) / 350);
    goalY = ((double)(350 - y) / 350);
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
  glutTimerFunc(frame, loop, 1);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutMouseFunc(mouseFunc);

  glutMainLoop();
}