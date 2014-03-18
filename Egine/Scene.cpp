/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/

#include "Scene.h"

// Initialize static members
const double Scene::CornerHitMargin = 0.1;

/********** CTORS **********/
Scene::Scene()
	: m_gravity(9.8)
{
}

Scene::Scene(UINT _creationFlags)
	: m_gravity(9.8)
{
	// 0-gravity
	if ((_creationFlags & SC_GRAVITY_MASK) == SC_GRAVITY_OFF)
	{
		m_gravity = 0.0;
	}
}

Scene::~Scene()
{
	m_physicsObjects.clear();
}


/********** HELPER FUNCTIONS **********/
bool Scene::CheckOverlap(AABB a, AABB b)
{
	/*
	bool alignedTop = false;
	bool alignedBottom = false;

	// Vertical alignment
	// alignedA: B lowerbound within error bounds of A upperbound
	alignedTop = (aabbB.GetLowerBound(AABB::Physics) - aabbA.GetUpperBound(AABB::Physics)) <= ERR_COLLISION;
	
	// alignedB: B upperbound within error bounds of A lowerbound
	alignedBottom = (aabbA.GetLowerBound(AABB::Physics) - aabbB.GetUpperBound(AABB::Physics)) <= ERR_COLLISION;

	if (alignedTop && alignedBottom)
	{
		// Horizontal overlap
		// A left of B
		if (((aabbB.GetLeftBound() - aabbA.GetRightBound()) <= ERR_COLLISION) &&
			(aabbA.GetCenter(AABB::Physics).x < aabbB.GetCenter(AABB::Physics).x))
		{
			overlapping = true;
		}
		// B left of A
		if (((aabbA.GetLeftBound() - aabbB.GetRightBound()) <= ERR_COLLISION) &&
			(aabbA.GetCenter(AABB::Physics).x > aabbB.GetCenter(AABB::Physics).x))
		{
			overlapping = true;
		}
	}
	*/

	double centerDist = 0.0;
	bool xOverlap = false;
	bool yOverlap = false;
	bool isOverlapping = false;

	// Check X-axis overlap
	centerDist = abs(a.GetCenter(AABB::Physics).x - b.GetCenter(AABB::Physics).x);
	if (centerDist - ((a.GetWidth()/2 + b.GetWidth()/2)) <= ERR_COLLISION)
	{
		xOverlap = true;
	}

	// Check Y-axis overlap
	centerDist = abs(a.GetCenter(AABB::Physics).y - b.GetCenter(AABB::Physics).y);
	if ((centerDist - (a.GetHeight()/2 + b.GetHeight()/2)) <= ERR_COLLISION)
	{
		yOverlap = true;
	}
	
	// AABBs must overlap on ALL AXES for actual overlap to occur
	isOverlapping = xOverlap && yOverlap;
	return isOverlapping;
}

bool Scene::CheckOverlap(PhysicsObject* poA, PhysicsObject* poB)
{
	bool bOverlapping = false; 

	AABB aabbA = poA->GetAABB();
	AABB aabbB = poB->GetAABB();

	bOverlapping = CheckOverlap(aabbA, aabbB);

	return bOverlapping;
}

std::vector<std::pair<PhysicsObject*,PhysicsObject*>> Scene::CheckCollisions()
{
	std::vector<std::pair<PhysicsObject*,PhysicsObject*>> collidingPairs;
	std::vector<std::pair<PhysicsObject*,PhysicsObject*>>::iterator pairsItr;

	std::vector<PhysicsObject*>::iterator poItrA;
	std::vector<PhysicsObject*>::iterator poItrB;
	for (poItrA=m_physicsObjects.begin(); poItrA!=m_physicsObjects.end(); ++poItrA)
	{
		for (poItrB=m_physicsObjects.begin(); poItrB!=m_physicsObjects.end(); ++poItrB)
		{
			// Dereference iterators and compare AABBs of contained phys objects
			PhysicsObject* pObjectA = (*poItrA);
			PhysicsObject* pObjectB = (*poItrB);

			bool skipPair = false;
			// Skip pair on UID match
			if (pObjectA->GetUID() == pObjectB->GetUID())
			{
				skipPair = true;
			}

			// Skip pair on already-exists
			for (pairsItr = collidingPairs.begin(); pairsItr != collidingPairs.end(); ++pairsItr)
			{
				if ((pObjectA->GetUID()==pairsItr->first->GetUID() && pObjectB->GetUID()==pairsItr->second->GetUID()) ||
					(pObjectB->GetUID()==pairsItr->first->GetUID() && pObjectA->GetUID()==pairsItr->second->GetUID()))
				{
					skipPair = true;
				}
			}

			if (skipPair)
			{
				continue;
			}

			bool bColliding = false;

			bColliding = CheckOverlap(pObjectA, pObjectB);

			// Add UID pair to vector on collision detect
			if (bColliding)
			{
				std::pair<PhysicsObject*,PhysicsObject*> collidingPair;
				collidingPair = std::make_pair(pObjectA, pObjectB);

				collidingPairs.push_back(collidingPair);
			}
		}
	}

	return collidingPairs;
}

std::vector<PhysicsObject*> Scene::CheckOutOfBounds(eCollisionAxis axis)
{
	std::vector<PhysicsObject*> vOutOfBounds;

	std::vector<PhysicsObject*>::iterator poItr;
	for (poItr=m_physicsObjects.begin(); poItr!=m_physicsObjects.end(); ++poItr)
	{
		AABB aabb = (*poItr)->GetAABB();
		double upBound = aabb.GetUpperBound(AABB::Physics);
		double lowBound = aabb.GetLowerBound(AABB::Physics);
		double leftBound = aabb.GetLeftBound();
		double rightBound = aabb.GetRightBound();
		
		switch (axis)
		{
		// X-coord check
		case XAxis:
			if (leftBound < 0.0 || rightBound > SCENE_WIDTH)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		// Y-coord check
		case YAxis:
			if (lowBound < 0.0 || upBound > SCENE_HEIGHT)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		}
	}

	return vOutOfBounds;
}

eCollisionAxis Scene::GetCollisionAxis(std::pair<PhysicsObject*,PhysicsObject*> poPair)
{
	eCollisionAxis axis = AxisErr;

	AABB aabbA = poPair.first->GetAABB();
	AABB aabbB = poPair.second->GetAABB();

	// Determine orientation by comparing the depth of the AABB overlap in each axis
	double yDepth = 0.0;
	double xDepth = 0.0;

	/*
	// A above and right of B
	if (aabbA.GetCenter(AABB::Physics).y >= aabbB.GetUpperBound(AABB::Physics) &&
		aabbA.GetCenter(AABB::Physics).x >= aabbB.GetRightBound())
	{
		yDepth = aabbB.GetUpperBound(AABB::Physics) - aabbA.GetLowerBound(AABB::Physics);
		xDepth = aabbB.GetRightBound() - aabbA.GetLeftBound();
	}
	// A above and left of B
	if (aabbA.GetCenter(AABB::Physics).y >= aabbB.GetUpperBound(AABB::Physics) &&
		aabbA.GetCenter(AABB::Physics).x <= aabbB.GetLeftBound())
	{
		yDepth = aabbB.GetUpperBound(AABB::Physics) - aabbA.GetLowerBound(AABB::Physics);
		xDepth = aabbB.GetLeftBound() - aabbA.GetRightBound();
	}
	// A below and right of B
	if (aabbA.GetCenter(AABB::Physics).y <= aabbB.GetLowerBound(AABB::Physics) &&
		aabbA.GetCenter(AABB::Physics).x >= aabbB.GetRightBound())
	{
		yDepth = aabbB.GetLowerBound(AABB::Physics) - aabbA.GetUpperBound(AABB::Physics);
		xDepth = aabbB.GetRightBound() - aabbA.GetLeftBound();
	}
	// A below and left of B
	if (aabbA.GetCenter(AABB::Physics).y <= aabbB.GetLowerBound(AABB::Physics) &&
		aabbA.GetCenter(AABB::Physics).x <= aabbB.GetLeftBound())
	{
		yDepth = aabbB.GetLowerBound(AABB::Physics) - aabbA.GetUpperBound(AABB::Physics);
		xDepth = aabbB.GetLeftBound() - aabbA.GetRightBound();
	}
	*/

	/*** Y-DEPTH **/
	// B below A
	if ((aabbA.GetLowerBound(AABB::Physics) - aabbB.GetLowerBound(AABB::Physics)) >= ERR_COLLISION)
	{
		yDepth = abs(aabbA.GetLowerBound(AABB::Physics) - aabbB.GetUpperBound(AABB::Physics));
	}
	// B above A
	else
	{
		yDepth = abs(aabbA.GetUpperBound(AABB::Physics) - aabbB.GetLowerBound(AABB::Physics));
	}

	/*** X-DEPTH ***/
	// B right of A
	if ((aabbA.GetLeftBound() - aabbB.GetLeftBound()) <= ERR_COLLISION)
	{
		xDepth = abs(aabbA.GetRightBound() - aabbB.GetLeftBound());
	}
	// B left of A
	else
	{
		xDepth = abs(aabbA.GetLeftBound() - aabbB.GetRightBound());
	}

	// Corner-hit
	if (abs(1-abs(yDepth/xDepth)) < CornerHitMargin)
	{
		axis = BothAxes;
	}
	// Y-collision
	else if (yDepth < xDepth)
	{
		axis = YAxis;
	}
	// X-collision
	else if (xDepth < yDepth)
	{
		axis = XAxis;
	}

	return axis;
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
		aabbMax.x > SCENE_WIDTH || aabbMax.y > SCENE_HEIGHT)
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

void Scene::Step()
{
	// Move all phys objects before collision checking
	std::vector<PhysicsObject*>::iterator poItr;
	for (poItr=m_physicsObjects.begin(); poItr!=m_physicsObjects.end(); ++poItr)
	{
		(*poItr)->Move();
	}

	/*** BEGIN Out-of-bounds checks ***/
	std::vector<PhysicsObject*> vOutOfBoundsX;
	std::vector<PhysicsObject*> vOutOfBoundsY;
	vOutOfBoundsX = CheckOutOfBounds(XAxis);
	vOutOfBoundsY = CheckOutOfBounds(YAxis);

	// Revert movements of all x-coord out-of-bounds objects, and "bounce" them back
	for (poItr=vOutOfBoundsX.begin(); poItr!=vOutOfBoundsX.end(); ++poItr)
	{
		(*poItr)->Revert();
		(*poItr)->Rebound(XAxis);
		(*poItr)->Move();
	}

	// Revert movements of all y-coord out-of-bounds objects, and "bounce" them back
	for (poItr=vOutOfBoundsY.begin(); poItr!=vOutOfBoundsY.end(); ++poItr)
	{
		(*poItr)->Revert();
		(*poItr)->Rebound(YAxis);
		(*poItr)->Move();
	}
	/*** END Out-of-bounds checks ***/

	/*** BEGIN Collision Handling ***/
	std::vector<std::pair<PhysicsObject*, PhysicsObject*>> vCollidingPairs;
	std::vector<std::pair<PhysicsObject*, PhysicsObject*>>::iterator vPairsItr;
	vCollidingPairs = CheckCollisions();

	for (vPairsItr=vCollidingPairs.begin(); vPairsItr!=vCollidingPairs.end(); ++vPairsItr)
	{
		std::pair<PhysicsObject*, PhysicsObject*> poPair = (*vPairsItr);

		// Determine axis of collision, corner hits will rebound on both axes
		eCollisionAxis axis = GetCollisionAxis(poPair);

		// Y-axis collision, revert movement and rebound both objects in y-direction
		if (axis == YAxis || axis == BothAxes)
		{
			poPair.first->Rebound(YAxis);
			poPair.second->Rebound(YAxis);
			poPair.first->Move();
			poPair.second->Move();
		}
		
		// X-axis collision, revert movement and rebound both objects in x-direction
		if (axis == XAxis || axis == BothAxes)
		{
			poPair.first->Rebound(XAxis);
			poPair.second->Rebound(XAxis);
			poPair.first->Move();
			poPair.second->Move();
		}
	}
	/*** END Collision Handling ***/
}
