/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/
#pragma once

#include "StdAfx.h"
#include "Parametric.h"

class SubTrajectory : public Parametric
{
// Ctors
public:
	// Default Constructor
	// Defines at-rest trajectory at (0,0)
	SubTrajectory();
	// Defines trajectory based on given Parametric
	SubTrajectory(Parametric _parametric, double _t0);
	// Defines trajectory based on given Quadratics
	SubTrajectory(Quadratic _x, Quadratic _y, double _t0);
	// Defines initially at-rest trajectory
	SubTrajectory(double _g, CartPoint _p0, double _t0);
	// Defines trajectory moving at given velocity along 0-rad line
	SubTrajectory(double _g, double _v0, CartPoint _p0, double _t0);
	// Defines trajectory moving at given velocity in given direction
	SubTrajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0);

	// Destructor
	~SubTrajectory();

// Data members
private:
	// Starting time of trajectory
	double m_t0;

// Helper Functions
private:
	// Returns the time relative to the start time of the SubTrajectory
	double NormalizeT(double t);

// Accessors
public:
	double GetT0() {return m_t0;};

	// Returns angle of trajectory in range (0,2pi) at time t
	double GetTheta(double t);

	// Returns scalar velocity at time t
	double GetVelocity(double t);
	// Returns axis-component of velocity at time t
	double GetVelocity(eAxis axis, double t);

	// Returns Cartesian position of object at the given time
	CartPoint GetPositionAt(double t);
	
	// Returns acceleration in m/s^2 on given axis
	double GetAcceleration(eAxis axis);
	// Returns the initial velocity (m/s) for the given axis
	double GetInitialVelocity(eAxis axis);
	// Returns initial position (m from origin) on the given axis
	double GetInitialPosition(eAxis axis);
	// Returns initial position (m from origin)
	CartPoint GetInitialPosition();

// Mutators
public:
	// Sets the quadratic factor for the given axis
	PHRESULT SetAcceleration(eAxis axis, double newA);
	// Sets the linear factor for the given axis
	PHRESULT SetInitialVelocity(eAxis axis, double newV);
	// Sets the constant factor for the given axis
	PHRESULT SetInitialPosition(eAxis axis, double newP);
};
