#pragma once

/*
MIT License
Copyright © 2006 The Mono.Xna Team

All rights reserved.

Authors:
Olivier Dufour (Duff)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "3DSphere_Utility.h"

class XNABoundingBox
{
public:
	XNABoundingBox() : Min(Vector3<float>{0, 0, 0}), Max(Vector3<float>(0, 0, 0)) {}   //Covers no area by default
	XNABoundingBox(Vector3<float> a_min, Vector3<float> a_max) : Min(a_min), Max(a_max) {} //Face independent
	XNABoundingBox(Vector3<float> a_pt[8]); //Construct from list of vertices, face dependent
	~XNABoundingBox();

#pragma region Variables
	// Face independent
	Vector3<float> Max;        //Top left vertice
	Vector3<float> Min;        //Bottom right vertice

	float Width;
	float Height;
	float Depth;
	// Face dependent
	union {
		struct {
			Vector3<float>
				TopMax, TopMin,
				LeftMax, LeftMin,
				RightMax, RightMin,
				FrontMax, FrontMin,
				BackMax, BackMin,
				BottomMax, BottomMin;
		};
		struct { Vector3<float> v[12]; };         //List of collision vertex points
	};
#pragma endregion

#pragma region Methods
	//static ContainmentType Collision(Vector3<float> a_maxA, Vector3<float> a_minA, Vector3<float> a_maxB, Vector3<float> a_minB);

	ContainmentType Collision(XNABoundingBox a_box);
	ContainmentType Collision(Vector3<float> a_pt);
	// ContainmentType Contains(XNABoundingSphere sphere);
#pragma endregion
private:

};

