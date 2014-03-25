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
	double GetXVelocity() {return m_Vx;};
	double GetYVelocity() {return m_Vy;};
	double GetTheta() {return m_theta;};

	double GetVelocity();

// Public methods
public:
	HRESULT SetVx(double newVx);
	HRESULT SetVy(double newVy);
	HRESULT SetTheta(double newTheta);

// Properties
private:
	// X-component of velocity vector
	double m_Vx;
	// Y-component of velocity vectory
	double m_Vy;
	// Direction of movement
	double m_theta;
	// Current gravity imposed on trajectory
	double m_g;
};
