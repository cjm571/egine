/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-23 *
*************************/

#include "SubTrajectory.h"

/********** CTORS **********/
SubTrajectory::SubTrajectory()
	: m_g(9.8)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// Earth gravity in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

SubTrajectory::SubTrajectory(double _g, CartPoint _p0)
	: m_g(_g)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, _p0.x);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, _p0.y);
}

SubTrajectory::SubTrajectory(double _g, double _v0, CartPoint _p0)
	: m_g(_g)
{
	// v0 in X-direction
	m_x = Quadratic(0.0, _v0, _p0.x);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, _p0.y);
}

SubTrajectory::SubTrajectory(double _g, double _v0, double _theta0, CartPoint _p0)
	: m_g(_g)
{
	// Vx in X-direction
	m_x = Quadratic(0.0, _v0*cos(_theta0), _p0.x);

	// g, Vy in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, _v0*sin(_theta0), _p0.y);
}

SubTrajectory::~SubTrajectory()
{
}


/********** PUBLIC METHODS **********/
double SubTrajectory::GetTheta(double t)
{
	double theta = -1.0;

	theta = GetTangentAngle(t);
	theta = WrapAngle(theta);

	return theta;
}

double SubTrajectory::GetVelocity(double t)
{
	double vScalar = -1.0;

	// Derive X & Y quadtratics
	Linear dx_dt = m_x.Derive();
	Linear dy_dt = m_y.Derive();

	// Solve derivatives at time t for X & Y velocities
	double vX = dx_dt.Solve(t);
	double vY = dy_dt.Solve(t);

	// Use pythagorean theorem to get scalar velocity
	Pythag(vX, vY, &vScalar);

	return vScalar;
}

double SubTrajectory::GetVelocity(eAxis axis, double t)
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

double SubTrajectory::GetQuadraticFactor(eAxis axis)
{
	double vel;

	if (axis == XAxis)
	{
		vel = m_x.GetA();
	}
	else // Y-axis
	{
		vel = m_y.GetA();
	}

	return vel;
}

double SubTrajectory::GetLinearFactor(eAxis axis)
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

double SubTrajectory::GetConstantFactor(eAxis axis)
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

CartPoint SubTrajectory::GetPositionAt(double t)
{
	CartPoint position;

	double xPos = m_x.Solve(t);
	double yPos = m_y.Solve(t);

	position.x = xPos;
	position.y = yPos;

	return position;
}

PHRESULT SubTrajectory::SetVelocityFactor(eAxis axis, double newV)
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

PHRESULT SubTrajectory::SetConstantFactor(eAxis axis, double newC)
{
	PHRESULT hr = S_OK;

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

PHRESULT SubTrajectory::SetGravity(double newG)
{
	PHRESULT hr = S_OK;

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
