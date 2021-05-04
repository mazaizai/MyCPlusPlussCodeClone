#include "Matrix.h"
#include "Vector.h"
#include <math.h>
#pragma once

class zuobiaoxi
{
public:
	zuobiaoxi(void);
public:
	~zuobiaoxi(void);
public:
	void fun_Init();
public:
	CMatrix G_sTowe,G_sTog,gToG_s,TtoD,DtoT,EtoD,DtoE;
};
