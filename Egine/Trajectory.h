/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/
#pragma once

#include <map>

#include "StdAfx.h"
#include "SubTrajectory.h"

class Trajectory
{
// Ctors
public:
	// Default Constructor
	// Defines empty trajectory at time 0
	Trajectory();
	// Defines trajectory with given properties beginning at the given time
	Trajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0);
	// Defines trajectory with the given first SubTrajectory starting at the given time
	Trajectory(SubTrajectory _subTraj, double _t0);


	// Destructor
	~Trajectory();

// Helper functions
private:
	// Returns time, t, normalized such that m_t0 becomes 0.0s
	// Called at the beginning of all functions involving time
	double NormalizeT0(double t);

	// Returns a COPY of SubTrajectory in effect at the given (normalized) time
	SubTrajectory GetSubTrajectory(double tNorm);

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
	
	// Returns velocity Quadratic factor for the given axis
	double GetQuadraticFactor(eAxis axis);
	// Returns velocity linear factor for the given axis
	double GetLinearFactor(eAxis axis);
	// Returns velocity constant factor for the given axis
	double GetConstantFactor(eAxis axis);

	// Returns Cartesian position of object at the given time
	CartPoint GetPositionAt(double t);


// Public Statics
public:
	// Calculates intersections of Trajectories a and b
	static std::vector<CartPoint> CalcIntersects(Trajectory a, Trajectory b);

// Data members
private:
	// Maps of subtrajectories keyed by their starting time
	std::map<double,SubTrajectory> m_subTrajs;

	// Point in simulation time at which trajectory began
	double m_t0;
};
