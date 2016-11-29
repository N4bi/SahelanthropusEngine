#ifndef __RAYCAST_H__
#define	__RAYCAST_H__
#include "MathGeoLib\include\MathGeoLib.h"

class GameObject;

struct RayCast
{
	RayCast() {};
	RayCast(float dist, float3 point, float3 normal, GameObject* game_object) : distance(dist), point(point), normal(normal), game_object(game_object) {};
	~RayCast() { game_object = nullptr; };

	float distance = 0;
	float3 point = float3::zero;
	float3 normal = float3::zero;
	GameObject* game_object = nullptr;


};


#endif // !__RAYCAST_H__
