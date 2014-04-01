/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/
#pragma once

#include "StdAfx.h"
#include "Parametric.h"

class Trajectory : public Parametric
{
// Ctors
public:
	// Default Construct
	// Defines initially at-rest trajactory in zero-gravity starting at (0,0)
	Trajectory();
	// Defines initially at-rest trajectory
	Trajectory(double _g, CartPoint _p0);
	// Defines trajectory moving at given velocity along 0-rad line
	Trajectory(double _g, double _v0, CartPoint _p0);
	// Defines trajectory moving at given velocity in given direction
	Trajectory(double _g, double _v0, double _theta0, CartPoint _p0);

	// Destructor
	~Trajectory();

// Accessors
public:
	double GetXVelocity()			{return m_x.GetB();};
	double GetYVelocity()			{return m_y.GetB();};
	double GetTheta()				{return m_theta;};
	double GetGravity()				{return m_g;};
	CartPoint GetInitialPosition()	{return m_p0;};

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
	HRESULT SetInitialPosition(CartPoint newp0);

// Properties
// NOTE: Velocity components are stored in inherited Quadratics' (m_x, m_y) member m_b
private:
	// Initial position of trajectory
	CartPoint m_p0;
	// Direction of movement
	double m_theta;
	// Current gravity imposed on trajectory
	double m_g;
};
