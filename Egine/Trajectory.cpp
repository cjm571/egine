/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-23 *
*************************/

#include "Trajectory.h"

/********** CTORS **********/
Trajectory::Trajectory()
	: m_g(9.8), m_theta(0.0), m_t0(0.0)
{
	// Default initial position
	m_p0.x = 0.0;
	m_p0.y = 0.0;

	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// Earth gravity in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

Trajectory::Trajectory(double _g, CartPoint _p0)
	: m_g(_g), m_theta(0.0), m_p0(_p0), m_t0(0.0)
{
	// No movement in X-direction, all coeffs 0
	m_x = Quadratic(0.0, 0.0, 0.0);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

Trajectory::Trajectory(double _g, double _v0, CartPoint _p0)
	: m_g(_g), m_theta(0.0), m_p0(_p0), m_t0(0.0)
{
	// v0 in X-direction
	m_x = Quadratic(0.0, _v0, 0.0);

	// g in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, 0.0, 0.0);
}

Trajectory::Trajectory(double _g, double _v0, double _theta0, CartPoint _p0)
	: m_g(_g), m_theta(_theta0), m_p0(_p0), m_t0(0.0)
{
	// Vx in X-direction
	m_x = Quadratic(0.0, _v0*cos(_theta0), 0.0);

	// g, Vy in Y-direction
	double a = -0.5*m_g;
	m_y = Quadratic(a, _v0*sin(_theta0), 0.0);
}

Trajectory::~Trajectory()
{
}


/********** PUBLIC METHODS **********/
double Trajectory::GetVelocity()
{
	double a = m_x.GetB();
	double b = m_y.GetB();
	double c = -1.0;

	Pythag(a, b, &c);

	return c;
}

HRESULT Trajectory::SetVx(double newVx)
{
	HRESULT hr = S_OK;
	
	// Sanity check
	// Speed of light
	if (newVx > abs(C * cos(m_theta)))
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
	if (newVy > abs(C * sin(m_theta)))
	{
		hr = E_FAIL;
		MessageBoxA(NULL,"Object exceeding speed of light!", "Causality Violation", MB_OK);
	}

	m_y.SetB(newVy);

	return hr;
}

HRESULT Trajectory::SetVelocity(double newV)
{
	HRESULT hr = S_OK;

	hr |= SetVx(newV * cos(m_theta));
	hr |= SetVy(newV * sin(m_theta));

	return hr;
}

HRESULT Trajectory::SetTheta(double newTheta)
{
	HRESULT hr = S_OK;

	// Wrap angle about (0,2pi) and set
	m_theta = WrapAngle(newTheta);

	// Adjust Quadratics accordingly
	double curV = GetVelocity(); // lol... "curvy"
	
	if (SUCCEEDED(hr))
	{
		hr |= SetVx(curV*cos(m_theta));
		hr |= SetVy(curV*sin(m_theta));
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
		m_g = newG;
	}

	return hr;
}

HRESULT Trajectory::SetInitialPosition(CartPoint newp0)
{
	HRESULT hr = S_OK;

	// Sanity check
	if (newp0.x < 0.0 || newp0.y < 0.0)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		m_p0 = newp0;
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