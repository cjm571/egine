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

void PhysicsObject::Move(double timeElapsed)
{
	// Calculate position, relative to starting point, at elapsed + epsilon
	double xRelPos = m_trajectory.SolveX(timeElapsed + STEP_EPSILON);
	double yRelPos = m_trajectory.SolveY(timeElapsed + STEP_EPSILON);

	// Calculate actual position
	CartPoint p0 = m_trajectory.GetInitialPosition();
	double xPos = p0.x + xRelPos;
	double yPos = p0.y + yRelPos;

	// Set new centerpoint
	CartPoint newCenter = {xPos, yPos};
	m_aabb.SetCenter(newCenter);

	// Set new theta via tangent of parametric function
	double newTheta = m_trajectory.GetTangentAngle(timeElapsed + STEP_EPSILON);
	m_trajectory.SetTheta(newTheta);
}

void PhysicsObject::Revert(double timeElapsed)
{
	// Calculate position at elapsed + epsilon
	double xRelPos = m_trajectory.SolveX(timeElapsed);
	double yRelPos = m_trajectory.SolveY(timeElapsed);

	// Calculate actual position
	CartPoint p0 = m_trajectory.GetInitialPosition();
	double xPos = p0.x + xRelPos;
	double yPos = p0.y + yRelPos;

	// Set new centerpoint
	CartPoint newCenter = {xPos, yPos};
	m_aabb.SetCenter(newCenter);

	// Set new theta via tangent of parametric function
	double newTheta = m_trajectory.GetTangentAngle(timeElapsed);
	m_trajectory.SetTheta(newTheta);
}

void PhysicsObject::Rebound(eAxis axis)
{
	// Reset initial position, as this is essentially a new trajectory
	CartPoint curPos = m_aabb.GetCenter(Physics);
	m_trajectory.SetInitialPosition(curPos);
	
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