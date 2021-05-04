//
//  Coordinate.cpp
//  
//
//  Created by 	P.H.D Ma on May/2/2021.
//  Copyright @ MHBN. All rights reserved.
//
#include "Vector.h"
#include "Matrix.h"
#include "Earth.h"
#include "Coordinate.h"
#include <iostream>
using namespace std;
/*
	发射坐标系  Launch Coordinate System, Launch
	发射惯性坐标系 Launch Inertial Coordinate System, INLaunch
	地心固体坐标系  Earth-Centered Earth-Fixed System, ECEF
	地理坐标系   Geographic Coordinate System, GeoCS
	弹体坐标系  Missile-Body Coordinate System, MBodyCS
	东北天坐标系  North-East-Up Coordinate System, ENU
	北东地坐标系  North-East-Down Corrdinate System,NED
*/

const double  pi=3.1415926;
Coordinate::Coordinate(){
}

Coordinate::~Coordinate(){
	if (Earth_para != NULL) {
		delete Earth_para;
	}

}

//发射坐标系转地心地固坐标系
void Coordinate::LaunchToECEF(const double& B0,const double& L0,const double& Height0,const double& AoT, const string& EarthType,const CVector& P_Launch,CVector& P_ECEF){  //发射坐标系到ECEF
//Input 发射点纬度（弧度）、经度（弧度）、高程（m）、瞄准方向（弧度），地球类型（string） ，目标点在发射坐标系坐标（m）3*1
//Output 目标点在ECEF中的坐标 
	CMatrix EtoD = MtxHld.L_('y', -(pi / 2 + AoT))*MtxHld.L_('x', B0)*MtxHld.L_('z', -(pi / 2 - L0));  //发射系到地心系转换矩阵
    CVector Point_ECEF;
	/* 临时注释
    GeoCSToECEF(B0,L0,Height0,EarthType,Point_ECEF); //计算发射点在ECEF中的位置坐标
	P_ECEF=EtoD*P_Launch+Point_ECEF;  //
	*/
	P_ECEF = EtoD * P_Launch;
}

//地心地固坐标系转发射坐标系
void Coordinate::ECEFToLaunch(const double& B0,const  double& L0,const  double& Height0,const double& AoT,const string& EarthType,const  CVector& P_ECEF,CVector& P_Launch){   //ECEF到发射坐标系
//Input 发射点纬度（弧度）、经度（弧度）、高程（m）、瞄准方向（弧度）、地球类型（string） ，目标点在ECEF中坐标（m）3*1
//Output 目标点在发射坐标系中的坐标 

	CMatrix DtoE = MtxHld.L_('z', -(pi / 2 - L0))*MtxHld.L_('x', B0)*MtxHld.L_('y', -(pi / 2 + AoT));  //发射系到地心系转换矩阵
	CVector Point_ECEF;//发射点在ECEF中的坐标向量
	
	GeoCSToECEF(B0,L0,Height0,EarthType,Point_ECEF); //计算发射点在ECEF中的位置坐标
	P_Launch=DtoE*(P_ECEF-Point_ECEF);//计算目标点在发射坐标系的坐标
	
	P_Launch = DtoE * P_ECEF;
}

//地理坐标系与ECCF的转换
void Coordinate::GeoCSToECEF(const double& B0,const double& L0,const  double& Height0,const string& EarthType,CVector& P_ecef){
 //Input    point的经（弧度）、纬（弧度）、高程（m），地球类型
 //Output   point在ECEF中的坐标
	//地球参数赋值
	if (Earth_para != NULL) {
		delete Earth_para;
	}
	Earth_para = new Earth(EarthType);
  double W = sqrt(1-pow(Earth_para->alphae*sin(B0),2));
  double N = Earth_para->ae/W;
   P_ecef.x = (N+Height0)*cos(B0)*cos(L0);
   P_ecef.y = (N+Height0)*cos(B0)*sin(L0);
   P_ecef.z = (N*(1-Earth_para->e2) + Height0)*sin(B0);
}

//ECEF与地理坐标系的转换
void Coordinate::ECEFToGeoCS(const CVector& P_ecef,const string& EarthType,double& B0,double& L0,double& Height0){
 //Input    point的经（弧度）、纬（弧度）、高程（m），地球类型
 //Output   point在ECEF中的坐标

//地球参数赋值
	if (Earth_para != NULL) {
		delete Earth_para;
	}
	Earth_para = new Earth(EarthType);

 //纬度计算
if (P_ecef.x==0&&P_ecef.y>=0){
	L0 = pi/2;
} 
else if (P_ecef.x==0&&P_ecef.y<=0){
	L0 = -pi/2;
}
else
{
	L0 = atan(P_ecef.y/P_ecef.x);
}
	double p = sqrt(P_ecef.x*P_ecef.x + P_ecef.y*P_ecef.y);
    double p2 = p*p;
    double e4 = pow(Earth_para->e2,2);
    double a2 = pow(Earth_para->alphae,2);
    double zi = (1-Earth_para->e2)*pow(P_ecef.z,2)/a2;
    double rho = (p2/a2 + zi - e4)/6.0;
    double rho2 = rho*rho;
    double rho3 = rho*rho2;
    double s = 0.25*e4*zi*p2/a2;
    double t = pow(rho3 + s + sqrt(s*(s+2.0*rho3)), 1.0/3.0);
    double u = rho + t + rho2 / t;
    double v = sqrt(u*u + e4*zi);
    double w = Earth_para->e2*(u + v - zi)/(2*v);
    double k = 1 + Earth_para->e2*(sqrt(u+v+w*w) + w)/(u+v);
    double Zk = P_ecef.z*k;
     B0 = atan2(k*P_ecef.z, p); //纬度
     Height0 = sqrt(p2 + Zk*Zk)*(1.0/k - (1-Earth_para->e2))/Earth_para->e2; //经度

}



//发射坐标系转惯性发射坐标系
void Coordinate::LaunchToINLaunch(const double& B0,const double& L0,const double& Height0,const double& AoT,const double& time, const string& EarthType,const CVector& P_Launch,CVector& P_INLaunch){
    //Input 发射点经纬度（弧度）高程（m） 瞄准方向（弧度） 飞行时间（s）  地球类型（string） 发射系下位置
	//OutPut  发射惯性系下位置
   //地球参数赋值
	if (Earth_para != NULL) {
		delete Earth_para;
	}
	Earth_para = new Earth(EarthType);
   /* 
	double  phi0=atan(pow(Earth_para.be/Earth_para.alphae,2)*tan(B0));//计算地心纬度
	CMatrix G_sTowe= L_('z',phi0)*L_('y',L0);//
	CMatrix G_sTog=(~G_sTowe)*L_('x',Earth_para.wed*time)*G_sTowe;//发射系到发射惯性系转换矩阵
	*/

	//惯性球下的发射点经纬高
	double B1 = B0;
	double L1 = L0 + Earth_para->wed*time;
	double Height1 = Height0;
	CVector P_ECEF; //ECEF下的坐标
    LaunchToECEF(B1,L1,Height1,AoT,EarthType,P_Launch,P_ECEF);  //发射坐标系到ECEF
    ECEFToLaunch(B0,L0,Height0,AoT,EarthType,P_ECEF,P_INLaunch);  //ECEF转换到发射惯性系

}

//惯性发射坐标系转发射坐标系
void Coordinate::INLaunchToLaunch(const double& B0,const double& L0,const double& Height0,const double& AoT,const double& time, const string& EarthType,CVector& P_INLaunch, CVector& P_Launch){
    //Input 发射点经纬度（弧度）高程（m） 瞄准方向（弧度） 飞行时间（s）  地球类型（string）  发射惯性系下位置 
	//OutPut  发射系下位置
    
   /* Earth Earth_para(EarthType);
	double  phi0=atan(pow(Earth_para.be/Earth_para.alphae,2)*tan(B0));//计算地心纬度
	CMatrix G_sTowe= L_('z',phi0)*L_('y',L0);//
	CMatrix G_sTog=(~G_sTowe)*L_('x',Earth_para.wed*time)*G_sTowe;//发射系到发射惯性系转换矩阵
	*/
	//地球参数
	Earth Earth_para(EarthType);
	//惯性球下的发射点经纬高
	double B1 = B0;
	double L1 = L0 + Earth_para.wed*time;
	double Height1 = Height0;
	CVector P_ECEF; //ECEF下坐标
    LaunchToECEF(B0,L0,Height1,AoT,EarthType,P_INLaunch,P_ECEF);  //发射惯性系到ECEF
    ECEFToLaunch(B1,L1,Height0,AoT,EarthType,P_ECEF,P_Launch);  //ECEF转换到发射系

}

//发射坐标系转弹体坐标系
void Coordinate::LaunchToMBodyCS(const double& phi,const double& psi,const double& gama,const CVector& P_launch,CVector&P_body){   //发射坐标系到弹体坐标系
	//Input  弹体姿态 俯仰角phi  偏航角psi  滚动角gama  目标点在发射系的坐标P_launch
	//Output  弹体系坐标 P_body
	CMatrix DtoT= MtxHld.L_('x', gama)*MtxHld.L_('y', psi)*MtxHld.L_('z', phi);//发射系到箭体系转化矩阵
    P_body=DtoT*P_launch;
}

//弹体坐标系转发射坐标系
void Coordinate::MBodyCSToLaunch(const double& phi,const double& psi,const double& gama,const CVector&P_body, CVector& P_launch){   //发射坐标系到弹体坐标系
	//Input   弹体姿态 俯仰角phi  偏航角psi  滚动角gama   弹体系坐标 P_body 
	//Output  目标点在发射系的坐标P_launch
	CMatrix TtoD= MtxHld.L_('z', phi)*MtxHld.L_('y', psi)*MtxHld.L_('x', gama);//发射系到弹体系转化矩阵
    P_launch= TtoD*P_body;
}

//北东地坐标系转东北天坐标系
void Coordinate::NEDtoENU(const CVector& P_ned, CVector& P_enu){
   P_enu = CVector(P_ned(1), P_ned(0), -P_ned(2));
}

//东北天坐标系转北东地坐标系
void Coordinate::ENUtoNED(const CVector& P_enu,CVector& P_ned){
    P_ned = CVector(P_enu(1), P_enu(0), -P_enu(2));
}

//东北天坐标系转换地心地固坐标系
void Coordinate::ENUToECEF(const double&B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_enu,CVector& P_ecef){

	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef);//大地坐标系（经纬高）与ECCF的转换
    CMatrix UToF= MtxHld.L_('x',pi/2-B0)*MtxHld.L_('z',-pi/2-L0); //转换矩阵
    P_ecef=UToF*P_enu+P_ecef;
}

//地心地固坐标系转东北天坐标系
void Coordinate::ECEFToENU(const double&B0,const double&L0,const double&Height0,const string& EarthType, const CVector& P_ecef,CVector& P_enu){
    CVector P_ecef_0;//站点在ECEF的坐标
	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef_0);//大地坐标系（经纬高）与ECCF的转换
    CMatrix FToU=MtxHld.L_('z',pi/2+L0)*MtxHld.L_('x',B0-pi/2); //转换矩阵
	P_enu=FToU*(P_ecef-P_ecef_0);
}

//北东地坐标系转地心地固坐标系
void Coordinate::NEDToECEF(const double&B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_ned, CVector& P_ecef){
	//未验证
	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef);//大地坐标系（经纬高）与ECCF的转换
    CMatrix NToF= MtxHld.L_('y',pi/2+B0)*MtxHld.L_('z',-L0); //转换矩阵
    P_ecef=NToF*P_ned+P_ecef;
}

//地心地固坐标系转北东地坐标系
void Coordinate::ECEFToNED(const double&B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_ecef, CVector& P_ned){
	
	CVector P_ecef_0;//站点在ECEF的坐标
	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef_0);//大地坐标系（经纬高）与ECCF的转换
	CMatrix FToN= MtxHld.L_('z',L0)*MtxHld.L_('y',-pi/2-B0); //转换矩阵
	P_ned=FToN*(P_ecef-P_ecef_0);
}

