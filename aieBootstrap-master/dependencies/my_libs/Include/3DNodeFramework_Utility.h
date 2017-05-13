#pragma once
#define UP_NORMAL				Vector4<float>(0, 1, 0, 0)

#define DEFAULT_ORIGIN3D		glm::vec3(0.f, 0.f, 0.f)
#define DEFAULT_ORIGIN2D		glm::vec2(0.f, 0.f)

#define VERTEX_RADIUS			5.f
#define VERTEX_COLOR			glm::vec4(1.f, 0.f, 0.f, 1.f)
#define	VERTEX_SUBDIVISIONS		10

#define PLANE_COLOR				glm::vec4(0.f, 1.0f, 0.f, 1.f)

enum eCoordType {LOCAL, WORLD};								/* Which coordinates to consider for a node.*/
enum eContainmentType {DISJOINT, INTERSECTS, CONTAINS};		/*DISJOINT = No overlap, INTERSECTS = Overlap, CONTAINS = Inside boundary*/ 