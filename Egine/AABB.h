/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/
#pragma once

#include "StdAfx.h"

class AABB
{
public:
	AABB();
	~AABB();

private:
	// Min and Max X, Y coordinates of AABB
	Point min;
	Point max;
};