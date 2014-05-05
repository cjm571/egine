/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-16 *
*************************/

#include "PhysicsObject.h"

// Initialize UID tracker
ULONG PhysicsObject::prevUID = 0;

/********** CTORS **********/
PhysicsObject::PhysicsObject()
	: m_color(Black), m_mass(1.0), m_shape(PhysCircle)
{
	m_aabb = AABB();
	m_trajectory = Trajectory(m_aabb.GetCenter(), TIME_SIM_START);

	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(CartPoint _center)
	: m_color(Black), m_mass(1.0), m_shape(PhysCircle)
{
	m_aabb = AABB(_center);
	m_trajectory = Trajectory(_center, TIME_SIM_START);

	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(AABB _aabb, Color _color, eShape _shape)
	: m_color(_color), m_mass(1.0), m_shape(_shape)
{
	m_aabb = AABB(_aabb);
	m_trajectory = Trajectory(m_aabb.GetCenter(), TIME_SIM_START);

	m_UID = ++prevUID;
}

PhysicsObject::~PhysicsObject()
{
}


/********** ACCESSORS **********/
CartPoint PhysicsObject::GetInitialPosition()
{
	CartPoint p0;
	
	p0 = m_trajectory.GetInitialPosition(TIME_SIM_START);

	return p0;
}


/********** MUTATORS **********/
PHRESULT PhysicsObject::SetTrajectory(Trajectory newTraj)
{
	PHRESULT hr = S_OK;

	m_trajectory = newTraj;

	return hr;
}

void PhysicsObject::SetColor(Color newColor)
{
	m_color = newColor;
}


/********** PUBLIC METHODS **********/
void PhysicsObject::Move(double t)
{	
	// Calculate centerpoint at the given time
	CartPoint newCenter = m_trajectory.GetPositionAt(t);

	// Set calculated point as new AABB centerpoint
	m_aabb.SetCenter(newCenter);
}

PHRESULT PhysicsObject::Rebound(eAxis axis, double reboundTime)
{
	PHRESULT hr = S_OK;	

	// Gather data members that will compose to next subtrajectory
	double aX = m_trajectory.GetAcceleration(XAxis, reboundTime);
	double aY = m_trajectory.GetAcceleration(YAxis, reboundTime);
	double vX = m_trajectory.GetVelocity(XAxis, reboundTime);
	double vY = m_trajectory.GetVelocity(YAxis, reboundTime);
	CartPoint p0 = m_trajectory.GetPositionAt(reboundTime);

	// Invert axis velocity based on collision axis
	switch (axis)
	{
	case XAxis:
		vX = -1 * vX;
		break;
	case YAxis:
		vY = -1 * vY;
		break;
	default:
		hr = E_FAIL;
		break;
	}

	// Create Quadratics based on properly inverted velocities
	Quadratic xQuad = Quadratic(0.5*aX, vX, p0.x);
	Quadratic yQuad = Quadratic(0.5*aY, vY, p0.y);

	// Create new subtrajectory for post-rebound
	SubTrajectory newSubTraj = SubTrajectory(xQuad, yQuad, reboundTime);

	// Push new subtrajectory onto deque
	m_trajectory.PushSubTrajectory(newSubTraj);

	return hr;
}


/********** PUBLIC STATICS **********/
bool PhysicsObject::CheckOverlap(PhysicsObject a, PhysicsObject b)
{
	bool bOverlapping = false; 

	AABB aabbA = a.GetAABB();
	AABB aabbB = b.GetAABB();

	bOverlapping = AABB::CheckOverlap(aabbA, aabbB);

	return bOverlapping;
}

/*
std::pair<CartPoint,CartPoint> PhysicsObject::CalcActualCollisionPosition(PhysicsObject a, PhysicsObject b)
{
	std::pair<CartPoint,CartPoint> collisionCoords;

	// Find intercept of the two Trajectories
	std::vector<CartPoint> intersects;
	intersects = Trajectory::CalcIntersects(a.GetTrajectory(), b.GetTrajectory());

	// TODO: lots of math to get overlap point
	// FORNOW: "stepping" backwards from intersect point until no longer overlapping
	

	return collisionCoords;
}
*/