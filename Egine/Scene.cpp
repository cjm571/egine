/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/

#include "MainFrame.h"
#include "Scene.h"

/********** CTORS **********/
Scene::Scene()
{
}

Scene::~Scene()
{
	m_physicsObjects.clear();
}


/********** PUBLIC METHODS **********/
HRESULT Scene::AddObject(PhysicsObject* newObject)
{
	HRESULT hr = S_OK;

	PhysPoint aabbMin = newObject->GetAABB().GetMin();
	PhysPoint aabbMax = newObject->GetAABB().GetMax();
	
	// Sanity check new physics object properties, add to list on pass
	// Out-of-bounds check
	if (aabbMin.x < 0 || aabbMin.y < 0 ||
		aabbMax.x > MainFrame::width || aabbMax.y > MainFrame::height)
	{
		MessageBoxA(NULL, "Cannot add object.\nBounding Box extends past scene perimeter.", NULL, MB_OK);
		hr = E_FAIL;
	}

	// AABB Overlap check
	if (SUCCEEDED(hr))
	{
		//TODO: Implement
	}

	m_physicsObjects.push_back(newObject);

	return hr;
}

std::vector<std::pair<ULONG,ULONG>> Scene::CheckCollisions()
{
	std::vector<std::pair<ULONG,ULONG>> collidingPairs;

	std::vector<PhysicsObject*>::iterator poItrA;
	std::vector<PhysicsObject*>::iterator poItrB;
	for (poItrA=m_physicsObjects.begin(); poItrA!=m_physicsObjects.end(); ++poItrA)
	{
		for (poItrB=m_physicsObjects.begin(); poItrB!=m_physicsObjects.end(); ++poItrB)
		{
			// Dereference iterators and compare AABBs of contained phys objects
			PhysicsObject* pObjectA = (*poItrA);
			PhysicsObject* pObjectB = (*poItrB);

			AABB aabbA = pObjectA->GetAABB();
			AABB aabbB = pObjectB->GetAABB();

			bool bColliding = false;
			// First check if A and B are aligned vertically
			if (((aabbA.GetMax().y >= aabbB.GetMin().y) && (aabbA.GetMax().y <= aabbB.GetMax().y)) ||
				((aabbA.GetMin().y >= aabbB.GetMin().y) && (aabbA.GetMin().y <= aabbB.GetMax().y)))
			{
				// Check for BB overlap presuming A is left of B
				if (aabbA.GetMax().x > aabbB.GetMin().x)
				{
					bColliding = true;
				}
				// Check for BB overlap presuming B is left of A
				if (aabbB.GetMax().x > aabbA.GetMin().x)
				{
					bColliding = true;
				}
			}

			// Add UID pair to vector on collision detect
			if (bColliding)
			{
				ULONG uidA = pObjectA->GetUID();
				ULONG uidB = pObjectB->GetUID();

				std::pair<ULONG,ULONG> uidPair;
				uidPair = std::make_pair(uidA, uidB);

				collidingPairs.push_back(uidPair);
			}
		}
	}

	return collidingPairs;
}

HRESULT Scene::ImposeGravity()
{
	HRESULT hr = S_OK;

	std::vector<PhysicsObject*> physicsObjects = GetObjects();

	std::vector<PhysicsObject*>::iterator poItr;
	for (poItr = physicsObjects.begin(); poItr != physicsObjects.end(); ++poItr)
	{
		PhysicsObject* curObject = (*poItr);

		Trajectory traj = curObject->GetTrajectory();

		//TODO: Calculate trajectory change due to gravity
	}

	return hr;
}
