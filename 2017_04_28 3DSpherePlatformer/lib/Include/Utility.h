#pragma once

#define _PI 3.14159265358979323846
#define _2PI (_2PI*2)
#define _PI_OVER_180 0.01745329		// 1 radian
#define _180_OVER_PI 57.29578		 

float degToRad(float degrees);
float radToDeg(float radians);
float LinearHalf(float x);

//Assembly fsqrt 2 - Fastest square root method: https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
///DO NOT CHANGE DOUBLE TO FLOAT, ERRORS WILL OCCUR!
double inline __declspec (naked) __fastcall sqrt14(double n)
{
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}