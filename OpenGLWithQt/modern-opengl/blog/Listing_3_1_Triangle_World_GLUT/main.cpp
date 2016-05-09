#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f( 0.0,  2.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f( 2.0, -2.0, 0.0);
   glEnd();
   glutSwapBuffers();
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

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   if (w <= h)
      glScalef(1, float(h)/w, 1);
   else
      glScalef(float(w)/h, 1, 1);
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
   glutMainLoop();
   return 0;
}
