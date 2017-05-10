#pragma once

#define _PI 3.14159265358979323846
#define _2PI (_2PI*2)
#define _PI_OVER_180 0.01745329		// 1 radian
#define _180_OVER_PI 57.29578		 

float degToRad(float degrees);
float radToDeg(float radians);
float LinearHalf(float x);

#ifndef SQRTFUNC
#define SQRTFUNC
namespace shash {

	double inline __declspec (naked) __fastcall sqrt(double n) {
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}

#define MINDIFF 2.25e-308

	float sqrt(float square) {
		float root = square / 3, last, diff = 1;
		if (square <= 0) return 0;
		do {
			last = root;
			root = (root + square / root) / 2;
			diff = root - last;
		} while (diff > MINDIFF || diff < -MINDIFF);
		return root;
	}

}

#endif