
#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__
#include "Color.h"
#include "MathGeoLib\include\MathGeoLib.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:

	Primitive();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	vec				GetPos();
	void			SetRotation(float angle, const vec &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;

public:

	Color color;
	float4x4 transform;
	bool axis, wire;

protected:
	PrimitiveTypes type;
};

// ============================================
class Cube_Prim : public Primitive
{
public:
	Cube_Prim();
	Cube_Prim(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
public:
	vec size;
};

// ============================================
class Sphere_Prim : public Primitive
{
public:
	Sphere_Prim();
	Sphere_Prim(float radius);
	void InnerRender() const;
public:
	float radius;
};

// ============================================
class Cylinder_Prim : public Primitive
{
public:
	Cylinder_Prim();
	Cylinder_Prim(float radius, float height);
	void InnerRender() const;
public:
	float radius;
	float height;
};

// ============================================
class Line_Prim : public Primitive
{
public:
	Line_Prim();
	Line_Prim(float x, float y, float z);
	void InnerRender() const;
public:
	vec origin;
	vec destination;
};

// ============================================
class Plane_Prim : public Primitive
{
public:
	Plane_Prim();
	Plane_Prim(float x, float y, float z, float d);
	void InnerRender() const;
public:
	vec normal;
	float constant;
};
#endif // !__PRIMITIVE_H__
