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
	: m_gravity(9.8), m_elapsed(0.0)
{
}

Scene::Scene(UINT _creationFlags)
	: m_elapsed(0.0)
{

	switch (_creationFlags & SC_GRAVITY_MASK)
	{
	case SC_GRAVITY_OFF:	// Zero-gravity
		m_gravity = 0.0;
		break;
	case SC_GRAVITY_EARTH:	// Earth gravity
		m_gravity = 9.8;
		break;
	case SC_GRAVITY_MOON:	// Moon gravity
		m_gravity = 1.622;
		break;
	}
}

Scene::~Scene()
{
	m_physicsObjects.clear();
}


/********** HELPER FUNCTIONS **********/
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
			PhysicsObject* objA = *poItrA;
			PhysicsObject* objB = *poItrB;

			bool skipPair = false;
			// Skip pair on UID match
			if (objA->GetUID() == objB->GetUID())
			{
				skipPair = true;
			}

			// Skip pair on already-exists
			for (pairsItr = collidingPairs.begin(); pairsItr != collidingPairs.end(); ++pairsItr)
			{
				if ((objA->GetUID()==pairsItr->first->GetUID() && objB->GetUID()==pairsItr->second->GetUID()) ||
					(objB->GetUID()==pairsItr->first->GetUID() && objA->GetUID()==pairsItr->second->GetUID()))
				{
					skipPair = true;
				}
			}

			if (skipPair)
			{
				continue;
			}

			bool bColliding = false;

			bColliding = PhysicsObject::CheckOverlap(*objA, *objB);

			// Add UID pair to vector on collision detect
			if (bColliding)
			{
				std::pair<PhysicsObject*,PhysicsObject*> collidingPair;
				collidingPair = std::make_pair(objA, objB);

				collidingPairs.push_back(collidingPair);
			}
		}
	}

	return collidingPairs;
}

std::vector<PhysicsObject*> Scene::CheckOutOfBounds(eAxis axis)
{
	std::vector<PhysicsObject*> vOutOfBounds;

	std::vector<PhysicsObject*>::iterator poItr;
	for (poItr=m_physicsObjects.begin(); poItr!=m_physicsObjects.end(); ++poItr)
	{
		AABB aabb = (*poItr)->GetAABB();
		double upBound = aabb.GetUpperBound();
		double lowBound = aabb.GetLowerBound();
		double leftBound = aabb.GetLeftBound();
		double rightBound = aabb.GetRightBound();
		
		switch (axis)
		{
		// X-coord check
		case XAxis:
			if (leftBound <= 0.0 || rightBound >= SCENE_WIDTH)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		// Y-coord check
		case YAxis:
			if (lowBound <= 0.0 || upBound >= SCENE_HEIGHT)
			{
				vOutOfBounds.push_back(*poItr);
			}
			break;
		// Invalid axis
		case BothAxes:
		case AxisErr:
			// TODO: Log error
			break;
		}
	}

	return vOutOfBounds;
}

eAxis Scene::GetCollisionAxis(std::pair<PhysicsObject*,PhysicsObject*> poPair)
{
	eAxis axis = AxisErr;

	AABB aabbA = poPair.first->GetAABB();
	AABB aabbB = poPair.second->GetAABB();

	// Determine orientation by comparing the depth of the AABB overlap in each axis
	double yDepth = 0.0;
	double xDepth = 0.0;
	
	/*** Y-DEPTH **/
	// B below A
	if ((aabbA.GetLowerBound() - aabbB.GetLowerBound()) >= ERR_COLLISION)
	{
		yDepth = abs(aabbA.GetLowerBound() - aabbB.GetUpperBound());
	}
	// B above A
	else
	{
		yDepth = abs(aabbA.GetUpperBound() - aabbB.GetLowerBound());
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

double Scene::CalcOOBTime(eAxis axis, PhysicsObject obj, double curTime)
{
	double t = -1.0;

	// Calculate AABB intercept with Scene boundary
	Trajectory traj = obj.GetTrajectory();
	std::pair<double,double> intercepts;
	double offset = 0.0;
	
	// Use dist of centerpoint from x=0 as offset
	if (axis == XAxis)
	{
		if (obj.GetAABB().GetCenter().x <= SCENE_WIDTH/2)
		{
			// Just halfwidth for left-side
			offset = -1*(obj.GetAABB().GetWidth()/2);
		}
		else
		{
			// Halfwidth - scene width for right-side
			offset = (obj.GetAABB().GetWidth()/2) - SCENE_WIDTH;
		}
		intercepts = traj.CalcYIntercepts(curTime, offset);
	}
	// Use dist of centerpoint from y=0 as offset
	else // Y-axis
	{
		if (obj.GetAABB().GetCenter().y <= SCENE_HEIGHT/2)
		{
			// Just halfheight for bottom-side
			offset = -1*(obj.GetAABB().GetHeight()/2);
		}
		else
		{
			// Halfheight - scene height for top-side
			offset = (obj.GetAABB().GetHeight()/2) - SCENE_HEIGHT;
		}
		intercepts = traj.CalcXIntercepts(curTime, offset);
	}

	// Use the positive intercept for t
	t = std::max(intercepts.first, intercepts.second);

	return t;
}

/********** PUBLIC METHODS **********/
PHRESULT Scene::AddObject(PhysicsObject* newObject)
{
	PHRESULT hr = S_OK;

	CartPoint aabbMin = newObject->GetAABB().GetBottomLeft();
	CartPoint aabbMax = newObject->GetAABB().GetTopRight();
	
	// Sanity check new physics object properties, add to list on pass
	// Out-of-bounds check
	if (aabbMin.x < 0 || aabbMin.y < 0 ||
		aabbMax.x > SCENE_WIDTH || aabbMax.y > SCENE_HEIGHT)
	{
		//TODO: Logging
		hr = E_FAIL;
	}

	// AABB-overlap check
	if (SUCCEEDED(hr))
	{
		bool bOverlapping = false;

		std::vector<PhysicsObject*>::iterator poItr;
		for (poItr=m_physicsObjects.begin(); poItr!=m_physicsObjects.end(); ++poItr)
		{
			PhysicsObject* curObject = *poItr;
			bOverlapping = PhysicsObject::CheckOverlap(*newObject, *curObject);
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
	double nextStepTime = m_elapsed + TIME_SIM_EPSILON;

	// Move all phys objects before collision checking
	std::vector<PhysicsObject*>::iterator poItr;
	for (poItr=m_physicsObjects.begin(); poItr!=m_physicsObjects.end(); ++poItr)
	{
		(*poItr)->Move(nextStepTime);
	}

	/*** BEGIN Out-of-bounds checks ***/
	std::vector<PhysicsObject*> vOutOfBoundsX;
	std::vector<PhysicsObject*> vOutOfBoundsY;
	vOutOfBoundsX = CheckOutOfBounds(XAxis);
	vOutOfBoundsY = CheckOutOfBounds(YAxis);
	
	// Rebound objects and move them to next TIME_SIM_EPSILON boundary
	double oobTime = -1.0;
	for (poItr=vOutOfBoundsX.begin(); poItr!=vOutOfBoundsX.end(); ++poItr)
	{
		oobTime = CalcOOBTime(XAxis, **poItr, m_elapsed);
		(*poItr)->Rebound(XAxis, oobTime);
		(*poItr)->Move(nextStepTime);
	}

	// Rebound objects and move them to next TIME_SIM_EPSILON boundary
	for (poItr=vOutOfBoundsY.begin(); poItr!=vOutOfBoundsY.end(); ++poItr)
	{
		oobTime = CalcOOBTime(YAxis, **poItr, m_elapsed);
		(*poItr)->Rebound(YAxis, oobTime);
		(*poItr)->Move(nextStepTime);
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
		eAxis axis = GetCollisionAxis(poPair);
		
		// Y-axis collision, revert movement and rebound both objects in y-direction
		if (axis == YAxis || axis == BothAxes)
		{
			// TODO: CalcCollisionTime()
			poPair.first->Rebound(YAxis, m_elapsed);
			poPair.second->Rebound(YAxis, m_elapsed);
		}
		
		// X-axis collision, revert movement and rebound both objects in x-direction
		if (axis == XAxis || axis == BothAxes)
		{
			// TODO: CalcCollisionTime()
			poPair.first->Rebound(XAxis, m_elapsed);
			poPair.second->Rebound(XAxis, m_elapsed);
		}
	}
	/*** END Collision Handling ***/

	// Increment elapsed time
	m_elapsed = nextStepTime;
}
