#include "stdafx.h"
#include "Vector.h"

#include "Matrix.h"
#include <iostream>
#include <math.h>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()
{

}

CVector::CVector(double x0,double y0,double z0)  //构造函数 
{
	x=x0;
	y=y0;
	z=z0;
}

CVector::~CVector()
{

}




CVector & CVector::operator = (const CVector & vct)  //矢量赋值运算
{
	if(this==&vct)
	{
		return *this;
	}
	x = vct.x;
	y = vct.y;
	z = vct.z;

	return *this;

}

CVector operator + ( CVector p ,CVector q )  //矢量相加
{
	CVector m;
	m.x=p.x+q.x;
	m.y=p.y+q.y;
	m.z=p.z+q.z;
	return m;   
}

CVector operator - ( CVector p ,CVector q )  //矢量相加
{
	CVector m;
	m.x=p.x-q.x;
	m.y=p.y-q.y;
	m.z=p.z-q.z;
	return m;   
}

CVector operator - ( CVector p )  //矢量相加
{
	CVector m;
	m.x=-p.x;
	m.y=-p.y;
	m.z=-p.z;
	return m;   
}
double operator * ( CVector p,CVector q)   //矢量点乘
{
	return (p.x*q.x + p.y*q.y +p.z*q.z);
}

CVector operator * ( CVector p, double a ) //矢量乘以常数
{
	CVector m;
	m.x=p.x*a;
	m.y=p.y*a;
	m.z=p.z*a;
	return m;   

}

CVector operator / ( CVector p, double a ) //矢量乘以常数
{
	CVector m;
	m.x=p.x/a;
	m.y=p.y/a;
	m.z=p.z/a;
	return m;   

}

CVector operator * (  double a,CVector p ) //矢量乘以常数
{
	CVector m;
	m.x=p.x*a;
	m.y=p.y*a;
	m.z=p.z*a;
	return m;   

}

CVector operator ^ (   CVector p,CVector q ) //矢量叉乘
{
	CVector m;

	m.x=p.y*q.z-p.z*q.y;
	m.y=-p.x*q.z+p.z*q.x;
	m.z=p.x*q.y-p.y*q.x;

	return m;   

}

CVector operator * (CMatrix p,CVector q)      //矩阵（3*3）与矢量相乘
{

	CVector m;
	if(p.cols!=3 || p.rows!=3 )
	{
		cout<<"矩阵乘以向量错误不能相乘！"<<endl;
		return m;
	}

	m.x=p(1,1)*q.x + p(1,2)*q.y + p(1,3)*q.z ;
	m.y=p(2,1)*q.x + p(2,2)*q.y + p(2,3)*q.z ;
	m.z=p(3,1)*q.x + p(3,2)*q.y + p(3,3)*q.z ;

	return m;

}

CMatrix X_ (CVector p)   //矢量的叉乘矩阵
{
	CMatrix m(3,3);

	m.SetElem(1,1,0);
	m.SetElem(1,2,-p.z);
	m.SetElem(1,3,p.y);
	m.SetElem(2,1,p.z);
	m.SetElem(2,2,0);
	m.SetElem(2,3,-p.x);
	m.SetElem(3,1,-p.y);
	m.SetElem(3,2,p.x);
	m.SetElem(3,3,0);

	return m;

}

void CVector::ShowData()
{
	cout<<"Data of Vector:"<<endl<<x<<endl<<y<<endl<<z<<endl;

}

double CVector::GetAbs()
{
	abs=sqrt(x*x+y*y+z*z);
	return abs;
}

