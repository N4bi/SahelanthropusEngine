#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "MathGeoLib\include\MathGeoLib.h"
#include "ComponentMesh.h"
#include "GameObject.h"
#include <stdlib.h>
#include <list>
#include <vector>
#include "Square.h"

class QuadNode
{
public:
	QuadNode();
	QuadNode(QuadNode* parent, float size, float2 center,GameObject* object);
	~QuadNode();

	void Divide();

public:
	GameObject* object = nullptr;
	Square bb;
	std::vector<QuadNode*> childs;
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
	bool Intersect();

private:
	QuadNode* root = nullptr;
	float size = 0.0f;

};



#endif // !__QUADTREE_H__

