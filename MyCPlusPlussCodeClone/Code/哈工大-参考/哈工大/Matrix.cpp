//#include "stdafx.h"
#include "Matrix.h"

#include <iostream>
#include <math.h>
#include "stdlib.h "
using namespace std;


//static char THIS_FILE[]=__FILE__;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix::CMatrix()
{
	rows=0;
	cols=0;
	size=0;
	elems=0;

}

CMatrix::CMatrix(unsigned r)
{
	unsigned i,j;
	rows=r;
	cols=r;
	size=rows*cols;
	elems=new double[size];
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			elems[i*cols+j]=0;
		}
	}

}

CMatrix::CMatrix(unsigned rs,unsigned cs)
{
	unsigned i,j;
	rows=rs;
	cols=cs;
	size=rows*cols;
	elems=new double[size];
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			elems[i*cols+j]=0;
		}
	}
}


CMatrix::CMatrix(unsigned rs,unsigned cs,double *val)
{
	unsigned i,j;
	rows=rs;
	cols=cs;
	size=rows*cols;
	elems=new double[size];

	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			elems[i*cols+j]=val[i*cols+j];
		}
	}

}

CMatrix::CMatrix(const CMatrix &mtr)
{
	unsigned i,j;
	rows=mtr.rows;
	cols=mtr.cols;
	size=rows*cols;
	elems=new double[size];
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			elems[i*cols+j]=mtr.elems[i*cols+j];
		}
	}

}


CMatrix::~CMatrix()
{
	if(elems!=0)
	{
		delete[] elems;
	}
	elems=0;

}

void CMatrix::ShowData()
{
	unsigned i,j;
	cout<<endl;
	cout<<"行数＝"<<rows<<endl;
	cout<<"列数＝"<<cols<<endl;
	cout<<"数据"<<endl;	
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			cout<<elems[i*cols+j]<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;

}

void CMatrix::Setvalue(unsigned int rs, unsigned int cs, double *val)
{

	unsigned i,j;
	rows=rs;
	cols=cs;
	size=rows*cols;
	elems=new double[size];
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			elems[i*cols+j]=val[i*cols+j];
		}
	}


}

void CMatrix::Setvalue(unsigned int rs, unsigned int cs)
{

	rows=rs;
	cols=cs;
	size=rows*cols;
	if(elems!=0)
	{
		delete [] elems;
	}
	elems=new double[size];

}



void CMatrix::SetElem(unsigned int row, unsigned int col, double val)
{
	if(row>=1 && rows<=rows &&  col>=1  &&col<=cols )
	{
		elems[(row-1)*cols+(col-1)]=val;
	}
	else
	{
		cout<<"矩阵元素标号超出"<<endl;
	}

}

double CMatrix::operator () (unsigned row,unsigned col)
{

	if(row>=1 && row<=rows &&  col>=1  &&col<=cols )
	{
		return elems[(row-1)*cols+(col-1)];
	}
	else
	{
		return 0;
		cout<<"矩阵元素标号超出"<<endl;
	}
}  

CMatrix & CMatrix::operator = (const CMatrix & mtx)
{
	unsigned i,j;
	unsigned size;
	if(this==&mtx)
	{
		return *this;
	}
	delete[] elems;
	rows=mtx.rows;
	cols=mtx.cols;
	size=mtx.rows*mtx.cols;
	elems=new double[size];
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			elems[i*cols+j]=mtx.elems[i*cols+j];
		}
	}
	return *this;


} 

CMatrix operator + (CMatrix p,CMatrix q)
{
	unsigned r,c;
	double val;
	CMatrix m(p.rows,p.cols);
	if(p.rows!=p.rows  || p.cols!=q.cols)
	{
		cout<<"两矩阵不能相加"<<endl;
		return m;
	}
	for(r=1;r<=p.rows;r++)
	{
		for(c=1;c<=p.cols;c++)
		{
			val=p(r,c)+q(r,c);
			m.SetElem(r,c,val);
		}

	}
	return m;

}

CMatrix operator -(CMatrix p,CMatrix q)
{
	unsigned r,c;
	double val;
	CMatrix m(p.rows,p.cols);
	if(p.rows!=p.rows  || p.cols!=q.cols)
	{
		cout<<"两矩阵不能相减"<<endl;
		return m;
	}
	for(r=1;r<=p.rows;r++)
	{
		for(c=1;c<=p.cols;c++)
		{
			val=p(r,c)-q(r,c);
			m.SetElem(r,c,val);
		}

	}
	return m;

}



CMatrix operator *(double p,CMatrix q)
{
	unsigned i,j,r,c;
	double val;
	CMatrix m(q.rows,q.cols);
	r=q.rows;
	c=q.cols;
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			val=p*q(i,j);
			m.SetElem(i,j,val);
		}
	}

	return m;

}

CMatrix operator /(CMatrix p,double q)
{
	unsigned i,j,r,c;
	double val;
	CMatrix m(p.rows,p.cols);

	if(q==0)
	{
		cout<<"矩阵不能除以0"<<endl;
		return p;
	}

	r=p.rows;
	c=p.cols;
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			val=p(i,j)/q;
			m.SetElem(i,j,val);
		}
	}

	return m;

}


CMatrix operator -(CMatrix p)
{
	unsigned i,j,r,c;
	double val;
	CMatrix m(p.rows,p.cols);

	r=p.rows;
	c=p.cols;
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			val=-p(i,j);
			m.SetElem(i,j,val);
		}
	}

	return m;

}

CMatrix operator ~(CMatrix p)
{
	unsigned i,j,r,c;
	double val;
	CMatrix m(p.cols,p.rows);

	r=p.rows;
	c=p.cols;
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			val=p(i,j);
			m.SetElem(j,i,val);
		}
	}

	return m;

}




CMatrix operator *(CMatrix p,CMatrix q)
{
	unsigned r,c,i;
	double sum;
	CMatrix m(p.rows,q.cols);
	if(p.cols!=q.rows)
	{
		cout<<"矩阵乘法错误不能相乘！"<<endl;
		return m;
	}


	for(r=1;r<=p.rows;r++)
	{
		for(c=1;c<=q.cols;c++)
		{
			sum=0;
			for(i=1;i<=p.cols;i++)
			{
				sum=sum+p(r,i)*q(i,c);
			}
			m.SetElem(r,c,sum);
		}

	}
	return m;

}


CMatrix X_ (double x0,double y0,double z0)   //矢量 x0,y0,z0 的乘矩阵
{
	CMatrix m(3,3);

	m.SetElem(1,1,0);
	m.SetElem(1,2,-z0);
	m.SetElem(1,3,y0);
	m.SetElem(2,1,z0);
	m.SetElem(2,2,0);
	m.SetElem(2,3,-x0);
	m.SetElem(3,1,-y0);
	m.SetElem(3,2,x0);
	m.SetElem(3,3,0);

	return m;

}



CMatrix L_ (char axis,double rad)   //基元变换矩阵    axis: 轴 x,y,z    angle  角度  单位 度

{
	CMatrix m(3,3);

	if(axis=='x')
	{
		m.SetElem(1,1,1);
		m.SetElem(1,2,0);
		m.SetElem(1,3,0);
		m.SetElem(2,1,0);
		m.SetElem(2,2,cos(rad));
		m.SetElem(2,3,sin(rad));
		m.SetElem(3,1,0);
		m.SetElem(3,2,-sin(rad));
		m.SetElem(3,3,cos(rad));
	}

	if(axis=='y')
	{
		m.SetElem(1,1,cos(rad));
		m.SetElem(1,2,0);
		m.SetElem(1,3,-sin(rad));
		m.SetElem(2,1,0);
		m.SetElem(2,2,1);
		m.SetElem(2,3,0);
		m.SetElem(3,1,sin(rad));
		m.SetElem(3,2,0);
		m.SetElem(3,3,cos(rad));

	}

	if(axis=='z')
	{
		m.SetElem(1,1,cos(rad));
		m.SetElem(1,2,sin(rad));
		m.SetElem(1,3,0);
		m.SetElem(2,1,-sin(rad));
		m.SetElem(2,2,cos(rad));
		m.SetElem(2,3,0);
		m.SetElem(3,1,0);
		m.SetElem(3,2,0);
		m.SetElem(3,3,1);

	}

	return m;

}


CMatrix operator ! (CMatrix m)  //逆矩阵
{



	if( m.InvertGaussJordan(m.rows,m.elems)==true)
	{
		return m;
	}
	else
	{
		m.InvertTrench();//未调试好
		return m;
	}









}



bool CMatrix::InvertTrench()
{ 


	return true;
}


bool CMatrix::InvertGaussJordan(	int m_nNumColumns, double  *m_pData)
{
	int *pnRow, *pnCol,i,j,k,l,u,v;
	double d = 0, p = 0;
	// 分配内存
	pnRow = new int[m_nNumColumns];
	pnCol = new int[m_nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return false;

	// 消元
	for (k=0; k<=m_nNumColumns-1; k++)
	{ 
		d=0.0;
		for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				l=i*m_nNumColumns+j; p=fabs(m_pData[l]);
				if (p>d) 
				{ 
					d=p; 
					pnRow[k]=i; 
					pnCol[k]=j;
				}
			}
		}

		// 失败
		if (d == 0.0)
		{
			delete[] pnRow;
			delete[] pnCol;
			cout<<"全主元为零，求解失败！"<<endl;

			return (false);   
		}

		if (pnRow[k] != k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
			{ 
				u=k*m_nNumColumns+j; 
				v=pnRow[k]*m_nNumColumns+j;
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
			}
		}

		if (pnCol[k] != k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
			{ 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnCol[k];
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
			}
		}

		l=k*m_nNumColumns+k;
		m_pData[l]=1.0/m_pData[l];
		for (j=0; j<=m_nNumColumns-1; j++)
		{
			if (j != k)
			{ 
				u=k*m_nNumColumns+j; 
				m_pData[u]=m_pData[u]*m_pData[l];
			}
		}

		for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
			{
				for (j=0; j<=m_nNumColumns-1; j++)
				{
					if (j!=k)
					{ 
						u=i*m_nNumColumns+j;
						m_pData[u]=m_pData[u]-m_pData[i*m_nNumColumns+k]*m_pData[k*m_nNumColumns+j];
					}
				}
			}
		}

		for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
			{ 
				u=i*m_nNumColumns+k; 
				m_pData[u]=-m_pData[u]*m_pData[l];
			}
		}
	}

	// 调整恢复行列次序
	for (k=m_nNumColumns-1; k>=0; k--)
	{ 
		if (pnCol[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
			{ 
				u=k*m_nNumColumns+j; 
				v=pnCol[k]*m_nNumColumns+j;
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
			}
		}

		if (pnRow[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
			{ 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnRow[k];
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
			}
		}
	}

	// 清理内存
	delete[] pnRow;
	delete[] pnCol;

	// 成功返回
	return true;

}

double CMatrix::GetElem(unsigned int row, unsigned int col)
{

	if(row>=1 && rows<=rows &&  col>=1  &&col<=cols )
	{
		return elems[(row-1)*cols+(col-1)];
	}
	else
	{
		return 0;
		cout<<"矩阵元素标号超出"<<endl;
	}

}

