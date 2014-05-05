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

Trajectory::Trajectory(CartPoint _p0, double _t0)
{
	SubTrajectory _subTraj = SubTrajectory(GRAV_EARTH, _p0, _t0);
	m_subTrajs.push_back(_subTraj);
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

Trajectory::~Trajectory()
{
	m_subTrajs.clear();
}


/********** HELPER FUNCTIONS **********/
SubTrajectory Trajectory::GetSubTrajectory(double t)
{
	SubTrajectory subTraj;

	// TODO: optimize this braindead search
	std::deque<SubTrajectory>::iterator itr = m_subTrajs.begin();
	do
	{
		// Copy, so the caller can't do anything dangerously stupid
		subTraj = SubTrajectory(*itr);
		
		// Break loop if we have gone past the given time
		// Previous map entry will be used for return
		if (itr->GetT0() > t)
		{
			break;
		}

		++itr;
	}
	while(itr!=m_subTrajs.end());
	
	return subTraj;
}


/********** PUBLIC METHODS **********/
void Trajectory::PushSubTrajectory(SubTrajectory subTraj)
{
	m_subTrajs.push_back(subTraj);
}


/********** SUBTRAJECTORY ACCESSORS **********/
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

CartPoint Trajectory::GetPositionAt(double t)
{
	CartPoint p;

	SubTrajectory subTraj = GetSubTrajectory(t);
	p = subTraj.GetPositionAt(t);

	return p;
}

double Trajectory::GetAcceleration(eAxis axis, double t)
{
	SubTrajectory subTraj = GetSubTrajectory(t);

	return subTraj.GetAcceleration(axis);
}

double Trajectory::GetInitialVelocity(eAxis axis, double t)
{
	double v0;

	SubTrajectory subTraj = GetSubTrajectory(t);
	v0 = subTraj.GetInitialVelocity(axis);

	return v0;
}

double Trajectory::GetInitialPosition(eAxis axis, double t)
{
	double p0;

	SubTrajectory subTraj = GetSubTrajectory(t);
	p0 = subTraj.GetInitialPosition(axis);

	return p0;
}

CartPoint Trajectory::GetInitialPosition(double t)
{
	CartPoint p0;

	SubTrajectory subTraj = GetSubTrajectory(t);
	p0 = subTraj.GetInitialPosition();

	return p0;
}

/********** SUBTRAJECTORY MUTATORS **********/
PHRESULT Trajectory::SetAcceleration(eAxis axis, double newA, double t)
{
	PHRESULT hr = S_OK;

	SubTrajectory subTraj = GetSubTrajectory(t);
	hr = subTraj.SetAcceleration(axis, newA);

	return hr;
}

PHRESULT Trajectory::SetInitialVelocity(eAxis axis, double newV, double t)
{
	PHRESULT hr = S_OK;

	SubTrajectory subTraj = GetSubTrajectory(t);
	hr = subTraj.SetInitialVelocity(axis, newV);

	return hr;
}

PHRESULT Trajectory::SetInitialPosition(eAxis axis, double newP, double t)
{
	PHRESULT hr = S_OK;

	SubTrajectory subTraj = GetSubTrajectory(t);
	hr = subTraj.SetInitialPosition(axis, newP);

	return hr;
}

PHRESULT Trajectory::SetInitialPosition(CartPoint newP0, double t)
{
	PHRESULT hr = S_OK;

	SubTrajectory subTraj = GetSubTrajectory(t);
	hr |= subTraj.SetInitialPosition(XAxis, newP0.x);
	hr |= subTraj.SetInitialPosition(YAxis, newP0.y);

	return hr;
}


/********** PARAMETRIC ACCESSORS **********/
Quadratic Trajectory::GetXQuadratic(double t)
{
	Quadratic xQuad;

	SubTrajectory subTraj = GetSubTrajectory(t);
	xQuad = subTraj.GetXQuadratic();

	return xQuad;
}

Quadratic Trajectory::GetYQuadratic(double t)
{
	Quadratic xQuad;

	SubTrajectory subTraj = GetSubTrajectory(t);
	xQuad = subTraj.GetYQuadratic();

	return xQuad;
}

double Trajectory::GetTangentAngle(double t)
{
	double tanTheta;

	SubTrajectory subTraj = GetSubTrajectory(t);
	tanTheta = subTraj.GetTangentAngle(t);

	return tanTheta;
}

double Trajectory::SolveX(double t)
{
	double xSoln;

	SubTrajectory subTraj = GetSubTrajectory(t);
	xSoln = subTraj.SolveX(t);

	return xSoln;
}

double Trajectory::SolveY(double t)
{
	double ySoln;

	SubTrajectory subTraj = GetSubTrajectory(t);
	ySoln = subTraj.SolveY(t);

	return ySoln;
}

std::pair<double,double> Trajectory::GetXRoots(double t, double x_t)
{
	std::pair<double,double> roots;

	SubTrajectory subTraj = GetSubTrajectory(t);
	roots = subTraj.GetXRoots(x_t);

	// Compensate for in-effect subtraj t0
	roots.first = roots.first + subTraj.GetT0();
	roots.second = roots.second + subTraj.GetT0();

	return roots;
}

std::pair<double,double> Trajectory::GetYRoots(double t, double y_t)
{
	std::pair<double,double> roots;

	SubTrajectory subTraj = GetSubTrajectory(t);
	roots = subTraj.GetYRoots(y_t);

	// Compensate for in-effect subtraj t0
	roots.first = roots.first + subTraj.GetT0();
	roots.second = roots.second + subTraj.GetT0();

	return roots;
}

std::pair<double,double> Trajectory::CalcXIntercepts(double t, double offset)
{
	std::pair<double,double> intercepts;

	SubTrajectory subTraj = GetSubTrajectory(t);
	intercepts = subTraj.CalcXIntercepts(offset);

	// Compensate for in-effect subtraj t0
	intercepts.first = intercepts.first + subTraj.GetT0();
	intercepts.second = intercepts.second + subTraj.GetT0();

	return intercepts;
}

std::pair<double,double> Trajectory::CalcYIntercepts(double t, double offset)
{
	std::pair<double,double> intercepts;

	SubTrajectory subTraj = GetSubTrajectory(t);
	intercepts = subTraj.CalcYIntercepts(offset);

	// Compensate for in-effect subtraj t0
	intercepts.first = intercepts.first + subTraj.GetT0();
	intercepts.second = intercepts.second + subTraj.GetT0();

	return intercepts;
}

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
