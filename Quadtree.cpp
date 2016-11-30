#include "Quadtree.h"
#include <queue>

QuadNode::QuadNode()
{
	
}

QuadNode::QuadNode(QuadNode * parent, float size,float2 center, GameObject * object) : parent(parent), object(object)
{
	bb = Square(center, size);
}


QuadNode::~QuadNode()
{
}

void QuadNode::Divide()
{
	for (int i = 0; i < 4; i++)
	{
		float2 center_point;
		switch (i)
		{
			case 0:
				center_point.x = (bb.GetCenterPoint().x - bb.GetSize() * 0.25f);
				center_point.y = (bb.GetCenterPoint().y + bb.GetSize() * 0.25f);
				break;
			case 1:
				center_point.x = (bb.GetCenterPoint().x + bb.GetSize() * 0.25f);
				center_point.y = (bb.GetCenterPoint().y + bb.GetSize() * 0.25f);
				break;

			case 2:
				center_point.x = (bb.GetCenterPoint().x + bb.GetSize() * 0.25f);
				center_point.y = (bb.GetCenterPoint().y - bb.GetSize() * 0.25f);
				break;

			case 3:
				center_point.x = (bb.GetCenterPoint().x - bb.GetSize() * 0.25f);
				center_point.y = (bb.GetCenterPoint().y - bb.GetSize() * 0.25f);
				break;
		}

		QuadNode* child = new QuadNode(this, bb.GetSize()*0.5f, center_point, nullptr);
		childs.push_back(child);
	}
}

Quadtree::Quadtree()
{
}

Quadtree::~Quadtree()
{
}

void Quadtree::Create(float size)
{
	//Remove old Quadtree
	if (root!= nullptr)
	{
		//remove
	}

	root = new QuadNode(nullptr, size, float2(0, 0), nullptr);
}

bool Quadtree::Insert(GameObject * object)
{
	if (root == nullptr || object == nullptr)
	{
		return false;
	}

	ComponentMesh* cmp_mesh = (ComponentMesh*)object->GetComponent(Component::MESH);
	if (cmp_mesh != nullptr)
	{
		float3 center_point_3D = cmp_mesh->world_bb.CenterPoint();
		float2 center_point = float2(center_point_3D.x, center_point_3D.z);

		std::queue<QuadNode*> queue;
		queue.push(root);

		while (queue.empty() == false)
		{
			QuadNode* node = queue.front();			
			queue.pop();

			if (node->bb.PointInSquare(center_point))
			{
				if (node->childs.empty() == false)
				{
					std::vector<QuadNode*>::iterator it = node->childs.begin();
					while (it != node->childs.end())
					{
						queue.push(*it);
						++it;
					}
				}
				else
				{
					if (node->object != nullptr )
					{						
						node->Divide();
						GameObject* tmp = node->object;
						node->object = nullptr;
						if (Insert(tmp) && Insert(node->object))
						{
							return true;
						}
						else
						{
							return false;
						}

					}
					else
					{
						node->object = object;
						return true;
					}
				}
			}	
		}
	}
	return false;
}

bool Quadtree::Remove(GameObject * object)
{
	if (root == nullptr || object == nullptr)
	{
		return false;
	}

	ComponentMesh* cmp_mesh = (ComponentMesh*)object->GetComponent(Component::MESH);
	if (cmp_mesh != nullptr)
	{
		float3 center_point_3D = cmp_mesh->world_bb.CenterPoint();
		float2 center_point = float2(center_point_3D.x, center_point_3D.z);

		std::queue<QuadNode*> queue;
		queue.push(root);

		while (queue.empty() == false)
		{
			QuadNode* node = queue.front();
			queue.pop();

			if (node->bb.PointInSquare(center_point))
			{
				if (node->childs.empty() == false)
				{
					std::vector<QuadNode*>::iterator it = node->childs.begin();
					while (it != node->childs.end())
					{
						queue.push(*it);
						++it;
					}
				}
				else
				{
					if (node->object == object)
					{
						node->object = nullptr;
						return true;
					}
				}
			}
		}
	}
	return false;
}
