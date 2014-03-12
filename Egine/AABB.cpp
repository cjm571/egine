/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-16 *
*************************/

#include "AABB.h"

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
PhysPoint AABB::GetCenter(CoordSys flag)
{
	PhysPoint center = PhysPoint();

	switch (flag)
	{
	case CoordSys::Physics:
		center = m_center;
		break;
	case CoordSys::Drawing:
		center.x = m_center.x;
		center.y = SCENE_HEIGHT - m_center.y;
		break;
	}

	return center;
}

PhysPoint AABB::GetBottomLeft(CoordSys flag)
{
	PhysPoint blPoint = PhysPoint();

	switch (flag)
	{
	case CoordSys::Physics:
		blPoint.x = m_center.x - (m_width/2);
		blPoint.y = m_center.y - (m_height/2);
		break;
	case CoordSys::Drawing:
		blPoint.x = m_center.x - (m_width/2);
		blPoint.y = SCENE_HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return blPoint;
}

PhysPoint AABB::GetBottomRight(CoordSys flag)
{
	PhysPoint brPoint = PhysPoint();

	switch (flag)
	{
	case CoordSys::Physics:
		brPoint.x = m_center.x + (m_width/2);
		brPoint.y = m_center.y - (m_height/2);
		break;
	case CoordSys::Drawing:
		brPoint.x = m_center.x + (m_width/2);
		brPoint.y = SCENE_HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return brPoint;
}

PhysPoint AABB::GetTopLeft(CoordSys flag)
{
	PhysPoint tlPoint = PhysPoint();

	switch (flag)
	{
	case CoordSys::Physics:
		tlPoint.x = m_center.x - (m_width/2);
		tlPoint.y = m_center.y + (m_height/2);
		break;
	case CoordSys::Drawing:
		tlPoint.x = m_center.x - (m_width/2);
		tlPoint.y = SCENE_HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return tlPoint;
}

PhysPoint AABB::GetTopRight(CoordSys flag)
{
	PhysPoint trPoint = PhysPoint();

	switch (flag)
	{
	case CoordSys::Physics:
		trPoint.x = m_center.x + (m_width/2);
		trPoint.y = m_center.y + (m_height/2);
		break;
	case CoordSys::Drawing:
		trPoint.x = m_center.x + (m_width/2);
		trPoint.y = SCENE_HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return trPoint;
}

double AABB::GetUpperBound(CoordSys flag)
{
	double upperBound = 0.0;

	switch (flag)
	{
	case CoordSys::Physics:
		upperBound = m_center.y + (m_height/2);
		break;
	case CoordSys::Drawing:
		upperBound = SCENE_HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return upperBound;
}

double AABB::GetLowerBound(CoordSys flag)
{
	double lowerBound = 0.0;

	switch (flag)
	{
	case CoordSys::Physics:
		lowerBound = m_center.y - (m_height/2);
		break;
	case CoordSys::Drawing:
		lowerBound = SCENE_HEIGHT - (m_center.y - (m_height/2));
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