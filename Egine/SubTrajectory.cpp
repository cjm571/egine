/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/

#include "SubTrajectory.h"

/********** CTORS **********/
SubTrajectory::SubTrajectory()
	: m_t0(0.0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// zero gravity in Y-direction
	m_y = Quadratic(0.0, 0.0, 0.0);
}

SubTrajectory::SubTrajectory(Parametric _parametric, double _t0)
	: Parametric(_parametric), m_t0(_t0)
{
}

SubTrajectory::SubTrajectory(Quadratic _x, Quadratic _y, double _t0)
	: Parametric(_x, _y), m_t0(_t0)
{
}

SubTrajectory::SubTrajectory(double _g, CartPoint _p0, double _t0)
	: m_t0(_t0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, _p0.x);

	// g in Y-direction
	double a = -0.5*_g;
	m_y = Quadratic(a, 0.0, _p0.y);
}

SubTrajectory::SubTrajectory(double _g, double _v0, CartPoint _p0, double _t0)
	: m_t0(_t0)
{
	// v0 in X-direction
	m_x = Quadratic(0.0, _v0, _p0.x);

	// g in Y-direction
	double a = -0.5*_g;
	m_y = Quadratic(a, 0.0, _p0.y);
}

SubTrajectory::SubTrajectory(double _g, double _v0, double _theta0, CartPoint _p0, double _t0)
	: m_t0(_t0)
{
	// Vx in X-direction
	m_x = Quadratic(0.0, _v0*cos(_theta0), _p0.x);

	// g, Vy in Y-direction
	double a = -0.5*_g;
	m_y = Quadratic(a, _v0*sin(_theta0), _p0.y);
}

SubTrajectory::~SubTrajectory()
{
}

/********** HELPER FUNCTIONS **********/
double SubTrajectory::NormalizeT(double t)
{
	double tRel = -1.0;

	tRel = t - m_t0;

	return tRel;
}


/********** ACCESSORS **********/
double SubTrajectory::GetTheta(double t)
{
	double theta = -1.0;

	double tRel = NormalizeT(t);

	theta = GetTangentAngle(tRel);
	theta = WrapAngle(theta);

	return theta;
}

double SubTrajectory::GetVelocity(double t)
{
	double vScalar = -1.0;

	double tRel = NormalizeT(t);

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

double SubTrajectory::GetVelocity(eAxis axis, double t)
{
	double axisV;

	double tRel = NormalizeT(t);
	
	if (axis == XAxis)
	{
		axisV = m_x.Derive(tRel);
	}
	else // Y-axis
	{
		axisV = m_y.Derive(tRel);
	}

	return axisV;
}

CartPoint SubTrajectory::GetPositionAt(double t)
{
	CartPoint position;

	double tRel = NormalizeT(t);

	double xPos = m_x.Solve(tRel);
	double yPos = m_y.Solve(tRel);

	position.x = xPos;
	position.y = yPos;

	return position;
}

double SubTrajectory::GetAcceleration(eAxis axis)
{
	double a;

	if (axis == XAxis)
	{
		a = 2*m_x.GetA();
	}
	else // Y-axis
	{
		a = 2*m_y.GetA();
	}

	return a;
}

double SubTrajectory::GetInitialVelocity(eAxis axis)
{
	double v0;

	if (axis == XAxis)
	{
		v0 = m_x.GetB();
	}
	else // Y-axis
	{
		v0 = m_y.GetB();
	}

	return v0;
}

double SubTrajectory::GetInitialPosition(eAxis axis)
{
	double p;

	if (axis == XAxis)
	{
		p = m_x.GetC();
	}
	else // Y-axis
	{
		p = m_y.GetC();
	}

	return p;
}

CartPoint SubTrajectory::GetInitialPosition()
{
	CartPoint p0;
	
	p0.x = m_x.GetC();
	p0.y = m_y.GetC();

	return p0;
}


/********** MUTATORS **********/
PHRESULT SubTrajectory::SetAcceleration(eAxis axis, double newA)
{
	PHRESULT hr = S_OK;

	if (axis == XAxis)
	{
		m_x.SetA(0.5*newA);
	}
	else if (axis == YAxis)
	{
		m_y.SetA(0.5*newA);
	}
	else
	{
		hr = E_FAIL;
	}

	return hr;
}

PHRESULT SubTrajectory::SetInitialVelocity(eAxis axis, double newV)
{
	PHRESULT hr = S_OK;

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

PHRESULT SubTrajectory::SetInitialPosition(eAxis axis, double newP)
{
	PHRESULT hr = S_OK;

	// Sanity check
	if (abs(newP) > C)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		if (axis==XAxis)
		{
			m_x.SetC(newP);
		}
		if (axis==YAxis)
		{
			m_y.SetC(newP);
		}
	}

	return hr;
}
