#include "Viewer.h"

#include <GL/freeglut.h>
void displayFunc(int w,int h)
{
	if(w==0){
		w=1;
	}
	float  ratio=(float)h/w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
glFrustrum(-1,1,-ratio,ratio,1,100);
	glRotatef(90,0,0,1);
}
void init_Viewer(gpointer* data)
{
//	gdk_threads_leave();
	printf("THREAD!\n");
//	int argc=1;
//	char** argv={"program"};
//	glutInit(&argc,argv);
	printf("INIT!\n");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(300,300);
glutCreateWindow("VIEWER");
	glEnable(GL_DEPTH_TEST);
/*	glutMainLoop();*/
int i;
	for(i=0;i<1000000;i++){
		printf("%i\n",(int)sqrt(i));
	}
glutMainLoop();
}
