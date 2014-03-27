/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/
#pragma once

#include "StdAfx.h"

class Trajectory : public Parametric
{
// Ctors
public:
	// Default Construct
	// Defines initially at-rest trajactory in zero-gravity
	Trajectory();
	// Defines initially at-rest trajectory
	Trajectory(double _g);
	// Defines trajectory moving at given velocity along 0-rad line
	Trajectory(double _g, double _v0);
	// Defines trajectory moving at given velocity in given direction
	Trajectory(double _g, double _v0, double _theta0);

	// Destructor
	~Trajectory();

// Accessors
public:
	double GetXVelocity()	{return m_x.GetB();};
	double GetYVelocity()	{return m_y.GetB();};
	double GetTheta()		{return m_theta;};
	double GetGravity()		{return m_g;};

	// Returns scalar velocity, or -1.0 on error
	// TODO: maybe this should return HRESULT, for style consistency
	double GetVelocity();

// Public methods
public:
	HRESULT SetVx(double newVx);
	HRESULT SetVy(double newVy);
	HRESULT SetVelocity(double newV);
	HRESULT SetTheta(double newTheta);
	HRESULT SetGravity(double newG);

// Properties
private:
	// NOTE: Velocity components are stored in inherited Quadratics' (m_x, m_y) member m_b

	// Direction of movement
	double m_theta;
	// Current gravity imposed on trajectory
	double m_g;
};
