/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
	: m_t0(0.0)
{
}

Trajectory::Trajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0)
	: m_t0(_t0)
{
	// Create SubTrajectory based on inputs, and map it to a sub-t0 of m_t0
	SubTrajectory _subTraj = SubTrajectory(_g, _v0, _theta0, _p0);
	m_subTrajs[m_t0] = _subTraj;
}

Trajectory::Trajectory(SubTrajectory _subTraj, double _t0)
	: m_t0(_t0)
{
	m_subTrajs[m_t0] = _subTraj;
}


/********** HELPER FUNCTIONS **********/
double Trajectory::NormalizeT0(double t)
{
	return (t - m_t0);
}

SubTrajectory Trajectory::GetSubTrajectory(double tNorm)
{
	SubTrajectory subTraj;

	// TODO: optimize this braindead search
	std::map<double,SubTrajectory>::iterator itr = m_subTrajs.begin();
	do
	{
		// Copy, so the caller can't do anything dangerously stupid
		subTraj = SubTrajectory(itr->second);
		++itr;
	}
	// Break loop if we have gone past the given time
	// Previous map entry will be used for return
	while(itr!=m_subTrajs.end() && itr->first > tNorm);
	
	return subTraj;
}


/********** PUBLIC METHODS **********/
double Trajectory::GetGravity(double t)
{
	double tNorm = NormalizeT0(t);

	SubTrajectory subTraj = GetSubTrajectory(tNorm);

	return subTraj.GetGravity();
}

double Trajectory::GetTheta(double t)
{
	double theta;

	double tNorm = NormalizeT0(t);
	SubTrajectory subTraj = GetSubTrajectory(tNorm);
	theta = subTraj.GetTheta(tNorm);

	return theta;
}


/********** PUBLIC STATICS **********/
std::vector<CartPoint> Trajectory::CalcIntersects(Trajectory a, Trajectory b)
{
	std::vector<CartPoint> intersects;
	
	// Find values of t in which ax(t) and bx(t) are equal
	std::pair<double,double> xIntersects;
	xIntersects = Quadratic::CalcIntersects(a.m_x, b.m_x);

	// Find values of t in which ay(t) and by(t) are equal
	std::pair<double,double> yIntersects;
	yIntersects = Quadratic::CalcIntersects(a.m_y, b.m_y);

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
