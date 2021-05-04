//
//  Coordinate.cpp
//  
//
//  Created by 	P.H.D Ma on May/2/2021.
//  Copyright @ MHBN. All rights reserved.
//
#include "Vector.h"
#include "Matrix.h"
#include "Earth.h"
#include "Coordinate.h"
#include <iostream>
using namespace std;
/*
	��������ϵ  Launch Coordinate System, Launch
	�����������ϵ Launch Inertial Coordinate System, INLaunch
	���Ĺ�������ϵ  Earth-Centered Earth-Fixed System, ECEF
	��������ϵ   Geographic Coordinate System, GeoCS
	��������ϵ  Missile-Body Coordinate System, MBodyCS
	����������ϵ  North-East-Up Coordinate System, ENU
	����������ϵ  North-East-Down Corrdinate System,NED
*/

const double  pi=3.1415926;
Coordinate::Coordinate(){
}

Coordinate::~Coordinate(){
	if (Earth_para != NULL) {
		delete Earth_para;
	}

}

//��������ϵת���ĵع�����ϵ
void Coordinate::LaunchToECEF(const double& B0,const double& L0,const double& Height0,const double& AoT, const string& EarthType,const CVector& P_Launch,CVector& P_ECEF){  //��������ϵ��ECEF
//Input �����γ�ȣ����ȣ������ȣ����ȣ����̣߳�m������׼���򣨻��ȣ����������ͣ�string�� ��Ŀ����ڷ�������ϵ���꣨m��3*1
//Output Ŀ�����ECEF�е����� 
	CMatrix EtoD = MtxHld.L_('y', -(pi / 2 + AoT))*MtxHld.L_('x', B0)*MtxHld.L_('z', -(pi / 2 - L0));  //����ϵ������ϵת������
    CVector Point_ECEF;
	/* ��ʱע��
    GeoCSToECEF(B0,L0,Height0,EarthType,Point_ECEF); //���㷢�����ECEF�е�λ������
	P_ECEF=EtoD*P_Launch+Point_ECEF;  //
	*/
	P_ECEF = EtoD * P_Launch;
}

//���ĵع�����ϵת��������ϵ
void Coordinate::ECEFToLaunch(const double& B0,const  double& L0,const  double& Height0,const double& AoT,const string& EarthType,const  CVector& P_ECEF,CVector& P_Launch){   //ECEF����������ϵ
//Input �����γ�ȣ����ȣ������ȣ����ȣ����̣߳�m������׼���򣨻��ȣ����������ͣ�string�� ��Ŀ�����ECEF�����꣨m��3*1
//Output Ŀ����ڷ�������ϵ�е����� 

	CMatrix DtoE = MtxHld.L_('z', -(pi / 2 - L0))*MtxHld.L_('x', B0)*MtxHld.L_('y', -(pi / 2 + AoT));  //����ϵ������ϵת������
	CVector Point_ECEF;//�������ECEF�е���������
	
	GeoCSToECEF(B0,L0,Height0,EarthType,Point_ECEF); //���㷢�����ECEF�е�λ������
	P_Launch=DtoE*(P_ECEF-Point_ECEF);//����Ŀ����ڷ�������ϵ������
	
	P_Launch = DtoE * P_ECEF;
}

//��������ϵ��ECCF��ת��
void Coordinate::GeoCSToECEF(const double& B0,const double& L0,const  double& Height0,const string& EarthType,CVector& P_ecef){
 //Input    point�ľ������ȣ���γ�����ȣ����̣߳�m������������
 //Output   point��ECEF�е�����
	//���������ֵ
	if (Earth_para != NULL) {
		delete Earth_para;
	}
	Earth_para = new Earth(EarthType);
  double W = sqrt(1-pow(Earth_para->alphae*sin(B0),2));
  double N = Earth_para->ae/W;
   P_ecef.x = (N+Height0)*cos(B0)*cos(L0);
   P_ecef.y = (N+Height0)*cos(B0)*sin(L0);
   P_ecef.z = (N*(1-Earth_para->e2) + Height0)*sin(B0);
}

//ECEF���������ϵ��ת��
void Coordinate::ECEFToGeoCS(const CVector& P_ecef,const string& EarthType,double& B0,double& L0,double& Height0){
 //Input    point�ľ������ȣ���γ�����ȣ����̣߳�m������������
 //Output   point��ECEF�е�����

//���������ֵ
	if (Earth_para != NULL) {
		delete Earth_para;
	}
	Earth_para = new Earth(EarthType);

 //γ�ȼ���
if (P_ecef.x==0&&P_ecef.y>=0){
	L0 = pi/2;
} 
else if (P_ecef.x==0&&P_ecef.y<=0){
	L0 = -pi/2;
}
else
{
	L0 = atan(P_ecef.y/P_ecef.x);
}
	double p = sqrt(P_ecef.x*P_ecef.x + P_ecef.y*P_ecef.y);
    double p2 = p*p;
    double e4 = pow(Earth_para->e2,2);
    double a2 = pow(Earth_para->alphae,2);
    double zi = (1-Earth_para->e2)*pow(P_ecef.z,2)/a2;
    double rho = (p2/a2 + zi - e4)/6.0;
    double rho2 = rho*rho;
    double rho3 = rho*rho2;
    double s = 0.25*e4*zi*p2/a2;
    double t = pow(rho3 + s + sqrt(s*(s+2.0*rho3)), 1.0/3.0);
    double u = rho + t + rho2 / t;
    double v = sqrt(u*u + e4*zi);
    double w = Earth_para->e2*(u + v - zi)/(2*v);
    double k = 1 + Earth_para->e2*(sqrt(u+v+w*w) + w)/(u+v);
    double Zk = P_ecef.z*k;
     B0 = atan2(k*P_ecef.z, p); //γ��
     Height0 = sqrt(p2 + Zk*Zk)*(1.0/k - (1-Earth_para->e2))/Earth_para->e2; //����

}



//��������ϵת���Է�������ϵ
void Coordinate::LaunchToINLaunch(const double& B0,const double& L0,const double& Height0,const double& AoT,const double& time, const string& EarthType,const CVector& P_Launch,CVector& P_INLaunch){
    //Input ����㾭γ�ȣ����ȣ��̣߳�m�� ��׼���򣨻��ȣ� ����ʱ�䣨s��  �������ͣ�string�� ����ϵ��λ��
	//OutPut  �������ϵ��λ��
   //���������ֵ
	if (Earth_para != NULL) {
		delete Earth_para;
	}
	Earth_para = new Earth(EarthType);
   /* 
	double  phi0=atan(pow(Earth_para.be/Earth_para.alphae,2)*tan(B0));//�������γ��
	CMatrix G_sTowe= L_('z',phi0)*L_('y',L0);//
	CMatrix G_sTog=(~G_sTowe)*L_('x',Earth_para.wed*time)*G_sTowe;//����ϵ���������ϵת������
	*/

	//�������µķ���㾭γ��
	double B1 = B0;
	double L1 = L0 + Earth_para->wed*time;
	double Height1 = Height0;
	CVector P_ECEF; //ECEF�µ�����
    LaunchToECEF(B1,L1,Height1,AoT,EarthType,P_Launch,P_ECEF);  //��������ϵ��ECEF
    ECEFToLaunch(B0,L0,Height0,AoT,EarthType,P_ECEF,P_INLaunch);  //ECEFת�����������ϵ

}

//���Է�������ϵת��������ϵ
void Coordinate::INLaunchToLaunch(const double& B0,const double& L0,const double& Height0,const double& AoT,const double& time, const string& EarthType,CVector& P_INLaunch, CVector& P_Launch){
    //Input ����㾭γ�ȣ����ȣ��̣߳�m�� ��׼���򣨻��ȣ� ����ʱ�䣨s��  �������ͣ�string��  �������ϵ��λ�� 
	//OutPut  ����ϵ��λ��
    
   /* Earth Earth_para(EarthType);
	double  phi0=atan(pow(Earth_para.be/Earth_para.alphae,2)*tan(B0));//�������γ��
	CMatrix G_sTowe= L_('z',phi0)*L_('y',L0);//
	CMatrix G_sTog=(~G_sTowe)*L_('x',Earth_para.wed*time)*G_sTowe;//����ϵ���������ϵת������
	*/
	//�������
	Earth Earth_para(EarthType);
	//�������µķ���㾭γ��
	double B1 = B0;
	double L1 = L0 + Earth_para.wed*time;
	double Height1 = Height0;
	CVector P_ECEF; //ECEF������
    LaunchToECEF(B0,L0,Height1,AoT,EarthType,P_INLaunch,P_ECEF);  //�������ϵ��ECEF
    ECEFToLaunch(B1,L1,Height0,AoT,EarthType,P_ECEF,P_Launch);  //ECEFת��������ϵ

}

//��������ϵת��������ϵ
void Coordinate::LaunchToMBodyCS(const double& phi,const double& psi,const double& gama,const CVector& P_launch,CVector&P_body){   //��������ϵ����������ϵ
	//Input  ������̬ ������phi  ƫ����psi  ������gama  Ŀ����ڷ���ϵ������P_launch
	//Output  ����ϵ���� P_body
	CMatrix DtoT= MtxHld.L_('x', gama)*MtxHld.L_('y', psi)*MtxHld.L_('z', phi);//����ϵ������ϵת������
    P_body=DtoT*P_launch;
}

//��������ϵת��������ϵ
void Coordinate::MBodyCSToLaunch(const double& phi,const double& psi,const double& gama,const CVector&P_body, CVector& P_launch){   //��������ϵ����������ϵ
	//Input   ������̬ ������phi  ƫ����psi  ������gama   ����ϵ���� P_body 
	//Output  Ŀ����ڷ���ϵ������P_launch
	CMatrix TtoD= MtxHld.L_('z', phi)*MtxHld.L_('y', psi)*MtxHld.L_('x', gama);//����ϵ������ϵת������
    P_launch= TtoD*P_body;
}

//����������ϵת����������ϵ
void Coordinate::NEDtoENU(const CVector& P_ned, CVector& P_enu){
   P_enu = CVector(P_ned(1), P_ned(0), -P_ned(2));
}

//����������ϵת����������ϵ
void Coordinate::ENUtoNED(const CVector& P_enu,CVector& P_ned){
    P_ned = CVector(P_enu(1), P_enu(0), -P_enu(2));
}

//����������ϵת�����ĵع�����ϵ
void Coordinate::ENUToECEF(const double&B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_enu,CVector& P_ecef){

	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef);//�������ϵ����γ�ߣ���ECCF��ת��
    CMatrix UToF= MtxHld.L_('x',pi/2-B0)*MtxHld.L_('z',-pi/2-L0); //ת������
    P_ecef=UToF*P_enu+P_ecef;
}

//���ĵع�����ϵת����������ϵ
void Coordinate::ECEFToENU(const double&B0,const double&L0,const double&Height0,const string& EarthType, const CVector& P_ecef,CVector& P_enu){
    CVector P_ecef_0;//վ����ECEF������
	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef_0);//�������ϵ����γ�ߣ���ECCF��ת��
    CMatrix FToU=MtxHld.L_('z',pi/2+L0)*MtxHld.L_('x',B0-pi/2); //ת������
	P_enu=FToU*(P_ecef-P_ecef_0);
}

//����������ϵת���ĵع�����ϵ
void Coordinate::NEDToECEF(const double&B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_ned, CVector& P_ecef){
	//δ��֤
	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef);//�������ϵ����γ�ߣ���ECCF��ת��
    CMatrix NToF= MtxHld.L_('y',pi/2+B0)*MtxHld.L_('z',-L0); //ת������
    P_ecef=NToF*P_ned+P_ecef;
}

//���ĵع�����ϵת����������ϵ
void Coordinate::ECEFToNED(const double&B0,const double&L0,const double&Height0,const string& EarthType,const CVector& P_ecef, CVector& P_ned){
	
	CVector P_ecef_0;//վ����ECEF������
	GeoCSToECEF(B0,L0,Height0,EarthType,P_ecef_0);//�������ϵ����γ�ߣ���ECCF��ת��
	CMatrix FToN= MtxHld.L_('z',L0)*MtxHld.L_('y',-pi/2-B0); //ת������
	P_ned=FToN*(P_ecef-P_ecef_0);
}

