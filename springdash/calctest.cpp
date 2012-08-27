#include <cmath>
#include <iostream>

using namespace std;

main(int argc,char** argv)
{
	cout<<"HELLO?"<<endl;
	float x0=0.0;
	float v0=0.0;
	float m=1.0;
	float l=0.0;
	float k=1.0;
	float g=0;
	cout<<"initial position: ";
	cin>>x0;
	cout<<"initial velocity: ";
	cin>>v0;
	cout<<"mass: ";
	cin>>m;
	cout<<"damping: ";
	cin>>l;
	cout<<"spring constant: ";
	cin>>k;
	cout<<"gravity: ";
	cin>>g;
	float a=-l/(2*m);
	float c=sqrt((k/m)-(l*l)/(4*m*m));
	float c2=-v0-g/k;
	float c1=(-x0-x0*l/m-l*g/(k*m))/c;
	float n=g/k;
	cout<<"e^("<<a<<"t) * ("<<c1<<"sin("<<c<<"t) + "<<c2<<"cos("<<c<<"t)) + "<<n<<endl;
	return 0;
}
