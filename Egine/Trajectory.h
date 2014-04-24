/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/
#pragma once

#include <deque>

#include "StdAfx.h"
#include "SubTrajectory.h"

class Trajectory
{
// Ctors
public:
	// Default Constructor
	// Defines empty trajectory at time 0
	Trajectory();
	// Defines trajectory with the given first SubTrajectory
	Trajectory(SubTrajectory _subTraj);
	// Defines trajectory with given properties beginning at the given time
	Trajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0);


	// Destructor
	~Trajectory();

// Helper functions
private:
	// Returns a COPY of SubTrajectory in effect at the given time
	SubTrajectory GetSubTrajectory(double t);

// Accessors
public:
	// Returns force of gravity in m/s^2 at time t
	double GetGravity(double t);

	// Returns angle of trajectory in range (0,2pi) at time t
	double GetTheta(double t);

	// Returns scalar velocity at time t
	double GetVelocity(double t);
	// Returns axis-component of velocity at time t
	double GetVelocity(eAxis axis, double t);
	
	// Returns velocity Quadratic factor for the given axis at time t
	double GetQuadraticFactor(eAxis axis, double t);
	// Returns velocity linear factor for the given axis at time t
	double GetLinearFactor(eAxis axis, double t);
	// Returns velocity constant factor for the given axis at time t
	double GetConstantFactor(eAxis axis, double t);

	// Returns Cartesian position of object at the given time
	CartPoint GetPositionAt(double t);


// Public Statics
public:
	// Calculates intersections of Trajectories a and b
	static std::vector<CartPoint> CalcIntersects(Trajectory a, Trajectory b);

// Data members
private:
	// Double-ended queue of subtrajectories ordered by their starting time
	std::deque<SubTrajectory> m_subTrajs;
};
