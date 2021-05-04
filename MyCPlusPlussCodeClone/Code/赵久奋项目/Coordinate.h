#ifndef COORDINATE_H 
#define COORDINATE_H

#include "Matrix.h"
#include "Vector.h"
#include <math.h>
#include <string.h>
#include "Earth.h"
using namespace std;
class Coordinate
{
public:
	Coordinate(); //construction function
public:
	~Coordinate(); //deconstruc function
	//friend class Earth;//定义友元类，使用该类相关内容
private: 
	CVector  VecHld; //向量运算
	CMatrix  MtxHld; //矩阵操作
	Earth* Earth_para=NULL;
	/*
	friend double CMatrix::operator () (unsigned row, unsigned col);  //提取某一矩阵元素
	friend CMatrix& CMatrix::operator = (const CMatrix & mtx);    //矩阵赋值运算

	friend CMatrix operator + (CMatrix p, CMatrix q);  //加运算符 
	friend CMatrix CMatrix::operator - (CMatrix p, CMatrix q);  //减运算符 
	friend CMatrix operator * (CMatrix p, CMatrix q);  //乘运算符，矩阵乘矩阵 
	friend CMatrix CMatrix::operator * (double p, CMatrix q);  //乘运算符，实数乘矩阵 
	friend CMatrix CMatrix::operator / (CMatrix p, double q);  //除运算符，矩阵除以实数 
	friend CMatrix CMatrix::operator ~ (CMatrix p);  //转置矩阵 
	friend CMatrix CMatrix::operator ! (CMatrix p);  //逆矩阵 
	friend CMatrix CMatrix::operator - (CMatrix p);  //负矩阵 
	
//	friend CMatrix CMatrix::operator* (CMatrix p, CMatrix q);  //乘运算符，矩阵乘矩阵 
	friend CMatrix L_(char axix, double rad);   //基元变换矩阵    axis: 轴 1:x ,2:y ,3:z    angle  角度  单位 度
	*/
		
public:
    void LaunchToECEF(const double& B0, const  double& L0, const  double& Height0, const double& AoT, const string& EarthType, const  CVector& P_Launch, CVector& P_ECEF);   //发射坐标系到ECEF
	void ECEFToLaunch(const double& B0, const  double& L0, const  double& Height0, const double& AoT, const string& EarthType, const  CVector& P_ECEF, CVector& P_Launch);  //ECEF到发射坐标系
	
	void GeoCSToECEF(const double& B0,const double& L0,const  double& Height0,const string& EarthType, CVector& P_ecef);//大地坐标系（经纬高）与ECCF的转换
	void ECEFToGeoCS(const CVector& P_ecef, const string& EarthType, double& B0, double& L0, double& Height0);//ECEF与大地坐标系（经纬高）的转换
	
	void LaunchToINLaunch(const double& B0,const double& L0,const double& Height0,const double& AoT,const double& time, const string& EarthType,const CVector& P_Launch,CVector& P_INLaunch);
    void INLaunchToLaunch(const double& B0,const double& L0,const double& Height0,const double& AoT,const double& time, const string& EarthType,CVector& P_INLaunch,CVector& P_Launch);
	
	void LaunchToMBodyCS(const double& phi,const double& psi,const double& gama,const CVector& P_launch,CVector&P_body);   //发射坐标系到弹体坐标系
	void MBodyCSToLaunch(const double& phi,const double& psi,const double& gama,const CVector&P_body,CVector& P_launch);   //发射坐标系到弹体坐标系
	
	void LaunchToBody(const double& phi,const double& psi,const double& gama,const CVector& P_launch,const CVector&P_body);   //发射坐标系到弹体坐标系
	void BodyToLaunch(const double& phi,const double& psi,const double& gama,const CVector&P_body,const CVector& P_launch);   //弹体坐标系到发射坐标系

	void NEDtoENU(const CVector& P_ned,CVector& P_enu);
	void ENUtoNED(const CVector& P_enu,CVector& P_ned);
	
    //东北天坐标系转换地心地固坐标系
	void ENUToECEF(const double& B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_enu, CVector& P_ecef);
	void ECEFToENU(const double&B0,const double&L0,const double&Height0,const string& EarthType, const CVector& P_ecef,CVector& P_enu);
	
	//北东地坐标系转地心地固坐标系
	void NEDToECEF(const double&B0, const double&L0, const double&Height0, const string& EarthType, const CVector& P_ned, CVector& P_ecef);
	void ECEFToNED(const double&B0, const double&L0, const double&Height0, const string& EarthType, const CVector& P_ecef, CVector& P_ned);
	
};
#endif // COORDINATE_H 