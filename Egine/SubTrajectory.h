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
	// Defines initially at-rest trajectory in zero-gravity starting at (0,0)
	SubTrajectory();
	// Defines initially at-rest trajectory
	SubTrajectory(double _g, CartPoint _p0, double _t0);
	// Defines trajectory moving at given velocity along 0-rad line
	SubTrajectory(double _g, double _v0, CartPoint _p0, double _t0);
	// Defines trajectory moving at given velocity in given direction
	SubTrajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0);

	// Destructor
	~SubTrajectory();

// SubTrajectory Accessors
public:
	double GetGravity()	{return m_g;};
	double GetT0()		{return m_t0;};

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

// Parametric Accessors
public:
	Quadratic GetXQuadratic();
	Quadratic GetYQuadratic();

	// Returns angle of the tangent line (in radians) at the given time
	double GetTangentAngle(double t);
	
	// Solve for value of x(t) given t
	double SolveX(double t);
	// Solve for value of y(t) given t
	double SolveY(double t);
	
	// Return real-number roots of x(t)
	std::pair<double,double> GetXRoots(double xt=0.0);
	// Return real-number roots of y(t)
	std::pair<double,double> GetYRoots(double yt=0.0);

	// Calculates X-intercept given offset from initial position
	std::pair<double,double> CalcXIntercepts(double offset=0.0);
	// Calculates Y-intercept given offset from initial position
	std::pair<double,double> CalcYIntercepts(double offset=0.0);
	

// Public methods
public:
	// Sets the trajectory gravity and the quadratic factor for the y-axis
	// NOTE: newG must be a positive value
	PHRESULT SetGravity(double newG);
	// Sets the linear factor for the given axis
	PHRESULT SetInitialVelocity(eAxis axis, double newV);
	// Sets the constant factor for the given axis
	PHRESULT SetInitialPosition(eAxis axis, double newP);


// Data members
// NOTE: Velocity components are stored in inherited Quadratics' (m_x, m_y) member m_b
private:
	// Current gravity imposed on trajectory
	double m_g;

	// Starting time of trajectory
	double m_t0;
};
