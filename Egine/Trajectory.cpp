/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
	: velocity(0.0), direction(0.0)
{
}

Trajectory::Trajectory(double _velocity)
	: velocity(_velocity), direction(0.0)
{
}

Trajectory::Trajectory(double _velocity, double _direction)
	: velocity(_velocity), direction(_direction)
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

	velocity = newVelocity;

	return hr;
}

HRESULT Trajectory::SetDirection(double newDirection)
{
	HRESULT hr = S_OK;

	// Wrap around at 2pi
	while (newDirection >= (2 * M_PI))
	{
		newDirection -= (2 * M_PI);
	}

	direction = newDirection;

	return hr;
}