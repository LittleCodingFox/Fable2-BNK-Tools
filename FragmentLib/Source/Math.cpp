#include <Fragment/Fragment.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
namespace Fragment
{
	vec2::vec2()
	{
		x = y = 0.0f;
	};

	vec2::vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	};

	vec2::vec2(const vec2 &o)
	{
		x = o.x;
		y = o.y;
	};

	vec2 vec2::operator+(const vec2 &o)
	{
		return vec2(x + o.x, y + o.y);
	};

	vec2 vec2::operator+(float f)
	{
		return vec2(x + f, y + f);
	};

	vec2 vec2::operator-(const vec2 &o)
	{
		return vec2(x - o.x, y - o.y);
	};

	vec2 vec2::operator-(float f)
	{
		return vec2(x - f, y - f);
	};

	vec2 vec2::operator*(const vec2 &o)
	{
		return vec2(x * o.x, y * o.y);
	};

	vec2 vec2::operator*(float f)
	{
		return vec2(x * f, y * f);
	};

	vec2 vec2::operator/(const vec2 &o)
	{
		return vec2(x / ((o.x > 0) ? (o.x) : (1)), y / ((o.y > 0) ? (o.y) : (1)));
	};

	vec2 vec2::operator/(float f)
	{
		return vec2(x / ((f > 0) ? (f) : (1)), y / ((f > 0) ? (f) : (1)));
	};

	vec2 vec2::operator+=(const vec2 &o)
	{
		vec2 v = *this + o;
		*this = v;
		return v;
	};

	vec2 vec2::operator+=(float f)
	{
		vec2 v = *this + f;
		*this = v;
		return v;
	};

	vec2 vec2::operator-=(const vec2 &o)
	{
		vec2 v = *this - o;
		*this = v;
		return v;
	};

	vec2 vec2::operator-=(float f)
	{
		vec2 v = *this - f;
		*this = v;
		return v;
	};

	vec2 vec2::operator/=(const vec2 &o)
	{
		vec2 v = *this / o;
		*this = v;
		return v;
	};

	vec2 vec2::operator/=(float f)
	{
		vec2 v = *this / f;
		*this = v;
		return v;
	};

	vec2 vec2::operator*=(const vec2 &o)
	{
		vec2 v = *this * o;
		*this = v;
		return v;
	};

	vec2 vec2::operator*=(float f)
	{
		vec2 v = *this * f;
		*this = v;
		return v;
	};

	vec2 vec2::operator-()
	{
		return vec2(-x, -y);
	};

	bool vec2::operator==(const vec2 &o)
	{
		return x == o.x && y == o.y;
	};

	bool vec2::operator!=(const vec2 &o)
	{
		return !(*this == o);
	};

	float vec2::Magnitude()
	{
		return sqrtf(x * x + y * y);
	};

	float vec2::MagnitudeSquare()
	{
		return x * x + y * y;
	};

	vec2 vec2::Normalized()
	{
		vec2 v = *this;
		float Mag = Magnitude();
		if(Mag <= 0) Mag = 1;
		v.x /= Mag;
		v.y /= Mag;
		return v;
	};

	void vec2::Normalize()
	{
		float Mag = Magnitude();
		if(Mag <= 0) Mag = 1;
		x /= Mag;
		y /= Mag;
	};

	float vec2::Distance(vec2 o)
	{
		vec2 v(o.x - x, o.y - y);
		return v.Magnitude();
	};

	float vec2::Dot(vec2 o)
	{
		return x * o.x + y * o.y;
	};

	vec2 vec2::Parallel()
	{
		float MagSq = x * x + y * y;
		if(MagSq <= 0) MagSq = 1;
		return *this * (Dot(*this) / MagSq);
	};

	vec2 vec2::Perpendicular()
	{
		vec2 p = Parallel();
		return -p + Magnitude();
	};

	vec3::vec3()
	{
		x = y = z = 0.0f;
	};

	vec3::vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	vec3::vec3(const vec3 &o)
	{
		x = o.x;
		y = o.y;
		z = o.z;
	};

	vec3::vec3(vec2 v)
	{
		x = v.x;
		y = v.y;
		z = 0.0f;
	};

	vec3::vec3(vec2 xy, float z)
	{
		x = xy.x;
		y = xy.y;
		this->z = z;
	};

	vec3::vec3(float x, vec2 yz)
	{
		this->x = x;
		y = yz.x;
		z = yz.y;
	};

	vec3 vec3::operator+(const vec3 &o)
	{
		return vec3(x + o.x, y + o.y, z + o.z);
	};

	vec3 vec3::operator+(float f)
	{
		return vec3(x + f, y + f, z + f);
	};

	vec3 vec3::operator-(const vec3 &o)
	{
		return vec3(x - o.x, y - o.y, z -  o.z);
	};

	vec3 vec3::operator-(float f)
	{
		return vec3(x - f, y - f, z - f);
	};

	vec3 vec3::operator*(const vec3 &o)
	{
		return vec3(x * o.x, y * o.y, z * o.z);
	};

	vec3 vec3::operator*(float f)
	{
		return vec3(x * f, y * f, z * f);
	};

	vec3 vec3::operator*(const mat4 &m)
	{
		vec4 v = vec4(x, y, z, 1) * m;
		return vec3(v.x, v.y, v.z);
	};

	vec3 vec3::operator/(const vec3 &o)
	{
		return vec3(x / ((o.x > 0) ? (o.x) : (1)), y / ((o.y > 0) ? (o.y) : (1)), z / ((o.z > 0) ? (o.z) : (1)));
	};

	vec3 vec3::operator/(float f)
	{
		return vec3(x / ((f > 0) ? (f) : (1)), y / ((f > 0) ? (f) : (1)), z / ((f > 0) ? (f) : (1)));
	};

	vec3 vec3::operator+=(const vec3 &o)
	{
		vec3 v = *this + o;
		*this = v;
		return *this;
	};

	vec3 vec3::operator+=(float f)
	{
		vec3 v = *this + f;
		*this = v;
		return *this;
	};

	vec3 vec3::operator-=(const vec3 &o)
	{
		vec3 v = *this - o;
		*this = v;
		return *this;
	};

	vec3 vec3::operator-=(float f)
	{
		vec3 v = *this - f;
		*this = v;
		return *this;
	};

	vec3 vec3::operator/=(const vec3 &o)
	{
		vec3 v = *this / o;
		*this = v;
		return *this;
	};

	vec3 vec3::operator/=(float f)
	{
		vec3 v = *this / f;
		*this = v;
		return *this;
	};

	vec3 vec3::operator*=(const vec3 &o)
	{
		vec3 v = *this * o;
		*this = v;
		return *this;
	};

	vec3 vec3::operator*=(float f)
	{
		vec3 v = *this * f;
		*this = v;
		return *this;
	};

	vec3 vec3::operator-()
	{
		return vec3(-x, -y, -z);
	};

	bool vec3::operator==(const vec3 &o)
	{
		return x == o.x && y == o.y && z == o.z;
	};

	bool vec3::operator!=(const vec3 &o)
	{
		return !(*this == o);
	};

	float vec3::Magnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	};

	float vec3::MagnitudeSquare()
	{
		return x * x + y * y + z * z;
	};


	vec3 vec3::Normalized()
	{
		vec3 v = *this;
		float Mag = Magnitude();
		if(Mag <= 0) Mag = 1;
		v.x /= Mag;
		v.y /= Mag;
		v.z /= Mag;
		return v;
	};

	void vec3::Normalize()
	{
		float Mag = Magnitude();
		if(Mag <= 0) Mag = 1;
		x /= Mag;
		y /= Mag;
		z /= Mag;
	};

	float vec3::Distance(vec3 o)
	{
		vec3 v(o.x - x, o.y - y, o.z - z);
		return v.Magnitude();
	};

	float vec3::Dot(vec3 o)
	{
		return x * o.x + y * o.y + z * o.z;
	};

	vec3 vec3::Parallel()
	{
		float MagSq = x * x + y * y + z * z;
		if(MagSq <= 0) MagSq = 1;
		return *this * (Dot(*this) / MagSq);
	};

	vec3 vec3::Perpendicular()
	{
		vec3 p = Parallel();
		return -p + Magnitude();
	};

	vec3 vec3::Cross(vec3 o)
	{
		vec3 v;
		v.x = y * o.z - z * o.y;
		v.y = z * o.x - x * o.z;
		v.z = x * o.y - y * o.x;
		return v;
	};

	void vec3::NormalTri(vec3 v1, vec3 v2, vec3 v3)
	{
		*this = (v2 - v1).Cross(v3 - v1).Normalized();
	};

	vec4::vec4()
	{
		x = y = z = w = 0.0f;
	};

	vec4::vec4(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1.0f;
	};

	vec4::vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};

	vec4::vec4(const vec4 &o)
	{
		x = o.x;
		y = o.y;
		z = o.z;
		w = o.w;
	};

	vec4::vec4(vec2 xy, float z, float w)
	{
		x = xy.x;
		y = xy.y;
		this->z = z;
		this->w = w;
	};

	vec4::vec4(float x, vec2 yz)
	{
		this->x = x;
		y = yz.x;
		z = yz.y;
		w = 0.0f;
	};

	vec4::vec4(float x, vec2 yz, float w)
	{
		this->x = x;
		y = yz.x;
		z = yz.y;
		this->w = w;
	};

	vec4::vec4(float x, float y, vec2 zw)
	{
		this->x = x;
		this->y = y;
		z = zw.x;
		w = zw.y;
	};

	vec4::vec4(vec2 xy, vec2 zw)
	{
		x = xy.x;
		y = xy.y;
		z = zw.x;
		w = zw.y;
	};

	vec4::vec4(vec3 xyz, float w)
	{
		x = xyz.x;
		y = xyz.y;
		z = xyz.z;
		this->w = w;
	};

	vec4::vec4(float x, vec3 yzw)
	{
		this->x = x;
		y = yzw.x;
		z = yzw.y;
		w = yzw.z;
	};

	vec4::vec4(vec2 v)
	{
		x = v.x;
		y = v.y;
		z = w = 0.0f;
	};

	vec4::vec4(vec3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0.0f;
	};

	vec4 vec4::operator+(const vec4 &o)
	{
		return vec4(x + o.x, y + o.y, z + o.z, w + o.w);
	};

	vec4 vec4::operator+(float f)
	{
		return vec4(x + f, y + f, z + f, w + f);
	};

	vec4 vec4::operator-(const vec4 &o)
	{
		return vec4(x - o.x, y - o.y, z - o.z, w - o.w);
	};

	vec4 vec4::operator-(float f)
	{
		return vec4(x - f, y - f, z - f, w - f);
	};

	vec4 vec4::operator*(const vec4 &o)
	{
		return vec4(x * o.x, y * o.y, z * o.z, w * o.w);
	};

	vec4 vec4::operator*(float f)
	{
		return vec4(x * f, y * f, z * f, w * f);
	};

	vec4 vec4::operator*(const mat4 &m)
	{
		vec4 v;
		v.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
		v.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
		v.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
		v.w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];
		return v;
	};

	vec4 vec4::operator/(const vec4 &o)
	{
		return vec4(x / ((o.x > 0) ? (o.x) : (1)), y / ((o.y > 0) ? (o.y) : (1)),
			z / ((o.z > 0) ? (o.z) : (1)), w / ((o.w > 0) ? (o.w) : (1)));
	};

	vec4 vec4::operator/(float f)
	{
		return vec4(x / ((f > 0) ? (f) : (1)), y / ((f > 0) ? (f) : (1)),
			z / ((f > 0) ? (f) : (1)), w / ((f > 0) ? (f) : (1)));
	};

	vec4 vec4::operator+=(const vec4 &o)
	{
		vec4 v = *this + o;
		*this = v;
		return *this;
	};

	vec4 vec4::operator+=(float f)
	{
		vec4 v = *this + f;
		*this = v;
		return *this;
	};

	vec4 vec4::operator-=(const vec4 &o)
	{
		vec4 v = *this - o;
		*this = v;
		return *this;
	};

	vec4 vec4::operator-=(float f)
	{
		vec4 v = *this - f;
		*this = v;
		return *this;
	};

	vec4 vec4::operator/=(const vec4 &o)
	{
		vec4 v = *this / o;
		*this = v;
		return *this;
	};

	vec4 vec4::operator/=(float f)
	{
		vec4 v = *this / f;
		*this = v;
		return *this;
	};

	vec4 vec4::operator*=(const vec4 &o)
	{
		vec4 v = *this * o;
		*this = v;
		return *this;
	};

	vec4 vec4::operator*=(float f)
	{
		vec4 v = *this * f;
		*this = v;
		return *this;
	};

	vec4 vec4::operator-()
	{
		return vec4(-x, -y, -z, -w);
	};

	bool vec4::operator==(const vec4 &o)
	{
		return x == o.x && y == o.y && z == o.z && w == o.w;
	};

	bool vec4::operator!=(const vec4 &o)
	{
		return !(*this == o);
	};

	float vec4::Magnitude()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	};

	float vec4::MagnitudeSquare()
	{
		return x * x + y * y + z * z + w * w;
	};

	vec4 vec4::Normalized()
	{
		vec4 v = *this;
		float Mag = Magnitude();
		if(Mag <= 0) Mag = 1;
		v.x /= Mag;
		v.y /= Mag;
		v.z /= Mag;
		v.w /= Mag;
		return v;
	};

	void vec4::Normalize()
	{
		float Mag = Magnitude();
		if(Mag <= 0) Mag = 1;
		x /= Mag;
		y /= Mag;
		z /= Mag;
		w /= Mag;
	};

	float vec4::Distance(vec4 o)
	{
		vec4 v(o.x - x, o.y - y, o.z - z, o.w - w);
		return v.Magnitude();
	};

	float vec4::Dot(vec4 o)
	{
		return x * o.x + y * o.y + z * o.z + w * o.w;
	};

	vec4 vec4::Parallel()
	{
		float MagSq = x * x + y * y + z * z + w * w;
		if(MagSq <= 0) MagSq = 1;
		return *this * (Dot(*this) / MagSq);
	};

	vec4 vec4::Perpendicular()
	{
		vec4 p = Parallel();
		return -p + Magnitude();
	};

	vec4 vec4::Cross(vec4 o)
	{
		vec4 v;
		v.x = y * o.z - z * o.y;
		v.y = z * o.x - x * o.z;
		v.z = x * o.y - y * o.x;
		//TODO: W component
		return v;
	};

	Plane::Plane()
	{
		a = b = c = d = 0.0f;
	};

	Plane::Plane(const Plane &o)
	{
		a = o.a;
		b = o.b;
		c = o.c;
		d = o.d;
	};

	Plane::Plane(float a, float b, float c, float d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	};

	void Plane::FromTriangle(vec3 v1, vec3 v2, vec3 v3)
	{
		vec3 Normal = (v2 - v1).Cross(v3 - v1).Normalized();
		a = Normal.x;
		b = Normal.y;
		c = Normal.z;
		d = -Normal.Dot(v1);
	};

	unsigned int Plane::ClassifyPoint(vec3 v)
	{
		float Dot = v.Dot(vec3(a, b, c)) + d;
		if(Dot > FR_EPSILON)
		{
			return FRP_FRONT;
		}
		else if(Dot < -FR_EPSILON)
		{
			return FRP_BACK;
		}
		else
		{
			return FRP_ON_PLANE;
		};
	};

	Rect::Rect()
	{
		Left = Right = Top = Bottom = 0.0f;
	};

	Rect::Rect(const Rect &Other)
	{
		this->Left = Other.Left;
		this->Right = Other.Right;
		this->Top = Other.Top;
		this->Bottom = Other.Bottom;
	};

	Rect::Rect(float Width, float Height)
	{
		Left = -Width / 2.0f;
		Right = -Left;
		Top = Height / 2.0f;
		Bottom = -Top;
	};

	Rect::Rect(float Left, float Right, float Top, float Bottom)
	{
		this->Left = Left;
		this->Right = Right;
		this->Top = Top;
		this->Bottom = Bottom;
	};

	bool Rect::IsInside(vec2 Position)
	{
		return(Position.x >= Left && Position.x <= Right &&
			Position.y >= Bottom && Position.y <= Top);
	};

	bool Rect::IsOutside(vec2 Position)
	{
		return !IsInside(Position);
	};

	AABB::AABB()
	{
		Clear();
	};

	AABB::AABB(const AABB &Other)
	{
		this->min = Other.min;
		this->max = Other.max;
	};

	AABB::AABB(vec3 min, vec3 max)
	{
		this->min = min;
		this->max = max;
	};

	void AABB::Clear()
	{
		min = vec3(9999999.0f, 9999999.0f, 9999999.0f);
		max = -min;
	};

	void AABB::Calculate(Array<vec3> Points)
	{
		for(unsigned long i = 0; i < Points.Size(); i++)
		{
			vec3& v = Points[i];
			if(v.x < min.x)
			{
				min.x = v.x;
			};

			if(v.y < min.y)
			{
				min.y = v.y;
			};

			if(v.z < min.z)
			{
				min.z = v.z;
			};

			if(v.x > max.x)
			{
				max.x = v.x;
			};

			if(v.y > max.y)
			{
				max.y = v.y;
			};

			if(v.z > max.z)
			{
				max.z = v.z;
			};
		};
	};

	void AABB::Calculate(vec3 Point)
	{
		if(Point.x < min.x)
		{
			min.x = Point.x;
		};

		if(Point.y < min.y)
		{
			min.y = Point.y;
		};

		if(Point.z < min.z)
		{
			min.z = Point.z;
		};

		if(Point.x > max.x)
		{
			max.x = Point.x;
		};

		if(Point.y > max.y)
		{
			max.y = Point.y;
		};

		if(Point.z > max.z)
		{
			max.z = Point.z;
		};
	};

	bool AABB::IsInside(vec3 Position) const
	{
		return(Position.x >= min.x && Position.x <= max.x &&
			Position.y >= min.y && Position.y <= max.y &&
			Position.z >= min.z && Position.z <= max.z);
	};

	bool AABB::IsOutside(vec3 Position) const
	{
		return !IsInside(Position);
	};

	void AABB::Corners(vec3 *Destination) const
	{
		Destination[0] = min;
		Destination[1] = vec3(max.x, min.y, min.z);
		Destination[2] = vec3(max.x, max.y, min.z);	
		Destination[3] = vec3(min.x, max.y, min.z);
		Destination[4] = vec3(min.x, min.y, max.z);
		Destination[5] = vec3(max.x, min.y, max.z);
		Destination[6] = max;
		Destination[7] = vec3(min.x, max.y, max.z);
	};

	OBB::OBB()
	{
		Clear();
	};

	OBB::OBB(const OBB &Other)
	{
		this->Transformation = Other.Transformation;
		this->aabb = Other.aabb;
	};

	OBB::OBB(AABB aabb, mat4 Transformation)
	{
		this->Transformation = Transformation;
		this->aabb = aabb;
	};

	void OBB::Clear()
	{
		aabb.Clear();
		Transformation.Identity();
	};

	void OBB::Calculate(Array<vec3> Points)
	{
		aabb.Calculate(Points);
	};

	void OBB::Calculate(vec3 Point)
	{
		aabb.Calculate(Point);
	};

	bool OBB::IsInside(vec3 Position) const
	{
		mat4 InvTransformation = Transformation;
		if(!InvTransformation.Inverse())
			return false;
		Position = Position * InvTransformation;
		return aabb.IsInside(Position);
	};

	bool OBB::IsOutside(vec3 Position) const
	{
		return !IsInside(Position);
	};

	BoundingSphere::BoundingSphere()
	{
		Radius = 0.0f;
	};

	void BoundingSphere::Calculate(Array<vec3> Points)
	{
		SILENTVOIDFRASSERT(Points.Size());

		for(unsigned long i = 0; i < Points.Size(); i++)
		{
			Center += Points[i];
		};
		Center /= (float)Points.Size();

		for(unsigned long i = 0; i < Points.Size(); i++)
		{
			float Distance = (Points[i].Distance(Center));
			if(Distance > Radius)
				Radius = Distance;
		};
	};

	bool BoundingSphere::Intersects(vec3 Point)
	{
		return Center.Distance(Point) > Radius;
	};

	bool BoundingSphere::Intersects(BoundingSphere Sphere)
	{
		float AddedRadius = Radius + Sphere.Radius;
		return Center.Distance(Sphere.Center) > AddedRadius;
	};

	Ray::Ray()
	{
	};

	Ray::Ray(const Ray &Other)
	{
		this->Position = Other.Position;
		this->Direction = Other.Direction;
	};

	Ray::Ray(vec3 Position, vec3 Direction)
	{
		this->Position = Position;
		this->Direction = Direction;
	};

	bool Ray::IntersectsTriangle(vec3 v1, vec3 v2, vec3 v3, vec3 *IntersectionPoint,
		float *t)
	{
		vec3 Edge1 = v2 - v1, Edge2 = v3 - v1;
		vec3 pvec = Direction.Cross(Edge2);
		float det = Edge1.Dot(pvec);

		if (det > -FR_EPSILON && det < FR_EPSILON)
		{
			return false;
		};

		float inv_det = 1.0f / det;
		vec3 tvec = Position - v1;
		float u = tvec.Dot(pvec) * inv_det;

		if (u < 0.0 || u > 1.0)
		{
			return false;
		};

		vec3 qvec = tvec.Cross(Edge1);
		float v = Direction.Dot(qvec) * inv_det;

		if (v < 0.0 || u + v > 1.0)
		{
			return false;
		};

		float _t = Edge2.Dot(qvec) * inv_det;

		if(t)
		{
			*t = _t;
		};

		if(IntersectionPoint)
		{
			*IntersectionPoint = Position + (Direction * _t);
		};
		return true;
	};

	bool Ray::IntersectsPlane(Plane p, vec3 *IntersectionPoint, float *t)
	{
		vec3 Normal(p.a, p.b, p.c);
		if(Normal.Dot(Direction) == 0)
		{
			return false;
		};
		float _t = -( Normal.Dot(Position) + p.d ) / ( Normal.Dot(Direction) );

		if(t)
		{
			*t = _t;
		};

		if(IntersectionPoint)
		{
			*IntersectionPoint = Position + Direction * _t;
		};
		return true;
	};

	bool Ray::IntersectsAABB(const AABB &aabb) const
	{
		vec3 InverseDirection(
			(Direction.x == 0.0f) ? (0) : (1.0f / Direction.x),
			(Direction.y == 0.0f) ? (0) : (1.0f / Direction.y),
			(Direction.z == 0.0f) ? (0) : (1.0f / Direction.z));

		float Slopes[6] = {
			Direction.x * InverseDirection.y,
			Direction.y * InverseDirection.x,
			Direction.y * InverseDirection.z,
			Direction.z * InverseDirection.y,
			Direction.x * InverseDirection.z,
			Direction.z * InverseDirection.x
		};

		float Precomputed[6] = {
			Position.y - Slopes[1] * Position.x,
			Position.x - Slopes[0] * Position.y,
			Position.y - Slopes[2] * Position.z,
			Position.z - Slopes[3] * Position.y,
			Position.z - Slopes[4] * Position.x,
			Position.x - Slopes[5] * Position.z
		};

		if((Position.x > aabb.max.x) || (Position.y > aabb.max.y) || 
			(Position.z > aabb.max.z) || 
			(Slopes[1] * aabb.max.x - aabb.min.y + Precomputed[0] < 0) ||
			(Slopes[0] * aabb.max.y - aabb.min.x + Precomputed[1] < 0) ||
			(Slopes[2] * aabb.max.z - aabb.min.y + Precomputed[2] < 0) ||
			(Slopes[3] * aabb.max.y - aabb.min.z + Precomputed[3] < 0) ||
			(Slopes[4] * aabb.max.x - aabb.min.z + Precomputed[4] < 0) ||
			(Slopes[5] * aabb.max.z - aabb.min.x + Precomputed[5] < 0))
			return false;

		return true;
	};


	mat4::mat4()
	{
		Identity();
	};

	mat4::mat4(const mat4 &m)
	{
		memcpy(this, &m, sizeof(m));
	};

	mat4 mat4::operator*(const mat4 &o)
	{
		mat4 M;

		M.m[0][0] = m[0][0] * o.m[0][0] + m[0][1] * o.m[1][0] + m[0][2] * o.m[2][0] + m[0][3] * o.m[3][0];
		M.m[0][1] = m[0][0] * o.m[0][1] + m[0][1] * o.m[1][1] + m[0][2] * o.m[2][1] + m[0][3] * o.m[3][1];
		M.m[0][2] = m[0][0] * o.m[0][2] + m[0][1] * o.m[1][2] + m[0][2] * o.m[2][2] + m[0][3] * o.m[3][2];
		M.m[0][3] = m[0][0] * o.m[0][3] + m[0][1] * o.m[1][3] + m[0][2] * o.m[2][3] + m[0][3] * o.m[3][3];

		M.m[1][0] = m[1][0] * o.m[0][0] + m[1][1] * o.m[1][0] + m[1][2] * o.m[2][0] + m[1][3] * o.m[3][0];
		M.m[1][1] = m[1][0] * o.m[0][1] + m[1][1] * o.m[1][1] + m[1][2] * o.m[2][1] + m[1][3] * o.m[3][1];
		M.m[1][2] = m[1][0] * o.m[0][2] + m[1][1] * o.m[1][2] + m[1][2] * o.m[2][2] + m[1][3] * o.m[3][2];
		M.m[1][3] = m[1][0] * o.m[0][3] + m[1][1] * o.m[1][3] + m[1][2] * o.m[2][3] + m[1][3] * o.m[3][3];

		M.m[2][0] = m[2][0] * o.m[0][0] + m[2][1] * o.m[1][0] + m[2][2] * o.m[2][0] + m[2][3] * o.m[3][0];
		M.m[2][1] = m[2][0] * o.m[0][1] + m[2][1] * o.m[1][1] + m[2][2] * o.m[2][1] + m[2][3] * o.m[3][1];
		M.m[2][2] = m[2][0] * o.m[0][2] + m[2][1] * o.m[1][2] + m[2][2] * o.m[2][2] + m[2][3] * o.m[3][2];
		M.m[2][3] = m[2][0] * o.m[0][3] + m[2][1] * o.m[1][3] + m[2][2] * o.m[2][3] + m[2][3] * o.m[3][3];

		M.m[3][0] = m[3][0] * o.m[0][0] + m[3][1] * o.m[1][0] + m[3][2] * o.m[2][0] + m[3][3] * o.m[3][0];
		M.m[3][1] = m[3][0] * o.m[0][1] + m[3][1] * o.m[1][1] + m[3][2] * o.m[2][1] + m[3][3] * o.m[3][1];
		M.m[3][2] = m[3][0] * o.m[0][2] + m[3][1] * o.m[1][2] + m[3][2] * o.m[2][2] + m[3][3] * o.m[3][2];
		M.m[3][3] = m[3][0] * o.m[0][3] + m[3][1] * o.m[1][3] + m[3][2] * o.m[2][3] + m[3][3] * o.m[3][3];

		return M;
	};

	void mat4::Identity()
	{
		static const float IdentityData[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		memcpy(this, IdentityData, sizeof(IdentityData));
	};

	void mat4::Transpose()
	{
		mat4 m;
		for(unsigned int i=0; i < 4; i++)
		{
			for(unsigned int j=0; j < 4; j++)
			{
				m.m[i][j] = this->m[j][i];
			};
		};
		*this = m;
	};

	float mat3Determinant(float m[3][3])
	{
		return m[0][0] * m[1][1] * m[2][2] + 
			m[1][0] * m[2][1] * m[0][2] + 
			m[2][0] * m[0][1] * m[1][2] -
			m[2][0] * m[1][1] * m[0][2] - 
			m[0][0] * m[2][1] * m[1][2] - 
			m[1][0] * m[0][1] * m[2][2];
	};

	void SplitMat4ToMat3(mat4 m, unsigned long x, unsigned long y, float *Data)
	{
		if(x > 3 || y > 3)
			return;

		unsigned long Curr = 0;
		for(unsigned long i = 0; i < 4; i++)
		{
			for(unsigned long j = 0; j < 4; j++)
			{
				if(i == x || j == y)
					continue;
				Data[Curr++] = m.m[i][j];
			};
		};
	};

	float mat4::Determinant()
	{
		//4 pieces for the determinant
		float Pieces[4];
		//split by line i and column 0
		for(unsigned long i = 0; i < 4; i++)
		{
			float RealPiece[3][3];
			SplitMat4ToMat3(*this, i, 0, &RealPiece[0][0]);
			//calculate determinant for a 3x3 matrix
			Pieces[i] = m[i][0] * mat3Determinant(RealPiece);
		};

		//return Determinant
		return Pieces[0] - Pieces[1] + Pieces[2] - Pieces[3];
	};

	bool mat4::Inverse()
	{
		//Calculate determinant, if 0, impossible
		float determinant = Determinant();
		if(determinant == 0.0f)
			return false;

		//copy matrix
		mat4 m;
		for(unsigned long i = 0; i < 4; i++)
		{
			for(unsigned long j = 0; j < 4; j++)
			{
				//remove row j and column i
				float RealPiece[3][3];
				SplitMat4ToMat3(*this, i, 0, &RealPiece[0][0]);
				//calculate determinant and set to copy matrix
				m.m[i][j] = mat3Determinant(RealPiece);
			};
		};

		//Whether we should swap sign
		bool Swap = false;

		//Inverse determinant
		float InvDeterminant = 1.0f / determinant;

		for(unsigned long i = 0; i < 4; i++)
		{
			for(unsigned long j = 0; j < 4; j++)
			{
				//Swap sign if needed, also multiply with Inverse Determinant
				if(Swap)
					m.m[i][j] *= -InvDeterminant;
				else
					m.m[i][j] *= InvDeterminant;
				Swap = !Swap;
			};
			//Swap after each line too
			Swap = !Swap;
		};

		//reset ourselves as the copy matrix
		*this = m;
		return true;
	};

	vec4 mat4::ProjectPoint(vec4 Point, mat4 World, mat4 View, mat4 Projection, vec4 Viewport)
	{
		vec4 v = Point * World * View * Projection;
		
		if(v.w == 0)
			return Point;

		v.x /= v.w;
		v.y /= v.w;
		v.z /= v.w;
		v.x = (v.x * 0.5f + 0.5f) * Viewport.z + Viewport.x;
		v.y = (v.y * 0.5f + 0.5f) * Viewport.w + Viewport.y;
		v.z = v.z * 0.5f + 0.5f;
		return v;
	};

	vec4 mat4::UnProjectPoint(vec3 Point, mat4 World, mat4 View, mat4 Projection, vec4 Viewport)
	{
		mat4 Inv = World * View * Projection;
		if(!Inv.Inverse())
			return Point;

		vec4 v(((Point.x - Viewport.x) / Viewport.z) * 2.0f - 1.0f, 
			((Point.y - Viewport.y) / Viewport.w) * 2.0f - 1.0f,
			Point.z * 2.0f - 1.0f, 1.0f);

		v = v * Inv;
		if(v.w == 0.0f)
			return Point;

		v.x /= v.w;
		v.y /= v.w;
		v.z /= v.w;
		return v;
	};

	void mat4::Translate(vec4 v)
	{
		//Identity matrix
		Identity();
		//setup
		m[3][0] = v.x;
		m[3][1] = v.y;
		m[3][2] = v.z;
		m[3][3] = v.w;
	};

	void mat4::Scale(vec4 Scales)
	{
		//Identity matrix
		Identity();
		//setup
		m[0][0] = Scales.x;
		m[1][1] = Scales.y;
		m[2][2] = Scales.z;
		m[3][3] = Scales.w;
	};

	void mat4::Rotate(vec3 Angles)
	{
		mat4 m;
		float sinval = 0.0f, cosval = 0.0f;
		//setup
		if(Angles.x != 0.0f)
		{
			mat4 m2;
			cosval = cosf(Angles.x);
			sinval = sinf(Angles.x);
			m2.m[0][0] = 1.0f;
			m2.m[1][1] = cosval;
			m2.m[1][2] = -sinval;
			m2.m[2][1] = sinval;
			m2.m[2][2] = cosval;
			m = m2;
		}

		if(Angles.y != 0.0f)
		{
			mat4 m2;
			cosval = cosf(Angles.y);
			sinval = sinf(Angles.y);
			m2.m[0][0] = cosval;
			m2.m[0][2] = sinval;
			m2.m[1][1] = 1.0f;
			m2.m[2][0] = -sinval;
			m2.m[2][2] = cosval;
			m = m * m2;
		}

		if(Angles.z != 0.0f)
		{
			mat4 m2;
			cosval = cosf(Angles.z);
			sinval = sinf(Angles.z);
			m2.m[0][0] = cosval;
			m2.m[0][1] = -sinval;
			m2.m[1][0] = sinval;
			m2.m[1][1] = cosval;
			m2.m[2][2] = 1.0f;
			m = m * m2;
		};

		memcpy(this, &m, sizeof(m));
	};

	void mat4::PerspectiveMatrixLH(float FOV, float AspectRatio, float zNear, float zFar)
	{
		float cotan = 0.0f, DeltaZ = float(zFar) - float(zNear),
			angle = FOV / 2.0f, sine = sinf(angle);

		FRASSERT(sine != 0.0f && DeltaZ != 0.0f && AspectRatio != 0.0f, 
			"Invalid Viewport Information");

		cotan = cosf(angle) / sine;

		Identity();
		m[0][0] = cotan / AspectRatio;
		m[1][1] = cotan;
		m[2][2] = zFar / DeltaZ;
		m[2][3] = 1.0f;
		m[3][2] = -zNear * zFar / DeltaZ;
		m[3][3] = 0.0f;
	};

	void mat4::PerspectiveMatrixRH(float FOV, float AspectRatio, float zNear, float zFar)
	{
		float cotan = 0.0f, DeltaZ = float(zNear) - float(zFar),
			angle = FOV / 2.0f, sine = sinf(angle);

		FRASSERT(sine != 0.0f && DeltaZ != 0.0f && AspectRatio != 0.0f, 
			"Invalid Viewport Information");

		cotan = cosf(angle) / sine;

		Identity();
		m[0][0] = cotan / AspectRatio;
		m[1][1] = cotan;
		m[2][2] = zFar / DeltaZ;
		m[2][3] = -1.0f;
		m[3][2] = zNear * zFar / DeltaZ;
		m[3][3] = 0.0f;
	};

	void mat4::LookAtMatrixLH(vec3 Position, vec3 EyePosition, vec3 UpVector)
	{
		vec3 ZAxis = vec3(EyePosition - Position).Normalized(), 
			XAxis = UpVector.Cross(ZAxis).Normalized(), 
			YAxis = ZAxis.Cross(XAxis);
		Identity();
		m[0][0] = XAxis.x;
		m[0][1] = YAxis.x;
		m[0][2] = ZAxis.x;
		m[1][0] = XAxis.y;
		m[1][1] = YAxis.y;
		m[1][2] = ZAxis.y;
		m[2][0] = XAxis.z;
		m[2][1] = YAxis.z;
		m[2][2] = ZAxis.z;
		m[3][0] = -XAxis.Dot(Position);
		m[3][1] = -YAxis.Dot(Position);
		m[3][2] = -ZAxis.Dot(Position);
	};

	void mat4::LookAtMatrixRH(vec3 Position, vec3 EyePosition, vec3 UpVector)
	{
		vec3 ZAxis = vec3(Position - EyePosition).Normalized(), 
			XAxis = UpVector.Cross(ZAxis).Normalized(), 
			YAxis = ZAxis.Cross(XAxis);
		Identity();
		m[0][0] = XAxis.x;
		m[0][1] = YAxis.x;
		m[0][2] = ZAxis.x;
		m[1][0] = XAxis.y;
		m[1][1] = YAxis.y;
		m[1][2] = ZAxis.y;
		m[2][0] = XAxis.z;
		m[2][1] = YAxis.z;
		m[2][2] = ZAxis.z;
		m[3][0] = -XAxis.Dot(Position);
		m[3][1] = -YAxis.Dot(Position);
		m[3][2] = -ZAxis.Dot(Position);
	};

	void mat4::OrthoMatrixLH(float Left, float Right, float Bottom, float Top, float zNear, float zFar)
	{
		Identity();
		m[0][0] = 2.0f / (Right - Left);
		m[1][1] = 2.0f / (Bottom - Top);
		m[2][2] = 1.0f / (zFar - zNear);
		m[3][0] = (Left + Right) / (Left - Right);
		m[3][1] = (Top + Bottom) / (Bottom - Top);
		m[3][2] = zNear / (zNear - zFar);
	};

	void mat4::OrthoMatrixRH(float Left, float Right, float Bottom, float Top, float zNear, float zFar)
	{
		Identity();
		m[0][0] = 2.0f / (Right - Left);
		m[1][1] = 2.0f / (Top - Bottom);
		m[2][2] = 1.0f / (zNear - zFar);
		m[3][0] = (Left + Right) / (Left - Right);
		m[3][1] = (Top + Bottom) / (Bottom - Top);
		m[3][2] = zNear / (zNear - zFar);
	};

	float &mat4::SingleIndex(unsigned short Index)
	{
		return ((float*)&m[0][0])[Index];
	};
};
