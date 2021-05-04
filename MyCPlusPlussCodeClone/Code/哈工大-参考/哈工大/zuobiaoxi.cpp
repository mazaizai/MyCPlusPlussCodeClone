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
	EtoD = L_('y', -(pi / 2 + A0T))*L_('x', PHI)*L_('z', -(pi / 2 - THETA));//地心到发射系。 A0T:发射方向。 PHI：发射点纬度。THETA：发射点经度。
	DtoE = ~EtoD;//发射到地心系

	DtoT=L_('X', GAMMA)*L_('Y', PSI)*L_('z', PHI1);//发射系到箭体系。PHI1:俯仰角。PSI：偏航角。GAMMA：滚动角。
	TtoD=~DtoT;//箭体系到发射系

	double ae=6378137;//地球半径长半轴
	double miu=3.986005e14;//地球引力常量
	double alphae=1/298.257;//偏心率
	double be=ae-ae*alphae;//地球短半轴
	double wed=7.292115e-5;//地球转率
        phi0=atan(pow(be/ae,2)*tan(B0));//B0:发射点纬度
	G_sTowe= L_('z',phi0)*L_('y',A0);//A0:发射点经度
	G_sTog=(~G_sTowe)*L_('x',wed*time)*G_sTowe;//发射惯性系到到发射系。time：导弹飞行时间
	gToG_s=G_sTog;//发射系到发射惯性系

	CVector a,b;
	a.x=1;
	a.y=2;
	a.z=3;
	b=EtoD*a;//例子：a为地心系向量。b即为发射系。



}