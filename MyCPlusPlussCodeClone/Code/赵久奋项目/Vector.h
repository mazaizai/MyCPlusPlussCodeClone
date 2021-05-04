#ifndef VECTOR_H
#define VECTOR_H


class  CMatrix;

class CVector     //矢量类
{
public:
	CVector();  //构造函数 
	CVector(double x0,double y0,double z0);  //构造函数 
	virtual ~CVector();



public:
	double GetAbs();
	void ShowData();

	//数据成员
	double x,y,z;     //在某一个坐标系的三个坐标轴的投影
private:
	double abs;    //模，长度

public:
	//运算符重载
	CVector &operator = (const CVector & vct);    //矢量赋值运算
	double operator()(int num) const;//取值符号重载

	//重载友员函数
	friend  CVector operator + ( CVector p,CVector q);   //矢量相加
	friend  CVector operator - ( CVector p,CVector q);   //矢量相减
	friend  CVector operator - ( CVector p);   //矢量相减
	friend  double operator * ( CVector p,CVector q);   //矢量点乘
	friend  CVector operator * (CMatrix p,CVector q);      //矩阵（3*3）与矢量相乘

	friend  CVector operator ^ ( CVector p,CVector q);   //矢量叉乘

	friend  CVector operator * ( CVector p, double a );  //矢量乘以常数
	friend  CVector operator * (double a , CVector p);  //常数乘以矢量
	friend  CVector operator / (CVector p, double a);    //矢量除以常数

	friend CMatrix X_ (CVector p);   //矢量的叉乘矩阵
};


#endif // !defined(AFX_VECTOR_H__D2DCDF7E_11E4_4F85_AF51_06977718B759__INCLUDED_)
