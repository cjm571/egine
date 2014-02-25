/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-16 *
*************************/

#include "AABB.h"
#include "MainFrame.h"

// NOTE: Default AABB is 30x30, with BL corner at (0,0) Cartesian

/********** CTORS **********/
AABB::AABB()
{
	m_min = PhysPoint();
	m_min.x = 0;
	m_min.y	= 0;

	m_max = PhysPoint();
	m_max.x = 30;
	m_max.y = 30;

	m_center = PhysPoint();
	m_center.x = 15;
	m_center.y = 15;
}

AABB::AABB(PhysPoint _min, PhysPoint _max)
{
	m_min = PhysPoint(_min);
	m_max = PhysPoint(_max);

	m_center = PhysPoint();
	m_center.x = ((m_max.x - m_min.x) / 2) + m_min.x;
	m_center.y = ((m_max.y - m_min.y) / 2) + m_min.y;
}

AABB::AABB(PhysPoint _center, UINT _width, UINT _height)
{
	m_center = PhysPoint(_center);

	m_min = PhysPoint();
	m_min.x = m_center.x - (_width/2);
	m_min.y = m_center.y - (_height/2);

	m_max = PhysPoint();
	m_max.x = m_center.x + (_width/2);
	m_max.y = m_center.y + (_height/2);
}

AABB::~AABB()
{
}


/********** ACCESSORS FOR DRAWING FUNCTIONS **********/
PhysPoint AABB::GetTL()
{
	PhysPoint tl = PhysPoint();

	tl.x = m_min.x;
	tl.y = MainFrame::height - m_max.y;

	return tl;
}

PhysPoint AABB::GetBR()
{
	PhysPoint br = PhysPoint();

	br.x = m_max.x;
	br.y = MainFrame::height - m_min.y;

	return br;
}

PhysPoint AABB::GetCenter()
{
	PhysPoint center = PhysPoint();

	center.x = m_center.x;
	center.y = MainFrame::height - m_center.y;

	return center;
}