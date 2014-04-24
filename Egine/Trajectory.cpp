/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
{
}

Trajectory::Trajectory(SubTrajectory _subTraj)
{
	m_subTrajs.push_back(_subTraj);
}

Trajectory::Trajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0)
{
	// Create SubTrajectory based on inputs, push onto deque
	SubTrajectory _subTraj = SubTrajectory(_g, _v0, _theta0, _p0, _t0);
	m_subTrajs.push_back(_subTraj);
}


/********** HELPER FUNCTIONS **********/
SubTrajectory Trajectory::GetSubTrajectory(double t)
{
	SubTrajectory subTraj;

	// TODO: optimize this braindead search
	// Break loop if we have gone past the given time
	// Previous map entry will be used for return
	std::deque<SubTrajectory>::iterator itr = m_subTrajs.begin();
	do
	{
		// Copy, so the caller can't do anything dangerously stupid
		subTraj = SubTrajectory(*itr);
		++itr;
	}
	while(itr!=m_subTrajs.end() || itr->GetT0() > t);
	
	return subTraj;
}


/********** SUBTRAJECTORY ACCESSORS **********/
double Trajectory::GetGravity(double t)
{
	SubTrajectory subTraj = GetSubTrajectory(t);

	return subTraj.GetGravity();
}

double Trajectory::GetTheta(double t)
{
	double theta;

	SubTrajectory subTraj = GetSubTrajectory(t);
	theta = subTraj.GetTheta(t);

	return theta;
}

double Trajectory::GetVelocity(double t)
{
	double vScalar;

	SubTrajectory subTraj = GetSubTrajectory(t);
	vScalar = subTraj.GetVelocity(t);

	return vScalar;
}

double Trajectory::GetVelocity(eAxis axis, double t)
{
	double vel;

	SubTrajectory subTraj = GetSubTrajectory(t);
	vel = subTraj.GetVelocity(axis, t);

	return vel;
}

double Trajectory::GetQuadraticFactor(eAxis axis, double t)
{
	double a;

	SubTrajectory subTraj = GetSubTrajectory(t);
	a = subTraj.GetQuadraticFactor(axis);

	return a;
}

double Trajectory::GetLinearFactor(eAxis axis, double t)
{
	double b;

	SubTrajectory subTraj = GetSubTrajectory(t);
	b = subTraj.GetLinearFactor(axis);

	return b;
}

double Trajectory::GetConstantFactor(eAxis axis, double t)
{
	double c;

	SubTrajectory subTraj = GetSubTrajectory(t);
	c = subTraj.GetConstantFactor(axis);

	return c;
}

CartPoint Trajectory::GetPositionAt(double t)
{
	CartPoint p;

	SubTrajectory subTraj = GetSubTrajectory(t);
	p = subTraj.GetPositionAt(t);

	return p;
}


/********** PARAMETRIC ACCESSORS **********/


/********** PUBLIC STATICS **********/
/* NOT READY YET
std::vector<CartPoint> Trajectory::CalcIntersects(Trajectory a, Trajectory b)
{
	std::vector<CartPoint> intersects;
	
	// Get first subtrajectories
	SubTrajectory subTrajA = a.GetSubTrajectory(0.0);
	SubTrajectory subTrajB = b.GetSubTrajectory(0.0);

	// TODO: optimize braindead O(n^2) search
	do
	{
		// Find values of t in which ax(t) and bx(t) are equal
		std::pair<double,double> xIntersects;
		xIntersects = Quadratic::CalcIntersects(a.m_x, b.m_x);

		// Find values of t in which ay(t) and by(t) are equal
		std::pair<double,double> yIntersects;
		yIntersects = Quadratic::CalcIntersects(a.m_y, b.m_y);
	}

	// Find matches between x(t) and y(t) intersects
	std::vector<double> matches;
	if (xIntersects.first == yIntersects.first || xIntersects.first == yIntersects.second)
	{
		matches.push_back(xIntersects.first);
	}
	if (xIntersects.second == yIntersects.first || xIntersects.second == yIntersects.second)
	{
		matches.push_back(xIntersects.second);
	}

	// Calculate position of each object at the matched values of t and push to results vector
	std::vector<double>::iterator matchesItr;
	for (matchesItr = matches.begin(); matchesItr != matches.end(); ++matchesItr);
	{
		double t = *matchesItr;

		CartPoint intersect = a.GetPositionAt(t);

		intersects.push_back(intersect);
	}

	return intersects;
}
*/
