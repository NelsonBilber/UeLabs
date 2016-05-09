#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    GLfloat light_ambient     [] = { 0.0f, 0.0f, 0.0f, 1.0f };  /* default value */
    GLfloat light_diffuse     [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* default value */
    GLfloat light_specular    [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* default value */
    GLfloat light_position    [] = { 1.0f, 1.0f, 1.0f, 0.0f };  /* NOT default value */
    GLfloat lightModel_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  /* default value */
    GLfloat material_specular [] = { 1.0f, 1.0f, 1.0f, 1.0f };  /* NOT default value */
    GLfloat material_emission [] = { 0.0f, 0.0f, 0.0f, 1.0f };  /* default value */

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModel_ambient);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);               /* NOT default value	*/

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(.5f,.5f,.5f,1.f);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static unsigned cnt;

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix ();
   glRotatef(float(cnt%360), 1,0,0);
   glRotatef(45.f, 0,0,1);

   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glNormal3f( 0.0f, 1.0f,  0.0f);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glNormal3f( 0.0f, -1.0f,  0.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glNormal3f( 0.0f,  0.0f, 1.0f);
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glNormal3f( 0.0f,  0.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glNormal3f(-1.0f,  0.0f,  0.0f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glNormal3f(1.0f,  0.0f,  0.0f);
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube

   glPopMatrix ();

   ++cnt;

   glutSwapBuffers();
}

void timeout (int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timeout, 1);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (w <= h)
      glOrtho (-2.f, 2.f, -2.f*h/w, 2.f*h/w, -10.f, 10.f);
   else
      glOrtho (-2.f*w/h, 2.f*w/h, -2.f, 2.f, -10.f, 10.f);
}

void keyboard (unsigned char key, int , int )
{
   switch (key) {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (640, 480);
   glutInitWindowPosition (50, 50);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(1000/60, timeout, 1);
   glutMainLoop();
   return 0;
}
