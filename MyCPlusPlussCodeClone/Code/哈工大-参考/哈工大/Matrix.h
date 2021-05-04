#ifndef MATRIX_H
#define MATRIX_H


class CMatrix  
{
public:
	void SetElem(unsigned row,unsigned col,double val);  //给单个元素赋值
	void Setvalue(unsigned rs,unsigned cs,double *val);  //给各个元素赋值
	void Setvalue(unsigned rs,unsigned cs);  //给定行数，列数
	void ShowData();
	//构造函数和析构函数
	CMatrix();
	CMatrix(unsigned r);  //自定义构造:  r维方阵
	CMatrix(unsigned rs,unsigned cs);   //自定义构造: 行数 rs  列数 cs
	CMatrix(unsigned rs,unsigned cs,double *val);  //自定义构造:  行数 rs  列数 cs  数据 val[]
	CMatrix(const CMatrix & mtr);  //拷贝构造函数 ，拷贝
	virtual ~CMatrix();   //析构函数


	bool InvertGaussJordan(	int , double  *);   //第二种求逆的方法
	bool  InvertTrench();  //第二种求逆的方法

	//运算符重载
	double operator () (unsigned row,unsigned col);  //提取某一矩阵元素
	CMatrix &operator = (const CMatrix & mtx);    //矩阵赋值运算
	//重载友员函数
	friend CMatrix operator + (CMatrix p,CMatrix q);  //加运算符 
	friend CMatrix operator - (CMatrix p,CMatrix q);  //减运算符 
	friend CMatrix operator * (CMatrix p,CMatrix q);  //乘运算符，矩阵乘矩阵 
	friend CMatrix operator * (double p,CMatrix q);  //乘运算符，实数乘矩阵 
	friend CMatrix operator / (CMatrix p,double q);  //除运算符，矩阵除以实数 
	friend CMatrix operator ~ (CMatrix p);  //转置矩阵 
	friend CMatrix operator ! (CMatrix p);  //逆矩阵 
	friend CMatrix operator - (CMatrix p);  //负矩阵 
	friend CMatrix L_ (char axix,double rad);   //基元变换矩阵    axis: 轴 1:x ,2:y ,3:z    angle  角度  单位 度


public:
	double GetElem(unsigned row,unsigned col);
	unsigned cols;  //矩阵列数
	unsigned rows;  //矩阵行数
	unsigned size;  //矩阵数据缓冲区大小
	double *elems;   //矩阵数据缓冲区指针






};

#endif // !defined(AFX_MATRIX_H__27E93BE0_F878_415E_9C3A_D356CA1A8416__INCLUDED_)
