#include <GL/glut.h>
#include <stdlib.h>

static GLuint texName;

/*
 * Texture copied and modifided modified from:
 * https://www.opengl.org/archives/resources/code/samples/mjktips/TexShadowReflectLight.html
 */
static char *circles[] = {
  "................",
  "................",
  "......xxxx......",
  "....xxxxxxxx....",
  "...xxxxxxxxxx...",
  "...xxx....xxx...",
  "..xxx......xxx..",
  "..xxx......xxx..",
  "..xxx......xxx..",
  "..xxx......xxx..",
  "...xxx....xxx...",
  "...xxxxxxxxxx...",
  "....xxxxxxxx....",
  "......xxxx......",
  "................",
  "................",
};

static void initTexture(void)
{
  GLubyte floorTexture[16][16][3];
  GLubyte *loc;
  int s, t;

  /* Setup RGB image for the texture. */
  loc = (GLubyte*) floorTexture;
  for (t = 0; t < 16; t++) {
    for (s = 0; s < 16; s++) {
      if (circles[t][s] == 'x') {
       /* Nice green. */
        loc[0] = 0x1f;
        loc[1] = 0x8f;
        loc[2] = 0x1f;
      } else {
       /* Light gray. */
        loc[0] = 0xaa;
        loc[1] = 0xaa;
        loc[2] = 0xaa;
      }
      loc += 3;
    }
  }

  glGenTextures  (1, &texName);
  glBindTexture  (GL_TEXTURE_2D, texName);
  glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D   (GL_TEXTURE_2D, 0, 3, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, floorTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    initTexture();

    glClearColor(.5f,.5f,.5f,1.f);

}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    static unsigned cnt;

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix ();
   glRotatef(float(cnt%360), 1,0,0);
   glRotatef(45.f, 0,0,1);

   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glNormal3f( 0.0f, 1.0f,  0.0f);
      glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f, 1.0f, -1.0f);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, 1.0f, -1.0f);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, 1.0f,  1.0f);
      glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glNormal3f( 0.0f, -1.0f,  0.0f);
      glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f, -1.0f,  1.0f);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f,  1.0f);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, -1.0f, -1.0f);
      glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glNormal3f( 0.0f,  0.0f, 1.0f);
      glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f,  1.0f, 1.0f);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f,  1.0f, 1.0f);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, -1.0f, 1.0f);
      glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glNormal3f( 0.0f,  0.0f, -1.0f);
      glTexCoord2f(0.0, 0.0); glVertex3f( 1.0f, -1.0f, -1.0f);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, -1.0f);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f,  1.0f, -1.0f);
      glTexCoord2f(1.0, 0.0); glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glNormal3f(-1.0f,  0.0f,  0.0f);
      glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f,  1.0f,  1.0f);
      glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f,  1.0f, -1.0f);
      glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, -1.0f, -1.0f);
      glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glNormal3f(1.0f,  0.0f,  0.0f);
      glTexCoord2f(0.0, 0.0); glVertex3f(1.0f,  1.0f, -1.0f);
      glTexCoord2f(0.0, 1.0); glVertex3f(1.0f,  1.0f,  1.0f);
      glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, -1.0f,  1.0f);
      glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, -1.0f, -1.0f);
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
