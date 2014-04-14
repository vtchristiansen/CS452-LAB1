
#include "initShaders.h"
using namespace std;
int counter=0;

//vertexIDs
GLuint vaoID, vboID;// the buffers that are going to be linked too
//vertices
GLfloat vertexarray[]={0.5f,-0.5f,0.0f,0.0f,0.5f,0.0f,-0.5f,-0.5f,0.0f};// vertices that are drawn x,y,z ...
GLfloat vertexarray2[]={-0.5f,-0.5f,0.0f,-0.5f,0.5f,0.0f,0.5f,0.5f,0.0f,0.5f,-0.5f,0.0f};
GLfloat vertexarray3[]={0.0f,-0.5f,0.0f,-0.5f,0.5f,0.0f,0.5f,0.5f,0.0f};


void init(){
   glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray)+sizeof(vertexarray2)+sizeof(vertexarray3), NULL, GL_STATIC_DRAW);//allocates the memory of the vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0,sizeof(vertexarray), vertexarray);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexarray),sizeof(vertexarray2), vertexarray2);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexarray)+sizeof(vertexarray2),sizeof(vertexarray3), vertexarray3);

 ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
}

void drawscene(){
   glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  switch(counter%3){//easy way to switch throw functions
    case 0:
      glDrawArrays(GL_TRIANGLES,0,3);
      glFlush();
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 1:
      glDrawArrays(GL_QUADS,3,4);
      glFlush();
      glutPostRedisplay();
      break;
    case 2:
      glDrawArrays(GL_POINTS,7,3);
      glFlush();
      glutPostRedisplay();
      break;
  }
}
//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click changes the shape color
    counter++;
    drawscene();
  }
}

int main(int argc, char **argv){
	//Freeglut window and context management	
  glutInit(&argc, argv);
  glutCreateWindow("Shapes");//creates the window with the specified name
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);//specifies the version of opengl
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);//specifies what profile your using


  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);
 	init();
  glutDisplayFunc(drawscene);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
 
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}
