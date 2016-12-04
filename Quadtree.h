#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "MathGeoLib\include\MathGeoLib.h"

#include "GameObject.h"
#include <stdlib.h>
#include <list>
#include <vector>
#include "Square.h"
#include "ComponentCamera.h"

#define MAX_BUCKET 1

class QuadNode
{
public:
	QuadNode();
	QuadNode(QuadNode* parent, float size, float2 center);
	~QuadNode();

	bool Insert(GameObject* object);
	bool Remove(GameObject* object);
	bool Intersect(const float2& position) const;
	void Divide();
	bool Clear();
	void Render();

	void FrustumCulling(ComponentCamera* cmp_cam);
	std::vector<GameObject*> RayPicking(const math::LineSegment& raycast);



public:
	Square bb;
	std::vector<QuadNode*> childs;
	std::vector<GameObject*> go;
	QuadNode* parent = nullptr;

};

class Quadtree
{
public:
	Quadtree();
	~Quadtree();

	void Create(float size);
	bool Insert(GameObject* object);
	bool Remove(GameObject* object);
	bool Clear();
	void Render();

	void FrustumCulling(ComponentCamera* cmp_cam) const;
	std::vector<GameObject*> RayPicking(const LineSegment& raycast) const;
	

private:
	QuadNode* root = nullptr;


};



#endif // !__QUADTREE_H__

