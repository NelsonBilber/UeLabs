#include <GL/glut.h>
#include <stdlib.h>
#include <stddef.h>

void init(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   static struct Vertex {
       GLfloat position[3],
               color[3];
   } attribs[3] = {
       { {   -1.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 } },  // left-bottom,  red
       { {    0.0,  1.0, 0.0 }, { 0.0, 1.0, 0.0 } },  // center-top,   blue
       { {    1.0, -1.0, 0.0 }, { 0.0, 0.0, 1.0 } },  // right-bottom, green
   };

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)attribs + offsetof(Vertex, position));

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)attribs + offsetof(Vertex, color));

   glDrawArrays (GL_TRIANGLES, 0, 3);

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
