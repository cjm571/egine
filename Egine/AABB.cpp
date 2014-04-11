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
	m_center = CartPoint();
	m_center.x = 10;
	m_center.y = 10;
}

AABB::AABB(CartPoint _center)
	: m_width(20.0), m_height(20.0)
{
	m_center = CartPoint(_center);
}

AABB::AABB(CartPoint _center, double _width, double _height)
	: m_width(_width), m_height(_height)
{
	m_center = CartPoint(_center);
}

AABB::~AABB()
{
}


/********** ACCESSORS **********/
CartPoint AABB::GetCenter(eCoordSys flag)
{
	CartPoint center = CartPoint();

	switch (flag)
	{
	case eCoordSys::Physics:
		center = m_center;
		break;
	case eCoordSys::Drawing:
		center.x = m_center.x;
		center.y = SCENE_HEIGHT - m_center.y;
		break;
	}

	return center;
}

CartPoint AABB::GetBottomLeft(eCoordSys flag)
{
	CartPoint blPoint = CartPoint();

	switch (flag)
	{
	case eCoordSys::Physics:
		blPoint.x = m_center.x - (m_width/2);
		blPoint.y = m_center.y - (m_height/2);
		break;
	case eCoordSys::Drawing:
		blPoint.x = m_center.x - (m_width/2);
		blPoint.y = SCENE_HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return blPoint;
}

CartPoint AABB::GetBottomRight(eCoordSys flag)
{
	CartPoint brPoint = CartPoint();

	switch (flag)
	{
	case eCoordSys::Physics:
		brPoint.x = m_center.x + (m_width/2);
		brPoint.y = m_center.y - (m_height/2);
		break;
	case eCoordSys::Drawing:
		brPoint.x = m_center.x + (m_width/2);
		brPoint.y = SCENE_HEIGHT - (m_center.y - (m_height/2));
		break;
	}

	return brPoint;
}

CartPoint AABB::GetTopLeft(eCoordSys flag)
{
	CartPoint tlPoint = CartPoint();

	switch (flag)
	{
	case eCoordSys::Physics:
		tlPoint.x = m_center.x - (m_width/2);
		tlPoint.y = m_center.y + (m_height/2);
		break;
	case eCoordSys::Drawing:
		tlPoint.x = m_center.x - (m_width/2);
		tlPoint.y = SCENE_HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return tlPoint;
}

CartPoint AABB::GetTopRight(eCoordSys flag)
{
	CartPoint trPoint = CartPoint();

	switch (flag)
	{
	case eCoordSys::Physics:
		trPoint.x = m_center.x + (m_width/2);
		trPoint.y = m_center.y + (m_height/2);
		break;
	case eCoordSys::Drawing:
		trPoint.x = m_center.x + (m_width/2);
		trPoint.y = SCENE_HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return trPoint;
}

double AABB::GetUpperBound(eCoordSys flag)
{
	double upperBound = 0.0;

	switch (flag)
	{
	case eCoordSys::Physics:
		upperBound = m_center.y + (m_height/2);
		break;
	case eCoordSys::Drawing:
		upperBound = SCENE_HEIGHT - (m_center.y + (m_height/2));
		break;
	}

	return upperBound;
}

double AABB::GetLowerBound(eCoordSys flag)
{
	double lowerBound = 0.0;

	switch (flag)
	{
	case eCoordSys::Physics:
		lowerBound = m_center.y - (m_height/2);
		break;
	case eCoordSys::Drawing:
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
void AABB::SetCenter(CartPoint newCenter)
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


/********** PUBLIC STATICS **********/
bool AABB::CheckOverlap(AABB a, AABB b)
{
	double centerDist = 0.0;
	bool xOverlap = false;
	bool yOverlap = false;
	bool isOverlapping = false;

	// Check X-axis overlap
	centerDist = abs(a.GetCenter().x - b.GetCenter().x);
	if (centerDist - ((a.GetWidth()/2 + b.GetWidth()/2)) <= ERR_COLLISION)
	{
		xOverlap = true;
	}

	// Check Y-axis overlap
	centerDist = abs(a.GetCenter().y - b.GetCenter().y);
	if ((centerDist - (a.GetHeight()/2 + b.GetHeight()/2)) <= ERR_COLLISION)
	{
		yOverlap = true;
	}
	
	// AABBs must overlap on ALL AXES for actual overlap to occur
	isOverlapping = xOverlap && yOverlap;
	return isOverlapping;
}