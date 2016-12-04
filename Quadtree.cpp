#include "Quadtree.h"
#include <queue>
#include "Application.h"
#include "Component.h"
#include "ComponentMesh.h"


//QUADNODE-------------------------------------------------
QuadNode::QuadNode()
{
	
}

QuadNode::QuadNode(QuadNode * parent, float size,float2 center) : parent(parent)
{
	bb = Square(center, size);
}


QuadNode::~QuadNode()
{
	Clear();
}

bool QuadNode::Insert(GameObject * object)
{
	if (object == nullptr)
	{
		return false;
	}

	ComponentMesh* cmp_mesh = (ComponentMesh*)object->GetComponent(Component::MESH);
	if (cmp_mesh != nullptr)
	{
		float3 center_point_3D = cmp_mesh->world_bb.CenterPoint();
		float2 center_point = float2(center_point_3D.x, center_point_3D.z);

		std::queue<QuadNode*> queue;
		queue.push(this);

		while (queue.empty() == false)
		{
			QuadNode* node = queue.front();
			queue.pop();

			if (node->Intersect(center_point))
			{
				if (node->childs.empty())
				{
					if (node->go.size() < MAX_BUCKET)
					{
						node->go.push_back(object);
						return true;
					}
					else
					{
						node->Divide();
						std::vector<GameObject*>::iterator it2 = node->go.begin();
						while (it2 != node->go.end())
						{
							ComponentMesh* m = (ComponentMesh*)(*it2)->GetComponent(Component::MESH);
							if (node->Insert(*it2))
							{
								(*it2) = nullptr;
							}
							else
							{
								return false;
								break;
							}
							++it2;
						}
						node->go.clear();
						node->Insert(object);
						return true;
						break;
					}
				
				}

				std::vector<QuadNode*>::iterator it = node->childs.begin();
				while (it != node->childs.end())
				{
					queue.push(*it);
					++it;
				}
		
			}
		}	
	}
return false;
}
	

bool QuadNode::Remove(GameObject * object)
{

	if (object == nullptr)
	{
		return false;
	}

	ComponentMesh* cmp_mesh = (ComponentMesh*)object->GetComponent(Component::MESH);
	if (cmp_mesh != nullptr)
	{
		float3 center_point_3D = cmp_mesh->world_bb.CenterPoint();
		float2 center_point = float2(center_point_3D.x, center_point_3D.z);

		std::queue<QuadNode*> queue;
		queue.push(this);

		while (queue.empty() == false)
		{
			QuadNode* node = queue.front();
			queue.pop();

			if (node->Intersect(center_point))
			{
				std::vector<GameObject*>::iterator it2 = node->go.begin();
				while (it2 != node->go.end())
				{
					if ((*it2) == object && node->bb.GetCenterPoint().Equals(center_point))
					{
						(*it2) = nullptr;
						return true;
						break;
					}
				}
			}
		}
	}
	return false;
}

bool QuadNode::Intersect(const float2 & position) const
{
	return bb.PointInSquare(position);
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

		QuadNode* child = new QuadNode(this, bb.GetSize()*0.5f, center_point);
		childs.push_back(child);
	}
}

bool QuadNode::Clear()
{
	if (childs.empty() == false)
	{
		std::vector<QuadNode*>::iterator it = childs.begin();
		while (it != childs.end())
		{
			(*it)->Clear();
			(*it) = nullptr;
			++it;
		}
		childs.clear();
	}

	if (go.empty() == false)
	{
		std::vector<GameObject*>::iterator it2 = go.begin();
		while (it2 != go.end())
		{
			(*it2) = nullptr;
			++it2;
		}
		go.clear();
	}

	parent = nullptr;

	return true;
}

void QuadNode::Render()
{
	if (childs.empty() == false)
	{
		std::vector<QuadNode*>::iterator it = childs.begin();
		while (it != childs.end())
		{
			(*it)->Render();
			++it;
		}		
	}	
	App->renderer3D->RenderBoundingBox(bb.GetAABB(), Blue);
}

void QuadNode::FrustumCulling(ComponentCamera * cmp_cam)
{
	std::queue<QuadNode*> queue;
	queue.push(this);

	while (queue.empty() == false)
	{
		QuadNode* node = queue.front();
		queue.pop();

		if (node->go.empty() == false)
		{
			std::vector<GameObject*>::iterator it2 = node->go.begin();
			while (it2 != node->go.end())
			{
				ComponentMesh* cmp_mesh = (ComponentMesh*)(*it2)->GetComponent(Component::MESH);
				if (cmp_cam->culling)
				{
					if (cmp_cam->ContainsAABB(node->bb.GetAABB()))
					{
						if (node->childs.empty())
						{
							cmp_mesh->render = true;
						}
					}
					else
					{
						cmp_mesh->render = false;
					}
				}
				else
				{
					cmp_mesh->render = true;
				}
				++it2;
			}
			
		}
			std::vector<QuadNode*>::iterator it = node->childs.begin();
			while (it != node->childs.end())
			{
				queue.push(*it);
				++it;
			}
	}
}

std::vector<GameObject*> QuadNode::RayPicking(const math::LineSegment & raycast)
{
	vector<GameObject*> hits;

	std::queue<QuadNode*> queue;
	queue.push(this);

	while (queue.empty() == false)
	{
		QuadNode* node = queue.front();
		queue.pop();

		if (node->go.empty() == false)
		{
			std::vector<GameObject*>::iterator it2 = node->go.begin();
			while (it2 != node->go.end())
			{
				ComponentMesh* cmp_mesh = (ComponentMesh*)(*it2)->GetComponent(Component::MESH);
				if (raycast.Intersects(node->bb.GetAABB()))
				{
					if (node->childs.empty())
					{
						hits.push_back((*it2));
						(*it2)->distance_hit = (App->editor->main_camera_component->frustum.pos - cmp_mesh->world_bb.CenterPoint());
					}

				}
				++it2;
			}

		}
		std::vector<QuadNode*>::iterator it = node->childs.begin();
		while (it != node->childs.end())
		{
			queue.push(*it);
			++it;
		}
	}
	return hits;
}


//QUADTREE------------------------------------------------------------------------

Quadtree::Quadtree()
{
	root = nullptr;
}

Quadtree::~Quadtree()
{
	Clear();
}

void Quadtree::Create(float size)
{
	//Remove old Quadtree
	if (root!= nullptr)
	{
		delete root;
	}

	root = new QuadNode(nullptr, size, float2(0,0));
}

bool Quadtree::Insert(GameObject * object)
{
	ComponentMesh* cmp_mesh = (ComponentMesh*)object->GetComponent(Component::MESH);
	if (cmp_mesh != nullptr)
	{
		float3 center_3D = cmp_mesh->world_bb.CenterPoint();
		if (root != nullptr && root->Intersect(float2(center_3D.x,center_3D.z)))
		{
			return root->Insert(object);
		}
	}
	return false;
}

bool Quadtree::Remove(GameObject * object)
{
	ComponentMesh* cmp_mesh = (ComponentMesh*)object->GetComponent(Component::MESH);
	if (cmp_mesh != nullptr)
	{
		float3 center_3D = cmp_mesh->world_bb.CenterPoint();
		if (root != nullptr && root->Intersect(float2(center_3D.x, center_3D.z)))
		{
			return root->Remove(object);
		}
	}
	return false;
}

bool Quadtree::Clear()
{
	if (root != nullptr && root->childs.empty() == false)
	{
		return root->Clear();
	}
	return false;
}

void Quadtree::Render()
{
	if (root != nullptr && root->childs.empty() == false)
	{
		 root->Render();
	}
}

void Quadtree::FrustumCulling(ComponentCamera * cmp_cam) const
{
	if (root != nullptr && root->childs.empty() == false )
	{
		root->FrustumCulling(cmp_cam);
	}
}

std::vector<GameObject*> Quadtree::RayPicking(const math::LineSegment & raycast) const
{
	vector<GameObject*> hits;
	if (root != nullptr && root->childs.empty() == false)
	{
		hits = root->RayPicking(raycast);
	}

	return hits;
}
