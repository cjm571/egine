/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/
#pragma once

#include "StdAfx.h"

class Trajectory
{
// Ctors
public:
	Trajectory();
	Trajectory(double _velocity);
	Trajectory(double _velocity, double _direction);
	~Trajectory();

// Accessors
public:
	double GetVelocity() {return m_velocity;};
	double GetDirection() {return m_direction;};

// Public methods
public:
	HRESULT SetVelocity(double newVelocity);
	HRESULT SetDirection(double newDirection);

// Properties
private:
	// Velocity in m/s
	double m_velocity;
	
	// Direction in radians
	double m_direction;
};
