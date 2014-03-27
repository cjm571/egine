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
	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(CartPoint _center)
	: m_color(D2D1::ColorF::Black), m_mass(1.0), m_shape(PhysCircle)
{
	m_aabb = AABB(_center);
	m_UID = ++prevUID;
}

PhysicsObject::PhysicsObject(AABB _aabb, D2D1::ColorF::Enum _color, eShape _shape)
	: m_color(_color), m_mass(1.0), m_shape(_shape)
{
	m_aabb = AABB(_aabb);
	m_UID = ++prevUID;
}

PhysicsObject::~PhysicsObject()
{
}


/********** PUBLIC METHODS **********/
HRESULT PhysicsObject::SetTrajectory(Trajectory newTrajectory)
{
	HRESULT hr = S_OK;

	m_trajectory = newTrajectory;

	return hr;
}

void PhysicsObject::Move()
{
	double xMovement = m_trajectory.GetXVelocity() * PHYSICS_EPSILON;
	double yMovement = m_trajectory.GetYVelocity() * PHYSICS_EPSILON;
	CartPoint center = m_aabb.GetCenter(Physics);

	// Translate centerpoint based on trajectory. Unit circle ftw
	center.x = center.x + xMovement;
	center.y = center.y + yMovement;
	m_aabb.SetCenter(center);
}

void PhysicsObject::Revert()
{
	double xMovement = m_trajectory.GetXVelocity() * PHYSICS_EPSILON;
	double yMovement = m_trajectory.GetYVelocity() * PHYSICS_EPSILON;
	CartPoint center = m_aabb.GetCenter(Physics);

	// Revert translation based on trajectory
	center.x = center.x - xMovement;
	center.y = center.y - yMovement;
	m_aabb.SetCenter(center);
}

void PhysicsObject::Rebound(eAxis axis)
{
	// X-axis rebounds reflect direction about pi/2
	if (axis == XAxis || axis == BothAxes)
	{
		double theta = m_trajectory.GetTheta();
		m_trajectory.SetTheta((theta * -1) + M_PI);
	}
	// Y-axis rebounds reflect direction about pi
	if (axis == YAxis || axis == BothAxes)
	{
		double theta = m_trajectory.GetTheta();
		m_trajectory.SetTheta(theta * -1);
	}
}