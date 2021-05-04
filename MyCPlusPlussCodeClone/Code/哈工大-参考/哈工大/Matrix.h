#ifndef MATRIX_H
#define MATRIX_H


class CMatrix  
{
public:
	void SetElem(unsigned row,unsigned col,double val);  //������Ԫ�ظ�ֵ
	void Setvalue(unsigned rs,unsigned cs,double *val);  //������Ԫ�ظ�ֵ
	void Setvalue(unsigned rs,unsigned cs);  //��������������
	void ShowData();
	//���캯������������
	CMatrix();
	CMatrix(unsigned r);  //�Զ��幹��:  rά����
	CMatrix(unsigned rs,unsigned cs);   //�Զ��幹��: ���� rs  ���� cs
	CMatrix(unsigned rs,unsigned cs,double *val);  //�Զ��幹��:  ���� rs  ���� cs  ���� val[]
	CMatrix(const CMatrix & mtr);  //�������캯�� ������
	virtual ~CMatrix();   //��������


	bool InvertGaussJordan(	int , double  *);   //�ڶ�������ķ���
	bool  InvertTrench();  //�ڶ�������ķ���

	//���������
	double operator () (unsigned row,unsigned col);  //��ȡĳһ����Ԫ��
	CMatrix &operator = (const CMatrix & mtx);    //����ֵ����
	//������Ա����
	friend CMatrix operator + (CMatrix p,CMatrix q);  //������� 
	friend CMatrix operator - (CMatrix p,CMatrix q);  //������� 
	friend CMatrix operator * (CMatrix p,CMatrix q);  //�������������˾��� 
	friend CMatrix operator * (double p,CMatrix q);  //���������ʵ���˾��� 
	friend CMatrix operator / (CMatrix p,double q);  //����������������ʵ�� 
	friend CMatrix operator ~ (CMatrix p);  //ת�þ��� 
	friend CMatrix operator ! (CMatrix p);  //����� 
	friend CMatrix operator - (CMatrix p);  //������ 
	friend CMatrix L_ (char axix,double rad);   //��Ԫ�任����    axis: �� 1:x ,2:y ,3:z    angle  �Ƕ�  ��λ ��


public:
	double GetElem(unsigned row,unsigned col);
	unsigned cols;  //��������
	unsigned rows;  //��������
	unsigned size;  //�������ݻ�������С
	double *elems;   //�������ݻ�����ָ��






};

#endif // !defined(AFX_MATRIX_H__27E93BE0_F878_415E_9C3A_D356CA1A8416__INCLUDED_)
