
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
void renderComponent(int index,float size,float mult,float time)
{
	Component* c=grid.map.components+index;
	int iA,iB,i;
	float x1,y1,z1,x2,y2,z2,dist;
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
dist=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
float fx,tx,fy,ty;//,d;
float ang=atan2(y2-y1,x2-x1);
	float sca=size*cos(ang);
	float ssa=size*sin(ang);
fx=x1+sca;
fy=y1+ssa;
tx=x2-sca;
ty=y2-ssa;
//d=sqrt((fx-tx)*(fx-tx)+(fy-ty)*(fy-ty));
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
//float a=atan2(z2-z1,d);
//glNormal3f(-sin(a)*cos(ang),-sin(a)*sin(ang),cos(a));
glVertex3f(x1+sca+ssa,y1+ssa-sca,z1);
glVertex3f(x1+sca-ssa,y1+ssa+sca,z1);
glVertex3f(x2-sca-ssa,y2-ssa+sca,z2);
glVertex3f(x2-sca+ssa,y2-ssa-sca,z2);
float spacing=.5;
float pos=-c->current*time;
while(pos>=spacing)pos-=spacing;
while(pos<0)pos+=spacing;
//float spacing=.5;
float density=abs(c->current);
glEnd();
if(c->type==RESISTOR){
glBegin(GL_QUADS);
glEnd();
}
while(pos<=dist){
	glPushMatrix();
	glTranslatef((x1*pos+x2*(dist-pos))/dist,(y1*pos+y2*(dist-pos))/dist,(z1*pos+z2*(dist-pos))/dist+size*2);
	glutSolidSphere(size,16,8);
if(c->type==BATTERY){
	glBegin(GL_QUADS);
glNormal3f(cos(ang),sin(ang),0);
	glVertex3f(-sca+ssa,-ssa-sca,size);
	glVertex3f(-sca-ssa,-ssa+sca,size);
	glVertex3f(-sca-ssa,-ssa+sca,-(z1*pos+z2*(dist-pos))/dist-size*2);
	glVertex3f(-sca+ssa,-ssa-sca,-(z1*pos+z2*(dist-pos))/dist-size*2);
glEnd();
}
	glPopMatrix();
pos+=spacing;
}
}
