/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
	: m_g(0.0), m_Vx(0.0), m_Vy(0.0), m_theta(0.0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// No movement in Y-direction, all coeffs 0
	m_y = Quadratic(0.0, 0.0, 0.0);
}

Trajectory::Trajectory(double _g)
	: m_g(_g), m_Vx(0.0), m_Vy(0.0), m_theta(0.0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

Trajectory::Trajectory(double _g, double _v0)
	: m_g(_g), m_Vx(_v0), m_Vy(0.0), m_theta(0.0)
{
	// v0 in X-direction
	m_x = Quadratic(0.0, m_Vx, 0.0);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

Trajectory::Trajectory(double _g, double _v0, double _theta0)
	: m_g(_g), m_Vx(_v0*cos(_theta0)), m_Vy(_v0*sin(_theta0)), m_theta(_theta0)
{
	// Vx in X-direction
	m_x = Quadratic(0.0, m_Vx, 0.0);

	// g, Vy in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, m_Vy, 0.0);
}

Trajectory::~Trajectory()
{
}


/********** PUBLIC METHODS **********/
HRESULT Trajectory::SetVx(double newVx)
{
	HRESULT hr = S_OK;
	
	// Sanity check
	// Speed of light
	if (newVx > abs(C * cos(m_theta)) )
	{
		hr = E_FAIL;
		MessageBoxA(NULL,"Object exceeding speed of light!", "Causality Violation", MB_OK);
	}

	m_x.SetB(newVx);

	return hr;
}

HRESULT Trajectory::SetVy(double newVy)
{
	HRESULT hr = S_OK;
	
	// Sanity check
	// Speed of light
	if (newVy > abs(C * sin(m_theta)) )
	{
		hr = E_FAIL;
		MessageBoxA(NULL,"Object exceeding speed of light!", "Causality Violation", MB_OK);
	}

	m_y.SetB(newVy);

	return hr;
}

HRESULT Trajectory::SetTheta(double newTheta)
{
	HRESULT hr = S_OK;

	m_theta = WrapAngle(newTheta);

	return hr;
}