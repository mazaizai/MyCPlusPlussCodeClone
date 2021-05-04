#include <iostream>
#include <String>
#include  "Vector.h"
#include "Coordinate.h"
using namespace std;

int main() {
	double B0=0, L0=0, Height0=0;
	double AoT = 0;
	string EarthType="WGS84";
	Coordinate Transform;
	CVector P_Launch(0,0,0),P_ecef;
	Transform.GeoCSToECEF(B0, L0, Height0, EarthType,P_ecef);
	P_ecef.ShowData();
	return 0;
}
