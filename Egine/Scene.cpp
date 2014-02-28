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

std::vector<PhysicsObject*> Scene::CheckOutOfBounds(BoundsType boundsType)
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
		
		switch (boundsType)
		{
		// X-coord check
		case Scene::XBounds:
			if (leftBound < 0.0 || rightBound > MainFrame::width)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		// Y-coord check
		case Scene::YBounds:
			if (lowBound < 0.0 || upBound > MainFrame::height)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		}
	}

	return vOutOfBounds;
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

	// Out-of-bounds checks
	std::vector<PhysicsObject*> vOutOfBoundsX;
	std::vector<PhysicsObject*> vOutOfBoundsY;
	vOutOfBoundsX = CheckOutOfBounds(Scene::XBounds);
	vOutOfBoundsY = CheckOutOfBounds(Scene::YBounds);

	// Revert movements of all x-coord out-of-bounds objects, and "bounce" them back
	for (poItr=vOutOfBoundsX.begin(); poItr!=vOutOfBoundsX.end(); ++poItr)
	{
		(*poItr)->Revert();

		// Invert trajectory direction
		Trajectory trajectory = (*poItr)->GetTrajectory();
		double direction = trajectory.GetDirection();
		double velocity = trajectory.GetVelocity();
		trajectory.SetDirection(direction * -1);
		trajectory.SetVelocity(velocity * -1);
		(*poItr)->ChangeTrajectory(trajectory);

		// Move in new direction
		(*poItr)->Move();
	}

	// Revert movements of all y-coord out-of-bounds objects, and "bounce" them back
	for (poItr=vOutOfBoundsY.begin(); poItr!=vOutOfBoundsY.end(); ++poItr)
	{
		(*poItr)->Revert();

		// Invert trajectory direction
		Trajectory trajectory = (*poItr)->GetTrajectory();
		double direction = trajectory.GetDirection();
		trajectory.SetDirection(direction * -1);
		(*poItr)->ChangeTrajectory(trajectory);

		// Move in new direction
		(*poItr)->Move();
	}

	std::vector<std::pair<PhysicsObject*, PhysicsObject*>> vCollidingPairs;
	vCollidingPairs = CheckCollisions();

	//TODO: Handle collisions
}
