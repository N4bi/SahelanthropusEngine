#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "MathGeoLib\include\MathGeoLib.h"

class Square
{
public:
	Square() {}
	Square(float2 center,float size) 
	{
		center_point = center;
		this->size = size;
		min_point.x = center.x - size / 2.0f;
		min_point.y = center.y - size / 2.0f;
		aabb.SetFromCenterAndSize(float3(center_point.x, 10.0f, center_point.y), float3(size, size, size));
	}
	~Square() {}

	float2 GetCenterPoint() const
	{
		return center_point;
	}

	float2 MinPoint() const
	{
		return min_point;
	}

	float GetSize() const
	{
		return size;
	}
	AABB GetAABB() const
	{
		return aabb;
	}

	bool PointInSquare(const float2& point) const
	{
		if (point.x >= min_point.x && point.x <= min_point.x + size && point.y >= min_point.y && point.y <= min_point.y + size)
		{
			return true;
		}
		return false;
	}


private:
	float2 center_point;
	float2 min_point;
	float size;
	AABB aabb;
};






#endif // !__SQUARE_H__

