#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "MathGeoLib\include\MathGeoLib.h"
#include "ComponentMesh.h"
#include "GameObject.h"
#include <stdlib.h>
#include <list>
#include <vector>

#define QUADTREE_MAX_ITEMS 2

class GameObject;

template<typename TYPE>
class QuadTreeNode
{
public:
	QuadTreeNode(AABB& aabb) : bounding_box(aabb), game_objects(QUADTREE_MAX_ITEMS)
	{
		parent = childs[0] = childs[1] = childs[2] = childs[3];
	}
	~QuadTreeNode()
	{
		for (uint i = 0; i < 4; ++i)
		{
			if (childs[i] != NULL)
			{
				delete childs[i];
			}
		}
	}

	void Insert(GameObject* game_object)
	{
		if (childs[0] == nullptr && childs[1] == nullptr && childs[2] == nullptr && childs[3] == nullptr)
		{
			if (game_objects.size() >= QUADTREE_MAX_ITEMS)
			{
				DivideNode();
				InsertChilds();
			}
			else
			{
				game_objects.push_back(game_object);
				return;
			}
		}
		InsertChilds();
		return;
	}

	void InsertChilds()
	{
		std::list<GameObject*>::iterator it = game_objects.begin();
		while (it != game_objects.end())
		{	
			ComponentMesh* cmp_mesh = (ComponentMesh)(*it)->GetComponent(Component::MESH);

			AABB new_bb(cmp_mesh->world_bb.MinimalEnclosingAABB());

			if (childs[0]->QuadTreeNode::bounding_box.Intersects(new_bb) && childs[1]->QuadTreeNode::bounding_box.Intersects(new_bb) && childs[2]->QuadTreeNode::bounding_box.Intersects(new_bb) && childs[3]->QuadTreeNode::bounding_box.Intersects(new_bb))
			{
				game_objects.push_back((*it));
				++it;

			}
			else
			{
				it = game_objects.erase((*it));
				for (uint i = 0; i < 4; ++i)
				{
					if (childs[i]->QuadTreeNode::bounding_box.Intersects(new_bb))
					{	
						childs[i]->QuadTreeNode::Insert((*it));
					}
				}
			}		
		}
	}

	void DivideNode()
	{
		/*		---------------------
				|		  |  		|
				|	3	  |		0	|
				|		  |			|
				|---------|---------|
				|		  |			|
				|	2	  |		1	|
				|		  |			|
				---------------------
		
		*/

		AABB new_bb;

		// child[0]
		new_bb.CenterPoint().x = bounding_box.CenterPoint().x + ((bounding_box.Size().x) / 4);
		new_bb.CenterPoint().z = bounding_box.CenterPoint().z + ((bounding_box.Size().z) / 4);
		childs[0]->QuadTreeNode::parent = this;
		childs[0] = new QuadTreeNode(new_bb);

		//child[1]

		new_bb.CenterPoint().x = bounding_box.CenterPoint().x + ((bounding_box.Size().x) / 4);
		new_bb.CenterPoint().z = bounding_box.CenterPoint().z - ((bounding_box.Size().z) / 4);
		childs[1]->QuadTreeNode::parent = this;
		childs[1] = new QuadTreeNode(new_bb);

		//child[2]

		new_bb.CenterPoint().x = bounding_box.CenterPoint().x - ((bounding_box.Size().x) / 4);
		new_bb.CenterPoint().z = bounding_box.CenterPoint().z - ((bounding_box.Size().z) / 4);
		childs[2]->QuadTreeNode::parent = this;
		childs[2] = new QuadTreeNode(new_bb);

		//child[3]

		new_bb.CenterPoint().x = bounding_box.CenterPoint().x - ((bounding_box.Size().x) / 4);
		new_bb.CenterPoint().z = bounding_box.CenterPoint().z + ((bounding_box.Size().z) / 4);
		childs[3]->QuadTreeNode::parent = this;
		childs[3] = new QuadTreeNode(new_bb);
	}

	void CollectCandidates(std::vector<GameObject*>& nodes) const
	{
		std::list<GameObject*>::iterator it = game_objects.begin();
		while (it != game_objects.end())
		{
			nodes.push_back((*it));
			++it;
		}

		if (childs[0] != nullptr)
		{
			for (uint i = 0; i < 4; ++i)
			{
				childs[i]->QuadTreeNode::CollectCandidates(nodes);
			}
		}
	}

	void CollectBoxes(std::vector<QuadTreeNode*>& nodes) const
	{
		nodes.push_back(this);

		if (childs[0] != nullptr)
		{
			for (uint i = 0; i < 4; ++i)
			{
				childs[i]->QuadTreeNode::CollectBoxes(nodes);
			}
		}
	}

public:
	AABB bounding_box;
	std::vector<GameObject*> game_objects;
	QuadTreeNode* parent;
	QuadTreeNode* childs[4];


};


template<typename TYPE>
class QuadTree
{
public:
	QuadTree(): root(nullptr)
	{}
	virtual ~QuadTree()
	{	
		Clear();
	}

	void SetBoundaries(const AABB& bb)
	{
		if (root != nullptr)
		{
			delete root;
		}
		root = new QuadTreeNode<TYPE>(bb);
	}

	void Insert(GameObject* game_object)
	{
		ComponentMesh* cmp_mesh = (ComponentMesh*)game_object->GetComponent(Component::MESH);

		if (root != nullptr)
		{
			if (cmp_mesh->world_bb.MinimalEnclosingAABB().Intersects(root->bounding_box))
			{
				root->Insert(game_object);
			}
		}
	}

	void Clear()
	{
		if (root != nullptr)
		{
			delete root;
			root = nullptr;
		}
	}

	void CollectCandidates(std::vector<GameObject*>& nodes)
	{
		if (root != nullptr)
		{
			root->CollectCandidates(nodes);
		}
	}

	void CollectBoxes(std::vector<QuadTreeNode*>& nodes)
	{
		if (root != nullptr)
		{
			root->CollectBoxes(nodes);
		}
	}

public:
	QuadTreeNode* root;
};


#endif // !__QUADTREE_H__

