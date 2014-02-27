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


/********** HELPER FUNCTIONS **********/
bool Scene::CheckOverlap(AABB aabbA, AABB aabbB)
{
	bool bOverlapping = false;

	double upBoundA = aabbA.GetUpperBound(AABB::Physics);
	double lowBoundA = aabbA.GetLowerBound(AABB::Physics);
	double leftBoundA = aabbA.GetLeftBound();
	double rightBoundA = aabbA.GetRightBound();
	double upBoundB = aabbB.GetUpperBound(AABB::Physics);
	double lowBoundB = aabbB.GetLowerBound(AABB::Physics);
	double leftBoundB = aabbB.GetLeftBound();
	double rightBoundB = aabbB.GetRightBound();

	// First check if A and B are aligned vertically
	if (((upBoundA >= lowBoundB) && (upBoundA <= upBoundB)) ||
		((lowBoundA >= lowBoundB) && (lowBoundA <= upBoundB)))
	{
		// Check for BB overlap presuming A is left of B
		if (rightBoundA > leftBoundB)
		{
			bOverlapping = true;
		}
		// Check for BB overlap presuming B is left of A
		if (rightBoundB > leftBoundA)
		{
			bOverlapping = true;
		}
	}

	return bOverlapping;
}

bool Scene::CheckOverlap(PhysicsObject* poA, PhysicsObject* poB)
{
	bool bOverlapping = false;

	AABB aabbA = poA->GetAABB();
	AABB aabbB = poB->GetAABB();

	bOverlapping = CheckOverlap(aabbA, aabbB);

	return bOverlapping;
}


/********** PUBLIC METHODS **********/
HRESULT Scene::AddObject(PhysicsObject* newObject)
{
	HRESULT hr = S_OK;

	PhysPoint aabbMin = newObject->GetAABB().GetBottomLeft(AABB::Physics);
	PhysPoint aabbMax = newObject->GetAABB().GetTopRight(AABB::Physics);
	
	// Sanity check new physics object properties, add to list on pass
	// Out-of-bounds check
	if (aabbMin.x < 0 || aabbMin.y < 0 ||
		aabbMax.x > MainFrame::width || aabbMax.y > MainFrame::height)
	{
		MessageBoxA(NULL, "Cannot add object.\nBounding Box extends past scene perimeter.", NULL, MB_OK);
		hr = E_FAIL;
	}

	// AABB-overlap check
	if (SUCCEEDED(hr))
	{
		bool bOverlapping = false;

		std::vector<PhysicsObject*>::iterator poItr;
		for (poItr=m_physicsObjects.begin(); poItr!=m_physicsObjects.end(); ++poItr)
		{
			bOverlapping = CheckOverlap(newObject, (*poItr));
			if (bOverlapping)
			{
				hr = E_FAIL;
				break;
			}
		}
	}

	if (SUCCEEDED(hr))
	{
		// Sanity checks passed, add object to list
		m_physicsObjects.push_back(newObject);
	}

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

			bool bColliding = false;

			bColliding = CheckOverlap(pObjectA, pObjectB);

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
