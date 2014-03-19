/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
	: m_velocity(0.0), m_direction(0.0)
{
}

Trajectory::Trajectory(double _velocity)
	: m_velocity(_velocity), m_direction(0.0)
{
}

Trajectory::Trajectory(double _velocity, double _direction)
	: m_velocity(_velocity), m_direction(_direction)
{
}

Trajectory::~Trajectory()
{
}


/********** PUBLIC METHODS **********/
HRESULT Trajectory::SetVelocity(double newVelocity)
{
	HRESULT hr = S_OK;
	
	// Sanity check
	// Speed of light
	if (newVelocity > C )
	{
		hr = E_FAIL;
		MessageBoxA(NULL,"Object exceeding speed of light!", "Causality Violation", MB_OK);
	}

	m_velocity = newVelocity;

	return hr;
}

HRESULT Trajectory::SetDirection(double newDirection)
{
	HRESULT hr = S_OK;

	m_direction = WrapAngle(newDirection);

	return hr;
}