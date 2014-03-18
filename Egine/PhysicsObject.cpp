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

PhysicsObject::PhysicsObject(AABB _aabb, D2D1::ColorF::Enum _color, Shape _shape)
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

	double newDirection = newTrajectory.GetDirection();
	double newVelocity = newTrajectory.GetVelocity();

	hr |= m_trajectory.SetDirection(newDirection);
	hr |= m_trajectory.SetVelocity(newVelocity);

	return hr;
}

void PhysicsObject::Move()
{
	double direction = m_trajectory.GetDirection();
	double velocity = m_trajectory.GetVelocity();
	CartPoint center = m_aabb.GetCenter(AABB::Physics);

	// Translate centerpoint based on trajectory. Unit circle ftw
	center.x = center.x + (cos(direction) * velocity);
	center.y = center.y + (sin(direction) * velocity);
	m_aabb.SetCenter(center);
}

void PhysicsObject::Revert()
{
	double direction = m_trajectory.GetDirection();
	double velocity = m_trajectory.GetVelocity();
	CartPoint center = m_aabb.GetCenter(AABB::Physics);

	// Revert translation based on trajectory
	center.x = center.x - (cos(direction) * velocity);
	center.y = center.y - (sin(direction) * velocity);
	m_aabb.SetCenter(center);
}

void PhysicsObject::Rebound(eCollisionAxis axis)
{
	// X-axis rebounds reflect direction about pi/2
	if (axis == XAxis || axis == BothAxes)
	{
		double direction = m_trajectory.GetDirection();
		m_trajectory.SetDirection((direction * -1) + M_PI);
	}
	// Y-axis rebounds reflect direction about pi
	if (axis == YAxis || axis == BothAxes)
	{
		double direction = m_trajectory.GetDirection();
		m_trajectory.SetDirection(direction * -1);
		SetTrajectory(m_trajectory);
	}
}