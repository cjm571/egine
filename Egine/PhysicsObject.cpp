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
	SetInitialPosition(m_aabb.GetCenter());

	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(CartPoint _center)
	: m_color(Black), m_mass(1.0), m_shape(PhysCircle)
{
	m_aabb = AABB(_center);
	SetInitialPosition(m_aabb.GetCenter());

	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(AABB _aabb, Color _color, eShape _shape)
	: m_color(_color), m_mass(1.0), m_shape(_shape)
{
	m_aabb = AABB(_aabb);
	SetInitialPosition(m_aabb.GetCenter());

	m_UID = ++prevUID;
}

PhysicsObject::~PhysicsObject()
{
}


/********** ACCESSORS **********/
CartPoint PhysicsObject::GetInitialPosition()
{
	CartPoint p0;
	
	p0.x = m_trajectory.GetConstantFactor(XAxis);
	p0.y = m_trajectory.GetConstantFactor(YAxis);

	return p0;
}


/********** MUTATORS **********/
PHRESULT PhysicsObject::SetInitialPosition(CartPoint newP0)
{
	PHRESULT hr = S_OK;
	
	hr |= m_trajectory.SetConstantFactor(XAxis, newP0.x);
	hr |= m_trajectory.SetConstantFactor(YAxis, newP0.y);

	return hr;
}

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
	
	// Calculate coords of p0 reflected over the collision line
	double collisionLine;
	double offset;
	CartPoint reflectedp0;
	CartPoint oldp0 = GetInitialPosition();
	CartPoint reboundCenterpoint = m_trajectory.GetPositionAt(reboundTime);
	if (axis == XAxis)
	{		
		// Left-side rebound 
		if (oldp0.x > reboundCenterpoint.x)
		{
			offset = -1*(m_aabb.GetWidth()/2);
			collisionLine = reboundCenterpoint.x + offset;
			reflectedp0.x = collisionLine - abs(oldp0.x - collisionLine) + m_aabb.GetWidth();
		}
		else // Right-side rebound
		{
			offset = m_aabb.GetWidth()/2;
			collisionLine = reboundCenterpoint.x + offset;
			reflectedp0.x = collisionLine + abs(oldp0.x - collisionLine) - m_aabb.GetWidth();
		}
		reflectedp0.y = oldp0.y;
	}
	else // Y-axis
	{
		// Bottom-side rebound
		if (oldp0.y > reboundCenterpoint.y)
		{
			offset = -1*(m_aabb.GetHeight()/2);
			collisionLine = reboundCenterpoint.y + offset;
			reflectedp0.y = collisionLine - abs(oldp0.y - collisionLine) + m_aabb.GetHeight();
		}
		else // Top-side rebound
		{
			offset = m_aabb.GetHeight()/2;
			collisionLine = reboundCenterpoint.y + offset;
			reflectedp0.y = collisionLine + abs(oldp0.y - collisionLine) - m_aabb.GetHeight();
		}
		reflectedp0.x = oldp0.x;
	}

	// Set new p0
	hr |= SetInitialPosition(reflectedp0);

	if (SUCCEEDED(hr))
	{
		// Calculate new linear velocity factor
		// c == constFactor + offsetFromEdge
		// 0 = at^2 + bt + c
		// bt = -at^2 - c
		// b = -at - (c/t)
		double a = m_trajectory.GetQuadraticFactor(axis);
		double c = m_trajectory.GetConstantFactor(axis) + offset;
		double newB = (-1*a*reboundTime) - (c/reboundTime);

		// Set new linear velocity factor
		hr |= m_trajectory.SetVelocityFactor(axis, newB);
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