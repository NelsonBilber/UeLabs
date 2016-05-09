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
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f( 0.0,  1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f( 1.0, -1.0, 0.0);
   glEnd();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
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
