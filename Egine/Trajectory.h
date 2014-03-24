/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/
#pragma once

#include "StdAfx.h"

class Trajectory : public Quadratic
{
// Ctors
public:
	// Defines initially at-rest trajectory
	Trajectory(double _gravity, CartPoint p0);
	// Defines trajectory moving at given velocity along 0-rad line
	Trajectory(double _gravity, double _velocity);
	// Defines trajectory moving at given velocity in given direction
	Trajectory(double _gravity, double _velocity, double _direction);

	// Destructor
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
	// X-component of velocity vector
	double m_Vx;
	// Y-component of velocity vectory
	double m_Vy;
	// Current gravity imposed on trajectory
	double m_g;
};
