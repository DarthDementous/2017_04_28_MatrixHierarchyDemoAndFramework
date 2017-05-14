#include "BoundingBoxNode.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <MathLib_Utility.h>

BoundingBoxNode::~BoundingBoxNode()
{
}

void BoundingBoxNode::CalculateExtents()
{
	// Get length inbetween the two points to form the dimensions
	float width		= m_max.x - m_min.x;
	float height	= m_max.y - m_min.y;
	float depth		= m_max.z - m_min.z;

	m_extents = Vector4<float>(width, height, depth, 0);
}

void BoundingBoxNode::CalculateMinMax()
{
	// Get the min and max by minusing and adding half extents from/to current world position
	Vector4<float> position = GetTransform(WORLD).getTranslation();

	m_max = position - m_extents / 2;
	m_min = position + m_extents / 2;
}

std::vector<Vector4<float>> BoundingBoxNode::CalculateVertices()
{
	// Use min and max points to create vertices and transform them by our transformMatrix (OBB)
	std::vector<Vector4<float>> vertices;
	
	vertices[0] = m_localTransform * Vector4<float>(m_min.x, m_max.y, m_max.z, 0);
	
	vertices[1] = m_max; // Already transformed by update
	
	vertices[2] = m_localTransform * Vector4<float>(m_min.x, m_max.y, m_min.z, 0);
	
	vertices[3] = m_localTransform * Vector4<float>(m_max.x, m_max.y, m_min.z, 0);
	
	vertices[4] = m_localTransform * Vector4<float>(m_min.x, m_min.y, m_max.z, 0);

	vertices[5] = m_localTransform * Vector4<float>(m_max.x, m_min.y, m_max.z, 0);

	vertices[6] = m_min; // Already transformed by update

	vertices[7] = m_localTransform * Vector4<float>(m_max.x, m_min.y, m_min.z, 0);

	// Debug draw vertices as spheres
#ifdef _DEBUG
	for (Vector4<float> vertex : vertices) {
		// Gizmos requires a pointer to the transformation matrix
		glm::mat4x4 transformMatrixPtr = glm::mat4x4(Matrix4<float>::createTranslation(vertex.x, vertex.y, vertex.z).convertToOpenGL());

		Gizmos::addSphere(DEFAULT_ORIGIN3D, VERTEX_RADIUS, VERTEX_SUBDIVISIONS, VERTEX_SUBDIVISIONS, VERTEX_COLOR, &transformMatrixPtr);
	}
#endif

	return vertices;
}

std::vector<Vector4<float>> BoundingBoxNode::CalculateFacePlanes()
{
	std::vector<Vector4<float>> vertices = CalculateVertices();
	std::vector<Vector4<float>> faceNormals;

	/// Since we're creating a line from the centre of the object to the centre of the face we assume that the starting point is (0, 0) and thus the normal is that centre face point
	// Top face normal
	faceNormals.push_back(LinearHalf(vertices[0], vertices[3]));

	// Bottom face normal
	faceNormals.push_back(LinearHalf(vertices[5], vertices[8]));

	// Left face normal
	faceNormals.push_back(LinearHalf(vertices[0], vertices[7]));

	// Right face normal
	faceNormals.push_back(LinearHalf(vertices[2], vertices[8]));

	// Front face normal
	faceNormals.push_back(LinearHalf(vertices[3], vertices[8]));

	// Back face normal
	faceNormals.push_back(LinearHalf(vertices[0], vertices[6]));

	// Debug draw planes as 2d bounding boxes
#ifdef _DEBUG
	for (Vector4<float> planePos : faceNormals) {
		// Gizmos requires a pointer to the transformation matrix
		glm::mat4x4 transformMatrixPtr = glm::mat4x4(Matrix4<float>::createTranslation(planePos.x, planePos.y, planePos.z).convertToOpenGL());

		Gizmos::add2DAABB(DEFAULT_ORIGIN2D, glm::vec2(m_extents.x, m_extents.y), PLANE_COLOR, &transformMatrixPtr);
	}
#endif

	return faceNormals;

}

///Basic collision code sourced from XNA Framework BoundingBox.cs:
///https://searchcode.com/file/8270413/MonoGame.Framework/BoundingBox.cs

eContainmentType BoundingBoxNode::Collision(BoundingBoxNode *a_bb)
{
	// test if all the corners are on the same side of a face by just checking min and max
	if (a_bb->m_max.x < m_min.x
		|| a_bb->m_min.x > m_max.x
		|| a_bb->m_max.y < m_min.y
		|| a_bb->m_min.y > m_max.y
		|| a_bb->m_max.z < m_min.z
		|| a_bb->m_min.z > m_max.z)
		return DISJOINT;

	// Check if this m_min and m_max encapsulates the bounding a_bb
	if (a_bb->m_min.x >= m_min.x
		&& a_bb->m_max.x <= m_max.x
		&& a_bb->m_min.y >= m_min.y
		&& a_bb->m_max.y <= m_max.y
		&& a_bb->m_min.z >= m_min.z
		&& a_bb->m_max.z <= m_max.z)
		return CONTAINS;

	// Only possible outcome is intersection
	return INTERSECTS;
}

eContainmentType BoundingBoxNode::Collision(const Vector4<float> &a_pt)
{
	//first we get if point is out of box
	if (a_pt.x < m_min.x
		|| a_pt.x > m_max.x
		|| a_pt.y < m_min.y
		|| a_pt.y > m_max.y
		|| a_pt.z < m_min.z
		|| a_pt.z > m_max.z)
	{
		return DISJOINT;
	} //or if a_pt is on box because coordonate of a_pt is lesser or equal
	else if (a_pt.x == m_min.x
		|| a_pt.x == m_max.x
		|| a_pt.y == m_min.y
		|| a_pt.y == m_max.y
		|| a_pt.z == m_min.z
		|| a_pt.z == m_max.z)
		return INTERSECTS;
	else
		return CONTAINS;
}

Vector4<float> BoundingBoxNode::AdvancedIntersect(BoundingBoxNode *a_bb)
{
	// Assume that min/max collision checks have already been performed and collision is inevitable
	std::vector<Vector4<float>> normals = a_bb->CalculateFacePlanes();

	// Use point collision detection on each normal to check for collision (not disjoint)
	for (Vector4<float> normal : normals) {

		if (Collision(normal) != DISJOINT) {
			return normal;						// Return normal we've collided with for use in physics calculations (e.g. ReflectVelocity)
		}

	}

	return Vector4<float>(0, 0, 0, 0);			// All code-paths must return a value, if this function is used only when a collision is certain this will never be returned.
}

void BoundingBoxNode::Update()
{
	// Mark max and min as points instead of vectors
	m_max.w = 1;
	m_min.w = 1;

	// Transform min/max every frame (basic box collision level)
	m_max = m_localTransform * m_max;
	m_min = m_localTransform * m_min;
}

void BoundingBoxNode::Render()
{
#ifdef _DEBUG
	/// Do conversions to openGL to use Gizmos
	// Gizmos requires a pointer to the transformation matrix
	glm::mat4x4 transformMatrixPtr = glm::mat4x4(m_localTransform.convertToOpenGL());
	glm::vec3 center = glm::vec3(m_origin.x, m_origin.y, m_origin.z);
	glm::vec3 extents = glm::vec3(m_extents.x, m_extents.y, m_extents.z);
	glm::vec4 color = glm::vec4(m_color.x, m_color.y, m_color.z, m_color.w);

	Gizmos::addAABB(center, extents, color, &transformMatrixPtr);
#endif

}