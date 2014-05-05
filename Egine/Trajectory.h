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
	// Defines empty trajectory at TIME_SIM_START
	Trajectory();
	// Defines at-rest trajectory at given centerpoint
	Trajectory(CartPoint _p0, double _t0);
	// Defines trajectory with the given first SubTrajectory
	Trajectory(SubTrajectory _subTraj);
	// Defines trajectory with given properties beginning at the given time
	Trajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0);

	// Destructor
	~Trajectory();
	
// Data members
private:
	// Double-ended queue of subtrajectories ordered by their starting time
	std::deque<SubTrajectory> m_subTrajs;

// Helper functions
private:
	// Returns a COPY of SubTrajectory in effect at the given time
	SubTrajectory GetSubTrajectory(double t);

// Public Methods
public:
	// Pushes a new subtrajectory onto the subtrajectory deque
	void PushSubTrajectory(SubTrajectory subTraj);


// SubTrajectory Accessors
public:
	// Returns angle of trajectory in range (0,2pi) at time t
	double GetTheta(double t);

	// Returns scalar velocity at time t
	double GetVelocity(double t);
	// Returns axis-component of velocity at time t
	double GetVelocity(eAxis axis, double t);

	// Returns Cartesian position of object at the given time
	CartPoint GetPositionAt(double t);
	
	// Returns acceleration (m/s^2) on given axis at time t
	double GetAcceleration(eAxis axis, double t);
	// Returns the initial velocity (m/s) of subtrajectory in effect at time t for the given axis
	double GetInitialVelocity(eAxis axis, double t);
	// Returns initial position (m from origin) on the given axis for the subtrajectory in effect at time t
	double GetInitialPosition(eAxis axis, double t);
	// Returns initial position (m from origin) for the subtrajectory in effect at time t
	CartPoint GetInitialPosition(double t);

// SubTrajectory Mutators
public:
	// Sets acceleration (m/s^2) on given axis at time t
	PHRESULT SetAcceleration(eAxis axis, double newA, double t);
	// Sets the initial velocity (m/s) of subtrajectory in effect at time t for the given axis
	PHRESULT SetInitialVelocity(eAxis axis, double newV, double t);
	// Sets initial position (m from origin) on the given axis for the subtrajectory in effect at time t
	PHRESULT SetInitialPosition(eAxis axis, double newP, double t);
	// Sets initial position (m from origin) for the subtrajectory in effect at time t
	PHRESULT SetInitialPosition(CartPoint newP0, double t);


// Parametric Accessors
public:
	// Returns copy of x-axis Quadratic at time t
	Quadratic GetXQuadratic(double t);
	// Returns copy of y-axis Quadratic at time t
	Quadratic GetYQuadratic(double t);

	// Returns angle of the tangent line (in radians) at the given time
	double GetTangentAngle(double t);
	
	// Solve for value of x(t) given t
	double SolveX(double t);
	// Solve for value of y(t) given t
	double SolveY(double t);
	
	// Return real-number roots of Quadratic x(t) in effect at time t
	std::pair<double,double> GetXRoots(double t, double x_t=0.0);
	// Return real-number roots of Quadratic y(t) in effect at time t
	std::pair<double,double> GetYRoots(double t, double y_t=0.0);

	// Calculates X-intercept of Quadratic x(t) in effect at time t, given offset from initial position
	std::pair<double,double> CalcXIntercepts(double t, double offset=0.0);
	// Calculates Y-intercept of Quadratic y(t) in effect at time t, given offset from initial position
	std::pair<double,double> CalcYIntercepts(double t, double offset=0.0);


// Public Statics
public:
	// Calculates intersections of Trajectories a and b
	//static std::vector<CartPoint> CalcIntersects(Trajectory a, Trajectory b);
};
