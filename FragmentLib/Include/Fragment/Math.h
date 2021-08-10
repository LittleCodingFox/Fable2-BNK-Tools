#ifndef FRAGMENTLIB_MATH_H
#define FRAGMENTLIB_MATH_H
namespace Fragment
{
	/*!
		\addtogroup mathservices Math Services
		@{
	*/

	//!PI Constant
#define FR_PI 3.14159265358979323846264338327950288419716939937510
	//!Epsilon Constant
#define FR_EPSILON 0.000001
	//!FRRAD2DEG
#define FRRAD2DEG(val) (((val) * 180.0f) / 3.14f)
	//!FRDEG2RAD
#define FRDEG2RAD(val) (((val) * 3.14f) / 180.0f)

	class vec3;
	class vec4;
	//!mat4 is a 4x4 Matrix class
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 17-11-2008
	*/
	class mat4
	{
	public:
		float m[4][4];
		mat4();
		mat4(const mat4 &m);
		mat4 operator*(const mat4 &m);

		//!Determinant will calculate this matrix's determinant
		float Determinant();

		//!Identity resets this matrix to an identity matrix
		void Identity();

		//!Transpose returns the transpose matrix of this matrix
		void Transpose();

		//!Inverse will invert the matrix
		bool Inverse();

		//!Scale will create a scale matrix
		/*!
			\param Scales are the scale values
		*/
		void Scale(vec4 Scales);

		//!Rotate will create a rotation matrix from 3 angles
		/*!
			\param Angles are the rotation values
		*/
		void Rotate(vec3 Angles);

		//!Translate will create a translation matrix
		/*!
			\param v is the translation vector
		*/
		void Translate(vec4 v);

		//!PerspectiveMatrixLH will create a Left-Handed perspective matrix
		/*!
			\param FOV is the viewport's Field Of View in Radians
			\param AspectRatio is the viewport's Aspect Ratio
			\param zNear is the viewport's zNear value
			\param zFar is the viewport's zFar value
		*/
		void PerspectiveMatrixLH(float FOV, float AspectRatio, float zNear, float zFar);

		//!PerspectiveMatrixRH will create a Right-Handed perspective matrix
		/*!
			\param FOV is the viewport's Field Of View in Radians
			\param AspectRatio is the viewport's Aspect Ratio
			\param zNear is the viewport's zNear value
			\param zFar is the viewport's zFar value
		*/
		void PerspectiveMatrixRH(float FOV, float AspectRatio, float zNear, float zFar);

		//!LookAtMatrixLH will create a Left-Handed Look At matrix
		/*!
			\param Position is the viewer's position
			\param EyePosition is the position the viewer is looking at
			\param UpVector is a vector showing where up is
		*/
		void LookAtMatrixLH(vec3 Position, vec3 EyePosition, vec3 UpVector);

		//!LookAtMatrixRH will create a Right-Handed Look At matrix
		/*!
			\param Position is the viewer's position
			\param EyePosition is the position the viewer is looking at
			\param UpVector is a vector showing where up is
		*/
		void LookAtMatrixRH(vec3 Position, vec3 EyePosition, vec3 UpVector);

		//!OrthoMatrixLH will create a Left-Handed Orthographic matrix
		/*!
			\param Left is the minimum x-value
			\param Right is the maximum x-value
			\param Bottom is the minimum y-value
			\param Top is the maximum y-value
			\param zNear is the viewport's zNear value
			\param zFar is the viewport's zFar value
		*/
		void OrthoMatrixLH(float Left, float Right, float Bottom, float Top, float zNear, float zFar);

		//!OrthoMatrixRH will create a Right-Handed Orthographic matrix
		/*!
			\param Left is the minimum x-value
			\param Right is the maximum x-value
			\param Bottom is the minimum y-value
			\param Top is the maximum y-value
			\param zNear is the viewport's zNear value
			\param zFar is the viewport's zFar value
		*/
		void OrthoMatrixRH(float Left, float Right, float Bottom, float Top, float zNear, float zFar);

		//!ProjectPoint will project a Point from 3D Space to 2D Space
		/*!
			\param Point is the point to project
			\param World is the world matrix
			\param View is the view matrix
			\param Projection is the projection matrix
			\param Viewport is the Viewport to project to in the form of (startx, starty, width, height)
			\note If you use OpenGL, pass View as mat4(), which will default to the Identity Matrix,
			and pass your current ModelView matrix as World
		*/
		vec4 ProjectPoint(vec4 Point, mat4 World, mat4 View, mat4 Projection, vec4 Viewport);

		//!UnProjectPoint will unproject a Point from 2D Space to 3D Space
		/*!
			\param Point is the point to unproject (z axis should be between 0 and 1, 
			0 for near zNear, 1 for near zFar)
			\param World is the world matrix
			\param View is the view matrix
			\param Projection is the projection matrix
			\param Viewport is the Viewport to project to in the form of (startx, starty, width, height)
			\note If you use OpenGL, pass View as mat4(), which will default to the Identity Matrix,
			and pass your current ModelView matrix as World
		*/
		vec4 UnProjectPoint(vec3 Point, mat4 World, mat4 View, mat4 Projection, vec4 Viewport);

		//!SingleIndex will return the reference to an element of the matrix by a single index
		/*!
			return the reference to an element of the matrix using only one index instead of the 
			usual two indexes
			\param Index is a number between 0 and 15
		*/
		float &SingleIndex(unsigned short Index);
	};

	//!vec2 is a 2D vector class
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 30-03-2008
	*/
	class vec2
	{
	public:
		float x, y;
		vec2();
		vec2(float x, float y);
		vec2(const vec2 &o);

		vec2 operator+(const vec2 &o);
		vec2 operator+(float f);

		vec2 operator-(const vec2 &o);
		vec2 operator-(float f);

		vec2 operator*(const vec2 &o);
		vec2 operator*(float f);

		vec2 operator/(const vec2 &o);
		vec2 operator/(float f);

		vec2 operator+=(const vec2 &o);
		vec2 operator+=(float f);

		vec2 operator-=(const vec2 &o);
		vec2 operator-=(float f);

		vec2 operator/=(const vec2 &o);
		vec2 operator/=(float f);

		vec2 operator*=(const vec2 &o);
		vec2 operator*=(float f);

		vec2 operator-();
		bool operator==(const vec2 &o);
		bool operator!=(const vec2 &o);

		//!Magnitude will calculate the magnitude of a vector
		float Magnitude();

		//!MagnitudeSquare will calculate the magnitude of a vector, squared
		float MagnitudeSquare();

		//!Normalized returns a vector that is unit-sized (normalized)
		vec2 Normalized();

		//!Normalize normalizes this vector (unit-size)
		void Normalize();

		//!Distance will return the distance between two vectors
		/*!
			\param o is another vector
		*/
		float Distance(vec2 o);

		//!Dot will return the dot product between two vectors
		/*!
			\param o is another vector
		*/
		float Dot(vec2 o);

		//!Parallel will return a parallel vector to this vector
		vec2 Parallel();

		//!Perpendicular will return a perpendicular vector to this vector
		vec2 Perpendicular();
	};

	//!vec3 is a 3D vector class
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 30-03-2008
	*/
	class vec3
	{
	public:
		float x, y, z;
		vec3();
		vec3(float x, float y, float z);
		vec3(const vec3 &o);
		vec3(vec2 v);
		vec3(vec2 xy, float z);
		vec3(float x, vec2 yz);

		vec3 operator+(const vec3 &o);
		vec3 operator+(float f);

		vec3 operator-(const vec3 &o);
		vec3 operator-(float f);

		vec3 operator*(const vec3 &o);
		vec3 operator*(float f);
		vec3 operator*(const mat4 &m);

		vec3 operator/(const vec3 &o);
		vec3 operator/(float f);

		vec3 operator+=(const vec3 &o);
		vec3 operator+=(float f);

		vec3 operator-=(const vec3 &o);
		vec3 operator-=(float f);

		vec3 operator/=(const vec3 &o);
		vec3 operator/=(float f);

		vec3 operator*=(const vec3 &o);
		vec3 operator*=(float f);

		bool operator==(const vec3 &o);
		bool operator!=(const vec3 &o);

		vec3 operator-();

		//!Magnitude will calculate the magnitude of a vector
		float Magnitude();

		//!MagnitudeSquare will calculate the magnitude of a vector, squared
		float MagnitudeSquare();

		//!Normalized returns a vector that is unit-sized (normalized)
		vec3 Normalized();

		//!Normalize normalizes this vector (unit-size)
		void Normalize();

		//!Distance will return the distance between two vectors
		/*!
			\param o is another vector
		*/
		float Distance(vec3 o);

		//!Dot will return the dot product between two vectors
		/*!
			\param o is another vector
		*/
		float Dot(vec3 o);

		//!Parallel will return a parallel vector to this vector
		vec3 Parallel();

		//!Perpendicular will return a perpendicular vector to this vector
		vec3 Perpendicular();

		//!Cross will return the cross product of a vector
		/*!
			\param o is another vector
		*/
		vec3 Cross(vec3 o);

		//!NormalTri will calculate the normal of a triangle
		/*!
			\param v1 is the first vertex of the triangle
			\param v2 is the second vertex of the triangle
			\param v3 is the third vertex of the triangle
		*/
		void NormalTri(vec3 v1, vec3 v2, vec3 v3);
	};

	//!vec4 is a 4D vector class
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 30-03-2008
	*/
	class vec4
	{
	public:
		float x, y, z, w;
		vec4();
		vec4(float x, float y, float z);
		vec4(float x, float y, float z, float w);
		vec4(const vec4 &o);
		vec4(vec2 v);
		vec4(vec2 xy, float z, float w);
		vec4(float x, vec2 yz);
		vec4(float x, vec2 yz, float w);
		vec4(float x, float y, vec2 zw);
		vec4(vec2 xy, vec2 zw);
		vec4(vec3 v);
		vec4(vec3 xyz, float w);
		vec4(float x, vec3 yzw);

		vec4 operator+(const vec4 &o);
		vec4 operator+(float f);

		vec4 operator-(const vec4 &o);
		vec4 operator-(float f);

		vec4 operator*(const vec4 &o);
		vec4 operator*(float f);
		vec4 operator*(const mat4 &m);

		vec4 operator/(const vec4 &o);
		vec4 operator/(float f);

		vec4 operator+=(const vec4 &o);
		vec4 operator+=(float f);

		vec4 operator-=(const vec4 &o);
		vec4 operator-=(float f);

		vec4 operator/=(const vec4 &o);
		vec4 operator/=(float f);

		vec4 operator*=(const vec4 &o);
		vec4 operator*=(float f);

		bool operator==(const vec4 &o);
		bool operator!=(const vec4 &o);

		vec4 operator-();

		//!Magnitude will calculate the magnitude of a vector
		float Magnitude();

		//!MagnitudeSquare will calculate the magnitude of a vector, squared
		float MagnitudeSquare();

		//!Normalized returns a vector that is unit-sized (normalized)
		vec4 Normalized();

		//!Normalize normalizes this vector (unit-size)
		void Normalize();

		//!Distance will return the distance between two vectors
		/*!
			\param o is another vector
		*/
		float Distance(vec4 o);

		//!Dot will return the dot product between two vectors
		/*!
			\param o is another vector
		*/
		float Dot(vec4 o);

		//!Parallel will return a parallel vector to this vector
		vec4 Parallel();

		//!Perpendicular will return a perpendicular vector to this vector
		vec4 Perpendicular();

		//!Cross will return the cross product of a vector
		/*!
			\param o is another vector
		*/
		vec4 Cross(vec4 o);
	};

	enum PlanePointClassif //!Plane Point Classifications
	{
		FRP_BACK = 1, //!<Back of Plane
		FRP_FRONT, //!<Front of Plane
		FRP_ON_PLANE //!<On Plane
	};

	//!Plane is a plane class
	/*!
		\author Nuno Miguel Azevedo Lopes Da Silva
		\version 1.0
		\date 30-03-2008
	*/
	class Plane
	{
	public:
		float a, b, c, d;
		Plane();
		Plane(float a, float b, float c, float d);
		Plane(const Plane& o);
		//!FromTriangle will create a plane from a triangle
		/*!
			\param v1 is the first vertex of the triangle
			\param v2 is the second vertex of the triangle
			\param v3 is the third vertex of the triangle
		*/
		void FromTriangle(vec3 v1, vec3 v2, vec3 v3);
		//!ClassifyPoint will return the classification of a point
		/*!
			\param v is the point to classify
			\return one of FRP_*
		*/
		unsigned int ClassifyPoint(vec3 v);
	};

	//!Rect is a rectangle container
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 30-3-2008
	*/
	class Rect
	{
	public:
		float Left, Right, Top, Bottom;
		Rect();
		Rect(const Rect &Other);
		Rect(float Width, float Height);
		Rect(float Left, float Right, float Top, float Bottom);

		//!IsInside will test a point to see if it's inside this rect
		/*!
			\param Position is the position to test
		*/
		bool IsInside(vec2 Position);

		//!IsInside will test a point to see if it's inside this rect
		/*!
			\param Position is the position to test
		*/
		bool IsOutside(vec2 Position);
	};

	//!AABB is an Axis-Aligned Bounding-Box container
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 31-3-2008
	*/
	class AABB
	{
	public:
		vec3 min, max;
		AABB();
		AABB(const AABB &Other);
		AABB(vec3 min, vec3 max);

		//!Clear will reset this AABB
		void Clear();

		//!Calculate will calculate this AABB from a list of points
		/*!
			\param Points is a list of points to use to calculate this AABB
		*/
		void Calculate(Array<vec3> Points);

		//!Calculate will calculate this AABB from a point
		/*!
			\param Point is a point to use to calculate this AABB
			\note to be used together with Clear()
		*/
		void Calculate(vec3 Point);

		//!IsInside will test if a position is inside this AABB
		/*!
			\param Position is the point to test
		*/
		bool IsInside(vec3 Position) const;

		//!IsInside will test if a position is outside this AABB
		/*!
			\param Position is the point to test
		*/
		bool IsOutside(vec3 Position) const;

		//!Corners will return the 8 corners of the AABB
		void Corners(vec3 *Destination) const;
	};

	//!OBB is an Oriented Bounding-Box container
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 2.0
		\date 31-3-2008
	*/
	class OBB
	{
	public:
		AABB aabb;
		mat4 Transformation;
		OBB();
		OBB(const OBB &Other);
		OBB(AABB aabb, mat4 Transformation);

		//!Clear will reset this OBB
		void Clear();
		//!Calculate will calculate this OBB from a list of points
		/*!
			\param Points is a list of points to use to calculate this OBB
		*/
		void Calculate(Array<vec3> Points);

		//!Calculate will calculate this OBB from a point
		/*!
			\param Point is a point to use to calculate this OBB
			\note to be used together with Clear()
		*/
		void Calculate(vec3 Point);

		//!IsInside will test if a position is inside this OBB
		/*!
			\param Position is the point to test
		*/
		bool IsInside(vec3 Position) const;

		//!IsInside will test if a position is outside this OBB
		/*!
			\param Position is the point to test
		*/
		bool IsOutside(vec3 Position) const;
	};

	//!BoundingSphere is a Bounding Sphere container
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 07-02-2009
	*/
	class BoundingSphere
	{
	public:
		vec3 Center;
		float Radius;
		BoundingSphere();
		//!Calculate will calculate this Bounding Sphere's Center and Radius
		/*!
			\param Points is a list of Points to use to calculate the Bounding Sphere
		*/
		void Calculate(Array<vec3> Points);
		//!Intersects will check whether a Point is intersecting this Bounding Sphere
		/*!
			\param Point is the point to test
		*/
		bool Intersects(vec3 Point);
		//!Intersects will check whether a Bounding Sphere is intersecting this Bounding Sphere
		/*!
			\param Sphere is the Bounding Sphere to test
		*/
		bool Intersects(BoundingSphere Sphere);
	};

	//!Ray is a ray container
	/*!
		\author Nuno Miguel Azevedo Lopes da Silva
		\version 1.0
		\date 31-3-2008
	*/
	class Ray
	{
	public:
		vec3 Position, Direction;
		Ray();
		Ray(const Ray &Other);
		Ray(vec3 Position, vec3 Direction);
		//!IntersectsTriangle will test to see if a ray intersects a triangle
		/*!
			\param v1 is the first vertex of the triangle
			\param v2 is the second vertex of the triangle
			\param v3 is the third vertex of the triangle
			\param IntersectionPoint is the point at which the Ray intersects the Triangle
			\param t is a scalar that defines how far the Ray's origin must move to
			intersect the triangle
		*/
		bool IntersectsTriangle(vec3 v1, vec3 v2, vec3 v3,
			vec3 *IntersectionPoint = nullptr, float *t = nullptr);
		//!IntersectsPlane will test to see if a ray intersects a plane
		/*!
			\param p is the Plane to test
			\param IntersectionPoint is the point at which the plane is intersected by the ray
			\param t is a scalar that defines how far the Ray's origin must move to
			intersect the Plane
		*/
		bool IntersectsPlane(Plane p, vec3 *IntersectionPoint = nullptr,
			float *t = nullptr);
		//!IntersectsAABB will test to see if a ray intersects an Axis-Aligned Bounding Box
		/*!
			\param aabb is the AABB to test
		*/
		bool IntersectsAABB(const AABB &aabb) const;
	};
	/*!
		@}
	*/
};
#endif
