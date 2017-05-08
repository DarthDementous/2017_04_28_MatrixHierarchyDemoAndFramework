#include "XNABoundingBox.h"

XNABoundingBox::XNABoundingBox(Vector3<float> a_pt[8])
{
	// Set up min points and max points for whole box and individual faces
	Max = a_pt[0], Min = a_pt[7];
	TopMax = Max, TopMin = a_pt[3];
	LeftMax = TopMax, LeftMin = a_pt[6];
	RightMax = TopMin, RightMin = a_pt[5];
	FrontMax = a_pt[2], FrontMin = Min;
	BackMax = Max, BackMin = RightMin;
	BottomMax = a_pt[4], BottomMin = Min;

	Width = Min.x - Max.x;
	Height = Min.y - Max.y;
	Depth = Min.z - Max.z;
}


XNABoundingBox::~XNABoundingBox()
{
}

/*
ContainmentType XNABoundingBox::Collision(Vector3<float> a_maxA, Vector3<float> a_minA, Vector3<float> a_maxB, Vector3<float> a_minB)
{
	// Check if the colliding box's vertices are disjointed (on the same side of our face)
	if (a_maxB.x < a_minA.x
		|| a_minB.x > a_maxA.x
		|| a_maxB.y < a_minA.y
		|| a_minB.y > a_maxA.y
		|| a_maxB.z < a_minA.z
		|| a_minB.z > a_maxA.z)
		return DISJOINT;
	// Check if the colliding box's vertices are inside our box
	if (a_minB.x >= a_minA.x
		&& a_maxB.x <= a_maxA.x
		&& a_minB.y >= a_minA.y
		&& a_maxB.y <= a_maxA.y
		&& a_minB.z >= a_minA.z
		&& a_maxB.z <= a_maxA.z)
		return CONTAIN;
	// Only possible outcome is that the boxes are intersecting
	return INTERSECTION;
}
*/

ContainmentType XNABoundingBox::Collision(XNABoundingBox a_box) {

}

ContainmentType XNABoundingBox::Collision(Vector3<float> a_pt) {
	if ()
}

