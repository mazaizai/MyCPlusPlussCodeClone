//#include "StdAfx.h"
#include "zuobiaoxi.h"

zuobiaoxi::zuobiaoxi(void)
{
}

zuobiaoxi::~zuobiaoxi(void)
{
}
void zuobiaoxi::fun_Init()
{
	EtoD = L_('y', -(pi / 2 + A0T))*L_('x', PHI)*L_('z', -(pi / 2 - THETA));//���ĵ�����ϵ�� A0T:���䷽�� PHI�������γ�ȡ�THETA������㾭�ȡ�
	DtoE = ~EtoD;//���䵽����ϵ

	DtoT=L_('X', GAMMA)*L_('Y', PSI)*L_('z', PHI1);//����ϵ������ϵ��PHI1:�����ǡ�PSI��ƫ���ǡ�GAMMA�������ǡ�
	TtoD=~DtoT;//����ϵ������ϵ

	double ae=6378137;//����뾶������
	double miu=3.986005e14;//������������
	double alphae=1/298.257;//ƫ����
	double be=ae-ae*alphae;//����̰���
	double wed=7.292115e-5;//����ת��
        phi0=atan(pow(be/ae,2)*tan(B0));//B0:�����γ��
	G_sTowe= L_('z',phi0)*L_('y',A0);//A0:����㾭��
	G_sTog=(~G_sTowe)*L_('x',wed*time)*G_sTowe;//�������ϵ��������ϵ��time����������ʱ��
	gToG_s=G_sTog;//����ϵ���������ϵ

	CVector a,b;
	a.x=1;
	a.y=2;
	a.z=3;
	b=EtoD*a;//���ӣ�aΪ����ϵ������b��Ϊ����ϵ��



}