/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/

#include "MainFrame.h"
#include "Scene.h"

const double Scene::CornerHitMargin = 0.1;

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
	PhysPoint centerA = aabbA.GetCenter(AABB::Physics);
	double upBoundB = aabbB.GetUpperBound(AABB::Physics);
	double lowBoundB = aabbB.GetLowerBound(AABB::Physics);
	double leftBoundB = aabbB.GetLeftBound();
	double rightBoundB = aabbB.GetRightBound();
	PhysPoint centerB = aabbB.GetCenter(AABB::Physics);

	// First check if A and B are aligned vertically
	if (((upBoundA >= lowBoundB) && (upBoundA <= upBoundB)) ||
		((lowBoundA >= lowBoundB) && (lowBoundA <= upBoundB)))
	{
		// Check for BB overlap if A is left of B
		if ((centerA.x < centerB.x) && (rightBoundA > leftBoundB))
		{
			bOverlapping = true;
		}
		// Check for BB overlap if B is left of A
		if ((centerB.x < centerA.x) && (rightBoundB > leftBoundA))
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

std::vector<std::pair<PhysicsObject*,PhysicsObject*>> Scene::CheckCollisions()
{
	std::vector<std::pair<PhysicsObject*,PhysicsObject*>> collidingPairs;

	std::vector<PhysicsObject*>::iterator poItrA;
	std::vector<PhysicsObject*>::iterator poItrB;
	for (poItrA=m_physicsObjects.begin(); poItrA!=m_physicsObjects.end(); ++poItrA)
	{
		for (poItrB=m_physicsObjects.begin(); poItrB!=m_physicsObjects.end(); ++poItrB)
		{
			// Dereference iterators and compare AABBs of contained phys objects
			PhysicsObject* pObjectA = (*poItrA);
			PhysicsObject* pObjectB = (*poItrB);

			// Skip pair on UID match
			if (pObjectA->GetUID() == pObjectB->GetUID())
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
			if (leftBound < 0.0 || rightBound > MainFrame::width)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		// Y-coord check
		case YAxis:
			if (lowBound < 0.0 || upBound > MainFrame::height)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		}
	}

	return vOutOfBounds;
}

eCollisionAxis Scene::CheckCollisionAxis(std::pair<PhysicsObject*,PhysicsObject*> poPair)
{
	eCollisionAxis axis = AxisErr;

	AABB aabbA = poPair.first->GetAABB();
	AABB aabbB = poPair.second->GetAABB();

	// Determine orientation by comparing the depth of the AABB overlap in each axis
	double yDepth = 0.0;
	double xDepth = 0.0;

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

	// Corner-hit
	if (1-abs(yDepth/xDepth) < CornerHitMargin)
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
		eCollisionAxis axis = CheckCollisionAxis(poPair);

		// Y-axis collision, revert movement and rebound both objects in y-direction
		if (axis == YAxis || axis == BothAxes)
		{
			poPair.first->Revert();
			poPair.second->Revert();
			poPair.first->Rebound(YAxis);
			poPair.second->Rebound(YAxis);
			poPair.first->Move();
			poPair.second->Move();			
		}
		
		// X-axis collision, revert movement and rebound both objects in x-direction
		if (axis == XAxis || axis == BothAxes)
		{
			poPair.first->Revert();
			poPair.second->Revert();
			poPair.first->Rebound(XAxis);
			poPair.second->Rebound(XAxis);
			poPair.first->Move();
			poPair.second->Move();
		}
	}
	/*** END Collision Handling ***/
}
