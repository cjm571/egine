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
	: m_color(D2D1::ColorF::Black), m_mass(1.0), m_shape(PhysCircle)
{
	m_aabb = AABB();
	m_p0 = m_aabb.GetCenter();

	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(CartPoint _center)
	: m_color(D2D1::ColorF::Black), m_mass(1.0), m_shape(PhysCircle)
{
	m_aabb = AABB(_center);
	m_p0 = m_aabb.GetCenter();

	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(AABB _aabb, D2D1::ColorF::Enum _color, eShape _shape)
	: m_color(_color), m_mass(1.0), m_shape(_shape)
{
	m_aabb = AABB(_aabb);
	m_p0 = m_aabb.GetCenter();

	m_UID = ++prevUID;
}

PhysicsObject::~PhysicsObject()
{
}


/********** PUBLIC METHODS **********/
HRESULT PhysicsObject::SetInitialPosition(CartPoint newP0)
{
	HRESULT hr = S_OK;

	// Sanity check
	if (newP0.x < 0 || newP0.y < 0)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		m_p0 = newP0;
	}

	return hr;
}

HRESULT PhysicsObject::SetTrajectory(Trajectory newTrajectory)
{
	HRESULT hr = S_OK;

	m_trajectory = newTrajectory;

	return hr;
}

void PhysicsObject::Move(double timeElapsed)
{
	// Time value to be used in position calculations
	double t = (timeElapsed - m_trajectory.GetT0()) + STEP_EPSILON;

	// Calculate position, relative to starting point, at elapsed + epsilon
	double xRelPos = m_trajectory.SolveX(t);
	double yRelPos = m_trajectory.SolveY(t);

	// Calculate actual position
	double xPos = m_p0.x + xRelPos;
	double yPos = m_p0.y + yRelPos;

	// Set new centerpoint
	CartPoint newCenter = {xPos, yPos};
	m_aabb.SetCenter(newCenter);
}

void PhysicsObject::Revert(double timeElapsed)
{
	// Time value to be used in position calculations
	double t = timeElapsed - m_trajectory.GetT0();

	// Calculate position change relative to t0
	double xRelPos = m_trajectory.SolveX(t);
	double yRelPos = m_trajectory.SolveY(t);

	// Calculate actual position
	double xPos = m_p0.x + xRelPos;
	double yPos = m_p0.y + yRelPos;

	// Set new centerpoint
	CartPoint newCenter = {xPos, yPos};
	m_aabb.SetCenter(newCenter);
}

HRESULT PhysicsObject::Rebound(eAxis axis, double curTime)
{
	HRESULT hr = S_OK;
	double reversedV;
	double instV;

	// TODO: something is wrong here.
	// Add negative of instantaneous velocity as constant, to maintain proper velocity after t0 reset
	instV = m_trajectory.GetVelocity(curTime);
	hr |= m_trajectory.SetConstantFactor(axis, (-1*instV));

	// Reverse linear x-axis velocity factor
	reversedV = -1 * m_trajectory.GetVelocityFactor(axis);
	hr |= m_trajectory.SetVelocityFactor(axis, reversedV);
	
	// Reset trajectory start time
	hr |=m_trajectory.SetT0(curTime);

	// Reset initial position to collision point, as this is essentially a new trajectory
	if(SUCCEEDED(hr))
	{
		CartPoint curPos = m_aabb.GetCenter();
		SetInitialPosition(curPos);
	}

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