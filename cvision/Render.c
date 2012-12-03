
#include "UIFunc.h"
#include <GL/freeglut.h>

void renderVertex(int index,float size,float mult)
{
	float height=grid.map.vertices[index].voltage*mult;
	int y=index/(grid.width+1);
	int x=index%(grid.width+1);
		glNormal3f(0,0,1);
glBegin(GL_QUADS);
				glVertex3f(x-size,y-size,height);
				glVertex3f(x-size,y+size,height);
				glVertex3f(x+size,y+size,height);
				glVertex3f(x+size,y-size,height);
				glNormal3f(1,0,0);
				glVertex3f(x+size,y-size,height);
				glVertex3f(x+size,y+size,height);
				glVertex3f(x+size,y+size,0);
				glVertex3f(x+size,y-size,0);
				glNormal3f(-1,0,0);
				glVertex3f(x-size,y-size,height);
				glVertex3f(x-size,y+size,height);
				glVertex3f(x-size,y+size,0);
				glVertex3f(x-size,y-size,0);
				glNormal3f(0,1,0);
				glVertex3f(x-size,y+size,height);
				glVertex3f(x+size,y+size,height);
				glVertex3f(x+size,y+size,0);
				glVertex3f(x-size,y+size,0);
				glNormal3f(0,-1,0);
				glVertex3f(x-size,y-size,height);
				glVertex3f(x+size,y-size,height);
				glVertex3f(x+size,y-size,0);
				glVertex3f(x-size,y-size,0);
glEnd();

}
void renderComponent(int index,float size,float mult)
{
	Component* c=grid.map.components+index;
	int iA,iB,i;
	float x1,y1,z1,x2,y2,z2;
	for(i=0;i<grid.map.vcount;i++){
		if(grid.map.vertices[i].id==c->A){
	y1=i/(grid.width+1);
	x1=i%(grid.width+1);
z1=grid.map.vertices[i].voltage*mult;
iA=i;
	}
		if(grid.map.vertices[i].id==c->B){
	y2=i/(grid.width+1);
	x2=i%(grid.width+1);
z2=grid.map.vertices[i].voltage*mult;
iB=i;
	}
	}
float ang=atan2(y2-y1,x2-x1);
	float sca=size*cos(ang);
	float ssa=size*sin(ang);
	glBegin(GL_QUADS);
glNormal3f(sin(ang),-cos(ang),0);
glVertex3f(x1+sca+ssa,y1+ssa-sca,0);
glVertex3f(x1+sca+ssa,y1+ssa-sca,z1);
glVertex3f(x2-sca+ssa,y2-ssa-sca,z2);
glVertex3f(x2-sca+ssa,y2-ssa-sca,0);
glNormal3f(-sin(ang),cos(ang),0);
glVertex3f(x1+sca-ssa,y1+ssa+sca,0);
glVertex3f(x1+sca-ssa,y1+ssa+sca,z1);
glVertex3f(x2-sca-ssa,y2-ssa+sca,z2);
glVertex3f(x2-sca-ssa,y2-ssa+sca,0);
glNormal3f(0,0,1);
glVertex3f(x1+sca+ssa,y1+ssa-sca,z1);
glVertex3f(x1+sca-ssa,y1+ssa+sca,z1);
glVertex3f(x2-sca-ssa,y2-ssa+sca,z2);
glVertex3f(x2-sca+ssa,y2-ssa-sca,z2);
	glEnd();
	
}
