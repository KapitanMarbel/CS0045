#define GLEW_STATIC
#define BUFFER_OFFSET(i) ((void*)(i))
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

using namespace std;

int texImageWidth;
int texImageHeight;
int window;
static GLuint texName;				//texture name
int anglex= 0, angley = 0, anglez = 0;		//rotation angles


void init(void)
{
   float light_ambient[4] = { 0.1, 0.1, 0.1, 1.0 }; 	// r, g, b, a
   float light_diffuse[4] = { 1.0, 1.0, 0.9, 1.0 }; 	// r, g, b, a
   //directional used
   float light_position[4] = { 1.0, 1.0, 1.0 , 0.0 }; 	// x, y, z, w 
    
   glClearColor (0, 0, 0, 0.0);				//black
   glShadeModel(GL_SMOOTH);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glEnable(GL_LIGHT0);

	
  //Generate Texture
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load("donut.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, 
	GL_UNSIGNED_BYTE, data);
  }

  else
  {
	cout << "Failed to load texture" << std::endl;
	exit(0);
  }
  
  stbi_image_free(data);

    
   //automatic texture coordinates generation
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_2D);
   
}


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   glPushMatrix(); 
   glRotatef( anglex, 1.0, 0.0, 0.0);		//rotate along x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);		//rotate along y-axis	
   glRotatef( anglez, 0.0, 0.0, 1.0);		//rotate along z-axis

   glutSolidTorus(1.0, 2, 30,30);
   glPopMatrix();
   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 'x':
      anglex = ( anglex + 3 ) % 360;
      break;
    case 'X':
      anglex = ( anglex - 3 ) % 360;
      break;
    case 'y':
      angley = ( angley + 3 ) % 360;
      break;
    case 'Y':
      angley = ( angley - 3 ) % 360;
      break;
    case 'z':
      anglez = ( anglez + 3 ) % 360;
      break;
    case 'Z':
      anglez = ( anglez - 3 ) % 360;
      break;
    case 'r':
      anglex = angley = anglez = 0;
      break;
    case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
  glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
            4.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt ( 5, 0, 0, 0, 0, 0, 0, 0, 1 );
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   window = glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
