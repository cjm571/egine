/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
	: m_g(9.8), m_t0(0.0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// Earth gravity in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

Trajectory::Trajectory(double _g, CartPoint _p0)
	: m_g(_g), m_t0(0.0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, _p0.x);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, _p0.y);
}

Trajectory::Trajectory(double _g, double _v0, CartPoint _p0)
	: m_g(_g), m_t0(0.0)
{
	// v0 in X-direction
	m_x = Quadratic(0.0, _v0, _p0.x);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, _p0.y);
}

Trajectory::Trajectory(double _g, double _v0, double _theta0, CartPoint _p0)
	: m_g(_g), m_t0(0.0)
{
	// Vx in X-direction
	m_x = Quadratic(0.0, _v0*cos(_theta0), _p0.x);

	// g, Vy in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, _v0*sin(_theta0), _p0.y);
}

Trajectory::~Trajectory()
{
}


/********** HELPER FUNCTIONS **********/
double Trajectory::GetRelativeTime(double t)
{
	return t - m_t0;
}


/********** PUBLIC METHODS **********/
double Trajectory::GetTheta(double t)
{
	double theta = -1.0;
	double tRel = GetRelativeTime(t);

	theta = GetTangentAngle(tRel);
	theta = WrapAngle(theta);

	return theta;
}

double Trajectory::GetVelocity(double t)
{
	double vScalar = -1.0;
	double tRel = GetRelativeTime(t);

	// Derive X & Y quadtratics
	Linear dx_dt = m_x.Derive();
	Linear dy_dt = m_y.Derive();

	// Solve derivatives at time t for X & Y velocities
	double vX = dx_dt.Solve(tRel);
	double vY = dy_dt.Solve(tRel);

	// Use pythagorean theorem to get scalar velocity
	Pythag(vX, vY, &vScalar);

	return vScalar;
}

double Trajectory::GetVelocity(eAxis axis, double t)
{
	double axisV;
	
	if (axis == XAxis)
	{
		axisV = m_x.Derive(t);
	}
	else // Y-axis
	{
		axisV = m_y.Derive(t);
	}

	return axisV;
}

double Trajectory::GetVelocityFactor(eAxis axis)
{
	double vel;

	if (axis == XAxis)
	{
		vel = m_x.GetB();
	}
	else // Y-axis
	{
		vel = m_y.GetB();
	}

	return vel;
}

double Trajectory::GetConstantFactor(eAxis axis)
{
	double vel;

	if (axis == XAxis)
	{
		vel = m_x.GetC();
	}
	else // Y-axis
	{
		vel = m_y.GetC();
	}

	return vel;
}

CartPoint Trajectory::GetPositionAt(double t)
{
	CartPoint position;
	double tRel = GetRelativeTime(t);

	double xPos = m_x.Solve(tRel);
	double yPos = m_y.Solve(tRel);

	position.x = xPos;
	position.y = yPos;

	return position;
}

HRESULT Trajectory::SetVelocityFactor(eAxis axis, double newV)
{
	HRESULT hr = S_OK;

	// Sanity check
	if (abs(newV) > C)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		if (axis==XAxis)
		{
			m_x.SetB(newV);
		}
		if (axis==YAxis)
		{
			m_y.SetB(newV);
		}
	}

	return hr;
}

HRESULT Trajectory::SetConstantFactor(eAxis axis, double newC)
{
	HRESULT hr = S_OK;

	// Sanity check
	if (abs(newC) > C)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		if (axis==XAxis)
		{
			m_x.SetC(newC);
		}
		if (axis==YAxis)
		{
			m_y.SetC(newC);
		}
	}

	return hr;
}

HRESULT Trajectory::SetGravity(double newG)
{
	HRESULT hr = S_OK;

	// Sanity check
	if (newG < 0.0)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		m_y.SetA(-1*newG);
		m_g = newG;
	}

	return hr;
}

HRESULT Trajectory::SetT0(double newt0)
{
	HRESULT hr = S_OK;

	// Sanity check
	// Cannot move backward in time
	if (newt0 < m_t0)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		m_t0 = newt0;
	}

	return hr;
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
