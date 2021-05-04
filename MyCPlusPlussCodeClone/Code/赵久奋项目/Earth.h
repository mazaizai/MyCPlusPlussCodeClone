#ifndef  EARTH_H
#define EARTH_H

#include <string>
using namespace std;
class Earth{
public:
	Earth();
	Earth(const string&);
    ~Earth();
   //void Updata(string& );
  //string Type;//参数类型
   //earth parameter
   	double ae;//地球半径长半轴
    double be;//地球短半轴
    double e2;//第二偏心率
	double miu;//地球引力常量
	double alphae;//偏心率
	double wed;//地球转率
    double J2; //动力形状因子
};

#endif