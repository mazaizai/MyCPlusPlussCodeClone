#include "Earth.h"
#include <string>
#include <math.h>
#include <iostream>
using namespace std;
Earth::Earth(){
	//Type = "WGS84";
    //default
	ae=6378137;//地球半径长半轴
	miu=3.986005e14;//地球引力常量
	alphae=1/298.257;//偏心率
    e2=pow(alphae,2);//第二偏心率
	be=ae-ae*alphae;//地球短半轴
	wed=7.292115e-5;//地球转率
    J2=1.08263e-3;

};
Earth::~Earth() {
};


Earth::Earth(const string& s){
    if (s.compare("WGS84")){
        ae=6378137;//地球半径长半轴
        miu = 3.986005e14;     //地球引力常量
        alphae = 1 / 298.257;  //偏心率
        e2=pow(alphae,2);//第二偏心率
        be = ae - ae * alphae; //地球短半轴
        wed = 7.292115e-5;     //地球转率
        J2 = 1.08263e-3;       //动力形状因子
      }
    else if(s.compare ("CGC2000")){
        ae=6378137;//地球半径长半轴  
        miu = 3.986004418e14;     //地球引力常量
        alphae = 1/298.257222101;  //偏心率
        e2=pow(alphae,2);//第二偏心率
        be = ae - ae * alphae; //地球短半轴
        wed = 7.292115e-5;     //地球转率
        J2 = 1.08262983e-3;   //动力形状因子
        }
    else if (s.compare("sphere")){
        ae=6378137;//地球半径长半轴  
        miu = 3.986004418e14;     //地球引力常量
        alphae = 1/298.257222101;  //偏心率
        e2=pow(alphae,2);//第二偏心率
        be = ae - ae * alphae; //地球短半轴
        wed = 7.292115e-5;     //地球转率
        J2 = 1.08262983e-3;   //动力形状因子
    }
    else
    {
        cout<<"please input the right type for earth model"<<endl; 
        ae=6378137;//地球半径长半轴
        miu = 3.986005e14;     //地球引力常量
        alphae = 1 / 298.257;  //偏心率
        e2=pow(alphae,2);//第二偏心率
        be = ae - ae * alphae; //地球短半轴
        wed = 7.292115e-5;     //地球转率
        J2 = 1.08263e-3;
    }
}