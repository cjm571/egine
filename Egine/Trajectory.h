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
	// Default Constructor
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
	double GetGravity()		{return m_g;};

	// Returns angle of trajectory in range (0,2pi) at time t
	double GetTheta(double t);

	// Returns scalar velocity at time t
	double GetVelocity(double t);
	// Returns axis-component of velocity at time t
	double GetVelocity(eAxis axis, double t);
	
	// Returns velocity Quadratic factor for the given axis
	double GetQuadraticFactor(eAxis axis);
	// Returns velocity linear factor for the given axis
	double GetLinearFactor(eAxis axis);
	// Returns velocity constant factor for the given axis
	double GetConstantFactor(eAxis axis);

	// Returns Cartesian position of object at the given time
	CartPoint GetPositionAt(double t);

// Public methods
public:
	// Sets the velocity linear factor for the given axis
	PHRESULT SetVelocityFactor(eAxis axis, double newV);
	// Sets the velocity constant factor for the given axis
	PHRESULT SetConstantFactor(eAxis axis, double newC);

	// Sets the trajectory gravity and the quadratic factor for the y-axis
	// NOTE: newG must be a positive value
	PHRESULT SetGravity(double newG);

	// Resets the trajectory start time to the given value
	// NOTE: newt0 must be greater than the current t0
	PHRESULT SetT0(double newt0);
	
// Public Statics
public:
	// Calculates intersections of Trajectories a and b
	static std::vector<CartPoint> CalcIntersects(Trajectory a, Trajectory b);

// Properties
// NOTE: Velocity components are stored in inherited Quadratics' (m_x, m_y) member m_b
private:
	// Current gravity imposed on trajectory
	double m_g;
};
