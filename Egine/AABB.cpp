/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-16 *
*************************/

#include "AABB.h"
#include "MainFrame.h"

// NOTE: Default AABB is 20x20, with BL corner at (0,0) Cartesian

/********** CTORS **********/
AABB::AABB()
	: m_width(20.0), m_height(20.0)
{
	m_center = PhysPoint();
	m_center.x = 10;
	m_center.y = 10;
}

AABB::AABB(PhysPoint _center)
	: m_width(20.0), m_height(20.0)
{
	m_center = PhysPoint(_center);
}

AABB::AABB(PhysPoint _center, double _width, double _height)
	: m_width(_width), m_height(_height)
{
	m_center = PhysPoint(_center);
}

AABB::~AABB()
{
}


/********** ACCESSORS **********/
PhysPoint AABB::GetCenter(CoordFlag flag)
{
	PhysPoint center = PhysPoint();

	switch (flag)
	{
	case CoordFlag::Physics:
		center = m_center;
		break;
	case CoordFlag::Drawing:
		center.x = m_center.x;
		center.y = Scene::HEIGHT - m_center.y;
		break;
	}

	return center;
}

PhysPoint AABB::GetBottomLeft(CoordFlag flag)
{
	PhysPoint blPoint = PhysPoint();

	switch (flag)
	{
	case CoordFlag::Physics:
		blPoint.x = m_center.x - (m_width/2);
		blPoint.y = m_center.y - (m_height/2);
		break;
	case CoordFlag::Drawing:
		blPoint.x = m_center.x - (m_width/2);
		blPoint.y = Scene::HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return blPoint;
}

PhysPoint AABB::GetBottomRight(CoordFlag flag)
{
	PhysPoint brPoint = PhysPoint();

	switch (flag)
	{
	case CoordFlag::Physics:
		brPoint.x = m_center.x + (m_width/2);
		brPoint.y = m_center.y - (m_height/2);
		break;
	case CoordFlag::Drawing:
		brPoint.x = m_center.x + (m_width/2);
		brPoint.y = Scene::HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return brPoint;
}

PhysPoint AABB::GetTopLeft(CoordFlag flag)
{
	PhysPoint tlPoint = PhysPoint();

	switch (flag)
	{
	case CoordFlag::Physics:
		tlPoint.x = m_center.x - (m_width/2);
		tlPoint.y = m_center.y + (m_height/2);
		break;
	case CoordFlag::Drawing:
		tlPoint.x = m_center.x - (m_width/2);
		tlPoint.y = Scene::HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return tlPoint;
}

PhysPoint AABB::GetTopRight(CoordFlag flag)
{
	PhysPoint trPoint = PhysPoint();

	switch (flag)
	{
	case CoordFlag::Physics:
		trPoint.x = m_center.x + (m_width/2);
		trPoint.y = m_center.y + (m_height/2);
		break;
	case CoordFlag::Drawing:
		trPoint.x = m_center.x + (m_width/2);
		trPoint.y = Scene::HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return trPoint;
}

double AABB::GetUpperBound(CoordFlag flag)
{
	double upperBound = 0.0;

	switch (flag)
	{
	case CoordFlag::Physics:
		upperBound = m_center.y + (m_height/2);
		break;
	case CoordFlag::Drawing:
		upperBound = Scene::HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return upperBound;
}

double AABB::GetLowerBound(CoordFlag flag)
{
	double lowerBound = 0.0;

	switch (flag)
	{
	case CoordFlag::Physics:
		lowerBound = m_center.y - (m_height/2);
		break;
	case CoordFlag::Drawing:
		lowerBound = Scene::HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return lowerBound;
}

double AABB::GetLeftBound()
{
	double leftBound = 0.0;

	leftBound = m_center.x - (m_width/2);

	return leftBound;
}

double AABB::GetRightBound()
{
	double rightBound = 0.0;

	rightBound = m_center.x + (m_width/2);

	return rightBound;
}


/********** MUTATORS **********/
void AABB::SetCenter(PhysPoint newCenter)
{
	m_center = newCenter;
}

void AABB::SetWidth(double newWidth)
{
	m_width = newWidth;
}

void AABB::SetHeight(double newHeight)
{
	m_height = newHeight;
}