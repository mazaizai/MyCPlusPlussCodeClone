
#include <iostream>
#include <math.h>
#include "Matrix.h"

using namespace std;


//static char THIS_FILE[]=__FILE__;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix::CMatrix(){
	rows=0;
	cols=0;
	size=0;
	elems = 0;
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
	cout<<"the row num of this matrix is"<<rows<<endl;
	cout<<"the cloumn num of this matrix is"<<cols<<endl;
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
		cout<<"please input the right row & column of matrix"<<endl;
	}

}

CMatrix CMatrix::X_ (double x0,double y0,double z0)   //cross matrix
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

CMatrix operator ! (CMatrix m)  //�����
{
	
	if (m.InvertGaussJordan(m.rows, m.elems) == true)
	{
		return m;
	}
	else
	{
		m.InvertTrench();//δ���Ժ�
		return m;
	}
	}

CMatrix CMatrix::L_ (char axis,double rad)   //rotate matrix   axis:  x,y,z    angle  rad

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


bool CMatrix::InvertTrench()
{ 


	return true;
}


bool CMatrix::InvertGaussJordan(	int m_nNumColumns, double  *m_pData)
{
	int *pnRow, *pnCol,i,j,k,l,u,v;
	double d = 0, p = 0;
	// �����ڴ�
	pnRow = new int[m_nNumColumns];
	pnCol = new int[m_nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return false;

	// ��Ԫ
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

		// ʧ��
		if (d == 0.0)
		{
			delete[] pnRow;
			delete[] pnCol;
			cout<<"the inverse of the Mtx is zero!"<<endl;

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

	// �����ָ����д���
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

	// �����ڴ�
	delete[] pnRow;
	delete[] pnCol;

	// �ɹ�����
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
		cout<<"XXX"<<endl;
	}

}




double CMatrix::operator () (unsigned int row, unsigned int col)
{

	if (row >= 1 && row <= rows && col >= 1 && col <= cols)
	{
		return elems[(row - 1)*cols + (col - 1)];
	}
	else
	{
		cout << "over the maxinux rows & cols of this matrix " << endl;
		return 0;

	}
}

CMatrix & CMatrix::operator = (const CMatrix & mtx)
{
	unsigned i, j;
	unsigned size;
	if (this == &mtx)
	{
		return *this;
	}
	delete[] elems;
	rows = mtx.rows;
	cols = mtx.cols;
	size = mtx.rows*mtx.cols;
	elems = new double[size];
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			elems[i*cols + j] = mtx.elems[i*cols + j];
		}
	}
	return *this;


}

CMatrix operator + (CMatrix p, CMatrix q)
{
	unsigned r, c;
	double val;
	CMatrix m(p.rows, p.cols);
	if (p.rows != p.rows || p.cols != q.cols)
	{
		cout << "the rows and columns of this two matrix is not matched!" << endl;
		return m;
	}
	for (r = 1; r <= p.rows; r++)
	{
		for (c = 1; c <= p.cols; c++)
		{
			val = p(r, c) + q(r, c);
			m.SetElem(r, c, val);
		}

	}
	return m;

}

CMatrix operator -(CMatrix p, CMatrix q)
{
	unsigned r, c;
	double val;
	CMatrix m(p.rows, p.cols);
	if (p.rows != p.rows || p.cols != q.cols)
	{
		cout << "the rows and columns of this two matrix is not matched!" << endl;
		return m;
	}
	for (r = 1; r <= p.rows; r++)
	{
		for (c = 1; c <= p.cols; c++)
		{
			val = p(r, c) - q(r, c);
			m.SetElem(r, c, val);
		}

	}
	return m;

}



CMatrix operator *(double p, CMatrix q)
{
	unsigned i, j, r, c;
	double val;
	CMatrix m(q.rows, q.cols);
	r = q.rows;
	c = q.cols;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
		{
			val = p * q(i, j);
			m.SetElem(i, j, val);
		}
	}

	return m;

}

CMatrix operator /(CMatrix p, double q)
{
	unsigned i, j, r, c;
	double val;
	CMatrix m(p.rows, p.cols);

	if (q == 0)
	{
		cout << "the dividend nums cannot be 0" << endl;
		return p;
	}

	r = p.rows;
	c = p.cols;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
		{
			val = p(i, j) / q;
			m.SetElem(i, j, val);
		}
	}

	return m;

}


CMatrix operator -(CMatrix p)
{
	unsigned i, j, r, c;
	double val;
	CMatrix m(p.rows, p.cols);

	r = p.rows;
	c = p.cols;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
		{
			val = -p(i, j);
			m.SetElem(i, j, val);
		}
	}

	return m;

}

CMatrix operator ~(CMatrix p)
{
	unsigned i, j, r, c;
	double val;
	CMatrix m(p.cols, p.rows);

	r = p.rows;
	c = p.cols;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
		{
			val = p(i, j);
			m.SetElem(j, i, val);
		}
	}

	return m;

}




CMatrix  operator *(CMatrix p, CMatrix q)
{
	unsigned r, c, i;
	double sum;
	CMatrix m(p.rows, q.cols);
	if (p.cols != q.rows)
	{
		cout << "the cols and rows of this two mtx are unmatched!" << endl;
		return m;
	}


	for (r = 1; r <= p.rows; r++)
	{
		for (c = 1; c <= q.cols; c++)
		{
			sum = 0;
			for (i = 1; i <= p.cols; i++)
			{
				sum = sum + p(r, i)*q(i, c);
			}
			m.SetElem(r, c, sum);
		}

	}
	return m;

}