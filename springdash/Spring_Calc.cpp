#include <cmath>

#include "Spring_Calc.h"

using namespace std;

float Spring_Calc::disp(float time)
{
	float c=sqrt(spring/mass-damp*damp/(4*mass*mass));
	float n=mass*grav/spring;
	float c1=(initv+(initv+n)*damp/mass-(initx+n)*damp/(2*mass))/c;
	float c2=initx+n;
	float a=-damp/(2*mass);
	/*float c=sqrt((spring/mass)-(damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;
	float n=grav/spring;*/
	return n-exp(a*time)*(c1*sin(c*time)+c2*cos(c*time));
}
float Spring_Calc::vel(float time)
{
	float c=sqrt(spring/mass-damp*damp/(4*mass*mass));
	float n=mass*grav/spring;
	float c1=(initv+(initv+n)*damp/mass-(initx+n)*damp/(2*mass))/c;
	float c2=initx+n;
	float a=-damp/(2*mass);
	/*float a=-damp/(2*mass);
	float c=sqrt((spring/mass)-(damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;*/
	return -exp(a*time)*((a*c1-c*c2)*sin(c*time)+(a*c2+c*c1)*cos(c*time));
}
float Spring_Calc::acc(float time)
{
	float c=sqrt(spring/mass-damp*damp/(4*mass*mass));
	float n=mass*grav/spring;
	float c1=(initv+(initv+n)*damp/mass-(initx+n)*damp/(2*mass))/c;
	float c2=initx+n;
	float a=-damp/(2*mass);
	/*float a=-damp/(2*mass);
	float c=sqrt((spring/mass)-(damp*damp)/(4*mass*mass));
	float c2=-initv-grav/spring;
	float c1=(-initx-initx*damp/mass-damp*grav/(spring*mass))/c;*/
	return a*exp(a*time)*((a*c1-c*c2)*sin(c*time)+(a*c2+c*c1)*cos(c*time))+ c*exp(a*time)*((a*c1-c*c2)*cos(c*time)-(a*c2+c*c1)*sin(c*time));
}

string Spring_Calc::eqstring()
{
	float c=sqrt(spring/mass-damp*damp/(4*mass*mass));
	float n=mass*grav/spring;
	float c1=(initv+(initv+n)*damp/mass-(initx+n)*damp/(2*mass))/c;
	float c2=initx+n;
	float a=-damp/(2*mass);
	stringstream out (stringstream::in | stringstream::out);
	if(a!=0&&(c1!=0||c2!=0)){
		out<<"e^("<<a<<"t)";
	}
	if(c!=0){
		if(c1!=0||c2!=0){
			out<<"( ";
			if(c1!=0){
				out<<c1;out<<"sin("<<c<<"t) "<<( c2!=0 ? " + " : "" );
			}
			if(c2!=0){
				out<<c2<<"cos("<<c<<"t) ";
			}
			out<<")";
		}
	}else{
		if(c2!=0){
			out<<c2;
		}
	}
	if((out.str().length()!=0)&&(n!=0)){
		out<<" + "<<n;
	}
	string o=out.str();
	if(o.length()==0){
		o+="0";
	}
	return o;
}
