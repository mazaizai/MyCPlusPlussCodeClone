#ifndef VECTOR_H
#define VECTOR_H


class  CMatrix;

class CVector     //ʸ����
{
public:
	CVector();  //���캯�� 
	CVector(double x0,double y0,double z0);  //���캯�� 
	virtual ~CVector();



public:
	double GetAbs();
	void ShowData();

	//���ݳ�Ա
	double x,y,z;     //��ĳһ������ϵ�������������ͶӰ
private:
	double abs;    //ģ������

public:
	//���������
	CVector &operator = (const CVector & vct);    //ʸ����ֵ����
	double operator()(int num) const;//ȡֵ��������

	//������Ա����
	friend  CVector operator + ( CVector p,CVector q);   //ʸ�����
	friend  CVector operator - ( CVector p,CVector q);   //ʸ�����
	friend  CVector operator - ( CVector p);   //ʸ�����
	friend  double operator * ( CVector p,CVector q);   //ʸ�����
	friend  CVector operator * (CMatrix p,CVector q);      //����3*3����ʸ�����

	friend  CVector operator ^ ( CVector p,CVector q);   //ʸ�����

	friend  CVector operator * ( CVector p, double a );  //ʸ�����Գ���
	friend  CVector operator * (double a , CVector p);  //��������ʸ��
	friend  CVector operator / (CVector p, double a);    //ʸ�����Գ���

	friend CMatrix X_ (CVector p);   //ʸ���Ĳ�˾���
};


#endif // !defined(AFX_VECTOR_H__D2DCDF7E_11E4_4F85_AF51_06977718B759__INCLUDED_)
