#ifndef SPRING_CALC_H
#define SPRING_CALC_H

#include<cmath>
#include<iostream>
#include<sstream>
#include<cstring>

using namespace std;

class Spring_Calc
{
	private:
		float mass;
		float damp;
		float spring;
		float grav;
		float initx;
		float initv;
	public:
		Spring_Calc(){
			mass=1;
			damp=0;
			spring=1;
			grav=0;
			initx=0;
			initv=0;
		}

		float m(){return mass;}
		void m(float m){mass= m>0 ? m : 1.0;}
		float l(){return damp;}
		void l(float l){damp= l>=0 ? l : 0;}
		float k(){return spring;}
		void k(float k){spring = k>0 ? k : 1.0;}
		float g(){return grav;}
		void g(float g){grav=g;}

		float x0(){return initx;}
		void x0(float x0){initx=x0;}
		float v0(){return initv;}
		void v0(float v0){initv=v0;}

		float disp(float t);
		float vel(float t);
		float acc(float t);

		string eqstring();
};

#endif
